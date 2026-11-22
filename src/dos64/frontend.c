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
    unsigned char continue_speech[29426];
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
static unsigned int continue_speech_size;
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

static void binding_name(unsigned char key, char name[5])
{
    static const char hex[] = "0123456789ABCDEF";
    name[0] = ' ';
    name[1] = ' ';
    name[2] = ' ';
    name[3] = ' ';
    name[4] = 0;
    if (key >= 4 && key <= 29) name[2] = (char)('A' + key - 4);
    else if (key >= 30 && key <= 38) name[2] = (char)('1' + key - 30);
    else if (key == 39) name[2] = '0';
    else if (key >= 0x3a && key <= 0x45) {
        unsigned int number = key - 0x3a + 1;
        name[1] = 'F';
        name[2] = number >= 10 ? '1' : (char)('0' + number);
        if (number >= 10) name[3] = (char)('0' + number % 10);
    } else {
        const char *label = 0;
        switch (key) {
        case 0x2b: label = " TAB"; break;
        case 0x2c: label = " SPC"; break;
        case 0x2d: label = "  - "; break;
        case 0x2e: label = "  = "; break;
        case 0x2f: label = "  ( "; break;
        case 0x30: label = "  ) "; break;
        case 0x32: label = "HASH"; break;
        case 0x33: label = "  ; "; break;
        case 0x36: label = "  , "; break;
        case 0x37: label = "  . "; break;
        case 0x38: label = "  / "; break;
        case 0x39: label = "CAPS"; break;
        case 0x4f: label = "RGHT"; break;
        case 0x50: label = "LEFT"; break;
        case 0x51: label = "DOWN"; break;
        case 0x52: label = " UP "; break;
        case 0xe0: label = "CTRL"; break;
        case 0xe4: label = "RCTL"; break;
        case 0xe1: label = " LSH"; break;
        case 0xe5: label = " RSH"; break;
        case 0xe2: label = " ALT"; break;
        case 0xe6: label = "RALT"; break;
        default: break;
        }
        if (label) {
            for (unsigned int i = 0; i < 4; ++i) name[i] = label[i];
        } else {
            name[0] = 'H';
            name[1] = 'I';
            name[2] = hex[key >> 4];
            name[3] = hex[key & 15];
        }
    }
}

static int binding_screen(const ENGINE_CONTROLS *controls, unsigned int binding,
    int duplicate_key)
{
    static const char *labels[CONTROL_COUNT] = {
        "   UP KEY", "   DOWN KEY", "   LEFT KEY", "   RIGHT KEY",
        "   JUMP", "   SLASH (ADULT)", "   ROAR", "   MAUL (ADULT)"
    };
    if (binding >= CONTROL_COUNT || text(80, 72, "DEFINE KEYBOARD CONTROLS") != 0)
        return -1;
    for (unsigned int i = 0; i <= binding; ++i) {
        char name[5];
        binding_name(controls->keys[i], name);
        if (text(80, 88 + i * 8, labels[i]) != 0 ||
            text(216, 88 + i * 8, name) != 0) return -1;
    }
    if (duplicate_key && text(64, 168, "KEY ALREADY USED") != 0) return -1;
    return text(64, 176, "ESC TO CANCEL");
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

int frontend_next_level_unavailable(const DOS64_API *api, const DOS64_API *resources,
    int bonus_selected)
{
    unsigned int loaded;
    if (bonus_selected != 0 && bonus_selected != 1) {
        lk_platform_log("Lion King: invalid next-level selection.\n");
        return -1;
    }
    if (frontend_prepare(resources) != 0) return -1;
    if (resources_load_entry(resources, "LIONKING.EPF", "F8X8_S.MCH",
        source, sizeof(buffers->source), font, sizeof(buffers->font), &dictionary, &loaded) != 0) {
        lk_platform_log("Lion King: cannot load next-level notice font.\n");
        return -1;
    }
    font_size = loaded;
    if (title_background() != 0 ||
        text(bonus_selected ? 68 : 76, 90,
            bonus_selected ? "BUG TOSS NOT AVAILABLE" : "LEVEL 2 NOT AVAILABLE") != 0 ||
        text(88, 110, "ENTER SPACE OR ESC") != 0) {
        lk_platform_log("Lion King: cannot draw next-level notice.\n");
        return -1;
    }
    lk_platform_log(bonus_selected ?
        "Transition: BUG TOSS is not available; awaiting confirmation.\n" :
        "Transition: LEVEL2 is not available; awaiting confirmation.\n");
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
    lk_platform_log(bonus_selected ?
        "Transition: returning without starting BUG TOSS.\n" :
        "Transition: returning without starting LEVEL2.\n");
    return 0;
}

int frontend_level_palette(const DOS64_COLOR *palette)
{
    for (unsigned int i = 0; i < 256; ++i) loading_colors[i] = palette[i];
    return 0;
}

int frontend_loading(unsigned int completed, unsigned int total)
{
    return frontend_loading_for_level(completed, total, 1);
}

int frontend_loading_for_level(unsigned int completed, unsigned int total,
    unsigned int level)
{
    if (!total || completed > total) {
        lk_platform_log("Lion King: invalid level loading state.\n");
        return -1;
    }
    for (unsigned int i = 0; i < sizeof(buffers->view); ++i) view[i] = 0;
    if (ready && frontend_level_title_for_level(level, view) != 0) return -1;
    lk_platform_present(view, ready ? loading_colors : colors);
    if (ready && completed == total) {
        lk_platform_log(level == 2 ?
            "Loading: LEVEL2 assets ready; title overlays the first 100 gameplay ticks.\n" :
            "Loading: LEVEL1 assets ready; title overlays the first 100 gameplay ticks.\n");
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
            &dictionary, &continue_music_size) != 0 ||
        resources_load_entry(resources, "LIONKING.EPF", "SPEECH2",
            source, sizeof(buffers->source), buffers->continue_speech, sizeof(buffers->continue_speech),
            &dictionary, &continue_speech_size) != 0) {
        lk_platform_log("Lion King: cannot load continue screen resources.\n");
        return -1;
    }
    continue_ready = 1;
    return 0;
}

