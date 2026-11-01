#include <assert.h>
#include <stdio.h>
#include "engine/render.h"

int main(void)
{
    static const short widths[] = {-32768, -1, 0, 1, 39, 40, 41, 4095, 4096, 32767};
    unsigned int cases = 0;
    for (unsigned int i = 0; i < 10; ++i) {
        int limit = widths[i] * 8 - 320;
        int wrapped = limit % 65536;
        if (wrapped < -32768) {
            wrapped += 65536;
        } else if (wrapped > 32767) {
            wrapped -= 65536;
        }
        for (int x = -32768; x <= 32767; ++x) {
            assert(render_limit_camera_x((short)x, widths[i]) ==
                (x > limit ? (short)wrapped : (short)x));
            ++cases;
        }
    }
    assert(render_limit_camera_x(-1, 40) == -1);
    assert(render_limit_camera_x(0, 40) == 0);
    assert(render_limit_camera_x(1, 40) == 0);
    printf("PASS: %u original 0x288e3 camera-X cases, signed tile width, "
        "upper-only clamp and wrapped output\n", cases);
    return 0;
}
