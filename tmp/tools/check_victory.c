#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "mock_layers.h"
#include "dos64/platform.h"
#include "dos64/frontend.h"
#include "engine/enemies.h"
#include "engine/assets.h"
#include "engine/animation_data.h"
#include "engine/ostrich_ride.h"
#include "engine/music.h"
#include "engine/pickups.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "libs/vga.h"

int __attribute__((ms_abi)) start(const DOS64_API *api);
extern unsigned char (*effect_samples)[65536];
extern unsigned int effect_sizes[];
int __real_engine_enemies_tick(ENGINE_ENEMIES *enemies, RENDER_OWNER camera);
int __real_engine_pickups_tick(ENGINE_PICKUPS *pickups, RENDER_OWNER camera);
int __real_render_follow_camera(RENDER_FOLLOW_CAMERA *camera, RENDER_OWNER target,
    unsigned char facing_left, unsigned char flags, unsigned short width,
    unsigned short height, int frozen);
int __real_engine_ostrich_ride_camera(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_ENEMIES *enemies, RENDER_FOLLOW_CAMERA *camera);
int __real_engine_ostrich_ride_release(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_PLAYER_AIR *player);
int __real_render_map_tile_pass_ostrich(const unsigned char *map, unsigned int size,
    unsigned int layer, unsigned int camera_x, unsigned int camera_y, int flagged,
    unsigned short base_x, unsigned char *pixels);
int __real_render_map_background_scrolled(const unsigned char *map, unsigned int size,
    unsigned int level, unsigned int camera_x, unsigned int camera_y,
    unsigned short scroll_offset, unsigned char *pixels);
int __real_resources_load_entry(const DOS64_API *api, const char *path, const char *name,
    unsigned char *source, unsigned int source_capacity, unsigned char *destination,
    unsigned int destination_capacity, RESOURCE_DICTIONARY *dictionary, unsigned int *loaded);
int run_bonus_toss_game(const DOS64_API *api, unsigned char *lives,
    unsigned int *continues, unsigned short *max_roar);
int start_level_two(const DOS64_API *api, unsigned char *lives, unsigned int *continues,
    unsigned short *max_roar);
int __real_start_level_two(const DOS64_API *api, unsigned char *lives,
    unsigned int *continues, unsigned short *max_roar);
int __real_frontend_loading_for_level(unsigned int completed, unsigned int total,
    unsigned int level);
int __real_frontend_level_palette(const DOS64_COLOR *palette);

static DOS64_API api;
static FILE *log_file;
static unsigned long long now, reward_begin;
static unsigned int polls, game_ticks, completions, scenes, speech_events, finished;
static unsigned int reward_frames, seen_frames, audio_opens, audio_stops;
static int reward_phase, audio_live, reward_audio, skip, muted, missing, audio_failure;
static int missing_notice, notice_phase;
static int notice_escape, notice_space;
static int bonus_selected;
static unsigned int notice_frames, notice_polls, notices, notice_returns;
static unsigned int bonus_starts;
static unsigned int bonus_starts, level2_starts;
static int bonus_escape, error_logged, skipped, terminal;
static int level2_test;
static int level2_ostrich_handoff;
static int level2_fall_test;
static int level2_log_test, log_landed, log_jump_requested, log_jump_seen;
static RENDER_OWNER log_marker;
static unsigned int fall_restart_tick, fall_restarts;
static int ride_test, ride_finished;
static int ride_hit_test, ride_hit_seen, ride_duck_seen, ride_jump_seen, ride_second_jump_seen;
static int ride_escape_test;
static int ride_hint_escape_test;
static int ride_avoid_test;
static int ride_jump_input_test, jump_input_stage;
static int ride_full_test;
static unsigned short ride_full_controls;
static int previous_jump_down;
static unsigned int ride_full_spawned, ride_full_passed, ride_full_passed_mask;
static int ride_obstacle_seen, ride_obstacle_passed;
static int ride_mount_seen, ride_rider_seen;
static unsigned int ride_ticks, ride_wraps, ride_hazards, ride_max_distance, ride_releases;
static unsigned int ride_render_passes[2], ride_scrolled_frames, ride_dismounted_frames;
static unsigned int hint_up_frames, hint_down_frames, hint_double_frames, hint_completed;
static unsigned int ride_marker;
static int level2_sound_failure;
static unsigned int level2_sounds, level1_sounds, sample_error_logged;
static unsigned int level2_completions;
static int menu_mode, in_menu;
static int menu_level2, level2_loading_frame;
static unsigned int loading2_count, loading2_previous, level2_palette_calls, level2_title_frames;
static unsigned int menu_visits, menu_returns;
static unsigned char packed[85438], map[580488], art[65536], speech[65536], notice_font[8192];
static unsigned char hint_sprite[65536], hint_pixels[64000], hint_expected[64000];
static unsigned int hint_sprite_size;
static unsigned char expected_background[64000], expected_pixels[64000];
static unsigned char expected_notice[64000];
static DOS64_COLOR palette[256];
static DOS64_COLOR level2_palette[256];
static unsigned char level2_title[32768], expected_level2_title[64000];
static RESOURCE_DICTIONARY dictionary;
static unsigned int art_size, speech_size;
static MUSIC_PLAYER reference;
static short expected_audio[2048];
static unsigned char level2_music[131072];
static int level2_audio;
static unsigned int level2_audio_frames;

int __wrap_render_map_tile_pass_ostrich(const unsigned char *data, unsigned int size,
    unsigned int layer, unsigned int camera_x, unsigned int camera_y, int flagged,
    unsigned short base_x, unsigned char *pixels)
{
    if (ride_full_test && ride_ticks && !ride_finished) {
        assert(base_x == (ride_marker == 52 ? 2208 : 3728));
        assert(flagged == 0 || flagged == 1);
        ++ride_render_passes[flagged];
    } else if (ride_full_test && ride_releases) {
        assert(base_x == 0);
    }
    return __real_render_map_tile_pass_ostrich(data, size, layer, camera_x, camera_y,
        flagged, base_x, pixels);
}

int __wrap_render_map_background_scrolled(const unsigned char *data, unsigned int size,
    unsigned int level, unsigned int camera_x, unsigned int camera_y,
    unsigned short scroll_offset, unsigned char *pixels)
{
    if (ride_full_test && ride_ticks) {
        assert(level == 2 && scroll_offset == (unsigned short)(ride_wraps * 512));
        if (scroll_offset) ++ride_scrolled_frames;
        if (ride_releases) ++ride_dismounted_frames;
    }
    return __real_render_map_background_scrolled(data, size, level, camera_x, camera_y,
        scroll_offset, pixels);
}

