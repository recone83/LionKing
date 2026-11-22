# Bonus games: asset compatibility

The bonus games are not implemented or connected to level completion. The
selection rules, game mechanics and rewards still need to be established.
The existing pickup code records a bonus counter and flag, but neither starts
a bonus game.

The shared bonus asset loader reads the map, three sprite banks and both
music tracks through the existing EPF reader. Its fixed decoded buffer sizes
match the archive examined here; a resource exceeding those sizes is rejected,
not truncated. Failed loads clear the `loaded` flag and may be retried.
The application allocates the approximately 461 KiB bonus asset structure on
the API 16 heap only when a bonus diagnostic starts. It stops audio before
releasing it, including on failure. Missing heap support, allocation failure,
and release failure are logged and result in an error. The loader itself
continues to use caller-owned storage; the buffer sizes are still fixed.

The host-side `tools/check_bonus_assets.c` diagnostic compares the loader's
output with independent EPF reads, exercises errors and retries, verifies the bonus map
palette and layer 0, renders every frame of the selected sprite banks, and
checks the two music tracks against the existing AMF player.

Results with the current archive:

- `BONUS.MAP`: 364,360 decoded bytes; palette and layer 0 render successfully.
- `TMBUGTOS.MCH`, `PUMBAA.MCH`, `BUGS.MCH`: 17, 22 and 20 frames respectively
  render successfully.
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
    -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_bonus_assets.c src/engine/bonus.c src/engine/resources.c src/engine/resource_decoder.c \
    src/engine/sprites.c src/libs/vga.c src/engine/tiles.c \
    src/engine/tile_blitters.c src/engine/music.c -o build/check_bonus_assets
build/check_bonus_assets
```

Create `build/` first if it does not exist.

The executable also accepts `--bonus-check`: it loads the six resources and
checks the map palette and first layer, the first frame from each sprite bank,
and initialization of both music tracks. It reports success or errors in
`LIONKING.LOG`, then exits; it does not start a bonus game. The host test
`tools/check_bonus_entry.c` covers this entry point and missing/corrupt archive
failures. Compile it using the source list in the
[frontend test instructions](02-main-menu-and-loading-screen.md), replacing
`tools/check_frontend.c` with `tools/check_bonus_entry.c`, adding `-Itools`,
and run it normally, with `--missing`, and with `--corrupt`.

Next steps are to establish bonus selection, rules and state transfer before
connecting either minigame to the level transition.

## Interactive asset view

Start the built executable with `--bonus-view`, with `LIONKING.EPF` in its
working directory. This is a research tool, not a playable bonus stage: it
draws a selected MAP layer and places a selected sprite at a fixed
diagnostic position, not a verified original scene.

- `1`, `2`, `3`: select Timon, Pumbaa or bug sprite bank.
- Left/Right: step through that bank's frames, wrapping at either end.
- Space: toggle a 10-frames-per-second sequential animation preview. This is
  an inspection aid, not a reconstruction of the original animation scripts.
- `4`–`9`: select one of the six populated map layers, resetting the camera.
  WASD moves the camera in 32-pixel steps, bounded by the selected layer.
- `H`/`T`: play `BUGHUNT.AMF`/`BUGTOSS.AMF`; `M` stops playback.
- Escape exits. Audio is opened only when a track is requested; errors are
  reported in `LIONKING.LOG`.

The six MAP layer descriptors have dimensions 80×194, 64×28, 200×52,
120×82, 40×26 and 40×26 tiles, respectively, with 8×8 pixels per tile.
The viewer displays one layer at a time; it does not establish how the
original game combined those layers or used the map.

The host entry test also accepts `--preview`, `--audio-failure`,
`--stream-failure`, `--audio-escape`, `--heap-missing`, `--alloc-failure`,
`--free-failure`, `--inspect`, and `--clock-failure` to cover pixel output,
all six map layers, bounded camera movement, timed animation, track switching,
failure reporting and audio/heap cleanup.

The [game overview](https://en.wikipedia.org/wiki/The_Lion_King_(video_game))
describes Pumbaa catching falling items until one falls or he eats a bad bug,
and Timon collecting bugs under a time limit while avoiding spiders, with
rewards every ten bugs. It does not specify enough detail to implement the
original timing, item distribution, controls, reward mapping or selection
order. These descriptions are not evidence that the current port implements
either game.
