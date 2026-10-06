#ifndef VERTRIX_FONT_BINDING_H
#define VERTRIX_FONT_BINDING_H
#include "font_bank.h"
#include "font_map.h"
#include <stddef.h>
/* Borrow resolved bank image. Missing glyph succeeds with NULL; invalid index
 * preserves output. Caller keeps the bank alive while using the image. */
int vertrix_font_bank_glyph(const VertrixFontBank *bank, const VertrixFontMap *map, uint8_t glyph,
                            const VertrixImage **output);
/* Compose original glyph mapping and440610 measurement with real VF images.
 * Invalid resources/text preserve output dimensions. */
int vertrix_font_bank_measure(const VertrixFontBank *bank, const VertrixFontMap *map,
                              const uint8_t *text, size_t storage, uint8_t mode,
                              uint8_t screen_unscaled, uint8_t screen_mode, uint32_t *width,
                              uint32_t *height);
#endif
