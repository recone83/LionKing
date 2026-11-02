#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static ENGINE_OBJECT_POOL pool;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR player;
static ENGINE_OBJECT *object;
static DOS64_INPUT input;
static RENDER_OWNER source;
static unsigned char collision;
static short supported;
static unsigned int sounds;
static unsigned short sample;
static short touching;
static unsigned int contact_queries;
static short ledge_x, ledge_y;
static short edge_hit, edge_kind;
static unsigned int edge_queries;

static int ledge_height(void *context, short x, short y, short *height)
{
    assert(context == &player);
    ledge_x = x; ledge_y = y;
    *height = 16;
    return 0;
}

static int contact(void *context, short *result)
{
    assert(context == &player);
    ++contact_queries;
    *result = touching;
    return 0;
}

static int support(void *context, short *result)
{
    assert(context == &player);
    *result = supported;
    return 0;
}

static int sound(void *context, unsigned short value)
{
    assert(context == &player);
    ++sounds;
    sample = value;
    return 0;
}

static int probe(void *context, short x, short y, short *hit)
{
    assert(context == &player);
    (void)x; (void)y;
    *hit = 0;
    return 0;
}

static int ground(void *context, short *kind, short *delta)
{
    assert(context == &player);
    *kind = *delta = 0;
    return 0;
}

static int edge(void *context, short *hit, short *kind, short *x, short *y)
{
    assert(context == &player);
    ++edge_queries;
    *hit = edge_hit; *kind = edge_kind; *x = 173; *y = 103;
    return 0;
}

static int edge_transition(void *context, const ENGINE_PLAYER_CALL *call,
    short kind, short x, short y)
{
    assert(context == &player);
    if (call->handler != 0xe775U && call->handler != 0xe8dfU) return -1;
    return engine_player_begin_ledge(&pool, object, &player, call->handler, kind, x, y);
}

static void setup(unsigned short form)
{
    engine_initialize_objects(&pool);
    render_initialize_nodes(&renders);
    memset(&player, 0, sizeof(player));
    player.player.body.owner = (RENDER_OWNER){160, 160};
    player.player.body.render_pool = &renders;
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner,
        0, 0, animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    object = engine_acquire_object(&pool, 0);
    assert(object && player.player.body.node);
    player.player.context = &player;
    player.player.collision_flags = &collision;
    player.player.form = form;
    player.player.probe = probe;
    player.support = support;
    player.sound = sound;
    player.ground = ground;
    player.edge = edge;
    player.damage_source = &source;
    player.contact = contact;
    player.ledge_height = ledge_height;
    player.transition = edge_transition;
    player.health = 10;
    player.roar_charge = 100;
    source = (RENDER_OWNER){144, 160};
    collision = 0;
    sounds = 0;
    supported = 1;
    touching = 0;
    contact_queries = 0;
    edge_hit = edge_kind = 0;
    edge_queries = 0;
}

static void tick(void)
{
    assert(engine_update_objects(&pool, &input) == 0);
}

