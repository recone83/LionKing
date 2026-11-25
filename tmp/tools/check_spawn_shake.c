#include <assert.h>
#include <stdio.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static unsigned int impacts;
static int impact(void *context)
{
    assert(context == &impacts);
    ++impacts;
    return 0;
}

int main(void)
{
    DOS64_INPUT keys = {0};
    for (unsigned int enabled = 0; enabled < 2; ++enabled) {
        ENGINE_OBJECT_POOL pool;
        RENDER_POOL renders;
        ENGINE_SHAKE_OBJECT shake = {0};
        ENGINE_MOTION player = {0};
        unsigned short camera_shake = 999, immunity = 0, player_flags = 0xa501;
        engine_initialize_objects(&pool);
        render_initialize_nodes(&renders);
        ENGINE_OBJECT *sentinel = engine_acquire_object(&pool, 0);
        pool.current = pool.tracked = sentinel;
        pool.update_status = -3;
        ENGINE_OBJECT *created = 0;
        assert(engine_spawn_shake(&pool, &renders, &shake, enabled ? -1 : 0,
            &camera_shake, &immunity, &player, &player_flags, impact, &impacts,
            -7, &created) == 0);
        assert(created && created->context == &shake && created->behavior == &engine_shake_behavior);
        assert(pool.current == sentinel && pool.tracked == sentinel && pool.update_status == -3);
        assert(shake.body.owner.x == (enabled ? -1 : 0) && shake.body.owner.y == 0);
        assert(shake.body.initialized && shake.body.animation.counter == 29 &&
            camera_shake == 8 && player_flags == 0xa541);
        assert(shake.body.node->parts == animation_emitter_data &&
            shake.body.node->parts_size == 20 && shake.body.node->order == -7);
        ENGINE_OBJECT *unchanged = created;
        assert(engine_spawn_shake(&pool, &renders, &shake, 0, &camera_shake,
            &immunity, &player, &player_flags, 0, 0, 0, &unchanged) == -1);
        assert(unchanged == created && shake.body.owner.x == (enabled ? -1 : 0));
        unsigned int before = impacts;
        pool.tracked = created;
        for (unsigned int tick = 1; tick <= 31; ++tick) {
            assert(engine_update_objects(&pool, &keys) == 0);
            assert(shake.body.animation.counter == (unsigned short)(29 - tick));
            assert(impacts == before + (enabled && tick >= 15 ? 1U : 0U));
            assert(!!created->active == (tick < 31));
        }
        assert(!shake.body.node && !pool.tracked && !renders.head &&
            pool.head == sentinel && pool.tail == sentinel && camera_shake == 0);
        assert(player_flags == 0xa541);
        assert(engine_spawn_shake(&pool, &renders, &shake, 0, &camera_shake,
            &immunity, &player, &player_flags, 0, 0, 0, &created) == 0);
        assert(camera_shake == 8 && shake.body.animation.counter == 29);
    }
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    ENGINE_SHAKE_OBJECT shake = {0};
    ENGINE_MOTION player = {0};
    unsigned short camera_shake = 123, immunity = 0, flags = 123;
    ENGINE_OBJECT *created = 0;
    assert(engine_spawn_shake(&pool, &renders, &shake, -1, &camera_shake,
        &immunity, &player, &flags, 0, 0, 0, &created) == -1);
    assert(flags == 123 && camera_shake == 123 && !pool.head && !renders.head);
    while (pool.free_head) {
        assert(engine_acquire_object(&pool, 0));
    }
    RENDER_NODE *free_before = renders.free_head;
    assert(engine_spawn_shake(&pool, &renders, &shake, 0, &camera_shake,
        &immunity, &player, &flags, 0, 0, 0, &created) == -1);
    assert(renders.free_head == free_before && flags == 123 && camera_shake == 123);
    puts("PASS: original 0x2853e shake spawn, DS:0x162d4 definition, marker X/zero Y, "
        "immediate counter 29 and shake 8, player flags OR 0x40, exact impact timing, "
        "32 total updates to removal, reuse and constructor failures");
    return 0;
}
