#ifndef VERTRIX_UI_SPRITE_BANK_H
#define VERTRIX_UI_SPRITE_BANK_H
#include "image.h"
typedef struct
{
    VertrixSpriteFrame *frames;
    size_t count;
} VertrixUiSpriteBank;
/* Read caller-selected original VF sprite and apply45dd52 frame substitutions.
 * Runtime selector and first_source are supplied explicitly, never guessed.
 * Output must be zero initialized. Owns every frame after archive closure. */
int vertrix_ui_sprite_bank_load(VertrixVf *archive, const char *name, const uint32_t masks[3],
                                size_t first_source, VertrixUiSpriteBank *output);
void vertrix_ui_sprite_bank_free(VertrixUiSpriteBank *bank);
#endif
