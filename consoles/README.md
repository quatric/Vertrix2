# Vertrix on the Switch, the Wii U and the 3DS

The Wii app (`launcher/README.md`) for three more consoles: the same menu and soundtrack player
(`launcher/main.c`, unchanged), and the four games recompiled from the originals, each the same
generated C as its Wii and Mac builds. They are homebrew, started from the Homebrew Menu (Switch),
the Homebrew Launcher or Aroma's menu (Wii U), or the Homebrew Launcher (3DS).

| Game | Year | Needs, in its folder |
| --- | --- | --- |
| Vertrix | 1997 (DOS) | `vertrix1/`: the whole original release (`VERTRIX.EXE`, `BIN1.BIN`, `BIN2.BIN` and the rest; the game checks every file `BIN2.BIN` lists) |
| Vertrix 2 v1.2 | 2001 | `vertrix2-v12/`: `Vertrix2.vf` from v1.2 |
| Vertrix 2 | 2003 (v2.0) | `vertrix2/`: `Vertrix2.vf` from v2.0 |
| Vertrix 3 | 2009 | `vertrix3/`: `VERTRIX3.VF` |

The release zip carries these files beside the programs, and the 3DS `.cia` titles carry theirs in their RomFS (copied to the card the first time a game starts).

## The SD card

```
Switch   sdmc:/switch/vertrix/vertrix.nro        the menu
         sdmc:/switch/vertrix/games/*.nro        the four games
Wii U    sd:/wiiu/apps/vertrix/vertrix.wuhb      the menu
         sd:/wiiu/apps/vertrix/games/*.rpx       the four games
3DS      sdmc:/3ds/vertrix/vertrix.3dsx          the menu
         sdmc:/3ds/vertrix/games/*.3dsx          the four games
```

and beside them, in the same folder, `vertrix1/`, `vertrix2-v12/`, `vertrix2/` and `vertrix3/`
with the games' own files, and `music/<album>/*.mp3` (optional). A game's settings and log are
written to its folder. The menu writes `launcher.log` only when something goes wrong.

On the 3DS the games need the DSP firmware dump (`sdmc:/3ds/dspfirm.cdc`) for sound, and the
menu starts a game through Luma3DS's homebrew loader. Started on its own (an emulator), a game
returns to the HOME Menu when it ends instead of to the menu.

## Controls

The buttons are where the Wii's Classic Controller has them: the right face button chooses
(A on all three), the bottom one goes back.

- **Menu:** Up and Down (or touch) choose a game, **A** starts it, **L** and **R** skip tracks,
  **+** (**START** on the 3DS) leaves.
- **Music:** Left and Right change the album, **A** plays a track, **Y** pauses, **L** and **R**
  skip, **X** turns shuffle on or off, **B** goes back.
- **In a game:** the stick or D-pad and the face buttons are the game's keys, as on the Wii
  (`vertrix1/README.md`, `vertrix3/README.md`). The touch screen is the mouse. A USB keyboard
  works as the PC's keyboard on the Switch and the Wii U. **+ and − together** end the game and
  return to the menu.

## How it is built

`consoles/` is a third shell under the games, beside the Mac's (`mac/`) and the Wii's:

- `shell_common.c`: what is the same everywhere: the frame hand-off between the game's thread
  and the screen, the input queue, the sound ring and its resampler, the log, the error screen,
  and starting the next program (menu → game → menu).
- `shell_sdl.c`: the screen, sound and USB keyboard through SDL2, on the Switch and the Wii U.
- `shell_3ds.c`: libctru's frame buffers and the DSP. The picture is scaled to 240 lines and shown
  on both screens, so touching the bottom one points at it.
- `system_switch.c`, `system_wiiu.c`, `system_3ds.c`: each console's folders, clock, controllers
  and program chaining (`console.h`).
- `launcher_shell.c` and `compat/`: the Wii menu's libogc, MP3 player and update-checker calls
  on the shell (the update check is off on the consoles).
- `rules.mk`: compiling, linking and packing a program for any of the three. `launcher.mk` builds
  the menu, and the game Makefiles' `switch`, `wiiu` and `3ds` targets build the games.

The Windows games run with the Wii's paged guest memory (`V3_PAGED`) and its heap: 40 MB for
Vertrix 2, 32 MB for Vertrix 3, and 8 MB for the 1997 game.

From the repository root, with devkitPro (`switch-dev`, `wiiu-dev`, `3ds-dev`, and
`switch-sdl2`, `wiiu-sdl2`, `switch-libmad`, `ppc-libmad`, `3ds-libmad`), Pillow for the icons,
and the games' executables:

```
make switch-app V1_EXE=.../VERTRIX.EXE V12_EXE=.../Vertrix2.exe V3_EXE=.../Vertrix3.exe \
    V20_EXE=Vertrix2.exe PYTHON=python3     # build/switch/sd/switch/vertrix/
make switch-app-zip                         # build/vertrix-switch.zip
```

and `wiiu-app` / `wiiu-app-zip` and `3ds-app` / `3ds-app-zip` likewise. The Wii U menu is also a `.wuhb` on its own (`build/wiiu/launcher/vertrix.wuhb`), and the 3DS
programs can be installed as titles with FBI: `make 3ds-cia-zip` packs `vertrix.cia` and one per game
(`vertrix1.cia`, `vertrix2-v12.cia`, `vertrix2.cia`, `vertrix3.cia`) from the `.elf` files that
`3ds-app` built, with `makerom` and `bannertool` on the PATH (`tools/make_cia.sh`, `3ds.rsf`).
The games' files still go in `sdmc:/3ds/vertrix/`, and the menu still starts the `.3dsx` games.

`make apps-zip` (same variables) builds every app one after another: the Wii, the Mac (on a Mac),
the Switch, the Wii U and the 3DS, each as `build/vertrix-<app>.zip`; `APPS="wii 3ds"` picks some.
CI builds them all in `.github/workflows/build.yml`.

A single game:
`make -C vertrix3 BUILD=../build/v20 GAME=vertrix2 V3_EXE=... wiiu`.

For scripted runs in an emulator, `CONSOLE_DEBUG="-DSHELL_SCRIPT='\"4 b; 6 down\"'"` presses
buttons at set times (`shell_common.c`).
