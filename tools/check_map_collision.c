#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/resources.h"
#include "engine/tiles.h"
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static unsigned char packed[79311], map[580488], contours[4096];
static unsigned char tile_frames[12800], original_map[580488];
static unsigned char background_pixels[64000], previous_pixels[64000];
static RESOURCE_DICTIONARY dictionary;
static ENGINE_MAP_COLLISION collision;
static ENGINE_PLAYER_AIR player;
static ENGINE_OBJECT_POOL pool;
static RENDER_POOL renders;
static ENGINE_OBJECT *object;
static unsigned char flags;
static unsigned int snaps, landings;

static unsigned int little32(const unsigned char *p)
{
    return p[0] | (unsigned int)p[1] << 8 | (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
}

static void check_scroll_profiles(void)
{
    unsigned char fixture[5312] = {0};
    fixture[4] = 0x80; fixture[5] = 0x14;
    fixture[8] = fixture[12] = 100;
    fixture[20] = 80; fixture[24] = 32; fixture[28] = 128;
    for (unsigned int i = 0; i < 80 * 32; ++i) fixture[128 + i * 2] = 1;
    for (unsigned int i = 0; i < 64; ++i) fixture[5248 + i] = (unsigned char)(i + 1);
    assert(render_map_background(fixture, sizeof(fixture), 1, 487, 0, background_pixels) == 0);
    assert(background_pixels[0] == 5);
    assert(render_map_background(fixture, sizeof(fixture), 1, 487, 239, background_pixels) == 0);
    assert(background_pixels[0] == 29);
    assert(render_map_background(fixture, sizeof(fixture), 2, 487, 0, background_pixels) == 0);
    assert(background_pixels[18 * 8 * 320] == 5);
    assert(background_pixels[19 * 8 * 320] == 1);
    assert(background_pixels[24 * 8 * 320] == 5);
    assert(render_map_background(fixture, sizeof(fixture), 2, 6000, 0, background_pixels) == 0);
    assert(background_pixels[19 * 8 * 320] == 6);
    assert(render_map_background(fixture, sizeof(fixture), 5, 487, 0, background_pixels) == 0);
    assert(background_pixels[20 * 8 * 320] == 7);
    assert(background_pixels[21 * 8 * 320] == 5);
    assert(background_pixels[22 * 8 * 320] == 7);
    fixture[128] = 1; fixture[129] = 0xc0;
    assert(render_map_background(fixture, sizeof(fixture), 1, 0, 0, background_pixels) == 0);
    assert(background_pixels[0] == 64);
    fixture[128] = fixture[129] = 0;
    memset(background_pixels, 71, sizeof(background_pixels));
    assert(render_map_background(fixture, sizeof(fixture), 1, 0, 0, background_pixels) == 0);
    assert(background_pixels[0] == 71);
    puts("PASS: original row thresholds, repeated level-5 threshold, wrapping, flip and empty background tiles");
}

static void check_background(const DOS64_API *api, unsigned int level)
{
    unsigned int size, frame_size;
    assert(resources_load_entry(api, "data/LIONKING.EPF",
        level == 6 ? "LEVEL6.MAP" : "LEVEL10.MAP", packed, sizeof(packed),
        map, sizeof(map), &dictionary, &size) == 0);
    assert(resources_load_entry(api, "data/LIONKING.EPF",
        level == 6 ? "LEVEL6.BLK" : "LEVEL10.BLK", packed, sizeof(packed),
        tile_frames, sizeof(tile_frames), &dictionary, &frame_size) == 0);
    memcpy(original_map, map, size);
    ENGINE_TILE_ANIMATION animation;
    assert(engine_tile_animation_initialize(&animation, map, size, level, tile_frames, frame_size) == 0);
    assert(engine_tile_animation_initialize(&animation, map, size, level, tile_frames, frame_size - 1) == -1);
    unsigned int camera_y = 0;
    printf("Background LEVEL%u: foreground %ux%u, background %ux%u, table %u\n", level,
        little32(map + 8), little32(map + 12), little32(map + 20),
        little32(map + 24), little32(map + 28));
    unsigned int changed = 0;
    for (unsigned int tick = 0; tick < 21; ++tick) {
        int result = engine_tile_animation_tick(&animation);
        assert(result == (tick % 5 == 0 ? 1 : 0));
        assert(animation.frame == (tick / 5 + 1) % 4);
        const unsigned char *source = tile_frames + animation.frame * animation.frame_size;
        for (unsigned int i = 0; i < animation.count; ++i) {
            assert(memcmp(map + animation.destinations[i], source, animation.lengths[i]) == 0);
            source += animation.lengths[i];
        }
        memset(background_pixels, 0, sizeof(background_pixels));
        assert(render_map_background(map, size, level, 0, camera_y, background_pixels) == 0);
        assert(render_map_tile_pass(map, size, 0, 0, camera_y, 0, background_pixels) == 0);
        assert(render_map_tile_pass(map, size, 0, 0, camera_y, 1, background_pixels) == 0);
        if (tick) {
            for (unsigned int i = 0; i < sizeof(background_pixels); ++i) {
                if (background_pixels[i] != previous_pixels[i]) ++changed;
            }
        }
        memcpy(previous_pixels, background_pixels, sizeof(previous_pixels));
    }
    unsigned int mutated = 0;
    for (unsigned int byte = 0; byte < size; ++byte) {
        if (map[byte] == original_map[byte]) continue;
        int destination = 0;
        for (unsigned int i = 0; i < animation.count; ++i) {
            if (byte >= animation.destinations[i] &&
                byte - animation.destinations[i] < animation.lengths[i]) destination = 1;
        }
        assert(destination);
        ++mutated;
    }
    printf("Background measurements: updates%u changed%u mutated%u cameraY%u\n",
        animation.updates, changed, mutated, camera_y);
    assert(animation.updates == 5 && changed && mutated);
    printf("PASS: LEVEL%u animated tiles, 5 changes in 21 ticks, %u visible pixel changes; map planes untouched\n",
        level, changed);
}

static int map_support(void *context, short *supported)
{
    assert(context == &player);
    ENGINE_MAP_GROUND ground;
    if (engine_map_ground(&collision, player.player.body.owner.x,
        player.player.body.owner.y, &ground) != 0) return -1;
    *supported = ground.supported;
    player.contact_kind = ground.kind; player.surface_kind = ground.surface_kind;
    if (ground.supported) {
        if (ground.delta_y) ++snaps;
        player.player.body.owner.y += ground.delta_y;
    }
    return 0;
}
static int map_ground(void *context, short *kind, short *delta)
{
    assert(context == &player);
    ENGINE_MAP_GROUND ground;
    if (engine_map_ground(&collision, player.player.body.owner.x,
        player.player.body.owner.y, &ground) != 0) return -1;
    *kind = ground.supported; *delta = ground.delta_y; player.contact_kind = ground.kind;
    return 0;
}
static int map_edge(void *context, short *hit, short *kind, short *x, short *y)
{
    assert(context == &player);
    return engine_map_edge(&collision, player.player.body.node, hit, kind, x, y);
}
static int probe(void *context, short x, short y, short *hit)
{
    assert(context == &player);
    return engine_map_ceiling(&collision, player.player.body.node, x, y, hit);
}
static int sound(void *context, unsigned short sample)
{
    assert(context == &player); (void)sample; return 0;
}
static int transition(void *context, const ENGINE_PLAYER_CALL *call, short kind, short x, short y)
{
    assert(context == &player);
    if (call->handler == 0xe775U || call->handler == 0xe8dfU)
        return engine_player_begin_ledge(&pool, object, &player, call->handler, kind, x, y);
    ++landings;
    return engine_player_begin_ground(&pool, object, &player, call);
}
static int ledge_height(void *context, short x, short y, short *height)
{
    assert(context == &player);
    return engine_map_ledge_height(&collision, x, y, height);
}

static void tick(void)
{
    assert(engine_map_lateral(&collision, &player.player.body.owner, player.flags,
        player.player.flags_high, &player.boundary_controls) == 0);
    player.pressed &= (unsigned short)~player.boundary_controls;
    DOS64_INPUT input = {0};
    assert(engine_update_objects(&pool, &input) == 0);
}

static void set_kind(unsigned char *data, unsigned int offset, unsigned int kind)
{
    unsigned int tile = (kind / 8) * 32 + (kind % 8) * 2;
    data[offset] = (unsigned char)tile;
    data[offset + 1] = (unsigned char)(tile >> 8);
}
static void __attribute__((ms_abi)) diagnostic(const char *text) { fputs(text, stderr); }
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode) { return fopen(path, mode); }
static int __attribute__((ms_abi)) close_file(void *file) { return fclose(file); }
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{
    return fseek(file, (long)offset, whence);
}
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    return fread(buffer, (size_t)size, (size_t)count, file);
}

