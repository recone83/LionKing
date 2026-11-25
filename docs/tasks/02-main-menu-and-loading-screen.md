# Main menu and loading screen

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Main menu and loading screen

Launching without arguments shows the original Disney/Virgin and East
Point Software screens from layers 0 and 2 of `CREDITS.MAP`, each for
210 IRQ ticks or until a key is pressed, then opens a basic menu.
The menu composes both original `TITLES.MAP` layers (sky before rock),
the `TITLE_S.MCH` logo at its recovered X44/Y17 position, `F8X8_S.MCH`
font and `SUN.MCH` selection marker. No replacement logo or font is drawn.
The SUN selector now follows the original horizontal oscillation from
`0x2730`: ten one-pixel steps, a direction-change tick, then ten steps back.
It follows the currently selected row and uses the original logic clock.
The main menu uses the original two entries and the four-line footer from
the original data, positioned at X32/Y168 with the original 8-pixel font.
The options screen contains the original five setting categories.

- Up/Down selects **START** or **OPTIONS**, wrapping at either end.
  Enter or Space activates the selection. OPTIONS contains difficulty,
  independent MUSIC and SOUND EFFECTS switches, REDEFINE KEYS and EXIT.
  Escape returns from OPTIONS; Escape on the main menu returns to the launcher.
  REDEFINE KEYS prompts for up, down, left, right, jump, adult slash, roar
  and adult maul in the original order. Their default bindings correspond to
  the original DOS key table at DS `0x2b0a`.
  Duplicate bindings are rejected, Escape cancels the entire change, and
  Enter is reserved for menu confirmation. Rebinding affects LEVEL1 controls;
  the two adult attack bindings are recorded but cannot yet be used because
  adult Simba gameplay is not ported. Menu and continue-screen navigation
  retain their fixed keys.
  The key screen follows the original DS `0x2b36` layout: a header at
  X80/Y72 and progressively displayed rows with their current assignments.
  For keys without a recovered four-character label, `HI` and the two
  hexadecimal HID digits are displayed. Escape cancellation and the
  duplicate-key warning are native usability additions.
- The startup Rafiki/baby-Simba animation plays after the logos, before
  the menu. The original manual-word/password screen is deliberately omitted.
- Start plays the separate original Timon intro before loading LEVEL1 at
  its original start position, on every new game.
  The sequence is **logos → baby-Simba intro → menu → Start Game → Timon intro → LEVEL1 + level name**.
  The loading display remains blank between resource groups. After initialization,
  the original `LEVELS.MCH` frame 0 ("The Pridelands") overlays the map for
  the first 100 gameplay ticks. Input, movement, enemies and audio run
  underneath it; there is no separate 100-tick black-screen hold.
- Original `TITLE.AMF` begins on the Disney/Virgin splash and continues
  through East Point, the baby-Simba intro and the menu without restarting.
  It stops before the Timon scene, whose speech has a separate PCM stream.
  Title playback primes a 250 ms queue and refills before and after drawing
  to tolerate slower QEMU presentations. Gameplay and speech retain their
  100 ms queues, preserving responsive sound effects. A draining-ring test
  covers 1000 consecutive 170 ms presentation delays without title underruns.
  Title/menu music uses linear sample interpolation rather than repeated
  nearest samples; gameplay music and PCM effects keep their existing
  sampling. Tests cover exact fractional values at sample loops and ends,
  unchanged timing and chunk-invariant output. On the opening second of
  the real title song at corrected pitch this reduces squared adjacent-sample
  steps by 71%; this is a resampling measurement, not a claim of 71% better sound.
  Title sample rates are calibrated to DSMI C5, correcting the previous
  octave-too-high/double-speed playback. The 31492-byte sample now remains
  active past two seconds instead of ending prematurely. LEVEL1 keeps its
  previous calibration so this title fix does not alter gameplay audio.
- Music selection controls title music immediately and AMF music in gameplay
  and continue screens. Sound effects separately control gameplay effects and
  character speech. With music disabled but effects enabled, gameplay uses the
  effects-only mixer. With both disabled, gameplay does not require an audio
  device. Settings survive returns to the menu but are not saved to disk.
- Escape during gameplay returns to the menu. GAME OVER, or defeating the
  final hyena, also returns after the scene finishes. Audio is stopped
  before returning, and a new game initializes fresh level state.
