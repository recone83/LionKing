# Braking, directional motion and original four-emitter setup

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Braking, directional motion and original four-emitter setup

`engine_motion_brake_x` ports original `0x1a844`, including its signed
absolute-value helper. It stops only below the strict magnitude threshold,
otherwise subtracting the caller-supplied signed decrement with 32-bit wrap.
It preserves the unusual x86 `abs(INT_MIN)` result rather than introducing
undefined signed overflow. It does not invent the sign of the decrement.
`engine_motion_right/left` port `0x1a886/0x1a8f2`, setting a minimum rightward
velocity +2 or leftward velocity -2 in 16.16 before integration. Only the
rightward original helper observes the stop bit 0x10 of object byte +0x4f.
This is the high byte of movement flags, not status byte +0x49:
the airborne status bit 0x10 must not stop horizontal movement. Jump ascent
and descent now use the original movement flag byte, preserving rightward
travel after the apex instead of shortening jumps into a ledge grab.

`engine_setup_emitter_group` ports original `0x287bb`. It resets the activation
flag and creates four original emitters in order: X 3480/3512/3536/3568,
Y 424, counters 170/190/200/210, variants 0/1/0/1.
An `ENGINE_EMITTER_GROUP` owns the live activation flag, emitter state,
parent/child slot storage and resulting object references. Callers supply
the live camera, visibility window and render orders. The group must outlive
all its active objects and cannot be reset while any member or descendant
is active in the same pool. Preflight requires four free object and render
slots, preventing partial creation or resetting the activation flag on
resource exhaustion.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_braking.c src/engine/physics.c -o build/check_braking
build/check_braking
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_directional_motion.c src/engine/physics.c -o build/check_directional_motion
build/check_directional_motion
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_emitter_group.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_emitter_group
build/check_emitter_group
```

Tests cover 1769472 braking cases and 2162688 directional-motion cases.
The group test checks original instruction constants, inactive animation,
90 active updates with eight parent-child chains, camera removal and pool
exhaustion. Activation in this host test is supplied explicitly; the original
boss behavior that sets DS `0x1938f` remains unported. The native diagnostic
entry is unchanged and does not claim to run this level.
