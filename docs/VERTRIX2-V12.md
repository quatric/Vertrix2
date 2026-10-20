# Vertrix 2 v1.2

Vertrix 2 v1.2 is the 2001 release, two years before v2.0, the version the recovered code comes
from. This page records how the two differ and how this repository supports v1.2.

## The original

| | v1.2 | v2.0 |
| --- | --- | --- |
| Installer | `Vertrix2-v1.2-Install.exe`, sha256 `3c647c2e…3ebd231`: a Petite-packed self-extracting ACE 1.0 solid archive | (archive) |
| Executable | `Vertrix2.exe`, 1,201,664 bytes, sha256 `8e27c76d…4141999` | 1,261,568 bytes, sha256 `4db546b7…525e28` |
| Link time stamp | 2001-05-28 | 2003-03-05 |
| Linker | Watcom 2.18 | Watcom 2.18 |
| Entry point | `0x4df8b4` | `0x4eb454` |
| Code (AUTO) | 0x0e3c00 bytes | 0x0efa00 bytes |
| Imports | 378, the same as v2.0's but DirectInput 1 (`DirectInputCreateA`) | 379: DirectInput 8 (`DirectInput8Create`) and `CoInitializeEx` |
| Archive | `Vertrix2.vf`, VF v10, 1,446 entries | VF v10, 1,525 entries |

The installer was not run. Its ACE main header marks no advert string but still carries the
advert's empty length byte, so acefile 0.6.14 reads the comment size one byte early and rejects
the archive. Setting the advert flag in a copy of the archive (and its header CRC) lets acefile
extract all five files: `Vertrix2.exe`, `Vertrix2.vf`, `Manual.chm`, `File_id.diz` and
`SXUNINST.EXE`. Every file's CRC checks. The archive comment is "(c) 2001 The Clusters".

## Code (`tools/v12_compare.py`)

