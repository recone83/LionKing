/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "timing.h"

void engine_clock_reset(ENGINE_CLOCK *clock, unsigned long long now_ns)
{
    clock->last_ns = now_ns;
    clock->pit_remainder = 0;
    clock->logic_remainder = 0;
}

int engine_clock_elapsed_ticks(ENGINE_CLOCK *clock, unsigned long long now_ns,
    unsigned long long *ticks)
{
    const unsigned long long denominator = 11830ULL * 1000000000ULL;
    if (!clock || !ticks || now_ns < clock->last_ns ||
        clock->pit_remainder >= denominator) {
        return -1;
    }
    unsigned long long elapsed = now_ns - clock->last_ns;
    if (elapsed > (~0ULL - clock->pit_remainder) / 1193182ULL) {
        return -1;
    }
    unsigned long long phase = elapsed * 1193182ULL + clock->pit_remainder;
    *ticks = phase / denominator;
    clock->last_ns = now_ns;
    clock->pit_remainder = phase % denominator;
    return 0;
}

int engine_dispatch_ticks(ENGINE_CLOCK *clock, unsigned long long now_ns,
    void (*update)(void *), void *context)
{
    if (!clock || !update || clock->logic_remainder >= 10) {
        return -1;
    }
    unsigned long long elapsed_ticks;
    if (engine_clock_elapsed_ticks(clock, now_ns, &elapsed_ticks) != 0) {
        return -1;
    }
    /* Only gameplay dispatch uses the original byte IRQ accumulator. */
    unsigned int ticks = (unsigned int)(elapsed_ticks & 255);
    unsigned int total = ticks * 5 + clock->logic_remainder;
    clock->logic_remainder = total % 10;
    unsigned int updates = total / 10;
    for (unsigned int i = 0; i < updates; ++i) {
        update(context);
    }
    return (int)updates;
}
#else
#include "timing_legacy.inc"
#endif
