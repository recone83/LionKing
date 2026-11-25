# LEVEL1 to LEVEL2 transition

After LEVEL1 completion and its Rafiki reward scene, the game now starts the
original `LEVEL2.MAP`, using the Level 2 title card, `LION2.AMF` music and the
21 sprite banks from the original Level 2 bank table. Lives and remaining
continues are carried forward; the BUG TOSS bonus runs first when its marker
was collected. `bash build.sh --level2` builds and starts this stage directly
in DOS64/QEMU; `LIONKING.EXE --level2` also starts it directly.

The stage uses the existing map collision, young-Simba movement, camera,
health/roar HUD, common pickup/checkpoint and continue systems. The original
level descriptor at DS:0x4e1c starts Simba at (67, 387). The original level
dispatcher at 0x7c99 ends the stage when Simba's world X reaches 0x18d8
(6360); the port now uses that threshold rather than the edge of the map.
LEVEL2 music uses the DSMI C5 sample-rate reference (856 period units), rather
than the previous octave-too-high 1712 reference. The opening PCM was compared
against the locally installed libopenmpt renderer; this is not a recording of
the original DOS sound card. It also uses linear interpolation and a 64-frame transition
(approximately 1.45 ms at 44100 Hz) on instrument/note or volume changes and
sample ends to reduce abrupt PCM steps. Tracker timing and sound-effect
sampling are unchanged; the settings are restored after a continue.
The tracker also decodes signed pitch slides correctly: for example, LEVEL2's
`0x84 FD` is a slide of -3 per tick, not -125. LEVEL2 scales regular, fine,
and tone-portamento slides to its period representation and the sample's
rate; the previous scale made its recurring melody slides twice too fast.
Fine-slide magnitudes are limited to the low nibble. Tests exercise both
signs and real LEVEL2 passages. Other tracks retain their previous slide scale.
This is a waveform-quality approximation, not a bit-exact DOS mixer, and
does not prevent audio underruns caused by slow rendering or the audio backend.

The original sound loader selects the LEVEL2 sound table at DS:0x12fb0.
The port loads `MONKEY`, `THROW1`, `HITHEAD` and `SPLASH` into slots 20–23,
alongside the common sounds, and clears previously loaded slot sizes when
changing levels. The monkeys use slots 20 and 21, and water contact uses
slot 23; the `HITHEAD` trigger has not yet been implemented.

The 13 type-107 bird markers now use the original `LVL2BIRD` bank and DS
animation streams. Their original controller at 0x1b7fa selects one of four
idle sequences every 19 ticks; on contact with Simba, a bird switches to
its flight animation, plays common sound 5 and flies right/up after six
updates without damaging him. Untriggered birds can respawn after scrolling;
triggered birds are removed until a life restart. The fixed random seed and
host-side update ordering have not been compared frame-by-frame to DOS.

Hanging-monkey markers (types 5/6/7/8/23/25/26/62/64) use the original idle
scripts and sprite banks selected by their constructor variants. Types
8/25/62/64 animate while idle; types 5/6/7/23/26 use still idle frames. Type 6
monkeys catch Simba only when he is falling toward their marker during a guided
throw, follow the animated attachment point, and throw him upward toward the
next marker using the original velocity table and sound. Types 8/25/62/64 catch
Simba the same way, follow their animated attachment for 31 updates, and then
throw him down at the original velocity toward the first matching marker below.
Twelve of the 15 such markers have no lower target and use the original -16
sentinel, allowing ordinary terrain landing. Their full active animation and
sound are reproduced. Types 5, 7, 23 and 26 also catch and throw Simba
horizontally: type 7 throws right and the others initially throw left, toward
the first matching marker on the same row. The throw uses the original
animation, early sound cue, horizontal speed and distance-indexed vertical
velocity. The original -16 sentinel is retained when no marker exists to
the left. The extracted velocity-data slice is limited to 512 entries and invalid
indices fail explicitly; the tested LEVEL2 horizontal throws fit in that range.
When Simba roars, idle type-23, type-25, type-26, type-62 and type-64 monkeys switch between
their original alternate directions if both coordinate differences are below
80 pixels. They perform the original 18-update motion and play common sound
20 before resuming with the new target, sprite and throw; another roar switches
them back. Unchangeable types ignore the pulse. Like the original spatial
object list, a culled monkey retains its changed variant until level restart.
Type 62 switches to type 24, which throws right;
type 64 switches to type 67, which throws left. Downward monkeys also use
the original mirrored orientation. These objects are monkeys, not bird nests.
The nests shown on tree branches are tiles in `LEVEL2.MAP`, not these actors;
the existing map renderer draws them and the map contour provides support.
Other nest-specific interactions have not been established. The five
type-27 rhino horns use their original idle and launch animation streams.
When falling Simba touches a horn without the active throw flag, the horn
stops him and after four updates launches him toward the nearest matching
marker above it, using the original velocity table and common sound 0.
Simba is drawn in front of the horn. The player enters the existing guided-air
state, and the horn completes its
12-update animation before it can be culled or triggered again. The port
checks the velocity-table index and reports invalid map/player states instead
of reading beyond the extracted 128 entries. Frame-by-frame comparison with
the original DOS game and a full keyboard playthrough remain outstanding.
LEVEL2 marker handling is scoped to the level so it does not spawn these
sprites on LEVEL1.

