#ifdef LK_DOS64_NATIVE
#include "music.h"

static unsigned int read16(const unsigned char *p)
{
    return p[0] | (unsigned int)p[1] << 8;
}

static unsigned int read32(const unsigned char *p)
{
    return read16(p) | read16(p + 2) << 16;
}

static int signed_byte(unsigned int value)
{
    return value < 128 ? (int)value : (int)value - 256;
}

static void clear_player(MUSIC_PLAYER *player)
{
    volatile unsigned char *bytes = (volatile unsigned char *)player;
    for (unsigned int i = 0; i < sizeof(*player); ++i) bytes[i] = 0;
}

int music_initialize(MUSIC_PLAYER *player, const unsigned char *data, unsigned int size)
{
    /* This migration handles the verified LION1 DSMI 1.4 shape, not arbitrary AMF. */
    if (!player || !data || size < 75 || data[0] != 'A' || data[1] != 'M' ||
        data[2] != 'F' || data[3] != 14 || data[36] != MUSIC_INSTRUMENTS ||
        data[37] != MUSIC_ORDERS || read16(data + 38) != MUSIC_TRACKS ||
        data[40] != 4 || data[73] < 33 || !data[74]) return -1;
    clear_player(player);
    player->tempo = data[73]; player->speed = data[74];
    for (unsigned int ch = 0; ch < 4; ++ch) {
        int pan = 128 + signed_byte(data[41 + ch]) * 2;
        if (pan < 0 || pan > 255) return -1;
        player->pan[ch] = (unsigned int)pan;
    }
    unsigned int offset = 75;
    for (unsigned int i = 0; i < MUSIC_ORDERS; ++i) {
        if (offset + 10 > size || read16(data + offset) != 64) return -1;
        for (unsigned int ch = 0; ch < 4; ++ch) {
            unsigned int track = read16(data + offset + 2 + ch * 2);
            if (track > MUSIC_TRACKS) return -1;
            player->orders[i][ch] = (unsigned short)track;
        }
        offset += 10;
    }
    unsigned int indices[MUSIC_INSTRUMENTS], maximum_sample = 0;
    for (unsigned int i = 0; i < MUSIC_INSTRUMENTS; ++i) {
        if (offset + 65 > size) return -1;
        const unsigned char *p = data + offset;
        MUSIC_SAMPLE *sample = &player->samples[i];
        indices[i] = read32(p + 46);
        sample->length = read32(p + 50);
        sample->rate = read16(p + 54); sample->volume = p[56];
        sample->loop_start = read32(p + 57); sample->loop_end = read32(p + 61);
        if (p[0] > 1 || indices[i] > MUSIC_INSTRUMENTS || sample->length > 65535 || !sample->rate ||
            sample->volume > 64 || sample->loop_start > sample->loop_end ||
            sample->loop_end > sample->length || (!indices[i] && sample->length)) return -1;
        if (indices[i] > maximum_sample) maximum_sample = indices[i];
        offset += 65;
    }
    if (offset + MUSIC_TRACKS * 2 > size) return -1;
    unsigned short mapping[MUSIC_TRACKS + 1] = {0};
    unsigned int stored_tracks = 0;
    for (unsigned int i = 1; i <= MUSIC_TRACKS; ++i) {
        mapping[i] = (unsigned short)read16(data + offset);
        if (mapping[i] > MUSIC_TRACKS) return -1;
        if (mapping[i] > stored_tracks) stored_tracks = mapping[i];
        offset += 2;
    }
    for (unsigned int order = 0; order < MUSIC_ORDERS; ++order)
        for (unsigned int ch = 0; ch < 4; ++ch)
            player->orders[order][ch] = mapping[player->orders[order][ch]];
    for (unsigned int track = 1; track <= stored_tracks; ++track) {
        if (offset + 3 > size) return -1;
        unsigned int events = read16(data + offset); offset += 3;
        if (events > (size - offset) / 3) return -1;
        for (unsigned int i = 0; i < events; ++i) {
            unsigned int row = data[offset], type = data[offset + 1], value = data[offset + 2];
            offset += 3;
            if (row == 255 && type == 255 && value == 255) continue;
            if (row >= 64) return -1;
            MUSIC_EVENT *event = &player->tracks[track][row];
            if (type < 127) {
                if (type) event->note = (unsigned char)type;
                if (value != 255) {
                    if (value > 64) return -1;
                    event->volume = (unsigned char)(value + 1);
                }
            } else if (type == 128) {
                if (value >= MUSIC_INSTRUMENTS) return -1;
                event->instrument = (unsigned char)(value + 1);
            } else if (type == 0x83) {
                if (value > 64) return -1;
                event->volume = (unsigned char)(value + 1);
            } else {
                if (type != 0x82 && type != 0x89 && type != 0x8b &&
                    type != 0x8c && type != 0x95) return -1;
                if (event->effect) return -1;
                if ((type == 0x8c && value >= 64) || (type == 0x95 && value < 33)) return -1;
                event->effect = (unsigned char)type; event->parameter = (unsigned char)value;
            }
        }
    }
    for (unsigned int index = 1; index <= maximum_sample; ++index) {
        int found = 0;
        for (unsigned int i = 0; i < MUSIC_INSTRUMENTS; ++i) {
            if (indices[i] != index) continue;
            if (found || player->samples[i].length > size - offset) return -1;
            found = 1;
            player->samples[i].data = data + offset;
            offset += player->samples[i].length;
        }
        if (!found) return -1;
    }
    return offset == size ? 0 : -1;
}

