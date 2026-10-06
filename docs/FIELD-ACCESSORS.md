# Field accessors

`field_accessors.c` recovers 24 one-field routines of the settings, score, stream and surface
objects: the flip flag `0x471e60` / `0x471e80`, player-table fields `0x471ea0..0x471ed0`,
the index ramp `0x45f1e0` (the original stores the loop counter, so the seven bytes become
0..6, not zeros), flag and counter objects `0x4757b0..0x475e40`, stream initialisers
`0x477240` / `0x477870`, rectangle words `0x477e10` / `0x478460`, the surface cell address
`0x479b30` and the nonzero test `0x47e990`.

Handles the original takes from global arrays are resolved by the caller; native functions work
on the object storage with bounds checks. `tools/verify_field_accessors.py` runs each original
routine 4,096 times and compares whole objects, globals and returned values. Evidence:
`field-accessors-verification.json`.
