#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/animation.h"
#include "engine/animation_data.h"

static short wrapped(int value)
{
    unsigned int bits = (unsigned int)value & 0xffffU;
    return (short)(bits < 0x8000U ? (int)bits : (int)bits - 65536);
}

int main(void)
{
    unsigned char original[ANIMATION_MOVEMENT_SIZE];
    FILE *dump = fopen("bin/obj2_data.bin", "rb");
    assert(dump && fseek(dump, ANIMATION_MOVEMENT_BASE, SEEK_SET) == 0);
    assert(fread(original, 1, sizeof(original), dump) == sizeof(original));
    assert(fclose(dump) == 0);
    assert(memcmp(original, animation_movement_data, sizeof(original)) == 0);

    /* Independent timeline decoded from DS:0x362b, including N+1 durations. */
    static const unsigned int descriptors[] = {
        0xfa28, 0xf898, 0xf8ac, 0xf8c0, 0xf8d4, 0xf8e8,
        0xf8fc, 0xf910, 0xf924, 0xf938, 0xf94c, 0xf960, 0xfc30
    };
    static const unsigned int durations[] = {18, 2, 4, 6, 6, 6, 4, 2, 4, 4, 4, 4, 100};
    for (unsigned int facing = 0; facing < 2; ++facing) {
        RENDER_POOL pool;
        RENDER_OWNER owner = {32760, -32760};
        render_initialize_nodes(&pool);
        RENDER_NODE *node = render_acquire_node(&pool, &owner, 0, 0,
            animation_movement_data + 0xfa28 - ANIMATION_MOVEMENT_BASE, 20);
        assert(node);
        node->pass_flags = facing ? 8 : 0;
        ANIMATION_PROGRAM program;
        assert(animation_movement_initialize(&program) == 0);
        unsigned int frame = 0, remaining = durations[0];
        int expected_x = owner.x;
        for (unsigned int tick = 1; tick <= 2000; ++tick) {
            if (tick == 500 || tick == 1000) {
                node->pass_flags ^= 8;
            }
            assert(animation_program_step(&program, node, &owner, 0, 0) == 0);
            assert(program.script.position == 0x3266 && program.visual_ready &&
                program.motion_ready && program.unsupported_handler == 0);
            assert(node->parts == animation_movement_data +
                descriptors[frame] - ANIMATION_MOVEMENT_BASE);
            assert(node->parts_size == 20 && owner.y == -32760);
            if (tick == 1) {
                expected_x = wrapped(expected_x + (facing ? 80 : -80));
                assert(!!(node->pass_flags & 8) == facing);
            }
            if (tick == 19) {
                expected_x = wrapped(expected_x + (facing ? -80 : 80));
                assert(!!(node->pass_flags & 8) == !facing);
            }
            if (tick > 60) {
                expected_x = wrapped(expected_x + ((node->pass_flags & 8) ? 2 : -2));
            }
            assert(owner.x == expected_x);
            assert(program.state == (tick >= 61 ? 1 : 0));
            assert(program.visual.remaining == remaining - 1);
            if (--remaining == 0) {
                if (frame < 12) {
                    ++frame;
                }
                remaining = durations[frame];
            }
        }
    }
    puts("PASS: original DS:0x3615 visual/motion program, 4000 updates, "
        "exact descriptors/durations/state, facing changes, 16-bit coordinate wrap");
    return 0;
}
