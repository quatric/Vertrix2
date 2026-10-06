#ifndef VERTRIX_FONT_DRAW_H
#define VERTRIX_FONT_DRAW_H
#include "font_run.h"
#include "surface.h"
/* Original4ae6fa..4ae740 subtracts low-word descriptor origins from anchors. */
int vertrix_font_glyph_position(const VertrixFontBank *bank, uint16_t descriptor, int16_t x,
                                int16_t y, int16_t *draw_x, int16_t *draw_y);
/* Compose recovered origin positioning, full-target clipping and binary-alpha
 * sprite drawing for unscaled original font glyphs in a zero-origin viewport.
 * Returns1 drawn,0 clipped out,-1 invalid input. Target pixels use bank order. */
int vertrix_font_draw_glyph(const VertrixFontBank *bank, const VertrixFontPlacement *placement,
                            VertrixSurface *target);
typedef struct
{
    int16_t x, y;
    uint16_t width, height;
} VertrixFontGlyphBounds;
/* Original4aed56..4aee28 scales descriptor origins by measured/source size. */
int vertrix_font_glyph_bounds(const VertrixFontBank *bank, const VertrixFontPlacement *placement,
                              uint8_t scale, VertrixFontGlyphBounds *output);
/* Basic scaled binary font pixels, scale0..16, zero-origin viewport. Parent
 * effects, custom clipping and viewport offsets are composed separately. */
int vertrix_font_draw_glyph_scaled(const VertrixFontBank *bank,
                                   const VertrixFontPlacement *placement, uint8_t scale,
                                   VertrixSurface *target);
/* Complete440490 traversal composed with recovered glyph rendering.
 * Supports unscaled fonts in a zero-origin32-bit viewport. Validate text,
 * target and all visible source rectangles before drawing. Caller keeps bank
 * storage separate from target pixels. Outputs change only on success. */
int vertrix_font_draw_text(const VertrixFontBank *bank, const VertrixFontMap *map,
                           const uint8_t *text, size_t storage, uint32_t x, int16_t y,
                           VertrixSurface *target, size_t *drawn, uint32_t *final_x);
/* Basic scaled440a20 text composition with original VF glyphs. Parent effects,
 * custom clipping and nonzero viewport offsets remain separate. */
int vertrix_font_draw_text_scaled(const VertrixFontBank *bank, const VertrixFontMap *map,
                                  const uint8_t *text, size_t storage, int16_t x, int16_t y,
                                  uint8_t mode, uint8_t screen_override, uint8_t screen_unscaled,
                                  uint8_t screen_mode, VertrixSurface *target, size_t *drawn,
                                  int16_t *final_x);
#endif
