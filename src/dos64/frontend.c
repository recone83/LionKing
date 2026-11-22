#include "frontend.h"
#include "platform.h"
#include "engine/resources.h"
#include "engine/tiles.h"
#include "engine/sprites.h"
#include "engine/timing.h"
#include "engine/animation_data.h"
#include "engine/render.h"
#include "engine/music.h"
#include "libs/vga.h"
#include "dos64_memory.h"

typedef struct {
    unsigned char title_map[131072], source[85438], view[64000];
    unsigned char title_music[88301], title_logo[16384];
    unsigned char credits_map[65536], font[8192], sun[4096];
    unsigned char intro_art[16384], level_titles[32768];
    unsigned char pregame_art[65536], pregame_speech[14826];
    unsigned char reward_art[65536], reward_speech[65536];
    unsigned char continue_art[2701], continue_rafiki[50205], continue_numbers[1826];
    unsigned char continue_sun[4096], continue_circle[2653];
    unsigned char continue_gameover[4096], continue_music[29879];
} FRONTEND_BUFFERS;

static FRONTEND_BUFFERS *buffers;
static unsigned char *title_map, *source, *view, *title_music, *title_logo;
static unsigned char *credits_map, *font, *sun, *intro_art, *level_titles;
static unsigned char *pregame_art, *pregame_speech, *reward_art, *reward_speech;
static MUSIC_PLAYER title_player;
static MUSIC_OUTPUT title_output;
static MUSIC_PLAYER continue_player;
static MUSIC_OUTPUT continue_output;
static DOS64_COLOR continue_colors[256];
static DOS64_COLOR continue_circle_colors[16];
static unsigned char continue_circle_remap[256];
static unsigned int continue_art_size, continue_rafiki_size, continue_numbers_size;
static unsigned int continue_sun_size, continue_circle_size, continue_gameover_size, continue_music_size;
static int continue_ready;
static RESOURCE_DICTIONARY dictionary;
static unsigned int title_size;
static unsigned int logo_size, logo_width;
static unsigned int credits_size, font_size, sun_size;
static unsigned int intro_size, level_titles_size;
static unsigned int pregame_size, speech_size;
static DOS64_COLOR loading_colors[256];
static DOS64_COLOR colors[256];
static int ready;

static int frontend_prepare(const DOS64_API *api)
{
    if (buffers) return 0;
    if (memory_init(api) != 0) {
        lk_platform_log("Lion King: frontend heap service unavailable.\n");
        return -1;
    }
    buffers = memory_calloc(1, sizeof(*buffers));
    if (!buffers) {
        lk_platform_log("Lion King: cannot allocate frontend buffers.\n");
        return -1;
    }
    title_map = buffers->title_map; source = buffers->source; view = buffers->view;
    title_music = buffers->title_music; title_logo = buffers->title_logo;
    credits_map = buffers->credits_map; font = buffers->font; sun = buffers->sun;
    intro_art = buffers->intro_art; level_titles = buffers->level_titles;
    pregame_art = buffers->pregame_art; pregame_speech = buffers->pregame_speech;
    reward_art = buffers->reward_art; reward_speech = buffers->reward_speech;
    return 0;
}

int frontend_release(void)
{
    frontend_stop_audio();
    frontend_stop_continue();
    ready = 0;
    continue_ready = 0;
    font_size = 0;
    if (!buffers) return 0;
    int result = memory_free(buffers);
    buffers = 0;
    if (result != 0) lk_platform_log("Lion King: cannot release frontend buffers.\n");
    return result;
}

void frontend_stop_audio(void)
{
    music_output_stop(&title_output);
}

static int title_sound(const DOS64_API *api, int enabled)
{
    if (!enabled) {
        frontend_stop_audio();
        return 0;
    }
    if (!title_output.opened) {
        if (music_initialize(&title_player, title_music, sizeof(buffers->title_music)) != 0 ||
            music_output_open(&title_output, &title_player, api) != 0) {
            lk_platform_log("Lion King: original TITLE.AMF requires usable DOS64 audio output.\n");
            return -1;
        }
        /* Title screens have no latency-sensitive effects; cover slower QEMU presentations. */
        title_output.target_frames = MUSIC_RATE / 4;
        title_player.interpolate_samples = 1;
        /* DSMI rates are C5: the legacy LEVEL1 calibration was one octave higher. */
        title_player.sample_reference_period = 856;
        if (music_output_service(&title_output) != 0) {
            lk_platform_log("Lion King: cannot prime original title music.\n");
            return -1;
        }
    }
    return 0;
}