/* Amiga periods for C..B, octave zero, in quarter-period units. */
static const unsigned int note_periods[12] = {
    27392,25856,24384,23040,21696,20480,19328,18240,17216,16256,15344,14480
};
static const unsigned char vibrato_sine[32] = {
    0,24,49,74,97,120,141,161,180,197,212,224,235,244,250,253,
    255,253,250,244,235,224,212,197,180,161,141,120,97,74,49,24
};

static void music_tick(MUSIC_PLAYER *player)
{
    if (!player->tick) {
        ++player->rows_played;
        for (unsigned int ch = 0; ch < 4; ++ch) {
            const MUSIC_EVENT *event = &player->tracks[player->orders[player->order][ch]][player->row];
            MUSIC_VOICE *voice = &player->voices[ch];
            voice->volume_slide = 0; voice->vibrato = 0;
            if (event->instrument) {
                voice->instrument = event->instrument;
                voice->volume = player->samples[voice->instrument - 1].volume;
            }
            if (event->note) {
                unsigned int octave = event->note / 12;
                voice->period = octave < 15 ? note_periods[event->note % 12] >> octave : 1;
                if (!voice->period) voice->period = 1;
                voice->phase = 0; voice->vibrato_phase = 0;
            }
            if (event->volume) voice->volume = event->volume - 1;
            if (event->effect == 0x82 || event->effect == 0x8b) {
                if (event->parameter) voice->volume_slide_memory = signed_byte(event->parameter);
                voice->volume_slide = voice->volume_slide_memory;
            }
            if (event->effect == 0x89) {
                if (event->parameter >> 4) voice->vibrato_speed = event->parameter >> 4;
                if (event->parameter & 15) voice->vibrato_depth = event->parameter & 15;
            }
            if (event->effect == 0x89 || event->effect == 0x8b) voice->vibrato = 1;
            if (event->effect == 0x8c) {
                player->breaking = 1; player->break_row = event->parameter;
            }
            if (event->effect == 0x95) player->tempo = event->parameter;
        }
    }
    for (unsigned int ch = 0; ch < 4; ++ch) {
        MUSIC_VOICE *voice = &player->voices[ch];
        if (player->tick) {
            int volume = (int)voice->volume + voice->volume_slide;
            voice->volume = volume < 0 ? 0 : volume > 64 ? 64 : (unsigned int)volume;
        }
        int period = (int)voice->period;
        if (voice->vibrato && player->tick) {
            unsigned int phase = voice->vibrato_phase;
            int delta = (int)(vibrato_sine[phase & 31] * voice->vibrato_depth / 128) * 4;
            period += phase & 32 ? -delta : delta;
            voice->vibrato_phase = (phase + voice->vibrato_speed) & 63;
        }
        voice->step = 0;
        if (voice->instrument && period > 0) {
            const MUSIC_SAMPLE *sample = &player->samples[voice->instrument - 1];
            /* Sample C4 rate is calibrated to period 428 (1712 quarter units). */
            voice->step = (unsigned int)((unsigned long long)sample->rate * 1712 * 65536 /
                ((unsigned int)period * (unsigned long long)MUSIC_RATE));
        }
    }
    unsigned int duration = MUSIC_RATE * 5 + player->tick_remainder;
    player->tick_remaining = duration / (player->tempo * 2);
    player->tick_remainder = duration % (player->tempo * 2);
    if (++player->tick >= player->speed) {
        player->tick = 0;
        if (player->breaking || ++player->row >= 64) {
            player->row = player->breaking ? player->break_row : 0;
            player->breaking = 0;
            if (++player->order >= MUSIC_ORDERS) {
                player->order = 0; ++player->loops;
            }
        }
    }
}

