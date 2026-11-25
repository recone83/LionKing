#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "mock_layers.h"
#include "dos64/platform.h"
#include "dos64/frontend.h"
#include "engine/behaviors.h"
#include "engine/animation_data.h"
#include "engine/assets.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "engine/timing.h"
#include "libs/vga.h"

int __attribute__((ms_abi)) start(const DOS64_API *api);
static DOS64_API api;
static ENGINE_OBJECT_POOL objects;
static ENGINE_EMITTER_GROUP emitters;
static ENGINE_SHAKE_OBJECT shake;
static ENGINE_MOTION player_motion;
static unsigned short camera_shake, immunity, player_flags;
static RENDER_POOL renders;
static RENDER_OWNER camera = {3400, 380};
static RENDER_BOUNDS visibility = {3272, 252, 3848, 580};
static unsigned char packed[79311], map[580488], sprite[32768], pixels[64000], background[64000];
static RESOURCE_DICTIONARY dictionary;
static RENDER_SPRITE_BANK banks[161];
static DOS64_COLOR palette[256];
static unsigned long long now, verified;
static unsigned long long cycle_begin;
static unsigned int iteration, map_size, shown, changed, object_frames, activation;
static unsigned int shake_frames, shake_pixels;
static ENGINE_CLOCK clock;
static int deflection_test, flight_test, player_completed, airborne;
static int steering_test;
static int jump_test, jump_manual, jump_steering;
static int jump_requested;
static unsigned long long jump_begin;
static unsigned int jump_count, jump_logs, ready_logs;
static short jump_min_y[16];
static unsigned int idle_events, idle_logs;
static int ground_test, ground_steering, ground_manual;
static unsigned short ground_taps;
static unsigned int ground_logs, run_frames, turn_frames, idle_frames, scroll_frames;
static unsigned int ground_jumps, ground_jump_logs;
static short min_world_x = 160, max_world_x = 160;
static RENDER_OWNER damage_source;
static int demo_hit;
static unsigned int action_frames, roar_sounds, damage_sounds;
static int map_test;
static int map_animation;
static int map_lifecycle;
static int map_gameover;
static int continue_test;
static unsigned int continue_started, continue_accepted, continue_frames;
static unsigned int exhausted_started, exhausted_frames, accept_animation_frames;
static unsigned int continue_speech_iteration;
static DOS64_COLOR countdown_first[20 * 8];
static int countdown_changed;
static unsigned int selector_left_frames, selector_right_frames;
static unsigned char continue_reference[64000];
static unsigned char gameover_reference[64000];
static DOS64_COLOR continue_palette[256];
static DOS64_COLOR continue_level_palette[256], gameover_palette[256];
static unsigned char continue_title[2701], continue_rafiki[50205];
static unsigned char continue_digits[1826], continue_marker[4096];
static unsigned char continue_circle[2653];
static unsigned char continue_gameover[4096];
static unsigned int continue_title_size, continue_rafiki_size, continue_digits_size, continue_marker_size;
static unsigned int continue_circle_size;
static unsigned int continue_gameover_size;
static unsigned int gameover_iteration;
static unsigned int restart_iteration;
static unsigned int map_deaths, map_restarts, map_lives, map_collected;
static unsigned int stomp_jump;
static unsigned int enemy_damage_logs, map_stuns, map_defeats, map_contacts;
static unsigned int rebound_logs;
static unsigned int stable_background_frames, animation_roar_logs;
static unsigned int map_spawns, map_jumps;
static unsigned long long audio_written, audio_energy, audio_queued, audio_time;
static unsigned long long continue_audio_start, continue_energy_start;
static unsigned int audio_stops;
static int audio_opened;
static DOS64_COLOR previous_map_frame[64000];

