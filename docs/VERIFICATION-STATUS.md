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
| entry points verified end to end (hand-recovered code) | 1390 |
| entry points verified end to end (machine translation, reference only) | about 675 more (706 translated routines kept, see docs/lifted-verification.json) |
| direct `call` targets in 0x401000..0x4d0000 | 1827 |
| of those, with a verified hand recovery | 902 |
| of those, only a verified machine translation (`reference/lifted/`, to be recovered by hand) | 444 |
| of those, neither | 481 (`docs/unported-call-targets.txt`) |

The lifted translations (`docs/LIFTED.md`) are a specification and a starting point, not recovered
source; the counts are kept apart on purpose.

## Not counted

- `verify_preview_generate`, `verify_sequence_player`, `verify_table_loops`,
  `verify_board_collections`: ran but their numbers differ from the committed report (REVIEW). Their
  functions are excluded until explained.
- `verify_mp3` needs the libogc libmad source; the six `verify_wii_*` scripts need devkitPPC for
  their PowerPC half.
- Verifiers that drive the emulator without `Original.call` are not seen by the tally.

## Not at 1:1

925 direct-call functions have no verified hand recovery: 444 have a verified
translation to be turned into named, untangled source, and 481 have neither (Win32
import wrappers, translations that did not pass, routines the tools refused). The dispatcher
0x43c140 and the wiring into the game are open.

## Direct-call targets with no verified hand recovery (current breakdown)

Of the 481 targets in `docs/unported-call-targets.txt` (list not regenerated; 136 of them now have
a verified translation):

| state | count |
| --- | --- |
| translation verified (reference only) | 136 |
| translation weak (inputs cannot model pointers or loops) | 174 |
| translation fails the comparison | 17 |
| refused: indirect call (absolute-memory call, i.e. an import-table call) | 139 |
| refused: indirect jmp | 6 |
| refused: callee with more than eleven stack arguments | 6 |
| refused: one-operand imul / shld / recursion | 3 |

The 139 indirect-call routines are wrappers around Win32 imports; they need Wii replacements, not
a port. The rest need hand recovery.