int __wrap_frontend_loading_for_level(unsigned int completed, unsigned int total,
    unsigned int level)
{
    if (menu_level2 && level == 2) {
        assert(total == 74 && completed <= total);
        assert(loading2_count ? completed > loading2_previous : completed == 0);
        if (completed) assert(level2_palette_calls == 1);
        loading2_previous = completed;
        ++loading2_count;
        level2_loading_frame = completed != 0;
    }
    int result = __real_frontend_loading_for_level(completed, total, level);
    level2_loading_frame = 0;
    return result;
}

int __wrap_frontend_level_palette(const DOS64_COLOR *colors)
{
    if (menu_level2 && level2_test) {
        assert(!memcmp(colors, level2_palette, sizeof(level2_palette)));
        ++level2_palette_calls;
    }
    return __real_frontend_level_palette(colors);
}

int __wrap_resources_load_entry(const DOS64_API *game_api, const char *path, const char *name,
    unsigned char *source, unsigned int source_capacity, unsigned char *destination,
    unsigned int destination_capacity, RESOURCE_DICTIONARY *resource_dictionary,
    unsigned int *loaded)
{
    static const char *const names2[] = {"MONKEY", "THROW1", "HITHEAD", "SPLASH"};
    static const char *const names1[] = {"LIZARD", "EXPLODE1", "WOLFROAR", "WOLFBREA"};
    for (unsigned int i = 0; i < 4; ++i) {
        if (!strcmp(name, names2[i])) {
            assert(level2_test && destination == effect_samples[20 + i]);
            level2_sounds |= 1U << i;
            if (level2_sound_failure && i == 1) return -1;
        }
        if (!strcmp(name, names1[i])) {
            assert(!level2_test && destination == effect_samples[15 + i]);
            level1_sounds |= 1U << i;
        }
    }
    return __real_resources_load_entry(game_api, path, name, source, source_capacity,
        destination, destination_capacity, resource_dictionary, loaded);
}

/* Inject only the controller input; the real boss/death path is tested by check_enemies. */
int __wrap_engine_enemies_tick(ENGINE_ENEMIES *enemies, RENDER_OWNER camera)
{
    int result = __real_engine_enemies_tick(enemies, camera);
    if (!result) {
        ++game_ticks;
        if (level2_test) {
            if (level2_log_test) {
                ENGINE_PLAYER_AIR *player = enemies->player;
                if (game_ticks == 1) {
                    ENGINE_LIZARD *log = 0;
                    for (unsigned int i = 0; i < enemies->count; ++i)
                        if (enemies->lizards[i].marker_type == 44) {
                            log = &enemies->lizards[i];
                            break;
                        }
                    assert(log);
                    log_marker = log->marker;
                    player->player.body.owner = (RENDER_OWNER){log_marker.x,
                        (short)(log_marker.y - 36)};
                    player->player.body.motion = (ENGINE_MOTION){0};
                    player->player.body.motion.velocity_y = 0x20000;
                    ENGINE_PLAYER_CALL call = {0xaa97, 0x6116, 0};
                    assert(engine_player_begin_air(enemies->objects,
                        enemies->objects->head, player, &call) == 0);
                } else if (player->player.flags_high & 0x80) {
                    log_landed = 1;
                    if (enemies->objects->head->behavior == &engine_player_ground_behavior)
                        log_jump_requested = 1;
                } else if (log_jump_requested &&
                    player->player.body.motion.velocity_y >= UINT32_C(0x80000000)) {
                    log_jump_seen = 1;
                    player->player.body.owner.x = 6360;
                }
                assert(game_ticks < 150 && player->health > 0);
            } else if (level2_fall_test) {
                ENGINE_PLAYER_AIR *player = enemies->player;
                if (game_ticks == 1) {
                    ENGINE_OBJECT *object = enemies->objects->head;
                    player->player.body.owner = (RENDER_OWNER){496, 440};
                    player->player.body.motion = (ENGINE_MOTION){0};
                    player->player.body.motion.velocity_y = 0x10000;
                    ENGINE_PLAYER_CALL call = {0xaa97, 0x6116, 0};
                    assert(engine_player_begin_air(enemies->objects, object, player, &call) == 0);
                } else if (fall_restarts && !fall_restart_tick) {
                    assert(player->player.body.owner.x == 67 && player->health > 0);
                    fall_restart_tick = game_ticks;
                    player->player.body.owner.x = 6359;
                } else if (fall_restart_tick && game_ticks == fall_restart_tick + 1) {
                    player->player.body.owner.x = 6360;
                }
                assert(game_ticks < 150);
            } else if (ride_test && game_ticks == 1) {
                ENGINE_PLAYER_AIR *player = enemies->player;
                ENGINE_OBJECT *object = enemies->objects->head;
                player->player.body.owner = (RENDER_OWNER){
                    (short)(ride_marker == 52 ? 2200 : 3720), 480};
                player->player.body.motion = (ENGINE_MOTION){0};
                player->player.handler = 0;
                ENGINE_PLAYER_CALL call = {0xcdc2, 0x6100, 0};
                assert(engine_player_begin_ground(enemies->objects, object, player, &call) == 0);
            } else if (ride_test && ride_finished) {
                if (game_ticks == 3) enemies->player->player.body.owner.x = 6359;
                if (game_ticks == 4) enemies->player->player.body.owner.x = 6360;
            } else if (ride_test) {
                assert(game_ticks < 20);
            } else if (game_ticks == 1) {
                assert(level2_sounds == 15 && (menu_level2 || !level1_sounds));
                for (unsigned int i = 15; i < 20; ++i) assert(!effect_sizes[i]);
                for (unsigned int i = 20; i < 24; ++i) assert(effect_sizes[i]);
                assert(enemies->player->player.body.owner.x == 67);
                if (level2_ostrich_handoff) {
                    ENGINE_PLAYER_AIR *player = enemies->player;
                    ENGINE_OBJECT *object = enemies->objects->head;
                    assert(player->ostrich_active && player->ostrich_motion &&
                        player->ostrich_sound && object && object->context == player);
                    *player->ostrich_active = 1;
                    player->flags |= 0x40;
                    player->player.body.owner.y = 250;
                    ENGINE_PLAYER_CALL call = {0xaa97, 0x6116, 0};
                    assert(engine_player_begin_air(enemies->objects, object, player, &call) == 0);
                    assert(object->behavior == &engine_player_ostrich_behavior &&
                        player->player.handler == 0xf94d);
                } else enemies->player->player.body.owner.x = 6359;
            } else if (level2_ostrich_handoff && game_ticks == 2) {
                assert(enemies->player->player.handler == 0xf94d);
                *enemies->player->ostrich_active = 0;
            } else if (level2_ostrich_handoff && game_ticks == 3) {
                assert(enemies->player->player.handler == 0xaa97);
                enemies->player->player.body.owner.x = 6359;
            } else if (game_ticks == (level2_ostrich_handoff ? 4U : 2U)) {
                assert(!level2_completions);
                enemies->player->player.body.owner.x = 6360;
            }
        } else if (game_ticks == 60) enemies->hyenas_defeated = 1;
    }
    return result;
}

