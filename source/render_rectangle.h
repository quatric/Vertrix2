#ifndef VERTRIX_RENDER_RECTANGLE_H
#define VERTRIX_RENDER_RECTANGLE_H
#include "palette_tables.h"
#include "render_preparation.h"
#include "surface.h"
/* Original 0x492dc0: destination rectangle operation. half_color is the
 * prepared packed color at 0x54d5ec. Entire backing is checked before writes.
 * Forward row/pixel order, including overlapping rows, is preserved. */
int vertrix_render_rectangle_half32(VertrixSurface *target, uint32_t x, uint32_t y, uint16_t width,
                                    uint16_t height, uint32_t half_color);
/* Original 0x492b90: destination palette conversion. Failure preserves storage. */
int vertrix_render_rectangle_palette32(VertrixSurface *target, uint32_t x, uint32_t y,
                                       uint16_t width, uint16_t height,
                                       const VertrixPaletteTables *tables, int16_t map_shift);
/* Original 0x492cc0: fixed palette indices, destination row selection.
 * Indices may cross rows when their referenced backing remains valid. */
int vertrix_render_rectangle_fixed_palette32(VertrixSurface *target, uint32_t x, uint32_t y,
                                             uint16_t width, uint16_t height,
                                             const VertrixPaletteTables *tables, int16_t map_shift,
                                             const uint16_t channels[3]);
/* Original 0x492e40 averages fixed/destination palette indices, retains row. */
int vertrix_render_rectangle_index_half32(VertrixSurface *target, uint32_t x, uint32_t y,
                                          uint16_t width, uint16_t height,
                                          const VertrixPaletteTables *tables, int16_t map_shift,
                                          const uint16_t channels[3]);
/* Original 0x492f90 blends packed RGB first, then selects palette row/indices. */
int vertrix_render_rectangle_half_palette32(VertrixSurface *target, uint32_t x, uint32_t y,
                                            uint16_t width, uint16_t height,
                                            const VertrixPaletteTables *tables, int16_t map_shift,
                                            uint32_t half_color);
/* Select the five recovered destination operations using original flag rules.
 * Unsupported selection and invalid preparation preserve destination storage. */
int vertrix_render_rectangle32(uint32_t flags, VertrixSurface *target, uint32_t x, uint32_t y,
                               uint16_t width, uint16_t height,
                               const VertrixRenderPreparation *prepared,
                               const VertrixPaletteTables *tables);
#endif
