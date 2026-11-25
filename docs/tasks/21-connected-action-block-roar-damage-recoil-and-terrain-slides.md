# Connected action block: roar, damage, recoil and terrain slides

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Connected action block: roar, damage, recoil and terrain slides

The default preview also migrates eight original handlers and their
generic vertical-motion helper, without replacing the original scripts:

| State | Original code addresses |
| --- | --- |
| Roar | `0x1ec69` |
| Passive reaction animation | `0x1ee35` |
| Grounded stun | `0x1ee60` |
| Damage and recoil selection | `0x1ef04` |
| Left/right-facing recoil | `0x1f017`, `0x1f160` |
| Rolling terrain slide | `0x1f80d` |
| Grounded/airborne slope slide | `0x1fe3c`, `0x1ff83` |

There are nine addresses in this table: the eight persistent state
handlers plus the immediate damage selector. `0x1a6ff` preserves generic
`0x4e00` gravity even for adult Simba, support checks and airborne
contact reset. Recoil starts at Vy=-3 and Vx=+1/-1, lasts 18/40 ticks, then
selects original ground or air behavior. Damage preserves masks,
immunity=100, positive-health decrement, source-side selection and the
grounded-stun exception. The original right-recoil form-bit test is
preserved, not replaced with a symmetric nonzero-form check.

Roar emits the charge pulse at age 14/30, clears it on the following
tick and returns to the original idle at age 55/94. Sound requests 2/3
are logged only. Calls to `0x1510c` are genuine RET stubs in the original
binary, not invented effects. The right-facing roar now passes counter=0,
the left-facing roar counter=1, matching the original assembly.

H's source position, T's terrain contacts, initial health/roar charge
and the absence of meter recharge/immunity ticking are diagnostic
fixtures. There is no enemy receiving the roar pulse yet, and no sound
playback. The grounded-stun and passive-animation paths are migrated but
not part of the default young-Simba sequence.

Earlier preview modes are retained: `--jump`, `--flight`, `--deflection`,
`--emitters`, `--idle`, `--manual`. The focused ground harness is
`tmp/tools/check_player_ground.c`; `build/check_scene` exercises the connected
default entry and `--ground-steering` its manual controls.
`tmp/tools/check_player_actions.c` covers the action and terrain block.
