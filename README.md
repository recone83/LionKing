# Lion King: reconstructed code and DOS64 port

This project separates the recovered DOS game code into modules and prepares
it for DOS64. **The DOS64 platform test builds; the game is not playable yet.**
The original export contains invalid C and missing functions. The executable
currently displays a real decoded Simba sprite with the first level's palette,
not gameplay.

## Layout

| Path | Purpose |
|---|---|
| [src/](src/) | Active recovered code, module documentation and manifests |
| [src/pseiudo.c](src/pseiudo.c) | Aggregates modules and shared declarations |
| [src/engine/main.c](src/engine/main.c) | Game initialization reconstructed from machine code |
| [include/](include/) | DOS64 SDK headers |
| [lib/](lib/) | Supplied DOS64 startup object and import library |
| [bin/](bin/) | Original executable, code/data dumps and disassembly evidence |
| [build/](build/) | Generated executables and temporary build products |
| [image/](image/) | Supplied EFI kernel, image creation and QEMU launcher |
| [data/](data/) | Game asset storage; installation is not automated yet |
| [tools/](tools/) | Reconstruction validation tools |
| [pseiudo.c.backup](pseiudo.c.backup) | Immutable original decompiler export |
| [FINDINGS.md](FINDINGS.md) | Reverse-engineering findings |
| [SDK.md](SDK.md) | DOS64 SDK reference, including upstream-specific examples |

Do not delete the original executable or dumps: the executable also retains
loader metadata and relocations absent from the dumps.

## Validation available now

Run from the project root:

```bash
perl tools/split_pseudocode.pl --check
perl tools/check_main.pl
bash -n build.sh image/build-image.sh image/run.sh
```

The first check verifies all 753 exported definitions and global declarations.
The second compares the reconstructed main with the binary and compiles an
isolated C harness using the host `cc`. These checks do not execute the game.

## DOS64 build

```bash
bash build.sh
```

This command compiles, creates a fresh temporary DOS64 image under `build/`
with the executable and game archive, then launches QEMU. Close QEMU before
building again. The temporary image is removed after QEMU exits; existing
images are never modified. To compile without launching, use:

```bash
bash build.sh --build-only
```
The output is `build/lionking.exe`. Input binaries remain in `bin/`.
A failed compilation leaves the last successfully built executable unchanged;
do not mistake an old executable for a successful new build.

The [DOS64 entry](src/dos64/start.c) provides
`int __attribute__((ms_abi)) start(const DOS64_API *Api)`.
The build links only this entry, [platform.c](src/dos64/platform.c) and SDK startup,
not the pseudocode aggregator or legacy DOS drivers. The platform test exercises
indexed 320x200 image conversion to ARGB, integer scaling, input polling and
monotonic time. Escape exits; `--selftest` exits after approximately one second.
It is not yet connected to `game_main`. The existing resource module now has a
native DOS64 branch selected by `LK_DOS64_NATIVE`; it validates the real EPF
header, index and payload bounds through DOS64 filesystem callbacks.
Its original exported bodies remain in the non-native branch for migration,
not in the executable. Memory management, decoding, audio and the actual game
loop remain to be migrated. Run the executable from a directory containing
`LIONKING.EPF`.

The native resource test uses the real supplied archive:

```bash
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_epf.c src/engine/resources.c src/engine/resource_decoder.c \
    src/engine/sprites.c src/libs/vga.c src/engine/tiles.c src/engine/tile_blitters.c \
    -o build/check_epf
build/check_epf
```

The archive has 338 entries (13 raw and 325 dictionary-compressed), totalling
8824931 decoded bytes. The original reader allocates/requests an extra record;
the native branch uses the actual on-disk count and rejects truncated reads.

The native branch of the existing decoder module reconstructs MSB-first codes,
9-to-14-bit widths, width-dependent terminal/reset codes and reset without
returning to 9 bits. The test decodes all 325 compressed entries, requires exact
output sizes, tests truncated input and too-small output, and compares named
resource loads with direct decoding. Enable `-fsanitize=address,undefined` with
the host compiler for memory checks. This validates structure and bounds, not
yet byte-for-byte equivalence with an independently run original decoder.
Caller-owned buffers replace the original DOS allocations; decoder errors
return failure and the resource layer reports diagnostics.

The existing sprite module now has a native branch for MCH frame tables and
run packets, clipped to the 320x200 framebuffer. Bits `0x8000` and `0x2000`
retain the original horizontal/vertical flip coordinates, including the original
width/height anchor convention. The viewer initially shows frame zero of `SYIDLE1.MCH`
and the palette of `LEVEL1.MAP`. This is an asset inspection stage, not a
replacement game loop or a reconstruction of the original opening screen.

MAP palettes are **not CMAP chunks**: code at `0x115c2` takes the first
little-endian dword as an offset to 768 six-bit RGB components. The native
palette reader expands those values for DOS64, without BIOS or DAC port I/O.
The test covers all 2597 MCH frames, both flips and clipping, all 14 MAP palettes,
and exact synthetic pixel-placement checks.

The existing [tile blitter module](src/engine/tile_blitters.c) has a native
`render_blit_tile` implementation shared by opaque and transparent operations.
It preserves 8x8 indexed pixels, zero-pixel transparency, horizontal `0x8000`
and vertical `0x4000` flags, row windows and 320-byte destination rows.
The old six entry points remain only in the reference branch.
Zero-length windows intentionally do nothing; invalid windows fail before writes.

```bash
cc -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_tiles.c src/engine/tile_blitters.c src/engine/tiles.c -o build/check_tiles
build/check_tiles
```

The test compares all destination pixels in 3600 cases with an independent
source-to-destination reference, covering both flips, edge clipping, transparency
and all valid row windows, plus invalid input without destination modifications.

The existing [tile pass module](src/engine/tiles.c) now reads one MAP layer
using its 12-byte dimension/offset record, tile storage offset and little-endian
entries. Tile indices start at 1; zero is empty. The two passes select bit
`0x2000` and use the native transparent blitter. Tests exercise layer zero
of all 14 maps and an exact synthetic two-pass camera-clipping case.
The viewer shows layer zero of LEVEL1 at camera (0,0) behind the sprite.
This is a map preview: parallax, opaque background stage, interleaved object
passes and the gameplay camera are still unported, so it is not a complete
reconstruction of `render_game_scene`.

