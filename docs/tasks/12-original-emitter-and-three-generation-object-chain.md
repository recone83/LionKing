# Original emitter and three-generation object chain

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Original emitter and three-generation object chain

`render_near_view` ports `0x2805c`, testing strict bounds around the original
320x200 camera rectangle with signed margins. Unlike descriptor collision,
these comparisons use expanded 32-bit bounds, without 16-bit wrapping.

`engine_emitter_behavior` ports `0x2865d`. Its first call only marks the
continuation initialized and returns. Subsequent calls retain the old 16-bit
counter before decrementing it when the original activation flag is nonzero.
The activated path checks camera proximity with margins 128/128 and removes
the emitter outside that expanded rectangle. Old counter low-seven-bit values
20/40 spawn the verified timed parent at X-8/X+8, before Y is snapped to a
multiple of four with bit-one-dependent offset 2. Negative old counters apply
gravity; script execution follows even when activation is off. The two
original script variants are extracted unchanged from the data dump.

`engine_spawn_emitter` ports constructors `0x28773` and `0x28797` as variants
0 and 1. It reads original definition DS `0x162e2`, checks behavior and
initializer `0x1865d`, and uses initial descriptor `0xe4a0`. After the immediate
initializer returns, it sets original script DS `0x166f6` or `0x1670f` and the
supplied counter. It intentionally does not render/advance the first script
frame during construction.

Callers supply live activation and camera pointers, a visibility window,
render orders and exclusive `ENGINE_EMITTER_SLOT` storage. Each slot contains
one timed parent and its falling child. It can be reused only after both are
removed from the object pool. Missing or exhausted storage is an explicit
error, never a skipped emission. The real object dispatcher updates spawned
parents and children later in the same traversal, preserving the existing
immediate-initializer effects.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_near_view.c src/engine/render.c src/engine/sprites.c -o build/check_near_view
build/check_near_view
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_emitter.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_emitter
build/check_emitter
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_spawn_emitter.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_spawn_emitter
build/check_spawn_emitter
```

Tests verify 9175040 camera proximity cases, a 160-update emitter timeline
with four emissions, and both constructors through an actual three-generation
chain, including activation, gravity, culling and exhaustion. The full level
setup and activation source remain unported; the diagnostic entry still shows
idle, with no invented spawning key.
