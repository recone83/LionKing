#ifndef LIONKING_BONUS_TOSS_ITEM_H
#define LIONKING_BONUS_TOSS_ITEM_H

#include "animation.h"
#include "physics.h"

typedef enum {
    BONUS_TOSS_ITEM_FALLING,
    BONUS_TOSS_ITEM_CAUGHT,
    BONUS_TOSS_ITEM_MISSED,
    BONUS_TOSS_ITEM_CLEARED
} BONUS_TOSS_ITEM_RESULT;

typedef struct {
    RENDER_OWNER owner;
    RENDER_NODE *node;
    ENGINE_MOTION motion;
    ANIMATION_PROGRAM animation;
    uint32_t acceleration;
    unsigned char kind;
    unsigned char active;
} BONUS_TOSS_ITEM;

typedef struct {
    uint32_t *random;
    unsigned short speed;
    unsigned short progress;
    unsigned short reward_count;
    unsigned char level;
    unsigned char lives;
    unsigned char continues;
    unsigned char next_hazard;
    unsigned short interval_progress;
} BONUS_TOSS_SELECTOR;

typedef struct {
    unsigned char kind;
    unsigned char reset_timer;
    short timer;
} BONUS_TOSS_SELECTION;

int bonus_toss_select_item(BONUS_TOSS_SELECTOR *selector, int force_reward,
    BONUS_TOSS_SELECTION *selection);
int bonus_toss_spawn_interval(const BONUS_TOSS_SELECTOR *selector, short *interval);
int bonus_toss_item_initialize(BONUS_TOSS_ITEM *item, RENDER_POOL *renders,
    RENDER_OWNER position, unsigned char kind, uint32_t *random);
int bonus_toss_item_tick(BONUS_TOSS_ITEM *item, RENDER_POOL *renders,
    const RENDER_NODE *player, unsigned char stage_signal, int floor_hit,
    BONUS_TOSS_ITEM_RESULT *result);
int bonus_toss_item_release(BONUS_TOSS_ITEM *item, RENDER_POOL *renders);

#endif
