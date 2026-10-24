# Wolf4SDL 3DS DualScreen

An enhanced port of **Wolfenstein 3D** for the **Nintendo 3DS** family of systems, featuring real-time **Dual-Screen Automap**, **New 3DS C-Stick analog looking**, and modern dual-analog controls.

Based on [Wolf4SDL](http://www.chaos-software.de.vu) and the initial 3DS port by hax0kartik.

---

## 🌟 Key Features

* **True Dual-Screen Experience**:
  * **Top Screen**: Clean 400×240 widescreen 3D maze with no HUD clutter.
  * **Bottom Screen**: Dedicated real-time **Live Automap** with line-of-sight Fog-of-War discovery, live player position and directional arrow, doors, pushwalls (secrets), enemy radars, and items.
* **Modern Twin-Stick Controls**:
  * **Circle Pad (Left)**: Calibrated analog movement and turning with smooth deadzone compensation.
  * **C-Stick (Right)**: Dedicated analog camera look/rotation (*New 3DS / Circle Pad Pro*).
  * **Circle-Strafing**: Hold `X` to strafe with the Circle Pad while maintaining full camera aim with the C-Stick.
* **Available Formats**:
  * Standalone **`.3dsx`** for the Homebrew Launcher.
  * Installable **`.cia`** for the 3DS HOME Menu featuring custom 3D banner artwork and high-res icon.
* **Compatible**: Supports official registered retail 6-episode game data (`.WL6`) as well as Shareware (`.WL1`).

---

## 🎮 Controls

| Button | Action |
| :--- | :--- |
| **Circle Pad** | Walk Forward / Backward, Turn Left / Right |
| **C-Stick** *(New 3DS / CPP)* | Smooth Analog Camera Look (Turn Left / Right) |
| **D-Pad** | Classic Digital Movement & Turning |
| **A / ZR** | Attack / Fire Weapon |
| **B** | Use / Open Doors / Push Secret Walls |
| **X** | Strafe *(Hold while moving Circle Pad to strafe)* |
| **Y / ZL** | Run / Sprint |
| **L / R** | Previous / Next Weapon |
| **Start** | In-Game Menu / Pause |
| **Select** | Quick Pause |

---

## 📂 Installation

> [!IMPORTANT]
> **No copyrighted game files are included with this repository.** You must provide your own legally obtained Wolfenstein 3D data files (`.wl6` or `.wl1`).

1. Download the latest `.cia` or `.3dsx` from the [Releases](https://github.com/) section.
2. Place your Wolfenstein 3D data files in:
   ```
   sdmc:/3ds/wolf4sdl/
   ```
   *(Required files for full 6-episode registered version: `AUDIOHED.WL6`, `AUDIOT.WL6`, `CONFIG.WL6`, `GAMEMAPS.WL6`, `MAPHEAD.WL6`, `VGADICT.WL6`, `VGAGRAPH.WL6`, `VGAHEAD.WL6`)*
3. **If using CIA**: Install `Wolfenstein-3D.cia` using **FBI** or **3dsDL**, then launch it directly from the HOME Menu.
4. **If using 3DSX**: Place `wolf4sdl.3dsx` into `sdmc:/3ds/wolf4sdl/` and launch it via the Homebrew Launcher.

---

## 🛠️ Building from Source

### Prerequisites
* [devkitPro](https://devkitpro.org/) with `devkitARM` and 3DS portlibs (`libctru`, `citro3d`, `3ds-sdl`, `3ds-sdl_mixer`).
* Alternatively, use the official Docker image `devkitpro/devkitarm:latest`.

### Compiling with Docker
```bash
docker run --rm -v $(pwd):/workspace -w /workspace devkitpro/devkitarm:latest bash -c "source /opt/devkitpro/3dsvars.sh && make clean && make -j$(nproc)"
```

### Compiling Locally
```bash
source /opt/devkitpro/3dsvars.sh
make -j$(nproc)
```

---

## 📜 Credits & Licenses
* **id Software** for creating the legendary *Wolfenstein 3D*.
* **Moritz "Ripper" Kroll** for [Wolf4SDL](http://www.chaos-software.de.vu).
* **hax0kartik** for the initial 3DS port.
* **devkitPro & libctru developers** for the 3DS homebrew toolchain.

Licensed under the GNU General Public License v2 (GPL-2.0). See [license-gpl.txt](license-gpl.txt) for details.
