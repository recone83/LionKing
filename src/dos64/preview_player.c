#include "start_runtime.h"
#include "preview_player.h"
#include "preview_idle.h"
#include "frontend.h"
#include "preview_bonus.h"

typedef struct {
    const DOS64_API *api;
    ENGINE_PLAYER_AIR air;
    ENGINE_OBJECT *object;
    unsigned int variant;
    unsigned char collision_flags;
    int completed;
    int failed;
    int flight;
    int airborne;
    int jump;
    int manual;
    int jump_requested;
    int ground_mode;
    unsigned short input_taps;
    RENDER_OWNER damage_source;
    unsigned char fixture_terrain;
    unsigned int terrain_variant;
    unsigned int terrain_ticks;
    int demo_hit;
    int contact_demo;
    unsigned int contact_demo_phase;
    unsigned int tether_ticks;
    int fixture_touching;
    int ledge_demo;
    unsigned int ledge_demo_phase;
    unsigned int ledge_variant;
    short fixture_floor;
    int wall_demo;
    unsigned int wall_demo_phase;
    unsigned int wall_variant;
    unsigned int wall_case;
    int fixture_wall_contact;
    int map_mode;
    RENDER_FOLLOW_CAMERA camera;
    ENGINE_MAP_COLLISION collision;
    ENGINE_LEVEL_LIFE life;
    short map_spawn_y;
    short map_spawn_x;
    unsigned int level_number;
    unsigned short game_over_ticks;
    unsigned short continue_ticks;
    unsigned short continue_accept_ticks;
    unsigned int continues_remaining, continues_shown;
    int continue_pressed;
    int continue_no;
    int continue_exhausted;
    unsigned int level_music_size;
    unsigned short level_title_ticks;
    unsigned int map_contacts;
    unsigned int map_height_changes;
    unsigned int map_landings;
    unsigned int map_edge_contacts;
    unsigned int map_left_blocks;
    unsigned int map_right_blocks;
    unsigned int map_ceiling_hits;
    unsigned long long jump_begin;
} DEFLECTION_PREVIEW;

static unsigned char next_level_lives;
static unsigned int next_level_continues;
static unsigned short next_level_max_roar;
static int next_level_state_valid;

static int preview_alternate_roar(void)
{
    return engine_controls_alternate_roar(&game_controls);
}

static int preview_player_contact(void *context, short *touching)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview->map_mode) {
        *touching = 0;
        for (unsigned int i = 0; i < map_enemies.count; ++i) {
            const ENGINE_LIZARD *lizard = &map_enemies.lizards[i];
            if (&lizard->body.owner == preview->air.contact_source && lizard->body.node)
                return render_objects_hit(preview->air.player.body.node, lizard->body.node, touching);
        }
        return 0;
    }
    *touching = preview->fixture_touching;
    return 0;
}

static int preview_camera(const DEFLECTION_PREVIEW *preview, RENDER_OWNER *camera)
{
    if (preview->map_mode) {
        *camera = preview->camera.position;
        return 0;
    }
    *camera = (RENDER_OWNER){
        preview->air.player.body.owner.x > 160 ?
            (short)(preview->air.player.body.owner.x - 160) : 0,
        preview->map_mode && preview->air.player.body.owner.y > 120 ?
            (short)(preview->air.player.body.owner.y - 120) : 0};
    RENDER_VIEWPORT viewport;
    return render_prepare_viewport(camera,
        (unsigned short)(map[8] | (unsigned int)map[9] << 8),
        (unsigned short)(map[12] | (unsigned int)map[13] << 8), 0, &viewport);
}

static int preview_ledge_height(void *context, short x, short y, short *height)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview->map_mode) return engine_map_ledge_height(&preview->collision, x, y, height);
    (void)x; (void)y;
    *height = 16;
    return 0;
}

static int preview_player_support(void *context, short *supported)
{
    DEFLECTION_PREVIEW *preview = context;
    ENGINE_FALLING_OBJECT *body = &preview->air.player.body;
    if (preview->map_mode) {
        if (preview->air.player.flags_high & 0x80) {
            *supported = -1;
            preview->air.contact_kind = preview->air.surface_kind = 0;
            return 0;
        }
        ENGINE_MAP_GROUND ground;
        if (engine_map_ground(&preview->collision, body->owner.x, body->owner.y, &ground) != 0) {
            lk_platform_log("Lion King: invalid map support query.\n");
            return -1;
        }
        *supported = ground.supported;
        preview->air.contact_kind = ground.kind;
        preview->air.surface_kind = ground.surface_kind;
        if (ground.supported) {
            ++preview->map_contacts;
            if (ground.delta_y) ++preview->map_height_changes;
            body->owner.y = (short)(body->owner.y + ground.delta_y);
        }
        return 0;
    }
    *supported = body->owner.y >= preview->fixture_floor;
    if (*supported) {
        body->owner.y = preview->fixture_floor;
    }
    preview->air.contact_kind = preview->fixture_terrain;
    preview->air.surface_kind = 0;
    return 0;
}

static int preview_ground_ready(DEFLECTION_PREVIEW *preview,
    const ENGINE_PLAYER_CALL *call)
{
    preview->airborne = 0;
    lk_platform_log("Original player ground handler selected.\n");
    if (preview->air.player.handler == call->handler) {
        preview->object->behavior = &engine_player_ground_behavior;
        return 0;
    }
    return engine_player_begin_ground(&scene_objects, preview->object, &preview->air, call);
}

static int preview_player_ready(DEFLECTION_PREVIEW *preview)
{
    ENGINE_FALLING_OBJECT *body = &preview->air.player.body;
    if (animation_program_initialize(&body->animation, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x6148,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) != 0) {
        return -1;
    }
    body->motion.velocity_x = 0;
    preview->object->behavior = 0;
    preview->completed = 1;
    preview->airborne = 0;
    lk_platform_log("Player jump reached ground boundary; idle/input fixture ready.\n");
    return animation_program_step(&body->animation, body->node, &body->owner,
        record_player_idle_event, preview);
}

static int preview_player_sound(void *context, unsigned short sample)
{
    DEFLECTION_PREVIEW *preview = context;
    if (sample != 0 && sample != 1 && sample != 10 && sample != 16 &&
        (sample < 2 || sample > 6)) {
        lk_platform_log("Lion King: unexpected player sound.\n");
        return -1;
    }
    if (preview->map_mode) {
        if (!sound_enabled) {
            lk_platform_log("Original LEVEL1 sample requested; sound muted.\n");
            return 0;
        }
        if (sample >= 19 || !effect_sizes[sample] ||
            music_effect_play(&music_player, 0, effect_samples[sample],
                effect_sizes[sample]) != 0) {
            lk_platform_log("Lion King: cannot play original LEVEL1 sound effect.\n");
            return -1;
        }
        lk_platform_log(sample == 0 ?
            "Original rebound sample 0 requested; PCM output active.\n" : sample == 2 || sample == 3 ?
            "Original roar sample requested; PCM output active.\n" :
            "Original LEVEL1 sample requested; PCM output active.\n");
        return 0;
    }
    lk_platform_log(sample == 16 ?
        "Original beetle explosion sample requested; audio output unported.\n" :
        sample == 1 || sample == 10 ?
        "Original pickup sample requested; audio output unported.\n" : sample == 0 ?
        "Original rebound sample 0 requested; audio output unported.\n" : sample <= 3 ?
        "Original roar sample requested; audio output unported.\n" : sample <= 5 ?
        "Original recovery sample 4 requested; audio output unported.\n" :
        "Original roll sample 6 requested; audio output unported.\n");
    return 0;
}

static int preview_enemy_sound(void *context, unsigned short channel, unsigned short sample)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview && preview->map_mode && !sound_enabled) return 0;
    if (!preview || !preview->map_mode || sample >= 19 || !effect_sizes[sample] ||
        music_effect_play(&music_player, channel, effect_samples[sample],
            effect_sizes[sample]) != 0) {
        lk_platform_log("Lion King: cannot play original enemy sound effect.\n");
        return -1;
    }
    return 0;
}

static int preview_player_probe(void *context, short x, short y, short *hit)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview->map_mode) {
        int result = engine_map_ceiling(&preview->collision,
            preview->air.player.body.node, x, y, hit);
        if (result != 0) lk_platform_log("Lion King: invalid map ceiling query.\n");
        else if (*hit) ++preview->map_ceiling_hits;
        return result;
    }
    (void)x;
    (void)y;
    *hit = !preview->jump && (preview->variant & 4) ? -1 : 0;
    return 0;
}

