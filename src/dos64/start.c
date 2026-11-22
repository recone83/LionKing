#include "start_runtime.h"
#include "preview_idle.h"
#include "preview_player.h"
#include "preview_background.h"
#include "preview_bonus.h"
#include "preview_emitter.h"
#include "frontend.h"

GAME_BUFFERS *game_buffers;
unsigned char *pixels, *hurt_layer, *packed, *map, *map_contours;
unsigned char *animated_tiles, *level_music;
unsigned char (*enemy_sprites)[65536], *game_over_sprites;
unsigned char (*pickup_sprites)[131072], *hud_sprites;
unsigned char (*effect_samples)[65536], *sprite;
unsigned char (*idle_sprites)[32768], (*player_sprites)[32768];
DOS64_COLOR palette[256];
MUSIC_PLAYER music_player;
MUSIC_OUTPUT music_output;
BONUS_ASSETS *bonus_assets;
int menu_active;
unsigned int loading_level = 1;
int sound_enabled = 1;
int music_enabled = 1;
ENGINE_CONTROLS game_controls = ENGINE_CONTROLS_DEFAULT;
ENGINE_DIFFICULTY game_difficulty = ENGINE_DIFFICULTY_NORMAL;

ENGINE_ENEMIES map_enemies;
ENGINE_PICKUPS map_pickups;
unsigned int game_over_size;
unsigned int effect_sizes[GAME_EFFECT_SLOTS];
RESOURCE_DICTIONARY dictionary;
RENDER_POOL render_pool;
VGA_FADE fade;
unsigned char level_rgb[768];
const unsigned char black_rgb[768];
ENGINE_OBJECT_POOL scene_objects;
ENGINE_EMITTER_GROUP scene_emitters;
int scene_failed;
DOS64_API resource_api;

int loading_progress(unsigned int completed)
{
    return menu_active ? frontend_loading_for_level(completed,
        25 + ASSETS_YOUNG_BANK_COUNT + (loading_level == 2 ?
            LEVEL2_ENEMY_BANK_COUNT : LEVEL1_ENEMY_BANK_COUNT), loading_level) : 0;
}

int start_level_two(const DOS64_API *api, unsigned char *lives,
    unsigned int *continues, unsigned short *max_roar)
{
    return run_level_two(api, lives, continues, max_roar);
}

static int game_buffers_initialize(const DOS64_API *api)
{
    if (memory_init(api) != 0) {
        lk_platform_log("Lion King: game heap service unavailable.\n");
        return -1;
    }
    game_buffers = memory_calloc(1, sizeof(*game_buffers));
    if (!game_buffers) {
        lk_platform_log("Lion King: cannot allocate game buffers.\n");
        return -1;
    }
    pixels = game_buffers->pixels;
    hurt_layer = game_buffers->hurt_layer;
    packed = game_buffers->packed;
    map = game_buffers->map;
    map_contours = game_buffers->map_contours;
    animated_tiles = game_buffers->animated_tiles;
    level_music = game_buffers->level_music;
    enemy_sprites = game_buffers->enemy_sprites;
    game_over_sprites = game_buffers->game_over_sprites;
    pickup_sprites = game_buffers->pickup_sprites;
    hud_sprites = game_buffers->hud_sprites;
    effect_samples = game_buffers->effect_samples;
    sprite = game_buffers->sprite;
    idle_sprites = game_buffers->idle_sprites;
    player_sprites = game_buffers->player_sprites;
    return 0;
}


static void __attribute__((ms_abi)) log_resource_message(const char *text)
{
    lk_platform_log(text);
}


void log_map_measurement(const char *label, unsigned int value)
{
    char text[12];
    unsigned int end = sizeof(text) - 1;
    text[end] = 0;
    text[--end] = '\n';
    do {
        text[--end] = (char)('0' + value % 10);
        value /= 10;
    } while (value);
    lk_platform_log(label);
    lk_platform_log(text + end);
}

