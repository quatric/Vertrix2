# Actor refresh state and base slot methods

`actor_refresh.c` recovers original `0x4ac1c0`, `0x4ac1e0`, `0x4adf70`,
`0x4adfa0`, `0x4adfb0`, `0x4adfe0`, `0x4adf90` (base vtable slot 6), `0x4ae0f0`
and `0x4ae0c0`. Shared state is the gate `0x5bb710` plus six refresh words
`0x5bb714..0x5bb728` (`VertrixActorRefresh`).

- `4ac1c0` clears the six words; `4ac1e0` sets one to 1.
- `4adf70` clears actor `0x120` only when the gate is 1.
- `4adfb0` takes the signed word at actor `0x148` as refresh index; `0xffff`
  means use actor `0x120` instead. `4adfe0`/`4adf90` set that value (actor
  `0x120 = 1` or refresh word = 1).
- `4ae0f0` calls slot 2 when actor `0x124` is 0; `4ae0c0` when `0x124` is 1 and
  `4adfb0` yields 1. Slot 2 is a supplied callback.

The base actor vtable `0x517af4` is `4ac130, 4ae150, 4ae140, 4ae010, 4ae0c0,
4ae0f0, 4adf90`; `4ae150`/`4adf70` were already recovered, `4ae140` calls
`4ade60` and `4ae010` draws through `47ce10` (both separate). The original
refresh index is unbounded; native entry points accept 0..5 and reject others.

`tools/verify_actor_refresh.py` compares each complete original in 4,096+ cases
against whole actor storage and global state. Evidence:
`actor-refresh-verification.json`.
