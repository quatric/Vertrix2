#include "exception_chain.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    FETCH = 0x4e0f8b,
    DESCRIBE = 0x4e0a95,
    PREPARE = 0x4e0eaf,
    UNWIND = 0x4e0ec7,
    REWRITE = 0x4e0b7c,
    FINISH = 0x4e0b9e,
    LOCAL_VALUE = 0x10,
    LOCAL_HEAD = 0x14,
    LOCAL_FIELD = 0x18,
    LOCAL_RESULT = 4,
    RECORD_FIELD = 8,
    RECORD_NEXT_FIELD = 0xc,
    DESCRIPTOR_FIELD = 4
};

typedef struct Chain
{
    const VertrixFactoryServices *services;
    int ok;
} Chain;

static uint32_t get(Chain *c, uint32_t handle, size_t offset)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!c->services->resolve(handle, &storage, &size, c->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, &value))
    {
        c->ok = 0;
    }
    return value;
}

static void put(Chain *c, uint32_t handle, size_t offset, uint32_t value)
{
    void *storage;
    size_t size;
    if (!c->services->resolve(handle, &storage, &size, c->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, value))
    {
        c->ok = 0;
    }
}

int vertrix_exception_chain_step(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t entry_esp, uint32_t eax, uint32_t edx, uint32_t ebx,
                                 uint32_t ecx, uint32_t *result)
{
    Chain chain = {services, 1};
    Chain *c = &chain;
    uint32_t frame = entry_esp - VERTRIX_EXCEPTION_FRAME, head, field, descriptor, prepared;
    put(c, frame, LOCAL_VALUE, vertrix_call(calls, FETCH, eax, edx, ebx, ecx, 0));
    head = get(c, VERTRIX_EXCEPTION_HEAD, 0);
    put(c, frame, LOCAL_HEAD, head);
    field = get(c, head, RECORD_FIELD);
    put(c, frame, LOCAL_FIELD, field);
    descriptor =
        vertrix_call(calls, DESCRIBE, field, get(c, head, RECORD_NEXT_FIELD), ebx, head, 0);
    ebx = get(c, descriptor, DESCRIPTOR_FIELD) - 1;
    prepared = vertrix_call(calls, PREPARE, frame + LOCAL_VALUE, head, ebx, head, 0);
    vertrix_call(calls, UNWIND, prepared, frame + LOCAL_VALUE, ebx, head, 0);
    vertrix_call(calls, REWRITE, frame, frame + LOCAL_VALUE, ebx, head, 0);
    vertrix_call(calls, FINISH, frame, frame + LOCAL_VALUE, ebx, head, 0);
    *result = get(c, frame, LOCAL_RESULT);
    put(c, head, RECORD_NEXT_FIELD, *result);
    return c->ok;
}
