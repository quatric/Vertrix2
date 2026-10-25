# Vertrix on the Wii: handoff

State 2026-10-24 (the build setup; the rest is as of 2026-10-20), branch `main`, remote `git@github.com:quatric/Vertrix2.git`. Commits are by
`quatric`. The rules are in `AGENTS.md`:

- Preserve the original behaviour: no guessed rules, timings or AI.
- Record addresses and evidence.
- clang-format all C (four spaces, Allman braces, 100 columns).
- Keep experimental reconstructions out of the source tree.

The repository now ports four games of the series. Each has its own page:

| Game | Approach | Where | Status | Page |
| --- | --- | --- | --- | --- |
| Vertrix 2 v2.0 (2003, Windows, Watcom) | recovered routines as native C, each checked against the original under Unicorn; the dispatcher serves 3,833 routines as ports | `source/`, `tools/`, top `Makefile` | `make wii-recomp` builds `build/vertrix2-recomp.dol`; `make wii-game` builds the older single-board app | `docs/WII-GAME.md`, `docs/LIFTED.md`, `docs/RECOVERY.md` |
| Vertrix 2 v2.0, recompiled whole | whole-program recompiler (`vertrix3/recomp.py`), function discovery checked against rea's Rizin list (`tools/rea_coverage.py`) | `vertrix3/`, `GAME=vertrix2`, `BUILD=../build/v20` | a Practice match to its result screen on the build machine and on the Wii in Dolphin (40 MB guest heap). Two early Dolphin runs stalled in the menus, cause unknown (see its page). The Wii app packs this build as `games/vertrix2.dol` | `docs/VERTRIX2-RECOMP.md` |
| Vertrix 2 v1.2 (2001) | whole-program recompiler (`vertrix3/recomp.py`) | `vertrix3/`, `GAME=vertrix2-v12` | menus, tournament stories, player select and a 1P vs CPU match to its result screen, on the build machine and on the Wii in Dolphin (40 MB guest heap) | `docs/VERTRIX2-V12.md` |
| Vertrix 3 (2009, Windows, Visual C++, Direct3D 9) | whole-program recompiler and runtime | `vertrix3/` | plays to a match on the build machine and on the Wii in Dolphin | `vertrix3/README.md`, `docs/VERTRIX3.md` |
| Vertrix (1997, DOS, PMODE/W, Watcom) | LE recompiler and an emulated DOS PC (DPMI, VGA mode X, PIT, PIC, keyboard, Sound Blaster) | `vertrix1/` | setup screen to a 1P vs CPU match with music, on the build machine, on the Mac and on the Wii in Dolphin. `vertrix1/assets.py` unpacks its data | `vertrix1/README.md`, `docs/VERTRIX1.md` |

None of the Wii builds has been run on real hardware. Every Wii result above comes from Dolphin.

## The Mac

`make mac-app` builds `build/mac/Vertrix.app`: a launcher (`mac/launcher.m`) with the four games
as their own apps in `Contents/Helpers`, and the soundtrack player. Every game is the same
generated C as its Wii build, universal (arm64 and x86_64), on the shell in `mac/`. The page is
`mac/README.md`.

- **Checked on this Mac (Apple silicon):**
  - Vertrix 2 v2.0: its intro and menus at 60 fps; quitting writes `Vertrix2.cfg`.
  - Vertrix 2 v1.2 and Vertrix 3: to their menus.
  - Vertrix (1997): setup, AUTODETECT, the title, player select and a 1P vs CPU match with
    music.
  - The launcher: it starts each game, hides, and comes back when the game ends. It plays the
    soundtrack.
- **Not checked:** an Intel Mac; game controllers (the mapping is in each driver).
- **The games' files:** each game asks for them at its first start and keeps them in
  `~/Library/Application Support/Vertrix/<folder>/` (`VERTRIX_HOME` overrides).
- **The soundtrack:** albums go in `MAC_MUSIC=`, which is not in the repository. See
  `mac/README.md` for where to get them.

## The Switch, the Wii U and the 3DS

`make switch-app`, `wiiu-app` and `3ds-app` build the Wii app for each console: the unchanged
menu (`launcher/main.c`) and the four games, on the console shell in `consoles/`. Each game is
the same generated C as its Wii build, with the Wii's paged guest memory and heap. The page is
`consoles/README.md`. The shell API the games use moved from `mac/` to `shell/` (`shell.h`,
`vertrix_games.c`), and each game's driver moved from `<game>/mac/mac_main.c` to
`<game>/shell/shell_main.c`, shared by the Mac and the consoles.

