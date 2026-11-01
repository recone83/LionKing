#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "engine/physics.h"

int main(void)
{
    static const uint32_t velocities[] = {0, 1, 0x1ffff, 0x20000, 0x20001,
        0x7fffffff, 0x80000000, 0xfffdffff, 0xfffe0000, 0xfffe0001, 0xffffffff};
    unsigned int cases = 0;
    for (unsigned int i = 0; i < 11; ++i) {
        uint32_t velocity = velocities[i];
        int64_t signed_velocity = velocity < UINT32_C(0x80000000) ? (int64_t)velocity :
            (int64_t)velocity - INT64_C(0x100000000);
        for (unsigned int fraction = 0; fraction <= 65535; ++fraction) {
            for (unsigned int mode = 0; mode < 3; ++mode) {
                RENDER_OWNER owner = {32767, -123};
                ENGINE_MOTION motion = {(unsigned short)fraction, 17, velocity, 18};
                uint32_t expected_velocity = mode == 2 ?
                    (signed_velocity > -0x20000 ? UINT32_C(0xfffe0000) : velocity) :
                    mode == 1 ? 0 : signed_velocity < 0x20000 ? UINT32_C(0x20000) : velocity;
                uint32_t expected = UINT32_C(0x7fff0000) + fraction + expected_velocity;
                int status = mode == 2 ? engine_motion_left(&motion, &owner) :
                    engine_motion_right(&motion, &owner, mode == 1 ? 0x10 : 0);
                assert(status == 0 && motion.velocity_x == expected_velocity);
                assert(((uint32_t)(unsigned short)owner.x << 16 | motion.fraction_x) == expected);
                assert(owner.y == -123 && motion.fraction_y == 17 && motion.velocity_y == 18);
                ++cases;
            }
        }
    }
    assert(engine_motion_right(0, 0, 0) == -1 && engine_motion_left(0, 0) == -1);
    printf("PASS: %u original directional integration cases, signed +/-2 minimums, "
        "right-only stop flag, all fractions, overflow and unchanged Y\n", cases);
    return 0;
}
