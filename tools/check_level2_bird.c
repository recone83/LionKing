#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/animation_data.h"
#include "engine/assets.h"
#include "engine/enemies.h"
#include "engine/random.h"
#include "engine/resources.h"

static unsigned char packed[79311], map[580488], contours[4096];
static unsigned char level2_banks[21][65536];
static unsigned char pixels[64000];
static RESOURCE_DICTIONARY dictionary;
static ENGINE_MAP_COLLISION collision;
static ENGINE_ENEMIES enemies;
static ENGINE_OBJECT_POOL objects;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR player;
static RENDER_SPRITE_BANK banks[127];
static unsigned int sounds;
static unsigned int monkey_sounds;
static unsigned int change_sounds;
static int fail_sound;
static int platform_test;
static unsigned char collision_flags;
static ENGINE_OBJECT *transition_object;

static void __attribute__((ms_abi)) log_message(const char *text) { fputs(text, stderr); }
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{ return fopen(path, mode); }
static int __attribute__((ms_abi)) close_file(void *file) { return fclose(file); }
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int origin)
{ return fseek(file, (long)offset, origin); }
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *p,
    unsigned long long size, unsigned long long count, void *file)
{ return fread(p, (size_t)size, (size_t)count, file); }

static int sound(void *context, unsigned short channel, unsigned short sample)
{
    assert(context == &player);
    if (channel == 0 && sample == 5) ++sounds;
    else if (channel == 1 && sample == 20) ++change_sounds;
    else {
        assert(channel == 1 && sample == 21);
        ++monkey_sounds;
    }
    return fail_sound ? -1 : 0;
}

static int player_sound(void *context, unsigned short sample)
{
    (void)context; (void)sample;
    return 0;
}

static int probe(void *context, short x, short y, short *hit)
{
    (void)context; (void)x; (void)y;
    *hit = 0;
    return 0;
}

static int ground(void *context, short *kind, short *delta_y)
{
    (void)context;
    *kind = platform_test && (player.player.flags_high & 0x80) ? 1 : 0;
    *delta_y = 0;
    return 0;
}

static int support(void *context, short *supported)
{
    assert(context == &player);
    *supported = player.player.flags_high & 0x80 ? -1 : 0;
    player.contact_kind = player.surface_kind = 0;
    return 0;
}

static int edge(void *context, short *hit, short *kind, short *x, short *y)
{
    (void)context;
    *hit = *kind = *x = *y = 0;
    return 0;
}

static int transition(void *context, const ENGINE_PLAYER_CALL *call,
    short kind, short x, short y)
{
    assert(context == &player && !kind && !x && !y);
    if (platform_test) return engine_player_begin_ground(&objects, transition_object, &player, call);
    assert(call->handler == 0xf6cc || call->handler == 0xfcb5);
    return engine_player_begin_action(&objects, transition_object, &player, call);
}

static int deflection_transition(void *context, const ENGINE_PLAYER_CALL *call)
{
    assert(context == &player);
    return engine_player_begin_air(&objects, transition_object, &player, call);
}

static void check_tail_grab(void)
{
    DOS64_INPUT keys = {0};
    ENGINE_OBJECT *object = engine_acquire_object(&objects, 0);
    assert(object);
    transition_object = object;
    player.player.body.render_pool = &renders;
    player.player.collision_flags = &collision_flags;
    player.player.probe = probe;
    player.player.transition = deflection_transition;
    player.transition = transition;
    player.ground = ground;
    player.edge = edge;
    player.sound = player_sound;
    for (unsigned int facing = 0; facing < 2; ++facing) {
        for (unsigned int release = 0; release < 4; ++release) {
            assert(engine_enemies_restart(&enemies) == 0);
            ENGINE_LIZARD *tail = 0;
            for (unsigned int i = 0; i < enemies.count; ++i) {
                enemies.lizards[i].destroyed = 1;
                if (!tail && enemies.lizards[i].marker_type == 28) tail = &enemies.lizards[i];
            }
            assert(tail);
            tail->destroyed = 0;
            player.flags = player.pressed = 0;
            player.player.flags_high = 0;
            player.player.immunity = 100;
            player.player.form = 0;
            player.player.handler = 0;
            player.player.body.owner = (RENDER_OWNER){0, 0};
            player.player.body.node->pass_flags = facing ? 8 : 0;
            ENGINE_PLAYER_CALL air = {facing ? 0xae53U : 0xaa97U, 0x6116, 0};
            assert(engine_player_begin_air(&objects, object, &player, &air) == 0);
            RENDER_OWNER camera = {(short)(tail->marker.x - 160), (short)(tail->marker.y - 100)};
            assert(engine_enemies_tick(&enemies, camera) == 0 && tail->timer == 10);
            for (unsigned int i = 0; i < 10; ++i) assert(engine_enemies_tick(&enemies, camera) == 0);
            assert(tail->timer == 0);
            const unsigned char *parts = player.player.body.node->parts;
            int px = (short)(parts[10] | (unsigned int)parts[11] << 8);
            int py = (short)(parts[12] | (unsigned int)parts[13] << 8);
            player.player.body.owner.x = (short)(tail->body.owner.x - (facing ? -px : px));
            player.player.body.owner.y = (short)(tail->body.owner.y - py);
            assert(engine_enemies_tick(&enemies, camera) == 0);
            assert((player.flags & 0x200) && player.swing_source == tail->body.node);
            assert(engine_update_objects(&objects, &keys) == 0);
            assert(player.player.handler == 0xfcb5 && (player.flags & 0x400) &&
                !(player.flags & 0x200));
            assert(engine_enemies_tick(&enemies, camera) == 0 && tail->handler == 0x168e9);
            assert(!!(tail->body.node->pass_flags & 8) == facing);
            RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
            RENDER_FOLLOW_CAMERA follow = {camera, 128};
            RENDER_OWNER previous = player.player.body.owner;
            unsigned int moved = 0;
            for (unsigned int i = 0; i < 100; ++i) {
                assert(engine_update_objects(&objects, &keys) == 0);
                assert(render_follow_camera(&follow, player.player.body.owner,
                    player.player.body.node->pass_flags & 8, player.player.flags_high,
                    collision.width, collision.height, (player.flags & 0x400U) != 0) == 0);
                assert(follow.position.x == camera.x && follow.position.y == camera.y &&
                    follow.horizontal_offset == 128);
                parts = tail->body.node->parts;
                px = (short)(parts[10] | (unsigned int)parts[11] << 8);
                py = (short)(parts[12] | (unsigned int)parts[13] << 8);
                RENDER_OWNER expected = {(short)(tail->body.owner.x + (facing ? -px : px)),
                    (short)(tail->body.owner.y + py)};
                assert(engine_enemies_tick(&enemies, distant) == 0 && tail->object);
                assert(player.player.body.owner.x == expected.x &&
                    player.player.body.owner.y == expected.y);
                if (previous.x != expected.x || previous.y != expected.y) ++moved;
                previous = expected;
                assert(player.player.handler == 0xfcb5 && (player.flags & 0x400));
            }
            assert(moved > 10);
            if (release == 3) {
                assert(engine_enemies_restart(&enemies) == 0);
                assert(!(player.flags & 0x600) && !player.swing_source && !player.swing_animation);
                continue;
            }
            player.pressed = release == 0 ? 0x20 : release == 1 ? 2 : 0x22;
            assert(engine_update_objects(&objects, &keys) == 0 && !(player.flags & 0x400));
            assert(!player.swing_source && !player.swing_animation);
            assert(render_follow_camera(&follow, player.player.body.owner,
                player.player.body.node->pass_flags & 8, player.player.flags_high,
                collision.width, collision.height, (player.flags & 0x400U) != 0) == 0);
            assert(follow.position.x != camera.x || follow.position.y != camera.y ||
                follow.horizontal_offset != 128);
            if (release == 1 || (release == 2 && facing))
                assert(player.player.handler == (facing ? 0xae53U : 0xaa97U));
            else assert(player.player.handler == 0xe410U || player.player.handler == 0xe545U);
            assert(engine_enemies_tick(&enemies, camera) == 0 && tail->timer == 40);
            player.pressed = 0;
            for (unsigned int i = 0; i < 20; ++i)
                assert(engine_update_objects(&objects, &keys) == 0);
            parts = player.player.body.node->parts;
            px = (short)(parts[10] | (unsigned int)parts[11] << 8);
            py = (short)(parts[12] | (unsigned int)parts[13] << 8);
            player.player.body.owner.x = (short)(tail->body.owner.x -
                ((player.player.body.node->pass_flags & 8) ? -px : px));
            player.player.body.owner.y = (short)(tail->body.owner.y - py);
            for (unsigned int i = 0; i < 39; ++i) {
                assert(engine_enemies_tick(&enemies, camera) == 0);
                assert(!(player.flags & 0x200));
            }
            assert(tail->timer == 1);
            assert(engine_enemies_tick(&enemies, camera) == 0 && (player.flags & 0x200));
        }
    }
    assert(engine_enemies_restart(&enemies) == 0);
    assert(engine_release_object(&objects, object) == 0);
}

