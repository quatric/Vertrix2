#ifndef VERTRIX_OBJECT_ACCESS_H
#define VERTRIX_OBJECT_ACCESS_H
#include "actor_storage.h"
#include "board_cells.h"
/* Field access through a handle resolver. Every helper returns zero (leaving outputs and the
 * object untouched) when the handle does not resolve or the field lies outside the storage. */

static inline int vertrix_object_read(uint32_t handle, VertrixObjectStorage resolve, void *context,
                                      size_t offset, unsigned width, uint32_t *value)
{
    void *storage;
    size_t size;
    if (!resolve(handle, &storage, &size, context))
    {
        return 0;
    }
    return vertrix_actor_storage_read(storage, size, offset, width, value);
}

static inline int vertrix_object_write(uint32_t handle, VertrixObjectStorage resolve, void *context,
                                       size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!resolve(handle, &storage, &size, context))
    {
        return 0;
    }
    return vertrix_actor_storage_write(storage, size, offset, width, value);
}
#endif
