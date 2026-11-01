#include <assert.h>
#include <stdio.h>
#include "engine/render.h"

static short wrap(int value)
{
    value %= 65536;
    return (short)(value < -32768 ? value + 65536 : value > 32767 ? value - 65536 : value);
}

int main(void)
{
    unsigned char descriptor[14] = {0, 0, 0xf6, 0xff, 0xec, 0xff, 30, 0, 40, 0};
    RENDER_OWNER target_owner = {0, 0}, source_owner = {0, 0};
    RENDER_NODE target = {0}, source = {0};
    target.active = source.active = 1;
    target.owner = &target_owner;
    source.owner = &source_owner;
    target.parts = descriptor;
    target.parts_size = sizeof(descriptor);
    static const short positions[] = {-32768, -32760, -41, -1, 0, 1, 41, 32760, 32767};
    static const RENDER_BOUNDS rectangles[] = {
        {-3, -7, 11, 19}, {0, 0, 0, 0}, {-32768, -32768, 32767, 32767},
        {10, 20, -10, -20}
    };
    unsigned int cases = 0;
    for (unsigned int tf = 0; tf < 4; ++tf) {
        target.pass_flags = (unsigned char)(tf * 8);
        for (unsigned int sf = 0; sf < 4; ++sf) {
            source.pass_flags = (unsigned char)(sf * 8);
            for (unsigned int p = 0; p < 9; ++p) {
                target_owner.x = positions[p];
                target_owner.y = positions[8 - p];
                RENDER_BOUNDS a = {
                    wrap(target_owner.x + (tf & 1 ? -30 : -10)),
                    wrap(target_owner.y + (tf & 2 ? -40 : -20)),
                    wrap(target_owner.x + (tf & 1 ? 10 : 30)),
                    wrap(target_owner.y + (tf & 2 ? 20 : 40))
                };
                for (unsigned int r = 0; r < 4; ++r) {
                    const RENDER_BOUNDS *local = &rectangles[r];
                    for (int x = -32768; x <= 32767; ++x) {
                        source_owner.x = (short)x;
                        source_owner.y = wrap(x + 17);
                        RENDER_BOUNDS b = {
                            wrap(x + (sf & 1 ? -local->right : local->left)),
                            wrap(source_owner.y + local->top),
                            wrap(x + (sf & 1 ? -local->left : local->right)),
                            wrap(source_owner.y + local->bottom)
                        };
                        short hit = 123;
                        assert(render_local_rectangle_hit(&target, &source, local, &hit) == 0);
                        assert(hit == (a.right >= b.left && a.bottom >= b.top &&
                            a.left <= b.right && a.top <= b.bottom ? -1 : 0));
                        ++cases;
                    }
                }
            }
        }
    }
    short hit = 123;
    assert(render_local_rectangle_hit(&target, 0, &rectangles[0], &hit) == -1 && hit == 123);
    target.parts_size = 13;
    assert(render_local_rectangle_hit(&target, &source, &rectangles[0], &hit) == -1 && hit == 123);
    printf("PASS: %u original local rectangle collision cases, target HV, source H-only, "
        "signed wrap and explicit invalid-input errors\n", cases);
    return 0;
}
