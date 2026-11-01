#ifndef LIONKING_ANIMATION_DATA_H
#define LIONKING_ANIMATION_DATA_H

#include "animation.h"

#define ANIMATION_IDLE_BASE 0x6531U
#define ANIMATION_IDLE_SIZE (0x8048U - ANIMATION_IDLE_BASE)
#define ANIMATION_IDLE_START 0x6531U
#define ANIMATION_IDLE_LOOP 0x6b4eU
#define ANIMATION_IDLE_SCRIPT_BASE 0x5f84U
#define ANIMATION_IDLE_SCRIPT_SIZE 22U

extern const unsigned char animation_idle_data[ANIMATION_IDLE_SIZE];
extern const unsigned char animation_idle_script[ANIMATION_IDLE_SCRIPT_SIZE];

#define ANIMATION_MOVEMENT_BASE 0x3252U
#define ANIMATION_MOVEMENT_SIZE (0xfc44U - ANIMATION_MOVEMENT_BASE)
#define ANIMATION_MOVEMENT_START 0x3615U

extern const unsigned char animation_movement_data[ANIMATION_MOVEMENT_SIZE];
int animation_movement_initialize(ANIMATION_PROGRAM *program);

#define ANIMATION_FALLING_BASE 0xe4b4U
#define ANIMATION_FALLING_SIZE (0x1675aU - ANIMATION_FALLING_BASE)
#define ANIMATION_FALLING_START 0x16741U
#define ANIMATION_FALLING_DEFINITION 0x162feU
#define ANIMATION_TIMED_START 0x16728U
#define ANIMATION_TIMED_DEFINITION 0x162f0U

extern const unsigned char animation_falling_data[ANIMATION_FALLING_SIZE];
int animation_falling_initialize(ANIMATION_PROGRAM *program);
int animation_timed_initialize(ANIMATION_PROGRAM *program);

#endif
