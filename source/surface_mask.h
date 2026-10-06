#ifndef VERTRIX_SURFACE_MASK_H
#define VERTRIX_SURFACE_MASK_H
#include <stdint.h>

#include "call_glue.h"

/* Original 0x4ab200 (eax = x, edx = y, ebx = width, ecx = height, the words sign extended or
 * counted as 16 bit values): 0x478eb0(surface, x, y, the source pixels) returns the first byte of
 * the mask (`mask`, rows `mask_width` = the surface's dword at +4 apart); for every pixel of the
 * width x height rectangle of `source` (rows width + skip pixels apart, skip being the global
 * 0x5bb79c) whose alpha byte is not zero the mask byte gets bit 0 set. Zero counts leave a loop
 * out: no rows for height zero, rows without pixels for width zero. The registers of the call
 * are the surface token, x and y sign extended and the source token. */
void vertrix_surface_mask32(const VertrixCalls *calls, uint32_t surface, uint32_t mask_width,
                            uint32_t source_token, uint32_t skip, uint32_t x, uint32_t y,
                            uint32_t width, uint32_t height, const uint32_t *source, uint8_t *mask);

#endif
