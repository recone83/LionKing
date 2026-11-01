#ifdef LK_DOS64_NATIVE
#include "render.h"
#include "sprites.h"

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

static unsigned int render_u16(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8;
}

static short bounds_word(unsigned int value)
{
    value &= 0xffff;
    return (short)(value < 0x8000 ? (int)value : (int)value - 65536);
}

int render_prepare_viewport(RENDER_OWNER *camera, unsigned short width_tiles,
    unsigned short height_tiles, unsigned short shake, RENDER_VIEWPORT *viewport)
{
    if (!camera || !viewport) {
        return -1;
    }
    short limit_x = bounds_word((unsigned int)width_tiles * 8U - 320U);
    short limit_y = bounds_word((unsigned int)height_tiles * 8U - 200U);
    short x = camera->x < 0 ? 0 : camera->x;
    short y = camera->y < 0 ? 0 : camera->y;
    camera->x = x > limit_x ? limit_x : x;
    camera->y = y > limit_y ? limit_y : y;
    viewport->x = (unsigned short)camera->x;
    viewport->y = (unsigned short)((unsigned int)(unsigned short)camera->y + shake);
    viewport->aligned_x = viewport->x & 0xfff8U;
    viewport->aligned_y = viewport->y & 0xfff8U;
    return 0;
}

int render_object_bounds(const RENDER_NODE *node, RENDER_BOUNDS *bounds)
{
    if (!node || !node->active || !node->owner || !node->parts ||
        node->parts_size < 14 || !bounds) {
        return -1;
    }
    unsigned int left = render_u16(node->parts + 2);
    unsigned int top = render_u16(node->parts + 4);
    unsigned int right = render_u16(node->parts + 6);
    unsigned int bottom = render_u16(node->parts + 8);
    if (node->pass_flags & 8) {
        unsigned int previous_left = left;
        left = 0U - right;
        right = 0U - previous_left;
    }
    if (node->pass_flags & 0x10) {
        unsigned int previous_top = top;
        top = 0U - bottom;
        bottom = 0U - previous_top;
    }
    *bounds = (RENDER_BOUNDS){
        bounds_word(left + (unsigned int)node->owner->x),
        bounds_word(top + (unsigned int)node->owner->y),
        bounds_word(right + (unsigned int)node->owner->x),
        bounds_word(bottom + (unsigned int)node->owner->y)
    };
    return 0;
}

int render_point_hit(const RENDER_NODE *node, short x, short y, short *hit)
{
    RENDER_BOUNDS bounds;
    if (!hit || render_object_bounds(node, &bounds) != 0) {
        return -1;
    }
    *hit = bounds.right >= x && bounds.bottom >= y &&
        bounds.left <= x && bounds.top <= y ? -1 : 0;
    return 0;
}

static short bounds_hit(const RENDER_BOUNDS *a, const RENDER_BOUNDS *b)
{
    return a->right >= b->left && a->bottom >= b->top &&
        a->left <= b->right && a->top <= b->bottom ? -1 : 0;
}

int render_near_view(const RENDER_OWNER *owner, const RENDER_OWNER *camera,
    short margin_x, short margin_y, short *near)
{
    if (!owner || !camera || !near) {
        return -1;
    }
    *near = (int)owner->x > (int)camera->x - margin_x &&
        (int)owner->x < (int)camera->x + 320 + margin_x &&
        (int)owner->y > (int)camera->y - margin_y &&
        (int)owner->y < (int)camera->y + 200 + margin_y ? -1 : 0;
    return 0;
}

short render_limit_camera_x(short x, short width_tiles)
{
    int limit = (int)width_tiles * 8 - 320;
    return x > limit ? bounds_word((unsigned int)limit) : x;
}

int render_objects_hit(const RENDER_NODE *current, const RENDER_NODE *other, short *hit)
{
    RENDER_BOUNDS a, b;
    if (!hit || render_object_bounds(current, &a) != 0 ||
        render_object_bounds(other, &b) != 0) {
        return -1;
    }
    *hit = bounds_hit(&a, &b);
    return 0;
}

