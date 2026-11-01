#include <assert.h>
#include <stdio.h>
#include "engine/timing.h"

static void update(void *context) { ++*(unsigned int *)context; }

int main(void)
{
    ENGINE_CLOCK clock;
    unsigned int count = 0;
    engine_clock_reset(&clock, 0);
    for (unsigned int ms = 1; ms <= 10000; ++ms) {
        assert(engine_dispatch_ticks(&clock, ms * 1000000ULL, update, &count) >= 0);
    }
    unsigned long long ticks = 10000000000ULL * 1193182ULL / (11830ULL * 1000000000ULL);
    assert(count == ticks / 2 && count == 504);
    assert(clock.logic_remainder == (ticks * 5) % 10);
    assert(engine_dispatch_ticks(&clock, 9999999999ULL, update, &count) == -1);
    assert(count == 504);
    engine_clock_reset(&clock, 10000000000ULL);
    assert(engine_dispatch_ticks(&clock, 10000000000ULL, update, &count) == 0);
    assert(clock.logic_remainder == 0 && clock.pit_remainder == 0);
    engine_clock_reset(&clock, 0);
    unsigned int batch = 0;
    assert(engine_dispatch_ticks(&clock, 3000000000ULL, update, &batch) == 23);
    /* 302 IRQ ticks wrap to 46; the original dispatcher then runs 23 updates. */
    assert(batch == 23);
    assert(engine_dispatch_ticks(&clock, ~0ULL, update, &batch) == -1);
    puts("PASS: exact PIT ratio, logic remainder, byte overflow, reset and clock errors");
    return 0;
}
