# Bonus games: asset compatibility

BUG TOSS is now a playable round. In LEVEL1, collecting marker type 41
selects the original bonus flag (DS `0x19369`). The original dispatcher at
`0x45a1` uses that flag to select stage 11 from the table at DS `0x5019`,
without advancing the next-level pointer. Stage 11 uses `BUGTOSS.AMF`.
After the LEVEL1 reward scene, the selected flag now launches the bonus round.
Left/Right (or the configured bindings) move Pumbaa; Jump, Slash or Roar
triggers his one-use burp. Caught rewards update the in-session lives,
continues and maximum roar. Missing a catchable item or catching a hazard ends
the round; reaching 110 caught items also ends it. Escape returns to the main menu.
After a completed round, gameplay continues to LEVEL2. Escape still returns to
the main menu without entering LEVEL2.

The shared bonus asset loader reads the map, eight sprite banks, BURP and
COLLECT1 effects, and both music tracks through the existing EPF reader. Its
fixed decoded buffer sizes match the archive examined here; a resource exceeding those sizes is rejected,
not truncated. Failed loads clear the `loaded` flag and may be retried.
The application allocates the approximately 594 KiB bonus asset structure on
the API 16 heap only when the viewer or bonus stage starts. Missing heap
support and allocation failures are reported. The loader itself continues to
use caller-owned storage; the buffer sizes are still fixed.

The host-side `tmp/tools/check_bonus_assets.c` diagnostic compares the loader's
output with independent EPF reads, exercises errors and retries, verifies the
bonus map palette and all stage layers, renders every frame of the sprite
banks, checks that both effects produce PCM, and checks both music tracks
against the existing AMF player.

Results with the current archive:

- `BONUS.MAP`: 364,360 decoded bytes; palette and all six layers render.
- `TMBUGTOS.MCH`, `TMWKWAIT.MCH`, `PUMBAA.MCH`, `BUGS.MCH`: 17, 16, 22 and 20 frames respectively
  render successfully.
- `PUMBBURP.MCH`: 15 frames render successfully; the 10,280-byte `BURP`
  sample produces non-silent PCM.
