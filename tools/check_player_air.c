#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static ENGINE_OBJECT_POOL pool;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR air;
static ENGINE_OBJECT *object;
static unsigned char collision_flags;
static short ceiling, ground_kind, ground_delta, edge_hit, edge_kind, edge_x, edge_y;
static unsigned int probes, grounds, edges, transitions;
static ENGINE_PLAYER_CALL last;
static short last_kind, last_x, last_y;
static DOS64_INPUT keys;

static int probe(void *context, short x, short y, short *hit)
{
    assert(context == &air && x == air.player.body.owner.x && y == air.player.body.owner.y);
    ++probes;
    *hit = ceiling;
    return 0;
}

static int ground(void *context, short *kind, short *delta)
{
    assert(context == &air);
    ++grounds;
    *kind = ground_kind;
    *delta = ground_delta;
    return 0;
}

static int edge(void *context, short *hit, short *kind, short *x, short *y)
{
    assert(context == &air);
    ++edges;
    *hit = edge_hit;
    *kind = edge_kind;
    *x = edge_x;
    *y = edge_y;
    return 0;
}

static int transition(void *context, const ENGINE_PLAYER_CALL *call,
    short kind, short x, short y)
{
    assert(context == &air);
    ++transitions;
    last = *call;
    last_kind = kind; last_x = x; last_y = y;
    object->behavior = 0;
    return 0;
}

static short word(unsigned int value)
{
    value &= 65535U;
    return (short)(value < 32768 ? (int)value : (int)value - 65536);
}

