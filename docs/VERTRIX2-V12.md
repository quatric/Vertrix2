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
