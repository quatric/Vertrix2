#ifndef VERTRIX_FONT_MEASURE_H
#define VERTRIX_FONT_MEASURE_H
#include "render_geometry.h"
#include <stddef.h>
/* Return1 for a resolved glyph,0 for an absent glyph,-1 for invalid resources. */
typedef int (*VertrixGlyphDimensions)(uint8_t glyph, VertrixResourceDimensions *dimensions,
                                      void *context);
/* Original 0x440610. Caller supplies original font space dimensions and glyph
 * descriptors. NUL must occur within storage. Failure preserves outputs. */
int vertrix_font_measure(const uint8_t *text, size_t storage, VertrixResourceDimensions space,
                         uint8_t mode, uint8_t screen_unscaled, uint8_t screen_mode,
                         VertrixGlyphDimensions glyph, void *context, uint32_t *width,
                         uint32_t *height);
#endif
