# Default test: original ground locomotion and connected player states

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Default test: original ground locomotion and connected player states

Run with `--preview` (without arguments the main menu opens).
Ground idle/input is no longer fabricated: this diagnostic
preview connects ten more original handlers:

| State | Original code addresses |
| --- | --- |
| Left/right ground idle | `0x1c2cd`, `0x1c8d5` |
| Right/left running | `0x1cdc2`, `0x1d108` |
| Turning to left/right | `0x1beb7`, `0x1c0a1` |
| Left/right crouching | `0x1b9ca`, `0x1bc80` |
| Right/left rolling | `0x1ea46`, `0x1eb56` |

All preview modes write diagnostics to `LIONKING.LOG` in the working
directory, replacing the previous run's log. They do not render console
text over the game. The file is closed on exit, including error exits.
If logging fails, the preview stops and reports the failure after rendering
has ended.

The original ground reset `0x1c28e` and existing capped acceleration helper
complete this block. Running accelerates by `+/-0x4000`, preserves signed
`+/-0x20000` minimum and `+/-0x40000` maximum, turns through the original
animation, stops through the original idle scripts, and selects a different
jump script from standing. Landing resumes the selected ground handler,
not a synthetic frozen frame. Down crouches while idle; Down at sufficient
running speed enters the original roll, slowing by `0xe00` per update.

Left/Right run, Down crouches/rolls, Space jumps (hold to prolong ascent),
Ctrl roars, and Escape exits. Any of those inputs takes over the automatic
twelve-second demo: movement/jumps, two roars, then an injected diagnostic
hit and original recoil. H injects another test hit; T enables one second
of synthetic terrain contact, cycling kinds 6/9/5/8 on successive presses.
These two keys also take over the demo. Manual input does not
teleport/restart Simba. The renderer follows X
using the existing original viewport clamps; camera-follow policy is a
fixture, not the original full game camera controller.

Ground support at Y=160, no walls/edges/ceiling hits and the automated
input sequence remain explicit fixtures. Real level collision, enemy hit
detection, adult attacks and progression actions remain explicit callback
boundaries. The ground code nevertheless preserves their
selection, ordering and operands, including the left-crouch fallthrough and
left-run flag asymmetry. Roll/recovery sound requests are logged, not played.
Long-idle animation events also remain diagnostic.
