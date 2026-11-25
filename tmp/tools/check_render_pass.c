#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/render.h"
#include "dos64/platform.h"

static RENDER_POOL pool;
static unsigned char pixels[LK_WIDTH * LK_HEIGHT];
static const unsigned char sprite[] = {1, 0, 3, 0, 2, 0, 10, 0, 0, 0,
    0, 0, 3, 7, 8, 9, 255};
static unsigned char parts[26] = {1, 0};
static RENDER_OWNER owner = {50, 50};
static RENDER_SPRITE_BANK banks[2] = {{sprite, sizeof(sprite)}, {sprite, sizeof(sprite)}};

static int expected_draw(unsigned char *flags, unsigned char *remaining,
    unsigned char period)
{
    if (*flags & 0x80) {
        return 0;
    }
    if (!(*flags & 0x20)) {
        return 1;
    }
    if (*flags & 0x10) {
        if (*remaining == 0) {
            *remaining = period;
            if (*flags & 8) {
                *flags &= 0xef;
            }
            return 1;
        }
        --*remaining;
        return 0;
    }
    if (*remaining == 0) {
        *remaining = period;
        if (*flags & 8) {
            *flags |= 4;
        }
        return 0;
    }
    --*remaining;
    return 1;
}

int main(void)
{
    render_initialize_nodes(&pool);
    RENDER_NODE *node = render_acquire_node(&pool, &owner, 0, 0, parts, sizeof(parts));
    assert(node);
    static const unsigned char values[] = {0, 1, 255};
    for (unsigned int f = 0; f < 256; ++f) {
        for (unsigned int r = 0; r < 3; ++r) {
            for (unsigned int p = 0; p < 3; ++p) {
                node->flags = (unsigned char)f;
                node->remaining = values[r];
                node->period = values[p];
                node->pass_flags = 0;
                for (unsigned int tick = 0; tick < 5; ++tick) {
                    unsigned char flags = node->flags, remaining = node->remaining;
                    int draw = expected_draw(&flags, &remaining, node->period);
                    memset(pixels, 0, sizeof(pixels));
                    assert(render_object_pass(&pool, 0, 0, 0, banks, 2, pixels) == 0);
                    assert(node->flags == flags && node->remaining == remaining);
                    assert(pixels[50 * LK_WIDTH + 50] == (draw ? 7 : 0));
                    assert(render_object_pass(&pool, 0x80, 0, 0, banks, 2, pixels) == 0);
                    assert(node->flags == flags && node->remaining == remaining);
                }
            }
        }
    }
    node->flags = 0x40;
    parts[14] = 2; parts[16] = 1;
    for (unsigned int flip = 0; flip < 4; ++flip) {
        node->pass_flags = (unsigned char)(0x80 | (flip & 1 ? 8 : 0) | (flip & 2 ? 0x10 : 0));
        memset(pixels, 0, sizeof(pixels));
        assert(render_object_pass(&pool, 0x80, -10, -20, banks, 2, pixels) == 0);
        unsigned int x = flip & 1 ? 42 : 38;
        unsigned int y = flip & 2 ? 31 : 29;
        assert(pixels[y * LK_WIDTH + x] == 7);
        assert(pixels[y * LK_WIDTH + (flip & 1 ? x - 1 : x + 1)] == 8);
        assert(pixels[y * LK_WIDTH + (flip & 1 ? x - 2 : x + 2)] == 9);
    }
    node->flags = 0;
    node->pass_flags = 0;
    parts[0] = 2;
    parts[20] = 0; parts[22] = 3; parts[25] = 1;
    memset(pixels, 0, sizeof(pixels));
    assert(render_object_pass(&pool, 0, 0, 0, banks, 2, pixels) == 0);
    assert(pixels[49 * LK_WIDTH + 48] == 7 && pixels[47 * LK_WIDTH + 50] == 7);
    node->parts_size = 25;
    assert(render_object_pass(&pool, 0, 0, 0, banks, 2, pixels) == -1);
    node->parts_size = sizeof(parts);
    parts[25] = 2;
    assert(render_object_pass(&pool, 0, 0, 0, banks, 2, pixels) == -1);
    parts[25] = 1; parts[24] = 1;
    assert(render_object_pass(&pool, 0, 0, 0, banks, 2, pixels) == -1);
    parts[24] = 0;
    node->parts_size = 1;
    assert(render_object_pass(&pool, 0, 0, 0, banks, 2, pixels) == -1);
    assert(render_object_pass(&pool, 1, 0, 0, banks, 2, pixels) == -1);
    assert(render_object_pass(0, 0, 0, 0, banks, 2, pixels) == -1);
    puts("PASS: 11520 animation transitions, pass gating, multipart banks, flip anchors and bounds");
    return 0;
}
