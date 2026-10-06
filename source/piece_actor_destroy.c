#include "piece_actor_destroy.h"

int vertrix_actor_base_destroy(void *actor, size_t size, uint32_t actor_handle, uint32_t flags,
                               VertrixPlayerActorDestroy release, void *context)
{
    if (!actor || size < VERTRIX_ACTOR_BASE_SIZE || (flags & 4) || ((flags & 2) && !release))
    {
        return 0;
    }
    vertrix_actor_storage_write(actor, size, 0x158, 4, 0x517af4);
    return !(flags & 2) || release(actor_handle, context);
}

int vertrix_piece_actor_destroy(void *parent, size_t size, uint32_t parent_handle, uint32_t flags,
                                VertrixPlayerActorDestroy destroy_child, void *child_context,
                                VertrixPlayerActorDestroy release, void *release_context)
{
    if (!parent || size < 0x18c || (flags & 4) || ((flags & 2) && !release))
    {
        return 0;
    }
    uint32_t handles[7];
    int any = 0;
    for (size_t i = 0; i < 7; ++i)
    {
        vertrix_actor_storage_read(parent, size, 0x15c + i * 4, 4, &handles[i]);
        any |= handles[i] != 0;
    }
    if (any && !destroy_child)
    {
        return 0;
    }
    vertrix_actor_storage_write(parent, size, 0x158, 4, 0x514774);
    for (size_t i = 0; i < 7; ++i)
    {
        if (handles[i] && !destroy_child(handles[i], child_context))
        {
            return 0;
        }
    }
    return vertrix_actor_base_destroy(parent, size, parent_handle, flags, release, release_context);
}

int vertrix_piece_actor_forward_slot2(void *parent, size_t size, uint32_t arg,
                                      VertrixActorVtable vtable_of, void *vtable_context,
                                      VertrixActorSlot2 call, void *context)
{
    if (!parent || size < 0x178 || !vtable_of || !call)
    {
        return 0;
    }
    uint32_t handles[7], vtables[7];
    for (size_t i = 0; i < 7; ++i)
    {
        vertrix_actor_storage_read(parent, size, 0x15c + i * 4, 4, &handles[i]);
        if (handles[i] && !vtable_of(handles[i], &vtables[i], vtable_context))
        {
            return 0;
        }
    }
    for (size_t i = 0; i < 7; ++i)
    {
        if (handles[i] && !call(handles[i], vtables[i], arg, context))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_piece_actor_self_slot2(const void *parent, size_t size, uint32_t handle, uint32_t arg,
                                   VertrixActorSlot2 call, void *context)
{
    uint32_t vtable;
    return call && vertrix_actor_storage_read(parent, size, 0x158, 4, &vtable) &&
           call(handle, vtable, arg, context);
}
