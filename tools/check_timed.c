#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static DOS64_INPUT keys;
static const RENDER_BOUNDS window = {-32768, -32768, 32767, 32767};

static ENGINE_OBJECT *setup(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_TIMED_OBJECT *timed, ENGINE_FALLING_OBJECT *child)
{
    engine_initialize_objects(pool);
    render_initialize_nodes(renders);
    *timed = (ENGINE_TIMED_OBJECT){0};
    *child = (ENGINE_FALLING_OBJECT){0};
    timed->body.owner = (RENDER_OWNER){100, -32768};
    timed->body.visibility = &window;
    timed->body.render_pool = renders;
    timed->body.node = render_acquire_node(renders, &timed->body.owner, 0, 0,
        animation_falling_data + 0xe4c8 - ANIMATION_FALLING_BASE, 20);
    timed->child = child;
    timed->child_order = -3;
    ENGINE_OBJECT *object = engine_acquire_object(pool, &engine_timed_behavior);
    assert(object);
    object->context = timed;
    pool->tracked = object;
    return object;
}

int main(void)
{
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    ENGINE_TIMED_OBJECT timed;
    ENGINE_FALLING_OBJECT child;
    ENGINE_OBJECT *parent = setup(&pool, &renders, &timed, &child);
    uint32_t position = UINT32_C(0x80000000), velocity = 0;
    for (unsigned int tick = 1; tick <= 65545; ++tick) {
        unsigned short before_y = (unsigned short)timed.body.owner.y;
        assert(engine_update_objects(&pool, &keys) == 0);
        velocity += 0x4e00;
        if (velocity > 0x70000) {
            velocity = 0x70000;
        }
        position += velocity;
        assert(((uint32_t)(unsigned short)timed.body.owner.y << 16 |
            timed.body.motion.fraction_y) == position);
        assert(timed.body.animation.counter == (unsigned short)(10 - tick));
        assert(timed.body.animation.script.position == 0x1427a);
        assert(timed.body.animation.visual.remaining == 99 - (tick - 1) % 100);
        assert(timed.body.node->parts == animation_falling_data + 0xe4c8 - ANIMATION_FALLING_BASE);
        assert(pool.tracked == parent && parent->active);
        if (tick < 10) {
            assert(parent == pool.tail && !child.node);
        } else {
            assert(parent->next == pool.tail && pool.tail->context == &child);
            if (tick == 10) {
                assert((unsigned short)child.owner.y == (unsigned short)(before_y - 16));
                assert(child.owner.x == 100 && child.motion.velocity_y == 0x9c00 &&
                    child.motion.fraction_y == 0xea00);
                assert(child.node->order == -3 && child.animation.visual.remaining == 98);
            }
        }
    }
    assert(timed.body.animation.counter == 1);
    velocity = timed.body.motion.velocity_y;
    assert(engine_update_objects(&pool, &keys) == -1 &&
        timed.body.animation.counter == 0 && timed.body.motion.velocity_y == velocity);
    assert(parent->next == pool.tail && pool.tail->context == &child);
    parent = setup(&pool, &renders, &timed, &child);
    for (unsigned int i = 0; i < 9; ++i) {
        assert(engine_update_objects(&pool, &keys) == 0);
    }
    timed.child = 0;
    velocity = timed.body.motion.velocity_y;
    assert(engine_update_objects(&pool, &keys) == -1 && parent->active);
    assert(timed.body.animation.counter == 0 && timed.body.motion.velocity_y == velocity);
    parent = setup(&pool, &renders, &timed, &child);
    timed.body.owner.x = 0;
    timed.body.owner.y = 100;
    RENDER_BOUNDS small_window = {-100, -100, 100, 100};
    timed.body.visibility = &small_window;
    assert(engine_update_objects(&pool, &keys) == 0);
    timed.body.owner.y = 101;
    unsigned short counter = timed.body.animation.counter;
    assert(engine_update_objects(&pool, &keys) == 0 && !parent->active);
    assert(timed.body.animation.counter == counter && !child.node && !pool.tracked);
    parent = setup(&pool, &renders, &timed, &child);
    for (unsigned int i = 0; i < 9; ++i) {
        assert(engine_update_objects(&pool, &keys) == 0);
    }
    while (pool.free_head) {
        assert(engine_acquire_object(&pool, 0));
    }
    assert(engine_update_objects(&pool, &keys) == -1 && parent->active && !child.node);
    puts("PASS: original 0x2881d timed behavior, 65545 updates, exact 10-update spawn "
        "before gravity, child immediate+same-tick update, full counter wrap, "
        "active child-state reuse rejected at update 65546, culling and errors");
    return 0;
}
