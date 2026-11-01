#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "dos64/platform.h"
#include "engine/resources.h"
#include "engine/sprites.h"
#include "engine/tiles.h"
#include "libs/vga.h"

int __attribute__((ms_abi)) start(const DOS64_API *api);

static DOS64_API api;
static unsigned int iteration, shown;
static unsigned long long now;
static unsigned char map[347816], sprite[20419], packed[65536];
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

static void __attribute__((ms_abi)) write_text(const char *text)
{
    if (strstr(text, "invalid") || strstr(text, "cannot")) {
        ++failures;
    }
}
static void * __attribute__((ms_abi)) open_file(const char *path, const char *mode)
{
    assert(strcmp(path, "LIONKING.EPF") == 0);
    return fopen("data/LIONKING.EPF", mode);
}
static int __attribute__((ms_abi)) close_file(void *file) { return fclose(file); }
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
    now += milliseconds * 1000000ULL;
}
static unsigned long long __attribute__((ms_abi)) time_ns(void) { return now; }
static int __attribute__((ms_abi)) select_layer(int layer) { assert(layer == 0); return 0; }
static void __attribute__((ms_abi)) present(void) { ++shown; }
static void __attribute__((ms_abi)) poll_input(void)
{
    memset(api.Input.KeyDown, 0, sizeof(api.Input.KeyDown));
    memset(api.Input.KeyPressed, 0, sizeof(api.Input.KeyPressed));
    ++iteration;
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
    case 112: key = 0x29; break;
    default: break;
    }
    if (key) {
        api.Input.KeyDown[key] = 1;
        api.Input.KeyPressed[key] = (iteration != 3 && iteration != 8);
    }
    assert(iteration <= 112);
}
static void __attribute__((ms_abi)) draw_image(const DOS64_COLOR *image,
    unsigned int width, unsigned int height, unsigned int stride,
    int x, int y, unsigned int dest_width, unsigned int dest_height)
{
    assert(width == 320 && height == 200 && stride == 320);
    assert(x == 0 && y == 40 && dest_width == 640 && dest_height == 400);
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
    memset(expected, 0, sizeof(expected));
    assert(render_map_tile_pass(map, map_size, 0, 0, 0, 0, expected) == 0);
    assert(render_map_tile_pass(map, map_size, 0, 0, 0, 1, expected) == 0);
    unsigned int frame = (iteration == 2 || iteration == 3) ? 1 :
        iteration == 10 ? frames - 1 : 0;
    unsigned short flags = (unsigned short)frame;
    int px = 140, py = 80;
    const unsigned char *entry = sprite + 2 + frame * 8;
    if (iteration >= 5 && iteration <= 8) {
        flags |= 0x8000;
        px -= (int)((unsigned int)entry[0] | (unsigned int)entry[1] << 8);
    }
    if (iteration >= 6 && iteration <= 8) {
        flags |= 0x2000;
        py -= (int)((unsigned int)entry[2] | (unsigned int)entry[3] << 8);
    }
    if (iteration != 7 && iteration != 8) {
        assert(render_draw_sprite(sprite, sprite_size, flags, px, py, expected) == 0);
    }
    for (unsigned int i = 0; i < 64000; ++i) {
        assert(image[i] == (palette[expected[i]] | 0xff000000U));
    }
}

int main(void)
{
    api.Size = sizeof(api);
    api.Version = DOS64_API_VERSION;
    api.Arguments = "";
    api.Write = write_text;
    api.Sleep = sleep_ms;
    api.Time.Nanoseconds = time_ns;
    api.Input.Poll = poll_input;
    api.Gfx.Width = 640; api.Gfx.Height = 480;
    api.Gfx.SelectLayer = select_layer;
    api.Gfx.Present = present;
    api.DrawImage = draw_image;
    api.Fs.Open = open_file; api.Fs.Close = close_file;
    api.Fs.Read = read_file; api.Fs.Seek = seek_file; api.Fs.Tell = tell_file;
    assert(resources_load_entry(&api, "LIONKING.EPF", "LEVEL1.MAP", packed, sizeof(packed),
        map, sizeof(map), &dictionary, &map_size) == 0);
    assert(vga_load_palette(map, map_size, palette) == 0);
    assert(vga_load_palette_rgb(map, map_size, original_rgb) == 0);
    memcpy(fade_rgb, original_rgb, sizeof(fade_rgb));
    assert(resources_load_entry(&api, "LIONKING.EPF", "SYIDLE1.MCH", packed, sizeof(packed),
        sprite, sizeof(sprite), &dictionary, &sprite_size) == 0);
    frames = (unsigned int)sprite[0] | (unsigned int)sprite[1] << 8;
    assert(frames > 1);
    assert(start(&api) == 0);
    assert(iteration == 112 && shown == 111 && failures == 0);
    printf("PASS: DOS64 start with real assets (%u frames), all 7104000 ARGB pixels, "
        "frame stepping, held keys, flips, hide/reset, timed fades/interruption and Escape\n", frames);
    return 0;
}
