# Vertrix (1997)

Vertrix v5.1 ("The Clusters", 1997, freeware) is the first game of the series: a DOS puzzle fight
game in 320x400 with 256 colours, Sound Blaster sound and MOD music. This page records what the
executable is, how it is recompiled, and what each of its hardware accesses does. Every claim
names the evidence behind it. The port itself is described in `vertrix1/README.md`.

## The original

| File | Size | What |
| --- | --- | --- |
| `VERTRIX.EXE` | 564,700 | the game, sha256 `4785d692…1866f04` |
| `VXSCORES.EXE` | 56,403 | the high score viewer (same format; not ported) |
| `BIN1.BIN` | 3,596,624 | the data archive, sha256 `3bab1ca7…b4fde5a` |
| `BIN2.BIN` | 242 | the release's file list: names and sizes |
| `README.TXT`, `LISEZMOI.TXT` | | the English and French manuals |
| `INSTALL.BAT`, `SETUP.BAT`, `README.BAT`, `LISEZMOI.BAT`, `FILE_ID.DIZ` | | the installer, launchers and description |

The archive was unpacked for reading. None of its programs or batch files were run.

### The executable

`VERTRIX.EXE` is an LE executable bound to the PMODE/W v1.33 DOS extender and linked by Watcom
C/C++32. Everything below was read from the file by `vertrix1/recomp.py` (`LEProgram`):

- **LE header:** at file offset 0x2d00, after the PMODE/W stub.
- **Objects:** two.
  - Object 1 is the code, at 0x10000 (virtual size 0x4cbfc).
  - Object 2 is the data and the stack, at 0x60000 (virtual size 0x1e780). The initial esp is
    0x7e780.
- **Entry:** 0x4e160 (`_cstart_`).
- **Fixups:** 15,491 records, all internal 32-bit offsets (type 7). The loader lays the objects
  at their link addresses, so no fixup changes a value. The fixups still tell code addresses
  from numbers during discovery.
- **Debug information:** the Watcom debug information (version 3, signature 0x8386) is still
  appended to the file. It holds 205 modules and 2,273 global symbols. The game is one module,
  `D:\DISKD\BORLANDC\BIN\SOURCE\THEAUDIO\VERTRIX.C`. Its sound is Carlos Hasan's MODPLAY
  (`modplay.asm`). The rest is the Watcom C library and its graph library.

Every function name on this page is a symbol from that debug information. Names ending in `_`
are Watcom's register-convention functions. Names without the trailing `_` in `VERTRIX.C` are
data.

### BIN1.BIN and BIN2.BIN

`BIN1.BIN` starts with `u16 count` (135). It then has `count` entries of
`char name[16]; u32 size; u32 offset`. The data follows the table: the first offset is
3,242 = 2 + 135 × 24, and the last entry ends at the file's size.

At start-up `BIN_CHECK_GENERAL_` (0x1e214) opens every file `BIN2.BIN` names. It compares each
size and refuses to run when one differs or is missing. The build machine's log shows the opens:
`bin2.bin`, then `BIN1.BIN`, `VERTRIX.EXE`, `VXSCORES.EXE`, the text files and the batch files.
The SD folder must therefore hold the whole release, unchanged.

## Recompilation

`vertrix1/recomp.py` reuses `vertrix3/recomp.py`'s decoder, flag liveness, x87 model and C
emission (`Gen`). It replaces the parts that differ for a DOS program:

- **Discovery:**
  - It starts from the entry. Code addresses come only from fixups: an immediate that a fixup
    relocates, or a relocated pointer outside the decoded instructions.
  - Watcom keeps read-only data in the code object, so the debug symbols mark which addresses
    are data. For example, `___begtext` and the `VERTRIX.C` tables are never decoded.
  - 1,443 functions are found.
- **Segments:**
  - The program loads selectors: PMODE/W's data selector, the PSP and the environment.
  - `es`/`fs`/`gs` overrides add the selector's base.
  - Functions that load `ds` read through its base.
- **Ports and interrupts:**
  - `in`/`out` call the runtime's port map.
  - `int n` goes to the guest's vector when the program has set one, otherwise to the DOS and
    BIOS services.
  - `cli`/`sti`, `pushfd`/`popfd` and `iretd` keep the interrupt flag.
- **Far transfers:**
  - `call far`/`jmp far` through memory are recognised by their encoding (FF /3, FF /5).
    Capstone reports the operand of `call m16:32` as 4 bytes. Treating it as a near call
    returned the timer handler to address 8; this was seen in the run, and the encoding check
    fixed it.
- **Interrupt delivery:**
  - Hardware interrupts are taken at safe points: each function's entry and each loop head.
  - The handler gets the frame the CPU builds (flags, cs, return address) and ends with
    `iretd`.
