#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/animation_data.h"
#include "engine/assets.h"
#include "engine/ostrich_visual.h"
#include "engine/ostrich_obstacle.h"
#include "engine/ostrich_sequence.h"
#include "engine/resources.h"

static unsigned char packed[79311], sprites[4][65536], pixels[64000];
static unsigned char hazard_sprites[2][65536];
static RESOURCE_DICTIONARY dictionary;
static ENGINE_OBJECT_POOL objects;
static RENDER_POOL renders;
static RENDER_SPRITE_BANK banks[127];

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

static unsigned int visible(void)
{
    unsigned int count = 0;
    for (unsigned int i = 0; i < sizeof(pixels); ++i) count += pixels[i] != 0;
    return count;
}

static void check_sequence(void)
{
    RENDER_OWNER player_position = {0, 0}, bird_position = {0, 0};
    RENDER_NODE *player = render_acquire_node(&renders, &player_position, 0, 0,
        animation_enemy_data + 0xc994 - ANIMATION_ENEMY_BASE, 20);
    RENDER_NODE *bird = render_acquire_node(&renders, &bird_position, 0, 0,
        animation_enemy_data + 0xc994 - ANIMATION_ENEMY_BASE, 20);
    assert(player && bird);
    for (unsigned int marker = 52; marker <= 53; ++marker) {
        short base = marker == 52 ? 2208 : 3728;
        RENDER_FOLLOW_CAMERA camera = {{base, 200}, 128};
        RENDER_OSTRICH_SCROLL scroll;
        ENGINE_OSTRICH_SEQUENCE sequence = {0};
        ENGINE_OSTRICH_SEQUENCE_RESULT result;
        assert(render_ostrich_scroll_initialize(&scroll, base, base) == 0);
        assert(engine_ostrich_sequence_initialize(&sequence, &objects, &renders, marker) == 0);
        assert(engine_ostrich_sequence_initialize(&sequence, &objects, &renders, marker) == -1);
        unsigned int spawned = 0, culled = 0, wraps = 0, max_count = 0;
        for (unsigned int tick = 0; tick < 2000; ++tick) {
            camera.position.x += 4;
            short shift;
            assert(render_ostrich_scroll_step(&scroll, &camera, &shift) == 0);
            assert(engine_ostrich_sequence_shift(&sequence, shift) == 0);
            if (shift) ++wraps;
            player_position = (RENDER_OWNER){(short)(camera.position.x + 48), 0};
            bird_position = player_position;
            RENDER_BOUNDS bounds = {(short)(camera.position.x - 111), 89,
                (short)(camera.position.x + 415), 504};
            assert(engine_ostrich_sequence_tick(&sequence, (short)scroll.distance,
                camera.position, &bounds, player, bird, &result) == 0);
            spawned += result.spawned;
            culled += result.culled;
            if (sequence.count > max_count) max_count = sequence.count;
            assert(!result.player_hit && !result.bird_hit);
            if (result.route_status == ENGINE_OSTRICH_FINISHED) break;
        }
        assert(sequence.route.finished && sequence.ending &&
            spawned == (marker == 52 ? 9U : 18U) &&
            culled + sequence.count == spawned && wraps >= 9 &&
            max_count < ENGINE_OSTRICH_HAZARD_CAPACITY);
        assert(engine_ostrich_sequence_release(&sequence) == 0);
        assert(!objects.head && !sequence.objects && !sequence.renders);
    }

    ENGINE_OSTRICH_SEQUENCE sequence = {0};
    ENGINE_OSTRICH_SEQUENCE_RESULT result;
    RENDER_BOUNDS bounds = {2000, 0, 2800, 500};
    assert(engine_ostrich_sequence_initialize(&sequence, &objects, &renders, 52) == 0);
    sequence.route.offset = 16;
    ENGINE_OBJECT *held[ENGINE_OBJECT_CAPACITY - 1];
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY - 1; ++i) {
        held[i] = engine_acquire_object(&objects, 0);
        assert(held[i]);
    }
    assert(engine_ostrich_sequence_tick(&sequence, 3062, (RENDER_OWNER){2208, 200},
        &bounds, player, bird, &result) == -1);
    assert(sequence.route.offset == 16 && sequence.count == 0 && objects.free_head);
    assert(engine_release_object(&objects, held[0]) == 0);
    assert(engine_ostrich_sequence_tick(&sequence, 3062, (RENDER_OWNER){2208, 200},
        &bounds, player, bird, &result) == 0);
    assert(result.spawned == 2 && result.route_flags == 12 && sequence.count == 2);
    player_position = (RENDER_OWNER){2588, 460};
    bird_position = (RENDER_OWNER){2588, 436};
    assert(engine_ostrich_sequence_tick(&sequence, 3062, (RENDER_OWNER){2208, 200},
        &bounds, player, bird, &result) == 0 && result.route_status == ENGINE_OSTRICH_WAIT);
    assert(result.player_hit == &sequence.hazards[sequence.order[1]].position &&
        result.bird_hit);
    short before_x = sequence.hazards[sequence.order[0]].position.x;
    assert(engine_ostrich_sequence_shift(&sequence, 512) == 0);
    assert(sequence.hazards[sequence.order[0]].position.x == before_x - 512);
    assert(engine_ostrich_sequence_release(&sequence) == 0);
    for (unsigned int i = 1; i < ENGINE_OBJECT_CAPACITY - 1; ++i)
        assert(engine_release_object(&objects, held[i]) == 0);
    assert(!objects.head);
    assert(render_release_node(&renders, player) == 0);
    assert(render_release_node(&renders, bird) == 0);
    assert(!renders.head);
}

