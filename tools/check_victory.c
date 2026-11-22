#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "mock_layers.h"
#include "dos64/platform.h"
#include "dos64/frontend.h"
#include "engine/enemies.h"
#include "engine/music.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "libs/vga.h"

int __attribute__((ms_abi)) start(const DOS64_API *api);
int __real_engine_enemies_tick(ENGINE_ENEMIES *enemies, RENDER_OWNER camera);

static DOS64_API api;
static FILE *log_file;
static unsigned long long now, reward_begin;
static unsigned int polls, game_ticks, completions, scenes, speech_events, finished;
static unsigned int reward_frames, seen_frames, audio_opens, audio_stops;
static int reward_phase, audio_live, reward_audio, skip, muted, missing, audio_failure;
static int missing_notice, notice_phase;
static int notice_escape, notice_space;
static unsigned int notice_frames, notice_polls, notices, notice_returns;
static int error_logged, skipped, terminal;
static int menu_mode, in_menu;
static unsigned int menu_visits, menu_returns;
static unsigned char packed[85438], map[131072], art[65536], speech[65536], notice_font[8192];
static unsigned char expected_background[64000], expected_pixels[64000];
static unsigned char expected_notice[64000];
static DOS64_COLOR palette[256];
static RESOURCE_DICTIONARY dictionary;
static unsigned int art_size, speech_size;
static MUSIC_PLAYER reference;
static short expected_audio[2048];

/* Inject only the controller input; the real boss/death path is tested by check_enemies. */
int __wrap_engine_enemies_tick(ENGINE_ENEMIES *enemies, RENDER_OWNER camera)
{
    int result = __real_engine_enemies_tick(enemies, camera);
    if (!result && ++game_ticks == 60) enemies->hyenas_defeated = 1;
    return result;
}

static unsigned int reward_ticks(void)
{
    return (unsigned int)((now - reward_begin) * 1193182ULL /
        (23660ULL * 1000000000ULL));
}

static void record(const char *text)
{
    if (strstr(text, "Main menu: ready.")) {
        in_menu = 1;
        ++menu_visits;
    }
    if (strstr(text, "Main menu: start LEVEL1.")) in_menu = 0;
    if (strstr(text, "Main menu: returning from LEVEL1.")) {
        assert(finished == 1 && !audio_live);
        ++menu_returns;
    }
    if (strstr(text, "original level-completion condition reached.")) {
        assert(!terminal && game_ticks == 60);
        terminal = 1;
        ++completions;
    }
    if (strstr(text, "Victory: original LEVEL1")) {
        assert(!reward_phase && !scenes && (muted || terminal));
        reward_phase = 1;
        reward_begin = now;
        ++scenes;
    }
    if (strstr(text, "Victory: SPEECH1")) {
        assert(reward_phase && reward_ticks() == 19 && !speech_events);
        ++speech_events;
        if (!muted) {
            assert(music_effect_play(&reference, 0, speech, speech_size) == 0);
            assert(music_effect_play(&reference, 1, speech, speech_size) == 0);
        }
    }
    if (strstr(text, "Victory: Rafiki scene skipped")) {
        assert(skip && reward_ticks() >= 30 && reward_ticks() < 475);
        skipped = 1;
    }
    if (strstr(text, "Victory: reward scene finished")) {
        assert(reward_phase && (skip ? skipped : reward_ticks() == 475));
        ++finished;
        reward_phase = 0;
    }
    if (strstr(text, "Transition: LEVEL2 is not available")) {
        assert(finished == 1 && !audio_live && !notice_phase);
        notice_phase = 1;
        ++notices;
    }
    if (strstr(text, "Transition: returning without starting LEVEL2")) {
        assert(notice_phase && notice_frames == 1 && notice_polls >= 2);
        notice_phase = 0;
        ++notice_returns;
    }
    if (strstr(text, "cannot load original LEVEL1 Rafiki") ||
        strstr(text, "reward speech requires usable") ||
        strstr(text, "cannot load next-level notice font")) error_logged = 1;
}

