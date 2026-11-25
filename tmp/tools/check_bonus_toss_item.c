#include <assert.h>
#include <stdio.h>
#include "engine/animation_data.h"
#include "engine/bonus_toss.h"
#include "engine/bonus_toss_item.h"
#include "engine/bonus_toss_stage.h"
#include "engine/random.h"

static RENDER_POOL pool;
static BONUS_TOSS_PLAYER player;
static BONUS_TOSS_ITEM item;
static uint32_t random_state;
static BONUS_TOSS_ITEM_RESULT result;

static int burp(void *context)
{
    (void)context;
    return 0;
}

static int flat_ground(void *context, short x, short y, short *supported, short *delta_y)
{
    (void)context;
    (void)x;
    (void)y;
    *supported = -1;
    *delta_y = 0;
    return 0;
}

static int test_ground(void *context, short x, short y, short *supported, short *delta_y)
{
    (void)x;
    (void)y;
    int mode = *(int *)context;
    if (mode < 0) return -1;
    *supported = (short)mode;
    *delta_y = mode ? 2 : 0;
    return 0;
}

static void check_timon_gravity(void)
{
    RENDER_POOL stage_pool;
    BONUS_TOSS_STAGE stage;
    unsigned char lives = 3;
    unsigned int continues = 1;
    unsigned short roar = 16;
    int mode = 0;
    assert(bonus_toss_stage_initialize(&stage, &stage_pool, 0x010101, &lives, &continues,
        &roar, burp, 0, 0, 0) == -1);
    assert(bonus_toss_stage_initialize(&stage, &stage_pool, 0x010101, &lives, &continues,
        &roar, burp, 0, test_ground, &mode) == 0);
    for (unsigned int i = 0; i < 3; ++i) {
        stage.move_ticks = 2;
        stage.move_delay = 1;
        assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
        assert(stage.timon.y == (i == 2 ? 49 : 48));
    }
    assert(stage.timon_vertical_speed == 0xea00);
    mode = -1;
    stage.move_ticks = 2;
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == -1);
    mode = 1;
    stage.move_ticks = 2;
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.timon.y == 51 && stage.timon_vertical_speed == 0);
    assert(bonus_toss_stage_release(&stage) == 0);
}

static void reset(void)
{
    render_initialize_nodes(&pool);
    random_state = 0x010101;
    assert(bonus_toss_player_initialize(&player, &pool, &random_state, burp, 0) == 0);
    assert(bonus_toss_player_tick(&player, 0, 0, 0) == 0);
}

static void check_original_fall_trajectories(void)
{
    static const struct {
        unsigned char kind;
        unsigned short positions[4];
        unsigned short fractions[4];
        unsigned int ticks_to_160;
    } cases[] = {
        {0, {13, 38, 75, 123}, {0x5200, 0x5c00, 0x1e00, 0x9800}, 47},
        {1, {8, 27, 57, 98}, {0x3400, 0x5800, 0x6c00, 0x7000}, 52},
        {2, {1, 6, 12, 21}, {0xea00, 0x2c00, 0xc600, 0xb800}, 114}
    };
    for (unsigned int i = 0; i < sizeof(cases) / sizeof(cases[0]); ++i) {
        reset();
        assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){200, 0},
            cases[i].kind, &random_state) == 0);
        for (unsigned int tick = 1; tick <= cases[i].ticks_to_160; ++tick) {
            assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == 0);
            assert(result == BONUS_TOSS_ITEM_FALLING);
            if (tick <= 40 && tick % 10 == 0) {
                unsigned int sample = tick / 10 - 1;
                assert(item.owner.y == cases[i].positions[sample]);
                assert(item.motion.fraction_y == cases[i].fractions[sample]);
            }
            if (tick < cases[i].ticks_to_160) assert(item.owner.y < 160);
        }
        assert(item.owner.y >= 160);
        assert(bonus_toss_item_release(&item, &pool) == 0);
    }
}

