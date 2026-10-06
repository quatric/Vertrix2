#include "marker_actor.h"

#include "actor_storage.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    MARKER_SIZE = 0x15c,
    MARKER_ALLOCATE = 0x4ca000,
    MARKER_WRAP = 0x4abd70,
    MARKER_INIT = 0x4adf20,
    MARKER_INIT_ARGUMENTS = 5,
    MARKER_BIND = 0x4ac8d0,
    MARKER_RESOURCE = 0x544a18,
    MARKER_FRAME = 0x4ac710,
    MARKER_FRAME_PREPARE = 0x4ac8a0,
    MARKER_REGISTER = 0x4b5e70,
    MARKER_LIST = 0x54671c,
    MARKER_SHOWN = 0x93,
    MARKER_SHOWN_TOO = 0x95,
    MARKER_STATE = 0x4e,
    MARKER_OFFSET = 0x48,
    MARKER_OFFSET_VALUE = 0xffd8
};

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(uint16_t)value;
}

uint32_t vertrix_marker_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t x, uint32_t y, uint32_t frame)
{
    static const uint32_t zeros[MARKER_INIT_ARGUMENTS] = {0, 0, 0, 0, 0};
    uint32_t actor = vertrix_call(calls, MARKER_ALLOCATE, MARKER_SIZE, y, frame, x, 0);
    uint32_t sy = sign16(y);
    void *storage;
    size_t size;
    if (actor != 0)
    {
        actor = vertrix_call(calls, MARKER_WRAP, actor, y, frame, x, 0);
    }
    vertrix_calln(calls, MARKER_INIT, actor, sign16(x), sy, 0, zeros, MARKER_INIT_ARGUMENTS, NULL);
    vertrix_call(calls, MARKER_BIND, actor, MARKER_RESOURCE, sy, 0, 0);
    vertrix_call(calls, MARKER_FRAME, actor, frame, sy, 0, 0);
    vertrix_call(calls, MARKER_FRAME_PREPARE, actor, frame, sy, 0, 0);
    if (!services->resolve(actor, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, MARKER_SHOWN, BYTE_WIDTH, 1) ||
        !vertrix_actor_storage_write(storage, size, MARKER_SHOWN_TOO, BYTE_WIDTH, 1) ||
        !vertrix_actor_storage_write(storage, size, MARKER_STATE, BYTE_WIDTH, 0) ||
        !vertrix_actor_storage_write(storage, size, MARKER_OFFSET, WORD_WIDTH, MARKER_OFFSET_VALUE))
    {
        return 0;
    }
    return vertrix_call(calls, MARKER_REGISTER, MARKER_LIST, actor, sy, 0, 0);
}
