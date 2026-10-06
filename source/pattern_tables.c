#include "pattern_tables.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    BYTE_WIDTH = 1,
    SURFACE_LENGTH = 4,
    MAX_RUN = 0x5440f6,
    MIN_RUN = 0x5440f7,
    POINTER_TABLE = 0x54414c,
    SIZE_TABLE = 0x544318,
    EXPANDED_POINTERS = 0x54438c,
    EXPANDED_SIZES = 0x544790,
    SOURCE_TABLE = 0x4fba48,
    SOURCE_ENTRIES = 0x73,
    MISSING_ENTRY = 0x53,
    EXPANDED_ENTRIES = 0x100,
    PASSES = 6,
    PASS_STEP = 0xb,
    FIRST_START = 1,
    FIRST_LIMIT = 0xb,
    COLUMNS = 10,
    INITIAL_MIN_RUN = 4,
    PIXEL_READ = 0x478f10,
    ALLOCATE = 0x4ec160,
    ALLOCATE_EDX = 1,
    WORD_MASK = 0xffff,
    BYTE_MASK = 0xff
};

typedef struct Patterns
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    int ok;
} Patterns;

static uint32_t table_read(Patterns *p, uint32_t handle, uint32_t address, uint32_t base,
                           unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!p->services->resolve(handle, &storage, &size, p->services->context) ||
        !vertrix_actor_storage_read(storage, size, address - base, width, &value))
    {
        p->ok = 0;
    }
    return value;
}

static void table_write(Patterns *p, uint32_t handle, uint32_t address, uint32_t base,
                        unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!p->services->resolve(handle, &storage, &size, p->services->context) ||
        !vertrix_actor_storage_write(storage, size, address - base, width, value))
    {
        p->ok = 0;
    }
}

static uint32_t target_read(Patterns *p, uint32_t address, unsigned width)
{
    return table_read(p, VERTRIX_PATTERN_TARGET, address, VERTRIX_PATTERN_TARGET, width);
}

static void target_write(Patterns *p, uint32_t address, unsigned width, uint32_t value)
{
    table_write(p, VERTRIX_PATTERN_TARGET, address, VERTRIX_PATTERN_TARGET, width, value);
}

static void expand(Patterns *p)
{
    for (uint32_t i = 0; i < EXPANDED_ENTRIES && p->ok; i++)
    {
        uint32_t entry = 0, pointer, size;
        while (entry < SOURCE_ENTRIES && table_read(p, VERTRIX_PATTERN_SOURCE, SOURCE_TABLE + entry,
                                                    SOURCE_TABLE, BYTE_WIDTH) != i)
        {
            entry++;
        }
        if (entry == SOURCE_ENTRIES)
        {
            entry = MISSING_ENTRY;
        }
        pointer = target_read(p, POINTER_TABLE + entry * DWORD_WIDTH, DWORD_WIDTH);
        size = target_read(p, SIZE_TABLE + entry, BYTE_WIDTH);
        target_write(p, EXPANDED_POINTERS + i * DWORD_WIDTH, DWORD_WIDTH, pointer);
        target_write(p, EXPANDED_SIZES + i, BYTE_WIDTH, size);
    }
}

int vertrix_pattern_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           uint32_t surface)
{
    Patterns patterns = {calls, services, 1};
    Patterns *p = &patterns;
    uint32_t length, pos = 0, start = FIRST_START, limit = FIRST_LIMIT, state = 0, pass = 0;
    uint32_t index = 0, ebx = FIRST_LIMIT, marked = 0;
    void *storage;
    size_t size;
    if (!services->resolve(surface, &storage, &size, services->context) ||
        !vertrix_actor_storage_read(storage, size, SURFACE_LENGTH, DWORD_WIDTH, &length))
    {
        return 0;
    }
    target_write(p, MAX_RUN, BYTE_WIDTH, 0);
    target_write(p, MIN_RUN, BYTE_WIDTH, INITIAL_MIN_RUN);
    while (p->ok && pass < PASSES)
    {
        while (p->ok && pos < length)
        {
            uint32_t column = start, zeros = 0, run;
            do
            {
                ebx = column;
                if (vertrix_call(calls, PIXEL_READ, surface, pos, ebx, column, 0) != 0)
                {
                    break;
                }
                ebx = limit;
                column++;
                zeros++;
            } while (column < limit);
            if (zeros != COLUMNS)
            {
                if (state == 0)
                {
                    state = 1;
                    marked = pos & WORD_MASK;
                }
                pos++;
                continue;
            }
            if (state != 1)
            {
                pos++;
                continue;
            }
            run = (pos - marked) & BYTE_MASK;
            if (run > target_read(p, MAX_RUN, BYTE_WIDTH))
            {
                target_write(p, MAX_RUN, BYTE_WIDTH, run);
            }
            if (run < target_read(p, MIN_RUN, BYTE_WIDTH))
            {
                target_write(p, MIN_RUN, BYTE_WIDTH, run);
            }
            target_write(p, SIZE_TABLE + (index & WORD_MASK), BYTE_WIDTH, run);
            {
                uint32_t buffer = vertrix_call(calls, ALLOCATE, run * COLUMNS, ALLOCATE_EDX, ebx,
                                               index & WORD_MASK, 0);
                uint32_t out = buffer, copy = start;
                target_write(p, POINTER_TABLE + (index & WORD_MASK) * DWORD_WIDTH, DWORD_WIDTH,
                             buffer);
                do
                {
                    for (uint32_t i = 0; i < run; i++)
                    {
                        void *out_storage;
                        size_t out_size;
                        uint32_t pixel;
                        ebx = copy;
                        pixel = vertrix_call(calls, PIXEL_READ, surface, marked + i, ebx, i, 0);
                        if (!services->resolve(buffer, &out_storage, &out_size,
                                               services->context) ||
                            !vertrix_actor_storage_write(out_storage, out_size, out - buffer,
                                                         BYTE_WIDTH, pixel & BYTE_MASK))
                        {
                            return 0;
                        }
                        out++;
                    }
                    copy++;
                } while (copy != limit);
            }
            index++;
            state = 0;
            pos++;
        }
        start += PASS_STEP;
        state = 0;
        pos = 0;
        limit += PASS_STEP;
        pass++;
    }
    expand(p);
    return p->ok;
}
