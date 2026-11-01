# DOS64 shared-executable SDK

This is the supplied SDK reference. Repository packaging commands and examples
below refer to upstream DOS64, not this game's build. For local layout, output
paths and current build limitations, see [README.md](README.md).

The same x86-64 PE executable runs on DOS64 and Windows. Windows requires
`bmetal.dll` next to the EXE; DOS64 binds the runtime import to its kernel.

The Windows backend supports text output, graphics/layers, keyboard and mouse,
timers, optional audio, files/directories, host device/volume reporting and
cooperative threads (Windows fibers on the calling OS thread).
Raw disk access is unavailable (`Present=0`; callbacks return EFI_UNSUPPORTED).
DOS64-only legacy PE files are rejected; rebuild them with shared startup.
ELF programs remain supported on DOS64.

## Build and distribution

For a ready-to-copy Linux development kit, run `bash sdk/package.sh` from the
repository root. It creates `build/sdk-kit/` with headers, the DLL, import
library, startup object, a matching EFI kernel, standalone image-building and
QEMU launch scripts, a buildable example and a walkthrough for compiling
on Linux, running the existing headless QEMU image test, and preparing a
portable image for interactive use. See the kit's README for the walkthrough.
The test emulator is QEMU + OVMF, not Bochs.

From the repository root, run `bash sdk/build.sh`, or `make` to build the kernel
and SDK. Set `MINGW_GCC` to override the MinGW-w64 compiler.

The distributable directory is `build/sdk/`:

```text
include/                 public API and runtime headers
bin/bmetal.dll           Windows runtime
lib/libbmetal.dll.a      MinGW import library
lib/dos64_startup.o      shared startup object
README.md                this guide
```

Applications include the public headers, initialize the wrappers they use,
and provide `int __attribute__((ms_abi)) start(const DOS64_API *Api)`.
Do not import Windows services or the C runtime directly from the EXE.

When using the distributed SDK, from its directory:

```bash
x86_64-w64-mingw32-gcc -m64 -O2 -ffreestanding -nostdlib -nostartfiles \
    -fno-stack-protector -mno-red-zone \
    -Iinclude -Wl,-e,dos64_entry -Wl,--subsystem,console -Wl,--dynamicbase \
    app.c lib/dos64_startup.o -Llib -lbmetal -o app.exe
cp bin/bmetal.dll .
```

Deploy only `app.exe` and `bmetal.dll` on Windows. Deploy only `app.exe` on DOS64.
The DLL may use Windows system libraries internally; the EXE imports only
`Dos64Run` from `bmetal.dll`.

The default startup requires runtime API 1.0, DOS64 table version 14 and text,
graphics, input, time, filesystem and system services. Audio is optional. Requirements are checked
before application code: a runtime providing 0.7 cannot launch an EXE requiring
1.0. The negotiation ABI is independent of the DLL release number.

## Batched rectangles (API version 13)

`DOS64_API.FillRects` accepts an array of `DOS64_RECT` values, each with its
own color, in one API call. `gfx_fill_rects` uses this callback when the API
table contains it and falls back to individual `SetColor`/`FillRect` calls for
older, shorter API tables. This avoids a runtime transition and draw-metric
instrumentation per rectangle.

## Image drawing (API version 14)

`gfx_draw_image` draws and scales a source image from an array of
`DOS64_COLOR` pixels. Pass the source width, height and row stride (in pixels),
then the destination position and size. The API callback is used when present;
otherwise the wrapper falls back to drawing scaled pixels individually.

## Example and validation

`bash programs/build.sh` produces all 15 examples as shared executables and copies
the DLL and sample data beside them in `build/programs/w64/`. Run `alphademo.exe --selftest` for
five seconds, or `alphademo.exe` until Escape. Closing its Windows window also
requests Escape.

Graphical examples (alphademo, breakout, cubedemo, edit, fpsdemo, gfxdemo and maze3d)
use `--subsystem,windows` so launching them opens only the program window.
Maze3D replaces the old input sample with an original maze shooter: W/S or Up/Down
move, A/D strafe, Left/Right turn, Shift sprints, Space/left click fires, R restarts
and Escape exits. Destroy six robots (three green scouts, two blue guards,
one orange heavy with increasing health, speed and damage) and reach the green
minimap exit. Quick shots are buffered between physics steps. Footsteps, gunfire and destruction sounds are
synthesized on a cooperative worker; no external assets are needed.
The weapon bobs with actual movement and smoothly settles at rest.
Text-oriented examples retain `--subsystem,console`. The runtime does not
allocate a new console for GUI executables; it can attach to an existing
parent terminal, and redirected output is preserved. GUI failures without a
terminal or redirected output show an error dialog.

