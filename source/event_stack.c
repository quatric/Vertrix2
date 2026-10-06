#include "event_stack.h"
#include "actor_storage.h"

enum
{
    STACK_COUNT = 0x208,
    RECORD_SIZE = 0x34,
    /* Field offsets inside one record. */
    F_B00 = 0x00,
    F_B01 = 0x01,
    F_D04 = 0x04,
    F_B08 = 0x08,
    F_D0C = 0x0c,
    F_D10 = 0x10,
    F_B14 = 0x14,
    F_D18 = 0x18,
    F_D1C = 0x1c,
    F_W20 = 0x20,
    F_W22 = 0x22,
    F_D24 = 0x24,
    F_D28 = 0x28,
    F_D2C = 0x2c
};

static int read_count(const void *storage, size_t size, uint32_t *count)
{
    return vertrix_actor_storage_read(storage, size, STACK_COUNT, 1, count);
}

/* True when the whole record at the given index lies inside the storage. */
static int record_fits(size_t size, uint32_t index)
{
    return (size_t)index * RECORD_SIZE + RECORD_SIZE <= size;
}

static int write_record(void *storage, size_t size, uint32_t index, const VertrixEventRecord *r)
{
    size_t base = (size_t)index * RECORD_SIZE;
    if (!record_fits(size, index))
    {
        return 0;
    }
    vertrix_actor_storage_write(storage, size, base + F_B01, 1, r->b01);
    vertrix_actor_storage_write(storage, size, base + F_D04, 4, r->d04);
    vertrix_actor_storage_write(storage, size, base + F_B00, 1, r->b00);
    vertrix_actor_storage_write(storage, size, base + F_B08, 1, r->b08);
    vertrix_actor_storage_write(storage, size, base + F_D0C, 4, r->d0c);
    vertrix_actor_storage_write(storage, size, base + F_D10, 4, r->d10);
    vertrix_actor_storage_write(storage, size, base + F_B14, 1, r->b14);
    vertrix_actor_storage_write(storage, size, base + F_D2C, 4, r->d2c);
    vertrix_actor_storage_write(storage, size, base + F_D18, 4, r->d18);
    vertrix_actor_storage_write(storage, size, base + F_D1C, 4, r->d1c);
    vertrix_actor_storage_write(storage, size, base + F_W20, 2, r->w20);
    vertrix_actor_storage_write(storage, size, base + F_W22, 2, r->w22);
    vertrix_actor_storage_write(storage, size, base + F_D24, 4, r->d24);
    vertrix_actor_storage_write(storage, size, base + F_D28, 4, r->d28);
    return 1;
}

int vertrix_event_stack_push(void *storage, size_t size, const VertrixEventRecord *record)
{
    uint32_t count;
    if (!read_count(storage, size, &count) || count >= VERTRIX_EVENT_STACK_CAPACITY)
    {
        return 0;
    }
    count++;
    if (!record_fits(size, count))
    {
        return 0;
    }
    vertrix_actor_storage_write(storage, size, STACK_COUNT, 1, count);
    return write_record(storage, size, count, record);
}

static void load_byte(const void *storage, size_t size, size_t offset, uint8_t *out)
{
    uint32_t value;
    if (out)
    {
        vertrix_actor_storage_read(storage, size, offset, 1, &value);
        *out = (uint8_t)value;
    }
}

static void load_word(const void *storage, size_t size, size_t offset, uint16_t *out)
{
    uint32_t value;
    if (out)
    {
        vertrix_actor_storage_read(storage, size, offset, 2, &value);
        *out = (uint16_t)value;
    }
}

static void load_dword(const void *storage, size_t size, size_t offset, uint32_t *out)
{
    if (out)
    {
        vertrix_actor_storage_read(storage, size, offset, 4, out);
    }
}

