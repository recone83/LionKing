#include "start_runtime.h"
#include "preview_bonus.h"
#include "engine/bonus_toss.h"
#include "engine/bonus_toss_stage.h"

typedef struct {
    BONUS_TOSS_PLAYER player;
    const DOS64_API *api;
    uint32_t random;
    int failed;
} TOSS_MOVEMENT_VIEW;

static int toss_movement_sound(void *context)
{
    TOSS_MOVEMENT_VIEW *view = context;
    if (!sound_enabled) return 0;
    if ((!music_output.opened &&
            (music_effects_initialize(&music_player) != 0 ||
             music_output_open(&music_output, &music_player, view->api) != 0)) ||
        music_effect_play(&music_player, 0, bonus_assets->burp_sound,
            bonus_assets->burp_sound_size) != 0) {
        lk_platform_log("Lion King: cannot play bonus burp sound.\n");
        return -1;
    }
    return 0;
}

static void toss_movement_update(void *context)
{
    TOSS_MOVEMENT_VIEW *view = context;
    if (view->failed) return;
    if (bonus_toss_player_tick(&view->player,
        !!view->api->Input.KeyDown[game_controls.keys[CONTROL_LEFT]],
        !!view->api->Input.KeyDown[game_controls.keys[CONTROL_RIGHT]],
        !!(view->api->Input.KeyDown[game_controls.keys[CONTROL_JUMP]] ||
           view->api->Input.KeyDown[game_controls.keys[CONTROL_SLASH]] ||
           view->api->Input.KeyDown[game_controls.keys[CONTROL_ROAR]] ||
           (engine_controls_alternate_roar(&game_controls) && view->api->Input.KeyDown[0xe4]))) != 0)
        view->failed = 1;
}

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
    int movement_view = 0;
    ENGINE_CLOCK movement_clock;
    static TOSS_MOVEMENT_VIEW movement;
    static RENDER_POOL movement_pool;
    RENDER_SPRITE_BANK movement_banks[0x57] = {{0}};
    movement = (TOSS_MOVEMENT_VIEW){0};
    movement.api = api;
    movement.random = 0x010101;
    movement_banks[0x55] = (RENDER_SPRITE_BANK){bonus_assets->pumbaa, bonus_assets->pumbaa_size};
    movement_banks[0x56] = (RENDER_SPRITE_BANK){bonus_assets->pumbaa_burp, bonus_assets->pumbaa_burp_size};
    lk_platform_log("Bonus asset view (not gameplay): 1/2/3 select sprite bank, "
        "Left/Right select frame, Space animates, 4-9 select map layer, WASD moves camera, "
        "P toggles Pumbaa inspection, jump/slash/roar burp once, H/T play BUGHUNT/BUGTOSS, "
        "M stops music, Escape exits.\n");
    for (;;) {
        lk_platform_poll();
        if (lk_platform_exit_requested()) break;
        if (api->Input.KeyPressed[0x13]) {
            if (movement_view) {
                if (render_release_node(&movement_pool, movement.player.node) != 0) {
                    lk_platform_log("Lion King: cannot release bonus movement node.\n");
                    return 1;
                }
                movement_view = 0;
            } else {
                render_initialize_nodes(&movement_pool);
                movement.random = 0x010101;
                if (bonus_toss_player_initialize(&movement.player, &movement_pool,
                    &movement.random, toss_movement_sound, &movement) != 0) {
                    lk_platform_log("Lion King: cannot initialize bonus movement view.\n");
                    return 1;
                }
                movement.failed = 0;
                engine_clock_reset(&movement_clock, lk_platform_time_ns());
                movement_view = 1;
                camera_x = 0;
                camera_y = 32;
            }
        }
        for (unsigned int i = 0; i < 3; ++i)
            if (api->Input.KeyPressed[0x1e + i]) { bank = i; index = 0; }
        for (unsigned int i = 0; i < 6; ++i) {
            if (api->Input.KeyPressed[0x21 + i]) {
                layer = i;
                camera_x = camera_y = 0;
            }
        }
        if (!movement_view && api->Input.KeyPressed[0x50]) index = index ? index - 1 : counts[bank] - 1;
        if (!movement_view && api->Input.KeyPressed[0x4f]) index = (index + 1) % counts[bank];
        if (!movement_view && api->Input.KeyPressed[0x2c]) {
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
        if (camera_x > max_x) camera_x = max_x;
        if (camera_y > max_y) camera_y = max_y;
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
        if (movement_view &&
            (engine_dispatch_ticks(&movement_clock, lk_platform_time_ns(),
                toss_movement_update, &movement) < 0 || movement.failed)) {
            lk_platform_log("Lion King: bonus movement view update failed.\n");
            return 1;
        }
        unsigned int view_y = camera_y;
        if (movement_view && movement.player.shake && view_y < max_y) ++view_y;
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) pixels[i] = 0;
        if (render_map_tile_pass(bonus_assets->map, bonus_assets->map_size, layer, camera_x, view_y, 0, pixels) != 0 ||
            render_map_tile_pass(bonus_assets->map, bonus_assets->map_size, layer, camera_x, view_y, 1, pixels) != 0 ||
            (movement_view ?
                render_object_pass(&movement_pool, 0, (short)-(int)camera_x, (short)-(int)view_y,
                    movement_banks, 0x57, pixels) :
                render_draw_sprite(banks[bank], sizes[bank], (unsigned short)index, 150, 80, pixels)) != 0) {
            lk_platform_log("Lion King: cannot render bonus view.\n");
            return 1;
        }
        lk_platform_present(pixels, palette);
        lk_platform_sleep(20);
    }
    return 0;
}