`mixer.exe` is a text-oriented master-volume utility: Up/Down or typed +/- adjust
volume in 5% steps and play a 150 ms tone; Space previews and Escape exits.
It opens 48000 Hz, 16-bit stereo and prints buffer availability. Since the API
has no volume getter, it explicitly starts at 70% rather than claiming to read
the current setting. `mixer.exe selftest` previews at 75% and exits after draining.
DOS64 images install it in `C:\BDOS`; the existing API is sufficient, with no ABI
or runtime version change.

## Cooperative threads

Include `dos64_thread.h` and check `thread_init(Api) == 0`. API table version 11
appends `Threads` without moving existing fields:

- `thread_start(entry, argument, stack_bytes)` returns a nonzero handle, or zero
  with a runtime diagnostic. The callback is
  `void * __attribute__((ms_abi)) entry(void *argument)`. Returning finishes the
  worker and publishes its result.
- `thread_pause()` yields round-robin to another runnable thread.
- `thread_wait(handle, &result)` waits cooperatively, then frees the worker stack.
  The result pointer is optional. Success is zero; invalid/stale handles,
  self/main joins, multiple joiners and join cycles return -1 with a diagnostic.
- `thread_current()` returns the current handle; the main thread is handle 1.

There are at most 15 worker threads plus main, including finished but unjoined
workers. Stack size zero selects 64 KiB; explicit sizes must be 16 KiB through
1 MiB and are rounded up to whole pages. Stack-local callback arguments must
remain valid until the worker finishes. Returned pointers must not refer to the
worker's stack, which join frees. Each thread preserves its x87/SSE state.
AVX is not supported on DOS64. Kernel stacks have no guard page or overflow
recovery; callbacks must stay within their allocated stack.

Scheduling happens at yield, join, sleep, mutex contention and condition waits,
not during input polling, graphics or filesystem calls. A non-yielding worker blocks all other application
threads. Graphics state, input, current directory and open-file tables are shared;
do not yield in the middle of a multi-call operation that depends on that state
or while holding a critical section. Kernel context switches preserve CPU flags,
including the interrupt-enable state. These are not preemptive or multicore
threads, there is no TLS, and this is not a pthread implementation.

When the main application returns, suspended and unjoined workers are discarded
and their stacks freed before code is unloaded. Their callbacks are not resumed
and no destructors or cancellation handlers run. Join workers explicitly for
orderly application cleanup. `threaddemo` demonstrates two interleaved workers;
It also demonstrates producer/consumer notifications while main sleeps.
`--cleanup-test` returns with an unfinished worker to exercise runtime cleanup.

### Mutexes, conditions and sleep (API version 12)

Check `thread_sync_init(Api) == 0` before using the synchronization wrappers.
The appended `Sync` table leaves all version 11 thread callbacks at their original
offsets. Each application can create 32 mutexes and 32 conditions. Creation returns
a nonzero handle or zero with a diagnostic; other synchronization calls return
zero on success or -1 with a diagnostic.

- `mutex_create`, `mutex_lock`, `mutex_unlock`, `mutex_destroy`: mutexes are
  non-recursive, owner-checked, with FIFO handoff to waiting threads. A worker
  returning with a held mutex poisons it; pending and future lock calls fail.
  Destroying a locked mutex or one referenced by a condition wait is rejected.
- `condition_create`, `condition_wait(condition, mutex)`, `condition_signal`,
  `condition_broadcast`, `condition_destroy`: wait requires ownership, registers
  the waiter and releases the lock without a scheduling gap. It reacquires the
  mutex before successful return. Signal wakes the oldest blocked waiter;
  broadcast wakes all. Notifications are not stored when nobody is waiting.
  Always check a shared predicate in a loop under the mutex; notification does
  not guarantee that the predicate is still true when a waiter reacquires it.
  All outstanding waits on a condition must use the same mutex. Destroying a
  condition is rejected until its wait calls have returned, including signaled
  waiters still reacquiring a mutex.
