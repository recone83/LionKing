#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static ENGINE_OBJECT_POOL pool;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR air;
static ENGINE_OBJECT *object;
static DOS64_INPUT keys;
static unsigned char collision_flags, probe_flags;
static short ceiling;
static unsigned int probes, transitions, sounds;
static unsigned short sample;
static ENGINE_PLAYER_CALL last;

static int probe(void *context, short x, short y, short *hit)
{
    assert(context == &air && x == air.player.body.owner.x && y == air.player.body.owner.y);
    ++probes;
    probe_flags = collision_flags;
    *hit = ceiling;
    return 0;
}

static int ground(void *context, short *kind, short *delta)
{
    assert(context == &air);
    *kind = *delta = 0;
    return 0;
}

static int edge(void *context, short *hit, short *kind, short *x, short *y)
{
    assert(context == &air);
    *hit = *kind = *x = *y = 0;
    return 0;
}

static int transition(void *context, const ENGINE_PLAYER_CALL *call,
    short kind, short x, short y)
{
    assert(context == &air && !kind && !x && !y);
    ++transitions;
    last = *call;
    object->behavior = 0;
    return 0;
}

static int sound(void *context, unsigned short value)
{
    assert(context == &air);
    ++sounds;
    sample = value;
    return 0;
}

static int sound_error(void *context, unsigned short value)
{
    (void)context; (void)value;
    return -1;
}

static short word(uint32_t value)
{
    value &= 65535U;
    return (short)(value < 32768 ? (int)value : (int)value - 65536);
}

