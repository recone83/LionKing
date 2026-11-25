#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static unsigned int following_updates;
static void following(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    assert(pool->current == object);
    ++following_updates;
}

static const ENGINE_OBJECT_BEHAVIOR following_behavior = {following};
static DOS64_INPUT keys;

static ENGINE_OBJECT *setup(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_FALLING_OBJECT *state)
{
    engine_initialize_objects(pool);
    render_initialize_nodes(renders);
    *state = (ENGINE_FALLING_OBJECT){0};
    state->render_pool = renders;
    state->owner = (RENDER_OWNER){25, -100};
    state->node = render_acquire_node(renders, &state->owner, 0, 0,
        animation_falling_data, ANIMATION_FALLING_SIZE);
    assert(state->node);
    ENGINE_OBJECT *object = engine_acquire_object(pool, &engine_falling_behavior);
    assert(object);
    object->context = state;
    pool->tracked = object;
    return object;
}

static unsigned int unlinks;
static RENDER_OWNER expected_location;
static int unlink_spatial(void *context, unsigned short type, short x, short y)
{
    assert(context == &unlinks && type == 12);
    assert(x == expected_location.x && y == expected_location.y);
    ++unlinks;
    return 0;
}

int main(void)
{
    unsigned char original[ANIMATION_FALLING_SIZE];
    FILE *dump = fopen("bin/obj2_data.bin", "rb");
    assert(dump && fseek(dump, ANIMATION_FALLING_BASE, SEEK_SET) == 0);
    assert(fread(original, 1, sizeof(original), dump) == sizeof(original));
    assert(fclose(dump) == 0);
    assert(memcmp(original, animation_falling_data, sizeof(original)) == 0);
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    ENGINE_FALLING_OBJECT state;
    ENGINE_OBJECT *object = setup(&pool, &renders, &state);
    state.flags = 1;
    state.spatial_type = 999;
    state.motion.velocity_x = 12345;
    uint32_t position = (uint32_t)(unsigned short)state.owner.y << 16;
    uint32_t velocity = 0;
    for (unsigned int tick = 1; tick <= 2000; ++tick) {
        velocity += 0x4e00;
        if (velocity > 0x70000) {
            velocity = 0x70000;
        }
        position += velocity;
        assert(engine_update_objects(&pool, &keys) == 0);
        assert(object->active && pool.tracked == object && state.initialized);
        assert(state.spatial_type == 0 && state.owner.x == 25 &&
            state.motion.velocity_x == 12345);
        assert(((uint32_t)(unsigned short)state.owner.y << 16 |
            state.motion.fraction_y) == position);
        assert(state.motion.velocity_y == velocity);
        assert(state.animation.script.position == 0x1427a);
        assert(state.animation.visual.remaining == 99 - ((tick - 1) % 100));
        assert(state.node->parts == animation_falling_data &&
            state.node->parts_size == 20);
        short hit;
        assert(render_point_hit(state.node, state.owner.x, state.owner.y, &hit) == 0 &&
            hit == -1);
    }
    RENDER_BOUNDS window = {-100, -100, 100, 100};
    for (unsigned int flags = 0; flags < 8; ++flags) {
        object = setup(&pool, &renders, &state);
        state.flags = (unsigned char)flags;
        state.visibility = &window;
        state.owner = (RENDER_OWNER){25, 100};
        state.fixed_bounds = (RENDER_BOUNDS){-100, -100, 100, 100};
        assert(engine_update_objects(&pool, &keys) == 0 && object->active);
        assert(state.motion.velocity_y == 0x4e00);
        /* Visibility runs before gravity, so leaving the window removes on the next tick. */
        state.owner.y = 101;
        int retained = (flags & 1) || ((flags & 6) == 6);
        uint32_t before_velocity = state.motion.velocity_y;
        RENDER_NODE *node = state.node;
        assert(engine_acquire_object(&pool, &following_behavior));
        unsigned int before_following = following_updates;
        assert(engine_update_objects(&pool, &keys) == 0);
        assert(following_updates == before_following + 1);
        assert(!!object->active == !!retained);
        if (!retained) {
            assert(!node->active && !state.node && !pool.tracked &&
                state.motion.velocity_y == before_velocity);
            assert(pool.head == pool.tail && pool.head != object);
        }
    }
    for (unsigned int flags = 0; flags <= 2; flags += 2) {
        object = setup(&pool, &renders, &state);
        state.visibility = &window;
        state.flags = (unsigned char)flags;
        assert(engine_update_objects(&pool, &keys) == 0);
        state.owner.y = 101;
        state.origin = (RENDER_OWNER){-25, -50};
        state.spatial_type = 12;
        state.unlink_spatial = unlink_spatial;
        state.spatial_context = &unlinks;
        expected_location = flags & 2 ? state.origin : state.owner;
        assert(engine_update_objects(&pool, &keys) == 0 && !object->active);
    }
    assert(unlinks == 2);
    object = setup(&pool, &renders, &state);
    assert(engine_update_objects(&pool, &keys) == -1 && pool.update_status == -1);
    assert(object->active && state.node->active && state.motion.velocity_y == 0);
    state.visibility = &window;
    assert(engine_update_objects(&pool, &keys) == 0);
    state.owner.y = 101;
    state.spatial_type = 12;
    assert(engine_update_objects(&pool, &keys) == -1 && object->active && state.node->active);
    state.spatial_type = 0;
    assert(engine_update_objects(&pool, &keys) == 0 && !object->active);
    object = setup(&pool, &renders, &state);
    state.flags = 1;
    assert(engine_update_objects(&pool, &keys) == 0);
    state.animation.script.position = ANIMATION_FALLING_BASE;
    unsigned int before_following = following_updates;
    assert(engine_acquire_object(&pool, &following_behavior));
    assert(engine_update_objects(&pool, &keys) == -1 && pool.update_status == -1);
    assert(object->active && state.node->active && following_updates == before_following);
    assert(state.animation.unsupported_handler != 0);
    object = setup(&pool, &renders, &state);
    object->context = 0;
    assert(engine_update_objects(&pool, &keys) == -1 && object->active);
    puts("PASS: original 0x288a1 behavior through object dispatcher: 2000 gravity/script "
        "updates, visibility flags/edges, render+object removal, tracked pointer, "
        "spatial unlink order and explicit error propagation");
    return 0;
}