int music_effect_play(MUSIC_PLAYER *player, unsigned int channel,
    const unsigned char *data, unsigned int size)
{
    if (!player || channel >= 2 || !data || !size) return -1;
    player->effects[channel] = (MUSIC_EFFECT){data, size, 0};
    return 0;
}

int music_samples(MUSIC_PLAYER *player, short *stereo, unsigned int frames)
{
    if (!player || !stereo || !player->speed || player->tempo < 33 ||
        player->order >= MUSIC_ORDERS || player->row >= 64) return -1;
    for (unsigned int frame = 0; frame < frames; ++frame) {
        if (!player->tick_remaining) music_tick(player);
        int left = 0, right = 0;
        for (unsigned int ch = 0; ch < 4; ++ch) {
            MUSIC_VOICE *voice = &player->voices[ch];
            if (!voice->instrument || !voice->period) continue;
            const MUSIC_SAMPLE *sample = &player->samples[voice->instrument - 1];
            unsigned int position = voice->phase >> 16;
            unsigned int end = sample->loop_end ? sample->loop_end : sample->length;
            if (position >= end) {
                if (sample->loop_end > sample->loop_start) {
                    position = sample->loop_start + (position - sample->loop_start) %
                        (sample->loop_end - sample->loop_start);
                    voice->phase = (position << 16) | (voice->phase & 65535);
                } else {
                    voice->period = 0; continue;
                }
            }
            int value = ((int)sample->data[position] - 128) * (int)voice->volume * 2;
            int pan = (int)player->pan[ch];
            left += value * (256 - pan) / 256; right += value * pan / 256;
            voice->phase += voice->step;
        }
        for (unsigned int channel = 0; channel < 2; ++channel) {
            MUSIC_EFFECT *effect = &player->effects[channel];
            if (!effect->data) continue;
            unsigned long long position = effect->phase >> 32;
            if (position >= effect->length) {
                effect->data = 0;
                continue;
            }
            int value = ((int)effect->data[position] - 128) * 128;
            left += value;
            right += value;
            effect->phase += (12604ULL << 32) / MUSIC_RATE;
        }
        stereo[frame * 2] = (short)(left < -32768 ? -32768 : left > 32767 ? 32767 : left);
        stereo[frame * 2 + 1] = (short)(right < -32768 ? -32768 : right > 32767 ? 32767 : right);
        --player->tick_remaining;
    }
    player->frames_generated += frames;
    return 0;
}

int music_output_open(MUSIC_OUTPUT *output, MUSIC_PLAYER *player, const DOS64_API *api)
{
    if (!output || !player || !api || !api->Audio.Present || !api->Audio.Open ||
        !api->Audio.Write || !api->Audio.FreeFrames || !api->Audio.QueuedFrames ||
        !api->Audio.Stop || api->Audio.Open(MUSIC_RATE) != 0) return -1;
    *output = (MUSIC_OUTPUT){0};
    output->player = player; output->api = api; output->opened = 1;
    return 0;
}

int music_output_service(MUSIC_OUTPUT *output)
{
    if (!output || !output->opened) return -1;
    /* Bound cooperative work and keep about 100 ms queued without discarding partial writes. */
    for (unsigned int block = 0; block < 8; ++block) {
        unsigned long long queued = output->api->Audio.QueuedFrames();
        if (queued >= MUSIC_RATE / 10) break;
        unsigned long long free = output->api->Audio.FreeFrames();
        if (!free) break;
        if (output->position == output->count) {
            output->position = 0;
            unsigned long long want = MUSIC_RATE / 10 - queued;
            if (want > free) want = free;
            output->count = want > 1024 ? 1024 : (unsigned int)want;
            if (music_samples(output->player, output->pending, output->count) != 0) return -1;
        }
        unsigned int want = output->count - output->position;
        if (want > free) want = (unsigned int)free;
        unsigned long long taken = output->api->Audio.Write(output->pending + output->position * 2, want);
        if (taken > want) return -1;
        output->position += (unsigned int)taken; output->submitted += taken;
        if (!taken) break;
    }
    return 0;
}

void music_output_stop(MUSIC_OUTPUT *output)
{
    if (output && output->opened) {
        output->api->Audio.Stop(); output->opened = 0;
    }
    #endif
}
