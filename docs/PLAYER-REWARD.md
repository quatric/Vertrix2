# Player match reward (0x43b9c0)

`vertrix_player_match_reward` in `source/player_slots.c` reproduces the
original chain/meter reward driver, the direct caller of the progress
update `0x43b720` recovered in `PLAYER-PROGRESS.md`.

Disassembly (`work/disassembly.txt:72847`):

```
0043b9c0 push ebx/ecx/esi/edi; ecx = eax (player), esi = edx (reward)
0043b9c8 mov ebx, [eax + 0x180]; sub ebx, edx
0043b9d0 cmp ebx, 1; jge store (signed)
loop: edx = 1; eax = ecx; call 0x43b720 (progress +1)
0043b9e3 edx = 1; eax = ecx; call 0x43b800 (level +1 via 0x43b810)
0043b9ec edx = [0x4f8190]; eax = ecx; add ebx, 0xc; call 0x43c0e0
0043b9fc call 0x4726d0; mov [ecx + 0x3ac], 1
0043ba07 cmp ebx, 1; jl loop (signed)
store: edx = [ecx + 0x44c]; mov [ecx + 0x180], ebx
0043ba1c cmp edx, 1; je suppress ([ecx + 0x18c] = 0)
0043ba21 edx = [ecx + 0x18c] + esi; mov [ecx + 0x18c], edx
0043ba2f cmp edx, 3; ja cap ([ecx + 0x18c] = 3, unsigned)
```

The loop's `ebx += 0xc` lands between the level and effect calls; the flag
store follows the refresh. The meter add wraps 32-bit; only an unsigned
result above 3 is capped. The return value is a native convention (1 =
stored); only state and event logs compare, as with `0x43bb00`.

Native takes the reward, the supplied loop effect (`[0x4f8190]`, read live
by the caller as with the side-setup steps), and supplied boundaries for
`0x43b720`, `0x43b800` (both always delta 1), `0x43c0e0` and `0x4726d0`.
Short storage preserves everything and returns 0.

Verification (`tools/verify_player_reward.py`, evidence
`docs/player-reward-verification.json`): 4,096 complete original
executions pass across multi-loop / single-loop / no-loop / suppress /
cap / exact-3 / negative-reward / random buckets, comparing the whole
player object and all four call logs.

Open: composing the loop with the real `vertrix_player_progress_update`
and `vertrix_player_set_level` natives instead of stubs (this proof
isolates the reward logic; the callees are proven separately); the 93
bonus effects hanging off `0x450ff0..0x456033` that consume the meter.
