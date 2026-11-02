#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/music.h"
#include "engine/resources.h"

static MUSIC_PLAYER player, reference;
static MUSIC_OUTPUT output;
static unsigned char packed[79311], data[49887];
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