static void setup(int right, unsigned short form)
{
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    memset(&air, 0, sizeof(air));
    air.player.body.owner = (RENDER_OWNER){32767, -32768};
    air.player.body.render_pool = &renders;
    air.player.body.node = render_acquire_node(&renders, &air.player.body.owner, 0, 0,
        animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    object = engine_acquire_object(&pool, 0);
    assert(air.player.body.node && object);
    air.player.form = form;
    air.player.context = &air;
    air.player.probe = probe;
    air.player.collision_flags = &collision_flags;
    air.ground = ground; air.edge = edge; air.transition = transition; air.sound = sound;
    collision_flags = 0xff;
    probe_flags = 0;
    probes = transitions = sounds = 0;
    ceiling = 0;
    last = (ENGINE_PLAYER_CALL){0};
    air.player.body.motion = (ENGINE_MOTION){65535, 12345,
        right ? 0x30000U : 0xfffd0000U, 0x12345678};
    air.player.body.animation.state = 0xffff;
}

static void launch(int right, unsigned short form, unsigned short counter)
{
    ENGINE_PLAYER_CALL call = {right ? 0xb604U : 0xb7e7U,
        form ? 0x5944U : 0x6180U, counter};
    assert(engine_player_begin_jump(&pool, object, &air, &call,
        form ? 0x5928U : 0x612cU) == 0);
    assert(air.player.handler == call.handler &&
        object->behavior == &engine_player_jump_behavior &&
        air.player.body.animation.script.position == call.script &&
        air.player.body.animation.counter == counter &&
        air.player.body.animation.state == 0xffff &&
        air.player.body.motion.velocity_y == (form ? 0xfffb0000U : 0xfffb2000U) &&
        air.jump_boost == (form ? 6 : 8) &&
        (air.player.body.node->pass_flags & 8) == (right ? 0 : 8) &&
        collision_flags == 0xdf && !probes);
}

int main(void)
{
    static const unsigned short forms[] = {0, 1, 65535};
    unsigned int delay_cases = 0, recovery_cases = 0, boost_cases = 0, ticks = 0;
    for (unsigned int f = 0; f < 3; ++f) {
        for (int right = 0; right <= 1; ++right) {
            /* Each original 16-bit delay, including negative signed values. */
            setup(right, forms[f]);
            launch(right, forms[f], 1);
            ANIMATION_PROGRAM initial = air.player.body.animation;
            for (unsigned int delay = 1; delay < 65536; ++delay) {
                object->behavior = &engine_player_jump_behavior;
                air.player.handler = right ? 0xb604U : 0xb7e7U;
                air.player.body.animation = initial;
                air.player.body.animation.counter = (unsigned short)delay;
                air.pressed = 0x10;
                uint32_t vy = air.player.body.motion.velocity_y;
                RENDER_OWNER owner = air.player.body.owner;
                assert(engine_update_objects(&pool, &keys) == 0 && !probes && !transitions);
                assert(air.player.body.animation.counter == delay - 1 &&
                    air.jump_boost == (forms[f] ? 6 : 8) &&
                    air.player.body.motion.velocity_y == vy &&
                    memcmp(&owner, &air.player.body.owner, sizeof(owner)) == 0);
                ++delay_cases;
            }
            /* Every boost byte and both hold sources, with exact probe ordering. */
            for (unsigned int boost = 0; boost < 256; ++boost) {
                for (unsigned int hold = 0; hold < 3; ++hold) {
                    setup(right, forms[f]);
                    launch(right, forms[f], 0);
                    air.jump_boost = (unsigned char)boost;
                    air.pressed = hold == 1 ? 0x20 : 0;
                    air.flags = hold == 2 ? 0x1000 : 0;
                    uint32_t vy = forms[f] ? 0xfffb0000U : 0xfffb2000U;
                    unsigned int expected_boost = boost ? hold ? boost - 1 : 0 : 0;
                    if (boost && hold) vy -= forms[f] ? 0x9000U : 0x5000U;
                    vy += forms[f] ? 0x6000U : 0x4e00U;
                    assert(engine_update_objects(&pool, &keys) == 0 && !transitions && probes == 1);
                    assert(air.player.body.motion.velocity_y == vy && air.jump_boost == expected_boost);
                    assert(probe_flags == (right && !expected_boost ? 0xff : 0xdf));
                    assert(collision_flags == (!expected_boost ? 0xff : 0xdf));
                    ++boost_cases;
                }
            }
            /* Full ascent: independent wrapped 16.16 trajectory and script stream. */
            for (unsigned int held = 0; held <= 8; held += 8) {
                setup(right, forms[f]);
                launch(right, forms[f], forms[f] ? 10 : 4);
                air.player.body.owner = (RENDER_OWNER){160, 160};
                assert(animation_program_step(&air.player.body.animation,
                    air.player.body.node, &air.player.body.owner, 0, 0) == 0);
                ANIMATION_PROGRAM reference = air.player.body.animation;
                RENDER_OWNER reference_owner = air.player.body.owner;
                RENDER_NODE reference_node = *air.player.body.node;
                reference_node.owner = &reference_owner;
                uint32_t y = UINT32_C(0xa03039), x = UINT32_C(0xa0ffff);
                uint32_t vy = forms[f] ? 0xfffb0000U : 0xfffb2000U;
                unsigned int boost = forms[f] ? 6 : 8, delay = forms[f] ? 10 : 4;
                unsigned int step = 0;
                for (;;) {
                    ++step;
                    assert(step < 100);
                    air.pressed = (right ? 8 : 4) | (step <= delay + held ? 0x20 : 0);
                    if (delay) {
                        --delay;
                    } else {
                        if (boost) {
                            --boost;
                            if (air.pressed & 0x20) vy -= forms[f] ? 0x9000U : 0x5000U;
                            else boost = 0;
                        }
                        int64_t sy = vy < 0x80000000U ? vy : (int64_t)vy - INT64_C(0x100000000);
                        if (sy >= (forms[f] ? -0x30000 : 0)) {
                            assert(engine_update_objects(&pool, &keys) == 0 &&
                                object->behavior == &engine_player_air_behavior &&
                                air.player.handler == (right ? 0xaa97U : 0xae53U) &&
                                air.jump_air_script == (forms[f] ? 0x5928U : 0x612cU));
                            break;
                        }
                        vy += forms[f] ? 0x6000U : 0x4e00U;
                        y += vy; x += right ? 0x30000U : 0xfffd0000U;
                    }
                    reference_owner = (RENDER_OWNER){word(x >> 16), word(y >> 16)};
                    assert(animation_program_step(&reference, &reference_node,
                        &reference_owner, 0, 0) == 0);
                    assert(engine_update_objects(&pool, &keys) == 0);
                    assert(air.player.body.owner.x == word(x >> 16) &&
                        air.player.body.owner.y == word(y >> 16) &&
                        air.player.body.motion.velocity_y == vy &&
                        air.player.body.motion.fraction_y == (unsigned short)y &&
                        air.player.body.animation.script.position == reference.script.position &&
                        air.player.body.node->parts == reference_node.parts);
                    ++ticks;
                }
            }
            setup(right, forms[f]);
            ENGINE_PLAYER_CALL recovery = {right ? 0xb253U : 0xb19fU,
                forms[f] ? 0x58feU : 0x6156U, 30};
            air.player.flags_high = 0xff;
            assert(engine_player_begin_recovery(&pool, object, &air, &recovery) == 0);
            assert(sounds == 1 && sample == (forms[f] ? 5 : 4) &&
                air.player.flags_high == 0xef && air.player.body.animation.state == 0xffff);
            initial = air.player.body.animation;
            air.player.flags_high = 0;
            for (unsigned int count = 0; count < 65536; ++count) {
                object->behavior = &engine_player_recovery_behavior;
                air.player.handler = recovery.handler;
                air.player.body.animation = initial;
                air.player.body.animation.counter = (unsigned short)count;
                transitions = 0;
                assert(engine_update_objects(&pool, &keys) == 0);
                assert(air.player.body.animation.counter == (count ? count - 1 : 0) &&
                    transitions == (count ? 0U : 1U));
                if (!count) assert(last.handler == (right ? 0xc8d5U : 0xc2cdU));
                ++recovery_cases;
            }
            setup(right, forms[f]);
            assert(engine_player_begin_recovery(&pool, object, &air, &recovery) == 0);
            air.surface_kind = 3;
            assert(engine_update_objects(&pool, &keys) == 0 &&
                transitions == 1 && !air.player.body.animation.counter);
            setup(right, forms[f]);
            assert(engine_player_begin_recovery(&pool, object, &air, &recovery) == 0);
            ENGINE_PLAYER_CALL same_recovery = {recovery.handler, 0, 65535};
            assert(engine_player_begin_recovery(&pool, object, &air, &same_recovery) == 0 &&
                air.player.body.animation.counter == 29 && sounds == 1);
            air.player.flags_high = 4;
            assert(engine_update_objects(&pool, &keys) == 0 &&
                last.handler == 0xef04 && air.player.body.animation.counter == 29);
            object->behavior = &engine_player_recovery_behavior;
            air.player.immunity = 1;
            transitions = 0;
            assert(engine_update_objects(&pool, &keys) == 0 &&
                air.player.body.animation.counter == 28 && !transitions);
            setup(right, forms[f]);
            launch(right, forms[f], 0);
            air.flags = 0xffff; air.pressed = right ? 4 : 8;
            uint32_t launch_y = air.player.body.motion.velocity_y;
            assert(engine_update_objects(&pool, &keys) == 0 &&
                air.player.handler == (right ? 0xb7e7U : 0xb604U) &&
                air.player.body.owner.x == 32767 && air.flags == 0xdfff &&
                air.player.body.motion.velocity_y ==
                    launch_y - (forms[f] ? 0x9000U : 0x5000U) + (forms[f] ? 0x6000U : 0x4e00U));
            ENGINE_PLAYER_CALL same = {air.player.handler, 0, 500};
            air.pressed = 0;
            assert(engine_player_begin_jump(&pool, object, &air, &same, 0) == 0 &&
                air.jump_air_script == (forms[f] ? 0x5928U : 0x612cU));
            setup(right, forms[f]);
            launch(right, forms[f], 0);
            ceiling = 1;
            assert(engine_update_objects(&pool, &keys) == 0 &&
                object->behavior == &engine_player_air_behavior && (collision_flags & 0x20));
            setup(right, forms[f]);
            launch(right, forms[f], 5);
            air.player.flags_high = 4; air.pressed = 0x10;
            assert(engine_update_objects(&pool, &keys) == 0 && last.handler == 0xef04 &&
                air.player.body.animation.counter == 5 && !probes);
            setup(right, forms[f]);
            launch(right, forms[f], 0);
            air.pressed = 0x10;
            assert(engine_update_objects(&pool, &keys) == 0);
            assert(forms[f] ? last.handler == 0x10bc6 && last.script == 0x57c1 :
                !transitions && probes == 1);
            setup(right, forms[f]);
            air.sound = 0;
            assert(engine_player_begin_recovery(&pool, object, &air, &recovery) == -1);
            setup(right, forms[f]);
            air.sound = sound_error;
            assert(engine_player_begin_recovery(&pool, object, &air, &recovery) == -1);
            setup(right, forms[f]);
            launch(right, forms[f], 0);
            air.player.flags_high = 0x10;
            air.pressed = right ? 0x28 : 0x24;
            assert(engine_update_objects(&pool, &keys) == 0 &&
                air.player.body.motion.velocity_x == (right ? 0x30000U : 0xfffd0000U) &&
                air.player.body.owner.x == word(32767U + (right ? 3U : 0U - 3U)));
            setup(right, forms[f]);
            launch(right, forms[f], 0);
            air.player.probe = 0;
            assert(engine_update_objects(&pool, &keys) == -1);
            air.player.collision_flags = 0;
            assert(engine_player_begin_jump(&pool, object, &air, &same, 0) == -1);
        }
    }
    printf("PASS: original jump/ascent/recovery, %u delay cases, %u recovery cases, "
        "%u boost cases, %u traced ascent ticks, forms/fractions/wrap, probe order, "
        "direction continuation, damage/attack gates, ceiling and explicit errors\n",
        delay_cases, recovery_cases, boost_cases, ticks);
    return 0;
}
