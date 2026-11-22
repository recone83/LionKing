# API 16 heap migration

The DOS64 adapter requires API 16 and uses `dos64_memory.h` for its major
mutable buffers. The platform allocates the ARGB framebuffer, the game
allocates a zeroed block for level maps, render buffers, sprite banks and audio
samples, and the frontend allocates its title, menu and reward resources when
needed. Bonus resources have their own allocation. Array capacities and the
existing resource validation remain unchanged; this does not add support for
larger archive variants.

Audio streams stop before the relevant buffers are freed. Initialization,
allocation and release failures are reported through the platform log and
return an error. Small state objects, lookup tables, music players and object
pools remain statically allocated; the gameplay algorithms are unchanged.
Allocation and release occur on the main thread. The lower-level page API is
not used, preserving Windows compatibility.

Validation includes the native PE build, host integration tests for gameplay,
frontend, bonus and framebuffer rendering, and injected allocation/release
failures. A DOS64 KVM run exercised `--bonus-check` followed by `--map` and
returned successfully to the shell. A Windows-runtime `--bonus-check` run
under Wine also returned successfully; Wine is not a native Windows test.
