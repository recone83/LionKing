#ifndef LIONKING_TILES_H
#define LIONKING_TILES_H

/* A single MAP layer, not the full scene/parallax orchestration. */
int render_map_tile_pass(const unsigned char *map, unsigned int size,
    unsigned int layer, unsigned int camera_x, unsigned int camera_y,
    int flagged, unsigned char *pixels);

#endif
