# Early project overview and validation

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

# Lion King: DOS64 and Windows port

The game is playable on both DOS64 and Windows. This project ports the DOS
version using native engine modules and the original game assets. The recovered
decompiler export is kept as analysis material; it is not the executable
game implementation.

## Layout

| Path | Purpose |
|---|---|
| [src/](../../src/) | Active recovered code, module documentation and manifests |
| [src/pseiudo.c](../../src/pseiudo.c) | Aggregates modules and shared declarations |
| [src/engine/main.c](../../src/engine/main.c) | Game initialization reconstructed from machine code |
| [include/](../../include/) | DOS64 SDK headers |
| [lib/](../../lib/) | Supplied DOS64 startup object and import library |
| [bin/](../../bin/) | Original executable, code/data dumps and disassembly evidence |
| [build/](../../build/) | Generated executables and temporary build products |
| [image/](../../image/) | Supplied EFI kernel, image creation and QEMU launcher |
| [data/](../../data/) | Game asset storage; installation is not automated yet |
| [tools/](../../tools/) | Reconstruction validation tools |
| [pseiudo.c.backup](../../pseiudo.c.backup) | Immutable original decompiler export |
| [FINDINGS.md](../../FINDINGS.md) | Reverse-engineering findings |
| [SDK.md](../../SDK.md) | DOS64 SDK reference, including upstream-specific examples |

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

The [DOS64 entry](../../src/dos64/start.c) provides
`int __attribute__((ms_abi)) start(const DOS64_API *Api)`.
The build links this entry, [platform.c](../../src/dos64/platform.c),
[frontend.c](../../src/dos64/frontend.c), the native engine modules and SDK startup,
not the pseudocode aggregator or legacy DOS drivers. The platform test exercises
indexed 320x200 image conversion to ARGB, integer scaling, input polling and
monotonic time. `--selftest` exits after approximately one second.
It is not yet connected to `game_main`. The existing resource module now has a
native DOS64 branch selected by `LK_DOS64_NATIVE`; it validates the real EPF
header, index and payload bounds through DOS64 filesystem callbacks.
