#include "actor_spawn.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    SPAWN_SIZE = 0x15c,
    SPAWN_ALLOCATE = 0x4ca000,
    SPAWN_WRAP = 0x4abd70,
    SPAWN_INIT = 0x4adf20,
    SPAWN_INIT_ARGUMENTS = 5,
    SPAWN_DELAY = 0x4ac7d0,
    SPAWN_HANDLER = 0x4ac8f0,
    SPAWN_FLAG = 0x4ac910,
    SPAWN_REGISTER = 0x4b5e70,
    SPAWN_LIST = 0x54676c,
    SPAWN_FIELD58 = 0x58,
    SPAWN_FIELD5C = 0x5c,
    SPAWN_FIELD60 = 0x60,
    MATCH_EFFECT_RESOURCE = 0x544d28,
    MATCH_BURST_LIST = 0xcec,
    MATCH_BURST_COUNT = 8,
    MATCH_BURST_RESOURCE = 0x54651c,
    MATCH_BURST_HANDLER = 0x444700,
    MATCH_BURST_DESCRIPTOR_DIVISOR = 0x168,
    MATCH_BURST_FRAME_DIVISOR = 0x20
};

uint32_t vertrix_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixSpawnSpec *spec, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t zeros[SPAWN_INIT_ARGUMENTS] = {0, 0, 0, 0, 0};
    uint32_t actor = vertrix_call(calls, SPAWN_ALLOCATE, SPAWN_SIZE, edx, ebx, ecx, 0);
    void *storage;
    size_t size;
    if (actor != 0)
    {
        actor = vertrix_call(calls, SPAWN_WRAP, actor, edx, ebx, ecx, 0);
    }
    vertrix_calln(calls, SPAWN_INIT, actor, 0, 0, 0, zeros, SPAWN_INIT_ARGUMENTS, NULL);
    if (!services->resolve(actor, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, 0, DWORD_WIDTH, spec->kind))
    {
        return 0;
    }
    vertrix_call(calls, SPAWN_DELAY, actor, spec->delay, 0, 0, 0);
    if (!vertrix_actor_storage_write(storage, size, SPAWN_FIELD58, DWORD_WIDTH, spec->field58) ||
        !vertrix_actor_storage_write(storage, size, SPAWN_FIELD5C, DWORD_WIDTH, spec->field5c) ||
        !vertrix_actor_storage_write(storage, size, SPAWN_FIELD60, DWORD_WIDTH, spec->field60))
    {
        return 0;
    }
    vertrix_call(calls, SPAWN_HANDLER, actor, spec->handler, 0, 0, 0);
    vertrix_call(calls, SPAWN_FLAG, actor, 0, 0, 0, 0);
    return vertrix_call(calls, SPAWN_REGISTER, SPAWN_LIST, actor, 0, 0, 0);
}

uint32_t vertrix_actor_spawn_match_effect(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const void *source, size_t source_size, uint32_t edx,
                                          uint32_t ebx, uint32_t ecx)
{
    uint32_t field;
    uint32_t actor;
    void *storage;
    size_t size;
    int32_t base_x;
    int32_t base_y;
    uint32_t word;
    if (!vertrix_actor_storage_read(source, source_size, 0xc, DWORD_WIDTH, &field))
    {
        return 0;
    }
    base_x = (int32_t)field >> 0x10;
    if (!vertrix_actor_storage_read(source, source_size, 0x14, DWORD_WIDTH, &field))
    {
        return 0;
    }
    base_y = (int32_t)field >> 0x10;
    actor = vertrix_call(calls, SPAWN_ALLOCATE, SPAWN_SIZE, edx, ebx, ecx, 0);
    if (!services->resolve(actor, &storage, &size, services->context) ||
        !vertrix_actor_storage_construct(storage, size) ||
        !vertrix_actor_initialize(storage, size, 0, 0, 0, 0, 0, 0, 0) ||
        !vertrix_actor_set_d0_steps(storage, size, 4) ||
        !vertrix_actor_set_period_steps(storage, size, 1) ||
        !vertrix_actor_attach_resource(storage, size, MATCH_EFFECT_RESOURCE) ||
        !vertrix_actor_storage_write(storage, size, 0xa8, WORD_WIDTH, (uint32_t)base_x) ||
        !vertrix_actor_storage_write(storage, size, 0xaa, WORD_WIDTH, (uint32_t)(base_x + 0x77)) ||
        !vertrix_actor_storage_write(storage, size, 0xac, WORD_WIDTH, (uint32_t)base_y) ||
        !vertrix_actor_storage_write(storage, size, 0xae, WORD_WIDTH, (uint32_t)(base_y + 0x137)) ||
        !vertrix_actor_set_frame_index(storage, size, 0))
    {
        return 0;
    }
    if (!vertrix_actor_storage_write(storage, size, 0x8e, BYTE_WIDTH, 3) ||
        !vertrix_actor_storage_write(storage, size, 0x94, BYTE_WIDTH, 1) ||
        !vertrix_actor_storage_write(storage, size, 0x95, BYTE_WIDTH, 1) ||
        !vertrix_actor_storage_write(storage, size, 0x48, WORD_WIDTH, 0x1e) ||
        !vertrix_actor_storage_write(storage, size, 0x4e, BYTE_WIDTH, 0x5a) ||
        !vertrix_actor_storage_write(storage, size, 0x93, BYTE_WIDTH, 1))
    {
        return 0;
    }
    if (!vertrix_actor_storage_read(source, source_size, 0xe, WORD_WIDTH, &word))
    {
        return 0;
    }
    if (!vertrix_actor_storage_write(storage, size, 0xe, WORD_WIDTH,
                                     ((edx * 0x18 + word) & 0xffff) - 3))
    {
        return 0;
    }
    if (!vertrix_actor_storage_read(source, source_size, 0x16, WORD_WIDTH, &word))
    {
        return 0;
    }
    if (!vertrix_actor_storage_write(storage, size, 0x16, WORD_WIDTH,
                                     ((ebx * 0x18 + word) & 0xffff) - 3))
    {
        return 0;
    }
    return actor;
}

