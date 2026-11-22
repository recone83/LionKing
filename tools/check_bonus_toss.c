#include <assert.h>
#include <stdio.h>
#include "engine/bonus_toss.h"
#include "engine/animation_data.h"
#include "engine/random.h"

static RENDER_POOL pool;
static BONUS_TOSS_PLAYER player;
static uint32_t random_state;
static int sounds;
static int sound_failure;

static int play_burp(void *context)
{
    assert(context == &sounds);
    ++sounds;
    return sound_failure ? -1 : 0;
}

static void reset(void)
{
    render_initialize_nodes(&pool);
    random_state = 0x010101;
    sounds = sound_failure = 0;
    assert(bonus_toss_player_initialize(&player, &pool, &random_state, play_burp, &sounds) == 0);
    assert(player.owner.x == 100 && player.owner.y == 214);
}

int main(void)
{
    static const unsigned char random_sequence[] = {0x82, 0x44, 0x28, 0x00, 0x28, 0x44, 0x02, 0xc0};
    uint32_t sequence_state = 0x010101;
    for (unsigned int i = 0; i < sizeof(random_sequence); ++i)
        assert(engine_random_byte(&sequence_state) == random_sequence[i]);
    assert(sequence_state == 0xc10101);
    reset();
    assert(bonus_toss_player_tick(&player, 0, 0, 0) == 0);
    assert(player.node->parts == animation_movement_data + 0xb324 - ANIMATION_MOVEMENT_BASE);
    assert(bonus_toss_player_tick(&player, 1, 0, 0) == 0);
    assert(player.owner.x == 94 && player.moving && player.direction_left);
    assert(player.node->pass_flags & 8);
    assert(player.node->parts == animation_movement_data + 0xb338 - ANIMATION_MOVEMENT_BASE);
    assert(bonus_toss_player_tick(&player, 0, 1, 0) == 0);
    assert(player.owner.x == 100 && !player.direction_left && player.turn_ticks == 9);
    assert(!(player.node->pass_flags & 8));
    assert(player.node->parts == animation_movement_data + 0xb43c - ANIMATION_MOVEMENT_BASE);
    for (int i = 0; i < 9; ++i) {
        assert(bonus_toss_player_tick(&player, 0, 1, 0) == 0);
        assert(player.owner.x == 100 && player.turn_ticks == 8 - i);
    }
    assert(bonus_toss_player_tick(&player, 0, 1, 0) == 0 && player.owner.x == 106);
    assert(bonus_toss_player_tick(&player, 0, 0, 0) == 0 && !player.moving);

    reset();
    for (int i = 0; i < 6; ++i) assert(bonus_toss_player_tick(&player, 1, 0, 0) == 0);
    assert(player.owner.x == 64);
    assert(bonus_toss_player_tick(&player, 1, 1, 1) == 0 && player.owner.x == 64 && !player.moving);
    assert(!player.action_used && !sounds);
    reset();
    for (int i = 0; i < 26; ++i) assert(bonus_toss_player_tick(&player, 0, 1, 0) == 0);
    assert(player.owner.x == 256);
    assert(bonus_toss_player_tick(&player, 1, 1, 1) == 0 && player.owner.x == 256 && !player.moving);
    assert(!player.action_used && !sounds);

    reset();
    assert(bonus_toss_player_tick(&player, 1, 1, 0) == 0);
    assert(player.owner.x == 100 && !player.direction_left && player.turn_ticks == 9);
    assert(bonus_toss_player_tick(&player, 2, 0, 0) == -1);
    assert(bonus_toss_player_tick(&player, 0, 0, 2) == -1);
    assert(render_release_node(&pool, player.node) == 0);
    assert(bonus_toss_player_tick(&player, 0, 0, 0) == -1);

    reset();
    assert(bonus_toss_player_tick(&player, 0, 0, 1) == 0);
    assert(sounds == 1 && player.action_used && player.action_active &&
        player.turn_ticks == 56 && player.stage_signal == 0);
    uint32_t expected_random = random_state;
    for (int remaining = 56; remaining > 0; --remaining) {
        unsigned int expected_shake = remaining > 14 && remaining < 46 ?
            engine_random_byte(&expected_random) & 1 : 0;
        assert(bonus_toss_player_tick(&player, 1, 0, 1) == 0);
        assert(player.owner.x == 100 && player.turn_ticks == remaining - 1);
        assert(player.stage_signal == 0 && player.shake == expected_shake &&
            random_state == expected_random);
        if (remaining == 56)
            assert(player.node->parts == animation_movement_data + 0xb4dc - ANIMATION_MOVEMENT_BASE);
    }
    assert(bonus_toss_player_tick(&player, 0, 0, 1) == 0 && player.stage_signal == 2);
    assert(bonus_toss_player_tick(&player, 0, 0, 1) == 0 &&
        player.stage_signal == 1 && !player.action_active && sounds == 1);
    assert(bonus_toss_player_tick(&player, 0, 0, 1) == 0 && sounds == 1 &&
        player.node->parts == animation_movement_data + 0xb324 - ANIMATION_MOVEMENT_BASE);
    assert(bonus_toss_player_tick(&player, 0, 1, 0) == 0 && player.owner.x == 106);

    reset();
    assert(bonus_toss_player_tick(&player, 1, 0, 0) == 0);
    assert(bonus_toss_player_tick(&player, 0, 1, 1) == 0);
    assert(player.owner.x == 100 && player.action_active && player.turn_ticks == 56 && sounds == 1);
    reset();
    assert(bonus_toss_player_tick(&player, 1, 0, 0) == 0);
    assert(bonus_toss_player_tick(&player, 0, 1, 0) == 0 && player.turn_ticks == 9);
    assert(bonus_toss_player_tick(&player, 0, 0, 1) == 0 && !player.action_used &&
        player.turn_ticks == 8 && !sounds);

    reset();
    sound_failure = 1;
    assert(bonus_toss_player_tick(&player, 0, 0, 1) == -1 && sounds == 1);
    puts("PASS: original BUG TOSS movement and one-use action state");
    return 0;
}
