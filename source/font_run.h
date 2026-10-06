#ifndef VERTRIX_FONT_RUN_H
#define VERTRIX_FONT_RUN_H
#include "font_binding.h"
typedef struct
{
    uint16_t descriptor;
    int16_t x, y;
    uint8_t glyph;
} VertrixFontPlacement;
/* Original440490 unscaled text traversal before each sprite virtual draw.
 * Spaces advance full32-bit position; glyph width adds only to low16 bits,
 * then the trailing pixel increments the full position. Missing glyphs skip.
 * Validate complete text/resources/capacity before changing any output. */
int vertrix_font_run(const VertrixFontBank *bank, const VertrixFontMap *map, const uint8_t *text,
                     size_t storage, uint32_t x, int16_t y, VertrixFontPlacement *placements,
                     size_t capacity, size_t *count, uint32_t *final_x);
/* Original440a20 styled traversal uses measured widths and signed-word x.
 * Screen override selects16 when unscaled, otherwise screen_mode. Rendering
 * effects and style transfer to each temporary sprite are separate. */
int vertrix_font_run_scaled(const VertrixFontBank *bank, const VertrixFontMap *map,
                            const uint8_t *text, size_t storage, int16_t x, int16_t y, uint8_t mode,
                            uint8_t screen_override, uint8_t screen_unscaled, uint8_t screen_mode,
                            VertrixFontPlacement *placements, size_t capacity, size_t *count,
                            int16_t *final_x);
#endif
