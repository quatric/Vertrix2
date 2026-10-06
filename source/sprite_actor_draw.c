#include "sprite_actor_draw.h"

int vertrix_sprite_actor_draw_mapped32(void *storage, size_t size, const VertrixSpriteBankMap *map,
                                       VertrixSurface *target, VertrixBoardClip cached_clip,
                                       const VertrixRenderWeights *weights,
                                       const VertrixRenderColorBank *colors,
                                       const VertrixPaletteTables *tables,
                                       VertrixRenderPreparation *prepared)
{
    uint32_t resource;
    if (!map || !map->bindings || map->count > SIZE_MAX / sizeof(*map->bindings) ||
        !vertrix_actor_storage_read(storage, size, 0xb0, 4, &resource))
    {
        return -1;
    }
    for (size_t i = 0; i < map->count; ++i)
    {
        if (map->bindings[i].resource_token == resource)
        {
            return vertrix_sprite_actor_draw_resource32(
                storage, size, resource, map->bindings[i].sprites, target, cached_clip, weights,
                colors, tables, prepared);
        }
    }
    return -1;
}

int vertrix_sprite_actor_draw32(void *storage, size_t size, const VertrixUiSpriteBank *sprites,
                                VertrixSurface *target, VertrixBoardClip cached_clip,
                                const VertrixRenderWeights *weights,
                                const VertrixRenderColorBank *colors,
                                const VertrixPaletteTables *tables,
                                VertrixRenderPreparation *prepared)
{
    return vertrix_sprite_actor_draw_resource32(storage, size, 0x5449fc, sprites, target,
                                                cached_clip, weights, colors, tables, prepared);
}

int vertrix_sprite_actor_draw_resource32(void *storage, size_t size, uint32_t resource_token,
                                         const VertrixUiSpriteBank *sprites, VertrixSurface *target,
                                         VertrixBoardClip cached_clip,
                                         const VertrixRenderWeights *weights,
                                         const VertrixRenderColorBank *colors,
                                         const VertrixPaletteTables *tables,
                                         VertrixRenderPreparation *prepared)
{
    uint32_t initialized, coordinates;
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !target || !prepared ||
        !vertrix_actor_storage_read(storage, size, 0x13c, 4, &initialized) || !initialized ||
        !vertrix_actor_storage_read(storage, size, 0x144, 4, &coordinates) || coordinates != 1)
    {
        return -1;
    }
    const VertrixImage *image;
    uint32_t origin_x, origin_y;
    if (!vertrix_sprite_actor_image_resource(storage, size, resource_token, sprites, &image,
                                             &origin_x, &origin_y))
    {
        return -1;
    }
    uint32_t frame;
    vertrix_actor_storage_read(storage, size, 0xb4, 4, &frame);
    return vertrix_actor_render_draw32(storage, size, &sprites->frames[frame], target, cached_clip,
                                       weights, colors, tables, prepared);
}
