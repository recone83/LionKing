#ifndef LIONKING_VGA_H
#define LIONKING_VGA_H

#include "dos64_api.h"

int vga_load_palette(const unsigned char *map, unsigned int size, DOS64_COLOR *palette);
int vga_load_palette_rgb(const unsigned char *map, unsigned int size,
    unsigned char *rgb);
int vga_palette_colors(const unsigned char *rgb, DOS64_COLOR *palette);

typedef struct {
    unsigned char current[768];
    unsigned char source[768];
    unsigned char target[768];
    unsigned int phase;
    int active;
} VGA_FADE;

int vga_fade_initialize(VGA_FADE *fade, const unsigned char *rgb);
int vga_fade_begin(VGA_FADE *fade, const unsigned char *target);
int vga_fade_tick(VGA_FADE *fade);

typedef int (*VGA_PRESENT)(void *context, const unsigned char *pixels,
    const DOS64_COLOR *palette);

typedef struct {
    const unsigned char *buffer;
    unsigned int size;
    unsigned short camera_y;
    const DOS64_COLOR *palette;
    VGA_PRESENT present;
    void *context;
} VGA_FRAME;

int vga_present_frame(VGA_FRAME *frame);

#endif