int frontend_accept_continue(const DOS64_API *api, int sound_enabled)
{
    frontend_stop_continue();
    if (sound_enabled && (music_effects_initialize(&continue_player) != 0 ||
        music_output_open(&continue_output, &continue_player, api) != 0)) {
        lk_platform_log("Lion King: cannot open continue acceptance audio.\n");
        return -1;
    }
    return 0;
}

int frontend_continue_speech(int sound_enabled)
{
    if (sound_enabled &&
        (music_effect_play(&continue_player, 0, buffers->continue_speech, continue_speech_size) != 0 ||
         music_effect_play(&continue_player, 1, buffers->continue_speech, continue_speech_size) != 0)) {
        lk_platform_log("Lion King: cannot play continue SPEECH2.\n");
        return -1;
    }
    if (sound_enabled) lk_platform_log("Continue: SPEECH2 on both original channels.\n");
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
    static const unsigned char durations[] = {8, 8, 10, 10, 8, 10, 10, 12, 16, 28, 8, 8, 10};
    static const unsigned char loop_frames[] = {13, 14, 15, 15, 15, 14};
    static const unsigned char loop_durations[] = {44, 6, 64, 64, 64, 6};
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
        frame = accepted < 4 ? 16 : accepted < 8 ? 17 : accepted < 14 ? 18 : 19;
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
             (!accept_ticks && render_draw_sprite(buffers->continue_sun, continue_sun_size,
                 (unsigned short)((elapsed / 8) % 4), no_selected ? 163 : 67, 44, pixels) != 0) ||
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
    return frontend_level_title_for_level(1, pixels);
}