uint32_t vertrix_actor_spawn_match_burst(const VertrixFactoryServices *services, const void *source,
                                         size_t source_size, uint32_t source_handle, uint32_t edx,
                                         uint32_t ebx, const VertrixMatchBurstHooks *hooks)
{
    uint32_t pair_x = edx * 0x18;
    uint32_t pair_y = ebx * 0x18;
    uint32_t list = source_handle + MATCH_BURST_LIST;
    uint16_t descriptor = hooks->draw(MATCH_BURST_DESCRIPTOR_DIVISOR, hooks->context);
    uint16_t count = (uint16_t)(hooks->draw(2, hooks->context) + 3);
    uint32_t index;
    uint32_t word;
    uint32_t field;
    for (index = 0; index < MATCH_BURST_COUNT; index++)
    {
        uint32_t actor = hooks->allocate(SPAWN_SIZE, hooks->context);
        void *storage;
        size_t size;
        uint16_t frame;
        if (!vertrix_actor_storage_read(source, source_size, 0xe, WORD_WIDTH, &word) ||
            !services->resolve(actor, &storage, &size, services->context) ||
            !vertrix_actor_storage_construct(storage, size) ||
            !vertrix_actor_initialize(storage, size, 0, 0, 0, 0, 0, 0, 0) ||
            !vertrix_actor_storage_write(storage, size, 0xe, WORD_WIDTH,
                                         (word + pair_x + 0xc) & 0xffff))
        {
            return 0;
        }
        if (!vertrix_actor_storage_read(source, source_size, 0x16, WORD_WIDTH, &word) ||
            !vertrix_actor_storage_write(storage, size, 0x16, WORD_WIDTH,
                                         (word + pair_y + 0xc) & 0xffff) ||
            !vertrix_actor_set_d0_steps(storage, size, 1) ||
            !vertrix_actor_set_period_steps(storage, size, 1) ||
            !vertrix_actor_set_e0_steps(storage, size, 2) ||
            !vertrix_actor_attach_resource(storage, size, MATCH_BURST_RESOURCE))
        {
            return 0;
        }
        frame = hooks->draw(MATCH_BURST_FRAME_DIVISOR, hooks->context);
        if (!vertrix_actor_set_frame_index(storage, size, frame))
        {
            return 0;
        }
        hooks->bind_frame(actor, descriptor, hooks->context);
        if (!vertrix_actor_storage_write(storage, size, 0x94, BYTE_WIDTH, 1) ||
            !vertrix_actor_storage_write(storage, size, 0x95, BYTE_WIDTH, 4) ||
            !vertrix_actor_storage_write(storage, size, 0x48, WORD_WIDTH, 0) ||
            !vertrix_actor_storage_write(storage, size, 0x4e, BYTE_WIDTH, 0x32) ||
            !vertrix_actor_storage_write(storage, size, 0x93, BYTE_WIDTH, 1) ||
            !vertrix_actor_storage_write(storage, size, 0x24, WORD_WIDTH,
                                         (uint32_t)(descriptor % MATCH_BURST_DESCRIPTOR_DIVISOR)) ||
            !vertrix_actor_storage_write(storage, size, 0x28, WORD_WIDTH, count))
        {
            return 0;
        }
        if (!vertrix_actor_storage_read(storage, size, 0xc, DWORD_WIDTH, &word) ||
            !vertrix_actor_storage_read(storage, size, 0x14, DWORD_WIDTH, &field) ||
            !vertrix_actor_set_words_2a(storage, size, 0, (uint16_t)((int32_t)word >> 0x10),
                                        (uint16_t)((int32_t)field >> 0x10)) ||
            !vertrix_actor_storage_write(storage, size, 0x30, WORD_WIDTH, 0x64) ||
            !vertrix_actor_storage_write(storage, size, 0x32, WORD_WIDTH, 1) ||
            !vertrix_actor_set_handler(storage, size, MATCH_BURST_HANDLER))
        {
            return 0;
        }
        hooks->append(list, actor, hooks->context);
        descriptor = (uint16_t)(descriptor + 0x2d);
    }
    return 0;
}
