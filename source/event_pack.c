#include "event_pack.h"

#include "actor_storage.h"

enum
{
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    BYTE_WIDTH = 1,
    RECORD_COUNT = 0,
    RECORD_NUMBER = 2,
    RECORD_SIZE_LIMIT = 4,
    RECORD_SIZE = 6,
    RECORD_POINTER = 8,
    SIZE_LIMIT = 0x40,
    NUMBER_SHIFT_BYTES = 8,
    NUMBER_SHIFT_SIZE = 6,
    ALLOCATE = 0x4e7c90,
    FILL = 0x40c220,
    VALUE_CALL = 0x40f170,
    REALLOC = 0x4ec0e0,
    FAILURE = 8,
    FLAG_BASE = 0x80,
    FLAG_VALUE = 1,
    FLAG_NIBBLES = 2,
    FLAG_COMMAND = 8,
    FLAG_LEVEL = 0x10,
    LEVEL_SCALE_COMMAND = 8,
    LEVEL_LIMIT = 0x80,
    LEVEL_FULL = 0xff,
    LOW_NIBBLE = 0xf,
    HIGH_NIBBLE = 0xf0,
    WORD_MASK = 0xffff,
    BYTE_MASK = 0xff,
    HIGH_WORD_MASK = 0xffff0000u
};

static const uint32_t DROPPED[] = {0x100, 0x200, 0xa00, 0xe10, 0xe20, 0xea0, 0xeb0};

static int dropped(uint32_t command)
{
    for (size_t i = 0; i < sizeof DROPPED / sizeof DROPPED[0]; i++)
    {
        if (DROPPED[i] == command)
        {
            return 1;
        }
    }
    return 0;
}

typedef struct Buffer
{
    const VertrixFactoryServices *services;
    uint32_t base;
    void *storage;
    size_t size;
} Buffer;

static int buffer_read(const Buffer *b, uint32_t address, uint32_t *value)
{
    return vertrix_actor_storage_read(b->storage, b->size, address - b->base, BYTE_WIDTH, value);
}

static int buffer_write(const Buffer *b, uint32_t address, uint32_t value)
{
    return vertrix_actor_storage_write(b->storage, b->size, address - b->base, BYTE_WIDTH, value);
}

static int record_store(const VertrixFactoryServices *services, uint32_t record, size_t offset,
                        unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(record, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, offset, width, value);
}

int vertrix_event_pack(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       uint32_t number, uint32_t record, uint32_t ebx, uint32_t *result)
{
    uint32_t bytes = number << NUMBER_SHIFT_BYTES;
    uint32_t size = (number * (1u << NUMBER_SHIFT_SIZE) + bytes) & WORD_MASK;
    uint32_t buffer_pointer, source, out, remaining, filled, eax;
    Buffer buffer;
    int ran = 0;
    if (!record_store(services, record, RECORD_COUNT, WORD_WIDTH, 0) ||
        !record_store(services, record, RECORD_NUMBER, WORD_WIDTH, number & WORD_MASK) ||
        !record_store(services, record, RECORD_SIZE_LIMIT, WORD_WIDTH, SIZE_LIMIT) ||
        !record_store(services, record, RECORD_SIZE, WORD_WIDTH, size))
    {
        return 0;
    }
    buffer_pointer = vertrix_call(calls, ALLOCATE, size, record, ebx, number, 0);
    if (!record_store(services, record, RECORD_POINTER, DWORD_WIDTH, buffer_pointer))
    {
        return 0;
    }
    if (buffer_pointer == 0)
    {
        *result = FAILURE;
        return 1;
    }
    source = buffer_pointer + (number << NUMBER_SHIFT_SIZE);
    out = buffer_pointer;
    filled = vertrix_call(calls, FILL, source, bytes, source, buffer_pointer, 0);
    buffer.services = services;
    buffer.base = buffer_pointer;
    if (!services->resolve(buffer_pointer, &buffer.storage, &buffer.size, services->context))
    {
        return 0;
    }
    for (remaining = bytes; remaining != 0; remaining -= 4)
    {
        uint32_t b0, b1, b2, b3, value, nibbles, part, level, flag;
        if (!buffer_read(&buffer, source, &b0) || !buffer_read(&buffer, source + 1, &b1) ||
            !buffer_read(&buffer, source + 2, &b2) || !buffer_read(&buffer, source + 3, &b3))
        {
            return 0;
        }
        value = vertrix_call(calls, VALUE_CALL, ((b0 & LOW_NIBBLE) << 8) + b1, b1, source, out, 0);
        nibbles = (b0 & HIGH_NIBBLE) + ((b2 >> 4) & LOW_NIBBLE);
        part = b2 & LOW_NIBBLE;
        level = b3;
        source += 4;
        if (dropped((part << 8) + b3))
        {
            part = 0;
            level = 0;
        }
        else if (part == LEVEL_SCALE_COMMAND)
        {
            level = b3 > LEVEL_LIMIT ? LEVEL_LIMIT : (b3 < LEVEL_LIMIT ? b3 * 2 : LEVEL_FULL);
        }
        flag = FLAG_BASE | (value != 0 ? FLAG_VALUE : 0) | (nibbles != 0 ? FLAG_NIBBLES : 0) |
               (part != 0 ? FLAG_COMMAND : 0) | (level != 0 ? FLAG_LEVEL : 0);
        if (!buffer_write(&buffer, out++, flag) ||
            (value != 0 && !buffer_write(&buffer, out++, value & BYTE_MASK)) ||
            (nibbles != 0 && !buffer_write(&buffer, out++, nibbles & BYTE_MASK)) ||
            (part != 0 && !buffer_write(&buffer, out++, part & BYTE_MASK)) ||
            (level != 0 && !buffer_write(&buffer, out++, level & BYTE_MASK)))
        {
            return 0;
        }
        ran = 1;
    }
    eax = ran ? 0 : (filled & HIGH_WORD_MASK);
    eax |= buffer_pointer & WORD_MASK;
    {
        uint32_t ecx = out - eax, edx = ecx & WORD_MASK, reallocated;
        if (!record_store(services, record, RECORD_SIZE, WORD_WIDTH, ecx & WORD_MASK))
        {
            return 0;
        }
        reallocated = vertrix_call(calls, REALLOC, buffer_pointer, edx, source, ecx, 0);
        if (!record_store(services, record, RECORD_POINTER, DWORD_WIDTH, reallocated))
        {
            return 0;
        }
        *result = reallocated == 0 ? FAILURE : 0;
    }
    return 1;
}