int frontend_level_title_for_level(unsigned int level, unsigned char *pixels)
{
    unsigned int frame = level ? level - 1 : 0;
    if (!ready || !pixels || !level || level > 10 ||
        render_draw_sprite(level_titles, level_titles_size, (unsigned short)frame,
        (LK_WIDTH - (level_titles[2] | (unsigned int)level_titles[3] << 8)) / 2,
        (LK_HEIGHT - (level_titles[4] | (unsigned int)level_titles[5] << 8)) / 2, pixels) != 0) {
        lk_platform_log("Lion King: cannot draw original level title.\n");
        return -1;
    }
    return 0;
}
int frontend_menu(const DOS64_API *api, int *music_enabled, int *sound_enabled,
    ENGINE_DIFFICULTY *difficulty, ENGINE_CONTROLS *controls)
{
    if (!api || !music_enabled || !sound_enabled || !difficulty || !controls ||
        *difficulty < ENGINE_DIFFICULTY_EASY || *difficulty > ENGINE_DIFFICULTY_HARD) {
        lk_platform_log("Lion King: invalid menu settings.\n");
        return -1;
    }
    unsigned int selected = 0, options = 0;
    unsigned int binding = 0;
    int duplicate_key = 0;
    ENGINE_CONTROLS pending = *controls;
    if (title_sound(api, *music_enabled) != 0) return -1;
    /* A held Enter/Escape from the previous scene must not activate the next screen. */
    do {
        lk_platform_poll();
        if (title_service() != 0) return -1;
    } while (api->Input.KeyDown[0x28] || api->Input.KeyDown[0x29] ||
        api->Input.KeyDown[0x2c]);
    ENGINE_CLOCK clock;
    engine_clock_reset(&clock, lk_platform_time_ns());
    int selector_x = 115, selector_remaining = 10, selector_right = 0;
    lk_platform_log("Main menu: ready.\n");
    for (;;) {
        lk_platform_poll();
        if (title_service() != 0) return -1;
        if (options == 2 && api->Input.KeyPressed[0x29]) {
            options = 1;
            lk_platform_log("Options: key changes cancelled.\n");
            do {
                lk_platform_poll();
                if (title_service() != 0) return -1;
            } while (api->Input.KeyDown[0x29]);
            continue;
        }
        if (options == 1 && api->Input.KeyPressed[0x29]) {
            options = selected = 0;
            lk_platform_log("Options: returned to main menu.\n");
            do {
                lk_platform_poll();
                if (title_service() != 0) return -1;
            } while (api->Input.KeyDown[0x29]);
            continue;
        }
        if (lk_platform_exit_requested()) return 0;
        unsigned int count = options ? 5 : 2;
        if (options == 2) {
            for (unsigned int key = 4; key < sizeof(api->Input.KeyPressed); ++key) {
                if (!api->Input.KeyPressed[key] || key == 0x28 || key == 0x29) continue;
                unsigned int previous = 0;
                while (previous < binding && pending.keys[previous] != key) ++previous;
                if (previous != binding) {
                    lk_platform_log("Options: key already assigned; choose another.\n");
                    duplicate_key = 1;
                    break;
                }
                duplicate_key = 0;
                pending.keys[binding++] = (unsigned char)key;
                lk_platform_log("Options: key recorded.\n");
                if (binding == CONTROL_COUNT) {
                    *controls = pending;
                    options = 1;
                    lk_platform_log("Options: key changes saved.\n");
                }
                break;
            }
        } else {
            if (api->Input.KeyPressed[0x52]) selected = (selected + count - 1) % count;
            if (api->Input.KeyPressed[0x51]) selected = (selected + 1) % count;
            if (api->Input.KeyPressed[0x28] || api->Input.KeyPressed[0x2c] ||
                (options && (api->Input.KeyPressed[0x50] || api->Input.KeyPressed[0x4f]))) {
                if (!options && selected == 0) {
                    frontend_stop_audio();
                    lk_platform_log("Main menu: start LEVEL1.\n");
                    return 1;
                }
                if (!options) {
                    options = 1;
                    selected = 0;
                    lk_platform_log("Options: opened.\n");
                } else if (selected == 4) {
                    options = selected = 0;
                    lk_platform_log("Options: returned to main menu.\n");
                } else if (selected == 0) {
                    *difficulty = (ENGINE_DIFFICULTY)((*difficulty +
                        (api->Input.KeyPressed[0x50] ? 2 : 1)) % 3);
                    lk_platform_log(*difficulty == ENGINE_DIFFICULTY_EASY ? "Main menu: difficulty easy.\n" :
                        *difficulty == ENGINE_DIFFICULTY_NORMAL ? "Main menu: difficulty normal.\n" :
                        "Main menu: difficulty hard.\n");
                } else if (selected == 1) {
                    *music_enabled = !*music_enabled;
                    if (title_sound(api, *music_enabled) != 0) return -1;
                    lk_platform_log(*music_enabled ? "Options: music on.\n" : "Options: music off.\n");
                } else if (selected == 2) {
                    *sound_enabled = !*sound_enabled;
                    lk_platform_log(*sound_enabled ? "Main menu: sound on.\n" : "Main menu: sound off.\n");
                } else {
                    pending = *controls;
                    binding = 0;
                    duplicate_key = 0;
                    options = 2;
                    lk_platform_log("Options: redefining keys.\n");
                }
            }
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
        if ((!options &&
                (text(144, 120, "START") != 0 || text(144, 136, "OPTIONS") != 0 ||
                 text(32, 168, "    @ 1994 Virgin Interactive") != 0 ||
                 text(32, 176, "   Entertainment (Europe) Ltd.") != 0 ||
                 text(32, 184, " @ 1994 The Walt Disney Company") != 0 ||
                 text(32, 192, "PC version - East Point Software") != 0)) ||
            (options == 1 &&
                (text(80, 80, "DIFFICULTY") != 0 ||
                 text(192, 80, *difficulty == ENGINE_DIFFICULTY_EASY ? "EASY" :
                    *difficulty == ENGINE_DIFFICULTY_NORMAL ? "NORMAL" : "DIFFICULT") != 0 ||
                 text(80, 96, "MUSIC") != 0 ||
                 text(192, 96, *music_enabled ? "YES" : "NO") != 0 ||
                 text(80, 112, "SOUND EFFECTS") != 0 ||
                 text(192, 112, *sound_enabled ? "YES" : "NO") != 0 ||
                 text(80, 128, "REDEFINE KEYS") != 0 ||
                 text(80, 144, "EXIT") != 0)) ||
            (options == 2 && binding_screen(&pending, binding, duplicate_key) != 0) ||
            (options != 2 && render_draw_sprite(sun, sun_size, 0, selector_x - (options ? 64 : 0),
                (options ? 72 : 112) + (int)selected * 16, view) != 0)) {
            lk_platform_log("Lion King: cannot draw original menu selection.\n");
            return -1;
        }
        lk_platform_present(view, colors);
        if (title_service() != 0) return -1;
    }
}
