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
int engine_motion_player_gravity(ENGINE_MOTION *motion, RENDER_OWNER *owner,
    unsigned short form);
int engine_motion_air_gravity(ENGINE_MOTION *motion, RENDER_OWNER *owner,
    unsigned short form, unsigned char flags);
int engine_motion_accelerate_x(ENGINE_MOTION *motion, RENDER_OWNER *owner,
    uint32_t increment);
int engine_motion_brake_x(ENGINE_MOTION *motion, uint32_t decrement);
int engine_motion_right(ENGINE_MOTION *motion, RENDER_OWNER *owner,
    unsigned char movement_flags_high);
int engine_motion_left(ENGINE_MOTION *motion, RENDER_OWNER *owner);

#endif
