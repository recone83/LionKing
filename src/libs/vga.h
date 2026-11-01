#ifndef LIONKING_VGA_H
#define LIONKING_VGA_H

#include "dos64_api.h"

int vga_load_palette(const unsigned char *map, unsigned int size, DOS64_COLOR *palette);

#endif
