# Timing and object pool

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

The existing [timing module](../../src/engine/timing.c) now derives IRQ-equivalent ticks
from DOS64 monotonic nanoseconds using the nominal PIT ratio `1193182 / 11830`.
It preserves the original byte counter wrap and
`updates = (ticks * 5 + remainder) / 10`, retaining the remainder modulo 10.
Reset clears both clock phases, suitable for the original pause/reset behavior.
Backward time and arithmetic overflow return an error, reported by the caller.
The viewer dispatches after presentation, as in the original gameplay path,
but the callback only counts updates: object simulation is not wired yet.
The PIT frequency is the nominal model, not a measured guarantee of the original hardware.

```bash
cc -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -Iinclude -Isrc \
    tmp/tools/check_timing.c src/engine/timing.c -o build/check_timing
build/check_timing
```

The existing [object module](../../src/engine/objects.c) now implements the pool
confirmed at `0x18350`, `0x183b5` and `0x183ee`: 96 entries, append-to-tail
acquisition and push-to-front recycling. Each object retains 116 bytes of game
data; list pointers and behavior pointers are native, so the old 128-byte binary
stride is deliberately not used in memory. Pool exhaustion still returns null.
Invalid releases return failure; future gameplay callers must report that error.
The native dispatcher now follows `0x14f50`: increments the 16-bit update
counter, reads controls, calls behavior entries, tracks the current-object
pointer and recycles an object when its callback clears that pointer. It
continues with the saved next object after removal. Real gameplay behaviors
remain unported; tests use callbacks only in the host harness.
The viewer does not yet use this pool; this step does not change its image.

```bash
cc -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -Iinclude -Isrc \
    tmp/tools/check_objects.c src/engine/objects.c src/engine/input.c -o build/check_objects
build/check_objects
```
