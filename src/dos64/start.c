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
static unsigned char map_contours[4096];
static unsigned char sprite[32768];
static RESOURCE_DICTIONARY dictionary;
static RENDER_POOL render_pool;
static VGA_FADE fade;
static unsigned char level_rgb[768];
static const unsigned char black_rgb[768];
static unsigned char idle_sprites[3][32768];
static unsigned char player_sprites[ASSETS_YOUNG_BANK_COUNT][32768];
static ENGINE_OBJECT_POOL scene_objects;
static ENGINE_EMITTER_GROUP scene_emitters;
static int scene_failed;
/* Resource errors use the file logger; input keeps the live runtime table. */
static DOS64_API resource_api;

static void __attribute__((ms_abi)) log_resource_message(const char *text)
{
    lk_platform_log(text);
}

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

static int log_idle_event(unsigned int target)
{
    if (target != 0x20bec && target != 0x20c70 &&
        target != 0x20d55 && target != 0x20cf4) {
        lk_platform_log("Lion King: unknown idle animation event.\n");
        return -1;
    }
    lk_platform_log("Idle script event recorded; game object side effects not executed in preview.\n");
    return 0;
}

static void log_map_measurement(const char *label, unsigned int value)
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

static int record_preview_event(void *context, unsigned int target)
{
    PREVIEW_ANIMATION *animation = context;
    if (log_idle_event(target) != 0) {
        return -1;
    }
    ++animation->events;
    return 0;
}

static int record_player_idle_event(void *context, unsigned int target)
{
    (void)context;
    return log_idle_event(target);
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
    ENGINE_MAP_COLLISION collision;
    short map_spawn_y;
    unsigned int map_contacts;
    unsigned int map_height_changes;
    unsigned int map_landings;
    unsigned int map_edge_contacts;
    unsigned long long jump_begin;
} DEFLECTION_PREVIEW;

static int preview_player_contact(void *context, short *touching)
{
    DEFLECTION_PREVIEW *preview = context;
    *touching = preview->fixture_touching;
    return 0;
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
    (void)context;
    if (sample != 0 && (sample < 2 || sample > 6)) {
        lk_platform_log("Lion King: unexpected player sound.\n");
        return -1;
    }
    lk_platform_log(sample == 0 ?
        "Original rebound sample 0 requested; audio output unported.\n" : sample <= 3 ?
        "Original roar sample requested; audio output unported.\n" : sample <= 5 ?
        "Original recovery sample 4 requested; audio output unported.\n" :
        "Original roll sample 6 requested; audio output unported.\n");
    return 0;
}

