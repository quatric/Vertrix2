#include "object_dwords.h"
#include "actor_storage.h"
#include "object_access.h"

enum
{
    ARM_FLAG = 0x30,
    BYTE_208 = 0x208,
    RANGE_FIRST = 0,
    RANGE_CURRENT = 4,
    RANGE_END = 8,
    RANGE_SHORT = 0xc,
    LIST_POINTER = 4,
    LIST_COUNT = 8,
    WORD_TABLE = 8,
    TIMER_BYTE = 0x178,
    TIMER_WORD = 0x17a,
    TIMER_LIMIT = 0x17c,
    TIMER_FLAG = 0x174,
    FOUR_WORDS = 0x16a,
    STATUS = 0x90,
    STATUS_ABORTED = 0xe002,
    STATUS_FINISHED = 0xe001,
    RESOURCE_VALID = 0x14,
    RESOURCE_TABLE = 8,
    COUNT_RESOURCE = 0xb0,
    COUNT_INDEX = 0xb8,
    COUNT_CACHED = 0xd0,
    LINK_A = 0xd8,
    LINK_B = 0x90,
    LINK_C = 0x1a0,
    LINK_OBJECT = 0x1b8,
    LINKED_FIELDS_COUNT = 4
};

static const size_t linked_fields[LINKED_FIELDS_COUNT] = {0xc, 0x10, 0x18, 0xa4};

int vertrix_object_dword(const void *storage, size_t size, size_t offset, uint32_t *value)
{
    return vertrix_actor_storage_read(storage, size, offset, 4, value);
}

int vertrix_object_set_dword(void *storage, size_t size, size_t offset, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, 4, value);
}

int vertrix_object_set_pair(void *storage, size_t size, size_t first_offset, size_t second_offset,
                            uint32_t first, uint32_t second)
{
    uint32_t probe;
    return vertrix_actor_storage_read(storage, size, second_offset, 4, &probe) &&
           vertrix_actor_storage_write(storage, size, first_offset, 4, first) &&
           vertrix_actor_storage_write(storage, size, second_offset, 4, second);
}

int vertrix_list_empty(const void *storage, size_t size, uint32_t *empty)
{
    uint32_t count;
    if (!vertrix_actor_storage_read(storage, size, LIST_COUNT, 4, &count))
    {
        return 0;
    }
    *empty = count == 0;
    return 1;
}

int vertrix_list_item(const void *storage, size_t size, uint32_t index, VertrixMemoryRead read,
                      void *context, uint32_t *item)
{
    uint32_t count, pointer;
    if (!vertrix_actor_storage_read(storage, size, LIST_COUNT, 4, &count))
    {
        return 0;
    }
    if (index >= count)
    {
        *item = 0;
        return 1;
    }
    return vertrix_actor_storage_read(storage, size, LIST_POINTER, 4, &pointer) &&
           read(pointer + 4 * index, 4, item, context);
}

int vertrix_table_item(const void *storage, size_t size, size_t pointer_offset, uint32_t index,
                       VertrixMemoryRead read, void *context, uint32_t *item)
{
    uint32_t pointer;
    return vertrix_actor_storage_read(storage, size, pointer_offset, 4, &pointer) &&
           read(pointer + 4 * index, 4, item, context);
}

int vertrix_object_zero_dwords(void *storage, size_t size, uint32_t count)
{
    if (!storage || (size_t)count * 4 > size)
    {
        return 0;
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        vertrix_actor_storage_write(storage, size, (size_t)i * 4, 4, 0);
    }
    return 1;
}

int vertrix_object_arm_30(void *storage, size_t size)
{
    uint32_t value;
    if (!vertrix_actor_storage_read(storage, size, ARM_FLAG, 4, &value))
    {
        return 0;
    }
    return value != 0 || vertrix_actor_storage_write(storage, size, ARM_FLAG, 4, 1);
}

int vertrix_object_clear_208(void *storage, size_t size)
{
    return vertrix_actor_storage_write(storage, size, BYTE_208, 1, 0);
}

