#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/resources.h"
#include "engine/tiles.h"
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static unsigned char packed[79311], map[580488], contours[4096];
static RESOURCE_DICTIONARY dictionary;
static ENGINE_MAP_COLLISION collision;
static ENGINE_PLAYER_AIR player;
static ENGINE_OBJECT_POOL pool;
static RENDER_POOL renders;
static ENGINE_OBJECT *object;
static unsigned char flags;
static unsigned int snaps, landings;

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
    assert(context == &player); (void)x; (void)y; *hit = 0; return 0;
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
    DOS64_INPUT input = {0};
    player.pressed = 8;
    for (unsigned int i = 0; i < 80; ++i) assert(engine_update_objects(&pool, &input) == 0);
    assert(player.player.body.owner.x > 360 && snaps > 0 && player.player.body.owner.y != 1255);
    short start_y = player.player.body.owner.y;
    player.pressed |= 0x20;
    for (unsigned int i = 0; i < 10; ++i) assert(engine_update_objects(&pool, &input) == 0);
    assert(player.player.body.owner.y < start_y - 20);
    player.pressed = 0;
    for (unsigned int i = 0; i < 120; ++i) assert(engine_update_objects(&pool, &input) == 0);
    assert(landings && object->behavior == &engine_player_ground_behavior);
    assert(engine_map_ground(&collision, player.player.body.owner.x, player.player.body.owner.y,
        &ground_sample) == 0 && ground_sample.supported && !ground_sample.delta_y);
    printf("Connected map motion: X%d Y%d, %u contour adjustments, %u landings\n",
        player.player.body.owner.x, player.player.body.owner.y, snaps, landings);
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
    puts("PASS: original two-row contour support, tags, real slope traversal, jump and map landing");
    return 0;
}
