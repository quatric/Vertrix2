#include "message_dispatch.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    HANDLER = 0x4d0c84,
    NOTIFY = 0x4cb820,
    HANDLER_BASE = 0xbc00,
    MESSAGE_FIRST_GROUP = 0x2b,
    MESSAGE_LAST_GROUP = 0x2f,
    MESSAGE_SELECT = 0x39,
    MESSAGE_CONTROL_FIRST = 0x114,
    MESSAGE_CONTROL_SECOND = 0x115,
    MESSAGE_LAST = 0x210,
    MESSAGE_RECORD = 0x4e,
    MESSAGE_KEY = 0x111,
    MESSAGE_RANGE_FIRST = 0x132,
    MESSAGE_RANGE_LAST = 0x138,
    RECORD_KEY = 0xbc4e0000u,
    KEY_RESULT = 0xbd110000u,
    RANGE_HANDLER = 0xbc19,
    RECORD_FIELD = 8,
    LOCAL_FLAG = 0xc,
    LOCAL_ECX = 0x10,
    LOCAL_RANGE_EBX = 4,
    LOCAL_RANGE_INDEX = 8,
    HIGH_SHIFT = 16
};

typedef struct Dispatch
{
    const VertrixFactoryServices *services;
    int ok;
} Dispatch;

static uint32_t get(Dispatch *d, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!d->services->resolve(handle, &storage, &size, d->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        d->ok = 0;
    }
    return value;
}

static void put(Dispatch *d, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!d->services->resolve(handle, &storage, &size, d->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        d->ok = 0;
    }
}

int vertrix_message_dispatch(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             uint32_t entry_esp, uint32_t object, uint32_t message, uint32_t ebx,
                             uint32_t ecx, uint32_t flag_pointer, uint32_t *result)
{
    Dispatch dispatch = {services, 1};
    Dispatch *d = &dispatch;
    uint32_t frame = entry_esp - VERTRIX_DISPATCH_FRAME;
    *result = 0;
    if ((message >= MESSAGE_FIRST_GROUP && message <= MESSAGE_LAST_GROUP) ||
        message == MESSAGE_SELECT || message == MESSAGE_CONTROL_FIRST ||
        message == MESSAGE_CONTROL_SECOND || message == MESSAGE_LAST)
    {
        *result =
            vertrix_call(calls, HANDLER, object, message + HANDLER_BASE, ebx, ecx, flag_pointer);
    }
    else if (message == MESSAGE_RECORD)
    {
        uint32_t record = get(d, ecx, RECORD_FIELD, WORD_WIDTH);
        put(d, frame, LOCAL_FLAG, DWORD_WIDTH, flag_pointer);
        put(d, frame, LOCAL_ECX, DWORD_WIDTH, ecx);
        *result =
            vertrix_call(calls, NOTIFY, object, 0, RECORD_KEY | record, frame + LOCAL_FLAG, 0);
    }
    else if (message == MESSAGE_KEY)
    {
        uint32_t high = (ebx >> HIGH_SHIFT) & 0xffff;
        if (vertrix_call(calls, NOTIFY, object, 0, KEY_RESULT | high, 0, 0) != 0)
        {
            if (flag_pointer != 0)
            {
                put(d, flag_pointer, 0, DWORD_WIDTH, 1);
            }
            *result = 1;
        }
    }
    else if (message >= MESSAGE_RANGE_FIRST && message <= MESSAGE_RANGE_LAST)
    {
        uint32_t answer;
        put(d, frame, LOCAL_RANGE_EBX, DWORD_WIDTH, ebx);
        put(d, frame, LOCAL_RANGE_INDEX, DWORD_WIDTH, message - MESSAGE_RANGE_FIRST);
        answer = vertrix_call(calls, HANDLER, object, RANGE_HANDLER, 0, frame, flag_pointer);
        if (get(d, flag_pointer, 0, DWORD_WIDTH) != 0)
        {
            *result = answer;
        }
    }
    return d->ok;
}
