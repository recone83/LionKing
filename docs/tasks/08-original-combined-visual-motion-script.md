# Original combined visual/motion script

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

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
