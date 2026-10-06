#ifndef VERTRIX_UI_BORDER_ARTWORK_H
#define VERTRIX_UI_BORDER_ARTWORK_H
#include "ui_sprite_bank.h"
/* Original45e530: solid stencil of selected interface frame (4fbf74 initial20)
 * with selected Circle bank frame9. Owns one generated frame for5466a4, retaining
 * wrapping origins. Explicit descriptor format; zero output, unchanged on failure.
 * Free the owned result with vertrix_sprite_free. Inputs remain borrowed. */
int vertrix_ui_border_artwork_build(const VertrixUiSpriteBank *interface,
                                    const VertrixUiSpriteBank *stencils, uint32_t source_index,
                                    uint32_t descriptor_format, VertrixSpriteFrame *output);
#endif
