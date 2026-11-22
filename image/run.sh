#!/usr/bin/env bash
set -euo pipefail
cd -- "$(dirname -- "$(readlink -f -- "${BASH_SOURCE[0]}")")"

if [ "$#" -gt 1 ]; then
    echo "Usage: bash run.sh [image.img]" >&2
    exit 2
fi
Image=${1:-dos64.img}
Firmware=${OVMF_PATH:-/usr/share/OVMF/OVMF_CODE.fd}
AudioDriver=${QEMU_AUDIO_DRIVER:-pa}
if ! command -v qemu-system-x86_64 >/dev/null 2>&1; then
    echo "Missing qemu-system-x86_64; install qemu-system-x86." >&2
    exit 1
fi
if [ ! -r /dev/kvm ] || [ ! -w /dev/kvm ]; then
    echo "The current DOS64 image requires accessible KVM; enable KVM and check /dev/kvm permissions." >&2
    exit 1
fi
if [ ! -f "$Firmware" ]; then
    echo "Missing UEFI firmware: $Firmware; install ovmf or set OVMF_PATH." >&2
    exit 1
fi
if [ ! -f "$Image" ]; then
    echo "Missing image: $Image; creating it."
    bash ./build-image.sh "$Image"
fi

exec qemu-system-x86_64 \
    -m 1G -accel kvm -cpu host -smp 4 \
    -device qemu-xhci -device usb-kbd -device usb-mouse \
    -device usb-storage,drive=u,removable=on \
    -drive "if=none,id=u,file=$Image,format=raw" \
    -drive "if=pflash,format=raw,readonly=on,file=$Firmware" \
    -audiodev "$AudioDriver,id=snd0" -device intel-hda -device hda-output,audiodev=snd0 \
    -net none -no-reboot -display "${QEMU_DISPLAY:-gtk}" -serial stdio -monitor none
