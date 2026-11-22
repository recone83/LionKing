#ifndef LIONKING_CONTROLS_H
#define LIONKING_CONTROLS_H

enum {
    CONTROL_UP, CONTROL_DOWN, CONTROL_LEFT, CONTROL_RIGHT,
    CONTROL_JUMP, CONTROL_SLASH, CONTROL_ROAR, CONTROL_MAUL, CONTROL_COUNT
};

typedef struct {
    unsigned char keys[CONTROL_COUNT];
} ENGINE_CONTROLS;

#define ENGINE_CONTROLS_DEFAULT {{0x52, 0x51, 0x50, 0x4f, 0x2c, 0xe2, 0xe0, 0xe1}}

static inline int engine_controls_alternate_roar(const ENGINE_CONTROLS *controls)
{
    if (controls->keys[CONTROL_ROAR] != 0xe0) return 0;
    for (unsigned int i = 0; i < CONTROL_COUNT; ++i)
        if (i != CONTROL_ROAR && controls->keys[i] == 0xe4) return 0;
    return 1;
}

#endif
