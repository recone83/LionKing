#ifndef LIONKING_FRONTEND_H
#define LIONKING_FRONTEND_H

#include "dos64_api.h"

int frontend_initialize(const DOS64_API *resources);
int frontend_release(void);
int frontend_splash(const DOS64_API *api);
int frontend_intro(const DOS64_API *api);
int frontend_pregame(const DOS64_API *api, int sound_enabled);
int frontend_victory(const DOS64_API *api, const DOS64_API *resources, int sound_enabled);
int frontend_next_level_unavailable(const DOS64_API *api, const DOS64_API *resources);
int frontend_level_title(unsigned char *pixels);
int frontend_prepare_continue(const DOS64_API *resources, const DOS64_COLOR *level_palette);
int frontend_start_continue(const DOS64_API *api, int sound_enabled);
int frontend_service_continue(void);
void frontend_stop_continue(void);
#define FRONTEND_CONTINUE_TICKS 721U
#define FRONTEND_CONTINUE_ACCEPT_TICKS 151U
#define FRONTEND_GAME_OVER_TICKS 201U
int frontend_continue(unsigned char *pixels, DOS64_COLOR *palette,
    unsigned int ticks, int no_selected, unsigned int continues,
    unsigned int accept_ticks, int exhausted);
void frontend_stop_audio(void);
int frontend_level_palette(const DOS64_COLOR *palette);
int frontend_menu(const DOS64_API *api, int *sound_enabled);
int frontend_loading(unsigned int completed, unsigned int total);

#endif
