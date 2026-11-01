# Lion King: reconstructed code and DOS64 port

This project separates the recovered DOS game code into modules and prepares
it for DOS64. **The DOS64 platform test builds; the game is not playable yet.**
The original export contains invalid C and missing functions. The executable
currently displays a grayscale test image, not game assets or gameplay.

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

This command compiles only: it does not modify disk images or launch QEMU.
The output is `build/lionking.exe`. Input binaries remain in `bin/`.
A failed compilation leaves the last successfully built executable unchanged;
do not mistake an old executable for a successful new build.

The [DOS64 entry](src/dos64/start.c) provides
`int __attribute__((ms_abi)) start(const DOS64_API *Api)`.
The build links only this entry, [platform.c](src/dos64/platform.c) and SDK startup,
not the pseudocode aggregator or legacy DOS drivers. The platform test exercises
indexed 320x200 image conversion to ARGB, integer scaling, input polling and
monotonic time. Escape exits; `--selftest` exits after approximately one second.
It is not yet connected to `game_main`. Files, memory management, audio and
the actual game loop remain to be migrated.

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
`build/lionking.exe` as `C:\GAMES\LIONKING\LIONKING.EXE` and configures startup
in that directory. Game assets still need to be installed there before the
game can use them.

Image creation refuses to overwrite existing files. The launcher creates a
missing image, but **does not update an existing one**. Use a new image name
to test a new executable; stop QEMU before manipulating any image.
Existing user images and startup commands are not rewritten by the build.

Image creation requires mtools, dosfstools and util-linux. Running requires
QEMU and OVMF; default firmware is `/usr/share/OVMF/OVMF_CODE.fd`.
Set `OVMF_PATH` or `QEMU_DISPLAY=none` as needed. The bundled launcher uses TCG
and silent audio, so it is not an audio-playback validation environment.
