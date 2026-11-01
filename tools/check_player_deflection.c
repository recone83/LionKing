#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

typedef struct {
    ENGINE_PLAYER_DEFLECTION *state;
    ENGINE_OBJECT *object;
    unsigned int probes;
    unsigned int transitions;
    short hit;
    ENGINE_PLAYER_CALL last;
} FIXTURE;

static int probe(void *context, short x, short y, short *hit)
{
    FIXTURE *fixture = context;
    assert(x == fixture->state->body.owner.x && y == fixture->state->body.owner.y);
    ++fixture->probes;
    *hit = fixture->hit;
    return 0;
}

static int transition(void *context, const ENGINE_PLAYER_CALL *call)
{
    FIXTURE *fixture = context;
    ++fixture->transitions;
    fixture->last = *call;
    if (call->handler != 0xef04) {
        assert(fixture->state->handler == call->handler);
        assert(fixture->state->body.animation.counter == 0 &&
            fixture->state->body.animation.state == 0);
    }
    fixture->object->behavior = 0;
    return 0;
}

static short signed_word(unsigned int word)
{
    word &= 65535U;
    return (short)(word < 32768 ? (int)word : (int)word - 65536);
}

static unsigned int descriptor(unsigned short form, int middle, unsigned int tick)
{
    static const unsigned int young_long[] = {0x78b4, 0x78c8, 0x78dc, 0x78f0};
    static const unsigned int young_short[] = {0x7940, 0x7954, 0x7968, 0x797c, 0x7954};
    static const unsigned int adult_long[] = {0x902c, 0x9040, 0x9054};
    static const unsigned int adult_short[] = {0x9090, 0x90a4, 0x90b8, 0x90cc};
    if (!form) {
        return middle ? young_short[tick <= 2 ? 0 : 1 + (tick - 3) / 4] :
            young_long[(tick - 1) / 4];
    }
    return middle ? adult_short[(tick - 1) / 4] :
        adult_long[tick <= 4 ? 0 : tick <= 10 ? 1 : 2];
}

