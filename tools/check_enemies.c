#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/resources.h"
#include "engine/enemies.h"
#include "engine/animation_data.h"
#include "engine/assets.h"

static unsigned char packed[79311], map[580488], contours[4096];
static RESOURCE_DICTIONARY dictionary;
static void __attribute__((ms_abi)) log_message(const char *text) { fputs(text, stderr); }
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{ return fopen(path, mode); }
static int __attribute__((ms_abi)) close_file(void *file) { return fclose(file); }
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{ return fseek(file, (long)offset, whence); }
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *p,
    unsigned long long size, unsigned long long count, void *file)
{ return fread(p, size, count, file); }
static unsigned int word(const unsigned char *p) { return p[0] | (unsigned int)p[1] << 8; }
static unsigned int dword(const unsigned char *p) { return word(p) | word(p + 2) << 16; }
static ENGINE_MAP_COLLISION collision;
static ENGINE_ENEMIES enemies;
static ENGINE_OBJECT_POOL pool;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR player;
static ENGINE_OBJECT *player_object;
static unsigned char collision_flags;
static unsigned char original_map[580488], enemy_banks[4][32768], player_bank[32768];
static unsigned char pixels[64000], previous_pixels[64000];
static RENDER_SPRITE_BANK banks[81];
static const RENDER_OWNER camera = {0, 1080};
static unsigned int sound_requests;

static int sound(void *context, unsigned short sample)
{
    assert(context == &player && sample == 4);
    ++sound_requests;
    return 0;
}