- **Checked in emulators on this Mac:**
  - Wii U (Cemu 2.6): the menu (Wii look, finds the music), and all four games start and run at
    60 fps to their own screens. Vertrix (1997) takes the controller on its setup screen.
  - 3DS (Azahar 2125.1.3): the menu, on both screens, and all four games to their own screens:
    Vertrix 2 and Vertrix 3 at full speed, v1.2 at about 72%, and Vertrix (1997) at about 54%
    (its setup screen).
  - Switch: all four games and the menu build (`.nro`); none has run.
- **Not checked:** real hardware; the Switch (no emulator here); starting a game from the menu
  and coming back (Cemu and Azahar load one program, and Azahar has no Luma3DS loader).
- **Wii U specifics** (`vertrix3/runtime/threads_posix.c`): an RPX cannot hold thread-local
  storage, so the current thread is kept in coreinit's thread-specific slot 0; and wut's timed
  condition wait leaves an alarm that crashed Cemu, so timed event waits poll every millisecond.
  `V3_HOST_THREAD_STACK` sets the host threads' stack (512 KB on the consoles).

## The build setup: one workflow for every app

`.github/workflows/build.yml` (the Build workflow) builds every app. It replaced `consoles.yml`,
`wii.yml` and `mac.yml` in 967fd13. It runs on pushes to `main` that touch the paths it lists,
on tags `v*`, on pull requests and by hand (`gh workflow run build.yml`).

| Job | Runs on | Make target | Artifact |
| --- | --- | --- | --- |
| `build (wii)` | `devkitpro/devkitppc` | `wii-app-zip` | `vertrix-wii` (`build/app/apps/vertrix`, `games/*.dol`) |
| `build (switch)` | `devkitpro/devkita64` | `switch-app-zip` | `vertrix-switch` (`games/*.nro`) |
| `build (wiiu)` | `devkitpro/devkitppc` | `wiiu-app-zip` | `vertrix-wiiu`, and `vertrix-wiiu-extra` with the menu as a bare `vertrix.wuhb` |
| `build (3ds)` | `devkitpro/devkitarm` | `3ds-app-zip` | `vertrix-3ds` (`games/*.3dsx`), and `vertrix-3ds-extra` with the five ELFs |
| `mac` | `macos-14` | `mac-app-zip` | `vertrix-mac` (universal `Vertrix.app`, ad-hoc signed, with the soundtrack) |
| `cia` | `ubuntu-latest`, after `build` | `3ds-cia-zip` | `vertrix-3ds-cia`: `vertrix.cia` (the menu), `vertrix1.cia`, `vertrix2-v12.cia`, `vertrix2.cia`, `vertrix3.cia` |

- **Inputs:** every job downloads the games' executables (and, for the Mac, the soundtrack)
  from vertrixgame.com with `tools/fetch_mac_inputs.sh`, cached by that script's hash. None of
  them are in the repository or in the apps.
- **Checks:** each console job checks the app has its four game programs. The Mac job checks
  the signature, that every binary is arm64 and x86_64, the four helper apps and the 50 MP3s.
  The `cia` job checks there are five CIAs.
- **Releases:** a tag `v*` attaches every zip, `vertrix.wuhb` and `vertrix-3ds-cia.zip` to the
  release.
- **CIAs:** packed on the runner, not in the devkitARM image, because the prebuilt makerom
  (0.19.0) and bannertool (1.2.3) need a newer glibc. `tools/make_cia.sh` and
  `consoles/3ds.rsf` do the packing; the title IDs and memory modes (80 MB, 64 MB for the menu)
  are in the `Makefile`. The games still run from `sdmc:/3ds/vertrix/` as `.3dsx`.
  **Unchecked:** the CIAs have not been installed on a 3DS or in an emulator, and the `hb:ldr`
  permission the installed menu needs to start a game through Luma3DS is a guess. If starting a
  game from the installed menu fails, look there first.
- **devkitPro's package server** sometimes answers 403, which fails the Tools step before the
  build. The step tries the package sync five times, a little longer apart each time. A run that
  fails only in Tools is that server; rerun it with `gh run rerun <id> --failed`.
