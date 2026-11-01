#ifndef LIONKING_DOS64_PLATFORM_H
#define LIONKING_DOS64_PLATFORM_H

#include "dos64_api.h"

#define LK_WIDTH 320U
#define LK_HEIGHT 200U

int lk_platform_init(const DOS64_API *api);
void lk_platform_poll(void);
int lk_platform_exit_requested(void);
unsigned long long lk_platform_time_ns(void);
void lk_platform_sleep(unsigned int milliseconds);
void lk_platform_present(const unsigned char *pixels, const DOS64_COLOR *palette);
void lk_platform_log(const char *text);

#endif
