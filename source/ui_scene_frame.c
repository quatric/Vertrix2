#include "ui_scene_frame.h"

typedef struct
{
    VertrixActorStorageMutableResolve resolve;
    void *context;
} SceneResolve;

static int scene_read(uint32_t handle, const void **storage, size_t *size, void *context)
{
    SceneResolve *scene = context;
    void *actor;
    if (!scene->resolve(handle, &actor, size, scene->context))
    {
        return 0;
    }
    *storage = actor;
    return 1;
}

int vertrix_ui_scene_frame_update(const VertrixObjectList *list,
                                  VertrixActorStorageMutableResolve resolve, void *context,
                                  int clear_refresh, int16_t start_y, uint32_t elapsed,
                                  uint32_t *refresh_words, size_t refresh_count,
                                  const VertrixFrameResource *resource_one,
                                  const VertrixFrameResource *resource_other, size_t budget)
{
    return vertrix_ui_scene_frame_update_random(list, resolve, context, clear_refresh, start_y,
                                                elapsed, refresh_words, refresh_count, resource_one,
                                                resource_other, budget, NULL);
}

int vertrix_ui_scene_frame_update_random(const VertrixObjectList *list,
                                         VertrixActorStorageMutableResolve resolve, void *context,
                                         int clear_refresh, int16_t start_y, uint32_t elapsed,
                                         uint32_t *refresh_words, size_t refresh_count,
                                         const VertrixFrameResource *resource_one,
                                         const VertrixFrameResource *resource_other, size_t budget,
                                         VertrixRandom *random)
{
    if (!list || !resolve || list->count > list->capacity ||
        list->capacity > SIZE_MAX / sizeof(*list->items) || (list->count && !list->items))
    {
        return 0;
    }
    SceneResolve scene = {resolve, context};
    size_t count = list->count;
    for (size_t i = 0; i < count; i++)
    {
        void *storage;
        size_t size;
        if (!list->items[i] || !resolve(list->items[i], &storage, &size, context) ||
            !vertrix_ui_actor_frame_update_random(
                storage, size, list, scene_read, &scene, clear_refresh, start_y, elapsed,
                refresh_words, refresh_count, resource_one, resource_other, budget, random))
        {
            return 0;
        }
    }
    return 1;
}
