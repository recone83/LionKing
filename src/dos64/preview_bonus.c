#include "start_runtime.h"
#include "preview_bonus.h"

int run_bonus_view(const DOS64_API *api)
{
    if (allocate_bonus_assets(api) != 0 ||
        bonus_assets_load(bonus_assets, &resource_api, "LIONKING.EPF",
            packed, sizeof(game_buffers->packed), &dictionary) != 0 ||
        bonus_assets->map_size < 8 + 6 * 12 ||
        vga_load_palette(bonus_assets->map, bonus_assets->map_size, palette) != 0) {
        lk_platform_log("Lion King: cannot load bonus view resources.\n");
        return 1;
    }
    const unsigned char *banks[] = {bonus_assets->timon, bonus_assets->pumbaa, bonus_assets->bugs};
    unsigned int sizes[] = {bonus_assets->timon_size, bonus_assets->pumbaa_size, bonus_assets->bugs_size};
    unsigned int counts[3];
    for (unsigned int i = 0; i < 3; ++i) {
        if (sizes[i] < 2 || !(counts[i] = banks[i][0] | (unsigned int)banks[i][1] << 8) ||
            counts[i] > 0x2000) {
            lk_platform_log("Lion King: invalid bonus view sprite bank.\n");
            return 1;
        }
    }
    unsigned int bank = 0, index = 0, layer = 0, camera_x = 0, camera_y = 0;
    int animate = 0;
    unsigned long long animation_time = 0;
    lk_platform_log("Bonus asset view (not gameplay): 1/2/3 select sprite bank, "
        "Left/Right select frame, Space animates, 4-9 select map layer, WASD moves camera, "
        "H/T play BUGHUNT/BUGTOSS, M stops music, Escape exits.\n");
    for (;;) {
        lk_platform_poll();
        if (lk_platform_exit_requested()) break;
        for (unsigned int i = 0; i < 3; ++i)
            if (api->Input.KeyPressed[0x1e + i]) { bank = i; index = 0; }
        for (unsigned int i = 0; i < 6; ++i) {
            if (api->Input.KeyPressed[0x21 + i]) {
                layer = i;
                camera_x = camera_y = 0;
            }
        }
        if (api->Input.KeyPressed[0x50]) index = index ? index - 1 : counts[bank] - 1;
        if (api->Input.KeyPressed[0x4f]) index = (index + 1) % counts[bank];
        if (api->Input.KeyPressed[0x2c]) {
            animate = !animate;
            animation_time = lk_platform_time_ns();
        }
        if (animate) {
            unsigned long long now = lk_platform_time_ns();
            if (now < animation_time) {
                lk_platform_log("Lion King: bonus view clock moved backwards.\n");
                return 1;
            }
            unsigned long long steps = (now - animation_time) / 100000000ULL;
            index = (index + (unsigned int)(steps % counts[bank])) % counts[bank];
            animation_time += steps * 100000000ULL;
        }
        const unsigned char *entry = bonus_assets->map + 8 + layer * 12;
        unsigned int width = entry[0] | (unsigned int)entry[1] << 8 |
            (unsigned int)entry[2] << 16 | (unsigned int)entry[3] << 24;
        unsigned int height = entry[4] | (unsigned int)entry[5] << 8 |
            (unsigned int)entry[6] << 16 | (unsigned int)entry[7] << 24;
        if (!width || !height || width > 65535 || height > 65535) {
            lk_platform_log("Lion King: invalid bonus view map layer.\n");
            return 1;
        }
        unsigned int max_x = width * 8 > LK_WIDTH ? width * 8 - LK_WIDTH : 0;
        unsigned int max_y = height * 8 > LK_HEIGHT ? height * 8 - LK_HEIGHT : 0;
        if (max_x > 65535) max_x = 65535;
        if (max_y > 65535) max_y = 65535;
        if (api->Input.KeyPressed[0x04]) camera_x = camera_x > 32 ? camera_x - 32 : 0;
        if (api->Input.KeyPressed[0x1a]) camera_y = camera_y > 32 ? camera_y - 32 : 0;
        if (api->Input.KeyPressed[0x07]) camera_x = camera_x + 32 < max_x ? camera_x + 32 : max_x;
        if (api->Input.KeyPressed[0x16]) camera_y = camera_y + 32 < max_y ? camera_y + 32 : max_y;
        if (api->Input.KeyPressed[0x10]) music_output_stop(&music_output);
        if (api->Input.KeyPressed[0x0b] || api->Input.KeyPressed[0x17]) {
            int hunt = api->Input.KeyPressed[0x0b] != 0;
            music_output_stop(&music_output);
            if (music_initialize(&music_player, hunt ? bonus_assets->hunt_music : bonus_assets->toss_music,
                    hunt ? bonus_assets->hunt_music_size : bonus_assets->toss_music_size) != 0 ||
                music_output_open(&music_output, &music_player, api) != 0) {
                lk_platform_log("Lion King: cannot play bonus view music.\n");
                return 1;
            }
        }
        if (music_output.opened && music_output_service(&music_output) != 0) {
            lk_platform_log("Lion King: bonus view audio streaming failed.\n");
            return 1;
        }
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) pixels[i] = 0;
        if (render_map_tile_pass(bonus_assets->map, bonus_assets->map_size, layer, camera_x, camera_y, 0, pixels) != 0 ||
            render_map_tile_pass(bonus_assets->map, bonus_assets->map_size, layer, camera_x, camera_y, 1, pixels) != 0 ||
            render_draw_sprite(banks[bank], sizes[bank], (unsigned short)index, 150, 80, pixels) != 0) {
            lk_platform_log("Lion King: cannot render bonus view.\n");
            return 1;
        }
        lk_platform_present(pixels, palette);
        lk_platform_sleep(20);
    }
    return 0;
}

