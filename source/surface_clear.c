#include "surface_clear.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    MAKE = 0x4872c0,
    FILL = 0x478f50
};

static int access(const VertrixFactoryServices *services, size_t offset, uint32_t *value, int write)
{
    void *storage;
    size_t size;
    if (!services->resolve(VERTRIX_SURFACE_PAIR, &storage, &size, services->context))
    {
        return 0;
    }
    return write ? vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, *value)
                 : vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, value);
}

int vertrix_surface_clear_second(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t ebx, uint32_t ecx, uint32_t *result)
{
    uint32_t surface = 0;
    if (!access(services, VERTRIX_SURFACE_SECOND, &surface, 0))
    {
        return 0;
    }
    *result = vertrix_call(calls, FILL, surface, 0, ebx, ecx, 0);
    return 1;
}

int vertrix_surface_pair_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t argument, uint32_t edx, uint32_t ebx)
{
    uint32_t first = vertrix_call(calls, MAKE, argument, edx, ebx, argument, 0), second;
    int ok = access(services, 0, &first, 1);
    vertrix_call(calls, FILL, first, 0, ebx, argument, 0);
    second = vertrix_call(calls, MAKE, argument, 0, ebx, argument, 0);
    ok = access(services, VERTRIX_SURFACE_SECOND, &second, 1) && ok;
    vertrix_call(calls, FILL, second, 0, ebx, argument, 0);
    return ok;
}
