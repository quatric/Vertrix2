#include "sprite_chain_draw.h"

int vertrix_sprite_chain_draw32(uint32_t head, VertrixSpriteActorResolve resolve, void *context,
                                const VertrixUiSpriteBank *sprites, VertrixSurface *target,
                                VertrixBoardClip cached_clip, const VertrixRenderWeights *weights,
                                const VertrixRenderColorBank *colors,
                                const VertrixPaletteTables *tables,
                                VertrixRenderPreparation *prepared, size_t budget,
                                size_t *completed)
{
    VertrixSpriteBankBinding binding = {0x5449fc, sprites};
    VertrixSpriteBankMap map = {&binding, 1};
    return vertrix_sprite_chain_draw_mapped32(head, resolve, context, &map, target, cached_clip,
                                              weights, colors, tables, prepared, budget, completed);
}

int vertrix_sprite_chain_draw_mapped32(uint32_t head, VertrixSpriteActorResolve resolve,
                                       void *context, const VertrixSpriteBankMap *map,
                                       VertrixSurface *target, VertrixBoardClip cached_clip,
                                       const VertrixRenderWeights *weights,
                                       const VertrixRenderColorBank *colors,
                                       const VertrixPaletteTables *tables,
                                       VertrixRenderPreparation *prepared, size_t budget,
                                       size_t *completed)
{
    size_t count = 0;
    if (completed)
    {
        *completed = 0;
    }
    while (head)
    {
        void *storage;
        size_t size;
        if (!resolve || count >= budget || !resolve(head, &storage, &size, context) ||
            vertrix_sprite_actor_draw_mapped32(storage, size, map, target, cached_clip, weights,
                                               colors, tables, prepared) < 0)
        {
            return 0;
        }
        ++count;
        if (completed)
        {
            *completed = count;
        }
        vertrix_actor_storage_read(storage, size, 0x108, 4, &head);
    }
    return 1;
}
