#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/animation_data.h"
#include "engine/lifecycle.h"
#include "engine/resources.h"
#include "engine/tiles.h"

static unsigned char packed[79311], map_data[580488], contours[4096];
static RESOURCE_DICTIONARY dictionary;
static ENGINE_MAP_COLLISION map;
static ENGINE_OBJECT_POOL objects;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR player;
static ENGINE_LEVEL_LIFE life;
static unsigned char collision_flags;
static unsigned int sounds;

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

static int ground(void *context, short *kind, short *delta)
{
    assert(context == &player);
    ENGINE_MAP_GROUND result;
    if (engine_map_ground(&map, player.player.body.owner.x,
        player.player.body.owner.y, &result) != 0) return -1;
    player.contact_kind = result.kind;
    *kind = result.supported;
    *delta = result.delta_y;
    return 0;
}

static int sound(void *context, unsigned short sample)
{
    assert(context == &player && sample == 23);
    ++sounds;
    return 0;
}

static int transition(void *context, const ENGINE_PLAYER_CALL *call,
    short kind, short x, short y)
{
    assert(context == &player && call->handler == 0x10d78 &&
        !kind && !x && !y);
    return engine_level_life_water(&life);
}

static int edge(void *context, short *hit, short *kind, short *x, short *y)
{
    (void)context;
    *hit = *kind = *x = *y = 0;
    return 0;
}

static void check_fall(short x, unsigned int handler, unsigned short held, int water)
{
    memset(&player, 0, sizeof(player));
    sounds = 0;
    engine_initialize_objects(&objects);
    render_initialize_nodes(&renders);
    player.player.body.owner = (RENDER_OWNER){x, (short)(water ? 330 : 440)};
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner, 0, 0,
        animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    assert(player.player.body.node);
    player.player.body.render_pool = &renders;
    player.player.context = &player;
    player.player.collision_flags = &collision_flags;
    player.player.body.motion.velocity_y = 0x10000;
    player.ground = ground; player.edge = edge; player.transition = transition; player.sound = sound;
    player.health = 4;
    player.pressed = held;
    ENGINE_OBJECT *object = engine_acquire_object(&objects, &engine_player_air_behavior);
    assert(object);
    object->context = &player;
    assert(animation_movement_initialize(&player.player.body.animation) == 0);
    assert(engine_level_life_initialize(&life, &player, object, 3) == 0);
    ENGINE_PLAYER_CALL call = {handler, 0x6116, 0};
    assert(engine_player_begin_air(&objects, object, &player, &call) == 0);
    DOS64_INPUT keys = {0};
    for (unsigned int tick = 0; tick < 200; ++tick) {
        assert(engine_level_life_check_bounds(&life, map.height, 2) == 0);
        int result = engine_level_life_tick(&life, (RENDER_OWNER){0, 296});
        assert(result >= 0);
        if (result == ENGINE_LIFE_RESTART) {
            assert(life.lives == 2 && life.deaths == 1 && life.restarts == 1);
            assert(!water && sounds == 0);
            return;
        }
        if (life.falling) {
            assert(water && sounds == 1 && player.player.handler == 0x10d78);
            return;
        }
        assert(result == ENGINE_LIFE_PLAYING);
        assert(engine_update_objects(&objects, &keys) == 0);
        assert(player.player.body.owner.y < 550);
    }
    assert(!"fall did not reach water or the bottom boundary");
}

int main(void)
{
    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    unsigned int map_size, contour_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVEL2.MAP", packed,
        sizeof(packed), map_data, sizeof(map_data), &dictionary, &map_size) == 0);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTOUR.CON", packed,
        sizeof(packed), contours, sizeof(contours), &dictionary, &contour_size) == 0);
    assert(engine_map_collision_initialize(&map, map_data, map_size, contours, contour_size) == 0);
    RENDER_OWNER water = {0, 0};
    int found = 0;
    for (unsigned int y = 0; y < map.height * 8 && !found; ++y) {
        for (unsigned int x = 0; x < map.width * 8; x += 8) {
            ENGINE_MAP_GROUND result;
            assert(engine_map_ground(&map, (short)x, (short)y, &result) == 0);
            if (result.kind == 4) {
                water = (RENDER_OWNER){(short)x, (short)y};
                found = 1;
                break;
            }
        }
    }
    assert(found);
    engine_initialize_objects(&objects);
    render_initialize_nodes(&renders);
    player.player.body.owner = water;
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner, 0, 0,
        animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    assert(player.player.body.node);
    player.player.body.render_pool = &renders;
    player.player.context = &player;
    player.player.collision_flags = &collision_flags;
    player.player.handler = 0xaa97;
    player.player.body.motion.velocity_y = 0x10000;
    player.ground = ground; player.edge = edge; player.transition = transition; player.sound = sound;
    player.health = 4;
    ENGINE_OBJECT *object = engine_acquire_object(&objects, &engine_player_air_behavior);
    assert(object);
    object->context = &player;
    assert(animation_movement_initialize(&player.player.body.animation) == 0);
    assert(engine_level_life_initialize(&life, &player, object, 3) == 0);
    DOS64_INPUT keys = {0};
    assert(engine_update_objects(&objects, &keys) == 0);
    assert(life.falling && player.player.handler == 0x10d78 && sounds == 1 && !object->behavior);
    assert(player.player.body.animation.visual.position >= 0x6379);
    short splash_y = player.player.body.owner.y;
    player.player.body.owner.y = (short)(map.height * 8 + 41);
    assert(engine_level_life_check_bounds(&life, map.height, 2) == 0 &&
        player.health == 4 && !life.out_of_bounds);
    player.player.body.owner.y = splash_y;
    for (unsigned int i = 0; i < 23; ++i)
        assert(engine_level_life_tick(&life, (RENDER_OWNER){0, 0}) == ENGINE_LIFE_DYING);
    assert(player.health == 4 && !life.remaining);
    assert(engine_level_life_tick(&life, (RENDER_OWNER){0, 0}) == ENGINE_LIFE_DYING);
    assert(player.health == 0 && !life.falling);
    assert(engine_level_life_tick(&life, (RENDER_OWNER){0, 0}) == ENGINE_LIFE_DYING);
    assert(life.lives == 2 && life.dying && life.deaths == 1);
    for (unsigned int i = 0; i < 220; ++i)
        assert(engine_level_life_tick(&life, (RENDER_OWNER){0, 0}) == ENGINE_LIFE_DYING);
    assert(engine_level_life_tick(&life, (RENDER_OWNER){0, 0}) == ENGINE_LIFE_RESTART);
    check_fall(384, 0xaa97, 0, 1);
    check_fall(496, 0xaa97, 8, 0);
    check_fall(512, 0xae53, 4, 0);
    player.player.body.owner.y = (short)(map.height * 8 + 40);
    player.health = 4;
    assert(engine_level_life_check_bounds(&life, map.height, 2) == 0 && player.health == 4);
    ++player.player.body.owner.y;
    assert(engine_level_life_check_bounds(&life, map.height, 4) == 0 && player.health == 4);
    life.lives = 1;
    assert(engine_level_life_check_bounds(&life, 0, 2) == -1 && player.health == 4);
    assert(engine_level_life_check_bounds(&life, map.height, 2) == 0 && !player.health);
    assert(engine_level_life_tick(&life, (RENDER_OWNER){0, 296}) == ENGINE_LIFE_GAME_OVER);
    printf("PASS: real LEVEL2 water at %d,%d, splash, death and restart\n", water.x, water.y);
    return 0;
}
