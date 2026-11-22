#ifdef LK_DOS64_NATIVE
#include "ostrich_obstacle.h"
#include "animation_data.h"

static int hazard_program(ANIMATION_PROGRAM *program, unsigned int entry)
{
    return animation_program_initialize(program, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE, entry, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE);
}

int engine_ostrich_hazard_create(ENGINE_OSTRICH_HAZARD *hazard,
    ENGINE_OBJECT_POOL *objects, RENDER_POOL *renders,
    const ENGINE_OSTRICH_OBSTACLE *descriptor)
{
    if (!hazard || !objects || !renders || !descriptor || hazard->collision ||
        hazard->decoration || hazard->object) return -1;
    unsigned int decoration;
    if (descriptor->constructor == 0x20826 && descriptor->definition == 0xc214)
        decoration = 0xc200;
    else if (descriptor->constructor == 0x208cd && descriptor->definition == 0xc23c)
        decoration = 0xc228;
    else if (descriptor->constructor == 0x20977 && descriptor->definition == 0xcd54)
        decoration = 0;
    else return -1;
    *hazard = (ENGINE_OSTRICH_HAZARD){0};
    hazard->objects = objects;
    hazard->renders = renders;
    hazard->position = (RENDER_OWNER){descriptor->x, descriptor->y};
    hazard->constructor = descriptor->constructor;
    hazard->armed = (unsigned char)(!decoration);
    if (!decoration && hazard_program(&hazard->animation, 0x19bf8) != 0) return -1;
    hazard->collision = render_acquire_node(renders, &hazard->position, 0, 1,
        animation_enemy_data + descriptor->definition - ANIMATION_ENEMY_BASE, 20);
    if (!hazard->collision) return -1;
    hazard->collision->flags |= 0x40;
    hazard->object = engine_acquire_object(objects, 0);
    if (!hazard->object) {
        if (engine_ostrich_hazard_release(hazard) != 0) return -1;
        return -1;
    }
    if (decoration) {
        hazard->decoration = render_acquire_node(renders, &hazard->position, 0, 0,
            animation_enemy_data + decoration - ANIMATION_ENEMY_BASE, 20);
        if (!hazard->decoration) {
            if (engine_ostrich_hazard_release(hazard) != 0) return -1;
            return -1;
        }
        hazard->decoration->flags |= 0x40;
        hazard->decoration->pass_flags |= 0x20;
    }
    return 0;
}

int engine_ostrich_hazard_tick(ENGINE_OSTRICH_HAZARD *hazard,
    const RENDER_BOUNDS *activation_bounds, const RENDER_NODE *player,
    const RENDER_NODE *bird)
{
    if (!hazard || !hazard->object || !hazard->collision || !activation_bounds ||
        !player || !player->active || !player->owner ||
        !bird || !bird->active || !bird->owner ||
        activation_bounds->left > activation_bounds->right ||
        activation_bounds->top > activation_bounds->bottom) return -1;
    if (hazard->constructor == 0x20977) {
        if (animation_program_step(&hazard->animation, hazard->collision,
            &hazard->position, 0, 0) != 0) return -1;
        if (hazard->armed && (int)player->owner->x - hazard->position.x > -64) {
            if (hazard_program(&hazard->animation, 0x19c0e) != 0) return -1;
            hazard->armed = 0;
        }
    }
    if (hazard->constructor != 0x20977 || hazard->position.x < player->owner->x) {
        if (hazard->position.x < activation_bounds->left ||
            hazard->position.x > activation_bounds->right ||
            hazard->position.y < activation_bounds->top ||
            hazard->position.y > activation_bounds->bottom) {
            if (engine_ostrich_hazard_release(hazard) != 0) return -1;
            return ENGINE_OSTRICH_HAZARD_CULLED;
        }
        if (hazard->constructor == 0x20977) return ENGINE_OSTRICH_HAZARD_CLEAR;
    }
    short hit;
    if (render_objects_hit(hazard->collision, player, &hit) != 0) return -1;
    if (hit) return ENGINE_OSTRICH_HAZARD_PLAYER_HIT;
    if (render_objects_hit(hazard->collision, bird, &hit) != 0) return -1;
    return hit ? ENGINE_OSTRICH_HAZARD_BIRD_HIT : ENGINE_OSTRICH_HAZARD_CLEAR;
}

int engine_ostrich_hazard_release(ENGINE_OSTRICH_HAZARD *hazard)
{
    if (!hazard || !hazard->renders || !hazard->objects) return -1;
    if (hazard->decoration) {
        if (render_release_node(hazard->renders, hazard->decoration) != 0) return -1;
        hazard->decoration = 0;
    }
    if (hazard->collision) {
        if (render_release_node(hazard->renders, hazard->collision) != 0) return -1;
        hazard->collision = 0;
    }
    if (hazard->object) {
        if (engine_release_object(hazard->objects, hazard->object) != 0) return -1;
        hazard->object = 0;
    }
    return 0;
}
#endif
