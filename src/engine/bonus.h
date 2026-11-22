#ifndef LIONKING_BONUS_H
#define LIONKING_BONUS_H

#include "resources.h"

typedef struct {
    unsigned char map[364360];
    unsigned char timon[9143];
    unsigned char pumbaa[26627];
    unsigned char bugs[5567];
    unsigned char hunt_music[37230];
    unsigned char toss_music[17744];
    unsigned int map_size, timon_size, pumbaa_size, bugs_size;
    unsigned int hunt_music_size, toss_music_size;
    int loaded;
} BONUS_ASSETS;

int bonus_assets_load(BONUS_ASSETS *assets, const DOS64_API *api, const char *archive,
    unsigned char *packed, unsigned int packed_capacity, RESOURCE_DICTIONARY *dictionary);

#endif
