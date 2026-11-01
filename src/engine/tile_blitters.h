#ifndef LIONKING_TILE_BLITTERS_H
#define LIONKING_TILE_BLITTERS_H

/* Coordinates are the top-left of the full tile, even for a row window. */
int render_blit_tile(const unsigned char *tile, unsigned short flags, int x, int y,
    unsigned int first_row, unsigned int rows, int transparent, unsigned char *pixels);

#endif