static void check_hazards(void)
{
    static const ENGINE_OSTRICH_OBSTACLE descriptors[] = {
        {0x20826, 0xc214, 2300, 344},
        {0x208cd, 0xc23c, 2300, 376},
        {0x20826, 0xc214, 2300, 436},
        {0x20977, 0xcd54, 2300, 464}
    };
    RENDER_BOUNDS active = {2000, 200, 2600, 500};
    RENDER_OWNER player_position = {2000, 300}, bird_position = {2000, 300};
    RENDER_NODE *player = render_acquire_node(&renders, &player_position, 0, 0,
        animation_enemy_data + 0xc994 - ANIMATION_ENEMY_BASE, 20);
    RENDER_NODE *bird = render_acquire_node(&renders, &bird_position, 0, 0,
        animation_enemy_data + 0xc994 - ANIMATION_ENEMY_BASE, 20);
    assert(player && bird);
    for (unsigned int i = 0; i < 4; ++i) {
        ENGINE_OSTRICH_HAZARD hazard = {0};
        player_position = bird_position = (RENDER_OWNER){2000, 300};
        assert(engine_ostrich_hazard_create(&hazard, &objects, &renders,
            &descriptors[i]) == 0);
        assert(hazard.object && hazard.collision && !!hazard.decoration == (i != 3));
        if (hazard.decoration)
            assert(hazard.decoration->owner == &hazard.position &&
                hazard.decoration->order == 0 && hazard.collision->order == 1 &&
                (hazard.decoration->pass_flags & 0x20));
        assert(engine_ostrich_hazard_tick(&hazard, &active, player, bird) ==
            ENGINE_OSTRICH_HAZARD_CLEAR);
        memset(pixels, 0, sizeof(pixels));
        assert(render_object_pass(&renders, 0, -2200, -300, banks, 127, pixels) == 0 &&
            visible() > 0);
        if (i == 3) {
            assert(hazard.armed);
            player_position.x = 2236;
            assert(engine_ostrich_hazard_tick(&hazard, &active, player, bird) ==
                ENGINE_OSTRICH_HAZARD_CLEAR && hazard.armed);
            player_position.x = 2237;
            assert(engine_ostrich_hazard_tick(&hazard, &active, player, bird) ==
                ENGINE_OSTRICH_HAZARD_CLEAR && !hazard.armed &&
                hazard.animation.script.position == 0x19c0e);
        }
        player_position = bird_position = hazard.position;
        assert(engine_ostrich_hazard_tick(&hazard, &active, player, bird) ==
            ENGINE_OSTRICH_HAZARD_PLAYER_HIT);
        player_position = (RENDER_OWNER){2000, 300};
        assert(engine_ostrich_hazard_tick(&hazard, &active, player, bird) ==
            ENGINE_OSTRICH_HAZARD_BIRD_HIT);
        if (i == 3) {
            player_position.x = 2301;
            assert(engine_ostrich_hazard_tick(&hazard, &active, player, bird) ==
                ENGINE_OSTRICH_HAZARD_CLEAR);
        }
        RENDER_BOUNDS distant = {0, 0, 100, 100};
        if (i == 3) player_position.x = 2301;
        assert(engine_ostrich_hazard_tick(&hazard, &distant, player, bird) ==
            ENGINE_OSTRICH_HAZARD_CULLED);
        assert(!hazard.object && !hazard.collision && !hazard.decoration);
        assert(engine_ostrich_hazard_release(&hazard) == 0);
    }
    ENGINE_OSTRICH_HAZARD invalid = {0};
    ENGINE_OSTRICH_OBSTACLE wrong = descriptors[0];
    wrong.definition = 0xcd54;
    assert(engine_ostrich_hazard_create(&invalid, &objects, &renders, &wrong) == -1);
    assert(!objects.head);
    for (unsigned int marker = 52; marker <= 53; ++marker) {
        ENGINE_OSTRICH_ROUTE route;
        ENGINE_OSTRICH_EVENT event;
        unsigned int spawned = 0;
        assert(engine_ostrich_route_initialize(&route, marker) == 0);
        for (;;) {
            int result = engine_ostrich_route_tick(&route, 8000, 2208, &event);
            assert(result != -1 && result != ENGINE_OSTRICH_WAIT);
            if (result == ENGINE_OSTRICH_FINISHED) break;
            for (unsigned int i = 0; i < event.count; ++i) {
                ENGINE_OSTRICH_HAZARD hazard = {0};
                assert(engine_ostrich_hazard_create(&hazard, &objects, &renders,
                    &event.obstacles[i]) == 0);
                assert(hazard.position.x == 2588);
                assert(engine_ostrich_hazard_release(&hazard) == 0);
                ++spawned;
            }
        }
        assert(spawned == (marker == 52 ? 9U : 18U));
    }
    assert(render_release_node(&renders, player) == 0);
    assert(render_release_node(&renders, bird) == 0);
    assert(!renders.head);
    ENGINE_OBJECT *held_objects[ENGINE_OBJECT_CAPACITY];
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY; ++i) {
        held_objects[i] = engine_acquire_object(&objects, 0);
        assert(held_objects[i]);
    }
    assert(engine_ostrich_hazard_create(&invalid, &objects, &renders, &descriptors[0]) == -1);
    assert(!invalid.collision && !invalid.decoration && !renders.head);
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY; ++i)
        assert(engine_release_object(&objects, held_objects[i]) == 0);
    RENDER_NODE *held_nodes[RENDER_NODE_COUNT];
    for (unsigned int i = 0; i < RENDER_NODE_COUNT; ++i) {
        held_nodes[i] = render_acquire_node(&renders, &player_position, 0, 0,
            animation_enemy_data + 0xc994 - ANIMATION_ENEMY_BASE, 20);
        assert(held_nodes[i]);
    }
    assert(render_release_node(&renders, held_nodes[0]) == 0);
    assert(engine_ostrich_hazard_create(&invalid, &objects, &renders, &descriptors[0]) == -1);
    assert(!invalid.collision && !invalid.decoration && !invalid.object && !objects.head);
    for (unsigned int i = 1; i < RENDER_NODE_COUNT; ++i)
        assert(render_release_node(&renders, held_nodes[i]) == 0);
    assert(!renders.head);
}