int main(void)
{
    DOS64_API api = {0};
    api.Write = diagnostic; api.Fs.Open = open_file; api.Fs.Close = close_file;
    api.Fs.Seek = seek_file; api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    unsigned int size, contour_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVEL1.MAP", packed, sizeof(packed),
        map, sizeof(map), &dictionary, &size) == 0);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTOUR.CON", packed, sizeof(packed),
        contours, sizeof(contours), &dictionary, &contour_size) == 0);
    assert(engine_map_collision_initialize(&collision, map, size, contours, contour_size) == 0);
    printf("Map grid: %u x %u; table %u, plane %u\n",
        collision.width, collision.height, collision.table, collision.plane_size);
    unsigned int hits = 0;
    for (int y = 12; y < (int)collision.height * 8; y += 16) {
        ENGINE_MAP_GROUND ground;
        assert(engine_map_ground(&collision, 160, (short)y, &ground) == 0);
        if (ground.supported && hits++ < 12) printf("X160 ground Y%d delta%d kind%u\n",
            y, ground.delta_y, ground.kind);
    }
    assert(hits);
    for (int x = 160; x <= 960; x += 80) {
        for (int y = 1200; y < 1280; ++y) {
            ENGINE_MAP_GROUND ground;
            assert(engine_map_ground(&collision, (short)x, (short)y, &ground) == 0);
            if (ground.supported && !ground.delta_y) {
                printf("Surface X%d Y%d kind%u\n", x, y, ground.kind);
                break;
            }
        }
    }
    ENGINE_MAP_GROUND ground_sample;
    assert(engine_map_ground(&collision, 160, 1255, &ground_sample) == 0 &&
        ground_sample.supported && ground_sample.delta_y == 0);
    assert(engine_map_ground(&collision, 400, 1255, &ground_sample) == 0 &&
        ground_sample.supported && ground_sample.delta_y == 6);
    assert(engine_map_ground(&collision, 880, 1255, &ground_sample) == 0 &&
        ground_sample.supported && ground_sample.delta_y == -2);
    assert(engine_map_ground(&collision, 160, 1000, &ground_sample) == 0 && !ground_sample.supported);
    engine_initialize_objects(&pool); render_initialize_nodes(&renders);
    player.player.context = &player;
    player.player.collision_flags = &flags;
    player.player.body.owner = (RENDER_OWNER){160, 1255};
    player.player.body.render_pool = &renders;
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner,
        0, 0, animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    object = engine_acquire_object(&pool, 0);
    assert(object && player.player.body.node);
    player.support = map_support; player.ground = map_ground; player.edge = map_edge;
    player.ledge_height = ledge_height; player.transition = transition;
    player.player.probe = probe; player.sound = sound;
    ENGINE_PLAYER_CALL idle = {0xc8d5, 0x6148, 0};
    assert(engine_player_begin_ground(&pool, object, &player, &idle) == 0);
    player.pressed = 8;
    for (unsigned int i = 0; i < 80; ++i) { player.pressed = 8; tick(); }
    assert(player.player.body.owner.x > 360 && snaps > 0 && player.player.body.owner.y != 1255);
    short start_y = player.player.body.owner.y;
    player.pressed |= 0x20;
    for (unsigned int i = 0; i < 10; ++i) { player.pressed = 0x28; tick(); }
    assert(player.player.body.owner.y < start_y - 20);
    player.pressed = 0;
    for (unsigned int i = 0; i < 120; ++i) tick();
    assert(landings && object->behavior == &engine_player_ground_behavior);
    assert(engine_map_ground(&collision, player.player.body.owner.x, player.player.body.owner.y,
        &ground_sample) == 0 && ground_sample.supported && !ground_sample.delta_y);
    printf("Connected map motion: X%d Y%d, %u contour adjustments, %u landings\n",
        player.player.body.owner.x, player.player.body.owner.y, snaps, landings);
    unsigned int side_hits = 0, ceiling_hits = 0;
    for (int y = 32; y < 1280; y += 16) {
        for (int x = 32; x < 1568; x += 16) {
            RENDER_OWNER point = {(short)x, (short)y};
            unsigned char blocked;
            short hit;
            assert(engine_map_lateral(&collision, &point, 0, 0, &blocked) == 0);
            assert(engine_map_ceiling(&collision, player.player.body.node,
                (short)x, (short)y, &hit) == 0);
            if (blocked && side_hits++ < 3) printf("Real side contact X%d Y%d mask%u correctedX%d\n",
                x, y, blocked, point.x);
            if (hit && ceiling_hits++ < 3) printf("Real ceiling contact X%d Y%d\n", x, y);
        }
    }
    assert(side_hits && ceiling_hits);
    for (unsigned int direction = 0; direction < 2; ++direction) {
        player.player.handler = 0;
        player.player.body.owner = (RENDER_OWNER){1088, 112};
        player.player.body.motion = (ENGINE_MOTION){0};
        ENGINE_PLAYER_CALL jump = {direction ? 0xb7e7U : 0xb604U, 0x6180, 0};
        assert(engine_player_begin_jump(&pool, object, &player, &jump, 0x612c) == 0);
        short hit = 0;
        for (short y = 32; y < 1280 && !hit; y += 16) {
            assert(probe(&player, 1088, y, &hit) == 0);
            if (hit) player.player.body.owner.y = y;
        }
        assert(hit);
        player.pressed = 0;
        tick();
        assert(flags & 0x20);
        assert(player.player.body.motion.velocity_y < 0x80000000U);
        assert(object->behavior == &engine_player_air_behavior);
    }
    puts("PASS: real LEVEL1 ceiling stops both original jump directions");
    unsigned char fixture[512] = {0}, heights[4096] = {0};
    fixture[8] = 8; fixture[12] = 4; fixture[16] = 128;
    heights[16 + 3] = 13 | 0xe0;
    fixture[192] = 2; fixture[256] = 6;
    ENGINE_MAP_COLLISION test;
    assert(engine_map_collision_initialize(&test, fixture, sizeof(fixture), heights, sizeof(heights)) == 0);
    assert(engine_map_ground(&test, 3, 12, &ground_sample) == 0 && ground_sample.supported &&
        !ground_sample.delta_y && ground_sample.kind == 3 && !ground_sample.surface_kind);
    heights[16 + 3] = 0;
    fixture[224] = 2; fixture[288] = 18;
    heights[16 + 3] = 1;
    assert(engine_map_ground(&test, 3, 13, &ground_sample) == 0 && ground_sample.supported &&
        ground_sample.delta_y == 3 && ground_sample.kind == 9 && ground_sample.surface_kind == 3);
    assert(engine_map_ground(&test, -1, 12, &ground_sample) == 0 && !ground_sample.supported);
    unsigned char parts[20] = {0};
    RENDER_OWNER position = {19, 16};
    RENDER_NODE node = {0};
    node.owner = &position; node.parts = parts; node.parts_size = sizeof(parts);
    fixture[292] = 0x94;
    fixture[293] = 3; /* EA contact, not contour index EA. */
    short hit, kind, x, y;
    assert(engine_map_edge(&test, &node, &hit, &kind, &x, &y) == 0 &&
        hit && kind == 0xea && x == 19 && y == 16);
    fixture[292] = 0;
    fixture[293] = 0;
    fixture[288] = 0x90; fixture[289] = 3;
    assert(engine_map_edge(&test, &node, &hit, &kind, &x, &y) == 0 &&
        hit && kind == 0xe8 && x == 3 && y == 16);
    node.pass_flags = 8;
    fixture[296] = 0xd0; fixture[297] = 3;
    assert(engine_map_edge(&test, &node, &hit, &kind, &x, &y) == 0 &&
        hit && kind == 0xf8 && x == 35 && y == 16);
    short height;
    assert(engine_map_ledge_height(&test, 3, 16, &height) == 0 && height == 1);
    fixture[224] = 0; fixture[225] = 4;
    assert(engine_map_ledge_height(&test, 3, 16, &height) == -1);
    assert(engine_map_collision_initialize(&test, fixture, 200, heights, sizeof(heights)) == -1);
    assert(engine_map_collision_initialize(&test, fixture, sizeof(fixture), heights, 4095) == -1);
    memset(fixture + 128, 0, sizeof(fixture) - 128);
    position = (RENDER_OWNER){24, 32};
    unsigned char blocked;
    set_kind(fixture, 288, 0xb0);
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 &&
        blocked == 4 && position.x == 27);
    memset(fixture + 128, 0, sizeof(fixture) - 128);
    position = (RENDER_OWNER){24, 32};
    set_kind(fixture, 296, 0xb0);
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 &&
        blocked == 8 && position.x == 24);
    set_kind(fixture, 294, 0x41);
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 &&
        blocked == 8 && position.x == 16);
    memset(fixture + 128, 0, sizeof(fixture) - 128);
    position = (RENDER_OWNER){24, 32};
    set_kind(fixture, 296, 6);
    assert(engine_map_lateral(&test, &position, 8, 0, &blocked) == 0 && !blocked && position.x == 24);
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 8);
    set_kind(fixture, 296, 0x4e);
    position = (RENDER_OWNER){24, 32};
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && !blocked);
    position.y = 40;
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 8);
    set_kind(fixture, 296, 0x4f);
    position = (RENDER_OWNER){24, 32};
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 8);
    position.y = 47;
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && !blocked);
    set_kind(fixture, 296, 0x40);
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && !blocked);
    set_kind(fixture, 296, 0x41);
    position = (RENDER_OWNER){24, 32};
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && !blocked);
    position.x = 28;
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 8);
    set_kind(fixture, 296, 0x140);
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && !blocked);
    memset(fixture + 128, 0, sizeof(fixture) - 128);
    set_kind(fixture, 288, 0x40);
    position = (RENDER_OWNER){24, 32};
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && !blocked);
    position.x = 20;
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 4 && position.x == 20);
    position.x = 18;
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 4 && position.x == 20);
    memset(fixture + 128, 0, sizeof(fixture) - 128);
    set_kind(fixture, 296, 6);
    position = (RENDER_OWNER){24, 0};
    assert(engine_map_lateral(&test, &position, 0x8000, 0, &blocked) == 0 && blocked == 8);
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && !blocked);
    set_kind(fixture, 296, 2);
    position = (RENDER_OWNER){24, 32};
    assert(engine_map_lateral(&test, &position, 0, 8, &blocked) == 0 && !blocked);
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 8);
    memset(fixture + 128, 0, sizeof(fixture) - 128);
    parts[4] = (unsigned char)-16; parts[5] = 255;
    set_kind(fixture, 292, 0xb0);
    assert(engine_map_ceiling(&test, &node, 24, 24, &hit) == 0 && hit);
    set_kind(fixture, 292, 0x40);
    assert(engine_map_ceiling(&test, &node, 24, 24, &hit) == 0 && hit);
    set_kind(fixture, 292, 2);
    assert(engine_map_ceiling(&test, &node, 24, 24, &hit) == 0 && !hit);
    memset(fixture + 128, 0, sizeof(fixture) - 128);
    position = (RENDER_OWNER){0, 32};
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 4 && position.x == 16);
    position = (RENDER_OWNER){63, 32};
    assert(engine_map_lateral(&test, &position, 0, 0, &blocked) == 0 && blocked == 8 && position.x == 48);
    puts("PASS: original two-row contour support, tags, real slope traversal, jump and map landing");
    assert(render_map_background(map, size, 1, 0, 0, background_pixels) == 0);
    memcpy(previous_pixels, background_pixels, sizeof(previous_pixels));
    assert(render_map_background(map, size, 1, 640, 1000, background_pixels) == 0);
    assert(memcmp(background_pixels, previous_pixels, sizeof(previous_pixels)) != 0);
    assert(render_map_background(map, size, 0, 0, 0, background_pixels) == -1);
    check_scroll_profiles();
    check_background(&api, 6);
    check_background(&api, 10);
    return 0;
}
