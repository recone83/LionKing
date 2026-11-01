/* Extracted pseudocode; not yet compilable. */

#ifdef LK_DOS64_NATIVE
#include "timing.h"

void engine_clock_reset(ENGINE_CLOCK *clock, unsigned long long now_ns)
{
    clock->last_ns = now_ns;
    clock->pit_remainder = 0;
    clock->logic_remainder = 0;
}

int engine_dispatch_ticks(ENGINE_CLOCK *clock, unsigned long long now_ns,
    void (*update)(void *), void *context)
{
    const unsigned long long denominator = 11830ULL * 1000000000ULL;
    if (!clock || !update || now_ns < clock->last_ns ||
        clock->pit_remainder >= denominator || clock->logic_remainder >= 10) {
        return -1;
    }
    unsigned long long elapsed = now_ns - clock->last_ns;
    if (elapsed > (~0ULL - clock->pit_remainder) / 1193182ULL) {
        return -1;
    }
    unsigned long long phase = elapsed * 1193182ULL + clock->pit_remainder;
    /* Preserve the original byte IRQ accumulator, including overflow. */
    unsigned int ticks = (unsigned int)((phase / denominator) & 255);
    unsigned int total = ticks * 5 + clock->logic_remainder;
    clock->last_ns = now_ns;
    clock->pit_remainder = phase % denominator;
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
