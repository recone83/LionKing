# Original camera limit and shake object

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

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
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_camera_limit.c src/engine/render.c src/engine/sprites.c \
    -o build/check_camera_limit
build/check_camera_limit
perl tools/extract_animation.pl bin/obj2_data.bin > build/animation_data.c
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_shake.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_shake
build/check_shake
cc -O2 -std=c99 -Wall -Wextra -Werror -Iinclude -Isrc \
    tmp/tools/check_spawn_shake.c build/animation_data.c src/engine/behaviors.c \
    src/engine/physics.c src/engine/animation.c src/engine/objects.c \
    src/engine/input.c src/engine/render.c src/engine/sprites.c -o build/check_spawn_shake
build/check_spawn_shake
```

Tests cover 655360 camera-limit cases and all impact gates, exact shake timing,
immediate constructor effects, tracked-object removal, state reuse and failures.

Migrated modules use ordinary `.h` interfaces and separately compiled `.c`
implementations, with `include/` and `src/` as include roots.
Original pseudocode bodies are kept separately in `tmp/` as `*_legacy.inc`
files. They do not enter the native build. The preservation validator reads
and updates these reference files independently. The pseudocode aggregator
still textually includes unported modules for reference; it is not built.

Compilation requires MinGW-w64 (`gcc-mingw-w64-x86-64` on Debian/Ubuntu).
Override the compiler with `MINGW_GCC`. Flags use freestanding x86-64 PE,
Microsoft x64 startup, no host CRT and no red zone.
DOS64 provides the runtime import; Windows additionally requires a supplied
`bmetal.dll` beside the executable. When available in `bin/`, the build copies
that DLL to `build/`.