static int idle_event(void *context, unsigned int target)
{
    (void)context;
    assert(target == 0x20bec || target == 0x20c70 || target == 0x20d55 || target == 0x20cf4);
    ++idle_events;
    return 0;
}
static ENGINE_PLAYER_AIR player_air;
static ENGINE_PLAYER_DEFLECTION *player = &player_air.player;
static ENGINE_OBJECT *player_object;
static unsigned int player_variant, player_transitions, player_logs, moving_frames;
static unsigned int flight_transitions, flight_logs, airborne_frames;
static unsigned int direction_changes;
static unsigned int variant_frames[8];
static unsigned char player_collision_flags, flip_sprites[ASSETS_YOUNG_BANK_COUNT][32768];
static RENDER_OWNER previous_player_position;
static void record_log(const char *text)
{
    if (strstr(text, "continue countdown started")) {
        ++continue_started;
        continue_audio_start = audio_written;
        continue_energy_start = audio_energy;
    }
    if (strstr(text, "continue accepted")) ++continue_accepted;
    if (strstr(text, "Continue: SPEECH2 on both original channels"))
        continue_speech_iteration = iteration;
    if (strstr(text, "continue accepted")) restart_iteration = iteration;
    if (strstr(text, "no continues remaining; GAME OVER started")) {
        ++exhausted_started;
        gameover_iteration = iteration;
    }
    if (strstr(text, "continue countdown started")) gameover_iteration = iteration;
    if (strstr(text, "restarted at the saved checkpoint.")) restart_iteration = iteration;
    if (strstr(text, "failed") || strstr(text, "invalid") || strstr(text, "cannot")) {
        fputs(text, stderr);
    }
    assert(!strstr(text, "failed") && !strstr(text, "invalid") && !strstr(text, "cannot"));
    if (strstr(text, "test activation enabled")) {
        ++activation;
    }
    if (strstr(text, "Player deflection reached unported next state")) {
        ++player_logs;
    }
    if (strstr(text, "Player flight landed through original selector")) {
        ++flight_logs;
    }
    if (strstr(text, "Original player jump started.")) {
        ++jump_logs;
    }
    if (strstr(text, "Player jump reached ground boundary")) {
        ++ready_logs;
    }
    if (strstr(text, "Idle script event recorded")) ++idle_logs;
    if (strstr(text, "Original player ground handler selected")) ++ground_logs;
    if (strstr(text, "Original running/standing jump selected")) ++ground_jump_logs;
    if (strstr(text, "damage/recoil handler selected from a real enemy contact"))
        ++enemy_damage_logs;
    if (strstr(text, "Original rebound sample 0 requested")) {
        if (stomp_jump) assert(enemy_damage_logs == 0);
        ++rebound_logs;
    }
    if (strstr(text, "Original roar sample requested")) ++animation_roar_logs;
}
static void __attribute__((ms_abi)) log_text(const char *text)
{
    fputs(text, stderr);
    assert(!"preview must not render console text");
}
static FILE *log_file;
static unsigned int map_counter(const char *text, const char *label)
{
    const char *value = strstr(text, label);
    unsigned int counter;
    assert(value && sscanf(value + strlen(label), "%u", &counter) == 1);
    return counter;
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    if (strcmp(path, "LIONKING.LOG") == 0) {
        assert(strcmp(mode, "w") == 0 && !log_file);
        log_file = tmpfile();
        assert(log_file);
        return log_file;
    }
    assert(strcmp(path, "LIONKING.EPF") == 0);
    return fopen("data/LIONKING.EPF", mode);
}
static int __attribute__((ms_abi)) close_file(void *file)
{
    if (map_test && file == log_file) {
        char text[32768];
        assert(fseek(file, 0, SEEK_SET) == 0);
        size_t count = fread(text, 1, sizeof(text) - 1, file);
        assert(count < sizeof(text) - 1);
        text[count] = 0;
        assert(map_counter(text, "Lizard map markers: ") == 14);
        assert(map_counter(text, "Porcupine map markers: ") == 5);
        assert(map_counter(text, "Beetle map markers: ") == 4);
        assert(map_counter(text, "Leaf map markers: ") == 9);
        assert(map_counter(text, "Hyena map markers: ") == 1);
        assert(map_counter(text, "Pickup map markers: ") == 14);
        map_deaths = map_counter(text, "Player deaths: ");
        map_restarts = map_counter(text, "Player checkpoint restarts: ");
        map_lives = map_counter(text, "Player lives remaining: ");
        map_collected = map_counter(text, "Pickups collected: ");
        map_spawns = map_counter(text, "Enemy spawns: ");
        map_stuns = map_counter(text, "Enemy roar stuns: ");
        map_defeats = map_counter(text, "Enemy defeats: ");
        map_contacts = map_counter(text, "Enemy contacts: ");
        map_jumps = map_counter(text, "Map landing transitions: ");
    }
    if (file == log_file) log_file = 0;
    return fclose(file);
}
static unsigned long long __attribute__((ms_abi)) write_file(const void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    assert(file == log_file && size == 1);
    record_log(buffer);
    return fwrite(buffer, (size_t)size, (size_t)count, file);
}
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{ return fseek(file, (long)offset, whence); }
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{ return fread(buffer, (size_t)size, (size_t)count, file); }
static void __attribute__((ms_abi)) sleep_ms(unsigned int ms) { (void)ms; assert(0); }
static unsigned long long __attribute__((ms_abi)) time_ns(void) { return now; }
static int __attribute__((ms_abi)) select_layer(int layer) { assert(layer == 0); return 0; }
static void __attribute__((ms_abi)) set_color(DOS64_COLOR color) { (void)color; }
static void __attribute__((ms_abi)) clear(void) {}
static void __attribute__((ms_abi)) present(void) { ++shown; }
static int __attribute__((ms_abi)) audio_open(unsigned int rate)
{
    assert(rate == 44100 && !audio_opened);
    audio_opened = 1;
    audio_time = now;
    return 0;
}
static unsigned long long __attribute__((ms_abi)) queued_frames(void)
{
    unsigned long long consumed = (now - audio_time) * 44100 / 1000000000ULL;
    audio_time = now;
    audio_queued = consumed < audio_queued ? audio_queued - consumed : 0;
    return audio_queued;
}
static unsigned long long __attribute__((ms_abi)) free_frames(void)
{ return 8192 - queued_frames(); }
static unsigned long long __attribute__((ms_abi)) audio_write(const short *frames,
    unsigned long long count)
{
    assert(audio_opened && count <= free_frames());
    for (unsigned long long i = 0; i < count * 2; ++i)
        audio_energy += frames[i] < 0 ? -frames[i] : frames[i];
    audio_queued += count;
    audio_written += count;
    return count;
}
static void __attribute__((ms_abi)) audio_stop(void)
{ assert(audio_opened); audio_opened = 0; audio_queued = 0; ++audio_stops; }
static void __attribute__((ms_abi)) poll(void)
{
    now += 10000000ULL;
    memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
    memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
    ++iteration;
    if (map_test) {
        api.Input.KeyDown[0x4f] = stomp_jump ? iteration < 280 :
            iteration < 70 || (iteration >= 220 && iteration < 400);
        api.Input.KeyDown[0x50] = iteration >= 1000 && iteration < 1200;
        api.Input.KeyDown[0x2c] = iteration >= 700 && iteration < 750;
        api.Input.KeyPressed[0x2c] = iteration == 700;
        if (stomp_jump && iteration >= stomp_jump && iteration < stomp_jump + 6) {
            api.Input.KeyDown[0x2c] = 1;
            api.Input.KeyPressed[0x2c] = iteration == stomp_jump;
        }
        api.Input.KeyDown[0xe0] = (iteration >= 450 && iteration < 462) ||
            (iteration >= 900 && iteration < 912) || (iteration >= 1400 && iteration < 1412) ||
            (!stomp_jump && iteration >= 80 && iteration < 92);
        if (map_animation) {
            memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
            memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
            api.Input.KeyDown[0xe0] = (iteration >= 200 && iteration < 212) ||
                (iteration >= 600 && iteration < 612) ||
                (iteration >= 1000 && iteration < 1012);
            api.Input.KeyDown[0x51] = (iteration >= 400 && iteration < 420) ||
                (iteration >= 800 && iteration < 820);
        }
        if (map_lifecycle) {
            memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
            memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
            api.Input.KeyDown[0x4f] = !map_gameover || iteration - restart_iteration < 280;
        }
        if (continue_test) {
            memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
            memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
            if ((continue_test == 4 || continue_test == 5) && iteration == 60)
                api.Input.KeyPressed[0x4f] = 1;
            if (continue_test == 5 && iteration == 80)
                api.Input.KeyPressed[0x50] = 1;
            if (continue_test == 6 && iteration == 80)
                api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
            if (continue_test == 7 && continue_accepted && !exhausted_started)
                api.Input.KeyDown[0x4f] = iteration - restart_iteration < 280;
            if (continue_test > 1 && iteration == 101) {
                unsigned int key = continue_test == 2 ? 0x2c : 0x28;
                api.Input.KeyDown[key] = api.Input.KeyPressed[key] = 1;
            }
            if (continue_test > 1 && continue_test < 6 && continue_test != 4 && iteration == 500)
                api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
        }
    }
    if (ground_steering && iteration <= 1400) {
        unsigned int phase = iteration % 400;
        unsigned int key = phase < 200 ? 0x4f : 0x50;
        if (phase < 160 || (phase >= 200 && phase < 350)) {
            api.Input.KeyDown[key] = 1;
            api.Input.KeyPressed[key] = phase == 1 || phase == 200;
        }
        if ((phase >= 65 && phase < 115) || (phase >= 265 && phase < 280)) {
            api.Input.KeyDown[0x2c] = 1;
            api.Input.KeyPressed[0x2c] = phase == 65 || phase == 265;
        }
    }
    if (jump_steering) {
        unsigned int within = iteration % 250;
        if (iteration <= 1000 && within >= 51 &&
            within <= ((iteration / 250) & 1 ? 100U : 55U)) {
            api.Input.KeyDown[0x2c] = 1;
            api.Input.KeyPressed[0x2c] = within == 51;
        }
        if (iteration <= 1000 && within >= 51 && within <= 140) {
            api.Input.KeyDown[within < 75 ? 0x4f : 0x50] = 1;
        }
    }
    if (steering_test && iteration >= 56 && iteration <= 75) {
        api.Input.KeyDown[0x50] = 1;
        api.Input.KeyPressed[0x50] = iteration == 56;
    }
    if (steering_test && iteration >= 41 && iteration <= 55) {
        api.Input.KeyDown[0x4f] = 1;
        api.Input.KeyPressed[0x4f] = iteration == 41;
    }
    if (iteration == (map_gameover || continue_test == 7 ? 20002U : map_lifecycle ? 6002U : 2002U)) {
        api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
    }
    if (jump_test && api.Input.KeyPressed[0x2c]) {
        jump_manual = 1;
        jump_requested = player_completed;
    }
    if (ground_test) {
        unsigned short taps = (api.Input.KeyPressed[0x50] ? 4 : 0) |
            (api.Input.KeyPressed[0x4f] ? 8 : 0) | (api.Input.KeyPressed[0x2c] ? 0x20 : 0) |
            (api.Input.KeyPressed[0x51] ? 2 : 0);
        if (taps || api.Input.KeyDown[0x50] || api.Input.KeyDown[0x4f] ||
            api.Input.KeyDown[0x2c] || api.Input.KeyDown[0x51]) {
            ground_manual = 1;
        }
        ground_taps |= taps;
    }
    assert(iteration <= (map_gameover || continue_test == 7 ? 20002U : map_lifecycle ? 6002U : 2002U));
}
static void update_reference(void *context)
{
    (void)context;
    if (ground_test) {
        unsigned short held = (api.Input.KeyDown[0x50] ? 4 : 0) |
            (api.Input.KeyDown[0x4f] ? 8 : 0) | (api.Input.KeyDown[0x2c] ? 0x20 : 0) |
            (api.Input.KeyDown[0x51] ? 2 : 0);
        if (!ground_manual) {
            unsigned long long phase = now % 12000000000ULL;
            held = phase < 1800000000ULL ? 8 : phase < 2100000000ULL ? 0 :
                phase < 4300000000ULL ? 4 : phase < 5200000000ULL ? 8 :
                phase < 5700000000ULL ? 2 :
                (phase >= 6200000000ULL && phase < 6400000000ULL) ||
                (phase >= 8100000000ULL && phase < 8300000000ULL) ? 0x40 :
                phase >= 7600000000ULL && phase < 7800000000ULL ? 4 : 0;
            if ((phase >= 800000000ULL && phase < 1300000000ULL) ||
                (phase >= 3100000000ULL && phase < 3600000000ULL)) held |= 0x20;
            if (phase < 10000000000ULL) {
                demo_hit = 0;
            } else if (!demo_hit) {
                damage_source.x = (short)(player->body.owner.x +
                    (player->body.node->pass_flags & 8 ? 16 : -16));
                player->immunity = 0;
                player->flags_high |= 4;
                assert(engine_player_damage(&objects, player_object, &player_air) == 0);
                demo_hit = 1;
            }
        }
        player_air.pressed = held | (ground_taps & 0x20);
        player->controls = (unsigned char)ground_taps;
        ground_taps = 0;
        unsigned int before = player->handler;
        assert(engine_update_objects(&objects, &api.Input) == 0);
        action_frames += player_object->behavior == &engine_player_action_behavior;
        airborne = player_object->behavior == &engine_player_jump_behavior ||
            player_object->behavior == &engine_player_air_behavior;
        ground_jumps += player->handler != before &&
            player_object->behavior == &engine_player_jump_behavior;
        return;
    }
    if (jump_test) {
        unsigned short directions = (api.Input.KeyDown[0x50] ? 4 : 0) |
            (api.Input.KeyDown[0x4f] ? 8 : 0);
        player_air.pressed = directions | (api.Input.KeyDown[0x2c] ? 0x20 : 0);
        if (!jump_manual && airborne) {
            if (!directions) player_air.pressed |= player_variant & 1 ? 4 : 8;
            if (now - jump_begin < (player_variant & 2 ? 500000000ULL : 100000000ULL)) {
                player_air.pressed |= 0x20;
            }
        }
        if (player_completed) {
            if (directions) {
                player->body.node->pass_flags = (unsigned char)(
                    (player->body.node->pass_flags & 0xf7) | (directions & 4 ? 8 : 0));
            }
            if (jump_requested || (!jump_manual && now - jump_begin >= 2000000000ULL)) {
                jump_requested = 0;
                if (!jump_manual) {
                    player_variant = (player_variant + 1) & 3;
                    player->body.owner.x = 160;
                    player->body.node->pass_flags = (unsigned char)(
                        (player->body.node->pass_flags & 0xf7) | (player_variant & 1 ? 8 : 0));
                }
                ENGINE_PLAYER_CALL call = {player->body.node->pass_flags & 8 ? 0xb7e7U : 0xb604U,
                    0x6180, 4};
                player_air.flags &= 0xdfffU;
                jump_begin = now;
                player_completed = 0; airborne = 1;
                assert(jump_count < 16);
                jump_min_y[jump_count++] = 160;
                assert(engine_player_begin_jump(&objects, player_object, &player_air,
                    &call, 0x612c) == 0);
            }
            assert(animation_program_step(&player->body.animation, player->body.node,
                &player->body.owner, idle_event, 0) == 0);
            return;
        }
    }
    if (flight_test && !jump_test && airborne) {
        unsigned short directions = (api.Input.KeyDown[0x50] ? 4 : 0) |
            (api.Input.KeyDown[0x4f] ? 8 : 0);
        player_air.pressed = directions ? directions : (player_variant & 1 ? 4 : 8);
    }
    unsigned int before = player->handler;
    int was_air = player_object && (player_object->behavior == &engine_player_air_behavior ||
        player_object->behavior == &engine_player_jump_behavior);
    assert(engine_update_objects(&objects, &api.Input) == 0);
    direction_changes += was_air && player->handler != before;
}
static int player_probe(void *context, short x, short y, short *hit)
{
    (void)context;
    assert(x == player->body.owner.x && y == player->body.owner.y);
    *hit = !jump_test && !ground_test && (player_variant & 4) ? -1 : 0;
    return 0;
}
static int player_transition(void *context, const ENGINE_PLAYER_CALL *call)
{
    (void)context;
    assert((call->handler == 0xaa97 || call->handler == 0xae53) &&
        call->script == 0x6116 && call->counter == 0);
    ++player_transitions;
    if (flight_test) {
        airborne = 1;
        player_air.pressed = player_variant & 1 ? 4 : 8;
        return engine_player_begin_air(&objects, player_object, &player_air, call);
    }
    player_object->behavior = 0;
    player_completed = 1;
    return 0;
}
static int flight_ground(void *context, short *kind, short *delta_y)
{
    (void)context;
    *kind = player->body.owner.y >= 160 ? 1 : 0;
    *delta_y = (short)(160 - player->body.owner.y);
    return 0;
}
static int flight_edge(void *context, short *hit, short *kind, short *x, short *y)
{
    (void)context;
    *hit = *kind = *x = *y = 0;
    return 0;
}
static int ground_support(void *context, short *supported)
{
    (void)context;
    *supported = player->body.owner.y >= 160;
    if (*supported) player->body.owner.y = 160;
    player_air.contact_kind = player_air.surface_kind = 0;
    return 0;
}

