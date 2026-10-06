#ifndef VERTRIX_UI_PLAYER_PREVIEW_DRAW_H
#define VERTRIX_UI_PLAYER_PREVIEW_DRAW_H
#include "sprite_chain_draw.h"
/* Original42b290: draw companion slots first, then border slots, skipping
 * nulls and reading each handle as reached. Parent class514814 is supported;
 * children use recovered base-class direct drawing and next108 chains.
 * Budget bounds total actor draws; earlier draws/bindings persist on failure.
 * The parent has no direct draw in this routine. */
int vertrix_ui_player_preview_draw32(
    const void *parent, size_t parent_size, VertrixSpriteActorResolve resolve, void *context,
    const VertrixSpriteBankMap *map, VertrixSurface *target, VertrixBoardClip cached_clip,
    const VertrixRenderWeights *weights, const VertrixRenderColorBank *colors,
    const VertrixPaletteTables *tables, VertrixRenderPreparation *prepared, size_t budget,
    size_t *completed);
#endif