static int preview_player_transition(void *context, const ENGINE_PLAYER_CALL *call)
{
    DEFLECTION_PREVIEW *preview = context;
    if ((call->handler != 0xaa97U && call->handler != 0xae53U) ||
        call->script != 0x6116U || call->counter != 0) {
        lk_platform_log("Lion King: unexpected player preview transition.\n");
        return -1;
    }
    if (preview->flight) {
        preview->airborne = 1;
        preview->air.pressed = preview->variant & 1 ? 4 : 8;
        return engine_player_begin_air(&scene_objects, preview->object, &preview->air, call);
    }
    preview->object->behavior = 0;
    preview->completed = 1;
    lk_platform_log("Player deflection reached unported next state; fixture pauses.\n");
    return 0;
}

static int preview_player_ground(void *context, short *kind, short *delta_y)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview->map_mode) {
        ENGINE_FALLING_OBJECT *body = &preview->air.player.body;
        ENGINE_MAP_GROUND ground;
        if (engine_map_ground(&preview->collision, body->owner.x, body->owner.y, &ground) != 0) {
            lk_platform_log("Lion King: invalid map landing query.\n");
            return -1;
        }
        *kind = ground.supported;
        *delta_y = ground.delta_y;
        preview->air.contact_kind = ground.kind;
        return 0;
    }
    *kind = preview->air.player.body.owner.y >= preview->fixture_floor ? 1 : 0;
    *delta_y = (short)(preview->fixture_floor - preview->air.player.body.owner.y);
    return 0;
}

static int preview_player_edge(void *context, short *hit, short *kind, short *x, short *y)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview->map_mode) {
        int result = engine_map_edge(&preview->collision, preview->air.player.body.node,
            hit, kind, x, y);
        if (result != 0) lk_platform_log("Lion King: invalid map edge query.\n");
        else if (*hit) ++preview->map_edge_contacts;
        return result;
    }
    *hit = *kind = *x = *y = 0;
    unsigned int handler = preview->air.player.handler;
    if (preview->fixture_wall_contact && (handler == 0xdc42U || handler == 0xdeafU) &&
        preview->air.player.body.animation.counter <= 8) {
        preview->fixture_wall_contact = 0;
        *hit = -1;
        *kind = preview->wall_case < 2 ? (handler == 0xdc42U ? 0xf8 : 0xe8) : 0xea;
        *x = preview->air.player.body.owner.x;
        *y = preview->air.player.body.owner.y;
        if (*kind == 0xea) preview->fixture_floor = (short)((*y & 0xfff0) + 15);
    }
    return 0;
}

static int preview_player_landed(void *context, const ENGINE_PLAYER_CALL *call,
    short kind, short x, short y)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview->ground_mode) {
        if (preview->map_mode && call->handler == 0xc884U) {
            lk_platform_log("LEVEL1: original lethal-fall countdown selected.\n");
            return engine_level_life_fall(&preview->life, call);
        }
        if (call->handler == 0xef04U) {
            if (preview->map_mode && (!preview->air.damage_source ||
                !(preview->air.player.flags_high & 4))) {
                lk_platform_log("Lion King: map hazard damage/source handling is not migrated.\n");
                return -1;
            }
            lk_platform_log(preview->map_mode ?
                "Original damage/recoil handler selected from a real enemy contact.\n" :
                "Original damage/recoil handler selected; source is a test fixture.\n");
            return engine_player_damage(&scene_objects, preview->object, &preview->air);
        }
        if (call->handler == 0xec69U || call->handler == 0xee35U ||
            call->handler == 0xee60U || call->handler == 0xf017U || call->handler == 0xf160U ||
            call->handler == 0xf2b1U || call->handler == 0xf3fbU || call->handler == 0xf6ccU ||
            call->handler == 0x10075U || call->handler == 0xd40aU || call->handler == 0xd4ffU ||
            call->handler == 0xdc42U || call->handler == 0xdeafU) {
            lk_platform_log("Original player action handler selected.\n");
            return engine_player_begin_action(&scene_objects, preview->object, &preview->air, call);
        }
        if (call->handler == 0xe775U || call->handler == 0xe8dfU) {
            int result = engine_player_begin_ledge(&scene_objects, preview->object, &preview->air,
                call->handler, kind, x, y);
            if (result != 0) lk_platform_log("Lion King: map contact selected an unported edge branch.\n");
            return result;
        }
        if (call->handler == 0xf5f1U || call->handler == 0xf618U || call->handler == 0xf672U) {
            return engine_player_rebound(&scene_objects, preview->object, &preview->air, call->handler);
        }
        if (call->handler == 0xf80dU || call->handler == 0xfe3cU) {
            uint32_t velocity = ((uint32_t)(unsigned short)x << 16) | (unsigned short)y;
            return engine_player_begin_terrain(&scene_objects, preview->object,
                &preview->air, call->handler, kind, velocity);
        }
    }
    if (call->handler != 0xc8d5U && call->handler != 0xc2cdU &&
        call->handler != 0xcdc2U && call->handler != 0xd108U &&
        call->handler != 0xb253U && call->handler != 0xb19fU) {
        lk_platform_log("Lion King: unexpected player flight boundary.\n");
        return -1;
    }
    if (preview->jump) {
        if (call->handler == 0xb253U || call->handler == 0xb19fU) {
            return engine_player_begin_recovery(&scene_objects, preview->object,
                &preview->air, call);
        }
        return preview_player_ready(preview);
    }
    if (preview->ground_mode) {
        if (preview->map_mode) ++preview->map_landings;
        if (call->handler == 0xb253U || call->handler == 0xb19fU) {
            return engine_player_begin_recovery(&scene_objects, preview->object,
                &preview->air, call);
        }
        return preview_ground_ready(preview, call);
    }
    preview->object->behavior = 0;
    preview->completed = 1;
    lk_platform_log("Player flight landed through original selector; next ground state unported.\n");
    return 0;
}

static int begin_player_preview(DEFLECTION_PREVIEW *preview)
{
    if (preview->ground_mode) {
        preview->air.player.body.owner = (RENDER_OWNER){160, 160};
        if (preview->map_mode) preview->air.player.body.owner =
            (RENDER_OWNER){preview->map_spawn_x, preview->map_spawn_y};
        preview->air.player.body.motion = (ENGINE_MOTION){0};
        ENGINE_PLAYER_CALL call = {0xc8d5, 0x6148, 0};
        return preview_ground_ready(preview, &call);
    }
    if (preview->jump) {
        preview->air.player.body.owner = (RENDER_OWNER){160, 160};
        preview->air.player.body.motion = (ENGINE_MOTION){0};
        return preview_player_ready(preview);
    }
    ENGINE_PLAYER_CALL call;
    uint32_t position = UINT32_C(0x6c31) + (preview->variant & 2 ? 2 : 0);
    int status = preview->variant & 1 ?
        engine_player_reaction_e6ee(0, position, &call) :
        engine_player_reaction_e667(0, position, &call);
    if (status != 0) {
        return -1;
    }
    preview->air.player.body.owner = (RENDER_OWNER){160, 100};
    preview->air.player.body.motion = (ENGINE_MOTION){0};
    preview->collision_flags = 0;
    preview->completed = 0;
    preview->airborne = 0;
    return engine_player_begin_deflection(preview->object, &preview->air.player, &call);
}

