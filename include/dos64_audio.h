#ifndef DOS64_AUDIO_H
#define DOS64_AUDIO_H

/* Sound and WAV files for DOS64 programs. Header-only wrappers over DOS64_API.Audio plus a streaming
 * WAV reader/writer. Needs dos64_fs.h (fs_init) for files. Call audio_init(Api) first.
 *
 * Raw output: audio_open(48000), then audio_write() interleaved 16-bit stereo frames; it never blocks,
 * so loop while audio_free_frames() > 0. Unwritten ring space plays silence.
 *
 * WAV: PCM 8/16/24-bit (also WAVE_FORMAT_EXTENSIBLE), 1 or 2 channels, any rate (resampled linearly
 * to the output rate). wav_open(), then call wav_pump() every loop iteration until it returns 1. */

#include "dos64_api.h"
#include "dos64_fs.h"

static const DOS64_API *Dos64Audio;

static inline void audio_init(const DOS64_API *Api) { Dos64Audio = Api; fs_init(Api); }
static inline int audio_present(void) { return (int)Dos64Audio->Audio.Present; }
static inline int audio_open(unsigned int Rate) { return Dos64Audio->Audio.Open(Rate); }
static inline unsigned long long audio_write(const short *Frames, unsigned long long Count)
{
    return Dos64Audio->Audio.Write(Frames, Count);
}
static inline unsigned long long audio_free_frames(void) { return Dos64Audio->Audio.FreeFrames(); }
static inline unsigned long long audio_queued_frames(void) { return Dos64Audio->Audio.QueuedFrames(); }
static inline void audio_stop(void) { Dos64Audio->Audio.Stop(); }
static inline void audio_volume(unsigned int Percent) { Dos64Audio->Audio.Volume(Percent); }

#define WAV_SRC_FRAMES 512
#define WAV_OUT_FRAMES 1024

typedef struct WAV {
    FILE *File;
    const short *Samples;             /* borrowed interleaved 16-bit stereo source */
    unsigned int Rate;                 /* rate stored in the file */
    unsigned int Channels, Bits;
    unsigned long long Frames;         /* total frames in the file */
    unsigned long long Remaining;      /* source frames not read yet */
    unsigned int OutRate;
    unsigned int Phase;
    int PrevL, PrevR, CurL, CurR;
    int Primed;
    unsigned int OutCount, OutPos;
    short Out[WAV_OUT_FRAMES * 2];
    unsigned char Raw[WAV_SRC_FRAMES * 6];
    unsigned int RawCount, RawPos;     /* frames */
    int ReadFailed;
} WAV;

static inline unsigned int wav_u16(const unsigned char *P) { return P[0] | (P[1] << 8); }
static inline unsigned int wav_u32(const unsigned char *P) { return wav_u16(P) | (wav_u16(P + 2) << 16); }

/* Borrows PCM storage until playback has stopped. No file or allocation is required. */
static inline int wav_open_pcm(WAV *Wav, const short *Samples, unsigned long long Frames,
                               unsigned int Rate)
{
    if (!Wav || !Samples || !Frames || Frames > (~0ULL >> 2) || !Rate) {
        if (Dos64Audio && Dos64Audio->Write) { Dos64Audio->Write("WAV FAILED: invalid PCM source\n"); }
        return -1;
    }
    *Wav = (WAV){ .Samples = Samples, .Rate = Rate, .Channels = 2, .Bits = 16,
                  .Frames = Frames, .Remaining = Frames };
    return 0;
}

