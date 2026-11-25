#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/animation_data.h"
#include "engine/assets.h"
#include "engine/pickups.h"
#include "engine/resources.h"

static unsigned char packed[79311], map[580488], original_map[580488], contours[4096];
static unsigned char sprite[65536], pixels[64000];
static RESOURCE_DICTIONARY dictionary;
static ENGINE_MAP_COLLISION collision;
static ENGINE_OBJECT_POOL objects;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR player;
static ENGINE_PICKUPS pickups;
static RENDER_SPRITE_BANK banks[95];
static unsigned char lives;
static unsigned int continues, sounds;
static int fail_sound;

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

static int sound(void *context, unsigned short sample)
{
    assert(context == &player && sample == 1);
    ++sounds;
    return fail_sound ? -1 : 0;
}

static ENGINE_PICKUP *setup(RENDER_OWNER marker, unsigned char starting_lives)
{
    engine_initialize_objects(&objects);
    render_initialize_nodes(&renders);
    memset(&player, 0, sizeof(player));
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner,
        0, 0, animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    assert(player.player.body.node);
    player.player.body.node->flags |= 0x80;
    player.player.context = &player;
    player.sound = sound;
    player.health = 4;
    lives = starting_lives;
    continues = 1;
    sounds = 0;
    fail_sound = 0;
    assert(engine_pickups_initialize(&pickups, &objects, &renders, &collision,
        &player, 4, 16, &lives, &continues) == 0);
    for (unsigned int i = 0; i < pickups.count; ++i) {
        ENGINE_PICKUP *item = &pickups.items[i];
        if (item->marker.x == marker.x && item->marker.y == marker.y) {
            assert(item->type == 1);
            return item;
        }
    }
    assert(0);
    return 0;
}

static void overlap(ENGINE_PICKUP *item)
{
    RENDER_BOUNDS a, b;
    player.player.body.owner = item->body.owner;
    assert(render_object_bounds(item->body.node, &a) == 0);
    assert(render_object_bounds(player.player.body.node, &b) == 0);
    player.player.body.owner.x += (short)((a.left + a.right - b.left - b.right) / 2);
    player.player.body.owner.y += (short)((a.top + a.bottom - b.top - b.bottom) / 2);
    short hit;
    assert(render_objects_hit(item->body.node, player.player.body.node, &hit) == 0 && hit);
}

int main(void)
{
    FILE *original = fopen("bin/obj1_code.bin", "rb");
    unsigned char first[8], alias[8];
    assert(original && fseek(original, 0x5c5c + 1 * 8, SEEK_SET) == 0);
    assert(fread(first, 1, sizeof(first), original) == sizeof(first));
    assert(fseek(original, 0x5c5c + 162 * 8, SEEK_SET) == 0);
    assert(fread(alias, 1, sizeof(alias), original) == sizeof(alias));
    assert(fclose(original) == 0 && memcmp(first, alias, sizeof(first)) == 0);

    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file; api.Fs.Close = close_file;
    api.Fs.Seek = seek_file; api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    unsigned int map_size, contour_size, slot, bank_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVEL2.MAP", packed,
        sizeof(packed), map, sizeof(map), &dictionary, &map_size) == 0);
    memcpy(original_map, map, map_size);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTOUR.CON", packed,
        sizeof(packed), contours, sizeof(contours), &dictionary, &contour_size) == 0);
    assert(engine_map_collision_initialize(&collision, map, map_size,
        contours, contour_size) == 0);
    assert(assets_load_named_bank(&api, "data/LIONKING.EPF",
        animation_common_bank_list, sizeof(animation_common_bank_list), 8, packed,
        sizeof(packed), sprite, sizeof(sprite), &dictionary, &slot, &bank_size) == 0);
    assert(slot == 89);
    banks[slot] = (RENDER_SPRITE_BANK){sprite, bank_size};
    RENDER_OWNER marker = {0, 0};
    unsigned int count = 0;
    for (unsigned int row = 0; row < collision.height / 2; ++row)
        for (unsigned int col = 0; col < collision.width / 2; ++col) {
            unsigned int type;
            RENDER_OWNER position;
            assert(engine_map_marker(&collision, col, row, &type, &position) == 0);
            if (type == 162) { marker = position; ++count; }
        }
    assert(count == 1);
    RENDER_OWNER camera = {(short)(marker.x - 160), (short)(marker.y - 100)};
    ENGINE_PICKUP *item = setup(marker, 3);
    assert(engine_pickups_tick(&pickups, camera) == 0 && item->object);
    assert(engine_pickups_tick(&pickups, camera) == 0 && item->body.node->parts[19] == 89);
    assert(render_object_pass(&renders, 0, (short)-camera.x, (short)-camera.y,
        banks, 95, pixels) == 0);
    unsigned int visible = 0;
    for (unsigned int i = 0; i < sizeof(pixels); ++i) visible += pixels[i] != 0;
    assert(visible);
    RENDER_OWNER distant = {(short)(marker.x + 600), marker.y};
    assert(engine_pickups_tick(&pickups, distant) == 0 && !item->object && !item->collected);
    assert(engine_pickups_tick(&pickups, camera) == 0 && item->object);
    overlap(item);
    fail_sound = 1;
    assert(engine_pickups_tick(&pickups, camera) == -1 && lives == 3 && !item->collected);
    fail_sound = 0;
    assert(engine_pickups_tick(&pickups, camera) == 0 && lives == 4 && item->collected);
    assert(sounds == 2 && !item->object);
    assert(engine_pickups_restart(&pickups) == 0);
    assert(engine_pickups_tick(&pickups, camera) == 0 && !item->object && lives == 4);
    item = setup(marker, 9);
    assert(engine_pickups_tick(&pickups, camera) == 0 && item->object);
    assert(engine_pickups_tick(&pickups, camera) == 0 && !item->object && item->collected);
    assert(lives == 9 && !sounds);
    assert(memcmp(map, original_map, map_size) == 0);
    puts("PASS: original type-162 extra life, map and sprite, contact, cull, restart, cap and sound error");
    return 0;
}
