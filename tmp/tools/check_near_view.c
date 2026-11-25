#include <assert.h>
#include <stdio.h>
#include "engine/render.h"

int main(void)
{
    static const short cameras[] = {-32768, -100, 0, 32700, 32767};
    static const short margins[] = {-32768, -200, -1, 0, 1, 128, 32767};
    unsigned int cases = 0;
    for (unsigned int c = 0; c < 5; ++c) {
        RENDER_OWNER camera = {cameras[c], cameras[4 - c]};
        for (unsigned int m = 0; m < 7; ++m) {
            short mx = margins[m], my = margins[6 - m];
            for (int x = -32768; x <= 32767; ++x) {
                RENDER_OWNER owner = {(short)x, (short)-1};
                int ys[] = {camera.y - my - 1, camera.y - my,
                    camera.y - my + 1, camera.y + 200 + my - 1,
                    camera.y + 200 + my, camera.y + 200 + my + 1};
                for (unsigned int edge = 0; edge < 6; ++edge) {
                    if (ys[edge] < -32768 || ys[edge] > 32767) {
                        continue;
                    }
                    owner.y = (short)ys[edge];
                    short near = 123;
                    assert(render_near_view(&owner, &camera, mx, my, &near) == 0);
                    assert(near == (x > camera.x - mx && x < camera.x + 320 + mx &&
                        owner.y > camera.y - my && owner.y < camera.y + 200 + my ? -1 : 0));
                    ++cases;
                }
            }
        }
    }
    short near = 123;
    assert(render_near_view(0, 0, 128, 128, &near) == -1 && near == 123);
    printf("PASS: %u original expanded-view cases, strict edges, signed margins "
        "and 32-bit comparisons without coordinate wrap\n", cases);
    return 0;
}
