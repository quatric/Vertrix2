#include "sprite_scene_draw.h"

typedef struct
{
    VertrixSpriteActorResolve resolve;
    void *context;
    int first;
} SceneDrawResolve;

static int scene_draw_resolve(uint32_t handle, void **storage, size_t *size, void *context)
{
    SceneDrawResolve *scene = context;
    if (!scene->resolve(handle, storage, size, scene->context))
    {
        return 0;
    }
    if (scene->first)
    {
        uint32_t type;
        scene->first = 0;
        if (!vertrix_actor_storage_read(*storage, *size, 0x158, 4, &type) || type != 0x517af4)
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_sprite_scene_draw32(const VertrixObjectList *list, VertrixSpriteActorResolve resolve,
                                void *context, const VertrixUiSpriteBank *sprites,
                                VertrixSurface *target, VertrixBoardClip cached_clip,
                                const VertrixRenderWeights *weights,
                                const VertrixRenderColorBank *colors,
                                const VertrixPaletteTables *tables,
                                VertrixRenderPreparation *prepared, size_t chain_budget,
                                size_t *completed)
{
    VertrixSpriteBankBinding binding = {0x5449fc, sprites};
    VertrixSpriteBankMap map = {&binding, 1};
    return vertrix_sprite_scene_draw_mapped32(list, resolve, context, &map, target, cached_clip,
                                              weights, colors, tables, prepared, chain_budget,
                                              completed);
}

int vertrix_sprite_scene_draw_mapped32(
    const VertrixObjectList *list, VertrixSpriteActorResolve resolve, void *context,
    const VertrixSpriteBankMap *map, VertrixSurface *target, VertrixBoardClip cached_clip,
    const VertrixRenderWeights *weights, const VertrixRenderColorBank *colors,
    const VertrixPaletteTables *tables, VertrixRenderPreparation *prepared, size_t chain_budget,
    size_t *completed)
{
    if (completed)
    {
        *completed = 0;
    }
    if (!list || list->count > list->capacity || list->count > 1024 ||
        list->capacity > SIZE_MAX / sizeof(*list->items) ||
        (list->count && (!list->items || !resolve)))
    {
        return 0;
    }
    uint32_t handles[1024];
    int16_t positions[1024];
    size_t count = list->count;
    for (size_t i = 0; i < count; ++i)
    {
        void *storage;
        size_t size;
        uint32_t y;
        handles[i] = list->items[i];
        if (!handles[i] || !resolve(handles[i], &storage, &size, context) ||
            !vertrix_actor_storage_read(storage, size, 0x16, 2, &y))
        {
            return 0;
        }
        positions[i] = (int16_t)(y < 32768 ? (int32_t)y : (int32_t)y - 65536);
    }
    size_t drawn = 0;
    for (;;)
    {
        int16_t lowest = 32000;
        for (size_t i = 0; i < count; ++i)
        {
            if (positions[i] < lowest)
            {
                lowest = positions[i];
            }
        }
        if (lowest == 32000)
        {
            return 1;
        }
        for (size_t i = 0; i < count; ++i)
        {
            if (positions[i] == lowest)
            {
                SceneDrawResolve scene = {resolve, context, 1};
                if (!vertrix_sprite_chain_draw_mapped32(handles[i], scene_draw_resolve, &scene, map,
                                                        target, cached_clip, weights, colors,
                                                        tables, prepared, chain_budget, NULL))
                {
                    return 0;
                }
                positions[i] = 32000;
                ++drawn;
                if (completed)
                {
                    *completed = drawn;
                }
            }
        }
    }
}