Both executables come from the same Watcom linker, so a routine that did not change between the
releases has the same instructions, only moved. The tool reduces each function to its bytes with
the moving fields masked: the dwords the loader relocates (from each file's `.reloc`) and every
rel8/rel32 branch and call displacement. It pairs functions whose masked bytes are equal and
unique, then spreads pairs through matching call sites. The result is in
`docs/v12-function-matches.json`.

- **1,584 of v2.0's 4,280 functions** are unchanged in v1.2, a third of v2.0's code. **1,227** of
  them are among the 3,833 routines the dispatcher serves as ports.
- The unchanged code is the engine and the C runtime: the mixer (0x401010), MP3 synthesis and
  IMDCT (0x405720, 0x4088e0), surfaces and blits, fonts (0x482e10), libjpeg, the heap (0x4ca000,
  0x4e7c90) and the runtime library (0x4d0000-0x4effff: 682 of 908 match).
- The game itself was largely rewritten between the releases: in 0x420000-0x46ffff (board, AI,
  players, bonuses, screens) only 101 of 1,259 functions are unchanged. The board settle 0x432980
  and the line pass 0x4346b0 are (at v1.2's 0x42e380 and 0x42ffa0); the figure pass 0x434ee0, the
  AI search 0x4270a0, the AI tick 0x43b430 and the screen builders are not.

Because the ports address v2.0's globals and data layout directly, an unchanged routine is a
candidate for reuse in v1.2 only once it passes the oracle against the v1.2 function, as for
Vertrix 3.

## Data (`tools/v3_assets_check.py`)

- 826 archive entries are byte-identical to v2.0's, 586 changed (475 PCX images, 34 JPEG, 23 XM,
  21 `Filtre/*.flt`, 18 BMP, 10 INI) and 34 exist only in v1.2 (logos, a loading screen, a story
  picture, a font).
- v2.0 added the bombs and blobs: `texte\BombesFileName.ini`, `texte\Blob1..5.ini`,
  `texte\BlobsFileName.ini` and `image\Bombes\*` exist only there.
- The shared loaders read v1.2's data unchanged: all 514 PCX images match Pillow and all 13 WAVs
  match Python's `wave` (`docs/v12-assets-verification.json`).
- `source/games.[ch]` names v1.2 (`VERTRIX_GAME_2_V12`, `sd:/apps/vertrix2-v12`).
  `vertrix_game_of_archive` tells it from v2.0 by `texte\BombesFileName.ini`.
  `tools/test_games.c` checks all three archives.

## Running v1.2

v2.0's playable build runs its recovered routines through the dispatcher, with a host layer
(`source/lift_host.c`) that serves Windows, DirectDraw and DirectInput 8. That host layer is tied
to v2.0's addresses (its float helpers, MPEG tables, palette and timer thread), and two thirds of
v1.2's game code has no port. So v1.2 takes the route Vertrix 3 took (`vertrix3/README.md`): the
whole executable recompiled to C, on a runtime that supplies the Windows interfaces it imports.

```
make -C vertrix3 BUILD=../build/v12 V3_EXE=/path/to/Vertrix2.exe PYTHON=python3 host
build/v12/v3_host build/v12/gen/v3_image.bin GAME_DIR OUT_DIR [seconds] [frame_every]
```

`recomp.py` recognizes the executable by its sha256 and tells the runtime the directory and name
it runs as (`C:\Vertrix2\Vertrix2.exe`). v1.2 plays its credits and menus, a tournament's story
screens, the player select, a 1P vs CPU match and its result screen, and saves `Vertrix2.cfg`
on exit. It polls the mouse from its 14 ms multimedia timer once the intro ends (about five
seconds in on the build machine, about 42 seconds in Dolphin).

### Reaching a match

The game is driven by the mouse:

1. On the main menu, click 1PLAYER, then TOURNAMENT.
2. The tournament introduces each character on a spiral, as a story ending in PREPARE TO FIGHT.
   A click skips to the next story; the last one leads to the player select.
3. On the player select, click GO (the middle picture, at about (310, 135)). The versus screen
   follows.
4. Click YES under READY TO FIGHT to start the match.

The game puts the cursor back at the centre of the screen (320, 240) on each new screen, and a
mouse unit moves it two pixels. With no input the computer wins, and the game shows LOSER &
WINNER with CONTINUE? YES NO.

The story screens take real time, so a script clicks at intervals instead of at fixed moments.
This one reached the result screen on the build machine:

```
S="20 move 0 25; 22 button 0 1; 22.1 button 0 0; 25 move 0 27; 26 button 0 1; 26.1 button 0 0"
for t in $(seq 40 4 116); do S="$S; $t button 0 1; $t.1 button 0 0"; done
S="$S; 124 move -2 -52; 126 button 0 1; 126.1 button 0 0; 134 move 56 102; 136 button 0 1; 136.1 button 0 0"
V3_SCRIPT="$S" build/v12/v3_host build/v12/gen/v3_image.bin GAME_DIR OUT_DIR 175 10000
```

The Wii build reached it in Dolphin with the same steps about 38 seconds later, as
`V3_WII_SCRIPT` with a final `quit` step:

- 58 and 64 for the two menu clicks;
- clicks every 4 seconds from 80 to 160;
- GO at 172 and YES at 184.

The Wii build shows 30 frames a second.

What v1.2 needed beyond Vertrix 3:

- **Recompiler** (`vertrix3/recomp.py`):
  - Watcom 2.18 writes `repne movsd` (f2 a5) in `memcpy`; Capstone drops that prefix, so the
    repeat is read from the raw bytes (`mnemonic_of`).
  - Switches that shift the index before the jump (`shl eax, 2; jmp [eax + table]`), bounded by
    a `cmp` on the index's stack slot.
  - Function starts after zero padding or Watcom's idle filler (`lea edx, [edx + 0]`,
    `mov eax, eax`), and the function a fixed-address pointer holds at load (`call [0x4fce13]`).
  - The start-up tables, 16-bit pops and `call [esp + n]` (see the commit that read v1.2 beside
    v2.0).
- **Runtime** (`vertrix3/win32`):
  - `ddraw.c`: DirectDraw 7 with surfaces in guest memory, `Blt`/`BltFast` (stretching, colour
    fills, source colour keys, mirroring), an attached back buffer and `Flip`, palettes and
    clippers. The game sets 640x480 at 32 bits, so the flipped surface goes to the platform as
    it is.
  - `gdi32.c`: MFC's device contexts, fonts, brushes and text measurements, drawing nothing.
  - `advapi32.c`: a registry held in memory for the run.
  - `shell32.c`: the shell, common controls, common dialogs and the print spooler MFC links.
  - `winmm.c`: `timeSetEvent`/`timeKillEvent`, each timer on its own thread.
  - `dinput8.c`: `DirectInputCreateA` (DirectInput 1).
  - `kernel32.c`, `user32.c`: the rest of MFC's calls (window hooks, properties, `wsprintfA`).
