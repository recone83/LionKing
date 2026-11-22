#ifndef LK_DOS64_PREVIEW_IDLE_H
#define LK_DOS64_PREVIEW_IDLE_H

#include "start_runtime.h"

typedef struct {
    ANIMATION_PROGRAM program;
    RENDER_NODE *node;
    RENDER_OWNER *owner;
    int enabled;
    int failed;
    unsigned int events;
} PREVIEW_ANIMATION;

int record_player_idle_event(void *context, unsigned int target);
void update_preview(void *context);
int start_idle_preview(const DOS64_API *api, RENDER_SPRITE_BANK banks[34], PREVIEW_ANIMATION *animation);
int load_preview_bank(const DOS64_API *api, unsigned int index, RENDER_SPRITE_BANK banks[34], unsigned char part[20], unsigned int *frames);
int present_frame(void *context, const unsigned char *source, const DOS64_COLOR *colors);

#endif
