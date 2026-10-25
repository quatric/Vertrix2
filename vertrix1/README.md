# Vertrix (1997), recompiled

The original DOS Vertrix runs here from its own executable. `recomp.py` turns every function of
`VERTRIX.EXE` (an LE program under PMODE/W, built with Watcom C) into C. A small runtime then
supplies the PC the game ran on: DOS and the DPMI extender, the VGA, the timer, the keyboard and
a Sound Blaster. The same generated code runs on the build machine (frames written as PPM, sound
as WAV), on the Wii (GX, ASND, Wii Remotes, SD card) and on the DSi (both screens, the ARM7's
sound channels, the buttons, SD card; `nds/README.md`).

Nothing of the game is in this repository. The build reads `VERTRIX.EXE`
(sha256 `4785d692…1866f04`). The game reads its data from the original release, which must be
complete: the game checks every file `BIN2.BIN` lists. `docs/VERTRIX1.md` records the
executable, the recompilation and every hardware access, with the evidence for each.

## Layout

| Path | What |
| --- | --- |
| `recomp.py` | the LE loader (objects, fixups, Watcom debug names); x86 to C on top of `vertrix3/recomp.py`: segments, ports, interrupts, far calls |
| `runtime/machine.c` | start-up, descriptors, interrupt delivery, the 8259 PICs, the 8253 PIT, the keyboard controller, the BIOS data |
| `runtime/dos.c` | `int 21h` (files in the game's folder as `C:\VERTRIX`), `int 31h` (DPMI), `int 10h`, `16h`, `1Ah`, `2Fh`, `33h` |
| `runtime/ports.c` | the I/O port map |
| `runtime/vga.c` | the VGA: planes, latches, registers, DAC, retrace timing, the picture |
| `runtime/sb.c` | the 8237 DMA controller and the Sound Blaster 2.0 DSP |
| `runtime/shared.c` | `vertrix3`'s CPU helpers and guest memory, built for this machine |
| `host/host_main.c` | the build-machine driver |
| `wii/wii_main.c` | the Wii driver: video, SD, controllers, ASND |
| `wii/vertrix.xml` | the Homebrew Channel's meta file |
| `nds/nds_main.c` | the DSi driver: both screens, SD, buttons, the ARM7's sound channels |
| `nds/README.md` | the DSi build: why DSi mode only, install, controls, status |
| `mac/mac_main.c` | the Mac driver, on `mac/shell.h` |
| `assets.py`, `assets.html` | unpacks `BIN1.BIN` (pictures, palettes, sounds, instruments, music as modules) and the page that shows it |

## Build and run on the build machine

```
make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE PYTHON=/path/to/python host
build/v1/v1_host build/v1/gen/v1_image.bin GAME_DIR OUT_DIR [seconds] [frame_every] [args...]
```

- **Python:** `recomp.py` needs Capstone 5 and pefile, which `vertrix3/recomp.py` imports.
- **The game's folder:** `GAME_DIR` holds the unpacked release. The game writes `setup.cfg` and
  its scores there.
- **Output:** `OUT_DIR` receives `frame_NNNNNN.ppm` every `frame_every` retraces (70 a second),
  `sound.wav` (8-bit mono at the Sound Blaster's rate) and `vertrix.log`.
- **Arguments:** these are the game's own. `-auto` autodetects the Sound Blaster, and `-setup`
  opens the setup screen.

Environment:

- `V1_SCRIPT="3 key 1c 1; 3.1 key 1c 0"` presses and releases keys at guest seconds. The codes
  are set 1 scan codes in hex; 0x1xx adds the E0 prefix, so 148 is Up.
- `V1_TRACE=1` logs every host call.
- `V1_WATCH=hex` logs each entry of a function.
- `V1_PEEK="addr:bytes,..."` logs guest memory every second.

The first run shows the setup screen. Choose SFX&MUSIC, then AUTODETECT, which finds 220h,
IRQ 7, DMA 1; then EXIT twice. The game saves `setup.cfg` and starts. The build machine reaches
the Clusters logo, the title with its music, the player and background select, the versus
screen and a 1P vs CPU match.

## The game's data

```
make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE PYTHON=/path/to/python assets   # build/v1-assets/
python3 -m http.server --directory build/v1-assets
```

`assets.py` reads `BIN1.BIN` from the folder that holds `VERTRIX.EXE` (or `V1_BIN1=`). It writes:

- every entry, unpacked, into `raw/`;
- the pictures as PNG, with the palette the game shows them with;
- the sound effects and the 171 instruments as WAV;
- each tune as a module with its instruments, and an MP3 of it when `openmpt123` and `lame` are
  on the PATH;
- `index.html`, the page that shows all of it. The page reads `data.js`, so open it through a
  web server.

`docs/VERTRIX1.md` ("The data formats") describes each format and where the game reads it.

## The Wii

```
make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE wii                 # build/v1/vertrix.dol
make -C vertrix1 V1_EXE=... wii-sync SYNC=/path/to/sd           # apps/vertrix/: boot.dol, meta.xml, icon.png
```

Copy the whole original release into `sd:/apps/vertrix/`: `VERTRIX.EXE`, `VXSCORES.EXE`,
`BIN1.BIN`, `BIN2.BIN`, the text and batch files and `FILE_ID.DIZ`.

How the driver works:

- **Threads:** the game runs on its own thread. The main thread shows the VGA's current picture
  on every TV frame, scaled to fill a 4:3 picture, with pillarboxes on a 16:9 TV.
- **Sound:** the Sound Blaster's samples play on an ASND voice at their own rate.
- **Memory:** the DPMI heap is 8 MB (`WII_HEAP`); the game asks for about 4 MB. Guest memory
  uses 64 KB pages (`V3_PAGED`).
- **Log:** the log is `sd:/apps/vertrix/vertrix.log`.

| Control | Key |
| --- | --- |
| D-pad, Nunchuk or Classic stick | arrows (the one-player keys; player 2 in a two-player game) |
| B | Up (permute) |
| A, 2 | Enter |
| 1, Minus | Escape |
| Plus | P (pause) |
| Second Wii Remote: D-pad left/right/down, Up or B | W, X, C, F: player 1's default keys in a two-player game |
| USB keyboard | itself |
| HOME | back to the loader |

The game saves its setup only when left through its own EXIT. HOME leaves it where it is.

## The DSi

```
make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE PYTHON=/path/to/python nds   # build/v1/nds/vertrix1.nds
```

The game needs about 7 MB with its code, so the program runs in DSi mode only (on a DSi, or on a
3DS in DSi mode). On a DS it says so. Copy the release into `vertrix1/` beside the `.nds`.
`nds/README.md` has the controls, how the driver works and what has been tested so far.

### Debug builds

To build a debug DOL:

```
make -C vertrix1 BUILD=../build/v1dbg GEN=../build/v1/gen \
    WII_DEBUG='-DV1_WII_SHOTS=140 -DV1_WII_SCRIPT="\"3 key 1c 1; 3.1 key 1c 0; 40 quit 0 0\""' wii
```

- `V1_WII_SHOTS` saves every Nth frame as `sd:/apps/vertrix/shots/frameNNNNN.ppm`.
- `V1_WII_SCRIPT` presses keys as `V1_SCRIPT` does. A `quit` step ends the run.

In Dolphin, with the SD folder synchronised, this build reached the setup, the title, the
player select and a 1P vs CPU match at full speed (59–60 frames a second). The log counted
22,222 samples a second reaching the sound voice.
