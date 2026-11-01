/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "tile_blitters.h"
#include "dos64/platform.h"

int render_blit_tile(const unsigned char *tile, unsigned short flags, int x, int y,
    unsigned int first_row, unsigned int rows, int transparent, unsigned char *pixels)
{
    if (!tile || !pixels || first_row > 8 || rows > 8 - first_row ||
        x < -65536 || x > 65536 || y < -65536 || y > 65536) {
        return -1;
    }
    for (unsigned int row = first_row; row < first_row + rows; ++row) {
        unsigned int source_row = (flags & 0x4000) ? 7 - row : row;
        int py = y + (int)row;
        if (py < 0 || py >= (int)LK_HEIGHT) {
            continue;
        }
        for (unsigned int column = 0; column < 8; ++column) {
            int px = x + (int)column;
            unsigned int source_column = (flags & 0x8000) ? 7 - column : column;
            unsigned char pixel = tile[source_row * 8 + source_column];
            if (px >= 0 && px < (int)LK_WIDTH && (!transparent || pixel)) {
                pixels[(unsigned int)py * LK_WIDTH + (unsigned int)px] = pixel;
            }
        }
    }
    return 0;
}
#else
#include "tile_blitters_legacy.inc"
#endif
