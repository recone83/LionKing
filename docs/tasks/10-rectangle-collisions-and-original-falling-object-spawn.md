# Rectangle collisions and original falling-object spawn

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Rectangle collisions and original falling-object spawn

`render_local_rectangle_hit` migrates original `0x1693d`: target descriptor
bounds use H/V flips, while a supplied local rectangle uses the current
object's H flip only, exactly as the original does. `render_objects_hit`
migrates `0x16a57`, applying both objects' own descriptors, H/V flags and
positions. Both retain signed, inclusive comparisons and 16-bit wrapping;
neither normalizes inverted bounds nor ignores hidden objects.

`engine_spawn_falling` now executes the original `0x1508e -> 0x14fbd` creation
path for definition DS `0x162fe`. It reads and checks the original handler,
flags, initial descriptor `0xe540` and initializer from the embedded dump.
It acquires the object then its render node, sets the native owner and render
order, and immediately invokes migrated behavior `0x288a1`. The caller's
current-object pointer is restored, including when spawning from another
behavior callback. The existing dispatcher then visits an appended object
later in the same update, preserving the original traversal.

The caller supplies a fresh `ENGINE_FALLING_OBJECT`, position, visibility
window and render order; state and visibility must outlive the spawned object.
The API returns 0 with an active output object, 1 with a null output when
original initialization culls it, or -1 on error. As a deliberate native
safety change, exhausted pools and failed initialization do not leave a
partially constructed object with a missing render node. Reusing active state
in the same pool is rejected. This only supports the verified original
definition, not all spawn records or their unported initialization callbacks.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_rectangle.c src/engine/render.c src/engine/sprites.c \
    -o build/check_rectangle
build/check_rectangle
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_overlap.c src/engine/render.c src/engine/sprites.c \
    -o build/check_overlap
build/check_overlap
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_spawn.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_spawn
build/check_spawn
```

Tests cover 37748736 local-rectangle cases and 15728640 object-pair cases
in both argument orders, plus actual spawning, immediate updates, pool
exhaustion, initialization culling and same-tick traversal. The diagnostic
entry still does not invoke level spawning; no preview key binding was added.