The existing [timing module](src/engine/timing.c) now derives IRQ-equivalent ticks
from DOS64 monotonic nanoseconds using the nominal PIT ratio `1193182 / 11830`.
It preserves the original byte counter wrap and
`updates = (ticks * 5 + remainder) / 10`, retaining the remainder modulo 10.
Reset clears both clock phases, suitable for the original pause/reset behavior.
Backward time and arithmetic overflow return an error, reported by the caller.
The viewer dispatches after presentation, as in the original gameplay path,
but the callback only counts updates: object simulation is not wired yet.
The PIT frequency is the nominal model, not a measured guarantee of the original hardware.

```bash
cc -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_timing.c src/engine/timing.c -o build/check_timing
build/check_timing
```

The existing [object module](src/engine/objects.c) now implements the pool
confirmed at `0x18350`, `0x183b5` and `0x183ee`: 96 entries, append-to-tail
acquisition and push-to-front recycling. Each object retains 116 bytes of game
data; list pointers and behavior pointers are native, so the old 128-byte binary
stride is deliberately not used in memory. Pool exhaustion still returns null.
Invalid releases return failure; future gameplay callers must report that error.
The native dispatcher now follows `0x14f50`: increments the 16-bit update
counter, reads controls, calls behavior entries, tracks the current-object
pointer and recycles an object when its callback clears that pointer. It
continues with the saved next object after removal. Real gameplay behaviors
remain unported; tests use callbacks only in the host harness.
The viewer does not yet use this pool; this step does not change its image.

```bash
cc -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_objects.c src/engine/objects.c src/engine/input.c -o build/check_objects
build/check_objects
```

Native [input.c](src/engine/input.c) preserves the original eight control bits
and configurable binding table, mapping the dumped defaults to USB HID:
arrows, Space, left Alt, left Ctrl and left Shift. Held/pressed masks retain
the original repeat-mask operation; DOS64 KeyPressed also captures quick taps.
Replay pairs keep the original N+1 update duration with checked boundaries.
Joystick hardware is deliberately not accessed: DOS64 has no supplied joystick
service. The original keyboard threshold belongs to its IRQ driver and is
replaced by HID state, not reimplemented as a delay. The numeric return register
artifact is replaced by explicit held/pressed state and a checked status.
Replay failures must be reported by its caller. The viewer is not gameplay.

```bash
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_input.c src/engine/input.c -o build/check_input
build/check_input
```

The [render orchestration](src/engine/render.c) now preserves the exported
`render_game_scene` and `render_basic_scene` call order with explicit stage
interfaces: viewport, stage one, object pass 0, stage two, object pass 0x80,
overlays and presentation. Levels below 11 use overlays; level 4 skips the
middle overlay. Missing stages and stage errors propagate failure.
These interfaces are not empty replacement implementations: the original
viewport/parallax, object draw callbacks and overlays still need migration.
The asset viewer continues its explicitly limited preview instead of supplying
fake stages to pretend it is the full game renderer. Test callbacks exist only
in the host test. Unported original renderer helpers remain in `render_legacy.inc`.

```bash
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_render.c src/engine/render.c src/engine/sprites.c -o build/check_render
build/check_render
```

Native render nodes preserve the pool of 80 entries established by binary
`0x188c1` (`0x1c398` to `0x1ca78`, stride 22). Acquisition inserts by signed
16-bit order, preserving insertion order for ties; release recycles at the free
head. The four control bytes retain countdown, period, pass and flags. Animation
enable/disable preserves unrelated bits and does not reset the countdown.
Native pointers deliberately replace the original packed 32-bit pointer layout.
Pool exhaustion and invalid release are explicit failures, not substitute nodes.

```bash
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_render_nodes.c src/engine/render.c src/engine/sprites.c -o build/check_render_nodes
build/check_render_nodes
```

The object render pass now draws real multipart descriptors: a 14-byte header
followed by six-byte records (two anchor words, frame byte, bank byte). It
preserves visibility/pass gating and the exact countdown/flag transitions from
binary `0x18762`, including the `0x08`, `0x04` and `0x10` interactions.
Sprite parts use the existing MCH decoder, original flip anchors and 16-bit
coordinate wrap. Banks and descriptor bounds are checked.

Binary verification corrected the decompiler's damaged register reconstruction:
owner offsets 0/2 are X/Y, not depth; flag `0x40` adds the viewport's X/Y words,
not a depth increment. This implementation uses the verified instructions.
The preview uses a clearly identified one-part diagnostic descriptor to exercise
this pass with the real `SYIDLE1.MCH` bank. It does not yet load the game's
multipart descriptors or bind them to gameplay objects; this is not claimed as
a working character animation controller.

```bash
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_render_pass.c src/engine/render.c src/engine/sprites.c \
    -o build/check_render_pass
build/check_render_pass
```

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
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_program.c build/animation_data.c src/engine/animation.c \
    src/engine/render.c src/engine/sprites.c -o build/check_program
build/check_program
```

```bash
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_animation.c src/engine/animation.c src/engine/render.c \
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
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_motion.c src/engine/animation.c src/engine/render.c \
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
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_idle.c build/animation_data.c src/engine/animation.c \
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
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_assets.c src/engine/assets.c src/engine/resources.c \
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
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_fade.c src/libs/vga.c -o build/check_fade
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
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_vga_present.c src/libs/vga.c -o build/check_vga_present
build/check_vga_present
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_viewer.c build/animation_data.c src/dos64/start.c src/dos64/platform.c \
    src/engine/resources.c src/engine/resource_decoder.c src/engine/sprites.c \
    src/engine/tiles.c src/engine/tile_blitters.c src/engine/timing.c \
    src/engine/input.c src/engine/render.c src/engine/assets.c \
    src/engine/animation.c src/engine/objects.c src/engine/physics.c \
    src/engine/behaviors.c src/libs/vga.c \
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

### Original combined visual/motion script

`animation_movement_initialize` prepares the original script at DS `0x3615`.
Its original bytes select visual stream `0x362b` and motion stream `0x367a`,
then branch to the shared update/yield loop at `0x325a`. The build embeds
checksum-verified DS `0x3252..0xfc44` unchanged, including its descriptors.
No synthetic movement records or replacement state transitions are introduced.

The host test verifies 4000 updates against an independently decoded timeline:
the initial facing-dependent 80-pixel offset, its restoration after 18 updates,
the subsequent facing toggle, all 13 descriptor selections and their durations,
state word change to 1, the first 60 stationary motion updates, subsequent
two-pixel motion, direction changes during repeated motion, and 16-bit wrap.
The script contains no callback events; none are skipped.

```bash
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_movement_program.c build/animation_data.c \
    src/engine/animation.c src/engine/render.c src/engine/sprites.c \
    -o build/check_movement_program
build/check_movement_program
```