static void check_ostrich_waiting(void)
{
    unsigned int found = 0;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *marker = &enemies.lizards[i];
        if (marker->marker_type != 52 && marker->marker_type != 53) continue;
        ++found;
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        marker->destroyed = 0;
        ENGINE_OSTRICH_VISUAL *ostrich = &enemies.ostriches[marker->ostrich_index];
        assert(!ostrich->body);
        RENDER_OWNER camera = {(short)(marker->marker.x - 160),
            (short)(marker->marker.y - 100)};
        player.player.body.owner = (RENDER_OWNER){0, 0};
        assert(engine_enemies_tick(&enemies, camera) == 0 && ostrich->body);
        assert(ostrich->position.x == marker->marker.x &&
            ostrich->position.y == marker->marker.y &&
            ostrich->body->parts[19] == 120 && ostrich->body->parts[18] == 1 &&
            !ostrich->head && ostrich->pose == ENGINE_OSTRICH_WAITING);
        memset(pixels, 0, sizeof(pixels));
        assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
            banks, 127, pixels) == 0);
        unsigned int visible = 0;
        for (unsigned int j = 0; j < sizeof(pixels); ++j) visible += pixels[j] != 0;
        assert(visible > 100);
        for (unsigned int tick = 0; tick < 40; ++tick) {
            assert(engine_enemies_tick(&enemies, camera) == 0);
            assert(ostrich->body->parts[19] == 120 && ostrich->body->parts[18] == 1);
        }
        RENDER_OWNER distant = {(short)(marker->marker.x + 112), camera.y};
        assert(engine_enemies_tick(&enemies, distant) == 0 && !ostrich->body &&
            !ostrich->body_object);
        assert(engine_enemies_tick(&enemies, camera) == 0 && ostrich->body);
        assert(engine_enemies_restart(&enemies) == 0 && !ostrich->body &&
            !ostrich->body_object);
    }
    assert(found == 2 && enemies.ostrich_count == 2);
}

static void check_giraffes(void)
{
    unsigned int counts[256] = {0};
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *head = &enemies.lizards[i];
        unsigned int type = head->marker_type;
        if (type != 29 && type != 73 && type != 51) continue;
        ++counts[type];
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        head->destroyed = 0;
        player.flags = 0;
        player.player.flags_high = 0;
        player.player.body.owner = (RENDER_OWNER){0, 0};
        RENDER_OWNER camera = {(short)(head->marker.x - 160), (short)(head->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0 && head->object);
        assert(head->body.owner.x == head->marker.x + (type == 29 ? 11 : type == 73 ? 6 : 5));
        assert(head->body.owner.y == head->marker.y - (type == 73 ? 6 : 0));
        assert(head->body.node->parts[19] == 109 &&
            head->body.node->parts[18] == (type == 51 ? 6 : 0));
        assert(!!(head->body.node->pass_flags & 8) == (type != 29));
        memset(pixels, 0, sizeof(pixels));
        assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
            banks, 127, pixels) == 0);
        unsigned int visible = 0;
        for (unsigned int p = 0; p < sizeof(pixels); ++p) visible += pixels[p] != 0;
        assert(visible);
        player.player.body.owner = head->body.owner;
        player.player.body.motion.velocity_y = UINT32_C(0xffff0000);
        assert(engine_enemies_tick(&enemies, camera) == 0 && !head->entered);
        player.player.body.motion.velocity_y = 0x10000;
        player.player.body.owner.y = (short)(head->body.owner.y + 20);
        assert(engine_enemies_tick(&enemies, camera) == 0 && !head->entered);
        player.player.body.motion.velocity_y = 0x10000;
        player.player.body.owner.x = (short)(head->body.owner.x + 100);
        assert(engine_enemies_tick(&enemies, camera) == 0 && !head->entered);
        player.player.body.owner = head->body.owner;
        assert(engine_enemies_tick(&enemies, camera) == 0 && head->entered);
        assert(player.player.flags_high & 0x80);
        assert(engine_enemies_tick(&enemies, camera) == 0);
        if (type == 51) {
            assert(player.flags & 0x20);
        } else {
            assert(head->timer == 60);
            for (unsigned int tick = 0; tick < 30; ++tick)
                assert(engine_enemies_tick(&enemies, camera) == 0);
            assert(head->timer == 30 && !(player.flags & (type == 29 ? 0x10 : 0x20)));
            assert(engine_enemies_tick(&enemies, camera) == 0);
            assert(head->timer == 29 && (player.flags & (type == 29 ? 0x10 : 0x20)));
            player.player.body.owner.x = (short)(head->body.owner.x + 100);
            assert(engine_enemies_tick(&enemies, camera) == 0 && !head->entered);
            assert(engine_enemies_tick(&enemies, camera) == 0);
            assert(!(player.flags & (type == 29 ? 0x10 : 0x20)));
        }
        RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
        assert(engine_enemies_tick(&enemies, distant) == 0 && !head->object);
    }
    assert(counts[29] == 2 && counts[73] == 7 && counts[51] == 5 &&
        enemies.giraffe_count == 14);
    assert(engine_enemies_restart(&enemies) == 0);
}

static void check_giraffe_landing(void)
{
    assert(engine_enemies_restart(&enemies) == 0);
    ENGINE_LIZARD *head = 0;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        enemies.lizards[i].destroyed = 1;
        if (!head && enemies.lizards[i].marker_type == 29) head = &enemies.lizards[i];
    }
    assert(head);
    head->destroyed = 0;
    ENGINE_OBJECT *object = engine_acquire_object(&objects, 0);
    assert(object);
    transition_object = object;
    player.flags = player.pressed = 0;
    player.player.flags_high = 0;
    player.player.handler = 0;
    player.player.body.node->pass_flags = 0;
    player.player.body.owner = (RENDER_OWNER){0, 0};
    player.player.body.motion.velocity_y = 0x30000;
    player.support = support;
    platform_test = 1;
    RENDER_OWNER camera = {(short)(head->marker.x - 160), (short)(head->marker.y - 100)};
    assert(engine_enemies_tick(&enemies, camera) == 0);
    player.player.body.owner = head->body.owner;
    player.player.body.owner.y -= 9;
    ENGINE_PLAYER_CALL air = {0xaa97, 0x6116, 0};
    assert(engine_player_begin_air(&objects, object, &player, &air) == 0);
    DOS64_INPUT keys = {0};
    for (unsigned int i = 0; i < 10 && !(player.player.flags_high & 0x80); ++i) {
        assert(engine_enemies_tick(&enemies, camera) == 0);
        if (!(player.player.flags_high & 0x80)) assert(engine_update_objects(&objects, &keys) == 0);
    }
    assert(player.player.flags_high & 0x80);
    assert(engine_update_objects(&objects, &keys) == 0);
    assert(object->behavior == &engine_player_ground_behavior);
    assert(player.player.body.owner.y == head->body.owner.y);
    for (unsigned int i = 0; i < 5; ++i) {
        assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(head->entered && (player.player.flags_high & 0x80));
        assert(engine_update_objects(&objects, &keys) == 0);
    }
    player.player.body.owner.x = (short)(head->body.owner.x + 100);
    assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(!head->entered && !(player.player.flags_high & 0x80));
    platform_test = 0;
    assert(engine_enemies_restart(&enemies) == 0);
    assert(engine_release_object(&objects, object) == 0);
}

