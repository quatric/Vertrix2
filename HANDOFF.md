# Vertrix on the Wii: handoff

State 2026-10-20, branch `main`, remote `git@github.com:quatric/Vertrix2.git`. Commits are by
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
| Vertrix (1997, DOS, PMODE/W, Watcom) | LE recompiler and an emulated DOS PC (DPMI, VGA mode X, PIT, PIC, keyboard, Sound Blaster) | `vertrix1/` | setup screen to a 1P vs CPU match with music, on the build machine and on the Wii in Dolphin | `vertrix1/README.md`, `docs/VERTRIX1.md` |

None of the Wii builds has been run on real hardware. Every Wii result above comes from Dolphin.

## Game files

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

devkitPro must be at `/opt/devkitpro`. On this machine it is at
`/Volumes/SSD/larsen/devkitpro`, linked there.

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
5. **Vertrix (1997):**
   - save the setup when HOME is pressed. This needs a decision: today the game saves only
     through its own EXIT, which is the original's behaviour.
   - the optional signature matching against Vertrix 2 (`tools/v3_signatures.py`).
   - `VXSCORES.EXE`, the high score viewer, is not ported.

Older handoffs, kept for their history: `docs/HANDOFF.md`, `docs/Vertrix2_Wii_Port_Handoff.md`,
`docs/VERTRIX1-HANDOFF.md`.