This is a runnable original script path, not a migrated behavior selector,
collision response or full game state. It is available to native engine callers
but intentionally does not replace idle in the diagnostic preview or introduce
an invented input binding.

### Original falling-object behavior and physics

The next native behavior is the original handler `0x288a1`, not a replacement
player controller. It initializes original DS script `0x16741`, clears the
spatial type, checks visibility, applies gravity and executes the script in
that exact order. The script uses descriptor DS `0xe4b4`, yields through the
original shared loop at `0x14272`, and repeats its frame every 100 updates.

Native callers acquire an object with `engine_falling_behavior`, set its
`context` to an `ENGINE_FALLING_OBJECT`, and supply its owner, active render
node, render pool and visibility window. State starts zero-initialized.
Pointers are native typed pointers, not original packed object addresses.
The original visibility flag 1 allows updates without a window; otherwise
missing visibility data is an error. Original fixed bounding boxes and flags
are preserved. Out-of-window objects release their render node before the
object dispatcher recycles them and clears a tracked-object reference.
An externally assigned nonzero spatial type requires an explicit unlink
callback; the level spatial index is not implemented by a no-op.

The shared physics helpers preserve 16.16 coordinates, signed velocity caps,
the original gravity increment and 32-bit overflow. Descriptor point collision
also preserves H/V flips, inclusive edges and signed 16-bit wrapping; it does
not yet implement terrain collision. Behavior errors propagate through
`engine_update_objects` and stop traversal rather than silently retaining an
apparently successful update.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_physics.c src/engine/physics.c -o build/check_physics
build/check_physics
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_bounds.c src/engine/render.c src/engine/sprites.c -o build/check_bounds
build/check_bounds
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_falling.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_falling
build/check_falling
```

These tests cover 720896 physics cases, 7340032 point-collision cases and 2000
falling-behavior updates through the real dispatcher, including removal and
error paths. This behavior is compiled into the DOS64 build but is not spawned
by the diagnostic entry. The preview remains idle; the original level/spawn
selection path and player behavior are still unported.

### Rectangle collisions and original falling-object spawn

`render_local_rectangle_hit` migrates original `0x1693d`: target descriptor
bounds use H/V flips, while a supplied local rectangle uses the current
object's H flip only, exactly as the original does. `render_objects_hit`
migrates `0x16a57`, applying both objects' own descriptors, H/V flags and
positions. Both retain signed, inclusive comparisons and 16-bit wrapping;
neither normalizes inverted bounds nor ignores hidden objects.

`engine_spawn_falling` now executes the original `0x1508e -> 0x14fbd` creation
path for definition DS `0x162fe`. It reads and checks the original handler,
flags, initial descriptor `0xe540` and initializer from the embedded dump.
It acquires the object then its render node, sets the native owner and render
order, and immediately invokes migrated behavior `0x288a1`. The caller's
current-object pointer is restored, including when spawning from another
behavior callback. The existing dispatcher then visits an appended object
later in the same update, preserving the original traversal.

The caller supplies a fresh `ENGINE_FALLING_OBJECT`, position, visibility
window and render order; state and visibility must outlive the spawned object.
The API returns 0 with an active output object, 1 with a null output when
original initialization culls it, or -1 on error. As a deliberate native
safety change, exhausted pools and failed initialization do not leave a
partially constructed object with a missing render node. Reusing active state
in the same pool is rejected. This only supports the verified original
definition, not all spawn records or their unported initialization callbacks.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_rectangle.c src/engine/render.c src/engine/sprites.c \
    -o build/check_rectangle
build/check_rectangle
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_overlap.c src/engine/render.c src/engine/sprites.c \
    -o build/check_overlap
build/check_overlap
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_spawn.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_spawn
build/check_spawn
```

Tests cover 37748736 local-rectangle cases and 15728640 object-pair cases
in both argument orders, plus actual spawning, immediate updates, pool
exhaustion, initialization culling and same-tick traversal. The diagnostic
entry still does not invoke level spawning; no preview key binding was added.

### Horizontal acceleration and timed parent-child creation

`engine_motion_accelerate_x` ports `0x1a9da` and its helper `0x1cda1`.
The original adds acceleration with 32-bit wrapping, clamps the signed result
to -4/+4 in 16.16, then integrates X using the new velocity. Y is unchanged.

`engine_timed_behavior` ports original `0x2881d`: initialize script DS `0x16728`
and a 16-bit counter of 10, check visibility, decrement the counter, spawn the
original falling child at zero at parent X/Y-16, then apply parent gravity and
execute its script. The child's position uses the parent's position before
gravity. Immediate child initialization and the subsequent same-tick dispatcher
visit are both preserved; these are two updates, not one.

`engine_spawn_timed` reads original definition DS `0x162f0`, with behavior and
initializer `0x1881d`, zero flags and descriptor `0xe4c8`. It reuses the verified
object/render construction path and restores the caller's current object.
Its immediate initialization leaves counter 9, so a parent created this way
spawns on the ninth subsequent dispatcher update. This is different from
manually acquired, uninitialized state, which spawns on its tenth update.

The caller supplies separate live parent and child states and render orders.
No unported allocator or child-spawn effect is replaced by a no-op. Missing
child storage, exhausted pools or reused active child storage are explicit
errors. The original counter wraps and reaches zero again after 65536 updates;
the caller must then supply available child storage if the previous child is
still active. The long-run test verifies that exact boundary and rejects
overwriting the active child at update 65546. Full level-owned state allocation
and spawn selection remain unported; the preview is unchanged.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_acceleration.c src/engine/physics.c -o build/check_acceleration
build/check_acceleration
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_timed.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_timed
build/check_timed
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_spawn_timed.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_spawn_timed
build/check_spawn_timed
```

The acceleration test covers 7929856 cases. Timed behavior is checked for
65545 successful updates and its next respawn boundary; the full parent
constructor chain is checked for 1000 updates plus culling and exhaustion.

### Original emitter and three-generation object chain

`render_near_view` ports `0x2805c`, testing strict bounds around the original
320x200 camera rectangle with signed margins. Unlike descriptor collision,
these comparisons use expanded 32-bit bounds, without 16-bit wrapping.

`engine_emitter_behavior` ports `0x2865d`. Its first call only marks the
continuation initialized and returns. Subsequent calls retain the old 16-bit
counter before decrementing it when the original activation flag is nonzero.
The activated path checks camera proximity with margins 128/128 and removes
the emitter outside that expanded rectangle. Old counter low-seven-bit values
20/40 spawn the verified timed parent at X-8/X+8, before Y is snapped to a
multiple of four with bit-one-dependent offset 2. Negative old counters apply
gravity; script execution follows even when activation is off. The two
original script variants are extracted unchanged from the data dump.

`engine_spawn_emitter` ports constructors `0x28773` and `0x28797` as variants
0 and 1. It reads original definition DS `0x162e2`, checks behavior and
initializer `0x1865d`, and uses initial descriptor `0xe4a0`. After the immediate
initializer returns, it sets original script DS `0x166f6` or `0x1670f` and the
supplied counter. It intentionally does not render/advance the first script
frame during construction.

Callers supply live activation and camera pointers, a visibility window,
render orders and exclusive `ENGINE_EMITTER_SLOT` storage. Each slot contains
one timed parent and its falling child. It can be reused only after both are
removed from the object pool. Missing or exhausted storage is an explicit
error, never a skipped emission. The real object dispatcher updates spawned
parents and children later in the same traversal, preserving the existing
immediate-initializer effects.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_near_view.c src/engine/render.c src/engine/sprites.c -o build/check_near_view
build/check_near_view
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_emitter.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_emitter
build/check_emitter
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_spawn_emitter.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_spawn_emitter
build/check_spawn_emitter
```

