#include "platform.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "engine/timing.h"
#include "engine/input.h"
#include "engine/render.h"
#include "libs/vga.h"

static unsigned char pixels[LK_WIDTH * (LK_HEIGHT + 7)];
static DOS64_COLOR palette[256];
static unsigned char packed[65536];
static unsigned char map[347816];
static unsigned char sprite[20419];
static RESOURCE_DICTIONARY dictionary;
static RENDER_POOL render_pool;
static VGA_FADE fade;
static unsigned char level_rgb[768];
static const unsigned char black_rgb[768];

static int present_frame(void *context, const unsigned char *source,
    const DOS64_COLOR *colors)
{
    (void)context;
    lk_platform_present(source, colors);
    return 0;
}

static void count_updates(void *context)
{
    ++*(unsigned long long *)context;
}

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
    if (vga_load_palette_rgb(map, loaded, level_rgb) != 0 ||
        vga_fade_initialize(&fade, level_rgb) != 0 ||
        vga_palette_colors(fade.current, palette) != 0) {
        lk_platform_log("Lion King: invalid level palette.\n");
        return 1;
    }
    unsigned int map_size = loaded;
    if (resources_load_entry(api, "LIONKING.EPF", "SYIDLE1.MCH", packed, sizeof(packed),
        sprite, sizeof(sprite), &dictionary, &loaded) != 0) {
        return 1;
    }
    if (loaded < 2) {
        lk_platform_log("Lion King: truncated preview sprite bank.\n");
        return 1;
    }
    unsigned int frames = (unsigned int)sprite[0] | (unsigned int)sprite[1] << 8;
    if (!frames || frames > 256 || 2ULL + frames * 8ULL > loaded) {
        lk_platform_log("Lion King: invalid preview sprite bank.\n");
        return 1;
    }
    RENDER_OWNER owner = {140, 80};
    /* Diagnostic one-part descriptor, not a reconstructed game animation script. */
    unsigned char part[20] = {1, 0};
    RENDER_SPRITE_BANK bank = {sprite, loaded};
    render_initialize_nodes(&render_pool);
    RENDER_NODE *node = render_acquire_node(&render_pool, &owner, 0, 0, part, sizeof(part));
    if (!node) {
        lk_platform_log("Lion King: cannot acquire preview render node.\n");
        return 1;
    }
    ENGINE_INPUT input;
    input_initialize(&input);
    VGA_FRAME frame = {pixels, sizeof(pixels), 0, palette, present_frame, 0};
    lk_platform_log("Lion King DOS64 interactive asset test; not gameplay.\n"
        "Left/Right: frame. Alt/Ctrl: flip X/Y. Shift: hide.\n"
        "F: fade to black/back. Space: reset. Escape: exit.\n");
    int selftest = selftest_requested(api->Arguments);
    unsigned long long begin = lk_platform_time_ns();
    ENGINE_CLOCK clock;
    ENGINE_CLOCK palette_clock;
    unsigned long long updates = 0;
    engine_clock_reset(&clock, begin);
    engine_clock_reset(&palette_clock, begin);
    int fade_black = 0;
    for (;;) {
        lk_platform_poll();
        if (lk_platform_exit_requested()) {
            break;
        }
        unsigned long long palette_ticks;
        if (engine_clock_elapsed_ticks(&palette_clock, lk_platform_time_ns(), &palette_ticks) != 0) {
            lk_platform_log("Lion King: invalid palette clock state.\n");
            return 1;
        }
        for (unsigned long long i = 0; i < palette_ticks && fade.active; ++i) {
            if (vga_fade_tick(&fade) < 0) {
                lk_platform_log("Lion King: invalid palette transition state.\n");
                return 1;
            }
        }
        if (input_poll_controls(&input, &api->Input) != 0) {
            lk_platform_log("Lion King: cannot read preview controls.\n");
            return 1;
        }
        if (input.pressed & 4) {
            part[18] = (unsigned char)((part[18] + frames - 1) % frames);
        }
        if (input.pressed & 8) {
            part[18] = (unsigned char)((part[18] + 1) % frames);
        }
        if (input.pressed & 0x10) {
            node->pass_flags ^= 8;
        }
        if (input.pressed & 0x40) {
            node->pass_flags ^= 0x10;
        }
        if (input.pressed & 0x100) {
            node->flags ^= 0x80;
        }
        if (input.pressed & 0x20) {
            part[18] = node->pass_flags = node->flags = 0;
            fade_black = 0;
            if (vga_fade_initialize(&fade, level_rgb) != 0) {
                lk_platform_log("Lion King: cannot reset preview palette.\n");
                return 1;
            }
        }
        /* F is a diagnostic command, not an added gameplay binding. */
        if (api->Input.KeyPressed[0x09]) {
            fade_black = !fade_black;
            if (vga_fade_begin(&fade, fade_black ? black_rgb : level_rgb) != 0) {
                lk_platform_log("Lion King: cannot start palette transition.\n");
                return 1;
            }
        }
        if (vga_palette_colors(fade.current, palette) != 0) {
            lk_platform_log("Lion King: invalid preview palette components.\n");
            return 1;
        }
        unsigned char *view = pixels + ((frame.camera_y + 1U) & 7) * LK_WIDTH;
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) {
            view[i] = 0;
        }
        if (render_map_tile_pass(map, map_size, 0, 0, 0, 0, view) != 0 ||
            render_map_tile_pass(map, map_size, 0, 0, 0, 1, view) != 0 ||
            render_object_pass(&render_pool, 0, 0, 0, &bank, 1, view) != 0 ||
            render_object_pass(&render_pool, 0x80, 0, 0, &bank, 1, view) != 0) {
            lk_platform_log("Lion King: invalid preview map or sprite descriptor.\n");
            return 1;
        }
        if (vga_present_frame(&frame) != 0) {
            lk_platform_log("Lion King: invalid presentation buffer.\n");
            return 1;
        }
        unsigned long long now = lk_platform_time_ns();
        /* Keep the original render-before-update ordering; no gameplay callback yet. */
        if (engine_dispatch_ticks(&clock, now, count_updates, &updates) < 0) {
            lk_platform_log("Lion King: invalid monotonic clock state.\n");
            return 1;
        }
        if (selftest && now - begin >= 1000000000ULL) {
            break;
        }
        lk_platform_sleep(10);
    }
    lk_platform_log("Lion King DOS64 platform test finished.\n");
    return 0;
}
