#ifndef LIONKING_ANIMATION_H
#define LIONKING_ANIMATION_H

#include "render.h"

typedef struct {
    const unsigned char *data;
    unsigned int size;
    unsigned int base;
    unsigned int position;
    unsigned char remaining;
    unsigned short state;
} ANIMATION_STREAM;

typedef int (*ANIMATION_EVENT)(void *context, unsigned int original_target);

int animation_initialize(ANIMATION_STREAM *stream, const unsigned char *data,
    unsigned int size, unsigned int base, unsigned int position);
int animation_step(ANIMATION_STREAM *stream, RENDER_NODE *node,
    RENDER_OWNER *owner, ANIMATION_EVENT event, void *context);
int animation_motion_step(ANIMATION_STREAM *stream, const RENDER_NODE *node,
    RENDER_OWNER *owner);

#endif
