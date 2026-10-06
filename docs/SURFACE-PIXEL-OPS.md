# Surface pixel operations

`surface_pixel_ops.c` recovers five software surface routines on `VertrixSurface`
views (data `+0`, width `+4`, height `+8`, pixel size `+0xc`, stride `+0x14`). The original
never bounds-checks; the native code validates that every byte it would touch is inside the
supplied storage and otherwise preserves everything and returns 0. The scratch globals the
original leaves behind (`0x5589xx..0x558cxx`) are not modeled.

- `0x479450`: OR a byte into a rectangle of one-byte pixels; rows are `+4` bytes apart.
- `0x479d70`: copy one pixel (target size 1/2/4 bytes; coordinates outside the target are
  a no-op; each surface locates its own pixel with `0x478eb0`).
- `0x479b50`: vertical mirror in place, rows packed (row length = low signed word of the
  width, times 3 truncated to a word for 3-byte pixels; rows = height / 2). A negative height
  makes the original run 65,534 times and is rejected.
- `0x47e200`: copy 32-bit pixels whose alpha byte is nonzero between two 4-byte surfaces
  whose flag dwords (`+0x10`) are zero.
- `0x47cd60`: decimate a 4-byte surface by a divisor into a packed dword output, with the
  original's row advance of `(divisor - 1)` widths after the columns read.

Not ported: `0x47c930` and `0x47cb40` (blends through the runtime table at `0x558cf0`),
`0x4792d0` (bounding box, depends on `0x478f10` and local stack words).

Verification (`tools/verify_surface_pixel_ops.py`): 4,096 complete original executions per
routine (13 rejected `0x479d70` cases checked for preserved storage); both surfaces' data and
the decimation output compare byte for byte. Evidence: `surface-pixel-ops-verification.json`.