int __wrap_render_follow_camera(RENDER_FOLLOW_CAMERA *camera, RENDER_OWNER target,
    unsigned char facing_left, unsigned char flags, unsigned short width,
    unsigned short height, int frozen)
{
    if (ride_test && game_ticks == 1 && !ride_ticks) {
        camera->position.x = (short)(target.x - 128);
        camera->position.y = 352;
    }
    if (level2_log_test && game_ticks == 1) {
        camera->position.x = (short)(log_marker.x - 160);
        camera->position.y = (short)(log_marker.y - 100);
    }
    return __real_render_follow_camera(camera, target, facing_left, flags, width, height, frozen);
}

int __wrap_engine_ostrich_ride_camera(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_ENEMIES *enemies, RENDER_FOLLOW_CAMERA *camera)
{
    unsigned int previous = ride->scroll.wrapped_distance;
    unsigned int route_offset = ride->sequence.route.offset;
    short player_x = enemies->player->player.body.owner.x;
    short bird_x = ride->visual->position.x;
    if (ride_avoid_test) {
        for (unsigned int i = 0; i < ride->sequence.count; ++i) {
            ENGINE_OSTRICH_HAZARD *hazard = &ride->sequence.hazards[ride->sequence.order[i]];
            if (hazard->constructor == 0x20977U) {
                ride_obstacle_seen = 1;
                if (hazard->position.x < player_x) ride_obstacle_passed = 1;
            }
        }
    }
    if (ride_full_test) {
        ride_full_controls = 0;
        for (unsigned int i = 0; i < ride->sequence.count; ++i) {
            ENGINE_OSTRICH_HAZARD *hazard = &ride->sequence.hazards[ride->sequence.order[i]];
            int dx = (int)hazard->position.x - player_x;
            if (hazard->constructor == 0x20977) {
                if (dx > -30 && ((!(enemies->player->flags & 0x80) && dx < 110 && dx > 0) ||
                    ((enemies->player->flags & 0x80) && dx < 40 &&
                    enemies->player->player.handler == 0xf94d &&
                    (!(ride->motion.velocity_y & UINT32_C(0x80000000)) ||
                    ride->motion.velocity_y > UINT32_C(0xfffa0000)))))
                    ride_full_controls |= 0x20;
            } else if (dx > -60 && dx < 150)
                ride_full_controls |= 2;
        }
        if (ride_full_controls & 0x20) ride_full_controls &= (unsigned short)~2U;
    }
    int result = __real_engine_ostrich_ride_camera(ride, enemies, camera);
    if (ride_test && !result) {
        ++ride_ticks;
        if (ride_jump_input_test) {
            ENGINE_PLAYER_AIR *player = enemies->player;
            if (!jump_input_stage && !ride->mounting && player->player.handler == 0xf94d)
                jump_input_stage = 1;
            else if (jump_input_stage == 1 && (player->flags & 0x80))
                jump_input_stage = 2;
            else if (jump_input_stage == 2)
                jump_input_stage = 3;
            else if (jump_input_stage == 3) {
                assert(ride->motion.velocity_y <= UINT32_C(0xfffa0000) &&
                    (ride->motion.velocity_y & UINT32_C(0x80000000)) &&
                    player->player.handler == 0xf94d);
                jump_input_stage = 4;
            } else if (jump_input_stage == 4) {
                assert(player->player.handler == 0xf94d);
                if (!(ride->motion.velocity_y & UINT32_C(0x80000000)) ||
                    ride->motion.velocity_y > UINT32_C(0xfffa0000))
                    jump_input_stage = 5;
            } else if (jump_input_stage == 5)
                jump_input_stage = 6;
            else if (jump_input_stage == 6 && player->player.handler == 0xfbc1)
                jump_input_stage = 7;
        }
        if (ride_full_test && ride_marker == 52) {
            static const unsigned int boundaries[] = {287, 348, 439, 500, 561,
                622, 703, 764, 855, 916};
            unsigned int phase = 0;
            while (phase < 10 && ride_ticks >= boundaries[phase]) ++phase;
            ENGINE_OSTRICH_HINT *hint = &ride->hints[0];
            if (phase < 10) {
                assert(hint->object && hint->node && hint->phase == phase);
                assert(hint->node->parts[19] == 106 && hint->position.x == 268);
                int shown = phase == 1 || phase == 3 || phase == 5 ||
                    phase == 7 || phase == 9;
                int down = phase == 3 || phase == 9;
                assert(!!(hint->node->flags & 0x80) == !shown);
                assert(!!(hint->node->pass_flags & 0x10) == down ||
                    (!shown && phase > 0));
                if (shown) {
                    if (down) ++hint_down_frames;
                    else ++hint_up_frames;
                    RENDER_POOL scene;
                    RENDER_SPRITE_BANK sprite_banks[127] = {{0}};
                    render_initialize_nodes(&scene);
                    RENDER_NODE *copy = render_acquire_node(&scene, &hint->position,
                        (unsigned int)hint->node->pass_flags << 16, 0,
                        hint->node->parts, hint->node->parts_size);
                    assert(copy);
                    sprite_banks[106] = (RENDER_SPRITE_BANK){hint_sprite, hint_sprite_size};
                    memset(hint_pixels, 0, sizeof(hint_pixels));
                    assert(render_object_pass(&scene, 0, -2208, -200,
                        sprite_banks, 127, hint_pixels) == 0);
                    unsigned int height = hint_sprite[4] | (unsigned int)hint_sprite[5] << 8;
                    int y = down ? hint->position.y - (int)height + 62 :
                        hint->position.y - 62;
                    memset(hint_expected, 0, sizeof(hint_expected));
                    assert(render_draw_sprite(hint_sprite, hint_sprite_size,
                        down ? 0x2000 : 0, 206, y, hint_expected) == 0);
                    assert(memcmp(hint_pixels, hint_expected, sizeof(hint_pixels)) == 0);
                    unsigned int visible = 0;
                    for (unsigned int i = 0; i < sizeof(hint_pixels); ++i)
                        visible += hint_pixels[i] != 0;
                    assert(visible);
                }
                if (phase == 7) {
                    assert(ride->hints[1].object && ride->hints[1].node &&
                        !(ride->hints[1].node->flags & 0x80) &&
                        ride->hints[1].position.x == 276);
                    ++hint_double_frames;
                } else assert(!ride->hints[1].object);
            } else {
                assert(!hint->object && !hint->node && !ride->hints[1].object);
                hint_completed = 1;
            }
        } else if (ride_test && ride_marker == 53) {
            assert(!ride->hints[0].object && !ride->hints[1].object);
        }
        if (ride->scroll.wrapped_distance != previous) {
            ++ride_wraps;
            assert(enemies->player->player.body.owner.x == player_x - 512);
            assert(ride->visual->position.x == bird_x - 512);
            assert(ride->visual->body->owner == &ride->visual->position &&
                ride->visual->head->owner == &ride->visual->position);
        }
        if (ride->scroll.distance > ride_max_distance) ride_max_distance = ride->scroll.distance;
        if (ride->mounting) ride_mount_seen = 1;
        if (enemies->player->player.handler == 0xf94d) ride_rider_seen = 1;
        for (unsigned int i = 0; i < enemies->count; ++i)
            assert(!enemies->lizards[i].object);
        if (ride->visual->pose == ENGINE_OSTRICH_CROUCHING) ride_duck_seen = 1;
        if (ride->visual->pose == ENGINE_OSTRICH_JUMPING) ride_jump_seen = 1;
        if (enemies->player->player.handler == 0xfbc1) ride_second_jump_seen = 1;
        if (enemies->player->player.handler == 0xfb2e) ride_hit_seen = 1;
        for (unsigned int i = 0; i < ride->sequence.count; ++i) {
            ENGINE_OSTRICH_HAZARD *hazard = &ride->sequence.hazards[ride->sequence.order[i]];
            if (!ride_hit_test && !ride_avoid_test && !ride_full_test) {
                if (hazard->position.y != 0) ++ride_hazards;
                hazard->position.y = 0;
            }
        }
        if (ride_full_test) {
            assert(enemies->player->health > 0 && enemies->player->player.handler != 0xfb2e &&
                !(enemies->player->player.flags_high & 4) && !ride->bird_hit);
            if (ride->sequence.route.offset != route_offset) {
                unsigned int flags = ride->sequence.route.records[route_offset + 2];
                for (unsigned int bit = 0; bit < 4; ++bit)
                    if (flags & (1U << bit)) ++ride_full_spawned;
            }
            unsigned int active = 0;
            for (unsigned int i = 0; i < ride->sequence.count; ++i) {
                unsigned int slot = ride->sequence.order[i], mask = 1U << slot;
                ENGINE_OSTRICH_HAZARD *hazard = &ride->sequence.hazards[slot];
                active |= mask;
                if (!(ride_full_passed_mask & mask) &&
                    hazard->position.x < enemies->player->player.body.owner.x) {
                    ride_full_passed_mask |= mask;
                    ++ride_full_passed;
                }
            }
            ride_full_passed_mask &= active;
        }
        if (ride_hit_test && enemies->player->health <= 0) ride_finished = 1;
        if (!ride->active) ride_finished = 1;
    }
    return result;
}

