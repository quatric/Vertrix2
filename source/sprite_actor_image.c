#include "sprite_actor_image.h"

int vertrix_sprite_actor_image(void *storage, size_t size, const VertrixUiSpriteBank *bank,
                               const VertrixImage **image, uint32_t *origin_x, uint32_t *origin_y)
{
    return vertrix_sprite_actor_image_resource(storage, size, 0x5449fc, bank, image, origin_x,
                                               origin_y);
}

int vertrix_sprite_actor_image_resource(void *storage, size_t size, uint32_t resource_token,
                                        const VertrixUiSpriteBank *bank, const VertrixImage **image,
                                        uint32_t *origin_x, uint32_t *origin_y)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !bank || !bank->frames || !image ||
        !origin_x || !origin_y || !resource_token)
    {
        return 0;
    }
    uint32_t resource, frame;
    vertrix_actor_storage_read(storage, size, 0xb0, 4, &resource);
    vertrix_actor_storage_read(storage, size, 0xb8, 4, &frame);
    if (resource != resource_token || frame >= bank->count || !bank->frames[frame].image.rgba)
    {
        return 0;
    }
    vertrix_actor_storage_write(storage, size, 0xb4, 4, frame);
    *image = &bank->frames[frame].image;
    *origin_x = bank->frames[frame].metadata[3];
    *origin_y = bank->frames[frame].metadata[4];
    return 1;
}
