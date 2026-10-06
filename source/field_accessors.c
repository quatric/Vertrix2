#include "field_accessors.h"
#include "actor_storage.h"

enum
{
    FLIP = 0x454,
    VALUE_464 = 0x464,
    VALUE_174 = 0x174,
    VALUE_178 = 0x178,
    CLEAR_COUNT = 7,
    FLAG_BYTE = 0,
    IDLE_BYTE = 0x5a,
    PROGRESS_3C = 0x3c,
    PROGRESS_40 = 0x40,
    PROGRESS_DONE = 0x44,
    PROGRESS_TOTAL = 0x48,
    STREAM_CLASS = 0x14,
    STREAM_FLAG = 4,
    STREAM_VALUE = 0,
    STREAM_CLASS_TOKEN = 0x516744,
    STREAM_BASE_CLASS = 0xc,
    STREAM_BASE_TOKEN = 0x5167a4,
    RECT_A = 0x3c,
    RECT_B = 0x3e,
    RECT_C = 0x40,
    RECT_D = 0x42,
    COMMIT_FROM = 0x48,
    COMMIT_TO = 0x4c,
    SURFACE_PITCH = 0x14
};

static int read(const void *storage, size_t size, size_t offset, unsigned width, uint32_t *value)
{
    return vertrix_actor_storage_read(storage, size, offset, width, value);
}

static int write(void *storage, size_t size, size_t offset, unsigned width, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, width, value);
}

int vertrix_object_flip_454(void *storage, size_t size)
{
    uint32_t value;
    return read(storage, size, FLIP, 4, &value) && write(storage, size, FLIP, 4, 1u - value);
}

int vertrix_object_set_464(void *storage, size_t size, uint32_t value)
{
    return write(storage, size, VALUE_464, 4, value);
}

int vertrix_object_get_464(const void *storage, size_t size, uint32_t *value)
{
    return read(storage, size, VALUE_464, 4, value);
}

int vertrix_object_get_174(const void *storage, size_t size, uint32_t *value)
{
    return read(storage, size, VALUE_174, 4, value);
}

int vertrix_object_get_178(const void *storage, size_t size, uint32_t *value)
{
    return read(storage, size, VALUE_178, 4, value);
}

void vertrix_global_index_bytes(uint8_t bytes[7])
{
    for (int i = 0; i < CLEAR_COUNT; ++i)
    {
        bytes[i] = (uint8_t)i;
    }
}

int vertrix_flags_clear(void *storage, size_t size)
{
    return write(storage, size, FLAG_BYTE, 1, 0);
}

int vertrix_flags_set(void *storage, size_t size)
{
    return write(storage, size, FLAG_BYTE, 1, 1);
}

int vertrix_flags_get(const void *storage, size_t size, uint32_t *value)
{
    return read(storage, size, FLAG_BYTE, 1, value);
}

int vertrix_flags_dword(const void *storage, size_t size, unsigned index, uint32_t *value)
{
    return index >= 1 && index <= 3 && read(storage, size, 4 * (size_t)index, 4, value);
}

int vertrix_flags_idle(const void *storage, size_t size, uint32_t *idle)
{
    uint32_t value;
    if (!read(storage, size, IDLE_BYTE, 1, &value))
    {
        return 0;
    }
    *idle = value == 0;
    return 1;
}

int vertrix_progress_set_40(void *storage, size_t size, uint32_t value)
{
    return write(storage, size, PROGRESS_40, 4, value);
}

int vertrix_progress_set_3c(void *storage, size_t size, uint32_t value)
{
    return write(storage, size, PROGRESS_3C, 4, value);
}

int vertrix_progress_done(const void *storage, size_t size, uint32_t *done)
{
    uint32_t progress, total;
    if (!read(storage, size, PROGRESS_DONE, 4, &progress) ||
        !read(storage, size, PROGRESS_TOTAL, 4, &total))
    {
        return 0;
    }
    *done = progress >= total;
    return 1;
}

int vertrix_progress_quotient(const void *storage, size_t size, uint32_t *quotient)
{
    uint32_t progress, total;
    if (!read(storage, size, PROGRESS_DONE, 4, &progress) ||
        !read(storage, size, PROGRESS_TOTAL, 4, &total))
    {
        return 0;
    }
    *quotient = progress / (total ? total : 1);
    return 1;
}

int vertrix_stream_init(void *storage, size_t size)
{
    uint32_t probe;
    return read(storage, size, STREAM_CLASS, 4, &probe) &&
           write(storage, size, STREAM_CLASS, 4, STREAM_CLASS_TOKEN) &&
           write(storage, size, STREAM_FLAG, 1, 0) && write(storage, size, STREAM_VALUE, 4, 0);
}

int vertrix_stream_set_class(void *storage, size_t size)
{
    return write(storage, size, STREAM_BASE_CLASS, 4, STREAM_BASE_TOKEN);
}

int vertrix_rect_set(void *storage, size_t size, uint16_t a, uint16_t b, uint16_t c, uint16_t d)
{
    uint32_t probe;
    return read(storage, size, RECT_D, 2, &probe) && write(storage, size, RECT_A, 2, a) &&
           write(storage, size, RECT_B, 2, b) && write(storage, size, RECT_C, 2, c) &&
           write(storage, size, RECT_D, 2, d);
}

int vertrix_rect_commit(void *storage, size_t size)
{
    uint32_t first, second;
    return read(storage, size, COMMIT_FROM, 2, &first) &&
           read(storage, size, COMMIT_FROM + 2, 2, &second) &&
           write(storage, size, COMMIT_TO, 2, first) &&
           write(storage, size, COMMIT_TO + 2, 2, second);
}

int vertrix_surface_cell_address(const void *storage, size_t size, uint32_t row, uint32_t column,
                                 uint32_t *address)
{
    uint32_t base, pitch;
    if (!read(storage, size, 0, 4, &base) || !read(storage, size, SURFACE_PITCH, 4, &pitch))
    {
        return 0;
    }
    *address = row * pitch + base + column * 4;
    return 1;
}

int vertrix_dword_set(const void *storage, size_t size, uint32_t *set)
{
    uint32_t value;
    if (!read(storage, size, 0, 4, &value))
    {
        return 0;
    }
    *set = value != 0;
    return 1;
}
