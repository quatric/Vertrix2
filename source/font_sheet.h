#ifndef VERTRIX_FONT_SHEET_H
#define VERTRIX_FONT_SHEET_H
#include "image.h"
typedef struct
{
    uint32_t count;
    VertrixImage *glyphs;
} VertrixFontSheet;
/* Original43f200 BMP sheet branch: use configured mask when present in VF,
 * otherwise key from top-left pixel, then slice bordered row-major glyphs.
 * Output must be zero initialized. Owns pixels independently of the archive.
 * Original final color ordering483ed0 and transformed glyphs are separate. */
int vertrix_font_sheet_load(VertrixVf *archive, const char *artwork, const char *mask,
                            uint32_t cell_width, uint32_t cell_height, VertrixFontSheet *output);
void vertrix_font_sheet_free(VertrixFontSheet *sheet);
#endif
