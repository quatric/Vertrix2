#include "ui_player_preview_update.h"

typedef struct
{
    VertrixActorStorageMutableResolve resolve;
    void *context;
} PreviewResolve;

static int preview_read(uint32_t handle, const void **storage, size_t *size, void *context)
{
    PreviewResolve *preview = context;
    void *actor;
    if (!preview->resolve(handle, &actor, size, preview->context))
    {
        return 0;
    }
    *storage = actor;
    return 1;
}

int vertrix_ui_player_preview_update(void *parent, size_t parent_size,
                                     const VertrixObjectList *linked_list,
                                     VertrixActorStorageMutableResolve resolve, void *context,
                                     const VertrixUiSceneFrameOptions *options,
                                     VertrixRandom *random)
{
    uint32_t class_token;
    if (!parent || parent_size < 0x174 || !resolve || !options ||
        !vertrix_actor_storage_read(parent, parent_size, 0x158, 4, &class_token) ||
        class_token != 0x514814)
    {
        return 0;
    }
    PreviewResolve preview = {resolve, context};
    if (!vertrix_ui_actor_base_frame_update_random(
            parent, parent_size, linked_list, preview_read, &preview, options->clear_refresh,
            options->start_y, options->elapsed, options->refresh_words, options->refresh_count,
            options->resource_one, options->resource_other, options->update_budget, random))
    {
        return 0;
    }
    for (size_t i = 0; i < 6; ++i)
    {
        uint32_t handle;
        vertrix_actor_storage_read(parent, parent_size, 0x15c + i * 4, 4, &handle);
        if (!handle)
        {
            continue;
        }
        void *actor;
        size_t size;
        if (!resolve(handle, &actor, &size, context) ||
            !vertrix_ui_actor_frame_update_random(
                actor, size, linked_list, preview_read, &preview, options->clear_refresh,
                options->start_y, options->elapsed, options->refresh_words, options->refresh_count,
                options->resource_one, options->resource_other, options->update_budget, random))
        {
            return 0;
        }
    }
    return 1;
}