Tests verify 9175040 camera proximity cases, a 160-update emitter timeline
with four emissions, and both constructors through an actual three-generation
chain, including activation, gravity, culling and exhaustion. The full level
setup and activation source remain unported; the diagnostic entry still shows
idle, with no invented spawning key.

### Braking, directional motion and original four-emitter setup

`engine_motion_brake_x` ports original `0x1a844`, including its signed
absolute-value helper. It stops only below the strict magnitude threshold,
otherwise subtracting the caller-supplied signed decrement with 32-bit wrap.
It preserves the unusual x86 `abs(INT_MIN)` result rather than introducing
undefined signed overflow. It does not invent the sign of the decrement.
`engine_motion_right/left` port `0x1a886/0x1a8f2`, setting a minimum rightward
velocity +2 or leftward velocity -2 in 16.16 before integration. Only the
rightward original helper observes the stop bit 0x10 of object byte +0x4f.

`engine_setup_emitter_group` ports original `0x287bb`. It resets the activation
flag and creates four original emitters in order: X 3480/3512/3536/3568,
Y 424, counters 170/190/200/210, variants 0/1/0/1.
An `ENGINE_EMITTER_GROUP` owns the live activation flag, emitter state,
parent/child slot storage and resulting object references. Callers supply
the live camera, visibility window and render orders. The group must outlive
all its active objects and cannot be reset while any member or descendant
is active in the same pool. Preflight requires four free object and render
slots, preventing partial creation or resetting the activation flag on
resource exhaustion.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_braking.c src/engine/physics.c -o build/check_braking
build/check_braking
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_directional_motion.c src/engine/physics.c -o build/check_directional_motion
build/check_directional_motion
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_emitter_group.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_emitter_group
build/check_emitter_group
```

Tests cover 1769472 braking cases and 2162688 directional-motion cases.
The group test checks original instruction constants, inactive animation,
90 active updates with eight parent-child chains, camera removal and pool
exhaustion. Activation in this host test is supplied explicitly; the original
boss behavior that sets DS `0x1938f` remains unported. The native diagnostic
entry is unchanged and does not claim to run this level.

### Original camera limit and shake object

`render_limit_camera_x` ports the consumed 16-bit result of `0x288e3`: signed
X is limited above by signed map width in tiles times eight minus 320. There
is no invented lower clamp to zero. Expanded comparisons remain 32-bit;
the returned coordinate preserves the original word wrapping.

`engine_shake_behavior` ports `0x283cd`, using the old counter before decrement.
It starts at 30, produces the original 8/0/7/0/.../1/0 camera-shake sequence,
and releases render and object when the old counter becomes negative.
At old counter 15, zero immunity, nonzero object X and zero player vertical
velocity invoke the original impact dependency via an explicit callback.
It does not execute an animation script or move the object.

`engine_spawn_shake` ports `0x2853e` using original definition DS `0x162d4`,
handler/initializer `0x183cd`, zero flags and descriptor `0xe48c`. It sets X
to the supplied impact marker and Y to zero, immediately runs initialization,
and then ORs player flags with `0x40`. Immediate initialization leaves shake 8
and counter 29; impact can occur on the fifteenth later dispatcher update.
The earlier caller's current object and update status are restored.

The caller supplies live shake, immunity, player-motion and player-flags
storage. Nonzero markers require a real impact callback; missing dependencies
or exhausted pools are explicit errors. The original damage handler `0x22315`
and full level camera application remain unported, not silently substituted.
The diagnostic preview remains unchanged.

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_camera_limit.c src/engine/render.c src/engine/sprites.c \
    -o build/check_camera_limit
build/check_camera_limit
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_shake.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_shake
build/check_shake
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_spawn_shake.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_spawn_shake
build/check_spawn_shake
```

Tests cover 655360 camera-limit cases and all impact gates, exact shake timing,
immediate constructor effects, tracked-object removal, state reuse and failures.

Migrated modules use ordinary `.h` interfaces and separately compiled `.c`
implementations, with `include/` and `src/` as include roots.
Original pseudocode bodies are kept in adjacent `*_legacy.inc` files,
conditionally included only without `LK_DOS64_NATIVE`. They do not enter the
native build. The preservation validator expands these reference includes
and keeps them separate when writing modules. The old pseudocode aggregator
still textually includes unported modules for reference; it is not built.

Compilation requires MinGW-w64 (`gcc-mingw-w64-x86-64` on Debian/Ubuntu).
Override the compiler with `MINGW_GCC`. Flags use freestanding x86-64 PE,
Microsoft x64 startup, no host CRT and no red zone.
DOS64 provides the runtime import; Windows additionally requires a supplied
`bmetal.dll` beside the executable. When available in `bin/`, the build copies
that DLL to `build/`.

## DOS64 images

After a successful build:

```bash
bash image/build-image.sh fresh.img
bash image/run.sh fresh.img
```

Relative image names are resolved inside `image/`. Image creation installs
`build/lionking.exe` as `C:\GAMES\LIONKING\LIONKING.EXE`, copies `LIONKING.EPF`
and the configuration when supplied, and configures startup in that directory.

Image creation refuses to overwrite existing files. The launcher creates a
missing image, but **does not update an existing one**. Use a new image name
to test a new executable; stop QEMU before manipulating any image.
Existing user images and startup commands are not rewritten by the build.
The default build/run workflow always uses a fresh temporary image.

