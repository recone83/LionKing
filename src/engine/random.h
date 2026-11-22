#ifndef LIONKING_RANDOM_H
#define LIONKING_RANDOM_H

#include <stdint.h>

static inline unsigned int engine_random_byte(uint32_t *state)
{
    unsigned int low = *state & 255;
    unsigned int middle = (*state >> 8) & 255;
    unsigned int high = (*state >> 16) & 255;
    unsigned int next_low = ((low << 1) | ((high >> 1) & 1)) & 255;
    unsigned int next_middle = ((middle << 1) | (low >> 7)) & 255;
    unsigned int difference = ((high >> 2) - high - (middle >> 7)) & 255;
    unsigned int next_high = (high >> 1) | ((difference & 1) << 7);
    *state = next_low | (next_middle << 8) | (next_high << 16);
    return next_high ^ next_middle;
}

#endif
