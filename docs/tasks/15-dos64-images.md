# DOS64 images

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

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
