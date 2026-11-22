# LEVEL1 to LEVEL2 transition

After LEVEL1 completion and its Rafiki reward scene, the game now starts the
original `LEVEL2.MAP`, using the Level 2 title card, `LION2.AMF` music and the
21 sprite banks from the original Level 2 bank table. Lives and remaining
continues are carried forward; the BUG TOSS bonus runs first when its marker
was collected. `--level2` starts this stage directly for testing.

The stage uses the existing map collision, young-Simba movement, camera,
health/roar HUD, common pickup/checkpoint and continue systems. The current
Level 2 completion condition is reaching the far edge of the map. This makes
the original map traversable, but is a port-side objective rather than a
verified reconstruction of the original stage dispatcher.

Level 2-specific enemy actors, hazards, scripted interactions, exact
completion condition and reward scene are not implemented yet. Their map
markers are not interpreted by the Level 1 enemy engine. Level 2 currently
returns to the main menu after reaching the map edge.

`tools/check_level2.c` validates the decoded map and contour data, stage-2
background rendering, the title frame, all 21 original sprite banks, and
eight seconds of non-silent `LION2.AMF` output. `tools/check_victory.c` checks
that LEVEL1 completion transfers the remaining lives and continues, and that
the bonus round runs before Level 2 when selected, while Escape during BUG
TOSS returns to the main menu without starting Level 2.
