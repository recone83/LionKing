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

static int lateral_probe(const ENGINE_MAP_COLLISION *collision, RENDER_OWNER *owner,
    unsigned short flags, unsigned char flags_high, int right, short *hit)
{
    int x = map_word((unsigned short)owner->x + (right ? 12U : 0U - 12U));
    int y = map_word((unsigned short)owner->y - 8U);
    if (flags & 0x8000) {
        x = map_word((unsigned short)x + (right ? 0U - 4U : 4U));
        y = map_word((unsigned short)y + 32U);
    }
    int px = x < 0 ? 0 : x, py = y < 8 ? 0 : y - 8;
    unsigned int tile;
    if (collision_cell(collision, px, py / 16, 2, &tile) != 0) return -1;
    unsigned int kind = map_shape(tile);
    *hit = 0;
    if ((kind & 255) != (right ? 6U : 9U)) {
        if (!(kind >= 0xb0 || (kind == 2 && !(flags_high & 8)) ||
            kind == 0x4f || kind == 0x4e || kind == 0x40 || kind == 0x41)) return 0;
        int half_y = ((unsigned short)y - 8U) & 15;
        if ((kind == 0x4e && half_y < 8) || (kind == 0x4f && half_y > 8)) return 0;
        if (right && (kind & 255) == 0x40) return 0;
        int half_x = (unsigned short)x & 15;
        if (right && (kind & 255) == 0x41) {
            *hit = half_x >= 8 ? -1 : 0;
            return 0;
        }
        if (!right && kind == 0x40) {
            if (half_x > 8) return 0;
            if (half_x < 8) owner->x = map_word((unsigned short)owner->x - (unsigned int)(half_x - 8));
            *hit = -1;
            return 0;
        }
        /* Unlike edge queries, these inspect the neighboring eight-pixel word. */
        unsigned int offset = collision->table + 2 * collision->plane_size +
            (unsigned int)(py / 16) * collision->width * 4 + (unsigned int)(px / 16) * 4;
        int neighbor_offset = (int)offset + (right ? -2 : 2);
        if (neighbor_offset < 0 || (unsigned int)neighbor_offset + 2 > collision->size) return -1;
        unsigned int neighbor = map_shape(map_u16(collision->map + neighbor_offset));
        if (right) {
            if ((neighbor & 255) == 0x41) owner->x = map_word((unsigned short)owner->x - 8U);
        } else {
            owner->x = map_word((unsigned short)owner->x +
                ((neighbor & 255) == 0x40 ? 8U : (unsigned int)(15 - half_x)));
        }
    }
    *hit = -1;
    return 0;
}

int engine_map_lateral(const ENGINE_MAP_COLLISION *collision, RENDER_OWNER *owner,
    unsigned short flags, unsigned char flags_high, unsigned char *blocked)
{
    if (!collision || !collision->map || !collision->contours || !owner || !blocked) return -1;
    *blocked = 0;
    if (flags & 8) return 0;
    short hit;
    if (owner->x <= 16) {
        owner->x = 16; *blocked |= 4;
    } else {
        if (lateral_probe(collision, owner, flags, flags_high, 0, &hit) != 0) return -1;
        if (hit) *blocked |= 4;
    }
    int limit = (int)collision->width * 8 - 16;
    if (owner->x >= limit) {
        owner->x = (short)limit; *blocked |= 8;
    } else {
        if (lateral_probe(collision, owner, flags, flags_high, 1, &hit) != 0) return -1;
        if (hit) *blocked |= 8;
    }
    return 0;
}