static void setup(void)
{
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    memset(&player, 0, sizeof(player));
    player.player.body.owner = (RENDER_OWNER){100, 1261};
    player.player.body.render_pool = &renders;
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner,
        0, 0, animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    player_object = engine_acquire_object(&pool, 0);
    assert(player_object && player.player.body.node);
    assert(animation_program_initialize(&player.player.body.animation, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x5f84, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
    assert(animation_program_step(&player.player.body.animation, player.player.body.node,
        &player.player.body.owner, 0, 0) == 0);
    player.player.context = &player;
    player.player.collision_flags = &collision_flags;
    player.sound = sound;
    player.health = 10;
    player.roar_charge = 100;
    sound_requests = 0;
    assert(engine_enemies_initialize(&enemies, &pool, &renders, &collision, &player) == 0);
    assert(enemies.count == 14);
    assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(enemies.spawned == 1);
}

static ENGINE_LIZARD *lower_lizard(void)
{
    for (unsigned int i = 0; i < enemies.count; ++i)
        if (enemies.lizards[i].marker.x == 352 && enemies.lizards[i].marker.y == 1248)
            return &enemies.lizards[i];
    assert(0);
    return 0;
}

static void tick(void)
{
    assert(engine_enemies_player_clock(&enemies) == 0);
    ++pool.update_count;
    assert(engine_enemies_tick(&enemies, camera) == 0);
}

static void check_patrol(void)
{
    setup();
    ENGINE_LIZARD *lizard = lower_lizard();
    assert(lizard->handler == 0x1127e && lizard->timer == 100);
    assert(lizard->body.node->parts[19] == 76);
    for (unsigned int i = 0; i < 30; ++i) tick();
    assert(lizard->body.owner.x == 367 && lizard->timer == 70);
    assert(lizard->body.owner.y == 1259);
    memset(pixels, 0, sizeof(pixels));
    assert(render_object_pass(&renders, 0, -100, -1080, banks, 81, pixels) == 0);
    memcpy(previous_pixels, pixels, sizeof(pixels));
    for (unsigned int i = 0; i < 8; ++i) tick();
    assert(player.roar_charge == 101);
    memset(pixels, 0, sizeof(pixels));
    assert(render_object_pass(&renders, 0, -100, -1080, banks, 81, pixels) == 0);
    assert(memcmp(previous_pixels, pixels, sizeof(pixels)) != 0);
    setup();
    lizard = lower_lizard();
    for (unsigned int i = 0; i < 30; ++i) tick();
    lizard->kind = 0x11;
    tick();
    assert(lizard->facing == 1 && lizard->timer == 30);
    assert(lizard->body.motion.velocity_x == UINT32_C(0xffff8000));
    assert(lizard->body.node->parts[19] == 75);
    lizard->kind = 0x10;
    tick();
    assert(lizard->facing == 0 && enemies.turns == 2);
    puts("PASS: original half-pixel patrol, real contour support, both turns and visible original banks");
}

static void check_contact(void)
{
    setup();
    ENGINE_LIZARD *lizard = lower_lizard();
    for (unsigned int i = 0; i < 30; ++i) tick();
    player.player.body.owner = lizard->body.owner;
    tick();
    assert(player.player.flags_high & 4);
    assert(player.damage_source == &lizard->body.owner);
    assert(engine_player_damage(&pool, player_object, &player) == 0);
    assert(player.health == 9 && player.player.immunity == 100 && sound_requests == 1);
    for (unsigned int i = 0; i < 100; ++i) {
        assert(engine_enemies_player_clock(&enemies) == 0);
        assert(!(player.player.flags_high & 4));
        ++pool.update_count;
    }
    assert(player.player.immunity == 0 && player.roar_charge == 4);
    setup();
    lizard = lower_lizard();
    for (unsigned int i = 0; i < 30; ++i) tick();
    player.player.body.owner = (RENDER_OWNER){lizard->body.owner.x,
        (short)(lizard->body.owner.y - 10)};
    player.player.flags_high = 0x10;
    player.player.body.motion.velocity_y = UINT32_C(0xffff0000);
    tick();
    assert(lizard->handler == 0x1127e && !(player.player.flags_high & 0x20));
    player.player.body.motion.velocity_y = 0x4000;
    tick();
    assert(lizard->handler == 0x1127e && !(player.player.flags_high & 0x20));
    player.player.body.motion.velocity_y = 0x4001;
    tick();
    assert(lizard->handler == 0x11609 && (player.player.flags_high & 0x20));
    assert(lizard->timer == 31 && player.health == 10);
    for (unsigned int i = 0; i < 33; ++i) tick();
    assert(lizard->destroyed && !lizard->object && enemies.defeated == 1);
    assert(render_object_pass(&renders, 0, 0, -1080, banks, 81, pixels) == 0);
    assert(engine_enemies_tick(&enemies, (RENDER_OWNER){700, 0}) == 0);
    assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(!lizard->object);
    puts("PASS: real overlap damage, recoil/immunity, strict downward threshold, death cleanup and no respawn");
}

static void check_attack_roar(void)
{
    setup();
    ENGINE_LIZARD *lizard = lower_lizard();
    for (unsigned int i = 0; i < 30; ++i) tick();
    lizard->timer = 1;
    player.player.body.owner = (RENDER_OWNER){(short)(lizard->body.owner.x + 60), lizard->body.owner.y};
    tick();
    assert(lizard->handler == 0x114ea && enemies.attacks == 1);
    assert(lizard->body.node->parts[19] == 74);
    for (unsigned int i = 0; i < 65; ++i) tick();
    assert(lizard->handler == 0x1127e && lizard->timer == 100);
    player.roar_pulse = 40;
    tick();
    assert(lizard->handler == 0x1117a && enemies.stuns == 1);
    short duration = lizard->timer;
    assert(duration == 38);
    player.roar_pulse = 0;
    for (int i = 0; i < duration + 1; ++i) tick();
    assert(lizard->handler == 0x1127e && lizard->body.owner.x == lizard->stun_x);
    setup();
    lizard = lower_lizard();
    for (unsigned int i = 0; i < 30; ++i) tick();
    lizard->kind = 0x90;
    lizard->cell_x = -1;
    tick();
    assert(lizard->handler == 0x11a51 && lizard->timer == 70 && enemies.jumps == 1);
    tick();
    assert(lizard->body.motion.velocity_x == 0x7000);
    for (unsigned int i = 0; i < 70; ++i) tick();
    assert(lizard->handler == 0x1127e && lizard->body.motion.velocity_x == 0x8000);
    puts("PASS: original attack cycle, distance-scaled roar stun and obstacle pause/braking/resume");
}

static void check_attack_windows(void)
{
    static const unsigned char point_parts[20] = {
        0, 0, 255, 255, 255, 255, 1, 0, 1, 0
    };
    for (unsigned int facing = 0; facing < 2; ++facing) {
        for (unsigned int probe = 0; probe < 2; ++probe) {
            for (short timer = 47; timer <= 55; ++timer) {
                setup();
                ENGINE_LIZARD *lizard = lower_lizard();
                lizard->timer = 1;
                player.player.body.owner = (RENDER_OWNER){412, 1248};
                tick();
                assert(lizard->handler == 0x114ea);
                lizard->timer = timer;
                lizard->facing = (unsigned char)facing;
                lizard->body.node->pass_flags = facing ? 8 : 0;
                lizard->body.node->parts = point_parts;
                player.player.body.node->parts = point_parts;
                int dx = probe ? 45 : 15;
                player.player.body.owner = (RENDER_OWNER){
                    (short)(lizard->body.owner.x + (facing ? -dx : dx)),
                    (short)(lizard->body.owner.y - (probe ? 8 : 5))
                };
                tick();
                int expected = probe ? timer >= 52 && timer <= 54 : timer >= 48 && timer <= 50;
                assert(!!(player.player.flags_high & 4) == expected);
                assert(enemies.contacts == (unsigned int)expected);
                if (expected) assert(player.damage_source == &lizard->body.owner);
            }
        }
    }
    puts("PASS: both exact attack windows and excluded boundary ticks, mirrored in both directions");
}

int main(void)
{
    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file; api.Fs.Close = close_file;
    api.Fs.Seek = seek_file; api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    unsigned int size, contour_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVEL1.MAP",
        packed, sizeof(packed), map, sizeof(map), &dictionary, &size) == 0);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTOUR.CON",
        packed, sizeof(packed), contours, sizeof(contours), &dictionary, &contour_size) == 0);
    assert(engine_map_collision_initialize(&collision, map, size, contours, contour_size) == 0);
    memcpy(original_map, map, size);
    static const unsigned int indices[4] = {4, 12, 13, 14};
    for (unsigned int i = 0; i < 4; ++i) {
        unsigned int slot, loaded;
        assert(assets_load_named_bank(&api, "data/LIONKING.EPF", animation_level1_bank_list,
            sizeof(animation_level1_bank_list), indices[i], packed, sizeof(packed),
            enemy_banks[i], sizeof(enemy_banks[i]), &dictionary, &slot, &loaded) == 0);
        banks[slot] = (RENDER_SPRITE_BANK){enemy_banks[i], loaded};
    }
    unsigned int slot, loaded;
    assert(assets_load_named_bank(&api, "data/LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), 8, packed, sizeof(packed), player_bank,
        sizeof(player_bank), &dictionary, &slot, &loaded) == 0);
    banks[slot] = (RENDER_SPRITE_BANK){player_bank, loaded};
    check_patrol();
    check_contact();
    check_attack_roar();
    check_attack_windows();
    setup();
    assert(engine_enemies_tick(&enemies, (RENDER_OWNER){700, 0}) == 0);
    assert(enemies.culled == 1 && !lower_lizard()->object);
    assert(engine_enemies_tick(&enemies, camera) == 0);
    assert(enemies.spawned > 1 && lower_lizard()->body.owner.x == 352);
    assert(memcmp(map, original_map, size) == 0);
    unsigned int table = dword(map + 16);
    ENGINE_MAP_COLLISION truncated = collision;
    truncated.size = table;
    assert(engine_enemies_initialize(&enemies, &pool, &renders, &truncated, &player) == -1);
    puts("PASS: viewport spawning/culling, original marker respawn, unchanged map bytes and bounded input");
    return 0;
}
