# Object slot arrays and initialisers

`object_slots.c` recovers the destroy-and-clear loop `0x4b22c0` as it is used on arrays inside
object storage: `0x42a480` and `0x42a4a0` (the three piece children at `+0x15c` / `+0x170`) and
`0x43d800` (500 handles at `+0x15c`, 8 at `+0x92c`). Each set handle is destroyed (virtual
destructor, flag 2, supplied as `VertrixBoardDestroy`) and cleared in order. It also covers
`0x429670` (base actor construct plus marker fields), `0x429660` (address + 4), `0x43d300` (a
linked list object is not empty), `0x475da0` (three dwords at `+8`) and `0x476120` / `0x476140`
(clear / set the flag byte of 0x60-byte record `index & 0xffff`).

`tools/verify_object_slots.py` runs each original routine 2,048 times with the virtual
destructors stubbed and logged, and compares whole objects, destroy events and returned values.
Evidence: `object-slots-verification.json`.

`0x471bb0`, `0x471bf0`, `0x471d90` and `0x471dd0` apply `0x4ac920` to every handle of a global actor list.
