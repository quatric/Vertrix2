#ifndef VERTRIX_RENDER_ROW_H
#define VERTRIX_RENDER_ROW_H
#include "render_pixel.h"
#include <stddef.h>
/* Original 0x492280: binary-alpha row with recovered 32-bit pixel dispatch.
 * Source and destination are offsets in one bounded backing. Staging retains
 * forward aliasing behavior; invalid kernels/backing preserve all bytes.
 * Prepared palette/weight views must remain independent of destination. */
int vertrix_render_binary_row32(uint8_t *storage, size_t size, size_t source_offset,
                                size_t destination_offset, uint16_t width, uint32_t flags,
                                const VertrixRenderPreparation *prepared,
                                const VertrixPaletteTables *tables);
/* Original 0x492550: sample current source, then advance by table byte*4.
 * Width must be positive; this original loop has no zero-width entry guard. Advance
 * storage must be independent of destination. Final advance is not sampled. */
int vertrix_render_sample_binary_row32(uint8_t *storage, size_t size, size_t source_offset,
                                       size_t destination_offset, uint16_t width, uint32_t flags,
                                       const VertrixRenderPreparation *prepared,
                                       const VertrixPaletteTables *tables, const uint8_t *advances,
                                       size_t advance_count);
/* Original 0x492710: apply every sampled pixel without alpha skipping.
 * Same positive-width, bounded-backing and independent-table requirements. */
int vertrix_render_sample_row32(uint8_t *storage, size_t size, size_t source_offset,
                                size_t destination_offset, uint16_t width, uint32_t flags,
                                const VertrixRenderPreparation *prepared,
                                const VertrixPaletteTables *tables, const uint8_t *advances,
                                size_t advance_count);
/* Original 0x4928f0 composed with sampled row 0x492550/0x492710.
 * Draw current row, then advance source by vertical byte*source_stride.
 * Horizontal table restarts each row; final vertical advance is not sampled.
 * Width/height must be positive and tables independent of destination. */
int vertrix_render_sample32(uint8_t *storage, size_t size, size_t source_offset,
                            size_t destination_offset, uint32_t source_stride,
                            uint32_t destination_stride, uint16_t width, uint16_t height,
                            uint32_t flags, const VertrixRenderPreparation *prepared,
                            const VertrixPaletteTables *tables, const uint8_t *horizontal,
                            size_t horizontal_count, const uint8_t *vertical, size_t vertical_count,
                            int binary);
/* Original 0x492400: native-size row, invokes every pixel regardless of alpha.
 * Zero width is a no-op. Shared backing retains forward aliasing behavior. */
int vertrix_render_row32(uint8_t *storage, size_t size, size_t source_offset,
                         size_t destination_offset, uint16_t width, uint32_t flags,
                         const VertrixRenderPreparation *prepared,
                         const VertrixPaletteTables *tables);
/* Original 0x492880 with native-size opaque/binary rows. Strides include
 * complete row spacing. Empty images succeed without pixel access. */
int vertrix_render_image32(uint8_t *storage, size_t size, size_t source_offset,
                           size_t destination_offset, uint32_t source_stride,
                           uint32_t destination_stride, uint16_t width, uint16_t height,
                           uint32_t flags, const VertrixRenderPreparation *prepared,
                           const VertrixPaletteTables *tables, int binary);
/* Original 0x4ab380 shared-backing premultiplied-alpha image traversal.
 * Alpha0 skips,255 copies, otherwise adds source channels to inverse-alpha
 * weighted destination channels. Forward aliasing and failure preservation. */
int vertrix_render_alpha_image32(uint8_t *storage, size_t size, size_t source_offset,
                                 size_t destination_offset, uint32_t source_stride,
                                 uint32_t destination_stride, uint16_t width, uint16_t height);
typedef struct
{
    uint32_t flags;
    uint32_t source_stride;
    uint32_t destination_stride;
    uint16_t width;
    uint16_t height;
    uint8_t scale;
    uint8_t binary_flag;
    uint8_t transform_flag;
    uint32_t alpha_override;
} VertrixRenderImageRequest;
/* Compose original operation selection with recovered 32-bit native/scaled
 * image paths. Preparation, clipping and pixel gate are caller-resolved.
 * General transform paths reject while preserving backing. */
int vertrix_render_bound32(uint8_t *storage, size_t size, size_t source_offset,
                           size_t destination_offset, const VertrixRenderImageRequest *request,
                           const VertrixRenderPreparation *prepared,
                           const VertrixPaletteTables *tables, const uint8_t *horizontal,
                           size_t horizontal_count, const uint8_t *vertical, size_t vertical_count);
/* Recovered pixel gate, flags, conditional preparation and bound drawing.
 * Geometry, actor clipping and destination format4 are caller-resolved.
 * Preparation is published only after successful drawing. Disabled pixel
 * drawing succeeds without changes. Prepared/table storage must not alias pixels. */
int vertrix_render_prepared32(uint8_t *storage, size_t size, size_t source_offset,
                              size_t destination_offset, const VertrixRenderImageRequest *request,
                              uint32_t pixel_resource, VertrixRenderFlagState state, uint8_t cycle,
                              const VertrixRenderWeights *weights,
                              const VertrixRenderColorBank *bank,
                              const VertrixPaletteTables *tables,
                              VertrixRenderPreparation *prepared, const uint8_t *horizontal,
                              size_t horizontal_count, const uint8_t *vertical,
                              size_t vertical_count);
#endif
