# Player progress update (0x43b720)

`vertrix_player_progress_update` in `source/player_slots.c` reproduces the
original race-progress driver.

Disassembly (`work/disassembly.txt:72614`):

```
0043b720 push ebx/ecx/esi/edi; ecx = eax (player)
0043b726 mov esi, [eax + 0x178]; lea ebx, [esi + edx] (signed add)
0043b72f test ebx, ebx; jl 0x43b79f (ebx = 0, floor)
0043b733 mov edx, [0x532bc8]; cmp edx, 1; jne store
0043b73e mov edi, [0x532b34]; cmp ebx, edi; jb store
0043b748 mov [eax + 0x464], edx (race flag, 1)
0043b74e mov eax, [eax + 0x3b0]; mov al, [eax + 0x4c5]; mov ebx, edi
0043b75c test al, al; je set_flag ([0x532a3c] = 1)
0043b760 mov eax, ecx; xor edx, edx; call 0x43bb00
0043b769 mov eax, [ecx]; call 0x4715a0
0043b770 mov edx, [0x4f81b4]; mov eax, ecx; call 0x43c0e0
0043b77d mov eax, ecx; mov [ecx + 0x474], 1; call 0x43ac00
store: mov [ecx + 0x178], ebx; cmp esi, ebx; jne refresh (0x4726d0, return 1)
0043b798 xor eax, eax; return 0
```

Delta arrives in `edx` (signed). The floor uses a signed test; the race
limit uses an unsigned compare. The win path stores the limit (not the
overshoot). The trailing refresh observes the win handler's return on the
win path, the opponent handle on the dead-opponent path, and the player
handle otherwise — the same convention as the conditional reset's trailing
refresh observing its reset.

Native takes the four globals (`VertrixProgressGlobals`: mode flag
`0x532bc8`, race limit `0x532b34`, loser flag `0x532a3c`, win effect
`0x4f81b4`) plus supplied boundaries for `0x43bb00` (always b01 = 0),
`0x4715a0` (mode is the dword at player +0), `0x43c0e0`, `0x43ac00`
(returns the refresh argument) and `0x4726d0`. Returns 1 when the progress
changed, 0 when unchanged, -1 for short storage or an unresolvable
opponent.

Verification (`tools/verify_player_progress.py`, evidence
`docs/player-progress-verification.json`): 4,096 complete original
executions pass across floor / unchanged / normal / race-below-limit /
win-alive / win-dead / random-flag buckets, comparing return value, whole
player object, opponent untouchedness, loser flag, and all five call logs,
plus short-storage and unresolvable-opponent guards.

The win boundary itself is now recovered and composed: `vertrix_object_chain_select`
(`0x43ac00`, `source/object_glue.c`; note `docs/OBJECT-CHAIN-SELECT.md`,
evidence `docs/object-chain-select-verification.json`) runs for real inside
the progress proof, with live grid/counts/defaults, the slot-6 dispatch, the
table allocation and the release call all compared. The win handler receives
the race limit and player handle as its register arguments, forwarded to the
slot method.

Caller context: `0x43b9c0` (match reward) calls this routine before the
level bump and effect dispatch; the bonus-ready test `0x43ba70` gates the
post-lock branch that follows. See `PLAYER-BONUS.md`.
