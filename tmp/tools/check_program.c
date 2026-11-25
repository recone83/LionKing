#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "engine/animation.h"
#include "engine/animation_data.h"

static unsigned int events;
static int event(void *context, unsigned int target)
{
    assert(context == &events);
    assert(target == 0x20bec || target == 0x20c70 ||
        target == 0x20d55 || target == 0x20cf4);
    ++events;
    return 0;
}

int main(void)
{
    unsigned char original[ANIMATION_IDLE_SCRIPT_SIZE];
    FILE *dump = fopen("bin/obj2_data.bin", "rb");
    assert(dump && fseek(dump, ANIMATION_IDLE_SCRIPT_BASE, SEEK_SET) == 0);
    assert(fread(original, 1, sizeof(original), dump) == sizeof(original));
    assert(fclose(dump) == 0);
    assert(memcmp(original, animation_idle_script, sizeof(original)) == 0);
    RENDER_POOL pool;
    RENDER_OWNER owner = {140, 80};
    render_initialize_nodes(&pool);
    RENDER_NODE *node = render_acquire_node(&pool, &owner, 0, 0,
        animation_idle_data, ANIMATION_IDLE_SIZE);
    RENDER_NODE reference = *node;
    ANIMATION_STREAM stream;
    ANIMATION_PROGRAM program;
    assert(animation_initialize(&stream, animation_idle_data, ANIMATION_IDLE_SIZE,
        ANIMATION_IDLE_BASE, ANIMATION_IDLE_START) == 0);
    assert(animation_program_initialize(&program, animation_idle_script,
        ANIMATION_IDLE_SCRIPT_SIZE, ANIMATION_IDLE_SCRIPT_BASE, ANIMATION_IDLE_SCRIPT_BASE,
        animation_idle_data, ANIMATION_IDLE_SIZE, ANIMATION_IDLE_BASE) == 0);
    for (unsigned int tick = 0; tick < 4071; ++tick) {
        assert(animation_program_step(&program, node, &owner, event, &events) == 0);
        /* Two separate event counts let the direct substream be a behavioral reference. */
        assert(animation_step(&stream, &reference, &owner, event, &events) >= 0);
        assert(node->parts == reference.parts && node->parts_size == reference.parts_size);
        assert(program.visual.remaining == stream.remaining &&
            program.visual.position == stream.position);
        assert(program.script.position == ANIMATION_IDLE_SCRIPT_BASE + 16);
    }
    assert(events == 24 && program.visual_ready && !program.motion_ready);
    assert(owner.x == 140 && owner.y == 80);
    unsigned char combined[] = {
        0xfc, 0x62, 0, 0, 0, 0x20, 0, 0,
        0xbc, 0x63, 0, 0, 0x10, 0x20, 0, 0,
        0x0b, 0x63, 0, 0, 0xce, 0x63, 0, 0,
        0xdf, 0x62, 0, 0, 0xd4, 0x64, 0, 0, 0xf0, 0xff
    };
    unsigned char data[64] = {1, 0x20, 0x20, 0, 0, 0xff, 0, 0, 0x20, 0, 0};
    data[16] = 1; data[17] = 2; data[18] = data[19] = 0xff;
    data[20] = 0xff; data[21] = 0; data[22] = 0x10; data[23] = 0x20;
    assert(animation_program_initialize(&program, combined, sizeof(combined),
        0x1000, 0x1000, data, sizeof(data), 0x2000) == 0);
    for (unsigned int tick = 1; tick <= 10; ++tick) {
        assert(animation_program_step(&program, node, &owner, 0, 0) == 0);
        assert(owner.x == 140 + (int)tick * 2 && owner.y == 80 - (int)tick);
        assert(program.visual_ready && program.motion_ready &&
            program.script.position == 0x101c && node->parts == data + 32);
    }
    unsigned char invalid[] = {0xef, 0xbe, 0xad, 0xde};
    assert(animation_program_initialize(&program, invalid, sizeof(invalid), 0x1000, 0x1000,
        animation_idle_data, ANIMATION_IDLE_SIZE, ANIMATION_IDLE_BASE) == 0);
    assert(animation_program_step(&program, node, &owner, event, &events) == -1);
    assert(program.unsupported_handler == 0xdeadbeef);
    unsigned char uninitialized[] = {0x0b, 0x63, 0, 0};
    assert(animation_program_initialize(&program, uninitialized, sizeof(uninitialized),
        0x1000, 0x1000, animation_idle_data, ANIMATION_IDLE_SIZE, ANIMATION_IDLE_BASE) == 0);
    assert(animation_program_step(&program, node, &owner, event, &events) == -1);
    unsigned char cycle[] = {0xd4, 0x64, 0, 0, 0xfc, 0xff};
    assert(animation_program_initialize(&program, cycle, sizeof(cycle), 0x1000, 0x1000,
        animation_idle_data, ANIMATION_IDLE_SIZE, ANIMATION_IDLE_BASE) == 0);
    assert(animation_program_step(&program, node, &owner, event, &events) == -1);
    cycle[4] = 0xff; cycle[5] = 0x7f;
    assert(animation_program_initialize(&program, cycle, sizeof(cycle), 0x1000, 0x1000,
        animation_idle_data, ANIMATION_IDLE_SIZE, ANIMATION_IDLE_BASE) == 0);
    assert(animation_program_step(&program, node, &owner, event, &events) == -1);
    puts("PASS: original outer idle script, 4071 updates, yield/resume, relative loop, "
        "matching descriptors/events and explicit unsupported/cycle errors");
    return 0;
}