- Victory now plays the original separate Rafiki reward scene, not the
  baby-Simba startup intro or Timon pre-game scene. It uses both `TITLES.MAP`
  layers without the menu logo, `RWDLVL1.MCH` slot 80, and the two original
  scripts at DS `0x130f0`/`0x13125`, with owners X142/Y163 and X142/Y162.
  `SPEECH1` starts on both PCM channels at logic tick 19; the script finishes
  at tick 475. Escape skips it, and menu mute also mutes its speech.
  The gameplay audio stream closes before reward speech opens.
- Escape in the main menu returns to the launcher.

`--map` still enters LEVEL1 directly; `--preview` preserves the previous
automatic locomotion demonstration. Other diagnostic arguments retain
their existing behavior. Missing or invalid title/level resources fail
explicitly rather than falling back to a fake successful loading screen.

The actual-entry sanitizer test
[check_frontend.c](../../tmp/tools/check_frontend.c) exercises original title assets,
menu wrapping, independent music/effects mute, key remapping and cancellation,
blank loading presentations and original level-title overlays across two starts,
startup-intro-before-menu ordering, distinct Timon intro on both starts,
the 100-tick level-name overlay during moving gameplay,
Escape return, three real-contact deaths/two
restarts/GAME OVER return, audio reopening/cleanup, exit and missing-resource
failure. Build it with the native source list from [build.sh](../../build.sh),
substituting the host compiler and `tmp/tools/check_frontend.c` for SDK startup:

```bash
mkdir -p build
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -fno-omit-frame-pointer -Iinclude -Isrc \
    -Itmp/tools tmp/tools/check_frontend.c src/start.c src/dos64/preview_idle.c \
    src/dos64/preview_player.c src/dos64/preview_background.c src/dos64/preview_bonus.c \
    src/dos64/preview_emitter.c src/dos64/platform.c src/dos64/frontend.c \
    src/engine/resources.c src/engine/resource_decoder.c src/engine/sprites.c \
    src/libs/vga.c src/engine/tile_blitters.c src/engine/tiles.c src/engine/timing.c \
    src/engine/objects.c src/engine/input.c src/engine/render.c src/engine/assets.c \
    src/engine/animation.c src/engine/physics.c src/engine/behaviors.c \
    src/engine/music.c src/engine/bonus.c src/engine/bonus_toss.c \
    src/engine/bonus_toss_item.c src/engine/bonus_toss_stage.c \
    src/engine/enemies.c src/engine/pickups.c src/engine/ostrich_visual.c \
    src/engine/ostrich_route.c src/engine/ostrich_obstacle.c \
    src/engine/ostrich_sequence.c src/engine/ostrich_ride.c \
    src/engine/lifecycle.c src/engine/hud.c build/animation_data.c \
    -o build/check_frontend_san
build/check_frontend_san
build/check_frontend_san --skip-splash
build/check_frontend_san --rebind
build/check_frontend_san --rebind-alias
```

Both publisher screens are compared against every original indexed pixel;
the complete menu and footer, options, sky/rock/logo composition, intro frames and original level-title
artwork are also checked pixel-for-pixel. The intro uses original DS table
`0x30a0` and parts `0xbd60` onwards: 120 ticks of the original changing
poses followed by a 240-tick hold, skippable during the hold. Its graphics
and timing are restored. Tests compare every submitted title-music sample,
including playback on the first splash and through the intro/menu, exercise
mute/reopening and ensure streams never overlap. The original selector
motion is also compared pixel-for-pixel across its full oscillation.
The rebinding tests cover all eight prompts, duplicate rejection and
cancellation, remapped movement and roar, and prevent right Control from
also roaring when assigned to another action.

[check_victory.c](../../tmp/tools/check_victory.c) tests the actual adapter's victory
transition separately. Build with the same host source list above, replacing
`tmp/tools/check_frontend.c` with `tmp/tools/check_victory.c`, adding
`-Wl,--wrap=resources_load_entry -Wl,--wrap=engine_enemies_tick
-Wl,--wrap=engine_pickups_tick -Wl,--wrap=run_bonus_toss_game
-Wl,--wrap=start_level_two -Wl,--wrap=frontend_loading_for_level
-Wl,--wrap=frontend_level_palette -Wl,--wrap=render_follow_camera
-Wl,--wrap=engine_ostrich_ride_camera -Wl,--wrap=engine_ostrich_ride_release
-Wl,--wrap=render_map_tile_pass_ostrich -Wl,--wrap=render_map_background_scrolled`, and choosing
`build/check_victory_san` as output.
The wrapper runs the real enemy update but injects a nonzero boss-death counter
at tick 60; this tests controller wiring, not a keyboard-driven boss victory.
The real two-hit fight and death-animation completion are covered by the
enemy test. Run:

