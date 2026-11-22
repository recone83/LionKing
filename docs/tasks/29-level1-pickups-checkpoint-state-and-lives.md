# LEVEL1 pickups, checkpoint state and lives

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### LEVEL1 pickups, checkpoint state and lives

Eleven additional map markers are connected: three small healing items
(type 17), four full-heal items (18), one roar-capacity upgrade (16), one
health-capacity upgrade (49), and two checkpoints (3). They use `BUGS`,
`SYMORPH` and `SYDSTYBG` from the original shared bank list; upgrade arrival
uses the original `SPARKLE2` effect. Collection is decided by current
animation bounds, not a radius or key shortcut.

Small healing adds four health points, bounded by the current capacity;
full healing restores that capacity. Upgrades retain their own sprite
while following the original motion stream in screen space towards
(16,20) or (300,20). Only arrival increases roar capacity/charge by eight
or health capacity by two and fully heals Simba. The arrival glow lasts
36 logic ticks and reuses the collected object's render node. The status
artwork itself is not implemented yet.

Checkpoints record their marker position and play the original activation
sequence. Scrolling away and back does not repeatedly activate them.
Consumed items stay consumed during this native run, including restarts;
an upgrade interrupted by death before reaching the HUD is not awarded.
This persistence policy is tested, but full original scanner/restart
fidelity is not claimed.

Fatal enemy damage removes a life and plays the original young Simba
`SYDIE` sequence for 221 ticks. World updates pause while the death sprite
converges on screen position (160,128). This is the original short lost-life
animation, not a separate movie file. It is rendered in screen space above
the world, so the level camera cannot move it off-screen. The original
palette transition at code `0x1409d` preserves the first eight colors and
fades the remaining colors to black using the IRQ-rate fade clock. The
normal level palette is restored on checkpoint restart. The scene plays
on every lost life, including the last life before GAME OVER.
With lives left, Simba restarts at
the saved checkpoint (or the preview spawn), with health restored, empty
roar charge and 100 ticks of immunity. Enemy instances are reset; their
diagnostic counters remain cumulative. At zero lives a continue screen
allows a checkpoint restart or a return to the launcher. Additional original
death screen transitions, non-normal difficulty and special hazard-death
branches are not migrated by this block.
The timed fatal support branch `0xc884` is connected separately: its
original invisible `0x5e35` sequence delays zero health by exactly 100
ticks before the normal death sequence. It no longer fails as an
unsupported selector.

Run `LIONKING.EXE --continue-test` to enter LEVEL1 directly in the zero-life
continue-countdown state. The screen uses the archive's title palette,
`CONTINUE.MCH`, animated `RAFIKI.MCH`, `NUMBERS.MCH` and `CONTINUE.AMF`.
The sun selector uses `SUN.MCH` to resemble the reference screenshot; the
original DOS code instead uses a paw. Left and Right select YES or NO;
Space or Enter confirms. YES restores three lives at the saved checkpoint
and resumes level music after Rafiki's acceptance animation. NO, Escape,
or timeout leaves the screen. Normal difficulty starts with one continue;
the number displayed at the bottom right is the number available when the
screen opened. The original code consumes a continue upon entry, so after
using it, the next zero-life event shows the original GAME OVER artwork
instead. The counter uses the original number sprite and position, with
the spiral sun from `CIRCLE.MCH` beside it as in the supplied reference
image. The YES/NO selector separately uses `SUN.MCH`.
The spiral uses LEVEL1's palette in reserved palette slots; the rest of the
screen continues to use the title palette.

The original initializes its loop counter to 720, and the native port runs
721 logic ticks (about 14.3 seconds). The visual countdown is an addition:
the recovered DOS code does not establish a countdown digit or wall-clock
duration. It is placed to the right of Rafiki so no animation frame overlaps
it. The original loop decrements its counter per rendered iteration, so
exact DOS timing is not claimed. The shortcut loads the required resources
without opening the main menu.

