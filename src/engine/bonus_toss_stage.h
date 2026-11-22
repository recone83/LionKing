#ifndef LIONKING_BONUS_TOSS_STAGE_H
#define LIONKING_BONUS_TOSS_STAGE_H

#include "bonus_toss_item.h"
#include "bonus_toss.h"

#define BONUS_TOSS_ITEM_CAPACITY 12U

typedef enum {
    BONUS_TOSS_STAGE_RUNNING,
    BONUS_TOSS_STAGE_WON,
    BONUS_TOSS_STAGE_LOST
} BONUS_TOSS_STAGE_RESULT;

typedef struct {
    int timer;
    unsigned int displayed;
    unsigned int target;
} BONUS_TOSS_RESULT_CLOCK;

int bonus_toss_result_initialize(BONUS_TOSS_RESULT_CLOCK *clock, unsigned int caught);
int bonus_toss_result_tick(BONUS_TOSS_RESULT_CLOCK *clock);

typedef struct {
    BONUS_TOSS_PLAYER player;
    RENDER_OWNER timon;
    RENDER_NODE *timon_node;
    ANIMATION_PROGRAM timon_animation;
    BONUS_TOSS_ITEM items[BONUS_TOSS_ITEM_CAPACITY];
    BONUS_TOSS_SELECTOR selector;
    RENDER_POOL *renders;
    uint32_t random;
    unsigned char *lives;
    unsigned int *continues;
    unsigned short *max_roar;
    unsigned int score;
    unsigned int caught;
    unsigned int spawned;
    unsigned int misses;
    short spawn_counter;
    unsigned short special_timer;
    unsigned short move_ticks;
    unsigned short special_ticks;
    unsigned char special_active;
    unsigned char move_delay;
    unsigned char direction_left;
    unsigned char active;
    unsigned char result;
} BONUS_TOSS_STAGE;

int bonus_toss_stage_initialize(BONUS_TOSS_STAGE *stage, RENDER_POOL *renders,
    uint32_t seed, unsigned char *lives, unsigned int *continues, unsigned short *max_roar,
    BONUS_TOSS_SOUND play_burp, void *sound_context);
int bonus_toss_stage_tick(BONUS_TOSS_STAGE *stage, int left, int right, int action);
int bonus_toss_stage_release(BONUS_TOSS_STAGE *stage);

#endif
