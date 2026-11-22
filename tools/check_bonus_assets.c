#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "dos64/platform.h"
#include "engine/music.h"
#include "engine/bonus.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "libs/vga.h"

static unsigned char packed[85438], decoded[364360], pixels[LK_WIDTH * LK_HEIGHT];
static RESOURCE_DICTIONARY dictionary;
static MUSIC_PLAYER music, reference;
static BONUS_ASSETS assets;
static short samples[MUSIC_RATE * 2], fragmented[MUSIC_RATE * 2];
static unsigned int diagnostics;
static unsigned int opens, fail_open, open_handles;

static void __attribute__((ms_abi)) report(const char *text)
{
    ++diagnostics;
    fputs(text, stderr);
}

static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    if (++opens == fail_open) return 0;
    FILE *file = fopen(path, mode);
    if (file) ++open_handles;
    return file;
}

static int __attribute__((ms_abi)) close_file(void *file)
{
    assert(open_handles);
    --open_handles;
    return fclose(file);
}
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int origin)
{
    return fseek(file, (long)offset, origin);
}
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    return fread(buffer, (size_t)size, (size_t)count, file);
}

static unsigned int load(const DOS64_API *api, const char *name)
{
    unsigned int length = 0;
    assert(resources_load_entry(api, "data/LIONKING.EPF", name, packed,
        sizeof(packed), decoded, sizeof(decoded), &dictionary, &length) == 0);
    assert(length > 0);
    return length;
}

static void check_note_delay(unsigned char delay, unsigned int trigger_tick)
{
    static const unsigned char sample[] = {128, 200, 80, 128};
    assert(music_effects_initialize(&music) == 0);
    music.order_count = 1;
    music.orders[0][0] = 1;
    music.samples[0] = (MUSIC_SAMPLE){sample, sizeof(sample), 0, sizeof(sample), 8363, 32};
    music.tracks[1][0] = (MUSIC_EVENT){48, 1, 21, 0x93, delay};
    for (unsigned int tick = 0; tick < 6; ++tick) {
        assert(music_samples(&music, samples, 882) == 0);
        if (tick >= trigger_tick) {
            assert(music.voices[0].instrument == 1 && music.voices[0].period > 0);
            assert(music.voices[0].volume == 20);
        } else {
            assert(music.voices[0].instrument == 0 && music.voices[0].period == 0);
        }
    }
    assert(music_samples(&music, samples, 882) == 0);
    if (trigger_tick >= 6)
        assert(music.voices[0].instrument == 0 && music.voices[0].period == 0);
}

static void check_delayed_retrigger(void)
{
    static const unsigned char sample[] = {128, 200, 80, 128};
    assert(music_effects_initialize(&music) == 0);
    music.order_count = 1;
    music.orders[0][0] = 1;
    music.samples[0] = (MUSIC_SAMPLE){sample, sizeof(sample), 0, sizeof(sample), 8363, 32};
    music.voices[0].instrument = 1;
    music.voices[0].period = 2000;
    music.voices[0].volume = 10;
    music.tracks[1][0] = (MUSIC_EVENT){48, 1, 21, 0x93, 4};
    for (unsigned int tick = 0; tick < 4; ++tick) {
        assert(music_samples(&music, samples, 882) == 0);
        assert(music.voices[0].period == 2000 && music.voices[0].volume == 10);
    }
    assert(music_samples(&music, samples, 1) == 0);
    assert(music.voices[0].period == 1712 && music.voices[0].volume == 20);
}

