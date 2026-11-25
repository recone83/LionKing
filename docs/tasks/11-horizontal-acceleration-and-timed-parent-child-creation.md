# Horizontal acceleration and timed parent-child creation

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Horizontal acceleration and timed parent-child creation

`engine_motion_accelerate_x` ports `0x1a9da` and its helper `0x1cda1`.
The original adds acceleration with 32-bit wrapping, clamps the signed result
to -4/+4 in 16.16, then integrates X using the new velocity. Y is unchanged.

`engine_timed_behavior` ports original `0x2881d`: initialize script DS `0x16728`
and a 16-bit counter of 10, check visibility, decrement the counter, spawn the
original falling child at zero at parent X/Y-16, then apply parent gravity and
execute its script. The child's position uses the parent's position before
gravity. Immediate child initialization and the subsequent same-tick dispatcher
visit are both preserved; these are two updates, not one.

`engine_spawn_timed` reads original definition DS `0x162f0`, with behavior and
initializer `0x1881d`, zero flags and descriptor `0xe4c8`. It reuses the verified
object/render construction path and restores the caller's current object.
Its immediate initialization leaves counter 9, so a parent created this way
spawns on the ninth subsequent dispatcher update. This is different from
manually acquired, uninitialized state, which spawns on its tenth update.

The caller supplies separate live parent and child states and render orders.
No unported allocator or child-spawn effect is replaced by a no-op. Missing
child storage, exhausted pools or reused active child storage are explicit
errors. The original counter wraps and reaches zero again after 65536 updates;
the caller must then supply available child storage if the previous child is
still active. The long-run test verifies that exact boundary and rejects
overwriting the active child at update 65546. Full level-owned state allocation
and spawn selection remain unported; the preview is unchanged.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_acceleration.c src/engine/physics.c -o build/check_acceleration
build/check_acceleration
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_timed.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_timed
build/check_timed
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_spawn_timed.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_spawn_timed
build/check_spawn_timed
```

The acceleration test covers 7929856 cases. Timed behavior is checked for
65545 successful updates and its next respawn boundary; the full parent
constructor chain is checked for 1000 updates plus culling and exhaustion.
