#include <assert.h>
#include <stdio.h>
#include "engine/render.h"

static RENDER_POOL pool;
static const unsigned char parts[14] = {0};
static const RENDER_OWNER owner = {12, 8};

static void check_links(unsigned int active, unsigned int free_count)
{
    RENDER_NODE *prev = 0;
    unsigned int count = 0;
    for (RENDER_NODE *node = pool.head; node; node = node->next) {
        assert(node->active && node->owner == &owner && node->prev == prev);
        if (prev) {
            assert(prev->order <= node->order);
        }
        prev = node;
        assert(++count <= RENDER_NODE_COUNT);
    }
    assert(count == active);
    prev = 0;
    count = 0;
    for (RENDER_NODE *node = pool.free_head; node; node = node->next) {
        assert(!node->active && node->prev == prev);
        prev = node;
        assert(++count <= RENDER_NODE_COUNT);
    }
    assert(count == free_count);
}

int main(void)
{
    render_initialize_nodes(&pool);
    check_links(0, 80);
    RENDER_NODE *a = render_acquire_node(&pool, &owner, 0xff800207U, 0, parts, sizeof(parts));
    RENDER_NODE *b = render_acquire_node(&pool, &owner, 0x20000000U, -32768, parts, sizeof(parts));
    RENDER_NODE *c = render_acquire_node(&pool, &owner, 0, 0, parts, sizeof(parts));
    RENDER_NODE *d = render_acquire_node(&pool, &owner, 0, 32767, parts, sizeof(parts));
    assert(a && b && c && d);
    assert(pool.head == b && b->next == a && a->next == c && c->next == d);
    assert(a->remaining == 7 && a->period == 2 && a->pass_flags == 0x80 && a->flags == 0xff);
    assert(b->flags == 0 && b->period == 0);
    render_disable_animation(a);
    assert(a->flags == 0xdf);
    render_set_animation_period(a, 0);
    assert(a->flags == 0xff && a->period == 2 && a->remaining == 7);
    render_set_animation_period(a, 255);
    assert(a->period == 255 && a->remaining == 7);
    check_links(4, 76);
    assert(render_release_node(&pool, a) == 0);
    check_links(3, 77);
    assert(render_acquire_node(&pool, &owner, 0, 1, parts, sizeof(parts)) == a);
    assert(a->flags == 0 && a->remaining == 0 && a->period == 0);
    while (pool.free_head) {
        assert(render_acquire_node(&pool, &owner, 0, 0, parts, sizeof(parts)));
    }
    check_links(80, 0);
    assert(!render_acquire_node(&pool, &owner, 0, 0, parts, sizeof(parts)));
    assert(render_release_node(&pool, b) == 0);
    assert(render_release_node(&pool, d) == 0);
    check_links(78, 2);
    assert(render_release_node(&pool, d) == -1);
    RENDER_NODE foreign = {0};
    assert(render_release_node(&pool, &foreign) == -1);
    assert(render_release_node(0, c) == -1);
    check_links(78, 2);
    render_initialize_nodes(&pool);
    check_links(0, 80);
    puts("PASS: 80 render nodes, stable signed ordering, recycling, flags and animation period");
    return 0;
}
