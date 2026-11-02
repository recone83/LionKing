#ifndef HEXEN_DOS64_OPL_H
#define HEXEN_DOS64_OPL_H

double Dos64OplExp2(double Value);
void Dos64OplCoreInit(unsigned int Rate);
void Dos64OplWrite(unsigned int Register, unsigned char Value);
void Dos64OplSamples(short *Samples, unsigned int Frames);

void Dos64OplInit(const unsigned char *Bank, int Length);
void Dos64OplReset(void);
void Dos64OplSilence(void);
void Dos64OplNoteOn(unsigned int Channel, unsigned int Note, unsigned int Velocity);
void Dos64OplNoteOff(unsigned int Channel, unsigned int Note);
void Dos64OplPitch(unsigned int Channel, unsigned int Pitch);
void Dos64OplController(unsigned int Channel, unsigned int Controller, unsigned int Value);

#endif
