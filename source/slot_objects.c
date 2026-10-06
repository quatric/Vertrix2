#include "slot_objects.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    BYTE_WIDTH = 1,
    SLOTS = 0x1c,
    COLUMNS = 4,
    ACTOR_SIZE = 0x160,
    NO_ANSWER = 0xffffffffu,
    LIST = 0x544a88,
    DELAY_ARGUMENT = 0x16,
    HANDLER = 0x456ca0,
    ROW_STRIDE = 0x10,
    FIELD_KIND = 0x274,
    FIELD_FIRST_BYTES = 0x23c,
    FIELD_SECOND_BYTES = 0x258,
    FIELD_ACTORS = 0x15c,
    QUERY = 0x4178d0,
    NOTIFY = 0x417930,
    ALLOCATE = 0x4ca000,
    CONSTRUCT = 0x43a080,
    INITIALISE = 0x4adf20,
    BIND = 0x4ac8a0,
    SET_DELAY = 0x4ac7d0,
    SET_HANDLER = 0x4ac8f0,
    FRAME_ARGUMENTS = 5,
    LOCAL_FIRST = 0x1c,
    LOCAL_SECOND = 0x18
};

typedef struct Slots
{
    const VertrixFactoryServices *services;
    int ok;
} Slots;

static uint32_t get(Slots *s, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!s->services->resolve(handle, &storage, &size, s->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        s->ok = 0;
    }
    return value;
}

static void put(Slots *s, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!s->services->resolve(handle, &storage, &size, s->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        s->ok = 0;
    }
}

int vertrix_slot_objects_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t frame, uint32_t owner, uint32_t kind)
{
    Slots slots = {services, 1};
    Slots *s = &slots;
    uint32_t i;
    put(s, owner, FIELD_KIND, BYTE_WIDTH, kind);
    for (i = 0; s->ok && i < SLOTS; i++)
    {
        uint32_t row = i / COLUMNS, column = i % COLUMNS, answer, object;
        VertrixCallSite site = {
            QUERY, kind & 0xff, i, frame - LOCAL_FIRST, frame - LOCAL_SECOND, 0, 0, 0, 0,
            0,     {0},         0};
        answer = calls->call(&site, calls->context);
        vertrix_call(calls, NOTIFY, kind & 0xff, i, frame - LOCAL_FIRST, frame - LOCAL_SECOND, 0);
        put(s, owner, FIELD_FIRST_BYTES + i, BYTE_WIDTH, site.out_ebx);
        put(s, owner, FIELD_SECOND_BYTES + i, BYTE_WIDTH, site.out_ecx);
        if (answer != NO_ANSWER)
        {
            uint32_t stack[FRAME_ARGUMENTS] = {LIST, answer, 0, 0, 0};
            object = vertrix_call(calls, ALLOCATE, ACTOR_SIZE, i, column, owner + i, 0);
            if (object != 0)
            {
                object = vertrix_call(calls, CONSTRUCT, object, i, column, owner + i, 0);
            }
            vertrix_calln(calls, INITIALISE, object, 0, 0, 0, stack, FRAME_ARGUMENTS, NULL);
            put(s, object, 0x4e, BYTE_WIDTH, 0);
            put(s, object, 0x93, BYTE_WIDTH, 1);
            put(s, object, 0x52, BYTE_WIDTH, get(s, owner, 0x52, BYTE_WIDTH));
            put(s, object, 0x94, BYTE_WIDTH, get(s, owner, 0x94, BYTE_WIDTH));
            put(s, object, 0x95, BYTE_WIDTH, get(s, owner, 0x95, BYTE_WIDTH));
            vertrix_call(calls, BIND, object, DELAY_ARGUMENT, 0, 0, 0);
            vertrix_call(calls, SET_DELAY, object, DELAY_ARGUMENT, 0, 0, 0);
            put(s, object, 0x15c, BYTE_WIDTH, 1);
            put(s, object, 0x15d, BYTE_WIDTH, 0);
            vertrix_call(calls, SET_HANDLER, object, HANDLER, 0, 0, 0);
            put(s, object, 0x124, DWORD_WIDTH, 1);
            put(s, object, 4, DWORD_WIDTH, get(s, owner, 4, DWORD_WIDTH));
            put(s, object, 0x64, DWORD_WIDTH, row);
            put(s, owner, FIELD_ACTORS + ROW_STRIDE * row + DWORD_WIDTH * column, DWORD_WIDTH,
                object);
        }
    }
    return s->ok;
}
