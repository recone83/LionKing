/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "tiles.h"
#include "tile_blitters.h"
#include "dos64/platform.h"

static unsigned int map_u32(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8 |
        (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
}

int render_map_tile_pass(const unsigned char *map, unsigned int size,
    unsigned int layer, unsigned int camera_x, unsigned int camera_y,
    int flagged, unsigned char *pixels)
{
    /* 0x11658 reads dimensions and offset from 12-byte records at MAP + 8. */
    if (!map || !pixels || size < 0x80 || layer >= 10 ||
        camera_x > 65535 || camera_y > 65535) {
        return -1;
    }
    const unsigned char *entry = map + 8 + layer * 12;
    unsigned int width = map_u32(entry), height = map_u32(entry + 4);
    unsigned int table = map_u32(entry + 8), tiles = map_u32(map + 4);
    if (!width || !height || width > 65535 || height > 65535 ||
        tiles >= size || table >= size ||
        (unsigned long long)table + width * (unsigned long long)height * 2 > size) {
        return -1;
    }
    unsigned int start_x = camera_x / 8, start_y = camera_y / 8;
    for (unsigned int row = start_y; row < height && row <= start_y + LK_HEIGHT / 8; ++row) {
        for (unsigned int column = start_x; column < width &&
            column <= start_x + LK_WIDTH / 8; ++column) {
            unsigned int position = table + (row * width + column) * 2;
            unsigned short value = (unsigned short)((unsigned int)map[position] |
                (unsigned int)map[position + 1] << 8);
            unsigned int index = value & 0x1fff;
            if (!index || !!(value & 0x2000) != !!flagged) {
                continue;
            }
            unsigned long long offset = tiles + (index - 1) * 64ULL;
            if (offset + 64 > size) {
                return -1;
            }
            if (render_blit_tile(map + offset, value,
                (int)(column * 8) - (int)camera_x, (int)(row * 8) - (int)camera_y,
                0, 8, 1, pixels) != 0) {
                return -1;
            }
        }
    }
    return 0;
}
#else
#include "tiles_legacy.inc"
#endif
