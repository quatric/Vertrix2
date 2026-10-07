#ifndef VERTRIX_SURFACE_H
#define VERTRIX_SURFACE_H
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    uint8_t *data;
    size_t size;
    uint32_t width;
    uint32_t height;
    uint32_t stride;
    uint8_t bytes_per_pixel;
} VertrixSurface;

/* Original 0x478eb0: low-32-bit byte offset, independent of host pointers. */
uint32_t vertrix_surface_offset(uint32_t stride, uint8_t bytes_per_pixel, int32_t x, int32_t y);
/* Original 0x478f10/0x478ed0: little-endian values for 1/2/4-byte pixels.
 * Bounds/storage validation precedes access; invalid operations preserve output. */
int vertrix_surface_read(const VertrixSurface *surface, uint32_t x, uint32_t y, uint32_t *value);
int vertrix_surface_write(VertrixSurface *surface, uint32_t x, uint32_t y, uint32_t value);
/* Original opaque 32-bit row traversal 0x4ab310. Validates the entire rectangle
 * before copying. Forward pixel order is retained, including overlapping views. */
int vertrix_surface_copy32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                           VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                           uint16_t width, uint16_t height);
/* Original fragment 0x4ab380: alpha zero skips, 255 copies, partial alpha adds
 * premultiplied source channels to table-scaled destination channels. */
uint32_t vertrix_surface_alpha_pixel(uint32_t source, uint32_t destination);
int vertrix_surface_alpha32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                            VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                            uint16_t width, uint16_t height);
/* Original 0x4ab2a0: alpha zero skips; every nonzero alpha copies unchanged. */
int vertrix_surface_binary32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                             VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                             uint16_t width, uint16_t height);
/* Original 0x492710 with direct-copy kernel: sample first, then advance by
 * the next table byte. Table generation and vertical sampling are separate. */
int vertrix_surface_sample_row32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                                 VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                                 const uint8_t *advances, size_t advance_count, uint16_t width);
/* Original 0x4928f0 plus 0x492710: sample current row, then advance source
 * by its vertical table byte; horizontal table restarts for every row. */
int vertrix_surface_sample32(const VertrixSurface *source, uint32_t source_x, uint32_t source_y,
                             VertrixSurface *target, uint32_t target_x, uint32_t target_y,
                             const uint8_t *horizontal, size_t horizontal_count,
                             const uint8_t *vertical, size_t vertical_count, uint16_t width,
                             uint16_t height);
/* Original 0x492550: skip zero-alpha samples and copy every nonzero alpha. */
int vertrix_surface_sample_binary_row32(const VertrixSurface *source, uint32_t source_x,
                                        uint32_t source_y, VertrixSurface *target,
                                        uint32_t target_x, uint32_t target_y,
                                        const uint8_t *advances, size_t advance_count,
                                        uint16_t width);
int vertrix_surface_sample_binary32(const VertrixSurface *source, uint32_t source_x,
                                    uint32_t source_y, VertrixSurface *target, uint32_t target_x,
                                    uint32_t target_y, const uint8_t *horizontal,
                                    size_t horizontal_count, const uint8_t *vertical,
                                    size_t vertical_count, uint16_t width, uint16_t height);
/* Supplied-table sampling with recovered 32-bit amount-50 effects 1,3..8.
 * binary selects original zero-alpha skipping before the pixel kernel. */
int vertrix_surface_sample_effect32(const VertrixSurface *source, uint32_t source_x,
                                    uint32_t source_y, VertrixSurface *target, uint32_t target_x,
                                    uint32_t target_y, const uint8_t *horizontal,
                                    size_t horizontal_count, const uint8_t *vertical,
                                    size_t vertical_count, uint16_t width, uint16_t height,
                                    uint8_t effect, int binary);
/* Original sampled traversal with weighted kernel 0x4902a0, percentages 0..100. */
int vertrix_surface_sample_weighted32(const VertrixSurface *source, uint32_t source_x,
                                      uint32_t source_y, VertrixSurface *target, uint32_t target_x,
                                      uint32_t target_y, const uint8_t *horizontal,
                                      size_t horizontal_count, const uint8_t *vertical,
                                      size_t vertical_count, uint16_t width, uint16_t height,
                                      uint8_t amount, int binary);
#endif
