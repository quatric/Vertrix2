# Surface blit (0x47ce10)

`vertrix_surface_blit` in `source/surface_blit.c` reproduces the original rectangle copy with
pixel format conversion. The original call takes the target surface (eax), the source surface
(edx), the target x and y (ebx, ecx) and on the stack the source x and y, the width and the height.

Surface object fields used: +0 pixel data, +4 width in pixels, +0xc bytes per pixel (1..4), +0xd
sub-format (1 = 5-5-5, 2 = 5-6-5 for two-byte pixels), +0x10 pitched flag, +0x14 byte pitch.

* Neither surface pitched: rows are packed (stride = width * bytes per pixel). Supported pairs
  (target <- source): 4<-4, 3<-4, 2<-4, 2<-2, 1<-4, 1<-1, 4<-1, 4<-2.
* Either surface pitched: rows follow the byte pitches (0x478eb0 supplies the pixel address).
  Supported pairs: equal formats, 3<-4, 2<-4, 1<-4, 4<-1, 4<-2.
* 3<-4 copies the low three bytes; 2<-4 packs 5-6-5 or 5-5-5 by the target sub-format; 1<-4 packs
  3-3-2 (RRRGGGBB); 4<-1 and 4<-2 unpack the same layouts to 0x00RRGGBB (4<-2 by the source
  sub-format). Any other pair, or a 2-byte surface with another sub-format, copies nothing.
* The original's contiguous fast paths (width equal to both surface widths) copy the same bytes as
  the row loops. Overlapping rectangles of one surface are not supported natively.

Evidence: 8,192 complete original executions over every format pair, sub-format and pitched
combination with random rectangles; the target pixel memory (including untouched bytes) compares and
the source stays unchanged (`tools/verify_surface_blit.py`, `docs/surface-blit-verification.json`).

## Wrappers 0x41a2f0 and 0x41ab90

`vertrix_surface_blit_progress` draws the leading `width * numerator / denominator` columns of a bar image at (0, 461) of the target (0x41a2f0); `vertrix_surface_blit_region` copies a source region given as four words (x, y, width, height) to the target origin (0x41ab90). Both verified with real pixel memory through the original wrappers, 2,048 executions each.

`vertrix_surface_blit_whole` (0x441b30) copies the source over the target from (0, 0) with the target size; absent surfaces do nothing. 2,048 executions.
