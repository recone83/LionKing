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

#define ENGINE_EMITTER_GROUP_COUNT 4U
#define ENGINE_EMITTER_GROUP_SLOTS 4U

typedef struct {
    unsigned short trigger;
    ENGINE_EMITTER_OBJECT emitters[ENGINE_EMITTER_GROUP_COUNT];
    ENGINE_EMITTER_SLOT slots[ENGINE_EMITTER_GROUP_COUNT][ENGINE_EMITTER_GROUP_SLOTS];
    ENGINE_OBJECT *objects[ENGINE_EMITTER_GROUP_COUNT];
} ENGINE_EMITTER_GROUP;

typedef int (*ENGINE_PLAYER_IMPACT)(void *context);

/* Original base-zero handler and DS script addresses, not native pointers. */
typedef struct {
    unsigned int handler;
    unsigned int script;
    unsigned short counter;
} ENGINE_PLAYER_CALL;

int engine_player_reaction_e667(unsigned short form, uint32_t script_position,
    ENGINE_PLAYER_CALL *call);
int engine_player_reaction_e6ee(unsigned short form, uint32_t script_position,
    ENGINE_PLAYER_CALL *call);
int engine_player_reaction_e36e(short contact, unsigned short form,
    uint32_t script_position, ENGINE_PLAYER_CALL *call);
int engine_player_reaction_e3bf(short contact, unsigned short form,
    uint32_t script_position, ENGINE_PLAYER_CALL *call);

typedef int (*ENGINE_PLAYER_PROBE)(void *context, short x, short y, short *hit);
typedef int (*ENGINE_PLAYER_TRANSITION)(void *context, const ENGINE_PLAYER_CALL *call);

typedef struct {
    ENGINE_FALLING_OBJECT body;
    unsigned int handler;
    unsigned short form;
    unsigned short immunity;
    unsigned char flags_high;
    unsigned char controls;
    unsigned char age;
    unsigned char *collision_flags;
    ENGINE_PLAYER_PROBE probe;
    ENGINE_PLAYER_TRANSITION transition;
    void *context;
} ENGINE_PLAYER_DEFLECTION;

extern const ENGINE_OBJECT_BEHAVIOR engine_player_deflection_behavior;
int engine_player_begin_deflection(ENGINE_OBJECT *object,
    ENGINE_PLAYER_DEFLECTION *state, const ENGINE_PLAYER_CALL *call);

typedef int (*ENGINE_PLAYER_GROUND)(void *context, short *kind, short *delta_y);
typedef int (*ENGINE_PLAYER_EDGE)(void *context, short *hit, short *kind,
    short *x, short *y);
typedef int (*ENGINE_PLAYER_AIR_TRANSITION)(void *context,
    const ENGINE_PLAYER_CALL *call, short kind, short x, short y);
typedef int (*ENGINE_PLAYER_SOUND)(void *context, unsigned short sample);
typedef int (*ENGINE_PLAYER_SUPPORT)(void *context, short *supported);

typedef struct {
    ENGINE_PLAYER_DEFLECTION player;
    unsigned short flags;
    unsigned short player_flags;
    unsigned short pressed;
    short anchor_x;
    short anchor_y;
    unsigned char contact_kind;
    unsigned char landing_flags;
    unsigned char surface_kind;
    unsigned char jump_boost;
    unsigned int jump_air_script;
    unsigned char auxiliary_controls;
    unsigned char boundary_controls;
    unsigned short action_timer;
    short progress;
    short progress_limit;
    ENGINE_PLAYER_GROUND ground;
    ENGINE_PLAYER_SUPPORT support;
    ENGINE_PLAYER_EDGE edge;
    ENGINE_PLAYER_AIR_TRANSITION transition;
    ENGINE_PLAYER_SOUND sound;
    ANIMATION_EVENT animation_event;
} ENGINE_PLAYER_AIR;

extern const ENGINE_OBJECT_BEHAVIOR engine_player_air_behavior;
int engine_player_begin_air(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, const ENGINE_PLAYER_CALL *call);
int engine_player_land(ENGINE_PLAYER_AIR *state, unsigned int handler,
    short duration);
extern const ENGINE_OBJECT_BEHAVIOR engine_player_jump_behavior;
extern const ENGINE_OBJECT_BEHAVIOR engine_player_recovery_behavior;
int engine_player_begin_jump(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, const ENGINE_PLAYER_CALL *call, unsigned int air_script);
int engine_player_begin_recovery(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, const ENGINE_PLAYER_CALL *call);
extern const ENGINE_OBJECT_BEHAVIOR engine_player_ground_behavior;
int engine_player_begin_ground(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, const ENGINE_PLAYER_CALL *call);

typedef struct {
    ENGINE_FALLING_OBJECT body;
    unsigned short *camera_shake;
    const unsigned short *immunity;
    const ENGINE_MOTION *player_motion;
    ENGINE_PLAYER_IMPACT impact;
    void *impact_context;
} ENGINE_SHAKE_OBJECT;

extern const ENGINE_OBJECT_BEHAVIOR engine_falling_behavior;
extern const ENGINE_OBJECT_BEHAVIOR engine_timed_behavior;
extern const ENGINE_OBJECT_BEHAVIOR engine_emitter_behavior;
extern const ENGINE_OBJECT_BEHAVIOR engine_shake_behavior;
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
int engine_setup_emitter_group(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_EMITTER_GROUP *group, const RENDER_OWNER *camera,
    const RENDER_BOUNDS *visibility, short order, short parent_order, short child_order);
int engine_spawn_shake(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_SHAKE_OBJECT *state, short impact_marker, unsigned short *camera_shake,
    const unsigned short *immunity, const ENGINE_MOTION *player_motion,
    unsigned short *player_flags, ENGINE_PLAYER_IMPACT impact, void *impact_context,
    short order, ENGINE_OBJECT **created);

#endif
