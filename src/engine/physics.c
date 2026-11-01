#ifdef LK_DOS64_NATIVE
#include "physics.h"

uint32_t engine_add_velocity(uint32_t velocity, uint32_t increment,
    unsigned char flags)
{
    uint32_t result = velocity + increment;
    if (!(flags & 2) && result < UINT32_C(0x80000000) && result > UINT32_C(0x70000)) {
        result = UINT32_C(0x70000);
    }
    return result;
}

static void integrate(short *coordinate, unsigned short *fraction, uint32_t velocity)
{
    uint32_t position = ((uint32_t)(unsigned short)*coordinate << 16) | *fraction;
    position += velocity;
    unsigned int high = position >> 16;
    *coordinate = (short)(high < 0x8000 ? (int)high : (int)high - 65536);
    *fraction = (unsigned short)position;
}

int engine_motion_x(ENGINE_MOTION *motion, RENDER_OWNER *owner)
{
    if (!motion || !owner) {
        return -1;
    }
    integrate(&owner->x, &motion->fraction_x, motion->velocity_x);
    return 0;
}

int engine_motion_y(ENGINE_MOTION *motion, RENDER_OWNER *owner)
{
    if (!motion || !owner) {
        return -1;
    }
    integrate(&owner->y, &motion->fraction_y, motion->velocity_y);
    return 0;
}

int engine_motion_gravity(ENGINE_MOTION *motion, RENDER_OWNER *owner)
{
    if (!motion || !owner) {
        return -1;
    }
    /* 0x1a7ed calls the capped helper directly, regardless of object flags. */
    motion->velocity_y = engine_add_velocity(motion->velocity_y, UINT32_C(0x4e00), 0);
    integrate(&owner->y, &motion->fraction_y, motion->velocity_y);
    return 0;
}

int engine_motion_accelerate_x(ENGINE_MOTION *motion, RENDER_OWNER *owner,
    uint32_t increment)
{
    if (!motion || !owner) {
        return -1;
    }
    uint32_t velocity = motion->velocity_x + increment;
    if (velocity >= UINT32_C(0x80000000) && velocity < UINT32_C(0xfffc0000)) {
        velocity = UINT32_C(0xfffc0000);
    } else if (velocity < UINT32_C(0x80000000) && velocity > UINT32_C(0x40000)) {
        velocity = UINT32_C(0x40000);
    }
    motion->velocity_x = velocity;
    integrate(&owner->x, &motion->fraction_x, velocity);
    return 0;
}

int engine_motion_brake_x(ENGINE_MOTION *motion, uint32_t decrement)
{
    if (!motion) {
        return -1;
    }
    uint32_t velocity = motion->velocity_x;
    uint32_t absolute_velocity = velocity & UINT32_C(0x80000000) ? 0U - velocity : velocity;
    uint32_t absolute_decrement = decrement & UINT32_C(0x80000000) ? 0U - decrement : decrement;
    /* x86 abs(INT_MIN) remains negative, including in the signed comparison. */
    int64_t a = absolute_velocity < UINT32_C(0x80000000) ? (int64_t)absolute_velocity :
        (int64_t)absolute_velocity - INT64_C(0x100000000);
    int64_t b = absolute_decrement < UINT32_C(0x80000000) ? (int64_t)absolute_decrement :
        (int64_t)absolute_decrement - INT64_C(0x100000000);
    motion->velocity_x = a < b ? 0 : velocity - decrement;
    return 0;
}

int engine_motion_right(ENGINE_MOTION *motion, RENDER_OWNER *owner,
    unsigned char flags_high)
{
    if (!motion || !owner) {
        return -1;
    }
    if (flags_high & 0x10) {
        motion->velocity_x = 0;
    } else if (motion->velocity_x >= UINT32_C(0x80000000) ||
        motion->velocity_x < UINT32_C(0x20000)) {
        motion->velocity_x = UINT32_C(0x20000);
    }
    integrate(&owner->x, &motion->fraction_x, motion->velocity_x);
    return 0;
}

int engine_motion_left(ENGINE_MOTION *motion, RENDER_OWNER *owner)
{
    if (!motion || !owner) {
        return -1;
    }
    if (motion->velocity_x < UINT32_C(0x80000000) ||
        motion->velocity_x > UINT32_C(0xfffe0000)) {
        motion->velocity_x = UINT32_C(0xfffe0000);
    }
    integrate(&owner->x, &motion->fraction_x, motion->velocity_x);
    return 0;
}
#else
/* Original helpers remain in recovered/block_08000.c. */
#endif
