# Vertrix 2 Wii port: handoff

Branch `claude/elegant-carson-sm1x3q` (head `1bd38a7`, "Recover 0x4b7cd0 clock sampler"). Rules live in `AGENTS.md`.

## State
- `Vertrix2.exe` is the oracle. Each recovered routine has `source/*.c`, a `docs/<NAME>.md` with executable
  addresses, and a `tools/verify_*.py` differential check writing `docs/*-verification.json`
  (about 150 docs, 467 verifiers).
- Playable single-player board and title screen on Wii (`tools/wii_game.c`, `make wii-game`,
  `wii-game/`). See `docs/WII-GAME.md`. Verified in Dolphin only, never on hardware
  (`hardware-check/` is a display/SD diagnostic).
- Not recovered: 2PLAYERS, OPTIONS, character screen, bonuses, opponents, computer board, chain
  notifications (`0x43c0e0`), sound effects, the clearing flash time, and the starting level counter
  (12, a stand-in). Skipped candidates and why: `docs/GAMEFLOW-NOT-PORTED.md`.

## Environment gaps seen in this session
- devkitPPC is absent (`/opt/devkitpro` missing), so `make`, `wii-game` and Wii targets were not built here.
- `make check-format` fails: `source/ai_player.c:61` and possibly more files are not clang-formatted. AGENTS.md
  says to keep formatting changes in their own commit, separate from behavior changes.
- Tracked scratch files violate "experimental reconstructions outside the source tree":
  `tools/dbg*_tmp.py`, `tools/*.py.txt`. Consider removing or moving them.

## Suggested next steps
1. Format-only commit to make `check-format` pass.
2. Hardware run of `hardware-check/boot.dol` and the game, then record the result.
3. Continue recovery from `GAMEFLOW-NOT-PORTED.md`, starting with the allocator `0x4ca000` and the actor
   helpers that block the constructors/update routines.
4. Replace platform-choice stand-ins only with recovered behavior, with addresses and verifier evidence.
