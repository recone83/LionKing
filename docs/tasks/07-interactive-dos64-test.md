# Interactive DOS64 test

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Interactive DOS64 test

The native visual animation stream implements the verified handler at
`0x1630b`, called by the original script interpreter `0x162c0`.
Duration N holds a descriptor for N+1 updates. Controls toggle flips, set
the script state, add signed X/Y offsets with 16-bit wrap, invoke explicitly
supplied event callbacks or follow checked DS-address jumps. Invalid pointers,
missing event handlers and control-only cycles return errors. This is the
visual substream, not the entire behavior/script interpreter.

The native outer script executor now preserves the original idle path from
DS `0x5f84`, rather than having the preview call the visual substream directly.
It dispatches original handler IDs for visual/motion initialization and stepping,
yield and signed relative jumps. Yield stores the next script address exactly
as `0x162df` does; `0x64d4` branches from its operand address, not after it.
The supported commands can interleave visual and motion streams. Unknown
handlers are explicit errors and retain the handler ID for inspection;
no original 32-bit code address is invoked as a native pointer.
This is the complete idle outer loop, not all opcodes of the game's interpreter.
Game-event side effects still remain diagnostic in the preview.

```bash
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_program.c build/animation_data.c src/engine/animation.c \
    src/engine/render.c src/engine/sprites.c -o build/check_program
build/check_program
```

```bash
cc -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_animation.c src/engine/animation.c src/engine/render.c \
    src/engine/sprites.c -o build/check_animation
build/check_animation
```

The neighboring motion substream at `0x163ce` is now migrated too.
Each four-byte record holds duration, signed X byte and a Y word. Movement
is applied immediately and on each of the next N updates. A high duration
bit mirrors X according to the live facing flag; `0xff` introduces an
absolute DS-address jump instead. Coordinates wrap exactly as 16-bit words.
It uses the same checked data-address resolver, without native calls to
original code addresses. It is not yet connected to gameplay behaviors;
the idle preview is intentionally unchanged rather than given invented motion.

```bash
cc -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_motion.c src/engine/animation.c src/engine/render.c \
    src/engine/sprites.c -o build/check_motion
build/check_motion
```

The movement test also reads the untouched original stream at DS `0x329c`,
selected by script handler `0x163bc` at DS `0x3252`. It checks the original
-4/-3/-2 opening and repeating -1 record for 1000 updates in each direction,
in addition to 2550 synthetic boundary cases.

The original idle visual sequence starts at DS `0x6531`, referenced by script
DS `0x5f84` through handler `0x162fc`. It contains 307 timed descriptors,
six callback commands and an absolute loop at `0x6b4e`. Its descriptors use
original MCH slots 14, 15 and 16 (`SYIDLE1`, `SYIDLE2`, `SYIDLE3`).
Build-time extraction embeds the untouched DS range `0x6531..0x8048`,
including descriptor anchors and metadata, with no pointer relocation casts.
The generator verifies the complete original dump SHA-256 before extracting.
The original dump remains required at build time, not at DOS64 runtime.

```bash
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_idle.c build/animation_data.c src/engine/animation.c \
    src/engine/render.c src/engine/sprites.c -o build/check_idle
build/check_idle
```

The native asset-list reader follows binary `0x11400`: a starting slot word,
a count word, then eight-byte space-padded names with `.MCH` appended.
The original young Simba list at DS `0x744c` is retained byte-for-byte: 28
banks assigned to slots 6 through 33. The host check compares the compiled
list directly to the untouched data dump. Invalid lists report failure;
the legacy full level bundle/sample loader remains unported.

```bash
cc -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_assets.c src/engine/assets.c src/engine/resources.c \
    src/engine/resource_decoder.c -o build/check_assets
build/check_assets
```

The native palette transition preserves default settings at DS `0xa60`:
one phase per PIT tick, no interval delay, all 256 colors. Binary `0x105cb`
snapshots the source/target palettes; `0x1062b` interpolates with signed
integer multiplication and division by 64, completing as soon as every
component matches. Interrupting a fade starts from the current palette.
No old timer interrupt or VGA port access is retained. Nondefault range/speed
settings are not yet exposed by this native interface.

The shared monotonic clock now also exposes the full elapsed PIT tick count.
Palette service uses those ticks, as verified by IRQ handler `0x108b4`;
it must not use the gameplay dispatcher's half-rate updates or byte-wrapped
accumulator. Both paths retain the same fractional PIT phase calculation,
using separate clock instances when serviced independently.

```bash
cc -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_fade.c src/libs/vga.c -o build/check_fade
build/check_fade
```

Run `./build.sh` to build and launch the updated sample in QEMU. It now uses
the native input masks, render-node pool, multipart sprite pass and migrated
`vga_present_frame`, rather than drawing the sprite directly once.

