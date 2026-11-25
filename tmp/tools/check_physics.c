#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "engine/physics.h"

static uint32_t capped(uint32_t value)
{
    int64_t signed_value = value < UINT32_C(0x80000000) ?
        (int64_t)value : (int64_t)value - INT64_C(0x100000000);
    return signed_value > 0x70000 ? UINT32_C(0x70000) : value;
}

static uint32_t position(short coordinate, unsigned short fraction)
{
    return (uint32_t)(unsigned short)coordinate * UINT32_C(65536) + fraction;
}

int main(void)
{
    static const uint32_t velocities[] = {
        0, 1, 0xffff, 0x10000, 0x6ffff, 0x70000, 0x70001,
        0x7fffffff, 0x80000000, 0xffff0000, 0xffffffff
    };
    unsigned int cases = 0;
    for (unsigned int fraction = 0; fraction <= 0xffff; ++fraction) {
        for (unsigned int i = 0; i < sizeof(velocities) / sizeof(velocities[0]); ++i) {
            uint32_t velocity = velocities[i];
            RENDER_OWNER owner = {(short)(fraction < 32768 ? (int)fraction : (int)fraction - 65536), 32767};
            ENGINE_MOTION motion = {(unsigned short)fraction, (unsigned short)fraction, velocity, velocity};
            uint32_t x = position(owner.x, motion.fraction_x) + velocity;
            uint32_t y = position(owner.y, motion.fraction_y) + velocity;
            assert(engine_motion_x(&motion, &owner) == 0);
            assert(position(owner.x, motion.fraction_x) == x);
            assert(owner.y == 32767 && motion.fraction_y == fraction);
            assert(engine_motion_y(&motion, &owner) == 0);
            assert(position(owner.y, motion.fraction_y) == y);
            uint32_t new_velocity = capped(velocity + UINT32_C(0x4e00));
            assert(engine_motion_gravity(&motion, &owner) == 0);
            assert(motion.velocity_y == new_velocity);
            assert(position(owner.y, motion.fraction_y) == y + new_velocity);
            assert(motion.velocity_x == velocity && position(owner.x, motion.fraction_x) == x);
            assert(engine_add_velocity(velocity, fraction, 0) == capped(velocity + fraction));
            assert(engine_add_velocity(velocity, fraction, 2) == velocity + fraction);
            ++cases;
        }
    }
    assert(engine_motion_x(0, 0) == -1 && engine_motion_y(0, 0) == -1 &&
        engine_motion_gravity(0, 0) == -1);
    printf("PASS: %u fixed-point cases, signed velocity cap, overflow, all fractions, "
        "XY integration and original gravity\n", cases);
    return 0;
}
