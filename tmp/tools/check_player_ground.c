#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static ENGINE_OBJECT_POOL pool;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR state;
static ENGINE_OBJECT *object;
static DOS64_INPUT input;
static unsigned char collision_flags;
static short supported, ceiling;
static unsigned int supports, probes, transitions, events;
static ENGINE_PLAYER_CALL last;
static short side, vx_word, fraction;

static int support(void *context, short *result)
{
    assert(context == &state);
    ++supports;
    *result = supported;
    return 0;
}

static int probe(void *context, short x, short y, short *result)
{
    assert(context == &state && x == state.player.body.owner.x && y == state.player.body.owner.y);
    ++probes;
    *result = ceiling;
    return 0;
}

static int ground(void *context, short *kind, short *delta)
{
    assert(context == &state);
    *kind = *delta = 0;
    return 0;
}

static int edge(void *context, short *hit, short *kind, short *x, short *y)
{
    assert(context == &state);
    *hit = *kind = *x = *y = 0;
    return 0;
}

static int transition(void *context, const ENGINE_PLAYER_CALL *call, short kind, short x, short y)
{
    assert(context == &state);
    ++transitions;
    last = *call; side = kind; vx_word = x; fraction = y;
    object->behavior = 0;
    return 0;
}

static int event(void *context, unsigned int target)
{
    assert(context == &state);
    assert(target == 0x20bec || target == 0x20c70 || target == 0x20d55 || target == 0x20cf4);
    ++events;
    return 0;
}

static int sound(void *context, unsigned short sample)
{
    assert(context == &state && sample == 6);
    return 0;
}

static short word(uint32_t value)
{
    value &= 0xffffU;
    return (short)(value < 0x8000U ? (int)value : (int)value - 65536);
}

