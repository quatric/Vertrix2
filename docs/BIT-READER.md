# Bit reader

`bit_reader.c`: the MSB-first bit reader state (`0x51f014` address, `0x51f018` position).
`0x4046e0` one bit, `0x404610` up to 24 bits over 3 bytes (zero count returns 0, no change),
`0x404680` up to 16 bits over 2 bytes, `0x4060e0` give back bytes to the stream (copy `0x4eb5e0`
supplied; fails with -1 when the fill level `[stream+0x10]` is negative and the count positive).
Shift counts use the low five bits as the processor does.

Verification: `tools/verify_bit_reader.py`, 4,096 executions each, including wide positions.
Evidence: `bit-reader-verification.json`.
