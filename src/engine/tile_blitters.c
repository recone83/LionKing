#include "tile_blitters.h"
#include "dos64/platform.h"

int render_blit_tile(const unsigned char *tile, unsigned short flags, int x, int y,
    unsigned int first_row, unsigned int rows, int transparent, unsigned char *pixels)
{
    if (!tile || !pixels || first_row > 8 || rows > 8 - first_row ||
        x < -65536 || x > 65536 || y < -65536 || y > 65536) {
        return -1;
    }
    unsigned int last_row = first_row + rows;
    if (y < 0 && first_row < (unsigned int)-y) {
        first_row = (unsigned int)-y;
    }
    if (y >= (int)LK_HEIGHT || first_row >= last_row) {
        return 0;
    }
    if (last_row > (unsigned int)((int)LK_HEIGHT - y)) {
        last_row = (unsigned int)((int)LK_HEIGHT - y);
    }

    int clipped_x = x < 0 || x > (int)LK_WIDTH - 8;
    int flipped_x = (flags & 0x8000) != 0;
    for (unsigned int row = first_row; row < last_row; ++row) {
        unsigned int source_row = (flags & 0x4000) ? 7 - row : row;
        int py = y + (int)row;
        const unsigned char *source = tile + source_row * 8;
        unsigned char *destination = pixels + (unsigned int)py * LK_WIDTH;
        if (!clipped_x) destination += x;
        if (!clipped_x && !flipped_x && !transparent) {
            for (unsigned int column = 0; column < 8; ++column) {
                destination[column] = source[column];
            }
            continue;
        }
        for (unsigned int column = 0; column < 8; ++column) {
            int px = x + (int)column;
            if (!clipped_x || (px >= 0 && px < (int)LK_WIDTH)) {
                unsigned int source_column = flipped_x ? 7 - column : column;
                unsigned char pixel = source[source_column];
                if (!transparent || pixel) {
                    destination[clipped_x ? (unsigned int)px : column] = pixel;
                }
            }
        }
    }
    return 0;
}