static int title_service(void)
{
    if (title_output.opened && music_output_service(&title_output) != 0) {
        lk_platform_log("Lion King: title music streaming failed.\n");
        return -1;
    }
    return 0;
}

static int text(unsigned int x, unsigned int y, const char *label)
{
    for (; *label; ++label, x += 8) {
        unsigned char character = (unsigned char)*label;
        if (character > 'Z') character -= 32;
        if (character < 32 || render_draw_sprite(font, font_size,
            (unsigned short)(character - 32), (int)x, (int)y, view) != 0) {
            lk_platform_log("Lion King: invalid original menu font.\n");
            return -1;
        }
    }
    return 0;
}

static int title_background(void)
{
    for (unsigned int i = 0; i < sizeof(buffers->view); ++i) view[i] = 0;
    if (render_map_tile_pass(title_map, title_size, 1, 0, 0, 0, view) != 0 ||
        render_map_tile_pass(title_map, title_size, 1, 0, 0, 1, view) != 0 ||
        render_map_tile_pass(title_map, title_size, 0, 0, 0, 0, view) != 0 ||
        render_map_tile_pass(title_map, title_size, 0, 0, 0, 1, view) != 0) {
        lk_platform_log("Lion King: invalid original title map.\n");
        return -1;
    }
    return 0;
}

static int background(void)
{
    for (unsigned int i = 0; i < sizeof(buffers->view); ++i) view[i] = 0;
    if (ready && (title_background() != 0 ||
        render_draw_sprite(title_logo, logo_size, 0,
            (short)((LK_WIDTH - logo_width) / 2), 17, view) != 0)) {
        lk_platform_log("Lion King: invalid original title artwork.\n");
        return -1;
    }
    return 0;
}

int frontend_initialize(const DOS64_API *resources)
{
    if (frontend_prepare(resources) != 0) return -1;
    ready = 0;
    font_size = 0;
    for (unsigned int i = 0; i < 256; ++i) colors[i] = 0;
    if (background() != 0) return -1;
    if (frontend_loading(0, 1) != 0) return -1;
    if (resources_load_entry(resources, "LIONKING.EPF", "TITLES.MAP",
        source, sizeof(buffers->source), title_map, sizeof(buffers->title_map), &dictionary, &title_size) != 0 ||
        vga_load_palette(title_map, title_size, colors) != 0) {
        lk_platform_log("Lion King: cannot load original title artwork/palette.\n");
        return -1;
    }
    if (resources_load_entry(resources, "LIONKING.EPF", "TITLE_S.MCH",
        source, sizeof(buffers->source), title_logo, sizeof(buffers->title_logo), &dictionary, &logo_size) != 0 ||
        logo_size < 10) {
        lk_platform_log("Lion King: cannot load original title logo.\n");
        return -1;
    }
    logo_width = title_logo[2] | (unsigned int)title_logo[3] << 8;
    if (!logo_width || logo_width > LK_WIDTH) {
        lk_platform_log("Lion King: invalid original title logo dimensions.\n");
        return -1;
    }
    if (resources_load_entry(resources, "LIONKING.EPF", "F8X8_S.MCH",
        source, sizeof(buffers->source), font, sizeof(buffers->font), &dictionary, &font_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "SUN.MCH",
        source, sizeof(buffers->source), sun, sizeof(buffers->sun), &dictionary, &sun_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "CREDITS.MAP",
        source, sizeof(buffers->source), credits_map, sizeof(buffers->credits_map), &dictionary, &credits_size) != 0) {
        lk_platform_log("Lion King: cannot load original menu font/selector/publisher screens.\n");
        return -1;
    }
    if (resources_load_entry(resources, "LIONKING.EPF", "INTRO.MCH",
        source, sizeof(buffers->source), intro_art, sizeof(buffers->intro_art), &dictionary, &intro_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "LEVELS.MCH",
        source, sizeof(buffers->source), level_titles, sizeof(buffers->level_titles), &dictionary, &level_titles_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "1TIMONS.MCH",
        source, sizeof(buffers->source), pregame_art, sizeof(buffers->pregame_art), &dictionary, &pregame_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "SPEECH5",
        source, sizeof(buffers->source), pregame_speech, sizeof(buffers->pregame_speech), &dictionary, &speech_size) != 0) {
        lk_platform_log("Lion King: cannot load original intro/level-title artwork.\n");
        return -1;
    }
    if (level_titles_size < 10 || !level_titles[0] ||
        (level_titles[2] | (unsigned int)level_titles[3] << 8) > LK_WIDTH ||
        (level_titles[4] | (unsigned int)level_titles[5] << 8) > LK_HEIGHT) {
        lk_platform_log("Lion King: invalid original level-title dimensions.\n");
        return -1;
    }
    unsigned int music_size;
    if (resources_load_entry(resources, "LIONKING.EPF", "TITLE.AMF",
        source, sizeof(buffers->source), title_music, sizeof(buffers->title_music), &dictionary, &music_size) != 0 ||
        music_size != sizeof(buffers->title_music) ||
        music_initialize(&title_player, title_music, music_size) != 0) {
        lk_platform_log("Lion King: invalid original TITLE.AMF soundtrack.\n");
        return -1;
    }
    ready = 1;
    for (unsigned int i = 0; i < 256; ++i) loading_colors[i] = colors[i];
    if (background() != 0) return -1;
    lk_platform_present(view, colors);
    return 0;
}

