#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/animation_data.h"
#include "engine/assets.h"
#include "engine/enemies.h"
#include "engine/resources.h"

static unsigned char packed[79311], map[580488], contours[4096], bank[65536], pixels[64000];
static unsigned char player_bank[65536], rhino_pixels[64000], player_pixels[64000];
static RESOURCE_DICTIONARY dictionary;
static ENGINE_MAP_COLLISION collision;
static ENGINE_ENEMIES enemies;
static ENGINE_OBJECT_POOL objects;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR player;
static unsigned int sounds;
static int fail_sound;
static unsigned char collision_flags;

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
    assert(context == &player && channel == 0 && sample == 0);
    ++sounds;
    return fail_sound ? -1 : 0;
}

static int probe(void *context, short x, short y, short *hit)
{
    assert(context == &player);
    (void)x; (void)y;
    *hit = 0;
    return 0;
}

static int ground(void *context, short *kind, short *delta_y)
{
    assert(context == &player);
    *kind = *delta_y = 0;
    return 0;
}

static int edge(void *context, short *hit, short *kind, short *x, short *y)
{
    assert(context == &player);
    *hit = *kind = *x = *y = 0;
    return 0;
}

static void align_player(ENGINE_LIZARD *rhino)
{
    RENDER_BOUNDS a, b;
    player.player.body.owner = rhino->body.owner;
    assert(render_object_bounds(rhino->body.node, &a) == 0);
    assert(render_object_bounds(player.player.body.node, &b) == 0);
    player.player.body.owner.x += (short)((a.left + a.right - b.left - b.right) / 2);
    player.player.body.owner.y += (short)((a.top + a.bottom - b.top - b.bottom) / 2);
    short hit;
    assert(render_objects_hit(rhino->body.node, player.player.body.node, &hit) == 0 && hit);
}

static void check_render_order(ENGINE_LIZARD *rhino, RENDER_OWNER camera,
    const RENDER_SPRITE_BANK *banks)
{
    align_player(rhino);
    player.player.body.node->flags = 0xc0;
    memset(rhino_pixels, 0, sizeof(rhino_pixels));
    assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
        banks, 125, rhino_pixels) == 0);
    player.player.body.node->flags &= 0x7f;
    rhino->body.node->flags |= 0x80;
    memset(player_pixels, 0, sizeof(player_pixels));
    assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
        banks, 125, player_pixels) == 0);
    rhino->body.node->flags &= 0x7f;
    memset(pixels, 0, sizeof(pixels));
    assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
        banks, 125, pixels) == 0);
    unsigned int overlap = 0;
    for (unsigned int j = 0; j < sizeof(pixels); ++j) {
        if (rhino_pixels[j] && player_pixels[j] && rhino_pixels[j] != player_pixels[j]) {
            ++overlap;
            assert(pixels[j] == player_pixels[j]);
        }
    }
    assert(overlap);
    player.player.body.node->flags |= 0x80;
}

