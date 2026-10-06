#ifndef VERTRIX_SURFACE_PIXEL_OPS_H
#define VERTRIX_SURFACE_PIXEL_OPS_H
#include "surface.h"

/* Software surface operations of the original (0x479450..0x47e200). A VertrixSurface mirrors the
 * original object: data (+0), width (+4), height (+8), bytes per pixel (+0xc, byte), stride
 * (+0x14). The original performs no bounds checks. Every operation here validates that all the
 * bytes it would touch lie inside the supplied data and otherwise preserves all storage and
 * returns 0. The original also leaves the last address/count in scratch globals
 * (0x5589f0..0x558c54); those are not modeled. */

/* Original 0x479450: OR value into a width x rows rectangle of one-byte pixels whose rows are
 * surface width (+4) bytes apart, starting at (x, y). Only the low byte of every row start is
 * relevant, so x and y wrap like 32-bit values. */
int vertrix_surface_or_rectangle(VertrixSurface *surface, uint32_t x, uint32_t y, uint32_t width,
                                 uint32_t rows, uint8_t value);

/* Original 0x479d70: copy one pixel at (x, y) from source to target. Negative or out-of-range
 * coordinates against the target dimensions do nothing (and succeed). The pixel size is the
 * target's (1, 2 or 4 bytes, otherwise nothing is copied); each surface locates its own pixel with
 * its own stride and pixel size. */
int vertrix_surface_copy_pixel(const VertrixSurface *source, VertrixSurface *target, int32_t x,
                               int32_t y);

/* Original 0x479b50: mirror the image top to bottom in place, row by row from the outside in. The
 * row length is the low signed word of the width (times 3, truncated to a signed word, for three
 * byte pixels) and the row count the low signed word of the height divided by two. Rows are
 * packed (not stride apart). Pixel sizes other than 1..4 do nothing. A negative height makes the
 * original run 65534 times past the image and is rejected here. */
int vertrix_surface_flip_vertical(VertrixSurface *surface);

/* Original 0x47e200: copy 32-bit pixels whose alpha byte is nonzero from the source rectangle at
 * (source_x, source_y) into the target at (target_x, target_y). Both surfaces must have 4-byte
 * pixels and a zero dword at +0x10 (flag); otherwise nothing happens. Row pitches are the
 * surface widths (+4) in pixels. */
int vertrix_surface_blit_keyed(VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                               const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                               uint32_t width, uint32_t rows, uint32_t target_flag,
                               uint32_t source_flag);

/* Original 0x47cd60: shrink a 4-byte-pixel surface by taking every divisor-th pixel of every
 * divisor-th row (width / divisor columns and height / divisor rows) into a packed output of
 * output_count dwords. The next source row starts (divisor - 1) widths after the end of the
 * columns read, exactly as the original advances. divisor must be nonzero. Other pixel sizes do
 * nothing. */
int vertrix_surface_decimate(const VertrixSurface *source, uint32_t divisor, uint32_t *output,
                             size_t output_count);
#endif
