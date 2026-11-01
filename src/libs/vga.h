#ifndef LIONKING_VGA_H
#define LIONKING_VGA_H

#include "dos64_api.h"

int vga_load_palette(const unsigned char *map, unsigned int size, DOS64_COLOR *palette);

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