int vertrix_object_restart_range(void *storage, size_t size)
{
    uint32_t first;
    return vertrix_actor_storage_read(storage, size, RANGE_FIRST, 4, &first) &&
           vertrix_actor_storage_write(storage, size, RANGE_SHORT, 2, 0) &&
           vertrix_actor_storage_write(storage, size, RANGE_END, 4, first);
}

int vertrix_range_done(const void *storage, size_t size, uint32_t *done)
{
    uint32_t current, end;
    if (!vertrix_actor_storage_read(storage, size, RANGE_CURRENT, 4, &current) ||
        !vertrix_actor_storage_read(storage, size, RANGE_END, 4, &end))
    {
        return 0;
    }
    *done = current >= end;
    return 1;
}

int vertrix_object_set_indexed_word(void *storage, size_t size, uint32_t index, uint16_t value)
{
    return vertrix_actor_storage_write(storage, size, WORD_TABLE + 2 * (size_t)(index & 0xff), 2,
                                       value);
}

static int block_pointer(const void *storage, size_t size, uint32_t *pointer)
{
    return vertrix_actor_storage_read(storage, size, RANGE_FIRST, 4, pointer);
}

int vertrix_range_start(void *storage, size_t size, VertrixMemoryRead read, void *context)
{
    uint32_t pointer, first, length, probe;
    if (!block_pointer(storage, size, &pointer) || !read(pointer, 4, &first, context) ||
        !read(pointer + 4, 4, &length, context) ||
        !vertrix_actor_storage_read(storage, size, RANGE_END, 4, &probe))
    {
        return 0;
    }
    return vertrix_actor_storage_write(storage, size, RANGE_CURRENT, 4, first) &&
           vertrix_actor_storage_write(storage, size, RANGE_END, 4, first + length);
}

int vertrix_range_seek(void *storage, size_t size, uint32_t offset, VertrixMemoryRead read,
                       void *context)
{
    uint32_t pointer, first;
    return block_pointer(storage, size, &pointer) && read(pointer, 4, &first, context) &&
           vertrix_actor_storage_write(storage, size, RANGE_CURRENT, 4, first + offset);
}

int vertrix_range_block_second(const void *storage, size_t size, VertrixMemoryRead read,
                               void *context, uint32_t *value)
{
    uint32_t pointer;
    return block_pointer(storage, size, &pointer) && read(pointer + 4, 4, value, context);
}

int vertrix_range_span(const void *storage, size_t size, VertrixMemoryRead read, void *context,
                       uint32_t *length)
{
    uint32_t pointer, first, current;
    if (!block_pointer(storage, size, &pointer) ||
        !vertrix_actor_storage_read(storage, size, RANGE_CURRENT, 4, &current) ||
        !read(pointer, 4, &first, context))
    {
        return 0;
    }
    *length = current - first;
    return 1;
}

int vertrix_timer_reset(void *storage, size_t size, uint8_t value)
{
    uint32_t probe;
    return vertrix_actor_storage_read(storage, size, TIMER_WORD + 1, 1, &probe) &&
           vertrix_actor_storage_write(storage, size, TIMER_WORD, 2, 0) &&
           vertrix_actor_storage_write(storage, size, TIMER_BYTE, 1, value);
}

int vertrix_object_set_word(void *storage, size_t size, size_t offset, uint16_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, 2, value);
}

int vertrix_object_word(const void *storage, size_t size, size_t offset, uint32_t *value)
{
    return vertrix_actor_storage_read(storage, size, offset, 2, value);
}

int vertrix_timer_running(const void *storage, size_t size, uint32_t *running)
{
    uint32_t flag, position, limit;
    if (!vertrix_actor_storage_read(storage, size, TIMER_FLAG, 4, &flag))
    {
        return 0;
    }
    if (flag == 0)
    {
        *running = 1;
        return 1;
    }
    if (!vertrix_actor_storage_read(storage, size, TIMER_WORD, 2, &position) ||
        !vertrix_actor_storage_read(storage, size, TIMER_LIMIT, 2, &limit))
    {
        return 0;
    }
    *running = (int16_t)position <= (int16_t)limit;
    return 1;
}

