#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/behaviors.h"
#include "engine/animation_data.h"

static ENGINE_OBJECT_POOL objects;
static RENDER_POOL renders;
static ENGINE_PLAYER_AIR player;
static ENGINE_OBJECT *object;
static ENGINE_MOTION bird;
static DOS64_INPUT input;
static unsigned char collision;
static int active;
static short supported;
static unsigned int sounds;
static int sound_failure;

static int support(void *context, short *result)
{
    assert(context == &player);
    *result = supported;
    return 0;
}

static int sound(void *context, unsigned short channel, unsigned short sample)
{
    assert(context == &player && channel == 1 && sample == 22);
    ++sounds;
    return sound_failure ? -1 : 0;
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

static int probe(void *context, short x, short y, short *hit)
{
    assert(context == &player);
    (void)x; (void)y;
    *hit = 0;
    return 0;
}

static void setup(void)
{
    engine_initialize_objects(&objects);
    render_initialize_nodes(&renders);
    memset(&player, 0, sizeof(player));
    bird = (ENGINE_MOTION){0};
    active = 1; supported = 0; sounds = 0; collision = 0; sound_failure = 0;
    player.player.body.owner = (RENDER_OWNER){160, 200};
    player.player.body.render_pool = &renders;
    player.player.body.node = render_acquire_node(&renders, &player.player.body.owner,
        0, 0, animation_movement_data + 0x78b4 - ANIMATION_MOVEMENT_BASE, 20);
    object = engine_acquire_object(&objects, 0);
    assert(object && player.player.body.node);
    player.player.context = &player;
    player.health = 4;
    player.player.collision_flags = &collision;
    player.player.probe = probe;
    player.support = support;
    player.ground = ground;
    player.edge = edge;
    player.ostrich_active = &active;
    player.ostrich_motion = &bird;
    player.ostrich_sound = sound;
    player.flags = 0x140;
    player.player.body.node->pass_flags |= 8;
    assert(engine_player_begin_ostrich(&objects, object, &player) == 0);
    assert(player.player.handler == 0xf94d && player.flags == 0x40 &&
        collision == 0x20 && !(player.player.body.node->pass_flags & 8));
}

static void tick(void)
{
    assert(engine_update_objects(&objects, &input) == 0);
}

int main(void)
{
    setup();
    player.player.body.motion.velocity_x = UINT32_C(0xfffe0000);
    tick();
    assert(player.player.body.owner.x == 164 && player.player.body.motion.velocity_x == 0x40000);
    player.pressed = 2;
    tick();
    assert(player.flags & 0x100);
    player.pressed = 0;
    tick();
    assert(!(player.flags & 0x100));
    player.flags |= 0x80;
    player.pressed = 2;
    tick();
    assert(!(player.flags & 0x100));
    player.pressed = 0x20;
    player.player.controls = 0x20;
    bird.velocity_y = UINT32_C(0xfffa0000);
    tick();
    assert(player.player.handler == 0xf94d);
    bird.velocity_y = UINT32_C(0xfffa0001);
    player.player.controls = 0;
    tick();
    assert(player.player.handler == 0xf94d);
    player.player.controls = 0x20;
    tick();
    assert(player.player.handler == 0xfbc1 && !(player.flags & 0x40) &&
        player.player.body.motion.velocity_y == UINT32_C(0xfff84e00));
    player.flags |= 0x40;
    tick();
    assert(player.player.handler == 0xf94d);

    setup();
    for (unsigned int i = 0; i < 180; ++i) {
        player.pressed = i % 60 < 30 ? 2 : 0;
        tick();
    }
    assert(player.player.handler == 0xf94d);

    setup();
    player.player.form = 1;
    player.flags |= 0x80;
    player.pressed = 0x20;
    player.player.controls = 0x20;
    bird.velocity_y = 0;
    tick();
    assert(player.player.handler == 0xfbc1 &&
        player.player.body.motion.velocity_y == UINT32_C(0xfff84e00));
    player.pressed = 0;
    for (unsigned int i = 0; i < 80; ++i) tick();
    assert(player.player.handler == 0xfbc1 &&
        !(player.player.body.motion.velocity_y & UINT32_C(0x80000000)));
    active = 0;
    tick();
    assert(player.player.handler == 0xaa97 &&
        object->behavior == &engine_player_air_behavior);

    setup();
    player.player.body.motion.velocity_x = 0x50000;
    tick();
    assert(player.player.body.motion.velocity_x == 0x50000 &&
        player.player.body.owner.x == 165);
    player.player.flags_high = 4;
    active = 0;
    tick();
    assert(player.player.handler == 0xaa97 && !(player.player.flags_high & 4) && !sounds);

    setup();
    player.player.flags_high = 4;
    player.player.immunity = 1;
    tick();
    assert(player.player.handler == 0xf94d && !sounds);
    player.player.immunity = 0;
    tick();
    assert(player.player.handler == 0xfb2e && sounds == 1 &&
        player.player.body.motion.velocity_x == 0 &&
        player.player.body.motion.velocity_y == UINT32_C(0xffff0000) &&
        (player.flags & 0x4000) && !(player.flags & 0x1c0));
    supported = 1;
    tick();
    assert(active && player.health == 4);
    player.player.body.motion.velocity_y = 0;
    tick();
    assert(active && !player.health);

    setup();
    player.flags |= 1;
    tick();
    assert(player.player.handler == 0xfb2e &&
        player.player.body.motion.velocity_x == 0x30000 && sounds == 1);

    setup();
    player.flags |= 1;
    sound_failure = 1;
    assert(engine_update_objects(&objects, &input) == -1 && sounds == 1);

    setup();
    active = 0;
    tick();
    assert(player.player.handler == 0xaa97 &&
        object->behavior == &engine_player_air_behavior &&
        player.player.body.motion.velocity_x == 0x64000 &&
        !(player.flags & 0x1c0));
    setup();
    player.ostrich_motion = 0;
    assert(engine_player_begin_ostrich(&objects, object, &player) == -1);
    puts("PASS: ostrich rider state, duck, jump, hit and dismount");
    return 0;
}
