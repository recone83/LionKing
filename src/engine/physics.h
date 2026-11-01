#ifndef LIONKING_PHYSICS_H
#define LIONKING_PHYSICS_H

#include <stdint.h>
#include "render.h"

typedef struct {
    unsigned short fraction_x;
    unsigned short fraction_y;
    uint32_t velocity_x;
    uint32_t velocity_y;
} ENGINE_MOTION;

uint32_t engine_add_velocity(uint32_t velocity, uint32_t increment,
    unsigned char flags);
int engine_motion_x(ENGINE_MOTION *motion, RENDER_OWNER *owner);
int engine_motion_y(ENGINE_MOTION *motion, RENDER_OWNER *owner);
int engine_motion_gravity(ENGINE_MOTION *motion, RENDER_OWNER *owner);

#endif