Image creation requires mtools, dosfstools and util-linux. Running requires
QEMU and OVMF; default firmware is `/usr/share/OVMF/OVMF_CODE.fd`.
Set `OVMF_PATH` or `QEMU_DISPLAY=none` as needed. The bundled launcher uses TCG
and Intel HDA with PulseAudio output (also usable with PipeWire's PulseAudio
server). The previous `none` backend discarded sound even when the game
successfully submitted audio. Restart QEMU after updating the launcher.
Set `QEMU_AUDIO_DRIVER=alsa` for direct ALSA output, or
`QEMU_AUDIO_DRIVER=none` only for intentionally silent tests.
Run `LIONKING.EXE --map` in DOS64 to hear LEVEL1 music; other previews are silent.

### Visible original emitter scene

The `LIONKING.EXE --emitters` entry displays the original `LEVEL6.MAP` palette
and tiles with `CRUMBLIN.MCH`, loaded from the original level-six list at
DS `0xe3d0`, slot 160. It runs the migrated four-emitter setup `0x287bb`,
emitter `0x2865d`, timed parent `0x2881d` and falling child `0x288a1`
through the real object dispatcher. Original descriptors, scripts, counters,
positions, gravity and culling drive the visible crumbling platforms and
falling fragments; frames do not depend on keyboard presses.

This is a migration demonstration, not a playable level. Its fixed camera,
activation after one second and restart after all objects are removed are
explicit test fixtures. The original boss activation writer is not migrated.
Camera mapping is enabled only during rendering, leaving behavior flags
unchanged. Escape exits; `--idle` retains the previous automatic Simba preview
and `--manual` retains the bank/frame browser.

`tools/check_scene.c --emitters` runs the actual emitter entry for 20 simulated seconds
and checks 128064000 exact ARGB pixels, repeated activation and Escape.
It requires more than 1500 frames with visible object pixels and at least
100000 object pixels overall. Compile it with the same source list as
`tools/check_viewer.c` above, substituting the test source and output name.
Real DOS64/QEMU captures also changed over time and Escape returned exit code 0.

The scene now also exercises the original impact camera shake: the migrated
`0x2853e` constructor and `0x283cd` behavior feed the restored viewport
preparation at `0x11799`. Its signed 16-bit lower/upper clamps, low-word map
limits and eight-pixel aligned origins come from `bin/frame_timing.asm`.
Shake is added to the visible camera Y with word wrapping, after clamping,
and cleared after successful presentation as in `0x10276`.
Tiles and objects receive the same shaken viewport; visibility/culling use
the unshaken camera. This replaces no gameplay damage: the demonstration
supplies marker X zero, so the original impact gate does not call the still
unported player damage routine. Starting the shake together with the emitter
fixture is diagnostic, not a claim that the boss attack has been migrated.

The scene test requires at least 20 visibly shaken frames and 100000 changed
ARGB pixels against an unshaken map, in addition to exact output comparisons.
`tools/check_viewport.c` checks 1966080 coordinate/dimension/shake combinations,
including negative and wrapped limits and shake `0xffff`:

```bash
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
    tools/check_viewport.c src/engine/render.c src/engine/sprites.c \
    -o build/check_viewport
build/check_viewport
```

### Original player deflection block

`LIONKING.EXE --deflection` runs a larger migrated player behavior segment,
not a replacement platformer. It cycles eight diagnostic cases using the
original `SYFLIPBW.MCH` / `SYFLIPFW.MCH` banks (slots 11/12):
two selectors, two visual-script ranges and probe off/on. Escape exits.
The original selectors, motion and animation run automatically, then pause at
the boundary to the still-unported ordinary player state.

Recovered from `src/recovered/block_0c000.c` and verified against the EXE:

- `0x1e36e` / `0x1e3bf`: signed contact ranges `[4,16]` and `[32,48]`
  select the ordinary handler; other values delegate to the script selector.
- `0x1e667` / `0x1e6ee`: wrapped original script-pointer subtraction,
  `SAR 1`, low-word mask and index `1..24` choose exact handler, DS script
  and counter `20` or `50`. Any nonzero form selects adult data.
- `0x1e410` / `0x1e545`: initialization at vertical velocity -5, 16 motion
  updates and the next-update transition; directional stop controls, damage
  gate, coordinate probe, collision flags **OR** `0x20`, original scripts,
  fixed-point integration and horizontal velocity -3/+3.
- `0x20e37`: player gravity +`0x4e00` for young / +`0x6000` for adult,
  with the original signed upper cap +7.

The probe is an explicit dependency for unported `0x174b2`. Its synthetic
results and the repeated starting position are test fixtures. Transitions to
`0x1aa97`, `0x1ae53` and damage `0x1ef04` are explicit callbacks, not fabricated
implementations. The preview stops at those boundaries. Original addresses
in `ENGINE_PLAYER_CALL` are data only, never invoked as native pointers.
The emitter scene (`--emitters`) and `--idle` / `--manual` modes remain available.

`tools/check_player_reactions.c` checks 11010048 calls, including every signed
contact word, wrapped pointer indices and young/adult forms.
`tools/check_player_deflection.c` runs the whole segment through the object
dispatcher: 1632 original-script updates, exact descriptors, velocity and
fractional coordinates, directional asymmetry, probe/stop/damage gates and
missing-dependency errors. Build these tests with the generated animation data
and `behaviors.c`, `animation.c`, `render.c`, `sprites.c`, `physics.c`,
`objects.c`, `input.c`.
`build/check_scene --deflection` additionally runs the actual entry for 20
seconds, verifies 128064000 ARGB pixels, all eight cases, 320 moving frames,
20 exact transition boundaries and Escape.
The player test also checks 1966080 gravity cases across all fractional Y
values, signed overflow and the +7 cap. Native QEMU verification showed
28624 changed viewport pixels and a successful Escape exit with code zero.

### Deflection, flight and landing test (`--flight`)

Run `LIONKING.EXE --flight` for the earlier automatic Simba flight test.
It chains the migrated deflection into the original right/left airborne
handlers `0x1aa97` / `0x1ae53`, then the landing selectors
`0x1b307` / `0x1b4a0`. Left/Right override the fixture's airborne direction.
Escape exits. Each fixture repeats after two seconds and stops at the selected
ground-state boundary; ordinary ground locomotion is not implemented here.
`--deflection` retains the shorter earlier test, `--emitters` the rock scene,
`--idle` automatic idle, and `--manual` the bank browser.

The airborne code preserves the original gate ordering, right-only upward
probe and counter-forced direction, left/right script-reset asymmetry,
edge sentinels `0xf8` / `0xe8`, fixed-point gravity at `0x20ea6` with the
flags-bit-2 cap bypass, anchor centering and direction changes. Landing
preserves signed duration/velocity thresholds, exact script/handler arguments,
flags and the right-only zeroing of vertical velocity.

