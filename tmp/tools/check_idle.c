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

static unsigned int u32(const unsigned char *p)
{
    return (unsigned int)p[0] | (unsigned int)p[1] << 8 |
        (unsigned int)p[2] << 16 | (unsigned int)p[3] << 24;
}

int main(void)
{
    unsigned char original[ANIMATION_IDLE_SIZE];
    FILE *file = fopen("bin/obj2_data.bin", "rb");
    assert(file && fseek(file, ANIMATION_IDLE_BASE, SEEK_SET) == 0);
    assert(fread(original, 1, sizeof(original), file) == sizeof(original));
    assert(fclose(file) == 0);
    assert(memcmp(original, animation_idle_data, sizeof(original)) == 0);
    RENDER_POOL pool;
    RENDER_OWNER owner = {140, 80};
    render_initialize_nodes(&pool);
    RENDER_NODE *node = render_acquire_node(&pool, &owner, 0, 0, original, sizeof(original));
    ANIMATION_STREAM stream;
    assert(animation_initialize(&stream, animation_idle_data, ANIMATION_IDLE_SIZE,
        ANIMATION_IDLE_BASE, ANIMATION_IDLE_START) == 0);
    unsigned int records = 0, ticks = 0, callbacks = 0;
    for (unsigned int cycle = 0; cycle < 2; ++cycle) {
        unsigned int position = ANIMATION_IDLE_START - ANIMATION_IDLE_BASE;
        while (position < ANIMATION_IDLE_LOOP - ANIMATION_IDLE_BASE) {
            unsigned int duration = original[position];
            if (duration == 0xfa) {
                ++callbacks;
                position += 5;
                continue;
            }
            assert(duration < 128);
            unsigned int descriptor = u32(original + position + 1);
            assert(animation_step(&stream, node, &owner, event, &events) == 1);
            assert(node->parts == animation_idle_data + descriptor - ANIMATION_IDLE_BASE);
            assert(node->parts_size == 20 && node->parts[0] == 1 && node->parts[1] == 0);
            assert(node->parts[19] >= 14 && node->parts[19] <= 16);
            assert(memcmp(node->parts, original + descriptor - ANIMATION_IDLE_BASE, 20) == 0);
            for (unsigned int i = 0; i < duration; ++i) {
                assert(animation_step(&stream, node, &owner, event, &events) == 0);
            }
            ticks += duration + 1;
            ++records;
            position += 5;
        }
    }
    assert(records == 614 && events == callbacks && events == 12);
    assert(owner.x == 140 && owner.y == 80);
    printf("PASS: exact original idle bytes, 2 script loops, %u descriptors, "
        "%u timed updates and %u explicit callback events\n", records, ticks, events);
    return 0;
}