static void check_floating_logs(void)
{
    unsigned int count = 0;
    ENGINE_OBJECT *object = engine_acquire_object(&objects, 0);
    assert(object);
    transition_object = object;
    player.player.body.render_pool = &renders;
    player.player.collision_flags = &collision_flags;
    player.player.probe = probe;
    player.ground = ground;
    player.edge = edge;
    player.sound = player_sound;
    player.support = support;
    platform_test = 1;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *log = &enemies.lizards[i];
        if (log->marker_type != 44) continue;
        ++count;
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        log->destroyed = 0;
        player.flags = player.pressed = 0;
        player.player.flags_high = 0;
        player.player.handler = 0;
        player.player.body.node->pass_flags = 0;
        player.player.body.owner = (RENDER_OWNER){0, 0};
        player.player.body.motion = (ENGINE_MOTION){0};
        RENDER_OWNER camera = {(short)(log->marker.x - 160), (short)(log->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0 && log->object);
        assert(log->body.node->parts[19] == 110 && (log->body.node->pass_flags & 8));
        memset(pixels, 0, sizeof(pixels));
        assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
            banks, 127, pixels) == 0);
        unsigned int visible = 0;
        for (unsigned int j = 0; j < sizeof(pixels); ++j) visible += pixels[j] != 0;
        assert(visible);
        RENDER_BOUNDS bounds;
        assert(render_object_bounds(log->body.node, &bounds) == 0);
        player.player.body.owner = (RENDER_OWNER){(short)(bounds.right + 1), log->body.owner.y};
        player.player.body.motion.velocity_y = 0x10000;
        assert(engine_enemies_tick(&enemies, camera) == 0 && !log->entered &&
            !(player.player.flags_high & 0x80));
        player.player.body.owner = log->body.owner;
        player.player.body.motion.velocity_y = UINT32_C(0xffff0000);
        assert(engine_enemies_tick(&enemies, camera) == 0 && !log->entered &&
            !(player.player.flags_high & 0x80));
        player.player.body.owner = log->body.owner;
        player.player.body.owner.y -= 9;
        player.player.body.motion.velocity_y = 0x30000;
        ENGINE_PLAYER_CALL air = {0xaa97, 0x6116, 0};
        assert(engine_player_begin_air(&objects, object, &player, &air) == 0);
        DOS64_INPUT keys = {0};
        for (unsigned int tick = 0; tick < 10 && !log->entered; ++tick) {
            assert(engine_enemies_tick(&enemies, camera) == 0);
            if (!log->entered) assert(engine_update_objects(&objects, &keys) == 0);
        }
        assert(log->entered && (player.player.flags_high & 0x80));
        assert(engine_update_objects(&objects, &keys) == 0);
        assert(object->behavior == &engine_player_ground_behavior);
        int deepest = 0, released = 0;
        for (unsigned int tick = 0; tick < 400; ++tick) {
            assert(engine_enemies_tick(&enemies, camera) == 0);
            int depth = log->body.owner.y - log->marker.y;
            if (depth > deepest) deepest = depth;
            if (!(player.player.flags_high & 0x80)) { released = 1; break; }
            assert(player.player.body.owner.y == log->body.owner.y);
            assert(engine_update_objects(&objects, &keys) == 0);
        }
        assert(deepest >= 16 && released && log->timer > 0);
        player.player.body.owner = log->body.owner;
        player.player.body.motion.velocity_y = 0x10000;
        assert(engine_enemies_tick(&enemies, camera) == 0 && !log->entered &&
            !(player.player.flags_high & 0x80));
        player.player.body.owner.x = 0;
        for (unsigned int tick = 0; tick < 500 && log->handler != 0x1af4b; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(log->handler == 0x1af4b);
        RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
        assert(engine_enemies_tick(&enemies, distant) == 0 && !log->object);
        assert(engine_enemies_tick(&enemies, camera) == 0 && log->object);
    }
    assert(count == 4 && enemies.log_count == 4);
    platform_test = 0;
    assert(engine_enemies_restart(&enemies) == 0);
    assert(engine_release_object(&objects, object) == 0);
}

static void check_monkeys(void)
{
    unsigned int counts[256] = {0};
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *monkey = &enemies.lizards[i];
        unsigned int type = monkey->marker_type, entry, slot;
        if (type == 5 || type == 7) { entry = 0x1470e; slot = 114; }
        else if (type == 23 || type == 24 || type == 26) { entry = 0x14727; slot = 115; }
        else if (type == 6) { entry = 0x147f0; slot = 116; }
        else if (type == 8) { entry = 0x148c8; slot = 112; }
        else if (type == 25 || type == 62 || type == 64) { entry = 0x148fa; slot = 113; }
        else continue;
        ++counts[type];
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        monkey->destroyed = 0;
        player.player.body.owner = (RENDER_OWNER){0, 0};
        RENDER_OWNER camera = {(short)(monkey->marker.x - 160), (short)(monkey->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(monkey->object && monkey->body.animation.script.position == 0x1427a &&
            monkey->body.animation.visual.position == entry + 19);
        assert(monkey->body.node->parts[19] == slot && monkey->body.node->parts[18] == 0);
        assert(!!(monkey->body.node->pass_flags & 8) ==
            (type == 5 || type == 23 || type == 26 || type == 8 ||
                type == 25 || type == 62 || type == 64));
        memset(pixels, 0, sizeof(pixels));
        assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
            banks, 127, pixels) == 0);
        unsigned int visible = 0;
        for (unsigned int j = 0; j < sizeof(pixels); ++j) visible += pixels[j] != 0;
        assert(visible);
        static const unsigned char animated_frames[] = {0, 1, 2, 3, 4, 3, 2, 3, 4};
        int animated = type == 8 || type == 25 || type == 62 || type == 64;
        for (unsigned int tick = 1; tick <= 64; ++tick) {
            int result = engine_enemies_tick(&enemies, camera);
            if (result != 0) fprintf(stderr, "monkey type %u tick %u script %x visual %x\n",
                type, tick, monkey->body.animation.script.position, monkey->body.animation.visual.position);
            assert(result == 0);
            assert(monkey->body.node->parts[19] == slot);
            assert(monkey->body.node->parts[18] ==
                (animated ? animated_frames[tick / 8] : 0));
        }
        RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
        assert(engine_enemies_tick(&enemies, distant) == 0 && !monkey->object);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->object &&
            monkey->body.node->parts[18] == 0);
        assert(engine_enemies_restart(&enemies) == 0 && !monkey->object);
    }
    assert(counts[5] == 7 && counts[6] == 2 && counts[7] == 8 &&
        counts[8] == 12 && counts[23] == 1 && counts[24] == 0 &&
        counts[25] == 1 && counts[26] == 1 && counts[62] == 1 && counts[64] == 1);
}

