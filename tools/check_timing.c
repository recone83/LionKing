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
    const unsigned int frame_steps[] = {100000, 4000000, 10000000, 33000000};
    for (unsigned int rate = 0; rate < sizeof(frame_steps) / sizeof(*frame_steps); ++rate) {
        ENGINE_CLOCK varied;
        unsigned int updates = 0;
        engine_clock_reset(&varied, 0);
        unsigned long long now = 0;
        while (now < 10000000000ULL) {
            now += frame_steps[rate];
            if (now > 10000000000ULL) now = 10000000000ULL;
            assert(engine_dispatch_ticks(&varied, now, update, &updates) >= 0);
            assert(engine_dispatch_ticks(&varied, now, update, &updates) == 0);
        }
        assert(updates == 504);
    }
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
    engine_clock_reset(&clock, 0);
    clock.logic_remainder = 5;
    unsigned long long irq = 0, total_irq = 0;
    for (unsigned int ms = 1; ms <= 10000; ++ms) {
        assert(engine_clock_elapsed_ticks(&clock, ms * 1000000ULL, &irq) == 0);
        total_irq += irq;
    }
    assert(total_irq == ticks && clock.logic_remainder == 5);
    engine_clock_reset(&clock, 0);
    assert(engine_clock_elapsed_ticks(&clock, 3000000000ULL, &irq) == 0 && irq == 302);
    ENGINE_CLOCK before = clock;
    irq = 999;
    assert(engine_clock_elapsed_ticks(&clock, 0, &irq) == -1);
    assert(irq == 999 && clock.last_ns == before.last_ns &&
        clock.pit_remainder == before.pit_remainder);
    assert(engine_clock_elapsed_ticks(&clock, ~0ULL, &irq) == -1 && irq == 999);
    assert(engine_clock_elapsed_ticks(&clock, 3000000000ULL, 0) == -1);
    clock.pit_remainder = 11830ULL * 1000000000ULL;
    assert(engine_clock_elapsed_ticks(&clock, 3000000000ULL, &irq) == -1 && irq == 999);
    puts("PASS: exact PIT ratio, logic remainder, byte overflow, reset and clock errors");
    puts("PASS: full IRQ tick sampling independent of gameplay byte wrap and update remainder");
    return 0;
}
