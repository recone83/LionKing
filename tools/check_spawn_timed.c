#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static const RENDER_BOUNDS window = {-32768, -32768, 32767, 32767};
static DOS64_INPUT keys;

int main(void)
{
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    ENGINE_TIMED_OBJECT timed = {0};
    ENGINE_FALLING_OBJECT child = {0};
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    ENGINE_OBJECT *sentinel = engine_acquire_object(&pool, 0);
    pool.current = pool.tracked = sentinel;
    pool.update_status = -5;
    ENGINE_OBJECT *parent = 0;
    assert(engine_spawn_timed(&pool, &renders, &timed, &child,
        (RENDER_OWNER){15, -100}, &window, 7, -7, &parent) == 0);
    assert(parent && parent->behavior == &engine_timed_behavior &&
        parent->context == &timed && parent->context == &timed.body);
    assert(pool.current == sentinel && pool.tracked == sentinel && pool.update_status == -5);
    assert(timed.child == &child && timed.child_order == -7);
    assert(timed.body.node->order == 7 && timed.body.node->parts ==
        animation_falling_data + 0xe4c8 - ANIMATION_FALLING_BASE);
    assert(timed.body.motion.velocity_y == 0x4e00 && timed.body.motion.fraction_y == 0x4e00 &&
        timed.body.animation.counter == 9 && timed.body.animation.visual.remaining == 99);
    ENGINE_OBJECT *original = parent;
    assert(engine_spawn_timed(&pool, &renders, &timed, &child,
        (RENDER_OWNER){0, 0}, &window, 0, 0, &parent) == -1);
    assert(parent == original && timed.child_order == -7 && timed.body.node->order == 7);
    pool.tracked = parent;
    for (unsigned int tick = 1; tick <= 1000; ++tick) {
        unsigned short before_y = (unsigned short)timed.body.owner.y;
        assert(engine_update_objects(&pool, &keys) == 0 && pool.tracked == parent);
        assert(timed.body.animation.counter == (unsigned short)(9 - tick));
        if (tick < 9) {
            assert(!child.node && pool.tail == parent);
        } else {
            assert(child.node && child.node->order == -7 && pool.tail->context == &child);
            if (tick == 9) {
                assert((unsigned short)child.owner.y == (unsigned short)(before_y - 16) &&
                    child.owner.x == 15 && child.motion.velocity_y == 0x9c00 &&
                    child.motion.fraction_y == 0xea00);
            }
        }
    }
    ENGINE_TIMED_OBJECT other = {0};
    ENGINE_OBJECT *unchanged = parent;
    assert(engine_spawn_timed(&pool, &renders, &other, &child,
        (RENDER_OWNER){0, 0}, &window, 0, 0, &unchanged) == -1);
    assert(unchanged == parent && !other.body.node);
    assert(engine_spawn_timed(&pool, &renders, &other, &other.body,
        (RENDER_OWNER){0, 0}, &window, 0, 0, &unchanged) == -1);
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    RENDER_BOUNDS small_window = {-10, -10, 10, 10};
    assert(engine_spawn_timed(&pool, &renders, &other, &child,
        (RENDER_OWNER){11, 0}, &small_window, 0, 0, &unchanged) == 1);
    assert(!unchanged && !other.body.node && !pool.head && !renders.head);
    assert(other.body.animation.counter == 10 && other.body.motion.velocity_y == 0);
    while (pool.free_head) {
        assert(engine_acquire_object(&pool, 0));
    }
    RENDER_NODE *free_before = renders.free_head;
    assert(engine_spawn_timed(&pool, &renders, &other, &child,
        (RENDER_OWNER){0, 0}, &window, 0, 0, &unchanged) == -1);
    assert(renders.free_head == free_before && !other.body.node);
    puts("PASS: original DS:0x162f0 parent spawn, immediate counter 9, "
        "child on ninth dispatcher tick before parent gravity, 1000 chain updates, "
        "current restoration, duplicate-state rejection, initialization culling and exhaustion");
    return 0;
}
