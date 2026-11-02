#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/music.h"
#include "engine/resources.h"
#include "engine/assets.h"
#include "engine/animation_data.h"

static MUSIC_PLAYER player, reference;
static MUSIC_OUTPUT output;
static unsigned char packed[79311], data[49887];
static unsigned char effect_data[65536];
static RESOURCE_DICTIONARY dictionary;
static short samples[44100 * 2], fragmented[44100 * 2];
static short submitted[4410 * 2];
static unsigned int queued, stopped, write_limit = 137;

static void __attribute__((ms_abi)) log_message(const char *s) { fputs(s, stderr); }
static void * __attribute__((ms_abi)) open_file(const char *p, const char *m) { return fopen(p, m); }
static int __attribute__((ms_abi)) close_file(void *f) { return fclose(f); }
static int __attribute__((ms_abi)) seek_file(void *f, long long p, int w) { return fseek(f, (long)p, w); }
static long long __attribute__((ms_abi)) tell_file(void *f) { return ftell(f); }
static unsigned long long __attribute__((ms_abi)) read_file(void *p,
    unsigned long long s, unsigned long long n, void *f) { return fread(p, s, n, f); }
static int __attribute__((ms_abi)) audio_open(unsigned int rate)
{
    assert(rate == MUSIC_RATE); queued = 0; return 0;
}
static unsigned long long __attribute__((ms_abi)) audio_free(void) { return 4410 - queued; }
static unsigned long long __attribute__((ms_abi)) audio_queued(void) { return queued; }
static unsigned long long __attribute__((ms_abi)) audio_write(const short *p, unsigned long long n)
{
    assert(n <= 4410 - queued);
    if (n > write_limit) n = write_limit;
    memcpy(submitted + queued * 2, p, (size_t)n * 4);
    queued += (unsigned int)n;
    return n;
}
static void __attribute__((ms_abi)) audio_stop(void) { ++stopped; queued = 0; }

