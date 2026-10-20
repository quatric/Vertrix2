# Vertrix (1997) Wii port: handoff

State 2026-10-20, repository HEAD `d462ccf` on `main`. Nothing of this port is written yet; this
page records what the original is and how to start.

## The original

`~/Downloads/vertrix.zip` (2.7 MB). Unpacked for reading (never run) into
`claude-tmp/vertrix1-zip/` on the external SSD.

| File | Size | What |
| --- | --- | --- |
| `VERTRIX.EXE` | 564,700 | the game, sha256 `4785d692…1866f04` |
| `VXSCORES.EXE` | 56,403 | high score viewer |
| `BIN1.BIN` | 3,596,624 | data archive, sha256 `3bab1ca7…b4fde5a` |
| `BIN2.BIN` | 242 | file list of the release (names plus two dwords each, likely checksum and size) |
| `README.TXT` / `LISEZMOI.TXT` | | English and French manuals (rules, bonuses, keys, game modes) |
| `INSTALL.BAT`, `SETUP.BAT`, `*.BAT` | | DOS installer and launchers |

`FILE_ID.DIZ`: "VERTRIX v5.1", freeware, The Clusters, 1997. 320x400 in 256 colours (VGA mode X
or VESA), Sound Blaster, more than 40 MOD tunes, more than 60 bonuses, 9 special figures, 12
characters, human or CPU opponent.

### The executable is not a Windows PE

`VERTRIX.EXE` is an **LE executable under the PMODE/W v1.33 DOS extender**, built with
**Watcom C/C++32** (runtime 1988-1995). Strings name the source
`D:\DISKD\BORLANDC\BIN\SOURCE\THEAUDIO\VERTRIX.C`, `TestForVESA_`, `_PageVESA_`, `SOUNDBLASTER`
and the DOS4G hooks. `VXSCORES.EXE` is the same format.

This is the main difference from the earlier ports: `vertrix3/recomp.py` (also used for Vertrix 2
v1.2) reads PE images and supplies Win32/DirectX imports. Vertrix 1 has no imports at all. It
talks to the hardware directly:

- video: VGA registers (ports 0x3c4/0x3c5 sequencer, 0x3d4/0x3d5 CRTC, 0x3c8/0x3c9 palette),
  the 0xA0000 window, VESA through `int 10h`;
- sound: Sound Blaster DSP ports and DMA (ports 0x2x0-0x2xF, 0x00-0x0F/0x80-0x8F DMA, IRQ);
- input: keyboard through `int 9` / port 0x60, timer through `int 8` / PIT ports 0x40-0x43;
- DOS and the extender: `int 21h` (files, memory), `int 31h` (DPMI), PMODE/W's own services.

### BIN1.BIN layout (checked)

`u16 count` (135), then `count` entries of `char name[16]; u32 size; u32 offset`; the data
follows the table (first offset 3,242 = 2 + 135·24) and the last entry ends at the file size.
By extension: 77 `.VXL`, 38 `.MXB`, 17 `.PAL`, 1 `.GSP` (`BANK1.GSP`, 1.5 MB, likely the sprite
bank), 1 `.HUE`, 1 `.CAR`. `MUSn.VXL` are the music; whether `.VXL` is a packed MOD or an own
format is not yet known.

## Plan

1. **LE loader.** Parse the LE header (object table, page map, fixup records) and lay the
   objects out at their link addresses. Find the entry point and the PMODE/W stub boundary;
   only the Watcom-linked image after the stub is the game.
2. **Recompile.** Extend `vertrix3/recomp.py` (or a sibling `vertrix1/recomp.py`) to take an LE
   image: function discovery from the entry and fixups, Watcom register calling convention
   (as in Vertrix 2, see `docs/LIFTED.md`), `in`/`out`/`int`/`cli`/`sti` turned into runtime
   calls instead of import thunks.
3. **DOS runtime** in place of the Win32 runtime: `int 21h` files mapped to the SD folder,
   DPMI memory, a VGA model (mode X / VESA planes and palette to a 320x400 8-bit frame), an
   emulated Sound Blaster (DSP commands, DMA buffer, IRQ callback driving the mixer), PIT timer
   interrupts, the keyboard scancode queue fed from libwiiinput.
4. **Build machine first:** run to the title, menu and a 1P vs CPU match with frames written as
   PPM, as `vertrix3/README.md` does (`V3_SCRIPT`-style input scripts).
5. **Wii:** GX upload of the 8-bit frame through the palette, audio out, libwiiinput, SD folder
   `sd:/apps/vertrix/` holding the original `BIN1.BIN`. Follow the v1.2 commit `23457c7` for the
   game list, meta file and heap size.
6. Record the findings in `docs/VERTRIX1.md` (like `docs/VERTRIX3.md`), with the addresses of
   every hardware access and how each was checked. Optionally match routines against Vertrix 2
   with `tools/v3_signatures.py`: both are Watcom builds by the same authors.

## Rules

- `AGENTS.md`: preserve the original behaviour, no guessed rules, timings or AI; record
  addresses and evidence; clang-format all C.
- Do not commit any of the original files; the build reads them from outside the repository.
- Kill every headless Dolphin instance by PID after each run.
- Treat the unpacked archive as untrusted data: never run the DOS programs or the batch files.