static void check_tails(void)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *tail = &enemies.lizards[i];
        if (tail->marker_type != 28) continue;
        ++count;
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        tail->destroyed = 0;
        player.player.body.owner = (RENDER_OWNER){0, 0};
        RENDER_OWNER camera = {(short)(tail->marker.x - 160), (short)(tail->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0 && tail->object);
        assert(tail->body.node->parts[19] == 126 && tail->body.node->parts[18] == 0);
        memset(pixels, 0, sizeof(pixels));
        assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
            banks, 127, pixels) == 0);
        unsigned int visible = 0;
        for (unsigned int j = 0; j < sizeof(pixels); ++j) visible += pixels[j] != 0;
        assert(visible);
        for (unsigned int tick = 0; tick < 8; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(tail->body.node->parts[18] != 0);
        RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
        assert(engine_enemies_tick(&enemies, distant) == 0 && !tail->object);
    }
    assert(count == 11 && enemies.tail_count == 11);
    assert(engine_enemies_restart(&enemies) == 0);
}

static void check_up_monkeys(void)
{
    ENGINE_OBJECT *player_object = engine_acquire_object(&objects, 0);
    assert(player_object);
    player.player.body.render_pool = &renders;
    player.player.collision_flags = &collision_flags;
    player.player.probe = probe;
    player.ground = ground;
    player.edge = edge;
    player.sound = player_sound;
    ENGINE_PLAYER_CALL held = {0xf6cc, 0, 0};
    unsigned int count = 0;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *monkey = &enemies.lizards[i];
        if (monkey->marker_type != 6) continue;
        ++count;
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        monkey->destroyed = 0;
        player.flags = 0;
        player.player.body.owner = (RENDER_OWNER){0, 0};
        RENDER_OWNER camera = {(short)(monkey->marker.x - 160), (short)(monkey->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->object);
        assert(monkey->target.x == monkey->marker.x);
        assert(monkey->target.y == (monkey->marker.x == 4576 ? 96 : 176));
        player.player.body.owner = monkey->body.owner;
        RENDER_BOUNDS a, b;
        assert(render_object_bounds(monkey->body.node, &a) == 0);
        assert(render_object_bounds(player.player.body.node, &b) == 0);
        player.player.body.owner.x += (short)((a.left + a.right - b.left - b.right) / 2);
        player.player.body.owner.y += (short)((a.top + a.bottom - b.top - b.bottom) / 2);
        short hit;
        assert(render_objects_hit(monkey->body.node, player.player.body.node, &hit) == 0 && hit);
        player.player.body.motion.velocity_y = 0x10000;
        player.anchor_x = monkey->marker.x;
        player.anchor_y = monkey->marker.y;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.flags = 2;
        player.anchor_x++;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        --player.anchor_x;
        player.player.body.motion.velocity_y = 0;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.motion.velocity_y = UINT32_C(0xffff0000);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.motion.velocity_y = 0x10000;
        RENDER_OWNER original = player.player.body.owner;
        player.player.body.owner.x += 200;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.owner = original;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x1745c);
        assert(monkey->timer == 64 && (player.flags & 4) && !(player.flags & 2));
        assert(player.tether_target.x == monkey->attachment.x &&
            player.tether_target.y == monkey->attachment.y);
        assert(animation_program_initialize(&player.player.body.animation,
            animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE,
            0x61e2, animation_movement_data, ANIMATION_MOVEMENT_SIZE,
            ANIMATION_MOVEMENT_BASE) == 0);
        player.player.handler = 0xaa97;
        assert(engine_player_begin_action(&objects, player_object, &player, &held) == 0);
        RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
        for (unsigned int tick = 0; tick < 12; ++tick) {
            assert(engine_player_begin_action(&objects, player_object, &player, &held) == 0);
            RENDER_OWNER before = player.player.body.owner;
            RENDER_OWNER attachment = monkey->attachment;
            assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->object);
            assert(monkey->timer == 63 - (short)tick && (player.flags & 4));
            assert(player.player.body.owner.x - before.x == monkey->attachment.x - attachment.x);
            assert(player.player.body.owner.y - before.y == monkey->attachment.y - attachment.y);
            assert(player.tether_target.x == monkey->attachment.x &&
                player.tether_target.y == monkey->attachment.y);
        }
        assert(monkey->timer == 52 && monkey_sounds == count - 1);
        int index = (player.player.body.owner.y - monkey->target.y) / 4;
        assert(index >= 0 && (unsigned int)index < ANIMATION_RHINO_VELOCITY_COUNT);
        const unsigned char *p = animation_rhino_velocities + index * 4;
        uint32_t speed = (uint32_t)p[0] | (uint32_t)p[1] << 8 |
            (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
        player.player.body.animation.counter = 99;
        assert(engine_enemies_tick(&enemies, distant) == 0 && monkey_sounds == count);
        assert(player.player.body.animation.counter == 0);
        assert(monkey->timer == 51 && !(player.flags & 4) && (player.flags & 2));
        assert(player.anchor_x == monkey->target.x && player.anchor_y == monkey->target.y);
        assert(player.player.body.motion.velocity_y == 0U - speed &&
            player.player.body.motion.velocity_x == 0);
        assert(engine_player_begin_action(&objects, player_object, &player, &held) == 0);
        assert(player.player.handler == 0xaa97 || player.player.handler == 0xae53);
        assert(player_object->behavior == &engine_player_air_behavior && (player.flags & 2));
        assert(player.player.body.motion.velocity_y == 0U - speed + 0x4e00U);
        for (unsigned int tick = 0; tick < 51; ++tick)
            assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->object);
        assert(monkey->timer == 0);
        assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->handler == 0x17116);
        assert(engine_enemies_tick(&enemies, distant) == 0 && !monkey->object);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->object);
        monkey->handler = 0x1745c;
        monkey->timer = 52;
        player.flags = 4;
        player.player.body.owner.y = (short)(monkey->target.y - 1);
        assert(engine_enemies_tick(&enemies, camera) == -1 && monkey_sounds == count);
        player.player.body.owner.y = (short)(monkey->target.y + ANIMATION_RHINO_VELOCITY_COUNT * 4);
        assert(engine_enemies_tick(&enemies, camera) == -1 && monkey_sounds == count);
        player.player.body.owner.y = (short)(monkey->target.y + 100);
        fail_sound = 1;
        assert(engine_enemies_tick(&enemies, camera) == -1 && monkey_sounds == count + 1);
        fail_sound = 0;
        --monkey_sounds;
        monkey->timer = 52;
        player.flags = 4;
        assert(engine_enemies_restart(&enemies) == 0 && !(player.flags & 4));
    }
    assert(count == 2);
    assert(engine_release_object(&objects, player_object) == 0);
}