static int preview_player_probe(void *context, short x, short y, short *hit)
{
    DEFLECTION_PREVIEW *preview = context;
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
        if (call->handler == 0xef04U) {
            if (preview->map_mode) {
                lk_platform_log("Lion King: map hazard damage/source handling is not migrated.\n");
                return -1;
            }
            lk_platform_log("Original damage/recoil handler selected; source is a test fixture.\n");
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
        if (preview->map_mode) preview->air.player.body.owner.y = preview->map_spawn_y;
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

static void update_player_preview(void *context)
{
    DEFLECTION_PREVIEW *preview = context;
    if (preview->ground_mode) {
        unsigned short held = (preview->api->Input.KeyDown[0x50] ? 4 : 0) |
            (preview->api->Input.KeyDown[0x4f] ? 8 : 0) |
            (preview->api->Input.KeyDown[0x2c] ? 0x20 : 0) |
            (preview->api->Input.KeyDown[0x51] ? 2 : 0) |
            (preview->api->Input.KeyDown[0x52] ? 1 : 0) |
            (preview->api->Input.KeyDown[0xe0] || preview->api->Input.KeyDown[0xe4] ? 0x40 : 0);
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
        if (engine_update_objects(&scene_objects, &preview->api->Input) != 0) {
            preview->failed = 1;
            return;
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

static int run_deflection_preview(const DOS64_API *api, int mode)
{
    int flight = mode != 0;
    unsigned int map_size;
    if (resources_load_entry(&resource_api, "LIONKING.EPF", "LEVEL1.MAP", packed, sizeof(packed),
        map, sizeof(map), &dictionary, &map_size) != 0 ||
        vga_load_palette(map, map_size, palette) != 0) {
        lk_platform_log("Lion King: cannot load player reaction preview map.\n");
        return 1;
    }
    RENDER_SPRITE_BANK banks[34] = {0};
    unsigned int count = flight ? ASSETS_YOUNG_BANK_COUNT : 2;
    for (unsigned int i = 0; i < count; ++i) {
        unsigned int slot, loaded;
        unsigned int index = flight ? i : 5 + i;
        if (assets_load_named_bank(&resource_api, "LIONKING.EPF", assets_young_bank_list,
            sizeof(assets_young_bank_list), index, packed, sizeof(packed),
            player_sprites[i], sizeof(player_sprites[i]), &dictionary, &slot, &loaded) != 0 ||
            slot != 6 + index) {
            lk_platform_log("Lion King: cannot load original flip banks.\n");
            return 1;
        }
        banks[slot] = (RENDER_SPRITE_BANK){player_sprites[i], loaded};
    }
    engine_initialize_objects(&scene_objects);
    render_initialize_nodes(&render_pool);
    DEFLECTION_PREVIEW preview = {0};
    preview.api = api;
    preview.flight = flight;
    preview.jump = mode == 2;
    preview.ground_mode = mode >= 3;
    preview.contact_demo = mode == 4;
    preview.ledge_demo = mode == 5;
    preview.wall_demo = mode == 6;
    preview.map_mode = mode == 7;
    if (preview.map_mode) {
        unsigned int contour_size;
        if (resources_load_entry(&resource_api, "LIONKING.EPF", "CONTOUR.CON",
            packed, sizeof(packed), map_contours, sizeof(map_contours),
            &dictionary, &contour_size) != 0 ||
            engine_map_collision_initialize(&preview.collision, map, map_size,
                map_contours, contour_size) != 0) {
            lk_platform_log("Lion King: cannot initialize real map collision.\n");
            return 1;
        }
        int found = 0;
        for (short y = 12; y < (int)preview.collision.height * 8; ++y) {
            ENGINE_MAP_GROUND ground;
            if (engine_map_ground(&preview.collision, 160, y, &ground) != 0) {
                lk_platform_log("Lion King: invalid map spawn query.\n");
                return 1;
            }
            if (ground.supported && !ground.delta_y) {
                preview.map_spawn_y = y;
                found = 1;
                break;
            }
        }
        if (!found) {
            lk_platform_log("Lion King: no supported preview start at map X160.\n");
            return 1;
        }
        preview.manual = 1;
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
    preview.air.health = 100;
    preview.air.roar_charge = 100;
    if (!preview.air.player.body.node || !preview.object || begin_player_preview(&preview) != 0) {
        lk_platform_log("Lion King: cannot initialize original player deflection.\n");
        return 1;
    }
    if (preview.ground_mode) {
        if (preview.map_mode) {
            lk_platform_log("Real LEVEL1.MAP collision and CONTOUR.CON are active.\n"
                "Left/Right: move; Space: jump; Down: crouch/roll; Escape: exit.\n"
                "Floor, slopes, landing and edge queries use map planes, not a fixed Y.\n"
                "Starting X160 is a preview choice; Y is found on the real contour.\n"
                "Ceiling and lateral blocking, dynamic map objects and hazards remain unported.\n"
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
    VGA_FRAME frame = {pixels, sizeof(pixels), 0, palette, present_frame, 0};
    unsigned long long begin = lk_platform_time_ns();
    preview.jump_begin = begin;
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, begin);
    for (;;) {
        lk_platform_poll();
        if (preview.ground_mode) {
            unsigned short taps = (api->Input.KeyPressed[0x50] ? 4 : 0) |
                (api->Input.KeyPressed[0x4f] ? 8 : 0) |
                (api->Input.KeyPressed[0x2c] ? 0x20 : 0) |
                (api->Input.KeyPressed[0x51] ? 2 : 0) |
                (api->Input.KeyPressed[0x52] ? 1 : 0) |
                (api->Input.KeyPressed[0xe0] || api->Input.KeyPressed[0xe4] ? 0x40 : 0) |
                (api->Input.KeyPressed[0x0b] ? 0x100 : 0) |
                (api->Input.KeyPressed[0x17] ? 0x200 : 0) |
                (api->Input.KeyPressed[0x05] ? 0x400 : 0) |
                (api->Input.KeyPressed[0x15] ? 0x800 : 0) |
                (api->Input.KeyPressed[0x09] ? 0x1000 : 0) |
                (api->Input.KeyPressed[0x0e] ? 0x2000 : 0) |
                (api->Input.KeyPressed[0x13] ? 0x4000 : 0) |
                (api->Input.KeyPressed[0x1a] ? 0x8000 : 0);
            if (taps || api->Input.KeyDown[0x50] || api->Input.KeyDown[0x4f] ||
                api->Input.KeyDown[0x2c] || api->Input.KeyDown[0x51] || api->Input.KeyDown[0x52] ||
                api->Input.KeyDown[0xe0] || api->Input.KeyDown[0xe4]) {
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
        unsigned long long now = lk_platform_time_ns();
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
            RENDER_OWNER camera = {
                preview.air.player.body.owner.x > 160 ?
                    (short)(preview.air.player.body.owner.x - 160) : 0,
                preview.map_mode && preview.air.player.body.owner.y > 120 ?
                    (short)(preview.air.player.body.owner.y - 120) : 0
            };
            RENDER_VIEWPORT viewport;
            if (render_prepare_viewport(&camera,
                (unsigned short)(map[8] | (unsigned int)map[9] << 8),
                (unsigned short)(map[12] | (unsigned int)map[13] << 8),
                0, &viewport) != 0) {
                lk_platform_log("Lion King: cannot prepare player viewport.\n");
                return 1;
            }
            camera_x = viewport.x;
            camera_y = viewport.y;
            preview.air.player.body.node->flags |= 0x40;
        }
        unsigned char *view = pixels + LK_WIDTH;
        for (unsigned int i = 0; i < LK_WIDTH * LK_HEIGHT; ++i) {
            view[i] = 0;
        }
        if (render_map_tile_pass(map, map_size, 0, camera_x, camera_y, 0, view) != 0 ||
            render_map_tile_pass(map, map_size, 0, camera_x, camera_y, 1, view) != 0 ||
            render_object_pass(&render_pool, 0, (short)-(int)camera_x, (short)-(int)camera_y,
                banks, 34, view) != 0 ||
            vga_present_frame(&frame) != 0) {
            lk_platform_log("Lion King: cannot render player deflection preview.\n");
            return 1;
        }
        if (engine_dispatch_ticks(&clock, now, update_player_preview, &preview) < 0 ||
            preview.failed) {
            lk_platform_log("Lion King: original player deflection preview failed.\n");
            return 1;
        }
        lk_platform_sleep(10);
    }
    lk_platform_log(preview.ground_mode ? "Original player ground preview finished.\n" :
        preview.jump ? "Original player jump preview finished.\n" :
        flight ? "Original player flight preview finished.\n" :
        "Original player deflection preview finished.\n");
    if (preview.map_mode) {
        log_map_measurement("Map supported queries: ", preview.map_contacts);
        log_map_measurement("Map contour height adjustments: ", preview.map_height_changes);
        log_map_measurement("Map landing transitions: ", preview.map_landings);
        log_map_measurement("Map edge contacts: ", preview.map_edge_contacts);
        log_map_measurement("Map final X: ", (unsigned short)preview.air.player.body.owner.x);
        log_map_measurement("Map final Y: ", (unsigned short)preview.air.player.body.owner.y);
    }
    return 0;
}

static int run_emitter_scene(const DOS64_API *api)
{
    unsigned int map_size, loaded, slot;
    if (resources_load_entry(&resource_api, "LIONKING.EPF", "LEVEL6.MAP", packed, sizeof(packed),
        map, sizeof(map), &dictionary, &map_size) != 0 ||
        vga_load_palette(map, map_size, palette) != 0 ||
        assets_load_named_bank(&resource_api, "LIONKING.EPF", animation_level6_bank_list,
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

static int run_preview(const DOS64_API *api)
{
    if (!api->Arguments) {
        lk_platform_log("Lion King: missing runtime argument string.\n");
        return 1;
    }
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
    if (argument_requested(api->Arguments, "--map")) {
        return run_deflection_preview(api, 7);
    }
    if (!argument_requested(api->Arguments, "--idle") &&
        !argument_requested(api->Arguments, "--manual") &&
        !argument_requested(api->Arguments, "--selftest")) {
        return run_deflection_preview(api, 3);
    }
    LK_EPF_INFO archive;
    if (resources_open_archive(&resource_api, "LIONKING.EPF", &archive) != 0) {
        return 1;
    }
    lk_platform_log("Lion King: EPF index and payload bounds verified.\n");
    unsigned int loaded;
    if (resources_load_entry(&resource_api, "LIONKING.EPF", "LEVEL1.MAP", packed, sizeof(packed),
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
    VGA_FRAME frame = {pixels, sizeof(pixels), 0, palette, present_frame, 0};
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
        lk_platform_sleep(10);
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
    return lk_platform_finish(run_preview(api));
}
