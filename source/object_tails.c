#include "object_tails.h"
#include "actor_storage.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    MODE_DECREMENT = 0,
    MODE_INCREMENT = 1
};

uint32_t vertrix_slot_toggle(const VertrixCalls *calls, uint32_t *flag)
{
    if (vertrix_call(calls, 0x476480, VERTRIX_CALL_POINT_LIST, VERTRIX_TAIL_SLOT_FLAG, 0, 0, 0) ==
        0)
    {
        return 0;
    }
    vertrix_call(calls, 0x4762e0, VERTRIX_CALL_POINT_LIST, VERTRIX_TAIL_SLOT_FLAG, 0, 0, 0);
    *flag = 1 - *flag;
    return *flag;
}

uint32_t vertrix_slot_table_init(const VertrixCalls *calls, uint32_t table)
{
    for (uint32_t i = 0; i < 256; ++i)
    {
        vertrix_call(calls, 0x475a20, table + 0x60 * i, i + 1, 0, table, 0);
    }
    return 256;
}

uint32_t vertrix_call_unless_zero(const VertrixCalls *calls, uint32_t eax)
{
    if (eax == 0)
    {
        return 0;
    }
    return vertrix_call(calls, 0x4b8170, eax, 0, 0, 0, 0);
}

uint32_t vertrix_object_table_517644(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax,
                                     uint32_t edx)
{
    void *storage;
    size_t size;
    uint32_t object = vertrix_call(calls, 0x4b78d0, eax, edx, 0, 0, 0);
    if (!services->resolve(object, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, VERTRIX_TAIL_TABLE_FIELD, DWORD_WIDTH,
                                     VERTRIX_TAIL_TABLE_517644))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_object_step_text_length(const VertrixCalls *calls, uint32_t object, void *storage,
                                         size_t size, uint32_t mode)
{
    uint32_t length;
    uint32_t next = UINT32_MAX;
    if (mode == MODE_DECREMENT || mode == MODE_INCREMENT)
    {
        if (!vertrix_actor_storage_read(storage, size, VERTRIX_TAIL_TEXT_LENGTH, DWORD_WIDTH,
                                        &length))
        {
            return 0;
        }
        next = mode == MODE_DECREMENT ? length - 1 : length + 1;
    }
    if (!vertrix_actor_storage_write(storage, size, VERTRIX_TAIL_TEXT_LENGTH, DWORD_WIDTH, next))
    {
        return 0;
    }
    return vertrix_call(calls, 0x4b4690, object, 0, 0, 0, 0);
}

uint32_t vertrix_object_slot_present(const VertrixCalls *calls, const void *storage, size_t size,
                                     size_t field, uint32_t object)
{
    uint32_t id;
    if (!vertrix_actor_storage_read(storage, size, field, WORD_WIDTH, &id) || id == 0)
    {
        return 0;
    }
    if (vertrix_call(calls, 0x476480, VERTRIX_CALL_POINT_LIST, id, 0, object, 0) != 1)
    {
        return 0;
    }
    vertrix_call(calls, 0x4762e0, VERTRIX_CALL_POINT_LIST, id, 1, object, 0);
    return 1;
}

int vertrix_object_clear_block(void *storage, size_t size)
{
    for (size_t offset = 0; offset < VERTRIX_TAIL_BLOCK_BYTES; ++offset)
    {
        if (!vertrix_actor_storage_write(storage, size, offset, BYTE_WIDTH, 0))
        {
            return 0;
        }
    }
    for (size_t offset = VERTRIX_TAIL_BLOCK_BYTES; offset <= VERTRIX_TAIL_BLOCK_END;
         offset += DWORD_WIDTH)
    {
        if (!vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, 0))
        {
            return 0;
        }
    }
    return 1;
}

uint32_t vertrix_forward_a2f0(const VertrixCalls *calls, uint32_t eax, uint32_t edx)
{
    return vertrix_call(calls, 0x4b7a80, eax, edx, 0, 0, 0);
}

uint32_t vertrix_list_notify_pair(const VertrixCalls *calls, uint32_t eax, uint32_t ebx)
{
    uint32_t hit = vertrix_call(calls, 0x4b5eb0, 0x54671c, 0x15, ebx, eax, 0);
    if (hit != 0)
    {
        ebx = hit;
        vertrix_call(calls, 0x4123d0, eax, 0, ebx, eax, 0);
    }
    hit = vertrix_call(calls, 0x4b5eb0, 0x54671c, 0x16, ebx, eax, 0);
    if (hit == 0)
    {
        return 0;
    }
    return vertrix_call(calls, 0x4123d0, eax, 0, hit, eax, 0);
}

