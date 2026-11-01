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

typedef struct {
    ENGINE_FALLING_OBJECT body;
    ENGINE_FALLING_OBJECT *child;
    short child_order;
} ENGINE_TIMED_OBJECT;

typedef struct {
    ENGINE_TIMED_OBJECT parent;
    ENGINE_FALLING_OBJECT child;
} ENGINE_EMITTER_SLOT;

typedef struct {
    ENGINE_FALLING_OBJECT body;
    const unsigned short *trigger;
    const RENDER_OWNER *camera;
    ENGINE_EMITTER_SLOT *slots;
    unsigned int slot_count;
    short parent_order;
    short child_order;
} ENGINE_EMITTER_OBJECT;

extern const ENGINE_OBJECT_BEHAVIOR engine_falling_behavior;
extern const ENGINE_OBJECT_BEHAVIOR engine_timed_behavior;
extern const ENGINE_OBJECT_BEHAVIOR engine_emitter_behavior;
/* 0: created, 1: culled by original initialization, -1: error. */
int engine_spawn_falling(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_FALLING_OBJECT *state, RENDER_OWNER position,
    const RENDER_BOUNDS *visibility, short order, ENGINE_OBJECT **created);
int engine_spawn_timed(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_TIMED_OBJECT *state, ENGINE_FALLING_OBJECT *child, RENDER_OWNER position,
    const RENDER_BOUNDS *visibility, short order, short child_order,
    ENGINE_OBJECT **created);
int engine_spawn_emitter(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_EMITTER_OBJECT *state, RENDER_OWNER position, unsigned short counter,
    unsigned int variant, const unsigned short *trigger, const RENDER_OWNER *camera,
    const RENDER_BOUNDS *visibility, ENGINE_EMITTER_SLOT *slots, unsigned int slot_count,
    short order, short parent_order, short child_order, ENGINE_OBJECT **created);

#endif
