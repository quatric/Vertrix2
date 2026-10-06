#include "sprite_actor_storage.h"
#include "actor_style_storage.h"

int vertrix_sprite_actor_storage_construct(void *storage, size_t size, int16_t x, int16_t y,
                                           uint32_t frame, const void *configuration,
                                           size_t configuration_size, uint32_t index,
                                           uint32_t sentinel)
{
    size_t selected = index;
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !configuration ||
        selected > (SIZE_MAX - 0x5cc) / 4 || selected > SIZE_MAX / 12)
    {
        return 0;
    }
    size_t availability = 0x5cc + (size_t)index * 4;
    size_t style = (size_t)index * 12;
    uint32_t enabled;
    if (!vertrix_actor_storage_read(configuration, configuration_size, availability, 4, &enabled) ||
        enabled != 1 || style > configuration_size || configuration_size - style < 12)
    {
        return 0;
    }
    vertrix_actor_storage_construct(storage, size);
    vertrix_actor_storage_write(storage, size, 8, 2, (uint16_t)x);
    vertrix_actor_storage_write(storage, size, 0xa, 2, (uint16_t)y);
    vertrix_actor_storage_write(storage, size, 0xe, 2, (uint16_t)x);
    vertrix_actor_storage_write(storage, size, 0x16, 2, (uint16_t)y);
    vertrix_actor_storage_write(storage, size, 0xb0, 4, 0x5449fc);
    vertrix_actor_storage_write(storage, size, 0xb8, 4, frame);
    vertrix_actor_storage_write(storage, size, 0x8e, 1, 0);
    vertrix_actor_storage_write(storage, size, 0x8f, 1, 1);
    vertrix_actor_storage_style(storage, size, (const uint8_t *)configuration + style);
    if (index == sentinel)
    {
        vertrix_actor_storage_write(storage, size, 0x110, 1, 1);
    }
    return 1;
}
