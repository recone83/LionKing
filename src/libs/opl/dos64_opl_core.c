#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dos64_opl.h"

/* OPL only needs powers of two. Range reduction keeps this series on [0, ln 2). */
double Dos64OplExp2(double Value)
{
    int Exponent = (int)Value;
    double Term = 1.0;
    double Result = 1.0;
    double Fraction;

    if (Value < Exponent) {
        Exponent--;
    }
    Fraction = (Value - Exponent) * 0.69314718055994530942;
    for (int Index = 1; Index <= 16; Index++) {
        Term *= Fraction / Index;
        Result += Term;
    }
    while (Exponent > 0) {
        Result *= 2.0;
        Exponent--;
    }
    while (Exponent < 0) {
        Result *= 0.5;
        Exponent++;
    }
    return Result;
}

static double OplPow(double Base, double Exponent)
{
    (void)Base;
    return Dos64OplExp2(Exponent);
}

static double OplSin(double Value)
{
    const double Pi = 3.14159265358979323846;
    double Term, Result;

    while (Value > Pi) {
        Value -= 2.0 * Pi;
    }
    if (Value > Pi / 2.0) {
        Value = Pi - Value;
    } else if (Value < -Pi / 2.0) {
        Value = -Pi - Value;
    }
    Term = Result = Value;
    for (int Index = 1; Index <= 10; Index++) {
        Term *= -Value * Value / ((2 * Index) * (2 * Index + 1));
        Result += Term;
    }
    return Result;
}

static unsigned int Noise = 1;
static double PreviousInput[2];
static double PreviousOutput[2];

static int OplRand(void)
{
    Noise ^= Noise << 13;
    Noise ^= Noise >> 17;
    Noise ^= Noise << 5;
    return (int)(Noise & 0x7fffffff);
}

#define pow OplPow
#define sin OplSin
#define rand OplRand
#define OPLTYPE_IS_OPL3
#include "opl/dosbox/opl.c"
#undef pow
#undef sin
#undef rand

void Dos64OplCoreInit(unsigned int Rate)
{
    Noise = 1;
    memset(PreviousInput, 0, sizeof(PreviousInput));
    memset(PreviousOutput, 0, sizeof(PreviousOutput));
    adlib_init(Rate);
    adlib_write(0x105, 1);
    adlib_write(0x104, 0);
    adlib_write(1, 0x20);
}

void Dos64OplWrite(unsigned int Register, unsigned char Value)
{
    adlib_write(Register, Value);
}

void Dos64OplSamples(short *Samples, unsigned int Frames)
{
    adlib_getsample(Samples, (Bits)Frames);
    /* AC coupling removes the DC bias of rectified OPL waveforms (20 Hz). */
    for (unsigned int Frame = 0; Frame < Frames; Frame++) {
        for (unsigned int Channel = 0; Channel < 2; Channel++) {
            unsigned int Index = Frame * 2 + Channel;
            double Input = Samples[Index];
            double Output = 0.997154539 * (PreviousOutput[Channel] +
                                           Input - PreviousInput[Channel]);

            PreviousInput[Channel] = Input;
            PreviousOutput[Channel] = Output;
            if (Output > 32767.0) {
                Output = 32767.0;
            } else if (Output < -32768.0) {
                Output = -32768.0;
            }
            Samples[Index] = (short)Output;
        }
    }
}