An important original behavior: deflection sets the next handler **before**
calling it. The airborne handler therefore skips initialization on this path;
it must retain the running flip script instead of loading the nominal `0x6116`
argument. The test covers that continuation. Later visual records require
additional original banks, so the extended preview loads all 28 young banks.

This remains an explicit migration test, not a playable level. The ground at
Y=160, ceiling probe outcomes, absence of edge hits and repeated starting
position are synthetic dependencies. The original map queries `0x14c72`,
`0x170ae`, `0x174b2`, special-state handlers and ground states remain explicit
callback boundaries, never silently fabricated gameplay.

`tools/check_player_air.c` verifies both full airborne paths and 2752512
landing cases: all signed duration words, young/adult forms, signed velocity
thresholds, gate precedence, exact edge operands, probes, anchors and errors.
It also verifies 1966080 capped/uncapped player-gravity combinations.
`build/check_scene --flight` checks the actual flight entry for 20 seconds:
128064000 exact ARGB pixels, 2001 visible frames, 398 moving frames,
460 airborne frames and ten complete deflection-to-landing chains.
`build/check_scene --steering` additionally verifies two direction changes
from actual mocked DOS64 arrow input, pixel-for-pixel.
Compile `check_player_air.c` with the same engine source list as the preceding
player tests. Run `build/check_scene --deflection` and `--emitters` for the
previous scene regressions.
Real native QEMU verification produced 14724 changed viewport pixels and
repeated landing-boundary logs; Escape returned exit code zero.

### Controlled jumps and repeated landings (`--jump`)

Run `LIONKING.EXE --jump`. This preview runs the original jump handlers
`0x1b604` / `0x1b7e7`, jump-hold helper `0x1b5ac`, airborne handlers and
landing selectors. Before keyboard takeover it demonstrates short and held
jumps in both directions, starting a new case every two seconds.

- Space takes control and starts a jump when ready on the ground.
- Hold Space to prolong the original ascent boost; releasing it stops the boost.
- Left/Right change facing on the ground fixture and direction while airborne.
- After landing, Space starts another jump without restarting the executable.
- Escape exits; `--flight`, `--deflection`, `--emitters`, `--idle` and `--manual`
  preserve the earlier previews.

The migration retains the original launch scripts (`6180/5944`), continuation
scripts (`612c/5928`), young/adult startup delays (4/10), vertical velocity,
8/6 boost ticks, hold flag `0x1000`, momentum flag `0x2000`, direction changes
without reinitializing the jump, ceiling handling and adult early transition
to the airborne handler at velocity -3. Collision-mask writes are bitwise
AND/OR, not the decompiler's substituted constants.

Landing recovery handlers `0x1b19f` / `0x1b253` are also migrated: exact
16-bit countdown, surface-kind-3 interruption, damage gate, sound request
4/5, and handler replacement before the final animation tick. The native
fixture explicitly logs the unported audio request rather than pretending
to play it. Ordinary jumps do not force recovery when the original selector
chooses a different ground state.

This is still a diagnostic stage, not a complete level: ground Y=160,
no ceiling/edge hits, ground-idle/input handling and automatic repositioning
are fixtures. Ground running, actual map collision and special states remain
unported. Long idle events are explicitly logged without their gameplay
side effects. Manual jumps are not automatically restarted or repositioned.

`tools/check_player_jump.c` verifies 393210 nonzero delay cases, 393216
recovery countdown cases, 4608 boost combinations and 218 independently
traced ascent ticks, including adult/young forms, fractions, word wrapping,
probe ordering, gates, same-handler continuation and dependency errors.
Compile it with the same engine source list as `check_player_air.c`.

`build/check_scene --jump` checks 20 seconds of the jump entry: 128064000
exact ARGB pixels, 2001 visible frames, 350 moving frames, 768 airborne frames,
and nine complete jumps/landings. `build/check_scene --jump-steering` tests
four manual jumps, eight direction transitions, sustained idle events and
Space height control: held jumps rise at least 40 pixels higher than short
jumps. Real QEMU showed Simba jumping, 13824 changed viewport pixels,
manual keyboard takeover and an Escape exit with code zero.

### Default test: original ground locomotion and connected player states

Run `bash build.sh`. Ground idle/input is no longer fabricated: the default
preview connects ten more original handlers:

| State | Original code addresses |
| --- | --- |
| Left/right ground idle | `0x1c2cd`, `0x1c8d5` |
| Right/left running | `0x1cdc2`, `0x1d108` |
| Turning to left/right | `0x1beb7`, `0x1c0a1` |
| Left/right crouching | `0x1b9ca`, `0x1bc80` |
| Right/left rolling | `0x1ea46`, `0x1eb56` |

All preview modes write diagnostics to `LIONKING.LOG` in the working
directory, replacing the previous run's log. They do not render console
text over the game. The file is closed on exit, including error exits.
If logging fails, the preview stops and reports the failure after rendering
has ended.

The original ground reset `0x1c28e` and existing capped acceleration helper
complete this block. Running accelerates by `+/-0x4000`, preserves signed
`+/-0x20000` minimum and `+/-0x40000` maximum, turns through the original
animation, stops through the original idle scripts, and selects a different
jump script from standing. Landing resumes the selected ground handler,
not a synthetic frozen frame. Down crouches while idle; Down at sufficient
running speed enters the original roll, slowing by `0xe00` per update.

Left/Right run, Down crouches/rolls, Space jumps (hold to prolong ascent),
Ctrl roars, and Escape exits. Any of those inputs takes over the automatic
twelve-second demo: movement/jumps, two roars, then an injected diagnostic
hit and original recoil. H injects another test hit; T enables one second
of synthetic terrain contact, cycling kinds 6/9/5/8 on successive presses.
These two keys also take over the demo. Manual input does not
teleport/restart Simba. The renderer follows X
using the existing original viewport clamps; camera-follow policy is a
fixture, not the original full game camera controller.

Ground support at Y=160, no walls/edges/ceiling hits and the automated
input sequence remain explicit fixtures. Real level collision, enemy hit
detection, adult attacks and progression actions remain explicit callback
boundaries. The ground code nevertheless preserves their
selection, ordering and operands, including the left-crouch fallthrough and
left-run flag asymmetry. Roll/recovery sound requests are logged, not played.
Long-idle animation events also remain diagnostic.

### Connected action block: roar, damage, recoil and terrain slides

The default preview also migrates eight original handlers and their
generic vertical-motion helper, without replacing the original scripts:

