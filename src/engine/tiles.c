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

static unsigned int map_u16(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8;
}

static unsigned int map_shape(unsigned int tile)
{
    return ((tile & 0xfe0U) >> 2) + ((tile & 0x1fU) >> 1);
}

int engine_map_collision_initialize(ENGINE_MAP_COLLISION *collision,
    const unsigned char *map, unsigned int size,
    const unsigned char *contours, unsigned int contour_size)
{
    if (!collision || !map || size < 0x80 || !contours || contour_size != 4096) return -1;
    unsigned int width = map_u16(map + 8), height = map_u16(map + 12);
    unsigned int table = map_u32(map + 16);
    unsigned long long plane = width * (unsigned long long)height * 2;
    if (!width || !height || (width & 1) || (height & 1) || width > 4095 || height > 2047 ||
        !table || table + plane * 4 > size) return -1;
    *collision = (ENGINE_MAP_COLLISION){map, size, contours, width, height,
        (unsigned int)plane, table};
    return 0;
}

static int collision_cell(const ENGINE_MAP_COLLISION *collision, int x, int row,
    unsigned int plane, unsigned int *tile)
{
    if (!collision || !collision->map || !collision->contours || !tile || plane > 3) return -1;
    *tile = 0;
    if (x < 0 || row < 0 || (unsigned int)x >= collision->width * 8 ||
        (unsigned int)row >= collision->height / 2) return 0;
    unsigned int offset = collision->table + plane * collision->plane_size +
        (unsigned int)row * collision->width * 4 + ((unsigned int)x / 16) * 4;
    if (offset + 2 > collision->size) return -1;
    *tile = map_u16(collision->map + offset);
    return 0;
}

int engine_map_ground(const ENGINE_MAP_COLLISION *collision, short x, short y,
    ENGINE_MAP_GROUND *ground)
{
    if (!ground || !collision || !collision->map || !collision->contours) return -1;
    *ground = (ENGINE_MAP_GROUND){0};
    if (y < 12 || x < 0) return 0;
    int row = (y - 12) / 16;
    for (unsigned int sample = 0; sample < 2; ++sample, ++row) {
        unsigned int tile, tag;
        if (collision_cell(collision, x, row, 1, &tile) != 0 ||
            collision_cell(collision, x, row, 2, &tag) != 0) return -1;
        ground->kind = (unsigned char)map_shape(tag);
        unsigned int shape = map_shape(tile);
        if (shape >= 256) return -1;
        /* 0x16b70 uses the low five contour bits, then decrements height. */
        unsigned int height = collision->contours[shape * 16 + ((unsigned short)x & 15)] & 31;
        if (height) {
            int delta = row * 16 + (int)height - 1 - y;
            if (delta >= -12 && delta <= 12) {
                ground->supported = -1;
                ground->delta_y = (short)delta;
                return 0;
            }
        }
        if (!sample) ground->surface_kind = ground->kind;
    }
    return 0;
}

int engine_map_kind(const ENGINE_MAP_COLLISION *collision, short x, short y,
    unsigned short *kind)
{
    if (!kind) return -1;
    unsigned int tile;
    /* 0x170ae adds 8 before 0x16d54 subtracts it: use the probe's row. */
    int px = x < 0 ? 0 : x, py = y < 0 ? 0 : y;
    if (collision_cell(collision, px, py / 16, 2, &tile) != 0) return -1;
    *kind = (unsigned short)map_shape(tile);
    return 0;
}

static int edge_kind(unsigned short kind, int left)
{
    return kind == 0xea || kind == 0xaf || (left ?
        kind == 0xfc || kind == 0xfe || kind == 0xec || kind == 0xee ||
        kind == 0x9d || kind == 0x9f || kind == 0x8d || kind == 0x8f || kind == 0xf8 :
        kind == 0xfd || kind == 0xfb || kind == 0xed || kind == 0xeb ||
        kind == 0x9e || kind == 0x9c || kind == 0x8e || kind == 0x8c || kind == 0xe8);
}

static short map_word(unsigned int value)
{
    value &= 0xffff;
    return (short)(value < 0x8000 ? (int)value : (int)value - 65536);
}

int engine_map_edge(const ENGINE_MAP_COLLISION *collision, const RENDER_NODE *node,
    short *hit, short *kind, short *x, short *y)
{
    if (!collision || !collision->map || !collision->contours ||
        !node || !node->owner || !node->parts || node->parts_size < 14 ||
        !hit || !kind || !x || !y) return -1;
    int left = (node->pass_flags & 8) != 0;
    short dx = map_word(map_u16(node->parts + 10));
    *x = map_word((unsigned short)node->owner->x + (left ? 0U - (unsigned int)dx : (unsigned int)dx));
    *y = map_word((unsigned short)node->owner->y + map_u16(node->parts + 12));
    *hit = *kind = 0;
    if (left && *x < 16) return 0;
    unsigned short current, neighbor;
    if (engine_map_kind(collision, *x, *y, &current) != 0) return -1;
    if (edge_kind(current, left)) {
        *hit = -1; *kind = (short)current;
        return 0;
    }
    short adjacent = map_word((unsigned short)*x + (left ? 16U : 0U - 16U));
    if (engine_map_kind(collision, adjacent, *y, &neighbor) != 0) return -1;
    if (edge_kind(neighbor, left)) {
        *x = adjacent; *hit = -1; *kind = (short)neighbor;
    }
    return 0;
}

int engine_map_ledge_height(const ENGINE_MAP_COLLISION *collision,
    short x, short y, short *height)
{
    if (!height) return -1;
    unsigned int tile;
    int px = x < 0 ? 0 : x, py = y < 0 ? 0 : y;
    if (collision_cell(collision, px, py / 16, 1, &tile) != 0) return -1;
    unsigned int shape = map_shape(tile);
    if (shape >= 256) return -1;
    *height = (short)(collision->contours[shape * 16 + (px & 15)] & 31);
    return 0;
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
