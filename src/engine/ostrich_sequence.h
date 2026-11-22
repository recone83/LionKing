#ifndef LIONKING_OSTRICH_SEQUENCE_H
#define LIONKING_OSTRICH_SEQUENCE_H

#include "ostrich_obstacle.h"

#define ENGINE_OSTRICH_HAZARD_CAPACITY 16U

typedef struct {
    ENGINE_OSTRICH_ROUTE route;
    ENGINE_OSTRICH_HAZARD hazards[ENGINE_OSTRICH_HAZARD_CAPACITY];
    unsigned char order[ENGINE_OSTRICH_HAZARD_CAPACITY];
    unsigned int count;
    ENGINE_OBJECT_POOL *objects;
    RENDER_POOL *renders;
    unsigned int ending;
} ENGINE_OSTRICH_SEQUENCE;

typedef struct {
    unsigned int route_status;
    unsigned int route_flags;
    unsigned int spawned;
    unsigned int culled;
    /* Owned by the sequence; valid only until the next tick or release. */
    const RENDER_OWNER *player_hit;
    unsigned int bird_hit;
} ENGINE_OSTRICH_SEQUENCE_RESULT;

/* sequence must be zero-initialized or previously released. */
int engine_ostrich_sequence_initialize(ENGINE_OSTRICH_SEQUENCE *sequence,
    ENGINE_OBJECT_POOL *objects, RENDER_POOL *renders, unsigned int marker_type);
int engine_ostrich_sequence_tick(ENGINE_OSTRICH_SEQUENCE *sequence,
    short distance, RENDER_OWNER camera, const RENDER_BOUNDS *activation_bounds,
    const RENDER_NODE *player, const RENDER_NODE *bird,
    ENGINE_OSTRICH_SEQUENCE_RESULT *result);
/* Apply the camera wrap once to each shared obstacle owner. */
int engine_ostrich_sequence_shift(ENGINE_OSTRICH_SEQUENCE *sequence, short shift);
int engine_ostrich_sequence_release(ENGINE_OSTRICH_SEQUENCE *sequence);

#endif
