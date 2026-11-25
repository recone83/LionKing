#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dos64/platform.h"
#include "mock_layers.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "engine/assets.h"
#include "engine/animation_data.h"
#include "libs/vga.h"

int __attribute__((ms_abi)) start(const DOS64_API *api);

static DOS64_API api;
static unsigned int iteration, shown;
static unsigned long long now;
static unsigned char map[347816], sprite[32768], packed[65536];
static RESOURCE_DICTIONARY dictionary;
static unsigned char expected[LK_WIDTH * LK_HEIGHT];
static DOS64_COLOR palette[256];
static unsigned int map_size, sprite_size;
static unsigned int frames;
static unsigned int failures;
static unsigned char original_rgb[768], fade_rgb[768], fade_source[768], fade_target[768];
static unsigned int fade_phase;
static int fade_active, fade_black;
static unsigned long long serviced_ticks;
static unsigned int bank_index = ASSETS_YOUNG_IDLE_INDEX;
static unsigned int seen_banks = 1U << ASSETS_YOUNG_IDLE_INDEX;
static unsigned char idle_banks[3][32768];
static unsigned int idle_sizes[3];
static unsigned char original_idle[ANIMATION_IDLE_SIZE];
static unsigned int idle_position, idle_descriptor, idle_remaining, idle_events;
static unsigned int logged_events;
static int idle_enabled;
static unsigned long long idle_begin, previous_time, expected_updates;
static int automatic_test;
static unsigned int default_frame_changes, default_descriptor;