int engine_map_ceiling(const ENGINE_MAP_COLLISION *collision, const RENDER_NODE *node,
    short x, short y, short *hit)
{
    if (!collision || !collision->map || !collision->contours || !node ||
        !node->parts || node->parts_size < 6 || !hit) return -1;
    *hit = 0;
    int top = map_word((unsigned short)y + map_u16(node->parts + 4));
    int px = x < 0 ? 0 : x, py = top < 8 ? 0 : top - 8;
    unsigned int tile;
    if (collision_cell(collision, px, py / 16 + 1, 2, &tile) != 0) return -1;
    unsigned int kind = map_shape(tile);
    if (kind >= 0xb0 || (kind >= 0x40 && kind <= 0x4f)) {
        *hit = -1; return 0;
    }
    /* Both original reads address the same cell; the later shape-table
       branches cannot be reached after the classification above. */
    return 0;
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

typedef struct {
    unsigned short row;
    unsigned short numerator;
    unsigned short denominator;
} BACKGROUND_SCROLL;

/* DS 0x18e6 -> 0x191e..0x19ac; repeated row 21 in level 5 is intentional. */
static const BACKGROUND_SCROLL background_scroll[][7] = {
    {{0xffff, 1, 1}},
    {{19,12,1}, {24,13,1}, {25,14,1}, {26,15,1}, {27,16,1}, {28,17,1}, {0xffff,1,1}},
    {{14,2,1}, {16,6,1}, {20,12,1}, {0xffff,1,1}},
    {{0xffff,1,1}},
    {{19,2,1}, {20,3,1}, {21,6,1}, {21,10,1}, {0xffff,1,1}},
    {{18,3,1}, {30,8,1}, {0xffff,1,1}},
    {{14,2,1}, {18,6,1}, {24,10,1}, {0xffff,1,1}},
    {{0xffff,1,1}},
    {{14,2,1}, {19,6,1}, {0xffff,1,1}},
    {{19,4,1}, {24,8,1}, {0xffff,1,1}},
    {{0xffff,1,1}},
    {{0xffff,1,1}}
};

int render_map_background(const unsigned char *map, unsigned int size,
    unsigned int level, unsigned int camera_x, unsigned int camera_y,
    unsigned char *pixels)
{
    if (!map || !pixels || size < 0x80 || !level || level > 12 ||
        camera_x > 32767 || camera_y > 32767) return -1;
    unsigned int width = map_u16(map + 20), height = map_u16(map + 24);
    unsigned int table = map_u32(map + 28), tiles = map_u32(map + 4);
    unsigned int main_width = map_u16(map + 8), main_height = map_u16(map + 12);
    if (width < 40 || height < 26 || main_width < 40 || main_height < 26 ||
        tiles >= size || !table || table + width * (unsigned long long)height * 2 > size) return -1;
    unsigned int vertical = 0;
    if (width > 40) {
        unsigned int divisor = main_height - 26;
        if (!divisor) return -1;
        vertical = (height - 26) * camera_y / divisor;
    }
    const BACKGROUND_SCROLL *profile = background_scroll[level - 1];
    unsigned int profile_index = 0, numerator = 1, denominator = 1;
    /* Expand the original threshold stream once per source row, not per pixel. */
    for (unsigned int row = 0; row < vertical / 8; ++row) {
        if (row >= profile[profile_index].row) {
            numerator = profile[profile_index].numerator;
            denominator = profile[profile_index++].denominator;
        }
    }
    for (unsigned int y = 0; y < LK_HEIGHT;) {
        unsigned int source_y = vertical + y, row = source_y / 8;
        if (row >= height) return -1;
        if (row >= profile[profile_index].row) {
            numerator = profile[profile_index].numerator;
            denominator = profile[profile_index++].denominator;
        }
        unsigned int dx = (camera_x * numerator) & 0xffff;
        unsigned int divisor = ((main_width - 40) * 8 * denominator) & 0xffff;
        unsigned int horizontal = (width - 40) * 8;
        if (dx) horizontal *= dx;
        if (divisor) horizontal /= divisor;
        horizontal %= width * 8;
        unsigned int first_row = source_y & 7, rows = 8 - first_row;
        if (rows > LK_HEIGHT - y) rows = LK_HEIGHT - y;
        int phase_x = (int)(horizontal & 7);
        for (int x = -phase_x; x < (int)LK_WIDTH; x += 8) {
            unsigned int column = (horizontal / 8 + (unsigned int)(x + phase_x) / 8) % width;
            unsigned int tile = map_u16(map + table + (row * width + column) * 2);
            unsigned int index = tile & 0x1fff;
            if (!index) continue;
            unsigned long long offset = tiles + (index - 1) * 64ULL;
            if (offset + 64 > size) return -1;
            if (render_blit_tile(map + offset, (unsigned short)tile, x,
                (int)y - (int)first_row, first_row, rows, 0, pixels) != 0) return -1;
        }
        y += rows;
    }
    return 0;
}

int engine_tile_animation_initialize(ENGINE_TILE_ANIMATION *animation,
    unsigned char *map, unsigned int size, unsigned int level,
    const unsigned char *frames, unsigned int frames_size)
{
    if (!animation || !map || size < 0x80 || !frames || (level != 6 && level != 10)) return -1;
    static const unsigned int positions[7] = {0xc02,0xc80,0xd00,0xd80,0xe00,0xe80,0xf00};
    ENGINE_TILE_ANIMATION result = {0};
    result.map = map; result.frames = frames;
    result.count = level == 6 ? 1 : 7;
    result.frame_size = level == 6 ? 0xb40 : 0xc80;
    if (frames_size != result.frame_size * 4) return -1;
    unsigned int table = map_u32(map + (level == 6 ? 16 : 28));
    unsigned int tiles = map_u32(map + 4);
    if (!table || table >= size || tiles >= size) return -1;
    for (unsigned int i = 0; i < result.count; ++i) {
        unsigned int offset = table + (level == 6 ? 0x3c : positions[i]);
        if (offset < table || offset + 2ULL > size) return -1;
        unsigned int index = map_u16(map + offset) & 0x1fff;
        if (!index) return -1;
        unsigned long long destination = tiles + (index - 1) * 64ULL;
        unsigned int length = level == 6 ? 0xb40 : (i ? 512 : 128);
        if (destination + length > size) return -1;
        result.destinations[i] = (unsigned int)destination;
        result.lengths[i] = length;
    }
    *animation = result;
    return 0;
}

int engine_tile_animation_tick(ENGINE_TILE_ANIMATION *animation)
{
    if (!animation || !animation->map || !animation->frames || !animation->count ||
        animation->count > 7 || animation->remaining > 4 || animation->frame > 3) return -1;
    if (animation->remaining) {
        --animation->remaining;
        return 0;
    }
    animation->remaining = 4;
    animation->frame = (animation->frame + 1) & 3;
    const unsigned char *source = animation->frames + animation->frame * animation->frame_size;
    for (unsigned int i = 0; i < animation->count; ++i) {
        unsigned char *destination = animation->map + animation->destinations[i];
        for (unsigned int byte = 0; byte < animation->lengths[i]; ++byte) {
            destination[byte] = *source++;
        }
    }
    ++animation->updates;
    return 1;
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
