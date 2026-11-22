#include "start_runtime.h"
#include "preview_emitter.h"
#include "preview_idle.h"

static void update_scene(void *context)
{
    const DOS64_API *const *runtime = context;
    const DOS64_API *api = *runtime;
    if (!scene_failed && engine_update_objects(&scene_objects, &api->Input) != 0) {
        scene_failed = 1;
    }
}

int run_emitter_scene(const DOS64_API *api)
{
    unsigned int map_size, loaded, slot;
    if (resources_load_entry(&resource_api, "LIONKING.EPF", "LEVEL6.MAP", packed, sizeof(game_buffers->packed),
        map, sizeof(game_buffers->map), &dictionary, &map_size) != 0 ||
        vga_load_palette(map, map_size, palette) != 0 ||
        assets_load_named_bank(&resource_api, "LIONKING.EPF", animation_level6_bank_list,
            sizeof(animation_level6_bank_list), 0, packed, sizeof(game_buffers->packed),
            sprite, sizeof(game_buffers->sprite), &dictionary, &slot, &loaded) != 0) {
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
    VGA_FRAME frame = {pixels, sizeof(game_buffers->pixels), 0, palette, present_frame, 0};
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
    }
    lk_platform_log("Original emitter scene finished.\n");
    return 0;
}

