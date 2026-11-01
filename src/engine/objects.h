#ifndef LIONKING_OBJECTS_H
#define LIONKING_OBJECTS_H
#include "input.h"

#define ENGINE_OBJECT_CAPACITY 96U

typedef struct ENGINE_OBJECT ENGINE_OBJECT;
typedef struct ENGINE_OBJECT_POOL ENGINE_OBJECT_POOL;
typedef struct {
    void (*update)(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object);
} ENGINE_OBJECT_BEHAVIOR;

struct ENGINE_OBJECT {
    ENGINE_OBJECT *previous;
    ENGINE_OBJECT *next;
    const ENGINE_OBJECT_BEHAVIOR *behavior;
    unsigned char data[116];
    unsigned int active;
    void *context;
};

struct ENGINE_OBJECT_POOL {
    ENGINE_OBJECT objects[ENGINE_OBJECT_CAPACITY];
    ENGINE_OBJECT *free_head;
    ENGINE_OBJECT *head;
    ENGINE_OBJECT *tail;
    ENGINE_OBJECT *current;
    ENGINE_OBJECT *tracked;
    unsigned short update_count;
    unsigned short controls;
    ENGINE_INPUT input;
    int update_status;
};

void engine_initialize_objects(ENGINE_OBJECT_POOL *pool);
ENGINE_OBJECT *engine_acquire_object(ENGINE_OBJECT_POOL *pool,
    const ENGINE_OBJECT_BEHAVIOR *behavior);
int engine_release_object(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object);
int engine_update_objects(ENGINE_OBJECT_POOL *pool, const DOS64_INPUT *keys);

#endif