The host `check_scene` tests `--continue-timeout`, `--continue-space`,
`--continue-enter`, `--continue-no`, `--continue-left`, and
`--continue-escape`, and `--continue-exhausted` exercise the shortcut,
original-resource pixels, all-frame countdown separation, input, music,
the second zero-life event, and audio cleanup. `--map-gameover` exercises
the countdown after three deaths in the normal map path.

`tools/check_pickups.c` uses real map markers and EPF banks to test healing,
collection persistence, both complete upgrade flights/glows, every
checkpoint animation frame, sound/query error propagation, three lives
and all 221 ticks of each death. It also covers upgrade collection at Y21,
where the original half-height slope divisor would be zero; the native
flight safely converges along the HUD instead.
`tools/check_scene.c --map-lifecycle` runs 60 seconds of genuine movement
and enemy contacts through the actual adapter, without synthetic hits:
one death, one restored run, two remaining lives, six damage transitions
and 2650410 submitted PCM frames. All scene regression modes, the unchanged
default exact-pixel output, and focused sanitizer tests pass.
An isolated native DOS64/QEMU run also crossed genuine enemy contacts,
completed one death/restart with two lives remaining, submitted 6384256
PCM frames and returned exit code zero on Escape. Its closed log recorded
all 11 pickup markers and 129 enemy contacts; pickup collection itself
was validated by the real-resource host tests, not this native traversal.

The four type-11 enemies now use their original `BOMBWLK`, `BOMBTURN`
and `BOMBEXP` banks. Ground contact damages Simba; airborne contact starts
the original delayed departure/explosion, rebounding descending Simba.
Roar requires an attenuated pulse strictly greater than ten. Terrain
markers select braking pauses, a returning spring trajectory or terminal
departure; no generic lizard death is substituted. Every departure and
explosion frame is rendered in the real-resource enemy tests.

All nine type-9 proximity emitters now release three original `LEAF2`
sprites on entering their exact 128-by-16 trigger region. They follow
the original randomized velocities, 0x1000 gravity increment and 100
movement ticks. Remaining inside does not emit repeatedly; exiting and
returning rearms the emitter. Restart clears the live leaf objects.
These effects do not damage Simba or alter map data.

The remaining collectible markers (1, 40, 41) use original `UP1`, `CIRCLE`
and `BUGS` art. Type 1 grants a life, capped at nine; at nine it disappears
without awarding another life or playing the collection sound. Type 40
increments the original bonus collectible counter, and type 41 selects
the original bonus flag. The bonus-game transition itself is not yet
migrated. Collected states and bonus counters survive native life restarts.

Map mode now draws the original `BARS.MCH` health, roar, Simba portrait and
life digit artwork at the original LEVEL1 screen positions. Meter fills
use the original 26-pixel integer ratio and right-edge clipping, not
replacement colored rectangles. The exact-background camera test excludes
only the changing meter areas; all remaining upper-background pixels
still match over 2000 comparisons.

Sound requests now play the original unsigned PCM samples, including
roar, recoil, rebound, collection, lizard attack and beetle explosion.
The two original effect channels mix at 12604 Hz with the ongoing 44100 Hz
AMF music. Lizard attacks use channel 1 at attack tick 32; player/pickup
requests use channel 0. Starting another sample on a channel interrupts
its prior sample. Native output retains its bounded queue and partial-write
handling. `check_music` verifies all 15 loaded sample resources, exact
resampling/conversion, channel replacement and chunk-invariant output.
Host builds of the pickup/scene tests now also require `src/engine/hud.c`;
the extended music test also uses the generated animation data and its
animation/render dependencies.

An isolated native QEMU run confirmed actual map contacts (56), three
lizard attacks, one death, two remaining lives, 1838586 submitted PCM
frames and a clean Escape exit 0 with a nonempty closed game log.
This input/lifecycle run used the `none` host backend; it verifies native
PCM submission, not audibility. A separate WAV HDA capture contained
nonzero PCM and showed the original HUD, but its Escape exit was not
confirmed, so it is not counted as a clean lifecycle test.
