#include <string.h>

#include "dos64_opl.h"

extern void I_Error(char *Format, ...);

#define OPL_VOICES 18
#define OPL_CHANNELS 16
#define INSTRUMENT_SIZE 36
#define INSTRUMENT_COUNT 175

typedef struct {
    unsigned int Program, Volume, Expression, Pan, Pitch, Sustain, Modulation;
} opl_channel_t;

typedef struct {
    unsigned int Active, Channel, Key, Velocity, Released, Age, Second;
    unsigned int Frequency;
    const unsigned char *Instrument;
} opl_voice_t;

static const unsigned char *Instruments;
static opl_channel_t Channels[OPL_CHANNELS];
static opl_voice_t Voices[OPL_VOICES];
static unsigned int Age;
static const unsigned int OperatorOffsets[9] = {0, 1, 2, 8, 9, 10, 16, 17, 18};

static unsigned int VoiceRegister(unsigned int Voice, unsigned int Register)
{
    return (Voice / 9) * 0x100 + Register + Voice % 9;
}

static unsigned int OperatorRegister(unsigned int Voice, unsigned int Carrier,
                                     unsigned int Register)
{
    return (Voice / 9) * 0x100 + Register +
           OperatorOffsets[Voice % 9] + Carrier * 3;
}

static const unsigned char *VoicePatch(const opl_voice_t *Voice)
{
    return Voice->Instrument + 4 + Voice->Second * 16;
}

static void VoiceOff(unsigned int Index, int Immediate)
{
    opl_voice_t *Voice = &Voices[Index];

    Dos64OplWrite(VoiceRegister(Index, 0xb0), Voice->Frequency >> 8);
    if (Immediate) {
        Dos64OplWrite(OperatorRegister(Index, 0, 0x40), 0x3f);
        Dos64OplWrite(OperatorRegister(Index, 1, 0x40), 0x3f);
        Dos64OplWrite(OperatorRegister(Index, 0, 0x80), 0x0f);
        Dos64OplWrite(OperatorRegister(Index, 1, 0x80), 0x0f);
    }
    Voice->Active = 0;
}

static void VoiceVolume(unsigned int Index)
{
    /* Extra OPL attenuation (0.75 dB steps) for MIDI level v: 40*log10(127/v). */
    static const unsigned char Attenuation[128] = {
        63, 63, 63, 63, 63, 63, 63, 63, 63, 61, 59, 57, 55, 53, 51, 49,
        48, 47, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 33,
        32, 31, 31, 30, 29, 29, 28, 27, 27, 26, 26, 25, 25, 24, 24, 23,
        23, 22, 22, 21, 21, 20, 20, 19, 19, 19, 18, 18, 17, 17, 17, 16,
        16, 16, 15, 15, 14, 14, 14, 13, 13, 13, 13, 12, 12, 12, 11, 11,
        11, 10, 10, 10, 10,  9,  9,  9,  8,  8,  8,  8,  7,  7,  7,  7,
         6,  6,  6,  6,  6,  5,  5,  5,  5,  4,  4,  4,  4,  4,  3,  3,
         3,  3,  3,  2,  2,  2,  2,  2,  1,  1,  1,  1,  1,  0,  0,  0
    };
    const opl_voice_t *Voice = &Voices[Index];
    const opl_channel_t *Channel = &Channels[Voice->Channel];
    const unsigned char *Patch = VoicePatch(Voice);
    unsigned int Volume = Voice->Velocity * Channel->Volume * Channel->Expression;

    Volume /= 127 * 127;
    if (Volume > 127) {
        Volume = 127;
    }
    for (unsigned int Carrier = 0; Carrier < 2; Carrier++) {
        const unsigned char *Operator = Patch + Carrier * 7;
        unsigned int Level = Operator[5] & 63;

        if (Carrier || (Patch[6] & 1)) {
            Level += Attenuation[Volume];
            if (Level > 63) {
                Level = 63;
            }
        }
        Dos64OplWrite(OperatorRegister(Index, Carrier, 0x40),
                      (Operator[4] & 0xc0) | Level);
        Dos64OplWrite(OperatorRegister(Index, Carrier, 0x20),
                      Operator[0] | (Channel->Modulation >= 40 ? 0x40 : 0));
    }
}

static void VoicePan(unsigned int Index)
{
    const opl_voice_t *Voice = &Voices[Index];
    unsigned int Pan = Channels[Voice->Channel].Pan;
    unsigned int Bits = Pan < 48 ? 0x10 : Pan > 80 ? 0x20 : 0x30;

    Dos64OplWrite(VoiceRegister(Index, 0xc0), (VoicePatch(Voice)[6] & 15) | Bits);
}

static void VoicePitch(unsigned int Index)
{
    opl_voice_t *Voice = &Voices[Index];
    const unsigned char *Patch = VoicePatch(Voice);
    int Offset = Patch[14] | (Patch[15] << 8);
    double Note, Frequency;
    unsigned int Block = 0, Number;

    if (Offset >= 32768) {
        Offset -= 65536;
    }
    Note = (Voice->Instrument[0] & 1) ? Voice->Instrument[3] :
           Voice->Channel == 15 ? 60 : Voice->Key;
    if (!(Voice->Instrument[0] & 1)) {
        Note += Offset;
        while (Note < 0) {
            Note += 12;
        }
        while (Note > 95) {
            Note -= 12;
        }
    }
    Note += ((int)Channels[Voice->Channel].Pitch - 128) / 64.0;
    if (Voice->Second) {
        Note += ((int)(Voice->Instrument[2] / 2) - 64) / 32.0;
    }
    Frequency = 440.0 * Dos64OplExp2((Note - 69.0) / 12.0);
    Frequency *= 1048576.0 / (14318180.0 / 288.0);
    while (Frequency > 1023.0 && Block < 7) {
        Frequency *= 0.5;
        Block++;
    }
    Number = Frequency > 1023.0 ? 1023 : (unsigned int)(Frequency + 0.5);
    Voice->Frequency = (Block << 10) | Number;
    Dos64OplWrite(VoiceRegister(Index, 0xa0), Voice->Frequency & 255);
    Dos64OplWrite(VoiceRegister(Index, 0xb0), (Voice->Frequency >> 8) | 0x20);
}

