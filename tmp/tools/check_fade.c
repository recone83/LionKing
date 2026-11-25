#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "libs/vga.h"

static VGA_FADE fade;
static unsigned char rgb[768], target[768];
static DOS64_COLOR palette[256];

int main(void)
{
    unsigned int checked = 0;
    for (unsigned int source = 0; source < 64; ++source) {
        for (unsigned int destination = 0; destination < 64; ++destination) {
            memset(rgb, source, sizeof(rgb));
            memset(target, destination, sizeof(target));
            assert(vga_fade_initialize(&fade, rgb) == 0);
            assert(vga_fade_begin(&fade, target) == 0);
            for (unsigned int phase = 0; fade.active; ++phase) {
                assert(phase <= 64);
                assert(vga_fade_tick(&fade) == 1);
                int product = ((int)destination - (int)source) * (int)phase;
                unsigned int ax = (unsigned int)product & 0xffff;
                unsigned char expected = (unsigned char)((ax >> 6) + source);
                for (unsigned int i = 0; i < 768; ++i) {
                    assert(fade.current[i] == expected);
                }
                assert(vga_palette_colors(fade.current, palette) == 0);
                unsigned int component = expected * 255 / 63;
                assert(palette[0] == DOS64_COLOR_ARGB(255, component, component, component));
                ++checked;
            }
            assert(memcmp(fade.current, target, sizeof(target)) == 0);
            assert(vga_fade_tick(&fade) == 0);
        }
    }
    memset(rgb, 63, sizeof(rgb)); memset(target, 0, sizeof(target));
    assert(vga_fade_initialize(&fade, rgb) == 0);
    assert(vga_fade_begin(&fade, target) == 0);
    for (unsigned int i = 0; i < 20; ++i) {
        assert(vga_fade_tick(&fade) == 1);
    }
    unsigned char intermediate = fade.current[0];
    assert(intermediate > 0 && intermediate < 63);
    assert(vga_fade_begin(&fade, rgb) == 0);
    assert(fade.source[0] == intermediate && fade.phase == 0);
    assert(vga_fade_tick(&fade) == 1 && fade.current[0] == intermediate);
    VGA_FADE before = fade;
    target[500] = 64;
    assert(vga_fade_begin(&fade, target) == -1 && memcmp(&fade, &before, sizeof(fade)) == 0);
    assert(vga_palette_colors(target, palette) == -1);
    assert(vga_fade_initialize(&fade, target) == -1);
    fade.phase = 65;
    assert(vga_fade_tick(&fade) == -1);
    assert(vga_fade_tick(0) == -1);
    printf("PASS: all 4096 six-bit fade pairs, %u exact x86 interpolation phases, "
        "early completion, interruption and invalid input\n", checked);
    return 0;
}
