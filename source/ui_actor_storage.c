#include "ui_actor_storage.h"
#include "block_factory.h"
#include "ui_display_layout.h"

enum
{
    PLACE_BANK = 0x5449fc,
    PLACE_MODE = 0x8e,
    PLACE_FLAG = 0x8f
};

int vertrix_ui_actor_storage_construct(void *storage, size_t size, size_t pair, unsigned side,
                                       int16_t offset_x, int16_t offset_y, uint32_t descriptor)
{
    int16_t x, y;
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE ||
        !vertrix_ui_display_position(pair, side, offset_x, offset_y, &x, &y))
    {
        return 0;
    }
    vertrix_actor_storage_construct(storage, size);
    vertrix_actor_storage_write(storage, size, 8, 2, (uint16_t)x);
    vertrix_actor_storage_write(storage, size, 0xa, 2, (uint16_t)y);
    vertrix_actor_storage_write(storage, size, 0xe, 2, (uint16_t)x);
    vertrix_actor_storage_write(storage, size, 0x16, 2, (uint16_t)y);
    vertrix_actor_storage_write(storage, size, 4, 4, 0x17 + side);
    vertrix_actor_storage_write(storage, size, 0xc0, 4, 10);
    vertrix_actor_storage_write(storage, size, 0xe0, 4, 441 - (uint32_t)pair * 40);
    vertrix_actor_storage_write(storage, size, 0x154, 4, 0x450a10);
    vertrix_actor_storage_write(storage, size, 0x134, 4, 0);
    vertrix_actor_storage_write(storage, size, 0x58, 4, (uint32_t)pair + 1);
    vertrix_actor_storage_write(storage, size, 0x93, 1, 1);
    vertrix_actor_storage_write(storage, size, 0x95, 1, 4);
    vertrix_actor_storage_write(storage, size, 0xb0, 4, 0x546618);
    vertrix_actor_storage_write(storage, size, 0xb4, 4, descriptor);
    return 1;
}

int vertrix_ui_actor_place(void *actor, size_t size, int16_t x, int16_t y, uint32_t frame)
{
    return vertrix_actor_initialize(actor, size, x, y, 0, PLACE_BANK, frame, 0, 0) &&
           vertrix_actor_storage_write(actor, size, PLACE_MODE, 1, 0) &&
           vertrix_actor_storage_write(actor, size, PLACE_FLAG, 1, 1);
}