static unsigned int idle_u32(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8 |
        (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
}

static void reference_idle_next(void)
{
    for (;;) {
        const unsigned char *p = original_idle + idle_position - ANIMATION_IDLE_BASE;
        if (p[0] == 0xfa) {
            ++idle_events;
            idle_position += 5;
        } else if (p[0] == 0xff) {
            idle_position = idle_u32(p + 2);
        } else {
            assert(p[0] < 128);
            idle_remaining = p[0];
            idle_descriptor = idle_u32(p + 1);
            idle_position += 5;
            return;
        }
    }
}

static void load_reference_bank(unsigned int index)
{
    unsigned int slot;
    char name[13];
    assert(assets_slot_list_entry(assets_young_bank_list, sizeof(assets_young_bank_list),
        index, &slot, name) == 0);
    assert(slot == index + 6);
    assert(resources_load_entry(&api, "LIONKING.EPF", name, packed, sizeof(packed),
        sprite, sizeof(sprite), &dictionary, &sprite_size) == 0);
    frames = (unsigned int)sprite[0] | (unsigned int)sprite[1] << 8;
    assert(frames && frames <= 256);
    bank_index = index;
    seen_banks |= 1U << index;
}

static void record_log(const char *text)
{
    if (strstr(text, "Idle script event recorded;")) {
        ++logged_events;
    }
    if (strstr(text, "invalid") || strstr(text, "cannot")) {
        ++failures;
    }
}
static int preview_started;
static FILE *log_file;
static void __attribute__((ms_abi)) write_text(const char *text)
{
    if (!preview_started) {
        record_log(text);
        return;
    }
    fputs(text, stderr);
    assert(!"preview must not render console text");
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    if (strcmp(path, "LIONKING.LOG") == 0) {
        assert(strcmp(mode, "w") == 0 && !log_file);
        log_file = tmpfile();
        assert(log_file);
        return log_file;
    }
    assert(strcmp(path, "LIONKING.EPF") == 0);
    return fopen("data/LIONKING.EPF", mode);
}
static int __attribute__((ms_abi)) close_file(void *file)
{
    if (file == log_file) log_file = 0;
    return fclose(file);
}
static unsigned long long __attribute__((ms_abi)) write_file(const void *buffer,
    unsigned long long size, unsigned long long count, void *file)
{
    assert(file == log_file && size == 1);
    record_log(buffer);
    return fwrite(buffer, (size_t)size, (size_t)count, file);
}
static int __attribute__((ms_abi)) seek_file(void *file, long long offset, int whence)
{
    return fseek(file, (long)offset, whence);
}
static long long __attribute__((ms_abi)) tell_file(void *file) { return ftell(file); }
static unsigned long long __attribute__((ms_abi)) read_file(
    void *buffer, unsigned long long size, unsigned long long count, void *file)
{
    return fread(buffer, (size_t)size, (size_t)count, file);
}
static void __attribute__((ms_abi)) sleep_ms(unsigned int milliseconds)
{
    (void)milliseconds;
    assert(0);
}
static unsigned long long __attribute__((ms_abi)) time_ns(void) { return now; }
static int __attribute__((ms_abi)) select_layer(int layer) { assert(layer == 0); return 0; }
static void __attribute__((ms_abi)) set_color(DOS64_COLOR color) { (void)color; }
static void __attribute__((ms_abi)) clear(void) {}
static void __attribute__((ms_abi)) present(void) { ++shown; }
static void __attribute__((ms_abi)) poll_input(void)
{
    now += iteration >= 172 ? 20000000ULL : 10000000ULL;
    memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
    memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
    ++iteration;
    if (automatic_test) {
        if (iteration == 202) {
            api.Input.KeyDown[0x29] = api.Input.KeyPressed[0x29] = 1;
        }
        assert(iteration <= 202);
        return;
    }
    unsigned int key = 0;
    switch (iteration) {
    case 2: case 3: key = 0x4f; break;
    case 4: key = 0x50; break;
    case 5: key = 0xe2; break;
    case 6: key = 0xe0; break;
    case 7: case 8: key = 0xe1; break;
    case 9: key = 0x2c; break;
    case 10: key = 0x50; break;
    case 11: key = 0x4f; break;
    case 12: case 80: case 90: case 100: key = 0x09; break;
    case 110: key = 0x2c; break;
    case 168: case 169: key = 0x52; break;
    case 170: key = 0x4f; break;
    case 171: key = 0xe2; break;
    case 172: case 4380: key = 0x04; break;
    case 4382: key = 0x2c; break;
    case 4384: key = 0x29; break;
    default: break;
    }
    if (iteration >= 112 && iteration <= 166 && !(iteration & 1)) {
        key = 0x51;
    }
    if (key) {
        api.Input.KeyDown[key] = 1;
        api.Input.KeyPressed[key] = (iteration != 3 && iteration != 8 && iteration != 169);
    }
    assert(iteration <= 4384);
}
static void __attribute__((ms_abi)) draw_image(const DOS64_COLOR *image,
    unsigned int width, unsigned int height, unsigned int stride,
    int x, int y, unsigned int dest_width, unsigned int dest_height)
{
    if (height == 5 && stride == 60) {
        assert(width <= 60 && x == (int)(640 - (width + 4) * 2) &&
            y == 422 && dest_width == width * 2 && dest_height == 10);
        return;
    }
    if (width == 1 && height == 1) {
        assert(stride == 1 && x == 0 && y == 0 && dest_width == api.Gfx.Width &&
            dest_height == api.Gfx.Height && image[0] == 0xff000000U);
        return;
    }
    assert(width == 320 && height == 200 && stride == 320);
    assert(x == 0 && y == 40 && dest_width == 640 && dest_height == 400);
    if (automatic_test) {
        if (iteration == 1) {
            for (unsigned int i = 0; i < 3; ++i) {
                unsigned int slot;
                assert(assets_load_named_bank(&api, "LIONKING.EPF", assets_young_bank_list,
                    sizeof(assets_young_bank_list), ASSETS_YOUNG_IDLE_INDEX + i,
                    packed, sizeof(packed), idle_banks[i], sizeof(idle_banks[i]),
                    &dictionary, &slot, &idle_sizes[i]) == 0);
            }
            idle_position = ANIMATION_IDLE_START;
            reference_idle_next();
        } else {
            unsigned long long updates = previous_time * 1193182ULL /
                (11830ULL * 1000000000ULL) / 2;
            while (expected_updates < updates) {
                if (idle_remaining) {
                    --idle_remaining;
                } else {
                    reference_idle_next();
                }
                ++expected_updates;
            }
        }
        memset(expected, 0, sizeof(expected));
        assert(render_map_tile_pass(map, map_size, 0, 0, 0, 0, expected) == 0);
        assert(render_map_tile_pass(map, map_size, 0, 0, 0, 1, expected) == 0);
        const unsigned char *part = original_idle + idle_descriptor - ANIMATION_IDLE_BASE;
        unsigned int bank = part[19] - 14, index = part[18];
        assert(bank < 3);
        int anchor_x = (int)((unsigned int)part[14] | (unsigned int)part[15] << 8);
        int anchor_y = (int)((unsigned int)part[16] | (unsigned int)part[17] << 8);
        assert(render_draw_sprite(idle_banks[bank], idle_sizes[bank], (unsigned short)index,
            140 - anchor_x, 80 - anchor_y, expected) == 0);
        for (unsigned int i = 0; i < 64000; ++i) {
            assert(image[i] == (palette[expected[i]] | 0xff000000U));
        }
        if (default_descriptor != idle_descriptor) {
            ++default_frame_changes;
            default_descriptor = idle_descriptor;
        }
        previous_time = now;
        return;
    }
    if (iteration == 172) {
        for (unsigned int i = 0; i < 3; ++i) {
            unsigned int slot;
            assert(assets_load_named_bank(&api, "LIONKING.EPF", assets_young_bank_list,
                sizeof(assets_young_bank_list), ASSETS_YOUNG_IDLE_INDEX + i,
                packed, sizeof(packed), idle_banks[i], sizeof(idle_banks[i]),
                &dictionary, &slot, &idle_sizes[i]) == 0);
            assert(slot == 14 + i);
        }
        idle_enabled = 1;
        idle_begin = now;
        idle_position = ANIMATION_IDLE_START;
        reference_idle_next();
    }
    if (idle_enabled && iteration > 172) {
        unsigned long long updates = (previous_time - idle_begin) * 1193182ULL /
            (11830ULL * 1000000000ULL) / 2;
        while (expected_updates < updates) {
            if (idle_remaining) {
                --idle_remaining;
            } else {
                reference_idle_next();
            }
            ++expected_updates;
        }
    }
    if (iteration == 4380) {
        idle_enabled = 0;
        assert(idle_events >= 12 && logged_events == idle_events);
        load_reference_bank(bank_index);
    }
    unsigned long long ticks = now * 1193182ULL / (11830ULL * 1000000000ULL);
    for (unsigned long long t = serviced_ticks; t < ticks && fade_active; ++t) {
        int complete = 1;
        for (unsigned int i = 0; i < 768; ++i) {
            int product = ((int)fade_target[i] - fade_source[i]) * (int)fade_phase;
            unsigned int ax = (unsigned int)product & 0xffff;
            fade_rgb[i] = (unsigned char)((ax >> 6) + fade_source[i]);
            if (fade_rgb[i] != fade_target[i]) {
                complete = 0;
            }
        }
        ++fade_phase;
        if (complete) {
            fade_active = 0;
        }
    }
    serviced_ticks = ticks;
    if (iteration == 12 || iteration == 80 || iteration == 90 || iteration == 100) {
        fade_black = !fade_black;
        memcpy(fade_source, fade_rgb, sizeof(fade_source));
        for (unsigned int i = 0; i < 768; ++i) {
            fade_target[i] = fade_black ? 0 : original_rgb[i];
        }
        fade_active = 1; fade_phase = 0;
    }
    if (iteration == 110) {
        memcpy(fade_rgb, original_rgb, sizeof(fade_rgb));
        fade_active = fade_black = 0;
    }
    if (iteration == 79) {
        for (unsigned int i = 0; i < 768; ++i) {
            assert(fade_rgb[i] == 0);
        }
    }
    assert(vga_palette_colors(fade_rgb, palette) == 0);
    if (iteration >= 112 && iteration <= 166 && !(iteration & 1)) {
        load_reference_bank((bank_index + 1) % ASSETS_YOUNG_BANK_COUNT);
    }
    if (iteration == 168) {
        load_reference_bank((bank_index + ASSETS_YOUNG_BANK_COUNT - 1) % ASSETS_YOUNG_BANK_COUNT);
    }
    memset(expected, 0, sizeof(expected));
    assert(render_map_tile_pass(map, map_size, 0, 0, 0, 0, expected) == 0);
    assert(render_map_tile_pass(map, map_size, 0, 0, 0, 1, expected) == 0);
    unsigned int frame = (iteration == 2 || iteration == 3) ? 1 :
        iteration == 10 ? frames - 1 : (iteration == 170 || iteration == 171) ? 1 : 0;
    unsigned short flags = (unsigned short)frame;
    int px = 140, py = 80;
    const unsigned char *entry = sprite + 2 + frame * 8;
    if ((iteration >= 5 && iteration <= 8) || (iteration >= 171 && iteration < 4382)) {
        flags |= 0x8000;
        px -= (int)((unsigned int)entry[0] | (unsigned int)entry[1] << 8);
    }
    if (iteration >= 6 && iteration <= 8) {
        flags |= 0x2000;
        py -= (int)((unsigned int)entry[2] | (unsigned int)entry[3] << 8);
    }
    if (idle_enabled) {
        const unsigned char *part = original_idle + idle_descriptor - ANIMATION_IDLE_BASE;
        assert(part[0] == 1 && part[1] == 0);
        unsigned int bank = part[19] - 14, index = part[18];
        assert(bank < 3);
        const unsigned char *idle_entry = idle_banks[bank] + 2 + index * 8;
        int anchor_x = (int)((unsigned int)part[14] | (unsigned int)part[15] << 8);
        int anchor_y = (int)((unsigned int)part[16] | (unsigned int)part[17] << 8);
        int width = (int)((unsigned int)idle_entry[0] | (unsigned int)idle_entry[1] << 8);
        assert(render_draw_sprite(idle_banks[bank], idle_sizes[bank],
            (unsigned short)(index | 0x8000), 140 - width + anchor_x,
            80 - anchor_y, expected) == 0);
    } else if (iteration != 7 && iteration != 8) {
        assert(render_draw_sprite(sprite, sprite_size, flags, px, py, expected) == 0);
    }
    for (unsigned int i = 0; i < 64000; ++i) {
        assert(image[i] == (palette[expected[i]] | 0xff000000U));
    }
    previous_time = now;
}

int main(int argc, char **argv)
{
    automatic_test = argc == 2 && strcmp(argv[1], "--automatic") == 0;
    api.Size = sizeof(api);
    api.Version = DOS64_API_VERSION;
    api.Arguments = automatic_test ? "--idle" : "--manual";
    api.Write = write_text;
    api.Sleep = sleep_ms;
    api.Time.Nanoseconds = time_ns;
    api.Input.Poll = poll_input;
    api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SelectLayer = select_layer;
    api.Gfx.Present = present;
    api.DrawImage = draw_image;
    api.Gfx.SetColor = set_color; api.Gfx.Clear = clear;
    mock_install_layers(&api);
    api.Fs.Open = open_file; api.Fs.Close = close_file;
    api.Fs.Read = read_file; api.Fs.Seek = seek_file; api.Fs.Tell = tell_file;
    api.Fs.Write = write_file;
    FILE *dump = fopen("bin/obj2_data.bin", "rb");
    assert(dump && fseek(dump, ANIMATION_IDLE_BASE, SEEK_SET) == 0);
    assert(fread(original_idle, 1, sizeof(original_idle), dump) == sizeof(original_idle));
    assert(fclose(dump) == 0);
    assert(resources_load_entry(&api, "LIONKING.EPF", "LEVEL1.MAP", packed, sizeof(packed),
        map, sizeof(map), &dictionary, &map_size) == 0);
    assert(vga_load_palette(map, map_size, palette) == 0);
    assert(vga_load_palette_rgb(map, map_size, original_rgb) == 0);
    memcpy(fade_rgb, original_rgb, sizeof(fade_rgb));
    load_reference_bank(ASSETS_YOUNG_IDLE_INDEX);
    assert(frames > 1);
    unsigned int invalid_slot = 999, invalid_loaded = 999;
    assert(assets_load_named_bank(&api, "LIONKING.EPF", assets_young_bank_list,
        sizeof(assets_young_bank_list), 28, packed, sizeof(packed), sprite,
        sizeof(sprite), &dictionary, &invalid_slot, &invalid_loaded) == -1);
    assert(failures == 1 && invalid_slot == 999 && invalid_loaded == 999);
    failures = 0;
    preview_started = 1;
    assert(start(&api) == 0);
    assert(!log_file);
    if (automatic_test) {
        assert(iteration == 202 && shown == 201 && failures == 0);
        assert(default_frame_changes >= 15 && expected_updates >= 100);
        printf("PASS: --idle entry animates without any keypress, %u descriptor changes, "
            "%llu original-rate updates, all 12864000 pixels verified\n",
            default_frame_changes, expected_updates);
        return 0;
    }
    assert(iteration == 4384 && shown == 4383 && failures == 0);
    assert(seen_banks == (1U << ASSETS_YOUNG_BANK_COUNT) - 1);
    assert(expected_updates > 4070 && logged_events >= 12);
    puts("PASS: DOS64 start, 28 banks, 280512000 exact ARGB pixels, 2 original idle loops, "
        "diagnostic events, manual-mode return, controls, fades and Escape");
    return 0;
}
