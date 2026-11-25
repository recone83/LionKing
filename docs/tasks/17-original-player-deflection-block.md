# Original player deflection block

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Original player deflection block

`LIONKING.EXE --deflection` runs a larger migrated player behavior segment,
not a replacement platformer. It cycles eight diagnostic cases using the
original `SYFLIPBW.MCH` / `SYFLIPFW.MCH` banks (slots 11/12):
two selectors, two visual-script ranges and probe off/on. Escape exits.
The original selectors, motion and animation run automatically, then pause at
the boundary to the still-unported ordinary player state.

Recovered from `tmp/recovered/block_0c000.c` and verified against the EXE:

- `0x1e36e` / `0x1e3bf`: signed contact ranges `[4,16]` and `[32,48]`
  select the ordinary handler; other values delegate to the script selector.
- `0x1e667` / `0x1e6ee`: wrapped original script-pointer subtraction,
  `SAR 1`, low-word mask and index `1..24` choose exact handler, DS script
  and counter `20` or `50`. Any nonzero form selects adult data.
- `0x1e410` / `0x1e545`: initialization at vertical velocity -5, 16 motion
  updates and the next-update transition; directional stop controls, damage
  gate, coordinate probe, collision flags **OR** `0x20`, original scripts,
  fixed-point integration and horizontal velocity -3/+3.
- `0x20e37`: player gravity +`0x4e00` for young / +`0x6000` for adult,
  with the original signed upper cap +7.

The probe is an explicit dependency for unported `0x174b2`. Its synthetic
results and the repeated starting position are test fixtures. Transitions to
`0x1aa97`, `0x1ae53` and damage `0x1ef04` are explicit callbacks, not fabricated
implementations. The preview stops at those boundaries. Original addresses
in `ENGINE_PLAYER_CALL` are data only, never invoked as native pointers.
The emitter scene (`--emitters`) and `--idle` / `--manual` modes remain available.

`tmp/tools/check_player_reactions.c` checks 11010048 calls, including every signed
contact word, wrapped pointer indices and young/adult forms.
`tmp/tools/check_player_deflection.c` runs the whole segment through the object
dispatcher: 1632 original-script updates, exact descriptors, velocity and
fractional coordinates, directional asymmetry, probe/stop/damage gates and
missing-dependency errors. Build these tests with the generated animation data
and `behaviors.c`, `animation.c`, `render.c`, `sprites.c`, `physics.c`,
`objects.c`, `input.c`.
`build/check_scene --deflection` additionally runs the actual entry for 20
seconds, verifies 128064000 ARGB pixels, all eight cases, 320 moving frames,
20 exact transition boundaries and Escape.
The player test also checks 1966080 gravity cases across all fractional Y
values, signed overflow and the +7 cap. Native QEMU verification showed
28624 changed viewport pixels and a successful Escape exit with code zero.
