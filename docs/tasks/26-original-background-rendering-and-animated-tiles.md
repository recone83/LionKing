# Original background rendering and animated tiles

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Original background rendering and animated tiles

`--map` now renders the second map layer behind the world, using the
original per-level parallax profiles (`0x11728`, `0x1181d`). Foreground
ordering is background -> unflagged map tiles -> ordinary objects ->
flagged map tiles -> high-pass objects, as in `0x144a3`. Other diagnostic
modes retain their previous rendering for regression comparisons.

Dedicated background previews:

```
LIONKING.EXE --background
LIONKING.EXE --background6
LIONKING.EXE --background10
```

The first shows LEVEL1 parallax; it does not invent a timed tile animation.
The other two also load `LEVEL6.BLK` / `LEVEL10.BLK` and run the original
four-frame tile substitution (`0x19d82`, `0x19e90`). Arrows pan the camera;
Escape exits. The starting camera is a preview fixture at X0/Y0. There
is no player, gameplay initialization or on-screen diagnostic text in
these dedicated previews.

The original animation changes frames on the first logic tick and then
every fifth tick, cycling 1 -> 2 -> 3 -> 0. LEVEL6 copies one 2880-byte
block; LEVEL10 copies 128 bytes followed by six 512-byte blocks. Targets
are resolved from the original map's tile references, not hardcoded
native graphics offsets. Only tile pixels are modified: map tables,
contact tags and contour indices remain unchanged.

Parallax preserves per-row integer ratios, horizontal wrapping and
the repeated LEVEL5 row-21 threshold. Level-specific extra horizontal
offsets from unported world effects are not yet supplied. These previews
do not migrate enemies, platforms, hazards or palette effects.

`tools/check_map_collision.c` additionally verifies row-profile thresholds,
tile flipping/wrapping, exact BLK frame copies and cadence, and unchanged
bytes outside the animated destinations. At a fixed starting camera,
21 ticks produced five substitutions and 7675 visible pixel changes
in LEVEL6, 950 in LEVEL10.

Native DOS64 smoke verification also captured changing pixels at a fixed
camera in both animated previews, then successfully ran LEVEL1 movement
with parallax. All three invocations exited with code zero. The existing
default demo still passes its 128064000-pixel regression.
