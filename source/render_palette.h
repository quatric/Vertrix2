#ifndef VERTRIX_RENDER_PALETTE_H
#define VERTRIX_RENDER_PALETTE_H

#include <stddef.h>
#include <stdint.h>

/* Original fragment 0x48d740/0x48d7f0: convenience palette conversion. The original54b800 lookup
 * contains262144 dwords; each low byte selects a channel map from
 * original54cdc8. This convenience API uses256-byte rows. Inputs borrow tables.
 * fixed_channels selects original54d5dc/de/e0 instead of the lookup's high
 * three bytes. Invalid tables/indices preserve output. */
int vertrix_render_palette_pixel(uint32_t source, const uint32_t *lookup, size_t lookup_count,
                                 const uint8_t *maps, size_t maps_size, int fixed_channels,
                                 const uint16_t channels[3], uint32_t *output);
/* Explicit regular pointer-table layout. Original475419 supplies201 rows
 * separated by101 bytes. Fixed word indices retain cross-row byte addressing
 * when within maps_size, just as the executable does. */
/* Original variants 0x48d740, 0x48d7f0: complete callable palette kernels with explicit
 * channel-map layout, verified in tools/verify_render_palette.py. */
int vertrix_render_palette_pixel_layout(uint32_t source, const uint32_t *lookup,
                                        size_t lookup_count, const uint8_t *maps, size_t maps_size,
                                        size_t map_stride, size_t map_count, int fixed_channels,
                                        const uint16_t channels[3], uint32_t *output);
/* Original 0x48dba0 half blend: average source/destination lookup channel indices
 * before resolving them through the SOURCE's selected channel map. */
int vertrix_render_palette_half_pixel(uint32_t source, uint32_t destination, const uint32_t *lookup,
                                      size_t lookup_count, const uint8_t *maps, size_t maps_size,
                                      size_t map_stride, size_t map_count, uint32_t *output);

/* Original 0x490340: weight lookup channel indices through two256-byte tables,
 * add their values, then resolve through the source map row. */
int vertrix_render_palette_weighted_pixel(uint32_t source, uint32_t destination,
                                          const uint32_t *lookup, size_t lookup_count,
                                          const uint8_t *maps, size_t maps_size, size_t map_stride,
                                          size_t map_count, const uint8_t source_weight[256],
                                          const uint8_t destination_weight[256], uint32_t *output);
#endif
