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
    *hit = *kind = *x = *y = 0;
    return 0;
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
    player.health = 10;
    player.roar_charge = 100;
    source = (RENDER_OWNER){144, 160};
    collision = 0;
    sounds = 0;
    supported = 1;
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
    player.damage_source = 0;
    assert(engine_player_damage(&pool, object, &player) == -1 && !sounds);
    player.sound = 0;
    ENGINE_PLAYER_CALL call = {0xec69, 0x61fe, 0};
    assert(engine_player_begin_action(&pool, object, &player, &call) == -1);
    puts("PASS: original roar pulse/timing/direction, damage masks/health, both recoil paths, "
        "adult form-bit asymmetry, stun, passive animation, slides and airborne slope return");
    return 0;
}