int main(void)
{
    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file; api.Fs.Close = close_file;
    api.Fs.Seek = seek_file; api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    for (unsigned int i = 0; i < 4; ++i) {
        unsigned int slot, size;
        assert(assets_load_named_bank(&api, "data/LIONKING.EPF",
            animation_level2_bank_list, sizeof(animation_level2_bank_list), 14 + i,
            packed, sizeof(packed), sprites[i], sizeof(sprites[i]), &dictionary,
            &slot, &size) == 0 && slot == 120 + i);
        banks[slot] = (RENDER_SPRITE_BANK){sprites[i], size};
    }
    for (unsigned int i = 0; i < 2; ++i) {
        unsigned int slot, size;
        assert(assets_load_named_bank(&api, "data/LIONKING.EPF",
            animation_level2_bank_list, sizeof(animation_level2_bank_list), i ? 19 : 2,
            packed, sizeof(packed), hazard_sprites[i], sizeof(hazard_sprites[i]),
            &dictionary, &slot, &size) == 0 && slot == (i ? 125U : 108U));
        banks[slot] = (RENDER_SPRITE_BANK){hazard_sprites[i], size};
    }
    unsigned char blank[14];
    FILE *source = fopen("bin/obj2_data.bin", "rb");
    assert(source && fseek(source, 0x16062, SEEK_SET) == 0 &&
        fread(blank, 1, sizeof(blank), source) == sizeof(blank) &&
        fclose(source) == 0);
    assert(memcmp(blank, animation_enemy_data + 0x16062 - ANIMATION_ENEMY_BASE,
        sizeof(blank)) == 0);
    engine_initialize_objects(&objects);
    render_initialize_nodes(&renders);
    ENGINE_OSTRICH_VISUAL bird = {0};
    assert(engine_ostrich_visual_create(&bird, &objects, &renders,
        (RENDER_OWNER){2208, 480}, 0) == 0);
    assert(engine_ostrich_visual_create(&bird, &objects, &renders,
        (RENDER_OWNER){2208, 480}, 0) == -1);
    assert(engine_ostrich_visual_tick(&bird) == 0);
    assert(bird.body->parts[19] == 120 && bird.body->parts[18] == 1);
    RENDER_OWNER attachment;
    assert(engine_ostrich_visual_attachment(&bird, &attachment) == 0);
    assert(attachment.x == 2212 && attachment.y == 439);
    unsigned int waiting_position = bird.body_animation.visual.position;
    unsigned char waiting_remaining = bird.body_animation.visual.remaining;
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_MOUNTING) == 0);
    assert(bird.body_animation.visual.position == waiting_position &&
        bird.body_animation.visual.remaining == waiting_remaining);
    assert(bird.head && bird.head->order == -100 && bird.head->owner == &bird.position);
    assert(engine_ostrich_visual_tick(&bird) == 0);
    assert(bird.head->parts[19] == 122 && bird.head->parts[18] == 0);
    memset(pixels, 0, sizeof(pixels));
    assert(render_object_pass(&renders, 0, -2100, -350, banks, 127, pixels) == 0);
    assert(visible() > 500);
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_RUNNING) == 0);
    unsigned int frames[12] = {0}, head_frames[12] = {0};
    for (unsigned int i = 0; i < 200; ++i) {
        assert(engine_ostrich_visual_tick(&bird) == 0);
        assert(bird.body->parts[19] == 120 && bird.head->parts[19] == 122);
        ++frames[bird.body->parts[18]];
        ++head_frames[bird.head->parts[18]];
    }
    for (unsigned int i = 0; i < 12; ++i) {
        assert(!!frames[i] == (i >= 2));
        assert(!!head_frames[i] == (i <= 10));
    }
    unsigned int body_position = bird.body_animation.visual.position;
    unsigned char body_remaining = bird.body_animation.visual.remaining;
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_CROUCHING) == 0);
    assert(bird.body_animation.visual.position == body_position &&
        bird.body_animation.visual.remaining == body_remaining);
    assert(engine_ostrich_visual_tick(&bird) == 0 && bird.head->parts[19] == 121);
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_RUNNING) == 0);
    assert(engine_ostrich_visual_tick(&bird) == 0 &&
        bird.head->parts[19] == 121 && bird.head->parts[18] == 11);
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_JUMPING) == 0);
    assert(engine_ostrich_visual_tick(&bird) == 0 && bird.body->parts[19] == 123 &&
        bird.body->parts[18] == 0 && bird.head->parts[0] == 0);
    memset(pixels, 0, sizeof(pixels));
    assert(render_object_pass(&renders, 0, -2100, -350, banks, 127, pixels) == 0 &&
        visible() > 500);
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_RUNNING) == 0);
    assert(engine_ostrich_visual_tick(&bird) == 0 && bird.body->parts[19] == 120 &&
        bird.head->parts[19] == 122);
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_WAITING) == -1);
    assert(engine_ostrich_visual_release(&bird) == 0);
    assert(engine_ostrich_visual_release(&bird) == 0);
    assert(!renders.head && !objects.head);
    ENGINE_OBJECT *held[ENGINE_OBJECT_CAPACITY];
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY; ++i) {
        held[i] = engine_acquire_object(&objects, 0);
        assert(held[i]);
    }
    assert(engine_ostrich_visual_create(&bird, &objects, &renders,
        (RENDER_OWNER){2208, 480}, 0) == -1);
    assert(!bird.body && !renders.head);
    assert(engine_release_object(&objects, held[0]) == 0);
    assert(engine_ostrich_visual_create(&bird, &objects, &renders,
        (RENDER_OWNER){2208, 480}, 0) == 0);
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_MOUNTING) == -1);
    assert(!bird.head && bird.pose == ENGINE_OSTRICH_WAITING && renders.head == bird.body);
    assert(engine_ostrich_visual_release(&bird) == 0);
    for (unsigned int i = 1; i < ENGINE_OBJECT_CAPACITY; ++i)
        assert(engine_release_object(&objects, held[i]) == 0);
    assert(!renders.head && !objects.head);
    RENDER_NODE *nodes[RENDER_NODE_COUNT];
    RENDER_OWNER position = {0, 0};
    for (unsigned int i = 0; i < RENDER_NODE_COUNT; ++i) {
        nodes[i] = render_acquire_node(&renders, &position, 0, 0,
            animation_enemy_data + 0xc994 - ANIMATION_ENEMY_BASE, 20);
        assert(nodes[i]);
    }
    assert(engine_ostrich_visual_create(&bird, &objects, &renders,
        (RENDER_OWNER){2208, 480}, 0) == -1 && !objects.head);
    assert(render_release_node(&renders, nodes[0]) == 0);
    assert(engine_ostrich_visual_create(&bird, &objects, &renders,
        (RENDER_OWNER){2208, 480}, 0) == 0);
    assert(engine_ostrich_visual_set_pose(&bird, ENGINE_OSTRICH_MOUNTING) == -1 &&
        !bird.head && bird.pose == ENGINE_OSTRICH_WAITING);
    assert(engine_ostrich_visual_release(&bird) == 0);
    for (unsigned int i = 1; i < RENDER_NODE_COUNT; ++i)
        assert(render_release_node(&renders, nodes[i]) == 0);
    assert(!renders.head && !objects.head);
    check_hazards();
    check_sequence();
    puts("PASS: ostrich body, head, animations, route hazards, collisions and lifecycle");
    return 0;
}
