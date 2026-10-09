#include "native_memory.h"

#include "actor_storage.h"

static const uint32_t GLOBAL_STORE = 0xf0000000u;

uint32_t vertrix_native_get(VertrixNativeMemory *memory, uint32_t base, size_t offset,
                            unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (memory->services->resolve(base, &storage, &size, memory->services->context) &&
        vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        return value;
    }
    if (memory->globals == NULL)
    {
        memory->ok = 0;
        return 0;
    }
    value = memory->globals->read(base + (uint32_t)offset, memory->globals->context);
    return width >= 4 ? value : value & ((1u << (8 * width)) - 1);
}

void vertrix_native_put(VertrixNativeMemory *memory, uint32_t base, size_t offset, unsigned width,
                        uint32_t value)
{
    void *storage;
    size_t size;
    uint32_t stack[1] = {width};
    if (memory->services->resolve(base, &storage, &size, memory->services->context) &&
        vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        return;
    }
    if (memory->globals == NULL)
    {
        memory->ok = 0;
        return;
    }
    vertrix_calln(memory->calls, GLOBAL_STORE, base + (uint32_t)offset, value, 0, 0, stack, 1,
                  NULL);
}