int __wrap_engine_ostrich_ride_release(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_PLAYER_AIR *player)
{
    RENDER_NODE *body = ride->visual ? ride->visual->body : 0;
    RENDER_NODE *head = ride->visual ? ride->visual->head : 0;
    RENDER_NODE *hint = ride->hints[0].node;
    RENDER_NODE *second_hint = ride->hints[1].node;
    int result = __real_engine_ostrich_ride_release(ride, player);
    if (ride_test && !result) {
        ++ride_releases;
        assert(body && !body->active && head && !head->active &&
            !ride->active && !ride->marker && !ride->sequence.objects &&
            !player->ostrich_active && !player->ostrich_motion);
        assert((!hint || !hint->active) && (!second_hint || !second_hint->active));
    }
    return result;
}

int __wrap_engine_pickups_tick(ENGINE_PICKUPS *pickups, RENDER_OWNER camera)
{
    if (level2_fall_test && fall_restart_tick) assert(*pickups->lives == 2);
    if (level2_test && game_ticks == 1) {
        unsigned int aliases = 0;
        for (unsigned int i = 0; i < pickups->count; ++i) {
            ENGINE_PICKUP *item = &pickups->items[i];
            unsigned int marker_type;
            RENDER_OWNER marker;
            assert(engine_map_marker(pickups->map, (unsigned short)item->marker.x / 16,
                (unsigned short)item->marker.y / 16, &marker_type, &marker) == 0);
            if (marker_type == 162) {
                assert(item->type == 1);
                ++aliases;
            }
        }
        assert(aliases == 1);
    }
    if (bonus_selected && !pickups->bonus_selected) {
        ENGINE_PICKUP *item = 0;
        for (unsigned int i = 0; i < pickups->count; ++i)
            if (pickups->items[i].type == 41) item = &pickups->items[i];
        assert(item);
        RENDER_OWNER saved = pickups->player->player.body.owner;
        RENDER_OWNER item_camera = {(short)(item->marker.x - 160),
            (short)(item->marker.y - 120)};
        assert(__real_engine_pickups_tick(pickups, item_camera) == 0 && item->object);
        pickups->player->player.body.owner = item->body.owner;
        RENDER_BOUNDS a, b;
        assert(render_object_bounds(item->body.node, &a) == 0);
        assert(render_object_bounds(pickups->player->player.body.node, &b) == 0);
        pickups->player->player.body.owner.x +=
            (short)((a.left + a.right - b.left - b.right) / 2);
        pickups->player->player.body.owner.y +=
            (short)((a.top + a.bottom - b.top - b.bottom) / 2);
        short hit;
        assert(render_objects_hit(item->body.node,
            pickups->player->player.body.node, &hit) == 0 && hit);
        assert(__real_engine_pickups_tick(pickups, item_camera) == 0);
        assert(item->collected && pickups->bonus_selected == 65535);
        pickups->player->player.body.owner = saved;
    }
    int result = __real_engine_pickups_tick(pickups, camera);
    return result;
}

int __wrap_run_bonus_toss_game(const DOS64_API *game_api, unsigned char *lives,
    unsigned int *continues, unsigned short *max_roar)
{
    assert(bonus_selected && game_api == &api && lives && continues && max_roar);
    assert(finished == 1 && !audio_live && !notice_phase);
    assert(*lives == 3 && *continues == 1);
    assert(*max_roar == 16);
    *max_roar += 8;
    ++bonus_starts;
    return bonus_escape ? 2 : 0;
}

