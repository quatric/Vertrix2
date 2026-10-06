# Player level bump (0x43b800)

`vertrix_player_bump_level` in `source/player_slots.c` reproduces the
original level-bump wrapper, used by the match-reward loop in place of a
direct level set.

Disassembly (mapped-image bytes):

```
0043b800 add edx, [eax + 0x17c]; call 0x43b810; ret
```

Delta arrives in `edx` and wraps 32-bit against the level dword at
`+0x17c`; the sum goes through the proven `0x43b810`
(`vertrix_player_set_level`: clamp 0..9, store, cursor notify via
`0x431400` on change). The native composes the two proven pieces with
unsigned wrap arithmetic and returns the set-level result unchanged
(1 changed, 0 unchanged, -1 short storage).

Verification (`tools/verify_player_bump.py`, evidence
`docs/player-bump-verification.json`): 4,096 complete original executions
pass — return value, whole player object, and notify log all compare —
across +1 / clamp-high / clamp-low / unchanged / wrapped / -1 / random
buckets, with `0x431400` stubbed and logged. The inner `0x43b810` runs
natively on both sides through the shared implementation, so this proof
also covers the composition. Short-storage guard included.