/* Returns 0 on success, -1 on a missing/unsupported file. Leaves the file open until wav_close(). */
static inline int wav_open(WAV *Wav, const char *Path)
{
    unsigned char Head[12];
    unsigned char Chunk[8];
    int HaveFormat = 0;
    char *Clear = (char *)Wav;

    for (unsigned long long I = 0; I < sizeof(WAV); I++) {
        Clear[I] = 0;
    }
    Wav->File = fopen(Path, "rb");
    if (Wav->File == 0) {
        return -1;
    }
    if (fread(Head, 1, 12, Wav->File) != 12 || Head[0] != 'R' || Head[1] != 'I' || Head[2] != 'F' ||
        Head[3] != 'F' || Head[8] != 'W' || Head[9] != 'A' || Head[10] != 'V' || Head[11] != 'E') {
        goto fail;
    }
    while (fread(Chunk, 1, 8, Wav->File) == 8) {
        unsigned int Size = wav_u32(Chunk + 4);

        if (Chunk[0] == 'f' && Chunk[1] == 'm' && Chunk[2] == 't' && Chunk[3] == ' ') {
            unsigned char Format[40];
            unsigned int Tag;
            unsigned int Take = Size < sizeof(Format) ? Size : (unsigned int)sizeof(Format);

            if (Take < 16 || fread(Format, 1, Take, Wav->File) != Take) {
                goto fail;
            }
            Tag = wav_u16(Format);
            if (Tag == 0xFFFE && Take >= 26) {
                Tag = wav_u16(Format + 24);
            }
            Wav->Channels = wav_u16(Format + 2);
            Wav->Rate = wav_u32(Format + 4);
            Wav->Bits = wav_u16(Format + 14);
            if (Tag != 1 || Wav->Channels < 1 || Wav->Channels > 2 || Wav->Rate == 0 ||
                (Wav->Bits != 8 && Wav->Bits != 16 && Wav->Bits != 24)) {
                goto fail;
            }
            HaveFormat = 1;
            if (Size > Take) {
                fseek(Wav->File, (long long)Size - Take + (Size & 1), SEEK_CUR);
            } else if (Size & 1) {
                fseek(Wav->File, 1, SEEK_CUR);
            }
        } else if (Chunk[0] == 'd' && Chunk[1] == 'a' && Chunk[2] == 't' && Chunk[3] == 'a') {
            unsigned int FrameBytes;

            if (!HaveFormat) {
                goto fail;
            }
            FrameBytes = Wav->Channels * Wav->Bits / 8;
            Wav->Frames = Size / FrameBytes;
            Wav->Remaining = Wav->Frames;
            return 0;
        } else {
            fseek(Wav->File, (long long)Size + (Size & 1), SEEK_CUR);
        }
    }
fail:
    fclose(Wav->File);
    Wav->File = 0;
    return -1;
}

static inline void wav_close(WAV *Wav)
{
    if (Wav->File != 0) {
        fclose(Wav->File);
        Wav->File = 0;
    }
}

/* Fetches the next source frame as 16-bit stereo; returns 0 at the end of the data. */
static inline int wav_next_frame(WAV *Wav, int *Left, int *Right)
{
    const unsigned char *P;
    unsigned int Step = Wav->Bits / 8;

    if (Wav->Samples) {
        if (!Wav->Remaining) { return 0; }
        unsigned long long Index = (Wav->Frames - Wav->Remaining) * 2;
        *Left = Wav->Samples[Index];
        *Right = Wav->Samples[Index + 1];
        Wav->Remaining--;
        return 1;
    }

    if (Wav->RawPos == Wav->RawCount) {
        unsigned long long Want = Wav->Remaining < WAV_SRC_FRAMES ? Wav->Remaining : WAV_SRC_FRAMES;
        unsigned long long Got;

        if (Want == 0) {
            return 0;
        }
        Got = fread(Wav->Raw, Step * Wav->Channels, Want, Wav->File);
        if (Got != Want) { Wav->ReadFailed = 1; }
        Wav->RawCount = (unsigned int)Got;
        Wav->RawPos = 0;
        if (Got == 0) {
            Wav->Remaining = 0;
            return 0;
        }
        Wav->Remaining -= Got;
    }
    P = Wav->Raw + (unsigned long long)Wav->RawPos * Step * Wav->Channels;
    Wav->RawPos++;
    for (unsigned int Channel = 0; Channel < 2; Channel++) {
        const unsigned char *S = P + (Channel < Wav->Channels ? Channel : 0) * Step;
        int Value;

        if (Step == 1) {
            Value = ((int)S[0] - 128) << 8;
        } else if (Step == 2) {
            Value = (short)wav_u16(S);
        } else {
            Value = (short)wav_u16(S + 1);
        }
        if (Channel == 0) {
            *Left = Value;
        } else {
            *Right = Value;
        }
    }
    return 1;
}

