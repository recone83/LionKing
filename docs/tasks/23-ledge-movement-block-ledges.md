# Ledge movement block (`--ledges`)

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Ledge movement block (`--ledges`)

`LIONKING.EXE --ledges` demonstrates left/right grabs and climbs, then
left/right drops, in a 16-second cycle. The same handlers are available
in the default preview: K grabs an alternating side, Up climbs after the
original grab delay, Down drops immediately. P selects the original
supported-turn state; Left/Right turn, Space jumps from it.

| Path | Original addresses |
| --- | --- |
| Ledge branches of directional edge selectors | `0x1e775`, `0x1e8df` |
| Left/right grab and hanging states | `0x1d5f4`, `0x1d7a3` |
| Left/right climbing states | `0x1d40a`, `0x1d4ff` |
| Supported turning and jump/fall selection | `0x20075` |

Grab aligns X to the original 16-pixel cell (plus 15 on the left),
queries ledge height through an explicit callback, zeros velocities,
starts script `618e/58d4`, sets the 42-tick counter and original flags.
Climb preserves the 31/39-tick sequence, final X offset -9/+9 or
-19/+19, and final Y offset -1/+3. Drop preserves the asymmetric
left/right flag clearing and forced-drop direction, not a normalized
replacement. The supported-turn handler preserves its counter=6,
final facing flip, and original `6180/612c` jump operands even for adult.

The demo's fixed height query, synthetic grab at Y=96 and support plane
Y=111 (Y=192 after dropping) are fixtures, not migrated map collision.
Other edge-selector branches for swing objects remain explicit
unported boundaries. Adult scripts/branches are covered by the engine
check but the visible preview still loads young-Simba banks.
All diagnostics continue to go to `LIONKING.LOG`, never over the game.

The focused action check covers both forms/directions, climb delays and
offsets, normal/forced drop masks, negative hang counters, supported-turn
timing, jump operands and support loss. The default scene regression still
matches 128064000 ARGB pixels. Native DOS64/QEMU exercised both completed
climbs and both drops; Escape returned zero.
