#include "ui_companion_storage.h"
#include "ui_display_layout.h"

int vertrix_ui_companion_storage_construct(void *storage, size_t size, size_t pair, unsigned side,
                                           int16_t offset_x, int16_t offset_y, uint32_t frame,
                                           const void *configuration, size_t configuration_size,
                                           uint32_t sentinel, uint32_t parameter_one,
                                           uint32_t parameter_other)
{
    int16_t x, y;
    if (!vertrix_ui_display_position(pair, side, offset_x, offset_y, &x, &y) ||
        !vertrix_sprite_actor_storage_construct(storage, size, x, y, frame, configuration,
                                                configuration_size, 64 + (uint32_t)pair, sentinel))
    {
        return 0;
    }
    vertrix_actor_storage_write(storage, size, 4, 4, 0x17 + side);
    vertrix_actor_storage_write(storage, size, 0x124, 4, 0);
    vertrix_actor_storage_write(storage, size, 0x128, 2, (uint16_t)x);
    vertrix_actor_storage_write(storage, size, 0x12a, 2, (uint16_t)y);
    vertrix_actor_storage_write(storage, size, 0x12c, 4, parameter_one);
    vertrix_actor_storage_write(storage, size, 0x130, 4, parameter_other);
    vertrix_actor_storage_write(storage, size, 0x134, 4, 0);
    vertrix_actor_storage_write(storage, size, 0x58, 4, (uint32_t)pair + 1);
    vertrix_actor_storage_write(storage, size, 0xc0, 4, 10);
    vertrix_actor_storage_write(storage, size, 0xe0, 4, 500);
    vertrix_actor_storage_write(storage, size, 0x154, 4, 0x450860);
    return 1;
}