static void setup(unsigned int handler, unsigned short form)
{
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    memset(&state, 0, sizeof(state));
    state.player.body.owner = (RENDER_OWNER){32767, 160};
    state.player.body.render_pool = &renders;
    state.player.body.node = render_acquire_node(&renders, &state.player.body.owner, 0, 0,
        animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    object = engine_acquire_object(&pool, &engine_player_ground_behavior);
    assert(state.player.body.node && object);
    state.player.handler = handler; state.player.form = form;
    state.player.context = &state; state.player.collision_flags = &collision_flags;
    state.player.probe = probe; state.support = support;
    state.ground = ground; state.edge = edge; state.transition = transition;
    state.animation_event = event;
    state.sound = sound;
    object->context = &state;
    collision_flags = 0xff; supported = 1; ceiling = 0;
    supports = probes = transitions = events = 0;
    last = (ENGINE_PLAYER_CALL){0};
    state.player.body.motion = (ENGINE_MOTION){65535, 12345, 0, 0};
    assert(animation_program_initialize(&state.player.body.animation, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, form ? 0x58f0U : 0x6148U,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
}

int main(void)
{
    static const unsigned int handlers[] = {0xc8d5, 0xc2cd, 0xcdc2, 0xd108, 0xbeb7, 0xc0a1};
    static const unsigned short forms[] = {0, 1, 65535};
    unsigned int trajectories = 0, gate_cases = 0, idle_cases = 0, turn_cases = 0;
    for (unsigned int f = 0; f < 3; ++f) {
        for (unsigned int h = 0; h < 6; ++h) {
            unsigned int handler = handlers[h];
            setup(handler, forms[f]);
            state.player.handler = 0;
            state.player.flags_high = 0xff;
            state.player.body.animation.counter = 99;
            state.player.body.animation.state = 12;
            state.player.body.motion.velocity_y = 0xffffffff;
            state.player.immunity = 1;
            ENGINE_PLAYER_CALL call = {handler, forms[f] ? 0x58f0U : 0x6148U, 123};
            if (h == 2 || h == 3) {
                state.pressed = h == 2 ? 8 : 4;
                call.script = forms[f] ? 0x597cU : 0x6100U;
            }
            assert(engine_player_begin_ground(&pool, object, &state, &call) == 0);
            assert(state.player.handler == handler &&
                object->behavior == &engine_player_ground_behavior &&
                (state.player.body.node->pass_flags & 8) == (h == 1 || h == 3 || h == 5 ? 8 : 0));
            if (h < 2) {
                assert(!supports && collision_flags == 0xfd &&
                    state.player.flags_high == 0xef &&
                    state.player.body.animation.state == 0 &&
                    state.player.body.animation.counter == 0);
            } else if (h < 4) {
                assert(supports == 1 && state.player.flags_high == 0xe7 &&
                    state.player.body.motion.velocity_y == 0);
            } else {
                assert(!supports && state.player.body.animation.counter == 0 &&
                    collision_flags == 0xff && state.player.body.motion.velocity_y == 0xffffffff);
            }
            setup(handler, forms[f]);
            state.flags = 1;
            state.player.flags_high = 4;
            assert(engine_update_objects(&pool, &input) == 0);
            assert(transitions == (h == 3 || h >= 4 ? 1U : 0U));
            assert(state.flags == (h >= 4 ? 1 : 0));
            setup(handler, forms[f]);
            state.player.flags_high = 4;
            assert(engine_update_objects(&pool, &input) == 0 &&
                last.handler == 0xef04 && !supports);
            for (unsigned int kind = 0; kind < 256; ++kind) {
                setup(handler, forms[f]);
                state.contact_kind = (unsigned char)kind;
                state.pressed = h == 2 ? 8 : h == 3 ? 4 : 0;
                assert(engine_update_objects(&pool, &input) == 0);
                if (kind == 3) {
                    assert(last.handler == 0xef04);
                } else if (h < 4 && (kind == 6 || kind == 9)) {
                    assert(last.handler == 0xf80d && fraction == 0 &&
                        side == (kind == 6 ? 1 : 0) && vx_word == (kind == 6 ? -3 : 3));
                } else if (h < 4 && (kind == 5 || kind == 8 || kind == 0xd8 || kind == 0xd9)) {
                    assert(last.handler == 0xfe3c && fraction == 0 &&
                        vx_word == (kind == 5 || kind == 0xd8 ? -4 : 4));
                } else {
                    assert(!transitions);
                }
                ++gate_cases;
            }
            setup(handler, forms[f]);
            supported = 0;
            assert(engine_update_objects(&pool, &input) == 0 &&
                object->behavior == &engine_player_air_behavior &&
                state.player.handler == (h == 0 || h == 2 || h == 5 ? 0xaa97U : 0xae53U));
            setup(handler, forms[f]);
            state.support = 0;
            assert(engine_update_objects(&pool, &input) == -1);
        }
        for (int right = 0; right <= 1; ++right) {
            unsigned int idle = right ? 0xc8d5U : 0xc2cdU, run = right ? 0xcdc2U : 0xd108U;
            setup(run, forms[f]);
            state.player.handler = 0;
            state.pressed = right ? 8 : 4;
            ENGINE_PLAYER_CALL call = {run, forms[f] ? 0x597cU : 0x6100U, 0};
            assert(engine_player_begin_ground(&pool, object, &state, &call) == 0);
            uint32_t position = UINT32_C(0x7fffffff) + (right ? 0x24000U : 0xfffdc000U);
            uint32_t velocity = right ? 0x24000U : 0xfffdc000U;
            for (unsigned int tick = 0; tick < 100; ++tick) {
                velocity += right ? 0x4000U : 0xffffc000U;
                if (right && velocity > 0x40000U) velocity = 0x40000;
                if (!right && velocity < 0xfffc0000U) velocity = 0xfffc0000;
                position += velocity;
                assert(engine_update_objects(&pool, &input) == 0 && !transitions);
                assert(state.player.body.owner.x == word(position >> 16) &&
                    state.player.body.owner.y == 160 &&
                    state.player.body.motion.velocity_x == velocity &&
                    state.player.body.motion.fraction_x == (unsigned short)position);
                ++trajectories;
            }
            state.pressed = 0;
            assert(engine_update_objects(&pool, &input) == 0 &&
                state.player.handler == idle && state.player.body.motion.velocity_x == 0 &&
                state.player.body.motion.velocity_y == 0 && collision_flags == 0xfd);
            /* Every signed idle state against original look-up/release threshold. */
            setup(idle, forms[f]);
            ANIMATION_PROGRAM initial = state.player.body.animation;
            for (unsigned int age = 0; age < 65536; ++age) {
                for (unsigned int up = 0; up < 2; ++up) {
                    object->behavior = &engine_player_ground_behavior;
                    state.player.handler = idle;
                    state.player.body.animation = initial;
                    state.player.body.animation.state = (unsigned short)age;
                    state.pressed = (unsigned short)up;
                    state.player.flags_high = 0;
                    transitions = 0;
                    assert(engine_update_objects(&pool, &input) == 0 && !transitions);
                    if (age == 50 && up) {
                        assert(state.player.flags_high == 1 &&
                            state.player.body.animation.state == 51 &&
                            state.player.body.animation.script.position == (forms[f] ? 0x62b4U : 0x628aU));
                    } else if (word(age) > 50 && !up) {
                        assert(state.player.body.animation.state == 0 &&
                            state.player.body.animation.script.position == (forms[f] ? 0x62a6U : 0x6298U));
                    } else {
                        assert(state.player.body.animation.state ==
                            (unsigned short)(age + (word(age) <= 50 ? up : 0)));
                    }
                    ++idle_cases;
                }
            }
            for (unsigned int count = 0; count < 65536; ++count) {
                setup(right ? 0xc0a1U : 0xbeb7U, forms[f]);
                state.player.body.animation.counter = (unsigned short)count;
                assert(engine_update_objects(&pool, &input) == 0);
                assert(state.player.handler == (word(count) < 7 ?
                    right ? 0xc0a1U : 0xbeb7U : idle));
                ++turn_cases;
            }
            setup(run, forms[f]);
            state.pressed = 0x20;
            assert(engine_update_objects(&pool, &input) == 0 &&
                object->behavior == &engine_player_jump_behavior &&
                state.player.body.animation.counter == 0 &&
                state.jump_air_script == (forms[f] ? 0x591aU : 0x6116U) &&
                state.player.body.animation.script.position == (forms[f] ? 0x5936U : 0x6172U));
            setup(run, forms[f]);
            state.flags = 0x1000; state.pressed = right ? 8 : 4;
            assert(engine_update_objects(&pool, &input) == 0);
            assert(right ? object->behavior == &engine_player_jump_behavior &&
                state.jump_air_script == (forms[f] ? 0x5928U : 0x612cU) :
                object->behavior == &engine_player_ground_behavior);
            setup(idle, forms[f]);
            state.pressed = 0x20;
            assert(engine_update_objects(&pool, &input) == 0 &&
                object->behavior == &engine_player_jump_behavior &&
                state.player.body.animation.counter == (forms[f] ? 10 : 4));
            setup(idle, forms[f]);
            supported = 0; state.player.body.animation.counter = 1;
            assert(engine_update_objects(&pool, &input) == 0 &&
                last.handler == 0xc884 && last.script == 0x5e35 && last.counter == 100 && supports == 1);
            setup(idle, forms[f]);
            state.player.controls = right ? 4 : 8; state.pressed = right ? 8 : 4;
            assert(engine_update_objects(&pool, &input) == 0 &&
                state.player.handler == (right ? 0xbeb7U : 0xc0a1U));
            setup(run, forms[f]);
            state.player.body.motion.velocity_x = right ? 0x30001U : 0xfffcffffU;
            state.pressed = 2;
            assert(engine_update_objects(&pool, &input) == 0);
            if (!forms[f]) assert(state.player.handler == (right ? 0xea46U : 0xeb56U) &&
                (state.player.flags_high & 8) && (collision_flags & 2));
            setup(idle, forms[f]);
            state.landing_flags = 1;
            assert(engine_update_objects(&pool, &input) == 0);
            assert(right ? state.player.body.animation.state == 51 && state.player.flags_high == 1 :
                last.handler == 0xc8d5 && state.player.handler == 0xc8d5);
            setup(idle, forms[f]);
            state.pressed = 2;
            assert(engine_update_objects(&pool, &input) == 0 &&
                state.player.handler == (right ? 0xbc80U : 0xb9caU) &&
                collision_flags == 0xfd);
            for (unsigned int age = 49; age <= 52; ++age) {
                state.player.body.animation.state = (unsigned short)age;
                assert(engine_update_objects(&pool, &input) == 0);
                assert(state.player.body.animation.state == (age <= 50 ? age + 1 : age));
                if (age == 50) assert(state.player.flags_high & 2);
            }
            state.pressed = 0;
            assert(engine_update_objects(&pool, &input) == 0 &&
                state.player.handler == idle && !(state.player.flags_high & 2));
            setup(right ? 0xbc80U : 0xb9caU, forms[f]);
            state.pressed = 0x22; state.player.flags_high = 2;
            assert(engine_update_objects(&pool, &input) == 0 &&
                object->behavior == &engine_player_jump_behavior &&
                !(state.player.flags_high & 2));
            setup(right ? 0xea46U : 0xeb56U, forms[f]);
            state.player.body.motion.velocity_x = right ? 0x30000U : 0xfffd0000U;
            assert(engine_update_objects(&pool, &input) == 0 &&
                state.player.body.motion.velocity_x == (right ? 0x2f200U : 0xfffd0e00U));
            state.boundary_controls = right ? 8 : 4;
            assert(engine_update_objects(&pool, &input) == 0 &&
                state.player.handler == (right ? 0xeb56U : 0xea46U));
        }
    }
    printf("PASS: original idle/run/turn, %u independent trajectory ticks, %u terrain gates, "
        "%u signed idle threshold cases, %u signed turn counter cases, "
        "ground reset, asymmetric flags, support/fall, exact jump scripts and errors\n",
        trajectories, gate_cases, idle_cases, turn_cases);
    return 0;
}
