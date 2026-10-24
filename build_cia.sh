#!/usr/bin/env bash
set -e

echo "=== Building Wolf4SDL 3DS (.3dsx) ==="
make -j$(nproc)

echo "=== Packaging CIA ==="
mkdir -p build/cia/exefs

# Check for bannertool
if command -v bannertool >/dev/null 2>&1; then
    BANNERTOOL=bannertool
elif [ -f /home/sh3ld0r/Schreibtisch/PocketVoxel3D/tools/bannertool ]; then
    BANNERTOOL=/home/sh3ld0r/Schreibtisch/PocketVoxel3D/tools/bannertool
else
    echo "Warning: bannertool not found on PATH. Using existing SMDH/banner if available."
fi

# Check for makerom
if command -v makerom >/dev/null 2>&1; then
    MAKEROM=makerom
elif [ -f /home/sh3ld0r/Schreibtisch/PocketVoxel3D/tools/makerom ]; then
    MAKEROM=/home/sh3ld0r/Schreibtisch/PocketVoxel3D/tools/makerom
fi

# Build SMDH and banner if bannertool is available
if [ -n "$BANNERTOOL" ] && [ -f assets/icon.png ] && [ -f assets/banner.png ]; then
    $BANNERTOOL makesmdh -s "Wolfenstein 3D" -l "Wolfenstein 3D DualScreen" -p "id Software" -i assets/icon.png -o build/cia/icon.bin
    $BANNERTOOL makebanner -i assets/banner.png -o build/cia/banner.bin
fi

echo "Done! .3dsx is ready in current directory."
