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

int music_effects_initialize(MUSIC_PLAYER *player)
{
    if (!player) return -1;
    clear_player(player);
    player->tempo = 125;
    player->speed = 6;
    player->order_count = MUSIC_ORDERS;
    player->sample_reference_period = 1712;
    return 0;
}

int music_initialize(MUSIC_PLAYER *player, const unsigned char *data, unsigned int size)
{
    /* Verified four-channel DSMI 1.4 modules used by the migrated levels. */
    if (!player || !data || size < 75 || data[0] != 'A' || data[1] != 'M' ||
        data[2] != 'F' || data[3] != 14 || data[36] != MUSIC_INSTRUMENTS ||
        !data[37] || data[37] > MUSIC_ORDERS || !read16(data + 38) ||
        read16(data + 38) > MUSIC_TRACKS ||
        data[40] != 4 || data[73] < 33 || !data[74]) return -1;
    clear_player(player);
    player->tempo = data[73]; player->speed = data[74];
    player->order_count = data[37];
    player->sample_reference_period = 1712;
    unsigned int track_count = read16(data + 38);
    for (unsigned int ch = 0; ch < 4; ++ch) {
        int pan = 128 + signed_byte(data[41 + ch]) * 2;
        if (pan < 0 || pan > 255) return -1;
        player->pan[ch] = (unsigned int)pan;
    }
    unsigned int offset = 75;
    for (unsigned int i = 0; i < player->order_count; ++i) {
        if (offset + 10 > size || read16(data + offset) != 64) return -1;
        for (unsigned int ch = 0; ch < 4; ++ch) {
            unsigned int track = read16(data + offset + 2 + ch * 2);
            if (track > track_count) return -1;
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
    if (offset + track_count * 2 > size) return -1;
    unsigned short mapping[MUSIC_TRACKS + 1] = {0};
    unsigned int stored_tracks = 0;
    for (unsigned int i = 1; i <= track_count; ++i) {
        mapping[i] = (unsigned short)read16(data + offset);
        if (mapping[i] > track_count) return -1;
        if (mapping[i] > stored_tracks) stored_tracks = mapping[i];
        offset += 2;
    }
    for (unsigned int order = 0; order < player->order_count; ++order)
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
            } else if (type == 127) {
                /* DSMI's instrument-without-retrigger marker follows instrument selection. */
                continue;
            } else if (type == 128) {
                if (value >= MUSIC_INSTRUMENTS) return -1;
                event->instrument = (unsigned char)(value + 1);
            } else if (type == 0x83) {
                if (value > 64) return -1;
                event->volume = (unsigned char)(value + 1);
            } else {
                if (type != 0x82 && type != 0x84 && type != 0x86 &&
                    type != 0x89 && type != 0x8b && type != 0x91 &&
                    type != 0x8c && type != 0x92 && type != 0x93 &&
                    type != 0x95) return -1;
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

static unsigned int music_note_period(unsigned int note)
{
    unsigned int octave = note / 12;
    unsigned int period = octave < 15 ? note_periods[note % 12] >> octave : 1;
    return period ? period : 1;
}

static void music_trigger(MUSIC_PLAYER *player, MUSIC_VOICE *voice,
    unsigned int note, unsigned int instrument, unsigned int volume)
{
    if (instrument) {
        voice->instrument = instrument;
        voice->volume = player->samples[instrument - 1].volume;
    }
    if (note) {
        voice->period = music_note_period(note);
        voice->target_period = 0;
        voice->tone_portamento = 0;
        voice->phase = 0;
        voice->vibrato_phase = 0;
    }
    if (volume) voice->volume = volume - 1;
}

static void music_tick(MUSIC_PLAYER *player)
{
    if (!player->tick) {
        ++player->rows_played;
        for (unsigned int ch = 0; ch < 4; ++ch) {
            const MUSIC_EVENT *event = &player->tracks[player->orders[player->order][ch]][player->row];
            MUSIC_VOICE *voice = &player->voices[ch];
            voice->volume_slide = 0;
            voice->period_slide = 0;
            voice->tone_portamento = 0;
            voice->vibrato = 0;
            voice->delay_tick = event->effect == 0x93 ? event->parameter & 15 : 0;
            if (voice->delay_tick) {
                voice->delayed_note = event->note;
                voice->delayed_instrument = event->instrument;
                voice->delayed_volume = event->volume;
            } else if (event->effect == 0x86 && event->note) {
                music_trigger(player, voice, 0, event->instrument, event->volume);
                voice->target_period = music_note_period(event->note);
                if (!voice->period) {
                    voice->period = voice->target_period;
                    voice->target_period = 0;
                    voice->phase = 0;
                }
            } else {
                music_trigger(player, voice, event->note, event->instrument, event->volume);
            }
            if (event->effect == 0x84) {
                unsigned int amount = event->parameter & 0x7f;
                voice->period_slide = event->parameter & 0x80 ?
                    -(int)amount : (int)amount;
            } else if (event->effect == 0x92) {
                unsigned int amount = event->parameter & 0x7f;
                int slide = event->parameter & 0x80 ? -(int)amount : (int)amount;
                int period = (int)voice->period + slide;
                voice->period = (unsigned int)(period < 1 ? 1 : period);
            } else if (event->effect == 0x86 && voice->target_period) {
                if (event->parameter) voice->portamento_speed = event->parameter;
                if (!voice->portamento_speed) voice->portamento_speed = 1;
                voice->tone_portamento = 1;
            }
            if (event->effect == 0x82 || event->effect == 0x8b) {
                if (event->parameter) voice->volume_slide_memory = signed_byte(event->parameter);
                voice->volume_slide = voice->volume_slide_memory;
            }
            if (event->effect == 0x91) {
                int slide = signed_byte(event->parameter);
                slide = slide < 0 ? -((-slide) & 15) : slide & 15;
                int volume = (int)voice->volume + slide;
                voice->volume = volume < 0 ? 0 : volume > 64 ? 64 : (unsigned int)volume;
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
        if (player->tick && player->tick == voice->delay_tick)
            music_trigger(player, voice, voice->delayed_note,
                voice->delayed_instrument, voice->delayed_volume);
        if (player->tick && voice->period_slide) {
            int period = (int)voice->period + voice->period_slide;
            voice->period = (unsigned int)(period < 1 ? 1 : period);
        }
        if (player->tick && voice->tone_portamento && voice->target_period) {
            if (voice->period < voice->target_period) {
                unsigned int next = voice->period + voice->portamento_speed;
                voice->period = next > voice->target_period ? voice->target_period : next;
            } else if (voice->period > voice->target_period) {
                voice->period = voice->period - voice->target_period >
                    voice->portamento_speed ? voice->period - voice->portamento_speed :
                    voice->target_period;
            }
            if (voice->period == voice->target_period) voice->tone_portamento = 0;
        }
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
            voice->step = (unsigned int)((unsigned long long)sample->rate *
                player->sample_reference_period * 65536 /
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
            if (++player->order >= player->order_count) {
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
        (player->sample_reference_period != 856 && player->sample_reference_period != 1712) ||
        !player->order_count || player->order_count > MUSIC_ORDERS ||
        player->order >= player->order_count || player->row >= 64) return -1;
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
            int value = (int)sample->data[position] - 128;
            if (player->interpolate_samples) {
                unsigned int next = position + 1;
                if (next >= end)
                    next = sample->loop_end > sample->loop_start ? sample->loop_start : position;
                int difference = (int)sample->data[next] - (int)sample->data[position];
                value = (value * 65536 + difference * (int)(voice->phase & 65535)) *
                    (int)voice->volume * 2 / 65536;
            } else value *= (int)voice->volume * 2;
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
    output->target_frames = MUSIC_RATE / 10;
    return 0;
}

int music_output_service(MUSIC_OUTPUT *output)
{
    if (!output || !output->opened || !output->target_frames ||
        output->target_frames > MUSIC_RATE) return -1;
    /* Bound cooperative work and preserve pending PCM across partial writes. */
    for (unsigned int block = 0; block < 8; ++block) {
        unsigned long long queued = output->api->Audio.QueuedFrames();
        if (queued >= output->target_frames) break;
        unsigned long long free = output->api->Audio.FreeFrames();
        if (!free) break;
        if (output->position == output->count) {
            output->position = 0;
            unsigned long long want = output->target_frames - queued;
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
