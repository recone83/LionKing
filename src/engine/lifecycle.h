#ifndef LIONKING_LIFECYCLE_H
#define LIONKING_LIFECYCLE_H

#include "behaviors.h"

enum {
    ENGINE_LIFE_PLAYING,
    ENGINE_LIFE_DYING,
    ENGINE_LIFE_RESTART,
    ENGINE_LIFE_GAME_OVER,
    ENGINE_LIFE_COMPLETE
};

typedef struct {
    ENGINE_PLAYER_AIR *player;
    ENGINE_OBJECT *object;
    unsigned int deaths;
    unsigned int restarts;
    unsigned short remaining;
    unsigned char lives;
    unsigned char dying;
    unsigned char falling;
    unsigned char game_over;
    unsigned char complete;
} ENGINE_LEVEL_LIFE;

int engine_level_life_initialize(ENGINE_LEVEL_LIFE *life, ENGINE_PLAYER_AIR *player,
    ENGINE_OBJECT *object, unsigned char lives);
int engine_level_life_tick(ENGINE_LEVEL_LIFE *life, RENDER_OWNER camera);
int engine_level_life_fall(ENGINE_LEVEL_LIFE *life, const ENGINE_PLAYER_CALL *call);
int engine_level_life_complete(ENGINE_LEVEL_LIFE *life, unsigned int defeated);

#endif
