#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

int main(void)
{
    unsigned char original[ANIMATION_EMITTER_SIZE];
    FILE *dump = fopen("bin/obj2_data.bin", "rb");
    assert(dump && fseek(dump, ANIMATION_EMITTER_BASE, SEEK_SET) == 0);
    assert(fread(original, 1, sizeof(original), dump) == sizeof(original));
    assert(fclose(dump) == 0);
    assert(memcmp(original, animation_emitter_data, sizeof(original)) == 0);
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    ENGINE_EMITTER_OBJECT emitter[2] = {0};
    ENGINE_EMITTER_SLOT slots[2][4];
    memset(slots, 0, sizeof(slots));
    RENDER_OWNER camera = {0, 0};
    const RENDER_BOUNDS window = {-32768, -32768, 32767, 32767};
    unsigned short trigger = 0;
    DOS64_INPUT keys = {0};
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    ENGINE_OBJECT *sentinel = engine_acquire_object(&pool, 0);
    pool.current = pool.tracked = sentinel;
    ENGINE_OBJECT *created[2];
    for (unsigned int variant = 0; variant < 2; ++variant) {
        assert(engine_spawn_emitter(&pool, &renders, &emitter[variant],
            (RENDER_OWNER){100, 103}, 40, variant, &trigger, &camera, &window,
            slots[variant], 4, (short)variant, -3, -4, &created[variant]) == 0);
        assert(pool.current == sentinel && pool.tracked == sentinel);
        assert(emitter[variant].body.initialized &&
            emitter[variant].body.animation.counter == 40 &&
            !emitter[variant].body.animation.visual_ready &&
            emitter[variant].body.motion.velocity_y == 0);
        assert(emitter[variant].body.node->parts == animation_emitter_data + 20 &&
            emitter[variant].body.node->parts_size == 20);
        assert(emitter[variant].body.animation.script.position ==
            (variant ? ANIMATION_EMITTER_SECOND : ANIMATION_EMITTER_FIRST));
    }
    for (unsigned int tick = 1; tick <= 101; ++tick) {
        assert(engine_update_objects(&pool, &keys) == 0);
        for (unsigned int variant = 0; variant < 2; ++variant) {
            assert(emitter[variant].body.animation.counter == 40);
            assert(emitter[variant].body.owner.y == 103 && !slots[variant][0].parent.body.node);
            assert(emitter[variant].body.animation.visual.remaining == 99 - (tick - 1) % 100);
            assert(emitter[variant].body.node->parts == animation_emitter_data + variant * 20);
        }
    }
    trigger = 1;
    for (unsigned int tick = 1; tick <= 30; ++tick) {
        assert(engine_update_objects(&pool, &keys) == 0);
        for (unsigned int variant = 0; variant < 2; ++variant) {
            assert(emitter[variant].body.animation.counter == 40 - tick);
            assert(slots[variant][0].parent.body.owner.x == 108);
            if (tick == 1) {
                assert(slots[variant][0].parent.body.owner.y == 103 &&
                    slots[variant][0].parent.body.animation.counter == 8);
                assert(slots[variant][0].parent.body.node->order == -3);
            }
            if (tick >= 21) {
                assert(slots[variant][1].parent.body.owner.x == 92);
            }
            if (tick == 10) {
                assert(slots[variant][0].child.node &&
                    slots[variant][0].child.node->order == -4);
            }
        }
    }
    ENGINE_OBJECT *unchanged = created[0];
    assert(engine_spawn_emitter(&pool, &renders, &emitter[0],
        (RENDER_OWNER){0, 0}, 1, 0, &trigger, &camera, &window,
        slots[0], 4, 0, 0, 0, &unchanged) == -1 && unchanged == created[0]);
    ENGINE_EMITTER_OBJECT extra = {0};
    assert(engine_spawn_emitter(&pool, &renders, &extra,
        (RENDER_OWNER){0, 0}, 1, 2, &trigger, &camera, &window,
        slots[0], 4, 0, 0, 0, &unchanged) == -1 && !extra.body.node);
    camera.x = -1000;
    assert(engine_update_objects(&pool, &keys) == 0 &&
        !created[0]->active && !created[1]->active);
    unsigned int before = pool.update_count;
    assert(engine_update_objects(&pool, &keys) == 0 && pool.update_count == before + 1);
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    while (pool.free_head) {
        assert(engine_acquire_object(&pool, 0));
    }
    RENDER_NODE *free_before = renders.free_head;
    assert(engine_spawn_emitter(&pool, &renders, &extra,
        (RENDER_OWNER){0, 0}, 1, 0, &trigger, &camera, &window,
        slots[0], 4, 0, 0, 0, &unchanged) == -1 && renders.free_head == free_before);
    puts("PASS: original 0x28773/0x28797 emitter constructors, exact DS data, "
        "deferred first frame, both script variants, trigger activation, "
        "full emitter->parent->child chain, duplicate state, invalid variant and exhaustion");
    return 0;
}
