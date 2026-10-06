#include "device_glue.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    SEH_EDX = 0x4ec1ec,
    RELEASE = 0x4ea190,
    RELEASE_FIRST = 0x54b804,
    RELEASE_SECOND = 0x54b800,
    RELEASE_ECX = 0x51646c,
    DESTROY_VTABLE_FIELD = 0x18,
    DESTROY_VTABLE = 0x5165c4,
    DESTROY_FREE = 0x4ca050,
    DESTROY_BASE = 0x4ccb9f,
    DESTROY_BASE_EDX = 0x516630,
    DESTROY_RELEASE = 0x4ca040,
    QUEUE_OFFSET = 0x20,
    QUEUE_COUNT = 0x2c,
    QUEUE_POP = 0x4d8540,
    QUEUE_VTABLE = 0x18,
    QUEUE_WORD = 0x10,
    QUEUE_DWORD = 0x14,
    QUEUE_DELETE_EDX = 2,
    STRING_EMPTY = 0x4ca060,
    STRING_ASSIGN = 0x4ca370,
    STRING_TABLE = 0x4fd800,
    STRING_STRIDE = 12,
    STRING_ECX = 0x516500,
    STRING_EMPTY_ADDRESS = 0x50081c,
    ENTRY_CALL = 0x4cea15,
    ENTRY_SIZE = 0x100,
    ENTRY_EBX = 0x516650,
    DEVICE_FLAG = 0xc,
    DEVICE_INTERFACE = 0x30,
    METHOD_ACQUIRE = 0x1c,
    METHOD_UNACQUIRE = 0x20,
    METHOD_FORMAT = 0x18,
    IMPORT_SET_CURSOR = 0x4f1a9c,
    IMPORT_SHOW_CURSOR = 0x4f1ae4,
    FORMAT_ECX = 0x14,
    FORMAT_SECOND = 0x10,
    FORMAT_ARGUMENTS = 8
};

static int read_value(const VertrixFactoryServices *services, uint32_t handle, uint32_t offset,
                      unsigned width, uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(handle, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, width, value);
}

int vertrix_release_pair(const VertrixCalls *calls, const VertrixGlobals *globals)
{
    vertrix_call(calls, RELEASE, globals->read(RELEASE_FIRST, globals->context), SEH_EDX, 0,
                 RELEASE_ECX, 0);
    vertrix_call(calls, RELEASE, globals->read(RELEASE_SECOND, globals->context), SEH_EDX, 0,
                 RELEASE_ECX, 0);
    return 1;
}

uint32_t vertrix_object_destroy_flags(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t object,
                                      uint32_t edx, uint32_t ebx)
{
    uint32_t result;
    if ((edx & 4) == 0)
    {
        if (!vertrix_build_store(services, object, DESTROY_VTABLE_FIELD, DWORD_WIDTH,
                                 DESTROY_VTABLE))
        {
            return 0;
        }
        if ((edx & 2) != 0)
        {
            vertrix_call(calls, DESTROY_FREE, object, edx, SEH_EDX, object, 0);
        }
        return object;
    }
    result = vertrix_call(calls, DESTROY_BASE, object, DESTROY_BASE_EDX, ebx, object, 0);
    vertrix_call(calls, DESTROY_RELEASE, result, 0, ebx, object, 0);
    return object;
}

static uint32_t pop(const VertrixCalls *calls, const VertrixFactoryServices *services,
                    uint32_t object, uint32_t edx, uint32_t ebx, uint32_t *entry)
{
    uint32_t queue = object + QUEUE_OFFSET;
    uint32_t count = 0;
    VertrixCallSite site = {QUEUE_POP, queue, edx, ebx, queue, 0, 0, 0, 0, 0, {0}, 0};
    *entry = calls->call(&site, calls->context);
    count = site.out_value;
    return vertrix_build_store(services, object, QUEUE_COUNT, DWORD_WIDTH, count);
}

uint32_t vertrix_queue_drain(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, uint32_t object, uint32_t edx,
                             uint32_t ebx)
{
    uint32_t count;
    uint32_t entry;
    uint32_t result = object;
    uint32_t queue = object + QUEUE_OFFSET;
    if (!read_value(services, object, QUEUE_COUNT, DWORD_WIDTH, &count))
    {
        return 0;
    }
    while (count != 0)
    {
        if (!pop(calls, services, object, edx, ebx, &entry))
        {
            return 0;
        }
        if (entry == 0)
        {
            result = 0;
        }
        else
        {
            uint32_t table;
            if (!read_value(services, entry, QUEUE_VTABLE, DWORD_WIDTH, &table))
            {
                return 0;
            }
            ebx = table;
            edx = QUEUE_DELETE_EDX;
            result = vertrix_call(calls, globals->read(table, globals->context), entry, edx, ebx,
                                  queue, 0);
        }
        if (!read_value(services, object, QUEUE_COUNT, DWORD_WIDTH, &count))
        {
            return 0;
        }
    }
    return result;
}

