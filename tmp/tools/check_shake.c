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
    static const unsigned short sequence[] = {
        8, 8, 0, 0, 7, 7, 0, 0, 6, 6, 0, 0, 5, 5, 0, 0,
        4, 4, 0, 0, 3, 3, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0
    };
    DOS64_INPUT keys = {0};
    for (unsigned int mode = 0; mode < 8; ++mode) {
        ENGINE_OBJECT_POOL pool;
        RENDER_POOL renders;
        engine_initialize_objects(&pool);
        render_initialize_nodes(&renders);
        ENGINE_SHAKE_OBJECT shake = {0};
        unsigned short camera_shake = 999, immunity = mode & 1;
        ENGINE_MOTION player = {0};
        player.velocity_y = mode & 2 ? 1 : 0;
        shake.camera_shake = &camera_shake;
        shake.immunity = &immunity;
        shake.player_motion = &player;
        shake.impact = impact;
        shake.impact_context = &impacts;
        shake.body.owner.x = mode & 4 ? 0 : -1;
        shake.body.render_pool = &renders;
        shake.body.node = render_acquire_node(&renders, &shake.body.owner, 0, 0,
            animation_emitter_data, 20);
        const unsigned char *parts = shake.body.node->parts;
        ENGINE_OBJECT *object = engine_acquire_object(&pool, &engine_shake_behavior);
        object->context = &shake;
        pool.tracked = object;
        unsigned int before = impacts;
        for (unsigned int tick = 1; tick <= 32; ++tick) {
            assert(engine_update_objects(&pool, &keys) == 0);
            assert(shake.body.animation.counter == (unsigned short)(30 - tick));
            assert(camera_shake == sequence[tick - 1]);
            if (tick < 32) {
                assert(object->active && pool.tracked == object &&
                    shake.body.node->parts == parts && !shake.body.animation.visual_ready);
            } else {
                assert(!object->active && !pool.tracked && !shake.body.node && !renders.head);
            }
            assert(impacts == before + (!mode && tick >= 16 ? 1U : 0U));
        }
    }
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    ENGINE_SHAKE_OBJECT shake = {0};
    unsigned short camera_shake = 777, immunity = 0;
    ENGINE_MOTION player = {0};
    shake.camera_shake = &camera_shake; shake.immunity = &immunity;
    shake.player_motion = &player;
    shake.body.owner.x = -1; shake.body.render_pool = &renders;
    shake.body.node = render_acquire_node(&renders, &shake.body.owner, 0, 0,
        animation_emitter_data, 20);
    ENGINE_OBJECT *object = engine_acquire_object(&pool, &engine_shake_behavior);
    object->context = &shake;
    for (unsigned int i = 0; i < 15; ++i) {
        assert(engine_update_objects(&pool, &keys) == 0);
    }
    assert(engine_update_objects(&pool, &keys) == -1 && object->active &&
        shake.body.animation.counter == 14 && camera_shake == 0);
    puts("PASS: original 0x283cd shake behavior, exact 32-update sequence, "
        "old-counter impact at 15, all immunity/X/vertical-velocity gates, "
        "no script advance, render+tracked object removal and missing callback error");
    return 0;
}
