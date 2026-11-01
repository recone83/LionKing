/* Extracted pseudocode from pseiudo.c; not a compilable translation unit. */
/* Video BIOS, VGA DAC and video-memory routines. */

#ifdef LK_DOS64_NATIVE
#include "vga.h"

int vga_present_frame(VGA_FRAME *frame)
{
    if (!frame || !frame->buffer || !frame->palette || !frame->present) {
        return -1;
    }
    unsigned int offset = ((frame->camera_y + 1U) & 7) * 320;
    if (offset > frame->size || frame->size - offset < 64000) {
        return -1;
    }
    if (frame->present(frame->context, frame->buffer + offset, frame->palette) != 0) {
        return -1;
    }
    frame->camera_y = 0;
    return 0;
}

static int palette_valid(const unsigned char *rgb)
{
    if (!rgb) {
        return 0;
    }
    for (unsigned int i = 0; i < 768; ++i) {
        if (rgb[i] > 63) {
            return 0;
        }
    }
    return 1;
}

int vga_palette_colors(const unsigned char *rgb, DOS64_COLOR *palette)
{
    if (!palette || !palette_valid(rgb)) {
        return -1;
    }
    for (unsigned int i = 0; i < 256; ++i) {
        palette[i] = DOS64_COLOR_ARGB(255, rgb[i * 3] * 255 / 63,
            rgb[i * 3 + 1] * 255 / 63, rgb[i * 3 + 2] * 255 / 63);
    }
    return 0;
}

int vga_load_palette_rgb(const unsigned char *map, unsigned int size, unsigned char *rgb)
{
    if (!map || !rgb || size < 4) {
        return -1;
    }
    /* Game MAP loader at 0x115c2 uses its first dword as the palette offset. */
    unsigned int offset = (unsigned int)map[0] | (unsigned int)map[1] << 8 |
        (unsigned int)map[2] << 16 | (unsigned int)map[3] << 24;
    if (offset < 4 || offset > size || size - offset < 768) {
        return -1;
    }
    if (!palette_valid(map + offset)) {
        return -1;
    }
    for (unsigned int i = 0; i < 768; ++i) {
        rgb[i] = map[offset + i];
    }
    return 0;
}

int vga_load_palette(const unsigned char *map, unsigned int size, DOS64_COLOR *palette)
{
    unsigned char rgb[768];
    if (!palette || vga_load_palette_rgb(map, size, rgb) != 0) {
        return -1;
    }
    return vga_palette_colors(rgb, palette);
}

int vga_fade_initialize(VGA_FADE *fade, const unsigned char *rgb)
{
    if (!fade || !palette_valid(rgb)) {
        return -1;
    }
    for (unsigned int i = 0; i < 768; ++i) {
        fade->current[i] = fade->source[i] = fade->target[i] = rgb[i];
    }
    fade->phase = 0;
    fade->active = 0;
    return 0;
}

int vga_fade_begin(VGA_FADE *fade, const unsigned char *target)
{
    if (!fade || !palette_valid(fade->current) || !palette_valid(target)) {
        return -1;
    }
    for (unsigned int i = 0; i < 768; ++i) {
        fade->source[i] = fade->current[i];
        fade->target[i] = target[i];
    }
    fade->phase = 0;
    fade->active = 1;
    return 0;
}

int vga_fade_tick(VGA_FADE *fade)
{
    if (!fade || fade->phase > 64) {
        return -1;
    }
    if (!fade->active) {
        return 0;
    }
    if (!palette_valid(fade->source) || !palette_valid(fade->target)) {
        return -1;
    }
    int complete = 1;
    for (unsigned int i = 0; i < 768; ++i) {
        int product = ((int)fade->target[i] - fade->source[i]) * (int)fade->phase;
        /* Match low byte of signed IMUL followed by logical SHR AX,6 at 0x10693. */
        int delta = product >= 0 ? product / 64 : -((-product + 63) / 64);
        fade->current[i] = (unsigned char)(fade->source[i] + delta);
        if (fade->current[i] != fade->target[i]) {
            complete = 0;
        }
    }
    if (complete) {
        fade->active = 0;
    } else {
        ++fade->phase;
    }
    return 1;
}
#else
#include "vga_legacy.inc"
#endif
