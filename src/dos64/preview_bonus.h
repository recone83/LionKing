#ifndef LK_DOS64_PREVIEW_BONUS_H
#define LK_DOS64_PREVIEW_BONUS_H

#include "start_runtime.h"

int run_bonus_view(const DOS64_API *api);
int run_bonus_toss_game(const DOS64_API *api, unsigned char *lives, unsigned int *continues,
    unsigned short *max_roar);

#endif
