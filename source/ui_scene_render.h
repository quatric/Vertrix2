#ifndef VERTRIX_UI_SCENE_RENDER_H
#define VERTRIX_UI_SCENE_RENDER_H
#include "sprite_scene_draw.h"
#include "ui_scene_frame.h"
typedef struct
{
    int clear_refresh;
    int16_t start_y;
    uint32_t elapsed;
    uint32_t *refresh_words;
    size_t refresh_count;
    const VertrixFrameResource *resource_one;
    const VertrixFrameResource *resource_other;
    size_t update_budget;
} VertrixUiSceneFrameOptions;
/* Compose original4b6200 virtual updates followed by4b6240 sorted rendering.
 * Uses the recovered update and draw entry points with their documented actor,
 * resource and geometry restrictions. Update failure prevents all drawing;
 * earlier update mutations persist. Draw failure retains completed updates and
 * preceding draws. Caller supplies the original elapsed interval/background.
 * Returns1 on completion,0 on failure; completed counts successful root draws. */
int vertrix_ui_scene_frame_render(
    const VertrixObjectList *list, VertrixActorStorageMutableResolve resolve, void *context,
    const VertrixUiSceneFrameOptions *options, const VertrixUiSpriteBank *sprites,
    VertrixSurface *target, VertrixBoardClip cached_clip, const VertrixRenderWeights *weights,
    const VertrixRenderColorBank *colors, const VertrixPaletteTables *tables,
    VertrixRenderPreparation *prepared, size_t draw_budget, size_t *completed);
/* Update first, then select drawing banks from each actor's resulting resource
 * token. Supports recovered bank-switching handlers with explicit live banks. */
int vertrix_ui_scene_frame_render_mapped(
    const VertrixObjectList *list, VertrixActorStorageMutableResolve resolve, void *context,
    const VertrixUiSceneFrameOptions *options, const VertrixSpriteBankMap *map,
    VertrixSurface *target, VertrixBoardClip cached_clip, const VertrixRenderWeights *weights,
    const VertrixRenderColorBank *colors, const VertrixPaletteTables *tables,
    VertrixRenderPreparation *prepared, size_t draw_budget, size_t *completed);
/* Same update/draw path with shared RNG for the recovered border callbacks. */
int vertrix_ui_scene_frame_render_mapped_random(
    const VertrixObjectList *list, VertrixActorStorageMutableResolve resolve, void *context,
    const VertrixUiSceneFrameOptions *options, const VertrixSpriteBankMap *map,
    VertrixSurface *target, VertrixBoardClip cached_clip, const VertrixRenderWeights *weights,
    const VertrixRenderColorBank *colors, const VertrixPaletteTables *tables,
    VertrixRenderPreparation *prepared, size_t draw_budget, size_t *completed,
    VertrixRandom *random);
#endif
