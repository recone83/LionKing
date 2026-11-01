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

static void update_falling(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_FALLING_OBJECT *state = object->context;
    if (!state || !state->render_pool || !state->node || !state->node->active ||
        state->node->owner != &state->owner) {
        pool->update_status = -1;
        return;
    }
    unsigned int index;
    for (index = 0; index < RENDER_NODE_COUNT &&
        state->node != &state->render_pool->nodes[index]; ++index) {
    }
    if (index == RENDER_NODE_COUNT) {
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
#else
/* Original behavior 0x288a1 and visibility helpers remain in recovered blocks. */
#endif