uint32_t vertrix_list_clear_hit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t ebx, uint32_t ecx)
{
    void *storage;
    size_t size;
    uint32_t hit = vertrix_call(calls, 0x4b5eb0, 0x546744, 0x190, ebx, ecx, 0);
    if (hit == 0)
    {
        return 0;
    }
    if (!services->resolve(hit, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, 0x94c, DWORD_WIDTH, 0))
    {
        return 0;
    }
    return hit;
}

uint32_t vertrix_object_table_516d34(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t eax)
{
    void *storage;
    size_t size;
    uint32_t object = vertrix_call(calls, 0x481b20, eax + 0x10, 0, 0, 0, 0) - 0x10;
    if (!services->resolve(object, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, 0x70, DWORD_WIDTH, 0x516d34))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_object_clear_with_table(void *storage, size_t size, uint32_t object)
{
    if (!vertrix_actor_storage_write(storage, size, 0x34, DWORD_WIDTH, 0x517a44) ||
        !vertrix_object_clear_block(storage, size))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_object_clear_with_ones(void *storage, size_t size, uint32_t object)
{
    if (!vertrix_object_clear_block(storage, size) ||
        !vertrix_actor_storage_write(storage, size, 0x20, DWORD_WIDTH, 1) ||
        !vertrix_actor_storage_write(storage, size, 0x2c, DWORD_WIDTH, 1))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_object_text_length_reset(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t object,
                                          void *storage, size_t size)
{
    uint32_t length;
    if (!vertrix_object_text_length(services, storage, size, &length) ||
        !vertrix_actor_storage_write(storage, size, VERTRIX_TAIL_TEXT_LENGTH, DWORD_WIDTH,
                                     length - 1))
    {
        return 0;
    }
    return vertrix_call(calls, 0x4b4690, object, object, 0, length - 1, 0);
}

uint32_t vertrix_object_slot_present_unowned(const VertrixCalls *calls, const void *storage,
                                             size_t size, uint32_t object)
{
    uint32_t id;
    uint32_t owner;
    if (!vertrix_actor_storage_read(storage, size, VERTRIX_TAIL_SLOT_ID, WORD_WIDTH, &id) ||
        id == 0)
    {
        return 0;
    }
    if (vertrix_call(calls, 0x476480, VERTRIX_CALL_POINT_LIST, id, 0, object, 0) != 1)
    {
        return 0;
    }
    if (!vertrix_actor_storage_read(storage, size, 0x160, DWORD_WIDTH, &owner))
    {
        return 0;
    }
    if (owner == 0)
    {
        vertrix_call(calls, 0x4762e0, VERTRIX_CALL_POINT_LIST, id, 0, object, 0);
    }
    return 1;
}

uint32_t vertrix_object_release_items(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, const void *storage,
                                      size_t size)
{
    uint32_t count;
    uint32_t array;
    uint32_t result = 0;
    if (!vertrix_actor_storage_read(storage, size, 8, DWORD_WIDTH, &count))
    {
        return 0;
    }
    result = count;
    for (uint32_t i = 0; i < count; ++i)
    {
        void *array_storage;
        size_t array_size;
        void *item_storage;
        size_t item_size;
        uint32_t item;
        uint32_t held;
        if (!vertrix_actor_storage_read(storage, size, 4, DWORD_WIDTH, &array) ||
            !services->resolve(array, &array_storage, &array_size, services->context) ||
            !vertrix_actor_storage_read(array_storage, array_size, 4 * (size_t)i, DWORD_WIDTH,
                                        &item) ||
            !services->resolve(item, &item_storage, &item_size, services->context) ||
            !vertrix_actor_storage_read(item_storage, item_size, 0xb4, DWORD_WIDTH, &held))
        {
            return 0;
        }
        result = held;
        if (held != 0)
        {
            result = vertrix_call(calls, 0x4830f0, held, item, 4 * i, i, 0);
            if (!vertrix_actor_storage_write(item_storage, item_size, 0xb4, DWORD_WIDTH, 0))
            {
                return 0;
            }
        }
    }
    return result;
}