- **Flags:**
  - `stc`/`clc` write only CF, and `cmc` reads and writes CF. Treating them as writing every
    flag lost ZF before `stc; je` in MODPLAY's card detection, which then reported a bad port.
  - Callees that return flags are found without vertrix3's six-instruction window.
    MODPLAY's DSP routines return status in CF after more than six instructions.

## The machine (`vertrix1/runtime`)

| Device | Model | Checked by |
| --- | --- | --- |
| DOS (`int 21h`) | files under the game's folder as `C:\VERTRIX`, case-insensitive; memory blocks; dates; find first/next | the file list above opens; `setup.cfg` is read and written |
| PMODE/W DPMI (`int 31h`) | selectors, DOS memory, real-mode interrupts, vectors, memory blocks, PIC bases (0400h: 08h/70h) | MODPLAY's 0100h/0101h DOS buffer and 0400h; the C library's 0501h heap blocks |
| BIOS (`int 10h`, `16h`, `1Ah`) | mode 13h and 03h, the DAC, no VESA (4F00h returns 0100h) | the game takes the mode X path (below) |
| 8259 PIC pair | IMR, IRR/ISR, fully nested priorities, EOI | every handler ends with `out 20h, 20h` (table below) |
| 8253 PIT | three channels, modes, latches; IRQ 0 at the programmed rate | `INTER_Timer_On_` sets 72.8 Hz; the timer handlers' tick counts advance at that rate |
| Keyboard controller | port 60h queue, 61h, 64h; IRQ 1 | menus and the match react to scripted keys |
| VGA | four planes, latches, sequencer, graphics controller, CRTC, DAC; 70 Hz, 449 lines | frames of the setup, title, menus and match |
| 8237 DMA + Sound Blaster 2.0 | DSP 2.01 at 220h, IRQ 7, DMA 1; single-cycle and auto-init 8-bit output | MODPLAY's autodetect finds 220/7/1; the title music in `sound.wav` |

## The hardware accesses

`tools/v1_hardware.py VERTRIX.EXE --out docs/v1-hardware-accesses.txt` lists every `in`,
`out`, `int`, `cli` and `sti` by address, under the routine that holds it. Each `dx` port is
resolved from the last `mov dx, imm`. The list has 1,590 lines over 178 routines; 79 of those
routines belong to the game and MODPLAY, and the rest to the Watcom libraries. The ones the
game depends on are below.

### Timer (PIT ports 40h/43h, IRQ 0)

- **`INTER_Timer_On_` (0x1f724):**
  - It sets vector 8 to a game handler through `_dos_setvect_`.
  - It then writes 36h to port 43h and 0xffff/4 = 16,383 to channel 0, low byte first
    (0x1f7ac–0x1f7ba). That is 1,193,182 / 16,383 = 72.8 Hz.
  - `INTER_Timer_Off_` (0x1f811) restores the BIOS rate.
- **The handlers:** `myTimer_Intro_`, `myTimer_1Joueur_`, `myTimer_2Joueurs_` and
  `INTER_Timer_Choose_` count ticks, then acknowledge with `out 20h, 20h` (0x1f52a, 0x1f5e4,
  0x1f68e, 0x1f719).
- **The music's own rate:** the PIT is also reprogrammed by `logo1_`, `PRESENTATION_Affichage_`,
  `OPTION_Sound_Relancer_Musique_Intro_`, `Boucle_Idem_Game_`, `final_credit_`,
  `CHOOSE_Player_Main_` and `Capture_Ecran_`. Each sets the rate the following screen runs at.
  MODPLAY sets its own rate during detection (0x4c1a1–0x4c1d4).
- **Check:** the guest clock is real time, and the PIT model raises IRQ 0 from it at the
  programmed divisor. The title music and the match run at a steady pace on both the build
  machine and the Wii; no timing was tuned by hand.

### Keyboard (port 60h, IRQ 1)

- **The handlers:** `New_Key_Int_` (0x1f108), `New_Key_Options_` (0x1f1b4) and
  `New_Key_Int_cerveau_`.
  - Each reads port 60h (0x1f11e, 0x1f1ca, 0x1f33a) into a key table indexed by the set 1 scan
    code, with E0h as a prefix. Each ends with `out 20h, 20h`.
  - `main_` installs `New_Key_Options_` as vector 9 (0x4b3e6).
- **`scankbd_` (0x36976):** polls port 60h and pulses port 61h bit 7.
- **Default keys:** set in `reinit_setup_fichier_` (0x33120).
  - One player: arrows, with Up permuting. P (19h) pauses.
  - Two players: player 1 has W/X (2Ch/2Dh) to move, C (2Eh) to drop and F (21h) to permute.
    Player 2 has the arrows.
