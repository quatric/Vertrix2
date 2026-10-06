#ifndef VERTRIX_SURFACE_BLEND_H
#define VERTRIX_SURFACE_BLEND_H
#include <stddef.h>
#include <stdint.h>

/* A surface of the original for the blend routines: pixel data and the original address token of
 * that data (pixel pointers of the original are addresses; the scratch globals keep them), the
 * width in pixels (+4), the bytes per pixel (+0xc) and the sub-format byte (+0xd). */
typedef struct VertrixBlendSurface
{
    uint8_t *data;
    size_t size;
    uint32_t address;
    uint32_t width;
    uint8_t bytes_per_pixel;
    uint8_t sub_format;
} VertrixBlendSurface;

/* The scratch globals the original 0x47c930 leaves behind (their addresses in the comments). */
typedef struct VertrixBlendScratch
{
    uint32_t destination;  /* 0x558b9c */
    uint32_t source;       /* 0x558ba0: loaded on entry, stored back on exit */
    uint32_t counter;      /* 0x558ba4 */
    uint32_t skip_target;  /* 0x558ba8 */
    uint32_t skip_source;  /* 0x558bac */
    uint32_t target_width; /* 0x558bb4 */
    uint32_t source_width; /* 0x558bb8 */
    uint8_t target_depth;  /* 0x558bbc */
    uint8_t source_depth;  /* 0x558bbd */
    uint8_t target_format; /* 0x558bbe */
    uint8_t source_format; /* 0x558bbf */
    uint32_t table_first;  /* 0x55f1f0 */
    uint32_t table_second; /* 0x55f1f4 */
} VertrixBlendScratch;

enum
{
    VERTRIX_BLEND_TABLES = 0x558cf0,
    VERTRIX_BLEND_PERCENT_MAX = 100
};

/* Original 0x47c930 (eax = target surface, edx = source surface, ecx = target row, ebx = target
 * column, five stack arguments nearest first: source column, source row, width, height and
 * percent). Only four-byte pixels of both surfaces are blended; otherwise nothing is drawn. The
 * rectangle of width x height pixels at the source column and row is blended onto the target at
 * (column, row): a source pixel whose alpha byte is not zero becomes, per channel,
 * tables[percent * 256 + source channel] + tables[(100 - percent) * 256 + target channel] with
 * the alpha byte 0xff in the red field, the sums (up to 0x1fe) carrying into the neighbouring
 * fields because the fields are ORed exactly as the original does. tables is the 101 x 256 byte
 * table at 0x558cf0 (percent at most 100). Returns 1 when the operation completed (also when
 * nothing is drawn) and 0 when a pixel lies outside the storage of its surface. */
int vertrix_surface_blend(VertrixBlendSurface *target, const VertrixBlendSurface *source,
                          uint32_t row, uint32_t column, const uint32_t arguments[5],
                          const uint8_t *tables, VertrixBlendScratch *scratch);
#endif
