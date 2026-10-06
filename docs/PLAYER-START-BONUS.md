# Bonus starter (0x451a60)

`vertrix_player_start_bonus` in `source/player_slots.c` reproduces the
original bonus starter at the end of the no-match bonus branch: spawn the
bonus piece, run the bonus event, reset the piece progress.

Disassembly (`work/disassembly.txt:101434`):

```
00451a60 push ebx/ecx/edx; ecx = eax (player)
00451a65 mov eax, [eax + 0x15c] (board)
00451a6b mov edx, [ecx + 0x18d]; mov ebx, [ecx + 0x17c] (level, ignored below)
00451a77 sar edx, 0x18 (signed top byte = byte at +0x190)
00451a7a call 0x4320d0 (spawn with the kind)
00451a7f mov edx, 0x451aa0; mov eax, ecx; call 0x4ac8f0 (bonus event)
00451a8b mov eax, ecx; call 0x43ad50 (piece progress = 1)
```

The kind extraction is the original's unaligned-dword-plus-shift idiom
(also seen at `0x43d260`): the dword at `+0x18d` shifted right 24,
i.e. the signed byte at `+0x190`. The level read into ebx is passthrough
garbage — `0x4320d0` never touches ebx — so the native does not read it.
The spawn and the progress reset run for real through the proven
`vertrix_piece_actor_spawn` and `vertrix_player_reset_piece_progress`;
only the event machine (`0x4ac8f0`) stays a supplied boundary taking the
player handle and the `0x451aa0` handler token.

Verification (`tools/verify_player_start_bonus.py`, evidence
`docs/player-start-bonus-verification.json`): 4,096 complete original
executions pass across occupied-slot / alloc-failure / normal / random
buckets, comparing the whole player, board, and piece objects plus the
event and finish call logs (constructor bytes excluded — the constructor
is stubbed oracle-side and proven by the piece-actor-construct suite),
plus a short-storage guard.