int frontend_splash(const DOS64_API *api)
{
    DOS64_COLOR credits_colors[256];
    if (title_sound(api, 1) != 0) return -1;
    lk_platform_log("Title music: original TITLE.AMF starts on Disney/Virgin splash.\n");
    if (vga_load_palette(credits_map, credits_size, credits_colors) != 0) {
        lk_platform_log("Lion King: invalid publisher-screen palette.\n");
        return -1;
    }
    for (unsigned int layer = 0; layer <= 2; layer += 2) {
        for (unsigned int i = 0; i < sizeof(buffers->view); ++i) view[i] = 0;
        if (render_map_tile_pass(credits_map, credits_size, layer, 0, 0, 0, view) != 0 ||
            render_map_tile_pass(credits_map, credits_size, layer, 0, 0, 1, view) != 0) {
            lk_platform_log("Lion King: invalid publisher-screen map.\n");
            return -1;
        }
        lk_platform_log(layer ? "Splash: East Point Software.\n" : "Splash: Disney and Virgin.\n");
        if (title_service() != 0) return -1;
        lk_platform_present(view, credits_colors);
        if (title_service() != 0) return -1;
        ENGINE_CLOCK clock;
        engine_clock_reset(&clock, lk_platform_time_ns());
        unsigned long long elapsed = 0;
        while (elapsed < 210) {
            lk_platform_poll();
            if (title_service() != 0) return -1;
            int skip = 0;
            for (unsigned int key = 0; key < sizeof(api->Input.KeyPressed); ++key)
                skip |= api->Input.KeyPressed[key] != 0;
            if (skip) break;
            unsigned long long ticks;
            if (engine_clock_elapsed_ticks(&clock, lk_platform_time_ns(), &ticks) != 0) {
                lk_platform_log("Lion King: invalid publisher-screen clock.\n");
                return -1;
            }
            elapsed += ticks;
        }
    }
    return background();
}

