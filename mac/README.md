# Vertrix on the Mac

One app for the four games of the series, recompiled from the originals, and a player for the
soundtrack. It is the Mac's version of the Wii app (`launcher/README.md`). The games run natively
on Apple silicon and Intel Macs from the same generated C as the Wii builds. Nothing is emulated
except the PC each game expected: Windows and Direct3D for the Windows games, and DOS, a VGA and
a Sound Blaster for the 1997 game.

| Game | Year | Needs |
| --- | --- | --- |
| Vertrix | 1997 (DOS) | the whole original release (`VERTRIX.EXE`, `BIN1.BIN`, `BIN2.BIN` and the rest; the game checks every file `BIN2.BIN` lists) |
| Vertrix 2 v1.2 | 2001 | `Vertrix2.vf` from v1.2 |
| Vertrix 2 | 2003 (v2.0) | `Vertrix2.vf` from v2.0 |
| Vertrix 3 | 2009 | `VERTRIX3.VF` |

None of the games' files come with this app. The first time a game starts, it asks for them:
choose the file, or the folder that holds it, from your own copy of the game. It copies them into
its folder in `~/Library/Application Support/Vertrix/`, where it also keeps its settings, scores
and log:

```
~/Library/Application Support/Vertrix/vertrix1/        the 1997 release, SETUP.CFG, vertrix.log
~/Library/Application Support/Vertrix/vertrix2-v12/    Vertrix2.vf, Vertrix2.cfg
~/Library/Application Support/Vertrix/vertrix2/        Vertrix2.vf, Vertrix2.cfg
~/Library/Application Support/Vertrix/vertrix3/        VERTRIX3.VF
~/Library/Application Support/Vertrix/music/<album>/   the soundtrack (optional)
```

`VERTRIX_HOME` names another folder. Each game app also runs on its own and takes `--data DIR`.

## The window

- **Games:** double-click a game, or select it and press Return, to play it. The launcher hides
  while the game runs and comes back when the game ends. **Show Files** opens the game's folder.
- **Soundtrack:** albums are the folders in `music/`, as on the Wii. An optional `album.txt`
  names one (its first line); otherwise the folder's name is used. MP3, M4A and WAV files play.
  The music starts on a random track when the launcher opens. **Shuffle** (on until you turn it
  off) picks each next track at random from every album; off, the album plays in order.
  **Next** skips. Starting a game pauses the music.

## Playing

Each game opens in its own window at the largest whole multiple of its picture that fits the
screen. **View** changes the size or enters full screen. The keyboard is the game's own, and the
mouse works where the game uses it. A game controller (any that macOS supports) plays as the Wii
Remote does:

| Controller | Vertrix 2 and 3 | Vertrix (1997) |
| --- | --- | --- |
| D-pad, left stick | the arrow keys | the arrow keys |
| A (bottom) | Up: permute | Up: permute |
| B (right) | Enter | Enter |
| X (left) | Space | Escape |
| Menu | Escape | Escape |
| Options | Escape | P: pause |

In Vertrix (1997) a second controller is player 1 of a two-player game, on the game's default
keys W, X, C and F.

Closing a Windows game's window or quitting it asks the game to close as Windows would, so it
leaves through its own exit (Vertrix 2 v2.0 writes `Vertrix2.cfg` there). Closing Vertrix (1997)
stops it where it is: it saves its setup only when you leave through its own EXIT, as the DOS
game did.

## Building

From the repository root, with the games' executables and Python with Capstone 5 and pefile:

```
make mac-app V1_EXE=.../VERTRIX.EXE V12_EXE=.../Vertrix2.exe V3_EXE=.../Vertrix3.exe \
    V20_EXE=Vertrix2.exe PYTHON=python3        # build/mac/Vertrix.app
make mac-app-zip                               # build/vertrix-mac.zip
```

- **Architectures:** the app is universal (arm64 and x86_64); `MAC_ARCHS=arm64` builds one.
  macOS 11 or later.
- **Music:** `MAC_MUSIC=folder` copies a folder of albums into the app. The soundtrack is on
  vertrixgame.com: the Vertrix 2 soundtrack (32 tracks, with an MD5 list to check them) from
  the downloads page, and Cédric Castel's other tracks (18) from the music page. The release
  build carries both, one folder each, with an `album.txt` naming it.
- **Signing:** the app is signed ad hoc. A copy from elsewhere needs right-click > Open the first
  time, or `xattr -dr com.apple.quarantine Vertrix.app`.
- **Inputs:** `tools/fetch_mac_inputs.sh DIR` downloads the four games and the soundtrack from
  vertrixgame.com. It unpacks the installers without running them (innoextract for Vertrix 3;
  `tools/unace_sfx.py`, with acefile, for the ACE self-extractors of Vertrix 2 v1.2 and v2.0)
  and checks the soundtrack against its MD5 list. v2.0's `Vertrix2.exe` is the same file as the
  repository's.
- **CI:** `.github/workflows/mac.yml` does all of this on a macOS runner. It runs for changes that
  touch the Mac build, uploads `vertrix-mac.zip`, and attaches it to the release for a `v*` tag.
- **One game:** `make -C vertrix1 V1_EXE=... mac` and `make -C vertrix3 ... mac` (with `BUILD`
  and `GAME` as for the Wii) build that game's app alone.

## Sources

| Path | What |
| --- | --- |
| `mac/launcher.m` | `Vertrix.app`: the game list and the soundtrack player |
| `mac/shell.h`, `mac/shell.m` | what a game needs of macOS: the window (Core Animation), keyboard, mouse and controllers (GameController), sound (Core Audio), the 60 Hz frame pacing |
| `mac/data.h`, `mac/data.m` | the Vertrix folder and the game files, asked for and copied in |
| `mac/vertrix_games.c` | the four games, as the Wii launcher lists them |
| `mac/icon.py` | each app's icon, from the game's own executable (the logo for the DOS game; Vertrix 3's for `Vertrix.app`) |
| `vertrix3/mac/mac_main.c` | the driver of the Windows games: Win32 time, the software Direct3D renderer's frames, wave-out on Core Audio, DirectInput |
| `vertrix1/mac/mac_main.c` | the driver of the DOS game: the VGA's picture, the Sound Blaster's samples, the PC keyboard |
