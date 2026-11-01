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

typedef struct {
    ANIMATION_STREAM script;
    ANIMATION_STREAM visual;
    ANIMATION_STREAM motion;
    int visual_ready;
    int motion_ready;
    unsigned short counter;
    unsigned short state;
    unsigned int unsupported_handler;
} ANIMATION_PROGRAM;

int animation_program_initialize(ANIMATION_PROGRAM *program,
    const unsigned char *script, unsigned int script_size, unsigned int script_base,
    unsigned int entry, const unsigned char *data, unsigned int data_size,
    unsigned int data_base);
int animation_program_step(ANIMATION_PROGRAM *program, RENDER_NODE *node,
    RENDER_OWNER *owner, ANIMATION_EVENT event, void *context);

#endif
