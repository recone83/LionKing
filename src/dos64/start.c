#include "platform.h"

static unsigned char pixels[LK_WIDTH * LK_HEIGHT];
static DOS64_COLOR palette[256];

static int selftest_requested(const char *arguments)
{
    const char *expected = "--selftest";
    while (*arguments == ' ') {
        ++arguments;
    }
    while (*expected && *arguments == *expected) {
        ++arguments;
        ++expected;
    }
    return !*expected && (!*arguments || *arguments == ' ');
}

int __attribute__((ms_abi)) start(const DOS64_API *api)
{
    if (lk_platform_init(api) != 0) {
        return 1;
    }
    if (!api->Arguments) {
        lk_platform_log("Lion King: missing runtime argument string.\n");
        return 1;
    }
    for (unsigned int i = 0; i < 256; ++i) {
        palette[i] = DOS64_COLOR_ARGB(255, i, i, i);
    }
    for (unsigned int y = 0; y < LK_HEIGHT; ++y) {
        for (unsigned int x = 0; x < LK_WIDTH; ++x) {
            pixels[y * LK_WIDTH + x] = (unsigned char)(x * 256 / LK_WIDTH);
        }
    }
    lk_platform_log("Lion King DOS64 platform test; not gameplay. Escape exits.\n");
    int selftest = selftest_requested(api->Arguments);
    unsigned long long begin = lk_platform_time_ns();
    for (;;) {
        lk_platform_poll();
        if (lk_platform_exit_requested()) {
            break;
        }
        lk_platform_present(pixels, palette);
        if (selftest && lk_platform_time_ns() - begin >= 1000000000ULL) {
            break;
        }
        lk_platform_sleep(10);
    }
    lk_platform_log("Lion King DOS64 platform test finished.\n");
    return 0;
}
