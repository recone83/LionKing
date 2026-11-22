# Original falling-object behavior and physics

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Original falling-object behavior and physics

The next native behavior is the original handler `0x288a1`, not a replacement
player controller. It initializes original DS script `0x16741`, clears the
spatial type, checks visibility, applies gravity and executes the script in
that exact order. The script uses descriptor DS `0xe4b4`, yields through the
original shared loop at `0x14272`, and repeats its frame every 100 updates.

Native callers acquire an object with `engine_falling_behavior`, set its
`context` to an `ENGINE_FALLING_OBJECT`, and supply its owner, active render
node, render pool and visibility window. State starts zero-initialized.
Pointers are native typed pointers, not original packed object addresses.
The original visibility flag 1 allows updates without a window; otherwise
missing visibility data is an error. Original fixed bounding boxes and flags
are preserved. Out-of-window objects release their render node before the
object dispatcher recycles them and clears a tracked-object reference.
An externally assigned nonzero spatial type requires an explicit unlink
callback; the level spatial index is not implemented by a no-op.

The shared physics helpers preserve 16.16 coordinates, signed velocity caps,
the original gravity increment and 32-bit overflow. Descriptor point collision
also preserves H/V flips, inclusive edges and signed 16-bit wrapping; it does
not yet implement terrain collision. Behavior errors propagate through
`engine_update_objects` and stop traversal rather than silently retaining an
apparently successful update.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_physics.c src/engine/physics.c -o build/check_physics
build/check_physics
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_bounds.c src/engine/render.c src/engine/sprites.c -o build/check_bounds
build/check_bounds
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_falling.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_falling
build/check_falling
```

These tests cover 720896 physics cases, 7340032 point-collision cases and 2000
falling-behavior updates through the real dispatcher, including removal and
error paths. This behavior is compiled into the DOS64 build but is not spawned
by the diagnostic entry. The preview remains idle; the original level/spawn
selection path and player behavior are still unported.
