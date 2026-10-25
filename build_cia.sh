#!/usr/bin/env bash
set -e

echo "=== Building Wolf4SDL 3DS (.3dsx) ==="
if command -v arm-none-eabi-gcc >/dev/null 2>&1 && [ -n "$DEVKITARM" ]; then
    make -j$(nproc)
else
    echo "Running build via Docker devkitpro/devkitarm:latest..."
    docker run --rm -v "$(pwd)":/workspace -w /workspace devkitpro/devkitarm:latest bash -c "make -j\$(nproc)"
fi

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
    $BANNERTOOL makesmdh -s "Wolfenstein 3D" -l "Wolfenstein 3D DualScreen" -p "id Software" -i assets/icon.png -f allow3d -o build/cia/icon.bin
    if [ -f assets/audio.wav ]; then
        $BANNERTOOL makebanner -i assets/banner.png -a assets/audio.wav -o build/cia/banner.bin
    else
        $BANNERTOOL makebanner -i assets/banner.png -o build/cia/banner.bin
    fi
fi

if [ -n "$MAKEROM" ] && [ -f wolf4sdl.elf ] && [ -f build/cia/icon.bin ] && [ -f build/cia/banner.bin ]; then
    echo "=== Packaging CIA with makerom ==="
    $MAKEROM -f cia -o Wolfenstein-3D-DualScreen.cia -elf wolf4sdl.elf -rsf wolf.rsf -icon build/cia/icon.bin -banner build/cia/banner.bin -exefslogo -target t
    echo "CIA created successfully: Wolfenstein-3D-DualScreen.cia"
fi

echo "Done! .3dsx and .cia are ready in current directory."
