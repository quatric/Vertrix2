#ifndef VERTRIX_SPRITE_ACTOR_DRAW_H
#define VERTRIX_SPRITE_ACTOR_DRAW_H
#include "actor_render_draw.h"
#include "sprite_actor_image.h"
typedef struct
{
    uint32_t resource_token;
    const VertrixUiSpriteBank *sprites;
} VertrixSpriteBankBinding;
typedef struct
{
    const VertrixSpriteBankBinding *bindings;
    size_t count;
} VertrixSpriteBankMap;
/* Original4ac8a0 binding followed by4af8c0 draw for direct5449fc VF banks.
 * Requires initialized actor geometry13c and direct-coordinate mode144=1.
 * Binding writes the local frame ID to actorb4 even when later drawing rejects
 * or clips, matching original binding-before-draw order. Keep the bank live.
 * Returns1 dispatched,0 clipped/empty,-1 invalid/unsupported. Drawing failure
 * preserves target/preparation; invalid binding preserves the actor too. */
int vertrix_sprite_actor_draw32(void *storage, size_t size, const VertrixUiSpriteBank *sprites,
                                VertrixSurface *target, VertrixBoardClip cached_clip,
                                const VertrixRenderWeights *weights,
                                const VertrixRenderColorBank *colors,
                                const VertrixPaletteTables *tables,
                                VertrixRenderPreparation *prepared);
/* Resolve any explicitly mapped direct bank, then use the same original draw
 * path and mutation/failure ordering. Geometry restrictions remain unchanged. */
int vertrix_sprite_actor_draw_resource32(void *storage, size_t size, uint32_t resource_token,
                                         const VertrixUiSpriteBank *sprites, VertrixSurface *target,
                                         VertrixBoardClip cached_clip,
                                         const VertrixRenderWeights *weights,
                                         const VertrixRenderColorBank *colors,
                                         const VertrixPaletteTables *tables,
                                         VertrixRenderPreparation *prepared);
/* Read actorb0 and select the first matching explicit bank binding. Missing
 * mappings reject before binding; bank ownership stays with the caller. */
int vertrix_sprite_actor_draw_mapped32(void *storage, size_t size, const VertrixSpriteBankMap *map,
                                       VertrixSurface *target, VertrixBoardClip cached_clip,
                                       const VertrixRenderWeights *weights,
                                       const VertrixRenderColorBank *colors,
                                       const VertrixPaletteTables *tables,
                                       VertrixRenderPreparation *prepared);
#endif
