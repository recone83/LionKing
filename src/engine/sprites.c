/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "sprites.h"
#include "dos64/platform.h"

static unsigned int sprite_u16(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8;
}

int render_draw_sprite(const unsigned char *asset, unsigned int size,
    unsigned short frame, int x, int y, unsigned char *pixels)
{
    if (!asset || !pixels || size < 2 || x < -65536 || x > 65536 ||
        y < -65536 || y > 65536) {
        return -1;
    }
    unsigned int index = frame & 0x1fff;
    unsigned int count = sprite_u16(asset);
    if (index >= count || 2ULL + count * 8ULL > size) {
        return -1;
    }
    const unsigned char *entry = asset + 2 + index * 8;
    unsigned int width = sprite_u16(entry), height = sprite_u16(entry + 2);
    unsigned int offset = (unsigned int)entry[4] | (unsigned int)entry[5] << 8 |
        (unsigned int)entry[6] << 16 | (unsigned int)entry[7] << 24;
    if (offset < 2 + count * 8 || offset >= size) {
        return -1;
    }
    while (offset < size) {
        unsigned int column = asset[offset++];
        if (column == 255) {
            return 0;
        }
        if (size - offset < 2) {
            return -1;
        }
        unsigned int row = asset[offset++], length = asset[offset++];
        if (!length || length > size - offset || row >= height ||
            column + length > width) {
            return -1;
        }
        /* Original bit 0x2000 reverses rows; 0x8000 reverses columns. */
        int py = y + ((frame & 0x2000) ? (int)height - (int)row : (int)row);
        for (unsigned int i = 0; i < length; ++i) {
            int px = x + ((frame & 0x8000) ?
                (int)width - (int)column - (int)i : (int)column + (int)i);
            if (px >= 0 && px < (int)LK_WIDTH && py >= 0 && py < (int)LK_HEIGHT) {
                pixels[(unsigned int)py * LK_WIDTH + (unsigned int)px] = asset[offset + i];
            }
        }
        offset += length;
    }
    return -1;
}
#else
#include "sprites_legacy.inc"
#endif
