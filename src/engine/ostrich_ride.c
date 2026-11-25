#include "ostrich_ride.h"
#include "animation_data.h"

static short word(unsigned int value)
{
    value &= 0xffffU;
    return (short)(value < 0x8000U ? (int)value : (int)value - 0x10000);
}

static int hint_release(ENGINE_OSTRICH_RIDE *ride, ENGINE_OSTRICH_HINT *hint)
{
    if (hint->node && render_release_node(ride->sequence.renders, hint->node) != 0)
        return -1;
    hint->node = 0;
    if (hint->object && engine_release_object(ride->sequence.objects, hint->object) != 0)
        return -1;
    hint->object = 0;
    return 0;
}

static int hint_create(ENGINE_OSTRICH_RIDE *ride, ENGINE_OSTRICH_HINT *hint,
    short x, short y, unsigned short timer, int hidden)
{
    hint->position = (RENDER_OWNER){x, y};
    hint->timer = timer;
    if (animation_program_initialize(&hint->animation, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE, 0x14455,
        animation_enemy_data, ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE) != 0)
        return -1;
    hint->node = render_acquire_node(ride->sequence.renders, &hint->position, 0, 100,
        animation_enemy_data + 0xc1d8 - ANIMATION_ENEMY_BASE, 20);
    if (!hint->node) return -1;
    if (hidden) hint->node->flags |= 0x80;
    hint->object = engine_acquire_object(ride->sequence.objects, 0);
    if (!hint->object) {
        if (hint_release(ride, hint) != 0) return -1;
        return -1;
    }
    return 0;
}

static int hint_tick(ENGINE_OSTRICH_RIDE *ride, ENGINE_OSTRICH_HINT *hint, int primary)
{
    if (!hint->object) return 0;
    if (hint->timer) {
        --hint->timer;
        return animation_program_step(&hint->animation, hint->node, &hint->position, 0, 0);
    }
    if (!primary || hint->phase == 9) return hint_release(ride, hint);
    ++hint->phase;
    switch (hint->phase) {
    case 1: case 5: case 7:
        hint->node->flags &= (unsigned char)~0x80U;
        hint->node->pass_flags &= (unsigned char)~0x10U;
        hint->timer = 60;
        if (hint->phase == 7 &&
            hint_create(ride, &ride->hints[1], 276, 100, 60, 0) != 0) return -1;
        break;
    case 3: case 9:
        hint->node->flags &= (unsigned char)~0x80U;
        hint->node->pass_flags |= 0x10;
        hint->timer = 60;
        break;
    case 2: case 8:
        hint->node->flags |= 0x80;
        hint->timer = 90;
        break;
    case 4:
        hint->node->flags |= 0x80;
        hint->timer = 60;
        break;
    case 6:
        hint->node->flags |= 0x80;
        hint->timer = 80;
        break;
    default: return -1;
    }
    return 0;
}

int engine_ostrich_ride_find_and_start(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_ENEMIES *enemies, RENDER_FOLLOW_CAMERA *camera)
{
    if (!ride || !enemies || !enemies->player || !camera) return -1;
    if (ride->active || ride->marker || enemies->level != 2) return 0;
    ENGINE_PLAYER_AIR *player = enemies->player;
    for (unsigned int i = 0; i < enemies->count; ++i) {
        ENGINE_LIZARD *marker = &enemies->lizards[i];
        if (marker->destroyed || (marker->marker_type != 52 && marker->marker_type != 53))
            continue;
        ENGINE_OSTRICH_VISUAL *visual = &enemies->ostriches[marker->ostrich_index];
        if (!visual->body) continue;
        int dx = (int)player->player.body.owner.x - visual->position.x;
        if (dx > 0 && player->player.body.owner.x > marker->marker.x) {
            visual->position.x = player->player.body.owner.x;
            dx = 0;
        }
        if (dx <= -12 || dx >= 12) continue;
        if (player->player.handler != 0xcdc2U &&
            player->player.handler != 0xb604U && player->player.handler != 0xaa97U)
            continue;
        if (engine_ostrich_sequence_initialize(&ride->sequence, enemies->objects,
            enemies->renders, marker->marker_type) != 0) return -1;
        if (render_ostrich_scroll_initialize(&ride->scroll, marker->marker.x,
            camera->position.x) != 0 ||
            engine_ostrich_visual_set_pose(visual, ENGINE_OSTRICH_MOUNTING) != 0) {
            if (engine_ostrich_sequence_release(&ride->sequence) != 0) return -1;
            return -1;
        }
        if (marker->marker_type == 52 &&
            hint_create(ride, &ride->hints[0], 268, 128, 286, 1) != 0) {
            if (engine_ostrich_sequence_release(&ride->sequence) != 0) return -1;
            if (engine_ostrich_visual_release(visual) != 0) return -1;
            return -1;
        }
        ride->marker = marker;
        ride->visual = visual;
        ride->active = 1;
        ride->mounting = 1;
        ride->motion = (ENGINE_MOTION){0};
        player->ostrich_active = &ride->active;
        player->ostrich_motion = &ride->motion;
        player->flags |= 0x1008;
        return 1;
    }
    return 0;
}

