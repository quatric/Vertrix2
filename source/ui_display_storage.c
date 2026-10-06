#include "ui_display_storage.h"
#include "ui_actor_storage.h"
#include "ui_actor_update.h"

int vertrix_ui_display_storage_construct(void *storage, size_t size, size_t pair, unsigned side,
                                         int16_t offset_x, int16_t offset_y,
                                         const VertrixUiDisplayAssets *assets)
{
    if (!assets || !assets->artwork.ready)
    {
        return 0;
    }
    return vertrix_ui_actor_storage_construct(storage, size, pair, side, offset_x, offset_y,
                                              assets->descriptors[0]);
}

int vertrix_ui_display_storage_update(void *storage, size_t size, int linked_present,
                                      uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                                      uint32_t elapsed, const VertrixUiDisplayAssets *assets)
{
    if (!assets || !assets->artwork.ready)
    {
        return 0;
    }
    return vertrix_ui_actor_storage_update(storage, size, linked_present, linked_value,
                                           linked_state, start_y, elapsed, &assets->resources[0],
                                           &assets->resources[1], 1);
}

int vertrix_ui_display_storage_image(const void *storage, size_t size,
                                     const VertrixUiDisplayAssets *assets,
                                     const VertrixImage **image, uint32_t *origin_x,
                                     uint32_t *origin_y)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !assets || !assets->artwork.ready || !image ||
        !origin_x || !origin_y)
    {
        return 0;
    }
    uint32_t resource, descriptor;
    vertrix_actor_storage_read(storage, size, 0xb0, 4, &resource);
    vertrix_actor_storage_read(storage, size, 0xb4, 4, &descriptor);
    for (size_t i = 0; i < 2; i++)
    {
        if (resource == (i == 0 ? 0x546618u : 0x546634u) && descriptor == assets->descriptors[i])
        {
            *image = &assets->artwork.images[i];
            *origin_x = assets->artwork.origin_x[i];
            *origin_y = assets->artwork.origin_y[i];
            return 1;
        }
    }
    return 0;
}
