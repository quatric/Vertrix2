#include "actor_list_idle.h"
#include "actor_fields.h"
#include "actor_storage.h"

enum
{
    OWNER_OFFSET = 0x14c
};

int vertrix_actor_list_all_idle(const uint32_t *handles, uint32_t count,
                                VertrixObjectStorage resolve, void *context, uint32_t *idle)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        void *storage;
        size_t size;
        uint32_t handler;
        if (!resolve(handles[i], &storage, &size, context) ||
            !vertrix_actor_get_handler(storage, size, &handler))
        {
            return 0;
        }
        if (handler != 0)
        {
            *idle = 0;
            return 1;
        }
    }
    *idle = 1;
    return 1;
}

int vertrix_actor_list_idle_except(const uint32_t *handles, uint32_t count, uint32_t owner,
                                   VertrixObjectStorage resolve, void *context, uint32_t *idle)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        void *storage;
        size_t size;
        uint32_t actor_owner;
        uint32_t handler;
        if (!resolve(handles[i], &storage, &size, context) ||
            !vertrix_actor_storage_read(storage, size, OWNER_OFFSET, 4, &actor_owner))
        {
            return 0;
        }
        if (actor_owner == owner)
        {
            continue;
        }
        if (!vertrix_actor_get_handler(storage, size, &handler))
        {
            return 0;
        }
        if (handler != 0)
        {
            *idle = 0;
            return 1;
        }
    }
    *idle = 1;
    return 1;
}