int argument_requested(const char *arguments, const char *expected)
{
    while (*arguments == ' ') {
        ++arguments;
    }
    while (*expected && *arguments == *expected) {
        ++arguments;
        ++expected;
    }
    return !*expected && (!*arguments || *arguments == ' ');
}


int allocate_bonus_assets(const DOS64_API *api)
{
    if (memory_init(api) != 0) {
        lk_platform_log("Lion King: bonus heap service unavailable.\n");
        return -1;
    }
    bonus_assets = memory_alloc(sizeof(*bonus_assets));
    if (!bonus_assets) {
        lk_platform_log("Lion King: cannot allocate bonus assets.\n");
        return -1;
    }
    return 0;
}


static int run_preview(const DOS64_API *api)
{
    if (!api->Arguments) {
        lk_platform_log("Lion King: missing runtime argument string.\n");
        return 1;
    }
    if (argument_requested(api->Arguments, "--bonus-check")) {
        if (allocate_bonus_assets(api) != 0 ||
            bonus_assets_load(bonus_assets, &resource_api, "LIONKING.EPF",
                packed, sizeof(game_buffers->packed), &dictionary) != 0)
            return 1;
        if (vga_load_palette(bonus_assets->map, bonus_assets->map_size, palette) != 0 ||
            render_map_tile_pass(bonus_assets->map, bonus_assets->map_size, 0, 0, 0, 0, pixels) != 0 ||
            render_draw_sprite(bonus_assets->timon, bonus_assets->timon_size, 0, 0, 0, pixels) != 0 ||
            render_draw_sprite(bonus_assets->pumbaa, bonus_assets->pumbaa_size, 0, 0, 0, pixels) != 0 ||
            render_draw_sprite(bonus_assets->pumbaa_burp, bonus_assets->pumbaa_burp_size, 0, 0, 0, pixels) != 0 ||
            render_draw_sprite(bonus_assets->bugs, bonus_assets->bugs_size, 0, 0, 0, pixels) != 0 ||
            music_initialize(&music_player, bonus_assets->hunt_music, bonus_assets->hunt_music_size) != 0 ||
            music_initialize(&music_player, bonus_assets->toss_music, bonus_assets->toss_music_size) != 0 ||
            music_effect_play(&music_player, 0, bonus_assets->burp_sound, bonus_assets->burp_sound_size) != 0) {
            lk_platform_log("Lion King: invalid bonus game graphics or music.\n");
            return 1;
        }
        lk_platform_log("Bonus check: map, sprites and music loaded; gameplay is not implemented.\n");
        return 0;
    }
    if (argument_requested(api->Arguments, "--bonus-view")) return run_bonus_view(api);
    if (argument_requested(api->Arguments, "--bug-toss")) {
        unsigned char lives;
        unsigned int continues;
        unsigned short max_roar = 16;
        if (engine_difficulty_counts(game_difficulty, &lives, &continues) != 0) {
            lk_platform_log("Lion King: invalid difficulty for BUG TOSS.\n");
            return 1;
        }
        return run_bonus_toss_game(api, &lives, &continues, &max_roar) == 1 ? 1 : 0;
    }
    if (argument_requested(api->Arguments, "--background6")) return run_background_preview(api, 6);
    if (argument_requested(api->Arguments, "--background10")) return run_background_preview(api, 10);
    if (argument_requested(api->Arguments, "--background")) return run_background_preview(api, 1);
    if (argument_requested(api->Arguments, "--deflection")) {
        return run_deflection_preview(api, 0);
    }
    if (argument_requested(api->Arguments, "--emitters")) {
        return run_emitter_scene(api);
    }
    if (argument_requested(api->Arguments, "--flight")) {
        return run_deflection_preview(api, 1);
    }
    if (argument_requested(api->Arguments, "--jump")) {
        return run_deflection_preview(api, 2);
    }
    if (argument_requested(api->Arguments, "--contacts")) {
        return run_deflection_preview(api, 4);
    }
    if (argument_requested(api->Arguments, "--ledges")) {
        return run_deflection_preview(api, 5);
    }
    if (argument_requested(api->Arguments, "--walls")) {
        return run_deflection_preview(api, 6);
    }
    if (argument_requested(api->Arguments, "--level2")) {
        return run_deflection_preview(api, 9);
    }
    if (argument_requested(api->Arguments, "--map") ||
        argument_requested(api->Arguments, "--continue-test")) {
        return run_deflection_preview(api,
            argument_requested(api->Arguments, "--continue-test") ? 8 : 7);
    }
    if (!argument_requested(api->Arguments, "--idle") &&
        !argument_requested(api->Arguments, "--manual") &&
        !argument_requested(api->Arguments, "--selftest")) {
        if (argument_requested(api->Arguments, "--preview"))
            return run_deflection_preview(api, 3);
        if (frontend_initialize(&resource_api) != 0 || frontend_splash(api) != 0 ||
            frontend_intro(api) != 0)
            return 1;
        menu_active = 1;
        for (;;) {
            int selection = frontend_menu(api, &music_enabled, &sound_enabled,
                &game_difficulty, &game_controls);
            if (selection <= 0) return selection < 0 ? 1 : 0;
            if (frontend_pregame(api, sound_enabled) != 0) return 1;
            int result = run_deflection_preview(api, 7);
            music_output_stop(&music_output);
            if (result != 0) return result;
            lk_platform_log("Main menu: returning from LEVEL1.\n");
        }
    }
    LK_EPF_INFO archive;
    if (resources_open_archive(&resource_api, "LIONKING.EPF", &archive) != 0) {
        return 1;
    }
    lk_platform_log("Lion King: EPF index and payload bounds verified.\n");
    unsigned int loaded;
    if (resources_load_entry(&resource_api, "LIONKING.EPF", "LEVEL1.MAP", packed, sizeof(game_buffers->packed),
        map, sizeof(game_buffers->map), &dictionary, &loaded) != 0) {
        return 1;
    }
    if (vga_load_palette_rgb(map, loaded, level_rgb) != 0 ||
        vga_fade_initialize(&fade, level_rgb) != 0 ||
        vga_palette_colors(fade.current, palette) != 0) {
        lk_platform_log("Lion King: invalid level palette.\n");
        return 1;
    }
    unsigned int map_size = loaded;
    RENDER_OWNER owner = {140, 80};
    /* Diagnostic one-part descriptor, not a reconstructed game animation script. */
    unsigned char part[20] = {1, 0};
    RENDER_SPRITE_BANK banks[34] = {0};
    unsigned int bank_index = ASSETS_YOUNG_IDLE_INDEX, frames;
    if (load_preview_bank(&resource_api, bank_index, banks, part, &frames) != 0) {
        return 1;
    }
    render_initialize_nodes(&render_pool);
    RENDER_NODE *node = render_acquire_node(&render_pool, &owner, 0, 0, part, sizeof(part));
    if (!node) {
        lk_platform_log("Lion King: cannot acquire preview render node.\n");
        return 1;
    }
    ENGINE_INPUT input;
    input_initialize(&input);
    VGA_FRAME frame = {pixels, sizeof(game_buffers->pixels), 0, palette, present_frame, 0};
    PREVIEW_ANIMATION animation = {0};
    animation.node = node;
    animation.owner = &owner;
    if (!argument_requested(api->Arguments, "--manual") &&
        start_idle_preview(&resource_api, banks, &animation) != 0) {
        return 1;
    }
    lk_platform_log("Lion King DOS64 interactive asset test; not gameplay.\n"
        "Up/Down: bank. Left/Right: frame. Alt/Ctrl: flip X/Y. Shift: hide.\n"
        "A: original idle sequence/manual. F: fade to black/back. Space: reset. Escape: exit.\n");
    int selftest = argument_requested(api->Arguments, "--selftest");
    unsigned long long begin = lk_platform_time_ns();
    ENGINE_CLOCK clock;
    ENGINE_CLOCK palette_clock;
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
        if (api->Input.KeyPressed[0x04]) {
            if (!animation.enabled) {
                if (start_idle_preview(&resource_api, banks, &animation) != 0) {
                    return 1;
                }
            } else {
                animation.enabled = 0;
                if (load_preview_bank(&resource_api, bank_index, banks, part, &frames) != 0) {
                    return 1;
                }
                node->parts = part;
                node->parts_size = sizeof(part);
                lk_platform_log("Manual bank/frame browsing restored.\n");
            }
            engine_clock_reset(&clock, lk_platform_time_ns());
        }
        unsigned int selected_bank = bank_index;
        if (!animation.enabled && (input.pressed & 1)) {
            selected_bank = (selected_bank + ASSETS_YOUNG_BANK_COUNT - 1) % ASSETS_YOUNG_BANK_COUNT;
        }
        if (!animation.enabled && (input.pressed & 2)) {
            selected_bank = (selected_bank + 1) % ASSETS_YOUNG_BANK_COUNT;
        }
        if (selected_bank != bank_index) {
            if (load_preview_bank(&resource_api, selected_bank, banks, part, &frames) != 0) {
                return 1;
            }
            bank_index = selected_bank;
        }
        if (!animation.enabled && (input.pressed & 4)) {
            part[18] = (unsigned char)((part[18] + frames - 1) % frames);
        }
        if (!animation.enabled && (input.pressed & 8)) {
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
            if (animation.enabled) {
                animation.enabled = 0;
                if (load_preview_bank(&resource_api, bank_index, banks, part, &frames) != 0) {
                    return 1;
                }
                node->parts = part;
                node->parts_size = sizeof(part);
            }
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
            render_object_pass(&render_pool, 0, 0, 0, banks, 34, view) != 0 ||
            render_object_pass(&render_pool, 0x80, 0, 0, banks, 34, view) != 0) {
            lk_platform_log("Lion King: invalid preview map or sprite descriptor.\n");
            return 1;
        }
        if (vga_present_frame(&frame) != 0) {
            lk_platform_log("Lion King: invalid presentation buffer.\n");
            return 1;
        }
        unsigned long long now = lk_platform_time_ns();
        if (engine_dispatch_ticks(&clock, now, update_preview, &animation) < 0) {
            lk_platform_log("Lion King: invalid monotonic clock state.\n");
            return 1;
        }
        if (animation.failed) {
            lk_platform_log("Lion King: original idle animation update failed.\n");
            return 1;
        }
        if (selftest && now - begin >= 1000000000ULL) {
            break;
        }
    }
    lk_platform_log("Lion King DOS64 platform test finished.\n");
    return 0;
}

int __attribute__((ms_abi)) start(const DOS64_API *api)
{
    if (lk_platform_init(api) != 0) {
        return 1;
    }
    resource_api = *api;
    resource_api.Write = log_resource_message;
    music_output = (MUSIC_OUTPUT){0};
    bonus_assets = 0;
    game_buffers = 0;
    menu_active = 0;
    sound_enabled = 1;
    music_enabled = 1;
    game_controls = (ENGINE_CONTROLS)ENGINE_CONTROLS_DEFAULT;
    game_difficulty = ENGINE_DIFFICULTY_NORMAL;
    int result = game_buffers_initialize(api) == 0 ? run_preview(api) : 1;
    frontend_stop_audio();
    music_output_stop(&music_output);
    if (frontend_release() != 0) result = 1;
    if (bonus_assets) {
        if (memory_free(bonus_assets) != 0) {
            lk_platform_log("Lion King: cannot release bonus assets.\n");
            result = 1;
        }
        bonus_assets = 0;
    }
    if (game_buffers) {
        if (memory_free(game_buffers) != 0) {
            lk_platform_log("Lion King: cannot release game buffers.\n");
            result = 1;
        }
        game_buffers = 0;
    }
    return lk_platform_finish(result);
}
