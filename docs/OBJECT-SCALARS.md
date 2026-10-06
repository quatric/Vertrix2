# Object scalar accessors

`object_scalars.c` recovers 30 one-field routines: the flag table at `+0x5cc` (`0x4126d0`,
`0x4126f0`), the timer period and counter (`0x418820`, `0x418830`, `0x418840`, `0x418870`),
piece placement offsets (`0x42a940`, `0x42a950`), the y-versus-limit comparison (`0x42ba40`),
player fields (`0x43b860`, `0x43b870`, `0x43b970`, `0x43bad0`, `0x43bae0`, `0x43bd40`,
`0x43cc90`, `0x43cde0`) and single global cells (`0x415b30`, `0x415b40`, `0x415d60`,
`0x415d90`, `0x417f40`, `0x41a930`, `0x41d660`).

Also `0x415b10` and `0x415530` (global table resets), `0x415d40` (index step), `0x418150`
(unsigned compare), `0x425e00` (count of used table entries) and `0x43bd60` (partner free test).
`piece_children.c` gained `0x43a510`, `0x43a560` and `0x42b920`, verified in
`piece-children-verification.json`.

Object storage is raw bytes with bounds checks; globals are caller-supplied cells (arrays take a
count, because the original indexes without bounds). `tools/verify_object_scalars.py` runs each
original routine 4,096 times and compares whole objects, global cells and returned values.
Evidence: `object-scalars-verification.json`.
