#ifndef LIONKING_MUSIC_H
#define LIONKING_MUSIC_H

#include "dos64_api.h"

#define MUSIC_RATE 44100U
#define MUSIC_TRACKS 60U
#define MUSIC_ORDERS 32U
#define MUSIC_INSTRUMENTS 31U

typedef struct {
    unsigned char note, instrument, volume, effect, parameter;
} MUSIC_EVENT;

typedef struct {
    const unsigned char *data;
    unsigned int length, loop_start, loop_end, rate, volume;
} MUSIC_SAMPLE;

typedef struct {
    unsigned int instrument, volume, period, phase, step;
    unsigned int vibrato_speed, vibrato_depth, vibrato_phase;
    unsigned int delayed_note, delayed_instrument, delayed_volume, delay_tick;
    unsigned int target_period, portamento_speed;
    int period_slide;
    int volume_slide;
    int volume_slide_memory;
    int vibrato;
    int tone_portamento;
} MUSIC_VOICE;

typedef struct {
    const unsigned char *data;
    unsigned int length;
    unsigned long long phase;
} MUSIC_EFFECT;

typedef struct {
    MUSIC_EVENT tracks[MUSIC_TRACKS + 1][64];
    unsigned short orders[MUSIC_ORDERS][4];
    MUSIC_SAMPLE samples[MUSIC_INSTRUMENTS];
    MUSIC_VOICE voices[4];
    MUSIC_EFFECT effects[2];
    unsigned int pan[4];
    unsigned int order, row, tick, speed, tempo, tick_remaining;
    unsigned int tick_remainder, break_row, loops, rows_played;
    unsigned long long frames_generated;
    int breaking;
    unsigned int order_count;
    int interpolate_samples;
    unsigned int sample_reference_period;
} MUSIC_PLAYER;

int music_initialize(MUSIC_PLAYER *player, const unsigned char *data, unsigned int size);
int music_effects_initialize(MUSIC_PLAYER *player);
int music_samples(MUSIC_PLAYER *player, short *stereo, unsigned int frames);
int music_effect_play(MUSIC_PLAYER *player, unsigned int channel,
    const unsigned char *data, unsigned int size);

typedef struct {
    MUSIC_PLAYER *player;
    const DOS64_API *api;
    short pending[1024 * 2];
    unsigned int position, count;
    unsigned long long submitted;
    int opened;
    unsigned int target_frames;
} MUSIC_OUTPUT;

int music_output_open(MUSIC_OUTPUT *output, MUSIC_PLAYER *player, const DOS64_API *api);
int music_output_service(MUSIC_OUTPUT *output);
void music_output_stop(MUSIC_OUTPUT *output);

#endif
