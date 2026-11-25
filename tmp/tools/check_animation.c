#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/animation.h"

static unsigned int events;
static int event(void *context, unsigned int target)
{
    assert(context == &events && target == 0x12345678);
    ++events;
    return 0;
}

int main(void)
{
    unsigned char data[128] = {
        0xff, 0xff, 0xff, 0xfe, 0xfd, 7, 0xfc, 0xfd, 0xfb, 4,
        0xfa, 0x78, 0x56, 0x34, 0x12,
        2, 0x50, 0x10, 0, 0, 0xff, 0, 0, 0x10, 0, 0
    };
    data[80] = 1;
    RENDER_POOL pool;
    RENDER_OWNER owner = {32767, 32766};
    render_initialize_nodes(&pool);
    RENDER_NODE *node = render_acquire_node(&pool, &owner, 0, 0, data + 80, 20);
    ANIMATION_STREAM stream;
    assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0x1000) == 0);
    assert(animation_step(&stream, node, &owner, event, &events) == 1);
    assert(events == 1 && stream.state == 7 && stream.remaining == 2);
    assert(node->pass_flags == 0x18 && owner.x == -32766 && owner.y == -32766);
    assert(node->parts == data + 80 && node->parts_size == 20);
    assert(animation_step(&stream, node, &owner, event, &events) == 0);
    assert(animation_step(&stream, node, &owner, event, &events) == 0);
    assert(animation_step(&stream, node, &owner, event, &events) == 1);
    assert(events == 2 && node->pass_flags == 0 && owner.x == 32767 && owner.y == -32762);
    for (unsigned int duration = 0; duration < 128; ++duration) {
        data[0] = (unsigned char)duration;
        data[1] = 0x50; data[2] = 0x10; data[3] = data[4] = 0;
        data[5] = 0xff; data[6] = 0; data[7] = 0; data[8] = 0x10;
        data[9] = data[10] = 0;
        assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0x1000) == 0);
        assert(animation_step(&stream, node, &owner, 0, 0) == 1);
        for (unsigned int i = 0; i < duration; ++i) {
            assert(animation_step(&stream, node, &owner, 0, 0) == 0);
        }
        assert(animation_step(&stream, node, &owner, 0, 0) == 1);
    }
    data[0] = 0xfa;
    assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0x1000) == 0);
    assert(animation_step(&stream, node, &owner, 0, 0) == -1);
    memset(data, 0, sizeof(data));
    data[0] = 0xff; data[3] = 0x10;
    assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0x1000) == 0);
    assert(animation_step(&stream, node, &owner, 0, 0) == -1);
    data[0] = 0; data[1] = 0xff;
    assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0x1000) == 0);
    assert(animation_step(&stream, node, &owner, 0, 0) == -1);
    assert(animation_initialize(&stream, data, sizeof(data), ~0U, ~0U) == -1);
    assert(animation_initialize(&stream, data, sizeof(data), 0x1000, 0xfff) == -1);
    puts("PASS: 128 original duration counts, flips, state, signed movement wrap, events, jumps and bounds");
    return 0;
}
