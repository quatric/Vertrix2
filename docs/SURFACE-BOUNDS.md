# Surface bounding box

`surface_bounds.c` recovers `0x4792d0`: the bounding box of the nonzero pixels of a software
surface, using the pixel reader `0x478f10` (1, 2 and 4 byte pixels; other sizes read as
zero). The scan walks columns then rows and tracks the extremes as signed words. Quirk kept:
when the smallest nonzero x equals width - 1 (which includes an image with no nonzero
pixel) the box is reported as the whole image. The function also returns 1 unless the box is
the whole image at the origin.

The native version rejects (returns 0, outputs untouched) dimensions above `0x7fff` and pixels
outside the supplied storage.

Verification (`tools/verify_surface_bounds.py`): 4,096 complete original executions over
0..20 column by 0..16 row surfaces of every pixel size (empty, sparse, dense, first-column
and last-column images); the four output dwords and the result compare. Evidence:
`surface-bounds-verification.json`.