| State | Original code addresses |
| --- | --- |
| Roar | `0x1ec69` |
| Passive reaction animation | `0x1ee35` |
| Grounded stun | `0x1ee60` |
| Damage and recoil selection | `0x1ef04` |
| Left/right-facing recoil | `0x1f017`, `0x1f160` |
| Rolling terrain slide | `0x1f80d` |
| Grounded/airborne slope slide | `0x1fe3c`, `0x1ff83` |

There are nine addresses in this table: the eight persistent state
handlers plus the immediate damage selector. `0x1a6ff` preserves generic
`0x4e00` gravity even for adult Simba, support checks and airborne
contact reset. Recoil starts at Vy=-3 and Vx=+1/-1, lasts 18/40 ticks, then
selects original ground or air behavior. Damage preserves masks,
immunity=100, positive-health decrement, source-side selection and the
grounded-stun exception. The original right-recoil form-bit test is
preserved, not replaced with a symmetric nonzero-form check.

Roar emits the charge pulse at age 14/30, clears it on the following
tick and returns to the original idle at age 55/94. Sound requests 2/3
are logged only. Calls to `0x1510c` are genuine RET stubs in the original
binary, not invented effects. The right-facing roar now passes counter=0,
the left-facing roar counter=1, matching the original assembly.

H's source position, T's terrain contacts, initial health/roar charge
and the absence of meter recharge/immunity ticking are diagnostic
fixtures. There is no enemy receiving the roar pulse yet, and no sound
playback. The grounded-stun and passive-animation paths are migrated but
not part of the default young-Simba sequence.

Earlier preview modes are retained: `--jump`, `--flight`, `--deflection`,
`--emitters`, `--idle`, `--manual`. The focused ground harness is
`tools/check_player_ground.c`; `build/check_scene` exercises the connected
default entry and `--ground-steering` its manual controls.
`tools/check_player_actions.c` covers the action and terrain block.

### Contact movement block (`--contacts`)

`LIONKING.EXE --contacts` cycles through right/left contact rebounds,
a thrown launch, and movement toward a tether point followed by release.
The previous default remains available with no arguments. B, R and F
activate these cases manually in either ground preview and stop automated
inputs; Left/Right, Space, Ctrl and Escape keep their existing meanings.

Migrated original code addresses:

| Path | Addresses |
| --- | --- |
| Contact rebound selector and directional entries | `0x1f5f1`, `0x1f618`, `0x1f672` |
| Thrown movement and facing-dependent velocity helper | `0x1f2b1`, `0x202de` |
| Adult contact escape / release | `0x1f3fb` |
| Tether-point movement and release into air | `0x1f6cc` |

Rebounds select the original `6228/58b8` script and preserve the unequal
right/left initial Vy (-4.5/-4). Thrown movement selects `621a/5864`,
starts at Vy=-4.5 and facing-dependent Vx=-1.5/+1.5, then uses the
original 35-tick counter and boundary checks. Tether movement advances
each integer coordinate by 4 only outside the +/-4 tolerance, with
wrapped word arithmetic and no animation update while attached.
Release calls the current air stream without reinitializing its script
or facing, matching the original handler replacement.

The adult contact path preserves its state=70 completion, attack counter,
two overlap queries on the right-facing miss path, and release flag.
It is available to engine callers but not demonstrated with young-Simba
banks. Original calls to the `0x1510d` RET stub have no invented effect.

B/R/F activation, forced directions in the automatic sequence, target
placement and release after 45 ticks are explicit test fixtures, not
level/enemy interactions. Real overlap detection is still a required
callback for adult contact sources. Sound sample 0 is logged, not played.
No original level collision or enemy AI is claimed by this preview.

### Ledge movement block (`--ledges`)

`LIONKING.EXE --ledges` demonstrates left/right grabs and climbs, then
left/right drops, in a 16-second cycle. The same handlers are available
in the default preview: K grabs an alternating side, Up climbs after the
original grab delay, Down drops immediately. P selects the original
supported-turn state; Left/Right turn, Space jumps from it.

| Path | Original addresses |
| --- | --- |
| Ledge branches of directional edge selectors | `0x1e775`, `0x1e8df` |
| Left/right grab and hanging states | `0x1d5f4`, `0x1d7a3` |
| Left/right climbing states | `0x1d40a`, `0x1d4ff` |
| Supported turning and jump/fall selection | `0x20075` |

Grab aligns X to the original 16-pixel cell (plus 15 on the left),
queries ledge height through an explicit callback, zeros velocities,
starts script `618e/58d4`, sets the 42-tick counter and original flags.
Climb preserves the 31/39-tick sequence, final X offset -9/+9 or
-19/+19, and final Y offset -1/+3. Drop preserves the asymmetric
left/right flag clearing and forced-drop direction, not a normalized
replacement. The supported-turn handler preserves its counter=6,
final facing flip, and original `6180/612c` jump operands even for adult.

The demo's fixed height query, synthetic grab at Y=96 and support plane
Y=111 (Y=192 after dropping) are fixtures, not migrated map collision.
Other edge-selector branches for swing objects remain explicit
unported boundaries. Adult scripts/branches are covered by the engine
check but the visible preview still loads young-Simba banks.
All diagnostics continue to go to `LIONKING.LOG`, never over the game.

The focused action check covers both forms/directions, climb delays and
offsets, normal/forced drop masks, negative hang counters, supported-turn
timing, jump operands and support loss. The default scene regression still
matches 128064000 ARGB pixels. Native DOS64/QEMU exercised both completed
climbs and both drops; Escape returned zero.

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

### First real-map interactions (`--map`)

`LIONKING.EXE --map` loads `LEVEL1.MAP` and `CONTOUR.CON` and starts
manual play on actual terrain, rather than the Y=160 test plane.
Left/Right move, Space jumps (hold for height), Down crouches/rolls,
and Escape exits. Earlier diagnostic preview modes remain unchanged.
Synthetic hit, terrain, tether, ledge and wall-grip shortcuts are disabled
in this mode.

Migrated map queries connect the original `0x14c21/0x14c72` support and
landing interfaces to the two-row contour sampler `0x16b70/0x16d3d`.
The layer-0 table contains four planes: the sampler reads contour indices
from the second plane and contact tags from the third, using one
16-pixel cell per four bytes. Shape indices use the original bit formula,
not rendered tile presence. Contour height is the low five bits, minus
one for support; candidates must be within -12..+12 pixels.