int main(void)
{
    DOS64_API api = {0};
    api.Write = log_message;
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file;
    unsigned int size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LION1.AMF",
        packed, sizeof(packed), data, sizeof(data), &dictionary, &size) == 0);
    assert(size == sizeof(data));
    assert(music_initialize(&player, data, size) == 0);
    assert(player.tempo == 125 && player.speed == 6);
    assert(player.pan[0] == 2 && player.pan[1] == 254 && player.pan[2] == 254 && player.pan[3] == 2);
    reference = player;
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    unsigned long long energy[2] = {0};
    for (unsigned int i = 0; i < MUSIC_RATE * 2; ++i) {
        int sample = samples[i];
        energy[i & 1] += sample < 0 ? (unsigned int)-sample : (unsigned int)sample;
    }
    assert(energy[0] > 1000000 && energy[1] > 1000000);
    for (unsigned int pos = 0; pos < MUSIC_RATE;) {
        unsigned int count = MUSIC_RATE - pos;
        if (count > 137) count = 137;
        assert(music_samples(&reference, fragmented + pos * 2, count) == 0);
        pos += count;
    }
    assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
    assert(player.row == reference.row && player.tick == reference.tick);
    printf("AMF position after second: order%u row%u tick%u tempo%u rows%u\n",
        player.order, player.row, player.tick, player.tempo, player.rows_played);
    assert(player.tempo == 165 && player.rows_played == 11);
    printf("PASS: LION1.AMF stereo PCM, energy %llu/%llu, 11 rows in one second, chunk-invariant playback\n",
        energy[0], energy[1]);

    assert(music_initialize(&player, data, size) == 0);
    unsigned int seconds = 0;
    while (!player.loops && seconds < 120) {
        assert(music_samples(&player, samples, MUSIC_RATE) == 0); ++seconds;
    }
    assert(player.loops == 1 && seconds > 30 && seconds < 120);
    assert(seconds == 82);
    printf("PASS: all 15 orders, vibrato/volume slides/tempo/break effects and song loop at %u seconds\n", seconds);

    assert(music_initialize(&player, data, size) == 0);
    assert(music_output_open(&output, &player, &api) == -1);
    api.Audio.Present = 1; api.Audio.Open = audio_open; api.Audio.FreeFrames = audio_free;
    api.Audio.QueuedFrames = audio_queued; api.Audio.Write = audio_write; api.Audio.Stop = audio_stop;
    assert(music_output_open(&output, &player, &api) == 0);
    write_limit = 0;
    assert(music_output_service(&output) == 0 && !queued && output.count == 1024);
    write_limit = 137;
    for (unsigned int i = 0; i < 20 && queued < 4410; ++i) assert(music_output_service(&output) == 0);
    assert(queued == 4410 && output.submitted == 4410);
    assert(music_initialize(&reference, data, size) == 0);
    assert(music_samples(&reference, samples, 4410) == 0);
    assert(memcmp(samples, submitted, sizeof(submitted)) == 0);
    music_output_stop(&output); music_output_stop(&output);
    assert(stopped == 1 && !output.opened);
    puts("PASS: partial/zero audio writes preserve every frame, bounded queue and idempotent stop");

    static const unsigned char effect[] = {128, 255, 0, 129};
    assert(music_initialize(&player, data, size) == 0);
    reference = player;
    assert(music_effect_play(&player, 0, effect, sizeof(effect)) == 0);
    assert(music_samples(&player, fragmented, 256) == 0);
    assert(music_samples(&reference, samples, 256) == 0);
    unsigned long long phase = 0;
    for (unsigned int i = 0; i < 256; ++i) {
        unsigned long long position = phase >> 32;
        int value = position < sizeof(effect) ? ((int)effect[position]-128)*128 : 0;
        for (unsigned int channel = 0; channel < 2; ++channel) {
            int mixed = samples[i*2+channel] + value;
            assert(fragmented[i*2+channel] ==
                (mixed < -32768 ? -32768 : mixed > 32767 ? 32767 : mixed));
        }
        phase += (12604ULL << 32) / MUSIC_RATE;
    }
    assert(!player.effects[0].data);
    assert(music_effect_play(&player, 2, effect, sizeof(effect)) == -1);
    assert(music_effect_play(&player, 0, effect, 0) == -1);
    static const unsigned char loud[] = {255};
    assert(music_initialize(&player, data, size) == 0);
    assert(music_effect_play(&player, 0, loud, 1) == 0);
    assert(music_effect_play(&player, 1, loud, 1) == 0);
    assert(music_samples(&player, samples, 1) == 0);
    assert(samples[0] == 32512 && samples[1] == 32512);
    assert(music_effect_play(&player, 0, effect, sizeof(effect)) == 0 &&
        !player.effects[0].phase);
    puts("PASS: exact unsigned PCM effect conversion, 12604 Hz resampling, two channels and interruption reset");
    static unsigned char saturated_effect[128];
    memset(saturated_effect, 255, sizeof(saturated_effect));
    assert(music_initialize(&player, data, size) == 0);
    reference = player;
    assert(music_effect_play(&player, 0, saturated_effect, sizeof(saturated_effect)) == 0);
    assert(music_effect_play(&player, 1, saturated_effect, sizeof(saturated_effect)) == 0);
    assert(music_samples(&player, fragmented, 256) == 0);
    assert(music_samples(&reference, samples, 256) == 0);
    unsigned int clipped = 0;
    for (unsigned int i = 0; i < 512; ++i) {
        assert(samples[i] != -32768 && samples[i] != 32767);
        int mixed = samples[i] + 32512;
        if (mixed > 32767) ++clipped;
        assert(fragmented[i] == (mixed > 32767 ? 32767 : mixed));
    }
    assert(clipped > 0);
    puts("PASS: combined music/two-effect saturation clamps actual over-range samples without wraparound");

    for (unsigned int i = 0; i < 15; ++i) {
        const unsigned char *list = i < 11 ? animation_common_sound_list : animation_level1_sound_list;
        unsigned int list_size = i < 11 ? sizeof(animation_common_sound_list) :
            sizeof(animation_level1_sound_list);
        char name[13];
        unsigned int slot, length;
        assert(assets_slot_list_name(list, list_size, i < 11 ? i : i-11, &slot, name) == 0);
        assert(resources_load_entry(&api, "data/LIONKING.EPF", name, packed, sizeof(packed),
            effect_data, sizeof(effect_data), &dictionary, &length) == 0);
        assert(length > 0);
        assert(music_initialize(&player, data, size) == 0);
        reference = player;
        assert(music_effect_play(&player, 0, effect_data, length) == 0);
        assert(music_effect_play(&reference, 0, effect_data, length) == 0);
        assert(music_samples(&player, samples, MUSIC_RATE) == 0);
        for (unsigned int pos = 0; pos < MUSIC_RATE;) {
            unsigned int count = MUSIC_RATE-pos;
            if (count > 137) count = 137;
            assert(music_samples(&reference, fragmented+pos*2, count) == 0);
            pos += count;
        }
        assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
        printf("PASS: original sample %u %s (%u bytes), music/effect chunk-invariant mix\n",
            slot, name, length);
        if (i == 0) {
            assert(music_initialize(&player, data, size) == 0);
            assert(music_effect_play(&player, 0, effect_data, length) == 0);
            assert(music_effect_play(&player, 1, effect_data, length) == 0);
            reference = player;
            assert(music_output_open(&output, &player, &api) == 0);
            write_limit = 0;
            assert(music_output_service(&output) == 0 && !queued && output.count == 1024);
            write_limit = 137;
            for (unsigned int j = 0; j < 20 && queued < 4410; ++j)
                assert(music_output_service(&output) == 0);
            assert(queued == 4410);
            assert(music_samples(&reference, samples, 4410) == 0);
            assert(memcmp(samples, submitted, sizeof(submitted)) == 0);
            music_output_stop(&output);
            puts("PASS: actual two-channel BOUNCE/music mix preserves exact PCM through partial/zero writes");
        }
    }

    for (unsigned int n = 0; n < size; n += 499) assert(music_initialize(&player, data, n) == -1);
    unsigned char saved = data[3]; data[3] = 13;
    assert(music_initialize(&player, data, size) == -1); data[3] = saved;
    saved = data[225 + 64]; data[225 + 64] = 255;
    assert(music_initialize(&player, data, size) == -1); data[225 + 64] = saved;
    saved = data[225 + 52]; data[225 + 52] = 1;
    assert(music_initialize(&player, data, size) == -1); data[225 + 52] = saved;
    data[77] = 255;
    assert(music_initialize(&player, data, size) == -1);
    puts("PASS: truncated and unsupported module data rejected explicitly");
    return 0;
}
