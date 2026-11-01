#include "platform.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "engine/timing.h"
#include "engine/input.h"
#include "engine/render.h"
#include "engine/assets.h"
#include "engine/animation.h"
#include "engine/animation_data.h"
#include "engine/behaviors.h"
#include "libs/vga.h"

static unsigned char pixels[LK_WIDTH * (LK_HEIGHT + 7)];
static DOS64_COLOR palette[256];
static unsigned char packed[79311];
static unsigned char map[580488];
static unsigned char sprite[32768];
static RESOURCE_DICTIONARY dictionary;
static RENDER_POOL render_pool;
static VGA_FADE fade;
static unsigned char level_rgb[768];
static const unsigned char black_rgb[768];
static unsigned char idle_sprites[3][32768];
static ENGINE_OBJECT_POOL scene_objects;
static ENGINE_EMITTER_GROUP scene_emitters;
static int scene_failed;

static void update_scene(void *context)
{
    const DOS64_API *const *runtime = context;
    const DOS64_API *api = *runtime;
    if (!scene_failed && engine_update_objects(&scene_objects, &api->Input) != 0) {
        scene_failed = 1;
    }
}

typedef struct {
    ANIMATION_PROGRAM program;
    RENDER_NODE *node;
    RENDER_OWNER *owner;
    int enabled;
    int failed;
    unsigned int events;
} PREVIEW_ANIMATION;

static int record_preview_event(void *context, unsigned int target)
{
    PREVIEW_ANIMATION *animation = context;
    if (target != 0x20bec && target != 0x20c70 &&
        target != 0x20d55 && target != 0x20cf4) {
        lk_platform_log("Lion King: unknown idle animation event.\n");
        return -1;
    }
    ++animation->events;
    lk_platform_log("Idle script event recorded; game object side effects not executed in preview.\n");
    return 0;
}

static void update_preview(void *context)
{
    PREVIEW_ANIMATION *animation = context;
    if (animation->enabled && !animation->failed &&
        animation_program_step(&animation->program, animation->node, animation->owner,
            record_preview_event, animation) < 0) {
        animation->failed = 1;
    }
}

static int start_idle_preview(const DOS64_API *api, RENDER_SPRITE_BANK banks[34],
    PREVIEW_ANIMATION *animation)
{
    for (unsigned int i = 0; i < 34; ++i) {
        banks[i] = (RENDER_SPRITE_BANK){0};
    }
    for (unsigned int i = 0; i < 3; ++i) {
        unsigned int slot, loaded;
        if (assets_load_named_bank(api, "LIONKING.EPF", assets_young_bank_list,
            sizeof(assets_young_bank_list), ASSETS_YOUNG_IDLE_INDEX + i,
            packed, sizeof(packed), idle_sprites[i], sizeof(idle_sprites[i]),
            &dictionary, &slot, &loaded) != 0) {
            return -1;
        }
        banks[slot] = (RENDER_SPRITE_BANK){idle_sprites[i], loaded};
    }
    if (animation_program_initialize(&animation->program, animation_idle_script,
        ANIMATION_IDLE_SCRIPT_SIZE, ANIMATION_IDLE_SCRIPT_BASE, ANIMATION_IDLE_SCRIPT_BASE,
        animation_idle_data, ANIMATION_IDLE_SIZE, ANIMATION_IDLE_BASE) != 0 ||
        animation_program_step(&animation->program, animation->node, animation->owner,
            record_preview_event, animation) < 0) {
        lk_platform_log("Lion King: invalid original idle animation stream.\n");
        return -1;
    }
    animation->enabled = 1;
    animation->failed = 0;
    lk_platform_log("Original idle visual sequence running; game events are diagnostic only.\n");
    return 0;
}