The character now follows real slopes/steps, loses support over gaps and
lands through the existing original flight selector. Queries for edges
use the current animation descriptor and facing (`0x170ae/0x171b3`);
ledge height comes from the contour plane (`0x17515`). These feed the
migrated grab/climb handlers without synthetic geometry.
The camera translates the same world coordinates in both X and Y.

Starting X=160 is still a preview choice, not migrated level startup.
Starting Y is located on the real surface (LEVEL1 currently Y=1255).
Dynamic map objects, complete hazard handling
and swing-object states remain unported. An encountered unported edge
branch reports an error rather than inventing a substitute.
Diagnostics and exit measurements remain in `LIONKING.LOG`.

`tools/check_map_collision.c` verifies the real terrain at X160/X400/X880,
connected running across six height changes, jumping and map landing,
plus synthetic contour/tag boundary checks. Compile it with the player
test source list plus `resources.c` and `resource_decoder.c`.
Native DOS64 verification recorded six contour adjustments, one jump/landing,
and final position X506/Y1261. The captured frame shows Simba on LEVEL1's
real terrain; Escape returned zero. The default preview's exact-pixel
regression still passes.

Map mode also runs the original left/right lateral probes (`0x16f41`,
`0x16e37`, classification `0x17053`) before each behavior tick, in that
order. Blocked directions are removed from held input and recorded in
`boundary_controls`, so existing run/roll/flight handlers choose their
original responses. The probes preserve half-cell neighbors, asymmetric
X corrections, half-height contacts and wall-leap offsets. Wall-grip
states bypass them. The preview uses map limits X16..map-width-minus-16;
level-specific moving boundaries and dynamic-object forced contacts
are not yet connected.

Ceiling queries (`0x1739c`) use the signed top offset of the current
animation descriptor and the original contact plane. The original reads
the same next-row cell twice; kinds 0x40..0x4f and >=0xb0 block before
the later contour-table branches. This behavior is preserved rather
than replaced by an invented ceiling shape sampler.

The focused map check now covers both lateral directions, correction
order, half-cell/half-height thresholds, grip and leap flags, map limits,
and cancellation of both jump directions against real LEVEL1 ceilings.
A native input smoke recorded 164 left-blocked ticks, six contour
adjustments, one landing and final X603/Y1261; Escape returned zero.
Its ground route did not touch a ceiling (zero ceiling hits), so ceiling
behavior was verified separately by the connected real-map player check.
All measurements remain file-only in `LIONKING.LOG`.

### Original background rendering and animated tiles

`--map` now renders the second map layer behind the world, using the
original per-level parallax profiles (`0x11728`, `0x1181d`). Foreground
ordering is background -> unflagged map tiles -> ordinary objects ->
flagged map tiles -> high-pass objects, as in `0x144a3`. Other diagnostic
modes retain their previous rendering for regression comparisons.

Dedicated background previews:

```
LIONKING.EXE --background
LIONKING.EXE --background6
LIONKING.EXE --background10
```

The first shows LEVEL1 parallax; it does not invent a timed tile animation.
The other two also load `LEVEL6.BLK` / `LEVEL10.BLK` and run the original
four-frame tile substitution (`0x19d82`, `0x19e90`). Arrows pan the camera;
Escape exits. The starting camera is a preview fixture at X0/Y0. There
is no player, gameplay initialization or on-screen diagnostic text in
these dedicated previews.

The original animation changes frames on the first logic tick and then
every fifth tick, cycling 1 -> 2 -> 3 -> 0. LEVEL6 copies one 2880-byte
block; LEVEL10 copies 128 bytes followed by six 512-byte blocks. Targets
are resolved from the original map's tile references, not hardcoded
native graphics offsets. Only tile pixels are modified: map tables,
contact tags and contour indices remain unchanged.

Parallax preserves per-row integer ratios, horizontal wrapping and
the repeated LEVEL5 row-21 threshold. Level-specific extra horizontal
offsets from unported world effects are not yet supplied. These previews
do not migrate enemies, platforms, hazards or palette effects.

`tools/check_map_collision.c` additionally verifies row-profile thresholds,
tile flipping/wrapping, exact BLK frame copies and cadence, and unchanged
bytes outside the animated destinations. At a fixed starting camera,
21 ticks produced five substitutions and 7675 visible pixel changes
in LEVEL6, 950 in LEVEL10.

Native DOS64 smoke verification also captured changing pixels at a fixed
camera in both animated previews, then successfully ran LEVEL1 movement
with parallax. All three invocations exited with code zero. The existing
default demo still passes its 128064000-pixel regression.

### LEVEL1 music in map mode

`LIONKING.EXE --map` now plays the original `LION1.AMF` from
`LIONKING.EPF`. This is DSMI AMF 1.4 tracker music, not MIDI: its four
channels use ten nonempty unsigned 8-bit PCM samples. No HEXEN
instrument bank or OPL synthesis is involved; the unused OPL import
has been removed.

The native player in `src/engine/music.c` handles the verified LEVEL1
module shape (31 instrument slots, 15 orders, 60 tracks, 64 rows) and
all effects present in it: instrument/note/volume events, volume slides,
vibrato with parameter memory, combined vibrato/volume slides, pattern
breaks and tempo changes. The opening row changes tempo from 125 to 165.
Playback uses fixed-point sample positions, original sample loops and
AMF stereo panning, and loops the song. This is a focused LEVEL1 player,
not a general AMF implementation or a bit-exact recreation of the old
sound-card mixer.

Output is signed 16-bit stereo at 44100 Hz through `DOS64_API.Audio`.
About 100 ms is queued cooperatively; partial/zero writes retain pending
frames instead of dropping music. Exit and error paths stop the stream.
Missing audio capability, invalid module data and streaming failures
are reported explicitly in `LIONKING.LOG`; map mode requires usable
audio rather than silently starting without the requested music.
Other preview modes remain unchanged and silent.

Focused validation:

```
cc -O2 -std=c99 -Wall -Wextra -Werror -DLK_DOS64_NATIVE -Iinclude -Isrc \
  tools/check_music.c src/engine/music.c src/engine/resources.c \
  src/engine/resource_decoder.c -o build/check_music
build/check_music
```

The check covers non-silent stereo, row timing, the full song loop,
chunk-invariant synthesis, truncated/invalid data, partial output writes
and stopping. Independent libopenmpt inspection reports a duration of
81.424 seconds; the native player crosses the song boundary during the
82nd one-second test block. Address/undefined-behavior sanitizer checks
pass. A native DOS64 HDA capture contains over three million nonzero
samples while map movement/jumping continues; Escape exits with zero.
Host checks that link `src/dos64/start.c` now also need
`src/engine/music.c`; the normal build already includes it.
