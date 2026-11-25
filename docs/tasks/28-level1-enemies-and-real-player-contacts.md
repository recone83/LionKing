# LEVEL1 enemies and real player contacts

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### LEVEL1 enemies and real player contacts

`LIONKING.EXE --map` now activates the 14 original lizard markers (type 14)
from LEVEL1's fourth map plane. The first two on the lower route start at
X352/Y1248 and X592/Y1248. Walk right from the preview start to meet them.
Left/Right move, Space jumps, Down crouches/rolls, Ctrl roars, and Escape
exits. Music continues during combat; diagnostics stay in `LIONKING.LOG`.

The connected block includes half-pixel patrol, contour support, directional
turns, terrain-tag obstacle pauses, the original attack sequence and its two
short hit windows, distance-scaled roar stun, body contact damage, recoil,
100-tick immunity, and the lizard death animation/removal. A contact while
Simba is descending faster than 0x4000 in 16.16 velocity and has the original
air/roll flags selects the existing rebound and defeats the lizard.
Walking into it instead costs one health point. Defeated lizards do not
respawn during the current run; live ones culled by scrolling can return at
their original marker.

After damage, Simba alternates between full and approximately 30% opacity during the
100-tick immunity window (about two seconds), using the original blink
timing helpers at `0x1893c/0x18941`.
The period is 2 normally, or 4 when more than 100 immunity ticks remain.
The softer opacity effect is an intentional visual change from the original
on/off blink. Dimmed pixels use a private DOS64 layer with opacity 77/255
(about 30.2%), not per-pixel RGB blending in the game. The base scene contains
no Simba; only pixels that differ between the with/without-Simba scenes are
submitted as opaque horizontal runs to his otherwise transparent layer using
batched `FillRects`. Foreground scenery, other sprites, the FPS text and the
HUD retain their normal draw order. The layer is hidden on full-opacity
frames and menus, reused between hits, and destroyed on exit. Layer service
failures are logged and terminate the game rather than silently falling back.
The two indexed scene renders are still needed to preserve occlusion; this
change moves blending to the runtime, not to a guaranteed GPU path. Render
timers advance only once. Collision and movement are unchanged; full opacity
returns when immunity expires, and the death animation is not left blinking.
[check_opacity.c](../../tmp/tools/check_opacity.c) checks all 65536 palette pairs at
77/255 opacity, real LEVEL1/Simba layers, both sprite draw passes, unchanged
HUD, single timer advancement and immunity expiry.

Original `LIZRDWLK`, `LIZRDTRN`, `LIZRDATK` and `DUST` banks and DS
animation streams are used, including the original shared death effect.
Map graphics, contour/tag planes and markers are not modified. Lizards and
porcupines, beetles and leaves are active, along with all collectible
markers, healing/upgrades/checkpoints, original PCM effects and HUD described
below. Hyenas, full world hazards and level transitions remain pending.
Map mode starts with normal-difficulty health/capacity 4, roar capacity 16
and three lives; roar recharges from zero by one increment per 32 logic
ticks, capped at its current capacity. Non-map fixtures retain their
previous 100 health/roar choices. Random enemy choices use the
original three-byte generator with a fixed preview seed. The original
startup seed has not yet been traced.

`tmp/tools/check_enemies.c` checks real-map positions/support, visible changing
enemy pixels, both turn directions, damage/immunity, the strict stomp
threshold, both mirrored attack windows and their excluded boundary ticks,
stun timing, obstacle braking/resume, culling, death and
unchanged map bytes. It passes Address/UndefinedBehavior sanitizer checks.
`tmp/tools/check_scene.c --map` runs the actual DOS64 adapter with movement,
roar, jumping and audio mocks: nine spawns, 19 contacts, two
damage transitions, one landing and 886410 PCM frames in its 20-second
fixture, with clean Escape/audio/log shutdown. The unchanged default demo
still matches 128064000 ARGB pixels. This input fixture now verifies that
its initially uncharged roar does not stun enemies; the exact strong-roar
thresholds remain covered by the enemy tests. Host scene builds also need
`src/engine/enemies.c`, `src/engine/pickups.c` and `src/engine/lifecycle.c`.
`tmp/tools/check_scene.c --map-stomp` exercises a real descending contact:
one lizard defeat, Simba's rebound, all subsequent death frames, continued
movement/roar/jumping and music, then clean Escape. The enemy test also renders
each death tick: DS stream `0x13887` references `DUST` slot 65, not
`HYENADIE` slot 66.
Native QEMU also showed Simba and a real lizard together, accepted movement,
roar and jumping, recorded seven damage/recoil events with 93 health left,
one stun and one landing, and returned exit code zero on Escape.

