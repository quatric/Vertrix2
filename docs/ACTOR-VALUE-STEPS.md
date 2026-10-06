# Actor value steps

`actor_value_steps.c` recovers small base-actor helpers (4,096 complete original
executions each):

- `0x4ac980`: step a signed value toward a target by `step * count` (32-bit
  product), clamping at the target; equal values stay put.
- `0x4acb00` / `0x4ad750`: the same stepping applied in place to the signed word at
  `+0x1e` (target `+0x20`, step `+0x22`) of an actor and to the dword at `+0x64`
  (target `+0x68`, step `+0x6c`) of another object type; each returns 1 while the
  stored value still differs from the target.
- `0x4ac3b0`: `+0xcc` divided (unsigned) by `+0xd0`, with a zero divisor read as one.
- `0x4ac420`: reduce `+0xcc` by whole `+0xd0` steps (zero divisor as one): the product reaching
  the counter zeroes it, otherwise it is subtracted. No return contract, so only storage compares.
- `0x4ac7e0` / `0x4ac810`: period (`+0xc0`) / dword `+0xd0` = random draw modulo the
  word at `+0xc8` / `+0xd8`, plus the base at `+0xc4` / `+0xd4`. The draw (`0x4826c0`,
  already recovered in `random.c`) is a supplied callback; the oracle stubs it and
  replays its results.
- `0x4ac760` / `0x4ac780`: whether the frame index at `+0xb8` (plus one for
  `0x4ac780`) equals the frame count (`0x487860`, resource `+4`) of the handle at
  `+0xb0`. The frame count is a supplied callback; handles are identity tokens.

Evidence: `actor-value-steps-verification.json`; script
`tools/verify_actor_value_steps.py` (whole object compared).
