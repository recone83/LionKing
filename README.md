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

The sample starts the original idle sequence automatically, without a key
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
    src/engine/animation.c src/libs/vga.c \
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
The `--automatic` host check tests the default entry without pressing A or
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
and silent audio, so it is not an audio-playback validation environment.
