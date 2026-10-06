# Board field accessors

`board_fields.c` recovers the small board accessors `0x431380`, `0x432000`, `0x431480`,
`0x431490` (dword field of the object whose handle is stored in the board), `0x431d80`
(`+0xa68`), `0x4334a0` / `0x4342f0` (byte counter at `+0x838`, value byte `+0x839`),
`0x432010` (active piece below the top margin) and `0x430090` (extra object has handler
`0x44c860`). `actor_fields.c` gains `0x4ac470` (`+0xd0 = steps * 12`) and `0x4ac900`
(handler at `+0x154`). `board_collections.c` gains the 260-entry `+0x324` collection
(`0x42eee0`).

Object handles resolve through `VertrixObjectStorage`; the original dereferences them
directly. `tools/verify_board_fields.py` runs each original routine 4,096 times and compares
returned values and whole storage. Evidence: `board-fields-verification.json`.