int vertrix_object_set_four_words(void *storage, size_t size, uint16_t a, uint16_t b, uint16_t c,
                                  uint16_t d)
{
    uint32_t probe;
    return vertrix_actor_storage_read(storage, size, FOUR_WORDS + 6, 2, &probe) &&
           vertrix_actor_storage_write(storage, size, FOUR_WORDS, 2, a) &&
           vertrix_actor_storage_write(storage, size, FOUR_WORDS + 2, 2, b) &&
           vertrix_actor_storage_write(storage, size, FOUR_WORDS + 4, 2, c) &&
           vertrix_actor_storage_write(storage, size, FOUR_WORDS + 6, 2, d);
}

int vertrix_object_reset_triple(void *storage, size_t size, uint32_t first, uint32_t second)
{
    uint32_t probe;
    return vertrix_actor_storage_read(storage, size, RANGE_END, 4, &probe) &&
           vertrix_actor_storage_write(storage, size, RANGE_END, 4, 0) &&
           vertrix_actor_storage_write(storage, size, RANGE_FIRST, 4, first) &&
           vertrix_actor_storage_write(storage, size, RANGE_CURRENT, 4, second);
}

int vertrix_object_status_active(const void *storage, size_t size, uint32_t *active)
{
    uint32_t status;
    if (!vertrix_actor_storage_read(storage, size, STATUS, 4, &status))
    {
        return 0;
    }
    *active = status != 0 && status != STATUS_ABORTED && status != STATUS_FINISHED;
    return 1;
}

int vertrix_scaled_round(int32_t a, int32_t b, int32_t *result)
{
    int32_t numerator = (int32_t)(255u * (2u * (uint32_t)a + 1u) + (uint32_t)b);
    int32_t divisor = (int32_t)(2u * (uint32_t)b);
    if (divisor == 0 || (numerator == INT32_MIN && divisor == -1))
    {
        return 0;
    }
    *result = numerator / divisor;
    return 1;
}

int vertrix_object_release_links(void *storage, size_t size, VertrixObjectStorage resolve,
                                 void *context)
{
    uint32_t linked;
    if (!vertrix_actor_storage_read(storage, size, LINK_OBJECT, 4, &linked) ||
        !vertrix_actor_storage_write(storage, size, LINK_A, 4, 0) ||
        !vertrix_actor_storage_write(storage, size, LINK_B, 4, 0) ||
        !vertrix_actor_storage_write(storage, size, LINK_C, 4, 0))
    {
        return 0;
    }
    for (int i = 0; i < LINKED_FIELDS_COUNT; ++i)
    {
        if (!vertrix_object_write(linked, resolve, context, linked_fields[i], 4, 0))
        {
            return 0;
        }
    }
    return 1;
}

uint32_t vertrix_resource_table_entry(uint32_t resource, uint32_t index, VertrixMemoryRead read,
                                      void *context)
{
    uint32_t valid;
    uint32_t table;
    uint32_t entry;
    if (!read(resource + RESOURCE_VALID, 4, &valid, context) || valid != 1)
    {
        return 0;
    }
    if (!read(resource + RESOURCE_TABLE, 4, &table, context))
    {
        return 0;
    }
    if (!read(table + index * 4, 4, &entry, context))
    {
        return 0;
    }
    return entry;
}

int vertrix_actor_refresh_count(void *actor, size_t size, VertrixMemoryRead read, void *context)
{
    uint32_t resource;
    uint32_t index;
    uint32_t valid;
    if (!vertrix_actor_storage_read(actor, size, COUNT_RESOURCE, 4, &resource))
    {
        return 0;
    }
    if (resource == 0)
    {
        return 1;
    }
    if (!vertrix_actor_storage_read(actor, size, COUNT_INDEX, 4, &index) ||
        !read(resource + RESOURCE_VALID, 4, &valid, context))
    {
        return 0;
    }
    if (valid != 1)
    {
        return 1;
    }
    valid = vertrix_resource_table_entry(resource, index, read, context);
    return vertrix_actor_storage_write(actor, size, COUNT_CACHED, 4, valid);
}

