#include "array_list.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    BUILD_ALLOCATE = 0x4ec160,
    BUILD_ELEMENT_SIZE = 4,
    LIST_ARRAY = 0x0,
    LIST_COUNT = 0x4,
    LIST_BUFFER_A = 0x8,
    LIST_BUFFER_B = 0xc,
    LIST_BUFFER_C = 0x10,
    LIST_MODE = 0x14,
    FREE_CALL = 0x4ea190,
    ITEM_RELEASE_CALL = 0x4830f0,
    ITEM_VISIT_CALL = 0x483790,
    MAKE_CALL = 0x483060,
    BYTE_MASK = 0xff
};

static int read_dword(const VertrixFactoryServices *services, uint32_t handle, uint32_t offset,
                      uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(handle, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, value);
}

static int write_dword(const VertrixFactoryServices *services, uint32_t handle, uint32_t offset,
                       uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(handle, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, value);
}

static int release_buffers(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           uint32_t object, uint32_t edx, uint32_t *eax)
{
    static const uint32_t fields[3] = {LIST_BUFFER_A, LIST_BUFFER_B, LIST_BUFFER_C};
    uint32_t first;
    if (!read_dword(services, object, LIST_BUFFER_A, &first))
    {
        return 0;
    }
    for (int i = 0; i < 3; ++i)
    {
        uint32_t buffer;
        if (!read_dword(services, object, fields[i], &buffer))
        {
            return 0;
        }
        if (buffer != 0)
        {
            *eax = vertrix_call(calls, FREE_CALL, buffer, edx, object, first, 0);
            if (i < 2 && !write_dword(services, object, fields[i], 0))
            {
                return 0;
            }
        }
    }
    return write_dword(services, object, LIST_BUFFER_C, 0) &&
           write_dword(services, object, LIST_MODE, 0) &&
           write_dword(services, object, LIST_COUNT, 0);
}

uint32_t vertrix_array_list_release(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t object,
                                    uint32_t edx)
{
    uint32_t mode, array, count, eax = object;
    if (!read_dword(services, object, LIST_MODE, &mode))
    {
        return 0;
    }
    if (mode != 0)
    {
        return release_buffers(calls, services, object, edx, &eax) ? eax : 0;
    }
    if (!read_dword(services, object, LIST_ARRAY, &array) ||
        !read_dword(services, object, LIST_COUNT, &count))
    {
        return 0;
    }
    if (array != 0)
    {
        uint32_t offset = 0;
        uint32_t index = 0;
        while (index < count)
        {
            uint32_t item;
            if (!read_dword(services, array, offset, &item))
            {
                return 0;
            }
            ++index;
            vertrix_call(calls, ITEM_RELEASE_CALL, item, offset, object, index, 0);
            if (!read_dword(services, object, LIST_COUNT, &count))
            {
                return 0;
            }
            offset += DWORD_WIDTH;
        }
        eax = vertrix_call(calls, FREE_CALL, array, offset, object, index, 0);
        if (!write_dword(services, object, LIST_ARRAY, 0))
        {
            return 0;
        }
    }
    return write_dword(services, object, LIST_COUNT, 0) ? eax : 0;
}

uint32_t vertrix_array_list_each(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, uint32_t argument)
{
    uint32_t array, count, eax = object;
    if (!read_dword(services, object, LIST_ARRAY, &array) || array == 0 ||
        !read_dword(services, object, LIST_COUNT, &count))
    {
        return array == 0 ? object : 0;
    }
    for (uint32_t index = 0, offset = 0; index < count;)
    {
        uint32_t item;
        if (!read_dword(services, array, offset, &item))
        {
            return 0;
        }
        if (item != 0)
        {
            vertrix_call(calls, ITEM_VISIT_CALL, item, argument, offset, index, 0);
        }
        ++index;
        if (!read_dword(services, object, LIST_COUNT, &count))
        {
            return 0;
        }
        eax = count;
        offset += DWORD_WIDTH;
    }
    return eax;
}

uint32_t vertrix_array_list_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, uint32_t index, uint32_t ebx_in, uint32_t ecx_in,
                                 const uint32_t arguments[VERTRIX_SLOT_MAKE_ARGUMENTS])
{
    uint32_t array, entry;
    uint32_t stack[8] = {arguments[2],
                         arguments[3],
                         arguments[4],
                         arguments[5],
                         arguments[6] & BYTE_MASK,
                         (uint32_t)(int32_t)(int8_t)arguments[7],
                         (uint32_t)(int32_t)(int8_t)arguments[8],
                         arguments[9] & BYTE_MASK};
    if (!read_dword(services, object, LIST_ARRAY, &array) ||
        !write_dword(services, array, DWORD_WIDTH * index, 0))
    {
        return 0;
    }
    entry =
        vertrix_calln(calls, MAKE_CALL, ebx_in, ecx_in, arguments[0], arguments[1], stack, 8, NULL);
    if (!read_dword(services, object, LIST_ARRAY, &array))
    {
        return 0;
    }
    return write_dword(services, array, DWORD_WIDTH * index, entry) ? entry : 0;
}

uint32_t vertrix_array_list_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t count, uint32_t ebx_in, uint32_t ecx_in,
                                  const uint32_t arguments[VERTRIX_SLOT_MAKE_ARGUMENTS])
{
    uint32_t result;
    if (!write_dword(services, object, LIST_COUNT, count))
    {
        return 0;
    }
    result = vertrix_call(calls, BUILD_ALLOCATE, count, BUILD_ELEMENT_SIZE, ebx_in, ecx_in, 0);
    if (!write_dword(services, object, LIST_ARRAY, result))
    {
        return 0;
    }
    for (uint32_t index = 0; index < count; index++)
    {
        result = vertrix_array_list_make(calls, services, object, index, ebx_in, ecx_in, arguments);
    }
    return result;
}
