#include <assert.h>
#include <stdio.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static unsigned int spawned;
static ENGINE_FALLING_OBJECT during;
static RENDER_POOL during_renders;
static const RENDER_BOUNDS window = {-1000, -1000, 1000, 1000};

static void spawn_during_update(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    if (spawned) {
        return;
    }
    ENGINE_OBJECT *created;
    assert(engine_spawn_falling(pool, &during_renders, &during,
        (RENDER_OWNER){10, 20}, &window, 0, &created) == 0);
    assert(pool->current == object && created->context == &during);
    assert(during.motion.velocity_y == 0x4e00);
    ++spawned;
}

static const ENGINE_OBJECT_BEHAVIOR spawning_behavior = {spawn_during_update};

int main(void)
{
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    ENGINE_FALLING_OBJECT state[RENDER_NODE_COUNT];
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    ENGINE_OBJECT *created = 0;
    ENGINE_OBJECT *sentinel = engine_acquire_object(&pool, 0);
    pool.current = pool.tracked = sentinel;
    pool.update_status = -7;
    assert(engine_spawn_falling(&pool, &renders, &state[0],
        (RENDER_OWNER){-100, -100}, &window, -3, &created) == 0);
    assert(pool.current == sentinel && pool.tracked == sentinel && pool.update_status == -7);
    assert(created && created->context == &state[0] && created->behavior == &engine_falling_behavior);
    assert(state[0].owner.x == -100 && state[0].owner.y == -100 &&
        state[0].motion.fraction_y == 0x4e00 && state[0].motion.velocity_y == 0x4e00);
    assert(state[0].node->order == -3 && state[0].node->flags == 0 &&
        state[0].node->pass_flags == 0 && state[0].initialized);
    assert(state[0].node->parts == animation_falling_data && state[0].node->parts_size == 20);
    assert(state[0].animation.script.position == 0x1427a &&
        state[0].animation.visual.remaining == 99);
    ENGINE_OBJECT *first = created;
    assert(engine_spawn_falling(&pool, &renders, &state[0],
        (RENDER_OWNER){0, 0}, &window, 0, &created) == -1);
    assert(created == first && first->active && state[0].owner.x == -100);
    for (unsigned int i = 1; i < RENDER_NODE_COUNT; ++i) {
        assert(engine_spawn_falling(&pool, &renders, &state[i],
            (RENDER_OWNER){0, 0}, &window, (short)(i % 3), &created) == 0);
    }
    assert(!renders.free_head);
    ENGINE_FALLING_OBJECT extra = {0};
    ENGINE_OBJECT *free_before = pool.free_head;
    assert(engine_spawn_falling(&pool, &renders, &extra,
        (RENDER_OWNER){0, 0}, &window, 0, &created) == -1);
    assert(pool.free_head == free_before && !extra.node);
    short previous_order = -32768;
    unsigned int nodes = 0;
    for (RENDER_NODE *node = renders.head; node; node = node->next) {
        assert(node->order >= previous_order);
        previous_order = node->order;
        ++nodes;
    }
    assert(nodes == 80);
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY; ++i) {
        assert(engine_acquire_object(&pool, 0));
    }
    RENDER_NODE *render_free = renders.free_head;
    assert(engine_spawn_falling(&pool, &renders, &extra,
        (RENDER_OWNER){0, 0}, &window, 0, &created) == -1 && renders.free_head == render_free);
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    sentinel = engine_acquire_object(&pool, 0);
    pool.current = sentinel;
    assert(engine_spawn_falling(&pool, &renders, &extra,
        (RENDER_OWNER){1001, 0}, &window, 0, &created) == 1);
    assert(!created && !extra.node && pool.current == sentinel &&
        pool.head == sentinel && pool.tail == sentinel && !renders.head);
    assert(extra.motion.velocity_y == 0);
    assert(engine_spawn_falling(&pool, &renders, &extra,
        (RENDER_OWNER){0, 0}, 0, 0, &created) == -1);
    engine_initialize_objects(&pool);
    render_initialize_nodes(&during_renders);
    sentinel = engine_acquire_object(&pool, &spawning_behavior);
    pool.tracked = sentinel;
    DOS64_INPUT keys = {0};
    assert(engine_update_objects(&pool, &keys) == 0);
    assert(spawned == 1 && pool.tracked == sentinel && sentinel->next == pool.tail);
    /* The appended object is visited later in the same original traversal. */
    assert(during.motion.velocity_y == 0x9c00 && during.motion.fraction_y == 0xea00 &&
        during.animation.visual.remaining == 98);
    assert(engine_update_objects(&pool, &keys) == 0 && spawned == 1 &&
        during.motion.velocity_y == 0xea00);
    puts("PASS: original falling definition DS:0x162fe spawn path, immediate behavior, "
        "80 render nodes, object exhaustion, initialization culling, current restoration "
        "and same-tick spawned-object traversal");
    return 0;
}