static unsigned int read32(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8 |
        (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
}

static int logic_ticks(ENGINE_CLOCK *clock, unsigned long long *ticks)
{
    unsigned long long irq;
    if (engine_clock_elapsed_ticks(clock, lk_platform_time_ns(), &irq) != 0 ||
        irq > (~0ULL - clock->logic_remainder) / 5) return -1;
    unsigned long long phase = irq * 5 + clock->logic_remainder;
    *ticks = phase / 10;
    clock->logic_remainder = (unsigned int)(phase % 10);
    return 0;
}

int frontend_intro(const DOS64_API *api)
{
    static RENDER_POOL pool;
    static RENDER_SPRITE_BANK banks[98];
    RENDER_OWNER owner = {138,157};
    render_initialize_nodes(&pool);
    RENDER_NODE *node = render_acquire_node(&pool, &owner, 0, 0,
        animation_enemy_data + 0xbd60 - ANIMATION_ENEMY_BASE, 20);
    if (!node) {
        lk_platform_log("Lion King: cannot initialize original title intro.\n");
        return -1;
    }
    banks[97] = (RENDER_SPRITE_BANK){intro_art, intro_size};
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, lk_platform_time_ns());
    unsigned int elapsed = 0, index = 15;
    int remaining = 30;
    lk_platform_log("Intro: original Rafiki and Simba title sequence.\n");
    for (;;) {
        lk_platform_poll();
        int skip = 0;
        for (unsigned int key = 0; key < sizeof(api->Input.KeyPressed); ++key)
            skip |= api->Input.KeyPressed[key] != 0;
        if (elapsed >= 120 && (skip || elapsed >= 360)) break;
        unsigned long long ticks;
        if (logic_ticks(&clock, &ticks) != 0) {
            lk_platform_log("Lion King: invalid original intro clock.\n");
            return -1;
        }
        for (unsigned long long tick = 0; tick < ticks && elapsed < 360; ++tick, ++elapsed) {
            if (elapsed < 120 && --remaining < 0 && index) {
                const unsigned char *entry = animation_intro_frames + --index * 8;
                unsigned int address = read32(entry);
                if (address < ANIMATION_ENEMY_BASE ||
                    address - ANIMATION_ENEMY_BASE > ANIMATION_ENEMY_SIZE - 20) {
                    lk_platform_log("Lion King: invalid original intro descriptor.\n");
                    return -1;
                }
                node->parts = animation_enemy_data + address - ANIMATION_ENEMY_BASE;
                remaining = (int)read32(entry + 4);
            }
        }
        if (title_service() != 0) return -1;
        if (background() != 0 || render_object_pass(&pool, 0, 0, 0,
            banks, 98, view) != 0) {
            lk_platform_log("Lion King: cannot render original title intro.\n");
            return -1;
        }
        lk_platform_present(view, colors);
        if (title_service() != 0) return -1;
    }
    lk_platform_log("Intro: finished before main menu.\n");
    return 0;
}

int frontend_pregame(const DOS64_API *api, int sound_enabled)
{
    static RENDER_POOL pool;
    static RENDER_SPRITE_BANK banks[240];
    static MUSIC_PLAYER player;
    static MUSIC_OUTPUT output;
    ANIMATION_PROGRAM program;
    RENDER_OWNER owner = {160,160};
    render_initialize_nodes(&pool);
    RENDER_NODE *node = render_acquire_node(&pool, &owner, 0, 0,
        animation_enemy_data + 0x12d78 - ANIMATION_ENEMY_BASE, 20);
    if (!node || animation_program_initialize(&program, animation_pregame_data,
        sizeof(animation_pregame_data), 0x5435, 0x5435,
        animation_pregame_data, sizeof(animation_pregame_data), 0x5435) != 0 ||
        music_effects_initialize(&player) != 0) {
        lk_platform_log("Lion King: cannot initialize original Timon pre-game intro.\n");
        return -1;
    }
    banks[239] = (RENDER_SPRITE_BANK){pregame_art, pregame_size};
    if (sound_enabled && music_output_open(&output, &player, api) != 0) {
        lk_platform_log("Lion King: pre-game speech requires usable DOS64 audio output.\n");
        return -1;
    }
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, lk_platform_time_ns());
    unsigned int elapsed = 0;
    int result = -1;
    lk_platform_log("Pre-game: original Timon intro, 130 ticks.\n");
    while (elapsed < 130) {
        unsigned long long ticks;
        lk_platform_poll();
        if (logic_ticks(&clock, &ticks) != 0) {
            lk_platform_log("Lion King: invalid pre-game intro clock.\n");
            goto finished;
        }
        for (unsigned long long tick = 0; tick < ticks && elapsed < 130; ++tick, ++elapsed) {
            if (elapsed == 50) {
                if (sound_enabled && (music_effect_play(&player, 0, pregame_speech, speech_size) != 0 ||
                    music_effect_play(&player, 1, pregame_speech, speech_size) != 0)) {
                    lk_platform_log("Lion King: cannot play original pre-game SPEECH5.\n");
                    goto finished;
                }
                lk_platform_log(sound_enabled ? "Pre-game: SPEECH5 on both original channels.\n" :
                    "Pre-game: SPEECH5 muted.\n");
            }
            if (elapsed >= 30 && animation_program_step(&program, node, &owner, 0, 0) != 0) {
                lk_platform_log("Lion King: invalid original pre-game animation script.\n");
                goto finished;
            }
        }
        for (unsigned int i = 0; i < sizeof(buffers->view); ++i) view[i] = 0;
        if (render_object_pass(&pool, 0, 0, 0, banks, 240, view) != 0) {
            lk_platform_log("Lion King: cannot render original Timon pre-game intro.\n");
            goto finished;
        }
        lk_platform_present(view, colors);
        if (sound_enabled && music_output_service(&output) != 0) {
            lk_platform_log("Lion King: pre-game speech streaming failed.\n");
            goto finished;
        }
    }
    lk_platform_log("Pre-game: finished before LEVEL1 loading.\n");
    result = 0;