void Dos64OplSilence(void)
{
    for (unsigned int Index = 0; Index < OPL_VOICES; Index++) {
        VoiceOff(Index, 1);
    }
}

void Dos64OplReset(void)
{
    Dos64OplCoreInit(44100);
    memset(Voices, 0, sizeof(Voices));
    Age = 0;
    for (unsigned int Index = 0; Index < OPL_CHANNELS; Index++) {
        Channels[Index] = (opl_channel_t){0, 100, 127, 64, 128, 0, 0};
    }
}

void Dos64OplInit(const unsigned char *Bank, int Length)
{
    if (!Bank || Length < 8 + INSTRUMENT_SIZE * INSTRUMENT_COUNT ||
        memcmp(Bank, "#OPL_II#", 8)) {
        I_Error("Hexen: GENMIDI has an invalid OPL instrument bank");
        return;
    }
    Instruments = Bank + 8;
    Dos64OplReset();
}

void Dos64OplNoteOff(unsigned int Channel, unsigned int Note)
{
    for (unsigned int Index = 0; Index < OPL_VOICES; Index++) {
        opl_voice_t *Voice = &Voices[Index];

        if (Voice->Active && Voice->Channel == Channel && Voice->Key == Note) {
            if (Channels[Channel].Sustain >= 64) {
                Voice->Released = 1;
            } else {
                VoiceOff(Index, 0);
            }
        }
    }
}

void Dos64OplNoteOn(unsigned int Channel, unsigned int Note, unsigned int Velocity)
{
    unsigned int Instrument = Channels[Channel].Program;
    const unsigned char *Data;

    if (!Velocity) {
        Dos64OplNoteOff(Channel, Note);
        return;
    }
    if (Channel == 15) {
        /* GENMIDI defines percussion keys 35..81 only. */
        if (Note < 35 || Note > 81) {
            return;
        }
        Instrument = 128 + Note - 35;
    }
    Data = Instruments + Instrument * INSTRUMENT_SIZE;
    for (unsigned int Second = 0; Second <= ((Data[0] & 4) != 0); Second++) {
        unsigned int Index, Oldest = 0;
        opl_voice_t *Voice;
        const unsigned char *Patch;

        for (Index = 0; Index < OPL_VOICES; Index++) {
            if (!Voices[Index].Active) {
                break;
            }
            if (Voices[Index].Age < Voices[Oldest].Age) {
                Oldest = Index;
            }
        }
        if (Index == OPL_VOICES) {
            Index = Oldest;
        }
        VoiceOff(Index, 1);
        Voice = &Voices[Index];
        *Voice = (opl_voice_t){1, Channel, Note, Velocity, 0, ++Age, Second, 0, Data};
        Patch = VoicePatch(Voice);
        for (unsigned int Carrier = 0; Carrier < 2; Carrier++) {
            const unsigned char *Operator = Patch + Carrier * 7;

            Dos64OplWrite(OperatorRegister(Index, Carrier, 0x60), Operator[1]);
            Dos64OplWrite(OperatorRegister(Index, Carrier, 0x80), Operator[2]);
            Dos64OplWrite(OperatorRegister(Index, Carrier, 0xe0), Operator[3] & 7);
        }
        VoiceVolume(Index);
        VoicePan(Index);
        VoicePitch(Index);
    }
}

void Dos64OplPitch(unsigned int Channel, unsigned int Pitch)
{
    Channels[Channel].Pitch = Pitch;
    for (unsigned int Index = 0; Index < OPL_VOICES; Index++) {
        if (Voices[Index].Active && Voices[Index].Channel == Channel) {
            VoicePitch(Index);
        }
    }
}

void Dos64OplController(unsigned int Channel, unsigned int Controller, unsigned int Value)
{
    opl_channel_t *State = &Channels[Channel];

    switch (Controller) {
    case 0: State->Program = Value; return;
    case 2: State->Modulation = Value; break;
    case 3: State->Volume = Value; break;
    case 4: State->Pan = Value; break;
    case 5: State->Expression = Value; break;
    case 8: State->Sustain = Value; break;
    case 14:
        State->Expression = 127;
        State->Pitch = 128;
        State->Sustain = State->Modulation = 0;
        break;
    default: break;
    }
    for (unsigned int Index = 0; Index < OPL_VOICES; Index++) {
        opl_voice_t *Voice = &Voices[Index];

        if (Voice->Channel != Channel) {
            continue;
        }
        if (Controller == 10) {
            VoiceOff(Index, 1);
        } else if (!Voice->Active) {
            continue;
        } else if (Controller == 11) {
            Dos64OplNoteOff(Channel, Voice->Key);
        } else if (Voice->Released && State->Sustain < 64) {
            VoiceOff(Index, 0);
        } else {
            VoiceVolume(Index);
            VoicePan(Index);
            VoicePitch(Index);
        }
    }
}
