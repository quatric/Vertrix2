# MPEG audio header

`mpeg_header.c`: `0x404480` decodes a frame header word into the structure (channels, version,
layer, sample rate index, bitrate, flags, and for layer 3 the frame size from the tables
`0x4f40ac` and `0x4f41ac`). Invalid sample rate bits call `0x4eb4d4(1)` (supplied) and decoding
continues. A zero sample rate divisor faults in the original; native returns 0.

Verification: `tools/verify_mpeg_header.py`, about 4,000 headers (faulting divisors skipped).
Evidence: `mpeg-header-verification.json`.
