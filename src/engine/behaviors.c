#ifdef LK_DOS64_NATIVE
#include "behaviors.h"
#include "animation_data.h"

static int check_visibility(ENGINE_OBJECT_POOL *pool, ENGINE_FALLING_OBJECT *state)
{
    if (state->flags & 1) {
        return 0;
    }
    if (!state->visibility) {
        return -1;
    }
    RENDER_BOUNDS bounds = {state->owner.x, state->owner.y, state->owner.x, state->owner.y};
    if ((state->flags & 6) == 6) {
        bounds = state->fixed_bounds;
    }
    const RENDER_BOUNDS *window = state->visibility;
    if (bounds.top >= window->top && bounds.bottom <= window->bottom &&
        bounds.left >= window->left && bounds.right <= window->right) {
        return 0;
    }
    if (state->spatial_type) {
        RENDER_OWNER location = state->flags & 2 ? state->origin : state->owner;
        if (!state->unlink_spatial || state->unlink_spatial(state->spatial_context,
            state->spatial_type, location.x, location.y) != 0) {
            return -1;
        }
    }
    if (render_release_node(state->render_pool, state->node) != 0) {
        return -1;
    }
    state->node = 0;
    pool->current = 0;
    return 1;
}

static int valid_state(const ENGINE_FALLING_OBJECT *state)
{
    if (!state || !state->render_pool || !state->node || !state->node->active ||
        state->node->owner != &state->owner) {
        return 0;
    }
    unsigned int index;
    for (index = 0; index < RENDER_NODE_COUNT &&
        state->node != &state->render_pool->nodes[index]; ++index) {
    }
    if (index == RENDER_NODE_COUNT) {
        return 0;
    }
    return 1;
}

