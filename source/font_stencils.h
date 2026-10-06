#ifndef VERTRIX_FONT_STENCILS_H
#define VERTRIX_FONT_STENCILS_H
#include "image.h"
typedef struct
{
    VertrixSpriteFrame frame6, frame9;
} VertrixFontStencils;
/* Original45e119..45e145 loads sprite table index17 into546538; original
 * SpriteFileName.ini index17 is Circle.spr. Resolve that row directly from VF;
 * Font43f110 resolves frames6/9.
 * Owned frames load original binary alpha and final color ordering.
 * Output must be zero initialized. */
int vertrix_font_stencils_load(VertrixVf *archive, const uint32_t masks[3],
                               VertrixFontStencils *output);
void vertrix_font_stencils_free(VertrixFontStencils *stencils);
#endif