static void check_selector(void)
{
    static const short intervals[] = {
        16, 16, 16, 16, 16, 16, 16, 16, 17, 18, 20, 21, 24, 29, 32, 35
    };
    static const unsigned short limits[] = {24, 32, 40, 48, 48, 48, 24, 32, 40, 48};
    BONUS_TOSS_SELECTOR selector = {&random_state, 15, 0, 0, 1, 3, 1, 0, 0};
    BONUS_TOSS_SELECTION selection;
    short interval;
    for (unsigned int i = 0; i < 16; ++i) {
        selector.speed = (unsigned short)i;
        assert(bonus_toss_spawn_interval(&selector, &interval) == 0 && interval == intervals[i]);
    }
    selector.speed = 15;
    selector.interval_progress = 50;
    assert(bonus_toss_spawn_interval(&selector, &interval) == 0 && interval == 12);
    selector.next_hazard = 1;
    assert(bonus_toss_spawn_interval(&selector, &interval) == 0 && interval == 55);
    random_state = 0x010101;
    assert(bonus_toss_select_item(&selector, 0, &selection) == 0);
    assert(selection.kind == 7 && selection.reset_timer && selection.timer == -55);
    assert(!selector.next_hazard);

    selector.progress = 0;
    selector.interval_progress = 0;
    selector.next_hazard = 0;
    random_state = 0x010101;
    assert(bonus_toss_select_item(&selector, 0, &selection) == 0);
    assert(selection.kind == 2 && !selection.reset_timer && !selector.next_hazard);
    random_state = 0x010101;
    assert(bonus_toss_select_item(&selector, 1, &selection) == 0);
    assert(selection.kind == 3 && selection.reset_timer && selection.timer == -50);
    selector.lives = 9;
    random_state = 0x010101;
    assert(bonus_toss_select_item(&selector, 1, &selection) == 0);
    assert(selection.kind == 2 && !selection.reset_timer);
    selector.progress = 99;
    random_state = 0x010101;
    assert(bonus_toss_select_item(&selector, 1, &selection) == 0);
    assert(selection.kind == 2 && !selection.reset_timer);
    selector.interval_progress = 99;
    random_state = 0x010101;
    assert(bonus_toss_select_item(&selector, 1, &selection) == 0);
    assert(selection.kind == 3 && !selection.reset_timer);
    selector.interval_progress = 0;

    unsigned int hazards = 0, rewards = 0, fallback = 0;
    for (uint32_t seed = 1; seed < 65536; ++seed) {
        uint32_t expected = seed;
        unsigned int chance = engine_random_byte(&expected);
        unsigned int roll = engine_random_byte(&expected);
        selector.speed = 2;
        selector.progress = 0;
        selector.lives = 3;
        selector.continues = 1;
        selector.reward_count = 0;
        selector.next_hazard = 1;
        random_state = seed;
        assert(bonus_toss_select_item(&selector, 0, &selection) == 0);
        assert(selection.kind == 7 + (roll & 3) && random_state == expected);
        assert(selector.next_hazard == (chance < 128));
        hazards |= 1U << (selection.kind - 7);

        selector.next_hazard = 1;
        random_state = seed;
        if ((roll & 3) == 3) {
            unsigned int reroll = engine_random_byte(&expected);
            assert(bonus_toss_select_item(&selector, 1, &selection) == 0);
            assert(selection.kind == 3 + (reroll & 1) && random_state == expected);
            fallback |= 1U << (selection.kind - 3);
        } else {
            assert(bonus_toss_select_item(&selector, 1, &selection) == 0);
            assert(selection.kind == 3 + (roll & 3) && random_state == expected);
            rewards |= 1U << (selection.kind - 3);
        }
    }
    assert(hazards == 15 && rewards == 7 && fallback == 3);

    for (unsigned int level = 1; level <= 10; ++level) {
        for (uint32_t seed = 1; seed < 65536; ++seed) {
            uint32_t expected = seed;
            engine_random_byte(&expected);
            unsigned int roll = engine_random_byte(&expected);
            if ((roll & 3) != 2) continue;
            unsigned int reroll = engine_random_byte(&expected);
            selector.level = (unsigned char)level;
            selector.reward_count = limits[level - 1] - 1;
            selector.next_hazard = 0;
            random_state = seed;
            assert(bonus_toss_select_item(&selector, 1, &selection) == 0 &&
                selection.kind == 5 && selection.timer == -50);
            selector.reward_count = limits[level - 1];
            selector.next_hazard = 0;
            random_state = seed;
            assert(bonus_toss_select_item(&selector, 1, &selection) == 0 &&
                selection.kind == 3 + (reroll & 1) && random_state == expected);
            break;
        }
    }

    for (uint32_t seed = 1; seed < 65536; ++seed) {
        uint32_t expected = seed;
        engine_random_byte(&expected);
        unsigned int roll = engine_random_byte(&expected);
        if ((roll & 3) != 1) continue;
        unsigned int bug = engine_random_byte(&expected) & 1;
        if ((engine_random_byte(&expected) & 7) == 0) bug = 2;
        selector.reward_count = 0;
        selector.continues = 9;
        selector.next_hazard = 0;
        random_state = seed;
        assert(bonus_toss_select_item(&selector, 1, &selection) == 0 &&
            selection.kind == bug && !selection.reset_timer && random_state == expected);
        break;
    }
    selector.level = 1;
    selector.reward_count = 24;
    selector.lives = 3;
    selector.continues = 1;
    selector.next_hazard = 0;
    random_state = 0x010101;
    assert(bonus_toss_select_item(&selector, 1, &selection) == 0 && selection.kind == 3);
    selector.level = 0;
    assert(bonus_toss_select_item(&selector, 1, &selection) == -1);
    assert(bonus_toss_spawn_interval(&selector, &interval) == -1);
    selector.level = 1;
    assert(bonus_toss_select_item(&selector, 2, &selection) == -1);
    assert(bonus_toss_spawn_interval(&selector, 0) == -1);
}

