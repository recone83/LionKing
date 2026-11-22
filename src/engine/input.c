#ifdef LK_DOS64_NATIVE
#include "input.h"

void input_initialize(ENGINE_INPUT *input)
{
    /* DS:0x2b0a: Up, Down, Left, Right, Space, Alt, Ctrl, Shift. */
    const ENGINE_CONTROLS defaults = ENGINE_CONTROLS_DEFAULT;
    *input = (ENGINE_INPUT){0};
    input->repeat_mask = 0xffff;
    for (unsigned int i = 0; i < CONTROL_COUNT; ++i) {
        input->bindings[i] = defaults.keys[i];
    }
}

int input_poll_controls(ENGINE_INPUT *input, const DOS64_INPUT *keys)
{
    static const unsigned short masks[CONTROL_COUNT] = {1, 2, 4, 8, 0x20, 0x10, 0x40, 0x100};
    if (!input || !keys) {
        return -1;
    }
    unsigned short held = 0, taps = 0;
    for (unsigned int i = 0; i < CONTROL_COUNT; ++i) {
        unsigned int key = input->bindings[i];
        if (keys->KeyDown[key]) {
            held |= masks[i];
        }
        if (keys->KeyPressed[key]) {
            taps |= masks[i];
        }
    }
    if (input->replay_active) {
        if (!input->replay || input->replay_position > input->replay_size ||
            input->replay_size - input->replay_position < 2) {
            return -1;
        }
        held = (unsigned short)((held & 0xff00) | input->replay[input->replay_position]);
        if (!input->replay_remaining) {
            /* A stored counter N lasts N+1 updates: original decrements to 0xff. */
            input->replay_remaining = input->replay[input->replay_position + 1] + 1U;
        }
        --input->replay_remaining;
        if (!input->replay_remaining) {
            input->replay_position += 2;
        }
        taps &= 0xff00;
    }
    input->pressed = (unsigned short)((held & ~(input->held & input->repeat_mask)) |
        (taps & ~input->held));
    input->held = held;
    return 0;
}
#else
#include "input_legacy.inc"
#endif