static int preview_map_life(DEFLECTION_PREVIEW *preview)
{
    unsigned int deaths = preview->life.deaths;
    int result = engine_level_life_tick(&preview->life, preview->camera.position);
    if (preview->life.deaths != deaths) {
        unsigned char death_rgb[768] = {0};
        for (unsigned int i = 0; i < 24; ++i) death_rgb[i] = level_rgb[i];
        if (vga_fade_begin(&fade, death_rgb) != 0) return -1;
        preview->level_title_ticks = 0;
        lk_platform_log("LEVEL1: original SYDIE lost-life scene and palette fade started.\n");
    }
    if (result == ENGINE_LIFE_RESTART) {
        if (vga_fade_initialize(&fade, level_rgb) != 0 ||
            vga_palette_colors(fade.current, palette) != 0) return -1;
        if (engine_enemies_restart(&map_enemies) != 0 ||
            engine_pickups_restart(&map_pickups) != 0) return -1;
        ENGINE_PLAYER_AIR *air = &preview->air;
        air->player.body.owner = map_pickups.checkpoint;
        air->player.body.motion = (ENGINE_MOTION){0};
        air->player.body.node->flags = 0x40;
        air->player.body.node->pass_flags = 0;
        air->player.immunity = 100;
        air->player.flags_high = 0;
        air->player.age = air->player.controls = 0;
        air->flags = air->player_flags = air->pressed = 0;
        air->anchor_x = air->anchor_y = 0;
        air->contact_kind = air->landing_flags = air->surface_kind = air->jump_boost = 0;
        air->jump_air_script = air->auxiliary_controls = air->boundary_controls = 0;
        air->action_timer = 0;
        air->progress = air->progress_limit = 0;
        preview->collision_flags = 0;
        preview->airborne = 0;
        preview->input_taps = 0;
        air->player.handler = 0;
        ENGINE_PLAYER_CALL call = {0xc8d5, 0x6148, 0};
        if (preview_ground_ready(preview, &call) != 0) return -1;
        preview->camera.horizontal_offset = 128;
        preview->camera.position = (RENDER_OWNER){
            (short)(air->player.body.owner.x - 128),
            (short)(air->player.body.owner.y - 128)};
        RENDER_VIEWPORT viewport;
        if (render_prepare_viewport(&preview->camera.position, preview->collision.width,
            preview->collision.height, 0, &viewport) != 0) return -1;
        lk_platform_log("LEVEL1: restored health and restarted at the saved checkpoint.\n");
    } else if (result == ENGINE_LIFE_GAME_OVER) {
        if (!preview->game_over_ticks) {
            preview->game_over_ticks = 1;
            preview->continue_exhausted = preview->continues_remaining == 0;
            if (!preview->continue_exhausted) {
                if (preview->continues_remaining > 9) preview->continues_remaining = 9;
                preview->continues_shown = preview->continues_remaining--;
            }
            preview->continue_ticks = preview->continue_exhausted ?
                FRONTEND_GAME_OVER_TICKS : FRONTEND_CONTINUE_TICKS;
            if (vga_fade_initialize(&fade, level_rgb) != 0 ||
                vga_palette_colors(fade.current, palette) != 0) return -1;
            music_output_stop(&music_output);
            if (frontend_start_continue(preview->api, music_enabled) != 0) return -1;
            lk_platform_log(preview->continue_exhausted ?
                "LEVEL1: no continues remaining; GAME OVER started.\n" :
                "LEVEL1: no lives remaining; continue countdown started.\n");
        }
        if (preview->continue_pressed && !preview->continue_accept_ticks) {
            preview->continue_pressed = 0;
            if (!preview->continue_exhausted && !preview->continue_no) {
                if (frontend_accept_continue(preview->api, sound_enabled) != 0) return -1;
                preview->continue_accept_ticks = FRONTEND_CONTINUE_ACCEPT_TICKS;
                return result;
            }
            frontend_stop_continue();
            preview->completed = 1;
            lk_platform_log(preview->continue_exhausted ?
                "LEVEL1: GAME OVER dismissed.\n" : "LEVEL1: continue declined.\n");
            return result;
        }
        if (preview->continue_accept_ticks == FRONTEND_CONTINUE_ACCEPT_TICKS - 40 &&
            frontend_continue_speech(sound_enabled) != 0) return -1;
        if (preview->continue_accept_ticks && !--preview->continue_accept_ticks) {
            frontend_stop_continue();
            unsigned char restored_lives;
            unsigned int initial_continues;
            if (engine_difficulty_counts(game_difficulty, &restored_lives, &initial_continues) != 0 ||
                vga_fade_initialize(&fade, level_rgb) != 0 ||
                vga_palette_colors(fade.current, palette) != 0 ||
                engine_enemies_restart(&map_enemies) != 0 ||
                engine_pickups_restart(&map_pickups) != 0 ||
                engine_level_life_initialize(&preview->life, &preview->air,
                    preview->object, restored_lives) != 0) return -1;
            preview->air.health = map_pickups.max_health;
            preview->air.roar_charge = 0;
            preview->air.player.body.owner = map_pickups.checkpoint;
            preview->air.player.body.motion = (ENGINE_MOTION){0};
            preview->air.player.body.node->flags = 0x40;
            preview->air.player.body.node->pass_flags = 0;
            preview->air.player.immunity = 100;
            preview->air.player.flags_high = 0;
            preview->air.player.age = preview->air.player.controls = 0;
            preview->air.flags = preview->air.player_flags = preview->air.pressed = 0;
            preview->air.anchor_x = preview->air.anchor_y = 0;
            preview->air.contact_kind = preview->air.landing_flags = 0;
            preview->air.surface_kind = preview->air.jump_boost = 0;
            preview->air.jump_air_script = preview->air.auxiliary_controls = 0;
            preview->air.boundary_controls = 0;
            preview->air.action_timer = preview->air.progress = preview->air.progress_limit = 0;
            preview->air.player.handler = 0;
            preview->collision_flags = 0;
            preview->airborne = 0;
            preview->input_taps = 0;
            preview->game_over_ticks = preview->continue_ticks = 0;
            preview->continue_pressed = 0;
            preview->completed = 0;
            preview->camera.horizontal_offset = 128;
            preview->camera.position = (RENDER_OWNER){
                (short)(preview->air.player.body.owner.x - 128),
                (short)(preview->air.player.body.owner.y - 128)};
            RENDER_VIEWPORT viewport;
            if (render_prepare_viewport(&preview->camera.position, preview->collision.width,
                preview->collision.height, 0, &viewport) != 0) return -1;
            ENGINE_PLAYER_CALL call = {0xc8d5, 0x6148, 0};
            if (preview_ground_ready(preview, &call) != 0) return -1;
            if (music_enabled || sound_enabled) {
                if ((music_enabled ? music_initialize(&music_player, level_music, preview->level_music_size) :
                        music_effects_initialize(&music_player)) != 0 ||
                    music_output_open(&music_output, &music_player, preview->api) != 0) {
                    lk_platform_log("Lion King: cannot restart LEVEL1 music after continue.\n");
                    return -1;
                }
            }
            lk_platform_log("LEVEL1: continue accepted; lives restored at checkpoint.\n");
            return ENGINE_LIFE_RESTART;
        }
        if (!preview->continue_accept_ticks && preview->continue_ticks > 1) --preview->continue_ticks;
        else if (!preview->continue_accept_ticks) {
            frontend_stop_continue();
            preview->completed = 1;
        }
    } else if (result == ENGINE_LIFE_COMPLETE) {
        lk_platform_log("LEVEL1: hyena defeated; original level-completion condition reached.\n");
        preview->completed = 1;
    }
    return result;
}

