# Actor list idle checks

`actor_list_idle.c` recovers the "is everything idle" scans over five actor handle arrays
(pointer/count globals `0x546720/24`, `0x54675c/60`, `0x546748/4c`, `0x546734/38`,
`0x546770/74`). The module receives the handles and resolves objects through
`VertrixObjectStorage`.

- `0x471c90`, `0x471cd0`, `0x471d10`, `0x471d50`, `0x472360`: 1 when every actor's handler
  token (`+0x154`, via `0x4ac900`) is zero, else 0.
- `0x471c40`: 1 when every actor either has owner token `+0x14c` equal to the argument or
  a zero handler token.

Verification (`tools/verify_actor_list_idle.py`): 4,096 complete original executions each
over arrays of 0 to 12 actors. Evidence: `actor-list-idle-verification.json`.
