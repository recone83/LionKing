#include "platform.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "libs/vga.h"

static unsigned char pixels[LK_WIDTH * LK_HEIGHT];
static DOS64_COLOR palette[256];
static unsigned char packed[65536];
static unsigned char map[347816];
static unsigned char sprite[20419];
static RESOURCE_DICTIONARY dictionary;

static int selftest_requested(const char *arguments)
{
    const char *expected = "--selftest";
    while (*arguments == ' ') {
        ++arguments;
    }
    while (*expected && *arguments == *expected) {
        ++arguments;
        ++expected;
    }
    return !*expected && (!*arguments || *arguments == ' ');
}

int __attribute__((ms_abi)) start(const DOS64_API *api)
{
    if (lk_platform_init(api) != 0) {
        return 1;
    }
    if (!api->Arguments) {
        lk_platform_log("Lion King: missing runtime argument string.\n");
        return 1;
    }
    LK_EPF_INFO archive;
    if (resources_open_archive(api, "LIONKING.EPF", &archive) != 0) {
        return 1;
    }
    lk_platform_log("Lion King: EPF index and payload bounds verified.\n");
    unsigned int loaded;
    if (resources_load_entry(api, "LIONKING.EPF", "LEVEL1.MAP", packed, sizeof(packed),
        map, sizeof(map), &dictionary, &loaded) != 0) {
        return 1;
    }
    if (vga_load_palette(map, loaded, palette) != 0) {
        lk_platform_log("Lion King: invalid level palette.\n");
        return 1;
    }
    if (render_map_tile_pass(map, loaded, 0, 0, 0, 0, pixels) != 0 ||
        render_map_tile_pass(map, loaded, 0, 0, 0, 1, pixels) != 0) {
        lk_platform_log("Lion King: invalid map tile layer.\n");
        return 1;
    }
    if (resources_load_entry(api, "LIONKING.EPF", "SYIDLE1.MCH", packed, sizeof(packed),
        sprite, sizeof(sprite), &dictionary, &loaded) != 0) {
        return 1;
    }
    if (render_draw_sprite(sprite, loaded, 0, 140, 80, pixels) != 0) {
        lk_platform_log("Lion King: invalid sprite frame.\n");
        return 1;
    }
    lk_platform_log("Lion King DOS64 asset viewer; not gameplay. Escape exits.\n");
    int selftest = selftest_requested(api->Arguments);
    unsigned long long begin = lk_platform_time_ns();
    for (;;) {
        lk_platform_poll();
        if (lk_platform_exit_requested()) {
            break;
        }
        lk_platform_present(pixels, palette);
        if (selftest && lk_platform_time_ns() - begin >= 1000000000ULL) {
            break;
        }
        lk_platform_sleep(10);
    }
    lk_platform_log("Lion King DOS64 platform test finished.\n");
    return 0;
}