static void check_down_monkeys(void)
{
    unsigned int counts[2] = {0, 0}, missing = 0;
    ENGINE_OBJECT *player_object = engine_acquire_object(&objects, 0);
    assert(player_object);
    ENGINE_PLAYER_CALL held = {0xf6cc, 0, 0};
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *monkey = &enemies.lizards[i];
        if (monkey->marker_type != 8 && monkey->marker_type != 25 &&
            monkey->marker_type != 62 && monkey->marker_type != 64) continue;
        ++counts[monkey->marker_type != 8];
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        monkey->destroyed = 0;
        player.flags = 0;
        player.player.body.owner = (RENDER_OWNER){0, 0};
        RENDER_OWNER camera = {(short)(monkey->marker.x - 160), (short)(monkey->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->object);
        short expected_y = -16;
        for (unsigned int row = (unsigned int)monkey->marker.y / 16 + 1;
            row < collision.height / 2; ++row) {
            unsigned int type;
            RENDER_OWNER position;
            assert(engine_map_marker(&collision, (unsigned int)monkey->marker.x / 16,
                row, &type, &position) == 0);
            if ((type >= 5 && type <= 8) || (type >= 23 && type <= 26) ||
                (type >= 62 && type <= 69)) {
                expected_y = position.y;
                break;
            }
        }
        if (expected_y == -16) ++missing;
        if (monkey->marker.x == 1728 && monkey->marker.y == 96) assert(expected_y == 304);
        else if (monkey->marker.x == 5008 && monkey->marker.y == 224) assert(expected_y == 368);
        else if (monkey->marker.x == 5744 && monkey->marker.y == 256) assert(expected_y == 368);
        else assert(expected_y == -16);
        assert(monkey->target.x == monkey->marker.x && monkey->target.y == expected_y);
        player.player.body.owner = monkey->body.owner;
        RENDER_BOUNDS a, b;
        assert(render_object_bounds(monkey->body.node, &a) == 0);
        assert(render_object_bounds(player.player.body.node, &b) == 0);
        player.player.body.owner.x += (short)((a.left + a.right - b.left - b.right) / 2);
        player.player.body.owner.y += (short)((a.top + a.bottom - b.top - b.bottom) / 2);
        short hit;
        assert(render_objects_hit(monkey->body.node, player.player.body.node, &hit) == 0 && hit);
        player.anchor_x = monkey->marker.x;
        player.anchor_y = monkey->marker.y;
        player.player.body.motion.velocity_y = 0x10000;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.flags = 2;
        ++player.anchor_y;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        --player.anchor_y;
        player.player.body.motion.velocity_y = 0;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.motion.velocity_y = UINT32_C(0xffff0000);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.motion.velocity_y = 0x10000;
        RENDER_OWNER original = player.player.body.owner;
        player.player.body.owner.x += 200;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.owner = original;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x1765f);
        assert(monkey->timer == 64 && (player.flags & 4) && !(player.flags & 2));
        assert(monkey->body.animation.script.position ==
            (monkey->marker_type == 8 ? 0x1492cU : 0x14972U));
        assert(animation_program_initialize(&player.player.body.animation,
            animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE,
            0x61e2, animation_movement_data, ANIMATION_MOVEMENT_SIZE,
            ANIMATION_MOVEMENT_BASE) == 0);
        player.player.handler = 0xaa97;
        assert(engine_player_begin_action(&objects, player_object, &player, &held) == 0);
        RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
        unsigned int sound_before = monkey_sounds;
        for (unsigned int tick = 0; tick < 31; ++tick) {
            assert(engine_player_begin_action(&objects, player_object, &player, &held) == 0);
            RENDER_OWNER before = player.player.body.owner;
            RENDER_OWNER attachment = monkey->attachment;
            assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->object);
            assert(monkey->timer == 63 - (short)tick && (player.flags & 4));
            assert(player.player.body.owner.x - before.x == monkey->attachment.x - attachment.x);
            assert(player.player.body.owner.y - before.y == monkey->attachment.y - attachment.y);
            assert(player.tether_target.x == monkey->attachment.x &&
                player.tether_target.y == monkey->attachment.y);
            assert(monkey->body.node->parts[19] == (monkey->marker_type == 8 ? 116 : 117));
            assert(monkey->body.node->parts[18] ==
                (tick < 6 ? 1 : tick < 10 ? 2 : tick < 16 ? 3 : tick < 26 ? 4 : 5));
        }
        assert(monkey->timer == 33 && monkey_sounds == sound_before);
        player.player.body.animation.counter = 99;
        player.player.body.motion.velocity_x = 0x10000;
        assert(engine_enemies_tick(&enemies, distant) == 0 && monkey_sounds == sound_before + 1);
        assert(monkey->timer == 32 && !(player.flags & 4) && (player.flags & 2));
        assert(player.player.body.animation.counter == 0 &&
            player.player.body.motion.velocity_x == 0 &&
            player.player.body.motion.velocity_y == 0x20000);
        assert(player.anchor_x == monkey->target.x && player.anchor_y == expected_y);
        assert(engine_player_begin_action(&objects, player_object, &player, &held) == 0);
        assert(player_object->behavior == &engine_player_air_behavior && (player.flags & 2));
        assert(player.player.body.motion.velocity_y == 0x24e00);
        for (unsigned int tick = 0; tick < 32; ++tick)
            assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->object);
        assert(monkey->timer == 0);
        assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->handler == 0x17116);
        assert(engine_enemies_tick(&enemies, distant) == 0 && !monkey->object);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->object);
        monkey->handler = 0x1765f;
        monkey->timer = 33;
        player.flags = 4;
        fail_sound = 1;
        assert(engine_enemies_tick(&enemies, camera) == -1 && monkey_sounds == sound_before + 2);
        fail_sound = 0;
        monkey->timer = 33;
        player.flags = 4;
        assert(engine_enemies_restart(&enemies) == 0 && !(player.flags & 4));
    }
    assert(counts[0] == 12 && counts[1] == 3 && missing == 12);
    assert(engine_release_object(&objects, player_object) == 0);
}