- **Check:** the build machine's scripted keys drive the setup, the menus and a match.

### Video (VGA ports 3C4h/3CEh/3D4h/3C6h–3C9h/3DAh, memory A0000h)

- **Mode X set-up in `main_` (0x4b2ff–0x4b397):**
  1. Unprotect CRTC 11h (bit 7 clear) and set mode 13h through `int 10h`.
  2. Sequencer 4: clear chain-4 and set bit 2. Map mask 0Fh. Clear both pages
     (`purge_page_x_`).
  3. CRTC 14h: clear doubleword mode. CRTC 17h: set byte mode. CRTC 09h &= 70h, which makes the
     maximum scan line 0, so each of the 400 lines is drawn once.
  4. Graphics controller 5 = 40h. Map mask 0Fh.
  - The result is an unchained 320x400 picture with 256 colours and two pages.
  - `exec_setup_` (0x3f3d4) repeats the set-up for the setup screen.
- **Drawing:**
  - Through the map mask: `VGA_Mem_To_ModeX_`, `LISTE_BLOC_affichage_`, `purge_plan_x_`.
  - Through the latches (write mode 1 after a read): `LISTE_BLOC_copie_` (0x21c9d).
- **Page flipping and scrolling:**
  - The CRTC start address in `BOUCLE_Rafraichissement_Ecran_pages_` (word write to 3D4h at
    0x47d71).
  - `FILES_Scrool_Personnalise_`, `boucle_jeux_test2_` and the `FX_Depart_*` effects.
  - These wait on 3DAh: bit 3 for the retrace, bit 0 for display enable.
- **Palette:**
  - Fades and colour cycling write the DAC through 3C8h/3C9h after waiting for the retrace on
    3DAh: `aff_lent_`, `baisser_lent_`, the `*_plus_music_` variants, `exec_rot_couleur_` and
    `PAL_Fusion_Palettes_`.
  - The DAC mask 3C6h is set to FFh first.
- **Check:** the PPM frames of the setup, title, player and background select, versus screen
  and match match the game's screens (`vertrix1/README.md`). The retrace timing (70 Hz,
  retrace on lines 412–413 of 449) keeps the fades at their original length.

### Sound (Sound Blaster 220h, DMA 1, IRQ 7)

MODPLAY (0x4b954–0x4cca7) does all the sound:

- **Detection (`_MODDetectCard`, 0x4bb98):**
  - It resets the DSP at base+6 and waits for AAh at base+0Ah. It tries bases from 210h up,
    which is why the log shows reads from 210h–21Fh before 220h answers.
  - It finds the IRQ by hooking the candidate vectors (2, 3, 5, 7 and 10) through `int 21h`
    35h/25h, unmasking them at ports 21h/A1h, and sending DSP F2h. The PIC bases come from
    DPMI 0400h (0x4cb67).
  - `-auto` on the command line, or the setup screen's AUTODETECT, runs it.
- **Playback:**
  - The routine at 0x4cac8 programs the DMA channel. It masks the channel (port 0Ah), clears
    the flip-flop (0Ch) and sets mode 58h (single, auto-init, read).
  - It then writes the buffer's address, a count of 3FFh, and the page. The page port comes
    from the table 0x82818387, which holds 87h, 83h, 81h and 82h for channels 0–3. Finally it
    unmasks the channel.
  - The buffer is 400h bytes of DOS memory (DPMI 0100h, 0x4c0af).
  - The DSP gets a time constant (40h) for 22,222 Hz, then single-cycle output (14h) with
    length FFFFh, which runs over the auto-initialising DMA buffer.
- **Check:**
  - The build machine's `sound.wav` holds the title and match music at 22,222 Hz with full
    amplitude.
  - On the Wii (Dolphin), the debug log counts 111,000 samples per 5 s with peaks of 85–91 of
    128.

### DOS and the extender

- **Files:** the game reads and writes through the Watcom library (`sopen_`, `read_`,
  `write_`, `lseek_`, `__close_`).
- **Setup:** `setup.cfg` is saved only when the game is left through its EXIT.
- **Memory:** about 4 MB comes from DPMI 0501h through Watcom's heap (`__CreateNewNHeap_`).
- **Ignored calls:** `int 21h` AH=63h, `int 10h` 6F00h/5F00h (video card probes) and port 3CDh
  (the Tseng probe in the graph library's `_SuperVGAType_`, 0x55f72). Each is answered as
  absent. Each is logged once.

## What is not modelled

- **AdLib (388h):** it reads as absent. The game uses only the Sound Blaster.
- **Joystick (201h):** it reads as nothing connected. The setup screen offers keys only.
- **VESA:** `int 10h` 4F00h reports no VESA. The game then uses mode X, the path its setup
  calls VGA.
