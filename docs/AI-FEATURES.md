# Computer-player evaluation helpers

`ai_features.c` recovers four evaluation helpers:

- `0x4261b0`: row reach. Five outputs start at 1; scanning left and right from
  a start column along one row, the first occupied cell and every column
  beyond it get 0 (rows of 10 or more never block). Uses the fill routine
  `0x4eb5c0`.
- `0x427c10`: five feature bytes (offsets `0x01`, `0x06`, `0x0b`, `0x0f`,
  `0x26`) from seven operands (three registers, four stack arguments). The
  `0x0f`/`0x26` threshold cascades keep the original order even though their
  middle results cannot occur.
- `0x427e10`: 4/0 flag bytes `0x13..0x2e` from the player's mode dword
  (`+0x4c8`) and its opponent's (handle at `+0x3b0`); the group test is
  `0x43d3d0`. The native function takes the two mode values.
- `0x428e70`: per-row scores for the seven rows of the choice grid (`+0x1cc`
  values, `+0x23c` weights): the largest weight among the first nonzero cell
  and the enabled cells, or the 8-bit signed average of the enabled weights
  for rows flagged in the table at `0x4fb6c0` when the mode is 2 or below. The
  result reports whether any enabled cell has a nonzero weight.

`tools/verify_ai_features.py` runs each complete original 8,192 times and
compares outputs, results, untouched bytes and the pool objects
(`ai-features-verification.json`). The larger evaluators `0x428110` and
`0x428610` are not yet ported.
