# Vertrix 3

Vertrix 3 v0.1 ("The Clusters", 2009) is the sequel: the same puzzle fight game with 19
characters, network play and Direct3D 9 rendering. This repository reads both games; this page
records what Vertrix 3 shares with Vertrix 2 and how that was established.

## The original

| | Vertrix 2 | Vertrix 3 |
| --- | --- | --- |
| Installer | (archive) | `Vertrix3-v0.1-Install.exe`, Inno Setup 5.2.3, sha256 `66129224…0477b77` |
| Executable | `Vertrix2.exe`, sha256 `4db546b7…525e28` | `Vertrix3.exe`, 1,368,576 bytes, sha256 `db625cfe…738f7e9` |
| Compiler | Watcom C/C++ (linker 2.18), register calling convention | Visual C++ 9 (linker 9.0), cdecl/thiscall |
| Video | DirectDraw (DirectX 8.1 required) | Direct3D 9 + D3DX |
| Input | DirectInput | DirectInput 8 |
| Sound | DirectSound + own XM mixer, MP3 decoder | the same mixer and decoder (see below) |
| Images | own BMP/PCX readers, IJG libjpeg 6b | IJG libjpeg 6b, libpng + zlib 1.1.4, PCX |
| Archive | `Vertrix2.vf`, VF v10, 1,525 entries | `vertrix3.vf`, VF v10, 2,201 entries |

The installer was unpacked with innoextract and was not run.

## Function signatures (`tools/v3_signatures.py`)

The two executables come from different compilers, so their instruction bytes rarely agree. A
function's signature is built from what a compiler change preserves:

- the strings it references;
- the imports it calls;
- its distinctive immediate constants;
- its floating constants. Watcom passes these to its runtime as integer immediates, while Visual
  C++ loads them from `.rdata`; both are reduced to the value.

Each Vertrix 2 routine is scored against Vertrix 3's functions by the tokens they share, weighted
by how rare each token is. Mutual best pairs that clear a threshold and a margin become anchors.
Matches then spread along the call graph in two ways:

- **By position:** callees in the same position of two matched functions pair up when their
  signatures agree.
- **By neighbours:** an unmatched function pairs with the one its matched callers and callees
  vote for.

```
python3 tools/v3_signatures.py path/to/Vertrix3.exe   # writes docs/v3-signature-matches.json
```

Result: 4,300 Vertrix 2 functions against 3,708 discovered in Vertrix 3 produced 137 pairs:

- 116 from signatures, 10 by call position and 11 by neighbours.
- 122 of the pairs are routines this port already has native C for.

The table lists each pair with its Vertrix 2 name or port and why it matched. Settings tuned for
coverage, such as field-offset tokens or data-table hashes, produced more contradictory pairs, so
the thresholds stay strict. The table favours precision over recall.

What matched, by subsystem:

- **Sound:**
  - The XM mixer and sequencer: note period, sample selection, retrigger, playback tick,
    sequence start and volume tables.
  - The module loader ("Extended Module: ").
  - The MPEG audio decoder: side info, Huffman decode, decode to memory.
  - The wave pump and the DirectSound device and record setup.
- **Images:** IJG libjpeg 6b throughout: marker reader, Huffman tables, IDCT, upsampler,
  quantizer and memory manager.
- **Input:** keyboard, mouse and joystick setup and poll.
- **Game:**
  - The settings defaults ("000.000.000.000", "PLAYER").
  - The menu choice dialogs (1PLAYER / 2PLAYERS / OPTIONS, practice, network).
  - Board frame, settle and place-extra.
  - Player piece creation, piece rise, animation end.
  - The network session start, address report and session names.
  - High-score and chat text, list text format, rotation tables, angle from ratio.
- **Runtime:** handle close and slots, string to long, file find, read-into, double to extended.

The game rules themselves (board, AI, bonuses) are mostly unmatched. Watcom code passes game state
in registers and refers to it by field offset, which leaves few compiler-independent tokens.
Vertrix 3 also reorganised its data around Direct3D textures. The matched board and player
routines are where tracing should start.

## Data (`tools/v3_assets_check.py`)

`source/vf.c`, the Vertrix 2 archive reader, opens and reads every one of the 2,201 Vertrix 3
entries unchanged. By content:

