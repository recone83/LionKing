#ifndef LK_DOS64_PREVIEW_PLAYER_H
#define LK_DOS64_PREVIEW_PLAYER_H

#include "start_runtime.h"

int run_deflection_preview(const DOS64_API *api, int mode);
int run_level_two(const DOS64_API *api, unsigned char *lives, unsigned int *continues,
    unsigned short *max_roar);

#endif
