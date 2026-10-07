#ifndef VERTRIX_SPRITE_SCENE_DRAW_H
#define VERTRIX_SPRITE_SCENE_DRAW_H
#include "object_list.h"
#include "sprite_chain_draw.h"
/* Original fragment 0x4b6240 snapshots handles and signed Y, then draws in ascending Y.
 * Equal Y retains list order. Original sentinel32000 excludes Y>=32000.
 * Supports at most1024 roots and base-class517af4 virtual drawing. Each root
 * uses recovered4ade60 linked drawing and its supplied chain budget.
 * Returns1 on completion,0 on invalid/unsupported state; preceding draws stay.
 * Completed counts root draws, excluding sentinel entries. Resolver preserves
 * list/actor/bank ownership. The Y snapshot survives later actor mutation. */
int vertrix_sprite_scene_draw32(const VertrixObjectList *list, VertrixSpriteActorResolve resolve,
                                void *context, const VertrixUiSpriteBank *sprites,
                                VertrixSurface *target, VertrixBoardClip cached_clip,
                                const VertrixRenderWeights *weights,
                                const VertrixRenderColorBank *colors,
                                const VertrixPaletteTables *tables,
                                VertrixRenderPreparation *prepared, size_t chain_budget,
                                size_t *completed);
/* Same sorted traversal with resource mapping for every root and companion. */
int vertrix_sprite_scene_draw_mapped32(
    const VertrixObjectList *list, VertrixSpriteActorResolve resolve, void *context,
    const VertrixSpriteBankMap *map, VertrixSurface *target, VertrixBoardClip cached_clip,
    const VertrixRenderWeights *weights, const VertrixRenderColorBank *colors,
    const VertrixPaletteTables *tables, VertrixRenderPreparation *prepared, size_t chain_budget,
    size_t *completed);
#endif