| Folder | Vertrix 2 | Vertrix 3 | Shared |
| --- | --- | --- | --- |
| `MUSIQUE` (XM) | 29 | 29 | all 29 byte-identical |
| `SON` (MP3, WAV) | 63 MP3, 13 WAV | 62 MP3, 24 WAV | 75 byte-identical |
| `TABLE` (sin/cos) | 3 | 3 | all byte-identical |
| `ANIM` (.ani text) | 142 | 142 | same names, extended text |
| `TEXTE` (.ini text) | 53 | 94 | 47 same names, rewritten |
| `IMAGE` (BMP/JPG/PCX), `SPRITE`, `FILTRE` | 1,222 | none | none |
| `TEXTURE` (PNG/PCX) | none | 936 PNG, 910 PCX | 498 PCX byte-identical to Vertrix 2 `IMAGE` PCX files |
| `MESHES` (.x) | none | 1 | none |

Every texture and sound effect was decoded by the shared loaders and compared with independent
decoders (Pillow, Python's `wave`). The result is in `docs/v3-assets-verification.json`:

- **PNG:** 936 of 936 match. These are 8-bit RGB and RGBA, not interlaced, decoded by
  `source/png.c` (a new inflate and unfilter).
- **PCX:** 910 of 910 match, using the existing `vertrix_image_pcx`.
- **WAV:** 24 of 24 match. Vertrix 3's 11 new effects are 16-bit mono, so `vertrix_audio_pcm16`
  was added beside `vertrix_audio_pcm8`.

The same check on `Vertrix2.vf` still passes: 529 PCX and 13 WAV.

## Two games in one repository

- `source/games.[ch]` names both games: title, SD directory, archive name and the executable
  hash the recovered code is checked against. `vertrix_game_of_archive` tells the archives apart:
  only Vertrix 3 has `texte\MeshesFileName.ini` and only Vertrix 2 has `texte\SpriteFileName.ini`.
  `tools/test_games.c` checks both archives.
- `vertrix_wii_archive_open_game` opens a given game's archive at `sd:/apps/vertrix3/vertrix3.vf`
  or `sd:/apps/vertrix2/Vertrix2.vf`, and refuses an archive that belongs to the other game.
  `vertrix_wii_archive_open` still opens Vertrix 2.
- Already shared by both games, with no changes:
  - the VF reader;
  - the XM loader, sequencer and mixer;
  - the MP3 decoder;
  - PCX, 8-bit WAV and the rotation tables.
- Added for Vertrix 3: PNG textures and 16-bit WAV.

## Running the game: `vertrix3/`

Vertrix 3 does not go through `tools/lift.py` and the routine-by-routine oracle. Those assume
Watcom's register convention and Vertrix 2's addresses. Instead, `vertrix3/recomp.py` turns every
function of `Vertrix3.exe` into C at once, and a small runtime supplies memory, threads, Win32,
Direct3D 9, DirectInput 8 and waveOut. The same generated code runs on the build machine
(software renderer) and on the Wii (GX renderer). `vertrix3/README.md` describes the build, the
runtime and the debug switches.

- Build machine: the game plays from the intro through the menus into a match (`a8d6ee3`).
  `x87_check.py` compares every x87 instruction form the game uses against a real x86 under
  Unicorn.
- Wii, in Dolphin at the Wii's own CPU speed: a scripted debug build went from the intro
  through the menu into a 1P vs computer match and on to the result screen, with GX drawing
  every frame. The release build boots into the menu. The guest heap is 32 MB of MEM2 (a match
  peaks near 25 MB), and GX's texture copies are evicted least-recently-drawn first when memory
  runs out.
- The display-mode confirmation (0x40f2c0) appears while the four saved display-mode globals are
  zero. 0x42af58 checks [0x5c7b65], and the globals are loaded at 0x452bd6. Quitting from the
  platform therefore closes the game's window, as Alt+F4 would, so the game saves
  `Settings/Vertrix3.cfg` and later launches skip the screen.

## Not done yet

- A run on real Wii hardware.
- Stencil (two masks in the board screens), fog and specular are not modelled in either renderer.
- The generated code does not reuse the Vertrix 2 ports. Where `docs/v3-signature-matches.json`
  pairs a function with a ported Vertrix 2 routine, that port could replace the generated C, but
  only once it passes the Unicorn oracle against the Vertrix 3 function. Argument passing and
  structure layouts differ between the two compilers.
