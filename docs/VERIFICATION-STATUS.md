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
| entry points verified end to end | 1840 |
| direct `call` targets in 0x401000..0x4d0000 | 1827 |
| of those, verified | 1258 |
| of those, named in `source/` but not verified end to end | 294 (`docs/named-but-unverified.txt`) |
| of those, lifted but too few cases complete to count | 158 (`docs/unverified-lifted.txt`) |
| of those, lifted but failing the comparison | 5 |
| of those, calling the Win32 import table (not portable) | 105 |
| of those, refused by the lifter for another reason | 7 |
| of those, not yet reached by any tool | 0 |

The bonus-effect verifier covers 105 hand-recovered routines (`docs/BONUS-EFFECTS.md`) and
`tools/verify_lifted.py` another 490 lifted ones (`docs/LIFTED.md`); both are in the counts above
(the 438-script run predates them; their entries were merged into `verified-functions.json`).

## Not counted

- `verify_preview_generate`, `verify_sequence_player`, `verify_table_loops`,
  `verify_board_collections`: ran but their numbers differ from the committed report (REVIEW). Their
  functions are excluded until explained.
- `verify_mp3` needs the libogc libmad source; the six `verify_wii_*` scripts need devkitPPC for
  their PowerPC half.
- Verifiers that drive the emulator without `Original.call` are not seen by the tally.

## Not at 1:1

569 directly-called functions are not verified end to end: 294 are named in `source/` but were
never run against the original, 158 are lifted but their inputs could not be modelled well enough
(pointer arguments, buffers), 5 fail the comparison, 105 call the Win32 import table and 7 use
constructs the lifter refuses. The dispatcher 0x43c140 and the wiring into the game are open.
