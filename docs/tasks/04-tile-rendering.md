# Tile rendering

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

The existing [tile blitter module](../../src/engine/tile_blitters.c) has a native
`render_blit_tile` implementation shared by opaque and transparent operations.
It preserves 8x8 indexed pixels, zero-pixel transparency, horizontal `0x8000`
and vertical `0x4000` flags, row windows and 320-byte destination rows.
Fully visible, unflipped opaque tiles skip per-pixel clipping checks.
The old six entry points remain only in the reference branch.
Zero-length windows intentionally do nothing; invalid windows fail before writes.

```bash
cc -std=c99 -Wall -Wextra -Werror -fsanitize=address,undefined \
    -Iinclude -Isrc \
    tmp/tools/check_tiles.c src/engine/tile_blitters.c src/engine/tiles.c -o build/check_tiles
build/check_tiles
```

The test compares all destination pixels in 3600 cases with an independent
source-to-destination reference, covering both flips, edge clipping, transparency
and all valid row windows, plus invalid input without destination modifications.

The existing [tile pass module](../../src/engine/tiles.c) now reads one MAP layer
using its 12-byte dimension/offset record, tile storage offset and little-endian
entries. Tile indices start at 1; zero is empty. The two passes select bit
`0x2000` and use the native transparent blitter. Tests exercise layer zero
of all 14 maps and an exact synthetic two-pass camera-clipping case.
The viewer shows layer zero of LEVEL1 at camera (0,0) behind the sprite.
This is a map preview: parallax, opaque background stage, interleaved object
passes and the gameplay camera are still unported, so it is not a complete
reconstruction of `render_game_scene`.