static void update_player_preview(void *context)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview->level_title_ticks && !--preview->level_title_ticks)
        lk_platform_log("LEVEL1: original level name removed after 100 gameplay ticks.\n");
    if (preview->ground_mode) {
        if (preview->map_mode) {
            int life = preview_map_life(preview);
            if (life < 0) {
                lk_platform_log("Lion King: LEVEL1 death/restart failed.\n");
                preview->failed = 1;
                return;
            }
            if (life != ENGINE_LIFE_PLAYING) return;
        }
        unsigned short held = (preview->api->Input.KeyDown[game_controls.keys[CONTROL_LEFT]] ? 4 : 0) |
            (preview->api->Input.KeyDown[game_controls.keys[CONTROL_RIGHT]] ? 8 : 0) |
            (preview->api->Input.KeyDown[game_controls.keys[CONTROL_JUMP]] ? 0x20 : 0) |
            (preview->api->Input.KeyDown[game_controls.keys[CONTROL_DOWN]] ? 2 : 0) |
            (preview->api->Input.KeyDown[game_controls.keys[CONTROL_UP]] ? 1 : 0) |
            ((preview->api->Input.KeyDown[game_controls.keys[CONTROL_ROAR]] ||
                (preview_alternate_roar() && preview->api->Input.KeyDown[0xe4])) ? 0x40 : 0);
        int request_hit = preview->input_taps & 0x100;
        int request_terrain = preview->input_taps & 0x200;
        unsigned short contact_actions = preview->input_taps & 0x1c00;
        int request_ledge = preview->input_taps & 0x2000;
        int request_perch = preview->input_taps & 0x4000;
        int request_wall = preview->input_taps & 0x8000;
        if (preview->map_mode && (request_hit || request_terrain || contact_actions ||
            request_ledge || request_perch || request_wall)) {
            lk_platform_log("Synthetic contact controls are disabled in map mode.\n");
            request_hit = request_terrain = request_ledge = request_perch = request_wall = 0;
            contact_actions = 0;
        }
        if (!preview->manual && preview->wall_demo) {
            unsigned long long elapsed = lk_platform_time_ns() - preview->jump_begin;
            unsigned int phase = (unsigned int)(elapsed / 4000000000ULL) + 1;
            unsigned long long within = elapsed % 4000000000ULL;
            if (phase != preview->wall_demo_phase) {
                preview->wall_demo_phase = phase;
                preview->wall_variant = (phase - 1) % 8;
                request_wall = 1;
            }
            held = within >= 700000000ULL ? (preview->wall_case >= 6 ? 2 : 0x20) : 0;
            if (preview->air.player.handler == 0xd5f4U || preview->air.player.handler == 0xd7a3U) {
                held = 1;
            }
        } else if (!preview->manual && preview->ledge_demo) {
            unsigned long long elapsed = lk_platform_time_ns() - preview->jump_begin;
            unsigned int phase = (unsigned int)(elapsed / 4000000000ULL) + 1;
            unsigned long long within = elapsed % 4000000000ULL;
            unsigned int action = (phase - 1) % 4;
            held = within >= 900000000ULL && within < 2100000000ULL ?
                (action < 2 ? 1 : 2) : 0;
            if (phase != preview->ledge_demo_phase) {
                preview->ledge_demo_phase = phase;
                preview->ledge_variant = action;
                request_ledge = 1;
            }
        } else if (!preview->manual && preview->contact_demo) {
            unsigned int phase = (unsigned int)((lk_platform_time_ns() - preview->jump_begin) /
                3000000000ULL) + 1;
            held = 0;
            if (phase != preview->contact_demo_phase) {
                preview->contact_demo_phase = phase;
                unsigned int action = (phase - 1) % 4;
                preview->air.player.body.node->pass_flags = (unsigned char)(
                    (preview->air.player.body.node->pass_flags & 0xf7) | (action & 1 ? 8 : 0));
                contact_actions = action < 2 ? 0x400 : action == 2 ? 0x800 : 0x1000;
            }
        } else if (!preview->manual) {
            unsigned long long phase = (lk_platform_time_ns() - preview->jump_begin) % 12000000000ULL;
            held = phase < 1800000000ULL ? 8 : phase < 2100000000ULL ? 0 :
                phase < 4300000000ULL ? 4 : phase < 5200000000ULL ? 8 :
                phase < 5700000000ULL ? 2 :
                (phase >= 6200000000ULL && phase < 6400000000ULL) ||
                (phase >= 8100000000ULL && phase < 8300000000ULL) ? 0x40 :
                phase >= 7600000000ULL && phase < 7800000000ULL ? 4 : 0;
            if ((phase >= 800000000ULL && phase < 1300000000ULL) ||
                (phase >= 3100000000ULL && phase < 3600000000ULL)) {
                held |= 0x20;
            }
            if (phase < 10000000000ULL) {
                preview->demo_hit = 0;
            } else if (!preview->demo_hit) {
                request_hit = 1;
                preview->demo_hit = 1;
            }
        }
        preview->air.pressed = held | (preview->input_taps & 0x60);
        preview->air.player.controls = (unsigned char)preview->input_taps;
        preview->input_taps = 0;
        if ((held & 2) && (preview->air.player.handler == 0xd5f4U ||
            preview->air.player.handler == 0xd7a3U)) {
            preview->fixture_floor = 192;
        }
        if (preview->tether_ticks && !--preview->tether_ticks) {
            preview->air.flags &= 0xfffbU;
        }
        if (preview->terrain_ticks && !--preview->terrain_ticks) {
            preview->fixture_terrain = 0;
        }
        if (request_terrain) {
            static const unsigned char kinds[] = {6, 9, 5, 8};
            preview->fixture_terrain = kinds[preview->terrain_variant++ & 3];
            preview->terrain_ticks = 60;
            lk_platform_log("Synthetic terrain contact enabled for original slide handlers.\n");
        }
        if (request_hit) {
            int left = preview->air.player.body.node->pass_flags & 8;
            preview->damage_source.x = (short)(preview->air.player.body.owner.x + (left ? 16 : -16));
            preview->air.player.immunity = 0;
            preview->air.player.flags_high |= 4;
            ENGINE_PLAYER_CALL damage = {0xef04, 0, 0};
            if (preview_player_landed(preview, &damage, 0, 0, 0) != 0) {
                preview->failed = 1;
                return;
            }
        }
        if (contact_actions) {
            ENGINE_PLAYER_CALL call = {contact_actions & 0x400 ? 0xf5f1U :
                contact_actions & 0x800 ? 0xf2b1U : 0xf6ccU, 0, 0};
            if (call.handler == 0xf6ccU) {
                preview->air.tether_target.x = (short)(preview->air.player.body.owner.x + 80);
                preview->air.tether_target.y = 100;
                preview->air.flags |= 4;
                preview->tether_ticks = 45;
            }
            lk_platform_log(call.handler == 0xf5f1U ?
                (preview->air.player.body.node->pass_flags & 8 ?
                    "Original left contact rebound selected; activation is diagnostic.\n" :
                    "Original right contact rebound selected; activation is diagnostic.\n") :
                call.handler == 0xf2b1U ?
                    "Original thrown launch selected; activation is diagnostic.\n" :
                    "Original tether movement selected; target/release are diagnostic.\n");
            if (preview_player_landed(preview, &call, 0, 0, 0) != 0) {
                preview->failed = 1;
                return;
            }
        }
        unsigned int before = preview->air.player.handler;
        if (request_ledge) {
            int right = preview->ledge_variant++ & 1;
            preview->fixture_floor = 111;
            ENGINE_PLAYER_CALL call = {right ? 0xe8dfU : 0xe775U, 0, 0};
            lk_platform_log(right ?
                "Original right ledge grab selected; geometry/support are fixtures.\n" :
                "Original left ledge grab selected; geometry/support are fixtures.\n");
            if (preview_player_landed(preview, &call, 0xea,
                preview->air.player.body.owner.x, 96) != 0) {
                preview->failed = 1;
                return;
            }
        }
        if (request_perch) {
            preview->air.flags |= 0x800;
            ENGINE_PLAYER_CALL call = {0x10075, 0, 0};
            if (preview_player_landed(preview, &call, 0, 0, 0) != 0) {
                preview->failed = 1;
                return;
            }
            lk_platform_log("Original supported-turn state selected; support is diagnostic.\n");
        }
        if (request_wall) {
            preview->wall_case = preview->wall_variant++ % 8;
            int left_wall = !(preview->wall_case & 1);
            preview->fixture_floor = 192;
            preview->fixture_wall_contact = preview->wall_case < 2 ||
                (preview->wall_case >= 4 && preview->wall_case < 6);
            preview->air.player.body.node->pass_flags = (unsigned char)(
                (preview->air.player.body.node->pass_flags & 0xf7) | (left_wall ? 8 : 0));
            lk_platform_log(left_wall ?
                "Original left wall grip selected; initial contact is diagnostic.\n" :
                "Original right wall grip selected; initial contact is diagnostic.\n");
            if (engine_player_begin_wall(&scene_objects, preview->object, &preview->air,
                left_wall ? 0xdb06U : 0xd985U, preview->air.player.body.owner.x, 160) != 0) {
                preview->failed = 1;
                return;
            }
        }
        if (preview->map_mode) {
            if (engine_enemies_player_clock(&map_enemies) != 0) {
                lk_platform_log("Lion King: original enemy/player immunity clock failed.\n");
                preview->failed = 1;
                return;
            }
            if (preview->air.roar_charge > map_pickups.max_roar)
                preview->air.roar_charge = map_pickups.max_roar;
            if (engine_map_lateral(&preview->collision, &preview->air.player.body.owner,
                preview->air.flags, preview->air.player.flags_high,
                &preview->air.boundary_controls) != 0) {
                lk_platform_log("Lion King: invalid map lateral query.\n");
                preview->failed = 1;
                return;
            }
            if (preview->air.boundary_controls & 4) ++preview->map_left_blocks;
            if (preview->air.boundary_controls & 8) ++preview->map_right_blocks;
            preview->air.pressed &= (unsigned short)~preview->air.boundary_controls;
        }
        if (engine_update_objects(&scene_objects, &preview->api->Input) != 0) {
            preview->failed = 1;
            return;
        }
        if (preview->map_mode) {
            RENDER_OWNER camera;
            if (render_follow_camera(&preview->camera, preview->air.player.body.owner,
                (unsigned char)(preview->air.player.body.node->pass_flags & 8),
                preview->air.player.flags_high, preview->collision.width,
                preview->collision.height) != 0 ||
                preview_camera(preview, &camera) != 0 ||
                engine_enemies_tick(&map_enemies, camera) != 0) {
                lk_platform_log("Lion King: original LEVEL1 enemy update failed.\n");
                preview->failed = 1;
                return;
            }
            if (engine_pickups_tick(&map_pickups, camera) != 0) {
                lk_platform_log("Lion King: original LEVEL1 pickup update failed.\n");
                preview->failed = 1;
                return;
            }
            unsigned int objective = preview->level_number == 1 ?
                map_enemies.hyenas_defeated :
                preview->air.player.body.owner.x >=
                    (short)(preview->collision.width * 8U - 32U);
            if (engine_level_life_complete(&preview->life, objective) != 0) {
                lk_platform_log(preview->level_number == 1 ?
                    "Lion King: LEVEL1 completion transition failed.\n" :
                    "Lion King: LEVEL2 completion transition failed.\n");
                preview->failed = 1;
                return;
            }
        }
        preview->airborne = preview->object->behavior == &engine_player_jump_behavior ||
            preview->object->behavior == &engine_player_air_behavior;
        if (preview->air.player.handler != before &&
            preview->object->behavior == &engine_player_jump_behavior) {
            lk_platform_log("Original running/standing jump selected.\n");
        }
        if (preview->air.player.handler != before &&
            (before == 0xd5f4U || before == 0xd7a3U)) {
            lk_platform_log(held & 2 ?
                "Original ledge drop selected.\n" : "Original ledge climb selected.\n");
        }
        if (preview->air.player.handler != before &&
            (before == 0xd40aU || before == 0xd4ffU)) {
            lk_platform_log("Original ledge climb completed; ground control resumed.\n");
        }
        if (preview->air.player.handler != before &&
            (before == 0xdb06U || before == 0xd985U)) {
            lk_platform_log(preview->air.player.handler == 0xdc42U ?
                "Original left wall leap selected.\n" : preview->air.player.handler == 0xdeafU ?
                "Original right wall leap selected.\n" : "Original wall detach selected.\n");
        }
        if (preview->air.player.handler != before &&
            (before == 0xdc42U || before == 0xdeafU)) {
            lk_platform_log(preview->air.player.handler == 0xdb06U ?
                "Original wall leap caught left wall.\n" : preview->air.player.handler == 0xd985U ?
                "Original wall leap caught right wall.\n" :
                preview->air.player.handler == 0xd5f4U || preview->air.player.handler == 0xd7a3U ?
                "Original wall leap caught ledge.\n" : "Original wall leap resumed flight.\n");
        }
        return;
    }
    if (preview->jump) {
        ENGINE_PLAYER_DEFLECTION *player = &preview->air.player;
        unsigned long long now = lk_platform_time_ns();
        unsigned short directions = (preview->api->Input.KeyDown[0x50] ? 4 : 0) |
            (preview->api->Input.KeyDown[0x4f] ? 8 : 0);
        preview->air.pressed = directions |
            (preview->api->Input.KeyDown[0x2c] ? 0x20 : 0);
        if (!preview->manual && preview->airborne) {
            if (!directions) {
                preview->air.pressed |= preview->variant & 1 ? 4 : 8;
            }
            if (now - preview->jump_begin < (preview->variant & 2 ? 500000000ULL : 100000000ULL)) {
                preview->air.pressed |= 0x20;
            }
        }
        if (preview->completed) {
            if (directions) {
                player->body.node->pass_flags = (unsigned char)(
                    (player->body.node->pass_flags & 0xf7) | (directions & 4 ? 8 : 0));
            }
            if (preview->jump_requested ||
                (!preview->manual && now - preview->jump_begin >= 2000000000ULL)) {
                preview->jump_requested = 0;
                if (!preview->manual) {
                    preview->variant = (preview->variant + 1) & 3;
                    player->body.owner.x = 160;
                    player->body.node->pass_flags = (unsigned char)(
                        (player->body.node->pass_flags & 0xf7) | (preview->variant & 1 ? 8 : 0));
                }
                ENGINE_PLAYER_CALL call = {
                    player->body.node->pass_flags & 8 ? 0xb7e7U : 0xb604U, 0x6180, 4
                };
                preview->air.flags &= 0xdfffU;
                preview->jump_begin = now;
                preview->completed = 0;
                preview->airborne = 1;
                if (engine_player_begin_jump(&scene_objects, preview->object,
                    &preview->air, &call, 0x612c) != 0) {
                    preview->failed = 1;
                    return;
                }
                lk_platform_log("Original player jump started.\n");
            }
            ENGINE_FALLING_OBJECT *body = &player->body;
            if (animation_program_step(&body->animation, body->node, &body->owner,
                record_player_idle_event, preview) != 0) {
                preview->failed = 1;
            }
            return;
        }
    }
    if (preview->flight && !preview->jump && preview->airborne) {
        unsigned short directions = (preview->api->Input.KeyDown[0x50] ? 4 : 0) |
            (preview->api->Input.KeyDown[0x4f] ? 8 : 0);
        preview->air.pressed = directions ? directions : (preview->variant & 1 ? 4 : 8);
    }
    if (!preview->failed &&
        engine_update_objects(&scene_objects, &preview->api->Input) != 0) {
        preview->failed = 1;
    }
}

