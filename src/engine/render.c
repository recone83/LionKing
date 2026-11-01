#ifdef LK_DOS64_NATIVE
#include "render.h"

void render_initialize_nodes(RENDER_POOL *pool)
{
    pool->head = 0;
    pool->free_head = pool->nodes;
    for (unsigned int i = 0; i < RENDER_NODE_COUNT; ++i) {
        RENDER_NODE *node = &pool->nodes[i];
        *node = (RENDER_NODE){0};
        node->prev = i ? &pool->nodes[i - 1] : 0;
        node->next = i + 1 < RENDER_NODE_COUNT ? &pool->nodes[i + 1] : 0;
    }
}

void render_disable_animation(RENDER_NODE *node)
{
    node->flags &= 0xdf;
}

void render_set_animation_period(RENDER_NODE *node, unsigned char period)
{
    if (period) {
        node->period = period;
    }
    if (node->period) {
        node->flags |= 0x20;
    }
}

RENDER_NODE *render_acquire_node(RENDER_POOL *pool, const RENDER_OWNER *owner,
    unsigned int control, short order, const unsigned char *parts,
    unsigned int parts_size)
{
    if (!pool || !owner || !parts || !pool->free_head) {
        return 0;
    }
    RENDER_NODE *node = pool->free_head;
    pool->free_head = node->next;
    if (pool->free_head) {
        pool->free_head->prev = 0;
    }
    node->owner = owner;
    node->remaining = (unsigned char)control;
    node->period = (unsigned char)(control >> 8);
    node->pass_flags = (unsigned char)(control >> 16);
    node->flags = (unsigned char)(control >> 24);
    node->order = order;
    node->parts = parts;
    node->parts_size = parts_size;
    node->active = 1;
    if (node->period) {
        render_set_animation_period(node, node->period);
    } else {
        render_disable_animation(node);
    }
    RENDER_NODE *next = pool->head;
    RENDER_NODE *prev = 0;
    while (next && order >= next->order) {
        prev = next;
        next = next->next;
    }
    node->prev = prev;
    node->next = next;
    if (prev) {
        prev->next = node;
    } else {
        pool->head = node;
    }
    if (next) {
        next->prev = node;
    }
    return node;
}

int render_release_node(RENDER_POOL *pool, RENDER_NODE *node)
{
    if (!pool || !node) {
        return -1;
    }
    unsigned int i;
    for (i = 0; i < RENDER_NODE_COUNT && node != &pool->nodes[i]; ++i) {
    }
    if (i == RENDER_NODE_COUNT || !node->active) {
        return -1;
    }
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        pool->head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    node->prev = 0;
    node->next = pool->free_head;
    if (pool->free_head) {
        pool->free_head->prev = node;
    }
    pool->free_head = node;
    node->owner = 0;
    node->active = 0;
    return 0;
}

static int render_scene_layers(RENDER_SCENE *scene)
{
    if (!scene || !scene->prepare_viewport || !scene->stage_one ||
        !scene->object_pass_draw || !scene->stage_two || !scene->present) {
        return -1;
    }
    if (scene->prepare_viewport(scene) != 0 || scene->stage_one(scene) != 0) {
        return -1;
    }
    scene->object_pass = 0;
    if (scene->object_pass_draw(scene) != 0 || scene->stage_two(scene) != 0) {
        return -1;
    }
    scene->object_pass = 0x80;
    if (scene->object_pass_draw(scene) != 0) {
        return -1;
    }
    return 0;
}

int render_basic_scene(RENDER_SCENE *scene)
{
    if (render_scene_layers(scene) != 0) {
        return -1;
    }
    return scene->present(scene);
}

int render_game_scene(RENDER_SCENE *scene)
{
    if (!scene || (scene->level < 11 &&
        (!scene->overlay_first || !scene->overlay_last ||
         (scene->level != 4 && !scene->overlay_second)))) {
        return -1;
    }
    if (render_scene_layers(scene) != 0) {
        return -1;
    }
    if (scene->level < 11) {
        if (scene->overlay_first(scene) != 0 ||
            (scene->level != 4 && scene->overlay_second(scene) != 0) ||
            scene->overlay_last(scene) != 0) {
            return -1;
        }
    }
    return scene->present(scene);
}
#else
#include "render_legacy.inc"
#endif
