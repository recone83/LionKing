#ifndef LIONKING_OSTRICH_ROUTE_H
#define LIONKING_OSTRICH_ROUTE_H

#include <stdint.h>

typedef struct {
    const unsigned char *records;
    unsigned int size;
    unsigned int offset;
    unsigned int finished;
} ENGINE_OSTRICH_ROUTE;

typedef struct {
    uint32_t constructor;
    uint32_t definition;
    short x;
    short y;
} ENGINE_OSTRICH_OBSTACLE;

typedef struct {
    unsigned int flags;
    unsigned int count;
    ENGINE_OSTRICH_OBSTACLE obstacles[4];
} ENGINE_OSTRICH_EVENT;

enum {
    ENGINE_OSTRICH_WAIT = 0,
    ENGINE_OSTRICH_EVENT_READY = 1,
    ENGINE_OSTRICH_FINISHED = 2
};

int engine_ostrich_route_initialize(ENGINE_OSTRICH_ROUTE *route,
    unsigned int marker_type);
int engine_ostrich_route_tick(ENGINE_OSTRICH_ROUTE *route, short distance,
    short camera_x, ENGINE_OSTRICH_EVENT *event);

#endif
