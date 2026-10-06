# Resource record

`resource_record.c` recovers routines on a resource record (name string at
`+0x00`, path string at `+0x104`, flag bytes `+0x220..+0x224`, five handles at
`+0x268..+0x278`) and one text measure:

- `0x441530`: initialize (copy both strings, clear the handles, store the
  flags). The original copies without a bound; the native function refuses
  strings longer than 259 bytes.
- `0x441a80`: release the handles (`0x478d80`) in the original order, the ones
  at `+0x270` and `+0x26c` only when byte `+0x220` / `+0x222` equals 1, then
  clear them.
- `0x441b30`: when `+0x274` and `+0x278` are both set, call the draw routine
  `0x47ce10` with them and the first object's dwords `+0x4` and `+0x8`.
- `0x442b00`: string width from the 256-byte glyph width table at `0x544790`
  (filled at runtime; supplied as a parameter): space adds 4, other characters
  add width minus one, a nonzero total gains one. The original result's upper
  16 bits mix a caller register, so only the low 16 bits are defined.

`tools/verify_resource_record.py` runs each complete original 4,096 times with
`0x478d80` and `0x47ce10` stubbed and compares the whole record, every pool
object, the ordered events and the width (`resource-record-verification.json`).

`0x41a9e0` releases the record, then re-reads the global cell at `0x544070`:
when still nonzero it runs the two-level virtual method (`+0x27c` names a
table whose first dword is the method, invoked with the object and flag 2)
and clears the cell. Covered by the same verifier (4,096 cases over null and
live globals with stubbed methods).