static int load_preview_bank(const DOS64_API *api, unsigned int index,
    RENDER_SPRITE_BANK banks[34], unsigned char part[20], unsigned int *frames)
{
    unsigned int slot, loaded;
    if (assets_load_named_bank(api, "LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), index, packed, sizeof(packed), sprite,
        sizeof(sprite), &dictionary, &slot, &loaded) != 0) {
        return -1;
    }
    if (loaded < 2 || slot >= 34) {
        lk_platform_log("Lion King: truncated preview sprite bank or invalid slot.\n");
        return -1;
    }
    unsigned int count = (unsigned int)sprite[0] | (unsigned int)sprite[1] << 8;
    if (!count || count > 256 || 2ULL + count * 8ULL > loaded) {
        lk_platform_log("Lion King: invalid preview sprite bank.\n");
        return -1;
    }
    for (unsigned int i = 0; i < 34; ++i) {
        banks[i] = (RENDER_SPRITE_BANK){0};
    }
    banks[slot] = (RENDER_SPRITE_BANK){sprite, loaded};
    part[18] = 0;
    part[19] = (unsigned char)slot;
    *frames = count;
    char name[13];
    if (assets_slot_list_entry(assets_young_bank_list, sizeof(assets_young_bank_list),
        index, &slot, name) != 0) {
        lk_platform_log("Lion King: invalid preview bank name.\n");
        return -1;
    }
    lk_platform_log("Sprite bank: ");
    lk_platform_log(name);
    lk_platform_log("\n");
    return 0;
}

static int present_frame(void *context, const unsigned char *source,
    const DOS64_COLOR *colors)
{
    (void)context;
    lk_platform_present(source, colors);
    return 0;
}

static int argument_requested(const char *arguments, const char *expected)
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

