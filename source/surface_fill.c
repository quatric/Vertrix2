#include "surface_fill.h"

#include "actor_storage.h"
#include "object_value_helpers.h"

enum
{
    DWORD_WIDTH = 4,
    BYTE_WIDTH = 1,
    FIELD_PIXELS = 0,
    FIELD_WIDTH = 4,
    FIELD_HEIGHT = 8,
    FIELD_BYTES = 0xc,
    FIELD_FORMAT = 0xd,
    FIELD_FLAT = 0x10,
    FIELD_PITCH = 0x18,
    STATE_POINTER = 0,
    STATE_COUNT = 4,
    STATE_SPARE = 8,
    STATE_ROWS = 0xc,
    STATE_PITCH = 0x10,
    STATE_DWORD = 0x14,
    STATE_PACKED = 0x18,
    STATE_FORMAT = 0x5c,
    BYTE_SHIFT = 8,
    WORD_SHIFT = 16,
    TOP_SHIFT = 24
};

typedef struct Fill
{
    const VertrixFactoryServices *services;
    int ok;
} Fill;

static uint32_t get(Fill *f, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!f->services->resolve(handle, &storage, &size, f->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        f->ok = 0;
    }
    return value;
}

static void put(Fill *f, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!f->services->resolve(handle, &storage, &size, f->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        f->ok = 0;
    }
}

static void fill_run(Fill *f, uint32_t base, uint32_t *cursor, uint32_t count, uint32_t value)
{
    for (; count != 0 && f->ok; count--)
    {
        put(f, base, *cursor - base, DWORD_WIDTH, value);
        *cursor += DWORD_WIDTH;
    }
}

int vertrix_surface_fill(const VertrixFactoryServices *services, uint32_t surface, uint32_t colour,
                         uint32_t *result)
{
    Fill fill = {services, 1};
    Fill *f = &fill;
    uint8_t format = 0;
    uint32_t cursor, count;
    uint32_t ecx = get(f, VERTRIX_FILL_STATE, STATE_SPARE, DWORD_WIDTH);
    uint32_t value = get(f, VERTRIX_FILL_STATE, STATE_DWORD, DWORD_WIDTH);
    uint32_t bytes, base, width, height, flat, eax;
    uint32_t packed =
        vertrix_pixel_pack((uint8_t)get(f, surface, FIELD_FORMAT, BYTE_WIDTH), colour, &format);
    put(f, VERTRIX_FILL_STATE, STATE_PACKED, DWORD_WIDTH, packed);
    put(f, VERTRIX_FILL_STATE, STATE_FORMAT, BYTE_WIDTH, format);
    bytes = get(f, surface, FIELD_BYTES, BYTE_WIDTH);
    if (bytes == 1)
    {
        value =
            colour + ((colour << BYTE_SHIFT) + ((colour << TOP_SHIFT) + (colour << WORD_SHIFT)));
    }
    else if (bytes == 2)
    {
        value = colour + (colour << WORD_SHIFT);
    }
    else if (bytes == 4)
    {
        value = colour;
    }
    flat = get(f, surface, FIELD_FLAT, DWORD_WIDTH);
    base = get(f, surface, FIELD_PIXELS, DWORD_WIDTH);
    width = get(f, surface, FIELD_WIDTH, DWORD_WIDTH);
    height = get(f, surface, FIELD_HEIGHT, DWORD_WIDTH);
    cursor = base;
    if (flat == 0)
    {
        eax = width * height;
        count = (eax * bytes) >> 2;
        fill_run(f, base, &cursor, count, value);
        count = 0;
    }
    else
    {
        uint32_t rows = height;
        uint32_t pitch = get(f, surface, FIELD_PITCH, DWORD_WIDTH);
        count = (width * bytes) >> 2;
        put(f, VERTRIX_FILL_STATE, STATE_PITCH, DWORD_WIDTH, pitch);
        put(f, VERTRIX_FILL_STATE, STATE_ROWS, DWORD_WIDTH, rows);
        for (; rows != 0 && f->ok; rows--)
        {
            fill_run(f, base, &cursor, count, value);
            cursor += pitch;
            ecx = 0;
            put(f, VERTRIX_FILL_STATE, STATE_ROWS, DWORD_WIDTH, rows - 1);
        }
        eax = 0;
    }
    put(f, VERTRIX_FILL_STATE, STATE_COUNT, DWORD_WIDTH, count);
    put(f, VERTRIX_FILL_STATE, STATE_DWORD, DWORD_WIDTH, value);
    put(f, VERTRIX_FILL_STATE, STATE_POINTER, DWORD_WIDTH, cursor);
    put(f, VERTRIX_FILL_STATE, STATE_SPARE, DWORD_WIDTH, ecx);
    *result = eax;
    return f->ok;
}
