#ifndef LIONKING_INPUT_H
#define LIONKING_INPUT_H

#include "dos64_api.h"

typedef struct {
    unsigned short held;
    unsigned short pressed;
    unsigned short repeat_mask;
    unsigned char bindings[8];
    const unsigned char *replay;
    unsigned int replay_size;
    unsigned int replay_position;
    unsigned int replay_remaining;
    int replay_active;
} ENGINE_INPUT;

void input_initialize(ENGINE_INPUT *input);
int input_poll_controls(ENGINE_INPUT *input, const DOS64_INPUT *keys);

#endif