static void __attribute__((ms_abi)) console(const char *text)
{
    fputs(text, stderr);
    assert(!"unexpected console output");
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    if (!strcmp(path, "LIONKING.LOG")) {
        assert(!log_file);
        return log_file = tmpfile();
    }
    assert(!strcmp(path, "LIONKING.EPF"));
    if ((terminal && missing) || (finished && missing_notice)) return 0;
    return fopen("data/LIONKING.EPF", mode);
}
static int __attribute__((ms_abi)) close_file(void *file)
{
    if (file == log_file) log_file = 0;
    return fclose(file);
}
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int origin)
{ return fseek(file, (long)offset, origin); }
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{ return fread(buffer, (size_t)size, (size_t)count, file); }
static unsigned long long __attribute__((ms_abi)) write_file(const void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    assert(file == log_file && size == 1);
    record(buffer);
    return fwrite(buffer, (size_t)size, (size_t)count, file);
}
static void __attribute__((ms_abi)) sleep_ms(unsigned int ms) { (void)ms; assert(0); }
static unsigned long long __attribute__((ms_abi)) time_ns(void) { return now; }
static int __attribute__((ms_abi)) select_layer(int layer) { assert(layer == 0); return 0; }
static void __attribute__((ms_abi)) set_color(DOS64_COLOR color) { (void)color; }
static void __attribute__((ms_abi)) clear(void) {}
static void __attribute__((ms_abi)) present(void) {}
static void __attribute__((ms_abi)) poll(void)
{
    now += 10000000ULL;
    assert(++polls < 4000);
    memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
    memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
    if (reward_phase && skip && reward_ticks() >= 30)
        api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
    if (notice_phase) {
        ++notice_polls;
        if (skip && notice_polls == 1)
            api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
        if (notice_polls == (skip ? 3U : 2U)) {
            unsigned int key = notice_escape ? 0x29 : notice_space ? 0x2c : 0x28;
            api.Input.KeyDown[key] = api.Input.KeyPressed[key] = 1;
        }
    }
    if (menu_mode && in_menu) {
        unsigned int key = menu_visits == 1 ? 0x28 : 0x29;
        api.Input.KeyDown[key] = api.Input.KeyPressed[key] = 1;
    }
}

static unsigned int frame_at(unsigned int ticks)
{
    static const unsigned char durations[] = {
        4,2,2,4,6,4,4,4,8,6,8,8,8,20,8,10,28,21,8,8,101,101,101
    };
    static const unsigned char frames[] = {
        0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,16,15,14,13,13,13
    };
    if (!ticks) return 0;
    --ticks;
    for (unsigned int i = 0; i < sizeof(durations); ++i) {
        if (ticks < durations[i]) return frames[i];
        ticks -= durations[i];
    }
    assert(ticks == 0);
    return 13;
}

static void __attribute__((ms_abi)) draw(const DOS64_COLOR *image, unsigned int width,
    unsigned int height, unsigned int stride, int x, int y, unsigned int dw, unsigned int dh)
{
    if (height == 5 && stride == 60) {
        assert(width <= 60 && x == (int)(640 - (width + 4) * 2) &&
            y == 422 && dw == width * 2 && dh == 10);
        return;
    }
    if (width == 1 && height == 1) {
        assert(image[0] == 0xff000000U && x == 0 && y == 0 && dw == 640 && dh == 480);
        return;
    }
    assert(width == 320 && height == 200 && stride == 320 &&
        x == 0 && y == 40 && dw == 640 && dh == 400);
    if (notice_phase) {
        for (unsigned int i = 0; i < 64000; ++i)
            assert(image[i] == (palette[expected_notice[i]] | 0xff000000U));
        ++notice_frames;
        return;
    }
    if (!reward_phase) return;
    unsigned int ticks = reward_ticks(), frame = frame_at(ticks);
    unsigned int backdrop = ticks ? 17 + ((ticks - 1) / 8) % 5 : 17;
    memcpy(expected_pixels, expected_background, sizeof(expected_pixels));
    assert(render_draw_sprite(art, art_size, (unsigned short)backdrop,
        142 - 64, 163 - 120, expected_pixels) == 0);
    assert(render_draw_sprite(art, art_size, (unsigned short)frame,
        142 - 64, 162 - 120, expected_pixels) == 0);
    for (unsigned int i = 0; i < 64000; ++i) {
        if (image[i] != (palette[expected_pixels[i]] | 0xff000000U))
            fprintf(stderr, "reward tick %u frame %u backdrop %u pixel %u: %x != %x\n",
                ticks, frame, backdrop, i, image[i], palette[expected_pixels[i]] | 0xff000000U);
        assert(image[i] == (palette[expected_pixels[i]] | 0xff000000U));
    }
    seen_frames |= (1U << frame) | (1U << backdrop);
    ++reward_frames;
}

static int __attribute__((ms_abi)) audio_open(unsigned int rate)
{
    assert(rate == MUSIC_RATE && !audio_live && !muted);
    reward_audio = terminal && !finished;
    if (reward_audio && audio_failure) return -1;
    assert(!reward_audio || audio_stops == (menu_mode ? 3U : 1U));
    audio_live = 1;
    if (reward_audio) assert(music_effects_initialize(&reference) == 0);
    ++audio_opens;
    return 0;
}
static unsigned long long __attribute__((ms_abi)) queued(void) { return 0; }
static unsigned long long __attribute__((ms_abi)) free_frames(void) { return 1024; }
static unsigned long long __attribute__((ms_abi)) audio_write(const short *samples,
    unsigned long long count)
{
    assert(audio_live && count <= 1024);
    if (reward_audio) {
        assert(music_samples(&reference, expected_audio, (unsigned int)count) == 0);
        assert(memcmp(samples, expected_audio, (size_t)count * 4) == 0);
    }
    return count;
}
static void __attribute__((ms_abi)) audio_stop(void)
{ assert(audio_live); audio_live = 0; ++audio_stops; }

