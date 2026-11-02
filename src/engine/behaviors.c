#ifdef LK_DOS64_NATIVE
#include "behaviors.h"
#include "animation_data.h"

static int select_player_reaction(unsigned short form, uint32_t script_position,
    int reverse, ENGINE_PLAYER_CALL *call)
{
    if (!call) {
        return -1;
    }
    uint32_t base = form ? UINT32_C(0x5bd9) : UINT32_C(0x6c31);
    /* SAR followed by AND 0xffff depends only on bits 1..16 of wrapped SUB. */
    unsigned int index = ((script_position - base) >> 1) & 0xffffU;
    int middle = index > 0 && index < 25;
    call->handler = middle != reverse ? 0xe545U : 0xe410U;
    call->script = middle ? (form ? 0x5960U : 0x61b8U) :
        (form ? 0x5952U : 0x61aaU);
    call->counter = middle ? 20 : 50;
    return 0;
}

int engine_player_reaction_e667(unsigned short form, uint32_t script_position,
    ENGINE_PLAYER_CALL *call)
{
    return select_player_reaction(form, script_position, 0, call);
}

int engine_player_reaction_e6ee(unsigned short form, uint32_t script_position,
    ENGINE_PLAYER_CALL *call)
{
    return select_player_reaction(form, script_position, 1, call);
}

static int select_contact_reaction(short contact, unsigned short form,
    uint32_t script_position, int reverse, ENGINE_PLAYER_CALL *call)
{
    if (!call) {
        return -1;
    }
    if (contact < 4 || contact > 48 || (contact > 16 && contact < 32)) {
        return select_player_reaction(form, script_position, reverse, call);
    }
    call->handler = reverse ? 0xae53U : 0xaa97U;
    call->script = form ? 0x591aU : 0x6116U;
    call->counter = 0;
    return 0;
}

int engine_player_reaction_e36e(short contact, unsigned short form,
    uint32_t script_position, ENGINE_PLAYER_CALL *call)
{
    return select_contact_reaction(contact, form, script_position, 1, call);
}

int engine_player_reaction_e3bf(short contact, unsigned short form,
    uint32_t script_position, ENGINE_PLAYER_CALL *call)
{
    return select_contact_reaction(contact, form, script_position, 0, call);
}

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

int engine_player_begin_deflection(ENGINE_OBJECT *object,
    ENGINE_PLAYER_DEFLECTION *state, const ENGINE_PLAYER_CALL *call)
{
    if (!object || !object->active || !state || !valid_state(&state->body) ||
        !call || (call->handler != 0xe410U && call->handler != 0xe545U)) {
        return -1;
    }
    ANIMATION_PROGRAM program;
    if (animation_program_initialize(&program, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, call->script,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) != 0) {
        return -1;
    }
    program.counter = call->counter;
    /* Initialization replaces the script pointer, not the object's state word. */
    program.state = state->body.animation.state;
    state->body.animation = program;
    state->body.motion.velocity_y = UINT32_C(0xfffb0000);
    state->age = 0;
    state->handler = call->handler;
    object->context = state;
    object->behavior = &engine_player_deflection_behavior;
    return 0;
}

