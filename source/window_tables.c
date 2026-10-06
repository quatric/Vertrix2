#include "window_tables.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    POINTERS = 0x4f5f90,
    INTEGERS = 0x4f5fa4,
    WINDOW_ARRAYS = 5,
    FIRST_COUNT = 0x10,
    FIRST_DIVISOR = 0x40,
    FROM_INT = 0x4d6768,
    MULTIPLY = 0x4db507,
    ADD = 0x4db350,
    DIVIDE = 0x4eb652,
    COSINE = 0x4c9dd6,
    TO_SINGLE = 0x4eb606,
    TWO_HIGH = 0x40000000,
    ONE_HIGH = 0x3ff00000,
    PI_LOW = 0x54442d18,
    PI_HIGH = 0x400921fb,
    SCALE_HIGH = 0x3ef00000,
    TABLE_START = 0x52e784,
    TABLE_LIMIT = 0x52efc4,
    ROW_STEP = 0x80,
    WRAP_BACK = 0xffc,
    WRAP_EVERY = 0x20,
    WRAP_REMAINDER = 0x1f,
    SIGN_EVERY = 0x40,
    SIGN_REMAINDER = 0x3f,
    COPY_DISTANCE = 0x40,
    FIRST_PASS = 0x100,
    SECOND_PASS = 0x200
};

typedef struct Tables
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    uint32_t eax, edx, ebx, ecx;
    int ok;
} Tables;

static void helper(Tables *t, uint32_t target)
{
    uint32_t high;
    t->eax = vertrix_calln(t->calls, target, t->eax, t->edx, t->ebx, t->ecx, NULL, 0, &high);
    t->edx = high;
}

static uint32_t read_at(Tables *t, uint32_t handle, size_t offset)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!t->services->resolve(handle, &storage, &size, t->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, &value))
    {
        t->ok = 0;
    }
    return value;
}

static void write_at(Tables *t, uint32_t handle, size_t offset, uint32_t value)
{
    void *storage;
    size_t size;
    if (!t->services->resolve(handle, &storage, &size, t->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, value))
    {
        t->ok = 0;
    }
}

static void store_pair(Tables *t, uint32_t address)
{
    write_at(t, VERTRIX_WINDOW_TARGET, address - TABLE_START, t->eax);
    write_at(t, VERTRIX_WINDOW_TARGET, address - TABLE_START + COPY_DISTANCE, t->eax);
}

/* The entry of the second table for the integer at `offset` of the pointer table region: the
 * integer times 2^-16 times the sign, as a single, stored at `address` and 0x40 further. `swapped`
 * is the register arrangement of the second pass. */
static void scaled_entry(Tables *t, uint32_t offset, uint32_t sign, uint32_t address, int swapped)
{
    uint32_t low, high;
    t->eax = read_at(t, VERTRIX_WINDOW_SOURCE, offset + INTEGERS - POINTERS);
    helper(t, FROM_INT);
    t->ebx = 0;
    t->ecx = SCALE_HIGH;
    helper(t, MULTIPLY);
    if (swapped)
    {
        t->ecx = t->eax;
        t->ebx = t->edx;
        t->eax = sign;
        helper(t, FROM_INT);
        low = t->eax;
        high = t->edx;
        t->eax = t->ecx;
        t->edx = t->ebx;
        t->ebx = low;
        t->ecx = high;
    }
    else
    {
        low = t->eax;
        t->ecx = t->edx;
        t->eax = sign;
        helper(t, FROM_INT);
        t->ebx = t->eax;
        high = t->edx;
        t->eax = low;
        t->edx = t->ecx;
        t->ecx = high;
    }
    helper(t, MULTIPLY);
    helper(t, TO_SINGLE);
    store_pair(t, address);
}

static void window_entry(Tables *t, uint32_t index, uint32_t divisor, uint32_t array, uint32_t slot)
{
    uint32_t low, high;
    t->eax = index;
    helper(t, FROM_INT);
    t->ebx = 0;
    t->ecx = TWO_HIGH;
    helper(t, MULTIPLY);
    t->ebx = 0;
    t->ecx = ONE_HIGH;
    helper(t, ADD);
    t->ebx = PI_LOW;
    t->ecx = PI_HIGH;
    helper(t, MULTIPLY);
    t->ecx = t->eax;
    t->ebx = t->edx;
    t->eax = divisor;
    helper(t, FROM_INT);
    low = t->eax;
    high = t->edx;
    t->eax = t->ecx;
    t->edx = t->ebx;
    t->ebx = low;
    t->ecx = high;
    helper(t, DIVIDE);
    helper(t, COSINE);
    t->ebx = 0;
    t->ecx = TWO_HIGH;
    helper(t, MULTIPLY);
    t->ebx = t->eax;
    t->ecx = t->edx;
    t->eax = 0;
    t->edx = ONE_HIGH;
    helper(t, DIVIDE);
    helper(t, TO_SINGLE);
    write_at(t, array, (size_t)slot * DWORD_WIDTH, t->eax);
}

int vertrix_window_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          uint32_t sign, uint32_t ebx, uint32_t ecx)
{
    Tables tables = {calls, services, sign, 0, ebx, ecx, 1};
    Tables *t = &tables;
    uint32_t value = 0u - sign, address = TABLE_START, offset = 0;
    int32_t row = 0, mirror;
    t->edx = 0;
    for (uint32_t k = 0; k < WINDOW_ARRAYS && t->ok; k++)
    {
        uint32_t count = FIRST_COUNT >> k, divisor = FIRST_DIVISOR >> k;
        uint32_t array = read_at(t, VERTRIX_WINDOW_SOURCE, k * DWORD_WIDTH);
        t->ecx = (t->ecx & ~0xffu) | k;
        t->edx = k;
        for (uint32_t i = 0; i < count && t->ok; i++)
        {
            window_entry(t, i, divisor, array, i);
            t->edx = array + i * DWORD_WIDTH;
        }
        t->edx = k + 1;
    }
    for (row = 0; row < (int32_t)FIRST_PASS && t->ok; row++)
    {
        if (address < TABLE_LIMIT)
        {
            scaled_entry(t, offset, value, address, 0);
        }
        t->ecx = WRAP_EVERY;
        t->edx = (uint32_t)row % WRAP_EVERY;
        if (t->edx == WRAP_REMAINDER)
        {
            address -= WRAP_BACK;
        }
        t->ecx = SIGN_EVERY;
        t->edx = (uint32_t)row % SIGN_EVERY;
        if (t->edx == SIGN_REMAINDER)
        {
            value = 0u - value;
        }
        offset += DWORD_WIDTH;
        address += ROW_STEP;
    }
    offset = FIRST_PASS * DWORD_WIDTH;
    for (mirror = FIRST_PASS; mirror < (int32_t)SECOND_PASS && t->ok; mirror++)
    {
        if (address < TABLE_LIMIT)
        {
            scaled_entry(t, offset, value, address, 1);
        }
        t->ecx = WRAP_EVERY;
        t->edx = (uint32_t)mirror % WRAP_EVERY;
        if (t->edx == WRAP_REMAINDER)
        {
            address -= WRAP_BACK;
        }
        t->ecx = SIGN_EVERY;
        t->edx = (uint32_t)mirror % SIGN_EVERY;
        if (t->edx == SIGN_REMAINDER)
        {
            value = 0u - value;
        }
        offset -= DWORD_WIDTH;
        address += ROW_STEP;
    }
    return t->ok;
}