int engine_ostrich_ride_update(ENGINE_OSTRICH_RIDE *ride, ENGINE_ENEMIES *enemies)
{
    if (!ride || !enemies || !enemies->player || !enemies->map ||
        !ride->active || !ride->visual || !ride->marker) return -1;
    ENGINE_PLAYER_AIR *player = enemies->player;
    ENGINE_FALLING_OBJECT *body = &player->player.body;
    ENGINE_OSTRICH_VISUAL *visual = ride->visual;
    if (hint_tick(ride, &ride->hints[1], 0) != 0 ||
        hint_tick(ride, &ride->hints[0], 1) != 0) return -1;
    if (ride->mounting) {
        if (body->motion.velocity_y & UINT32_C(0x80000000))
            return engine_ostrich_visual_tick(visual);
        ride->mounting = 0;
        player->flags &= (unsigned short)~0x1000U;
        if (engine_ostrich_visual_set_pose(visual, ENGINE_OSTRICH_RUNNING) != 0)
            return -1;
    }
    if (ride->bird_hit) player->flags |= 1;
    if (player->flags & 0x4000U)
        visual->position.x = word((unsigned short)visual->position.x + 4U);
    else {
        RENDER_OWNER attachment;
        if (engine_ostrich_visual_attachment(visual, &attachment) != 0) return -1;
        int dy = (int)body->owner.y - attachment.y;
        if (!(body->motion.velocity_y & UINT32_C(0x80000000)) && dy > -16 && dy < 16) {
            body->motion.velocity_y = 0;
            body->owner.y = attachment.y;
            player->flags |= 0x40;
        }
        if (!(player->flags & 0x180U) && !ride->sequence.ending &&
            (player->player.controls & 0x20U)) {
            if (!player->ostrich_sound ||
                player->ostrich_sound(player->player.context, 1, 22) != 0) return -1;
            player->flags |= 0x80;
            ride->motion.velocity_y = UINT32_C(0xfff80000);
        }
        visual->position.x = body->owner.x;
    }
    int landed = 0;
    if (!(ride->motion.velocity_y & UINT32_C(0x80000000))) {
        ENGINE_MAP_GROUND ground;
        if (engine_map_ground_ostrich(enemies->map, visual->position.x, visual->position.y,
            ride->scroll.base_x, &ground) != 0)
            return -1;
        if (ground.supported) {
            visual->position.y = word((unsigned short)visual->position.y + ground.delta_y);
            ride->motion.velocity_y = 0;
            player->flags &= (unsigned short)~0x80U;
            landed = 1;
        }
    }
    if (!landed && engine_motion_gravity(&ride->motion, &visual->position) != 0) return -1;
    ENGINE_OSTRICH_POSE pose = player->flags & 0x80U ? ENGINE_OSTRICH_JUMPING :
        player->flags & 0x100U ? ENGINE_OSTRICH_CROUCHING : ENGINE_OSTRICH_RUNNING;
    if (engine_ostrich_visual_set_pose(visual, pose) != 0 ||
        engine_ostrich_visual_tick(visual) != 0) return -1;
    return 0;
}

int engine_ostrich_ride_camera(ENGINE_OSTRICH_RIDE *ride,
    ENGINE_ENEMIES *enemies, RENDER_FOLLOW_CAMERA *camera)
{
    if (!ride || !ride->active || !ride->visual || !enemies || !enemies->map ||
        !enemies->player || !camera) return -1;
    ENGINE_PLAYER_AIR *player = enemies->player;
    if (render_follow_ostrich_camera(camera, player->player.body.owner,
        (unsigned char)(player->player.body.node->pass_flags & 8),
        player->player.flags_high, enemies->map->width, enemies->map->height,
        ride->sequence.ending) != 0) return -1;
    short shift;
    if (render_ostrich_scroll_step(&ride->scroll, camera, &shift) != 0 ||
        engine_ostrich_sequence_shift(&ride->sequence, shift) != 0) return -1;
    if (shift) {
        player->player.body.owner.x = word((unsigned short)player->player.body.owner.x -
            (unsigned short)shift);
        ride->visual->position.x = word((unsigned short)ride->visual->position.x -
            (unsigned short)shift);
    }
    int x = camera->position.x & ~15;
    int y = camera->position.y & ~15;
    int left = x - 96, top = y - 96;
    int right = x + 400, bottom = y + 288;
    if (left < 0) left = 0;
    if (top < 16) top = 16;
    if (right >= (int)enemies->map->width * 8) right = enemies->map->width * 8 - 16;
    if (bottom >= (int)enemies->map->height * 8) bottom = enemies->map->height * 8 - 16;
    RENDER_BOUNDS bounds = {(short)(left - 15), (short)(top - 15),
        (short)(right + 15), (short)(bottom + 16)};
    ENGINE_OSTRICH_SEQUENCE_RESULT result;
    if (engine_ostrich_sequence_tick(&ride->sequence, (short)ride->scroll.distance,
        camera->position, &bounds, player->player.body.node, ride->visual->body, &result) != 0)
        return -1;
    if (result.player_hit) {
        ride->damage_source = *result.player_hit;
        player->damage_source = &ride->damage_source;
        player->player.flags_high |= 4;
    }
    if (result.bird_hit) ride->bird_hit = 1;
    if (result.route_status == ENGINE_OSTRICH_FINISHED) ride->active = 0;
    return 0;
}

int engine_ostrich_ride_release(ENGINE_OSTRICH_RIDE *ride, ENGINE_PLAYER_AIR *player)
{
    if (!ride || !player) return -1;
    for (unsigned int i = 0; i < 2; ++i)
        if (hint_release(ride, &ride->hints[i]) != 0) return -1;
    if (ride->sequence.objects && engine_ostrich_sequence_release(&ride->sequence) != 0)
        return -1;
    if (ride->visual && ride->visual->body &&
        engine_ostrich_visual_release(ride->visual) != 0) return -1;
    if (ride->marker) ride->marker->destroyed = 1;
    if (player->damage_source == &ride->damage_source) player->damage_source = 0;
    player->ostrich_active = 0;
    player->ostrich_motion = 0;
    player->flags &= (unsigned short)~0x1008U;
    *ride = (ENGINE_OSTRICH_RIDE){0};
    return 0;
}
