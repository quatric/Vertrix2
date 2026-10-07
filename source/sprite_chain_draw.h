#ifndef VERTRIX_SPRITE_CHAIN_DRAW_H
#define VERTRIX_SPRITE_CHAIN_DRAW_H
#include "sprite_actor_draw.h"
typedef int (*VertrixSpriteActorResolve)(uint32_t handle, void **storage, size_t *size,
                                         void *context);
/* Original fragment 0x4ade60: bind and draw current actor, then read its next108 handle.
 * Resolved actors use the direct5449fc bank and initialized direct geometry.
 * Resolver preserves actor/bank ownership. Budget bounds malformed cycles.
 * Returns1 on chain end,0 on failure/budget exhaustion. Completed counts actors
 * whose draw dispatched or clipped. Earlier bindings/draws persist on failure.
 * A null head succeeds without resolving or accessing destination state. */
int vertrix_sprite_chain_draw32(uint32_t head, VertrixSpriteActorResolve resolve, void *context,
                                const VertrixUiSpriteBank *sprites, VertrixSurface *target,
                                VertrixBoardClip cached_clip, const VertrixRenderWeights *weights,
                                const VertrixRenderColorBank *colors,
                                const VertrixPaletteTables *tables,
                                VertrixRenderPreparation *prepared, size_t budget,
                                size_t *completed);
/* Select each reached actor's resource bank from the live map. Mutation and
 * failure ordering match draw32; the map must remain valid throughout. */
int vertrix_sprite_chain_draw_mapped32(uint32_t head, VertrixSpriteActorResolve resolve,
                                       void *context, const VertrixSpriteBankMap *map,
                                       VertrixSurface *target, VertrixBoardClip cached_clip,
                                       const VertrixRenderWeights *weights,
                                       const VertrixRenderColorBank *colors,
                                       const VertrixPaletteTables *tables,
                                       VertrixRenderPreparation *prepared, size_t budget,
                                       size_t *completed);
#endif
