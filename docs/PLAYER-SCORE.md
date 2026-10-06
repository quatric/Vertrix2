# Player score accumulator (0x43ba90)

`vertrix_player_add_score` in `source/player_slots.c` reproduces the
original difficulty-scaled score accumulator, used by the post-lock
handlers (`0x4517c0` / `0x451920`) after the match reward.

Disassembly (mapped-image bytes, matching `work/disassembly.txt:72913`):

```
0043ba90 push ecx/esi
0043ba92 mov ecx, [0x532bbc] (difficulty)
0043ba98 imul edx, [ecx*4 + 0x4f80cc] (signed 32-bit, wraps)
0043baa0 mov esi, [eax + 0x174] (score)
0043baa6 add esi, edx; mov [eax + 0x174], esi
0043baae cmp esi, 0x5f5e0ff; ja cap (unsigned, 99,999,999)
```

The live multiplier table at `0x4f80cc` reads
`5, 10, 20, 750, 1000, 1500, 0, 1` — difficulty 5+ scores at most the bare
reward. The unsigned cap means a wrapped-negative total caps upward to
99,999,999; the native uses unsigned arithmetic throughout to preserve
this exactly (and to avoid signed-overflow UB).

Native takes the table with an explicit count and refuses short storage,
null tables, and out-of-range difficulties. The return value is a native
convention (1 = stored); only state compares.

Verification (`tools/verify_player_score.py`, evidence
`docs/player-score-verification.json`): 4,096 complete original executions
pass across small / near-cap / at-cap / negative-reward / zero-reward /
zero-multiplier / random buckets, alternating the live table with random
tables (restored in the emulator each case), comparing the whole player
object, plus short-storage, out-of-range, and null-table guards.

Oracle trap caught during verification: the emulator image keeps the
previous case's overwritten table bytes, so even (live-table) cases must
rewrite the live table back before executing — otherwise the original
reads stale random multipliers while the native reads the live copy.
