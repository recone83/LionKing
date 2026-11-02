#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/pickups.h"
#include "engine/resources.h"
#include "engine/assets.h"
#include "engine/animation_data.h"
#include "engine/lifecycle.h"

static unsigned char packed[79311], map[580488], original_map[580488], contours[4096];
static unsigned char sprites[6][131072], pixels[64000];
static RESOURCE_DICTIONARY dictionary;
static ENGINE_MAP_COLLISION collision;
static ENGINE_OBJECT_POOL objects;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR player;
static ENGINE_OBJECT *player_object;
static ENGINE_PICKUPS pickups;
static RENDER_SPRITE_BANK banks[95];
static unsigned int requests[11], map_size;

static void __attribute__((ms_abi)) log_message(const char *text) { fputs(text, stderr); }
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{ return fopen(path, mode); }
static int __attribute__((ms_abi)) close_file(void *file) { return fclose(file); }
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{ return fseek(file, (long)offset, whence); }
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *data,
    unsigned long long size, unsigned long long count, void *file)
{ return fread(data, size, count, file); }

static int sound(void *context, unsigned short sample)
{
    assert(context == &player && (sample == 1 || sample == 10));
    ++requests[sample];
    return 0;
}

static void setup(void)
{
    engine_initialize_objects(&objects);
    render_initialize_nodes(&renders);
    memset(&player, 0, sizeof(player));
    memset(requests, 0, sizeof(requests));
    player.player.body.owner = (RENDER_OWNER){160, 1261};
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner,
        0, 0, animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    assert(player.player.body.node);
    player_object = engine_acquire_object(&objects, 0);
    assert(player_object);
    assert(animation_program_initialize(&player.player.body.animation, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x5f84, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
    assert(animation_program_step(&player.player.body.animation, player.player.body.node,
        &player.player.body.owner, 0, 0) == 0);
    player.player.context = &player;
    player.sound = sound;
    player.health = 8;
    player.roar_charge = 16;
    assert(engine_pickups_initialize(&pickups, &objects, &renders, &collision,
        &player, 8, 16) == 0);
    assert(pickups.count == 11 && pickups.max_health == 8 && pickups.max_roar == 16);
}

static ENGINE_PICKUP *find_item(unsigned int type)
{
    for (unsigned int i = 0; i < pickups.count; ++i)
        if (pickups.items[i].type == type) return &pickups.items[i];
    assert(0);
    return 0;
}

static RENDER_OWNER activate(ENGINE_PICKUP *item)
{
    RENDER_OWNER camera = {(short)(item->marker.x - 160), (short)(item->marker.y - 120)};
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(item->object && item->body.node);
    return camera;
}

static void overlap(ENGINE_PICKUP *item)
{
    player.player.body.owner = item->body.owner;
    RENDER_BOUNDS a, b;
    assert(render_object_bounds(item->body.node, &a) == 0);
    assert(render_object_bounds(player.player.body.node, &b) == 0);
    player.player.body.owner.x += (short)((a.left + a.right - b.left - b.right) / 2);
    player.player.body.owner.y += (short)((a.top + a.bottom - b.top - b.bottom) / 2);
    short hit;
    assert(render_objects_hit(item->body.node, player.player.body.node, &hit) == 0 && hit);
}

static void draw(RENDER_OWNER camera)
{
    memset(pixels, 0, sizeof(pixels));
    assert(render_object_pass(&renders, 0, -camera.x, -camera.y, banks, 95, pixels) == 0);
    assert(render_object_pass(&renders, 0x80, -camera.x, -camera.y, banks, 95, pixels) == 0);
}

static void check_healing(void)
{
    setup();
    ENGINE_PICKUP *item = find_item(17);
    assert(item->marker.x == 1264 && item->marker.y == 96);
    RENDER_OWNER camera = activate(item);
    assert(item->body.node->parts[19] == 81 && item->body.node->parts[18] == 0);
    player.health = 1;
    player.player.body.owner = (RENDER_OWNER){0, 1261};
    assert(engine_pickups_tick(&pickups, camera) == 0 && !item->collected && player.health == 1);
    overlap(item);
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(item->collected && !item->object && player.health == 5 && requests[10] == 1);
    for (unsigned int i = 0; i < 100; ++i)
        assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(player.health == 5 && requests[10] == 1 && !item->object);
    setup();
    item = find_item(17);
    camera = activate(item);
    player.health = 7;
    overlap(item);
    assert(engine_pickups_tick(&pickups, camera) == 0 && player.health == 8);
    setup();
    item = find_item(18);
    camera = activate(item);
    player.health = 1;
    overlap(item);
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(player.health == 8 && item->collected && !item->object && requests[10] == 1);
    assert(memcmp(map, original_map, map_size) == 0);
    puts("PASS: real healing markers/BUGS frames, +4 and full heal, saturation, exact overlap and no repeat collection");
}

static void check_upgrades(unsigned int type, int screen_y)
{
    setup();
    ENGINE_PICKUP *item = find_item(type);
    RENDER_OWNER camera = activate(item);
    camera.y = (short)(item->marker.y - screen_y);
    overlap(item);
    unsigned char original_frame = item->body.node->parts[18];
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(item->collected && item->flying && !item->glowing && requests[1] == 1);
    assert((item->body.node->pass_flags & 0x80) && !(item->body.node->flags & 0x40));
    assert(item->body.owner.x == 160 && item->body.owner.y == screen_y);
    assert(pickups.max_health == 8 && pickups.max_roar == 16);
    int target = type == 16 ? 16 : 300;
    int divisor = (screen_y - 20) / 2;
    assert(item->horizontal_step == (divisor > 0 ? (target - 160) / divisor : 0));
    player.player.body.owner = (RENDER_OWNER){0, 1261};
    camera = (RENDER_OWNER){0, 1080};
    unsigned int flight_ticks = 0;
    while (item->flying && flight_ticks < 200) {
        assert(engine_pickups_tick(&pickups, camera) == 0);
        if (item->flying) {
            assert(item->body.node->parts[18] == original_frame);
            assert(pickups.max_health == 8 && pickups.max_roar == 16);
            assert(player.health == 8 && player.roar_charge == 16 && !pickups.upgrades);
        }
        draw(camera);
        ++flight_ticks;
    }
    assert(flight_ticks < 200 && item->glowing && item->timer == 36 && pickups.upgrades == 1);
    assert(item->body.owner.y == 20 && item->body.owner.x > target - 8 &&
        item->body.owner.x < target + 8);
    if (type == 16) assert(pickups.max_roar == 24 && player.roar_charge == 24);
    else assert(pickups.max_health == 10 && player.health == 10);
    unsigned int glow_ticks = 0;
    while (item->object && glow_ticks < 40) {
        assert(engine_pickups_tick(&pickups, camera) == 0);
        draw(camera);
        ++glow_ticks;
    }
    assert(glow_ticks == 36 && !item->object && !item->glowing);
    camera = (RENDER_OWNER){(short)(item->marker.x - 160), (short)(item->marker.y - 120)};
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(!item->object && pickups.upgrades == 1 && requests[1] == 1);
    assert(memcmp(map, original_map, map_size) == 0);
    puts("PASS: real upgrade, original screen-space motion, arrival-only meter increase and all 36 glow ticks");
}

static void check_lives(void)
{
    setup();
    ENGINE_PICKUP *checkpoint = find_item(3);
    RENDER_OWNER camera = activate(checkpoint);
    overlap(checkpoint);
    assert(engine_pickups_tick(&pickups, camera) == 0);
    ENGINE_LEVEL_LIFE life;
    assert(engine_level_life_initialize(&life, &player, player_object, 3) == 0);
    assert(engine_level_life_tick(&life, camera) == ENGINE_LIFE_PLAYING);
    for (unsigned int death = 0; death < 3; ++death) {
        player.health = 0;
        player.player.flags_high = 4;
        player.damage_source = &checkpoint->body.owner;
        assert(engine_level_life_tick(&life, camera) == ENGINE_LIFE_DYING);
        assert(life.remaining == 221 && life.lives == 2 - death && life.deaths == death + 1);
        assert(!player.player.flags_high && !player.damage_source && !player.contact_source);
        for (unsigned int i = 0; i < 221; ++i) {
            int result = engine_level_life_tick(&life, (RENDER_OWNER){0, 0});
            if (i < 220) assert(result == ENGINE_LIFE_DYING);
            else assert(result == (death == 2 ? ENGINE_LIFE_GAME_OVER : ENGINE_LIFE_RESTART));
            draw(camera);
        }
        assert(player.player.body.node->parts[19] == 8);
        assert(player.player.body.owner.x == 160 && player.player.body.owner.y == 128);
        if (death < 2) {
            assert(engine_pickups_restart(&pickups) == 0);
            assert(player.health == pickups.max_health && !player.roar_charge);
            player.player.body.owner = pickups.checkpoint;
            player.player.body.node->flags = 0x40;
            assert(checkpoint->activated && !checkpoint->object);
            assert(engine_level_life_tick(&life, camera) == ENGINE_LIFE_PLAYING);
        }
    }
    assert(life.game_over && life.restarts == 2 && !life.lives);
    assert(engine_level_life_tick(&life, camera) == ENGINE_LIFE_GAME_OVER);
    puts("PASS: three lives, every original SYDIE frame over 221 ticks, two checkpoint restores and terminal game-over state");
}

static void check_lethal_fall(void)
{
    setup();
    ENGINE_LEVEL_LIFE life;
    assert(engine_level_life_initialize(&life, &player, player_object, 3) == 0);
    ENGINE_PLAYER_CALL call = {0xc884, 0x5e35, 100};
    assert(engine_level_life_fall(&life, &call) == 0);
    assert(life.remaining == 99 && !player.player.body.node->parts[0]);
    RENDER_OWNER camera = {0, 1080};
    for (unsigned int i = 0; i < 100; ++i) {
        assert(engine_level_life_tick(&life, camera) == ENGINE_LIFE_DYING);
        draw(camera);
        assert(life.lives == 3 && !life.deaths);
        if (i < 99) assert(player.health == 8);
    }
    assert(!player.health && !life.falling);
    assert(engine_level_life_tick(&life, camera) == ENGINE_LIFE_DYING);
    assert(life.deaths == 1 && life.lives == 2 && life.remaining == 221);
    puts("PASS: original lethal-fall branch delays health zero by exactly 100 ticks before normal death/restart");
}

static void check_checkpoints(void)
{
    setup();
    ENGINE_PICKUP *item = find_item(3);
    RENDER_OWNER camera = activate(item);
    overlap(item);
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(item->activated && !item->collected && pickups.checkpoints == 1);
    assert(pickups.checkpoint.x == item->marker.x && pickups.checkpoint.y == item->marker.y);
    for (unsigned int i = 0; i < 400; ++i) {
        assert(engine_pickups_tick(&pickups, camera) == 0);
        draw(camera);
    }
    assert(requests[1] == 1 && pickups.checkpoints == 1);
    RENDER_OWNER away = {0, 1080};
    player.player.body.owner = (RENDER_OWNER){0, 1261};
    assert(engine_pickups_tick(&pickups, away) == 0 && !item->object);
    assert(engine_pickups_tick(&pickups, camera) == 0 && item->object && item->activated);
    for (unsigned int i = 0; i < 200; ++i) {
        assert(engine_pickups_tick(&pickups, camera) == 0);
        draw(camera);
    }
    assert(requests[1] == 1 && pickups.checkpoints == 1);
    assert(memcmp(map, original_map, map_size) == 0);
    puts("PASS: checkpoint marker position, complete SYMORPH/SYDSTYBG sequence and activated cull/return without recollection");
}

static int fail_sound(void *context, unsigned short sample)
{
    assert(context == &player && sample == 10);
    return -1;
}

static void check_restart_and_errors(void)
{
    setup();
    ENGINE_PICKUP *item = find_item(17);
    RENDER_OWNER camera = activate(item);
    overlap(item);
    player.health = 1;
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(engine_pickups_restart(&pickups) == 0);
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(item->collected && !item->object && player.health == 8 && !player.roar_charge);
    setup();
    item = find_item(49);
    camera = activate(item);
    overlap(item);
    assert(engine_pickups_tick(&pickups, camera) == 0 && item->collected && item->flying);
    assert(engine_pickups_restart(&pickups) == 0);
    assert(engine_pickups_tick(&pickups, camera) == 0);
    assert(item->collected && !item->object && !item->flying && !item->glowing);
    assert(pickups.max_health == 8 && !pickups.upgrades);
    setup();
    item = find_item(17);
    camera = activate(item);
    overlap(item);
    player.sound = fail_sound;
    assert(engine_pickups_tick(&pickups, camera) == -1);
    assert(!item->collected && item->object && player.health == 8);
    player.sound = sound;
    ENGINE_MAP_COLLISION invalid = collision;
    invalid.size = collision.table;
    assert(engine_pickups_initialize(&pickups, &objects, &renders, &invalid,
        &player, 8, 16) == -1);
    unsigned int type;
    RENDER_OWNER position;
    assert(engine_map_marker(&collision, collision.width / 2, 0, &type, &position) == -1);
    assert(memcmp(map, original_map, map_size) == 0);
    puts("PASS: restart preserves consumed markers; sound/query errors propagate without collecting or modifying map bytes");
}

int main(void)
{
    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file;
    api.Fs.Close = close_file;
    api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file;
    api.Fs.Read = read_file;
    unsigned int loaded;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LEVEL1.MAP",
        packed, sizeof(packed), map, sizeof(map), &dictionary, &map_size) == 0);
    memcpy(original_map, map, map_size);
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTOUR.CON",
        packed, sizeof(packed), contours, sizeof(contours), &dictionary, &loaded) == 0);
    assert(engine_map_collision_initialize(&collision, map, map_size, contours, loaded) == 0);
    static const unsigned int indices[3] = {0, 12, 13};
    for (unsigned int i = 0; i < 3; ++i) {
        unsigned int slot;
        assert(assets_load_named_bank(&api, "data/LIONKING.EPF", animation_common_bank_list,
            sizeof(animation_common_bank_list), indices[i], packed, sizeof(packed), sprites[i],
            sizeof(sprites[i]), &dictionary, &slot, &loaded) == 0);
        assert(slot == 81 + indices[i]);
        banks[slot] = (RENDER_SPRITE_BANK){sprites[i], loaded};
    }
    unsigned int slot;
    assert(assets_load_named_bank(&api, "data/LIONKING.EPF", animation_level1_bank_list,
        sizeof(animation_level1_bank_list), 17, packed, sizeof(packed), sprites[3],
        sizeof(sprites[3]), &dictionary, &slot, &loaded) == 0 && slot == 79);
    banks[slot] = (RENDER_SPRITE_BANK){sprites[3], loaded};
    assert(assets_load_named_bank(&api, "data/LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), 8, packed, sizeof(packed), sprites[4],
        sizeof(sprites[4]), &dictionary, &slot, &loaded) == 0 && slot == 14);
    banks[slot] = (RENDER_SPRITE_BANK){sprites[4], loaded};
    assert(assets_load_named_bank(&api, "data/LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), 2, packed, sizeof(packed), sprites[5],
        sizeof(sprites[5]), &dictionary, &slot, &loaded) == 0 && slot == 8);
    banks[slot] = (RENDER_SPRITE_BANK){sprites[5], loaded};
    check_healing();
    check_upgrades(16, 120);
    check_upgrades(49, 120);
    check_upgrades(16, 21);
    check_upgrades(49, 20);
    check_checkpoints();
    check_lives();
    check_lethal_fall();
    check_restart_and_errors();
    return 0;
}