Map mode now retains a camera across logic ticks instead of immediately
recentering it on every animation frame. The original LEVEL1 follow logic
(`0x17580`) gradually changes the horizontal anchor between 128 and 192,
uses a 20-pixel vertical dead zone around the normal 128-pixel anchor,
and limits either axis to 8 pixels per tick. Looking up/crouching uses the
original 210/64 vertical anchors. Map bounds still clamp the viewport.
The preview initializes the camera beside its chosen spawn rather than
scrolling down from the original zero-camera startup.

`tmp/tools/check_viewport.c` covers these limits, facing reversals, posture
anchors and map bounds. `tmp/tools/check_scene.c --map-animation` runs repeated
idle/roar/short-crouch transitions while checking that the distant background
remains pixel-identical for all 2000 successive frame comparisons. The
original sprite poses, per-frame anchors and movement commands are retained;
they are not recentered artificially when switching animations. The default
non-map scene keeps its previous camera and exact-pixel output.

The five original type-10 markers now activate porcupines using `PORCUWLK`
and `PORCUTRN`, not recolored lizards. The lower-route marker is at
X896/Y1248. Patrol speed is 0xa000 (5/8 pixel per tick); obstacle pauses
are 120/30 ticks with braking 0x800. Jumping onto an upright porcupine
damages Simba rather than defeating it. Rolling into it, or a roar pulse
of at least 8 after distance attenuation, flips it upside down. The
original inverted pose remains protected from contact for 20 ticks.
An airborne contact after that interval starts Simba's rebound and the
porcupine's falling removal; fallen enemies do not respawn in this run.
The focused enemy test uses actual animation bounds and renders every
inversion/fall tick, including culling and subsequent no-respawn checks.
An isolated native QEMU run also displayed Simba and a real porcupine
together, accepted movement and roar, and closed with exit code zero on
Escape. The closed log recorded all 19 enemy markers, 49 contacts, four
damage/recoil events and 1531037 submitted music frames. Combined counters
now use `Enemy` labels; marker counts remain separate for each class.

LEVEL1 is **not complete yet**. The authoritative fourth-plane inventory
contains 47 nonzero markers of 13 types, not just the enemies on the lower
route. Its counts are: 1:1, 3:2, 9:9, 10:5, 11:4, 14:14, 16:1, 17:3,
18:4, 40:1, 41:1, 43:1, 49:1. All thirteen marker types now cover all
47 positions, including the final hyena. The original starting descriptor
uses X65/Y1255, rather than the previous contour-search preview start.
Remaining fidelity work includes a complete world-hazard audit,
bonus-game/continue/menu transitions and difficulty selection.
The normal-difficulty boss, death-count completion condition and original
GAMEOVER artwork/timing are implemented. Completion plays the original
Rafiki reward before returning to the menu (or launcher with `--map`),
rather than entering an unported next level or bonus game.
Unmigrated types are not
substituted with generic enemy or pickup behavior.

The hyena uses the original waiting gate, jumping/landing, patrol/attack,
panting vulnerability, hit and final-death scripts, including all seven
HYENA banks and samples 17/18. Normal difficulty requires two hits.
Only panting permits a stomp, with downward velocity strictly above
`0x4000`; other contacts damage Simba. A successful hit rebounds Simba,
and the defeated counter advances only after the terminal death animation.
The LEVEL1 controller at base-zero `0x7c6d` tests this counter, not the
bonus-only reward collectible. The native terminal result is idempotent
and rejects completion while Simba is dead or in a death/fall transition.
Hit/death facing follows the original inverse of Simba's sprite direction,
not their relative X positions. Patrol jumps require a clear side probe.
The original 512-pixel cull applies to patrol, pause and moving jumps,
not the waiting gate or terminal hit/death animation.

`tmp/tools/check_enemies.c` exercises the natural boss cycle with real terrain,
sprites, sound requests, unsafe/threshold stomps, both hits, terminal
cleanup and restart. It asserts all eight naturally reached boss states,
both hit directions and a single completion only after final death;
host builds of this test also link `src/engine/lifecycle.c`.
`tmp/tools/check_pickups.c` checks the completion result
and visible GAMEOVER artwork. `tmp/tools/check_scene.c --map-gameover` drives
the actual adapter with keyboard input and real enemy contacts through
three deaths, two restarts, zero lives and the 200-tick GAMEOVER display.
The ordinary map, stomp, stationary-camera and lifecycle selectors remain
separate regression tests; the stomp input timing now reflects X65.
