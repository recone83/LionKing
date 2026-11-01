#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "engine/physics.h"

int main(void)
{
    static const uint32_t values[] = {
        0, 1, 0x3ffff, 0x40000, 0x40001, 0xfffbffff, 0xfffc0000,
        0xfffc0001, 0x7fffffff, 0x80000000, 0xffffffff
    };
    unsigned int cases = 0;
    for (unsigned int a = 0; a < 11; ++a) {
        for (unsigned int b = 0; b < 11; ++b) {
            uint32_t sum = values[a] + values[b];
            int64_t signed_sum = sum < UINT32_C(0x80000000) ? (int64_t)sum :
                (int64_t)sum - INT64_C(0x100000000);
            uint32_t capped = signed_sum < -0x40000 ? UINT32_C(0xfffc0000) :
                signed_sum > 0x40000 ? UINT32_C(0x40000) : sum;
            for (unsigned int fraction = 0; fraction <= 65535; ++fraction) {
                RENDER_OWNER owner = {-32768, 123};
                ENGINE_MOTION motion = {(unsigned short)fraction, 17, values[a], 12345};
                uint32_t expected = UINT32_C(0x80000000) + fraction + capped;
                assert(engine_motion_accelerate_x(&motion, &owner, values[b]) == 0);
                assert(motion.velocity_x == capped);
                assert(((uint32_t)(unsigned short)owner.x << 16 | motion.fraction_x) == expected);
                assert(owner.y == 123 && motion.fraction_y == 17 && motion.velocity_y == 12345);
                ++cases;
            }
        }
    }
    assert(engine_motion_accelerate_x(0, 0, 0) == -1);
    printf("PASS: %u original horizontal acceleration cases, +/-4 cap after "
        "32-bit overflow, all fractions and unchanged Y state\n", cases);
    return 0;
}
