#ifndef VERTRIX_SURFACE_BOUNDS_H
#define VERTRIX_SURFACE_BOUNDS_H
#include "surface.h"

typedef struct
{
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
} VertrixSurfaceBounds;

/* Original 0x4792d0: bounding box of the nonzero pixels of a surface, scanned column by column
 * with the pixel reader 0x478f10 (1, 2 and 4 byte pixels; other sizes read as zero). Extremes are
 * tracked as signed words. When the smallest nonzero x equals width - 1 (which includes an
 * image without any nonzero pixel) the box is the whole image, a quirk of the original.
 * Returns 1 and fills bounds and differs (1 unless the box is the whole image at the origin),
 * or returns 0, leaving the outputs untouched, when the surface is invalid, a dimension exceeds
 * 0x7fff, or a pixel lies outside the supplied storage. */
int vertrix_surface_bounds(const VertrixSurface *surface, VertrixSurfaceBounds *bounds,
                           uint32_t *differs);
#endif
