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
#else
/* Original helpers remain in recovered/block_08000.c. */
#endif
