# Actor angle motion

`actor_angle.c` recovers the actor angle helpers (angles are 16-bit words in whole
degrees, 360 per turn) built on `fixed_point.c`:

- `0x4ad110`: advance the angle word at `+0x34` by the rate word at `+0x38`, `count`
  times, wrapping after every step (unsigned remainder by 360 when the signed word is
  at least 360, `(word + 360) % 360` when negative). Returns 1 when no wrap was
  needed, 0 otherwise. A zero rate or count changes nothing.
- `0x4ace40`: turn the angle at `+0x24` toward the target at `+0x26` by `count *
  rate` (signed word at `+0x28`), the short way round the circle; reaching or passing
  the target snaps to it. Returns 1 while the angle differs from the target.
- `0x4ad1c0` / `0x4ad210`: scale the x and y factors (16.16 tables at `0x59939c` and
  `0x598dfc`, 360 entries each, supplied by the caller) of the angle at `+0x24` /
  `+0x34` by two radii. The original reads past the tables for an angle outside
  0..359; the native version rejects it.
- `0x4ad260`: point on the circle of the radius word `+0x2a` and angle `+0x24` around
  the origin words `+0x2c`/`+0x2e` (x added, y subtracted; 16-bit results).

The scratch globals the original uses (`0x5bb5dc..0x5bb608`) are dead temporaries and
are not reproduced. `tools/verify_actor_angle.py` runs the complete originals over
random actors and tables (4,096 executions for spin and turn, 2,800 to 3,800 for
the table users after excluding out-of-range angles). Evidence:
`actor-angle-verification.json`.
