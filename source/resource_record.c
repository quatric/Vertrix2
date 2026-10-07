#include "resource_record.h"
#include <string.h>

enum
{
    NAME_OFFSET = 0x000,
    PATH_OFFSET = 0x104,
    FIELD_208 = 0x208,
    FIELD_20C = 0x20c,
    FLAG_220 = 0x220,
    FLAG_221 = 0x221,
    FLAG_222 = 0x222,
    FLAG_223 = 0x223,
    FLAG_224 = 0x224,
    HANDLE_268 = 0x268,
    HANDLE_26C = 0x26c,
    HANDLE_270 = 0x270,
    HANDLE_274 = 0x274,
    HANDLE_278 = 0x278,
    SPACE_WIDTH = 4,
    OBJECT_FIELD_4 = 4,
    OBJECT_FIELD_8 = 8
};

static int copy_string(uint8_t *record, size_t offset, const char *text)
{
    size_t length = strlen(text) + 1;
    if (length > VERTRIX_RECORD_STRING_SIZE)
    {
        return 0;
    }
    memcpy(record + offset, text, length);
    return 1;
}

int vertrix_record_init(void *record, size_t size, const char *name, const char *path,
                        uint8_t flag_220, uint8_t flag_221, uint8_t flag_222, uint8_t flag_223,
                        uint8_t flag_224)
{
    static const uint16_t cleared[] = {FIELD_208,  FIELD_20C,  HANDLE_268, HANDLE_26C,
                                       HANDLE_270, HANDLE_274, HANDLE_278};
    uint8_t *bytes = record;
    if (record == 0 || size < VERTRIX_RECORD_SIZE ||
        strlen(name) + 1 > VERTRIX_RECORD_STRING_SIZE ||
        strlen(path) + 1 > VERTRIX_RECORD_STRING_SIZE)
    {
        return 0;
    }
    copy_string(bytes, NAME_OFFSET, name);
    copy_string(bytes, PATH_OFFSET, path);
    for (size_t i = 0; i < sizeof cleared / sizeof cleared[0]; ++i)
    {
        vertrix_actor_storage_write(record, size, cleared[i], 4, 0);
    }
    bytes[FLAG_220] = flag_220;
    bytes[FLAG_221] = flag_221;
    bytes[FLAG_222] = flag_222;
    bytes[FLAG_223] = flag_223;
    bytes[FLAG_224] = flag_224;
    return 1;
}

static uint32_t handle_at(void *record, size_t size, size_t offset)
{
    uint32_t value = 0;
    vertrix_actor_storage_read(record, size, offset, 4, &value);
    return value;
}

static void release_if_set(void *record, size_t size, size_t offset, VertrixRecordRelease release,
                           void *context)
{
    uint32_t handle = handle_at(record, size, offset);
    if (handle != 0)
    {
        release(handle, context);
    }
}

int vertrix_record_release(void *record, size_t size, VertrixRecordRelease release, void *context)
{
    const uint8_t *bytes = record;
    if (record == 0 || size < VERTRIX_RECORD_SIZE)
    {
        return 0;
    }
    release_if_set(record, size, HANDLE_268, release, context);
    release_if_set(record, size, HANDLE_274, release, context);
    release_if_set(record, size, HANDLE_278, release, context);
    if (bytes[FLAG_220] == 1)
    {
        release_if_set(record, size, HANDLE_270, release, context);
    }
    if (bytes[FLAG_222] == 1)
    {
        release_if_set(record, size, HANDLE_26C, release, context);
    }
    vertrix_actor_storage_write(record, size, HANDLE_268, 4, 0);
    vertrix_actor_storage_write(record, size, HANDLE_274, 4, 0);
    vertrix_actor_storage_write(record, size, HANDLE_278, 4, 0);
    vertrix_actor_storage_write(record, size, HANDLE_270, 4, 0);
    vertrix_actor_storage_write(record, size, HANDLE_26C, 4, 0);
    return 1;
}

int vertrix_record_draw(const void *record, size_t size, VertrixObjectStorage resolve,
                        VertrixRecordDraw draw, void *context)
{
    uint32_t stack[4] = {0, 0, 0, 0};
    uint32_t first;
    uint32_t second;
    void *storage;
    size_t object_size;
    if (!vertrix_actor_storage_read(record, size, HANDLE_274, 4, &first) ||
        !vertrix_actor_storage_read(record, size, HANDLE_278, 4, &second))
    {
        return 0;
    }
    if (first == 0 || second == 0)
    {
        return 1;
    }
    if (!resolve(first, &storage, &object_size, context) ||
        !vertrix_actor_storage_read(storage, object_size, OBJECT_FIELD_8, 4, &stack[3]) ||
        !vertrix_actor_storage_read(storage, object_size, OBJECT_FIELD_4, 4, &stack[2]))
    {
        return 0;
    }
    draw(first, second, 0, 0, stack, context);
    return 1;
}

