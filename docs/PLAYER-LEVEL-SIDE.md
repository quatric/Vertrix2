# Level-side handler (0x431400)

`vertrix_player_level_side` in `source/player_slots.c` reproduces the side
refresh driven by `vertrix_player_set_level` (`0x43b810`): with the holder's
child at `+0xa60` present and its dword at `+0x168` clear, the delay table
(original `0x4f7d50`, dword at level + alter * 10) sets the period
(`0x4ac7d0`), the frame table (original `0x4f7dc8`, word at level * 2 +
alter * 20) sets the word at `+0x1a`, and the counter clears (`0x4ac510`).
A null child or a nonzero slot dword returns the holder unchanged (the
dword means already set up, confirmed against the branch bytes — the
disassembly text misattributes both jump targets). Returns the child on
the full path, zero when storage is short or an object does not resolve.

Verification (`tools/verify_player_level_side.py`, evidence
`docs/player-level-side-verification.json`): 1,024 complete original
executions pass with both callees executing for real on both sides,
covering the null-child, already-set and full paths; the returned handle,
the holder bytes and every pool object compare.