finished:
    music_output_stop(&output);
    return result;
}

int frontend_victory(const DOS64_API *api, const DOS64_API *resources, int sound_enabled)
{
    static RENDER_POOL pool;
    static RENDER_SPRITE_BANK banks[81];
    static MUSIC_PLAYER player;
    static MUSIC_OUTPUT output;
    ANIMATION_PROGRAM programs[2];
    RENDER_OWNER owners[2] = {{142,163}, {142,162}};
    RENDER_NODE *nodes[2];
    unsigned int art_size, speech_size;
    if (frontend_prepare(resources) != 0) return -1;
    frontend_stop_audio();
    if (resources_load_entry(resources, "LIONKING.EPF", "TITLES.MAP",
        source, sizeof(buffers->source), title_map, sizeof(buffers->title_map), &dictionary, &title_size) != 0 ||
        vga_load_palette(title_map, title_size, colors) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "RWDLVL1.MCH",
        source, sizeof(buffers->source), reward_art, sizeof(buffers->reward_art), &dictionary, &art_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "SPEECH1",
        source, sizeof(buffers->source), reward_speech, sizeof(buffers->reward_speech), &dictionary, &speech_size) != 0) {
        lk_platform_log("Lion King: cannot load original LEVEL1 Rafiki reward scene.\n");
        return -1;
    }
    render_initialize_nodes(&pool);
    for (unsigned int i = 0; i < 2; ++i) {
        nodes[i] = render_acquire_node(&pool, &owners[i], 0, 0,
            animation_enemy_data + (i ? 0xae64 : 0xafb8) - ANIMATION_ENEMY_BASE, 20);
        if (!nodes[i] || animation_program_initialize(&programs[i], animation_enemy_data,
            ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE, i ? 0x13125 : 0x130f0,
            animation_enemy_data, ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE) != 0) {
            lk_platform_log("Lion King: cannot initialize original Rafiki reward scripts.\n");
            return -1;
        }
    }
    banks[80] = (RENDER_SPRITE_BANK){reward_art, art_size};
    if (music_effects_initialize(&player) != 0 ||
        (sound_enabled && music_output_open(&output, &player, api) != 0)) {
        lk_platform_log("Lion King: reward speech requires usable DOS64 audio output.\n");
        return -1;
    }
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, lk_platform_time_ns());
    int result = -1, done = 0;
    lk_platform_log("Victory: original LEVEL1 Rafiki reward scene.\n");
    while (!done) {
        unsigned long long ticks;
        lk_platform_poll();
        if (lk_platform_exit_requested()) {
            lk_platform_log("Victory: Rafiki scene skipped.\n");
            break;
        }
        if (logic_ticks(&clock, &ticks) != 0) {
            lk_platform_log("Lion King: invalid reward scene clock.\n");
            goto finished_reward;
        }
        for (unsigned long long tick = 0; tick < ticks && !done; ++tick) {
            for (unsigned int i = 0; i < 2; ++i)
                if (animation_program_step(&programs[i], nodes[i], &owners[i], 0, 0) != 0) {
                    lk_platform_log("Lion King: invalid original Rafiki reward animation.\n");
                    goto finished_reward;
                }
            if (programs[1].state == 2) {
                if (sound_enabled && (music_effect_play(&player, 0, reward_speech, speech_size) != 0 ||
                    music_effect_play(&player, 1, reward_speech, speech_size) != 0)) {
                    lk_platform_log("Lion King: cannot play original reward SPEECH1.\n");
                    goto finished_reward;
                }
                lk_platform_log(sound_enabled ? "Victory: SPEECH1 on both original channels.\n" :
                    "Victory: SPEECH1 muted.\n");
                programs[1].state = 0;
            }
            if (programs[1].state == 3) programs[1].state = 0;
            done = programs[1].state == 1;
        }
        if (title_background() != 0 ||
            render_object_pass(&pool, 0, 0, 0, banks, 81, view) != 0) {
            lk_platform_log("Lion King: cannot render original Rafiki reward scene.\n");
            goto finished_reward;
        }
        lk_platform_present(view, colors);
        if (sound_enabled && music_output_service(&output) != 0) {
            lk_platform_log("Lion King: reward speech streaming failed.\n");
            goto finished_reward;
        }
    }
    lk_platform_log("Victory: reward scene finished; next level/bonus gameplay is not yet ported.\n");
    result = 0;