uint16_t vertrix_text_width(const uint8_t *text, const uint8_t widths[VERTRIX_WIDTH_TABLE_SIZE])
{
    uint16_t total = 0;
    for (; *text != 0; ++text)
    {
        if (*text == ' ')
        {
            total = (uint16_t)(total + SPACE_WIDTH);
        }
        else
        {
            total = (uint16_t)(total + widths[*text] - 1);
        }
    }
    return total == 0 ? 0 : (uint16_t)(total + 1);
}

int vertrix_record_release_global(uint32_t *global, void *record, size_t record_size,
                                  VertrixRecordRelease release, void *context,
                                  VertrixRecordMethod method, void *method_context,
                                  VertrixMemoryRead read, void *read_context)
{
    enum
    {
        METHOD_SLOT = 0x27c,
        METHOD_FLAG = 2
    };
    uint32_t object;
    uint32_t table;
    uint32_t entry;
    if (!global || !record)
    {
        return 0;
    }
    if (!vertrix_record_release(record, record_size, release, context))
    {
        return 0;
    }
    object = *global;
    if (object == 0)
    {
        return 0;
    }
    if (!read(object + METHOD_SLOT, 4, &table, read_context) ||
        !read(table, 4, &entry, read_context) || entry == 0)
    {
        return 0;
    }
    int result = method(object, METHOD_FLAG, method_context);
    *global = 0;
    return result;
}

uint32_t vertrix_record_release_full(void *record, size_t size, uint32_t record_handle,
                                     const VertrixCalls *runtime, uint32_t caller_ebx)
{
    const uint8_t *bytes = record;
    if (!record || size < VERTRIX_RECORD_SIZE)
    {
        return 0;
    }
    uint32_t result = record_handle;
    uint32_t ecx = handle_at(record, size, HANDLE_268);
    if (ecx)
    {
        result = vertrix_call(runtime, 0x478d80, ecx, record_handle, caller_ebx, ecx, 0);
    }
    uint32_t ebx = handle_at(record, size, HANDLE_274);
    if (ebx)
    {
        result = vertrix_call(runtime, 0x478d80, ebx, record_handle, ebx, ecx, 0);
    }
    uint32_t handle = handle_at(record, size, HANDLE_278);
    if (handle)
    {
        result = vertrix_call(runtime, 0x478d80, handle, record_handle, ebx, ecx, 0);
    }
    if (bytes[FLAG_220] == 1)
    {
        handle = handle_at(record, size, HANDLE_270);
        if (handle)
        {
            result = vertrix_call(runtime, 0x478d80, handle, record_handle, ebx, ecx, 0);
        }
    }
    if (bytes[FLAG_222] == 1)
    {
        result = handle_at(record, size, HANDLE_26C);
        if (result)
        {
            result = vertrix_call(runtime, 0x478d80, result, record_handle, ebx, ecx, 0);
        }
    }
    vertrix_actor_storage_write(record, size, HANDLE_268, 4, 0);
    vertrix_actor_storage_write(record, size, HANDLE_274, 4, 0);
    vertrix_actor_storage_write(record, size, HANDLE_278, 4, 0);
    vertrix_actor_storage_write(record, size, HANDLE_270, 4, 0);
    vertrix_actor_storage_write(record, size, HANDLE_26C, 4, 0);
    return result;
}

uint32_t vertrix_record_release_global_full(uint32_t *global, void *record, size_t size,
                                            const VertrixCalls *runtime, uint32_t caller_ebx,
                                            VertrixMemoryRead read, void *read_context)
{
    if (!global)
    {
        return 0;
    }
    uint32_t object = *global;
    if (!object)
    {
        return 0;
    }
    if (!record || size < VERTRIX_RECORD_SIZE)
    {
        return 0;
    }
    uint32_t result = vertrix_record_release_full(record, size, object, runtime, caller_ebx);
    object = *global;
    if (!object)
    {
        return result;
    }
    uint32_t table, entry;
    if (!read || !read(object + 0x27c, 4, &table, read_context) ||
        !read(table, 4, &entry, read_context) || !entry)
    {
        return 0;
    }
    result = vertrix_call(runtime, entry, object, 2, caller_ebx, table, 0);
    *global = 0;
    return result;
}
