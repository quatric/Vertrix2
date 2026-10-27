# Vertrix on the Wii

One Homebrew Channel app for the four games of the series, recompiled from the originals, and a
player for the soundtrack.

| Game | Year | Needs, in its folder |
| --- | --- | --- |
| Vertrix | 1997 (DOS) | `vertrix1/`: the whole original release (`VERTRIX.EXE`, `BIN1.BIN`, `BIN2.BIN` and the rest; the game checks every file `BIN2.BIN` lists) |
| Vertrix 2 v1.2 | 2001 | `vertrix2-v12/`: `Vertrix2.vf` from v1.2 |
| Vertrix 2 | 2003 (v2.0) | `vertrix2/`: `Vertrix2.vf` from v2.0 |
| Vertrix 3 | 2009 | `vertrix3/`: `VERTRIX3.VF` |

The release zip carries these files beside the programs, and the 3DS `.cia` titles carry theirs in their RomFS (copied to the card the first time a game starts).

## The SD card

```
sd:/apps/vertrix/boot.dol          the menu
sd:/apps/vertrix/meta.xml, icon.png
sd:/apps/vertrix/games/*.dol       the four games
sd:/apps/vertrix/vertrix1/  vertrix2-v12/  vertrix2/  vertrix3/     the games' own files
sd:/apps/vertrix/music/<album>/*.mp3                                 optional
```

Every DOL is compressed with FIX94's dolxz and unpacks itself at start. A game's settings and
log are written to its folder.

## Controls

On the menu:

- **Up and Down** (or point with the Wii Remote) choose a game.
- **A** or **2** starts the game.
- **Plus** and **Minus** skip tracks.

On the music screen:

- **Left and Right** change the album.
- **A** plays a track.
- **2** pauses, and **1** turns shuffle on or off.
- **B** or **HOME** goes back.

In a game, **HOME** comes back to this menu. Each game's own controls are on its page in the
repository (`vertrix1/README.md`, `vertrix3/README.md`).

The soundtrack starts by itself, shuffled, when the menu opens. Text is set in FOT-Rodin NTLG Pro
Bold (`launcher/font.c`, made by `tools/make_font.py`).

Albums are the folders in `music/`. An optional `album.txt` names one (its first line); otherwise
the tracks' ID3 album tag is used.

## Building

From the repository root, with devkitPro and the games' executables:

```
git submodule update --init
make wii-app V1_EXE=.../VERTRIX.EXE V12_EXE=.../Vertrix2.exe V3_EXE=.../Vertrix3.exe \
    V20_EXE=Vertrix2.exe PYTHON=python3        # build/app/apps/vertrix/
make wii-app-zip                               # build/vertrix-wii.zip
```

`tools/build_dolxz.sh` builds dolxz from the `tools/dolxz` submodule. `tools/dol_align.py` then
pads each packed DOL's last section to 32 bytes, which Dolphin needs.
