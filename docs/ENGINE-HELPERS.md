# Small engine helpers

`engine_helpers.c` groups five self-contained original routines:

- `0x482480`: construct a random-sample object (sample table token `+0` = 0, mode
  byte `+4` = 1, cursor `+8` = 0, position word `+0xc` = 0, seed `+0x10` = 0, class
  token `+0x14` = `0x516c24`). Class tokens are original addresses, never native
  pointers.
- `0x487870`: construct a table object (`+0` = 0, `+8` = 0, class token `+0xc` =
  `0x516dc4`, `+4` = the value of the global `0x4f81cc`, supplied by the caller).
- `0x482750`: inclusive random range, `minimum + draw(maximum - minimum + 1)` with
  16-bit operands, built on `vertrix_random_modulo` (`random.c`). A width that wraps
  to zero faults in the original and is rejected natively; the oracle confirms the
  fault.
- `0x481420`: PCX-style run-length encoded size of a byte run (runs of up to 63
  equal bytes take two bytes; a lone byte below `0xc0` takes one, otherwise two).
- `0x4ae170`: clamp the cell cursor globals (`0x5bb740..0x5bb746`: x, y, width,
  height) and recompute the index at `0x5bb73c` as `y * width + x`.

`tools/verify_engine_helpers.py` runs the complete originals (4,096 each; 17,900
random draws over three seeds, 73 faulting widths) comparing whole objects, the
cursor globals, sizes, draw values and sample positions. Evidence:
`engine-helpers-verification.json`.

## Engine range 0x480000..0x4affff: not ported

- Platform code replaced by libogc: DirectDraw/DirectInput/DirectSound COM calls and
  Win32 API users (`0x480030`, `0x4844b0` timer setup, `0x484b30`, `0x485520`,
  `0x486da0`, `0x487020`, `0x487080`, `0x487130`, `0x4871d0`, `0x4828f0`, `0x482860`,
  `0x482930`, `0x4808f0`, `0x4856d0`, `0x48c970`) and the path-string helpers over
  `CharNext`/`lstrlen` (`0x488510..0x4889a0`).
- Delphi runtime glue: destructor/constructor shells with SEH frames and
  class-token writes (`0x481b30`, `0x4823b0`, `0x484820`, `0x4848f0` file read).
- Not attempted for fidelity or size: `0x483790` (1.3 KB image routine with
  allocator callees), `0x480080` (1.7 KB switch table), `0x4ae1f0` and `0x487750`
  (dereference original pointers), `0x4ad060`/`0x4ad2c0` family.
