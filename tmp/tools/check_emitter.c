#include <assert.h>
#include <stdio.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static const RENDER_BOUNDS window = {-32768, -32768, 32767, 32767};
static DOS64_INPUT keys;

static ENGINE_OBJECT *setup(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_EMITTER_OBJECT *emitter, unsigned short *trigger, RENDER_OWNER *camera,
    ENGINE_EMITTER_SLOT *slots)
{
    engine_initialize_objects(pool);
    render_initialize_nodes(renders);
    *emitter = (ENGINE_EMITTER_OBJECT){0};
    emitter->body.owner = (RENDER_OWNER){100, 103};
    emitter->body.visibility = &window;
    emitter->body.render_pool = renders;
    emitter->body.node = render_acquire_node(renders, &emitter->body.owner, 0, 0,
        animation_emitter_data, 20);
    emitter->trigger = trigger;
    emitter->camera = camera;
    emitter->slots = slots;
    emitter->slot_count = 4;
    assert(animation_program_initialize(&emitter->body.animation, animation_emitter_data,
        ANIMATION_EMITTER_SIZE, ANIMATION_EMITTER_BASE, ANIMATION_EMITTER_FIRST,
        animation_emitter_data, ANIMATION_EMITTER_SIZE, ANIMATION_EMITTER_BASE) == 0);
    emitter->body.animation.counter = 40;
    ENGINE_OBJECT *object = engine_acquire_object(pool, &engine_emitter_behavior);
    assert(object);
    object->context = emitter;
    pool->tracked = object;
    return object;
}

int main(void)
{
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    ENGINE_EMITTER_OBJECT emitter;
    ENGINE_EMITTER_SLOT slots[4] = {0};
    RENDER_OWNER camera = {0, 0};
    unsigned short trigger = 1;
    ENGINE_OBJECT *object = setup(&pool, &renders, &emitter, &trigger, &camera, slots);
    assert(engine_update_objects(&pool, &keys) == 0);
    assert(emitter.body.initialized && emitter.body.animation.counter == 40 &&
        !emitter.body.animation.visual_ready && pool.tail == object);
    unsigned int emissions = 0;
    for (unsigned int tick = 1; tick <= 160; ++tick) {
        unsigned short old = emitter.body.animation.counter;
        short before_y = emitter.body.owner.y;
        uint32_t velocity = emitter.body.motion.velocity_y;
        uint32_t fraction = emitter.body.motion.fraction_y;
        unsigned short snapped = (unsigned short)(((unsigned short)before_y & 0xfffc) + (old & 2));
        uint32_t expected = (uint32_t)snapped << 16 | fraction;
        if (old & 0x8000) {
            velocity += 0x4e00;
            if (velocity > 0x70000) {
                velocity = 0x70000;
            }
            expected += velocity;
        }
        camera.y = before_y;
        assert(engine_update_objects(&pool, &keys) == 0);
        assert(emitter.body.animation.counter == (unsigned short)(old - 1));
        assert(((uint32_t)(unsigned short)emitter.body.owner.y << 16 |
            emitter.body.motion.fraction_y) == expected);
        assert(emitter.body.motion.velocity_y == velocity);
        assert(emitter.body.animation.script.position == 0x1427a &&
            emitter.body.node->parts == animation_emitter_data &&
            emitter.body.animation.visual.remaining == 99 - (tick - 1) % 100);
        if (old == 40 || old == 20 || old == 0xffa8 || old == 0xff94) {
            ++emissions;
        }
        if (tick == 1 || tick == 21 || tick == 129 || tick == 149) {
            ENGINE_TIMED_OBJECT *parent = &slots[emissions - 1].parent;
            assert(parent->body.owner.x == (old % 128 == 40 ? 108 : 92));
            assert(parent->body.owner.y == before_y && parent->body.animation.counter == 8);
            assert(parent->body.motion.velocity_y == 0x9c00);
        }
        if (!(old & 0x8000)) {
            assert((emitter.body.owner.y & 3) == (old & 2));
        }
        assert(pool.tracked == object);
    }
    assert(emissions == 4 && emitter.body.motion.velocity_y == 0x70000);
    trigger = 0;
    unsigned short counter = emitter.body.animation.counter;
    unsigned char remaining = emitter.body.animation.visual.remaining;
    assert(engine_update_objects(&pool, &keys) == 0 &&
        emitter.body.animation.counter == counter);
    assert(emitter.body.animation.visual.remaining != remaining);
    object = setup(&pool, &renders, &emitter, &trigger, &camera, slots);
    assert(engine_update_objects(&pool, &keys) == 0);
    camera.x = -1000;
    assert(engine_update_objects(&pool, &keys) == 0 && object->active);
    trigger = 1;
    assert(engine_update_objects(&pool, &keys) == 0 && !object->active &&
        !emitter.body.node && !pool.tracked);
    camera.x = 0;
    camera.y = 0;
    object = setup(&pool, &renders, &emitter, &trigger, &camera, slots);
    assert(engine_update_objects(&pool, &keys) == 0);
    emitter.slots = 0;
    assert(engine_update_objects(&pool, &keys) == -1 && object->active &&
        emitter.body.animation.counter == 39);
    puts("PASS: original emitter 0x2865d initialization, old-counter 20/40 spawns, "
        "160 updates, +/-8 offsets before Y snapping, trigger gating, gravity, "
        "expanded camera removal and explicit storage error");
    return 0;
}