static void initialize(ENGINE_OBJECT_POOL *pool, RENDER_POOL *renders,
    ENGINE_PLAYER_DEFLECTION *state, FIXTURE *fixture, unsigned char *collision_flags)
{
    engine_initialize_objects(pool);
    render_initialize_nodes(renders);
    memset(state, 0, sizeof(*state));
    state->body.owner = (RENDER_OWNER){32760, -32760};
    state->body.motion = (ENGINE_MOTION){65535, 12345, 0x12345678, 0x76543210};
    state->body.animation.state = 77;
    state->body.render_pool = renders;
    state->body.node = render_acquire_node(renders, &state->body.owner, 0, 0,
        animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    assert(state->body.node);
    *fixture = (FIXTURE){0};
    fixture->state = state;
    fixture->object = engine_acquire_object(pool, 0);
    assert(fixture->object);
    state->probe = probe;
    state->transition = transition;
    state->context = fixture;
    state->collision_flags = collision_flags;
}

int main(void)
{
    DOS64_INPUT keys = {0};
    static const unsigned short forms[] = {0, 1, 65535};
    static const uint32_t velocities[] = {
        0, 0x6a000, 0x6a001, 0x6b200, 0x6b201, 0x70000, 0x7fffffff,
        0x80000000, 0xffffb200, 0xffffffff
    };
    for (unsigned int f = 0; f < 3; ++f) {
        for (unsigned int v = 0; v < sizeof(velocities) / sizeof(velocities[0]); ++v) {
            for (unsigned int fraction = 0; fraction < 65536; ++fraction) {
                ENGINE_MOTION motion = {0, (unsigned short)fraction, 0, velocities[v]};
                RENDER_OWNER owner = {7, 32767};
                uint32_t velocity = velocities[v] + (forms[f] ? 0x6000U : 0x4e00U);
                int64_t signed_velocity = velocity < UINT32_C(0x80000000) ? velocity :
                    (int64_t)velocity - INT64_C(0x100000000);
                if (signed_velocity > 0x70000) {
                    velocity = 0x70000;
                }
                uint32_t position = UINT32_C(0x7fff0000) + fraction + velocity;
                assert(engine_motion_player_gravity(&motion, &owner, forms[f]) == 0);
                assert(owner.x == 7 && owner.y == signed_word(position >> 16) &&
                    motion.fraction_y == (unsigned short)position && motion.velocity_y == velocity);
            }
        }
    }
    assert(engine_motion_player_gravity(0, 0, 0) == -1);
    unsigned int updates = 0;
    for (unsigned int f = 0; f < 3; ++f) {
        for (unsigned int mode = 0; mode < 32; ++mode) {
            ENGINE_OBJECT_POOL pool;
            RENDER_POOL renders;
            ENGINE_PLAYER_DEFLECTION state;
            FIXTURE fixture;
            unsigned char collision_flags = 0x45;
            initialize(&pool, &renders, &state, &fixture, &collision_flags);
            state.form = forms[f];
            fixture.hit = mode & 4 ? -1 : 0;
            state.flags_high = mode & 8 ? 0x10 : 0;
            state.body.node->pass_flags = mode & 16 ? 8 : 0;
            int middle = !!(mode & 2);
            ENGINE_PLAYER_CALL call;
            uint32_t position = (state.form ? 0x5bd9U : 0x6c31U) + (middle ? 2 : 0);
            assert((mode & 1 ? engine_player_reaction_e6ee(state.form, position, &call) :
                engine_player_reaction_e667(state.form, position, &call)) == 0);
            assert(engine_player_begin_deflection(fixture.object, &state, &call) == 0);
            assert(state.body.motion.velocity_x == 0x12345678 &&
                state.body.motion.velocity_y == 0xfffb0000 && state.age == 0);
            assert(state.body.animation.counter == (middle ? 20 : 50) &&
                state.body.animation.state == 77);
            uint32_t y = ((uint32_t)(unsigned short)state.body.owner.y << 16) | 12345U;
            uint32_t vy = UINT32_C(0xfffb0000);
            unsigned int x = (unsigned short)state.body.owner.x;
            for (unsigned int tick = 1; tick <= 16; ++tick) {
                vy = (fixture.hit ? 0 : vy) + (state.form ? 0x6000U : 0x4e00U);
                y += vy;
                x += call.handler == 0xe410 ? (unsigned int)-3 :
                    state.flags_high & 0x10 ? 0 : 3;
                assert(engine_update_objects(&pool, &keys) == 0);
                assert(fixture.transitions == 0 && fixture.probes == tick && state.age == tick);
                assert(state.body.animation.state == 77 &&
                    state.body.animation.counter == call.counter);
                assert(state.body.owner.x == signed_word(x));
                assert(state.body.owner.y == signed_word(y >> 16));
                assert(state.body.motion.fraction_y == (unsigned short)y &&
                    state.body.motion.fraction_x == 65535);
                assert(state.body.motion.velocity_y == vy);
                assert(state.body.motion.velocity_x == (call.handler == 0xe410 ?
                    UINT32_C(0xfffd0000) : state.flags_high & 0x10 ? 0 : UINT32_C(0x30000)));
                assert(state.body.node->parts == animation_movement_data +
                    descriptor(state.form, middle, tick) - ANIMATION_MOVEMENT_BASE);
                assert(collision_flags == (fixture.hit ? 0x65 : 0x45));
                ++updates;
            }
            RENDER_OWNER before = state.body.owner;
            assert(engine_update_objects(&pool, &keys) == 0);
            assert(fixture.probes == 17 && fixture.transitions == 1);
            assert(fixture.last.handler == (call.handler == 0xe410 ? 0xae53U : 0xaa97U));
            assert(fixture.last.script == (state.form ? 0x591aU : 0x6116U) &&
                fixture.last.counter == 0 && state.age == 16);
            assert(state.body.owner.x == before.x && state.body.owner.y == before.y);
            ++updates;
        }
    }
    for (unsigned int mode = 0; mode < 8; ++mode) {
        ENGINE_OBJECT_POOL pool;
        RENDER_POOL renders;
        ENGINE_PLAYER_DEFLECTION state;
        FIXTURE fixture;
        unsigned char collision_flags = 0x81;
        initialize(&pool, &renders, &state, &fixture, &collision_flags);
        ENGINE_PLAYER_CALL call = {mode & 1 ? 0xe545U : 0xe410U, 0x61aa, 50};
        assert(engine_player_begin_deflection(fixture.object, &state, &call) == 0);
        ENGINE_PLAYER_CALL invalid = {0xe410, 0, 50};
        assert(engine_player_begin_deflection(fixture.object, &state, &invalid) == -1);
        assert(state.handler == call.handler && state.body.animation.script.position == 0x61aa);
        fixture.hit = -1;
        state.flags_high = mode & 2 ? 4 : 0;
        state.immunity = mode & 4 ? 1 : 0;
        state.controls = mode & 1 ? 8 : 4;
        assert(engine_update_objects(&pool, &keys) == 0);
        assert(fixture.transitions == 1);
        if ((mode & 2) && !(mode & 4)) {
            assert(fixture.last.handler == 0xef04 && fixture.probes == 0 &&
                collision_flags == 0x81 && state.age == 0 &&
                state.body.motion.velocity_x == 0x12345678);
        } else {
            assert(fixture.last.handler == (mode & 1 ? 0xaa97U : 0xae53U) &&
                fixture.probes == 1 && collision_flags == 0xa1 && state.age == 16 &&
                state.body.motion.velocity_x == 0 && state.body.motion.velocity_y == 0);
        }
    }
    ENGINE_OBJECT_POOL pool;
    RENDER_POOL renders;
    ENGINE_PLAYER_DEFLECTION state;
    FIXTURE fixture;
    unsigned char collision_flags = 0;
    initialize(&pool, &renders, &state, &fixture, &collision_flags);
    ENGINE_PLAYER_CALL call = {0xe410, 0x61aa, 50};
    assert(engine_player_begin_deflection(fixture.object, &state, &call) == 0);
    state.probe = 0;
    assert(engine_update_objects(&pool, &keys) == -1 && state.age == 0);
    state.probe = probe;
    state.age = 16;
    state.transition = 0;
    assert(engine_update_objects(&pool, &keys) == -1);
    assert(state.handler == 0xae53 && state.body.animation.counter == 0);
    call.handler = 0xaa97;
    assert(engine_player_begin_deflection(fixture.object, &state, &call) == -1);
    assert(state.handler == 0xae53);
    call.handler = 0xe410;
    assert(engine_player_begin_deflection(fixture.object, &state, &call) == 0);
    state.flags_high = 4;
    assert(engine_update_objects(&pool, &keys) == -1 && state.age == 0);
    state.flags_high = 0;
    fixture.hit = -1;
    state.collision_flags = 0;
    assert(engine_update_objects(&pool, &keys) == -1 && state.age == 0);
    printf("PASS: original player deflection selectors -> initialization -> dispatcher, "
        "%u full-script updates, 1966080 gravity cases, exact descriptors and motion, "
        "wrap/fractions, probe flags OR, stop/damage gates and explicit dependency errors\n", updates);
    return 0;
}
