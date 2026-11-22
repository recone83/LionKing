#ifndef LIONKING_DOS64_PLATFORM_H
#define LIONKING_DOS64_PLATFORM_H

#include "dos64_api.h"

#define LK_WIDTH 320U
#define LK_HEIGHT 200U

int lk_platform_init(const DOS64_API *api);
int lk_platform_finish(int result);
void lk_platform_poll(void);
int lk_platform_exit_requested(void);
unsigned long long lk_platform_time_ns(void);
void lk_platform_sleep(unsigned int milliseconds);
void lk_platform_present(const unsigned char *pixels, const DOS64_COLOR *palette);
void lk_platform_present_hurt_opacity(const unsigned char *foreground,
    const unsigned char *background, const DOS64_COLOR *palette);
void lk_platform_present_game(const unsigned char *foreground,
    const unsigned char *background, const DOS64_COLOR *palette);
void lk_platform_log(const char *text);

typedef enum {
    LK_PROFILE_INPUT,
    LK_PROFILE_AUDIO,
    LK_PROFILE_RENDER,
    LK_PROFILE_CONVERT,
    LK_PROFILE_CLEAR,
    LK_PROFILE_DRAW,
    LK_PROFILE_PRESENT,
    LK_PROFILE_LOGIC,
    LK_PROFILE_SLEEP,
    LK_PROFILE_COUNT
} LK_PROFILE_STAGE;

void lk_platform_profile_enable(int enabled);
void lk_platform_profile_record(LK_PROFILE_STAGE stage, unsigned long long begin);

#endif
