#include "scene_lookups.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    LOOKUP = 0x4b5eb0,
    LOOKUP_LIST = 0x54671c,
    LOOKUP_FIRST_KIND = 0x15,
    LOOKUP_SECOND_KIND = 0x16,
    LOOKUP_USE = 0x4123d0,
    MARKER_LIST = 0x546744,
    MARKER_KIND = 0x190,
    MARKER_FIELD = 0x94c
};

uint32_t vertrix_scene_lookup_pair(const VertrixCalls *calls, uint32_t object, uint32_t ebx)
{
    uint32_t found = vertrix_call(calls, LOOKUP, LOOKUP_LIST, LOOKUP_FIRST_KIND, ebx, object, 0);
    if (found != 0)
    {
        ebx = found;
        vertrix_call(calls, LOOKUP_USE, object, 0, ebx, object, 0);
    }
    found = vertrix_call(calls, LOOKUP, LOOKUP_LIST, LOOKUP_SECOND_KIND, ebx, object, 0);
    if (found == 0)
    {
        return 0;
    }
    return vertrix_call(calls, LOOKUP_USE, object, 0, found, object, 0);
}

uint32_t vertrix_scene_clear_marker(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t ebx,
                                    uint32_t ecx)
{
    uint32_t found = vertrix_call(calls, LOOKUP, MARKER_LIST, MARKER_KIND, ebx, ecx, 0);
    void *storage;
    size_t size;
    if (found == 0)
    {
        return 0;
    }
    if (!services->resolve(found, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, MARKER_FIELD, DWORD_WIDTH, 0))
    {
        return 0;
    }
    return found;
}
