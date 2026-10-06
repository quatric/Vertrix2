#include "ui_border_actor.h"

int vertrix_ui_border_actor_position(size_t index, uint8_t side, int16_t *x, int16_t *y)
{
    static const int16_t left[3] = {143, 133, 153};
    static const int16_t right[3] = {477, 467, 487};
    static const int16_t heights[3] = {129, 147, 147};
    if (index >= 3 || !x || !y)
    {
        return 0;
    }
    *x = side ? right[index] : left[index];
    *y = heights[index];
    return 1;
}

int vertrix_ui_border_actor_construct(void *storage, size_t size, int16_t x, int16_t y,
                                      uint32_t linked_identity)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    vertrix_actor_storage_construct(storage, size);
    const size_t x_offsets[2] = {8, 0xe};
    const size_t y_offsets[2] = {0xa, 0x16};
    for (size_t i = 0; i < 2; ++i)
    {
        vertrix_actor_storage_write(storage, size, x_offsets[i], 2, (uint16_t)x);
        vertrix_actor_storage_write(storage, size, y_offsets[i], 2, (uint16_t)y);
    }
    vertrix_actor_storage_write(storage, size, 0xc, 2, 0);
    vertrix_actor_storage_write(storage, size, 0x1e, 2, 0);
    vertrix_actor_storage_write(storage, size, 0xb0, 4, 0x5466a4);
    vertrix_actor_storage_write(storage, size, 0xb8, 4, 0);
    vertrix_actor_storage_write(storage, size, 0xb4, 4, 0);
    vertrix_actor_storage_write(storage, size, 0x154, 4, 0);
    vertrix_actor_storage_write(storage, size, 0xc0, 4, 12);
    vertrix_actor_storage_write(storage, size, 0x4e, 1, 50);
    vertrix_actor_storage_write(storage, size, 0x93, 1, 1);
    vertrix_actor_storage_write(storage, size, 0x95, 1, 4);
    vertrix_actor_storage_write(storage, size, 0x48, 2, 0);
    vertrix_actor_storage_write(storage, size, 4, 4, linked_identity);
    vertrix_actor_storage_write(storage, size, 0x134, 4, 0);
    return 1;
}
