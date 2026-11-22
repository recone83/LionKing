# LEVEL1 completion and next-level notice

The LEVEL1 completion path closes gameplay audio and plays the existing reward
scene. It then displays a notice that LEVEL2 is unavailable. Enter, Space or
Escape dismisses the notice after the triggering key has been released. The
menu path returns to the menu; `--map` returns to the launcher. No LEVEL2
gameplay, state transfer or progress saving is implemented.

The notice reuses the loaded title background and loads the menu font from
the game archive, including when `--map` bypasses menu initialization. Missing
font data or drawing failures return an error rather than claiming success.

`tools/check_victory.c` covers the menu and direct-map paths, reward skipping,
the notice image and acknowledgement keys, and missing-resource and audio
failures. The reward test injects the completion condition; the actual boss
behavior is tested separately by `tools/check_enemies.c`.
