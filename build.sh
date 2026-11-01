#!/usr/bin/env bash
set -euo pipefail
ScriptDir=$(dirname -- "$(readlink -f -- "${BASH_SOURCE[0]}")")
cd -- "$ScriptDir"

if [ "$#" -ne 0 ]; then
    echo "Usage: bash build.sh (compile only; image/run.sh launches DOS64)" >&2
    exit 2
fi

if [ ! -f src/dos64/start.c ]; then
    echo "Build unavailable: src/dos64/start.c is not implemented yet." >&2
    echo "The DOS64 start(const DOS64_API *) adapter and recovered game code must be made compilable first." >&2
    exit 1
fi

Compiler=${MINGW_GCC:-x86_64-w64-mingw32-gcc}
if [ -z "${MINGW_GCC:-}" ] && ! command -v "$Compiler" >/dev/null 2>&1 &&
    [ -x "$HOME/.local/share/dos64-mingw/usr/bin/x86_64-w64-mingw32-gcc-posix" ]; then
    Compiler="$HOME/.local/share/dos64-mingw/usr/bin/x86_64-w64-mingw32-gcc-posix"
fi
if ! command -v "$Compiler" >/dev/null 2>&1; then
    echo "Missing MinGW-w64 compiler: $Compiler; install gcc-mingw-w64-x86-64 or set MINGW_GCC." >&2
    exit 1
fi

mkdir -p build
Temporary=$(mktemp -d "$ScriptDir/build/.lionking.XXXXXX")
cleanup() {
    rm -f -- "$Temporary/lionking.exe"
    rmdir -- "$Temporary"
}
trap cleanup EXIT
trap 'exit 130' INT
trap 'exit 143' TERM

"$Compiler" -m64 -O2 -Wall -Wextra -Werror -ffreestanding -nostdlib -nostartfiles \
    -fno-stack-protector -mno-red-zone -Iinclude -Isrc \
    -Wl,-e,dos64_entry -Wl,--subsystem,windows -Wl,--dynamicbase \
    src/dos64/start.c src/dos64/platform.c lib/dos64_startup.o -Llib -lbmetal \
    -o "$Temporary/lionking.exe"
mv -- "$Temporary/lionking.exe" build/lionking.exe
if [ -f bin/bmetal.dll ]; then
    cp bin/bmetal.dll build/bmetal.dll
fi
echo "Built build/lionking.exe. Windows additionally requires bmetal.dll beside it."
