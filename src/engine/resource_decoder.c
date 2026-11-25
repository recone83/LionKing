#include "resource_decoder.h"

/* Reconstruction of 0x1248f-0x12736: MSB-first, width-dependent control codes. */
int resources_decode_dictionary_stream(const unsigned char *source, unsigned int stored,
    unsigned char *destination, unsigned int decoded, RESOURCE_DICTIONARY *dictionary)
{
    unsigned int position = 0, output = 0, bits = 0, accumulator = 0;
    unsigned int width = 9, next = 0x100, previous = 0, first = 0;
    int initial = 1;
    if (!source || !destination || !dictionary || !stored || !decoded) {
        return -1;
    }
    for (;;) {
        while (bits < width) {
            if (position == stored) {
                return -1;
            }
            accumulator = (accumulator << 8) | source[position++];
            bits += 8;
        }
        bits -= width;
        unsigned int mask = (1U << width) - 1;
        unsigned int code = (accumulator >> bits) & mask;
        if (initial) {
            if (code > 255 || output == decoded) {
                return -1;
            }
            destination[output++] = (unsigned char)code;
            previous = first = code;
            initial = 0;
            continue;
        }
        if (code == mask) {
            return output == decoded ? 0 : -1;
        }
        if (code == mask - 1) {
            /* Original reset keeps the current width and buffered bits. */
            next = 0x100;
            initial = 1;
            continue;
        }
        unsigned int current = code, count = 0;
        if (code >= next) {
            if (code != next) {
                return -1;
            }
            dictionary->stack[count++] = (unsigned char)first;
            current = previous;
        }
        unsigned int links = 0;
        while (current > 255) {
            if (current >= next || ++links >= 0xfa0 || count >= 0xfa0) {
                return -1;
            }
            dictionary->stack[count++] = dictionary->suffix[current];
            current = dictionary->prefix[current];
        }
        if (count >= 0xfa0 || count + 1 > decoded - output || next >= 0x4680) {
            return -1;
        }
        first = current;
        dictionary->stack[count++] = (unsigned char)first;
        while (count) {
            destination[output++] = dictionary->stack[--count];
        }
        dictionary->prefix[next] = (unsigned short)previous;
        dictionary->suffix[next] = (unsigned char)first;
        ++next;
        if (next > mask - 2 && width < 14) {
            ++width;
        }
        previous = code;
    }
}
