#ifndef VERTRIX_SURFACE_BLIT_H
#define VERTRIX_SURFACE_BLIT_H
#include "surface.h"

/* The surface object of the original 0x47ce10: pixel data (+0), width in pixels (+4), bytes per
 * pixel (+0xc), the sub-format byte (+0xd: 1 = 5-5-5, 2 = 5-6-5 for two-byte pixels) and the
 * pitched flag (+0x10) that selects the pitch based traversal; the byte pitch (+0x14) is the
 * stride of VertrixSurface. */
typedef struct
{
    VertrixSurface surface;
    uint8_t sub_format;
    uint8_t pitched;
} VertrixBlitSurface;

/* Original0x47ce10: copy the rectangle of width x height pixels at (source_x, source_y) of source
 * to (target_x, target_y) of target, converting the pixel formats. Four-byte pixels are 0x00RRGGBB
 * (the fourth byte is not touched when writing three-byte pixels), three-byte pixels are copied by
 * their low three bytes, two-byte pixels are 5-5-5 or 5-6-5 by the sub-format of the two-byte
 * surface, one-byte pixels are 3-3-2 (RRRGGGBB).
 *
 * Without the pitched flag on either surface the rows are packed (stride width * bytes per pixel)
 * and the supported pairs (target <- source) are 4<-4, 3<-4, 2<-4, 2<-2, 1<-4, 1<-1, 4<-1 and
 * 4<-2. With the flag on either surface the rows follow the byte pitches and the supported pairs
 * are equal formats, 3<-4, 2<-4, 1<-4, 4<-1 and 4<-2. Other pairs and 2-byte surfaces with another
 * sub-format copy nothing. Pixels are copied row by row in forward order; overlapping rectangles
 * of one surface are not supported. Returns 1 when the operation completed (also when nothing is
 * copied) and 0 when a rectangle does not lie inside its surface storage. */
int vertrix_surface_blit(VertrixBlitSurface *target, const VertrixBlitSurface *source,
                         uint32_t target_x, uint32_t target_y, uint32_t source_x, uint32_t source_y,
                         uint32_t width, uint32_t height);

enum
{
    VERTRIX_PROGRESS_ROW = 461
};

/* Original0x41a2f0: draw the leading part of a bar image: copy the rectangle of the source at (0,
 * 0) whose width is the source width times numerator divided by denominator (unsigned) and whose
 * height is the source height to (0, 461) of the target. Returns 0 for a zero denominator (a fault
 * in the original) or when the blit fails. */
int vertrix_surface_blit_progress(VertrixBlitSurface *target, const VertrixBlitSurface *source,
                                  uint32_t numerator, uint32_t denominator);

/* Original0x41ab90: copy the region (x, y, width, height) of the source to (0, 0) of the target. */
int vertrix_surface_blit_region(VertrixBlitSurface *target, const VertrixBlitSurface *source,
                                const uint16_t region[4]);

/* Original fragment 0x441b30: copy the source over the target from (0, 0) with the target's width
 * and height. Nothing happens (returns 1) when either surface is absent (a null pointer). */
int vertrix_surface_blit_whole(VertrixBlitSurface *target, const VertrixBlitSurface *source);

enum
{
    VERTRIX_FADE_TABLE_SIZE = 256,
    VERTRIX_FADE_PERCENT_MAX = 100,
    VERTRIX_FADE_CHANNELS = 3
};

/* Original0x47a040: soften the rectangle (x, y, width, height) of a 2 or 4 byte pixel surface in
 * place. The rectangle is first copied to a packed scratch surface (width * height * bytes
 * bytes) with vertrix_surface_blit; every pixel is then rebuilt per channel as
 * tables[percent * 256 + own] + tables[(100 - percent) * 256 + average], where average is the
 * integer mean of the up, down, left and right neighbours inside the rectangle (the pixel itself
 * is not part of the mean; the sums may carry into the next channel field exactly as the
 * original does). tables is the 101 x 256 byte table at 0x558cf0. One-byte surfaces and
 * three-byte surfaces are not changed. A one-pixel rectangle has no neighbour (a division by
 * zero in the original) and is left alone. */
int vertrix_surface_fade(VertrixBlitSurface *surface, uint32_t x, uint32_t y, uint32_t width,
                         uint32_t height, uint32_t percent, const uint8_t *tables,
                         uint8_t *scratch);
#endif
