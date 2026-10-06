# Verification status

Produced by `python3 tools/prepare_assets.py <dir>` then
`python3 tools/run_verifiers.py <dir> --verified docs/verified-functions.json`.

**Definition.** A function is verified end to end when a verifier that passes ran it to completion
in the original `Vertrix2.exe` under Unicorn (`Original.call`) and compared the result with the
native recovery. `docs/verified-functions.json` lists each such entry point with the verifiers that
cover it. Functions that only run inside another verified function, with real code, are not counted
separately.

## Counts (run of this commit's parent)

| | |
|---|---|
| verifier scripts run | 438 (427 pass, 4 REVIEW, 1 SKIP, 6 PARTIAL) |
| entry points verified end to end | 1390 |
| direct `call` targets in 0x401000..0x4d0000 | 1827 |
| of those, verified | 902 |
| of those, named in `source/` but not verified end to end | 294 (`docs/named-but-unverified.txt`) |
| of those, not named in `source/` (not ported) | 688 (`docs/unported-call-targets.txt`) |
| verified entry points outside the direct-call set (handlers reached by token or vtable, library) | 488 |

The bonus-effect verifier alone covers 73 routines (`docs/BONUS-EFFECTS.md`); the run above started
before the last ones were added, so the total is a little higher now.

## Not counted

- `verify_preview_generate`, `verify_sequence_player`, `verify_table_loops`,
  `verify_board_collections`: ran but their numbers differ from the committed report (REVIEW). Their
  functions are excluded until explained.
- `verify_mp3` needs the libogc libmad source; the six `verify_wii_*` scripts need devkitPPC for
  their PowerPC half.
- Verifiers that drive the emulator without `Original.call` are not seen by the tally.

## Not at 1:1

688 directly-called functions are not ported at all, about 260 of them in 0x452830..0x45bd00, and
the dispatcher 0x43c140 and the wiring into the game are open.
