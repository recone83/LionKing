#ifdef LK_DOS64_NATIVE
#include "lifecycle.h"
#include "animation_data.h"

int engine_level_life_initialize(ENGINE_LEVEL_LIFE *life, ENGINE_PLAYER_AIR *player,
    ENGINE_OBJECT *object, unsigned char lives)
{
    if (!life || !player || !object || !object->active || !lives ||
        !player->player.body.node || !player->player.body.node->active) return -1;
    *life = (ENGINE_LEVEL_LIFE){0};
    life->player = player;
    life->object = object;
    life->lives = lives;
    return 0;
}

int engine_level_life_fall(ENGINE_LEVEL_LIFE *life, const ENGINE_PLAYER_CALL *call)
{
    if (!life || !life->player || !life->object || !call || life->dying ||
        life->falling || life->game_over || life->complete || call->handler != 0xc884 ||
        call->script != 0x5e35 || call->counter != 100) return -1;
    ENGINE_FALLING_OBJECT *body = &life->player->player.body;
    if (animation_program_initialize(&body->animation, animation_movement_data,
        ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, call->script,
        animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) != 0)
        return -1;
    if (animation_program_step(&body->animation, body->node, &body->owner, 0, 0) != 0)
        return -1;
    life->remaining = call->counter - 1;
    life->falling = 1;
    life->player->player.handler = call->handler;
    life->object->behavior = 0;
    return 0;
}

int engine_level_life_complete(ENGINE_LEVEL_LIFE *life, unsigned int defeated)
{
    if (!life || !life->player || !life->object || !life->object->active) return -1;
    if (!defeated || life->dying || life->falling || life->game_over ||
        life->player->health <= 0) return 0;
    life->complete = 1;
    life->object->behavior = 0;
    return 0;
}

int engine_level_life_tick(ENGINE_LEVEL_LIFE *life, RENDER_OWNER camera)
{
    if (!life || !life->player || !life->object || !life->object->active ||
        !life->player->player.body.node || !life->player->player.body.node->active)
        return -1;
    if (life->game_over) return ENGINE_LIFE_GAME_OVER;
    if (life->complete) return ENGINE_LIFE_COMPLETE;
    ENGINE_PLAYER_AIR *player = life->player;
    ENGINE_FALLING_OBJECT *body = &player->player.body;
    if (life->falling) {
        if (!life->remaining) {
            life->falling = 0;
            player->health = 0;
        } else {
            --life->remaining;
            if (animation_program_step(&body->animation, body->node, &body->owner, 0, 0) != 0)
                return -1;
        }
        return ENGINE_LIFE_DYING;
    }
    if (!life->dying) {
        if (player->health > 0) return ENGINE_LIFE_PLAYING;
        if (!life->lives || player->player.form) return -1;
        --life->lives;
        ++life->deaths;
        life->remaining = 221; /* 0x5011 starts at 220 and finishes when negative. */
        life->dying = 1;
        life->object->behavior = 0;
        player->player.immunity = 0;
        player->player.flags_high = 0;
        player->damage_source = player->contact_source = 0;
        body->node->flags &= 0x3f;
        render_disable_animation(body->node);
        body->node->pass_flags &= 0xe7;
        body->owner.x = (short)(body->owner.x - camera.x);
        body->owner.y = (short)(body->owner.y - camera.y);
        if (animation_program_initialize(&body->animation, animation_movement_data,
            ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE, 0x5ff2,
            animation_movement_data, ANIMATION_MOVEMENT_SIZE, ANIMATION_MOVEMENT_BASE) != 0)
            return -1;
        return ENGINE_LIFE_DYING;
    }
    if (body->owner.x != 160) body->owner.x += body->owner.x < 160 ? 1 : -1;
    if (body->owner.y != 128) body->owner.y += body->owner.y < 128 ? 1 : -1;
    if (animation_program_step(&body->animation, body->node, &body->owner, 0, 0) != 0)
        return -1;
    if (--life->remaining) return ENGINE_LIFE_DYING;
    life->dying = 0;
    if (!life->lives) {
        life->game_over = 1;
        return ENGINE_LIFE_GAME_OVER;
    }
    ++life->restarts;
    return ENGINE_LIFE_RESTART;
}
#endif
