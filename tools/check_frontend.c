#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dos64_api.h"
#include "mock_layers.h"
#include "engine/resources.h"
#include "engine/tiles.h"
#include "engine/sprites.h"
#include "libs/vga.h"
#include "engine/animation_data.h"
#include "engine/timing.h"
#include "engine/music.h"

int __attribute__((ms_abi)) start(const DOS64_API *api);
static DOS64_API api;
static unsigned int polls, menu_visits, menu_step, scene_polls, restart_poll;
static unsigned int draws, loading_frames, clears, audio_opens, audio_stops;
static unsigned int deaths, restarts, muted_requests, returns;
static unsigned int death_scenes;
static unsigned long long now, audio_frames;
static int in_menu, in_scene, missing_title, error_logged;
static FILE *log_file;
static int splash_phase, skip_splash;
static unsigned int splash_polls, splash_frames;
static unsigned char expected_splash[2][64000], expected_title[64000];
static unsigned char expected_loading[64000];
static DOS64_COLOR splash_colors[256], title_colors[256];
static DOS64_COLOR level_colors[256];
static int intro_phase;
static unsigned int intro_frames;
static unsigned char intro_art[16384], intro_pixels[64000];
static unsigned int intro_size, intro_ticks, intro_index;
static int intro_remaining;
static ENGINE_CLOCK intro_clock;
static unsigned int seen_intro_frames;
static int skipped_intro;
static unsigned int intro_runs, finished_intros;
static unsigned long long loading_hold_start;
static int pregame_phase, level_title_visible;
static unsigned int pregame_runs, finished_pregames, speech_requests, title_completions;
static unsigned int pregame_ticks, seen_pregame_frames, level_title_frames, moving_title_frames;
static ENGINE_CLOCK pregame_clock;
static unsigned char pregame_art[65536], pregame_pixels[64000];
static unsigned int pregame_size;
static DOS64_COLOR initial_game[64000];
static MUSIC_PLAYER title_reference;
static unsigned char title_module[88301], title_source[85438], selector_art[4096];
static unsigned int selector_size;
static short expected_audio[2048];
static int audio_live, audio_kind;
static unsigned long long title_audio_frames, disney_audio_frames;
static ENGINE_CLOCK selector_clock;
static int selector_x, selector_remaining, selector_right;
static unsigned int selector_selected, selector_wait, selector_positions;

static void record(const char *text)
{
    if (strstr(text, "original SYDIE lost-life scene")) ++death_scenes;
    if (strstr(text, "Lion King:")) fputs(text, stderr);
    if (strstr(text, "Intro: original Rafiki")) {
        assert(!menu_visits && !intro_runs && !in_scene);
        ++intro_runs;
        splash_phase = 0;
        intro_phase = 1;
        engine_clock_reset(&intro_clock, now);
        intro_ticks = 0;
        intro_index = 15;
        intro_remaining = 30;
        skipped_intro = 0;
    }
    if (strstr(text, "Intro: finished before main menu.")) {
        assert(intro_phase && intro_ticks >= 120 && (skip_splash ?
            skipped_intro && intro_ticks < 360 : intro_ticks >= 358));
        ++finished_intros;
        intro_phase = 0;
    }
    if (strstr(text, "Pre-game: original Timon")) {
        assert(menu_visits == pregame_runs + 1 && in_scene && finished_intros == 1);
        ++pregame_runs;
        pregame_phase = 1;
        pregame_ticks = 0;
        engine_clock_reset(&pregame_clock, now);
    }
    if (strstr(text, "Pre-game: SPEECH5")) {
        assert(pregame_phase && pregame_ticks >= 49 && pregame_ticks <= 50);
        ++speech_requests;
    }
    if (strstr(text, "Pre-game: finished")) {
        assert(pregame_phase && pregame_ticks == 130);
        ++finished_pregames;
        pregame_phase = 0;
        scene_polls = 0;
        restart_poll = polls;
    }
    if (strstr(text, "Splash: Disney and Virgin.")) {
        assert(audio_live && audio_kind == 1);
        splash_phase = 1;
        splash_polls = 0;
    }
    if (strstr(text, "Splash: East Point Software.")) {
        splash_phase = 2;
        splash_polls = 0;
    }
    if (strstr(text, "Main menu: ready.")) {
        ++menu_visits;
        in_menu = 1;
        in_scene = 0;
        menu_step = 0;
        selector_wait = 0;
        selector_selected = 0;
        selector_x = 82;
        selector_remaining = 10;
        selector_right = 0;
        engine_clock_reset(&selector_clock, now);
        splash_phase = 0;
        intro_phase = 0;
        assert(finished_intros == 1 && finished_pregames == menu_visits - 1);
    }
    if (strstr(text, "Main menu: start LEVEL1.")) {
        assert(!audio_live);
        in_menu = 0;
        in_scene = 1;
        scene_polls = 0;
        restart_poll = polls;
    }
    if (strstr(text, "Loading: LEVEL1 assets ready")) {
        assert(!intro_phase && !pregame_phase && finished_pregames == menu_visits);
        level_title_visible = 1;
        loading_hold_start = now;
        scene_polls = 0;
        restart_poll = polls;
    }
    if (strstr(text, "level name removed after 100 gameplay ticks")) {
        assert(level_title_visible &&
            now - loading_hold_start >= 100ULL * 23660 * 1000000000 / 1193182);
        level_title_visible = 0;
        ++title_completions;
    }
    if (strstr(text, "Main menu: returning from LEVEL1.")) {
        ++returns;
        in_scene = 0;
    }
    if (strstr(text, "sound muted.")) ++muted_requests;
    if (strstr(text, "restarted at the saved checkpoint.")) {
        ++restarts;
        restart_poll = polls;
    }
    if (strstr(text, "cannot load original title")) error_logged = 1;
}

