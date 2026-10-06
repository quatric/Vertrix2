#include "piece_actor_layout.h"

int vertrix_piece_actor_parent_construct(void *parent, size_t parent_size)
{
    if (!parent || parent_size < 0x18c)
    {
        return 0;
    }
    vertrix_actor_storage_construct(parent, parent_size);
    vertrix_actor_storage_write(parent, parent_size, 0x158, 4, 0x514774);
    for (size_t i = 0; i < 7; ++i)
    {
        vertrix_actor_storage_write(parent, parent_size, 0x15c + i * 4, 4, 0);
    }
    for (size_t i = 0; i < 5; ++i)
    {
        vertrix_actor_storage_write(parent, parent_size, 0x178 + i * 4, 4, 0);
    }
    return 1;
}

int vertrix_piece_actor_cycle(void *parent, size_t parent_size,
                              VertrixActorStorageMutableResolve resolve, void *context)
{
    uint32_t count;
    if (!vertrix_actor_storage_read(parent, parent_size, 0x188, 4, &count) || count > 7)
    {
        return 0;
    }
    if (count < 2)
    {
        return 1;
    }
    uint32_t handles[7];
    for (size_t i = 0; i < count; ++i)
    {
        vertrix_actor_storage_read(parent, parent_size, 0x15c + i * 4, 4, &handles[i]);
    }
    void *penultimate, *last;
    size_t penultimate_size, last_size;
    if (!resolve || !handles[count - 1] || !handles[0] ||
        !resolve(handles[count - 1], &penultimate, &penultimate_size, context) ||
        !resolve(handles[0], &last, &last_size, context) || !penultimate || !last ||
        penultimate_size < 0x158 || last_size < 0x158)
    {
        return 0;
    }
    for (size_t i = 0; i + 1 < count; ++i)
    {
        vertrix_actor_storage_write(parent, parent_size, 0x15c + i * 4, 4, handles[i + 1]);
    }
    vertrix_actor_storage_write(parent, parent_size, 0x158 + count * 4, 4, handles[0]);
    vertrix_actor_storage_write(penultimate, penultimate_size, 0x154, 4, 0x44c370);
    vertrix_actor_storage_write(last, last_size, 0x154, 4, 0x44c2b0);
    return 1;
}

int vertrix_piece_actor_layout(void *parent, size_t parent_size, uint16_t row_height,
                               VertrixActorStorageMutableResolve resolve, void *context)
{
    if (!parent || parent_size < 0x178 || !resolve)
    {
        return 0;
    }
    for (size_t i = 0; i < 7; ++i)
    {
        uint32_t handle;
        vertrix_actor_storage_read(parent, parent_size, 0x15c + i * 4, 4, &handle);
        if (!handle)
        {
            continue;
        }
        void *actor;
        size_t size;
        if (!resolve(handle, &actor, &size, context) || !actor || size < 0x18)
        {
            return 0;
        }
        uint32_t x, y;
        vertrix_actor_storage_read(parent, parent_size, 0xe, 2, &x);
        vertrix_actor_storage_write(actor, size, 0xe, 2, x);
        vertrix_actor_storage_read(parent, parent_size, 0x16, 2, &y);
        vertrix_actor_storage_write(actor, size, 0x16, 2, y + (uint32_t)i * row_height);
    }
    return 1;
}
