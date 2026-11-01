#include <assert.h>
#include <stdio.h>
#include "engine/objects.h"

int main(void)
{
    ENGINE_OBJECT_POOL pool;
    ENGINE_OBJECT foreign = {0};
    engine_initialize_objects(&pool);
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY; ++i) {
        ENGINE_OBJECT *object = engine_acquire_object(&pool, 0);
        assert(object == &pool.objects[i] && object->active);
        assert(object->previous == (i ? &pool.objects[i - 1] : 0));
        for (unsigned int j = 0; j < sizeof(object->data); ++j) {
            assert(object->data[j] == 0);
        }
        object->data[0] = 123;
    }
    assert(engine_acquire_object(&pool, 0) == 0);
    assert(engine_release_object(&pool, &foreign) == -1);
    assert(engine_release_object(&pool, &pool.objects[40]) == 0);
    assert(pool.objects[39].next == &pool.objects[41]);
    assert(pool.objects[41].previous == &pool.objects[39]);
    assert(engine_release_object(&pool, &pool.objects[40]) == -1);
    assert(engine_acquire_object(&pool, 0) == &pool.objects[40]);
    assert(pool.tail == &pool.objects[40] && pool.tail->data[0] == 0);
    while (pool.head) {
        assert(engine_release_object(&pool, pool.head) == 0);
    }
    assert(pool.tail == 0);
    assert(engine_acquire_object(&pool, 0) != 0);
    engine_initialize_objects(&pool);
    assert(pool.head == 0 && pool.tail == 0 && pool.free_head == &pool.objects[0]);
    puts("PASS: 96-object pool, exhaustion, unlinking, recycling, reset and invalid release");
    return 0;
}