static int render_player_frame(const DEFLECTION_PREVIEW *preview, unsigned int map_size,
    unsigned short camera_x, unsigned short camera_y, const RENDER_SPRITE_BANK *banks,
    unsigned char *view)
{
    for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) view[i] = 0;
    RENDER_NODE *player = preview->air.player.body.node;
    unsigned char player_flags = player->flags;
    if (preview->map_mode && preview->life.game_over) {
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) view[i] = 0;
        if (frontend_continue(view, palette, preview->continue_ticks, preview->continue_no,
            preview->continues_shown, preview->continue_accept_ticks,
            preview->continue_exhausted) != 0) return -1;
        return 0;
    }
    if (preview->life.dying) player->flags |= 0x80;
    if ((preview->map_mode && render_map_background(map, map_size,
            preview->level_number,
            camera_x, camera_y, view) != 0) ||
        render_map_tile_pass(map, map_size, 0, camera_x, camera_y, 0, view) != 0 ||
        (!preview->map_mode && render_map_tile_pass(map, map_size, 0,
            camera_x, camera_y, 1, view) != 0) ||
        render_object_pass(&render_pool, 0, (short)-(int)camera_x, (short)-(int)camera_y,
            banks, 127, view) != 0 ||
        (preview->map_mode && (render_map_tile_pass(map, map_size, 0,
            camera_x, camera_y, 1, view) != 0 ||
            render_object_pass(&render_pool, 0x80, (short)-(int)camera_x,
                (short)-(int)camera_y, banks, 127, view) != 0)) ||
        (preview->map_mode && engine_hud_draw(hud_sprites, banks[1].size,
            preview->air.health, map_pickups.max_health, preview->air.roar_charge,
            map_pickups.max_roar, preview->life.lives, view) != 0) ||
        (preview->level_title_ticks &&
            frontend_level_title_for_level(preview->level_number, view) != 0)) {
        if (preview->life.dying) player->flags = player_flags;
        return -1;
    }
    if (preview->life.dying) {
        RENDER_NODE *head = render_pool.head, *next = player->next;
        unsigned char pass = player->pass_flags;
        render_pool.head = player;
        player->next = 0;
        player->flags = player_flags & 0x3f;
        player->pass_flags &= 0x7f;
        int result = render_object_pass(&render_pool, 0, 0, 0, banks, 127, view);
        render_pool.head = head;
        player->next = next;
        player->flags = player_flags;
        player->pass_flags = pass;
        if (result != 0) return -1;
    }
    return 0;
}

static int render_player_opacity_frame(const DEFLECTION_PREVIEW *preview,
    unsigned int map_size, unsigned short camera_x, unsigned short camera_y,
    const RENDER_SPRITE_BANK *banks, unsigned char *view, int *dim_phase)
{
    RENDER_NODE *player = preview->air.player.body.node;
    *dim_phase = preview->map_mode && preview->air.player.immunity &&
        (player->flags & 0x20) && !(player->flags & 0x80) &&
        ((player->flags & 0x10) ? player->remaining != 0 : player->remaining == 0);
    unsigned char before_flags[RENDER_NODE_COUNT], before_remaining[RENDER_NODE_COUNT];
    if (*dim_phase) {
        for (unsigned int i = 0; i < RENDER_NODE_COUNT; ++i) {
            before_flags[i] = render_pool.nodes[i].flags;
            before_remaining[i] = render_pool.nodes[i].remaining;
        }
    }
    if (render_player_frame(preview, map_size, camera_x, camera_y, banks, view) != 0)
        return -1;
    if (!*dim_phase) return 0;
    unsigned char after_flags[RENDER_NODE_COUNT], after_remaining[RENDER_NODE_COUNT];
    /* Replay the same frame with Simba visible. Foreground tiles and other
       sprites stay in both layers; render timers advance only once. */
    for (unsigned int i = 0; i < RENDER_NODE_COUNT; ++i) {
        after_flags[i] = render_pool.nodes[i].flags;
        after_remaining[i] = render_pool.nodes[i].remaining;
        render_pool.nodes[i].flags = before_flags[i];
        render_pool.nodes[i].remaining = before_remaining[i];
    }
    player->flags &= 0xdf;
    int result = render_player_frame(preview, map_size, camera_x, camera_y, banks, hurt_layer);
    for (unsigned int i = 0; i < RENDER_NODE_COUNT; ++i) {
        render_pool.nodes[i].flags = after_flags[i];
        render_pool.nodes[i].remaining = after_remaining[i];
    }
    return result;
}

