# Player chain initializer (0x43ba60)

`vertrix_player_init_chain` in `source/player_slots.c` reproduces the
original chain-seed store.

Disassembly (mapped-image bytes):

```
0043ba60 mov dword ptr [eax + 0x180], 0xc
0043ba6a ret
```

Stores 12 in the chain dword at `+0x180` (the same field the match reward
`0x43b9c0` decrements). No callees, no return contract; the native returns
1 when stored and 0 for short storage (preserved).

Verification (`tools/verify_player_chain_init.py`, evidence
`docs/player-chain-init-verification.json`): 4,096 complete original
executions pass comparing the whole player object, plus a short-storage
guard.
