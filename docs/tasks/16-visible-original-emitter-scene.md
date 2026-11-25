# Visible original emitter scene

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Visible original emitter scene

The `LIONKING.EXE --emitters` entry displays the original `LEVEL6.MAP` palette
and tiles with `CRUMBLIN.MCH`, loaded from the original level-six list at
DS `0xe3d0`, slot 160. It runs the migrated four-emitter setup `0x287bb`,
emitter `0x2865d`, timed parent `0x2881d` and falling child `0x288a1`
through the real object dispatcher. Original descriptors, scripts, counters,
positions, gravity and culling drive the visible crumbling platforms and
falling fragments; frames do not depend on keyboard presses.

This is a migration demonstration, not a playable level. Its fixed camera,
activation after one second and restart after all objects are removed are
explicit test fixtures. The original boss activation writer is not migrated.
Camera mapping is enabled only during rendering, leaving behavior flags
unchanged. Escape exits; `--idle` retains the previous automatic Simba preview
and `--manual` retains the bank/frame browser.

`tmp/tools/check_scene.c --emitters` runs the actual emitter entry for 20 simulated seconds
and checks 128064000 exact ARGB pixels, repeated activation and Escape.
It requires more than 1500 frames with visible object pixels and at least
100000 object pixels overall. Compile it with the same source list as
`tmp/tools/check_viewer.c` above, substituting the test source and output name.
Real DOS64/QEMU captures also changed over time and Escape returned exit code 0.

The scene now also exercises the original impact camera shake: the migrated
`0x2853e` constructor and `0x283cd` behavior feed the restored viewport
preparation at `0x11799`. Its signed 16-bit lower/upper clamps, low-word map
limits and eight-pixel aligned origins come from `bin/frame_timing.asm`.
Shake is added to the visible camera Y with word wrapping, after clamping,
and cleared after successful presentation as in `0x10276`.
Tiles and objects receive the same shaken viewport; visibility/culling use
the unshaken camera. This replaces no gameplay damage: the demonstration
supplies marker X zero, so the original impact gate does not call the still
unported player damage routine. Starting the shake together with the emitter
fixture is diagnostic, not a claim that the boss attack has been migrated.

The scene test requires at least 20 visibly shaken frames and 100000 changed
ARGB pixels against an unshaken map, in addition to exact output comparisons.
`tmp/tools/check_viewport.c` checks 1966080 coordinate/dimension/shake combinations,
including negative and wrapped limits and shake `0xffff`:

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_viewport.c src/engine/render.c src/engine/sprites.c \
    -o build/check_viewport
build/check_viewport
```