int main(int argc, char **argv)
{
    assert(argc == 1 || argc == 2);
    if (argc == 2) {
        skip = !strcmp(argv[1], "--skip");
        muted = !strcmp(argv[1], "--muted");
        missing = !strcmp(argv[1], "--missing");
        audio_failure = !strcmp(argv[1], "--audio-failure");
        missing_notice = !strcmp(argv[1], "--missing-notice");
        notice_escape = !strcmp(argv[1], "--notice-escape");
        notice_space = !strcmp(argv[1], "--notice-space");
        menu_mode = !strcmp(argv[1], "--menu");
        assert(skip || muted || missing || audio_failure || missing_notice ||
            notice_escape || notice_space || menu_mode);
    }
    api.Size = sizeof(api); api.Version = DOS64_API_VERSION; api.Arguments = "--map";
    if (menu_mode) api.Arguments = "";
    api.Write = console; api.Sleep = sleep_ms; api.Time.Nanoseconds = time_ns;
    api.Input.Poll = poll; api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SetColor = set_color; api.Gfx.Clear = clear;
    api.Gfx.SelectLayer = select_layer; api.Gfx.Present = present; api.DrawImage = draw;
    mock_install_layers(&api);
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file; api.Fs.Write = write_file;
    api.Audio.Present = 1; api.Audio.Open = audio_open; api.Audio.Write = audio_write;
    api.Audio.FreeFrames = free_frames; api.Audio.QueuedFrames = queued; api.Audio.Stop = audio_stop;
    unsigned int size;
    assert(resources_load_entry(&api, "LIONKING.EPF", "TITLES.MAP", packed,
        sizeof(packed), map, sizeof(map), &dictionary, &size) == 0);
    assert(vga_load_palette(map, size, palette) == 0);
    for (int layer = 1; layer >= 0; --layer) {
        assert(render_map_tile_pass(map, size, (unsigned int)layer, 0, 0, 0, expected_background) == 0);
        assert(render_map_tile_pass(map, size, (unsigned int)layer, 0, 0, 1, expected_background) == 0);
    }
    unsigned int font_size;
    assert(resources_load_entry(&api, "LIONKING.EPF", "F8X8_S.MCH", packed,
        sizeof(packed), notice_font, sizeof(notice_font), &dictionary, &font_size) == 0);
    memcpy(expected_notice, expected_background, sizeof(expected_notice));
    const char *lines[] = {"LEVEL 2 NOT AVAILABLE", "ENTER SPACE OR ESC"};
    for (unsigned int row = 0; row < 2; ++row)
        for (unsigned int column = 0; lines[row][column]; ++column)
            assert(render_draw_sprite(notice_font, font_size,
                (unsigned short)(lines[row][column] - 32),
                (int)((row ? 88U : 76U) + column * 8U),
                (int)(row ? 110 : 90), expected_notice) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "RWDLVL1.MCH", packed,
        sizeof(packed), art, sizeof(art), &dictionary, &art_size) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "SPEECH1", packed,
        sizeof(packed), speech, sizeof(speech), &dictionary, &speech_size) == 0);
    int result;
    if (muted) {
        assert(lk_platform_init(&api) == 0);
        result = lk_platform_finish(frontend_victory(&api, &api, 0) != 0);
    } else result = start(&api);
    assert(!log_file && !audio_live && (muted || completions == 1));
    if (missing || audio_failure) {
        assert(result == 1 && error_logged && !scenes && !finished &&
            audio_opens == 1 && audio_stops == 1);
        puts("PASS: reward resource/audio failure is explicit; gameplay audio and log close cleanly");
    } else if (missing_notice) {
        assert(result == 1 && error_logged && scenes == 1 && finished == 1 &&
            !notices && !notice_returns && audio_opens == 2 && audio_stops == 2);
        puts("PASS: missing next-level notice font reports failure after closing reward audio");
    } else {
        assert(result == 0 && scenes == 1 && finished == 1 && speech_events == 1);
        assert(audio_opens == (muted ? 0U : menu_mode ? 5U : 2U) && audio_stops == audio_opens);
        assert(reward_frames > (skip ? 30U : 900U));
        if (!skip) assert(seen_frames == 0x3fffff);
        puts("PASS: Rafiki reward has exact original background/frame pixels, speech at tick 19, "
            "no audio overlap and clean exit");
        if (!skip) puts("PASS: all 22 RWDLVL1 frames and original terminal tick 475");
        if (!muted) puts("PASS: original LEVEL1 controller enters reward exactly once; exact two-channel SPEECH1 PCM");
        if (skip) puts("PASS: Escape skips reward and closes its audio stream");
        if (muted) puts("PASS: muted reward preserves animation timing without opening audio");
        if (!muted) {
            assert(notices == 1 && notice_returns == 1 && notice_frames == 1);
            puts("PASS: LEVEL2 unavailable notice waits for a new key and does not start LEVEL2");
        }
        if (menu_mode) {
            assert(menu_visits == 2 && menu_returns == 1);
            puts("PASS: menu Start -> Timon -> LEVEL1 completion -> Rafiki -> menu -> exit; five nonoverlapping audio streams");
        }
    }
    return 0;
}