typedef struct {
    BONUS_TOSS_STAGE stage;
    const DOS64_API *api;
    int failed;
} TOSS_GAME_LOOP;

static int toss_game_sound(void *context)
{
    const DOS64_API *api = context;
    if (!sound_enabled) return 0;
    if (!music_output.opened &&
        (music_effects_initialize(&music_player) != 0 ||
         music_output_open(&music_output, &music_player, api) != 0)) {
        lk_platform_log("Lion King: cannot open BUG TOSS sound output.\n");
        return -1;
    }
    if (music_effect_play(&music_player, 0, bonus_assets->burp_sound,
        bonus_assets->burp_sound_size) != 0) {
        lk_platform_log("Lion King: cannot play BUG TOSS burp.\n");
        return -1;
    }
    return 0;
}

static void toss_game_tick(void *context)
{
    TOSS_GAME_LOOP *loop = context;
    if (loop->failed || loop->stage.result != BONUS_TOSS_STAGE_RUNNING) return;
    const DOS64_API *api = loop->api;
    int left = !!api->Input.KeyDown[game_controls.keys[CONTROL_LEFT]];
    int right = !!api->Input.KeyDown[game_controls.keys[CONTROL_RIGHT]];
    int action = !!(api->Input.KeyDown[game_controls.keys[CONTROL_JUMP]] ||
        api->Input.KeyDown[game_controls.keys[CONTROL_SLASH]] ||
        api->Input.KeyDown[game_controls.keys[CONTROL_ROAR]] ||
        (engine_controls_alternate_roar(&game_controls) && api->Input.KeyDown[0xe4]));
    unsigned int caught = loop->stage.caught;
    if (bonus_toss_stage_tick(&loop->stage, left, right, action) != 0) {
        lk_platform_log("Lion King: BUG TOSS simulation failed.\n");
        loop->failed = 1;
    } else if (loop->stage.caught != caught && sound_enabled &&
        music_effect_play(&music_player, 0, bonus_assets->collect_sound,
            bonus_assets->collect_sound_size) != 0) {
        lk_platform_log("Lion King: cannot play BUG TOSS catch sound.\n");
        loop->failed = 1;
    }
}

typedef struct {
    BONUS_TOSS_RESULT_CLOCK clock;
    const DOS64_API *api;
    int failed;
} TOSS_RESULT_CLOCK;

static void toss_result_tick(void *context)
{
    TOSS_RESULT_CLOCK *result = context;
    if (result->failed) return;
    int sound = bonus_toss_result_tick(&result->clock);
    if (sound < 0) {
        result->failed = 1;
        return;
    }
    if (sound && sound_enabled) {
        if ((!music_output.opened &&
                (music_effects_initialize(&music_player) != 0 ||
                 music_output_open(&music_output, &music_player, result->api) != 0)) ||
            music_effect_play(&music_player, 0, bonus_assets->burp_sound,
                bonus_assets->burp_sound_size) != 0 ||
            music_effect_play(&music_player, 1, bonus_assets->burp_sound,
                bonus_assets->burp_sound_size) != 0) {
            lk_platform_log("Lion King: cannot play BUG TOSS result sound.\n");
            result->failed = 1;
            return;
        }
    }
}