finished_reward:
    music_output_stop(&output);
    return result;
}

int frontend_next_level_unavailable(const DOS64_API *api, const DOS64_API *resources)
{
    unsigned int loaded;
    if (frontend_prepare(resources) != 0) return -1;
    if (resources_load_entry(resources, "LIONKING.EPF", "F8X8_S.MCH",
        source, sizeof(buffers->source), font, sizeof(buffers->font), &dictionary, &loaded) != 0) {
        lk_platform_log("Lion King: cannot load next-level notice font.\n");
        return -1;
    }
    font_size = loaded;
    if (title_background() != 0 ||
        text(76, 90, "LEVEL 2 NOT AVAILABLE") != 0 ||
        text(88, 110, "ENTER SPACE OR ESC") != 0) {
        lk_platform_log("Lion King: cannot draw next-level notice.\n");
        return -1;
    }
    lk_platform_log("Transition: LEVEL2 is not available; awaiting confirmation.\n");
    lk_platform_present(view, colors);
    int released = 0;
    for (;;) {
        lk_platform_poll();
        int held = api->Input.KeyDown[0x28] || api->Input.KeyDown[0x29] ||
            api->Input.KeyDown[0x2c];
        if (released && (lk_platform_exit_requested() ||
            api->Input.KeyPressed[0x28] || api->Input.KeyPressed[0x2c]))
            break;
        if (!held) released = 1;
    }
    lk_platform_log("Transition: returning without starting LEVEL2.\n");
    return 0;
}

int frontend_level_palette(const DOS64_COLOR *palette)
{
    for (unsigned int i = 0; i < 256; ++i) loading_colors[i] = palette[i];
    return 0;
}

int frontend_loading(unsigned int completed, unsigned int total)
{
    if (!total || completed > total) {
        lk_platform_log("Lion King: invalid level loading state.\n");
        return -1;
    }
    for (unsigned int i = 0; i < sizeof(buffers->view); ++i) view[i] = 0;
    if (ready && frontend_level_title(view) != 0) return -1;
    lk_platform_present(view, ready ? loading_colors : colors);
    if (ready && completed == total) {
        lk_platform_log("Loading: LEVEL1 assets ready; title overlays the first 100 gameplay ticks.\n");
    }
    return 0;
}


