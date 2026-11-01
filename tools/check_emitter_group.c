#include <assert.h>
#include <stdio.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static ENGINE_EMITTER_GROUP group;

static unsigned int dword(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8 |
        (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
}

int main(void)
{
    /* Verify setup constants in original instructions, not just copied C arrays. */
    unsigned char code[0x5e];
    FILE *file = fopen("bin/obj1_code.bin", "rb");
    assert(file && fseek(file, 0x187bb, SEEK_SET) == 0);
    assert(fread(code, 1, sizeof(code), file) == sizeof(code));
    assert(fclose(file) == 0);
    assert(dword(code + 6) == 170 && dword(code + 13) == 3480);
    assert(dword(code + 25) == 424 && dword(code + 35) == 190 &&
        dword(code + 40) == 424 && dword(code + 45) == 3512);
    assert(dword(code + 55) == 200 && dword(code + 60) == 424 &&
        dword(code + 65) == 3536);
    assert(dword(code + 75) == 210 && dword(code + 80) == 424 &&
        dword(code + 85) == 3568);
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    RENDER_OWNER camera = {3400, 400};
    RENDER_BOUNDS visibility = {-32768, -32768, 32767, 32767};
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    ENGINE_OBJECT *sentinel = engine_acquire_object(&pool, 0);
    pool.current = pool.tracked = sentinel;
    group.trigger = 999;
    assert(engine_setup_emitter_group(&pool, &renders, &group, &camera,
        &visibility, 3, 2, 1) == 0);
    assert(!group.trigger && pool.current == sentinel && pool.tracked == sentinel);
    static const short xs[] = {3480, 3512, 3536, 3568};
    static const unsigned short counters[] = {170, 190, 200, 210};
    for (unsigned int i = 0; i < 4; ++i) {
        assert(group.objects[i]->context == &group.emitters[i]);
        assert(group.emitters[i].body.owner.x == xs[i] && group.emitters[i].body.owner.y == 424);
        assert(group.emitters[i].body.animation.counter == counters[i]);
        assert(group.emitters[i].body.animation.script.position ==
            (i & 1 ? ANIMATION_EMITTER_SECOND : ANIMATION_EMITTER_FIRST));
        assert(!group.emitters[i].body.animation.visual_ready);
        assert(group.emitters[i].trigger == &group.trigger);
        assert(group.emitters[i].body.node->order == 3);
        assert(group.objects[i]->previous == (i ? group.objects[i - 1] : sentinel));
    }
    DOS64_INPUT keys = {0};
    for (unsigned int tick = 0; tick < 5; ++tick) {
        assert(engine_update_objects(&pool, &keys) == 0);
        for (unsigned int i = 0; i < 4; ++i) {
            assert(group.emitters[i].body.animation.counter == counters[i]);
            assert(group.emitters[i].body.node->parts == animation_emitter_data + (i & 1) * 20);
        }
    }
    group.trigger = 1;
    assert(engine_setup_emitter_group(&pool, &renders, &group, &camera,
        &visibility, 3, 2, 1) == -1 && group.trigger == 1);
    for (unsigned int tick = 1; tick <= 90; ++tick) {
        assert(engine_update_objects(&pool, &keys) == 0);
        for (unsigned int i = 0; i < 4; ++i) {
            assert(group.emitters[i].body.animation.counter == counters[i] - tick);
        }
    }
    unsigned int parents = 0, children = 0;
    for (ENGINE_OBJECT *object = pool.head; object; object = object->next) {
        parents += object->behavior == &engine_timed_behavior;
        children += object->behavior == &engine_falling_behavior;
    }
    assert(parents == 8 && children == 8);
    camera.x = 0;
    assert(engine_update_objects(&pool, &keys) == 0);
    for (unsigned int i = 0; i < 4; ++i) {
        assert(!group.objects[i]->active && !group.emitters[i].body.node);
    }
    assert(engine_setup_emitter_group(&pool, &renders, &group, &camera,
        &visibility, 3, 2, 1) == -1 && group.trigger == 1);
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    for (unsigned int i = 0; i < ENGINE_OBJECT_CAPACITY - 3; ++i) {
        assert(engine_acquire_object(&pool, 0));
    }
    RENDER_NODE *before = renders.free_head;
    assert(engine_setup_emitter_group(&pool, &renders, &group, &camera,
        &visibility, 0, 0, 0) == -1 && renders.free_head == before && group.trigger == 1);
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    RENDER_OWNER owner = {0, 0};
    for (unsigned int i = 0; i < RENDER_NODE_COUNT - 3; ++i) {
        assert(render_acquire_node(&renders, &owner, 0, 0, animation_emitter_data, 20));
    }
    ENGINE_OBJECT *free_before = pool.free_head;
    assert(engine_setup_emitter_group(&pool, &renders, &group, &camera,
        &visibility, 0, 0, 0) == -1 && pool.free_head == free_before);
    puts("PASS: original 0x287bb four-emitter setup, binary constants, exact order/variants, "
        "inactive start, 90 active updates, eight parent-child chains, live camera culling, "
        "active-group reuse rejection and both resource preflights");
    return 0;
}
