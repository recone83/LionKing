#ifndef LIONKING_OSTRICH_RIDE_H
#define LIONKING_OSTRICH_RIDE_H

#include "enemies.h"
#include "ostrich_sequence.h"

typedef struct {
    RENDER_OWNER position;
    RENDER_NODE *node;
    ENGINE_OBJECT *object;
    ANIMATION_PROGRAM animation;
    unsigned short timer;
    unsigned char phase;
} ENGINE_OSTRICH_HINT;

typedef struct {
    ENGINE_OSTRICH_SEQUENCE sequence;
    RENDER_OSTRICH_SCROLL scroll;
    ENGINE_MOTION motion;
    ENGINE_LIZARD *marker;
    ENGINE_OSTRICH_VISUAL *visual;
    RENDER_OWNER damage_source;
    ENGINE_OSTRICH_HINT hints[2];
    int active;
    int mounting;
    int bird_hit;
} ENGINE_OSTRICH_RIDE;

int engine_ostrich_ride_find_and_start(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_ENEMIES *enemies, RENDER_FOLLOW_CAMERA *camera);
int engine_ostrich_ride_update(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_ENEMIES *enemies);
int engine_ostrich_ride_camera(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_ENEMIES *enemies, RENDER_FOLLOW_CAMERA *camera);
int engine_ostrich_ride_release(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_PLAYER_AIR *player);

#endif