int render_local_rectangle_hit(const RENDER_NODE *target, const RENDER_NODE *source,
    const RENDER_BOUNDS *local, short *hit)
{
    RENDER_BOUNDS target_bounds;
    if (!source || !source->active || !source->owner || !local || !hit ||
        render_object_bounds(target, &target_bounds) != 0) {
        return -1;
    }
    RENDER_BOUNDS source_bounds = *local;
    /* 0x1693d mirrors the supplied rectangle horizontally only. */
    if (source->pass_flags & 8) {
        source_bounds.left = bounds_word(0U - (unsigned int)local->right);
        source_bounds.right = bounds_word(0U - (unsigned int)local->left);
    }
    source_bounds.left = bounds_word((unsigned int)source_bounds.left + (unsigned int)source->owner->x);
    source_bounds.right = bounds_word((unsigned int)source_bounds.right + (unsigned int)source->owner->x);
    source_bounds.top = bounds_word((unsigned int)source_bounds.top + (unsigned int)source->owner->y);
    source_bounds.bottom = bounds_word((unsigned int)source_bounds.bottom + (unsigned int)source->owner->y);
    *hit = bounds_hit(&target_bounds, &source_bounds);
    return 0;
}

static int render_signed_word(int value)
{
    unsigned int word = (unsigned int)value & 0xffff;
    return word < 0x8000 ? (int)word : (int)word - 65536;
}

static int render_node_visible(RENDER_NODE *node, unsigned char pass)
{
    if ((node->pass_flags & 0x80) != pass || (node->flags & 0x80)) {
        return 0;
    }
    if (!(node->flags & 0x20)) {
        return 1;
    }
    if (!(node->flags & 0x10)) {
        if (node->remaining) {
            --node->remaining;
            return 1;
        }
        node->remaining = node->period;
        if (node->flags & 8) {
            node->flags |= 4;
        }
        return 0;
    }
    if (node->remaining) {
        --node->remaining;
        return 0;
    }
    node->remaining = node->period;
    if (node->flags & 8) {
        node->flags &= 0xef;
    }
    return 1;
}

int render_object_pass(RENDER_POOL *pool, unsigned char pass, short viewport_x,
    short viewport_y, const RENDER_SPRITE_BANK *banks, unsigned int bank_count,
    unsigned char *pixels)
{
    if (!pool || !banks || bank_count > 256 || !pixels || (pass != 0 && pass != 0x80)) {
        return -1;
    }
    for (RENDER_NODE *node = pool->head; node; node = node->next) {
        if (!render_node_visible(node, pass)) {
            continue;
        }
        if (!node->owner || !node->parts || node->parts_size < 14) {
            return -1;
        }
        unsigned int count = render_u16(node->parts);
        if (count > (node->parts_size - 14) / 6) {
            return -1;
        }
        int x = node->owner->x;
        int y = node->owner->y;
        if (node->flags & 0x40) {
            x = render_signed_word(x + viewport_x);
            y = render_signed_word(y + viewport_y);
        }
        for (unsigned int i = 0; i < count; ++i) {
            const unsigned char *part = node->parts + 14 + i * 6;
            unsigned int bank = part[5], frame = part[4];
            if (bank >= bank_count || !banks[bank].data || banks[bank].size < 2) {
                return -1;
            }
            const unsigned char *asset = banks[bank].data;
            unsigned int frames = render_u16(asset);
            if (frame >= frames || 2ULL + frames * 8ULL > banks[bank].size) {
                return -1;
            }
            const unsigned char *entry = asset + 2 + frame * 8;
            int px = x - (int)render_u16(part);
            int py = y - (int)render_u16(part + 2);
            if (node->pass_flags & 8) {
                frame |= 0x8000;
                px = x - (int)render_u16(entry) + (int)render_u16(part);
            }
            if (node->pass_flags & 0x10) {
                frame |= 0x2000;
                py = y - (int)render_u16(entry + 2) + (int)render_u16(part + 2);
            }
            if (render_draw_sprite(asset, banks[bank].size, (unsigned short)frame,
                render_signed_word(px), render_signed_word(py), pixels) != 0) {
                return -1;
            }
        }
    }
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
