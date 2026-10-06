# Fixed-point and angle helpers

`fixed_point.c` recovers the 16.16 fixed-point and angle routines used by the
actor motion code:

- `0x4849e0`: fixed-point product, low 32 bits of `(a * b) >> 16`.
- `0x4849f0`: fixed-point quotient `(a << 16) / b`. The original faults (#DE) on a
  zero divisor or a quotient that does not fit 32 bits; the native version reports
  that through a `valid` flag. The oracle confirms every faulting case.
- `0x484630`: iterative square root (Newton steps from 1 until two guesses differ by
  at most one, with 32-bit wrap in the averaging step); `0x484680`: the same root of
  the squared distance between two points whose coordinates are the low 16 bits of
  four registers.
- `0x4845d0`: angle in degrees for a signed 16.16 ratio through the original
  65,536-word table at `0x59993c` (zero beyond the table, 180 minus the entry for
  negative ratios, 180 for negative ones past the table). The table is a runtime
  structure and is supplied by the caller.
- `0x484700`: heading in degrees between two points: angle of the horizontal
  component over the distance, `360 - angle` when the vertical component is
  positive; identical points give 0. Only the low 16 bits (`ax`) are defined.

The scratch globals the original stores through (`0x598db4..0x598df8`) are dead
temporaries and are not reproduced. `tools/verify_fixed_point.py` runs each complete
original 8,192 times (6,185 divisions plus 2,007 matched faults). Evidence:
`fixed-point-verification.json`.
