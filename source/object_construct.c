#include "object_construct.h"
#include "actor_storage.h"
#include "block_factory.h"

enum
{
    DWORD_WIDTH = 4,
    BOARD_FRAME_TYPE = 0x514950,
    BOARD_TAIL = 0xcec,
    SLOT_FRAME_TYPE = 0x514d90,
    CHAIN_FRAME_TYPE = 0x515010
};

typedef struct BoardArray
{
    uint16_t offset;
    uint16_t count;
} BoardArray;

typedef struct BoardWrite
{
    uint16_t offset;
    uint8_t value;
} BoardWrite;

static int resolve_object(const VertrixFactoryServices *services, uint32_t handle, void **storage,
                          size_t *size)
{
    return services->resolve(handle, storage, size, services->context);
}

uint32_t vertrix_board_construct(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t eax)
{
    static const BoardArray arrays[] = {{0x220, 0x41}, {0x87c, 0x41},  {0x988, 5},   {0x9e8, 0xd},
                                        {0xa2c, 0xd},  {0x324, 0x104}, {0xbdc, 0x41}};
    static const uint32_t setup[] = {0x42f850, 0x42f860, 0x42ef00, 0x42ef10, 0x42ef20,
                                     0x42ef30, 0x42ef40, 0x42ef50, 0x42f870, 0x42f880};
    static const BoardWrite clears_before[] = {{0xa60, 0}, {0xb70, 0}, {0xb78, 0}};
    static const BoardWrite stores_after[] = {{0xa68, 2}, {0xb80, 0}, {0xb84, 0}, {0xb88, 0},
                                              {0xbd8, 0}, {0xb8c, 0}, {0xb90, 1}, {0xce0, 0},
                                              {0xce4, 0}, {0xce8, 0}};
    void *storage;
    size_t size;
    uint32_t built = vertrix_call(calls, 0x4abd70, eax, VERTRIX_CONSTRUCT_FRAME_HANDLER,
                                  BOARD_FRAME_TYPE, eax, 0);
    uint32_t board = vertrix_call(calls, 0x4b5db0, built + BOARD_TAIL,
                                  VERTRIX_CONSTRUCT_FRAME_HANDLER, BOARD_FRAME_TYPE, eax, 0) -
                     BOARD_TAIL;
    uint32_t count = 0x41;
    if (!resolve_object(services, board, &storage, &size) ||
        !vertrix_actor_storage_write(storage, size, 0x158, DWORD_WIDTH, 0x5149e4))
    {
        return 0;
    }
    for (size_t i = 0; i < sizeof arrays / sizeof arrays[0]; ++i)
    {
        count = arrays[i].count;
        vertrix_call(calls, 0x4b2290, board + arrays[i].offset, count, BOARD_FRAME_TYPE, board, 0);
    }
    for (size_t i = 0; i < sizeof clears_before / sizeof clears_before[0]; ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, clears_before[i].offset, DWORD_WIDTH,
                                         clears_before[i].value))
        {
            return 0;
        }
    }
    for (size_t i = 0; i < sizeof setup / sizeof setup[0]; ++i)
    {
        vertrix_call(calls, setup[i], board, count, BOARD_FRAME_TYPE, board, 0);
    }
    for (size_t i = 0; i < sizeof stores_after / sizeof stores_after[0]; ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, stores_after[i].offset, DWORD_WIDTH,
                                         stores_after[i].value))
        {
            return 0;
        }
    }
    return board;
}

uint32_t vertrix_slot_object_construct(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t eax)
{
    void *storage;
    size_t size;
    uint32_t object = vertrix_call(calls, 0x4abd70, eax, VERTRIX_CONSTRUCT_FRAME_HANDLER,
                                   SLOT_FRAME_TYPE, eax, 0);
    if (!resolve_object(services, object, &storage, &size) ||
        !vertrix_actor_storage_write(storage, size, 0x158, DWORD_WIDTH, 0x514df4))
    {
        return 0;
    }
    vertrix_call(calls, 0x4b2290, object + 0x15c, 0x1f4, SLOT_FRAME_TYPE, object, 0);
    vertrix_call(calls, 0x4b2290, object + 0x92c, 8, SLOT_FRAME_TYPE, object, 0);
    if (!vertrix_actor_storage_write(storage, size, 0x94c, DWORD_WIDTH, 0) ||
        !vertrix_actor_storage_write(storage, size, 0x950, DWORD_WIDTH, 1))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_chain_object_construct(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t eax)
{
    void *storage;
    size_t size;
    uint32_t chained = vertrix_call(calls, 0x4b5db0, eax + 0x22c, eax, CHAIN_FRAME_TYPE, 3, 0);
    chained = vertrix_call(calls, 0x4b5db0, chained + 0x14, 2, CHAIN_FRAME_TYPE, 3, 0);
    chained = vertrix_call(calls, 0x4b5db0, chained + 0x14, 2, CHAIN_FRAME_TYPE, 3, 0);
    uint32_t object = chained - 0x254;
    if (!resolve_object(services, object, &storage, &size) ||
        !vertrix_actor_storage_write(storage, size, 0x27c, DWORD_WIDTH, 0x5150f4))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_special_actor_spawn(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t edx,
                                     uint32_t ebx, uint32_t ecx)
{
    void *storage;
    size_t size;
    uint32_t actor = services->allocate(0x15c, services->context);
    if (actor != 0)
    {
        actor = vertrix_call(calls, 0x4abd70, actor, edx, ebx, ecx, 0);
    }
    if (!resolve_object(services, actor, &storage, &size) ||
        !vertrix_actor_initialize(storage, size, 0, 0, 0, 0, 0, 0, 0) ||
        !vertrix_actor_storage_write(storage, size, 0, DWORD_WIDTH, 9))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac7d0, actor, 0xa, 0, 0, 0);
    if (!vertrix_actor_storage_write(storage, size, 0x58, DWORD_WIDTH, 0x1df) ||
        !vertrix_actor_storage_write(storage, size, 0x5c, DWORD_WIDTH, 0) ||
        !vertrix_actor_storage_write(storage, size, 0x60, DWORD_WIDTH, 4))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac8f0, actor, 0x4597a0, 0, 0, 0);
    vertrix_call(calls, 0x4ac910, actor, 0, 0, 0, 0);
    return vertrix_call(calls, 0x4b5e70, 0x54676c, actor, 0, 0, 0);
}
