# Deflection, flight and landing test (`--flight`)

> Historical development notes, preserved from the previous README. Statements describe the stage at which they were written and may not reflect the current implementation. Commands are run from the project root unless stated otherwise.

### Deflection, flight and landing test (`--flight`)

Run `LIONKING.EXE --flight` for the earlier automatic Simba flight test.
It chains the migrated deflection into the original right/left airborne
handlers `0x1aa97` / `0x1ae53`, then the landing selectors
`0x1b307` / `0x1b4a0`. Left/Right override the fixture's airborne direction.
Escape exits. Each fixture repeats after two seconds and stops at the selected
ground-state boundary; ordinary ground locomotion is not implemented here.
`--deflection` retains the shorter earlier test, `--emitters` the rock scene,
`--idle` automatic idle, and `--manual` the bank browser.

The airborne code preserves the original gate ordering, right-only upward
probe and counter-forced direction, left/right script-reset asymmetry,
edge sentinels `0xf8` / `0xe8`, fixed-point gravity at `0x20ea6` with the
flags-bit-2 cap bypass, anchor centering and direction changes. Landing
preserves signed duration/velocity thresholds, exact script/handler arguments,
flags and the right-only zeroing of vertical velocity.

An important original behavior: deflection sets the next handler **before**
calling it. The airborne handler therefore skips initialization on this path;
it must retain the running flip script instead of loading the nominal `0x6116`
argument. The test covers that continuation. Later visual records require
additional original banks, so the extended preview loads all 28 young banks.

This remains an explicit migration test, not a playable level. The ground at
Y=160, ceiling probe outcomes, absence of edge hits and repeated starting
position are synthetic dependencies. The original map queries `0x14c72`,
`0x170ae`, `0x174b2`, special-state handlers and ground states remain explicit
callback boundaries, never silently fabricated gameplay.

`tmp/tools/check_player_air.c` verifies both full airborne paths and 2752512
landing cases: all signed duration words, young/adult forms, signed velocity
thresholds, gate precedence, exact edge operands, probes, anchors and errors.
It also verifies 1966080 capped/uncapped player-gravity combinations.
`build/check_scene --flight` checks the actual flight entry for 20 seconds:
128064000 exact ARGB pixels, 2001 visible frames, 398 moving frames,
460 airborne frames and ten complete deflection-to-landing chains.
`build/check_scene --steering` additionally verifies two direction changes
from actual mocked DOS64 arrow input, pixel-for-pixel.
Compile `check_player_air.c` with the same engine source list as the preceding
player tests. Run `build/check_scene --deflection` and `--emitters` for the
previous scene regressions.
Real native QEMU verification produced 14724 changed viewport pixels and
repeated landing-boundary logs; Escape returned exit code zero.
