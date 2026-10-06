#include "ui_player_preview_draw.h"

typedef struct
{
    VertrixSpriteActorResolve resolve;
    void *context;
} PreviewDrawResolve;

static int preview_draw_resolve(uint32_t handle, void **storage, size_t *size, void *context)
{
    PreviewDrawResolve *preview = context;
    uint32_t class_token;
    return preview->resolve(handle, storage, size, preview->context) &&
           vertrix_actor_storage_read(*storage, *size, 0x158, 4, &class_token) &&
           class_token == 0x517af4;
}

int vertrix_ui_player_preview_draw32(
    const void *parent, size_t parent_size, VertrixSpriteActorResolve resolve, void *context,
    const VertrixSpriteBankMap *map, VertrixSurface *target, VertrixBoardClip cached_clip,
    const VertrixRenderWeights *weights, const VertrixRenderColorBank *colors,
    const VertrixPaletteTables *tables, VertrixRenderPreparation *prepared, size_t budget,
    size_t *completed)
{
    if (completed)
    {
        *completed = 0;
    }
    uint32_t class_token;
    if (!parent || parent_size < 0x174 || !resolve ||
        !vertrix_actor_storage_read(parent, parent_size, 0x158, 4, &class_token) ||
        class_token != 0x514814)
    {
        return 0;
    }
    size_t total = 0;
    PreviewDrawResolve preview = {resolve, context};
    for (size_t i = 0; i < 6; ++i)
    {
        uint32_t handle;
        vertrix_actor_storage_read(parent, parent_size, 0x15c + i * 4, 4, &handle);
        if (!handle)
        {
            continue;
        }
        size_t drawn = 0;
        int success = vertrix_sprite_chain_draw_mapped32(handle, preview_draw_resolve, &preview,
                                                         map, target, cached_clip, weights, colors,
                                                         tables, prepared, budget - total, &drawn);
        total += drawn;
        if (completed)
        {
            *completed = total;
        }
        if (!success)
        {
            return 0;
        }
    }
    return 1;
}
