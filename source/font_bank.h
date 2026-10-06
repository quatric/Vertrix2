#ifndef VERTRIX_FONT_BANK_H
#define VERTRIX_FONT_BANK_H
#include "image.h"
typedef struct
{
    VertrixImage glyphs[548];
    uint32_t origin_x[548], origin_y[548];
    unsigned ready;
} VertrixFontBank;
/* Original43eab0 loading order, including source-mutating outline transforms.
 * Uses verified original VF filenames and configured graphics color masks.
 * Output must be zero initialized. Owns all548 glyphs and descriptor origins. */
int vertrix_font_bank_load(VertrixVf *archive, const uint32_t masks[3], VertrixFontBank *output);
void vertrix_font_bank_free(VertrixFontBank *bank);
#endif