static void __attribute__((ms_abi)) console(const char *text)
{
    fprintf(stderr, "%s", text);
    assert(!"unexpected console error");
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    if (!strcmp(path, "LIONKING.LOG")) {
        assert(!log_file);
        return log_file = tmpfile();
    }
    assert(!strcmp(path, "LIONKING.EPF"));
    return missing_title ? 0 : fopen("data/LIONKING.EPF", mode);
}
static int __attribute__((ms_abi)) close_file(void *file)
{
    if (file == log_file) {
        char contents[32768];
        assert(fseek(file, 0, SEEK_SET) == 0);
        size_t count = fread(contents, 1, sizeof(contents) - 1, file);
        assert(count < sizeof(contents) - 1);
        contents[count] = 0;
        const char *cursor = contents;
        while ((cursor = strstr(cursor, "Player deaths: "))) {
            unsigned int value;
            assert(sscanf(cursor + strlen("Player deaths: "), "%u", &value) == 1);
            deaths += value;
            cursor += strlen("Player deaths: ");
        }
        log_file = 0;
    }
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
static DOS64_COLOR clear_color;
static void __attribute__((ms_abi)) set_color(DOS64_COLOR color) { clear_color = color; }
static void __attribute__((ms_abi)) clear(void)
{
    assert(clear_color == 0xff000000U);
    ++clears;
}
static void __attribute__((ms_abi)) present(void) {}
static void __attribute__((ms_abi)) poll(void)
{
    now += 10000000ULL;
    memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
    memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
    assert(++polls < 20000);
    if (splash_phase) {
        if (skip_splash && !splash_polls)
            api.Input.KeyDown[0x28] = api.Input.KeyPressed[0x28] = 1;
        ++splash_polls;
    } else if (intro_phase) {
        if (skip_splash && intro_ticks >= 120 && !skipped_intro) {
            api.Input.KeyDown[0x28] = api.Input.KeyPressed[0x28] = 1;
            skipped_intro = 1;
        }
    } else if (pregame_phase) {
        /* Startup input must not skip the original 130-tick Timon scene. */
        api.Input.KeyDown[0x28] = api.Input.KeyPressed[0x28] = 1;
    } else if (in_menu) {
        if (menu_visits < 3 && ++selector_wait < 70) return;
        unsigned int key;
        if (menu_visits == 3) key = menu_step++ == 0 ? 0x52 : 0x28;
        else {
            static const unsigned int keys[] = {0x52,0x51,0x51,0x28,0x52,0x28};
            assert(menu_step < sizeof(keys) / sizeof(keys[0]));
            key = keys[menu_step++];
        }
        api.Input.KeyPressed[key] = api.Input.KeyDown[key] = 1;
        if (key == 0x52) selector_selected = (selector_selected + 2) % 3;
        if (key == 0x51) selector_selected = (selector_selected + 1) % 3;
    } else if (in_scene) {
        ++scene_polls;
        api.Input.KeyDown[0x4f] = polls - restart_poll < 280;
        if (menu_visits == 1 && scene_polls == 2002)
            api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
    }
}
static void __attribute__((ms_abi)) draw(const DOS64_COLOR *image, unsigned int width,
    unsigned int height, unsigned int stride, int x, int y, unsigned int dw, unsigned int dh)
{
    if (height == 5 && stride == 60) {
        assert(width <= 60 && x == (int)(640 - (width + 4) * 2) &&
            y == 422 && dw == width * 2 && dh == 10);
        return;
    }
    assert(width == 320 && height == 200 && stride == 320 &&
        x == 0 && y == 40 && dw == 640 && dh == 400);
    ++draws;
    unsigned int visible = 0;
    for (unsigned int i = 0; i < 64000; ++i) {
        assert((image[i] >> 24) == 255);
        visible += (image[i] & 0xffffff) != 0;
    }
    assert(visible > 100 || missing_title || (!in_scene && !menu_visits && !splash_phase && !intro_phase));
    if (intro_phase) {
        unsigned long long ticks;
        assert(engine_clock_elapsed_ticks(&intro_clock, now, &ticks) == 0);
        unsigned long long phase = ticks * 5 + intro_clock.logic_remainder;
        ticks = phase / 10;
        intro_clock.logic_remainder = (unsigned int)(phase % 10);
        for (unsigned long long i = 0; i < ticks && intro_ticks < 360; ++i, ++intro_ticks)
            if (intro_ticks < 120 && --intro_remaining < 0 && intro_index) {
                --intro_index;
                const unsigned char *p = animation_intro_frames + intro_index * 8 + 4;
                intro_remaining = (int)(p[0] | (unsigned int)p[1] << 8 |
                    (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24);
            }
        unsigned int address = 0xbd60;
        if (intro_index < 15) {
            const unsigned char *p = animation_intro_frames + intro_index * 8;
            address = p[0] | (unsigned int)p[1] << 8 |
                (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
        }
        const unsigned char *part = animation_enemy_data + address - ANIMATION_ENEMY_BASE + 14;
        unsigned int frame = part[4];
        seen_intro_frames |= 1U << frame;
        memcpy(intro_pixels, expected_title, sizeof(intro_pixels));
        assert(render_draw_sprite(intro_art, intro_size, (unsigned short)frame,
            138 - (int)(part[0] | part[1] << 8), 157 - (int)(part[2] | part[3] << 8),
            intro_pixels) == 0);
        for (unsigned int i = 0; i < 64000; ++i)
            assert(image[i] == (title_colors[intro_pixels[i]] | 0xff000000U));
        ++intro_frames;
    }
    if (pregame_phase) {
        unsigned long long ticks;
        assert(engine_clock_elapsed_ticks(&pregame_clock, now, &ticks) == 0);
        unsigned long long phase = ticks * 5 + pregame_clock.logic_remainder;
        ticks = phase / 10;
        pregame_clock.logic_remainder = (unsigned int)(phase % 10);
        pregame_ticks += (unsigned int)ticks;
        if (pregame_ticks > 130) pregame_ticks = 130;
        unsigned int frame = pregame_ticks <= 30 ? 0 : (pregame_ticks - 31) / 4;
        if (frame > 21) frame = 21;
        seen_pregame_frames |= 1U << frame;
        const unsigned char *part = animation_enemy_data +
            0x12d78 - ANIMATION_ENEMY_BASE + frame * 20 + 14;
        memset(pregame_pixels, 0, sizeof(pregame_pixels));
        assert(render_draw_sprite(pregame_art, pregame_size, (unsigned short)frame,
            160 - (int)(part[0] | part[1] << 8),
            160 - (int)(part[2] | part[3] << 8), pregame_pixels) == 0);
        for (unsigned int i = 0; i < 64000; ++i)
            assert(image[i] == (title_colors[pregame_pixels[i]] | 0xff000000U));
    }
    if (splash_phase) {
        for (unsigned int i = 0; i < 64000; ++i)
            assert(image[i] == (splash_colors[expected_splash[splash_phase - 1][i]] | 0xff000000U));
        ++splash_frames;
    }
    if (in_menu && !missing_title) {
        for (unsigned int i = 0; i < 320 * 110; ++i)
            assert(image[i] == (title_colors[expected_title[i]] | 0xff000000U));
        unsigned long long ticks;
        assert(engine_clock_elapsed_ticks(&selector_clock, now, &ticks) == 0);
        unsigned long long phase = ticks * 5 + selector_clock.logic_remainder;
        ticks = phase / 10;
        selector_clock.logic_remainder = (unsigned int)(phase % 10);
        for (unsigned long long i = 0; i < ticks; ++i) {
            if (--selector_remaining < 0) {
                selector_remaining = 10;
                selector_right = !selector_right;
            } else selector_x += selector_right ? 1 : -1;
        }
        assert(selector_x >= 72 && selector_x <= 82);
        selector_positions |= 1U << (selector_x - 72);
        memcpy(intro_pixels, expected_title, sizeof(intro_pixels));
        assert(render_draw_sprite(selector_art, selector_size, 0, selector_x,
            115 + (int)selector_selected * 18, intro_pixels) == 0);
        for (unsigned int y = 115; y < 183; ++y)
            for (unsigned int x = 65; x < 111; ++x) {
                unsigned int i = y * 320 + x;
                assert(image[i] == (title_colors[intro_pixels[i]] | 0xff000000U));
            }
    }
    if (in_scene && !pregame_phase && !scene_polls) {
        ++loading_frames;
        if (loading_frames % 71 == 0) loading_hold_start = now;
        const DOS64_COLOR *p = loading_frames == 1 ? title_colors : level_colors;
        for (unsigned int i = 0; i < 64000; ++i)
            assert(image[i] == (p[expected_loading[i]] | 0xff000000U));
    }
    if (level_title_visible && in_scene && scene_polls) {
        for (unsigned int i = 0; i < 64000; ++i)
            if (expected_loading[i])
                assert(image[i] == (level_colors[expected_loading[i]] | 0xff000000U));
        if (scene_polls == 1) memcpy(initial_game, image, sizeof(initial_game));
        else if (memcmp(initial_game, image, sizeof(initial_game))) ++moving_title_frames;
        ++level_title_frames;
    }
}
static int __attribute__((ms_abi)) audio_open(unsigned int rate)
{
    assert(rate == MUSIC_RATE && !audio_live);
    audio_live = 1;
    audio_kind = !in_scene ? 1 : finished_pregames < menu_visits ? 2 : 3;
    if (audio_kind == 1) {
        assert(music_initialize(&title_reference, title_module, sizeof(title_module)) == 0);
        title_reference.interpolate_samples = 1;
        title_reference.sample_reference_period = 856;
    }
    else assert(menu_visits == 2);
    ++audio_opens;
    return 0;
}
static unsigned long long __attribute__((ms_abi)) queued(void) { return 0; }
static unsigned long long __attribute__((ms_abi)) free_frames(void) { return 1024; }
static unsigned long long __attribute__((ms_abi)) audio_write(const short *samples,
    unsigned long long count)
{
    assert(samples && audio_live && count <= 1024);
    if (audio_kind == 1) {
        assert(music_samples(&title_reference, expected_audio, (unsigned int)count) == 0);
        assert(memcmp(samples, expected_audio, (size_t)count * 4) == 0);
        title_audio_frames += count;
        if (splash_phase == 1) disney_audio_frames += count;
    }
    audio_frames += count;
    return count;
}
static void __attribute__((ms_abi)) audio_stop(void)
{ assert(audio_live); audio_live = 0; ++audio_stops; }

int main(int argc, char **argv)
{
    assert(argc == 1 || (argc == 2 && !strcmp(argv[1], "--skip-splash")));
    skip_splash = argc == 2;
    api.Size = sizeof(api); api.Version = DOS64_API_VERSION; api.Arguments = "";
    api.Write = console; api.Sleep = sleep_ms; api.Time.Nanoseconds = time_ns;
    api.Input.Poll = poll; api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SetColor = set_color; api.Gfx.Clear = clear;
    api.Gfx.SelectLayer = select_layer; api.Gfx.Present = present; api.DrawImage = draw;
    mock_install_layers(&api);
    api.Fs.Open = open_file; api.Fs.Close = close_file; api.Fs.Seek = seek_file;
    api.Fs.Tell = tell_file; api.Fs.Read = read_file; api.Fs.Write = write_file;
    api.Audio.Present = 1; api.Audio.Open = audio_open; api.Audio.Write = audio_write;
    api.Audio.FreeFrames = free_frames; api.Audio.QueuedFrames = queued; api.Audio.Stop = audio_stop;
    static unsigned char source[79311], map[580488], logo[32768];
    static RESOURCE_DICTIONARY dictionary;
    unsigned int size, logo_size;
    assert(resources_load_entry(&api, "LIONKING.EPF", "CREDITS.MAP", source,
        sizeof(source), map, sizeof(map), &dictionary, &size) == 0);
    assert(vga_load_palette(map, size, splash_colors) == 0);
    for (unsigned int layer = 0; layer <= 2; layer += 2) {
        assert(render_map_tile_pass(map, size, layer, 0, 0, 0, expected_splash[layer / 2]) == 0);
        assert(render_map_tile_pass(map, size, layer, 0, 0, 1, expected_splash[layer / 2]) == 0);
    }
    assert(resources_load_entry(&api, "LIONKING.EPF", "TITLES.MAP", source,
        sizeof(source), map, sizeof(map), &dictionary, &size) == 0);
    assert(vga_load_palette(map, size, title_colors) == 0);
    for (int layer = 1; layer >= 0; --layer) {
        assert(render_map_tile_pass(map, size, (unsigned int)layer, 0, 0, 0, expected_title) == 0);
        assert(render_map_tile_pass(map, size, (unsigned int)layer, 0, 0, 1, expected_title) == 0);
    }
    assert(resources_load_entry(&api, "LIONKING.EPF", "TITLE_S.MCH", source,
        sizeof(source), logo, sizeof(logo), &dictionary, &logo_size) == 0);
    assert(render_draw_sprite(logo, logo_size, 0, 44, 17, expected_title) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "INTRO.MCH", source,
        sizeof(source), intro_art, sizeof(intro_art), &dictionary, &intro_size) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "1TIMONS.MCH", source,
        sizeof(source), pregame_art, sizeof(pregame_art), &dictionary, &pregame_size) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "LEVEL1.MAP", source,
        sizeof(source), map, sizeof(map), &dictionary, &size) == 0);
    assert(vga_load_palette(map, size, level_colors) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "LEVELS.MCH", source,
        sizeof(source), logo, sizeof(logo), &dictionary, &logo_size) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "TITLE.AMF", title_source,
        sizeof(title_source), title_module, sizeof(title_module), &dictionary, &size) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "SUN.MCH", source,
        sizeof(source), selector_art, sizeof(selector_art), &dictionary, &selector_size) == 0);
    assert(render_draw_sprite(logo, logo_size, 0, 58, 77, expected_loading) == 0);
    assert(start(&api) == 0);
    assert(splash_frames == 2);
    assert(menu_visits == 3 && returns == 2 && intro_runs == 1 &&
        finished_intros == 1 && pregame_runs == 2 && finished_pregames == 2 &&
        speech_requests == 2 && title_completions == 2 && level_title_frames >= 396 &&
        moving_title_frames > 100 && seen_pregame_frames == 0x3fffff &&
        loading_frames == 142 &&
        intro_frames > 100 && clears == draws && (seen_intro_frames & 0xff) == 0xff);
    assert(audio_opens == 5 && audio_stops == 5 && !audio_live &&
        audio_frames > 800000 && title_audio_frames > 800000 && disney_audio_frames > 0 &&
        selector_positions == 0x7ff);
    assert(muted_requests && deaths == 3 && death_scenes == 3 &&
        restarts == 2 && !log_file);
    printf("PASS: original title map, menu wrap/toggle/start/exit, %u loading frames, "
        "startup baby-Simba intro before menu, Timon/SPEECH5 before both starts, "
        "pixel-exact 22 Timon frames and LEVEL1 heading over 100 live gameplay ticks, "
        "opaque screen clear, muted gameplay, Escape return, three deaths/two restarts/"
        "GAMEOVER return, audio reopening/cleanup; %u rendered frames\n", loading_frames, draws);
    puts(skip_splash ? "PASS: both original publisher screens match every pixel and are skippable" :
        "PASS: both original publisher screens match every pixel; original sky/rock/title menu composition");
    puts("PASS: exact TITLE.AMF PCM starts on Disney splash, continues through intro/menu; "
        "full original selector oscillation matches pixels; five audio streams open/close without overlap");
    missing_title = 1;
    assert(start(&api) == 1 && error_logged && !log_file && audio_opens == 5);
    puts("PASS: missing title resources fail explicitly without entering gameplay");
    return 0;
}