int vertrix_event_stack_pop(void *storage, size_t size, const VertrixEventPopRefs *refs)
{
    uint32_t count;
    if (!read_count(storage, size, &count) || count == 0 || !record_fits(size, count))
    {
        return 0;
    }
    size_t base = (size_t)count * RECORD_SIZE;
    load_byte(storage, size, base + F_B01, refs->b01);
    load_dword(storage, size, base + F_D04, refs->d04);
    load_byte(storage, size, base + F_B08, refs->b08);
    load_dword(storage, size, base + F_D0C, refs->d0c);
    load_dword(storage, size, base + F_D10, refs->d10);
    load_byte(storage, size, base + F_B14, refs->b14);
    load_dword(storage, size, base + F_D2C, refs->d2c);
    load_dword(storage, size, base + F_D18, refs->d18);
    load_dword(storage, size, base + F_D1C, refs->d1c);
    load_word(storage, size, base + F_W20, refs->w20);
    load_word(storage, size, base + F_W22, refs->w22);
    load_dword(storage, size, base + F_D24, refs->d24);
    load_dword(storage, size, base + F_D28, refs->d28);
    load_byte(storage, size, base + F_B00, refs->b00);
    vertrix_actor_storage_write(storage, size, STACK_COUNT, 1, (count - 1) & 0xff);
    return 1;
}

int vertrix_event_stack_replace_top(void *storage, size_t size, const VertrixEventTopRefs *refs)
{
    uint32_t count;
    if (!read_count(storage, size, &count) || !record_fits(size, count))
    {
        return 0;
    }
    size_t base = (size_t)count * RECORD_SIZE;
    if (refs->b00)
    {
        vertrix_actor_storage_write(storage, size, base + F_B00, 1, *refs->b00);
    }
    if (refs->b01)
    {
        vertrix_actor_storage_write(storage, size, base + F_B01, 1, *refs->b01);
    }
    if (refs->d04)
    {
        vertrix_actor_storage_write(storage, size, base + F_D04, 4, *refs->d04);
    }
    if (refs->b08)
    {
        vertrix_actor_storage_write(storage, size, base + F_B08, 1, *refs->b08);
    }
    if (refs->d0c)
    {
        vertrix_actor_storage_write(storage, size, base + F_D0C, 4, *refs->d0c);
    }
    if (refs->d10)
    {
        vertrix_actor_storage_write(storage, size, base + F_D10, 4, *refs->d10);
    }
    if (refs->b14)
    {
        vertrix_actor_storage_write(storage, size, base + F_B14, 1, *refs->b14);
    }
    if (refs->d2c)
    {
        vertrix_actor_storage_write(storage, size, base + F_D2C, 4, *refs->d2c);
    }
    if (refs->d18)
    {
        vertrix_actor_storage_write(storage, size, base + F_D18, 4, *refs->d18);
    }
    if (refs->d1c)
    {
        vertrix_actor_storage_write(storage, size, base + F_D1C, 4, *refs->d1c);
    }
    if (refs->w20)
    {
        vertrix_actor_storage_write(storage, size, base + F_W20, 2, *refs->w20);
    }
    if (refs->w22)
    {
        vertrix_actor_storage_write(storage, size, base + F_W22, 2, *refs->w22);
    }
    if (refs->d24)
    {
        vertrix_actor_storage_write(storage, size, base + F_D24, 4, *refs->d24);
    }
    if (refs->d28)
    {
        vertrix_actor_storage_write(storage, size, base + F_D28, 4, *refs->d28);
    }
    return 1;
}

int vertrix_event_stack_empty(const void *storage, size_t size, uint32_t *empty)
{
    uint32_t count;
    if (!empty || !read_count(storage, size, &count))
    {
        return 0;
    }
    *empty = count == 0;
    return 1;
}

int vertrix_event_key_index(void *event, size_t size, uint32_t key)
{
    static const uint8_t codes[] = {8, 0xf, 0x10, 0x18, 0x20};
    uint32_t index;
    uint8_t code = (uint8_t)key;
    for (index = 0; index < sizeof(codes); ++index)
    {
        if (code == codes[index])
        {
            return vertrix_actor_storage_write(event, size, 0xd, 1, index);
        }
    }
    return event != NULL;
}

int vertrix_event_scale_fields(void *event, size_t size)
{
    uint32_t base;
    uint32_t mult;
    uint32_t limit;
    uint32_t scaled;
    uint32_t diff;
    if (!vertrix_actor_storage_read(event, size, 4, 4, &base) ||
        !vertrix_actor_storage_read(event, size, 0xc, 1, &mult) ||
        !vertrix_actor_storage_read(event, size, 0x14, 4, &limit))
    {
        return 0;
    }
    scaled = base * mult;
    diff = limit - scaled;
    if (!vertrix_actor_storage_write(event, size, 0x18, 4, diff) ||
        !vertrix_actor_storage_write(event, size, 0x10, 4, diff != 0))
    {
        return 0;
    }
    return diff != 0;
}