- `BUGHUNT.AMF` and `BUGTOSS.AMF`: initialize and produce non-silent,
  chunk-invariant PCM; each completes a loop in approximately 20 and 26 seconds.
  `BUGTOSS.AMF` uses the AMF note-delay effect (`0x93`, track 8 row 43),
  which was not previously supported. The player now delays the note,
  instrument and volume until the specified tick; a delay at or beyond the
  row speed does not trigger. Tests cover immediate and delayed triggering,
  preserving a previously sounding note, and truncated input. Effect
  identification was cross-checked against the
  [OpenMPT AMF loader](https://github.com/OpenMPT/openmpt/blob/master/soundlib/Load_amf.cpp).

This tests resource compatibility, not the correct sprite placement, gameplay,
audio fidelity or the full map. Run from the repository root with the original
archive at `data/LIONKING.EPF`:

```bash
cc -O2 -g -std=c99 -Wall -Wextra -Werror \
    -fsanitize=address,undefined -fno-omit-frame-pointer \
    -Iinclude -Isrc \
    tmp/tools/check_bonus_assets.c src/engine/bonus.c src/engine/resources.c src/engine/resource_decoder.c \
    src/engine/sprites.c src/libs/vga.c src/engine/tiles.c \
    src/engine/tile_blitters.c src/engine/music.c -o build/check_bonus_assets
build/check_bonus_assets
```

Create `build/` first if it does not exist.

The executable also accepts `--bonus-check`: it loads the stage resources and
checks the map palette/layer, sprite frames, both music tracks and both effects.
It reports success or errors in `LIONKING.LOG`, then exits; it does not start a
bonus game. The host test
`tmp/tools/check_bonus_entry.c` covers this entry point and missing/corrupt archive
failures. Compile it using the source list in the
[frontend test instructions](./02-main-menu-and-loading-screen.md), replacing
`tmp/tools/check_frontend.c` with `tmp/tools/check_bonus_entry.c`, adding `-Itmp/tools`,
and run it normally, with `--missing`, and with `--corrupt`.

To play BUG TOSS directly, run `bash build.sh --bug-toss` from the project
root. This builds and boots a temporary DOS64 image that starts the round
automatically. Alternatively, run `LIONKING.EXE --bug-toss` from the directory
containing `LIONKING.EPF`. The standalone round starts with the normal
difficulty's three lives and one continue, and returns to the DOS64 shell
when the round ends or Escape is pressed; it does not start LEVEL2.

The stage runner draws map layer 5 as the background, then layer 4 around
the object passes, using the original 8-pixel vertical viewport. It uses
the verified sprite banks and the normal logic clock/audio mixer. Timon starts
at the stage's marker `(160, 48)`, moves at five pixels per logic tick,
turns at X=64/256 and drops objects from his position. The scheduler uses the
original counter starting at -120, the recovered type and interval tables,
and the separate special-throw timer starting at 500. The latter starts a
45-tick animation and throws a reward at Y+16 when its counter reaches 30.
The normal interval uses a separate count of catches since the last speed
change; at 20 catches the speed changes and the spawn counter resets.
The rare type-3 override also uses this interval counter, not the separate
total caught count (`0x24bbe`).
Timon waits 13 ticks at startup and after a special throw, and 14 ticks on a
turn, before advancing horizontally. Ordinary movement phases restart without
the 13-tick delay; his throw counter continues advancing during those waits.
During movement, his height follows the `BONUS.MAP` layer 4 ground contours
from `CONTOUR.CON`, matching the original ground probe at `0xa6ff`; unsupported
positions use its fixed-point gravity. Dropped items inherit his adjusted height.
At each new movement phase the original chooses a random turn with probability
1/4; this can produce closely spaced reversals. The turn script advances once
when the turn starts, before the next regular animation update. At a boundary
the facing changes before that first update, while a random turn changes it
afterwards, matching `0x24827` and `0x24869`.
His special throw also resets that counter while Pumbaa's burp pauses the
stage, and completes its zero-count transition on the following tick.

The original stage initialization at `0x4322` and draw routine at `0x44ca`
skip the standard level HUD when the stage number is 11 or higher. Thus BUG
TOSS has no normal health/roar bars during play; the port intentionally does
not add an invented overlay.

The result transition at `0x80b0`/`0x80e8` uses the `TITLES.MAP` palette
and a black background, with `COLLECT.MCH` and two `NUMBERS.MCH` sprites.
The displayed catch count is capped at 99, begins counting after 50 logic
ticks and then increments once per tick; the two-channel `BURP` effect is
played during counting for totals above 20. The countdown holds while the
number increases. Escape skips the result screen.

This is a playable reconstruction, not a fully verified reproduction of every
BUG TOSS rule. The original item
out-of-bounds test at `0xa743`/`0x583d` uses the viewport object bounds rather
than a floor-contour probe; for this fixed scene the port checks the recovered
rectangle X=-15..319, Y=1..208. Catch detection takes precedence. Ordinary
items outside the rectangle end the round, whereas hazards are removed
without ending it. The selector receives the actual maximum roar on entry;
a roar reward adds eight and its updated maximum is carried into LEVEL2,
as are lives and continues. The remaining in-level end-state path at
`0x243f9`/`0x24460` is not fully simulated; the port transitions directly
to the separate result screen. See the
[LEVEL1-to-LEVEL2 transition](./30-level-transition.md) notes for remaining
Level 2 limitations.

The host `check_bonus_entry --game` test compares the background composition
and checks that Pumbaa and Timon are visible. It also checks measured trunk
heights from the real map, movement in both directions, a turn, and normal and
special drop heights; `--game-complete` also
checks that falling items appear and compares the first result frame. The
item test checks result-clock thresholds, counts and duration separately.

The original fall routine at `0x24dcf` accelerates before integrating 16.16
position and caps downward speed at seven pixels per logic tick. Its kind 0
bug starts at `0xb000` with acceleration `0x1e00`; kinds 1 and 2 use
`0x3800`/`0x1c00` and `0x1000`/`0x600`, respectively. The port uses the
same values and nominal logic clock. Starting at the initial velocity,
covering 160 pixels takes 47, 52 and 114 updates respectively; collision can
end the visible fall earlier. The item test checks fixed-point positions
and these travel times for all three bug kinds.

## Interactive asset view

Start the built executable with `--bonus-view`, with `LIONKING.EPF` in its
working directory. This is a research tool, not a playable bonus stage: it
draws a selected MAP layer and places a selected sprite at a fixed
diagnostic position, not a verified original scene.

- `1`, `2`, `3`: select Timon, Pumbaa or bug sprite bank.
- Left/Right: step through that bank's frames, wrapping at either end.
- Space: toggle a 10-frames-per-second sequential animation preview. This is
  an inspection aid, not a reconstruction of the original animation scripts.
- `P`: toggle a separate BUG TOSS movement inspection. Hold the configured
  left/right controls to move Pumbaa using the original movement and animation
  scripts; jump, slash or roar triggers his one-use burp, including the original
  effect and animation. `P` returns to the sprite viewer. The selected map
  layer remains an arbitrary diagnostic background, not a verified stage
  composition; the diagnostic uses a fixed random seed.
- `4`–`9`: select one of the six populated map layers, resetting the camera.
  WASD moves the camera in 32-pixel steps, bounded by the selected layer.
- `H`/`T`: play `BUGHUNT.AMF`/`BUGTOSS.AMF`; `M` stops playback.
- Escape exits. Audio is opened only when a track is requested; errors are
  reported in `LIONKING.LOG`.

The six MAP layer descriptors have dimensions 80×194, 64×28, 200×52,
120×82, 40×26 and 40×26 tiles, respectively, with 8×8 pixels per tile.
The viewer displays one layer at a time; it does not establish how the
original game combined those layers or used the map.

The host entry test also accepts `--action`, `--action-audio-failure`,
`--action-stream-failure`, `--movement`, `--preview`, `--audio-failure`,
`--stream-failure`, `--audio-escape`, `--heap-missing`, `--alloc-failure`,
`--free-failure`, `--inspect`, and `--clock-failure` to cover pixel output,
all six map layers, bounded camera movement, timed animation, track switching,
failure reporting and audio/heap cleanup.

The movement controller translates the normal movement branch at `0x2414b`,
including the starting position `(100, 214)`, six-pixel steps, directional
gates, simultaneous inputs and nine-tick turnaround delay. It runs the
original animation programs at DS `0x4c86`, `0x4c94`, `0x4ca2`, and `0x4cb0`
against Pumbaa's original sprite bank. The action at `0x242d7` uses the
original `0x4c6a` animation, `BURP` sound, 56-tick countdown and random shake
window. The last shake value remains until the action ends, as in `0x2432d`.
It sets the stage signal to 0 while running, then 2 for one update
before returning it to 1. The viewer uses the existing game clock and sound
setting, but there are no objects to respond to that signal in the viewer or
inspection mode. The gameplay stage now drives the items with that stage signal.

The engine reconstructs the individual item behavior at
`0x248b4` and `0x2491f`: original item graphics definitions, randomized bug
frame, type-dependent initial velocity and fixed-point gravity, collision
precedence over floor contact, and pause/clear stage signals. The caller must
supply spawn coordinates and real floor collision. The original selector at
`0x24af4`–`0x24ce8` and interval calculation at `0x24e9c` are also available
as separate engine functions, including the hazard thresholds, reward limits
and spawn timer. The stage runner drives those functions, applies caught
rewards and failure results, and performs object cleanup on finish.

The movement controller can also be tested independently after extracting the
animation data:

```bash
mkdir -p build
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -g -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -fno-omit-frame-pointer -Iinclude -Isrc \
    tmp/tools/check_bonus_toss.c src/engine/bonus_toss.c src/engine/animation.c \
    src/engine/render.c src/engine/sprites.c build/animation_data.c \
    -o build/check_bonus_toss
build/check_bonus_toss

cc -O2 -g -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -fno-omit-frame-pointer -Iinclude -Isrc \
    tmp/tools/check_bonus_toss_item.c src/engine/bonus_toss_item.c \
    src/engine/bonus_toss_stage.c src/engine/bonus_toss.c \
    src/engine/animation.c src/engine/render.c \
    src/engine/physics.c src/engine/sprites.c build/animation_data.c \
    -o build/check_bonus_toss_item
build/check_bonus_toss_item
```

The [game overview](https://en.wikipedia.org/wiki/The_Lion_King_(video_game))
describes Pumbaa catching falling items until one falls or he eats a bad bug,
and Timon collecting bugs under a time limit while avoiding spiders, with
rewards every ten bugs. It does not specify enough detail to implement the
original timing, item distribution, controls, reward mapping or selection
order. These descriptions are not evidence that the current port implements
either game.