int run_deflection_preview(const DOS64_API *api, int mode)
{
    int flight = mode != 0;
    unsigned int level_number = mode == 9 ? 2 : 1;
    loading_level = level_number;
    if (mode == 7 && loading_progress(0) != 0) return 1;
    unsigned int map_size;
    const char *map_name = level_number == 2 ? "LEVEL2.MAP" : "LEVEL1.MAP";
    if (resources_load_entry(&resource_api, "LIONKING.EPF", map_name, packed, sizeof(game_buffers->packed),
        map, sizeof(game_buffers->map), &dictionary, &map_size) != 0 ||
        vga_load_palette_rgb(map, map_size, level_rgb) != 0 ||
        vga_fade_initialize(&fade, level_rgb) != 0 ||
        vga_palette_colors(fade.current, palette) != 0) {
        lk_platform_log("Lion King: cannot load player reaction preview map.\n");
        return 1;
    }
    if (mode == 7 && menu_active && frontend_level_palette(palette) != 0) return 1;
    if (mode == 7 && loading_progress(1) != 0) return 1;
    RENDER_SPRITE_BANK banks[127] = {0};
    unsigned int count = flight ? ASSETS_YOUNG_BANK_COUNT : 2;
    for (unsigned int i = 0; i < count; ++i) {
        unsigned int slot, loaded;
        unsigned int index = flight ? i : 5 + i;
        if (assets_load_named_bank(&resource_api, "LIONKING.EPF", assets_young_bank_list,
            sizeof(assets_young_bank_list), index, packed, sizeof(game_buffers->packed),
            player_sprites[i], sizeof(player_sprites[i]), &dictionary, &slot, &loaded) != 0 ||
            slot != 6 + index) {
            lk_platform_log("Lion King: cannot load original flip banks.\n");
            return 1;
        }
        banks[slot] = (RENDER_SPRITE_BANK){player_sprites[i], loaded};
        if (mode == 7 && loading_progress(2 + i) != 0) return 1;
    }
    engine_initialize_objects(&scene_objects);
    render_initialize_nodes(&render_pool);
    DEFLECTION_PREVIEW preview = {0};
    preview.api = api;
    preview.level_number = level_number;
    preview.flight = flight;
    preview.jump = mode == 2;
    preview.ground_mode = mode >= 3;
    preview.contact_demo = mode == 4;
    preview.ledge_demo = mode == 5;
    preview.wall_demo = mode == 6;
    preview.map_mode = mode == 7 || mode == 8 || mode == 9;
    unsigned char starting_lives;
    unsigned short starting_max_roar = 16;
    if (engine_difficulty_counts(game_difficulty, &starting_lives, &preview.continues_remaining) != 0) {
        lk_platform_log("Lion King: invalid difficulty.\n");
        return 1;
    }
    if (level_number == 2 && next_level_state_valid) {
        starting_lives = next_level_lives;
        preview.continues_remaining = next_level_continues;
        starting_max_roar = next_level_max_roar;
        next_level_state_valid = 0;
    }
    if (preview.map_mode) {
        lk_platform_log(level_number == 1 ? "LEVEL1 gameplay resources.\n" :
            "LEVEL2 gameplay resources.\n");
        if (frontend_prepare_continue(&resource_api, palette) != 0) return 1;
        if (resources_load_entry(&resource_api, "LIONKING.EPF", "GAMEOVER.MCH",
            packed, sizeof(game_buffers->packed), game_over_sprites, sizeof(game_buffers->game_over_sprites),
            &dictionary, &game_over_size) != 0) {
            lk_platform_log("Lion King: cannot load original GAMEOVER artwork.\n");
            return 1;
        }
        unsigned int loaded_hud;
        if (resources_load_entry(&resource_api, "LIONKING.EPF", "BARS.MCH",
            packed, sizeof(game_buffers->packed), hud_sprites, sizeof(game_buffers->hud_sprites),
            &dictionary, &loaded_hud) != 0) {
            lk_platform_log("Lion King: cannot load original status artwork.\n");
            return 1;
        }
        banks[1] = (RENDER_SPRITE_BANK){hud_sprites, loaded_hud};
        if (loading_progress(3 + ASSETS_YOUNG_BANK_COUNT) != 0) return 1;
        for (unsigned int index = 0; index < 15; ++index) {
            const unsigned char *list = index < 11 ? animation_common_sound_list :
                animation_level1_sound_list;
            unsigned int size = index < 11 ? sizeof(animation_common_sound_list) :
                sizeof(animation_level1_sound_list);
            unsigned int slot;
            char name[13];
            if (assets_slot_list_name(list, size, index < 11 ? index : index-11,
                &slot, name) != 0 || slot >= 19 ||
                resources_load_entry(&resource_api, "LIONKING.EPF", name, packed,
                    sizeof(game_buffers->packed), effect_samples[slot], sizeof(effect_samples[slot]),
                    &dictionary, &effect_sizes[slot]) != 0) {
                lk_platform_log("Lion King: cannot load gameplay sound samples.\n");
                return 1;
            }
            if (loading_progress(4 + ASSETS_YOUNG_BANK_COUNT + index) != 0) return 1;
        }
        unsigned int contour_size;
        if (resources_load_entry(&resource_api, "LIONKING.EPF", "CONTOUR.CON",
            packed, sizeof(game_buffers->packed), map_contours, sizeof(game_buffers->map_contours),
            &dictionary, &contour_size) != 0 ||
            engine_map_collision_initialize(&preview.collision, map, map_size,
                map_contours, contour_size) != 0) {
            lk_platform_log("Lion King: cannot initialize real map collision.\n");
            return 1;
        }
        preview.map_spawn_x = 65;
        preview.map_spawn_y = level_number == 1 ? 1255 : 398;
        preview.manual = 1;
        if (loading_progress(19 + ASSETS_YOUNG_BANK_COUNT) != 0) return 1;
    }
    preview.fixture_floor = 160;
    preview.air.player.body.render_pool = &render_pool;
    preview.air.player.body.node = render_acquire_node(&render_pool,
        &preview.air.player.body.owner, 0, 0,
        animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    preview.object = engine_acquire_object(&scene_objects, 0);
    preview.air.player.probe = preview_player_probe;
    preview.air.player.transition = preview_player_transition;
    preview.air.player.context = &preview;
    preview.air.player.collision_flags = &preview.collision_flags;
    preview.air.ground = preview_player_ground;
    preview.air.edge = preview_player_edge;
    preview.air.transition = preview_player_landed;
    preview.air.sound = preview_player_sound;
    preview.air.support = preview_player_support;
    preview.air.animation_event = record_player_idle_event;
    preview.air.damage_source = preview.map_mode ? 0 : &preview.damage_source;
    preview.air.contact = preview_player_contact;
    preview.air.ledge_height = preview_ledge_height;
    preview.air.health = preview.map_mode ? 4 : 100;
    preview.air.roar_charge = preview.map_mode ? 0 : 100;
    if (!preview.air.player.body.node || !preview.object || begin_player_preview(&preview) != 0) {
        lk_platform_log("Lion King: cannot initialize original player deflection.\n");
        return 1;
    }
    if (preview.map_mode) {
        preview.camera.horizontal_offset = 128;
        preview.camera.position = (RENDER_OWNER){
            (short)(preview.air.player.body.owner.x - 128),
            (short)(preview.air.player.body.owner.y - 128)};
        RENDER_VIEWPORT viewport;
        if (render_prepare_viewport(&preview.camera.position, preview.collision.width,
            preview.collision.height, 0, &viewport) != 0) {
            lk_platform_log("Lion King: cannot initialize map follow camera.\n");
            return 1;
        }
        unsigned int enemy_bank_count = level_number == 1 ? 18 : 21;
        const unsigned char *enemy_bank_list = level_number == 1 ?
            animation_level1_bank_list : animation_level2_bank_list;
        unsigned int enemy_bank_list_size = level_number == 1 ?
            sizeof(animation_level1_bank_list) : sizeof(animation_level2_bank_list);
        for (unsigned int i = 0; i < enemy_bank_count; ++i) {
            unsigned int slot, loaded;
            if (assets_load_named_bank(&resource_api, "LIONKING.EPF", enemy_bank_list,
                enemy_bank_list_size, i, packed, sizeof(game_buffers->packed),
                enemy_sprites[i], sizeof(enemy_sprites[i]), &dictionary, &slot, &loaded) != 0 ||
                slot != (level_number == 1 ? 62U + i : 106U + i)) {
                lk_platform_log(level_number == 1 ?
                    "Lion King: cannot load original LEVEL1 enemy banks.\n" :
                    "Lion King: cannot load original LEVEL2 enemy banks.\n");
                return 1;
            }
            banks[slot] = (RENDER_SPRITE_BANK){enemy_sprites[i], loaded};
            if (loading_progress(20 + ASSETS_YOUNG_BANK_COUNT + i) != 0) return 1;
        }
        static const unsigned int common_indices[5] = {0, 2, 8, 12, 13};
        for (unsigned int i = 0; i < 5; ++i) {
            unsigned int slot, loaded;
            if (assets_load_named_bank(&resource_api, "LIONKING.EPF", animation_common_bank_list,
                sizeof(animation_common_bank_list), common_indices[i], packed, sizeof(game_buffers->packed),
                pickup_sprites[i], sizeof(pickup_sprites[i]), &dictionary, &slot, &loaded) != 0 ||
                slot != 81 + common_indices[i]) {
                lk_platform_log("Lion King: cannot load original LEVEL1 pickup/checkpoint banks.\n");
                return 1;
            }
            banks[slot] = (RENDER_SPRITE_BANK){pickup_sprites[i], loaded};
            if (loading_progress(38 + ASSETS_YOUNG_BANK_COUNT + i) != 0) return 1;
        }
        if (engine_enemies_initialize(&map_enemies, &scene_objects, &render_pool,
            &preview.collision, &preview.air) != 0) {
            lk_platform_log(level_number == 1 ?
                "Lion King: invalid LEVEL1 enemy marker plane.\n" :
                "Lion King: invalid LEVEL2 enemy marker plane.\n");
            return 1;
        }
        map_enemies.sound = preview_enemy_sound;
        map_enemies.difficulty = game_difficulty;
        if (engine_level_life_initialize(&preview.life, &preview.air, preview.object, starting_lives) != 0 ||
            engine_pickups_initialize(&map_pickups, &scene_objects, &render_pool,
            &preview.collision, &preview.air, preview.air.health,
            starting_max_roar, &preview.life.lives, &preview.continues_remaining) != 0) {
            lk_platform_log(level_number == 1 ?
                "Lion King: invalid LEVEL1 pickup marker plane.\n" :
                "Lion King: invalid LEVEL2 pickup marker plane.\n");
            return 1;
        }
        if (mode == 8) {
            preview.life.game_over = 1;
            preview.life.lives = 0;
            preview.air.health = 0;
            lk_platform_log("Continue test: starting directly in the countdown state.\n");
        }
    }
    if (preview.ground_mode) {
        if (preview.map_mode) {
            lk_platform_log("Real LEVEL1.MAP collision and CONTOUR.CON are active.\n"
                "Left/Right: move; Space: jump; Down: crouch/roll; Ctrl: roar; Escape: exit.\n"
                "Floor, slopes, landing and edge queries use map planes, not a fixed Y.\n"
                "Original LEVEL1 descriptor starting position X65/Y1255 is active.\n"
                "Lateral contacts mask movement before each tick; ceiling probes use animation geometry.\n"
                "Original LEVEL1 parallax and foreground/object layer order are active.\n"
                "Original lizard/porcupine/beetle movement/roar/contact/removal and leaf markers are active.\n"
                "Original healing/upgrades/checkpoint and special collectible markers are active.\n"
                "Normal starting health 4, roar capacity 16 and 3 lives; roar recharges from zero.\n"
                "Checkpoint/death/restart, BARS HUD, PCM effects, hyena and completion are active.\n"
                "Synthetic contact controls are disabled; no diagnostic text is rendered.\n");
        } else {
            lk_platform_log("Original Simba ground test: idle -> run -> turn -> jump -> land -> run.\n"
            "Left/Right: run; Down: crouch; Space: jump/hold; Ctrl: roar. Escape: exit.\n"
            "H: diagnostic hit/recoil; T: diagnostic terrain contact (6/9/5/8).\n"
            "B: contact rebound; R: thrown launch; F: tether target then release (fixtures).\n"
            "--contacts: automatic rebound both ways, launch and tether demonstration.\n"
            "K: ledge grab alternating sides; Up: climb; Down: drop; P: supported turn/jump.\n"
            "--ledges: automatic grabs, climbs and drops in both directions.\n"
            "W: wall grip alternating sides; Space: leap; Down: detach after grab delay.\n"
            "--walls: opposite catches, free leaps, ledge transfers and detaches.\n"
            "Ground Y=160, damage source, terrain, initial meters and camera are fixtures.\n"
            "Enemy response to roar, meter recharge/immunity ticking and map collision unported.\n");
            lk_platform_log(preview.wall_demo ?
            "Before input: both wall catches -> free leaps -> ledge climbs -> detaches.\n" : preview.ledge_demo ?
            "Before input: left/right ledge climb -> left/right ledge drop.\n" : preview.contact_demo ?
            "Before input: right/left rebounds -> thrown launch -> tether/release.\n" :
            "Before input: running/jumping/roaring/damage demo. --jump: previous jump fixture.\n");
        }
    } else if (preview.jump) {
        lk_platform_log("Original Simba jump test: ascent -> air -> landing, repeatable.\n"
            "Space: take control/jump; hold for height. Left/Right: direction. Escape: exit.\n"
            "Before Space: automatic short/held jump demo. --flight: previous flip scene.\n"
            "Ground Y=160, idle/input, no ceiling/edges and demo restarts are fixtures.\n"
            "Ground locomotion and level collision are not yet migrated.\n");
    } else if (flight) {
        lk_platform_log("Original Simba flight test: deflection -> air -> landing selector.\n"
            "Left/Right: airborne direction. Escape: exit. --emitters: previous rock scene.\n"
            "Ground Y=160, probe results and restarts are fixtures, not level collision.\n");
    }
    if (!flight) {
        lk_platform_log("Original Simba deflection test: --deflection, Escape exits.\n");
    }
    if (!preview.jump && !preview.ground_mode) {
        lk_platform_log("Eight automatic fixture cases: both selectors, both script ranges, probe off/on.\n"
            "Original motion and visual scripts; probe results and restarts are diagnostic.\n");
    }
    if (preview.map_mode) {
        unsigned int music_size;
        if (resources_load_entry(&resource_api, "LIONKING.EPF",
            level_number == 1 ? "LION1.AMF" : "LION2.AMF",
            packed, sizeof(game_buffers->packed), level_music, sizeof(game_buffers->level_music),
            &dictionary, &music_size) != 0 ||
            (music_enabled ? music_initialize(&music_player, level_music, music_size) :
                music_effects_initialize(&music_player)) != 0) {
            lk_platform_log(level_number == 1 ?
                "Lion King: invalid or unsupported LEVEL1 AMF music.\n" :
                "Lion King: invalid or unsupported LEVEL2 AMF music.\n");
            return 1;
        }
        preview.level_music_size = music_size;
        if ((music_enabled || sound_enabled) && music_output_open(&music_output, &music_player, api) != 0) {
            lk_platform_log(level_number == 1 ?
                "Lion King: LEVEL1 music requires a usable DOS64 audio output.\n" :
                "Lion King: LEVEL2 music requires a usable DOS64 audio output.\n");
            return 1;
        }
        lk_platform_log(music_enabled ?
            (level_number == 1 ?
                "LEVEL1 music: original LION1.AMF samples, 44100 Hz stereo, looping.\n" :
                "LEVEL2 music: original LION2.AMF samples, 44100 Hz stereo, looping.\n") :
            (sound_enabled ? "LEVEL1 music muted; sound effects enabled.\n" :
                "LEVEL1 music and effects muted by menu selection.\n"));
        if (loading_progress(43 + ASSETS_YOUNG_BANK_COUNT) != 0) return 1;
        if (menu_active) preview.level_title_ticks = 100;
        if (mode == 8 && preview_map_life(&preview) < 0) {
            lk_platform_log("Lion King: cannot start continue test.\n");
            return 1;
        }
    }
    VGA_FRAME frame = {pixels, sizeof(game_buffers->pixels), 0, palette, present_frame, 0};
    unsigned long long begin = lk_platform_time_ns();
    preview.jump_begin = begin;
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, begin);
    ENGINE_CLOCK death_palette_clock;
    engine_clock_reset(&death_palette_clock, begin);
    lk_platform_profile_enable(1);
    for (;;) {
        lk_platform_poll();
        if (preview.life.game_over && !preview.continue_accept_ticks) {
            if (api->Input.KeyPressed[0x50]) preview.continue_no = 0;
            if (api->Input.KeyPressed[0x4f]) preview.continue_no = 1;
            if (api->Input.KeyPressed[0x2c] || api->Input.KeyPressed[0x28])
                preview.continue_pressed = 1;
        }
        if (preview.ground_mode) {
            unsigned short taps = (api->Input.KeyPressed[game_controls.keys[CONTROL_LEFT]] ? 4 : 0) |
                (api->Input.KeyPressed[game_controls.keys[CONTROL_RIGHT]] ? 8 : 0) |
                (api->Input.KeyPressed[game_controls.keys[CONTROL_JUMP]] ? 0x20 : 0) |
                (api->Input.KeyPressed[game_controls.keys[CONTROL_DOWN]] ? 2 : 0) |
                (api->Input.KeyPressed[game_controls.keys[CONTROL_UP]] ? 1 : 0) |
                ((api->Input.KeyPressed[game_controls.keys[CONTROL_ROAR]] ||
                    (preview_alternate_roar() && api->Input.KeyPressed[0xe4])) ? 0x40 : 0) |
                (api->Input.KeyPressed[0x0b] ? 0x100 : 0) |
                (api->Input.KeyPressed[0x17] ? 0x200 : 0) |
                (api->Input.KeyPressed[0x05] ? 0x400 : 0) |
                (api->Input.KeyPressed[0x15] ? 0x800 : 0) |
                (api->Input.KeyPressed[0x09] ? 0x1000 : 0) |
                (api->Input.KeyPressed[0x0e] ? 0x2000 : 0) |
                (api->Input.KeyPressed[0x13] ? 0x4000 : 0) |
                (api->Input.KeyPressed[0x1a] ? 0x8000 : 0);
            if (taps || api->Input.KeyDown[game_controls.keys[CONTROL_LEFT]] ||
                api->Input.KeyDown[game_controls.keys[CONTROL_RIGHT]] ||
                api->Input.KeyDown[game_controls.keys[CONTROL_JUMP]] ||
                api->Input.KeyDown[game_controls.keys[CONTROL_DOWN]] ||
                api->Input.KeyDown[game_controls.keys[CONTROL_UP]] ||
                api->Input.KeyDown[game_controls.keys[CONTROL_ROAR]] ||
                (preview_alternate_roar() && api->Input.KeyDown[0xe4])) {
                preview.manual = 1;
            }
            preview.input_taps |= taps;
        }
        if (preview.jump && api->Input.KeyPressed[0x2c]) {
            preview.manual = 1;
            preview.jump_requested = preview.completed;
        }
        if (lk_platform_exit_requested()) {
            break;
        }
        unsigned long long stage_begin = lk_platform_time_ns();
        if (preview.map_mode && music_output.opened &&
            music_output_service(&music_output) != 0) {
            lk_platform_log("Lion King: LEVEL1 audio streaming failed.\n");
            return 1;
        }
        if (preview.life.game_over && frontend_service_continue() != 0) return 1;
        lk_platform_profile_record(LK_PROFILE_AUDIO, stage_begin);
        unsigned long long now = lk_platform_time_ns();
        unsigned long long palette_ticks;
        if (engine_clock_elapsed_ticks(&death_palette_clock, now, &palette_ticks) != 0) {
            lk_platform_log("Lion King: invalid lost-life palette clock.\n");
            return 1;
        }
        for (unsigned long long i = 0; i < palette_ticks && fade.active; ++i) {
            if (vga_fade_tick(&fade) < 0) {
                lk_platform_log("Lion King: lost-life palette fade failed.\n");
                return 1;
            }
        }
        if (vga_palette_colors(fade.current, palette) != 0) {
            lk_platform_log("Lion King: invalid lost-life palette.\n");
            return 1;
        }
        if (!preview.jump && !preview.ground_mode && preview.completed &&
            now - begin >= (flight ? 2000000000ULL : 1000000000ULL)) {
            preview.variant = (preview.variant + 1) & 7;
            begin = now;
            if (begin_player_preview(&preview) != 0) {
                lk_platform_log("Lion King: cannot restart player deflection fixture.\n");
                return 1;
            }
        }
        unsigned short camera_x = 0, camera_y = 0;
        if (preview.ground_mode) {
            RENDER_OWNER camera;
            if (preview_camera(&preview, &camera) != 0) {
                lk_platform_log("Lion King: cannot prepare player viewport.\n");
                return 1;
            }
            camera_x = (unsigned short)camera.x;
            camera_y = (unsigned short)camera.y;
            if (!preview.life.dying) preview.air.player.body.node->flags |= 0x40;
        }
        unsigned char *view = pixels + LK_WIDTH;
        int dim_phase;
        stage_begin = lk_platform_time_ns();
        if (render_player_opacity_frame(&preview, map_size, camera_x, camera_y,
                banks, view, &dim_phase) != 0) {
            lk_platform_log("Lion King: cannot render player opacity layers.\n");
            return 1;
        }
        lk_platform_profile_record(LK_PROFILE_RENDER, stage_begin);
        frame.context = dim_phase ? hurt_layer : 0;
        if (vga_present_frame(&frame) != 0) {
            lk_platform_log("Lion King: cannot render player deflection preview.\n");
            return 1;
        }
        stage_begin = lk_platform_time_ns();
        if (engine_dispatch_ticks(&clock, now, update_player_preview, &preview) < 0 ||
            preview.failed) {
            lk_platform_log("Lion King: original player deflection preview failed.\n");
            return 1;
        }
        lk_platform_profile_record(LK_PROFILE_LOGIC, stage_begin);
        if (preview.map_mode && preview.completed &&
            (preview.life.game_over || preview.life.complete)) break;
    }
    lk_platform_profile_enable(0);
    frontend_stop_continue();
    lk_platform_log(preview.ground_mode ? "Original player ground preview finished.\n" :
        preview.jump ? "Original player jump preview finished.\n" :
        flight ? "Original player flight preview finished.\n" :
        "Original player deflection preview finished.\n");
    if (preview.map_mode) {
        log_map_measurement("Lizard map markers: ", map_enemies.lizard_count);
        log_map_measurement("Porcupine map markers: ", map_enemies.porcupine_count);
        log_map_measurement("Beetle map markers: ", map_enemies.beetle_count);
        log_map_measurement("Leaf map markers: ", map_enemies.leaf_marker_count);
        log_map_measurement("Hyena map markers: ", map_enemies.hyena_count);
        log_map_measurement("Hyenas defeated: ", map_enemies.hyenas_defeated);
        log_map_measurement("Level completed: ", preview.life.complete);
        log_map_measurement("Leaves spawned: ", map_enemies.leaves_spawned);
        log_map_measurement("Enemy spawns: ", map_enemies.spawned);
        log_map_measurement("Enemy culls: ", map_enemies.culled);
        log_map_measurement("Lizard attacks: ", map_enemies.attacks);
        log_map_measurement("Enemy turns: ", map_enemies.turns);
        log_map_measurement("Enemy obstacle jumps: ", map_enemies.jumps);
        log_map_measurement("Enemy roar stuns: ", map_enemies.stuns);
        log_map_measurement("Enemy contacts: ", map_enemies.contacts);
        log_map_measurement("Enemy defeats: ", map_enemies.defeated);
        log_map_measurement("Pickup map markers: ", map_pickups.count);
        log_map_measurement("Pickups collected: ", map_pickups.collected);
        log_map_measurement("Pickup upgrades completed: ", map_pickups.upgrades);
        log_map_measurement("Checkpoints activated: ", map_pickups.checkpoints);
        log_map_measurement("Bonus collectibles: ", map_pickups.bonus_count);
        log_map_measurement("Bonus selected: ", map_pickups.bonus_selected);
        log_map_measurement("Player lives remaining: ", preview.life.lives);
        log_map_measurement("Player world X: ", (unsigned short)preview.air.player.body.owner.x);
        log_map_measurement("Player deaths: ", preview.life.deaths);
        log_map_measurement("Player checkpoint restarts: ", preview.life.restarts);
        log_map_measurement("Player health remaining: ", (unsigned int)preview.air.health);
        log_map_measurement("Music submitted frames: ", (unsigned int)music_output.submitted);
        log_map_measurement("Music tracker rows: ", music_player.rows_played);
        log_map_measurement("Music completed loops: ", music_player.loops);
        log_map_measurement("Map supported queries: ", preview.map_contacts);
        log_map_measurement("Map contour height adjustments: ", preview.map_height_changes);
        log_map_measurement("Map landing transitions: ", preview.map_landings);
        log_map_measurement("Map edge contacts: ", preview.map_edge_contacts);
        log_map_measurement("Map left blocked ticks: ", preview.map_left_blocks);
        log_map_measurement("Map right blocked ticks: ", preview.map_right_blocks);
        log_map_measurement("Map ceiling hits: ", preview.map_ceiling_hits);
        log_map_measurement("Map final X: ", (unsigned short)preview.air.player.body.owner.x);
        log_map_measurement("Map final Y: ", (unsigned short)preview.air.player.body.owner.y);
    }
    if (preview.map_mode && preview.life.complete) {
        music_output_stop(&music_output);
        if (level_number == 2) {
            lk_platform_log("LEVEL2: end of playable map reached; returning to menu.\n");
            return 0;
        }
        if (frontend_victory(api, &resource_api, sound_enabled) != 0) return 1;
        if (map_pickups.bonus_selected) {
            int bonus_result = run_bonus_toss_game(api, &preview.life.lives,
                &preview.continues_remaining, &map_pickups.max_roar);
            if (bonus_result == 1) return 1;
            if (bonus_result == 2) return 0;
        }
        return start_level_two(api, &preview.life.lives,
            &preview.continues_remaining, &map_pickups.max_roar);
    }
    return 0;
}

int run_level_two(const DOS64_API *api, unsigned char *lives,
    unsigned int *continues, unsigned short *max_roar)
{
    if (!api || !lives || *lives > 9 || !continues || *continues > 9 ||
        !max_roar || *max_roar < 16 || *max_roar > 48) {
        lk_platform_log("Lion King: invalid LEVEL2 carry-over state.\n");
        return 1;
    }
    next_level_lives = *lives;
    next_level_continues = *continues;
    next_level_max_roar = *max_roar;
    next_level_state_valid = 1;
    lk_platform_log("Transition: starting LEVEL2.\n");
    return run_deflection_preview(api, 9);
}