The 11 type-28 markers use the original `RHINTAL3` tail animation and grab
point. Simba follows the swinging tail, can jump off or drop down, and the
camera remains fixed during the grab and resumes following on release, as in
the original camera freeze flag at DS:0x1939b. The tail has the original
10-tick initial and 40-tick re-grab delays. The 14
type-29, type-73 and type-51 giraffe-head markers use the `GIRAF` bank and
their original offsets, facing, contact animation and slide directions.
The head collision uses the original sprite bounds and vertical velocity
crossing test; the generic platform's separate ten-tick contact-grace path has
not yet been reconstructed. A full in-game comparison remains outstanding.
Water contact enters the original Simba splash animation, plays `SPLASH`, and
continues into the existing lost-life and checkpoint restart flow. The separate
original water-splash particle object is not yet reproduced.

The four type-44 water logs use the original `LOGLVL2` bank, idle and
sinking animation streams and platform contact bounds. Simba can land and
jump from them; while occupied they sink until support is removed, then
resurface. They respawn after leaving the activation window or restarting.
The generic platform's ten-tick contact-grace path remains unimplemented.
The real-map actor test checks all four logs, including landing, sinking,
resurfacing, and cleanup; `check_victory --level2-log` tests landing and a
keyboard jump through the gameplay loop.

The map also contains one type-162 extra-life marker. The original constructor
table at code address 0x5c5c maps it to the same descriptor as type 1, so it
now uses the existing extra-life animation, collection, nine-life cap and
restart behavior. This does not implement the other unported collectibles.

Other Level 2 actors, hazards, scripted interactions, and the original
completion sequence and reward scene are not implemented yet. Level 2
currently returns to the main menu after reaching the completion threshold.
The ostrich rides at map markers 52 `(2208,480)` and 53 `(3728,480)` use
distinct obstacle tables at DS:0x19c4b and DS:0x19c83, a scrolling/wrapping
camera and player ride states.
The checksum-verified route records and obstacle definitions are now extracted
and decoded by `src/engine/ostrich_route.c`. `src/engine/render.c` contains the
ride's camera look-ahead and scroll-distance/wrap calculations.
The separate visual component in `src/engine/ostrich_visual.c` implements the
original body and head animation programs, their draw order and attachment
point, and releases their render and object slots.
`src/engine/ostrich_obstacle.c` implements the three original route obstacle
constructors, including their graphics, collision priorities and cleanup.
`src/engine/ostrich_sequence.c` connects both schedules to obstacle creation,
ordered updates, camera-wrap shifts, collision reporting and cleanup. An event
that runs out of object or render slots is rolled back without consuming its
route record.
The rider, airborne rider and hit states (0xf94d, 0xfbc1 and 0xfb2e) are
implemented in `src/engine/behaviors.c`, including ducking, the second jump,
hit sound, and dismount transitions. `src/engine/ostrich_ride.c` and the
gameplay adapter connect mounting, animation, jump and duck controls, collisions,
camera wrapping and route completion. Existing map actors and pickups are
suspended during the looping section so they do not respawn on each wrap;
their persistent collected/defeated state is retained. The ride is cleaned up
on exit or death, and markers are reset on level restart.
As in the original input routine at `0x84bc`, jumping requires a new key press:
holding the first jump does not automatically trigger the second. Simba can
jump from the ostrich only after its vertical velocity exceeds `-6.0`;
a press before that threshold is not buffered.
Ground probes follow the original `0x6b9f` rule: while a ride is active,
positions at least 320 pixels beyond its base are sampled 320 pixels earlier.
This keeps the ostrich and rider supported across the repeating map section.
Both foreground passes wrap at the original 512-pixel boundary; the parallax
background uses the accumulated 16-bit scroll offset, retained after dismount
and reset on level restart. `tmp/tools/check_level2.c` checks both real route
sections pixel-for-pixel at all camera phases and verifies background wrapping;
an additional map copy with foreground flags set exercises both draw passes.
The full ride tests also check these render arguments through the gameplay loop.
The first ride also runs the original tutorial arrow sequence (object
0x14439): the `ARROW` sprite points up and down, with a second arrow during
the double-jump prompt. The original motion stream, screen positions and
timings are used; the second ride has no tutorial. Both arrows are cleaned up
on death, dismount or exit. The full ride test checks their timing and
rendered pixels; `--level2-ride-hint-escape` checks cleanup while both are
visible. A visual comparison against the original in QEMU remains outstanding.

