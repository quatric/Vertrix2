#include "ui_scene_render.h"

int vertrix_ui_scene_frame_render(
    const VertrixObjectList *list, VertrixActorStorageMutableResolve resolve, void *context,
    const VertrixUiSceneFrameOptions *options, const VertrixUiSpriteBank *sprites,
    VertrixSurface *target, VertrixBoardClip cached_clip, const VertrixRenderWeights *weights,
    const VertrixRenderColorBank *colors, const VertrixPaletteTables *tables,
    VertrixRenderPreparation *prepared, size_t draw_budget, size_t *completed)
{
    VertrixSpriteBankBinding binding = {0x5449fc, sprites};
    VertrixSpriteBankMap map = {&binding, 1};
    return vertrix_ui_scene_frame_render_mapped(list, resolve, context, options, &map, target,
                                                cached_clip, weights, colors, tables, prepared,
                                                draw_budget, completed);
}

int vertrix_ui_scene_frame_render_mapped(
    const VertrixObjectList *list, VertrixActorStorageMutableResolve resolve, void *context,
    const VertrixUiSceneFrameOptions *options, const VertrixSpriteBankMap *map,
    VertrixSurface *target, VertrixBoardClip cached_clip, const VertrixRenderWeights *weights,
    const VertrixRenderColorBank *colors, const VertrixPaletteTables *tables,
    VertrixRenderPreparation *prepared, size_t draw_budget, size_t *completed)
{
    return vertrix_ui_scene_frame_render_mapped_random(list, resolve, context, options, map, target,
                                                       cached_clip, weights, colors, tables,
                                                       prepared, draw_budget, completed, NULL);
}

int vertrix_ui_scene_frame_render_mapped_random(
    const VertrixObjectList *list, VertrixActorStorageMutableResolve resolve, void *context,
    const VertrixUiSceneFrameOptions *options, const VertrixSpriteBankMap *map,
    VertrixSurface *target, VertrixBoardClip cached_clip, const VertrixRenderWeights *weights,
    const VertrixRenderColorBank *colors, const VertrixPaletteTables *tables,
    VertrixRenderPreparation *prepared, size_t draw_budget, size_t *completed,
    VertrixRandom *random)
{
    if (completed)
    {
        *completed = 0;
    }
    if (!options ||
        !vertrix_ui_scene_frame_update_random(
            list, resolve, context, options->clear_refresh, options->start_y, options->elapsed,
            options->refresh_words, options->refresh_count, options->resource_one,
            options->resource_other, options->update_budget, random))
    {
        return 0;
    }
    return vertrix_sprite_scene_draw_mapped32(list, resolve, context, map, target, cached_clip,
                                              weights, colors, tables, prepared, draw_budget,
                                              completed);
}
