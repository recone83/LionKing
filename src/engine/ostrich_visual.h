#ifndef LIONKING_OSTRICH_VISUAL_H
#define LIONKING_OSTRICH_VISUAL_H

#include "animation.h"
#include "objects.h"

typedef enum {
    ENGINE_OSTRICH_WAITING,
    ENGINE_OSTRICH_MOUNTING,
    ENGINE_OSTRICH_RUNNING,
    ENGINE_OSTRICH_CROUCHING,
    ENGINE_OSTRICH_JUMPING
} ENGINE_OSTRICH_POSE;

typedef struct {
    RENDER_OWNER position;
    RENDER_POOL *renders;
    ENGINE_OBJECT_POOL *objects;
    RENDER_NODE *body;
    RENDER_NODE *head;
    ENGINE_OBJECT *body_object;
    ENGINE_OBJECT *head_object;
    ANIMATION_PROGRAM body_animation;
    ANIMATION_PROGRAM head_animation;
    ENGINE_OSTRICH_POSE pose;
} ENGINE_OSTRICH_VISUAL;

/* visual must be zero-initialized or previously released. */
int engine_ostrich_visual_create(ENGINE_OSTRICH_VISUAL *visual,
    ENGINE_OBJECT_POOL *objects, RENDER_POOL *renders, RENDER_OWNER position,
    short order);
int engine_ostrich_visual_set_pose(ENGINE_OSTRICH_VISUAL *visual,
    ENGINE_OSTRICH_POSE pose);
int engine_ostrich_visual_tick(ENGINE_OSTRICH_VISUAL *visual);
int engine_ostrich_visual_attachment(const ENGINE_OSTRICH_VISUAL *visual,
    RENDER_OWNER *attachment);
int engine_ostrich_visual_release(ENGINE_OSTRICH_VISUAL *visual);

#endif