int frontend_prepare_continue(const DOS64_API *resources, const DOS64_COLOR *level_palette)
{
    if (!level_palette) {
        lk_platform_log("Lion King: cannot prepare continue screen without level palette.\n");
        return -1;
    }
    if (frontend_prepare(resources) != 0) return -1;
    for (unsigned int i = 0; i < 16; ++i) continue_circle_colors[i] = level_palette[128 + i];
    if (continue_ready) return 0;
    for (unsigned int i = 0; i < 256; ++i)
        continue_circle_remap[i] = (unsigned char)(i >= 128 && i < 144 ? i + 112 : i);
    unsigned int map_size;
    if (resources_load_entry(resources, "LIONKING.EPF", "TITLES.MAP",
            source, sizeof(buffers->source), title_map, sizeof(buffers->title_map),
            &dictionary, &map_size) != 0 ||
        vga_load_palette(title_map, map_size, continue_colors) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "CONTINUE.MCH",
            source, sizeof(buffers->source), buffers->continue_art, sizeof(buffers->continue_art),
            &dictionary, &continue_art_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "RAFIKI.MCH",
            source, sizeof(buffers->source), buffers->continue_rafiki, sizeof(buffers->continue_rafiki),
            &dictionary, &continue_rafiki_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "NUMBERS.MCH",
            source, sizeof(buffers->source), buffers->continue_numbers, sizeof(buffers->continue_numbers),
            &dictionary, &continue_numbers_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "SUN.MCH",
            source, sizeof(buffers->source), buffers->continue_sun, sizeof(buffers->continue_sun),
            &dictionary, &continue_sun_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "CIRCLE.MCH",
            source, sizeof(buffers->source), buffers->continue_circle, sizeof(buffers->continue_circle),
            &dictionary, &continue_circle_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "GAMEOVER.MCH",
            source, sizeof(buffers->source), buffers->continue_gameover, sizeof(buffers->continue_gameover),
            &dictionary, &continue_gameover_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "CONTINUE.AMF",
            source, sizeof(buffers->source), buffers->continue_music, sizeof(buffers->continue_music),
            &dictionary, &continue_music_size) != 0) {
        lk_platform_log("Lion King: cannot load continue screen resources.\n");
        return -1;
    }
    continue_ready = 1;
    return 0;
}

int frontend_start_continue(const DOS64_API *api, int sound_enabled)
{
    if (!continue_ready) return -1;
    if (sound_enabled &&
        (music_initialize(&continue_player, buffers->continue_music, continue_music_size) != 0 ||
         music_output_open(&continue_output, &continue_player, api) != 0)) {
        lk_platform_log("Lion King: cannot play continue music.\n");
        return -1;
    }
    return 0;
}

int frontend_service_continue(void)
{
    if (continue_output.opened && music_output_service(&continue_output) != 0) {
        lk_platform_log("Lion King: continue music streaming failed.\n");
        return -1;
    }
    return 0;
}

void frontend_stop_continue(void)
{
    music_output_stop(&continue_output);
}

int frontend_continue(unsigned char *pixels, DOS64_COLOR *palette,
    unsigned int ticks, int no_selected, unsigned int continues,
    unsigned int accept_ticks, int exhausted)
{
    static const unsigned char durations[] = {7, 7, 9, 9, 7, 9, 9, 11, 15, 27, 7, 7, 9};
    static const unsigned char loop_frames[] = {13, 14, 15, 15, 15, 14};
    static const unsigned char loop_durations[] = {43, 5, 63, 63, 63, 5};
    if (!continue_ready || !pixels || !palette ||
        ticks > (exhausted ? FRONTEND_GAME_OVER_TICKS : FRONTEND_CONTINUE_TICKS) ||
        accept_ticks > FRONTEND_CONTINUE_ACCEPT_TICKS || continues > 9 ||
        (no_selected != 0 && no_selected != 1) || (exhausted != 0 && exhausted != 1))
        return -1;
    unsigned int elapsed = (exhausted ? FRONTEND_GAME_OVER_TICKS : FRONTEND_CONTINUE_TICKS) - ticks;
    unsigned int frame = 0, phase = elapsed;
    while (frame < sizeof(durations) && phase >= durations[frame])
        phase -= durations[frame++];
    if (frame == sizeof(durations)) {
        unsigned int cycle = 0, index = 0;
        for (unsigned int i = 0; i < sizeof(loop_durations); ++i) cycle += loop_durations[i];
        phase %= cycle;
        while (phase >= loop_durations[index]) phase -= loop_durations[index++];
        frame = loop_frames[index];
    }
    if (accept_ticks) {
        unsigned int accepted = FRONTEND_CONTINUE_ACCEPT_TICKS - accept_ticks;
        frame = accepted < 3 ? 16 : accepted < 6 ? 17 : accepted < 11 ? 18 : 19;
    }
    for (unsigned int i = 0; i < 256; ++i) palette[i] = continue_colors[i];
    if (!exhausted)
        for (unsigned int i = 0; i < 16; ++i) palette[240 + i] = continue_circle_colors[i];
    if (render_draw_sprite(buffers->continue_rafiki, continue_rafiki_size,
            (unsigned short)frame, 96, 70, pixels) != 0 ||
        (exhausted ?
            render_draw_sprite(buffers->continue_gameover, continue_gameover_size, 0, 95, 32, pixels) != 0 :
            (render_draw_sprite(buffers->continue_art, continue_art_size, 0, 89, 16, pixels) != 0 ||
             (!accept_ticks && render_draw_sprite(buffers->continue_numbers, continue_numbers_size,
                 (unsigned short)(ticks ? (ticks - 1) * 10 / FRONTEND_CONTINUE_TICKS : 0),
                 150, 38, pixels) != 0) ||
             render_draw_sprite(buffers->continue_sun, continue_sun_size,
                 (unsigned short)((elapsed / 8) % 4), no_selected ? 163 : 67, 44, pixels) != 0 ||
             render_draw_sprite_remapped(buffers->continue_circle, continue_circle_size,
                 (unsigned short)((elapsed / 8) % 4), 242, 161, pixels, continue_circle_remap) != 0 ||
             render_draw_sprite(buffers->continue_numbers, continue_numbers_size,
                 (unsigned short)continues, 218, 118, pixels) != 0))) {
        lk_platform_log("Lion King: cannot render continue screen artwork.\n");
        return -1;
    }
    return 0;
}

