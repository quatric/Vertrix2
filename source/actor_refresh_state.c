#include "actor_refresh_state.h"

enum
{
    FIELD_FLAG = 0x120,
    FIELD_INDEX = 0x148,
    INDEX_WIDTH = 2,
    DWORD_WIDTH = 4,
    INDEX_NONE = 0xffff
};

int vertrix_actor_refresh_value(const VertrixActorRefresh *state, const void *actor, size_t size,
                                uint32_t *value)
{
    uint32_t word;
    if (!vertrix_actor_storage_read(actor, size, FIELD_INDEX, INDEX_WIDTH, &word))
    {
        return 0;
    }
    if (word == INDEX_NONE)
    {
        return vertrix_actor_storage_read(actor, size, FIELD_FLAG, DWORD_WIDTH, value);
    }
    if (word >= VERTRIX_ACTOR_REFRESH_COUNT)
    {
        return 0;
    }
    *value = state->refresh[word];
    return 1;
}

int vertrix_actor_refresh_arm(VertrixActorRefresh *state, void *actor, size_t size)
{
    uint32_t word;
    if (!vertrix_actor_storage_read(actor, size, FIELD_INDEX, INDEX_WIDTH, &word))
    {
        return 0;
    }
    if (word == INDEX_NONE)
    {
        return vertrix_actor_storage_write(actor, size, FIELD_FLAG, DWORD_WIDTH, 1);
    }
    if (word >= VERTRIX_ACTOR_REFRESH_COUNT)
    {
        return 0;
    }
    state->refresh[word] = 1;
    return 1;
}

static uint32_t refresh_index(uint32_t word)
{
    return (word & 0x8000u) ? word | 0xffff0000u : word;
}

uint32_t vertrix_actor_refresh_value_full(const void *actor, size_t size, VertrixMemoryRead read,
                                          void *context)
{
    uint32_t word, value;
    if (!vertrix_actor_storage_read(actor, size, FIELD_INDEX, INDEX_WIDTH, &word))
    {
        return 0;
    }
    if (word == INDEX_NONE)
    {
        return vertrix_actor_storage_read(actor, size, FIELD_FLAG, DWORD_WIDTH, &value) ? value : 0;
    }
    uint32_t address = 0x5bb714u + 4u * refresh_index(word);
    return read && read(address, DWORD_WIDTH, &value, context) ? value : 0;
}

uint32_t vertrix_actor_refresh_arm_full(void *actor, size_t size, uint32_t handle,
                                        VertrixMemoryWrite write, void *context)
{
    uint32_t word;
    if (!vertrix_actor_storage_read(actor, size, FIELD_INDEX, INDEX_WIDTH, &word))
    {
        return 0;
    }
    if (word == INDEX_NONE)
    {
        return vertrix_actor_storage_write(actor, size, FIELD_FLAG, DWORD_WIDTH, 1) ? handle : 0;
    }
    uint32_t index = refresh_index(word);
    uint32_t address = 0x5bb714u + 4u * index;
    return write && write(address, DWORD_WIDTH, 1, context) ? index : 0;
}