/* Produces output frames at OutRate into Wav->Out; returns 0 once the file is exhausted. */
static inline int wav_generate(WAV *Wav)
{
    Wav->OutCount = 0;
    Wav->OutPos = 0;
    while (Wav->OutCount < WAV_OUT_FRAMES) {
        int T;
        int L;
        int R;

        if (!Wav->Primed) {
            if (!wav_next_frame(Wav, &Wav->CurL, &Wav->CurR)) {
                break;
            }
            Wav->PrevL = Wav->CurL;
            Wav->PrevR = Wav->CurR;
            Wav->Primed = 1;
        }
        Wav->Phase += Wav->Rate;
        while (Wav->Phase >= Wav->OutRate) {
            Wav->Phase -= Wav->OutRate;
            Wav->PrevL = Wav->CurL;
            Wav->PrevR = Wav->CurR;
            if (!wav_next_frame(Wav, &Wav->CurL, &Wav->CurR)) {
                Wav->CurL = 0;
                Wav->CurR = 0;
                Wav->Primed = 0;
                return Wav->OutCount != 0;
            }
        }
        T = (int)((unsigned long long)Wav->Phase * 256 / Wav->OutRate);
        L = Wav->PrevL + (((Wav->CurL - Wav->PrevL) * T) >> 8);
        R = Wav->PrevR + (((Wav->CurR - Wav->PrevR) * T) >> 8);
        Wav->Out[Wav->OutCount * 2] = (short)L;
        Wav->Out[Wav->OutCount * 2 + 1] = (short)R;
        Wav->OutCount++;
    }
    return Wav->OutCount != 0;
}

/* Starts playback: opens the audio device at 44100 (for 44100 Hz files) or 48000 Hz. 0 on success. */
static inline int wav_start(WAV *Wav)
{
    Wav->OutRate = Wav->Rate == 44100 ? 44100 : 48000;
    if (audio_open(Wav->OutRate) != 0) {
        return -1;
    }
    Wav->Phase = 0;
    Wav->Primed = 0;
    Wav->OutCount = 0;
    Wav->OutPos = 0;
    return 0;
}

/* Feeds the ring buffer without blocking. Returns 1 when everything has been played. */
static inline int wav_pump(WAV *Wav)
{
    for (;;) {
        unsigned long long Taken;

        if (Wav->OutPos == Wav->OutCount) {
            if (!wav_generate(Wav)) {
                return audio_queued_frames() == 0;
            }
        }
        Taken = audio_write(Wav->Out + Wav->OutPos * 2, Wav->OutCount - Wav->OutPos);
        Wav->OutPos += (unsigned int)Taken;
        if (Wav->OutPos < Wav->OutCount) {
            return 0;
        }
    }
}

/* Writes interleaved 16-bit stereo frames as a canonical 44-byte-header WAV. 0 on success. */
static inline int wav_save(const char *Path, const short *Frames, unsigned long long FrameCount,
                           unsigned int Rate)
{
    unsigned char H[44] = {'R', 'I', 'F', 'F', 0, 0, 0, 0, 'W', 'A', 'V', 'E', 'f', 'm', 't', ' ',
                           16, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 16, 0,
                           'd', 'a', 't', 'a', 0, 0, 0, 0};
    unsigned int Bytes = (unsigned int)(FrameCount * 4);
    unsigned int ByteRate = Rate * 4;
    FILE *File = fopen(Path, "wb");

    if (File == 0) {
        return -1;
    }
    for (int I = 0; I < 4; I++) {
        H[4 + I] = (unsigned char)((Bytes + 36) >> (8 * I));
        H[24 + I] = (unsigned char)(Rate >> (8 * I));
        H[28 + I] = (unsigned char)(ByteRate >> (8 * I));
        H[40 + I] = (unsigned char)(Bytes >> (8 * I));
    }
    if (fwrite(H, 1, 44, File) != 44 || fwrite(Frames, 4, FrameCount, File) != FrameCount) {
        fclose(File);
        return -1;
    }
    return fclose(File) == 0 ? 0 : -1;
}

#endif
