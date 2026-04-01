#!/bin/bash
set -e

SERIAL="$1"
CONFIG="$2"
BUILD="$3"
OBJCOPY="$4"

if [[ -z "$SERIAL" ]]; then
    echo "usage: $0 <SERIAL> (e.g. SLUS_206.22)" >&2
    exit 1
fi

ROM=$CONFIG/rom
CHECKSUM_FILE="$CONFIG/checksum.sha"

BUILD_BIN="$BUILD/$SERIAL"
ROM_BIN="$ROM/$SERIAL"

BUILD_ROM="$BUILD_BIN.rom"
ROM_ROM="$ROM_BIN.rom"

$OBJCOPY -O binary "$BUILD_BIN" "$BUILD_ROM"
$OBJCOPY -O binary "$ROM_BIN" "$ROM_ROM"

source_sha=$(sha256sum "$BUILD_ROM")
target_sha=$(sha256sum "$ROM_ROM")

echo "source executable sha256: $source_sha"
echo "target executable sha256: $target_sha"

if sha256sum -c "$CHECKSUM_FILE"; then
    echo "🟣 ROMs 100% match!"
    exit 0
else
    echo "🔴 mismatch"
    exit 1
fi
