#include "actor_lookup.h"

typedef struct
{
    VertrixActorStorageResolve resolve;
    void *context;
} ActorLookup;

static int actor_identity(uint32_t handle, uint32_t *identity, void *context)
{
    ActorLookup *lookup = context;
    const void *storage;
    size_t size;
    return lookup->resolve(handle, &storage, &size, lookup->context) &&
           vertrix_actor_storage_read(storage, size, 0, 4, identity);
}

int vertrix_actor_linked_values(const void *storage, size_t size, const VertrixObjectList *list,
                                VertrixActorStorageResolve resolve, void *context, int *present,
                                uint32_t *value, uint32_t *state)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !resolve || !present || !value || !state)
    {
        return 0;
    }
    uint32_t identity, handle, next_value = 0, next_state = 0;
    vertrix_actor_storage_read(storage, size, 4, 4, &identity);
    ActorLookup lookup = {resolve, context};
    if (!vertrix_object_list_find(list, identity, actor_identity, &lookup, &handle))
    {
        return 0;
    }
    if (handle)
    {
        const void *linked;
        size_t linked_size;
        if (!resolve(handle, &linked, &linked_size, context) ||
            !vertrix_actor_storage_read(linked, linked_size, 0x58, 4, &next_value) ||
            !vertrix_actor_storage_read(linked, linked_size, 0x64, 4, &next_state))
        {
            return 0;
        }
    }
    *present = handle != 0;
    *value = next_value;
    *state = next_state;
    return 1;
}
