# Vertrix 2 Wii port: handoff

## State (commit 80b3671, branch `claude/vertrix-2-wii-port-3ktihn`)

- Recovered native C library only. The playable Wii application is NOT finished.
- `source/`: about 595 files of recovered logic (actors, board, AI, UI, VF archive,
  XM/MPEG audio, text, surface ops). `source/wii_*.c` are Wii-specific and excluded from
  the portable library build.
- `tools/`: about 492 scripts. `verify_*.py` run differential checks against the original
  executable (oracle). `recover_*.py` extract tables. `*_tmp.py` are debug scratch.
- `docs/`: about 625 files. Each recovered routine has a `.md` with executable addresses and a
  `*-verification.json` with evidence. `GAMEFLOW-NOT-PORTED.md` lists skipped routines and why.
- `hardware-check/`: diagnostic `boot.dol`. Built and linked, never run on hardware.
- `wii-game/`: Wii game directory (not inspected in this handoff).
- Assets: the original `Vertrix2.vf` is read directly from `sd:/apps/vertrix2/`. It is not
  bundled.

## Rules (AGENTS.md)

- Preserve original behavior. No guessed rules, timings, AI or bonuses.
- Record executable addresses and verification evidence for each recovered routine.
- Keep experimental reconstructions out of the source tree.
- Format with `make format`. Check with `make check-format`. Four spaces, Allman braces,
  100 columns, one statement per line. Keep formatting commits separate from behavior commits.

## Build

- `make` builds `build/libvertrix-recovered.a` with devkitPPC (`/opt/devkitpro/devkitPPC`).
  Other targets: `wii-textures`, `wii-archive`.
- This cloud container has no devkitPro and no `powerpc-eabi-gcc`. Only `clang-format` is
  installed. Nothing was built or run in this session.

## Next steps

1. Install devkitPro and run `make` and `make check-format`. Fix anything that fails.
2. Finish the routines listed in `docs/GAMEFLOW-NOT-PORTED.md`. Most are blocked on
   unrecovered allocator `0x4ca000` and actor/list helpers, or on imported API/COM setup code.
3. Integrate the pieces into a startup and game loop in `wii-game/`.
4. Run `hardware-check/boot.dol` on a real Wii (Homebrew Channel) and record the result.
5. Test in Dolphin. Reference screenshots: `docs/wii-title-dolphin.png`,
   `docs/wii-game-dolphin.png`.

## Open question

The request pointed at `~/.opencode/`. That path does not exist in this container, so no
prior opencode notes could be read. If you meant to export this handoff there, copy this file
to your local machine's `~/.opencode/`. This container is ephemeral.
