# Session registers

`session_registers.c`: `0x415550` releases the latch at `0x532b40` (only when it equals 1);
`0x415b50`, `0x415b90`, `0x415bd0` reset the registers `0x532a68/6c/70` and the cleared group
`0x532aa4..ab0` from the dword `0x5332bc` (open variant stores `0xffffffff` in `0x532a6c`;
the last variant only touches `0x532a6c`).

Verification: `tools/verify_session_registers.py`, 4,096 complete original executions each;
whole register memory compares. Evidence: `session-registers-verification.json`.
