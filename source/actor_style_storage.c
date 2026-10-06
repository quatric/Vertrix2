#include "actor_style_storage.h"

int vertrix_actor_storage_style(void *storage, size_t size, const uint8_t record[12])
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !record)
    {
        return 0;
    }
    vertrix_actor_storage_write(storage, size, 0x4e, 1, record[2]);
    vertrix_actor_storage_write(storage, size, 0x48, 2,
                                (uint32_t)record[4] | ((uint32_t)record[5] << 8));
    vertrix_actor_storage_write(storage, size, 0x52, 1, record[6]);
    vertrix_actor_storage_write(storage, size, 0x94, 1, record[7]);
    vertrix_actor_storage_write(storage, size, 0x95, 1, record[1]);
    vertrix_actor_storage_write(storage, size, 0x93, 1, record[0]);
    vertrix_actor_storage_write(storage, size, 0x80, 4,
                                (uint32_t)record[10] | ((uint32_t)record[11] << 8));
    vertrix_actor_storage_write(storage, size, 0x8c, 1, record[8]);
    return 1;
}
