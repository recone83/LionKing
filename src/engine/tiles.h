#ifndef LIONKING_TILES_H
#define LIONKING_TILES_H
#include "render.h"

/* A single MAP layer, not the full scene/parallax orchestration. */
int render_map_tile_pass(const unsigned char *map, unsigned int size,
    unsigned int layer, unsigned int camera_x, unsigned int camera_y,
    int flagged, unsigned char *pixels);

typedef struct {
    const unsigned char *map;
    unsigned int size;
    const unsigned char *contours;
    unsigned int width;
    unsigned int height;
    unsigned int plane_size;
    unsigned int table;
} ENGINE_MAP_COLLISION;

typedef struct {
    short supported;
    short delta_y;
    unsigned char kind;
    unsigned char surface_kind;
} ENGINE_MAP_GROUND;

int engine_map_collision_initialize(ENGINE_MAP_COLLISION *collision,
    const unsigned char *map, unsigned int size,
    const unsigned char *contours, unsigned int contour_size);
int engine_map_ground(const ENGINE_MAP_COLLISION *collision, short x, short y,
    ENGINE_MAP_GROUND *ground);
int engine_map_kind(const ENGINE_MAP_COLLISION *collision, short x, short y,
    unsigned short *kind);
int engine_map_ledge_height(const ENGINE_MAP_COLLISION *collision,
    short x, short y, short *height);
int engine_map_edge(const ENGINE_MAP_COLLISION *collision, const RENDER_NODE *node,
    short *hit, short *kind, short *x, short *y);
int engine_map_lateral(const ENGINE_MAP_COLLISION *collision, RENDER_OWNER *owner,
    unsigned short flags, unsigned char flags_high, unsigned char *blocked);
int engine_map_ceiling(const ENGINE_MAP_COLLISION *collision, const RENDER_NODE *node,
    short x, short y, short *hit);

#endif
