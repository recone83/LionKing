#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "engine/physics.h"

static int64_t signed_bits(uint32_t value)
{
    return value < UINT32_C(0x80000000) ? (int64_t)value :
        (int64_t)value - INT64_C(0x100000000);
}

static int64_t original_absolute(uint32_t value)
{
    int64_t signed_value = signed_bits(value);
    return signed_value == -INT64_C(2147483648) ? signed_value :
        signed_value < 0 ? -signed_value : signed_value;
}

int main(void)
{
    static const uint32_t values[] = {0, 1, 0x10000, 0x20000, 0x7fffffff,
        0x80000000, 0xfffffffe, 0xffffffff, 0xffff0000};
    unsigned int cases = 0;
    for (unsigned int i = 0; i < 9; ++i) {
        for (unsigned int bits = 0; bits <= 65535; ++bits) {
            uint32_t velocity = values[i];
            uint32_t decrements[] = {bits, 0U - bits, values[bits % 9]};
            for (unsigned int d = 0; d < 3; ++d) {
                ENGINE_MOTION motion = {17, 18, velocity, 19};
                uint32_t decrement = decrements[d];
                uint32_t expected = original_absolute(velocity) < original_absolute(decrement) ?
                    0 : velocity - decrement;
                assert(engine_motion_brake_x(&motion, decrement) == 0);
                assert(motion.velocity_x == expected && motion.velocity_y == 19 &&
                    motion.fraction_x == 17 && motion.fraction_y == 18);
                ++cases;
            }
        }
    }
    assert(engine_motion_brake_x(0, 0) == -1);
    printf("PASS: %u original horizontal braking cases, strict magnitude threshold, "
        "signed subtraction and abs(INT_MIN) behavior\n", cases);
    return 0;
}
