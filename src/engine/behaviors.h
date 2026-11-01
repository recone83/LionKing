#ifndef LIONKING_BEHAVIORS_H
#define LIONKING_BEHAVIORS_H

#include "objects.h"
#include "physics.h"
#include "animation.h"

typedef int (*ENGINE_SPATIAL_UNLINK)(void *context, unsigned short type,
    short x, short y);

typedef struct {
    RENDER_OWNER owner;
    ENGINE_MOTION motion;
    ANIMATION_PROGRAM animation;
    RENDER_POOL *render_pool;
    RENDER_NODE *node;
    const RENDER_BOUNDS *visibility;
    RENDER_OWNER origin;
    RENDER_BOUNDS fixed_bounds;
    unsigned char flags;
    unsigned short spatial_type;
    int initialized;
    ENGINE_SPATIAL_UNLINK unlink_spatial;
    void *spatial_context;
} ENGINE_FALLING_OBJECT;

extern const ENGINE_OBJECT_BEHAVIOR engine_falling_behavior;
/* 0: created, 1: culled by original initialization, -1: error. */
int engine_spawn_falling(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_FALLING_OBJECT *state, RENDER_OWNER position,
    const RENDER_BOUNDS *visibility, short order, ENGINE_OBJECT **created);

#endif
