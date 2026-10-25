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

## 📂 Step-by-Step Installation & Data Setup

> [!IMPORTANT]
> **No copyrighted game files are included with this port.** You must provide your own legally obtained Wolfenstein 3D data files (`.wl6`).

### 1. Requirements
* A Nintendo 3DS / 2DS family console running modern custom firmware (**Luma3DS**).
* An official copy of the **Wolfenstein 3D Full Version (6 Episodes)**.
  * Available on [Steam](https://store.steampowered.com/app/2270/Wolfenstein_3D/) or [GOG](https://www.gog.com/game/wolfenstein_3d).
  * *Note: Shareware (`.wl1`) files are not compatible with this 6-episode registered build.*

### 2. Locate Your Game Data Files
If you own the game on Steam or GOG, you can find the data files here:
* **Steam**: `<SteamLibrary>/steamapps/common/Wolfenstein 3D/base/`
* **GOG**: `C:/GOG Games/Wolfenstein 3D/` (or your GOG installation folder)

You need the following **8 files**:
| File Name | Description |
| :--- | :--- |
| `vswap.wl6` | Wall textures, sprite graphics, and digitized sound effects |
| `gamemaps.wl6` | Level maps for all 6 episodes |
| `maphead.wl6` | Map header data and tile pointers |
| `vgagraph.wl6` | VGA UI graphics, fonts, and menus |
| `vgahead.wl6` | Graphics header offset table |
| `vgadict.wl6` | Huffman dictionary for graphics compression |
| `audiot.wl6` | Music and AdLib/Sound Blaster sound effects |
| `audiohed.wl6` | Audio header offset table |

> [!TIP]
> **Check the file extension:**
> * The extension is **`.wl6`** with a letter **L** (lowercase `l` or uppercase `L`), **not** the number `1` and **not** the capital letter `I`.
> * Both lowercase (`vswap.wl6`) and uppercase (`VSWAP.WL6`) are supported.

### 3. SD Card Folder Structure
Insert your 3DS SD card into your PC (or use FTP / MicroSD Management) and place the files into `sdmc:/3ds/wolf4sdl/`:

```
SD Card Root
└── 3ds/
    └── wolf4sdl/
        ├── audiohed.wl6
        ├── audiot.wl6
        ├── gamemaps.wl6
        ├── maphead.wl6
        ├── vgadict.wl6
        ├── vgagraph.wl6
        ├── vgahead.wl6
        ├── vswap.wl6
        └── wolf4sdl.3dsx    <-- (Optional: only needed if using Homebrew Launcher)
```
*(Files placed in `sdmc:/3ds/wolf4sdl/wolf3d/` are also automatically detected).*

### 4. Install & Play
* **CIA Version (Recommended)**:
  1. Copy `Wolfenstein-3D-DualScreen.cia` to your SD card (e.g. `/cias/`).
  2. Open **FBI** on your 3DS, navigate to `SD` -> `cias` -> `Wolfenstein-3D-DualScreen.cia` -> **Install CIA**.
  3. Exit FBI and unwrap the new gift on your 3DS HOME Menu!
* **3DSX Version (Homebrew Launcher)**:
  1. Copy `wolf4sdl.3dsx` into `sdmc:/3ds/wolf4sdl/`.
  2. Launch the **Homebrew Launcher** and start **Wolfenstein 3D DualScreen**.

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