int main(void)
{
    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    unsigned int map_size, contour_size, slot, bank_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVEL2.MAP", packed,
        sizeof(packed), map, sizeof(map), &dictionary, &map_size) == 0);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTOUR.CON", packed,
        sizeof(packed), contours, sizeof(contours), &dictionary, &contour_size) == 0);
    assert(engine_map_collision_initialize(&collision, map, map_size, contours, contour_size) == 0);
    assert(assets_load_named_bank(&api, "data/LIONKING.EPF", animation_level2_bank_list,
        sizeof(animation_level2_bank_list), 18, packed, sizeof(packed), bank, sizeof(bank),
        &dictionary, &slot, &bank_size) == 0 && slot == 124);
    unsigned int player_bank_size;
    assert(assets_load_named_bank(&api, "data/LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), 5, packed, sizeof(packed), player_bank,
        sizeof(player_bank), &dictionary, &slot, &player_bank_size) == 0 && slot == 11);
    FILE *original = fopen("bin/obj2_data.bin", "rb");
    unsigned char velocity_data[ANIMATION_RHINO_VELOCITY_COUNT * 4U];
    assert(original && fseek(original, 0x149b8, SEEK_SET) == 0 &&
        fread(velocity_data, 1, sizeof(velocity_data), original) == sizeof(velocity_data));
    assert(fclose(original) == 0);
    assert(memcmp(velocity_data, animation_rhino_velocities, sizeof(velocity_data)) == 0);
    engine_initialize_objects(&objects);
    render_initialize_nodes(&renders);
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner,
        0, 0, animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    assert(player.player.body.node);
    player.player.body.render_pool = &renders;
    player.player.collision_flags = &collision_flags;
    player.player.probe = probe;
    player.ground = ground;
    player.edge = edge;
    ENGINE_OBJECT *player_object = engine_acquire_object(&objects, 0);
    assert(player_object);
    assert(animation_movement_initialize(&player.player.body.animation) == 0);
    player.player.body.node->flags |= 0x80;
    player.player.context = &player;
    assert(engine_enemies_initialize(&enemies, &objects, &renders, &collision, &player, 0) == -1);
    assert(engine_enemies_initialize(&enemies, &objects, &renders, &collision, &player, 2) == 0);
    enemies.sound = sound;
    static const short targets[][2] = {{288, 128}, {1584, 96}, {4496, 224},
        {4912, 80}, {5904, 112}};
    ENGINE_LIZARD *rhinos[5] = {0};
    unsigned int count = 0;
    for (unsigned int i = 0; i < enemies.count; ++i) {
        ENGINE_LIZARD *item = &enemies.lizards[i];
        item->destroyed = 1;
        if (item->marker_type == 27) {
            assert(count < 5);
            rhinos[count++] = item;
        }
    }
    assert(count == 5);
    for (unsigned int i = 0; i < count; ++i) {
        ENGINE_LIZARD *rhino = rhinos[i];
        assert(rhino->marker.x == targets[i][0]);
        rhino->destroyed = 0;
        RENDER_OWNER camera = {(short)(rhino->marker.x - 160), (short)(rhino->marker.y - 100)};
        player.player.body.owner = (RENDER_OWNER){0, 0};
        assert(engine_enemies_tick(&enemies, camera) == 0);
        assert(rhino->object && rhino->target.x == targets[i][0] &&
            rhino->target.y == targets[i][1] && rhino->handler == 0x1667a);
        assert(engine_enemies_tick(&enemies, camera) == 0);
        RENDER_SPRITE_BANK banks[125] = {{0}};
        banks[124] = (RENDER_SPRITE_BANK){bank, bank_size};
        memset(pixels, 0, sizeof(pixels));
        assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
            banks, 125, pixels) == 0);
        unsigned int visible = 0;
        for (unsigned int j = 0; j < sizeof(pixels); ++j) visible += pixels[j] != 0;
        assert(visible);
        banks[11] = (RENDER_SPRITE_BANK){player_bank, player_bank_size};
        check_render_order(rhino, camera, banks);
        assert(engine_enemies_restart(&enemies) == 0);
        for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
    }

    ENGINE_LIZARD *rhino = rhinos[0];
    rhino->destroyed = 0;
    RENDER_OWNER camera = {(short)(rhino->marker.x - 160), (short)(rhino->marker.y - 100)};
    player.player.body.owner = (RENDER_OWNER){0, 0};
    assert(engine_enemies_tick(&enemies, camera) == 0);
    align_player(rhino);
    player.player.body.motion.velocity_y = 0;
    assert(engine_enemies_tick(&enemies, camera) == 0 && rhino->handler == 0x1667a);
    player.player.body.motion.velocity_y = UINT32_C(0xffff0000);
    assert(engine_enemies_tick(&enemies, camera) == 0 && rhino->handler == 0x1667a);
    player.flags = 2;
    player.player.body.motion.velocity_y = 0x10000;
    assert(engine_enemies_tick(&enemies, camera) == 0 && rhino->handler == 0x1667a);
    player.flags = 0;
    player.player.body.motion.velocity_x = 0x20000;
    assert(engine_enemies_tick(&enemies, camera) == 0 && rhino->handler == 0x166cc);
    assert(rhino->timer == 12 && !player.player.body.motion.velocity_x &&
        !player.player.body.motion.velocity_y);
    unsigned int animation_frames = 0;
    for (unsigned int i = 0; i < 4; ++i) {
        assert(engine_enemies_tick(&enemies, camera) == 0 && !sounds);
        unsigned int frame = rhino->body.node->parts[18];
        assert(frame >= 6 && frame <= 9);
        animation_frames |= 1U << (frame - 6);
    }
    assert(animation_frames & 1);
    assert(animation_frames & 2);
    assert(rhino->timer == 8);
    unsigned int index = (unsigned int)(player.player.body.owner.y - rhino->target.y) / 4;
    uint32_t speed = (uint32_t)velocity_data[index * 4] |
        (uint32_t)velocity_data[index * 4 + 1] << 8 |
        (uint32_t)velocity_data[index * 4 + 2] << 16 |
        (uint32_t)velocity_data[index * 4 + 3] << 24;
    assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(sounds == 1 && rhino->timer == 7 && player.anchor_x == 288 &&
        player.anchor_y == 128 && (player.flags & 1) &&
        player.player.body.motion.velocity_y == 0U - speed);
    player.player.handler = 0xaa97;
    ENGINE_PLAYER_CALL air = {0xaa97, 0x61e2, 0};
    assert(engine_player_begin_air(&objects, player_object, &player, &air) == 0);
    assert(player.flags == 2 && player.player.body.motion.velocity_y == 0U - speed);
    short launch_y = player.player.body.owner.y;
    assert(engine_player_begin_air(&objects, player_object, &player, &air) == 0);
    assert(player.player.body.owner.y < launch_y &&
        player.player.body.motion.velocity_y == 0U - speed + 0x4e00U);
    RENDER_OWNER distant = {(short)(camera.x + 1000), camera.y};
    for (unsigned int i = 0; i < 7; ++i)
        assert(engine_enemies_tick(&enemies, distant) == 0 && rhino->object);
    assert(!rhino->timer && engine_enemies_tick(&enemies, distant) == 0 &&
        rhino->object && rhino->handler == 0x1667a);
    assert(engine_enemies_tick(&enemies, distant) == 0 && !rhino->object);
    player.player.body.owner = (RENDER_OWNER){0, 0};
    assert(engine_enemies_tick(&enemies, camera) == 0 && rhino->object);
    assert(engine_enemies_tick(&enemies, camera) == 0);
    player.player.body.node->parts = animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE;
    player.player.body.node->parts_size = 20;
    RENDER_SPRITE_BANK respawn_banks[125] = {{0}};
    respawn_banks[11] = (RENDER_SPRITE_BANK){player_bank, player_bank_size};
    respawn_banks[124] = (RENDER_SPRITE_BANK){bank, bank_size};
    check_render_order(rhino, camera, respawn_banks);
    assert(engine_enemies_restart(&enemies) == 0);
    for (unsigned int j = 0; j < enemies.count; ++j) enemies.lizards[j].destroyed = 1;
    rhino->destroyed = 0;
    player.player.body.owner = (RENDER_OWNER){0, 0};
    assert(engine_enemies_tick(&enemies, camera) == 0);
    rhino->handler = 0x166cc;
    rhino->timer = 8;
    player.player.body.owner.y = (short)(rhino->target.y - 1);
    assert(engine_enemies_tick(&enemies, camera) == -1 && sounds == 1);
    player.player.body.owner.y = (short)(rhino->target.y + ANIMATION_RHINO_VELOCITY_COUNT * 4);
    assert(engine_enemies_tick(&enemies, camera) == -1 && sounds == 1);
    player.player.body.owner.y = (short)(rhino->target.y + 100);
    fail_sound = 1;
    assert(engine_enemies_tick(&enemies, camera) == -1 && sounds == 2);
    assert(engine_enemies_restart(&enemies) == 0 && !rhino->object);
    puts("PASS: all five rhino targets, animation, collision gates, launch timing, velocity, culling and errors");
    return 0;
}
