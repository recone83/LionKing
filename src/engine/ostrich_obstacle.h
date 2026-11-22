#ifndef LIONKING_OSTRICH_OBSTACLE_H
#define LIONKING_OSTRICH_OBSTACLE_H

#include "animation.h"
#include "objects.h"
#include "ostrich_route.h"

typedef struct {
    RENDER_OWNER position;
    RENDER_POOL *renders;
    ENGINE_OBJECT_POOL *objects;
    RENDER_NODE *collision;
    RENDER_NODE *decoration;
    ENGINE_OBJECT *object;
    ANIMATION_PROGRAM animation;
    unsigned int constructor;
    unsigned char armed;
} ENGINE_OSTRICH_HAZARD;

enum {
    ENGINE_OSTRICH_HAZARD_CLEAR = 0,
    ENGINE_OSTRICH_HAZARD_PLAYER_HIT = 1,
    ENGINE_OSTRICH_HAZARD_BIRD_HIT = 2,
    ENGINE_OSTRICH_HAZARD_CULLED = 3
};

/* hazard must be zero-initialized or previously released. */
int engine_ostrich_hazard_create(ENGINE_OSTRICH_HAZARD *hazard,
    ENGINE_OBJECT_POOL *objects, RENDER_POOL *renders,
    const ENGINE_OSTRICH_OBSTACLE *descriptor);
int engine_ostrich_hazard_tick(ENGINE_OSTRICH_HAZARD *hazard,
    const RENDER_BOUNDS *activation_bounds, const RENDER_NODE *player,
    const RENDER_NODE *bird);
int engine_ostrich_hazard_release(ENGINE_OSTRICH_HAZARD *hazard);

#endif