static void update_player_deflection(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_PLAYER_DEFLECTION *state = object->context;
    if (!state || !valid_state(&state->body) ||
        (state->handler != 0xe410U && state->handler != 0xe545U)) {
        pool->update_status = -1;
        return;
    }
    if (!state->immunity && (state->flags_high & 4)) {
        ENGINE_PLAYER_CALL call = {0xef04, 0, 0};
        if (!state->transition || state->transition(state->context, &call) != 0) {
            pool->update_status = -1;
        }
        return;
    }
    unsigned char stop = state->handler == 0xe410U ? 4 : 8;
    if (state->controls & stop) {
        state->body.motion.velocity_x = 0;
        state->age = 16;
    }
    short hit;
    if (!state->probe || state->probe(state->context, state->body.owner.x,
        state->body.owner.y, &hit) != 0) {
        pool->update_status = -1;
        return;
    }
    if (hit) {
        if (!state->collision_flags) {
            pool->update_status = -1;
            return;
        }
        state->body.motion.velocity_y = 0;
        *state->collision_flags |= 0x20;
    }
    if (state->age == 16) {
        ENGINE_PLAYER_CALL call = {
            state->handler == 0xe410U ? 0xae53U : 0xaa97U,
            state->form ? 0x591aU : 0x6116U, 0
        };
        state->handler = call.handler;
        state->body.animation.counter = state->body.animation.state = 0;
        if (!state->transition || state->transition(state->context, &call) != 0) {
            pool->update_status = -1;
        }
        return;
    }
    ++state->age;
    if (engine_motion_player_gravity(&state->body.motion, &state->body.owner,
        state->form) != 0 ||
        animation_program_step(&state->body.animation, state->body.node,
            &state->body.owner, 0, 0) != 0) {
        pool->update_status = -1;
        return;
    }
    state->body.motion.velocity_x = state->handler == 0xe410U ?
        UINT32_C(0xfffd0000) : UINT32_C(0x30000);
    int status = state->handler == 0xe410U ?
        engine_motion_left(&state->body.motion, &state->body.owner) :
        engine_motion_right(&state->body.motion, &state->body.owner, state->flags_high);
    if (status != 0) {
        pool->update_status = -1;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_player_deflection_behavior = {update_player_deflection};

static int player_air_transition(ENGINE_PLAYER_AIR *state, unsigned int handler,
    unsigned int script, unsigned short counter, short kind, short x, short y)
{
    ENGINE_PLAYER_CALL call = {handler, script, counter};
    if (!state->transition) {
        return -1;
    }
    return state->transition(state->player.context, &call, kind, x, y);
}

static int player_air_script(ENGINE_PLAYER_DEFLECTION *player, unsigned int script)
{
    ANIMATION_PROGRAM program;
    if (animation_program_initialize(&program, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, script,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) != 0) {
        return -1;
    }
    program.counter = player->body.animation.counter;
    program.state = player->body.animation.state;
    player->body.animation = program;
    return 0;
}

static void player_facing(ENGINE_PLAYER_DEFLECTION *player, int left)
{
    player->body.node->pass_flags = (unsigned char)((player->body.node->pass_flags & 0xf7) |
        (left ? 8 : 0));
}

static short player_word(unsigned int value)
{
    value &= 0xffffU;
    return (short)(value < 0x8000U ? (int)value : (int)value - 65536);
}

int engine_player_land(ENGINE_PLAYER_AIR *state, unsigned int handler, short duration)
{
    if (!state || !valid_state(&state->player.body) ||
        (handler != 0xb307U && handler != 0xb4a0U)) {
        return -1;
    }
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    if (player->flags_high & 0x20) {
        return player_air_transition(state, player->form ? 0xf3fbU : 0xf5f1U, 0, 0, 0, 0, 0);
    }
    state->player_flags &= 0xfffdU;
    state->flags &= 0xdffdU;
    player->flags_high &= 0xef;
    player->body.animation.state = 0;
    if (handler == 0xb307U) {
        player->body.motion.velocity_y = 0;
        if (state->landing_flags & 1) {
            return player_air_transition(state, 0xb43d, 0x7040, 0, 0, 0, 0);
        }
    }
    if (duration > 60 && !(player->flags_high & 0x80)) {
        return player_air_transition(state, handler == 0xb307U ? 0xb253U : 0xb19fU,
            player->form ? 0x58feU : 0x6156U, 30, 0, 0, 0);
    }
    uint32_t velocity = player->body.motion.velocity_x;
    int64_t signed_velocity = velocity < UINT32_C(0x80000000) ? velocity :
        (int64_t)velocity - INT64_C(0x100000000);
    int moving = handler == 0xb307U ? signed_velocity >= 2 : signed_velocity < -1;
    return player_air_transition(state, handler == 0xb307U ?
        (moving ? 0xcdc2U : 0xc8d5U) : (moving ? 0xd108U : 0xc2cdU),
        moving ? (player->form ? 0x590cU : 0x6164U) :
            (player->form ? 0x58f0U : 0x6148U), 0, 0, 0, 0);
}

static int step_player_air(ENGINE_PLAYER_AIR *state)
{
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    ENGINE_FALLING_OBJECT *body = &player->body;
    int right = player->handler == 0xaa97U;
    if (player->flags_high & 0x20) {
        return player_air_transition(state, player->form ? 0xf3fbU : 0xf5f1U, 0, 0, 0, 0, 0);
    }
    if ((state->pressed & 0x10) && player->form) {
        return player_air_transition(state, 0x10bc6, 0x57c1, 0, 0, 0, 0);
    }
    if (state->flags & 1) {
        if (player_air_script(player, 0x61e2) != 0) {
            return -1;
        }
        state->flags = 2;
        if (right) {
            player_facing(player, 0);
            return 0;
        }
    }
    /* Only the right-facing handler performs this upward probe. */
    if (right && (body->motion.velocity_y & UINT32_C(0x80000000))) {
        short hit;
        if (!player->probe || player->probe(player->context,
            body->owner.x, body->owner.y, &hit) != 0) {
            return -1;
        }
        if (hit) {
            if (!player->collision_flags) {
                return -1;
            }
            body->motion.velocity_y = 0;
            *player->collision_flags |= 0x20;
        }
    }
    if (state->flags & 4) {
        return player_air_transition(state, 0xf6cc, 0, 0, 0, 0, 0);
    }
    if (state->flags & 0x800) {
        return player_air_transition(state, 0x10075, 0, 0, 0, 0, 0);
    }
    if (state->flags & 0x200) {
        return player_air_transition(state, 0xfcb5, 0x6c31, 0, 0, 0, 0);
    }
    if (state->flags & 0x40) {
        return player_air_transition(state, 0xf94d, 0, 0, 0, 0, 0);
    }
    if (!player->immunity && (player->flags_high & 4)) {
        return player_air_transition(state, 0xef04, 0, 0, 0, 0, 0);
    }
    if (right && body->animation.counter && !(player->controls & 8)) {
        --body->animation.counter;
        state->pressed = (unsigned short)((state->pressed & 0xfffbU) | 8);
    }
    short kind, delta_y;
    if (!state->ground || state->ground(player->context, &kind, &delta_y) != 0) {
        return -1;
    }
    ++body->animation.state;
    if (state->contact_kind == 4) {
        return player_air_transition(state, 0x10d78, 0, 0, 0, 0, 0);
    }
    if ((state->flags & 2) && state->anchor_y > 0) {
        kind = 0;
    }
    uint32_t velocity_y = body->motion.velocity_y;
    int64_t signed_y = velocity_y < UINT32_C(0x80000000) ? velocity_y :
        (int64_t)velocity_y - INT64_C(0x100000000);
    if (kind && delta_y >= -20 && delta_y <= signed_y) {
        body->owner.y = player_word((unsigned short)body->owner.y + (unsigned int)delta_y);
        return engine_player_land(state, right ? 0xb307U : 0xb4a0U,
            player_word(body->animation.state));
    }
    short hit, edge_x, edge_y;
    if (!state->edge || state->edge(player->context, &hit, &kind, &edge_x, &edge_y) != 0) {
        return -1;
    }
    if (hit && kind != (right ? 0xf8 : 0xe8)) {
        if (right) {
            player_facing(player, 0);
        }
        return player_air_transition(state, right ? 0xe8dfU : 0xe775U, 0, 0,
            kind, edge_x, edge_y);
    }
    if (engine_motion_air_gravity(&body->motion, &body->owner, player->form,
        (unsigned char)state->flags) != 0 ||
        animation_program_step(&body->animation, body->node, &body->owner, 0, 0) != 0) {
        return -1;
    }
    if (state->flags & 2) {
        if (!body->motion.velocity_x && body->owner.x > state->anchor_x) {
            body->owner.x = player_word((unsigned short)body->owner.x - 1U);
            return 0;
        }
        if (engine_motion_x(&body->motion, &body->owner) != 0) {
            return -1;
        }
        if (!body->motion.velocity_x && body->owner.x < state->anchor_x) {
            body->owner.x = player_word((unsigned short)body->owner.x + 1U);
        }
        return 0;
    }
    if (state->pressed & (right ? 4 : 8)) {
        player->handler = right ? 0xae53U : 0xaa97U;
        player_facing(player, right);
        return 0;
    }
    if (!(state->pressed & (right ? 8 : 4)) && !(state->flags & 0x2000)) {
        body->motion.velocity_x = 0;
        return 0;
    }
    return right ? engine_motion_right(&body->motion, &body->owner, player->flags_high) :
        engine_motion_left(&body->motion, &body->owner);
}

static void update_player_air(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_PLAYER_AIR *state = object->context;
    if (!state || !valid_state(&state->player.body) ||
        (state->player.handler != 0xaa97U && state->player.handler != 0xae53U) ||
        step_player_air(state) != 0) {
        pool->update_status = -1;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_player_air_behavior = {update_player_air};

int engine_player_begin_air(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, const ENGINE_PLAYER_CALL *call)
{
    if (!pool || !object || !object->active || !state || !valid_state(&state->player.body) ||
        !call || (call->handler != 0xaa97U && call->handler != 0xae53U)) {
        return -1;
    }
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    if (player->handler != call->handler) {
        if (player_air_script(player, call->script) != 0) {
            return -1;
        }
        player->handler = call->handler;
        player->body.animation.counter = call->counter;
        player->body.animation.state = 0;
        player->flags_high = (unsigned char)((player->flags_high | 0x10) & 0xf7);
        player_facing(player, call->handler == 0xae53U);
        if (animation_program_step(&player->body.animation, player->body.node,
            &player->body.owner, 0, 0) != 0) {
            return -1;
        }
    }
    object->context = state;
    object->behavior = &engine_player_air_behavior;
    return step_player_air(state);
}

static int player_animation(ENGINE_PLAYER_AIR *state)
{
    ENGINE_FALLING_OBJECT *body = &state->player.body;
    return animation_program_step(&body->animation, body->node, &body->owner, 0, 0);
}

static int step_player_jump(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state)
{
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    ENGINE_FALLING_OBJECT *body = &player->body;
    int right = player->handler == 0xb604U;
    if (!player->immunity && (player->flags_high & 4)) {
        return player_air_transition(state, 0xef04, 0, 0, 0, 0, 0);
    }
    if (body->animation.counter) {
        --body->animation.counter;
        return player_animation(state);
    }
    if ((state->pressed & 0x10) && player->form) {
        return player_air_transition(state, 0x10bc6, 0x57c1, 0, 0, 0, 0);
    }
    if (state->jump_boost) {
        --state->jump_boost;
        if ((state->pressed & 0x20) || (state->flags & 0x1000)) {
            body->motion.velocity_y -= player->form ? 0x9000U : 0x5000U;
        } else {
            state->jump_boost = 0;
        }
    }
    if (right && !state->jump_boost) {
        *player->collision_flags |= 0x20;
    }
    short hit;
    if (!player->probe || player->probe(player->context,
        body->owner.x, body->owner.y, &hit) != 0) {
        return -1;
    }
    if (hit) {
        body->motion.velocity_y = 0;
        *player->collision_flags |= 0x20;
    }
    /* The left path writes this bit after the probe, the right path before. */
    if (!right && !state->jump_boost) {
        *player->collision_flags |= 0x20;
    }
    uint32_t vy = body->motion.velocity_y;
    int64_t signed_y = vy < UINT32_C(0x80000000) ? vy :
        (int64_t)vy - INT64_C(0x100000000);
    if (signed_y >= (player->form ? -0x30000 : 0)) {
        ENGINE_PLAYER_CALL call = {right ? 0xaa97U : 0xae53U,
            state->jump_air_script, 0};
        return engine_player_begin_air(pool, object, state, &call);
    }
    if (engine_motion_player_gravity(&body->motion, &body->owner, player->form) != 0 ||
        player_animation(state) != 0) {
        return -1;
    }
    if (state->pressed & (right ? 4 : 8)) {
        state->flags &= 0xdfffU;
        player->handler = right ? 0xb7e7U : 0xb604U;
        player_facing(player, right);
        return 0;
    }
    if (!(state->pressed & (right ? 8 : 4)) && !(state->flags & 0x2000)) {
        body->motion.velocity_x = 0;
        return 0;
    }
    return right ? engine_motion_right(&body->motion, &body->owner, player->flags_high) :
        engine_motion_left(&body->motion, &body->owner);
}

static void update_player_jump(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_PLAYER_AIR *state = object->context;
    if (!state || !valid_state(&state->player.body) || !state->player.collision_flags ||
        (state->player.handler != 0xb604U && state->player.handler != 0xb7e7U) ||
        step_player_jump(pool, object, state) != 0) {
        pool->update_status = -1;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_player_jump_behavior = {update_player_jump};

int engine_player_begin_jump(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, const ENGINE_PLAYER_CALL *call, unsigned int air_script)
{
    if (!pool || !object || !object->active || !state || !valid_state(&state->player.body) ||
        !state->player.collision_flags || !call ||
        (call->handler != 0xb604U && call->handler != 0xb7e7U)) {
        return -1;
    }
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    object->context = state;
    object->behavior = &engine_player_jump_behavior;
    if (player->handler == call->handler) {
        return step_player_jump(pool, object, state);
    }
    if (player_air_script(player, call->script) != 0) {
        return -1;
    }
    state->jump_air_script = air_script;
    player->body.animation.counter = call->counter;
    player->body.motion.velocity_y = player->form ? UINT32_C(0xfffb0000) :
        UINT32_C(0xfffb2000);
    state->jump_boost = player->form ? 6 : 8;
    player->handler = call->handler;
    player_facing(player, call->handler == 0xb7e7U);
    *player->collision_flags &= 0xdf;
    return 0;
}

static int step_player_recovery(ENGINE_PLAYER_AIR *state)
{
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    if (!player->immunity && (player->flags_high & 4)) {
        return player_air_transition(state, 0xef04, 0, 0, 0, 0, 0);
    }
    if (state->surface_kind == 3) {
        player->body.animation.counter = 0;
    }
    int finished = !player->body.animation.counter;
    if (finished) {
        player->handler = player->handler == 0xb253U ? 0xc8d5U : 0xc2cdU;
    } else {
        --player->body.animation.counter;
    }
    if (player_animation(state) != 0) {
        return -1;
    }
    /* Original recovery changes the handler, then animates; it does not call idle. */
    return finished ? player_air_transition(state, player->handler,
        player->body.animation.script.position, player->body.animation.counter, 0, 0, 0) : 0;
}

static void update_player_recovery(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_PLAYER_AIR *state = object->context;
    if (!state || !valid_state(&state->player.body) ||
        (state->player.handler != 0xb19fU && state->player.handler != 0xb253U) ||
        step_player_recovery(state) != 0) {
        pool->update_status = -1;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_player_recovery_behavior = {update_player_recovery};

int engine_player_begin_recovery(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, const ENGINE_PLAYER_CALL *call)
{
    if (!pool || !object || !object->active || !state || !valid_state(&state->player.body) ||
        !call || (call->handler != 0xb19fU && call->handler != 0xb253U)) {
        return -1;
    }
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    object->context = state;
    object->behavior = &engine_player_recovery_behavior;
    if (player->handler == call->handler) {
        return step_player_recovery(state);
    }
    if (!state->sound || player_air_script(player, call->script) != 0) {
        return -1;
    }
    player->handler = call->handler;
    player->body.animation.counter = call->counter;
    player->flags_high &= 0xef;
    return state->sound(player->context, player->form ? 5 : 4);
}

static int player_ground_animation(ENGINE_PLAYER_AIR *state)
{
    ENGINE_FALLING_OBJECT *body = &state->player.body;
    return animation_program_step(&body->animation, body->node, &body->owner,
        state->animation_event, state->player.context);
}

static int player_support(ENGINE_PLAYER_AIR *state, short *supported)
{
    return state->support ? state->support(state->player.context, supported) : -1;
}

static int player_ground_call(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, unsigned int handler, unsigned int script)
{
    ENGINE_PLAYER_CALL call = {handler, script, 0};
    return engine_player_begin_ground(pool, object, state, &call);
}

static int player_ground_jump(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, int right, int running, int forced)
{
    int adult = state->player.form != 0;
    ENGINE_PLAYER_CALL call = {right ? 0xb604U : 0xb7e7U,
        running ? (adult ? 0x5936U : 0x6172U) : (adult ? 0x5944U : 0x6180U),
        running ? 0 : adult ? 10 : 4};
    if (!forced) {
        state->flags &= 0xdfffU;
    }
    unsigned int script = running && !forced ?
        (adult ? 0x591aU : 0x6116U) : (adult ? 0x5928U : 0x612cU);
    return engine_player_begin_jump(pool, object, state, &call, script);
}

static int player_ground_fall(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, int right)
{
    ENGINE_PLAYER_CALL call = {right ? 0xaa97U : 0xae53U,
        state->player.form ? 0x591aU : 0x6116U, 0};
    return engine_player_begin_air(pool, object, state, &call);
}

static int player_ceiling(ENGINE_PLAYER_AIR *state, short *hit)
{
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    return player->probe ? player->probe(player->context,
        player->body.owner.x, player->body.owner.y, hit) : -1;
}

/* Terrain transitions carry the original side and full velocity as two words. */
static int player_ground_terrain(ENGINE_PLAYER_AIR *state)
{
    unsigned char kind = state->contact_kind;
    if (kind == 6 || (state->flags & 0x10)) {
        return player_air_transition(state, 0xf80d, 0, 0, 1, -3, 0);
    }
    if (kind == 9 || (state->flags & 0x20)) {
        return player_air_transition(state, 0xf80d, 0, 0, 0, 3, 0);
    }
    if (kind == 5 || kind == 0xd8) {
        return player_air_transition(state, 0xfe3c, 0, 0, 1, -4, 0);
    }
    if (kind == 8 || kind == 0xd9) {
        return player_air_transition(state, 0xfe3c, 0, 0, 0, 4, 0);
    }
    return 1;
}

static int player_adult_action(ENGINE_PLAYER_AIR *state, int running)
{
    if (!running && player_air_transition(state, 0x1089b, 0x5732, 16, 0, 0, 0) != 0) {
        return -1;
    }
    state->player_flags |= 4;
    if (player_air_script(&state->player, 0x5724) != 0) {
        return -1;
    }
    state->player.body.animation.counter = 5;
    state->action_timer = 60;
    return 0;
}

static int step_player_ground(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state)
{
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    ENGINE_FALLING_OBJECT *body = &player->body;
    unsigned int handler = player->handler;
    int running = handler == 0xcdc2U || handler == 0xd108U;
    int turning = handler == 0xbeb7U || handler == 0xc0a1U;
    int crouching = handler == 0xbc80U || handler == 0xb9caU;
    int rolling = handler == 0xea46U || handler == 0xeb56U;
    int right = handler == 0xc8d5U || handler == 0xcdc2U || handler == 0xc0a1U ||
        handler == 0xbc80U || handler == 0xea46U;
    if (!turning && !crouching && !rolling && (state->flags & 1)) {
        state->flags &= 0xfffeU;
        /* The original left run continues; right run and both idles return. */
        if (handler != 0xd108U) {
            return 0;
        }
    }
    if (running) {
        uint32_t vx = body->motion.velocity_x;
        int64_t signed_x = vx < UINT32_C(0x80000000) ? vx :
            (int64_t)vx - INT64_C(0x100000000);
        if (right ? signed_x < 0x20000 : signed_x > -0x20000) {
            body->motion.velocity_x = right ? 0x20000U : 0xfffe0000U;
        }
    }
    if (!player->immunity && (player->flags_high & 4)) {
        if (crouching) {
            player->flags_high &= 0xfd;
        }
        return player_air_transition(state, 0xef04, 0, 0, 0, 0, 0);
    }
    short supported;
    if (player_support(state, &supported) != 0) {
        return -1;
    }
    if (!running && !turning && !crouching && !rolling) {
        if (!supported && body->animation.counter) {
            return player_air_transition(state, 0xc884, 0x5e35, 100, 0, 0, 0);
        }
        if (player_support(state, &supported) != 0) {
            return -1;
        }
    }
    if (!supported) {
        if (crouching) {
            player->flags_high &= 0xfd;
        }
        if (rolling) {
            ENGINE_PLAYER_CALL call = {right ? 0xaa97U : 0xae53U,
                player->form ? 0x591aU : 0x6116U, 6};
            return engine_player_begin_air(pool, object, state, &call);
        }
        return player_ground_fall(pool, object, state, right);
    }
    if (rolling) {
        if (state->boundary_controls & (right ? 8 : 4)) {
            body->motion.velocity_x = 0U - body->motion.velocity_x;
            return player_ground_call(pool, object, state, right ? 0xeb56U : 0xea46U, 0x61e2);
        }
        uint32_t vx = body->motion.velocity_x;
        int64_t signed_x = vx < UINT32_C(0x80000000) ? vx :
            (int64_t)vx - INT64_C(0x100000000);
        if (right ? signed_x < 0x20000 : signed_x > -0x20000) {
            player->flags_high &= 0xf7;
            return player_ground_call(pool, object, state, right ? 0xcdc2U : 0xd108U, 0x61f0);
        }
        body->motion.velocity_x += right ? 0xfffff200U : 0xe00U;
        if (engine_motion_x(&body->motion, &body->owner) != 0) {
            return -1;
        }
        return player_ground_animation(state);
    }
    /* Left crouch invokes both terrain transitions before the damage gate. */
    if (crouching && !right) {
        if (state->contact_kind == 6 || (state->flags & 0x10)) {
            player->flags_high &= 0xfd;
            if (player_air_transition(state, 0xf80d, 0, 0, 1, -3, 0) != 0) {
                return -1;
            }
        }
        if (state->contact_kind == 9 || (state->flags & 0x20)) {
            player->flags_high &= 0xfd;
            if (player_air_transition(state, 0xf80d, 0, 0, 0, 3, 0) != 0) {
                return -1;
            }
        }
    }
    if (!player->immunity && (state->contact_kind == 3 || state->surface_kind == 3)) {
        if (crouching) {
            player->flags_high &= 0xfd;
        }
        return player_air_transition(state, 0xef04, 0, 0, 0, 0, 0);
    }
    if (!turning && !crouching) {
        int terrain = player_ground_terrain(state);
        if (terrain != 1) {
            return terrain;
        }
    }
    if (crouching) {
        if (state->pressed & 0x20) {
            short hit;
            if (player_ceiling(state, &hit) != 0) {
                return -1;
            }
            if (!hit) {
                player->flags_high &= 0xfd;
                return player_ground_jump(pool, object, state, right, 0, 0);
            }
        }
        if (!(state->pressed & 2)) {
            player->flags_high &= 0xfd;
            return player_ground_call(pool, object, state, right ? 0xc8d5U : 0xc2cdU,
                player->form ? 0x5880U : 0x5f84U);
        }
        if (player->form && (state->pressed & 0x10)) {
            player->flags_high &= 0xfd;
            return player_air_transition(state, 0x1089b, 0x5804, 24, 0, 0, 0);
        }
        short age = player_word(body->animation.state);
        if (age == 50) {
            player->flags_high |= 2;
            ++body->animation.state;
            return 0;
        }
        if (age < 51) {
            ++body->animation.state;
        }
        return player_ground_animation(state);
    }
    if (turning) {
        if (state->pressed & 0x20) {
            short hit;
            if (player_ceiling(state, &hit) != 0) {
                return -1;
            }
            if (!hit) {
                return player_ground_jump(pool, object, state, right, 0, 0);
            }
        }
        if (player_word(body->animation.counter) < 7) {
            ++body->animation.counter;
            return player_ground_animation(state);
        }
        return state->pressed & (right ? 8 : 4) ?
            player_ground_call(pool, object, state, right ? 0xcdc2U : 0xd108U,
                player->form ? 0x598aU : 0x6100U) :
            player_ground_call(pool, object, state, right ? 0xc8d5U : 0xc2cdU,
                player->form ? 0x5856U : 0x64b5U);
    }
    if (running) {
        uint32_t vx = body->motion.velocity_x;
        int64_t signed_x = vx < UINT32_C(0x80000000) ? vx :
            (int64_t)vx - INT64_C(0x100000000);
        if ((right ? signed_x > 0x30000 : signed_x < -0x30000) &&
            (state->pressed & 2) && !player->form) {
            return player_ground_call(pool, object, state, right ? 0xea46U : 0xeb56U, 0x61e2);
        }
        if (player->form && (state->auxiliary_controls & 7)) {
            return player_adult_action(state, 1);
        }
        if (player->form && (state->pressed & 0x10)) {
            return player_air_transition(state, 0x1089b, 0x5848, 24, 0, 0, 0);
        }
        int forced = right && (state->flags & 0x1000);
        if (forced) {
            return player_ground_jump(pool, object, state, right, 1, 1);
        }
        if (state->pressed & 0x20) {
            short hit;
            if (player_ceiling(state, &hit) != 0) {
                return -1;
            }
            if (!hit) {
                return player_ground_jump(pool, object, state, right, 1, 0);
            }
        }
        if (state->pressed & (right ? 8 : 4)) {
            if (engine_motion_accelerate_x(&body->motion, &body->owner,
                right ? 0x4000U : 0xffffc000U) != 0) {
                return -1;
            }
            return player_ground_animation(state);
        }
        if (state->pressed & (right ? 4 : 8)) {
            return player_ground_call(pool, object, state, right ? 0xbeb7U : 0xc0a1U, 0);
        }
        return player_ground_call(pool, object, state, right ? 0xc8d5U : 0xc2cdU,
            player->form ? 0x583aU : 0x5f84U);
    }
    if ((!right && state->contact_kind == 0x16) ||
        (right && state->contact_kind == 0x14)) {
        if (!body->animation.counter) {
            if (player_air_script(player, 0x5e27) != 0) {
                return -1;
            }
            body->animation.counter = 0xffff;
        }
    }
    if (state->contact_kind == 0x14) {
        body->owner.x = player_word((unsigned short)body->owner.x - 1U);
    } else if (state->contact_kind == 0x16) {
        body->owner.x = player_word((unsigned short)body->owner.x + 1U);
    }
    if (state->landing_flags & 1) {
        if (!right) {
            player_facing(player, 0);
            player->handler = 0xc8d5;
            return player_air_transition(state, player->handler,
                body->animation.script.position, body->animation.counter, 0, 0, 0);
        }
        state->pressed = 1;
        body->animation.state = 50;
    }
    short age = player_word(body->animation.state);
    if (age == 50 && (state->pressed & 1)) {
        player->flags_high |= 1;
        if (player_air_script(player, player->form ? 0x62b4U : 0x628aU) != 0) {
            return -1;
        }
        ++body->animation.state;
        return 0;
    }
    if (age > 50 && !(state->pressed & 1)) {
        player->flags_high &= 0xfe;
        if (player_air_script(player, player->form ? 0x62a6U : 0x6298U) != 0) {
            return -1;
        }
        body->animation.state = 0;
        return 0;
    }
    if (age <= 50 || !(state->pressed & 1)) {
        if (state->pressed & 0x20) {
            short hit;
            if (player_ceiling(state, &hit) != 0) {
                return -1;
            }
            if (!hit) {
                return player_ground_jump(pool, object, state, right, 0, 0);
            }
        }
        if (state->pressed & 2) {
            return player_ground_call(pool, object, state, right ? 0xbc80U : 0xb9caU, 0);
        }
        if (player->controls & (right ? 4 : 8)) {
            return player_ground_call(pool, object, state, right ? 0xbeb7U : 0xc0a1U, 0);
        }
        if (state->pressed & (right ? 8 : 4)) {
            return player_ground_call(pool, object, state, right ? 0xcdc2U : 0xd108U,
                player->form ? 0x597cU : 0x6100U);
        }
        if (state->pressed & 0x40) {
            return player_air_transition(state, 0xec69,
                player->form ? 0x596eU : 0x61feU, 1, 0, 0, 0);
        }
        if (player->form && (state->auxiliary_controls & 7)) {
            return player_adult_action(state, 0);
        }
        if (player->form && (state->pressed & 0x10)) {
            return player_air_transition(state, 0x1089b, 0x5732, 16, 0, 0, 0);
        }
        if (state->pressed & 1) {
            ++body->animation.state;
            if (player_ground_animation(state) != 0) {
                return -1;
            }
            if (state->progress >= state->progress_limit &&
                state->contact_kind >= 32 && state->contact_kind <= 63) {
                return player_air_transition(state, 0x10f45, 0x6f26, 28, 0, 0, 0);
            }
            return 0;
        }
    }
    return player_ground_animation(state);
}

static int player_ground_handler(unsigned int handler)
{
    return handler == 0xc2cdU || handler == 0xc8d5U || handler == 0xcdc2U ||
        handler == 0xd108U || handler == 0xbeb7U || handler == 0xc0a1U ||
        handler == 0xb9caU || handler == 0xbc80U || handler == 0xea46U || handler == 0xeb56U;
}

static void update_player_ground(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_PLAYER_AIR *state = object->context;
    if (!state || !valid_state(&state->player.body) || !state->player.collision_flags ||
        !player_ground_handler(state->player.handler) ||
        step_player_ground(pool, object, state) != 0) {
        pool->update_status = -1;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_player_ground_behavior = {update_player_ground};

int engine_player_begin_ground(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object,
    ENGINE_PLAYER_AIR *state, const ENGINE_PLAYER_CALL *call)
{
    if (!pool || !object || !object->active || !state || !valid_state(&state->player.body) ||
        !state->player.collision_flags || !call || !player_ground_handler(call->handler)) {
        return -1;
    }
    ENGINE_PLAYER_DEFLECTION *player = &state->player;
    ENGINE_FALLING_OBJECT *body = &player->body;
    object->context = state;
    object->behavior = &engine_player_ground_behavior;
    if (player->handler == call->handler) {
        return step_player_ground(pool, object, state);
    }
    int running = call->handler == 0xcdc2U || call->handler == 0xd108U;
    int turning = call->handler == 0xbeb7U || call->handler == 0xc0a1U;
    int crouching = call->handler == 0xb9caU || call->handler == 0xbc80U;
    int rolling = call->handler == 0xea46U || call->handler == 0xeb56U;
    int right = call->handler == 0xc8d5U || call->handler == 0xcdc2U ||
        call->handler == 0xbeb7U || call->handler == 0xea46U;
    if (rolling && !state->sound) {
        return -1;
    }
    unsigned int script = turning ? (player->form ? 0x58c6U : 0x5f9aU) :
        crouching ? (player->form ? 0x5872U : 0x5fb0U) : call->script;
    if (player_air_script(player, script) != 0) {
        return -1;
    }
    player->handler = call->handler;
    if (crouching) {
        *player->collision_flags &= 0xfd;
        if (call->handler == 0xb9caU) {
            body->animation.state = 0;
        }
        return player_ground_animation(state);
    }
    player_facing(player, !right);
    if (rolling) {
        *player->collision_flags |= 2;
        player->flags_high |= 8;
        if (state->sound(player->context, 6) != 0) {
            return -1;
        }
        return step_player_ground(pool, object, state);
    }
    if (running) {
        body->motion.velocity_y = 0;
        player->flags_high &= 0xe7;
        return step_player_ground(pool, object, state);
    }
    body->motion.velocity_x = 0;
    if (!turning) {
        body->motion.velocity_y = 0;
        *player->collision_flags &= 0xfd;
        body->animation.state = body->animation.counter = 0;
        player->flags_high &= 0xef;
    }
    int status = player_ground_animation(state);
    if (turning) {
        body->animation.counter = 0;
    }
    return status;
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

static short offset_coordinate(short coordinate, int offset)
{
    unsigned int bits = ((unsigned int)coordinate + (unsigned int)offset) & 0xffff;
    return (short)(bits < 0x8000 ? (int)bits : (int)bits - 65536);
}

static int spawn_emission(ENGINE_OBJECT_POOL *pool, ENGINE_EMITTER_OBJECT *emitter,
    int offset)
{
    if (!emitter->slots || !emitter->slot_count ||
        !emitter->body.visibility) {
        return -1;
    }
    for (unsigned int i = 0; i < emitter->slot_count; ++i) {
        ENGINE_EMITTER_SLOT *slot = &emitter->slots[i];
        int used = 0;
        for (ENGINE_OBJECT *object = pool->head; object; object = object->next) {
            if (object->context == &slot->parent || object->context == &slot->child) {
                used = 1;
                break;
            }
        }
        if (!used) {
            ENGINE_OBJECT *created;
            RENDER_OWNER position = {
                offset_coordinate(emitter->body.owner.x, offset), emitter->body.owner.y
            };
            return engine_spawn_timed(pool, emitter->body.render_pool, &slot->parent,
                &slot->child, position, emitter->body.visibility, emitter->parent_order,
                emitter->child_order, &created) < 0 ? -1 : 0;
        }
    }
    return -1;
}

static void update_emitter(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_EMITTER_OBJECT *emitter = object->context;
    ENGINE_FALLING_OBJECT *state = emitter ? &emitter->body : 0;
    if (!valid_state(state)) {
        pool->update_status = -1;
        return;
    }
    if (!state->initialized) {
        state->initialized = 1;
        return;
    }
    if (!emitter->trigger || !state->animation.script.data) {
        pool->update_status = -1;
        return;
    }
    /* The original keeps CX from before decrementing the object counter. */
    unsigned short counter = state->animation.counter;
    if (*emitter->trigger) {
        --state->animation.counter;
        short near;
        if (render_near_view(&state->owner, emitter->camera, 128, 128, &near) != 0) {
            pool->update_status = -1;
            return;
        }
        if (!near) {
            if (render_release_node(state->render_pool, state->node) != 0) {
                pool->update_status = -1;
                return;
            }
            state->node = 0;
            pool->current = 0;
            return;
        }
        if ((counter & 0x7f) == 20 && spawn_emission(pool, emitter, -8) != 0) {
            pool->update_status = -1;
            return;
        }
        if ((counter & 0x7f) == 40 && spawn_emission(pool, emitter, 8) != 0) {
            pool->update_status = -1;
            return;
        }
        state->owner.y = offset_coordinate(state->owner.y,
            -(int)((unsigned short)state->owner.y & 3) + (counter & 2 ? 2 : 0));
    }
    if ((counter & 0x8000) && engine_motion_gravity(&state->motion, &state->owner) != 0) {
        pool->update_status = -1;
        return;
    }
    if (animation_program_step(&state->animation, state->node, &state->owner, 0, 0) != 0) {
        pool->update_status = -1;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_emitter_behavior = {update_emitter};

static void update_shake(ENGINE_OBJECT_POOL *pool, ENGINE_OBJECT *object)
{
    ENGINE_SHAKE_OBJECT *shake = object->context;
    ENGINE_FALLING_OBJECT *state = shake ? &shake->body : 0;
    if (!valid_state(state) || !shake->camera_shake || !shake->immunity ||
        !shake->player_motion) {
        pool->update_status = -1;
        return;
    }
    if (!state->initialized) {
        state->initialized = 1;
        state->animation.counter = 30;
    }
    unsigned short counter = state->animation.counter;
    --state->animation.counter;
    if (!*shake->immunity && counter == 15 && state->owner.x &&
        !shake->player_motion->velocity_y) {
        if (!shake->impact || shake->impact(shake->impact_context) != 0) {
            pool->update_status = -1;
            return;
        }
    }
    if (counter <= 30 && !(counter & 1)) {
        *shake->camera_shake = counter % 4 == 2 ? (unsigned short)((counter + 2) / 4) : 0;
    } else if (counter & 0x8000) {
        *shake->camera_shake = 0;
        if (render_release_node(state->render_pool, state->node) != 0) {
            pool->update_status = -1;
            return;
        }
        state->node = 0;
        pool->current = 0;
    }
}

const ENGINE_OBJECT_BEHAVIOR engine_shake_behavior = {update_shake};

static unsigned int definition_word(const unsigned char *data)
{
    return (unsigned int)data[0] | (unsigned int)data[1] << 8;
}

static unsigned int definition_dword(const unsigned char *data)
{
    return definition_word(data) | definition_word(data + 2) << 16;
}

typedef enum {
    SPAWN_FALLING,
    SPAWN_TIMED,
    SPAWN_EMITTER,
    SPAWN_SHAKE
} SPAWN_KIND;

static int spawn_definition(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_FALLING_OBJECT *state, RENDER_OWNER position,
    const RENDER_BOUNDS *visibility, short order, ENGINE_OBJECT **created, SPAWN_KIND kind)
{
    if (!pool || !renders || !state || (!visibility && kind != SPAWN_SHAKE) || !created ||
        !pool->free_head || !renders->free_head) {
        return -1;
    }
    for (ENGINE_OBJECT *object = pool->head; object; object = object->next) {
        if (object->context == state) {
            return -1;
        }
    }
    int emitter_data = kind == SPAWN_EMITTER || kind == SPAWN_SHAKE;
    const unsigned char *data = emitter_data ? animation_emitter_data : animation_falling_data;
    unsigned int base = emitter_data ? ANIMATION_EMITTER_BASE : ANIMATION_FALLING_BASE;
    unsigned int size = emitter_data ? ANIMATION_EMITTER_SIZE : ANIMATION_FALLING_SIZE;
    unsigned int definition_address = kind == SPAWN_SHAKE ? ANIMATION_SHAKE_DEFINITION :
        kind == SPAWN_EMITTER ? ANIMATION_EMITTER_DEFINITION :
        kind == SPAWN_TIMED ? ANIMATION_TIMED_DEFINITION : ANIMATION_FALLING_DEFINITION;
    const unsigned char *definition = data + definition_address - base;
    unsigned int handler = kind == SPAWN_SHAKE ? 0x183cd :
        kind == SPAWN_EMITTER ? 0x1865d : kind == SPAWN_TIMED ? 0x1881d : 0x188a1;
    unsigned int flags = definition_word(definition + 4);
    unsigned int address = definition_dword(definition + 6);
    if (definition_dword(definition) != handler ||
        definition_dword(definition + 10) != handler || flags != 0 ||
        address < base || address - base > size - 14) {
        return -1;
    }
    const unsigned char *parts = data + address - base;
    unsigned int bytes = 14 + definition_word(parts) * 6;
    if (bytes > size - (address - base)) {
        return -1;
    }
    const ENGINE_OBJECT_BEHAVIOR *behavior = kind == SPAWN_SHAKE ? &engine_shake_behavior :
        kind == SPAWN_EMITTER ? &engine_emitter_behavior :
        kind == SPAWN_TIMED ? &engine_timed_behavior : &engine_falling_behavior;
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
    return spawn_definition(pool, renders, state, position, visibility, order, created, SPAWN_FALLING);
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
        order, created, SPAWN_TIMED);
    if (status == 0) {
        /* The immediate initializer changes 10 to 9; it cannot spawn yet. */
        state->child = child;
        state->child_order = child_order;
    }
    return status;
}

int engine_spawn_emitter(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_EMITTER_OBJECT *state, RENDER_OWNER position, unsigned short counter,
    unsigned int variant, const unsigned short *trigger, const RENDER_OWNER *camera,
    const RENDER_BOUNDS *visibility, ENGINE_EMITTER_SLOT *slots, unsigned int slot_count,
    short order, short parent_order, short child_order, ENGINE_OBJECT **created)
{
    if (!state || variant > 1 || !trigger || !camera || !slots || !slot_count) {
        return -1;
    }
    ANIMATION_PROGRAM animation;
    if (animation_program_initialize(&animation, animation_emitter_data,
        ANIMATION_EMITTER_SIZE, ANIMATION_EMITTER_BASE,
        variant ? ANIMATION_EMITTER_SECOND : ANIMATION_EMITTER_FIRST,
        animation_emitter_data, ANIMATION_EMITTER_SIZE, ANIMATION_EMITTER_BASE) != 0) {
        return -1;
    }
    int status = spawn_definition(pool, renders, &state->body, position, visibility,
        order, created, SPAWN_EMITTER);
    if (status == 0) {
        /* 0x28773/0x28797 assign script and counter after the initial callback returns. */
        state->body.animation = animation;
        state->body.animation.counter = counter;
        state->trigger = trigger;
        state->camera = camera;
        state->slots = slots;
        state->slot_count = slot_count;
        state->parent_order = parent_order;
        state->child_order = child_order;
    }
    return status;
}

int engine_setup_emitter_group(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_EMITTER_GROUP *group, const RENDER_OWNER *camera,
    const RENDER_BOUNDS *visibility, short order, short parent_order, short child_order)
{
    if (!pool || !renders || !group || !camera || !visibility) {
        return -1;
    }
    unsigned int free_objects = 0, free_nodes = 0;
    for (ENGINE_OBJECT *object = pool->free_head; object; object = object->next) {
        ++free_objects;
    }
    for (RENDER_NODE *node = renders->free_head; node; node = node->next) {
        ++free_nodes;
    }
    if (free_objects < ENGINE_EMITTER_GROUP_COUNT || free_nodes < ENGINE_EMITTER_GROUP_COUNT) {
        return -1;
    }
    for (ENGINE_OBJECT *object = pool->head; object; object = object->next) {
        for (unsigned int i = 0; i < ENGINE_EMITTER_GROUP_COUNT; ++i) {
            if (object->context == &group->emitters[i]) {
                return -1;
            }
            for (unsigned int j = 0; j < ENGINE_EMITTER_GROUP_SLOTS; ++j) {
                ENGINE_EMITTER_SLOT *slot = &group->slots[i][j];
                if (object->context == &slot->parent || object->context == &slot->child) {
                    return -1;
                }
            }
        }
    }
    static const short x_positions[ENGINE_EMITTER_GROUP_COUNT] = {0xd98, 0xdb8, 0xdd0, 0xdf0};
    static const unsigned short counters[ENGINE_EMITTER_GROUP_COUNT] = {0xaa, 0xbe, 0xc8, 0xd2};
    group->trigger = 0;
    for (unsigned int i = 0; i < ENGINE_EMITTER_GROUP_COUNT; ++i) {
        group->objects[i] = 0;
    }
    for (unsigned int i = 0; i < ENGINE_EMITTER_GROUP_COUNT; ++i) {
        if (engine_spawn_emitter(pool, renders, &group->emitters[i],
            (RENDER_OWNER){x_positions[i], 0x1a8}, counters[i], i & 1,
            &group->trigger, camera, visibility, group->slots[i],
            ENGINE_EMITTER_GROUP_SLOTS, order, parent_order, child_order,
            &group->objects[i]) != 0) {
            return -1;
        }
    }
    return 0;
}

int engine_spawn_shake(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_SHAKE_OBJECT *state, short impact_marker, unsigned short *camera_shake,
    const unsigned short *immunity, const ENGINE_MOTION *player_motion,
    unsigned short *player_flags, ENGINE_PLAYER_IMPACT impact, void *impact_context,
    short order, ENGINE_OBJECT **created)
{
    if (!pool || !renders || !state || !camera_shake || !immunity ||
        !player_motion || !player_flags || !created || (impact_marker && !impact) ||
        !pool->free_head || !renders->free_head) {
        return -1;
    }
    for (ENGINE_OBJECT *object = pool->head; object; object = object->next) {
        if (object->context == state) {
            return -1;
        }
    }
    state->camera_shake = camera_shake;
    state->immunity = immunity;
    state->player_motion = player_motion;
    state->impact = impact;
    state->impact_context = impact_context;
    int status = spawn_definition(pool, renders, &state->body,
        (RENDER_OWNER){impact_marker, 0}, 0, order, created, SPAWN_SHAKE);
    if (status == 0) {
        *player_flags |= 0x40;
    }
    return status;
}
#else
/* Original behavior 0x288a1 and visibility helpers remain in recovered blocks. */
#endif
