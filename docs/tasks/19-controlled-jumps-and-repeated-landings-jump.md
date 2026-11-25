# Controlled jumps and repeated landings (`--jump`)

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Controlled jumps and repeated landings (`--jump`)

Run `LIONKING.EXE --jump`. This preview runs the original jump handlers
`0x1b604` / `0x1b7e7`, jump-hold helper `0x1b5ac`, airborne handlers and
landing selectors. Before keyboard takeover it demonstrates short and held
jumps in both directions, starting a new case every two seconds.

- Space takes control and starts a jump when ready on the ground.
- Hold Space to prolong the original ascent boost; releasing it stops the boost.
- Left/Right change facing on the ground fixture and direction while airborne.
- After landing, Space starts another jump without restarting the executable.
- Escape exits; `--flight`, `--deflection`, `--emitters`, `--idle` and `--manual`
  preserve the earlier previews.

The migration retains the original launch scripts (`6180/5944`), continuation
scripts (`612c/5928`), young/adult startup delays (4/10), vertical velocity,
8/6 boost ticks, hold flag `0x1000`, momentum flag `0x2000`, direction changes
without reinitializing the jump, ceiling handling and adult early transition
to the airborne handler at velocity -3. Collision-mask writes are bitwise
AND/OR, not the decompiler's substituted constants.

Landing recovery handlers `0x1b19f` / `0x1b253` are also migrated: exact
16-bit countdown, surface-kind-3 interruption, damage gate, sound request
4/5, and handler replacement before the final animation tick. The native
fixture explicitly logs the unported audio request rather than pretending
to play it. Ordinary jumps do not force recovery when the original selector
chooses a different ground state.

This is still a diagnostic stage, not a complete level: ground Y=160,
no ceiling/edge hits, ground-idle/input handling and automatic repositioning
are fixtures. Ground running, actual map collision and special states remain
unported. Long idle events are explicitly logged without their gameplay
side effects. Manual jumps are not automatically restarted or repositioned.

`tmp/tools/check_player_jump.c` verifies 393210 nonzero delay cases, 393216
recovery countdown cases, 4608 boost combinations and 218 independently
traced ascent ticks, including adult/young forms, fractions, word wrapping,
probe ordering, gates, same-handler continuation and dependency errors.
Compile it with the same engine source list as `check_player_air.c`.

`build/check_scene --jump` checks 20 seconds of the jump entry: 128064000
exact ARGB pixels, 2001 visible frames, 350 moving frames, 768 airborne frames,
and nine complete jumps/landings. `build/check_scene --jump-steering` tests
four manual jumps, eight direction transitions, sustained idle events and
Space height control: held jumps rise at least 40 pixels higher than short
jumps. Real QEMU showed Simba jumping, 13824 changed viewport pixels,
manual keyboard takeover and an Escape exit with code zero.
