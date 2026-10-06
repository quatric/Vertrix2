# Player bonus meter (0x43ba70)

`vertrix_player_bonus_ready` in `source/player_slots.c` reproduces the
original bonus-ready test.

Disassembly (`work/disassembly.txt:72905`):

```
0043ba70 cmp dword ptr [eax + 0x18c], 3
0043ba77 sete al
0043ba7a and eax, 0xff
0043ba7f ret
```

Inputs are the player object (`eax`); the bonus meter dword lives at
`+0x18c` (shared with `vertrix_player_clear_field_18c`). Returns 1 when
the meter equals 3, else 0. No other state is touched.

Native preserves short storage and returns -1 there; the original would
read out of bounds, the native refuses. This matches the direct-storage
helper convention elsewhere in `player_slots.c`.

Verification (`tools/verify_player_bonus.py`, evidence
`docs/player-bonus-verification.json`): 4,096 complete original
executions pass, plus a short-storage preservation check.

Open: `0x43b720` (progress update `+0x178 += n`, floor 0, race win at
`[0x532b34]` when `[0x532bc8] == 1`, via `0x43bb00`/`0x4715a0`/`0x43c0e0`/
`0x43ac00`/`0x4726d0`) is disassembled but not yet recovered; it is the
direct caller-context for this test in the post-lock chain
(`0x4517c0`/`0x451970` -> `0x43ba70` -> `0x451a60` vs spawn).
