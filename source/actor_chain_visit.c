#include "actor_chain_visit.h"
#include "actor_storage.h"

int vertrix_actor_lookup_image(void *actor, size_t size, VertrixImageLookup lookup, void *context)
{
    uint32_t bank, index;
    if (!lookup || !vertrix_actor_storage_read(actor, size, 0xb0, 4, &bank) ||
        !vertrix_actor_storage_read(actor, size, 0xb8, 4, &index))
    {
        return 0;
    }
    if (bank == 0)
    {
        return 1;
    }
    return vertrix_actor_storage_write(actor, size, 0xb4, 4, lookup(bank, index, context));
}

int vertrix_actor_chain_paint(uint32_t actor_handle, const void *actor, size_t size, uint32_t arg,
                              uint32_t *global_arg, VertrixActorGate gate, VertrixActorPaint paint,
                              void *context)
{
    uint32_t value;
    if (!global_arg || !gate || !paint ||
        !vertrix_actor_storage_read(actor, size, 0x144, 4, &value))
    {
        return 0;
    }
    *global_arg = arg;
    if (gate(actor_handle, value, context))
    {
        paint(actor_handle, context);
    }
    return 1;
}
