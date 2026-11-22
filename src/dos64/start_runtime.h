#ifndef LK_DOS64_START_RUNTIME_H
#define LK_DOS64_START_RUNTIME_H

#include "platform.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "engine/timing.h"
#include "engine/input.h"
#include "engine/controls.h"
#include "engine/render.h"
#include "engine/assets.h"
#include "engine/animation.h"
#include "engine/animation_data.h"
#include "engine/behaviors.h"
#include "engine/music.h"
#include "engine/bonus.h"
#include "engine/enemies.h"
#include "engine/pickups.h"
#include "engine/lifecycle.h"
#include "engine/hud.h"
#include "libs/vga.h"
#include "dos64_memory.h"

typedef struct {
    unsigned char pixels[LK_WIDTH * (LK_HEIGHT + 7)];
    unsigned char hurt_layer[LK_WIDTH * LK_HEIGHT];
    unsigned char packed[79311], map[580488], map_contours[4096];
    unsigned char animated_tiles[12800], level_music[131072];
    unsigned char enemy_sprites[21][65536], game_over_sprites[4096];
    unsigned char pickup_sprites[5][131072], hud_sprites[32768];
    unsigned char effect_samples[19][65536], sprite[32768];
    unsigned char idle_sprites[3][32768];
    unsigned char player_sprites[ASSETS_YOUNG_BANK_COUNT][32768];
} GAME_BUFFERS;

extern GAME_BUFFERS *game_buffers;
extern unsigned char *pixels, *hurt_layer, *packed, *map, *map_contours;
extern unsigned char *animated_tiles, *level_music;
extern unsigned char (*enemy_sprites)[65536], *game_over_sprites;
extern unsigned char (*pickup_sprites)[131072], *hud_sprites;
extern unsigned char (*effect_samples)[65536], *sprite;
extern unsigned char (*idle_sprites)[32768], (*player_sprites)[32768];
extern DOS64_COLOR palette[256];
extern MUSIC_PLAYER music_player;
extern MUSIC_OUTPUT music_output;
extern BONUS_ASSETS *bonus_assets;
extern int menu_active;
extern unsigned int loading_level;
extern int sound_enabled;
extern int music_enabled;
extern ENGINE_CONTROLS game_controls;
extern ENGINE_DIFFICULTY game_difficulty;
extern ENGINE_ENEMIES map_enemies;
extern ENGINE_PICKUPS map_pickups;
extern unsigned int game_over_size;
extern unsigned int effect_sizes[19];
extern RESOURCE_DICTIONARY dictionary;
extern RENDER_POOL render_pool;
extern VGA_FADE fade;
extern unsigned char level_rgb[768];
extern const unsigned char black_rgb[768];
extern ENGINE_OBJECT_POOL scene_objects;
extern ENGINE_EMITTER_GROUP scene_emitters;
extern int scene_failed;
extern DOS64_API resource_api;

int loading_progress(unsigned int completed);
int start_level_two(const DOS64_API *api, unsigned char *lives, unsigned int *continues,
    unsigned short *max_roar);
int allocate_bonus_assets(const DOS64_API *api);
int argument_requested(const char *arguments, const char *expected);
void log_map_measurement(const char *label, unsigned int value);

#endif
