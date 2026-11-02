#include <assert.h>
#include <stdio.h>
#include "engine/render.h"

static short word(unsigned int value)
{
    value &= 65535U;
    return (short)(value < 32768U ? (int)value : (int)value - 65536);
}

int main(void)
{
    static const unsigned short dimensions[] = {0, 1, 24, 25, 39, 40, 41, 4096, 8191, 65535};
    unsigned int cases = 0;
    for (unsigned int d = 0; d < sizeof(dimensions) / sizeof(dimensions[0]); ++d) {
        for (unsigned int v = 0; v < 65536; ++v) {
            for (unsigned int s = 0; s < 3; ++s) {
                unsigned short shake = s == 0 ? 0 : s == 1 ? 8 : 65535;
                RENDER_OWNER camera = {word(v), word(65535U - v)};
                int x = camera.x < 0 ? 0 : camera.x;
                int y = camera.y < 0 ? 0 : camera.y;
                int max_x = word(dimensions[d] * 8U - 320U);
                int max_y = word(dimensions[d] * 8U - 200U);
                if (x > max_x) x = max_x;
                if (y > max_y) y = max_y;
                RENDER_VIEWPORT viewport;
                assert(render_prepare_viewport(&camera, dimensions[d], dimensions[d],
                    shake, &viewport) == 0);
                assert(camera.x == x && camera.y == y);
                assert(viewport.x == (unsigned short)x);
                assert(viewport.y == (unsigned short)(y + shake));
                assert(viewport.aligned_x == (viewport.x & 65528U));
                assert(viewport.aligned_y == (viewport.y & 65528U));
                ++cases;
            }
        }
    }
    RENDER_OWNER camera = {1, 2};
    RENDER_VIEWPORT viewport = {1, 2, 3, 4};
    assert(render_prepare_viewport(0, 40, 25, 0, &viewport) == -1);
    assert(viewport.x == 1 && viewport.y == 2);
    assert(render_prepare_viewport(&camera, 40, 25, 0, 0) == -1);
    assert(camera.x == 1 && camera.y == 2);
    RENDER_FOLLOW_CAMERA follow = {{300, 600}, 128};
    for (int delta = -20; delta <= 20; ++delta) {
        follow.position = (RENDER_OWNER){300, 600};
        assert(render_follow_camera(&follow, (RENDER_OWNER){428, (short)(728 + delta)},
            0, 0, 200, 160) == 0);
        assert(follow.position.x == 300 && follow.position.y == 600);
    }
    assert(render_follow_camera(&follow, (RENDER_OWNER){428, 753}, 0, 0, 200, 160) == 0);
    assert(follow.position.y == 605);
    assert(render_follow_camera(&follow, (RENDER_OWNER){428, 690}, 0, 0, 200, 160) == 0);
    assert(follow.position.y == 597);
    follow = (RENDER_FOLLOW_CAMERA){{300, 600}, 128};
    assert(render_follow_camera(&follow, (RENDER_OWNER){428, 728}, 1, 0, 200, 160) == 0);
    assert(follow.horizontal_offset == 129 && follow.position.x == 299);
    for (unsigned int tick = 1; tick < 64; ++tick) {
        assert(render_follow_camera(&follow, (RENDER_OWNER){428, 728}, 1, 0, 200, 160) == 0);
        assert(follow.position.x == 300 - (short)(tick + 1));
    }
    assert(follow.horizontal_offset == 192);
    for (unsigned int tick = 0; tick < 64; ++tick)
        assert(render_follow_camera(&follow, (RENDER_OWNER){428, 728}, 0, 0, 200, 160) == 0);
    assert(follow.horizontal_offset == 128 && follow.position.x == 300);
    follow = (RENDER_FOLLOW_CAMERA){{300, 600}, 128};
    assert(render_follow_camera(&follow, (RENDER_OWNER){500, 750}, 0, 0, 200, 160) == 0);
    assert(follow.position.x == 308 && follow.position.y == 602);
    follow = (RENDER_FOLLOW_CAMERA){{300, 600}, 128};
    assert(render_follow_camera(&follow, (RENDER_OWNER){428, 728}, 0, 1, 200, 160) == 0);
    assert(follow.position.y == 592);
    follow = (RENDER_FOLLOW_CAMERA){{300, 600}, 128};
    assert(render_follow_camera(&follow, (RENDER_OWNER){428, 728}, 0, 2, 200, 160) == 0);
    assert(follow.position.y == 608);
    follow = (RENDER_FOLLOW_CAMERA){{0, 0}, 128};
    assert(render_follow_camera(&follow, (RENDER_OWNER){0, 0}, 0, 0, 200, 160) == 0);
    assert(follow.position.x == 0 && follow.position.y == 0);
    follow.position = (RENDER_OWNER){1280, 1080};
    assert(render_follow_camera(&follow, (RENDER_OWNER){1600, 1280}, 0, 0, 200, 160) == 0);
    assert(follow.position.x == 1280 && follow.position.y == 1080);
    assert(render_follow_camera(0, camera, 0, 0, 200, 160) == -1);
    assert(render_follow_camera(&follow, camera, 0, 0, 39, 160) == -1);
    puts("PASS: original LEVEL1 camera look-ahead, vertical dead zone, posture offsets, 8-pixel cap and map bounds");
    printf("PASS: original 0x11799 viewport, %u cases, signed low-word clamps, "
        "lower-then-upper order, shake wrapping, aligned origins and pointer errors\n", cases);
    return 0;
}
