#ifndef LIONKING_BONUS_TOSS_H
#define LIONKING_BONUS_TOSS_H

#include "animation.h"
#include <stdint.h>

typedef int (*BONUS_TOSS_SOUND)(void *context);

typedef struct {
    RENDER_OWNER owner;
    RENDER_NODE *node;
    ANIMATION_PROGRAM animation;
    unsigned short turn_ticks;
    unsigned char moving;
    unsigned char direction_left;
    unsigned char action_used;
    unsigned char action_active;
    unsigned char stage_signal;
    unsigned char shake;
    uint32_t *random;
    BONUS_TOSS_SOUND play_burp;
    void *sound_context;
} BONUS_TOSS_PLAYER;

int bonus_toss_player_initialize(BONUS_TOSS_PLAYER *player, RENDER_POOL *renders,
    uint32_t *random, BONUS_TOSS_SOUND play_burp, void *sound_context);
int bonus_toss_player_tick(BONUS_TOSS_PLAYER *player, int left, int right, int action);

#endif