`tmp/tools/check_level2.c` validates the decoded map and contour data, stage-2
background rendering, starting position and completion boundary, the title
frame, the exact rendered pixels and ground support of a real tree nest,
all 21 original sprite banks, and
eight seconds of non-silent `LION2.AMF` output. It also checks the real
ostrich marker locations, constructor descriptors, full obstacle schedules,
spawn positions and route termination, including simulated scrolling and
multiple wraps; this is not an ostrich gameplay test.
`tmp/tools/check_level2_ostrich.c` exercises actual ostrich sprite banks and
animation frames, pose changes, all obstacle events from both routes,
collision priority and resource-exhaustion cleanup. It also simulates both
complete schedules through the obstacle controller with multiple camera wraps,
and verifies rollback and retry of a two-obstacle event. These are component
tests, not a playable ride or a full gameplay-loop test.
`tmp/tools/check_player_ostrich.c` checks the rider states, jump velocity threshold,
duck animation changes, immunity, collision reactions and both dismount paths.
`check_victory --level2-ride-jump-input` exercises held, early and correctly
timed presses through the actual input and gameplay loop.
`tmp/tools/check_level2_bird.c` additionally checks the idle bodies at both real
markers, including rendering, culling, respawn and restart.
`tmp/tools/check_victory.c` checks
that LEVEL1 completion transfers the remaining lives and continues, and that
the bonus round runs before Level 2 when selected, while Escape during BUG
TOSS returns to the main menu without starting Level 2. Its `--level2` case
also places the player immediately before and at the completion threshold
in the real gameplay loop; it does not simulate traversal of the whole map.
Its `--level2-ostrich-handoff` case injects ride activity and an attachment
flag into that loop, checks the airborne-to-rider transition, then clears the
activity flag and checks the rider-to-air transition. It does not test mounting
or a complete ride.
The `--level2-ride-first` and `--level2-ride-second` cases position Simba near
the respective real markers, then run mounting, both jump stages, ducking,
camera wraps and full route completion through the game loop. They move
spawned obstacles out of the way, so they do not prove an unassisted ride.
`--level2-ride-hit` leaves the obstacles in place and checks an actual hit,
death, cleanup and restart; `--level2-ride-escape` checks cleanup on exit.
`--level2-ride-avoid` also leaves the first obstacle in place and checks that
a timed jump clears it without a hit.
`--level2-ride-full-first` and `--level2-ride-full-second` use scripted
keyboard input based on obstacle positions, leave every obstacle in place, and
check that all 9 and 18 obstacles respectively are passed without a hit,
including the combined obstacles, camera wraps and dismount. The tests position
Simba near each marker and do not replace manual play or visual comparison.
The `--menu-level2` case runs the real menu-to-Level-2 transition, checks the
blank loading frames and title-overlay pixels against the original art and Level 2 palette, and verifies
that loading progress increases through all 21 level-specific banks.
The `--level2` and `--level2-sound-failure` cases check the sound slot mapping
and missing-sample error; the host test must be linked with
`-Wl,--wrap=resources_load_entry` in addition to its other wrappers.
`tmp/tools/check_level2_bird.c` checks real marker counts and sprite rendering,
bird idle choices, contact and flight timing, culling, restart and sound errors;
it also checks each of the 34 real monkey markers, their idle banks and
64-update frame sequences, mirroring, culling and restart, plus the two
type-6 capture and upward-throw sequences and all 15 type-8/25/62/64 downward throws,
including the missing-target sentinel, animation timing, sound errors and restart.
It also checks all 17 horizontal monkeys, fixed real-map targets, the original
velocity bytes and timing, player-state handoff, sound and bounds failures.
Roar tests cover both directions of all five real variant changes, distance
boundaries, timed motion, actual player-roar updates, subsequent throws,
sound failure and respawn.
`tmp/tools/check_level2_bird.c` additionally exercises tail capture, both facing
directions and release modes, re-grab delay, and all 14 giraffe markers.
`tmp/tools/check_level2_water.c` exercises actual LEVEL2 water collision through
the player update, splash sound, lost life and restart signal. It also checks
falls beneath the giraffe-area slopes in both directions. The original
`0x4e22` bottom boundary (map bottom plus 40 pixels, except level 4) triggers
the lost-life restart when a fall misses the water markers; it does not invent
a splash where the map has none. `check_victory --level2-fall` verifies this
restart and life loss through the real gameplay loop.
`tmp/tools/check_level2_life.c` checks the original constructor-table equivalence,
real marker and sprite, collection, culling, life cap and sound failure.
`tmp/tools/check_level2_rhino.c` checks all five original marker targets, rendering,
collision gates, animation, delayed launch, original velocity data, the
guided-air handoff, culling and error paths.