static void update_falling(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_FALLING_OBJECT *state = object->context;
    if (!valid_state(state)) {
        pool->update_status = -1;
        return;
    }
    if (!state->initialized) {
        if (animation_falling_initialize(&state->animation) != 0) {
            pool->update_status = -1;
            return;
        }
        state->initialized = 1;
        state->spatial_type = 0;
    }
    int visibility = check_visibility(pool, state);
    if (visibility < 0) {
        pool->update_status = -1;
        return;
    }
    if (visibility) {
        return;
    }
    if (engine_motion_gravity(&state->motion, &state->owner) != 0 ||
        animation_program_step(&state->animation, state->node, &state->owner, 0, 0) != 0) {
        pool->update_status = -1;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_falling_behavior = {update_falling};

static void update_timed(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_TIMED_OBJECT *timed = object->context;
    ENGINE_FALLING_OBJECT *state = timed ? &timed->body : 0;
    if (!valid_state(state)) {
        pool->update_status = -1;
        return;
    }
    if (!state->initialized) {
        if (animation_timed_initialize(&state->animation) != 0) {
            pool->update_status = -1;
            return;
        }
        state->initialized = 1;
        state->animation.counter = 10;
        state->spatial_type = 0;
    }
    int visibility = check_visibility(pool, state);
    if (visibility < 0) {
        pool->update_status = -1;
        return;
    }
    if (visibility) {
        return;
    }
    --state->animation.counter;
    if (!state->animation.counter) {
        unsigned int bits = ((unsigned int)state->owner.y - 16U) & 0xffff;
        RENDER_OWNER position = {state->owner.x,
            (short)(bits < 0x8000 ? (int)bits : (int)bits - 65536)};
        ENGINE_OBJECT *child;
        if (!timed->child || timed->child == state ||
            engine_spawn_falling(pool, state->render_pool, timed->child, position,
                state->visibility, timed->child_order, &child) < 0) {
            pool->update_status = -1;
            return;
        }
    }
    if (engine_motion_gravity(&state->motion, &state->owner) != 0 ||
        animation_program_step(&state->animation, state->node, &state->owner, 0, 0) != 0) {
        pool->update_status = -1;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_timed_behavior = {update_timed};

static unsigned int definition_word(const unsigned char *data)
{
    return (unsigned int)data[0] | (unsigned int)data[1] << 8;
}

static unsigned int definition_dword(const unsigned char *data)
{
    return definition_word(data) | definition_word(data + 2) << 16;
}

static int spawn_definition(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_FALLING_OBJECT *state, RENDER_OWNER position,
    const RENDER_BOUNDS *visibility, short order, ENGINE_OBJECT **created, int timed)
{
    if (!pool || !renders || !state || !visibility || !created ||
        !pool->free_head || !renders->free_head) {
        return -1;
    }
    for (ENGINE_OBJECT *object = pool->head; object; object = object->next) {
        if (object->context == state) {
            return -1;
        }
    }
    const unsigned char *definition = animation_falling_data +
        (timed ? ANIMATION_TIMED_DEFINITION : ANIMATION_FALLING_DEFINITION) - ANIMATION_FALLING_BASE;
    unsigned int handler = timed ? 0x1881d : 0x188a1;
    unsigned int flags = definition_word(definition + 4);
    unsigned int address = definition_dword(definition + 6);
    if (definition_dword(definition) != handler ||
        definition_dword(definition + 10) != handler || flags != 0 ||
        address < ANIMATION_FALLING_BASE ||
        address - ANIMATION_FALLING_BASE > ANIMATION_FALLING_SIZE - 14) {
        return -1;
    }
    const unsigned char *parts = animation_falling_data + address - ANIMATION_FALLING_BASE;
    unsigned int bytes = 14 + definition_word(parts) * 6;
    if (bytes > ANIMATION_FALLING_SIZE - (address - ANIMATION_FALLING_BASE)) {
        return -1;
    }
    const ENGINE_OBJECT_BEHAVIOR *behavior = timed ? &engine_timed_behavior : &engine_falling_behavior;
    ENGINE_OBJECT *object = engine_acquire_object(pool, behavior);
    if (!object) {
        return -1;
    }
    *state = (ENGINE_FALLING_OBJECT){0};
    state->owner = position;
    state->visibility = visibility;
    state->render_pool = renders;
    state->node = render_acquire_node(renders, &state->owner, flags << 16, order, parts, bytes);
    if (!state->node) {
        if (engine_release_object(pool, object) != 0) {
            return -1;
        }
        return -1;
    }
    state->flags = (unsigned char)(flags >> 8);
    object->context = state;
    ENGINE_OBJECT *previous = pool->current;
    int previous_status = pool->update_status;
    pool->current = object;
    pool->update_status = 0;
    behavior->update(pool, object);
    int status = pool->update_status;
    int culled = !pool->current;
    pool->current = previous;
    pool->update_status = previous_status;
    if (status || culled) {
        if (state->node) {
            if (render_release_node(renders, state->node) != 0) {
                return -1;
            }
            state->node = 0;
        }
        if (engine_release_object(pool, object) != 0) {
            return -1;
        }
        *created = 0;
        return status ? -1 : 1;
    }
    *created = object;
    return 0;
}

int engine_spawn_falling(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_FALLING_OBJECT *state, RENDER_OWNER position,
    const RENDER_BOUNDS *visibility, short order, ENGINE_OBJECT **created)
{
    return spawn_definition(pool, renders, state, position, visibility, order, created, 0);
}

int engine_spawn_timed(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_TIMED_OBJECT *state, ENGINE_FALLING_OBJECT *child, RENDER_OWNER position,
    const RENDER_BOUNDS *visibility, short order, short child_order,
    ENGINE_OBJECT **created)
{
    if (!state || !child || child == &state->body || !pool) {
        return -1;
    }
    for (ENGINE_OBJECT *object = pool->head; object; object = object->next) {
        if (object->context == child) {
            return -1;
        }
    }
    int status = spawn_definition(pool, renders, &state->body, position, visibility,
        order, created, 1);
    if (status == 0) {
        /* The immediate initializer changes 10 to 9; it cannot spawn yet. */
        state->child = child;
        state->child_order = child_order;
    }
    return status;
}
#else
/* Original behavior 0x288a1 and visibility helpers remain in recovered blocks. */
#endif