static int toss_result_screen(const DOS64_API *api, unsigned int caught)
{
    unsigned int map_size, collect_size, numbers_size;
    if (resources_load_entry(&resource_api, "LIONKING.EPF", "TITLES.MAP",
            packed, sizeof(game_buffers->packed), map, sizeof(game_buffers->map),
            &dictionary, &map_size) != 0 ||
        resources_load_entry(&resource_api, "LIONKING.EPF", "COLLECT.MCH",
            packed, sizeof(game_buffers->packed), sprite, sizeof(game_buffers->sprite),
            &dictionary, &collect_size) != 0 ||
        resources_load_entry(&resource_api, "LIONKING.EPF", "NUMBERS.MCH",
            packed, sizeof(game_buffers->packed), game_over_sprites,
            sizeof(game_buffers->game_over_sprites), &dictionary, &numbers_size) != 0 ||
        vga_load_palette(map, map_size, palette) != 0) {
        lk_platform_log("Lion King: cannot load BUG TOSS result screen.\n");
        return -1;
    }
    static RENDER_POOL pool;
    render_initialize_nodes(&pool);
    RENDER_OWNER label = {130, 96}, ones = {266, 95}, tens = {250, 95};
    RENDER_NODE *label_node = render_acquire_node(&pool, &label, 0, 0,
        animation_movement_data + 0xc044 - ANIMATION_MOVEMENT_BASE, 20);
    RENDER_NODE *ones_node = render_acquire_node(&pool, &ones, 0, 0,
        animation_movement_data + 0xc058 - ANIMATION_MOVEMENT_BASE, 20);
    RENDER_NODE *tens_node = render_acquire_node(&pool, &tens, 0, 0,
        animation_movement_data + 0xc058 - ANIMATION_MOVEMENT_BASE, 20);
    if (!label_node || !ones_node || !tens_node) {
        lk_platform_log("Lion King: cannot initialize BUG TOSS result screen.\n");
        return -1;
    }
    static RENDER_SPRITE_BANK banks[0x66];
    banks[0x64] = (RENDER_SPRITE_BANK){sprite, collect_size};
    banks[0x65] = (RENDER_SPRITE_BANK){game_over_sprites, numbers_size};
    TOSS_RESULT_CLOCK result = {0};
    if (bonus_toss_result_initialize(&result.clock, caught) != 0) return -1;
    result.api = api;
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, lk_platform_time_ns());
    lk_platform_log("BUG TOSS: result screen.\n");
    while (result.clock.timer >= 0) {
        lk_platform_poll();
        if (lk_platform_exit_requested() || api->Input.KeyPressed[0x29]) {
            music_output_stop(&music_output);
            return 1;
        }
        if (engine_dispatch_ticks(&clock, lk_platform_time_ns(), toss_result_tick, &result) < 0 ||
            result.failed || (music_output.opened && music_output_service(&music_output) != 0)) {
            lk_platform_log("Lion King: BUG TOSS result clock failed.\n");
            music_output_stop(&music_output);
            return -1;
        }
        ones_node->parts = animation_movement_data + 0xc058 +
            20 * (result.clock.displayed % 10) - ANIMATION_MOVEMENT_BASE;
        tens_node->parts = animation_movement_data + 0xc058 +
            20 * (result.clock.displayed / 10) - ANIMATION_MOVEMENT_BASE;
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) pixels[i] = 0;
        if (render_object_pass(&pool, 0, 0, 0, banks, 0x66, pixels) != 0) {
            lk_platform_log("Lion King: cannot render BUG TOSS result screen.\n");
            music_output_stop(&music_output);
            return -1;
        }
        lk_platform_present(pixels, palette);
        lk_platform_sleep(10);
    }
    music_output_stop(&music_output);
    return 0;
}

