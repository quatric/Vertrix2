#include "font_style.h"

int vertrix_font_glyph_style(const VertrixFontStyle *parent, VertrixFontStyle *glyph)
{
    if (!parent || !glyph)
    {
        return 0;
    }
    *glyph = *parent;
    glyph->binary = 1;
    return 1;
}
