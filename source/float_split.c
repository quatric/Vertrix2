#include "float_split.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    SPLIT = 0x4e509c,
    LOCAL_VALUE = 8,
    LOCAL_INTEGER = 0x10,
    HIGH_OFFSET = 4,
    SHIFT = 32
};

static int access_dword(const VertrixFactoryServices *services, uint32_t handle, size_t offset,
                        uint32_t *value, int write)
{
    void *storage;
    size_t size;
    if (!services->resolve(handle, &storage, &size, services->context))
    {
        return 0;
    }
    return write ? vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, *value)
                 : vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, value);
}

int vertrix_float_split(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t low, uint32_t high, uint32_t destination,
                        uint32_t ecx, uint64_t *result)
{
    uint32_t base = frame - VERTRIX_FLOAT_SPLIT_FRAME, integer_low = 0, integer_high = 0,
             low_out = 0, high_out = 0;
    int ok = access_dword(services, base, VERTRIX_FLOAT_SPLIT_FRAME - LOCAL_VALUE, &low, 1) &&
             access_dword(services, base, VERTRIX_FLOAT_SPLIT_FRAME - LOCAL_VALUE + HIGH_OFFSET,
                          &high, 1);
    vertrix_call(calls, SPLIT, frame - LOCAL_VALUE, frame - LOCAL_INTEGER, destination, ecx, 0);
    ok = ok && access_dword(services, base, 0, &integer_low, 0) &&
         access_dword(services, base, HIGH_OFFSET, &integer_high, 0) &&
         access_dword(services, destination, 0, &integer_low, 1) &&
         access_dword(services, destination, HIGH_OFFSET, &integer_high, 1) &&
         access_dword(services, base, VERTRIX_FLOAT_SPLIT_FRAME - LOCAL_VALUE, &low_out, 0) &&
         access_dword(services, base, VERTRIX_FLOAT_SPLIT_FRAME - LOCAL_VALUE + HIGH_OFFSET,
                      &high_out, 0);
    *result = ((uint64_t)high_out << SHIFT) | low_out;
    return ok;
}
