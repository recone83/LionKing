#ifndef LIONKING_TIMING_H
#define LIONKING_TIMING_H

typedef struct {
    unsigned long long last_ns;
    unsigned long long pit_remainder;
    unsigned int logic_remainder;
} ENGINE_CLOCK;

void engine_clock_reset(ENGINE_CLOCK *clock, unsigned long long now_ns);
int engine_dispatch_ticks(ENGINE_CLOCK *clock, unsigned long long now_ns,
    void (*update)(void *), void *context);

#endif