- **Locally:** `make apps-zip V1_EXE=… V12_EXE=… V3_EXE=… [V20_EXE=…]` builds every app's zip
  in turn (they share the games' generated C under `build/v*/`, so not in parallel). `APPS="wii
  mac"` picks some; the Mac is built only on a Mac. `make 3ds-cia-zip` needs makerom and
  bannertool on the `PATH`.
- **Last results:** Build run 40154615166 on 64df9b3 passed every job (Wii, Switch, Wii U, 3DS,
  Mac, CIA). The Switch needed one rerun: the package server refused it all five tries.
- **Dropped:** a DSi port of Vertrix (1997) (ba79b08, reverted in 0daa553). The game needs
  about 7 MB with its code, more than a DS has; DSi mode was never tested. A Windows and Linux
  build on the SDL shell was started and abandoned; none of it is in the repository.


The builds read the originals from outside the repository. Do not add any more of them, and do
not commit the files the unpacked archives contain.

| Game | Executable (build input) | Data on the SD card |
| --- | --- | --- |
| Vertrix 2 v2.0 | `Vertrix2.exe` | `sd:/apps/vertrix2/Vertrix2.vf` |
| Vertrix 2 v1.2 | its `Vertrix2.exe` (sha256 `8e27c76d…`) | `sd:/apps/vertrix2-v12/` |
| Vertrix 3 | `Vertrix3.exe` (sha256 `db625cfe…`) | `sd:/apps/vertrix3/VERTRIX3.VF` |
| Vertrix | `VERTRIX.EXE` (sha256 `4785d692…`) | the whole release in `sd:/apps/vertrix/` (the game checks every file `BIN2.BIN` lists) |

`Vertrix2.exe` and `Vertrix2.vf.zip` are still tracked at the root from early in the project,
together with the scratch images `diff.png` and `y1.png`–`y7.png`. Whether to remove them from
the tree is the owner's call.

## Building

devkitPro must be at `/opt/devkitpro`. On the build machine it lives on the external disk and
is linked there.

```
make check-format                                   # passes at this commit
make wii-recomp && make wii-sync-recomp SYNC=…      # Vertrix 2 v2.0
make -C vertrix3 V3_EXE=…/Vertrix3.exe wii-sync SYNC=…
make -C vertrix3 BUILD=../build/v12 GAME=vertrix2-v12 V3_EXE=…/Vertrix2.exe wii-sync SYNC=…
make -C vertrix3 BUILD=../build/v20 GAME=vertrix2 V3_EXE=../Vertrix2.exe wii-sync SYNC=…   # v2.0, whole
make -C vertrix1 V1_EXE=…/VERTRIX.EXE PYTHON=… wii-sync SYNC=…
```

- **Python:** the recompilers need Capstone 5 and pefile.
- **Sync:** each `wii-sync` copies `boot.dol`, `meta.xml` and the shared `wii-game/icon.png`
  (128x48, the Vertrix logo) into `apps/<game>/`.
- **Build machine:** each recompiled game also has a build-machine driver that writes PPM frames
  and a WAV file:
  - Vertrix 3 and v1.2: `make -C vertrix3 host`.
  - Vertrix: `make -C vertrix1 host`.
  - Their READMEs give the scripted-input variables (`V3_SCRIPT`, `V1_SCRIPT`).

## Testing in Dolphin

- **Debug builds:** these take a key script and save screenshots to the SD card:
  - Vertrix: `WII_DEBUG='-DV1_WII_SHOTS=… -DV1_WII_SCRIPT="…"'`.
  - Vertrix 3 and v1.2: the `V3_WII_*` equivalents.
  - A `quit` step ends the run.
- **Running:** run Dolphin headless (`Dolphin -b -u USER_DIR -e DOL`) with a user folder whose
  `Dolphin.ini` enables the SD folder sync.
- **Cleaning up:** kill every headless Dolphin by PID afterwards:

```
for p in $(pgrep -f "^/Applications/Dolphin.app/Contents/MacOS/Dolphin"); do kill $p; done
pgrep -fl "^/Applications/Dolphin.app"
```

## Next steps

1. **Real hardware:** run each DOL on a real Wii from the Homebrew Channel and record the
   result. Start with `hardware-check/boot.dol`.
2. **Vertrix 2 v2.0:** the routines still open are in `docs/GAMEFLOW-NOT-PORTED.md` and
   `docs/REMAINING.md`.
3. **Vertrix 2 v1.2:** the intro is about eight times slower on the Wii (Dolphin) than on the
   build machine; profile it. The two-player, options and practice modes are untested.
4. **Vertrix 3:** see "Not done yet" in `docs/VERTRIX3.md`:
   - fog and specular;
   - reusing the Vertrix 2 ports only where the oracle agrees.
5. **The consoles:** run the apps on a Switch, a Wii U and a 3DS, including starting a game
   from the menu and coming back. On the 3DS, check that the Windows games fit in an Old 3DS's
   memory, and the speed of v1.2 and Vertrix (1997), which are slow in Azahar. Install the CIAs
   and start a game from the installed menu (the `hb:ldr` permission above).
6. **Vertrix (1997):**
   - save the setup when HOME is pressed. This needs a decision: today the game saves only
     through its own EXIT, which is the original's behaviour.
   - the optional signature matching against Vertrix 2 (`tools/v3_signatures.py`).
   - `VXSCORES.EXE`, the high score viewer, is not ported.

Older handoffs, kept for their history: `docs/HANDOFF.md`, `docs/Vertrix2_Wii_Port_Handoff.md`,
`docs/VERTRIX1-HANDOFF.md`.
