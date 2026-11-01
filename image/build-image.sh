#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$(readlink -f -- "${BASH_SOURCE[0]}")")"

if [ "$#" -gt 1 ]; then
    echo "Usage: bash build-image.sh [new-image.img]" >&2
    exit 2
fi
Image=${1:-dos64.img}
if [ -e "$Image" ] || [ -L "$Image" ]; then
    echo "Refusing to overwrite $Image; choose a new image filename." >&2
    exit 1
fi
for Tool in sfdisk mkfs.vfat mcopy mmd truncate mktemp; do
    if ! command -v "$Tool" >/dev/null 2>&1; then
        echo "Missing $Tool; install mtools, dosfstools and util-linux." >&2
        exit 1
    fi
done
if [ ! -f BOOTX64.EFI ] || [ ! -f ../build/lionking.exe ]; then
    echo "Requires image/BOOTX64.EFI and build/lionking.exe; run bash build.sh from the project root first." >&2
    exit 1
fi

Temporary=$(mktemp -d "$(dirname "$Image")/.dos64-image.XXXXXX")
cleanup() {
    rm -f "$Temporary/disk.img" "$Temporary/autoexec.txt"
    rmdir "$Temporary"
}
trap cleanup EXIT
trap 'exit 130' INT
trap 'exit 143' TERM

SystemStart=2048
SystemSectors=102400
DataStart=$((SystemStart + SystemSectors))
DataSectors=204800
ExtraStart=$((DataStart + DataSectors))
ExtraSectors=159744
Disk="$Temporary/disk.img"
truncate -s "$(((ExtraStart + ExtraSectors) * 512))" "$Disk"
printf 'label: dos\nunit: sectors\nstart=%s, size=%s, type=ef, bootable\nstart=%s, size=%s, type=c\nstart=%s, size=%s, type=c\n' \
    "$SystemStart" "$SystemSectors" "$DataStart" "$DataSectors" \
    "$ExtraStart" "$ExtraSectors" | sfdisk "$Disk" >/dev/null
mkfs.vfat -F 32 -I -n EFI --offset="$SystemStart" "$Disk" "$((SystemSectors / 2))"
mkfs.vfat -F 32 -I -n DOS64_C --offset="$DataStart" "$Disk" "$((DataSectors / 2))"
mkfs.vfat -F 32 -I -n DOS64_D --offset="$ExtraStart" "$Disk" "$((ExtraSectors / 2))"

export MTOOLS_SKIP_CHECK=1
System="$Disk@@$((SystemStart * 512))"
Data="$Disk@@$((DataStart * 512))"
mmd -i "$System" ::/EFI ::/EFI/BOOT
mcopy -i "$System" BOOTX64.EFI ::/EFI/BOOT/BOOTX64.EFI
mmd -i "$Data" ::/GAMES ::/GAMES/LIONKING
mcopy -i "$Data" ../build/lionking.exe ::/GAMES/LIONKING/LIONKING.EXE
printf '@ECHO OFF\r\nCD C:\\GAMES\\LIONKING\r\nLIONKING.EXE\r\n' > "$Temporary/autoexec.txt"
mcopy -i "$Data" "$Temporary/autoexec.txt" ::/AUTOEXEC.BAT

# A hard link publishes the completed image without replacing an existing path.
ln "$Disk" "$Image"
echo "Created $Image; C: starts at byte $((DataStart * 512))."
echo "Boot from the image directory with: bash run.sh \"$Image\""
