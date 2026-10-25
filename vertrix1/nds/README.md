# Vertrix (1997) on the Nintendo DSi

`nds_main.c` runs the recompiled `VERTRIX.EXE` on a DSi, or on a 3DS in DSi mode. It's the same
generated C and the same DOS machine (`../runtime/`) as the build machine, the Wii and the Mac,
behind a driver for the DS hardware: the two 2D engines, the ARM7's sound channels, the buttons
and the SD card.

## Why the DSi and not the DS

The game doesn't fit in a DS's 4 MB of main memory. On the build machine, a 1P vs CPU match
needs:

| What | Size |
| --- | --- |
| The PC's first megabyte (the image at its link addresses, DOS memory, the VGA window) | 1 MB |
| The runtime's system area | 1 MB |
| What the game takes from DPMI (`int 31h` 0501h), at its peak in a match | about 3.1 MB |
| The generated code (Thumb, `-Os`) and the image | 1.9 MB |

That comes to about 7 MB. The DSi has 16 MB, so the program runs in DSi mode only. The build
names the generated code's objects and the image's `*.twl.o`, and calico's linker script loads
them into the DSi's own load area. On a DS the loader leaves that area out, and the program only
says why it can't start the game.

## Build

```
make -C vertrix1 V1_EXE=/path/to/VERTRIX.EXE PYTHON=/path/to/python nds   # build/v1/nds/vertrix1.nds
```

It needs devkitARM with libnds 2 and calico (`DEVKITPRO`, `/opt/devkitpro` by default). Python
needs Capstone 5 and pefile for `recomp.py`, and Pillow for the icon (`tools/console_art.py
nds-icon`). The ROM header is DSi-enhanced (unit code 2).

## Install

Copy `vertrix1.nds` to the SD card, and the whole original release next to it in a folder called
`vertrix1/`: `VERTRIX.EXE`, `VXSCORES.EXE`, `BIN1.BIN`, `BIN2.BIN`, the text and batch files, and
`FILE_ID.DIZ`. The game checks every file `BIN2.BIN` lists. The program looks for the release in
these places, in order:

1. `vertrix1/` beside the `.nds` (from the path the loader passes in `argv[0]`)
2. `sd:/vertrix1/`
3. `fat:/vertrix1/` (a flash card)

Start the game from a loader that boots DSi-enhanced homebrew in DSi mode, such as TWiLight Menu++
or hiyaCFW. The game writes `SETUP.CFG`, its scores and `vertrix.log` in its folder.

The first run shows the game's setup screen. Choose SFX&MUSIC, then AUTODETECT (it finds 220h,
IRQ 7, DMA 1), then EXIT twice.

## Controls

| Button | Key |
| --- | --- |
| D-pad | arrows (the one-player keys; player 2 in a two-player game) |
| B | Up (permute) |
| A | Enter |
| X, Select | Escape |
| Start | P (pause) |
| Y | F: player 1 permutes in a two-player game |
| L, R | W, X: player 1 moves left, right in a two-player game |
| L+R+Start | back to the loader |

The game saves its setup only when you leave through its own EXIT. L+R+Start leaves it where it
is.

## How the driver works

- **Picture:** the VGA's 320x400 mode X picture fills both screens. The top half goes on the top
  screen and the bottom half on the bottom screen, each scaled to 256x192 by the engine's affine
  background. Each engine shows an 8-bit 512x256 bitmap: bank A on the main engine, bank C on the
  sub engine.
- **Frame copy:** at each VBlank after a VGA retrace, the main thread copies the planes the CRT
  controller scans out (`v1_vga_scan`) into the bitmaps. Each 32-bit word is the four planes'
  bytes at one address, which is four pixels, because VRAM takes no byte writes. The DAC
  (`v1_vga_palette`) goes to both palettes.
- **Threads:** the game runs on a calico thread with a 256 KB stack, below the main thread's
  priority. The main thread therefore preempts it at each VBlank to read the buttons and copy the
  picture, while the game is stopped between instructions.
- **Sound:** the Sound Blaster's 8-bit samples go round a 16 KB ring that channel 0 repeats at
  the Sound Blaster's rate. They're converted from unsigned to signed, and the write position
  stays about 60 ms ahead of the channel. When no sound comes for 150 ms, the channel stops so the
  ring's old samples don't play again.
- **Memory:** the DPMI heap is 6 MB (`NDS_HEAP`). Guest memory uses 64 KB pages (`V3_PAGED`). The
  ARM9 runs at 134 MHz (`setCpuClock(true)`).
- **Clock:** `v3_microseconds` comes from calico's tick counter, and `v3_sleep_ms` is
  `threadSleep`.

## Status

What's been checked:

- **Build:** the ROM builds with devkitARM 16.1, libnds 2.0 and calico. The DS part of the ARM9
  binary is 174 KB, and the DSi part is 1.8 MB (the generated code and the image), within the
  2.5 MB calico allows.
- **On a DS:** in melonDS 1.1 in DS mode, the program boots and shows its "needs a Nintendo DSi"
  message.
- **Frame copy:** a host test of `nds_main.c`'s word packing gives the same pixels as
  `v1_vga_render_indexed`. It covered mode X at 320x400 and the 320x200, dword, pitch and
  start-address variants.
- **CPU load:** on the build machine, about 1% of the game's CPU time is its own code. The rest is
  waiting for the retrace and reading the clock.

What hasn't been checked:

- **DSi mode:** the game hasn't run in DSi mode yet. melonDS needs a DSi's BIOS and NAND dumps for
  that, and DeSmuME 0.9.13 shows only a white screen for DSi-enhanced homebrew.
- **Speed:** whether a DSi's 134 MHz ARM9 holds 70 frames a second of guest time is unknown.
- **Sound:** the sound ring's timing hasn't been heard on hardware.
