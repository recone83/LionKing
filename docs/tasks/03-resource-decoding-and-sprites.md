# Resource decoding and sprites

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

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