int run_bonus_toss_game(const DOS64_API *api, unsigned char *lives, unsigned int *continues,
    unsigned short *max_roar)
{
    static RENDER_POOL renders;
    static RENDER_SPRITE_BANK banks[0x59];
    if (!api || !lives || !continues || !max_roar ||
        (!bonus_assets && allocate_bonus_assets(api) != 0) ||
        bonus_assets_load(bonus_assets, &resource_api, "LIONKING.EPF",
            packed, sizeof(game_buffers->packed), &dictionary) != 0 ||
        vga_load_palette(bonus_assets->map, bonus_assets->map_size, palette) != 0) {
        lk_platform_log("Lion King: cannot load original BUG TOSS stage resources.\n");
        return 1;
    }
    banks[0x51] = (RENDER_SPRITE_BANK){bonus_assets->bugs, bonus_assets->bugs_size};
    banks[0x52] = (RENDER_SPRITE_BANK){bonus_assets->destiny, bonus_assets->destiny_size};
    banks[0x53] = (RENDER_SPRITE_BANK){bonus_assets->circle, bonus_assets->circle_size};
    banks[0x54] = (RENDER_SPRITE_BANK){bonus_assets->meat, bonus_assets->meat_size};
    banks[0x55] = (RENDER_SPRITE_BANK){bonus_assets->pumbaa, bonus_assets->pumbaa_size};
    banks[0x56] = (RENDER_SPRITE_BANK){bonus_assets->pumbaa_burp, bonus_assets->pumbaa_burp_size};
    banks[0x57] = (RENDER_SPRITE_BANK){bonus_assets->timon, bonus_assets->timon_size};
    banks[0x58] = (RENDER_SPRITE_BANK){bonus_assets->timon_walk, bonus_assets->timon_walk_size};

    music_output_stop(&music_output);
    if ((music_enabled &&
            music_initialize(&music_player, bonus_assets->toss_music,
                bonus_assets->toss_music_size) != 0) ||
        (!music_enabled && music_effects_initialize(&music_player) != 0) ||
        ((music_enabled || sound_enabled) &&
            music_output_open(&music_output, &music_player, api) != 0)) {
        music_output_stop(&music_output);
        lk_platform_log("Lion King: cannot start original BUG TOSS audio.\n");
        return 1;
    }
    TOSS_GAME_LOOP loop = {0};
    loop.api = api;
    if (bonus_toss_stage_initialize(&loop.stage, &renders, 0x010101,
        lives, continues, max_roar, toss_game_sound, (void *)api) != 0) {
        music_output_stop(&music_output);
        lk_platform_log("Lion King: cannot initialize original BUG TOSS stage.\n");
        return 1;
    }
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, lk_platform_time_ns());
    lk_platform_log("BUG TOSS: left/right move Pumbaa; jump/slash/roar burp once; Escape exits the round.\n");
    int done = 0, failed = 0, escaped = 0;
    while (!done) {
        lk_platform_poll();
        if (lk_platform_exit_requested() || api->Input.KeyPressed[0x29]) {
            escaped = 1;
            break;
        }
        unsigned long long now = lk_platform_time_ns();
        if (engine_dispatch_ticks(&clock, now, toss_game_tick, &loop) < 0 ||
            loop.failed || (music_output.opened && music_output_service(&music_output) != 0)) {
            lk_platform_log("Lion King: BUG TOSS update or audio failed.\n");
            failed = 1;
            break;
        }
        if (loop.stage.result != BONUS_TOSS_STAGE_RUNNING) { done = 1; continue; }
        unsigned int view_y = 8 + loop.stage.player.shake;
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) pixels[i] = 0;
        if (render_map_tile_pass(bonus_assets->map, bonus_assets->map_size,
                5, 0, 0, 0, pixels) != 0 ||
            render_map_tile_pass(bonus_assets->map, bonus_assets->map_size,
                5, 0, 0, 1, pixels) != 0 ||
            render_map_tile_pass(bonus_assets->map, bonus_assets->map_size,
                4, 0, view_y, 0, pixels) != 0 ||
            render_object_pass(&renders, 0, 0, (short)-(int)view_y, banks, 0x59, pixels) != 0 ||
            render_map_tile_pass(bonus_assets->map, bonus_assets->map_size,
                4, 0, view_y, 1, pixels) != 0 ||
            render_object_pass(&renders, 0x80, 0, (short)-(int)view_y, banks, 0x59, pixels) != 0) {
            lk_platform_log("Lion King: cannot render original BUG TOSS stage.\n");
            failed = 1;
            break;
        }
        lk_platform_present(pixels, palette);
        lk_platform_sleep(10);
    }
    if (bonus_toss_stage_release(&loop.stage) != 0) {
        lk_platform_log("Lion King: cannot release BUG TOSS render objects.\n");
        failed = 1;
    }
    music_output_stop(&music_output);
    if (!failed && !escaped) {
        int result = toss_result_screen(api, loop.stage.caught);
        if (result < 0) failed = 1;
        else if (result > 0) escaped = 1;
    }
    if (loop.stage.result == BONUS_TOSS_STAGE_WON)
        lk_platform_log("BUG TOSS: round survived; earned lives and continues retained in the current level state.\n");
    else if (loop.stage.result == BONUS_TOSS_STAGE_LOST)
        lk_platform_log("BUG TOSS: Pumbaa missed an item or caught a hazard.\n");
    else
        lk_platform_log("BUG TOSS: exited before round completion.\n");
    return failed ? 1 : escaped ? 2 : 0;
}
