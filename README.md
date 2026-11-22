# The Lion King: DOS64 and Windows port

A port of the DOS game *The Lion King* for [DOS64 / BMetal](https://bmetal.recone.org)
and Windows. The project includes a native engine, graphics, keyboard input,
music and sound, using the original game data. LEVEL1 is playable; the project
does not yet claim full game compatibility.
After LEVEL1, the game displays a notice that LEVEL2 is not yet available
and returns to the menu after confirmation.

## Requirements

- The original `LIONKING.EPF` game archive in `data/`. The optional
  `LIONKING.CFG` in the same directory is copied to the DOS64 image if present.
- The code and data dumps in `bin/`, including `obj2_data.bin`, which the build
  uses to generate animation data.
- Linux with Perl, MinGW-w64 and standard shell utilities to build.
- For DOS64: QEMU, OVMF, mtools, dosfstools and util-linux.
- For Windows: a compatible `bmetal.dll` next to the executable.

On Debian/Ubuntu, install the build and DOS64 runtime tools with:

```bash
sudo apt install bash coreutils grep perl gcc-mingw-w64-x86-64 \
    qemu-system-x86 ovmf mtools dosfstools util-linux
```

## Run on DOS64

From the project directory:

```bash
bash build.sh
```

This builds the game, creates a temporary DOS64 image with the game and its
archive, then boots it in QEMU. The image is removed after QEMU exits; close
QEMU before building again. The launcher defaults to PulseAudio-compatible
sound and `/usr/share/OVMF/OVMF_CODE.fd`. Set `QEMU_AUDIO_DRIVER=alsa` for
ALSA, `QEMU_AUDIO_DRIVER=none` for silence, or `OVMF_PATH` to select firmware.

## Run on Windows

Build the executable on Linux without launching QEMU:

```bash
bash build.sh --build-only
```

Place a compatible `bmetal.dll` beside `build/lionking.exe`, and place
`LIONKING.EPF` in the working directory from which you run the executable.
If `bin/bmetal.dll` is available, the build copies it to `build/`.

## Controls

Use Up/Down and Enter or Space in the menu. In gameplay, Left/Right move,
Space jumps, Down crouches or rolls, Ctrl roars, and Escape returns to the
menu.

## Documentation

- [Development task archive](docs/tasks/README.md) — historical work and tests,
  split by task.
- [Executable analysis](FINDINGS.md) and [DOS64 SDK reference](SDK.md).
