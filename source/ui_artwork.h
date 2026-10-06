#ifndef VERTRIX_UI_ARTWORK_H
#define VERTRIX_UI_ARTWORK_H
#include "ui_sprite_bank.h"
typedef struct
{
    VertrixImage images[2];
    uint32_t origin_x[2], origin_y[2];
    unsigned ready;
} VertrixUiArtwork;
/* Original45e490: selected source stencilled solid/hollow with Circle frame9.
 * Owned images represent546618/546634, retaining wrapping descriptor origins.
 * Caller supplies filename/first-source selector and source index4fbfac (default34). */
int vertrix_ui_artwork_load(VertrixVf *archive, const char *name, const uint32_t masks[3],
                            size_t first_source, uint32_t source_index, VertrixUiArtwork *output);
void vertrix_ui_artwork_free(VertrixUiArtwork *artwork);
/* Original45e490 using already loaded5449fc and546538 banks. Borrows inputs;
 * owns the generated images. Uses frame9 of the supplied stencil bank, retaining
 * source origins. No VF reread or hardcoded stencil selection. */
int vertrix_ui_artwork_build(const VertrixUiSpriteBank *bank, const VertrixUiSpriteBank *stencils,
                             uint32_t source_index, VertrixUiArtwork *output);
#endif
