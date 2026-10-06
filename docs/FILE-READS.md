# Exact-size file reads

`file_reads.c`: `0x40c220` read n bytes through the runtime read `0x4ebec0` (supplied), zero
filling the buffer on a short read; always returns 0. `0x40c260`/`0x40c320` (1 byte, identical),
`0x40c2a0` (2), `0x40c2e0` (4) fix the count; `0x40c360` reads 2 bytes then swaps them.
Not ported: `0x40c1c0` (opens a file through `0x4ebb78`), `0x40c430` (flag-selected mixer call).

Verification: `tools/verify_file_reads.py`, 4,096 each, full and short reads. Evidence:
`file-reads-verification.json`.

`0x410890` flips the high bit of a buffer span in place (post-read transform
used at `0x410ee3`). `tools/verify_flip_bits.py` runs it 4,096 times over
random buffers and counts including zero and whole-buffer spans, plus
involution (double application restores bytes) and overrun preservation
checks. Evidence: `flip-bits-verification.json`.