int main(void)
{
    const unsigned short forms[] = {0, 1, 2};
    for (unsigned int f = 0; f < 3; ++f) {
        unsigned short form = forms[f];
        for (unsigned short left = 0; left < 2; ++left) {
            setup(form);
            ENGINE_PLAYER_CALL call = {0xec69, form ? 0x596eU : 0x61feU, left};
            assert(engine_player_begin_action(&pool, object, &player, &call) == 0);
            assert(player.player.age == 0 && player.player.body.animation.counter == left);
            unsigned int pulse = form ? 30 : 14, finish = form ? 94 : 55;
            for (unsigned int i = 0; i <= finish; ++i) {
                unsigned int script = player.player.body.animation.script.position;
                tick();
                if (i == pulse) {
                    assert(player.roar_pulse == 100 && player.roar_charge == 0 &&
                        script == player.player.body.animation.script.position);
                }
                if (i == pulse + 1) assert(player.roar_pulse == 0);
            }
            assert(sounds == 1 && sample == (form ? 3 : 2));
            assert(player.player.handler == (left ? 0xc2cdU : 0xc8d5U));

            setup(form);
            source.x = left ? 144 : 176;
            player.flags = player.player_flags = 0xffff;
            player.player.flags_high = 0xff;
            supported = 0;
            assert(engine_player_damage(&pool, object, &player) == 0);
            assert(player.flags == 0x5ff7 && player.player_flags == 0xfffd &&
                player.player.flags_high == 0xd4 && player.player.immunity == 100 &&
                player.health == 9 && !player.roar_charge && sounds == 1);
            assert(player.player.handler == (left ? 0xf017U : 0xf160U));
            assert(player.player.body.animation.counter == (form ? 40 : 18));
            assert(player.player.body.motion.velocity_y == UINT32_C(0xfffd0000));
            assert(player.player.body.motion.velocity_x == (left ? 0x10000U : 0xffff0000U));
            player.player.body.animation.counter = 12;
            tick();
            assert(player.player.body.motion.velocity_x ==
                ((left ? form != 0 : (form & 1) != 0) ? 0U :
                    left ? 0x10000U : 0xffff0000U));
            assert(player.player.body.motion.velocity_y == UINT32_C(0xfffd4e00));
            player.player.body.animation.counter = 0;
            supported = 1;
            player.player_flags &= 0xffdeU;
            player.player.body.animation.state = 0;
            tick();
            assert(player.player.handler == (left ? 0xc2cdU : 0xc8d5U));
            assert(!(player.player.flags_high & 4));
        }
        setup(form);
        player.player_flags = 0x20;
        assert(engine_player_damage(&pool, object, &player) == 0);
        assert(player.player.handler == 0xee60U && player.player.immunity == 0 &&
            player.player.body.animation.state == 0 && player.health == 9);
        tick();
        player.player.body.animation.state = 1;
        tick();
        assert(player.player.handler == 0xc8d5U);

        setup(form);
        ENGINE_PLAYER_CALL call = {0xee35, 0, 0};
        assert(engine_player_begin_action(&pool, object, &player, &call) == 0);
        tick();
        assert(player.player.handler == 0xee35U);

        setup(form);
        player.contact_kind = 6;
        assert(engine_player_begin_terrain(&pool, object, &player, 0xf80d, 1,
            UINT32_C(0xfffd0000)) == 0);
        tick();
        assert(player.player.body.owner.x == 157 && (player.player.flags_high & 8));
        player.contact_kind = 0;
        tick();
        assert(player.player.handler == 0xae53U &&
            player.player.body.animation.counter == 10 && !(player.player.flags_high & 8));

        setup(form);
        player.contact_kind = 5;
        assert(engine_player_begin_terrain(&pool, object, &player, 0xfe3c, 1,
            UINT32_C(0xfffc0000)) == 0);
        tick();
        assert(player.player.body.owner.x == 156 && player.player.handler == 0xfe3cU);
        supported = 0;
        tick();
        assert(player.player.handler == 0xff83U && player.player.body.animation.state == 1);
        supported = 1; player.contact_kind = 7; player.pressed = 12;
        player.player.body.motion.velocity_y = 0;
        tick();
        assert(player.player.handler == 0xfe3cU && player.player.body.animation.state == 1 &&
            player.player.body.motion.velocity_x == UINT32_C(0xfffc0000));
    }
    setup(0);
    for (unsigned int left = 0; left < 2; ++left) {
        setup(0);
        player.player.body.node->pass_flags = left ? 8 : 0;
        player.player.flags_high = 0x20;
        player.pressed = left ? 4 : 8;
        assert(engine_player_rebound(&pool, object, &player, 0xf5f1) == 0);
        assert(sounds == 1 && sample == 0 &&
            player.player.handler == (left ? 0xae53U : 0xaa97U));
        assert(!(player.player.flags_high & 0x20));
        assert(player.player.body.motion.velocity_y ==
            (left ? UINT32_C(0xfffc4e00) : UINT32_C(0xfffbce00)));

        setup(0);
        player.player.body.node->pass_flags = left ? 8 : 0;
        ENGINE_PLAYER_CALL launch = {0xf2b1, 0, 0};
        assert(engine_player_begin_action(&pool, object, &player, &launch) == 0);
        assert(player.player.body.motion.velocity_x ==
            (left ? UINT32_C(0x18000) : UINT32_C(0xfffe8000)));
        assert(player.player.body.animation.counter == 35);
        tick();
        assert(player.player.body.animation.counter == 34);
        player.boundary_controls = left ? 8 : 4;
        tick();
        assert(!player.player.body.motion.velocity_x);
        player.player.body.animation.counter = 0;
        tick();
        assert(player.player.handler == (left ? 0xc2cdU : 0xc8d5U));

        setup(0);
        player.player.body.node->pass_flags = left ? 8 : 0;
        ENGINE_PLAYER_CALL tether = {0xf6cc, 0, 0};
        player.tether_target = (RENDER_OWNER){180, 140};
        player.flags |= 4;
        assert(engine_player_begin_action(&pool, object, &player, &tether) == 0);
        assert(player.player.body.owner.x == 160 && player.player.body.owner.y == 160);
        for (unsigned int i = 0; i < 5; ++i) tick();
        assert(player.player.body.owner.x == 176 && player.player.body.owner.y == 144);
        player.flags &= 0xfffbU;
        player.pressed = left ? 4 : 8;
        player.player.body.motion.velocity_y = 0;
        supported = 0;
        /* Tether release resumes the existing stream, not the operand's script. */
        assert(animation_program_initialize(&player.player.body.animation, animation_movement_data,
            ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x6116,
            animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) == 0);
        tick();
        assert(player.player.handler == (left ? 0xae53U : 0xaa97U));
    }
    setup(1);
    player.contact_source = &source;
    touching = 1;
    ENGINE_PLAYER_CALL hold = {0xf3fb, 0, 0};
    assert(engine_player_begin_action(&pool, object, &player, &hold) == 0);
    assert(player.player.handler == 0xf3fbU && player.player.body.animation.state == 1);
    player.player_flags |= 1;
    tick();
    assert(player.player.handler == 0xf2b1U && !(player.player_flags & 1));
    setup(1);
    player.contact_source = &source;
    assert(engine_player_begin_action(&pool, object, &player, &hold) == 0);
    assert(contact_queries == 2 && player.player.handler == 0xc8d5U);
    for (unsigned int form = 0; form < 2; ++form) {
        for (unsigned int right = 0; right < 2; ++right) {
            setup((unsigned short)form);
            unsigned int selector = right ? 0xe8dfU : 0xe775U;
            assert(engine_player_begin_ledge(&pool, object, &player, selector, 0xea, 173, 103) == 0);
            assert(player.player.handler == (right ? 0xd7a3U : 0xd5f4U));
            assert(player.player.body.owner.x == (right ? 160 : 175) &&
                player.player.body.owner.y == 112 && ledge_x == player.player.body.owner.x &&
                ledge_y == 103 && player.player.body.animation.counter == 42 &&
                player.player_flags == 0x80);
            player.pressed = 1;
            for (unsigned int i = 0; i < 42; ++i) tick();
            assert(player.player.body.animation.counter == 0 &&
                player.player.handler == (right ? 0xd7a3U : 0xd5f4U));
            tick();
            assert(player.player.handler == (right ? 0xd4ffU : 0xd40aU) &&
                player.player.body.animation.counter == (form ? 39 : 31));
            player.pressed = 0;
            for (unsigned int i = 0; i < (form ? 39U : 31U); ++i) tick();
            tick();
            assert(player.player.handler == (right ? 0xc8d5U : 0xc2cdU) &&
                player.player.body.owner.x == (right ? 160 + (form ? 19 : 9) :
                    175 - (form ? 19 : 9)) &&
                player.player.body.owner.y == (form ? 115 : 111));

            for (unsigned int forced = 0; forced < 2; ++forced) {
                setup((unsigned short)form);
                assert(engine_player_begin_ledge(&pool, object, &player, selector,
                    0xea, 173, 103) == 0);
                if (forced) player.player_flags |= 0x40;
                else player.pressed = 2;
                supported = 0;
                tick();
                assert(player.player.handler == (right && !forced ? 0xaa97U : 0xae53U));
                assert((player.player_flags & 0x80) == (!right && !forced ? 0x80 : 0));
                assert(player.player.body.owner.x == (right ? 148 : 187));
            }
        }
    }
    setup(0);
    player.flags = 0x800;
    ENGINE_PLAYER_CALL perch = {0x10075, 0, 0};
    assert(engine_player_begin_action(&pool, object, &player, &perch) == 0);
    player.pressed = 4;
    tick();
    assert(player.player.body.animation.counter == 6 && !(player.player.body.node->pass_flags & 8));
    player.pressed = 0;
    for (unsigned int i = 0; i < 6; ++i) tick();
    assert(player.player.body.node->pass_flags & 8);
    player.pressed = 0x20;
    tick();
    assert(player.player.handler == 0xb7e7U && !(player.flags & 0x800) &&
        player.player.body.animation.counter == 4);
    setup(1);
    player.flags = 0x800;
    assert(engine_player_begin_action(&pool, object, &player, &perch) == 0);
    player.pressed = 0x20;
    tick();
    assert(player.player.handler == 0xb604U && player.player.body.animation.counter == 10 &&
        player.jump_air_script == 0x612cU);
    setup(0);
    player.flags = 0x800;
    assert(engine_player_begin_action(&pool, object, &player, &perch) == 0);
    player.flags = 0; supported = 0;
    tick();
    assert(player.player.handler == 0xaa97U);
    setup(0);
    assert(engine_player_begin_ledge(&pool, object, &player, 0xe775, 0xea, 160, 96) == 0);
    player.player.body.animation.counter = 0xffff;
    player.pressed = 1;
    tick();
    assert(player.player.handler == 0xd5f4U && player.player.body.animation.counter == 0xffff);
    for (unsigned int form = 0; form < 2; ++form) {
        for (unsigned int right = 0; right < 2; ++right) {
            setup((unsigned short)form);
            unsigned int grip = right ? 0xdb06U : 0xd985U;
            unsigned int leap = right ? 0xdeafU : 0xdc42U;
            assert(engine_player_begin_wall(&pool, object, &player, grip, 173, 167) == 0);
            assert(player.player.handler == grip && player.player.body.animation.counter == 20 &&
                player.player.body.owner.x == (right ? 175 : 160) &&
                player.player.body.owner.y == 160 && (player.flags & 8));
            player.pressed = 0x20;
            for (unsigned int i = 0; i < 20; ++i) tick();
            assert(player.player.handler == grip && player.player.body.animation.counter == 0);
            tick();
            assert(player.player.handler == leap && player.player.body.animation.counter == 16 &&
                player.player.body.animation.state == 8 && !(player.flags & 8) &&
                (player.flags & 0x8000) && player.player.body.motion.velocity_y == UINT32_C(0xfff98000) &&
                player.player.body.owner.x == (right ? 220 : 115) &&
                player.player.body.owner.y == (form ? 121 : 142) &&
                (player.player.body.node->pass_flags & 8) == (right ? 8 : 0));
            player.pressed = 0;
            for (unsigned int i = 0; i < 8; ++i) tick();
            assert(player.player.body.animation.state == 0 && player.player.body.animation.counter == 16 &&
                !edge_queries && player.player.body.owner.y == (form ? 121 : 142));
            tick();
            assert(player.player.body.animation.state == 0xffff &&
                player.player.body.animation.counter == 15 &&
                player.player.body.motion.velocity_y == UINT32_C(0xfff9ce00) && edge_queries == 1);
            for (unsigned int i = 0; i < 8; ++i) tick();
            player.pressed = 12;
            tick();
            assert(player.player.body.motion.velocity_x == UINT32_C(0xfffd8000));
            edge_hit = -1; edge_kind = right ? 0xe8 : 0xf8;
            tick();
            assert(player.player.handler == (right ? 0xd985U : 0xdb06U) &&
                player.player.body.animation.counter == 20 && !(player.flags & 0x8000) &&
                (player.flags & 8));

            setup((unsigned short)form);
            ENGINE_PLAYER_CALL call = {leap, 0, 0};
            assert(engine_player_begin_action(&pool, object, &player, &call) == 0);
            player.player.body.animation.state = 0xffff;
            edge_hit = -1; edge_kind = right ? 0xf8 : 0xe8;
            tick();
            assert(player.player.handler == leap && player.player.body.animation.counter == 15);
            edge_kind = 0xea;
            tick();
            assert(player.player.handler == (right ? 0xd7a3U : 0xd5f4U) &&
                !(player.flags & 0x8000));

            for (unsigned int variant = 0; variant < 2; ++variant) {
                setup((unsigned short)form);
                player.level_variant = variant ? 8 : 0;
                assert(engine_player_begin_action(&pool, object, &player, &call) == 0);
                player.player.body.animation.state = 0xffff;
                player.player.body.animation.counter = 0;
                player.player.body.motion.velocity_y = 0;
                short x = player.player.body.owner.x, y = player.player.body.owner.y;
                supported = 0;
                tick();
                assert(player.player.handler == (right ? 0xaa97U : 0xae53U) &&
                    !(player.flags & 0x8000) &&
                    player.player.body.owner.x == x + (right ? -13 : 13) - (variant ? 16 : 0) &&
                    player.player.body.owner.y == y + 54);
            }
            setup((unsigned short)form);
            assert(engine_player_begin_wall(&pool, object, &player, grip, 173, 167) == 0);
            player.player.body.animation.counter = 0;
            player.pressed = 2; supported = 0;
            tick();
            assert(player.player.handler == (right ? 0xaa97U : 0xae53U) && !(player.flags & 8));
        }
    }
    setup(0);
    assert(engine_player_begin_wall(&pool, object, &player, 0xd985, 160, 160) == 0);
    player.player.body.animation.counter = 0;
    player.level_id = 5; source = (RENDER_OWNER){0x390, 0x5b0}; player.contact_source = &source;
    player.pressed = 0x20; supported = 0;
    tick();
    assert(player.pressed == 2 && player.player.handler == 0xae53U);
    for (unsigned int right = 0; right < 2; ++right) {
        setup(0);
        ENGINE_PLAYER_CALL leap = {right ? 0xdeafU : 0xdc42U, 0, 0};
        assert(engine_player_begin_action(&pool, object, &player, &leap) == 0);
        player.player.body.animation.state = 0xffff;
        player.player.body.animation.counter = 8;
        player.boundary_controls = right ? 8 : 4;
        player.pressed = 12;
        tick();
        assert(!player.player.body.motion.velocity_x && player.player.body.animation.counter == 7);
        tick();
        assert(player.player.body.motion.velocity_x == UINT32_C(0xfffd8000));
        setup(0);
        assert(engine_player_begin_action(&pool, object, &player, &leap) == 0);
        player.player.flags_high |= 4;
        tick();
        assert(sounds == 1 && player.health == 9 && player.player.immunity == 100 &&
            player.player.body.animation.state == 7 &&
            (player.player.handler == 0xf017U || player.player.handler == 0xf160U));
    }
    setup(0);
    ENGINE_PLAYER_CALL leap = {0xdc42, 0, 0};
    assert(engine_player_begin_action(&pool, object, &player, &leap) == 0);
    player.player.body.animation.state = 0xffff;
    player.edge = 0;
    assert(engine_update_objects(&pool, &input) == -1);
    setup(0);
    assert(engine_player_begin_ledge(&pool, object, &player, 0xe775, 0xf8, 160, 96) == -1);
    player.ledge_height = 0;
    assert(engine_player_begin_ledge(&pool, object, &player, 0xe775, 0xea, 160, 96) == -1);
    setup(0);
    assert(engine_player_begin_ledge(&pool, object, &player, 0xe775, 0xaf, 160, 96) == -1);
    player.damage_source = 0;
    assert(engine_player_damage(&pool, object, &player) == -1 && !sounds);
    player.sound = 0;
    ENGINE_PLAYER_CALL call = {0xec69, 0x61fe, 0};
    assert(engine_player_begin_action(&pool, object, &player, &call) == -1);
    puts("PASS: original roar pulse/timing/direction, damage masks/health, both recoil paths, "
        "adult form-bit asymmetry, stun, slides, contact rebound, thrown launch, "
        "tether/release, ledge grabs/climbs/drops, supported turn/jump, wall grips, "
        "delayed leaps, steering, opposite catches, ledge transfers and detach");
    return 0;
}
