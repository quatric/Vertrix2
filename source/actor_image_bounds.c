#include "actor_image_bounds.h"
#include "render_geometry.h"

static int16_t bounds_word(uint32_t value)
{
    value &= 65535;
    return (int16_t)(value < 32768 ? (int32_t)value : (int32_t)value - 65536);
}

int vertrix_actor_image_bounds(const void *storage, size_t size, const VertrixImage *image,
                               uint32_t origin_x, uint32_t origin_y, uint8_t screen_unscaled,
                               uint8_t screen_mode, VertrixActorImageBounds *output)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !image || !output)
    {
        return 0;
    }
    uint32_t mode, override, x, y;
    vertrix_actor_storage_read(storage, size, 0x44, 1, &mode);
    vertrix_actor_storage_read(storage, size, 0x91, 1, &override);
    vertrix_actor_storage_read(storage, size, 0xe, 2, &x);
    vertrix_actor_storage_read(storage, size, 0x16, 2, &y);
    if (override)
    {
        mode = screen_unscaled ? 16 : screen_mode;
    }
    VertrixActorImageBounds bounds;
    if (!vertrix_resource_bounds((uint16_t)image->width, (uint16_t)image->height,
                                 bounds_word(origin_x), bounds_word(origin_y), (uint8_t)mode,
                                 bounds_word(x), bounds_word(y), &bounds.x, &bounds.y,
                                 &bounds.width, &bounds.height))
    {
        return 0;
    }
    *output = bounds;
    return 1;
}
