# First real-map interactions (`--map`)

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### First real-map interactions (`--map`)

`LIONKING.EXE --map` loads `LEVEL1.MAP` and `CONTOUR.CON` and starts
manual play on actual terrain, rather than the Y=160 test plane.
Left/Right move, Space jumps (hold for height), Down crouches/rolls,
and Escape exits. Earlier diagnostic preview modes remain unchanged.
Synthetic hit, terrain, tether, ledge and wall-grip shortcuts are disabled
in this mode.

Migrated map queries connect the original `0x14c21/0x14c72` support and
landing interfaces to the two-row contour sampler `0x16b70/0x16d3d`.
The layer-0 table contains four planes: the sampler reads contour indices
from the second plane and contact tags from the third, using one
16-pixel cell per four bytes. Shape indices use the original bit formula,
not rendered tile presence. Contour height is the low five bits, minus
one for support; candidates must be within -12..+12 pixels.

The character now follows real slopes/steps, loses support over gaps and
lands through the existing original flight selector. Queries for edges
use the current animation descriptor and facing (`0x170ae/0x171b3`);
ledge height comes from the contour plane (`0x17515`). These feed the
migrated grab/climb handlers without synthetic geometry.
The camera translates the same world coordinates in both X and Y.

Starting X=160 is still a preview choice, not migrated level startup.
Starting Y is located on the real surface (LEVEL1 currently Y=1255).
Dynamic map objects, complete hazard handling
and swing-object states remain unported. An encountered unported edge
branch reports an error rather than inventing a substitute.
Diagnostics and exit measurements remain in `LIONKING.LOG`.

`tools/check_map_collision.c` verifies the real terrain at X160/X400/X880,
connected running across six height changes, jumping and map landing,
plus synthetic contour/tag boundary checks. Compile it with the player
test source list plus `resources.c` and `resource_decoder.c`.
It also checks the final hyena-platform jump against unmodified LEVEL1:
held running jumps from X1284/X1288 land normally at X1540/Y255, while
the earlier X1280 launch still grabs the edge. The next support tick settles
Simba at Y254 on the platform's slope. Four-pixel rightward movement
continues through descent, matching the original flag operand at `0x1a8a8`.
Native DOS64 verification recorded six contour adjustments, one jump/landing,
and final position X506/Y1261. The captured frame shows Simba on LEVEL1's
real terrain; Escape returned zero. The default preview's exact-pixel
regression still passes.

Map mode also runs the original left/right lateral probes (`0x16f41`,
`0x16e37`, classification `0x17053`) before each behavior tick, in that
order. Blocked directions are removed from held input and recorded in
`boundary_controls`, so existing run/roll/flight handlers choose their
original responses. The probes preserve half-cell neighbors, asymmetric
X corrections, half-height contacts and wall-leap offsets. Wall-grip
states bypass them. The preview uses map limits X16..map-width-minus-16;
level-specific moving boundaries and dynamic-object forced contacts
are not yet connected.

Ceiling queries (`0x1739c`) use the signed top offset of the current
animation descriptor and the original contact plane. The original reads
the same next-row cell twice; kinds 0x40..0x4f and >=0xb0 block before
the later contour-table branches. This behavior is preserved rather
than replaced by an invented ceiling shape sampler.

The focused map check now covers both lateral directions, correction
order, half-cell/half-height thresholds, grip and leap flags, map limits,
and cancellation of both jump directions against real LEVEL1 ceilings.
A native input smoke recorded 164 left-blocked ticks, six contour
adjustments, one landing and final X603/Y1261; Escape returned zero.
Its ground route did not touch a ceiling (zero ceiling hits), so ceiling
behavior was verified separately by the connected real-map player check.
All measurements remain file-only in `LIONKING.LOG`.
