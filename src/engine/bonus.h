#ifndef LIONKING_BONUS_H
#define LIONKING_BONUS_H

#include "resources.h"

typedef struct {
    unsigned char map[364360];
    unsigned char timon[9143];
    unsigned char timon_walk[10160];
    unsigned char pumbaa[26627];
    unsigned char pumbaa_burp[16432];
    unsigned char bugs[5567];
    unsigned char destiny[32768];
    unsigned char circle[32768];
    unsigned char meat[32768];
    unsigned char burp_sound[10280];
    unsigned char collect_sound[32768];
    unsigned char hunt_music[37230];
    unsigned char toss_music[17744];
    unsigned int map_size, timon_size, timon_walk_size, pumbaa_size, pumbaa_burp_size, bugs_size;
    unsigned int destiny_size, circle_size, meat_size, burp_sound_size, collect_sound_size;
    unsigned int hunt_music_size, toss_music_size;
    int loaded;
} BONUS_ASSETS;

int bonus_assets_load(BONUS_ASSETS *assets, const DOS64_API *api, const char *archive,
    unsigned char *packed, unsigned int packed_capacity, RESOURCE_DICTIONARY *dictionary);

#endif
