#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "libs/vga.h"

static unsigned char buffer[320 * 207];
static unsigned char copied[64000];
static DOS64_COLOR colors[256];
static unsigned int calls;
static int failure;

static int present(void *context, const unsigned char *pixels, const DOS64_COLOR *palette)
{
    assert(context == &calls && palette == colors);
    ++calls;
    memcpy(copied, pixels, sizeof(copied));
    return failure;
}

int main(void)
{
    for (unsigned int i = 0; i < sizeof(buffer); ++i) {
        buffer[i] = (unsigned char)(i * 17 + i / 320);
    }
    VGA_FRAME frame = {buffer, sizeof(buffer), 0, colors, present, &calls};
    for (unsigned int camera = 0; camera <= 65535; ++camera) {
        frame.camera_y = (unsigned short)camera;
        assert(vga_present_frame(&frame) == 0 && frame.camera_y == 0);
        assert(memcmp(copied, buffer + ((camera + 1) & 7) * 320, 64000) == 0);
    }
    assert(calls == 65536);
    frame.camera_y = 6;
    frame.size = sizeof(buffer) - 1;
    assert(vga_present_frame(&frame) == -1 && calls == 65536 && frame.camera_y == 6);
    frame.size = sizeof(buffer);
    failure = 1;
    assert(vga_present_frame(&frame) == -1 && calls == 65537 && frame.camera_y == 6);
    assert(vga_present_frame(0) == -1);
    frame.present = 0;
    assert(vga_present_frame(&frame) == -1 && calls == 65537);
    puts("PASS: all 65536 camera words, exact 64000-byte source, reset, bounds and sink failure");
    return 0;
}