static void setup(int right, unsigned short form)
{
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    memset(&air, 0, sizeof(air));
    air.player.body.owner = (RENDER_OWNER){32760, 100};
    air.player.body.render_pool = &renders;
    air.player.body.node = render_acquire_node(&renders, &air.player.body.owner, 0, 0,
        animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    assert(air.player.body.node);
    object = engine_acquire_object(&pool, &engine_player_air_behavior);
    assert(object);
    object->context = &air;
    air.player.handler = right ? 0xaa97U : 0xae53U;
    air.player.form = form;
    air.player.probe = probe;
    air.player.context = &air;
    air.player.collision_flags = &collision_flags;
    air.ground = ground; air.edge = edge; air.transition = transition;
    collision_flags = 0x81;
    ceiling = ground_kind = ground_delta = edge_hit = edge_kind = edge_x = edge_y = 0;
    probes = grounds = edges = transitions = 0;
    last = (ENGINE_PLAYER_CALL){0};
    air.player.body.motion = (ENGINE_MOTION){65535, 12345, right ? 0x30000U : 0xfffd0000U,
        UINT32_C(0xfffe0000)};
    unsigned int script = form ? 0x591aU : 0x6116U;
    assert(animation_program_initialize(&air.player.body.animation, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, script,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
    air.pressed = right ? 8 : 4;
}

int main(void)
{
    static const unsigned short forms[] = {0, 1, 65535};
    static const uint32_t velocities_y[] = {0, 0x70000, 0x7fffffff, 0x80000000, 0xffffffff};
    unsigned int gravity_cases = 0;
    for (unsigned int f = 0; f < 3; ++f) {
        for (unsigned int v = 0; v < 5; ++v) {
            for (unsigned int flags = 0; flags <= 2; flags += 2) {
                for (unsigned int fraction = 0; fraction < 65536; ++fraction) {
                    ENGINE_MOTION motion = {0, (unsigned short)fraction, 0, velocities_y[v]};
                    RENDER_OWNER owner = {7, 32767};
                    uint32_t velocity = velocities_y[v] + (forms[f] ? 0x6000U : 0x4e00U);
                    int64_t signed_velocity = velocity < UINT32_C(0x80000000) ? velocity :
                        (int64_t)velocity - INT64_C(0x100000000);
                    if (!flags && signed_velocity > 0x70000) velocity = 0x70000;
                    uint32_t position = UINT32_C(0x7fff0000) + fraction + velocity;
                    assert(engine_motion_air_gravity(&motion, &owner, forms[f],
                        (unsigned char)flags) == 0);
                    assert(owner.x == 7 && owner.y == word(position >> 16) &&
                        motion.fraction_y == (unsigned short)position && motion.velocity_y == velocity);
                    ++gravity_cases;
                }
            }
        }
    }
    assert(engine_motion_air_gravity(0, 0, 0, 0) == -1);
    unsigned int ticks = 0;
    for (unsigned int f = 0; f < 3; ++f) {
        for (int right = 0; right <= 1; ++right) {
            setup(right, forms[f]);
            air.player.body.animation.counter = 3;
            air.player.controls = 0;
            uint32_t x = UINT32_C(0x7ff8ffff);
            uint32_t y = UINT32_C(0x00643039);
            uint32_t vy = UINT32_C(0xfffe0000);
            for (unsigned int tick = 1; tick <= 30; ++tick) {
                vy += forms[f] ? 0x6000U : 0x4e00U;
                if (vy < UINT32_C(0x80000000) && vy > 0x70000U) vy = 0x70000;
                y += vy;
                x += right ? 0x30000U : 0xfffd0000U;
                assert(engine_update_objects(&pool, &keys) == 0);
                assert(!transitions && grounds == tick && edges == tick);
                assert(air.player.body.owner.x == word(x >> 16) &&
                    air.player.body.owner.y == word(y >> 16));
                assert(air.player.body.motion.fraction_x == (unsigned short)x &&
                    air.player.body.motion.fraction_y == (unsigned short)y &&
                    air.player.body.motion.velocity_y == vy);
                assert(air.player.body.animation.counter == (right ? tick < 3 ? 3 - tick : 0 : 3));
                assert(air.player.body.animation.state == tick);
                ++ticks;
            }
            assert(right ? probes > 0 : probes == 0);
        }
    }
    /* Exact gate precedence, before ground/edge callbacks. */
    static const unsigned short flags[] = {4, 0x800, 0x200, 0x40};
    static const unsigned int targets[] = {0xf6cc, 0x10075, 0xfcb5, 0xf94d};
    for (int right = 0; right <= 1; ++right) {
        for (unsigned int i = 0; i < 4; ++i) {
            setup(right, 0);
            air.flags = flags[i];
            assert(engine_update_objects(&pool, &keys) == 0);
            assert(transitions == 1 && last.handler == targets[i] && !grounds && !edges);
            assert(last.script == (i == 2 ? 0x6c31U : 0));
        }
        setup(right, 1);
        air.player.flags_high = 0x20;
        air.pressed = 0x10;
        air.flags = 4;
        assert(engine_update_objects(&pool, &keys) == 0 && last.handler == 0xf3fb);
        setup(right, 0);
        air.player.flags_high = 0x20;
        assert(engine_update_objects(&pool, &keys) == 0 && last.handler == 0xf5f1);
        setup(right, 65535);
        air.pressed = 0x10;
        assert(engine_update_objects(&pool, &keys) == 0 && last.handler == 0x10bc6 &&
            last.script == 0x57c1 && !grounds);
        setup(right, 0);
        air.player.flags_high = 4;
        assert(engine_update_objects(&pool, &keys) == 0 && last.handler == 0xef04 && !grounds);
        setup(right, 0);
        air.player.flags_high = 4; air.player.immunity = 1;
        assert(engine_update_objects(&pool, &keys) == 0 && !transitions && grounds == 1);
        setup(right, 0);
        air.contact_kind = 4;
        assert(engine_update_objects(&pool, &keys) == 0 && last.handler == 0x10d78 &&
            grounds == 1 && edges == 0 && air.player.body.animation.state == 1);
        setup(right, 0);
        ceiling = -1;
        assert(engine_update_objects(&pool, &keys) == 0);
        assert(collision_flags == (right ? 0xa1 : 0x81));
        assert(air.player.body.motion.velocity_y == (right ? 0x4e00U : 0xfffe4e00U));
        /* Flags bit 1 is an original asymmetric script-reset branch. */
        setup(right, 0);
        air.flags = 0xffff;
        assert(engine_update_objects(&pool, &keys) == 0);
        assert(air.flags == 2 && air.player.body.animation.script.position == (right ? 0x61e2U : 0x6110U));
        assert(grounds == (right ? 0U : 1U));
        /* Edge sentinel suppresses transition; preserve all edge operands otherwise. */
        setup(right, 0);
        edge_hit = -1; edge_kind = right ? 0xf8 : 0xe8;
        assert(engine_update_objects(&pool, &keys) == 0 && !transitions);
        setup(right, 0);
        edge_hit = -1; edge_kind = 7; edge_x = -32768; edge_y = 32767;
        assert(engine_update_objects(&pool, &keys) == 0 && transitions == 1);
        assert(last.handler == (right ? 0xe8dfU : 0xe775U) &&
            last_kind == 7 && last_x == -32768 && last_y == 32767);
        /* Landing threshold compares signed integer delta to full 16.16 velocity. */
        static const short deltas[] = {-21, -20, 0, 1};
        for (unsigned int i = 0; i < 4; ++i) {
            setup(right, 0);
            air.player.body.motion.velocity_y = 0;
            ground_kind = 1; ground_delta = deltas[i];
            assert(engine_update_objects(&pool, &keys) == 0);
            assert(transitions == (i == 1 || i == 2 ? 1U : 0));
            if (transitions) {
                assert(air.player.body.owner.y == 100 + deltas[i] && edges == 0);
                assert(last.handler == (right ? 0xcdc2U : 0xd108U));
                assert(air.player.body.motion.velocity_y == 0);
            }
        }
        /* Anchor centering, free integration and flag-dependent uncapped gravity. */
        for (int dx = -1; dx <= 1; ++dx) {
            setup(right, 0);
            air.flags = 2; air.anchor_x = 32760 + dx; air.anchor_y = 1;
            air.player.body.motion.velocity_x = 0;
            air.player.body.motion.velocity_y = 0x70000;
            ground_kind = 1; ground_delta = 0;
            assert(engine_update_objects(&pool, &keys) == 0 && !transitions && edges == 1);
            assert(air.player.body.owner.x == 32760 + dx &&
                air.player.body.motion.velocity_y == 0x74e00);
        }
        setup(right, 0);
        air.player.body.animation.counter = 0;
        air.pressed = right ? 4 : 8;
        assert(engine_update_objects(&pool, &keys) == 0 && !transitions);
        assert(air.player.handler == (right ? 0xae53U : 0xaa97U));
        assert(!!(air.player.body.node->pass_flags & 8) == !!right);
        assert(air.player.body.owner.x == 32760);
        setup(right, 0);
        air.player.body.animation.counter = 0; air.pressed = 0;
        assert(engine_update_objects(&pool, &keys) == 0 &&
            air.player.body.motion.velocity_x == 0 && air.player.body.owner.x == 32760);
    }
    /* Every duration word, both landing handlers and signed velocity boundaries. */
    static const uint32_t velocities[] = {0xfffffffd, 0xfffffffe, 0xffffffff, 0, 1, 2, 3};
    unsigned int landings = 0;
    for (unsigned int f = 0; f < 3; ++f) {
        for (int right = 0; right <= 1; ++right) {
            setup(right, forms[f]);
            for (unsigned int d = 0; d < 65536; ++d) {
                for (unsigned int v = 0; v < 7; ++v) {
                    air.flags = 0xffff; air.player_flags = 0xffff;
                    air.player.flags_high = 0x1f;
                    air.player.body.motion.velocity_x = velocities[v];
                    air.player.body.motion.velocity_y = 0x12345678;
                    assert(engine_player_land(&air, right ? 0xb307 : 0xb4a0, word(d)) == 0);
                    assert(air.flags == 0xdffd && air.player_flags == 0xfffd &&
                        air.player.flags_high == 0x0f && air.player.body.animation.state == 0);
                    assert(air.player.body.motion.velocity_y == (right ? 0U : 0x12345678U));
                    if (word(d) > 60) {
                        assert(last.handler == (right ? 0xb253U : 0xb19fU) &&
                            last.counter == 30 && last.script == (forms[f] ? 0x58feU : 0x6156U));
                    } else {
                        int moving = right ? v >= 5 : v <= 1;
                        assert(last.handler == (right ? moving ? 0xcdc2U : 0xc8d5U :
                            moving ? 0xd108U : 0xc2cdU));
                        assert(last.script == (moving ? forms[f] ? 0x590cU : 0x6164U :
                            forms[f] ? 0x58f0U : 0x6148U));
                    }
                    ++landings;
                }
            }
        }
    }
    setup(1, 0);
    air.landing_flags = 1;
    assert(engine_player_land(&air, 0xb307, 32767) == 0 && last.handler == 0xb43d &&
        last.script == 0x7040);
    setup(1, 0);
    air.player.flags_high = 0x80;
    assert(engine_player_land(&air, 0xb307, 61) == 0 && last.handler == 0xcdc2);
    setup(0, 0);
    air.player.flags_high = 0x80;
    assert(engine_player_land(&air, 0xb4a0, 61) == 0 && last.handler == 0xd108);
    setup(0, 1);
    air.player.flags_high = 0x20;
    air.flags = air.player_flags = 0xffff;
    assert(engine_player_land(&air, 0xb4a0, 61) == 0 && last.handler == 0xf3fb &&
        air.flags == 0xffff && air.player_flags == 0xffff);
    setup(1, 0);
    air.ground = 0;
    assert(engine_update_objects(&pool, &keys) == -1);
    setup(0, 0);
    air.edge = 0;
    assert(engine_update_objects(&pool, &keys) == -1);
    setup(1, 0);
    air.transition = 0; air.flags = 4;
    assert(engine_update_objects(&pool, &keys) == -1);
    assert(engine_player_land(&air, 0, 0) == -1);
    /* Same-handler continuation must NOT reset script/velocity/facing. */
    setup(0, 0);
    unsigned int entry = air.player.body.animation.script.position;
    ENGINE_PLAYER_CALL call = {0xae53, 0x61e2, 99};
    assert(engine_player_begin_air(&pool, object, &air, &call) == 0);
    assert(air.player.body.animation.script.position != 0x61e2 && entry == 0x6116 &&
        air.player.body.animation.counter == 0 && air.player.flags_high == 0);
    setup(0, 0);
    call = (ENGINE_PLAYER_CALL){0xaa97, 0x6116, 0};
    air.pressed = 8;
    assert(engine_player_begin_air(&pool, object, &air, &call) == 0);
    assert(air.player.handler == 0xaa97 && air.player.flags_high == 0x10 &&
        !(air.player.body.node->pass_flags & 8) && object->context == &air);
    call = (ENGINE_PLAYER_CALL){0xae53, 0, 0};
    assert(engine_player_begin_air(&pool, object, &air, &call) == -1 &&
        air.player.handler == 0xaa97);
    printf("PASS: original 0x1aa97/0x1ae53 air and 0x1b307/0x1b4a0 landing, "
        "%u traced ticks, %u exact landing cases, %u flag-dependent gravity cases, "
        "asymmetric probes/reset/counter, "
        "gate precedence, sentinel/edge operands, anchor motion, same-handler continuation\n",
        ticks, landings, gravity_cases);
    return 0;
}
