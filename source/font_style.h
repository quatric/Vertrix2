#ifndef VERTRIX_FONT_STYLE_H
#define VERTRIX_FONT_STYLE_H
#include <stdint.h>
typedef struct
{
    uint8_t clip_mode, binary, amount;
    int16_t effect;
    uint8_t stage, flag94, flag95, flag93, mode, screen_override;
    uint32_t cycle;
    uint8_t cycle_flag;
    int16_t clip_left, clip_right, clip_top, clip_bottom;
} VertrixFontStyle;
/* Original440b93..440c46 transfers parent drawing fields and forces8f=1.
 * Null inputs preserve output; in-place transfer is supported. */
int vertrix_font_glyph_style(const VertrixFontStyle *parent, VertrixFontStyle *glyph);
#endif
