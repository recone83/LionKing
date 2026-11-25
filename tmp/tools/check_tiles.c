#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/tile_blitters.h"
#include "engine/tiles.h"

int main(void)
{
    unsigned char tile[64], actual[320 * 200], expected[320 * 200];
    for (unsigned int i = 0; i < 64; ++i) {
        tile[i] = (unsigned char)i;
    }
    unsigned int cases = 0;
    const int coordinates[] = {-8, -3, 0, 195, 198, 199, 200, 315, 319, 320};
    for (unsigned int flip = 0; flip < 4; ++flip) {
        unsigned short flags = (unsigned short)(((flip & 1) ? 0x8000 : 0) |
            ((flip & 2) ? 0x4000 : 0));
        for (int transparent = 0; transparent < 2; ++transparent) {
            for (unsigned int first = 0; first <= 8; ++first) {
                for (unsigned int rows = 0; rows <= 8 - first; ++rows) {
                    for (unsigned int p = 0; p < sizeof(coordinates) / sizeof(*coordinates); ++p) {
                        int x = coordinates[p], y = coordinates[p];
                        memset(actual, 99, sizeof(actual));
                        memset(expected, 99, sizeof(expected));
                        /* Independent reference maps source pixels to their destinations. */
                        for (unsigned int sy = 0; sy < 8; ++sy) {
                            for (unsigned int sx = 0; sx < 8; ++sx) {
                                unsigned int dy = (flip & 2) ? 7 - sy : sy;
                                unsigned int dx = (flip & 1) ? 7 - sx : sx;
                                int px = x + (int)dx, py = y + (int)dy;
                                unsigned char value = tile[sy * 8 + sx];
                                if (dy >= first && dy < first + rows &&
                                    px >= 0 && px < 320 && py >= 0 && py < 200 &&
                                    (!transparent || value)) {
                                    expected[py * 320 + px] = value;
                                }
                            }
                        }
                        assert(render_blit_tile(tile, flags, x, y, first, rows,
                            transparent, actual) == 0);
                        assert(memcmp(actual, expected, sizeof(actual)) == 0);
                        ++cases;
                    }
                }
            }
        }
    }
    memset(actual, 99, sizeof(actual));
    assert(render_blit_tile(tile, 0, 0, 0, 7, 2, 0, actual) == -1);
    assert(render_blit_tile(0, 0, 0, 0, 0, 8, 0, actual) == -1);
    for (unsigned int i = 0; i < sizeof(actual); ++i) {
        assert(actual[i] == 99);
    }
    unsigned char map[196] = {0};
    map[4] = 128;
    map[8] = 2;
    map[12] = 1;
    map[16] = 192;
    memcpy(map + 128, tile, 64);
    map[192] = 1;
    map[194] = 1;
    map[195] = 0xa0;
    memset(actual, 99, sizeof(actual));
    assert(render_map_tile_pass(map, sizeof(map), 0, 3, 0, 0, actual) == 0);
    assert(actual[0] == 3 && actual[4] == 7 && actual[5] == 99);
    assert(render_map_tile_pass(map, sizeof(map), 0, 3, 0, 1, actual) == 0);
    assert(actual[5] == 7 && actual[11] == 1 && actual[12] == 99);
    assert(render_map_tile_pass(map, sizeof(map) - 1, 0, 0, 0, 0, actual) == -1);
    printf("PASS: %u exact tile flip/clipping/transparency/window cases\n", cases);
    return 0;
}
