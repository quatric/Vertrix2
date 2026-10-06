# Generic object field routines

`object_dwords.c` recovers about 60 small routines of the library, list, score and effect
objects with generic accessors instead of one function per field:

- **Getters and setters** `vertrix_object_dword` / `vertrix_object_set_dword` /
  `vertrix_object_set_pair`: the address-to-offset tables are in `object_dwords.h` (0x47e9a0,
  0x480070, 0x4877e0, 0x48a2e0, 0x48aa80, 0x4b4500, 0x4d5350, 0x47ed60..0x47ed90, 0x47f8e0,
  0x481b20, 0x484410, 0x48abe0, 0x4b35b0, 0x4b3c30, 0x4b4fa0).
- **Lists and tables** (0x4879e0, 0x48d5f0, 0x487a20, 0x48d630, 0x4b6fa0, 0x4b79c0, 0x488030,
  0x488040): item lookups read the original pointer through `VertrixMemoryRead`.
- **Range objects** (0x482540, 0x48a8a0, 0x48a910, 0x48aa70, 0x48aad0, 0x48aaf0, 0x48abe0,
  0x48abf0, 0x4d2700) and the **timer words** (0x4b6530..0x4b65b0, 0x4b6690) with the running
  test 0x4b6560, which reports running when the flag `+0x174` is zero (found by the oracle).
- **Compound routines**: 0x4b2290 (zero n dwords), 0x47ecf0 (arm once), 0x482050, 0x4d2d70
  (status check), 0x4c5d60 (`(255 * (2a + 1) + b) / (2b)` with wrapping 32-bit arithmetic; a zero
  divisor or `INT_MIN / -1` faults in the original and is rejected) and 0x4c0990 (clear object
  links through a resolver).
- **Resource table entry** `0x487770`: when the dword at resource `+0x14` is 1, the dword at
  `[resource + 8][index]` (original addresses through `VertrixMemoryRead`); otherwise 0.
- **Count refresh** `0x4ac4a0`: when the resource handle at `+0xb0` is nonzero, refresh the cached
  count at `+0xd0` from the entry selected by the index at `+0xb8`. Null resource or non-1 flag
  leaves everything untouched.
- **Range copy** `0x48a930`: copy bytes from the source range object (absolute read pointer at
  `+4`, end at `+8`) to a flat destination; the count is the smaller of `factor_a * factor_b`
  and the available span, the cursor advances, and shared globals record the outcome.
- **List node alloc** `0x487640`: store the value at `+4`, allocate value * 4
  zeroed bytes (heap and fill services stubbed), and store the handle at `+0`.
- **Range save/copy** `0x4121e0`: save `[object + 0x5bc]`, start the range, copy 1 * 8 bytes to
  `+0x5b8`, copy the saved value times 12 to the object start, and restore the saved dword. The
  copy flags are data, not status (the original ignores them).

The routines that are plain `ret` in the original (0x404580, 0x425f40, 0x4713c0, 0x471ee0,
0x477930, 0x47f8f0, 0x4b3360, 0x4c5c20) need no native code.

`tools/verify_object_dwords.py` runs each original routine 2,048 times over a pool of random
objects and compares whole objects and returned values. Evidence:
`object-dwords-verification.json`.