uint32_t vertrix_queue_next(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, uint32_t object, uint32_t edx)
{
    uint32_t count;
    uint32_t entry;
    uint32_t result = 0;
    uint32_t table;
    uint32_t value;
    if (edx != 0 && !vertrix_build_store(services, edx, 0, DWORD_WIDTH, 0))
    {
        return 0;
    }
    if (!read_value(services, object, QUEUE_COUNT, DWORD_WIDTH, &count))
    {
        return 0;
    }
    if (count == 0)
    {
        return 0;
    }
    if (!pop(calls, services, object, edx, 0, &entry) ||
        !read_value(services, entry, QUEUE_WORD, WORD_WIDTH, &result))
    {
        return 0;
    }
    if (edx != 0)
    {
        if (!read_value(services, entry, QUEUE_DWORD, DWORD_WIDTH, &value) ||
            !vertrix_build_store(services, edx, 0, DWORD_WIDTH, value))
        {
            return 0;
        }
    }
    if (entry != 0)
    {
        if (!read_value(services, entry, QUEUE_VTABLE, DWORD_WIDTH, &table))
        {
            return 0;
        }
        vertrix_call(calls, globals->read(table, globals->context), entry, QUEUE_DELETE_EDX, result,
                     entry, 0);
    }
    return result;
}

uint32_t vertrix_string_table_assign(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, uint32_t ebx, uint32_t edx)
{
    uint32_t index = ebx & 0xffff;
    uint32_t entry = STRING_TABLE + index * STRING_STRIDE;
    uint32_t empty =
        vertrix_call(calls, STRING_EMPTY, index * STRING_STRIDE, SEH_EDX, entry, STRING_ECX, 0);
    if (!vertrix_build_store(services, edx, 0, DWORD_WIDTH, globals->read(empty, globals->context)))
    {
        return 0;
    }
    vertrix_call(calls, STRING_ASSIGN, edx, entry, entry, STRING_ECX, 0);
    return edx;
}

uint32_t vertrix_resource_entry_256(const VertrixCalls *calls, uint32_t object)
{
    return vertrix_call(calls, ENTRY_CALL, object, ENTRY_SIZE, ENTRY_EBX, object, 0);
}

uint32_t vertrix_cursor_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, uint32_t object, uint32_t ecx)
{
    uint32_t iface;
    uint32_t table;
    uint32_t result;
    uint32_t edx;
    uint32_t eax;
    if (!read_value(services, object, DEVICE_INTERFACE, DWORD_WIDTH, &iface))
    {
        return 0;
    }
    if (iface == 0)
    {
        vertrix_build_store(services, object, DEVICE_FLAG, DWORD_WIDTH, 0);
        return 0;
    }
    if (!read_value(services, iface, 0, DWORD_WIDTH, &table))
    {
        return 0;
    }
    edx = table;
    vertrix_calln(calls, globals->read(table + METHOD_ACQUIRE, globals->context), iface, edx,
                  object, ecx, &iface, 1, NULL);
    if (!read_value(services, object, DEVICE_INTERFACE, DWORD_WIDTH, &iface) ||
        !read_value(services, iface, 0, DWORD_WIDTH, &table))
    {
        return 0;
    }
    edx = table;
    result = vertrix_calln(calls, globals->read(table + METHOD_ACQUIRE, globals->context), iface,
                           edx, object, ecx, &iface, 1, NULL);
    if (result != 0)
    {
        vertrix_build_store(services, object, DEVICE_FLAG, DWORD_WIDTH, 0);
        return 0;
    }
    {
        uint32_t zero = 0;
        eax = vertrix_calln(calls, IMPORT_SET_CURSOR, 0, edx, object, ecx, &zero, 1, NULL);
        do
        {
            eax = vertrix_calln(calls, IMPORT_SHOW_CURSOR, eax, edx, object, ecx, &zero, 1, NULL);
        } while ((int32_t)eax >= 0);
    }
    if (!vertrix_build_store(services, object, DEVICE_FLAG, DWORD_WIDTH, 1))
    {
        return 0;
    }
    return 1;
}

uint32_t vertrix_cursor_release(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, uint32_t frame, uint32_t object,
                                uint32_t edx, uint32_t ecx)
{
    uint32_t flag;
    uint32_t iface;
    uint32_t table;
    uint32_t stack[FORMAT_ARGUMENTS];
    uint32_t result;
    if (!read_value(services, object, DEVICE_FLAG, DWORD_WIDTH, &flag))
    {
        return 0;
    }
    if (flag != 0)
    {
        if (!read_value(services, object, DEVICE_INTERFACE, DWORD_WIDTH, &iface) ||
            !read_value(services, iface, 0, DWORD_WIDTH, &table))
        {
            return 0;
        }
        vertrix_calln(calls, globals->read(table + METHOD_UNACQUIRE, globals->context), iface,
                      table, object, ecx, &iface, 1, NULL);
    }
    if (!read_value(services, object, DEVICE_INTERFACE, DWORD_WIDTH, &iface) ||
        !read_value(services, iface, 0, DWORD_WIDTH, &table))
    {
        return 0;
    }
    stack[0] = iface;
    stack[1] = 2;
    stack[2] = frame - 0x24;
    stack[3] = FORMAT_ECX;
    stack[4] = FORMAT_SECOND;
    stack[5] = 0;
    stack[6] = 0;
    stack[7] = edx == 0;
    result = vertrix_calln(calls, globals->read(table + METHOD_FORMAT, globals->context), iface,
                           table, object, FORMAT_ECX, stack, FORMAT_ARGUMENTS, NULL);
    if (!read_value(services, object, DEVICE_FLAG, DWORD_WIDTH, &flag))
    {
        return 0;
    }
    if (flag == 0)
    {
        return result;
    }
    if (!read_value(services, object, DEVICE_INTERFACE, DWORD_WIDTH, &iface) ||
        !read_value(services, iface, 0, DWORD_WIDTH, &table))
    {
        return 0;
    }
    return vertrix_calln(calls, globals->read(table + METHOD_ACQUIRE, globals->context), table,
                         table, iface, FORMAT_ECX, &iface, 1, NULL);
}
