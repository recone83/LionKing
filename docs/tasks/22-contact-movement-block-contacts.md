# Contact movement block (`--contacts`)

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Contact movement block (`--contacts`)

`LIONKING.EXE --contacts` cycles through right/left contact rebounds,
a thrown launch, and movement toward a tether point followed by release.
The previous default remains available with no arguments. B, R and F
activate these cases manually in either ground preview and stop automated
inputs; Left/Right, Space, Ctrl and Escape keep their existing meanings.

Migrated original code addresses:

| Path | Addresses |
| --- | --- |
| Contact rebound selector and directional entries | `0x1f5f1`, `0x1f618`, `0x1f672` |
| Thrown movement and facing-dependent velocity helper | `0x1f2b1`, `0x202de` |
| Adult contact escape / release | `0x1f3fb` |
| Tether-point movement and release into air | `0x1f6cc` |

Rebounds select the original `6228/58b8` script and preserve the unequal
right/left initial Vy (-4.5/-4). Thrown movement selects `621a/5864`,
starts at Vy=-4.5 and facing-dependent Vx=-1.5/+1.5, then uses the
original 35-tick counter and boundary checks. Tether movement advances
each integer coordinate by 4 only outside the +/-4 tolerance, with
wrapped word arithmetic and no animation update while attached.
Release calls the current air stream without reinitializing its script
or facing, matching the original handler replacement.

The adult contact path preserves its state=70 completion, attack counter,
two overlap queries on the right-facing miss path, and release flag.
It is available to engine callers but not demonstrated with young-Simba
banks. Original calls to the `0x1510d` RET stub have no invented effect.

B/R/F activation, forced directions in the automatic sequence, target
placement and release after 45 ticks are explicit test fixtures, not
level/enemy interactions. Real overlap detection is still a required
callback for adult contact sources. Sound sample 0 is logged, not played.
No original level collision or enemy AI is claimed by this preview.
