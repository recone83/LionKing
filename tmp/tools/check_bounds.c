#include <assert.h>
#include <stdio.h>
#include "engine/render.h"

static short wrap(int value)
{
    int result = value % 65536;
    if (result < -32768) {
        result += 65536;
    } else if (result > 32767) {
        result -= 65536;
    }
    return (short)result;
}

static void put_word(unsigned char *p, short value)
{
    unsigned short bits = (unsigned short)value;
    p[0] = (unsigned char)bits;
    p[1] = (unsigned char)(bits >> 8);
}

int main(void)
{
    static const short coordinates[] = {-32768, -32760, -1, 0, 1, 32760, 32767};
    static const short offsets[][4] = {
        {-31, -56, 24, 1}, {-32768, -32768, 32767, 32767},
        {0, 0, 0, 0}, {10, 20, -10, -20}
    };
    unsigned char descriptor[14] = {0};
    RENDER_OWNER owner;
    RENDER_NODE node = {0};
    node.owner = &owner;
    node.active = 1;
    node.parts = descriptor;
    node.parts_size = sizeof(descriptor);
    unsigned int cases = 0;
    for (unsigned int shape = 0; shape < 4; ++shape) {
        for (unsigned int i = 0; i < 4; ++i) {
            put_word(descriptor + 2 + i * 2, offsets[shape][i]);
        }
        for (unsigned int flip = 0; flip < 4; ++flip) {
            node.pass_flags = (unsigned char)(flip * 8);
            for (unsigned int position = 0; position < 7; ++position) {
                owner.x = coordinates[position];
                owner.y = coordinates[6 - position];
                RENDER_BOUNDS expected = {
                    wrap(owner.x + (flip & 1 ? -offsets[shape][2] : offsets[shape][0])),
                    wrap(owner.y + (flip & 2 ? -offsets[shape][3] : offsets[shape][1])),
                    wrap(owner.x + (flip & 1 ? -offsets[shape][0] : offsets[shape][2])),
                    wrap(owner.y + (flip & 2 ? -offsets[shape][1] : offsets[shape][3]))
                };
                RENDER_BOUNDS actual;
                assert(render_object_bounds(&node, &actual) == 0);
                assert(actual.left == expected.left && actual.top == expected.top &&
                    actual.right == expected.right && actual.bottom == expected.bottom);
                for (int x = -32768; x <= 32767; ++x) {
                    short y = wrap(x + position);
                    short hit = 123;
                    assert(render_point_hit(&node, (short)x, y, &hit) == 0);
                    assert(hit == (x >= expected.left && x <= expected.right &&
                        y >= expected.top && y <= expected.bottom ? -1 : 0));
                    ++cases;
                }
                short hit;
                assert(render_point_hit(&node, expected.left, expected.top, &hit) == 0);
                assert(hit == (expected.left <= expected.right &&
                    expected.top <= expected.bottom ? -1 : 0));
                assert(render_point_hit(&node, expected.right, expected.bottom, &hit) == 0);
                assert(hit == (expected.left <= expected.right &&
                    expected.top <= expected.bottom ? -1 : 0));
            }
        }
    }
    short hit = 123;
    node.parts_size = 13;
    assert(render_point_hit(&node, 0, 0, &hit) == -1 && hit == 123);
    assert(render_point_hit(0, 0, 0, &hit) == -1);
    assert(render_object_bounds(&node, 0) == -1);
    printf("PASS: %u original point-hit cases, inclusive edges, HV bounds, "
        "signed wrapping and malformed descriptors\n", cases);
    return 0;
}