- `thread_sleep_ms(ms)` and `Api->Sleep(ms)` block only the calling thread until
  its monotonic deadline; zero yields. Runnable peers continue, and the runtime
  idles when all remaining runnable work is waiting on timers. This is not a
  realtime guarantee; a non-yielding peer can delay wakeup.

Join/mutex dependency cycles and an absence of runnable threads or pending
timers produce errors instead of spinning indefinitely. Condition-wait failure
attempts to reacquire its mutex; if that fails (for example, a poisoned mutex),
the caller must not assume it owns the lock. No timed condition wait, recursive
mutex, cancellation or robust-mutex recovery is provided yet. All synchronization
objects are discarded during application cleanup and stale handles are rejected.

## Queues and background audio

### Bounded message queues

`dos64_queue.h` provides a header-only, fixed-size FIFO using API version 12
mutexes and conditions. Zero-initialize a `DOS64_QUEUE`, then call
`queue_init(&queue, Api, storage, capacity, item_bytes)` with caller-owned storage
of at least `capacity * item_bytes` bytes. Messages are copied by value; copying
a pointer does not transfer ownership of the pointed-to data.

`queue_send` and `queue_receive` block cooperatively on full/empty queues.
`queue_try_send` and `queue_try_receive` never wait for capacity/data (they still
acquire the internal mutex). Return values are `QUEUE_OK` (0), `QUEUE_CLOSED` (1),
`QUEUE_WOULD_BLOCK` (2, try calls only), or `QUEUE_ERROR` (-1 with a diagnostic).
`queue_close` is idempotent, rejects new sends and wakes all blocked peers;
receivers can drain already queued items before receiving `QUEUE_CLOSED`.
Close, join all users, then `queue_destroy`; destruction rejects active waiters.
Do not copy a live queue or begin operations while it is being destroyed.
One queue consumes one mutex and two conditions. See `threaddemo` and
`bash tests/thread.sh` for producer/consumer and shutdown examples.

### Background WAV playback

`dos64_audio_stream.h` provides `WAV_STREAM` without changing the synchronous
`wav_pump` API. Open the WAV, zero-initialize the stream, and call
`wav_stream_start(&stream, Api, &wav)`. Alternatively, initialize the source with
`wav_open_pcm(&wav, samples, frame_count, rate)` for borrowed interleaved 16-bit
stereo PCM. Keep those samples alive and unchanged until the worker is joined.
A cooperative worker decodes/writes at
most 1024 stereo frames per turn, handles partial writes, and sleeps between
batches while the main thread polls input or does other bounded work.

`wav_stream_status` is a non-switching cooperative snapshot: 0 running, 1
finished after the hardware queue drains, or -1 on a read/write failure.
`wav_stream_stop` closes the worker's control queue, joins it, stops audio and
destroys synchronization objects; it returns -1 if playback or cleanup failed.
If stop fails while `stream.Worker` is still nonzero, the worker has not been
joined: keep the stream/WAV storage alive and retry stop before closing it.
Only close the WAV or release its storage after the worker is joined. One stream
owns the shared audio device and WAV/file state: do not pump, seek, close or modify
them concurrently, and do not open another audio stream while it is active.
There is no preemptive or realtime guarantee; long non-yielding work can still
starve playback. `wavplay` and `sounddemo` use this helper. `sounddemo` plays
from memory without disk I/O; `sounddemo --save` additionally writes and retains
`TUNE.WAV` before playback, so that optional mode can pause on slow storage. Validate with
`bash tests/audio-stream.sh`.

## Filesystem behavior

Windows file paths are UTF-8, relative to the process working directory, with
normal Windows drive letters and permissions; there is no DOS64 FAT32 drive
mapping. File modes are binary, at most eight files may be open, and remaining
handles are closed on return. Seek/tell offsets are signed 64-bit on both hosts.
LastError returns EFI-style statuses, including EFI_NOT_FOUND for absent files.
Rename does not overwrite an existing destination. Directory entries use the
existing 256-byte UTF-8 name and 32-bit size limits; unrepresentable metadata
reports an error. System storage counts accessible mounted Windows volumes;
partition numbers are unavailable (zero) and writable indicates the volume
read-only flag, not a guarantee that Windows permissions allow a write.

DOS64 QEMU and Wine checks exercise the shared file; native Windows remains
a required release validation target. Wine alone is not proof of native
Windows graphics/audio compatibility.
