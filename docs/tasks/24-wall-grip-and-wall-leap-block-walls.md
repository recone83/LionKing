# Wall-grip and wall-leap block (`--walls`)

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Wall-grip and wall-leap block (`--walls`)

`LIONKING.EXE --walls` runs eight connected cases in a 32-second cycle:
both opposite-wall catches, both free leaps back into flight,
both wall-to-ledge transfers followed by climbing, and both wall detaches.
W selects a wall grip, alternating sides, in any ground preview.
Space leaps after the original grip delay; Down detaches after that delay.
Late Left/Right steering is preserved, including Left winning when both
directions are held. Up climbs after a wall leap reaches a ledge.

Migrated handlers: grips `0x1d985/0x1db06`, leaps `0x1dc42/0x1deaf`,
and their guarded branches in `0x1e775/0x1e8df`. Grips retain the
20-tick delay, `62d0/62de` streams, cell-aligned coordinates and flag 8.
Leaps retain `6236/6244`, counter=16, state=8, initial X=-45/+45,
Y=-18/-39, velocity X=-2.5/+2.5 and Y=-6.5. The eight initial ticks
animate without integrating motion. Afterwards the original generic
gravity helper adds `0x4e00`, even for adult Simba. Finishing restores
flight using `613a/5928`; detaching uses `612c/5928` and counter=8.

An opposite-wall catch is allowed only from the corresponding leap
handler, not from arbitrary airborne states. The level-5 special-contact
drop and variant-8 final X correction are retained as explicit state
inputs. Collision queries, initial grips and support heights in this
preview remain diagnostic fixtures. The preview supplies one contact
per selected case; it does not claim real wall/map collision or new
level geometry. The original scripts and migrated physics produce the
motion. Young Simba is visible; adult branches are checked in the engine.
Diagnostics remain file-only.

The focused action check verifies both forms/directions, exact initialization
and delays, generic gravity, late steering/stop ordering, ignored same-side
contacts, opposite-wall and ledge transfers, both finish corrections,
detach, the level-5 special drop, damage continuation and missing queries.
The default scene still matches 128064000 ARGB pixels. Native DOS64/QEMU
completed all eight wall cases, including both ledge climbs and both
detaches, and Escape returned zero without rendering diagnostic text.
