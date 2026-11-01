/* Extracted pseudocode from pseiudo.c; not a compilable translation unit. */
/* Video BIOS, VGA DAC and video-memory routines. */

#ifdef LK_DOS64_NATIVE
#include "vga.h"

int vga_load_palette(const unsigned char *map, unsigned int size, DOS64_COLOR *palette)
{
    if (!map || !palette || size < 4) {
        return -1;
    }
    /* Game MAP loader at 0x115c2 uses its first dword as the palette offset. */
    unsigned int offset = (unsigned int)map[0] | (unsigned int)map[1] << 8 |
        (unsigned int)map[2] << 16 | (unsigned int)map[3] << 24;
    if (offset < 4 || offset > size || size - offset < 768) {
        return -1;
    }
    for (unsigned int i = 0; i < 768; ++i) {
        if (map[offset + i] > 63) {
            return -1;
        }
    }
    for (unsigned int i = 0; i < 256; ++i) {
        const unsigned char *rgb = map + offset + i * 3;
        palette[i] = DOS64_COLOR_ARGB(255, rgb[0] * 255 / 63,
            rgb[1] * 255 / 63, rgb[2] * 255 / 63);
    }
    return 0;
}
#else
#include "vga_legacy.inc"
#endif
