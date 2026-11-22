# LEVEL1 music in map mode

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### LEVEL1 music in map mode

`LIONKING.EXE --map` now plays the original `LION1.AMF` from
`LIONKING.EPF`. This is DSMI AMF 1.4 tracker music, not MIDI: its four
channels use ten nonempty unsigned 8-bit PCM samples. No HEXEN
instrument bank or OPL synthesis is involved; the unused OPL import
has been removed.

The native player in `src/engine/music.c` handles both LION1 and LION2
(31 instrument slots, up to 32 orders, 60 tracks, 64 rows). It supports
instrument/note/volume events, volume slides, vibrato with parameter
memory, combined vibrato/volume slides, pattern breaks, tempo changes,
and the Level 2 portamento effects. The opening
LION1 row changes tempo from 125 to 165. Level 2 music is validated for
eight seconds of non-silent output; its portamento timing is a native
approximation, not a bit-exact recreation.
Playback uses fixed-point sample positions, original sample loops and
AMF stereo panning, and loops the song. This is a focused player for the
migrated levels and title, not a general AMF implementation or a bit-exact
recreation of the old sound-card mixer.

Output is signed 16-bit stereo at 44100 Hz through `DOS64_API.Audio`.
About 100 ms is queued cooperatively; partial/zero writes retain pending
frames instead of dropping music. Exit and error paths stop the stream.
Missing audio capability, invalid module data and streaming failures
are reported explicitly in `LIONKING.LOG`; map mode requires usable
audio rather than silently starting without the requested music.
Other preview modes remain unchanged and silent.

Focused validation:

```
mkdir -p build
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
  tools/check_music.c src/engine/music.c src/engine/assets.c src/engine/animation.c \
  src/engine/resources.c src/engine/resource_decoder.c build/animation_data.c \
  -o build/check_music
build/check_music
```

The check covers non-silent stereo, row timing, both full song loops,
chunk-invariant synthesis, truncated/invalid data, partial output writes
and stopping. Independent libopenmpt inspection reports a duration of
81.424 seconds; the native player crosses the song boundary during the
82nd one-second test block. Address/undefined-behavior sanitizer checks
pass. A native DOS64 HDA capture contains over three million nonzero
samples while map movement/jumping continues; Escape exits with zero.
Host checks that link `src/dos64/start.c` now also need
`src/engine/music.c`; the normal build already includes it.
