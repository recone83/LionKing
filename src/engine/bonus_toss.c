#include "bonus_toss.h"
#include "animation_data.h"
#include "random.h"

static int toss_animation(BONUS_TOSS_PLAYER *player, unsigned int entry)
{
    return animation_program_initialize(&player->animation, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, entry, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE);
}

int bonus_toss_player_initialize(BONUS_TOSS_PLAYER *player, RENDER_POOL *renders,
    uint32_t *random, BONUS_TOSS_SOUND play_burp, void *sound_context)
{
    if (!player || !renders || !random || !play_burp) return -1;
    *player = (BONUS_TOSS_PLAYER){0};
    player->random = random;
    player->play_burp = play_burp;
    player->sound_context = sound_context;
    player->stage_signal = 1;
    player->owner = (RENDER_OWNER){100, 214};
    player->node = render_acquire_node(renders, &player->owner, 0, 0,
        animation_falling_data + 0x16062 - ANIMATION_FALLING_BASE, 14);
    if (!player->node) return -1;
    player->node->flags |= 0x40;
    if (toss_animation(player, 0x4c86) != 0) {
        if (render_release_node(renders, player->node) != 0) return -1;
        player->node = 0;
        return -1;
    }
    return 0;
}

static int toss_move(BONUS_TOSS_PLAYER *player, int left)
{
    player->owner.x = (short)(player->owner.x + (left ? -6 : 6));
    if (!player->moving) {
        if (toss_animation(player, 0x4c94) != 0) return -1;
        player->moving = 1;
        player->direction_left = (unsigned char)left;
    } else if (player->direction_left != left) {
        if (toss_animation(player, 0x4ca2) != 0) return -1;
        player->direction_left = (unsigned char)left;
        player->turn_ticks = 9;
    }
    if (left) player->node->pass_flags |= 8;
    else player->node->pass_flags &= (unsigned char)~8U;
    return 0;
}

int bonus_toss_player_tick(BONUS_TOSS_PLAYER *player, int left, int right, int action)
{
    if (!player || !player->node || !player->node->active ||
        player->node->owner != &player->owner ||
        !player->random || !player->play_burp || (left != 0 && left != 1) ||
        (right != 0 && right != 1) || (action != 0 && action != 1)) return -1;
    if (player->action_active) {
        if (animation_program_step(&player->animation, player->node, &player->owner, 0, 0) != 0)
            return -1;
        if (player->turn_ticks > 14 && player->turn_ticks < 46)
            player->shake = (unsigned char)(engine_random_byte(player->random) & 1);
        if (player->turn_ticks) {
            --player->turn_ticks;
        } else if (!player->stage_signal) {
            player->stage_signal = 2;
        } else {
            player->shake = 0;
            player->stage_signal = 1;
            player->action_active = 0;
            player->direction_left = 0;
            if (toss_animation(player, 0x4c86) != 0) return -1;
        }
        return 0;
    }
    if (player->turn_ticks) {
        --player->turn_ticks;
    } else {
        if ((left && player->owner.x < 70) || (right && player->owner.x > 250))
            left = right = action = 0;
        if (left && player->owner.x > 64 && toss_move(player, 1) != 0) return -1;
        if (right && player->owner.x < 256 && toss_move(player, 0) != 0) return -1;
        if (!left && !right && player->moving) {
            if (toss_animation(player, 0x4cb0) != 0) return -1;
            player->moving = 0;
        }
        if (action && !player->action_used) {
            if (toss_animation(player, 0x4c6a) != 0 || player->play_burp(player->sound_context) != 0)
                return -1;
            player->action_used = 1;
            player->action_active = 1;
            player->stage_signal = 0;
            player->turn_ticks = 56;
            return 0;
        }
    }
    return animation_program_step(&player->animation, player->node, &player->owner, 0, 0);
}
