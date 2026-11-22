# DOS64 SDK kit

The SDK kit contains the headers, runtime import library, startup object, and
example source needed to build x86-64 Windows-format PE applications for DOS64
and Windows. It does not include an automated image builder or QEMU launcher.

## Contents

```text
include/                 public DOS64 API and wrapper headers
bin/bmetal.dll           Windows runtime DLL
lib/libbmetal.dll.a      MinGW linking/import library
lib/dos64_startup.o      standard PE startup object
elf_startup.c            ELF entry adapter source
hello.c                  minimal SDK application example
SDK.md                   API, ABI and runtime reference
README.md                compile and test instructions
```

## Compile the example

From the kit directory, use MinGW-w64 to build the example:

```bash
x86_64-w64-mingw32-gcc -m64 -O2 -Wall -Wextra -Werror \
    -ffreestanding -nostdlib -nostartfiles -fno-stack-protector -mno-red-zone \
    -Iinclude -Wl,-e,dos64_entry -Wl,--subsystem,console -Wl,--dynamicbase \
    hello.c lib/dos64_startup.o -Llib -lbmetal -o bin/hello.exe
```

Set `MINGW_GCC` to use a different compiler executable. Applications implement
`int start(const DOS64_API *Api)`. Keep the
`dos64_entry` entry point and startup object; DOS64 does not support legacy PE
startup. See [SDK.md](SDK.md) for the API and runtime details.

On Windows, keep `bin/bmetal.dll` beside the generated executable. DOS64
provides the runtime imports through its kernel, so the DLL is not needed there.
GUI-subsystem DOS64 applications show a bMETAL runtime/system-information splash
for three seconds on Windows before the application starts; this does not change
DOS64 boot behavior or console-subsystem applications.
Native Linux cannot run the PE executable directly.

For DOS64 ELF builds with Linux GCC, compile `elf_startup.c` together with
the application, using `-Iinclude` and `-Wl,-e,dos64_elf_entry`. The adapter
translates the loader's Microsoft x64 ABI to GCC's native System V ABI.
API function pointers and callbacks still use their declared ABI; only `start`
uses the compiler's native ABI. Existing PE and ELF binaries remain compatible.

```bash
gcc -m64 -ffreestanding -nostdlib -nostartfiles -fPIC -fno-stack-protector \
    -mno-red-zone -fno-unwind-tables -fno-asynchronous-unwind-tables -O2 \
    -shared -Wl,-e,dos64_elf_entry,-Bsymbolic,--build-id=none,-z,defs,-z,max-page-size=4096 \
    -Iinclude hello.c elf_startup.c -o hello.lnx
```

## Portable API

The public SDK exposes services supported by both runtimes. Cooperative
threads remain available. DOS64-only raw disk access, live-mapped pages, and
parallel-thread requirements remain internal to the DOS64 source tree. Their
table slots are reserved to preserve binary compatibility.

## Program heap

Current source provides API 16 heap allocation through `dos64_memory.h`:

```c
#include "dos64_memory.h"

/* In start(), on the main thread: */
if (memory_init(Api) != 0) return 1;
void *data = memory_alloc(10u * 1024u * 1024u);
if (data == NULL) return 1;
/* Read data with Api->Fs.Read and use it. */
if (memory_free(data) != 0) return 1;
```

`memory_alloc`, `memory_calloc`, `memory_realloc`, and `memory_free` provide
malloc-style operations, but are not a complete C standard library. Call
`memory_init(Api)` in every translation unit using these helpers. PE apps may
require `DOS64_SERVICE_HEAP` using `DOS64_REQUIRE_SERVICES` (once per app);
the service is implemented in both the current DOS64 and Windows runtimes.
Applications need an API 16 SDK and matching runtime; older API 14 builds do
not include it.

Allocations are contiguous and 16-byte aligned; their size is limited by
available contiguous RAM, heap fragmentation, and up to 128 backing arenas,
not the separate 64-page live-mapping limit. DOS64 uses identity-mapped
physical RAM, with no process isolation or per-allocation execution guarantee.
Memory is not initialized by `memory_alloc`; `memory_calloc` clears it and
rejects multiplication overflow. Zero-size allocation returns NULL.
`memory_realloc(NULL, size)` allocates; `memory_realloc(ptr, 0)` frees and
returns NULL. A failed nonzero reallocation leaves the old allocation intact.
`memory_free(NULL)` succeeds; otherwise it returns 0 on success and -1 for an
invalid pointer or a backing-page release failure. On a backing release failure
the allocation has still been relinquished, and the runtime logs the error.
Empty arenas are returned to the runtime; outstanding arenas are reclaimed
when the app exits after its workers stop. These calls are main-thread-only.
Applications must synchronize access to
shared data and stop workers before freeing it.

Run `bash tests/program-heap.sh` for host allocator tests and
`bash tests/sdk-heap-qemu.sh` for a 10 MiB file and reallocation test in DOS64.

## Test in DOS64

The repository provides the tested QEMU + OVMF workflow. From the repository
root, package the SDK and build the kernel, then copy the executable into the
test programs directory and run the headless QEMU test:

```bash
bash sdk/package.sh
mkdir -p build/programs/w64
cp build/sdk-kit/bin/hello.exe build/programs/w64/sdkhello.exe
bash tools/qemu-test.sh -t 90 'C:\EXAMPLES\W64\SDKHELLO.EXE sdk-test'
```

The helper creates a fresh test image and checks serial output. Expected output
includes:

```text
HELLO FROM THE DOS64 SDK
ARGS: sdk-test
```

The final `RESULT:` must report `failed=0`. See the repository README and
`tools/qemu-test.sh` for other test options.