int frontend_level_title(unsigned char *pixels)
{
    if (!ready || !pixels || render_draw_sprite(level_titles, level_titles_size, 0,
        (LK_WIDTH - (level_titles[2] | (unsigned int)level_titles[3] << 8)) / 2,
        (LK_HEIGHT - (level_titles[4] | (unsigned int)level_titles[5] << 8)) / 2, pixels) != 0) {
        lk_platform_log("Lion King: cannot draw original LEVEL1 title.\n");
        return -1;
    }
    return 0;
}
int frontend_menu(const DOS64_API *api, int *sound_enabled)
{
    unsigned int selected = 0;
    if (title_sound(api, *sound_enabled) != 0) return -1;
    /* A held Enter/Escape from the previous scene must not activate the next screen. */
    do {
        lk_platform_poll();
        if (title_service() != 0) return -1;
    } while (api->Input.KeyDown[0x28] || api->Input.KeyDown[0x29] ||
        api->Input.KeyDown[0x2c]);
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, lk_platform_time_ns());
    int selector_x = 82, selector_remaining = 10, selector_right = 0;
    lk_platform_log("Main menu: ready.\n");
    for (;;) {
        lk_platform_poll();
        if (title_service() != 0) return -1;
        if (lk_platform_exit_requested()) return 0;
        if (api->Input.KeyPressed[0x52]) selected = (selected + 2) % 3;
        if (api->Input.KeyPressed[0x51]) selected = (selected + 1) % 3;
        if (api->Input.KeyPressed[0x28] || api->Input.KeyPressed[0x2c]) {
            if (selected == 0) {
                frontend_stop_audio();
                lk_platform_log("Main menu: start LEVEL1.\n");
                return 1;
            }
            if (selected == 2) return 0;
            *sound_enabled = !*sound_enabled;
            if (title_sound(api, *sound_enabled) != 0) return -1;
            lk_platform_log(*sound_enabled ? "Main menu: sound on.\n" : "Main menu: sound off.\n");
        }
        unsigned long long ticks;
        if (logic_ticks(&clock, &ticks) != 0) {
            lk_platform_log("Lion King: invalid original menu-selector clock.\n");
            return -1;
        }
        for (unsigned long long tick = 0; tick < ticks; ++tick) {
            if (--selector_remaining < 0) {
                selector_remaining = 10;
                selector_right = !selector_right;
            } else selector_x += selector_right ? 1 : -1;
        }
        if (background() != 0) return -1;
        if (text(116, 123, "START GAME") != 0 ||
            text(116, 141, *sound_enabled ? "SOUND ON" : "SOUND OFF") != 0 ||
            text(116, 159, "EXIT") != 0 ||
            render_draw_sprite(sun, sun_size, 0, selector_x, 115 + (int)selected * 18, view) != 0) {
            lk_platform_log("Lion King: cannot draw original menu selection.\n");
            return -1;
        }
        lk_platform_present(view, colors);
        if (title_service() != 0) return -1;
    }
}
