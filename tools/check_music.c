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
static unsigned int ring_capacity = 4410;

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
static unsigned long long __attribute__((ms_abi)) audio_free(void) { return ring_capacity - queued; }
static unsigned long long __attribute__((ms_abi)) audio_queued(void) { return queued; }
static unsigned long long __attribute__((ms_abi)) audio_write(const short *p, unsigned long long n)
{
    assert(n <= ring_capacity - queued);
    if (n > write_limit) n = write_limit;
    if (ring_capacity == 4410) memcpy(submitted + queued * 2, p, (size_t)n * 4);
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

    assert(music_effects_initialize(&player) == 0);
    player.orders[0][0] = 1;
    player.tracks[1][0].effect = 0x91;
    player.tracks[1][0].parameter = 254;
    player.voices[0].volume = 10;
    assert(music_samples(&player, samples, 1) == 0 && player.voices[0].volume == 8);
    assert(music_samples(&player, samples, 4410) == 0 && player.voices[0].volume == 8);
    puts("PASS: fine volume slide applies once per row");

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
    assert(music_effects_initialize(0) == -1);
    assert(music_effects_initialize(&player) == 0);
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    for (unsigned int i = 0; i < MUSIC_RATE * 2; ++i) assert(samples[i] == 0);
    unsigned int speech_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "SPEECH5",
        packed, sizeof(packed), effect_data, sizeof(effect_data),
        &dictionary, &speech_size) == 0);
    assert(music_effects_initialize(&player) == 0);
    assert(music_effect_play(&player, 0, effect_data, speech_size) == 0);
    assert(music_effect_play(&player, 1, effect_data, speech_size) == 0);
    reference = player;
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    unsigned long long speech_energy = 0;
    for (unsigned int i = 0; i < MUSIC_RATE; ++i) {
        unsigned long long position = ((12604ULL << 32) / MUSIC_RATE * i) >> 32;
        int value = position < speech_size ? ((int)effect_data[position] - 128) * 256 : 0;
        if (value < -32768) value = -32768;
        if (value > 32767) value = 32767;
        assert(samples[i * 2] == value && samples[i * 2 + 1] == value);
        speech_energy += value < 0 ? (unsigned int)-value : (unsigned int)value;
    }
    assert(speech_energy > 1000000);
    for (unsigned int pos = 0; pos < MUSIC_RATE;) {
        unsigned int count = MUSIC_RATE - pos;
        if (count > 137) count = 137;
        assert(music_samples(&reference, fragmented + pos * 2, count) == 0);
        pos += count;
    }
    assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
    puts("PASS: effect-only output is silent until triggered; exact two-channel SPEECH5 PCM is chunk invariant");
    static unsigned char title_packed[85438], title_data[88301];
    unsigned int title_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "TITLE.AMF",
        title_packed, sizeof(title_packed), title_data, sizeof(title_data),
        &dictionary, &title_size) == 0);
    assert(music_initialize(&player, title_data, title_size) == 0);
    assert(player.order_count == 5 && player.tempo == 125 && player.speed == 6);
    assert(player.sample_reference_period == 1712);
    assert(player.samples[1].length == 31492 && player.samples[1].rate == 8368);
    player.sample_reference_period = 856;
    reference = player;
    reference.sample_reference_period = 1712;
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    assert(music_samples(&reference, fragmented, MUSIC_RATE) == 0);
    assert(player.voices[1].instrument == 2 && player.voices[1].period == 570);
    unsigned int vocal_step = (unsigned int)(8368ULL * 856 * 65536 / (570ULL * MUSIC_RATE));
    assert(player.voices[1].step == vocal_step &&
        reference.voices[1].step >= vocal_step * 2 &&
        reference.voices[1].step <= vocal_step * 2 + 1);
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    assert(music_samples(&reference, fragmented, MUSIC_RATE) == 0);
    assert(player.voices[1].period && player.voices[1].phase >> 16 < 31492);
    assert(!reference.voices[1].period);
    printf("PASS: original 31492-byte title vocal uses C5 rate, not double-speed C4; "
        "vocal is still active after two seconds (step %u)\n", vocal_step);
    assert(music_initialize(&player, title_data, title_size) == 0);
    player.sample_reference_period = 856;
    reference = player;
    assert(music_samples(&reference, fragmented, MUSIC_RATE) == 0);
    player.interpolate_samples = 1;
    reference = player;
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    unsigned long long title_energy = 0;
    for (unsigned int i = 0; i < MUSIC_RATE * 2; ++i)
        title_energy += samples[i] < 0 ? (unsigned int)-samples[i] : (unsigned int)samples[i];
    assert(title_energy > 1000000);
    unsigned long long nearest_steps = 0, smooth_steps = 0;
    for (unsigned int i = 2; i < MUSIC_RATE * 2; ++i) {
        long long a = (int)fragmented[i] - (int)fragmented[i - 2];
        long long b = (int)samples[i] - (int)samples[i - 2];
        nearest_steps += (unsigned long long)(a * a);
        smooth_steps += (unsigned long long)(b * b);
    }
    assert(smooth_steps * 100 < nearest_steps * 95);
    printf("PASS: real title sample interpolation reduces squared adjacent-sample steps by %llu%%\n",
        100 - smooth_steps * 100 / nearest_steps);
    for (unsigned int pos = 0; pos < MUSIC_RATE;) {
        unsigned int count = MUSIC_RATE - pos;
        if (count > 137) count = 137;
        assert(music_samples(&reference, fragmented + pos * 2, count) == 0);
        pos += count;
    }
    assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
    seconds = 1;
    while (!player.loops && seconds < 120) {
        assert(music_samples(&player, samples, MUSIC_RATE) == 0);
        ++seconds;
    }
    assert(player.loops == 1 && player.order == 0 && seconds > 20 && seconds < 120);
    printf("PASS: original TITLE.AMF, 5 orders/20 tracks and instrument-without-retrigger markers, "
        "chunk-invariant PCM, song loop at %u seconds\n", seconds);
    for (unsigned int n = 0; n < title_size; n += 997)
        assert(music_initialize(&player, title_data, n) == -1);
    unsigned char saved_count = title_data[37];
    title_data[37] = MUSIC_ORDERS + 1;
    assert(music_initialize(&player, title_data, title_size) == -1);
    title_data[37] = 0;
    assert(music_initialize(&player, title_data, title_size) == -1);
    title_data[37] = saved_count;
    ring_capacity = 16320;
    write_limit = 1024;
    assert(music_initialize(&player, title_data, title_size) == 0);
    assert(music_output_open(&output, &player, &api) == 0);
    assert(output.target_frames == MUSIC_RATE / 10);
    assert(music_output_service(&output) == 0 && queued == MUSIC_RATE / 10);
    unsigned int presentation_frames = MUSIC_RATE * 170 / 1000;
    assert(queued < presentation_frames);
    music_output_stop(&output);
    assert(music_initialize(&player, title_data, title_size) == 0);
    assert(music_output_open(&output, &player, &api) == 0);
    output.target_frames = MUSIC_RATE / 4;
    assert(music_output_service(&output) == 0 && music_output_service(&output) == 0);
    assert(queued == MUSIC_RATE / 4);
    for (unsigned int frame = 0; frame < 1000; ++frame) {
        assert(queued >= presentation_frames);
        queued -= presentation_frames;
        assert(music_output_service(&output) == 0);
        assert(queued == MUSIC_RATE / 4);
    }
    music_output_stop(&output);
    puts("PASS: title-only 250 ms queue survives 1000 slow 170 ms presentations without underrun; "
        "gameplay retains its 100 ms queue");
    static const unsigned char ramp[] = {128,130};
    assert(music_effects_initialize(&player) == 0);
    player.samples[0] = (MUSIC_SAMPLE){ramp,2,0,2,22050,64};
    player.voices[0].instrument = 1;
    player.voices[0].volume = 64;
    player.voices[0].period = 1712;
    player.voices[0].step = 32768;
    player.pan[0] = 128;
    player.tick_remaining = 100;
    reference = player;
    player.interpolate_samples = 1;
    assert(music_samples(&player, samples, 5) == 0);
    assert(music_samples(&reference, fragmented, 5) == 0);
    const short smooth[] = {0,64,128,64,0}, nearest[] = {0,0,128,128,0};
    for (unsigned int i = 0; i < 5; ++i) {
        assert(samples[i * 2] == smooth[i] && samples[i * 2 + 1] == smooth[i]);
        assert(fragmented[i * 2] == nearest[i] && fragmented[i * 2 + 1] == nearest[i]);
    }
    assert(player.voices[0].phase == reference.voices[0].phase);
    player.samples[0].loop_end = 0;
    player.voices[0].phase = 65536 + 32768;
    player.voices[0].period = 1712;
    assert(music_samples(&player, samples, 2) == 0);
    assert(samples[0] == 128 && samples[1] == 128 && samples[2] == 0 && samples[3] == 0);
    puts("PASS: title interpolation produces exact fractional PCM across loop/end boundaries; "
        "default gameplay/effect sampling remains unchanged");
    static const unsigned char positive[] = {228,228}, negative[] = {28,28};
    assert(music_effects_initialize(&player) == 0);
    player.samples[0] = (MUSIC_SAMPLE){positive,2,0,2,22050,64};
    player.samples[1] = (MUSIC_SAMPLE){negative,2,0,2,22050,64};
    player.orders[0][0] = 1;
    player.tracks[1][0].instrument = 2;
    player.voices[0].instrument = 1;
    player.voices[0].volume = 64;
    player.voices[0].period = 1712;
    player.voices[0].step = 65536;
    player.pan[0] = 128;
    player.tick_remaining = 1;
    player.smooth_transitions = 1;
    reference = player;
    reference.smooth_transitions = 0;
    assert(music_samples(&player, samples, 66) == 0);
    assert(music_samples(&reference, fragmented, 66) == 0);
    assert(samples[0] == 6400 && samples[2] == 6400);
    assert(fragmented[0] == 6400 && fragmented[2] == -6400);
    assert(samples[2 + 64 * 2] == -6400);
    for (unsigned int i = 1; i < 65; ++i)
        assert(samples[i * 2] - samples[(i + 1) * 2] == 200);
    assert(music_effects_initialize(&player) == 0);
    player.samples[0] = (MUSIC_SAMPLE){positive,1,0,0,22050,64};
    player.voices[0].instrument = 1;
    player.voices[0].volume = 64;
    player.voices[0].period = 1712;
    player.voices[0].step = 65536;
    player.pan[0] = 128;
    player.tick_remaining = 100;
    player.smooth_transitions = 1;
    assert(music_samples(&player, samples, 66) == 0);
    assert(samples[0] == 6400 && samples[2] == 6400 && samples[2 + 64 * 2] == 0);
    puts("PASS: instrument switches and sample ends use a 64-frame transition without discontinuities");
    unsigned int continue_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "CONTINUE.AMF",
        packed, sizeof(packed), data, sizeof(data), &dictionary, &continue_size) == 0);
    assert(music_initialize(&player, data, continue_size) == 0);
    reference = player;
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    for (unsigned int pos = 0; pos < MUSIC_RATE; pos += 147)
        assert(music_samples(&reference, fragmented + pos * 2, 147) == 0);
    assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
    unsigned long long continue_energy = 0;
    for (unsigned int i = 0; i < MUSIC_RATE * 2; ++i)
        continue_energy += samples[i] < 0 ? (unsigned int)-samples[i] : (unsigned int)samples[i];
    assert(continue_energy > 1000000);
    puts("PASS: original CONTINUE.AMF produces non-silent, chunk-invariant PCM");

    static const unsigned char slide_sample[] = {128, 129};
    static const struct {
        unsigned char effect, parameter;
        int first_delta, next_delta;
    } slides[] = {
        {0x84, 0xfd, 0, -12}, {0x84, 0x03, 0, 12},
        {0x84, 0x80, 0, 0}, {0x92, 0xfe, -8, 0},
        {0x92, 0x11, 4, 0}, {0x92, 0xf0, 0, 0}
    };
    for (unsigned int i = 0; i < sizeof(slides) / sizeof(slides[0]); ++i) {
        assert(music_effects_initialize(&player) == 0);
        player.samples[0] = (MUSIC_SAMPLE){slide_sample, 2, 0, 2, 8368, 64};
        player.orders[0][0] = 1;
        player.tracks[1][0] = (MUSIC_EVENT){60, 1, 0, slides[i].effect, slides[i].parameter};
        assert(music_samples(&player, samples, 1) == 0);
        assert(player.voices[0].period == (unsigned int)(856 + slides[i].first_delta));
        player.tick_remaining = 0;
        assert(music_samples(&player, samples, 1) == 0);
        assert(player.voices[0].period ==
            (unsigned int)(856 + slides[i].first_delta + slides[i].next_delta));
        assert(music_effects_initialize(&player) == 0);
        player.scaled_pitch_slides = 1;
        player.samples[0] = (MUSIC_SAMPLE){slide_sample, 2, 0, 2, 8368, 64};
        player.orders[0][0] = 1;
        player.tracks[1][0] = (MUSIC_EVENT){60, 1, 0, slides[i].effect, slides[i].parameter};
        assert(music_samples(&player, samples, 1) == 0);
        assert(player.voices[0].period == (unsigned int)(856 + slides[i].first_delta / 2));
        player.tick_remaining = 0;
        assert(music_samples(&player, samples, 1) == 0);
        assert(player.voices[0].period ==
            (unsigned int)(856 + (slides[i].first_delta + slides[i].next_delta) / 2));
    }
    assert(music_effects_initialize(&player) == 0);
    player.scaled_pitch_slides = 1;
    player.samples[0] = (MUSIC_SAMPLE){slide_sample, 2, 0, 2, 16726, 64};
    player.orders[0][0] = 1;
    player.tracks[1][0] = (MUSIC_EVENT){60, 1, 0, 0x84, 3};
    assert(music_samples(&player, samples, 1) == 0);
    player.tick_remaining = 0;
    assert(music_samples(&player, samples, 1) == 0 && player.voices[0].period == 868);
    puts("PASS: signed regular and fine slides retain legacy behavior and use sample-rate-scaled AMF units when enabled");

    static unsigned char level2_data[131072];
    unsigned int level2_size;
    assert(resources_load_entry(&api, "data/LIONKING.EPF", "LION2.AMF",
        packed, sizeof(packed), level2_data, sizeof(level2_data),
        &dictionary, &level2_size) == 0);
    assert(music_initialize(&player, level2_data, level2_size) == 0);
    player.sample_reference_period = 856;
    player.scaled_pitch_slides = 1;
    player.row = 12;
    assert(player.tracks[player.orders[0][1]][12].effect == 0x84 &&
        player.tracks[player.orders[0][1]][12].parameter == 0xfd);
    assert(music_samples(&player, samples, 1) == 0);
    assert(player.voices[1].period == 508);
    player.tick_remaining = 0;
    assert(music_samples(&player, samples, 1) == 0);
    assert(player.voices[1].period == 502);
    player.row = 13;
    player.tick = 0;
    player.tick_remaining = 0;
    assert(music_samples(&player, samples, 1) == 0);
    assert(player.voices[1].period == 504);
    puts("PASS: real LEVEL2 melody slide FD (-3) and following fine slide 01");
    assert(music_initialize(&player, level2_data, level2_size) == 0);
    player.sample_reference_period = 856;
    player.scaled_pitch_slides = 1;
    player.order = 13;
    player.row = 39;
    player.voices[0].instrument = 1;
    player.voices[0].period = 856;
    assert(player.tracks[player.orders[13][0]][39].effect == 0x86 &&
        player.tracks[player.orders[13][0]][39].parameter == 15);
    assert(music_samples(&player, samples, 1) == 0);
    assert(player.voices[0].period == 856 && player.voices[0].target_period == 428);
    player.tick_remaining = 0;
    assert(music_samples(&player, samples, 1) == 0 && player.voices[0].period == 826);
    player.row = 40;
    player.tick = 0;
    player.tick_remaining = 0;
    assert(player.tracks[player.orders[13][0]][40].effect == 0x86 &&
        player.tracks[player.orders[13][0]][40].parameter == 0);
    assert(music_samples(&player, samples, 1) == 0);
    player.tick_remaining = 0;
    assert(music_samples(&player, samples, 1) == 0 && player.voices[0].period == 796);
    puts("PASS: real LEVEL2 tone portamento uses scaled speed and continues with remembered parameter");
    assert(music_initialize(&player, level2_data, level2_size) == 0);
    reference = player;
    player.sample_reference_period = reference.sample_reference_period = 856;
    player.scaled_pitch_slides = reference.scaled_pitch_slides = 1;
    player.interpolate_samples = 1;
    unsigned long long level2_steps[2] = {0, 0};
    int last[2][2] = {{0}};
    seconds = 0;
    while (!player.loops && seconds < 180) {
        assert(music_samples(&player, samples, MUSIC_RATE) == 0);
        assert(music_samples(&reference, fragmented, MUSIC_RATE) == 0);
        for (unsigned int i = 0; i < MUSIC_RATE; ++i) {
            for (unsigned int ch = 0; ch < 2; ++ch) {
                int a = samples[i * 2 + ch] - last[0][ch];
                int b = fragmented[i * 2 + ch] - last[1][ch];
                level2_steps[0] += (unsigned long long)((long long)a * a);
                level2_steps[1] += (unsigned long long)((long long)b * b);
                last[0][ch] = samples[i * 2 + ch];
                last[1][ch] = fragmented[i * 2 + ch];
            }
        }
        assert(player.order == reference.order && player.row == reference.row &&
            player.tick == reference.tick && player.loops == reference.loops);
        ++seconds;
    }
    assert(player.loops == 1 && seconds == 108);
    assert(level2_steps[0] * 100 < level2_steps[1] * 75);
    assert(music_initialize(&player, level2_data, level2_size) == 0);
    player.sample_reference_period = 856;
    player.scaled_pitch_slides = 1;
    player.interpolate_samples = 1;
    reference = player;
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    for (unsigned int pos = 0; pos < MUSIC_RATE;) {
        unsigned int count = MUSIC_RATE - pos;
        if (count > 137) count = 137;
        assert(music_samples(&reference, fragmented + pos * 2, count) == 0);
        pos += count;
    }
    assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
    printf("PASS: full LEVEL2 loop (%u seconds) retains timing; interpolation reduces "
        "squared adjacent-sample steps by %llu%% and is chunk invariant\n",
        seconds, 100 - level2_steps[0] * 100 / level2_steps[1]);
    assert(music_initialize(&player, level2_data, level2_size) == 0);
    player.sample_reference_period = 856;
    player.scaled_pitch_slides = 1;
    player.interpolate_samples = 1;
    player.smooth_transitions = 1;
    reference = player;
    reference.smooth_transitions = 0;
    unsigned long long boundary_energy[2] = {0, 0};
    int previous[2][2] = {{0}};
    while (!player.loops) {
        assert(music_samples(&player, samples, 1) == 0);
        assert(music_samples(&reference, fragmented, 1) == 0);
        for (unsigned int ch = 0; ch < 2; ++ch) {
            int a = samples[ch] - previous[0][ch];
            int b = fragmented[ch] - previous[1][ch];
            boundary_energy[0] += (unsigned long long)((long long)a * a);
            boundary_energy[1] += (unsigned long long)((long long)b * b);
        }
        unsigned int count = player.tick_remaining;
        assert(count && count <= MUSIC_RATE && count == reference.tick_remaining);
        assert(music_samples(&player, samples, count) == 0);
        assert(music_samples(&reference, fragmented, count) == 0);
        for (unsigned int ch = 0; ch < 2; ++ch) {
            previous[0][ch] = samples[(count - 1) * 2 + ch];
            previous[1][ch] = fragmented[(count - 1) * 2 + ch];
        }
        assert(player.order == reference.order && player.row == reference.row &&
            player.tick == reference.tick && player.loops == reference.loops);
    }
    assert(boundary_energy[0] * 100 < boundary_energy[1] * 80);
    printf("PASS: LEVEL2 tick-boundary step energy reduced by %llu%% over the full loop\n",
        100 - boundary_energy[0] * 100 / boundary_energy[1]);
    assert(music_initialize(&player, level2_data, level2_size) == 0);
    player.sample_reference_period = 856;
    player.scaled_pitch_slides = 1;
    player.interpolate_samples = player.smooth_transitions = 1;
    reference = player;
    assert(music_samples(&player, samples, MUSIC_RATE) == 0);
    for (unsigned int pos = 0; pos < MUSIC_RATE;) {
        unsigned int count = MUSIC_RATE - pos;
        if (count > 137) count = 137;
        assert(music_samples(&reference, fragmented + pos * 2, count) == 0);
        pos += count;
    }
    assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
    puts("PASS: LEVEL2 transition smoothing is chunk invariant");
    return 0;
}