uint32_t vertrix_range_copy(void *source, size_t source_size, void *dest, size_t dest_size,
                            uint32_t factor_a, uint32_t factor_b, VertrixMemoryRead read,
                            void *context, VertrixRangeCopy *cursor)
{
    uint32_t wanted;
    uint32_t pointer;
    uint32_t end;
    uint32_t available;
    uint32_t count;
    uint32_t i;
    uint8_t *to;
    if (!source || !dest || !cursor)
    {
        return 0;
    }
    wanted = factor_a * factor_b;
    if (!vertrix_actor_storage_read(source, source_size, 4, 4, &pointer) ||
        !vertrix_actor_storage_read(source, source_size, 8, 4, &end))
    {
        return 0;
    }
    available = end - pointer;
    cursor->wanted = wanted;
    cursor->available = available;
    if (wanted > available)
    {
        cursor->flag = 0;
        count = available;
    }
    else
    {
        cursor->flag = 1;
        count = wanted;
    }
    if (count == 0)
    {
        cursor->copied = 0;
        return cursor->flag;
    }
    if (count > dest_size)
    {
        return 0;
    }
    to = dest;
    for (i = 0; i < count; ++i)
    {
        uint32_t byte;
        if (!read(pointer + i, 1, &byte, context))
        {
            return 0;
        }
        to[i] = (uint8_t)byte;
    }
    if (!vertrix_actor_storage_write(source, source_size, 4, 4, pointer + count))
    {
        return 0;
    }
    cursor->copied = count;
    return cursor->flag;
}

int vertrix_range_save_copy(void *object, size_t object_size, void *range, size_t range_size,
                            VertrixMemoryRead read, void *context)
{
    enum
    {
        SAVED_FIELD = 0x5bc,
        COPY_DEST = 0x5b8,
        SECOND_COUNT = 0xc
    };
    uint32_t saved;
    uint32_t factor;
    VertrixRangeCopy first;
    VertrixRangeCopy second;
    if (!vertrix_actor_storage_read(object, object_size, SAVED_FIELD, 4, &saved) ||
        object_size < COPY_DEST)
    {
        return 0;
    }
    if (!vertrix_range_start(range, range_size, read, context))
    {
        return 0;
    }
    /* The original ignores both copy results; the flag is data (1 unless
     * wanted exceeds available), not a status. The copies still guard their
     * own writes. */
    vertrix_range_copy(range, range_size, (uint8_t *)object + COPY_DEST, object_size - COPY_DEST, 1,
                       8, read, context, &first);
    if (!vertrix_actor_storage_read(object, object_size, SAVED_FIELD, 4, &factor))
    {
        return 0;
    }
    vertrix_range_copy(range, range_size, object, object_size, factor, SECOND_COUNT, read, context,
                       &second);
    return vertrix_actor_storage_write(object, object_size, SAVED_FIELD, 4, saved);
}

uint32_t vertrix_list_node_alloc(void *object, size_t size, uint32_t value,
                                 VertrixBlockAllocate allocate, VertrixObjectStorage resolve,
                                 void *context)
{
    uint32_t bytes = value * 4;
    uint32_t handle;
    void *storage;
    size_t storage_size;
    uint32_t i;
    if (!vertrix_actor_storage_write(object, size, 4, 4, value))
    {
        return 0;
    }
    handle = allocate(bytes, context);
    if (handle == 0)
    {
        if (!vertrix_actor_storage_write(object, size, 0, 4, 0))
        {
            return 0;
        }
        return 0;
    }
    if (!resolve(handle, &storage, &storage_size, context) || storage_size < bytes)
    {
        return 0;
    }
    for (i = 0; i < bytes; ++i)
    {
        ((uint8_t *)storage)[i] = 0;
    }
    if (!vertrix_actor_storage_write(object, size, 0, 4, handle))
    {
        return 0;
    }
    return handle;
}
