#include "pair_sync.h"

enum
{
    WORD_WIDTH = 2,
    PAIR_TABLE = 0x54d640,
    PAIR_STORE_WORD = 0x476320,
    PAIR_SET_VALUE = 0x476440,
    PAIR_REFRESH = 0x476010,
    PAIR_STORE_PAIR = 0x4735e0,
    PAIR_STORE_FLAG = 0x473610,
    PAIR_WORD_BASE = 0x160,
    PAIR_WORDS = 4,
    PAIR_PARTNER_DELTA = 8,
    PAIR_GATE_ON = 1,
    PAIR_FLAG_HALF = 4,
    PAIR_PROBE = 0x476480,
    PAIR_BYTE_MASK = 0xff
};

static const uint32_t PROBE_OFFSETS[PAIR_WORDS] = {0x164, 0x166, 0x160, 0x162};

static const uint32_t FLAG_OFFSETS[PAIR_FLAG_HALF] = {0x16c, 0x16e, 0x168, 0x16a};

static int read_word(const VertrixFactoryServices *services, uint32_t object, uint32_t offset,
                     uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(object, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, WORD_WIDTH, value);
}

static uint32_t word_pairs(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           uint32_t first, uint32_t second, uint32_t result)
{
    const uint32_t objects[2] = {first, second};
    for (unsigned object = 0; object < 2; object++)
    {
        for (uint32_t index = 0; index < PAIR_WORDS; index++)
        {
            uint32_t low, high;
            if (!read_word(services, objects[object], PAIR_WORD_BASE + WORD_WIDTH * index, &low) ||
                !read_word(services, objects[object],
                           PAIR_WORD_BASE + PAIR_PARTNER_DELTA + WORD_WIDTH * index, &high))
            {
                return 0;
            }
            result = vertrix_call(calls, PAIR_STORE_PAIR, low, high, second, first, 0);
        }
    }
    return result;
}

uint32_t vertrix_pair_words(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t first, uint32_t second, uint32_t gate, uint32_t gate_after,
                            uint32_t value)
{
    uint32_t result;
    if (gate == 0)
    {
        const uint32_t objects[2] = {first, second};
        for (unsigned object = 0; object < 2; object++)
        {
            for (uint32_t index = 0; index < PAIR_WORDS; index++)
            {
                uint32_t word;
                if (!read_word(services, objects[object], PAIR_WORD_BASE + WORD_WIDTH * index,
                               &word))
                {
                    return 0;
                }
                vertrix_call(calls, PAIR_STORE_WORD, PAIR_TABLE, word, second, first, 0);
            }
        }
    }
    vertrix_call(calls, PAIR_SET_VALUE, PAIR_TABLE, value, second, first, 0);
    result = vertrix_call(calls, PAIR_REFRESH, PAIR_TABLE, 0, second, first, 0);
    if (gate_after == 0)
    {
        result = word_pairs(calls, services, first, second, result);
    }
    return result;
}

uint32_t vertrix_pair_flags(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t first, uint32_t second, uint32_t gate,
                            const uint8_t flags[VERTRIX_PAIR_FLAG_COUNT])
{
    const uint32_t objects[2] = {gate == PAIR_GATE_ON ? second : first,
                                 gate == PAIR_GATE_ON ? first : second};
    uint32_t result = vertrix_call(calls, PAIR_REFRESH, PAIR_TABLE, 0, second, first, 0);
    for (unsigned half = 0; half < 2; half++)
    {
        for (unsigned index = 0; index < PAIR_FLAG_HALF; index++)
        {
            uint32_t word;
            if (!read_word(services, objects[half], FLAG_OFFSETS[index], &word))
            {
                return 0;
            }
            result = vertrix_call(calls, PAIR_STORE_FLAG, word,
                                  flags[half * PAIR_FLAG_HALF + index], second, first, 0);
        }
    }
    return result;
}

static int probe_words(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       uint32_t object, uint32_t ebx, uint8_t bytes[PAIR_WORDS])
{
    for (unsigned index = 0; index < PAIR_WORDS; index++)
    {
        uint32_t word;
        if (!read_word(services, object, PROBE_OFFSETS[index], &word))
        {
            return 0;
        }
        bytes[index] = (uint8_t)(vertrix_call(calls, PAIR_PROBE, PAIR_TABLE, word, ebx, object, 0) &
                                 PAIR_BYTE_MASK);
    }
    return 1;
}

static int store_words(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       uint32_t object, uint32_t ebx, uint32_t *result, uint32_t *last_word)
{
    for (uint32_t index = 0; index < PAIR_WORDS; index++)
    {
        if (!read_word(services, object, PAIR_WORD_BASE + WORD_WIDTH * index, last_word))
        {
            return 0;
        }
        *result = vertrix_call(calls, PAIR_STORE_WORD, PAIR_TABLE, *last_word, ebx, object, 0);
    }
    return 1;
}

uint32_t vertrix_pair_scan(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           uint32_t first, uint32_t second, uint32_t gate, uint32_t ebx,
                           uint8_t bytes[VERTRIX_PAIR_FLAG_COUNT])
{
    uint32_t object = gate == PAIR_GATE_ON ? second : first;
    uint32_t result = 0, word;
    if (!probe_words(calls, services, object, ebx, bytes) ||
        !store_words(calls, services, object, ebx, &result, &word))
    {
        return 0;
    }
    vertrix_call(calls, PAIR_SET_VALUE, PAIR_TABLE, 0, ebx, object, 0);
    vertrix_call(calls, PAIR_REFRESH, PAIR_TABLE, 0, ebx, object, 0);
    if (!probe_words(calls, services, object, ebx, bytes + PAIR_WORDS) ||
        !store_words(calls, services, object, ebx, &result, &word))
    {
        return 0;
    }
    return result;
}