int main(void)
{
    DOS64_API api = {0};
    api.Write = report;
    api.Fs.Open = open_file;
    api.Fs.Close = close_file;
    api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file;
    api.Fs.Read = read_file;

    assert(bonus_assets_load(&assets, &api, "data/LIONKING.EPF", packed,
        sizeof(packed), &dictionary) == 0);
    assert(assets.loaded && assets.map_size && assets.timon_size && assets.timon_walk_size &&
        assets.pumbaa_size && assets.pumbaa_burp_size && assets.bugs_size &&
        assets.destiny_size && assets.circle_size && assets.meat_size &&
        assets.burp_sound_size && assets.collect_sound_size && assets.hunt_music_size &&
        assets.toss_music_size);
    assert(bonus_assets_load(&assets, &api, "data/LIONKING.EPF", packed, 1,
        &dictionary) == -1 && !assets.loaded && diagnostics > 0);
    diagnostics = 0;
    assert(bonus_assets_load(&assets, &api, 0, packed, sizeof(packed),
        &dictionary) == -1 && !assets.loaded && diagnostics > 0);
    diagnostics = 0;
    assert(bonus_assets_load(&assets, &api, "data/missing-bonus-archive.epf",
        packed, sizeof(packed), &dictionary) == -1 && !assets.loaded &&
        diagnostics > 0 && !open_handles);
    diagnostics = 0;
    fail_open = opens + 5;
    assert(bonus_assets_load(&assets, &api, "data/LIONKING.EPF", packed,
        sizeof(packed), &dictionary) == -1 && !assets.loaded &&
        diagnostics > 0 && !open_handles);
    fail_open = 0;
    diagnostics = 0;
    assert(bonus_assets_load(&assets, &api, "data/LIONKING.EPF", packed,
        sizeof(packed), &dictionary) == 0 && assets.loaded);
    puts("PASS: bonus loader handles all resources, failure and retry");

    unsigned int length = load(&api, "BONUS.MAP");
    assert(length == assets.map_size && memcmp(decoded, assets.map, length) == 0);
    DOS64_COLOR colors[256];
    assert(vga_load_palette(decoded, length, colors) == 0);
    for (unsigned int layer = 0; layer < 6; ++layer) {
        assert(render_map_tile_pass(decoded, length, layer, 0, layer >= 4 ? 8 : 0,
            0, pixels) == 0);
        assert(render_map_tile_pass(decoded, length, layer, 0, layer >= 4 ? 8 : 0,
            1, pixels) == 0);
    }
    printf("PASS: BONUS.MAP decoded (%u bytes), palette and stage layers rendered\n", length);

    const char *const sprites[] = {"TMBUGTOS.MCH", "PUMBAA.MCH", "BUGS.MCH",
        "PUMBBURP.MCH", "DESTINY.MCH", "CIRCLE.MCH", "PMEAT.MCH"};
    for (unsigned int i = 0; i < sizeof(sprites) / sizeof(*sprites); ++i) {
        length = load(&api, sprites[i]);
        const unsigned char *expected = i == 0 ? assets.timon :
            i == 1 ? assets.pumbaa : i == 2 ? assets.bugs :
            i == 3 ? assets.pumbaa_burp : i == 4 ? assets.destiny :
            i == 5 ? assets.circle : assets.meat;
        unsigned int expected_size = i == 0 ? assets.timon_size :
            i == 1 ? assets.pumbaa_size : i == 2 ? assets.bugs_size :
            i == 3 ? assets.pumbaa_burp_size : i == 4 ? assets.destiny_size :
            i == 5 ? assets.circle_size : assets.meat_size;
        assert(length == expected_size && memcmp(decoded, expected, length) == 0);
        assert(length >= 2);
        unsigned int frames = (unsigned int)decoded[0] | (unsigned int)decoded[1] << 8;
        assert(frames && frames <= 0x2000);
        for (unsigned int frame = 0; frame < frames; ++frame) {
            memset(pixels, 0, sizeof(pixels));
            assert(render_draw_sprite(decoded, length, (unsigned short)frame, 0, 0, pixels) == 0);
        }
        printf("PASS: %s decoded (%u bytes), %u frames rendered\n", sprites[i], length, frames);
    }
    length = load(&api, "TMWKWAIT.MCH");
    assert(length == assets.timon_walk_size && memcmp(decoded, assets.timon_walk, length) == 0);
    assert((decoded[0] | (unsigned int)decoded[1] << 8) == 16);
    for (unsigned int frame = 0; frame < 16; ++frame)
        assert(render_draw_sprite(decoded, length, (unsigned short)frame, 0, 0, pixels) == 0);
    puts("PASS: TMWKWAIT.MCH decoded and all 16 frames rendered");
    length = load(&api, "BURP");
    assert(length == assets.burp_sound_size && memcmp(decoded, assets.burp_sound, length) == 0);
    assert(music_effects_initialize(&music) == 0);
    assert(music_effect_play(&music, 0, assets.burp_sound, assets.burp_sound_size) == 0);
    assert(music_samples(&music, samples, MUSIC_RATE / 10) == 0);
    unsigned long long effect_energy = 0;
    for (unsigned int i = 0; i < MUSIC_RATE / 5; ++i)
        effect_energy += samples[i] < 0 ? (unsigned int)-(int)samples[i] : (unsigned int)samples[i];
    assert(effect_energy > 0);
    puts("PASS: original BURP sample produces PCM");

    length = load(&api, "COLLECT1");
    assert(length == assets.collect_sound_size &&
        memcmp(decoded, assets.collect_sound, length) == 0);
    assert(music_effects_initialize(&music) == 0);
    assert(music_effect_play(&music, 0, assets.collect_sound,
        assets.collect_sound_size) == 0);
    assert(music_samples(&music, samples, MUSIC_RATE / 10) == 0);
    effect_energy = 0;
    for (unsigned int i = 0; i < MUSIC_RATE / 5; ++i)
        effect_energy += samples[i] < 0 ? (unsigned int)-(int)samples[i] : (unsigned int)samples[i];
    assert(effect_energy > 0);
    puts("PASS: original COLLECT1 sample produces PCM");

    const char *const tracks[] = {"BUGHUNT.AMF", "BUGTOSS.AMF"};
    for (unsigned int i = 0; i < sizeof(tracks) / sizeof(*tracks); ++i) {
        length = load(&api, tracks[i]);
        assert(length == (i ? assets.toss_music_size : assets.hunt_music_size));
        assert(memcmp(decoded, i ? assets.toss_music : assets.hunt_music, length) == 0);
        int result = music_initialize(&music, decoded, length);
        assert(result == 0);
        printf("PASS: %s decoded and accepted (%u bytes)\n", tracks[i], length);
        printf("  AMF version=%u instruments=%u orders=%u tracks=%u channels=%u\n",
            decoded[3], decoded[36], decoded[37],
            (unsigned int)decoded[38] | (unsigned int)decoded[39] << 8, decoded[40]);
        {
            if (i == 1) {
                assert(music.tracks[8][43].effect == 0x93);
                assert(music.tracks[8][43].parameter == 4);
            }
            reference = music;
            assert(music_samples(&music, samples, MUSIC_RATE) == 0);
            for (unsigned int position = 0; position < MUSIC_RATE;) {
                unsigned int count = MUSIC_RATE - position;
                if (count > 137) count = 137;
                assert(music_samples(&reference, fragmented + position * 2, count) == 0);
                position += count;
            }
            assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
            unsigned long long energy = 0;
            for (unsigned int sample = 0; sample < MUSIC_RATE * 2; ++sample)
                energy += samples[sample] < 0 ? (unsigned int)-(int)samples[sample] :
                    (unsigned int)samples[sample];
            assert(energy > 0);
            printf("PASS: %s produces non-silent, chunk-invariant PCM (energy %llu)\n",
                tracks[i], energy);
            unsigned int seconds = 1;
            while (!music.loops && seconds < 120) {
                assert(music_samples(&music, samples, MUSIC_RATE) == 0);
                for (unsigned int position = 0; position < MUSIC_RATE;) {
                    unsigned int count = MUSIC_RATE - position;
                    if (count > 137) count = 137;
                    assert(music_samples(&reference, fragmented + position * 2, count) == 0);
                    position += count;
                }
                assert(memcmp(samples, fragmented, sizeof(samples)) == 0);
                ++seconds;
            }
            assert(music.loops > 0 && music.loops == reference.loops);
            printf("PASS: %s completes a song loop in %u seconds\n", tracks[i], seconds);
            assert(music_initialize(&music, decoded, length - 1) == -1);
        }
    }
    check_note_delay(0, 0);
    check_note_delay(4, 4);
    check_note_delay(6, 6);
    check_note_delay(0x14, 4);
    check_delayed_retrigger();
    puts("PASS: note delay triggers on the requested tick, or not at all beyond row speed");
    assert(diagnostics == 0);
    return 0;
}
