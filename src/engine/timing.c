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

/* Backup line 3716; original FUN_00004520; code address 0x14520. */




// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void __regparm3 engine_dispatch_ticks(undefined4 param_1,code *param_2)

{
  char cVar1;
  ushort uVar2;
  
  uVar2 = _DAT_0000541d + 0x15e;
  _DAT_0000541d = CONCAT11(DAT_0000541d_1,(char)(uVar2 % 10));
  for (cVar1 = (char)(uVar2 / 10); cVar1 != '\0'; cVar1 = cVar1 + -1) {
    (*param_2)();
  }
  return;
}
#endif
