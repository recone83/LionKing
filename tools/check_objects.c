#include <assert.h>
#include <stdio.h>
#include "engine/objects.h"

static unsigned int calls;
static void remove_self(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    assert(pool->current == object);
    ++calls;
    pool->current = 0;
}
static void remain(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    assert(pool->current == object);
    ++calls;
    ++object->data[0];
}

int main(void)
{
    ENGINE_OBJECT_POOL pool;
    ENGINE_OBJECT foreign = {0};
    engine_initialize_objects(&pool);
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY; ++i) {
        ENGINE_OBJECT *object = engine_acquire_object(&pool, 0);
        assert(object == &pool.objects[i] && object->active);
        assert(object->context == 0);
        assert(object->previous == (i ? &pool.objects[i - 1] : 0));
        for (unsigned int j = 0; j < sizeof(object->data); ++j) {
            assert(object->data[j] == 0);
        }
        object->data[0] = 123;
        object->context = &foreign;
    }
    assert(engine_acquire_object(&pool, 0) == 0);
    assert(engine_release_object(&pool, &foreign) == -1);
    assert(engine_release_object(&pool, &pool.objects[40]) == 0);
    assert(pool.objects[39].next == &pool.objects[41]);
    assert(pool.objects[41].previous == &pool.objects[39]);
    assert(engine_release_object(&pool, &pool.objects[40]) == -1);
    assert(engine_acquire_object(&pool, 0) == &pool.objects[40]);
    assert(pool.tail == &pool.objects[40] && pool.tail->data[0] == 0);
    assert(pool.tail->context == 0);
    while (pool.head) {
        assert(engine_release_object(&pool, pool.head) == 0);
    }
    assert(pool.tail == 0);
    assert(engine_acquire_object(&pool, 0) != 0);
    engine_initialize_objects(&pool);
    assert(pool.head == 0 && pool.tail == 0 && pool.free_head == &pool.objects[0]);
    ENGINE_OBJECT_BEHAVIOR remove = {remove_self}, keep = {remain};
    ENGINE_OBJECT *a = engine_acquire_object(&pool, &remove);
    ENGINE_OBJECT *b = engine_acquire_object(&pool, &keep);
    ENGINE_OBJECT *c = engine_acquire_object(&pool, &remove);
    pool.tracked = a;
    DOS64_INPUT keys = {0};
    keys.KeyDown[0x52] = 1;
    assert(engine_update_objects(&pool, &keys) == 0);
    assert(calls == 3 && pool.head == b && pool.tail == b);
    assert(!a->active && !c->active && pool.tracked == 0);
    assert(pool.controls == 1 && pool.update_count == 1 && b->data[0] == 1);
    assert(engine_update_objects(&pool, &keys) == 0);
    assert(calls == 4 && pool.controls == 0 && b->data[0] == 2);
    pool.update_count = 65535;
    assert(engine_update_objects(&pool, &keys) == 0 && pool.update_count == 0);
    puts("PASS: 96-object pool, exhaustion, unlinking, recycling, reset and invalid release");
    puts("PASS: object callbacks, removal traversal, tracked pointer, input and counter wrap");
    return 0;
}
