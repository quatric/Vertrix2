#include "piece_actor_destroy.h"

static uint32_t cleanup_free(const VertrixCalls *runtime, uint32_t actor, uint32_t class_token,
                             uint32_t ebx, uint32_t ecx)
{
    uint32_t allocation = vertrix_call(runtime, 0x4ccb9f, actor, class_token, ebx, ecx, 0);
    vertrix_call(runtime, 0x4ca040, allocation, 0, ebx, ecx, 0);
    return actor;
}

uint32_t vertrix_actor_base_destroy_full(void *actor, size_t size, uint32_t actor_handle,
                                         uint32_t flags, VertrixPlayerActorDestroy release,
                                         void *context, const VertrixCalls *runtime,
                                         uint32_t caller_ebx, uint32_t caller_ecx)
{
    (void)caller_ecx;
    if (!actor || size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    if (flags & 4)
    {
        return runtime && runtime->call
                   ? cleanup_free(runtime, actor_handle, 0x517b10, caller_ebx, actor_handle)
                   : 0;
    }
    return vertrix_actor_base_destroy(actor, size, actor_handle, flags, release, context)
               ? actor_handle
               : 0;
}

uint32_t vertrix_piece_actor_destroy_full(void *parent, size_t size, uint32_t parent_handle,
                                          uint32_t flags, VertrixPlayerActorDestroy destroy_child,
                                          void *child_context, VertrixPlayerActorDestroy release,
                                          void *release_context, const VertrixCalls *runtime,
                                          uint32_t caller_ebx, uint32_t caller_ecx)
{
    if (!parent || size < 0x18c)
    {
        return 0;
    }
    if (flags & 4)
    {
        return runtime && runtime->call
                   ? cleanup_free(runtime, parent_handle, 0x514790, caller_ebx, caller_ecx)
                   : 0;
    }
    if ((flags & 2) && !release)
    {
        return 0;
    }
    if (!destroy_child)
    {
        for (size_t i = 0; i < 7; ++i)
        {
            uint32_t handle;
            vertrix_actor_storage_read(parent, size, 0x15c + i * 4, 4, &handle);
            if (handle)
            {
                return 0;
            }
        }
    }
    vertrix_actor_storage_write(parent, size, 0x158, 4, 0x514774);
    for (size_t i = 0; i < 7; ++i)
    {
        uint32_t handle;
        vertrix_actor_storage_read(parent, size, 0x15c + i * 4, 4, &handle);
        if (handle && !destroy_child(handle, child_context))
        {
            return 0;
        }
    }
    return vertrix_actor_base_destroy_full(parent, size, parent_handle, flags, release,
                                           release_context, runtime, caller_ebx, caller_ecx);
}

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
    for (size_t i = 0; i < 7; ++i)
    {
        uint32_t handle;
        uint32_t vtable;
        vertrix_actor_storage_read(parent, size, 0x15c + i * 4, 4, &handle);
        if (handle &&
            (!vtable_of(handle, &vtable, vtable_context) || !call(handle, vtable, arg, context)))
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