static int ground_sound(void *context, unsigned short sample)
{
    (void)context;
    assert(sample >= 2 && sample <= 6);
    roar_sounds += sample == 2;
    damage_sounds += sample == 4;
    return 0;
}

static int flight_landed(void *context, const ENGINE_PLAYER_CALL *call,
    short kind, short x, short y)
{
    (void)context; (void)kind; (void)x; (void)y;
    if (ground_test && call->handler == 0xec69U) {
        return engine_player_begin_action(&objects, player_object, &player_air, call);
    }
    assert(call->handler == 0xc8d5 || call->handler == 0xc2cd ||
        call->handler == 0xcdc2 || call->handler == 0xd108 ||
        call->handler == 0xb253 || call->handler == 0xb19f);
    assert(player->body.owner.y == 160);
    if (ground_test) {
        assert(call->handler != 0xb253 && call->handler != 0xb19f);
        airborne = 0;
        if (player->handler == call->handler) {
            player_object->behavior = &engine_player_ground_behavior;
        } else {
            assert(engine_player_begin_ground(&objects, player_object, &player_air, call) == 0);
        }
        ++flight_transitions;
        return 0;
    }
    if (jump_test) {
        assert(call->handler != 0xb253 && call->handler != 0xb19f);
        assert(animation_program_initialize(&player->body.animation, animation_movement_data,
            ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x6148,
            animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
        player->body.motion.velocity_x = 0;
        airborne = 0;
        assert(animation_program_step(&player->body.animation, player->body.node,
            &player->body.owner, 0, 0) == 0);
    }
    player_object->behavior = 0;
    player_completed = 1;
    ++flight_transitions;
    return 0;
}
static void begin_reference_player(void)
{
    if (ground_test) {
        player->body.owner = (RENDER_OWNER){160, 160};
        player->body.motion = (ENGINE_MOTION){0};
        ENGINE_PLAYER_CALL call = {0xc8d5, 0x6148, 0};
        assert(engine_player_begin_ground(&objects, player_object, &player_air, &call) == 0);
        previous_player_position = player->body.owner;
        return;
    }
    if (jump_test) {
        player->body.owner = (RENDER_OWNER){160, 160};
        player->body.motion = (ENGINE_MOTION){0};
        player_completed = 1;
        assert(animation_program_initialize(&player->body.animation, animation_movement_data,
            ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x6148,
            animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
        assert(animation_program_step(&player->body.animation, player->body.node,
            &player->body.owner, 0, 0) == 0);
        previous_player_position = player->body.owner;
        return;
    }
    ENGINE_PLAYER_CALL call;
    uint32_t position = UINT32_C(0x6c31) + (player_variant & 2 ? 2 : 0);
    assert((player_variant & 1 ? engine_player_reaction_e6ee(0, position, &call) :
        engine_player_reaction_e667(0, position, &call)) == 0);
    player->body.owner = (RENDER_OWNER){160, 100};
    player->body.motion = (ENGINE_MOTION){0};
    player_collision_flags = 0;
    player_completed = 0;
    airborne = 0;
    previous_player_position = player->body.owner;
    assert(engine_player_begin_deflection(player_object, player, &call) == 0);
}
static void draw_reference_player(const DOS64_COLOR *image)
{
    if (!jump_test && !ground_test && player_completed &&
        now - cycle_begin >= (flight_test ? 2000000000ULL : 1000000000ULL)) {
        player_variant = (player_variant + 1) & 7;
        cycle_begin = now;
        begin_reference_player();
    }
    memset(pixels, 0, sizeof(pixels));
    unsigned short camera_x = 0;
    if (ground_test) {
        RENDER_OWNER view = {player->body.owner.x > 160 ? (short)(player->body.owner.x - 160) : 0, 0};
        RENDER_VIEWPORT viewport;
        assert(render_prepare_viewport(&view,
            (unsigned short)(map[8] | (unsigned int)map[9] << 8),
            (unsigned short)(map[12] | (unsigned int)map[13] << 8), 0, &viewport) == 0);
        camera_x = viewport.x;
        player->body.node->flags |= 0x40;
        scroll_frames += camera_x != 0;
        run_frames += player->handler == 0xcdc2 || player->handler == 0xd108;
        turn_frames += player->handler == 0xbeb7 || player->handler == 0xc0a1;
        idle_frames += player->handler == 0xc8d5 || player->handler == 0xc2cd;
        if (player->body.owner.x < min_world_x) min_world_x = player->body.owner.x;
        if (player->body.owner.x > max_world_x) max_world_x = player->body.owner.x;
    }
    assert(render_map_tile_pass(map, map_size, 0, camera_x, 0, 0, pixels) == 0);
    assert(render_map_tile_pass(map, map_size, 0, camera_x, 0, 1, pixels) == 0);
    memcpy(background, pixels, sizeof(pixels));
    assert(render_object_pass(&renders, 0, (short)-(int)camera_x, 0, banks, 34, pixels) == 0);
    unsigned int visible = 0;
    for (unsigned int i = 0; i < 64000; ++i) {
        assert(memcmp(&image[i], &palette[pixels[i]], sizeof(image[i])) == 0);
        visible += memcmp(&palette[pixels[i]], &palette[background[i]],
            sizeof(palette[0])) != 0;
        ++verified;
    }
    object_frames += visible != 0;
    changed += visible;
    variant_frames[player_variant] += visible != 0;
    moving_frames += player->body.owner.x != previous_player_position.x ||
        player->body.owner.y != previous_player_position.y;
    airborne_frames += airborne && !player_completed;
    if (jump_test && jump_count && player->body.owner.y < jump_min_y[jump_count - 1]) {
        jump_min_y[jump_count - 1] = player->body.owner.y;
    }
    previous_player_position = player->body.owner;
    assert(engine_dispatch_ticks(&clock, now, update_reference, 0) >= 0);
}
static void __attribute__((ms_abi)) draw(const DOS64_COLOR *image, unsigned int w,
    unsigned int h, unsigned int stride, int x, int y, unsigned int dw, unsigned int dh)
{
    if (h == 5 && stride == 60) {
        assert(w <= 60 && x == (int)(640 - (w + 4) * 2) &&
            y == 422 && dw == w * 2 && dh == 10);
        return;
    }
    if (w == 1 && h == 1) {
        assert(stride == 1 && x == 0 && y == 0 && dw == api.Gfx.Width &&
            dh == api.Gfx.Height && image[0] == 0xff000000U);
        return;
    }
    assert(w == 320 && h == 200 && stride == 320 && x == 0 && y == 40 && dw == 640 && dh == 400);
    if (map_test) {
        if (exhausted_started) {
            if (!exhausted_frames)
                for (unsigned int i = 0; i < 64000; ++i)
                    assert(image[i] == gameover_palette[gameover_reference[i]]);
            ++exhausted_frames;
        }
        if ((continue_test || (map_gameover && continue_started)) && !continue_accepted &&
            !exhausted_started) {
            if (!continue_frames) {
                for (unsigned int i = 0; i < 64000; ++i)
                    assert(image[i] == continue_palette[continue_reference[i]]);
            }
            if (continue_test == 4 || continue_test == 5) {
                unsigned int left = 0, right = 0;
                for (unsigned int row = 44; row < 68; ++row)
                    for (unsigned int col = 0; col < 26; ++col) {
                        left += (image[row * 320 + 67 + col] & 0x00ffffffU) != 0;
                        right += (image[row * 320 + 163 + col] & 0x00ffffffU) != 0;
                    }
                if (left) ++selector_left_frames;
                if (right) ++selector_right_frames;
            }
            unsigned int visible = 0;
            for (unsigned int row = 16; row < 32; ++row)
                for (unsigned int col = 89; col < 231; ++col)
                    visible += (image[row * 320 + col] & 0x00ffffffU) != 0;
            assert(visible > 0);
            for (unsigned int row = 0; row < 8; ++row)
                for (unsigned int col = 0; col < 20; ++col) {
                    DOS64_COLOR pixel = image[(93 + row) * 320 + 203 + col];
                    unsigned int index = row * 20 + col;
                    if (!continue_frames) countdown_first[index] = pixel;
                    else if (countdown_first[index] != pixel) countdown_changed = 1;
                }
            ++continue_frames;
            if (continue_test > 1 && iteration > 101) {
                unsigned int visible_digit = 0;
                for (unsigned int row = 93; row < 108; ++row)
                    for (unsigned int col = 203; col < 218; ++col)
                        visible_digit += (image[row * 320 + col] & 0x00ffffffU) != 0;
                if (!visible_digit) ++accept_animation_frames;
                if (!visible_digit && (continue_test == 2 || continue_test == 3 || continue_test == 5 || continue_test == 7)) {
                    for (unsigned int row = 44; row < 68; ++row)
                        for (unsigned int col = 67; col < 93; ++col)
                            assert((image[row * 320 + col] & 0x00ffffffU) == 0);
                }
            }
        }
        if (map_animation && shown) {
            for (unsigned int row = 0; row < 80; ++row)
                for (unsigned int column = 0; column < 320; ++column) {
                    int meter = row >= 12 && row < 40 &&
                        ((column >= 18 && column < 44) || (column >= 274 && column < 300));
                    if (!meter) assert(previous_map_frame[row*320+column] == image[row*320+column]);
                }
            ++stable_background_frames;
        }
        if (shown && memcmp(previous_map_frame, image, sizeof(previous_map_frame)) != 0) ++changed;
        memcpy(previous_map_frame, image, sizeof(previous_map_frame));
        return;
    }
    if (deflection_test || flight_test) {
        draw_reference_player(image);
        return;
    }
    if (!objects.head) {
        assert(engine_setup_emitter_group(&objects, &renders, &emitters, &camera,
            &visibility, 0, 0, 0) == 0);
        cycle_begin = now;
    }
    if (!emitters.trigger && now - cycle_begin >= 1000000000ULL) {
        ENGINE_OBJECT *created;
        assert(engine_spawn_shake(&objects, &renders, &shake, 0, &camera_shake,
            &immunity, &player_motion, &player_flags, 0, 0, 0, &created) == 0);
        emitters.trigger = 1;
    }
    RENDER_VIEWPORT viewport;
    assert(render_prepare_viewport(&camera,
        (unsigned short)(map[8] | (unsigned int)map[9] << 8),
        (unsigned short)(map[12] | (unsigned int)map[13] << 8),
        camera_shake, &viewport) == 0);
    memset(pixels, 0, sizeof(pixels));
    assert(render_map_tile_pass(map, map_size, 0, viewport.x, viewport.y, 0, pixels) == 0);
    assert(render_map_tile_pass(map, map_size, 0, viewport.x, viewport.y, 1, pixels) == 0);
    memcpy(background, pixels, sizeof(pixels));
    if (camera_shake) {
        unsigned char stationary[64000] = {0};
        assert(render_map_tile_pass(map, map_size, 0, viewport.x, camera.y, 0, stationary) == 0);
        assert(render_map_tile_pass(map, map_size, 0, viewport.x, camera.y, 1, stationary) == 0);
        unsigned int differences = 0;
        for (unsigned int i = 0; i < 64000; ++i) {
            differences += memcmp(&palette[stationary[i]], &palette[pixels[i]],
                sizeof(palette[0])) != 0;
        }
        assert(differences > 1000);
        shake_pixels += differences;
        ++shake_frames;
    }
    for (RENDER_NODE *node = renders.head; node; node = node->next) {
        node->flags |= 0x40;
    }
    assert(render_object_pass(&renders, 0, (short)-viewport.x, (short)-viewport.y, banks, 161, pixels) == 0);
    unsigned int visible = 0;
    for (unsigned int i = 0; i < 64000; ++i) {
        assert(memcmp(&image[i], &palette[pixels[i]], sizeof(image[i])) == 0);
        visible += memcmp(&palette[pixels[i]], &palette[background[i]],
            sizeof(palette[0])) != 0;
        ++verified;
    }
    object_frames += visible != 0;
    changed += visible;
    camera_shake = 0;
    for (RENDER_NODE *node = renders.head; node; node = node->next) {
        node->flags &= 0xbf;
    }
    assert(engine_dispatch_ticks(&clock, now, update_reference, 0) >= 0);
}
int main(int argc, char **argv)
{
    assert(argc == 1 || (argc == 2 && (strcmp(argv[1], "--deflection") == 0 ||
        strcmp(argv[1], "--emitters") == 0 || strcmp(argv[1], "--steering") == 0 ||
        strcmp(argv[1], "--flight") == 0 || strcmp(argv[1], "--jump-steering") == 0 ||
        strcmp(argv[1], "--jump") == 0 || strcmp(argv[1], "--ground-steering") == 0 ||
        strcmp(argv[1], "--map") == 0 || strcmp(argv[1], "--map-stomp") == 0 ||
        strcmp(argv[1], "--map-animation") == 0 || strcmp(argv[1], "--map-lifecycle") == 0 ||
        strcmp(argv[1], "--map-gameover") == 0 ||
        strcmp(argv[1], "--continue-timeout") == 0 ||
        strcmp(argv[1], "--continue-space") == 0 ||
        strcmp(argv[1], "--continue-enter") == 0 ||
        strcmp(argv[1], "--continue-no") == 0 ||
        strcmp(argv[1], "--continue-left") == 0 ||
        strcmp(argv[1], "--continue-escape") == 0 ||
        strcmp(argv[1], "--continue-exhausted") == 0)));
    if (argc == 2 && strcmp(argv[1], "--continue-timeout") == 0) continue_test = 1;
    if (argc == 2 && strcmp(argv[1], "--continue-space") == 0) continue_test = 2;
    if (argc == 2 && strcmp(argv[1], "--continue-enter") == 0) continue_test = 3;
    if (argc == 2 && strcmp(argv[1], "--continue-no") == 0) continue_test = 4;
    if (argc == 2 && strcmp(argv[1], "--continue-left") == 0) continue_test = 5;
    if (argc == 2 && strcmp(argv[1], "--continue-escape") == 0) continue_test = 6;
    if (argc == 2 && strcmp(argv[1], "--continue-exhausted") == 0) continue_test = 7;
    map_gameover = argc == 2 && strcmp(argv[1], "--map-gameover") == 0;
    map_lifecycle = map_gameover || (argc == 2 && strcmp(argv[1], "--map-lifecycle") == 0);
    map_animation = argc == 2 && strcmp(argv[1], "--map-animation") == 0;
    stomp_jump = argc == 2 && strcmp(argv[1], "--map-stomp") == 0 ? 104 : 0;
    map_test = continue_test || map_lifecycle || map_animation || stomp_jump ||
        (argc == 2 && strcmp(argv[1], "--map") == 0);
    steering_test = argc == 2 && strcmp(argv[1], "--steering") == 0;
    jump_steering = argc == 2 && strcmp(argv[1], "--jump-steering") == 0;
    ground_steering = argc == 2 && strcmp(argv[1], "--ground-steering") == 0;
    ground_test = argc == 1 || ground_steering;
    jump_test = jump_steering || (argc == 2 && strcmp(argv[1], "--jump") == 0);
    flight_test = ground_test || jump_test || steering_test ||
        (argc == 2 && strcmp(argv[1], "--flight") == 0);
    deflection_test = argc == 2 && strcmp(argv[1], "--deflection") == 0;
    api.Size = sizeof(api); api.Version = DOS64_API_VERSION;
    api.Arguments = continue_test ? "--continue-test" : map_test ? "--map" : ground_test ? "--preview" : jump_test ? "--jump" : flight_test ? "--flight" :
        deflection_test ? "--deflection" : "--emitters";
    api.Write = log_text; api.Sleep = sleep_ms; api.Time.Nanoseconds = time_ns;
    api.Input.Poll = poll; api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SetColor = set_color; api.Gfx.Clear = clear;
    api.Gfx.SelectLayer = select_layer; api.Gfx.Present = present; api.DrawImage = draw;
    mock_install_layers(&api);
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file; api.Fs.Write = write_file;
    if (map_test) {
        api.Audio.Present = 1; api.Audio.Open = audio_open; api.Audio.Write = audio_write;
        api.Audio.FreeFrames = free_frames; api.Audio.QueuedFrames = queued_frames;
        api.Audio.Stop = audio_stop;
        if (continue_test || map_gameover) {
            unsigned int size;
            assert(resources_load_entry(&api, "LIONKING.EPF", "LEVEL1.MAP", packed, sizeof(packed),
                map, sizeof(map), &dictionary, &size) == 0);
            assert(vga_load_palette(map, size, continue_level_palette) == 0);
        }
        if (continue_test == 1) {
            assert(frontend_prepare_continue(&api, continue_level_palette) == 0);
            assert(frontend_start_continue(&api, 0) == 0);
            assert(frontend_service_continue() == 0 && !audio_opened && !audio_stops);
            assert(frontend_accept_continue(&api, 0) == 0);
            assert(frontend_continue_speech(0) == 0);
            assert(frontend_service_continue() == 0 && !audio_opened && !audio_stops);
            frontend_stop_continue();
            assert(frontend_release() == 0);
        }
        if (continue_test || map_gameover) {
            unsigned int size;
            assert(resources_load_entry(&api, "LIONKING.EPF", "TITLES.MAP", packed, sizeof(packed),
                map, sizeof(map), &dictionary, &size) == 0);
            assert(vga_load_palette(map, size, continue_palette) == 0);
            memcpy(gameover_palette, continue_palette, sizeof(gameover_palette));
            for (unsigned int i = 0; i < 16; ++i)
                continue_palette[240 + i] = continue_level_palette[128 + i];
            assert(resources_load_entry(&api, "LIONKING.EPF", "CONTINUE.MCH", packed, sizeof(packed),
                continue_title, sizeof(continue_title), &dictionary, &continue_title_size) == 0);
            assert(resources_load_entry(&api, "LIONKING.EPF", "RAFIKI.MCH", packed, sizeof(packed),
                continue_rafiki, sizeof(continue_rafiki), &dictionary, &continue_rafiki_size) == 0);
            assert(resources_load_entry(&api, "LIONKING.EPF", "NUMBERS.MCH", packed, sizeof(packed),
                continue_digits, sizeof(continue_digits), &dictionary, &continue_digits_size) == 0);
            assert(resources_load_entry(&api, "LIONKING.EPF", "SUN.MCH", packed, sizeof(packed),
                continue_marker, sizeof(continue_marker), &dictionary, &continue_marker_size) == 0);
            assert(resources_load_entry(&api, "LIONKING.EPF", "CIRCLE.MCH", packed, sizeof(packed),
                continue_circle, sizeof(continue_circle), &dictionary, &continue_circle_size) == 0);
            assert(resources_load_entry(&api, "LIONKING.EPF", "GAMEOVER.MCH", packed, sizeof(packed),
                continue_gameover, sizeof(continue_gameover), &dictionary, &continue_gameover_size) == 0);
            const unsigned char *screen_assets[] = {
                continue_title, continue_rafiki, continue_digits, continue_marker, continue_gameover
            };
            const unsigned int screen_sizes[] = {
                continue_title_size, continue_rafiki_size, continue_digits_size,
                continue_marker_size, continue_gameover_size
            };
            for (unsigned int asset = 0; asset < 5; ++asset) {
                unsigned int frames = screen_assets[asset][0] | (unsigned int)screen_assets[asset][1] << 8;
                for (unsigned int frame = 0; frame < frames; ++frame) {
                    memset(pixels, 0, sizeof(pixels));
                    assert(render_draw_sprite(screen_assets[asset], screen_sizes[asset],
                        (unsigned short)frame, 0, 0, pixels) == 0);
                    for (unsigned int i = 0; i < 64000; ++i) assert(pixels[i] < 240);
                }
            }
            assert(render_draw_sprite(continue_title, continue_title_size, 0, 89, 16, continue_reference) == 0);
            assert(render_draw_sprite(continue_rafiki, continue_rafiki_size, 0, 96, 70, continue_reference) == 0);
            assert(render_draw_sprite(continue_digits, continue_digits_size, 9, 150, 38, continue_reference) == 0);
            assert(render_draw_sprite(continue_marker, continue_marker_size, 0, 67, 44, continue_reference) == 0);
            memset(background, 0, sizeof(background));
            assert(render_draw_sprite(continue_circle, continue_circle_size, 0, 242, 161, background) == 0);
            for (unsigned int i = 0; i < 64000; ++i) {
                if (!background[i]) continue;
                assert(background[i] >= 128 && background[i] < 144);
                continue_reference[i] = (unsigned char)(background[i] + 112);
            }
            assert(render_draw_sprite(continue_digits, continue_digits_size, 1, 218, 118, continue_reference) == 0);
            assert(render_draw_sprite(continue_rafiki, continue_rafiki_size, 0, 96, 70, gameover_reference) == 0);
            assert(render_draw_sprite(continue_gameover, continue_gameover_size, 0, 95, 32, gameover_reference) == 0);
            for (unsigned int frame = 0; frame < 20; ++frame) {
                memset(pixels, 0, sizeof(pixels));
                assert(render_draw_sprite(continue_rafiki, continue_rafiki_size,
                    (unsigned short)frame, 96, 70, pixels) == 0);
                for (unsigned int digit = 0; digit < 10; ++digit) {
                    memset(background, 0, sizeof(background));
                    assert(render_draw_sprite(continue_digits, continue_digits_size,
                        (unsigned short)digit, 150, 38, background) == 0);
                    for (unsigned int i = 0; i < 64000; ++i)
                        assert(!pixels[i] || !background[i]);
                }
            }
            if (continue_test == 1) {
                assert(frontend_prepare_continue(&api, continue_level_palette) == 0);
                static const unsigned int elapsed[] = {0, 3, 4, 7, 8, 13, 14, 40, 100, 150};
                static const unsigned short rafiki_frames[] = {16, 16, 17, 17, 18, 18, 19, 19, 19, 19};
                for (unsigned int sample = 0; sample < sizeof(elapsed) / sizeof(elapsed[0]); ++sample) {
                    memset(pixels, 0, sizeof(pixels));
                    memset(background, 0, sizeof(background));
                    assert(frontend_continue(pixels, palette, 700, 0, 2,
                        FRONTEND_CONTINUE_ACCEPT_TICKS - elapsed[sample], 0) == 0);
                    assert(render_draw_sprite(continue_rafiki, continue_rafiki_size,
                        rafiki_frames[sample], 96, 70, background) == 0);
                    assert(render_draw_sprite(continue_title, continue_title_size, 0, 89, 16, background) == 0);
                    unsigned char icon[64000] = {0};
                    assert(render_draw_sprite(continue_circle, continue_circle_size,
                        (unsigned short)((FRONTEND_CONTINUE_TICKS - 700) / 8 % 4),
                        242, 161, icon) == 0);
                    for (unsigned int i = 0; i < 64000; ++i)
                        if (icon[i]) background[i] = (unsigned char)(icon[i] + 112);
                    assert(render_draw_sprite(continue_digits, continue_digits_size, 2, 218, 118, background) == 0);
                    assert(memcmp(pixels, background, sizeof(pixels)) == 0);
                }
                for (unsigned int frame = 0; frame < 4; ++frame) {
                    memset(pixels, 0, sizeof(pixels));
                    memset(background, 0, sizeof(background));
                    assert(frontend_continue(pixels, palette, FRONTEND_CONTINUE_TICKS - frame * 8,
                        0, 1, 0, 0) == 0);
                    assert(render_draw_sprite(continue_circle, continue_circle_size,
                        (unsigned short)frame, 242, 161, background) == 0);
                    for (unsigned int i = 0; i < 64000; ++i) {
                        if (!background[i]) continue;
                        assert(background[i] >= 128 && background[i] < 144);
                        background[i] = (unsigned char)(background[i] + 112);
                    }
                    assert(render_draw_sprite(continue_digits, continue_digits_size,
                        1, 218, 118, background) == 0);
                    for (unsigned int row = 160; row < 195; ++row)
                        for (unsigned int col = 240; col < 290; ++col)
                            assert(pixels[row * 320 + col] == background[row * 320 + col]);
                    for (unsigned int i = 0; i < 16; ++i)
                        assert(palette[240 + i] == continue_level_palette[128 + i]);
                }
                assert(frontend_release() == 0);
            }
        }
        assert(start(&api) == 0);
        if (continue_test) {
            assert(continue_started == 1 && continue_frames > 50);
            assert(audio_written > continue_audio_start && audio_energy > continue_energy_start);
            if (continue_test == 1) {
                assert(!continue_accepted && countdown_changed && iteration >= 1420 && iteration <= 1450);
                assert(map_lives == 0 && audio_stops == 2);
            } else if (continue_test == 4 || continue_test == 6) {
                assert(!continue_accepted && map_lives == 0 && audio_stops == 2);
                if (continue_test == 4) assert(selector_left_frames && selector_right_frames);
            } else if (continue_test == 7) {
                assert(continue_accepted == 1 && exhausted_started == 1 && exhausted_frames > 390);
                assert(map_lives == 0 && map_deaths == 3 && audio_stops == 5);
                assert(continue_speech_iteration >= 180 && continue_speech_iteration <= 185);
            } else {
                assert(continue_accepted == 1 && map_lives == 3 && iteration == 500);
                assert(audio_stops == 4);
                assert(continue_speech_iteration >= 180 && continue_speech_iteration <= 185);
                assert(accept_animation_frames > 200);
                if (continue_test == 5) assert(selector_left_frames && selector_right_frames);
            }
            assert(!audio_opened && !log_file);
            puts("PASS: direct continue countdown, visible text, input and audio cleanup");
            return 0;
        }
        printf("Map measurements: %u spawns/%u contacts/%u stuns/%u defeats, %u damage logs/"
            "%u landings, %u changed frames, %llu audio frames\n", map_spawns, map_contacts,
            map_stuns, map_defeats, enemy_damage_logs, map_jumps, changed, audio_written);
        fflush(stdout);
        if (map_lifecycle) {
            printf("Lifecycle measurements: %u deaths/%u restarts/%u lives/%u pickups\n",
                map_deaths, map_restarts, map_lives, map_collected);
            assert(map_deaths > 0 && map_restarts > 0 && map_lives == 3 - map_deaths);
            if (map_gameover) {
                assert(map_deaths == 3 && map_restarts == 2 && map_lives == 0);
                assert(gameover_iteration && iteration - gameover_iteration >= 1420 &&
                    iteration - gameover_iteration <= 1450 && countdown_changed &&
                    continue_frames > 1400 && iteration < 20002);
            } else assert(shown > 2001 && iteration <= 6002);
        } else assert(iteration == 2002 && shown == 2001 && !map_deaths);
        assert(audio_written > 800000 && audio_energy > 0 &&
            audio_stops == (map_gameover ? 2U : 1U) && !log_file);
        if (map_lifecycle) {
            puts("PASS: actual native adapter fatal enemy damage, death animation and restored gameplay without fixture hits");
        } else if (map_animation) {
            assert(stable_background_frames == 2000 && changed > 100 &&
                animation_roar_logs == 3 && enemy_damage_logs == 0);
            puts("PASS: repeated idle/roar/crouch transitions keep distant background exactly stationary");
        } else if (stomp_jump) {
            assert(changed > 200 && map_spawns >= 2 && map_contacts > 0 &&
                map_jumps > 0 && map_defeats == 1 && rebound_logs == 1);
            puts("PASS: real-map stomp, rendered lizard death, Simba rebound, continued gameplay/music and Escape");
        } else {
            assert(changed > 200 && map_spawns >= 2 && map_contacts > 0 &&
                map_jumps > 0 && enemy_damage_logs > 0 && !map_stuns && animation_roar_logs > 0);
            puts("PASS: real map contacts/recoil, initially uncharged roar, jumping, music and Escape with file-only logs");
        }
        return 0;
    }
    assert(resources_load_entry(&api, "LIONKING.EPF",
        (deflection_test || flight_test) ? "LEVEL1.MAP" : "LEVEL6.MAP", packed,
        sizeof(packed), map, sizeof(map), &dictionary, &map_size) == 0);
    assert(vga_load_palette(map, map_size, palette) == 0);
    unsigned int slot, loaded;
    engine_initialize_objects(&objects); render_initialize_nodes(&renders);
    if (deflection_test || flight_test) {
        unsigned int count = flight_test ? ASSETS_YOUNG_BANK_COUNT : 2;
        for (unsigned int i = 0; i < count; ++i) {
            unsigned int index = flight_test ? i : 5 + i;
            assert(assets_load_named_bank(&api, "LIONKING.EPF", assets_young_bank_list,
                sizeof(assets_young_bank_list), index, packed, sizeof(packed),
                flip_sprites[i], sizeof(flip_sprites[i]), &dictionary,
                &slot, &loaded) == 0 && slot == 6 + index);
            banks[slot] = (RENDER_SPRITE_BANK){flip_sprites[i], loaded};
        }
        player->body.render_pool = &renders;
        player->body.node = render_acquire_node(&renders, &player->body.owner, 0, 0,
            animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
        player_object = engine_acquire_object(&objects, 0);
        assert(player->body.node && player_object);
        player->probe = player_probe;
        player->transition = player_transition;
        player->collision_flags = &player_collision_flags;
        player_air.ground = flight_ground;
        player_air.edge = flight_edge;
        player_air.transition = flight_landed;
        player_air.support = ground_support;
        player_air.animation_event = idle_event;
        player_air.sound = ground_sound;
        player_air.damage_source = &damage_source;
        player_air.health = 100;
        player_air.roar_charge = 100;
        begin_reference_player();
    } else {
        assert(assets_load_named_bank(&api, "LIONKING.EPF", animation_level6_bank_list,
            sizeof(animation_level6_bank_list), 0, packed, sizeof(packed), sprite,
            sizeof(sprite), &dictionary, &slot, &loaded) == 0 && slot == 160);
        banks[slot] = (RENDER_SPRITE_BANK){sprite, loaded};
        assert(engine_setup_emitter_group(&objects, &renders, &emitters, &camera,
            &visibility, 0, 0, 0) == 0);
    }
    engine_clock_reset(&clock, 0);
    assert(start(&api) == 0);
    if (ground_test) {
        assert(iteration == 2002 && shown == 2001 && !player_transitions &&
            ground_logs == flight_transitions + 1 && ground_jumps == ground_jump_logs);
        printf("Ground measurements: %u visible/%u moving/%u air, %u run/%u turn/%u idle/"
            "%u scrolling, %u jumps/%u landings, world X %d..%d\n",
            object_frames, moving_frames, airborne_frames, run_frames, turn_frames, idle_frames,
            scroll_frames, ground_jumps, flight_transitions, min_world_x, max_world_x);
        assert(object_frames > 1800 && moving_frames > 300 && run_frames > 200 &&
            idle_frames > 100 && turn_frames > 10 && scroll_frames > 500 &&
            ground_jumps >= 4 && flight_transitions >= 4 && max_world_x - min_world_x > 100);
        assert(ground_steering || (action_frames > 100 && roar_sounds >= 2 && damage_sounds == 1));
        assert(!ground_steering || ground_manual);
        printf("PASS: default original idle/run/turn/jump/landing%s, %llu exact ARGB pixels, "
            "continuous world motion and camera, Escape\n",
            ground_steering ? " with manual input" : " demo", verified);
        return 0;
    }
    if (jump_test) {
        assert(iteration == 2002 && shown == 2001 && jump_logs == jump_count &&
            flight_transitions == jump_count && ready_logs == jump_count + 1 &&
            player_completed && !player_transitions);
        assert(object_frames > 1800 && moving_frames > 100 && airborne_frames > 200);
        assert(jump_count == (jump_steering ? 4U : 9U));
        assert(idle_events == idle_logs);
        if (jump_steering) {
            assert(idle_events > 0);
            assert(jump_manual && direction_changes >= 4);
            assert(jump_min_y[0] - jump_min_y[1] >= 40 &&
                jump_min_y[2] - jump_min_y[3] >= 40);
        } else {
            assert(moving_frames == 355 && airborne_frames == 768 &&
                jump_min_y[0] == 123 && jump_min_y[1] == 83);
        }
        printf("PASS: default jump%s, %llu exact ARGB pixels, %u visible/%u moving/"
            "%u airborne frames, %u jumps/landings, %u direction transitions, "
            "short/held minimum Y %d/%d, Escape\n", jump_steering ? " with manual keys" : " demo",
            verified, object_frames, moving_frames, airborne_frames, jump_count,
            direction_changes, jump_min_y[0], jump_min_y[1]);
        return 0;
    }
    if (flight_test) {
        assert(iteration == 2002 && shown == 2001 && player_transitions == 10 &&
            flight_transitions == 10 && flight_logs == flight_transitions && !player_logs);
        assert(object_frames > 1800 && changed > 100000);
        if (steering_test) {
            assert(moving_frames > 300 && airborne_frames > 300 && direction_changes >= 2);
        } else {
            assert(moving_frames == 398 && airborne_frames == 460);
        }
        for (unsigned int i = 0; i < 8; ++i) {
            assert(variant_frames[i] >= 190);
        }
        printf("PASS: --flight player entry, %llu exact ARGB pixels, "
            "%u visible/%u moving/%u airborne frames, %u direction changes, "
            "10 deflection->air->landing chains, Escape\n",
            verified, object_frames, moving_frames, airborne_frames, direction_changes);
        return 0;
    }
    if (deflection_test) {
        assert(iteration == 2002 && shown == 2001 && player_transitions == 20 &&
            player_logs == player_transitions);
        assert(object_frames > 1800 && changed > 100000 && moving_frames >= 300);
        for (unsigned int i = 0; i < 8; ++i) {
            assert(variant_frames[i] >= 200);
        }
        printf("PASS: --deflection actual entry, eight original player cases, "
            "%llu exact ARGB pixels, %u visible frames, %u movement frames, "
            "20 exact transition boundaries and Escape\n", verified, object_frames, moving_frames);
        return 0;
    }
    assert(iteration == 2002 && shown == 2001 && activation >= 3);
    assert(object_frames > 1500 && changed > 100000 && objects.update_count > 900);
    assert(shake_frames >= 20 && shake_pixels > 100000 && player_flags == 0x40);
    printf("PASS: --emitters DOS64 scene, 20 seconds, %llu exact ARGB pixels, "
        "%u visible-object frames, %u object pixels, %u shaken frames/%u shake pixels, "
        "live spawning/culling and Escape\n",
        verified, object_frames, changed, shake_frames, shake_pixels);
    return 0;
}
