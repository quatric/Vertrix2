# Actor chain visit routines

`actor_chain_visit.c` recovers the two per-node routines that the chain walk
(see ACTOR-DRAW-SLOT.md) calls.

- `0x4ac8a0`: when actor dword `0xb0` (bank) is nonzero, store the result of
  `4877f0(bank, dword 0xb8)` at dword `0xb4`.
- `0x4af8c0`: store `edx` in global `0x5bc010`, then call `4ae3e0(actor, dword
  0x144)`; when nonzero call `4af560(actor)`.

`4877f0`, `4ae3e0` and `4af560` are supplied boundaries.
`tools/verify_actor_chain_visit.py` runs both complete originals in 4,096 cases
each and compares call order, registers, whole actor storage and the global.
Evidence: `actor-chain-visit-verification.json`.
