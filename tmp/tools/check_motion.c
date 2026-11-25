#include <assert.h>
#include <stdio.h>
#include "engine/animation.h"

static short wrap(int value)
{
    unsigned int bits = (unsigned int)value & 65535;
    return (short)(bits < 32768 ? (int)bits : (int)bits - 65536);
}

int main(void)
{
    unsigned char data[10] = {0, 0, 0, 0, 0xff, 0, 0, 0x10, 0, 0};
    RENDER_POOL pool;
    RENDER_OWNER owner = {0};
    render_initialize_nodes(&pool);
    RENDER_NODE *node = render_acquire_node(&pool, &owner, 0, 0, data, sizeof(data));
    ANIMATION_STREAM stream;
    unsigned int cases = 0;
    static const int offsets[] = {-128, -1, 0, 1, 127};
    static const int vertical[] = {-32768, -1, 0, 1, 32767};
    for (unsigned int mirrored = 0; mirrored < 2; ++mirrored) {
        for (unsigned int direction = 0; direction < 2; ++direction) {
            for (unsigned int duration = 0; duration < (mirrored ? 127U : 128U); ++duration) {
                for (unsigned int d = 0; d < 5; ++d) {
                    data[0] = (unsigned char)(duration | (mirrored ? 128 : 0));
                    data[1] = (unsigned char)offsets[d];
                    data[2] = (unsigned char)vertical[d];
                    data[3] = (unsigned char)((unsigned int)vertical[d] >> 8);
                    node->pass_flags = (unsigned char)(direction ? 8 : 0);
                    owner.x = 32767; owner.y = -32768;
                    int x = owner.x, y = owner.y;
                    assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0x1000) == 0);
                    for (unsigned int tick = 0; tick < (duration + 1) * 2; ++tick) {
                        int dx = offsets[d] * ((mirrored && direction) ? -1 : 1);
                        x = wrap(x + dx); y = wrap(y + vertical[d]);
                        assert(animation_motion_step(&stream, node, &owner) == 0);
                        assert(owner.x == x && owner.y == y && stream.position == 0x1004);
                        assert(stream.remaining == ((duration - tick % (duration + 1)) |
                            (mirrored ? 128U : 0U)));
                    }
                    ++cases;
                }
            }
        }
    }
    /* Mirroring follows live direction changes even during a held movement record. */
    data[0] = 0x82; data[1] = 3; data[2] = data[3] = 0;
    node->pass_flags = 0; owner.x = 0;
    assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0x1000) == 0);
    assert(animation_motion_step(&stream, node, &owner) == 0 && owner.x == 3);
    node->pass_flags = 8;
    assert(animation_motion_step(&stream, node, &owner) == 0 && owner.x == 0);
    assert(animation_motion_step(&stream, node, &owner) == 0 && owner.x == -3);
    data[0] = 0xff; data[1] = 0; data[2] = 0; data[3] = 0x10;
    data[4] = data[5] = 0;
    assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0x1000) == 0);
    assert(animation_motion_step(&stream, node, &owner) == -1 && owner.x == -3);
    data[0] = 0;
    assert(animation_initialize(&stream, data, 3, 0x1000, 0x1000) == 0);
    assert(animation_motion_step(&stream, node, &owner) == -1);
    assert(animation_motion_step(0, node, &owner) == -1);
    unsigned char original[22];
    FILE *dump = fopen("bin/obj2_data.bin", "rb");
    assert(dump && fseek(dump, 0x329c, SEEK_SET) == 0);
    assert(fread(original, 1, sizeof(original), dump) == sizeof(original));
    assert(fclose(dump) == 0);
    /* Original selected stream starts with -4,-3,-2, then repeats -1. */
    static const int opening[] = {-4, -4, -3, -3, -2, -2};
    for (unsigned int direction = 0; direction < 2; ++direction) {
        node->pass_flags = (unsigned char)(direction ? 8 : 0);
        owner.x = owner.y = 0;
        int expected_x = 0;
        assert(animation_initialize(&stream, original, sizeof(original), 0x329c, 0x329c) == 0);
        for (unsigned int tick = 0; tick < 1000; ++tick) {
            int dx = tick < 6 ? opening[tick] : -1;
            expected_x = wrap(expected_x + (direction ? -dx : dx));
            assert(animation_motion_step(&stream, node, &owner) == 0);
            assert(owner.x == expected_x && owner.y == 0);
        }
    }
    printf("PASS: %u motion cases, duration+1 repetitions, live mirroring, signed XY wrap, "
        "absolute loops and invalid streams\n", cases);
    puts("PASS: original DS:0x329c motion stream, 2000 updates in both facing directions");
    return 0;
}
