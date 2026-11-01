#ifndef DOS64_STDIO_H
#define DOS64_STDIO_H

/* Minimal stdio for DOS64 programs, built on DOS64_API.Write. Header-only, no libc needed.
 * Call stdio_init(Api) first thing in start(). printf supports: %% %c %s %d %i %u %x %X %p,
 * the l / ll / z length modifiers, '0' and '-' flags and a field width. */

#include "dos64_api.h"

/* GCC builtins, so no compiler headers are needed. */
typedef __builtin_va_list va_list;
#define va_start(Ap, Last) __builtin_va_start(Ap, Last)
#define va_arg(Ap, Type) __builtin_va_arg(Ap, Type)
#define va_end(Ap) __builtin_va_end(Ap)

static const DOS64_API *Dos64Stdio;

static inline void stdio_init(const DOS64_API *Api)
{
    Dos64Stdio = Api;
}

static inline int putchar(int Character)
{
    char Text[2];

    Text[0] = (char)Character;
    Text[1] = '\0';
    Dos64Stdio->Write(Text);
    return (unsigned char)Character;
}

static inline int puts(const char *Text)
{
    Dos64Stdio->Write(Text);
    Dos64Stdio->Write("\n");
    return 0;
}

static inline int vprintf(const char *Format, va_list Arguments)
{
    char Chunk[128];
    int Used = 0;
    int Total = 0;

#define DOS64_EMIT(Ch) \
    do { Chunk[Used++] = (Ch); Total++; \
         if (Used == (int)sizeof(Chunk) - 1) { Chunk[Used] = '\0'; Dos64Stdio->Write(Chunk); Used = 0; } } while (0)

    for (; *Format != '\0'; Format++) {
        char Digits[24];
        int Length = 0;
        int Width = 0;
        int Left = 0;
        int Zero = 0;
        int Long = 0;
        int Base = 10;
        int Signed = 0;
        int Upper = 0;
        int Negative = 0;
        unsigned long long Value;
        const char *Text = 0;
        int TextLength = 0;
        int Pad;

        if (*Format != '%') {
            DOS64_EMIT(*Format);
            continue;
        }
        Format++;
        for (;; Format++) {
            if (*Format == '-') { Left = 1; }
            else if (*Format == '0') { Zero = 1; }
            else { break; }
        }
        while (*Format >= '0' && *Format <= '9') {
            Width = Width * 10 + (*Format++ - '0');
        }
        while (*Format == 'l' || *Format == 'z') {
            Long = 1;
            Format++;
        }
        switch (*Format) {
        case '%': DOS64_EMIT('%'); continue;
        case 'c': Digits[0] = (char)va_arg(Arguments, int); Text = Digits; TextLength = 1; break;
        case 's':
            Text = va_arg(Arguments, const char *);
            if (Text == 0) { Text = "(null)"; }
            while (Text[TextLength] != '\0') { TextLength++; }
            break;
        case 'd': case 'i': Signed = 1; break;
        case 'u': break;
        case 'x': Base = 16; break;
        case 'X': Base = 16; Upper = 1; break;
        case 'p': Base = 16; Long = 1; Zero = 1; Width = 18; DOS64_EMIT('0'); DOS64_EMIT('x'); Width -= 2; break;
        case '\0': Format--; continue;
        default: DOS64_EMIT('%'); DOS64_EMIT(*Format); continue;
        }
        if (Text == 0) {
            if (Signed) {
                long long Number = Long ? va_arg(Arguments, long long) : va_arg(Arguments, int);

                Negative = Number < 0;
                Value = Negative ? 0ULL - (unsigned long long)Number : (unsigned long long)Number;
            } else {
                Value = Long ? va_arg(Arguments, unsigned long long) : va_arg(Arguments, unsigned int);
            }
            do {
                int Digit = (int)(Value % (unsigned)Base);

                Digits[sizeof(Digits) - 1 - Length++] = (char)(Digit < 10 ? '0' + Digit : (Upper ? 'A' : 'a') + Digit - 10);
                Value /= (unsigned)Base;
            } while (Value != 0);
            Text = &Digits[sizeof(Digits) - Length];
            TextLength = Length;
        }
        Pad = Width - TextLength - Negative;
        if (Negative && Zero && !Left) { DOS64_EMIT('-'); Negative = 0; }
        while (!Left && Pad-- > 0) { DOS64_EMIT(Zero && *Format != 's' && *Format != 'c' ? '0' : ' '); }
        if (Negative) { DOS64_EMIT('-'); }
        for (Length = 0; Length < TextLength; Length++) { DOS64_EMIT(Text[Length]); }
        while (Left && Pad-- > 0) { DOS64_EMIT(' '); }
    }
    Chunk[Used] = '\0';
    if (Used != 0) {
        Dos64Stdio->Write(Chunk);
    }
#undef DOS64_EMIT
    return Total;
}

static inline int printf(const char *Format, ...)
{
    va_list Arguments;
    int Count;

    va_start(Arguments, Format);
    Count = vprintf(Format, Arguments);
    va_end(Arguments);
    return Count;
}

#endif
