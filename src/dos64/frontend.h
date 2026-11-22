#ifndef LIONKING_FRONTEND_H
#define LIONKING_FRONTEND_H

#include "dos64_api.h"

int frontend_initialize(const DOS64_API *resources);
int frontend_splash(const DOS64_API *api);
int frontend_intro(const DOS64_API *api);
int frontend_pregame(const DOS64_API *api, int sound_enabled);
int frontend_victory(const DOS64_API *api, const DOS64_API *resources, int sound_enabled);
int frontend_level_title(unsigned char *pixels);
void frontend_stop_audio(void);
int frontend_level_palette(const DOS64_COLOR *palette);
int frontend_menu(const DOS64_API *api, int *sound_enabled);
int frontend_loading(unsigned int completed, unsigned int total);

#endif