static void check_horizontal_monkeys(void)
{
    static const struct { short x, y, target; unsigned char type; } expected[] = {
        {384, 48, -16, 5}, {5808, 64, 5088, 5}, {4912, 80, 4704, 5},
        {1584, 96, 1440, 23}, {4576, 96, 4976, 7}, {5904, 112, 6064, 7},
        {288, 128, 384, 7}, {1520, 176, 1808, 7}, {1808, 176, 2080, 7},
        {5808, 176, 4864, 5}, {6144, 176, 5968, 5}, {4496, 224, 5008, 7},
        {4784, 256, 5744, 7}, {1728, 304, 1520, 5}, {4784, 368, 4576, 26},
        {5008, 368, 4784, 5}, {5744, 368, 6144, 7}
    };
    unsigned int counts[256] = {0};
    ENGINE_OBJECT *player_object = engine_acquire_object(&objects, 0);
    assert(player_object);
    transition_object = player_object;
    player.transition = transition;
    DOS64_INPUT keys = {0};
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *monkey = &enemies.lizards[i];
        unsigned int type = monkey->marker_type;
        if (type != 5 && type != 7 && type != 23 && type != 26) continue;
        ++counts[type];
        int left = type != 7;
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        monkey->destroyed = 0;
        player.flags = 0;
        player.player.body.owner = (RENDER_OWNER){0, 0};
        RENDER_OWNER camera = {(short)(monkey->marker.x - 160), (short)(monkey->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->object);
        short expected_x = (short)(left ? -16 : (int)collision.width * 8);
        int column = monkey->marker.x / 16 + (left ? -1 : 1);
        for (; column >= 0 && column < (int)collision.width / 2; column += left ? -1 : 1) {
            unsigned int marker;
            RENDER_OWNER position;
            assert(engine_map_marker(&collision, (unsigned int)column,
                (unsigned int)monkey->marker.y / 16, &marker, &position) == 0);
            if ((marker >= 5 && marker <= 8) || (marker >= 23 && marker <= 26) ||
                (marker >= 62 && marker <= 69)) {
                expected_x = position.x;
                break;
            }
        }
        assert(monkey->target.x == expected_x && monkey->target.y == monkey->marker.y);
        unsigned int match = 0;
        for (unsigned int j = 0; j < sizeof(expected) / sizeof(expected[0]); ++j)
            if (expected[j].x == monkey->marker.x && expected[j].y == monkey->marker.y &&
                expected[j].type == type && expected[j].target == expected_x) ++match;
        assert(match == 1);
        player.player.body.owner = monkey->body.owner;
        RENDER_BOUNDS a, b;
        assert(render_object_bounds(monkey->body.node, &a) == 0);
        assert(render_object_bounds(player.player.body.node, &b) == 0);
        player.player.body.owner.x += (short)((a.left + a.right - b.left - b.right) / 2);
        player.player.body.owner.y += (short)((a.top + a.bottom - b.top - b.bottom) / 2);
        short hit;
        assert(render_objects_hit(monkey->body.node, player.player.body.node, &hit) == 0 && hit);
        player.anchor_x = monkey->marker.x;
        player.anchor_y = monkey->marker.y;
        player.player.body.motion.velocity_y = 0x10000;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.flags = 2;
        ++player.anchor_x;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        --player.anchor_x;
        player.player.body.motion.velocity_y = 0;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.motion.velocity_y = UINT32_C(0xffff0000);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.motion.velocity_y = 0x10000;
        RENDER_OWNER original = player.player.body.owner;
        player.player.body.owner.x += 200;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.owner = original;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17218);
        assert(monkey->timer == 80 && (player.flags & 4) && !(player.flags & 2));
        assert(monkey->body.animation.script.position ==
            (type == 5 || type == 7 ? 0x14740U : 0x1477cU));
        assert(animation_program_initialize(&player.player.body.animation,
            animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE,
            0x61e2, animation_movement_data, ANIMATION_MOVEMENT_SIZE,
            ANIMATION_MOVEMENT_BASE) == 0);
        player.player.handler = 0xaa97;
        player_object->context = &player;
        player_object->behavior = &engine_player_air_behavior;
        assert(engine_update_objects(&objects, &keys) == 0 && player.player.handler == 0xf6cc);
        RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
        unsigned int sound_before = monkey_sounds;
        for (unsigned int tick = 0; tick < 42; ++tick) {
            assert(engine_update_objects(&objects, &keys) == 0);
            RENDER_OWNER before = player.player.body.owner, attachment = monkey->attachment;
            assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->object);
            assert(monkey->timer == 79 - (short)tick && (player.flags & 4));
            assert(player.player.body.owner.x - before.x == monkey->attachment.x - attachment.x);
            assert(player.player.body.owner.y - before.y == monkey->attachment.y - attachment.y);
            assert(player.tether_target.x == monkey->attachment.x &&
                player.tether_target.y == monkey->attachment.y);
            assert(monkey_sounds == sound_before + (tick >= 24));
            assert(monkey->body.node->parts[19] == (type == 5 || type == 7 ? 114 : 115));
            assert(monkey->body.node->parts[18] == (tick < 8 ? 1 :
                tick < 14 ? 2 : tick < 30 ? 3 : tick < 36 ? 4 : tick < 40 ? 5 : 6));
        }
        assert(monkey->timer == 38);
        int distance = monkey->target.x - player.player.body.owner.x;
        if (distance < 0) distance = -distance;
        unsigned int index = (unsigned int)(distance + 32) / 4;
        if (index >= ANIMATION_MONKEY_VELOCITY_COUNT)
            fprintf(stderr, "horizontal monkey %u at %d,%d target %d index %u\n",
                type, monkey->marker.x, monkey->marker.y, expected_x, index);
        assert(index < ANIMATION_MONKEY_VELOCITY_COUNT);
        const unsigned char *p = animation_monkey_velocities + index * 4;
        uint32_t speed = (uint32_t)p[0] | (uint32_t)p[1] << 8 |
            (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24;
        player.player.body.animation.counter = 99;
        assert(engine_enemies_tick(&enemies, distant) == 0);
        assert(monkey->timer == 37 && !(player.flags & 4) && (player.flags & 2));
        assert(player.player.body.animation.counter == 0 &&
            player.player.body.motion.velocity_x == (left ? UINT32_C(0xfff70000) : 0x90000) &&
            player.player.body.motion.velocity_y == 0U - speed);
        assert(player.anchor_x == expected_x && player.anchor_y == monkey->marker.y);
        assert(engine_update_objects(&objects, &keys) == 0);
        assert(player_object->behavior == &engine_player_air_behavior && (player.flags & 2));
        assert(player.player.body.motion.velocity_y == 0U - speed + 0x4e00U);
        for (unsigned int tick = 0; tick < 37; ++tick)
            assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->object);
        assert(monkey->timer == 0);
        assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->handler == 0x17116);
        assert(engine_enemies_tick(&enemies, distant) == 0 && !monkey->object);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->object);
        monkey->handler = 0x17218;
        monkey->timer = 56;
        player.flags = 4;
        fail_sound = 1;
        assert(engine_enemies_tick(&enemies, camera) == -1 && monkey_sounds == sound_before + 2);
        fail_sound = 0;
        monkey->timer = 38;
        player.flags = 4;
        monkey->target.x = (short)(player.player.body.owner.x + 4096);
        assert(engine_enemies_tick(&enemies, camera) == -1);
        assert(engine_enemies_restart(&enemies) == 0 && !(player.flags & 4));
    }
    assert(counts[5] == 7 && counts[7] == 8 && counts[23] == 1 && counts[26] == 1);
    assert(engine_release_object(&objects, player_object) == 0);
}