static int run_emitter_scene(const DOS64_API *api)
{
    unsigned int map_size, loaded, slot;
    if (resources_load_entry(api, "LIONKING.EPF", "LEVEL6.MAP", packed, sizeof(packed),
        map, sizeof(map), &dictionary, &map_size) != 0 ||
        vga_load_palette(map, map_size, palette) != 0 ||
        assets_load_named_bank(api, "LIONKING.EPF", animation_level6_bank_list,
            sizeof(animation_level6_bank_list), 0, packed, sizeof(packed),
            sprite, sizeof(sprite), &dictionary, &slot, &loaded) != 0) {
        lk_platform_log("Lion King: cannot load original emitter scene assets.\n");
        return 1;
    }
    if (slot != 160) {
        lk_platform_log("Lion King: invalid original CRUMBLIN slot.\n");
        return 1;
    }
    RENDER_SPRITE_BANK banks[161] = {0};
    banks[slot] = (RENDER_SPRITE_BANK){sprite, loaded};
    RENDER_OWNER camera = {3400, 380};
    RENDER_BOUNDS visibility = {3272, 252, 3848, 580};
    ENGINE_SHAKE_OBJECT shake = {0};
    ENGINE_MOTION player_motion = {0};
    unsigned short camera_shake = 0, immunity = 0, player_flags = 0;
    unsigned short width_tiles = (unsigned short)(map[8] | (unsigned int)map[9] << 8);
    unsigned short height_tiles = (unsigned short)(map[12] | (unsigned int)map[13] << 8);
    engine_initialize_objects(&scene_objects);
    render_initialize_nodes(&render_pool);
    scene_failed = 0;
    if (engine_setup_emitter_group(&scene_objects, &render_pool, &scene_emitters,
        &camera, &visibility, 0, 0, 0) != 0) {
        lk_platform_log("Lion King: cannot initialize original emitter group.\n");
        return 1;
    }
    lk_platform_log("Original level 6 CRUMBLIN scene: emitter -> parent -> falling child.\n"
        "Migration test, not full gameplay. Activation and impact shake after one second are fixtures.\n"
        "Escape: exit. --idle: previous Simba preview. --manual: asset browser.\n");
    VGA_FRAME frame = {pixels, sizeof(pixels), 0, palette, present_frame, 0};
    unsigned long long begin = lk_platform_time_ns();
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, begin);
    for (;;) {
        lk_platform_poll();
        if (lk_platform_exit_requested()) {
            break;
        }
        unsigned long long now = lk_platform_time_ns();
        if (!scene_objects.head) {
            if (engine_setup_emitter_group(&scene_objects, &render_pool, &scene_emitters,
                &camera, &visibility, 0, 0, 0) != 0) {
                lk_platform_log("Lion King: cannot restart emitter scene fixture.\n");
                return 1;
            }
            begin = now;
            lk_platform_log("Emitter scene fixture restarting original setup.\n");
        }
        if (!scene_emitters.trigger && now - begin >= 1000000000ULL) {
            ENGINE_OBJECT *created;
            if (engine_spawn_shake(&scene_objects, &render_pool, &shake, 0,
                &camera_shake, &immunity, &player_motion, &player_flags,
                0, 0, 0, &created) != 0) {
                lk_platform_log("Lion King: cannot create original camera shake.\n");
                return 1;
            }
            scene_emitters.trigger = 1;
            lk_platform_log("Emitter scene test activation enabled.\n");
        }
        RENDER_VIEWPORT viewport;
        if (render_prepare_viewport(&camera, width_tiles, height_tiles,
            camera_shake, &viewport) != 0) {
            lk_platform_log("Lion King: cannot prepare original scene viewport.\n");
            return 1;
        }
        unsigned char *view = pixels + ((frame.camera_y + 1U) & 7) * LK_WIDTH;
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) {
            view[i] = 0;
        }
        /* Test-scene world-to-camera mapping; original behavior state is unchanged. */
        for (RENDER_NODE *node = render_pool.head; node; node = node->next) {
            node->flags |= 0x40;
        }
        if (render_map_tile_pass(map, map_size, 0, viewport.x, viewport.y, 0, view) != 0 ||
            render_map_tile_pass(map, map_size, 0, viewport.x, viewport.y, 1, view) != 0 ||
            render_object_pass(&render_pool, 0, (short)-viewport.x, (short)-viewport.y,
                banks, 161, view) != 0 ||
            vga_present_frame(&frame) != 0) {
            lk_platform_log("Lion King: invalid original emitter scene rendering.\n");
            return 1;
        }
        camera_shake = 0;
        for (RENDER_NODE *node = render_pool.head; node; node = node->next) {
            node->flags &= 0xbf;
        }
        if (engine_dispatch_ticks(&clock, now, update_scene, &api) < 0 ||
            scene_failed) {
            lk_platform_log("Lion King: original emitter scene update failed.\n");
            return 1;
        }
        lk_platform_sleep(10);
    }
    lk_platform_log("Original emitter scene finished.\n");
    return 0;
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
    if (!argument_requested(api->Arguments, "--idle") &&
        !argument_requested(api->Arguments, "--manual") &&
        !argument_requested(api->Arguments, "--selftest")) {
        return run_emitter_scene(api);
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
    RENDER_OWNER owner = {140, 80};
    /* Diagnostic one-part descriptor, not a reconstructed game animation script. */
    unsigned char part[20] = {1, 0};
    RENDER_SPRITE_BANK banks[34] = {0};
    unsigned int bank_index = ASSETS_YOUNG_IDLE_INDEX, frames;
    if (load_preview_bank(api, bank_index, banks, part, &frames) != 0) {
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
    VGA_FRAME frame = {pixels, sizeof(pixels), 0, palette, present_frame, 0};
    PREVIEW_ANIMATION animation = {0};
    animation.node = node;
    animation.owner = &owner;
    if (!argument_requested(api->Arguments, "--manual") &&
        start_idle_preview(api, banks, &animation) != 0) {
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
                if (start_idle_preview(api, banks, &animation) != 0) {
                    return 1;
                }
            } else {
                animation.enabled = 0;
                if (load_preview_bank(api, bank_index, banks, part, &frames) != 0) {
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
            if (load_preview_bank(api, selected_bank, banks, part, &frames) != 0) {
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
                if (load_preview_bank(api, bank_index, banks, part, &frames) != 0) {
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
        lk_platform_sleep(10);
    }
    lk_platform_log("Lion King DOS64 platform test finished.\n");
    return 0;
}
