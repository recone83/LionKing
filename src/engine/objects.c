/* Native reconstruction of the original pool, not a general allocator. */
#include "objects.h"

void engine_initialize_objects(ENGINE_OBJECT_POOL *pool)
{
    pool->head = pool->tail = 0;
    pool->current = pool->tracked = 0;
    pool->update_count = pool->controls = 0;
    pool->update_status = 0;
    input_initialize(&pool->input);
    pool->free_head = &pool->objects[0];
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY; ++i) {
        ENGINE_OBJECT *object = &pool->objects[i];
        object->previous = i ? &pool->objects[i - 1] : 0;
        object->next = i + 1 < ENGINE_OBJECT_CAPACITY ? &pool->objects[i + 1] : 0;
        object->behavior = 0;
        object->active = 0;
        object->context = 0;
    }
}

ENGINE_OBJECT *engine_acquire_object(ENGINE_OBJECT_POOL *pool,
    const ENGINE_OBJECT_BEHAVIOR *behavior)
{
    ENGINE_OBJECT *object = pool->free_head;
    if (!object) {
        return 0; /* The original returns null on exhaustion. */
    }
    pool->free_head = object->next;
    object->previous = pool->tail;
    object->next = 0;
    if (pool->tail) {
        pool->tail->next = object;
    } else {
        pool->head = object;
    }
    pool->tail = object;
    object->behavior = behavior;
    object->active = 1;
    object->context = 0;
    for (unsigned int i = 0; i < sizeof(object->data); ++i) {
        object->data[i] = 0;
    }
    return object;
}

int engine_release_object(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    int owned = 0;
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY; ++i) {
        if (object == &pool->objects[i]) {
            owned = 1;
            break;
        }
    }
    if (!owned || !object->active) {
        return -1;
    }
    if (object->previous) {
        object->previous->next = object->next;
    } else {
        pool->head = object->next;
    }
    if (object->next) {
        object->next->previous = object->previous;
    } else {
        pool->tail = object->previous;
    }
    object->previous = 0;
    object->next = pool->free_head;
    if (pool->free_head) {
        pool->free_head->previous = object;
    }
    pool->free_head = object;
    object->active = 0;
    object->context = 0;
    return 0;
}

int engine_update_objects(ENGINE_OBJECT_POOL *pool, const DOS64_INPUT *keys)
{
    if (!pool || !keys) {
        return -1;
    }
    ++pool->update_count;
    pool->update_status = 0;
    if (input_poll_controls(&pool->input, keys) != 0) {
        return -1;
    }
    pool->controls = pool->input.pressed;
    ENGINE_OBJECT *object = pool->head;
    while (object) {
        if (!object->behavior || !object->behavior->update) {
            object = object->next;
            continue;
        }
        pool->current = object;
        object->behavior->update(pool, object);
        if (pool->update_status != 0) {
            return pool->update_status;
        }
        if (object == pool->tracked) {
            pool->tracked = pool->current;
        }
        if (!pool->current) {
            ENGINE_OBJECT *next = object->next;
            if (engine_release_object(pool, object) != 0) {
                return -1;
            }
            object = next;
        } else {
            object = object->next;
        }
    }
    return 0;
}