```bash
build/check_victory_san
build/check_victory_san --menu
build/check_victory_san --menu-level2
build/check_victory_san --level2-fall
build/check_victory_san --level2-log
build/check_victory_san --level2-ride-full-first
build/check_victory_san --level2-ride-full-second
build/check_victory_san --level2-ride-hint-escape
build/check_victory_san --level2-ride-jump-input
build/check_victory_san --skip
build/check_victory_san --muted
build/check_victory_san --missing
build/check_victory_san --audio-failure
build/check_victory_san --bonus
build/check_victory_san --bonus-escape
```

The reward fixture compares every rendered pixel against an independent
frame-duration table and original assets, all 22 reward frames, tick-19
speech, tick-475 completion and exact two-channel speech PCM. It verifies
direct-map and menu-start victory paths, return to menu, skip/mute, explicit
resource/audio failure, closed logs and nonoverlapping audio ownership.
The bonus tests place Simba on the real type-41 marker using the pickup wrapper,
then verify the bonus-round entry runs after the real victory transition, and
that Escape from BUG TOSS returns to the menu without starting Level 2.
Restart persistence is tested separately by `check_pickups`.
The pre-game intro follows code `0x4711`/`0x47b2`, with
`1TIMONS.MCH` at owner X160/Y160 and the original script at DS `0x5435`.
It lasts 130 logic ticks: the first 30 retain the initial pose, then the
22 original animation frames run. `SPEECH5` starts on both PCM channels
when the remaining counter reaches 80; the menu sound setting also mutes
this speech. Effect-only output reuses the existing mixer without loading
an AMF song and is closed before LEVEL1 opens its own audio stream.
The bounded AMF reader supports the verified `TITLE.AMF` shape (31 instrument
slots, 5 orders, 20 tracks) as well as `LION1.AMF` (31/15/60), including
TITLE's instrument-without-note-retrigger marker. The title song loops
after approximately 59 seconds with the original tempo changes.
Independent libopenmpt inspection reports 58.520 seconds for the original
title module. This validates the song structure, not bit-exact equivalence
to the original sound-card mixer.
An independent pattern comparison also matches all 333 notes and 219
instrument selections over the title's 1280 channel rows. This checks for
missing decoded parts, not full mixer equivalence to a video recording.
An isolated native QEMU run confirmed the corrected title menu, starting
LEVEL1, returning to the menu and exiting with code zero; the closed log
recorded both publisher screens and successful audio/scene startup.
Every presentation clears the entire DOS64 surface to opaque black, then
draws the integer-scaled 320x200 image in the center. The letterbox areas
therefore never expose the DOS console; the tests verify the clear color and
scaled image without changing game pixels.
Gameplay displays a compact white 3x5-font FPS counter with no background
box in the bottom-right of the HUD, inset four game pixels from the image
edges. It uses completed presentations over the
actual elapsed monotonic time and refreshes once per second; `FPS: --` is
shown until the first sample. Menus and cutscenes do not show the counter,
and returning to gameplay starts a fresh measurement. It does not change
the fixed gameplay logic clock.

Gameplay also accumulates frame-stage timings and writes a summary to
`LIONKING.LOG` when the game exits cleanly. The report lists average
microseconds per presented gameplay frame and peak microseconds per call for
input polling, audio streaming, scene rendering, palette conversion, screen
clearing, image drawing (including the FPS overlay), presentation, game logic,
and sleep. No profiling log writes occur inside the frame loop. Menus and
cutscenes are excluded. The stages do not include every bookkeeping operation,
so their sum is not an exact total frame time.
Gameplay, menus, and cutscenes do not explicitly sleep or busy-wait to cap
rendering. Game logic and animations still advance from elapsed monotonic
time, independently of render FPS. Rendering runs as fast as the runtime
allows; this can increase CPU usage. The sleep profile stage remains available
but should report zero during normal gameplay.
The supplied QEMU launcher uses software CPU emulation (`-accel tcg`), which
can limit FPS independently of rendering cost.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -Iinclude -Isrc tmp/tools/check_fps.c src/dos64/platform.c -o build/check_fps
build/check_fps
```

The original exported bodies remain in the non-native branch as reference;
the playable build uses the native engine and DOS64 platform modules. Run the
executable from a directory containing `LIONKING.EPF`.
