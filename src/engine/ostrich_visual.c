#include "ostrich_visual.h"
#include "animation_data.h"

static int program(ANIMATION_PROGRAM *animation, unsigned int entry)
{
    return animation_program_initialize(animation, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE, entry, animation_enemy_data,
        ANIMATION_ENEMY_SIZE, ANIMATION_ENEMY_BASE);
}

static short signed_word(unsigned int value)
{
    value &= 0xffffU;
    return (short)(value < 0x8000U ? (int)value : (int)value - 0x10000);
}

int engine_ostrich_visual_create(ENGINE_OSTRICH_VISUAL *visual,
    ENGINE_OBJECT_POOL *objects, RENDER_POOL *renders, RENDER_OWNER position,
    short order)
{
    if (!visual || !objects || !renders || visual->body || visual->head ||
        visual->body_object || visual->head_object) return -1;
    *visual = (ENGINE_OSTRICH_VISUAL){0};
    visual->objects = objects;
    visual->renders = renders;
    visual->position = position;
    if (program(&visual->body_animation, 0x145d6) != 0) return -1;
    visual->body = render_acquire_node(renders, &visual->position, 0, order,
        animation_enemy_data + 0xc994 - ANIMATION_ENEMY_BASE, 20);
    if (!visual->body) return -1;
    visual->body->flags |= 0x40;
    visual->body_object = engine_acquire_object(objects, 0);
    if (!visual->body_object) {
        if (render_release_node(renders, visual->body) != 0) return -1;
        visual->body = 0;
        return -1;
    }
    return 0;
}

int engine_ostrich_visual_set_pose(ENGINE_OSTRICH_VISUAL *visual,
    ENGINE_OSTRICH_POSE pose)
{
    if (!visual || !visual->body || !visual->body_object ||
        pose < ENGINE_OSTRICH_WAITING || pose > ENGINE_OSTRICH_JUMPING) return -1;
    if (pose == visual->pose) return 0;
    if (pose == ENGINE_OSTRICH_WAITING) return -1;
    ANIMATION_PROGRAM body_animation, head_animation;
    unsigned int body_entry = pose == ENGINE_OSTRICH_MOUNTING ? 0x145d6 :
        pose == ENGINE_OSTRICH_JUMPING ? 0x1463d : 0x145e4;
    unsigned int head_entry = pose == ENGINE_OSTRICH_MOUNTING ? 0x14525 :
        pose == ENGINE_OSTRICH_CROUCHING ? 0x14517 :
        pose == ENGINE_OSTRICH_JUMPING ? 0x14533 :
        visual->pose == ENGINE_OSTRICH_CROUCHING ? 0x144fb : 0x14509;
    if (program(&body_animation, body_entry) != 0 ||
        program(&head_animation, head_entry) != 0) return -1;
    if (!visual->head) {
        visual->head = render_acquire_node(visual->renders, &visual->position, 0,
            signed_word((unsigned short)visual->body->order - 100U),
            animation_enemy_data + 0xc994 - ANIMATION_ENEMY_BASE, 20);
        if (!visual->head) return -1;
        visual->head->flags |= 0x40;
        visual->head_object = engine_acquire_object(visual->objects, 0);
        if (!visual->head_object) {
            if (render_release_node(visual->renders, visual->head) != 0) return -1;
            visual->head = 0;
            return -1;
        }
    }
    if (!((visual->pose == ENGINE_OSTRICH_WAITING && pose == ENGINE_OSTRICH_MOUNTING) ||
        (visual->pose == ENGINE_OSTRICH_RUNNING && pose == ENGINE_OSTRICH_CROUCHING) ||
        (visual->pose == ENGINE_OSTRICH_CROUCHING && pose == ENGINE_OSTRICH_RUNNING)))
        visual->body_animation = body_animation;
    visual->head_animation = head_animation;
    visual->pose = pose;
    return 0;
}

int engine_ostrich_visual_tick(ENGINE_OSTRICH_VISUAL *visual)
{
    if (!visual || !visual->body || !visual->body_object) return -1;
    if (animation_program_step(&visual->body_animation, visual->body,
        &visual->position, 0, 0) != 0) return -1;
    if (visual->head && animation_program_step(&visual->head_animation,
        visual->head, &visual->position, 0, 0) != 0) return -1;
    return 0;
}

int engine_ostrich_visual_attachment(const ENGINE_OSTRICH_VISUAL *visual,
    RENDER_OWNER *attachment)
{
    if (!visual || !attachment || !visual->body || !visual->body->active ||
        !visual->body->parts || visual->body->parts_size < 14) return -1;
    unsigned int x = visual->body->parts[10] | (unsigned int)visual->body->parts[11] << 8;
    unsigned int y = visual->body->parts[12] | (unsigned int)visual->body->parts[13] << 8;
    if (visual->body->pass_flags & 8) x = 0U - x;
    if (visual->body->pass_flags & 0x10) y = 0U - y;
    *attachment = (RENDER_OWNER){
        signed_word((unsigned short)visual->position.x + x),
        signed_word((unsigned short)visual->position.y + y)
    };
    return 0;
}

int engine_ostrich_visual_release(ENGINE_OSTRICH_VISUAL *visual)
{
    if (!visual || !visual->renders || !visual->objects) return -1;
    if (visual->head) {
        if (render_release_node(visual->renders, visual->head) != 0) return -1;
        visual->head = 0;
    }
    if (visual->head_object) {
        if (engine_release_object(visual->objects, visual->head_object) != 0) return -1;
        visual->head_object = 0;
    }
    if (visual->body) {
        if (render_release_node(visual->renders, visual->body) != 0) return -1;
        visual->body = 0;
    }
    if (visual->body_object) {
        if (engine_release_object(visual->objects, visual->body_object) != 0) return -1;
        visual->body_object = 0;
    }
    return 0;
}
