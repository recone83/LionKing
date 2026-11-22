#include "start_runtime.h"
#include "preview_background.h"
#include "preview_idle.h"

typedef struct {
    ENGINE_TILE_ANIMATION tiles;
    int failed;
} BACKGROUND_PREVIEW;

static void update_background_preview(void *context)
{
    BACKGROUND_PREVIEW *preview = context;
    if (preview->tiles.count && engine_tile_animation_tick(&preview->tiles) < 0) {
        lk_platform_log("Lion King: animated tile update failed.\n");
        preview->failed = 1;
    }
}

int run_background_preview(const DOS64_API *api, unsigned int level)
{
    const char *name = level == 6 ? "LEVEL6.MAP" : level == 10 ? "LEVEL10.MAP" : "LEVEL1.MAP";
    unsigned int size;
    if (resources_load_entry(&resource_api, "LIONKING.EPF", name, packed, sizeof(game_buffers->packed),
        map, sizeof(game_buffers->map), &dictionary, &size) != 0 ||
        vga_load_palette(map, size, palette) != 0) {
        lk_platform_log("Lion King: cannot load background preview map.\n");
        return 1;
    }
    BACKGROUND_PREVIEW preview = {0};
    if (level == 6 || level == 10) {
        unsigned int bytes;
        if (resources_load_entry(&resource_api, "LIONKING.EPF",
            level == 6 ? "LEVEL6.BLK" : "LEVEL10.BLK", packed, sizeof(game_buffers->packed),
            animated_tiles, sizeof(game_buffers->animated_tiles), &dictionary, &bytes) != 0 ||
            engine_tile_animation_initialize(&preview.tiles, map, size, level,
                animated_tiles, bytes) != 0) {
            lk_platform_log("Lion King: cannot initialize original animated tiles.\n");
            return 1;
        }
    }
    RENDER_OWNER camera = {0};
    unsigned short width = (unsigned short)(map[8] | (unsigned int)map[9] << 8);
    unsigned short height = (unsigned short)(map[12] | (unsigned int)map[13] << 8);
    lk_platform_log("Original background preview: arrows pan the camera; Escape exits.\n"
        "Parallax uses per-level row profiles; only levels 6/10 have BLK tile animation.\n"
        "Four original frames, one change per five logic ticks; no gameplay or text overlay.\n");
    VGA_FRAME frame = {pixels, sizeof(game_buffers->pixels), 0, palette, present_frame, 0};
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, lk_platform_time_ns());
    for (;;) {
        lk_platform_poll();
        if (lk_platform_exit_requested()) break;
        if (api->Input.KeyDown[0x50] && camera.x >= 4) camera.x -= 4;
        if (api->Input.KeyDown[0x4f]) camera.x += 4;
        if (api->Input.KeyDown[0x52] && camera.y >= 4) camera.y -= 4;
        if (api->Input.KeyDown[0x51]) camera.y += 4;
        RENDER_VIEWPORT viewport;
        if (render_prepare_viewport(&camera, width, height, 0, &viewport) != 0) {
            lk_platform_log("Lion King: invalid background preview viewport.\n");
            return 1;
        }
        camera.x = (short)viewport.x; camera.y = (short)viewport.y;
        unsigned char *view = pixels + LK_WIDTH;
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) view[i] = 0;
        if (render_map_background(map, size, level, viewport.x, viewport.y, view) != 0 ||
            render_map_tile_pass(map, size, 0, viewport.x, viewport.y, 0, view) != 0 ||
            render_map_tile_pass(map, size, 0, viewport.x, viewport.y, 1, view) != 0 ||
            vga_present_frame(&frame) != 0) {
            lk_platform_log("Lion King: cannot render original animated background.\n");
            return 1;
        }
        if (engine_dispatch_ticks(&clock, lk_platform_time_ns(),
            update_background_preview, &preview) < 0 || preview.failed) {
            lk_platform_log("Lion King: background preview tick dispatch failed.\n");
            return 1;
        }
    }
    log_map_measurement("Background level: ", level);
    log_map_measurement("Background tile frame changes: ", preview.tiles.updates);
    return 0;
}