int __wrap_start_level_two(const DOS64_API *game_api, unsigned char *lives,
    unsigned int *continues, unsigned short *max_roar)
{
    assert(game_api == &api && lives && continues && max_roar);
    assert(finished == 1 && !audio_live && !notice_phase);
    assert(bonus_starts == (bonus_selected ? 1U : 0U));
    assert(*lives == 3 && *continues == 1);
    assert(*max_roar == (bonus_selected ? 24 : 16));
    ++level2_starts;
    if (menu_level2) {
        level2_test = 1;
        game_ticks = 0;
        return __real_start_level_two(game_api, lives, continues, max_roar);
    }
    return 0;
}

static unsigned int reward_ticks(void)
{
    return (unsigned int)((now - reward_begin) * 1193182ULL /
        (23660ULL * 1000000000ULL));
}

static void record(const char *text)
{
    if (strstr(text, "cannot load gameplay sound samples.")) sample_error_logged = 1;
    if (strstr(text, "LEVEL2: original completion threshold reached")) {
        assert(level2_test && (level2_log_test ? log_jump_seen : level2_fall_test ?
            fall_restart_tick && game_ticks == fall_restart_tick + 1 :
            game_ticks == (level2_ostrich_handoff || ride_test ? 4U : 2U)));
        ++level2_completions;
    }
    if (level2_fall_test && strstr(text, "restored health and restarted at the saved checkpoint"))
        ++fall_restarts;
    if (strstr(text, "Main menu: ready.")) {
        in_menu = 1;
        ++menu_visits;
    }
    if (strstr(text, "Main menu: start LEVEL1.")) in_menu = 0;
    if (strstr(text, "Main menu: returning from LEVEL1.")) {
        assert(finished == 1 && !audio_live);
        ++menu_returns;
    }
    if (strstr(text, "LEVEL1: hyena defeated; original level-completion condition reached.")) {
        assert(!terminal && game_ticks == 60);
        terminal = 1;
        ++completions;
    }
    if (strstr(text, "Victory: original LEVEL1")) {
        assert(!reward_phase && !scenes && (muted || terminal));
        reward_phase = 1;
        reward_begin = now;
        ++scenes;
    }
    if (strstr(text, "Victory: SPEECH1")) {
        assert(reward_phase && reward_ticks() == 19 && !speech_events);
        ++speech_events;
        if (!muted) {
            assert(music_effect_play(&reference, 0, speech, speech_size) == 0);
            assert(music_effect_play(&reference, 1, speech, speech_size) == 0);
        }
    }
    if (strstr(text, "Victory: Rafiki scene skipped")) {
        assert(skip && reward_ticks() >= 30 && reward_ticks() < 475);
        skipped = 1;
    }
    if (strstr(text, "Victory: reward scene finished")) {
        assert(reward_phase && (skip ? skipped : reward_ticks() == 475));
        ++finished;
        reward_phase = 0;
    }
    if (!bonus_selected && strstr(text, "Transition: LEVEL2 is not available")) {
        assert(finished == 1 && !audio_live && !notice_phase);
        notice_phase = 1;
        ++notices;
    }
    if (!bonus_selected &&
        strstr(text, "Transition: returning without starting LEVEL2")) {
        assert(notice_phase && notice_frames == 1 && notice_polls >= 2);
        notice_phase = 0;
        ++notice_returns;
    }
    if (strstr(text, "cannot load original LEVEL1 Rafiki") ||
        strstr(text, "reward speech requires usable") ||
        strstr(text, "cannot load next-level notice font")) error_logged = 1;
}

static void __attribute__((ms_abi)) console(const char *text)
{
    fputs(text, stderr);
    assert(!"unexpected console output");
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    if (!strcmp(path, "LIONKING.LOG")) {
        assert(!log_file);
        return log_file = tmpfile();
    }
    assert(!strcmp(path, "LIONKING.EPF"));
    if ((terminal && missing) || (finished && missing_notice)) return 0;
    return fopen("data/LIONKING.EPF", mode);
}
static int __attribute__((ms_abi)) close_file(void *file)
{
    if (file == log_file) log_file = 0;
    return fclose(file);
}
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int origin)
{ return fseek(file, (long)offset, origin); }
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{ return fread(buffer, (size_t)size, (size_t)count, file); }
static unsigned long long __attribute__((ms_abi)) write_file(const void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    assert(file == log_file && size == 1);
    record(buffer);
    return fwrite(buffer, (size_t)size, (size_t)count, file);
}
static void __attribute__((ms_abi)) sleep_ms(unsigned int ms) { (void)ms; assert(0); }
static unsigned long long __attribute__((ms_abi)) time_ns(void) { return now; }
static int __attribute__((ms_abi)) select_layer(int layer) { assert(layer == 0); return 0; }
static void __attribute__((ms_abi)) set_color(DOS64_COLOR color) { (void)color; }
static void __attribute__((ms_abi)) clear(void) {}
static void __attribute__((ms_abi)) present(void) {}
static void __attribute__((ms_abi)) poll(void)
{
    now += 10000000ULL;
    assert(++polls < (ride_test ? 20000U : 4000U));
    memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
    memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
    if (ride_test && !ride_finished)
        api.Input.KeyDown[0x4f] = 1;
    if (level2_log_test && log_jump_requested && !log_jump_seen)
        api.Input.KeyDown[0x2c] = 1;
    if (ride_test && !ride_hit_test && !ride_avoid_test && ride_ticks >= 100 && ride_ticks < 130)
        api.Input.KeyDown[0x51] = 1;
    if (ride_test && !ride_hit_test && !ride_avoid_test &&
        ((ride_ticks >= 150 && ride_ticks < 154) ||
        (ride_ticks >= 162 && ride_ticks < 166)))
        api.Input.KeyDown[0x2c] = 1;
    if (ride_full_test) {
        api.Input.KeyDown[0x51] = !!(ride_full_controls & 2);
        api.Input.KeyDown[0x2c] = !!(ride_full_controls & 0x20);
    }
    if (ride_avoid_test && ride_max_distance >= 1620 && ride_max_distance < 1640)
        api.Input.KeyDown[0x2c] = 1;
    if (ride_jump_input_test) {
        api.Input.KeyDown[0x2c] = jump_input_stage == 1 ||
            jump_input_stage == 3 || jump_input_stage == 4 || jump_input_stage == 6;
        if (jump_input_stage == 7)
            api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
    }
    if (api.Input.KeyDown[0x2c] && !previous_jump_down)
        api.Input.KeyPressed[0x2c] = 1;
    previous_jump_down = api.Input.KeyDown[0x2c];
    if (ride_escape_test && ride_ticks >= (ride_hint_escape_test ? 710U : 100U))
        api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
    if (ride_avoid_test && ride_max_distance >= 1900)
        api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
    if (reward_phase && skip && reward_ticks() >= 30)
        api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
    if (notice_phase) {
        ++notice_polls;
        if (skip && notice_polls == 1)
            api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
        if (notice_polls == (skip ? 3U : 2U)) {
            unsigned int key = notice_escape ? 0x29 : notice_space ? 0x2c : 0x28;
            api.Input.KeyDown[key] = api.Input.KeyPressed[key] = 1;
        }
    }
    if (menu_mode && in_menu) {
        unsigned int key = menu_visits == 1 ? 0x28 : 0x29;
        api.Input.KeyDown[key] = api.Input.KeyPressed[key] = 1;
    }
}