static void check_monkey_roar(void)
{
    unsigned int found = 0;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *monkey = &enemies.lizards[i];
        unsigned int type = monkey->marker_type;
        if (type != 23 && type != 25 && type != 26 && type != 62 && type != 64) continue;
        ++found;
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        monkey->destroyed = 0;
        player.flags = player.roar_pulse = 0;
        player.player.body.owner = (RENDER_OWNER){0, 0};
        RENDER_OWNER camera = {(short)(monkey->marker.x - 160), (short)(monkey->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->object);
        unsigned int alt = type == 23 ? 69 : type == 25 ? 68 :
            type == 26 ? 65 : type == 62 ? 24 : 67;
        int horizontal = type == 23 || type == 62 || type == 64;
        RENDER_OWNER original = monkey->body.owner;
        player.player.body.owner = (RENDER_OWNER){(short)(original.x + 80), original.y};
        player.roar_pulse = 1;
        assert(engine_enemies_tick(&enemies, camera) == 0 &&
            monkey->handler == 0x17116 && monkey->monkey_variant == type);
        player.player.body.owner = (RENDER_OWNER){original.x, (short)(original.y - 80)};
        assert(engine_enemies_tick(&enemies, camera) == 0 &&
            monkey->handler == 0x17116 && monkey->monkey_variant == type);
        player.player.body.owner = (RENDER_OWNER){(short)(original.x + 79), (short)(original.y - 79)};
        assert(engine_enemies_tick(&enemies, camera) == 0 &&
            monkey->handler == 0x1783e && monkey->timer == 18 && monkey->monkey_variant == alt);
        player.roar_pulse = 0;
        unsigned int before = change_sounds;
        RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
        for (unsigned int tick = 0; tick < 18; ++tick) {
            assert(engine_enemies_tick(&enemies, distant) == 0 && monkey->object);
            assert(monkey->timer == 17 - (short)tick && change_sounds == before);
        }
        assert(monkey->body.owner.x == original.x && monkey->body.owner.y == original.y);
        assert(engine_enemies_tick(&enemies, distant) == 0 && change_sounds == before + 1);
        assert(monkey->handler == 0x17116 && monkey->monkey_variant == alt);
        assert(!!(monkey->body.node->pass_flags & 8) == (type == 64));
        assert(monkey->body.node->parts[19] == (horizontal ? 115 : 117));
        if (type == 23 || type == 62) assert(monkey->target.x > monkey->marker.x &&
            monkey->target.y == monkey->marker.y);
        else if (type == 64) assert(monkey->target.x < monkey->marker.x &&
            monkey->target.y == monkey->marker.y);
        else assert(monkey->target.x == monkey->marker.x &&
            monkey->target.y < monkey->marker.y);
        if (horizontal) {
            int direction = type == 64 ? -1 : 1;
            int limit = (int)collision.width / 2;
            short expected = (short)(direction < 0 ? -16 : limit * 16);
            int row = monkey->marker.y / 16;
            for (int col = monkey->marker.x / 16 + direction;
                col >= 0 && col < limit; col += direction) {
                unsigned int marker;
                RENDER_OWNER position;
                assert(engine_map_marker(&collision, (unsigned int)col,
                    (unsigned int)row, &marker, &position) == 0);
                if ((marker >= 5 && marker <= 8) ||
                    (marker >= 23 && marker <= 26) ||
                    (marker >= 62 && marker <= 69)) {
                    expected = position.x;
                    break;
                }
            }
            assert(monkey->target.x == expected);
        }
        player.player.body.owner = monkey->body.owner;
        RENDER_BOUNDS a, b;
        assert(render_object_bounds(monkey->body.node, &a) == 0 &&
            render_object_bounds(player.player.body.node, &b) == 0);
        player.player.body.owner.x += (short)((a.left + a.right - b.left - b.right) / 2);
        player.player.body.owner.y += (short)((a.top + a.bottom - b.top - b.bottom) / 2);
        player.anchor_x = monkey->marker.x;
        player.anchor_y = monkey->marker.y;
        player.flags = 2;
        player.player.body.motion.velocity_y = 0x10000;
        assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(monkey->handler == (horizontal ? 0x17218U : 0x1745cU));
        assert(monkey->body.animation.script.position == (horizontal ? 0x1477cU : 0x14859U));
        unsigned int hold = horizontal ? 42 : 12;
        for (unsigned int tick = 0; tick < hold; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0 && (player.flags & 4));
        uint32_t expected_vertical = 0;
        if (horizontal) {
            int distance = monkey->target.x - player.player.body.owner.x;
            if (distance < 0) distance = -distance;
            unsigned int index = (unsigned int)(distance + 32) / 4;
            assert(index < ANIMATION_MONKEY_VELOCITY_COUNT);
            const unsigned char *p = animation_monkey_velocities + index * 4;
            expected_vertical = 0U - ((uint32_t)p[0] | (uint32_t)p[1] << 8 |
                (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24);
        }
        assert(engine_enemies_tick(&enemies, camera) == 0 && (player.flags & 2) && !(player.flags & 4));
        assert(player.player.body.motion.velocity_x == (type == 64 ? UINT32_C(0xfff70000) :
            horizontal ? 0x90000U : 0));
        assert(player.player.body.motion.velocity_y & UINT32_C(0x80000000));
        if (horizontal) assert(player.player.body.motion.velocity_y == expected_vertical);
        unsigned int remaining = horizontal ? 37 : 51;
        for (unsigned int tick = 0; tick < remaining; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        player.player.body.owner = monkey->body.owner;
        player.roar_pulse = 1;
        assert(engine_enemies_tick(&enemies, camera) == 0 &&
            monkey->handler == 0x1783e && monkey->monkey_variant == type);
        player.roar_pulse = 0;
        for (unsigned int tick = 0; tick < 18; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0);
        fail_sound = 1;
        assert(engine_enemies_tick(&enemies, camera) == -1);
        fail_sound = 0;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x17116);
        assert(monkey->monkey_variant == type && (monkey->body.node->pass_flags & 8));
        player.roar_pulse = 1;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x1783e);
        player.roar_pulse = 0;
        for (unsigned int tick = 0; tick < 19; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(monkey->monkey_variant == alt);
        assert(engine_enemies_tick(&enemies, distant) == 0 && !monkey->object);
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->monkey_variant == alt);
        assert(monkey->body.node->parts[19] == (horizontal ? 115 : 117));
        if (type == 23 || type == 62) assert(monkey->target.x > monkey->marker.x);
        else if (type == 64) assert(monkey->target.x < monkey->marker.x);
        else assert(monkey->target.y < monkey->marker.y);
        player.player.body.owner = monkey->body.owner;
        assert(render_object_bounds(monkey->body.node, &a) == 0 &&
            render_object_bounds(player.player.body.node, &b) == 0);
        player.player.body.owner.x += (short)((a.left + a.right - b.left - b.right) / 2);
        player.player.body.owner.y += (short)((a.top + a.bottom - b.top - b.bottom) / 2);
        player.anchor_x = monkey->marker.x;
        player.anchor_y = monkey->marker.y;
        player.flags = 2;
        player.player.body.motion.velocity_y = 0x10000;
        assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(monkey->handler == (horizontal ? 0x17218U : 0x1745cU));
        for (unsigned int tick = 0; tick < hold; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0 && (player.flags & 4));
        assert(engine_enemies_tick(&enemies, camera) == 0 && (player.flags & 2) &&
            !(player.flags & 4));
        assert(player.player.body.motion.velocity_x == (type == 64 ? UINT32_C(0xfff70000) :
            horizontal ? 0x90000U : 0));
        assert(player.player.body.motion.velocity_y & UINT32_C(0x80000000));
        for (unsigned int tick = 0; tick <= remaining; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(monkey->handler == 0x17116);
        player.roar_pulse = 1;
        player.player.body.owner = monkey->body.owner;
        assert(engine_enemies_tick(&enemies, camera) == 0 && monkey->handler == 0x1783e);
        player.roar_pulse = 0;
        for (unsigned int tick = 0; tick < 19; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(monkey->monkey_variant == type);
    }
    assert(found == 5);
    player.roar_pulse = 0;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *monkey = &enemies.lizards[i];
        if (monkey->marker_type != 8) continue;
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
        monkey->destroyed = 0;
        player.player.body.owner = monkey->marker;
        RENDER_OWNER camera = {(short)(monkey->marker.x - 160), (short)(monkey->marker.y - 100)};
        assert(engine_enemies_tick(&enemies, camera) == 0);
        unsigned int position = monkey->body.animation.visual.position;
        unsigned char remaining = monkey->body.animation.visual.remaining;
        player.roar_pulse = 1;
        assert(engine_enemies_tick(&enemies, camera) == 0 &&
            monkey->handler == 0x17116 && monkey->monkey_variant == 8);
        assert(monkey->body.animation.visual.position == position &&
            monkey->body.animation.visual.remaining == remaining);
        player.roar_pulse = 0;
        break;
    }
    ENGINE_LIZARD *changeable = 0;
    for (unsigned int i = 0; i < enemies.count; ++i)
        if (enemies.lizards[i].marker_type == 23) changeable = &enemies.lizards[i];
    assert(changeable && engine_enemies_restart(&enemies) == 0);
    for (unsigned int i = 0; i < enemies.count; ++i) enemies.lizards[i].destroyed = 1;
    changeable->destroyed = 0;
    RENDER_OWNER camera = {(short)(changeable->marker.x - 160), (short)(changeable->marker.y - 100)};
    player.player.body.owner = changeable->marker;
    player.flags = player.roar_pulse = 0;
    assert(engine_enemies_tick(&enemies, camera) == 0);
    ENGINE_OBJECT *player_object = engine_acquire_object(&objects, 0);
    assert(player_object);
    ENGINE_PLAYER_CALL roar = {0xec69, 0x61fe, 0};
    player.player.handler = 0;
    player.player.form = 0;
    player.player.immunity = 0;
    player.player.flags_high = 0;
    player.roar_charge = 8;
    assert(engine_player_begin_action(&objects, player_object, &player, &roar) == 0);
    DOS64_INPUT keys = {0};
    for (unsigned int tick = 0; tick < 15; ++tick) {
        assert(engine_update_objects(&objects, &keys) == 0);
        assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(changeable->handler == (tick == 14 ? 0x1783eU : 0x17116U));
    }
    assert(player.roar_pulse == 8 && !player.roar_charge);
    assert(engine_update_objects(&objects, &keys) == 0 && !player.roar_pulse);
    assert(engine_release_object(&objects, player_object) == 0);
    assert(engine_enemies_restart(&enemies) == 0);
}

int main(void)
{
    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file; api.Fs.Close = close_file;
    api.Fs.Seek = seek_file; api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    unsigned int map_size, contour_size, slot, bank_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVEL2.MAP", packed,
        sizeof(packed), map, sizeof(map), &dictionary, &map_size) == 0);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTOUR.CON", packed,
        sizeof(packed), contours, sizeof(contours), &dictionary, &contour_size) == 0);
    assert(engine_map_collision_initialize(&collision, map, map_size,
        contours, contour_size) == 0);
    FILE *original = fopen("bin/obj2_data.bin", "rb");
    unsigned char active_scripts[0x149b8 - 0x1492c];
    assert(original && fseek(original, 0x1492c, SEEK_SET) == 0 &&
        fread(active_scripts, 1, sizeof(active_scripts), original) == sizeof(active_scripts));
    assert(fclose(original) == 0);
    assert(memcmp(active_scripts, animation_enemy_data + 0x1492c - ANIMATION_ENEMY_BASE,
        sizeof(active_scripts)) == 0);
    original = fopen("bin/obj2_data.bin", "rb");
    unsigned char horizontal_velocities[ANIMATION_MONKEY_VELOCITY_COUNT * 4U];
    assert(original && fseek(original, 0x14da0, SEEK_SET) == 0 &&
        fread(horizontal_velocities, 1, sizeof(horizontal_velocities), original) ==
            sizeof(horizontal_velocities));
    assert(fclose(original) == 0);
    assert(memcmp(horizontal_velocities, animation_monkey_velocities,
        sizeof(horizontal_velocities)) == 0);
    unsigned int list_count;
    assert(assets_slot_list_count(animation_level2_bank_list,
        sizeof(animation_level2_bank_list), &list_count) == 0 && list_count == 21);
    for (unsigned int i = 0; i < list_count; ++i) {
        assert(assets_load_named_bank(&api, "data/LIONKING.EPF",
            animation_level2_bank_list, sizeof(animation_level2_bank_list), i, packed,
            sizeof(packed), level2_banks[i], sizeof(level2_banks[i]), &dictionary,
            &slot, &bank_size) == 0);
        banks[slot] = (RENDER_SPRITE_BANK){level2_banks[i], bank_size};
    }
    engine_initialize_objects(&objects);
    render_initialize_nodes(&renders);
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner,
        0, 0, animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    assert(player.player.body.node);
    player.player.body.node->flags |= 0x80;
    player.player.context = &player;
    assert(engine_enemies_initialize(&enemies, &objects, &renders, &collision, &player, 2) == 0);
    enemies.sound = sound;
    assert(enemies.bird_count == 13 && enemies.rhino_count == 5 && enemies.monkey_count == 34);
    ENGINE_LIZARD *bird = 0;
    ENGINE_LIZARD *rhino = 0;
    ENGINE_LIZARD *monkey = 0;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *item = &enemies.lizards[i];
        if (!bird && item->marker_type == 107) bird = item;
        if (!rhino && item->marker_type == 27) rhino = item;
        if (!monkey && (item->marker_type == 5 || item->marker_type == 6 ||
            item->marker_type == 7 || item->marker_type == 8 ||
            item->marker_type == 23 || item->marker_type == 24 ||
            item->marker_type == 25 || item->marker_type == 26)) monkey = item;
    }
    assert(bird && rhino && monkey);
    for (unsigned int i = 0; i < enemies.count; ++i)
        if (&enemies.lizards[i] != bird && &enemies.lizards[i] != rhino &&
            &enemies.lizards[i] != monkey) enemies.lizards[i].destroyed = 1;
    RENDER_OWNER rhino_camera = {(short)(rhino->marker.x - 160), (short)(rhino->marker.y - 100)};
    RENDER_OWNER monkey_camera = {(short)(monkey->marker.x - 160), (short)(monkey->marker.y - 100)};
    RENDER_OWNER camera = {(short)(bird->marker.x - 160), (short)(bird->marker.y - 100)};
    player.player.body.owner = (RENDER_OWNER){0, 0};
    assert(engine_enemies_tick(&enemies, rhino_camera) == 0);
    assert(rhino->object && rhino->body.node->parts[19] == 124);
    assert(engine_enemies_tick(&enemies, monkey_camera) == 0);
    assert(monkey->object && (monkey->body.node->parts[19] == 114 || monkey->body.node->parts[19] == 116));
    unsigned short flags = monkey->body.node->pass_flags;
    if (monkey->marker_type == 5 || monkey->marker_type == 23 || monkey->marker_type == 26) {
        assert(flags & 8);
    } else {
        assert(!(flags & 8));
    }
    assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(bird->object && bird->handler == 0x1b824 && bird->timer == 19);
    assert(bird->body.node->parts[19] == 111);
    assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
        banks, 127, pixels) == 0);
    unsigned int visible = 0;
    for (unsigned int i = 0; i < sizeof(pixels); ++i) visible += pixels[i] != 0;
    assert(visible);
    for (unsigned int i = 0; i < 19; ++i)
        assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(bird->timer == 19 && bird->body.animation.script.position != 0);
    static const unsigned int entries[] = {0x141b0, 0x141d3, 0x141fb, 0x14219};
    for (unsigned int choice = 0; choice < 4; ++choice) {
        uint32_t seed;
        for (seed = 1; seed < 100000; ++seed) {
            uint32_t next = seed;
            if ((engine_random_byte(&next) & 3U) == choice) break;
        }
        assert(seed < 100000);
        enemies.random = seed;
        bird->timer = 1;
        unsigned char facing = bird->facing;
        assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(bird->timer == 19 && bird->body.animation.script.position == entries[choice]);
        if (choice == 3) {
            assert(bird->facing != facing);
            assert(!!(bird->body.node->pass_flags & 8) == bird->facing);
            assert(bird->body.owner.x == bird->marker.x + bird->facing);
        }
        for (unsigned int tick = 0; tick < 18; ++tick)
            assert(engine_enemies_tick(&enemies, camera) == 0);
    }
    RENDER_OWNER distant = {(short)(bird->body.owner.x + 600), bird->body.owner.y};
    assert(engine_enemies_tick(&enemies, distant) == 0 && !bird->object && !bird->destroyed);
    assert(!rhino->object && !monkey->object);
    assert(engine_enemies_tick(&enemies, camera) == 0 && bird->object);
    player.player.body.owner = bird->body.owner;
    short hit;
    assert(render_objects_hit(bird->body.node, player.player.body.node, &hit) == 0 && hit);
    assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(sounds == 1 && bird->handler == 0x1b99c && bird->timer == 1);
    assert(!(player.player.flags_high & 4));
    RENDER_OWNER origin = bird->body.owner;
    for (unsigned int i = 0; i < 5; ++i) assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(bird->timer == 6 && bird->body.owner.x == origin.x && bird->body.owner.y == origin.y);
    assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(bird->body.owner.x == origin.x + 3 && bird->body.owner.y == origin.y - 3);
    distant = (RENDER_OWNER){(short)(bird->body.owner.x + 600), bird->body.owner.y};
    assert(engine_enemies_tick(&enemies, distant) == 0 && !bird->object && bird->destroyed);
    assert(engine_enemies_tick(&enemies, camera) == 0 && !bird->object);
    assert(engine_enemies_restart(&enemies) == 0 && !bird->destroyed);
    player.player.body.owner = (RENDER_OWNER){0, 0};
    assert(engine_enemies_tick(&enemies, camera) == 0 && bird->object);
    player.player.body.owner = bird->body.owner;
    fail_sound = 1;
    assert(engine_enemies_tick(&enemies, camera) == -1 && sounds == 2);
    assert(engine_enemies_restart(&enemies) == 0 && !bird->object);
    fail_sound = 0;
    check_monkeys();
    check_up_monkeys();
    check_down_monkeys();
    check_horizontal_monkeys();
    check_monkey_roar();
    check_tails();
    check_tail_grab();
    check_giraffes();
    check_giraffe_landing();
    check_floating_logs();
    check_ostrich_waiting();
    puts("PASS: birds, monkeys, rhino tails, giraffe heads, floating logs and waiting ostrich markers");
    return 0;
}
