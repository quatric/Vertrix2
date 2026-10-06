# One-field actor setters

`actor_fields.c` recovers four tiny base-actor methods used throughout the
game (`0x4ac8f0` alone has 839 call sites):

- `0x4ac510`: counter at `+0xbc` = 0.
- `0x4ac7b0`: period at `+0xc0` = 12 * steps (32-bit wrap).
- `0x4ac7d0`: period at `+0xc0` = value.
- `0x4ac8f0`: handler token at `+0x154` = value (an original address, not a
  native pointer).
- `0x4ac380`: dword at `+0xcc` = 0. `0x4ac490`: dword at `+0xd0` = value.
- `0x4ac710`: frame index at `+0xb8` = value (`0x4ac8a0` looks it up in the bank at `+0xb0`).

`tools/verify_actor_fields.py` runs each complete original 4,096 times over
random actor storage and compares the whole object; short storage is rejected
unchanged. Evidence: `actor-fields-verification.json`.

## Timers, counters and further setters

`actor_fields.c` also recovers 0x4ac370 (add the frame step to `+0xcc`), 0x4ac390, 0x4ac520
(reached tests), 0x4ac540 and 0x4ac640 (quotients, divisor 1 when zero), 0x4ac700, 0x4ac740,
0x4ac750 and 0x4ac7a0 (frame counter `+0xb8`), 0x4ac840, 0x4ac860, 0x4ac910, 0x4ac930, 0x4ac950
(setters), 0x4ac920 and 0x4ac940 (copy `+0xec` / `+0xf0` to the handler), 0x4ac960, 0x4ac4e0,
0x4ac4f0, 0x4ad510, 0x4ad520 and 0x4b54d0 (position and size). Each runs 4,096 times in
`tools/verify_actor_counters.py`; evidence in `actor-counters-verification.json`.