static unsigned int frame_at(unsigned int ticks)
{
    static const unsigned char durations[] = {
        4,2,2,4,6,4,4,4,8,6,8,8,8,20,8,10,28,21,8,8,101,101,101
    };
    static const unsigned char frames[] = {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,16,15,14,13,13,13
    };
    if (!ticks) return 0;
    --ticks;
    for (unsigned int i = 0; i < sizeof(durations); ++i) {
        if (ticks < durations[i]) return frames[i];
        ticks -= durations[i];
    }
    assert(ticks == 0);
    return 13;
}

static void __attribute__((ms_abi)) draw(const DOS64_COLOR *image, unsigned int width,
    unsigned int height, unsigned int stride, int x, int y, unsigned int dw, unsigned int dh)
{
    if (height == 5 && stride == 60) {
        assert(width <= 60 && x == (int)(640 - (width + 4) * 2) &&
            y == 422 && dw == width * 2 && dh == 10);
        return;
    }
    if (width == 1 && height == 1) {
        assert(image[0] == 0xff000000U && x == 0 && y == 0 && dw == 640 && dh == 480);
        return;
    }
    assert(width == 320 && height == 200 && stride == 320 &&
        x == 0 && y == 40 && dw == 640 && dh == 400);
    if (level2_loading_frame) {
        for (unsigned int i = 0; i < 64000; ++i)
            assert(image[i] == (level2_palette[0] | 0xff000000U));
        return;
    }
    if (menu_level2 && level2_test && game_ticks && game_ticks <= 2 && !reward_phase) {
        for (unsigned int i = 0; i < 64000; ++i)
            if (expected_level2_title[i])
                assert(image[i] == (level2_palette[expected_level2_title[i]] | 0xff000000U));
        ++level2_title_frames;
    }
    if (notice_phase) {
        for (unsigned int i = 0; i < 64000; ++i)
            assert(image[i] == (palette[expected_notice[i]] | 0xff000000U));
        ++notice_frames;
        return;
    }
    if (!reward_phase) return;
    unsigned int ticks = reward_ticks(), frame = frame_at(ticks);
    unsigned int backdrop = ticks ? 17 + ((ticks - 1) / 8) % 5 : 17;
    memcpy(expected_pixels, expected_background, sizeof(expected_pixels));
    assert(render_draw_sprite(art, art_size, (unsigned short)backdrop,
        142 - 64, 163 - 120, expected_pixels) == 0);
    assert(render_draw_sprite(art, art_size, (unsigned short)frame,
        142 - 64, 162 - 120, expected_pixels) == 0);
    for (unsigned int i = 0; i < 64000; ++i) {
        if (image[i] != (palette[expected_pixels[i]] | 0xff000000U))
            fprintf(stderr, "reward tick %u frame %u backdrop %u pixel %u: %x != %x\n",
                ticks, frame, backdrop, i, image[i], palette[expected_pixels[i]] | 0xff000000U);
        assert(image[i] == (palette[expected_pixels[i]] | 0xff000000U));
    }
    seen_frames |= (1U << frame) | (1U << backdrop);
    ++reward_frames;
}

static int __attribute__((ms_abi)) audio_open(unsigned int rate)
{
    assert(rate == MUSIC_RATE && !audio_live && !muted);
    reward_audio = terminal && !finished;
    level2_audio = level2_test && !game_ticks;
    if (reward_audio && audio_failure) return -1;
    assert(!reward_audio || audio_stops == (menu_mode ? 3U : 1U));
    audio_live = 1;
    if (reward_audio) assert(music_effects_initialize(&reference) == 0);
    if (level2_audio) {
        unsigned int size;
        if (ride_full_test && ride_marker == 52) {
            unsigned int slot;
            assert(assets_load_named_bank(&api, "LIONKING.EPF", animation_level2_bank_list,
                sizeof(animation_level2_bank_list), 0, packed, sizeof(packed), hint_sprite,
                sizeof(hint_sprite), &dictionary, &slot, &hint_sprite_size) == 0 && slot == 106);
        }
        assert(__real_resources_load_entry(&api, "LIONKING.EPF", "LION2.AMF",
            packed, sizeof(packed), level2_music, sizeof(level2_music), &dictionary, &size) == 0);
        assert(music_initialize(&reference, level2_music, size) == 0);
        reference.interpolate_samples = 1;
        reference.smooth_transitions = 1;
        reference.sample_reference_period = 856;
        reference.scaled_pitch_slides = 1;
    }
    ++audio_opens;
    return 0;
}
static unsigned long long __attribute__((ms_abi)) queued(void) { return 0; }
static unsigned long long __attribute__((ms_abi)) free_frames(void) { return 1024; }
static unsigned long long __attribute__((ms_abi)) audio_write(const short *samples,
    unsigned long long count)
{
    assert(audio_live && count <= 1024);
    if (reward_audio) {
        assert(music_samples(&reference, expected_audio, (unsigned int)count) == 0);
        assert(memcmp(samples, expected_audio, (size_t)count * 4) == 0);
    }
    if (level2_audio && !game_ticks) {
        assert(music_samples(&reference, expected_audio, (unsigned int)count) == 0);
        assert(memcmp(samples, expected_audio, (size_t)count * 4) == 0);
        level2_audio_frames += (unsigned int)count;
    }
    return count;
}
static void __attribute__((ms_abi)) audio_stop(void)
{ assert(audio_live); audio_live = 0; ++audio_stops; }

