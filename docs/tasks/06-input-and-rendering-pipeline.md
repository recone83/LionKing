# Input and rendering pipeline

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

Native [input.c](../../src/engine/input.c) preserves the original eight control bits
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

The [render orchestration](../../src/engine/render.c) now preserves the exported
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
