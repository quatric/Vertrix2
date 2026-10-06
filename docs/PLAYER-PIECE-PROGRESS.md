# Player piece-progress reset (0x43ad50)

`vertrix_player_reset_piece_progress` in `source/player_slots.c` reproduces
the original piece-progress store, used by the bonus starter `0x451a60`
after spawning.

Disassembly (`work/disassembly.txt:71871`):

```
0043ad50 mov eax, [eax + 0x450] (piece handle)
0043ad56 mov [eax + 0x178], 1
0043ad60 ret
```

Stores 1 in the progress dword at `+0x178` of the piece resolved from the
handle at `+0x450` (the same `PIECE_TARGET` field the preview generator
uses). The original returns the piece address in eax; the native returns 1
when stored and 0 for short storage or an unresolvable piece, following
the `vertrix_player_conditional_reset` convention where only state
compares.

Verification (`tools/verify_player_piece_progress.py`, evidence
`docs/player-piece-progress-verification.json`): 4,096 complete original
executions pass comparing the whole player (untouched) and piece objects,
plus short-storage and unresolvable-piece guards.