int main(int argc, char **argv)
{
    assert(argc == 1 || argc == 2);
    if (argc == 2) {
        skip = !strcmp(argv[1], "--skip");
        muted = !strcmp(argv[1], "--muted");
        missing = !strcmp(argv[1], "--missing");
        audio_failure = !strcmp(argv[1], "--audio-failure");
        missing_notice = !strcmp(argv[1], "--missing-notice");
        notice_escape = !strcmp(argv[1], "--notice-escape");
        notice_space = !strcmp(argv[1], "--notice-space");
        menu_mode = !strcmp(argv[1], "--menu");
        menu_level2 = !strcmp(argv[1], "--menu-level2");
        menu_mode |= menu_level2;
        bonus_escape = !strcmp(argv[1], "--bonus-escape");
        level2_test = !strcmp(argv[1], "--level2");
        level2_ostrich_handoff = !strcmp(argv[1], "--level2-ostrich-handoff");
        level2_fall_test = !strcmp(argv[1], "--level2-fall");
        level2_log_test = !strcmp(argv[1], "--level2-log");
        ride_test = !strcmp(argv[1], "--level2-ride-first") ||
            !strcmp(argv[1], "--level2-ride-second") ||
            !strcmp(argv[1], "--level2-ride-hit") ||
            !strcmp(argv[1], "--level2-ride-escape") ||
            !strcmp(argv[1], "--level2-ride-hint-escape") ||
            !strcmp(argv[1], "--level2-ride-avoid") ||
            !strcmp(argv[1], "--level2-ride-jump-input") ||
            !strcmp(argv[1], "--level2-ride-full-first") ||
            !strcmp(argv[1], "--level2-ride-full-second");
        ride_hit_test = !strcmp(argv[1], "--level2-ride-hit");
        ride_hint_escape_test = !strcmp(argv[1], "--level2-ride-hint-escape");
        ride_escape_test = !strcmp(argv[1], "--level2-ride-escape") || ride_hint_escape_test;
        ride_avoid_test = !strcmp(argv[1], "--level2-ride-avoid");
        ride_jump_input_test = !strcmp(argv[1], "--level2-ride-jump-input");
        ride_full_test = ride_hint_escape_test || !strcmp(argv[1], "--level2-ride-full-first") ||
            !strcmp(argv[1], "--level2-ride-full-second");
        ride_marker = !strcmp(argv[1], "--level2-ride-second") ||
            !strcmp(argv[1], "--level2-ride-full-second") ? 53U : 52U;
        level2_test |= level2_ostrich_handoff;
        level2_test |= level2_fall_test;
        level2_test |= level2_log_test;
        level2_test |= ride_test;
        level2_sound_failure = !strcmp(argv[1], "--level2-sound-failure");
        level2_test |= level2_sound_failure;
        bonus_selected = !strcmp(argv[1], "--bonus") || bonus_escape;
        assert(skip || muted || missing || audio_failure || missing_notice ||
            notice_escape || notice_space || menu_mode || bonus_selected || level2_test);
    }
    api.Size = sizeof(api); api.Version = DOS64_API_VERSION; api.Arguments = "--map";
    if (menu_mode) api.Arguments = "";
    if (level2_test) api.Arguments = "--level2";
    api.Write = console; api.Sleep = sleep_ms; api.Time.Nanoseconds = time_ns;
    api.Input.Poll = poll; api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SetColor = set_color; api.Gfx.Clear = clear;
    api.Gfx.SelectLayer = select_layer; api.Gfx.Present = present; api.DrawImage = draw;
    mock_install_layers(&api);
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file; api.Fs.Write = write_file;
    api.Audio.Present = 1; api.Audio.Open = audio_open; api.Audio.Write = audio_write;
    api.Audio.FreeFrames = free_frames; api.Audio.QueuedFrames = queued; api.Audio.Stop = audio_stop;
    unsigned int size;
    assert(resources_load_entry(&api, "LIONKING.EPF", "TITLES.MAP", packed,
        sizeof(packed), map, sizeof(map), &dictionary, &size) == 0);
    assert(vga_load_palette(map, size, palette) == 0);
    for (int layer = 1; layer >= 0; --layer) {
        assert(render_map_tile_pass(map, size, (unsigned int)layer, 0, 0, 0, expected_background) == 0);
        assert(render_map_tile_pass(map, size, (unsigned int)layer, 0, 0, 1, expected_background) == 0);
    }
    unsigned int font_size;
    assert(resources_load_entry(&api, "LIONKING.EPF", "F8X8_S.MCH", packed,
        sizeof(packed), notice_font, sizeof(notice_font), &dictionary, &font_size) == 0);
    memcpy(expected_notice, expected_background, sizeof(expected_notice));
    const char *lines[] = {"LEVEL 2 NOT AVAILABLE", "ENTER SPACE OR ESC"};
    for (unsigned int row = 0; row < 2; ++row)
        for (unsigned int column = 0; lines[row][column]; ++column)
            assert(render_draw_sprite(notice_font, font_size,
                (unsigned short)(lines[row][column] - 32),
                (int)((row ? 88U : 76U) + column * 8U),
                (int)(row ? 110 : 90), expected_notice) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "RWDLVL1.MCH", packed,
        sizeof(packed), art, sizeof(art), &dictionary, &art_size) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "SPEECH1", packed,
        sizeof(packed), speech, sizeof(speech), &dictionary, &speech_size) == 0);
    if (menu_level2) {
        unsigned int title_size;
        assert(resources_load_entry(&api, "LIONKING.EPF", "LEVEL2.MAP", packed,
            sizeof(packed), map, sizeof(map), &dictionary, &size) == 0);
        assert(vga_load_palette(map, size, level2_palette) == 0);
        assert(resources_load_entry(&api, "LIONKING.EPF", "LEVELS.MCH", packed,
            sizeof(packed), level2_title, sizeof(level2_title), &dictionary, &title_size) == 0);
        unsigned int width = level2_title[2] | (unsigned int)level2_title[3] << 8;
        unsigned int height = level2_title[4] | (unsigned int)level2_title[5] << 8;
        assert(render_draw_sprite(level2_title, title_size, 1, (320 - width) / 2,
            (200 - height) / 2, expected_level2_title) == 0);
    }
    int result;
    if (muted) {
        assert(lk_platform_init(&api) == 0);
        result = frontend_victory(&api, &api, 0) != 0;
        if (frontend_release() != 0) result = 1;
        result = lk_platform_finish(result);
    } else result = start(&api);
    if (level2_sound_failure) {
        assert(result == 1 && sample_error_logged && level2_sounds == 3 &&
            !level1_sounds && !game_ticks && !log_file && !audio_live);
        puts("PASS: missing LEVEL2 sound reports failure and closes resources");
        return 0;
    }
    if (menu_level2) {
        assert(result == 0 && !log_file && !audio_live && game_ticks == 2 &&
            level2_completions == 1 && level2_starts == 1 && finished == 1 &&
            menu_visits == 2 && menu_returns == 1 &&
            loading2_count == 74 && loading2_previous == 74 && level2_palette_calls == 1 &&
            level2_title_frames && level2_audio_frames > 0 && audio_opens == 6 && audio_stops == 6);
        puts("PASS: real menu transition displays blank LEVEL2 loading and title over the map");
        return 0;
    }
    if (level2_test) {
        if (level2_log_test) {
            assert(result == 0 && !log_file && !audio_live && log_landed &&
                log_jump_seen && level2_completions == 1);
            puts("PASS: real LEVEL2 gameplay lands and jumps on a floating log");
            return 0;
        }
        if (level2_fall_test) {
            assert(result == 0 && !log_file && !audio_live && fall_restarts == 1 &&
                fall_restart_tick > 1 && level2_completions == 1);
            puts("PASS: real LEVEL2 gameplay fall below the giraffes loses a life and restarts");
            return 0;
        }
        if (ride_jump_input_test) {
            assert(result == 0 && !log_file && !audio_live && jump_input_stage == 7 &&
                ride_rider_seen && ride_jump_seen && ride_second_jump_seen &&
                ride_releases == 1 && !level2_completions);
            puts("PASS: held, early and correctly timed jump presses through real LEVEL2 gameplay");
            return 0;
        }
        if (ride_escape_test || ride_avoid_test) {
            assert(result == 0 && !log_file && !audio_live && ride_ticks >= 100 &&
                ride_rider_seen && ride_releases == 1 && !level2_completions);
            if (ride_hint_escape_test) assert(hint_double_frames > 0);
            if (ride_avoid_test) {
                assert(ride_max_distance >= 1900 && ride_jump_seen && !ride_hit_seen &&
                    ride_obstacle_seen && ride_obstacle_passed);
                puts("PASS: first real LEVEL2 ostrich obstacle avoided by jumping");
            } else puts("PASS: escape during LEVEL2 ostrich ride releases controller and visuals");
            return 0;
        }
        assert(result == 0 && !log_file && !audio_live &&
            game_ticks == (level2_ostrich_handoff || ride_test ? 4U : 2U) &&
            level2_completions == 1 && !scenes && !finished &&
            level2_audio_frames > 0 && audio_opens == 1 && audio_stops == 1);
        if (ride_test) {
            if (ride_hit_test) {
                assert(ride_finished && ride_hit_seen && ride_releases == 1);
                puts("PASS: real LEVEL2 obstacle hit, death, cleanup and restart");
            } else if (ride_full_test) {
                unsigned int expected = ride_marker == 52 ? 9U : 18U;
                assert(ride_finished && ride_ticks > 500 && ride_wraps >= 9 &&
                    ride_max_distance >= (ride_marker == 52 ? 4868U : 7428U) &&
                    ride_full_spawned == expected && ride_full_passed == expected &&
                    ride_releases == 1 && ride_mount_seen && ride_rider_seen &&
                    ride_duck_seen && ride_jump_seen && ride_second_jump_seen &&
                    ride_render_passes[0] && ride_render_passes[1] &&
                    ride_scrolled_frames && ride_dismounted_frames);
                if (ride_marker == 52)
                    assert(hint_up_frames == 183 && hint_down_frames == 122 &&
                       hint_double_frames == 61 && hint_completed);
                puts("PASS: full LEVEL2 ostrich ride with all real obstacles and no hits");
            } else {
                assert(ride_finished && ride_ticks > 500 && ride_wraps >= 9 &&
                    ride_max_distance >= (ride_marker == 52 ? 4868U : 7428U) &&
                    ride_hazards == (ride_marker == 52 ? 9U : 18U) &&
                    ride_releases == 1 && ride_mount_seen && ride_rider_seen && ride_duck_seen &&
                    ride_jump_seen && ride_second_jump_seen);
                puts("PASS: real LEVEL2 ride, controls, scrolling, hazards and dismount (hazards moved aside)");
            }
            return 0;
        }
        puts(level2_ostrich_handoff ?
            "PASS: LEVEL2 air-to-rider handoff and rider-to-air transition in gameplay loop" :
            "PASS: LEVEL2 starts at the original X and ends at 6360, not 6359");
        return 0;
    }
    assert(!log_file && !audio_live && (muted || completions == 1));
    if (missing || audio_failure) {
        assert(result == 1 && error_logged && !scenes && !finished &&
            audio_opens == 1 && audio_stops == 1);
        puts("PASS: reward resource/audio failure is explicit; gameplay audio and log close cleanly");
    } else if (missing_notice) {
        assert(result == 1 && error_logged && scenes == 1 && finished == 1 &&
            !notices && !notice_returns && audio_opens == 2 && audio_stops == 2);
        puts("PASS: missing next-level notice font reports failure after closing reward audio");
    } else {
        assert(result == 0 && scenes == 1 && finished == 1 && speech_events == 1);
        if (!muted) assert(level1_sounds == 15 && !level2_sounds);
        assert(audio_opens == (muted ? 0U : menu_mode ? 5U : 2U) && audio_stops == audio_opens);
        assert(reward_frames > (skip ? 30U : 900U));
        if (!skip) assert(seen_frames == 0x3fffff);
        puts("PASS: Rafiki reward has exact original background/frame pixels, speech at tick 19, "
            "no audio overlap and clean exit");
        if (!skip) puts("PASS: all 22 RWDLVL1 frames and original terminal tick 475");
        if (!muted) puts("PASS: original LEVEL1 controller enters reward exactly once; exact two-channel SPEECH1 PCM");
        if (skip) puts("PASS: Escape skips reward and closes its audio stream");
        if (muted) puts("PASS: muted reward preserves animation timing without opening audio");
        if (!muted) {
            assert(!notices && !notice_returns && !notice_frames);
            if (bonus_escape) {
                assert(bonus_starts == 1 && !level2_starts);
                puts("PASS: Escape in BUG TOSS returns to the menu instead of entering LEVEL2");
            } else {
                assert(level2_starts == 1);
            }
            if (bonus_selected && !bonus_escape)
                puts("PASS: collected BUG TOSS marker starts the bonus before LEVEL2");
            else if (!bonus_escape)
                puts("PASS: LEVEL1 completion starts LEVEL2 with lives and continues preserved");
        }
        if (menu_mode) {
            assert(menu_visits == 2 && menu_returns == 1);
            puts("PASS: menu Start -> Timon -> LEVEL1 completion -> Rafiki -> menu -> exit; five nonoverlapping audio streams");
        }
    }
    return 0;
}
