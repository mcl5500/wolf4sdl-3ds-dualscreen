# Wolf4SDL 3DS DualScreen

An enhanced, feature-packed port of **Wolfenstein 3D** for the **Nintendo 3DS** family of systems, featuring real-time **Dual-Screen Automap**, **Stereoscopic 3D**, **Native Touch Virtual Keyboard**, and modern **WASD / Dual-Stick controls**.

Based on [Wolf4SDL](http://www.chaos-software.de.vu) and the initial 3DS port by hax0kartik.

---

## 🌟 Key Features

* **Stereoscopic 3D Display**:
  * Full hardware support for the 3DS **3D Depth Slider** and green 3D LED.
  * Native stereoscopic parallax rendering with optimized 1× VRAM usage (~1 MB vs previous >8 MB crashes).
  * Seamless transitions between 2D (slider down) and full stereoscopic 3D (slider up).
* **True Dual-Screen Experience**:
  * **Top Screen**: Clean 400×240 widescreen 3D maze with no HUD clutter.
  * **Bottom Screen**: Dedicated real-time **Live Automap** with line-of-sight Fog-of-War discovery, live player position and directional arrow, doors, pushwalls (secrets), enemy radars, and items.
* **Modern Dual-Stick / WASD Controls**:
  * **Circle Pad (Left)**: Full analog WASD movement — Up/Down to walk forward/back, Left/Right to **strafe** left/right.
  * **C-Stick (Right)**: Dedicated analog camera look and rotation (*New 3DS / Circle Pad Pro*).
  * **D-Pad**: Classic digital turning fallback.
* **Native Virtual Touch Keyboard (`swkbd`)**:
  * Official Nintendo 3DS touch screen keyboard applet integration for entering custom savegame names, High Score entries, and cheat/debug inputs.
* **Available Formats**:
  * Standalone **`.3dsx`** for the Homebrew Launcher.
  * Installable **`.cia`** for the 3DS HOME Menu featuring custom 3D banner artwork and high-res icon.
* **Compatible**: Supports official registered retail 6-episode game data (`.WL6`) as well as Shareware (`.WL1`).

---

## 🎮 Controls

| Button | Action |
| :--- | :--- |
| **Circle Pad** | **WASD Movement** (Walk Forward / Backward, **Strafe** Left / Right) |
| **C-Stick** *(New 3DS / CPP)* | **Camera Look** (Turn Left / Right) |
| **D-Pad** | Classic Digital Movement & Turning |
| **A / ZR** | Attack / Fire Weapon |
| **B** | Use / Open Doors / Push Secret Walls |
| **Y / ZL** | Run / Sprint |
| **L / R** | Previous / Next Weapon |
| **Start** | In-Game Menu / Pause |
| **Select** | Quick Pause |

---

## 📲 Direct 3DS Download (3dsDL / FBI)

Scan either QR code with **3dsDL** or **FBI** (*Remote Install -> Scan QR Code*) on your 3DS to download and install directly over the air:

| **Installable CIA** (HOME Menu) | **Standalone 3DSX** (Homebrew Launcher) |
| :---: | :---: |
| ![Installable CIA QR Code](assets/qrcode_cia.png) | ![Standalone 3DSX QR Code](assets/qrcode_3dsx.png) |
| [Download .CIA (v1.4.0)](https://github.com/mcl5500/wolf4sdl-3ds-dualscreen/releases/download/v1.4.0/Wolfenstein-3D-DualScreen.cia) | [Download .3DSX (v1.4.0)](https://github.com/mcl5500/wolf4sdl-3ds-dualscreen/releases/download/v1.4.0/wolf4sdl.3dsx) |

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