| Key | Diagnostic action |
|-----|-------------------|
| Up / Down | Previous / next of the 28 original young Simba sprite banks |
| Left / Right | Previous / next frame of the selected bank, wrapping |
| Left Alt | Toggle horizontal flip |
| Left Ctrl | Toggle vertical flip |
| Left Shift | Hide / show the sprite using its original visibility flag |
| A | Switch between the running original idle sequence and manual browsing |
| F | Original integer palette fade to black / back; can interrupt a fade |
| Space | Reset frame, flips, visibility and palette |
| Escape | Exit |

Actions trigger on presses, not repeatedly while a key is held. This is an
interactive **asset test**, not invented gameplay or a replacement animation
script. The background remains the limited layer-zero preview.
The initial bank is `SYIDLE1.MCH` (24 frames), in its original slot 14.
Bank selection uses the original slot-list names and EPF loader, resets only
the frame, and preserves flips/visibility. Only the selected bank is resident,
in a checked caller buffer; no allocator or original DOS resource pointers
are reused. Bank names are printed when selected. Selecting banks/frames is
diagnostic browsing, not replacement movement or animation logic.

Run `LIONKING.EXE --idle` to start the original idle sequence automatically, without a key
press. Run `LIONKING.EXE --manual` from the DOS64 shell to start with static
bank/frame browsing instead. A switches between the two modes.

Animation mode loads the three original idle banks simultaneously and runs the original
307-record visual sequence, using its real durations, descriptor anchors and
bank changes, at the existing gameplay update rate. It is not a synthetic
frame-number loop. Bank/frame arrow browsing is disabled in this mode;
A again returns to the previously selected manual bank, and Space stops the
sequence and resets the preview. Flips, hide/show and palette fades remain
available in either mode.

This is explicitly a **visual-substream test**, not full gameplay animation.
The six original callback commands include game-object spawning and a game
flag update (verified at code `0x30bec`, `0x30c70`, `0x30d55`, `0x30cf4`).
The diagnostic mode records and reports these known events instead of
executing their unported game side effects; unknown targets are errors.
Their original pointer values are not called as native function pointers.
F is a diagnostic command, not a new gameplay binding. It calls the migrated
palette transition at the original PIT rate, about 101 ticks per second,
independent of gameplay updates. A full transition takes at most 65 serviced
ticks (phase zero through 64); fade-to-black can finish earlier due to the
original signed rounding. It does not install an IRQ driver.

The VGA wrapper preserves the original source row `((camera_y + 1) & 7) * 320`,
64000-byte visible area and reset of the low camera word after presentation.
It sends indexed pixels to the DOS64 adapter instead of VGA memory and rejects
short buffers or a failed presentation sink without resetting camera state.
The sample renders into the appropriate shifted buffer window.

```bash
cc -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_vga_present.c src/libs/vga.c -o build/check_vga_present
build/check_vga_present
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_viewer.c build/animation_data.c src/start.c src/dos64/platform.c \
    src/dos64/frontend.c \
    src/engine/resources.c src/engine/resource_decoder.c src/engine/sprites.c \
    src/engine/tiles.c src/engine/tile_blitters.c src/engine/timing.c \
    src/engine/input.c src/engine/render.c src/engine/assets.c \
    src/engine/animation.c src/engine/objects.c src/engine/physics.c \
    src/engine/behaviors.c src/engine/music.c src/engine/bonus.c src/engine/enemies.c \
    src/engine/pickups.c src/engine/lifecycle.c src/engine/hud.c src/libs/vga.c \
    -o build/check_viewer
build/check_viewer
build/check_viewer --automatic
```

The end-to-end host test runs the actual DOS64 entry with the real EPF and mocked
runtime services. It verifies every output pixel through frame changes, held
keys, flips, hiding, reset, timed fades and interrupted fades, and Escape. The presentation test checks all 65536
It loads all 28 original banks through the actual entry, checks bank wrap
and held keys, then runs more than two original idle loops against an independent
trace of the original data. In total it compares 280512000 ARGB pixels,
including manual-mode return and the reported diagnostic event counts. The presentation test checks all 65536
The `--automatic` host check tests the `--idle` entry without pressing A or
any frame key: 20 descriptor changes and 12864000 verified pixels. Real QEMU
was also tested without animation-key input; successive one-second captures
changed 4356, 990 and 747 viewport pixels, and Escape exited with code zero. The presentation test checks all 65536
camera words. The real PE sample was also booted in headless QEMU: Right
changed 3150 viewport pixels, Shift removed the sprite (5787 changed pixels),
and Escape returned to the DOS64 shell with exit code zero. Host tests verify
the other controls pixel-for-pixel; manual QEMU testing remains useful.
The updated fade sample was also tested in real QEMU: F made all 576000
scaled viewport pixels black; F again restored the viewport byte-for-byte,
including all 5967 previously nonblack pixels. Escape again exited cleanly.
Bank selection was verified in QEMU too: Down loaded `SYIDLE2.MCH`, changing
4797 viewport pixels; Up reloaded `SYIDLE1.MCH` and restored the original
viewport exactly. The sample exited with code zero.
The original idle visual sequence was also verified in real QEMU: A started
automatic timed changes (828 changed viewport pixels across three captures),
reported an original script event, A returned to manual browsing, and Escape
returned to the shell with exit code zero.