static void check_stage(void)
{
    RENDER_POOL stage_pool;
    BONUS_TOSS_STAGE stage;
    unsigned char lives = 3;
    unsigned int continues = 1;
    unsigned short max_roar = 16;
    uint32_t seed = 0x010101;
    assert(bonus_toss_stage_initialize(&stage, &stage_pool, seed,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    assert(stage.timon.x == 160 && stage.timon.y == 48 &&
        stage.spawn_counter == -120 && stage.selector.speed == 15);
    assert(stage.move_delay >= 13);
    for (unsigned int tick = 0; tick < 119; ++tick)
        assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.spawned == 0 && stage.selector.progress == 0);
    for (unsigned int tick = 0; !stage.spawned && tick < 100; ++tick)
        assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.spawned == 1 && stage.items[0].owner.x == stage.timon.x &&
        stage.items[0].owner.y >= 48 && stage.items[0].owner.y <= 49);
    assert(bonus_toss_stage_release(&stage) == 0);

    assert(bonus_toss_stage_initialize(&stage, &stage_pool, seed,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    stage.timon.x = 256;
    stage.direction_left = 0;
    stage.move_ticks = 1;
    stage.spawn_counter = -120;
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.direction_left && stage.timon.x == 256 && stage.move_delay == 13);
    for (unsigned int tick = 0; tick < 13; ++tick) {
        assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
        assert(stage.timon.x == 256);
    }
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0 && stage.timon.x == 251);
    stage.special_timer = 1;
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.special_ticks == 45 && stage.special_timer >= 1500 &&
        stage.special_timer <= 1755);
    for (unsigned int tick = 0; tick < 15; ++tick)
        assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.special_ticks == 30 && stage.spawned == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.spawned == 1 && stage.items[0].owner.x == stage.timon.x &&
        stage.items[0].owner.y >= 64 && stage.items[0].owner.y <= 65);
    for (unsigned int tick = 0; tick < 29; ++tick)
        assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.special_ticks == 0 && stage.special_active);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(!stage.special_active && stage.timon_animation.script.position != 0);
    assert(bonus_toss_stage_release(&stage) == 0);

    max_roar = 32;
    assert(bonus_toss_stage_initialize(&stage, &stage_pool, seed,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    assert(stage.selector.reward_count == 32);
    assert(bonus_toss_item_initialize(&stage.items[0], &stage_pool,
        (RENDER_OWNER){100, 214}, 5, &stage.random) == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(max_roar == 40 && stage.selector.reward_count == 40);
    assert(bonus_toss_stage_release(&stage) == 0);
    max_roar = 16;

    assert(bonus_toss_stage_initialize(&stage, &stage_pool, seed,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    stage.selector.interval_progress = 20;
    stage.spawn_counter = 100;
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.spawned == 1 && stage.selector.speed == 14 &&
        stage.selector.interval_progress == 0 && stage.spawn_counter == -120);
    assert(bonus_toss_stage_release(&stage) == 0);

    assert(bonus_toss_stage_initialize(&stage, &stage_pool, seed,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    assert(bonus_toss_item_initialize(&stage.items[0], &stage_pool,
        (RENDER_OWNER){200, 208}, 2, &stage.random) == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0 &&
        stage.items[0].active && stage.result == BONUS_TOSS_STAGE_RUNNING);
    stage.items[0].owner.y = 209;
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0 &&
        !stage.items[0].active && stage.result == BONUS_TOSS_STAGE_LOST);
    assert(bonus_toss_stage_release(&stage) == 0);

    assert(bonus_toss_stage_initialize(&stage, &stage_pool, seed,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    assert(bonus_toss_item_initialize(&stage.items[0], &stage_pool,
        (RENDER_OWNER){200, 209}, 7, &stage.random) == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0 &&
        !stage.items[0].active && stage.result == BONUS_TOSS_STAGE_RUNNING);
    assert(bonus_toss_stage_release(&stage) == 0);

    lives = 3;
    continues = 1;
    seed = 0x010101;
    assert(bonus_toss_stage_initialize(&stage, &stage_pool, seed,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    const unsigned char rewards[] = {3, 4, 5};
    for (unsigned int i = 0; i < sizeof(rewards); ++i) {
        assert(bonus_toss_item_initialize(&stage.items[0], &stage_pool,
            (RENDER_OWNER){100, 214}, rewards[i], &stage.random) == 0);
        assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
        assert(stage.caught == i + 1);
        if (rewards[i] == 3) assert(lives == 4);
        if (rewards[i] == 4) assert(continues == 2);
        if (rewards[i] == 5) assert(stage.score == 8 && max_roar == 24 &&
            stage.selector.reward_count == 24);
    }
    assert(bonus_toss_stage_release(&stage) == 0);

    lives = 3;
    continues = 1;
    assert(bonus_toss_stage_initialize(&stage, &stage_pool, 0x010101,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    assert(bonus_toss_item_initialize(&stage.items[0], &stage_pool,
        (RENDER_OWNER){100, 214}, 7, &stage.random) == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0 &&
        stage.result == BONUS_TOSS_STAGE_LOST);
    assert(bonus_toss_stage_release(&stage) == 0);

    assert(bonus_toss_stage_initialize(&stage, &stage_pool, 0x010101,
        &lives, &continues, &max_roar, burp, 0, flat_ground, 0) == 0);
    stage.selector.progress = 109;
    assert(bonus_toss_item_initialize(&stage.items[0], &stage_pool,
        (RENDER_OWNER){100, 214}, 0, &stage.random) == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0 &&
        stage.result == BONUS_TOSS_STAGE_WON);
    assert(bonus_toss_stage_release(&stage) == 0);
}

static void check_timon_turns(void)
{
    RENDER_POOL pool;
    BONUS_TOSS_STAGE stage;
    unsigned char lives = 3;
    unsigned int continues = 1;
    unsigned short roar = 16;
    assert(bonus_toss_stage_initialize(&stage, &pool, 0x010101,
        &lives, &continues, &roar, burp, 0, flat_ground, 0) == 0);

    uint32_t seed = 1;
    for (;; ++seed) {
        uint32_t state = seed;
        engine_random_byte(&state);
        engine_random_byte(&state);
        if ((engine_random_byte(&state) & 3) == 0) break;
    }
    stage.random = seed;
    stage.timon.x = 160;
    stage.direction_left = 0;
    stage.timon_node->pass_flags &= (unsigned char)~8U;
    stage.move_ticks = 0;
    stage.spawn_counter = -120;
    RENDER_OWNER owner = stage.timon;
    RENDER_NODE reference_node = *stage.timon_node;
    reference_node.owner = &owner;
    ANIMATION_PROGRAM reference;
    assert(animation_program_initialize(&reference, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x4b89,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
    assert(animation_program_step(&reference, &reference_node, &owner, 0, 0) == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.direction_left && (stage.timon_node->pass_flags & 8) &&
        stage.timon.x == 160 && stage.move_ticks >= 28 && stage.move_delay == 14);
    assert(stage.timon_node->parts == reference_node.parts &&
        stage.timon_animation.visual.position == reference.visual.position &&
        stage.timon_animation.visual.remaining == reference.visual.remaining);

    stage.timon.x = 256;
    stage.direction_left = 0;
    stage.timon_node->pass_flags &= (unsigned char)~8U;
    stage.move_ticks = 1;
    stage.spawn_counter = -120;
    owner = stage.timon;
    reference_node = *stage.timon_node;
    reference_node.owner = &owner;
    reference_node.pass_flags |= 8;
    assert(animation_program_initialize(&reference, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x4b89,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
    assert(animation_program_step(&reference, &reference_node, &owner, 0, 0) == 0);
    assert(animation_program_step(&reference, &reference_node, &owner, 0, 0) == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.direction_left && (stage.timon_node->pass_flags & 8) &&
        stage.timon.x == 256 && stage.move_delay == 13);
    assert(stage.timon_node->parts == reference_node.parts &&
        stage.timon_animation.visual.position == reference.visual.position &&
        stage.timon_animation.visual.remaining == reference.visual.remaining);
    assert(bonus_toss_stage_release(&stage) == 0);
}

static void check_timon_phase_and_spawn_timing(void)
{
    RENDER_POOL stage_pool;
    BONUS_TOSS_STAGE stage;
    unsigned char lives = 3;
    unsigned int continues = 1;
    unsigned short roar = 16;
    assert(bonus_toss_stage_initialize(&stage, &stage_pool, 0x010101,
        &lives, &continues, &roar, burp, 0, flat_ground, 0) == 0);

    uint32_t seed = 1;
    for (;; ++seed) {
        uint32_t state = seed;
        engine_random_byte(&state);
        engine_random_byte(&state);
        if ((engine_random_byte(&state) & 3) != 0) break;
    }
    stage.random = seed;
    stage.timon.x = 160;
    stage.direction_left = 0;
    stage.move_ticks = 0;
    stage.move_delay = 0;
    stage.spawn_counter = 34;
    stage.timon_vertical_speed = 0x20000;
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.timon.x == 160 && stage.move_delay == 0 &&
        stage.spawn_counter == 34 && stage.timon_vertical_speed == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.timon.x == 165 && stage.spawn_counter == 35 && stage.spawned == 0);
    assert(bonus_toss_stage_tick(&stage, 0, 0, 0) == 0);
    assert(stage.timon.x == 170 && stage.spawn_counter == 0 && stage.spawned == 1);
    assert(stage.items[0].owner.x == 170);
    assert(bonus_toss_stage_release(&stage) == 0);
}

static void check_result_clock(void)
{
    static const unsigned int counts[] = {0, 1, 20, 21, 99, 110};
    for (unsigned int i = 0; i < sizeof(counts) / sizeof(*counts); ++i) {
        BONUS_TOSS_RESULT_CLOCK clock;
        assert(bonus_toss_result_initialize(&clock, counts[i]) == 0);
        unsigned int target = counts[i] > 99 ? 99 : counts[i];
        unsigned int ticks = 0, sounds = 0;
        while (clock.timer >= 0) {
            int sound = bonus_toss_result_tick(&clock);
            assert(sound >= 0);
            sounds += (unsigned int)sound;
            ++ticks;
        }
        assert(clock.displayed == target);
        assert(ticks == 171 + (target ? target - 1 : 0));
        assert(sounds == (target > 20 ? target : 0));
    }
    assert(bonus_toss_result_initialize(0, 0) == -1);
    assert(bonus_toss_result_tick(0) == -1);
}

int main(void)
{
    check_timon_gravity();
    check_original_fall_trajectories();
    check_selector();
    check_stage();
    check_timon_turns();
    check_timon_phase_and_spawn_timing();
    check_result_clock();
    static const unsigned int definitions[] = {
        0xb130, 0xb144, 0xb158, 0xb89c, 0xb284, 0xb0cc,
        0xb220, 0xb0f4, 0xb0f4, 0xb108, 0xb11c
    };
    for (unsigned int kind = 0; kind < 11; ++kind) {
        reset();
        assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){200, 48},
            (unsigned char)kind, &random_state) == 0);
        unsigned int address = kind <= 1 ? 0xb144 : definitions[kind];
        assert(item.node->parts == animation_movement_data + address - ANIMATION_MOVEMENT_BASE);
        assert(item.owner.x == 200 && item.owner.y == 48 && item.active);
        assert(item.motion.velocity_y == (kind == 1 ? 0x3800U : kind == 2 ? 0x1000U : 0xb000U));
        assert(item.acceleration == (kind == 1 ? 0x1c00U : kind == 2 ? 0x600U : 0x1e00U));
        assert((item.node->flags & 1) == (kind == 3));
        assert(random_state == (kind <= 1 ? 0x800202U : 0x010101U));
        assert(bonus_toss_item_release(&item, &pool) == 0);
    }

    reset();
    assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){200, 48}, 0, &random_state) == 0);
    for (unsigned int tick = 1; tick <= 100; ++tick) {
        assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == 0);
        assert(result == BONUS_TOSS_ITEM_FALLING);
        unsigned int expected_velocity = 0xb000U + 0x1e00U * tick;
        if (expected_velocity > 0x70000U) expected_velocity = 0x70000U;
        assert(item.motion.velocity_y == expected_velocity);
    }
    assert(item.motion.velocity_y == 0x70000U);
    assert(bonus_toss_item_release(&item, &pool) == 0);

    reset();
    assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){200, 48}, 1, &random_state) == 0);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == 0 &&
        item.owner.y == 48 && item.motion.fraction_y == 0x5400);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == 0 &&
        item.owner.y == 48 && item.motion.fraction_y == 0xc400);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == 0 &&
        item.owner.y == 49 && item.motion.fraction_y == 0x5000);
    assert(bonus_toss_item_release(&item, &pool) == 0);

    reset();
    assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){0, 214}, 2, &random_state) == 0);
    RENDER_BOUNDS p, b;
    assert(render_object_bounds(player.node, &p) == 0);
    assert(render_object_bounds(item.node, &b) == 0);
    item.owner.x = (short)(p.right - b.left + 1);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == 0 &&
        result == BONUS_TOSS_ITEM_FALLING);
    --item.owner.x;
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == 0 &&
        result == BONUS_TOSS_ITEM_CAUGHT);

    reset();
    assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){100, 214}, 1, &random_state) == 0);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 0, 1, &result) == 0 &&
        result == BONUS_TOSS_ITEM_FALLING && item.owner.y == 214 && item.active);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 1, &result) == 0 &&
        result == BONUS_TOSS_ITEM_CAUGHT && !item.active && !item.node);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == -1);

    reset();
    assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){200, 48}, 5, &random_state) == 0);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 1, &result) == 0 &&
        result == BONUS_TOSS_ITEM_MISSED && item.owner.y == 48 && !item.active);

    reset();
    assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){200, 48}, 7, &random_state) == 0);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 2, 1, &result) == 0 &&
        result == BONUS_TOSS_ITEM_CLEARED && !item.active);

    reset();
    assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){200, 48}, 7, &random_state) == 0);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 0, &result) == 0 &&
        result == BONUS_TOSS_ITEM_FALLING && item.motion.velocity_y == 0xce00U);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 3, 0, &result) == -1);
    assert(bonus_toss_item_tick(&item, &pool, player.node, 1, 2, &result) == -1);
    assert(bonus_toss_item_release(&item, &pool) == 0);
    assert(bonus_toss_item_initialize(&item, &pool, (RENDER_OWNER){0, 0}, 11, &random_state) == -1);
    puts("PASS: original BUG TOSS item definitions, gravity, collision and stage signals");
    return 0;
}
