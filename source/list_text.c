#include "list_text.h"
#include "actor_storage.h"
#include "rtl_glue.h"

enum
{
    DWORD_WIDTH = 4,
    NAME_NAME = 0x5110c1,
    NAME_FORMAT = 0x5110c2,
    FORMAT_STRING = 0x5110c3,
    FORMAT_FIELD = 0x18,
    NAME_OFFSET = 0x14,
    LABEL_VALUE = 0x190,
    LABEL_TARGET = 0x160,
    LABEL_TEXT = 0x15c,
    LABEL_LOCAL = 0x14,
    LABEL_FORMAT = 0x511094,
    RESIZE_BLOCK_SIZE = 4,
    RELEASE_EMPTY_ECX = 0x51864c,
    LOOKUP_NAME = 0x5110cb,
    LOOKUP_WRAPPER_LOCAL = 0x18,
    INDEXED_ARRAY = 4,
    INDEXED_COUNT = 8,
    INDEXED_NAME = 0x5110ca,
    LABEL_ALTERNATE_VALUE = 0x18c,
    LABEL_ALTERNATE_FORMAT = 0x51108e
};

static int read_field(const VertrixFactoryServices *services, uint32_t item, size_t field,
                      uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(item, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, field, DWORD_WIDTH, value);
}

uint32_t vertrix_list_text_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixListTextSpec *spec, uint32_t reader, uint32_t slot,
                                 uint32_t ebx)
{
    uint32_t value;
    uint32_t item = vertrix_call(calls, 0x4b6fa0, reader, ebx, VERTRIX_LIST_TEXT_FRAME, reader, 0);
    uint32_t text;
    vertrix_call(calls, 0x4ca280, slot, spec->name, VERTRIX_LIST_TEXT_FRAME, item, 0);
    if (item == 0)
    {
        return slot;
    }
    if (!read_field(services, item, spec->field, &value))
    {
        return 0;
    }
    text = vertrix_call(calls, 0x415ed0, value, spec->format_edx, spec->format_ebx,
                        spec->format_ecx, 0);
    vertrix_call(calls, 0x4ca370, slot, text, spec->format_ebx, spec->format_ecx, 0);
    return slot;
}

uint32_t vertrix_list_text_name(const VertrixCalls *calls, uint32_t reader, uint32_t slot,
                                uint32_t ebx)
{
    uint32_t item = vertrix_call(calls, 0x4b6fa0, reader, ebx, ebx, slot, 0);
    vertrix_call(calls, 0x4ca280, slot, NAME_NAME, item, slot, 0);
    if (item == 0)
    {
        return slot;
    }
    vertrix_call(calls, 0x4ca310, slot, item + NAME_OFFSET, item, slot, 0);
    return slot;
}

uint32_t vertrix_list_text_format(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t reader, uint32_t slot, uint32_t ebx)
{
    uint32_t value;
    uint32_t item = vertrix_call(calls, 0x4b6fa0, reader, ebx, VERTRIX_LIST_TEXT_FRAME, slot, 0);
    uint32_t stack[3];
    uint32_t cleared =
        vertrix_call(calls, 0x4ca280, slot, NAME_FORMAT, VERTRIX_LIST_TEXT_FRAME, slot, 0);
    if (item == 0)
    {
        return slot;
    }
    if (!read_field(services, item, FORMAT_FIELD, &value))
    {
        return 0;
    }
    stack[0] = slot;
    stack[1] = FORMAT_STRING;
    stack[2] = value;
    vertrix_call3(calls, 0x4cdfb0, cleared, value, VERTRIX_LIST_TEXT_FRAME, slot, stack);
    return slot;
}

enum
{
    CYCLE_TEXT = 0x15c,
    CYCLE_PARENT = 0x160,
    CYCLE_ARRAY = 0x170,
    CYCLE_COUNT = 0x174
};

static int array_entry(const VertrixFactoryServices *services, uint32_t array, uint32_t index,
                       uint32_t *entry)
{
    return read_field(services, array, 4 * (size_t)index, entry);
}

static int cycle_assign(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t object, uint32_t parent, uint32_t array, uint32_t index,
                        uint32_t ecx)
{
    uint32_t entry;
    if (!array_entry(services, array, index, &entry))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ca370, parent + CYCLE_TEXT, entry, object, ecx, 0);
    return 1;
}

uint32_t vertrix_list_cycle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t object, const void *storage, size_t size, unsigned mode)
{
    uint32_t count;
    uint32_t parent;
    uint32_t array;
    uint32_t found = UINT32_MAX;
    if (!vertrix_actor_storage_read(storage, size, CYCLE_COUNT, DWORD_WIDTH, &count))
    {
        return 0;
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t text;
        uint32_t entry;
        if (!vertrix_actor_storage_read(storage, size, CYCLE_PARENT, DWORD_WIDTH, &parent) ||
            !vertrix_actor_storage_read(storage, size, CYCLE_ARRAY, DWORD_WIDTH, &array) ||
            !read_field(services, parent, CYCLE_TEXT, &text) ||
            !array_entry(services, array, i, &entry))
        {
            return 0;
        }
        if (vertrix_call(calls, 0x4ccfe0, entry, text, object, i, 0) == 0)
        {
            found = i;
        }
    }
    if (found == UINT32_MAX ||
        !vertrix_actor_storage_read(storage, size, CYCLE_PARENT, DWORD_WIDTH, &parent) ||
        !vertrix_actor_storage_read(storage, size, CYCLE_ARRAY, DWORD_WIDTH, &array))
    {
        return 0;
    }
    if (mode == VERTRIX_CYCLE_PREVIOUS || mode == VERTRIX_CYCLE_PREVIOUS_WRAP)
    {
        if ((int32_t)found > 0)
        {
            return cycle_assign(calls, services, object, parent, array, found - 1,
                                mode == VERTRIX_CYCLE_PREVIOUS ? count : 1);
        }
        if (mode == VERTRIX_CYCLE_PREVIOUS)
        {
            return 0;
        }
        return cycle_assign(calls, services, object, parent, array, count - 1, count);
    }
    if (found < count - 1)
    {
        return cycle_assign(calls, services, object, parent, array, found + 1,
                            mode == VERTRIX_CYCLE_NEXT ? count : 1);
    }
    if (mode == VERTRIX_CYCLE_NEXT)
    {
        return 0;
    }
    return cycle_assign(calls, services, object, parent, array, 0, count);
}

static uint32_t label_format(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             uint32_t frame, uint32_t object, uint32_t value, void *storage,
                             size_t size, size_t value_offset, uint32_t format)
{
    uint32_t target, text;
    uint32_t local = frame - LABEL_LOCAL;
    uint32_t stack[3] = {local, format, value};
    if (!vertrix_actor_storage_write(storage, size, value_offset, DWORD_WIDTH, value) ||
        !read_field(services, object, LABEL_TARGET, &target))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ca070, local, value, VERTRIX_LIST_TEXT_FRAME, object, 0);
    vertrix_calln(calls, 0x4cdfb0, local, value, VERTRIX_LIST_TEXT_FRAME, object, stack, 3, &text);
    vertrix_call(calls, 0x4ca370, target + LABEL_TEXT, text, VERTRIX_LIST_TEXT_FRAME, object, 0);
    vertrix_call(calls, 0x4ca210, local, 0, VERTRIX_LIST_TEXT_FRAME, object, 0);
    return 0;
}

uint32_t vertrix_object_label_format(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t frame,
                                     uint32_t object, uint32_t value, void *storage, size_t size)
{
    return label_format(calls, services, frame, object, value, storage, size, LABEL_VALUE,
                        LABEL_FORMAT);
}

uint32_t vertrix_object_label_format_alternate(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               uint32_t frame, uint32_t object, uint32_t value,
                                               void *storage, size_t size)
{
    return label_format(calls, services, frame, object, value, storage, size, LABEL_ALTERNATE_VALUE,
                        LABEL_ALTERNATE_FORMAT);
}

uint32_t vertrix_list_text_indexed(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t object,
                                   uint32_t slot, uint32_t index)
{
    uint32_t count, array, entry;
    if (!read_field(services, object, INDEXED_COUNT, &count))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ca280, slot, INDEXED_NAME, index, slot, 0);
    if (index >= count)
    {
        return slot;
    }
    if (!read_field(services, object, INDEXED_ARRAY, &array) ||
        !array_entry(services, array, index, &entry))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ca310, slot, entry, index, slot, 0);
    return slot;
}

uint32_t vertrix_list_resize_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t count;
    uint32_t block;
    if (!read_field(services, object, INDEXED_COUNT, &count))
    {
        return 0;
    }
    block = vertrix_call(calls, 0x4ca000, RESIZE_BLOCK_SIZE, edx, ebx, ecx, 0);
    if (block != 0)
    {
        block = vertrix_call(calls, 0x4ca090, block, edx, ebx, ecx, 0);
    }
    vertrix_call(calls, 0x4d88a0, object, count, block, 1, 0);
    return 0;
}

uint32_t vertrix_list_release_entries(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t object)
{
    uint32_t count, array;
    if (!read_field(services, object, INDEXED_COUNT, &count))
    {
        return 0;
    }
    for (uint32_t index = 0; index < count; index++)
    {
        uint32_t entry;
        if (!read_field(services, object, INDEXED_ARRAY, &array) ||
            !array_entry(services, array, index, &entry))
        {
            return 0;
        }
        if (entry != 0)
        {
            uint32_t released = vertrix_call(calls, 0x4ca210, entry, 0, index, 4 * index, 0);
            vertrix_call(calls, 0x4ca050, released, 0, index, 4 * index, 0);
        }
    }
    vertrix_call(calls, 0x4d8770, object, 0, 0xffffffffu,
                 count == 0 ? RELEASE_EMPTY_ECX : 4 * count, 0);
    return 0;
}

uint32_t vertrix_list_text_lookup(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t local, uint32_t reader, uint32_t slot, uint32_t ebx,
                                  uint32_t index)
{
    uint32_t item;
    vertrix_call(calls, 0x4ca280, slot, LOOKUP_NAME, ebx, index, 0);
    item = vertrix_call(calls, 0x4b79c0, reader, ebx, ebx, index, 0);
    if (item == 0)
    {
        return slot;
    }
    uint32_t text = vertrix_list_text_indexed(calls, services, item, local, index);
    vertrix_call(calls, 0x4ca310, slot, text, 0, 1, 0);
    vertrix_call(calls, 0x4ca210, local, 0, 0, 1, 0);
    return slot;
}

uint32_t vertrix_list_text_lookup_slot(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t stack_base,
                                       uint32_t reader, uint32_t slot, uint32_t ebx, uint32_t index)
{
    vertrix_list_text_lookup(calls, services, stack_base - LOOKUP_WRAPPER_LOCAL, reader, slot, ebx,
                             index);
    return slot;
}

enum
{
    DESCRIBE_KIND = 0xd,
    DESCRIBE_FLAG = 0x10,
    DESCRIBE_LOCAL = 0x14,
    DESCRIBE_EDX = 0x4ec1ec,
    DESCRIBE_EBX = 0x516840,
    DESCRIBE_INIT = 0x4ca070,
    DESCRIBE_ASSIGN = 0x4ca370,
    DESCRIBE_APPEND = 0x4ca600,
    DESCRIBE_RELEASE = 0x4ca210,
    DESCRIBE_HEAD = 0x50ea1e,
    DESCRIBE_TAIL = 0x50ea3c,
    DESCRIBE_FLAG_ON = 0x50ea48,
    DESCRIBE_FLAG_OFF = 0x50ea4c,
    DESCRIBE_KIND_COUNT = 5
};

static const uint32_t DESCRIBE_KINDS[DESCRIBE_KIND_COUNT] = {0x50ea2b, 0x50ea2d, 0x50ea30, 0x50ea33,
                                                             0x50ea36};

uint32_t vertrix_object_describe(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t frame, uint32_t object)
{
    uint32_t local = frame - DESCRIBE_LOCAL;
    uint32_t kind, flag, edx;
    if (!read_field(services, object, DESCRIBE_KIND, &kind) ||
        !read_field(services, object, DESCRIBE_FLAG, &flag))
    {
        return 0;
    }
    kind &= 0xff;
    vertrix_call(calls, DESCRIBE_INIT, local, DESCRIBE_EDX, DESCRIBE_EBX, object, 0);
    vertrix_call(calls, DESCRIBE_ASSIGN, local, DESCRIBE_HEAD, DESCRIBE_EBX, object, 0);
    if (kind < DESCRIBE_KIND_COUNT)
    {
        vertrix_call(calls, DESCRIBE_APPEND, local, DESCRIBE_KINDS[kind], DESCRIBE_EBX, object, 0);
    }
    vertrix_call(calls, DESCRIBE_ASSIGN, local, DESCRIBE_TAIL, DESCRIBE_EBX, object, 0);
    edx = flag == 1 ? DESCRIBE_FLAG_ON : DESCRIBE_FLAG_OFF;
    vertrix_call(calls, DESCRIBE_APPEND, local, edx, DESCRIBE_EBX, object, 0);
    return vertrix_call(calls, DESCRIBE_RELEASE, local, 0, DESCRIBE_EBX, 0, 0);
}

enum
{
    SCRIPT_CHECK = 0x4ccfe0,
    SCRIPT_KEY = 0x50d652,
    SCRIPT_FORMAT = 0x50d653,
    SCRIPT_EBX = 0x513b9c,
    SCRIPT_FORMAT_CALL = 0x4cdfb0,
    SCRIPT_TARGET = 0x47faf0,
    SCRIPT_TARGET_OBJECT = 0x5bb254,
    SCRIPT_LOCAL = 0x18,
    SCRIPT_FORMAT_ARGUMENTS = 3
};

uint32_t vertrix_object_load_script(const VertrixCalls *calls, uint32_t frame, uint32_t object)
{
    uint32_t local = frame - SCRIPT_LOCAL;
    uint32_t arguments[SCRIPT_FORMAT_ARGUMENTS] = {local, SCRIPT_FORMAT, object};
    uint32_t text;
    if (vertrix_call(calls, SCRIPT_CHECK, object, SCRIPT_KEY, SCRIPT_EBX, object, 0) == 0)
    {
        return 0;
    }
    vertrix_call(calls, DESCRIBE_INIT, local, SCRIPT_KEY, SCRIPT_EBX, object, 0);
    vertrix_calln(calls, SCRIPT_FORMAT_CALL, local, SCRIPT_KEY, SCRIPT_EBX, object, arguments,
                  SCRIPT_FORMAT_ARGUMENTS, &text);
    vertrix_call(calls, SCRIPT_TARGET, SCRIPT_TARGET_OBJECT, text, SCRIPT_EBX, object, 0);
    return vertrix_call(calls, DESCRIBE_RELEASE, local, 0, SCRIPT_EBX, object, 0);
}

enum
{
    CLOCK_INIT = 0x4ca070,
    CLOCK_FORMAT = 0x4cdfb0,
    CLOCK_JOIN = 0x4ca4a0,
    CLOCK_JOIN_FIRST = 0x4ca430,
    CLOCK_ASSIGN = 0x4ca310,
    CLOCK_LEAVE_FIRST = 0x4cda12,
    CLOCK_LEAVE_SECOND = 0x4cda10,
    CLOCK_EDX = 0x4ec1ec,
    CLOCK_TENS_FORMAT = 0x50d7bd,
    CLOCK_ONES_FORMAT = 0x50d7c1,
    CLOCK_JOIN_TEXT = 0x50d7c5,
    CLOCK_LOCAL_TENS = 0x20,
    CLOCK_LOCAL_ONES = 0x1c,
    CLOCK_LOCAL_JOINED = 0x18,
    CLOCK_LOCAL_RESULT = 0x14,
    CLOCK_BASE = 10,
    CLOCK_JOIN_ARGUMENTS = 4,
    CLOCK_FIRST_ARGUMENTS = 2
};

uint32_t vertrix_clock_text(const VertrixCalls *calls, uint32_t frame, uint32_t variable,
                            uint32_t value)
{
    uint32_t quotient = value / CLOCK_BASE;
    uint32_t remainder = value - quotient * CLOCK_BASE;
    uint32_t tens = frame - CLOCK_LOCAL_TENS, ones = frame - CLOCK_LOCAL_ONES;
    uint32_t format_tens[3] = {tens, CLOCK_TENS_FORMAT, quotient};
    uint32_t format_ones[3] = {ones, CLOCK_ONES_FORMAT, remainder};
    uint32_t join[CLOCK_JOIN_ARGUMENTS] = {frame - CLOCK_LOCAL_JOINED, tens, CLOCK_JOIN_TEXT, ones};
    uint32_t first[CLOCK_FIRST_ARGUMENTS], joined, text, leave;
    vertrix_call(calls, CLOCK_INIT, variable, CLOCK_EDX, variable, value, 0);
    vertrix_call(calls, CLOCK_INIT, tens, CLOCK_EDX, variable, value, 0);
    vertrix_call(calls, CLOCK_INIT, ones, 2, variable, value, 0);
    vertrix_calln(calls, CLOCK_FORMAT, tens, quotient, variable, remainder, format_tens, 3, NULL);
    vertrix_calln(calls, CLOCK_FORMAT, ones, quotient, variable, remainder, format_ones, 3, NULL);
    joined = vertrix_calln(calls, CLOCK_JOIN, frame - CLOCK_LOCAL_JOINED, quotient, variable,
                           remainder, join, CLOCK_JOIN_ARGUMENTS, NULL);
    first[0] = frame - CLOCK_LOCAL_RESULT;
    first[1] = joined;
    text = vertrix_calln(calls, CLOCK_JOIN_FIRST, frame - CLOCK_LOCAL_RESULT, quotient, variable, 3,
                         first, CLOCK_FIRST_ARGUMENTS, NULL);
    vertrix_call(calls, CLOCK_ASSIGN, variable, text, variable, 3, 0);
    leave = vertrix_call(calls, CLOCK_LEAVE_FIRST, 2, text, variable, 3, 0);
    vertrix_call(calls, CLOCK_LEAVE_SECOND, leave, text, variable, 3, 0);
    return variable;
}

enum
{
    VALUES_COUNT = 0x48a2e0,
    VALUES_ITEM = 0x48a2f0,
    VALUES_LOOKUP = 0x48a300,
    VALUES_PARSE = 0x4d6710,
    VALUES_RELEASE = 0x4ca210,
    VALUES_EBX = 0x517608,
    VALUES_ECX = 0x4ec1ec,
    VALUES_LOCAL = 0x18,
    VALUES_WORD = 0xffff
};

void vertrix_list_parse_values(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t reader, uint32_t destination_token,
                               uint32_t count, uint32_t fallback, uint32_t threshold,
                               uint32_t *destination)
{
    uint32_t ebx = VALUES_EBX, ecx = VALUES_ECX;
    for (uint32_t index = 0; index < (count & VALUES_WORD); index++)
    {
        uint32_t available =
            vertrix_call(calls, VALUES_COUNT, reader, destination_token, ebx, ecx, 0);
        uint32_t value = fallback;
        if (index < available)
        {
            uint32_t item = vertrix_call(calls, VALUES_ITEM, reader, index, ebx, ecx, 0);
            if (item > threshold)
            {
                uint32_t local = frame - VALUES_LOCAL, slot, text;
                slot = vertrix_call(calls, VALUES_LOOKUP, reader, local, index, threshold, 0);
                if (!read_field(services, slot, 0, &text))
                {
                    return;
                }
                value = vertrix_call(calls, VALUES_PARSE, text, destination_token, 0, threshold, 0);
                vertrix_call(calls, VALUES_RELEASE, local, 0, 0, threshold, 0);
                ebx = 0;
                ecx = threshold;
            }
        }
        *destination++ = value;
        destination_token += 4;
    }
}

enum
{
    TEXTS_ASSIGN = 0x4ca310,
    TEXTS_DEFAULT = 0x4ca370,
    TEXTS_EBX = 0x5175fc,
    TEXTS_RELEASED_ECX = 1
};

void vertrix_list_parse_texts(const VertrixCalls *calls, uint32_t frame, uint32_t reader,
                              uint32_t destination, uint32_t count, uint32_t fallback,
                              uint32_t threshold)
{
    uint32_t ebx = TEXTS_EBX, ecx = VALUES_ECX;
    for (uint32_t index = 0; index < (count & VALUES_WORD); index++)
    {
        uint32_t available = vertrix_call(calls, VALUES_COUNT, reader, destination, ebx, ecx, 0);
        int assigned = 0;
        if (index < available &&
            vertrix_call(calls, VALUES_ITEM, reader, index, ebx, ecx, 0) > threshold)
        {
            uint32_t local = frame - VALUES_LOCAL;
            uint32_t slot = vertrix_call(calls, VALUES_LOOKUP, reader, local, index, threshold, 0);
            ebx = 0;
            ecx = TEXTS_RELEASED_ECX;
            vertrix_call(calls, TEXTS_ASSIGN, destination, slot, ebx, ecx, 0);
            vertrix_call(calls, VALUES_RELEASE, local, 0, ebx, ecx, 0);
            assigned = 1;
        }
        if (!assigned)
        {
            vertrix_call(calls, TEXTS_DEFAULT, destination, fallback, ebx, ecx, 0);
        }
        destination += 4;
    }
}

enum
{
    NAMES_COUNT = 0x14,
    NAMES_ARRAY = 0x20,
    NAMES_NOT_FOUND = 0xffffffffu
};

int vertrix_list_find_name(const VertrixFactoryServices *services, uint32_t list, uint32_t text,
                           uint32_t *index)
{
    uint32_t count, array;
    if (!read_field(services, list, NAMES_COUNT, &count) ||
        !read_field(services, list, NAMES_ARRAY, &array))
    {
        return 0;
    }
    *index = NAMES_NOT_FOUND;
    for (uint32_t i = 0; i < count; i++)
    {
        uint32_t name, equal;
        if (!read_field(services, array, DWORD_WIDTH * (size_t)i, &name))
        {
            return 0;
        }
        if (name == 0)
        {
            continue;
        }
        if (!vertrix_rtl_text_equal(services, name, text, &equal))
        {
            return 0;
        }
        if (equal == 1)
        {
            *index = i;
            return 1;
        }
    }
    return 1;
}

enum
{
    TEXT_PARENT = 0x160,
    TEXT_POINTER = 0x15c,
    TEXT_CURSOR = 0x170,
    TEXT_FROM_POINTER = 0x4ca280,
    TEXT_INIT = 0x4ca070,
    TEXT_COPY = 0x4cdb70,
    TEXT_SLICE = 0x4cdaf0,
    TEXT_ASSIGN = 0x4ca310,
    TEXT_RELEASE = 0x4ca210,
    TEXT_JOIN = 0x4ca430,
    TEXT_STORE = 0x4ca370,
    TEXT_LEAVE = 0x4cda10,
    TEXT_LOCAL_A = 0x2c,
    TEXT_LOCAL_B = 0x28,
    TEXT_LOCAL_C = 0x24,
    TEXT_LOCAL_T1 = 0x20,
    TEXT_LOCAL_T2 = 0x1c,
    TEXT_LOCAL_T3 = 0x18,
    TEXT_JOIN_COUNT = 3,
    TEXT_JOIN_ARGUMENTS = 3,
    TEXT_ASSIGN_COUNT = 8,
    TEXT_MAX = 0x10000,
    NOT_FOUND = 0xffffffffu
};

static int text_strlen(const VertrixFactoryServices *services, uint32_t text, uint32_t *length)
{
    void *storage;
    size_t size;
    const uint8_t *bytes;
    if (!services->resolve(text, &storage, &size, services->context))
    {
        return 0;
    }
    bytes = storage;
    for (uint32_t i = 0; i < size; i++)
    {
        if (bytes[i] == 0)
        {
            *length = i;
            return 1;
        }
    }
    return 0;
}

static int text_rebuild(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t object, uint32_t skip_before, uint32_t skip_after,
                        uint32_t *result)
{
    uint32_t parent, text, cursor, length, copy, tail, joined, remaining, join[TEXT_JOIN_ARGUMENTS];
    uint32_t a = frame - TEXT_LOCAL_A, b = frame - TEXT_LOCAL_B, c = frame - TEXT_LOCAL_C;
    uint32_t t1 = frame - TEXT_LOCAL_T1, t2 = frame - TEXT_LOCAL_T2, t3 = frame - TEXT_LOCAL_T3;
    if (!read_field(services, object, TEXT_PARENT, &parent) ||
        !read_field(services, parent, TEXT_POINTER, &text) ||
        !read_field(services, object, TEXT_CURSOR, &cursor) ||
        !text_strlen(services, text, &length))
    {
        return 0;
    }
    vertrix_call(calls, TEXT_FROM_POINTER, a, text, 0, length, 0);
    vertrix_call(calls, TEXT_INIT, b, text, 0, length, 0);
    vertrix_call(calls, TEXT_INIT, c, TEXT_JOIN_COUNT, 0, length, 0);
    if (skip_before == 0 ? cursor == NOT_FOUND : length - 1 == cursor)
    {
        vertrix_call(calls, TEXT_RELEASE, c, 0, cursor, length, 0);
        vertrix_call(calls, TEXT_RELEASE, b, 0, cursor, length, 0);
        vertrix_call(calls, TEXT_RELEASE, a, 0, cursor, length, 0);
        *result = 0;
        return 1;
    }
    copy = vertrix_call(calls, TEXT_COPY, a, t1, cursor + skip_before, length, 0);
    vertrix_call(calls, TEXT_ASSIGN, b, copy, cursor + skip_before, length, 0);
    vertrix_call(calls, TEXT_RELEASE, t1, 0, cursor + skip_before, length, 0);
    remaining = length - cursor;
    tail = vertrix_call(calls, TEXT_SLICE, a, t2, remaining - skip_after, remaining, 0);
    vertrix_call(calls, TEXT_ASSIGN, c, tail, remaining - skip_after, remaining, 0);
    vertrix_call(calls, TEXT_RELEASE, t2, 0, remaining - skip_after, remaining, 0);
    join[0] = t3;
    join[1] = b;
    join[2] = c;
    joined = vertrix_calln(calls, TEXT_JOIN, t3, TEXT_JOIN_COUNT, TEXT_JOIN_COUNT, remaining, join,
                           TEXT_JOIN_ARGUMENTS, NULL);
    vertrix_call(calls, TEXT_ASSIGN, a, joined, TEXT_JOIN_COUNT, TEXT_ASSIGN_COUNT, 0);
    vertrix_call(calls, TEXT_RELEASE, t3, 0, TEXT_JOIN_COUNT, TEXT_ASSIGN_COUNT, 0);
    vertrix_call(calls, TEXT_LEAVE,
                 vertrix_call(calls, TEXT_STORE, parent + TEXT_POINTER, joined, TEXT_JOIN_COUNT,
                              TEXT_ASSIGN_COUNT, 0),
                 joined, TEXT_JOIN_COUNT, TEXT_ASSIGN_COUNT, 0);
    *result = 1;
    return 1;
}

int vertrix_object_text_rebuild(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t frame, uint32_t object, uint32_t *result)
{
    return text_rebuild(calls, services, frame, object, 1, 2, result);
}

int vertrix_object_text_remove(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t object, uint32_t *result)
{
    return text_rebuild(calls, services, frame, object, 0, 1, result);
}

enum
{
    INSERT_LIMIT = 0x178,
    INSERT_LOCAL_A = 0x30,
    INSERT_LOCAL_B = 0x2c,
    INSERT_LOCAL_C = 0x28,
    INSERT_LOCAL_T1 = 0x24,
    INSERT_LOCAL_T2 = 0x20,
    INSERT_LOCAL_T3 = 0x1c,
    INSERT_LOCAL_T4 = 0x18,
    INSERT_JOIN = 0x4ca4a0,
    INSERT_LEAVE_FIRST = 0x4cda12,
    INSERT_JOIN_ARGUMENTS = 4,
    INSERT_STORE_ARGUMENTS = 2,
    INSERT_STORE_EBX = 8
};

int vertrix_object_text_insert(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t object, uint32_t value, uint32_t *result)
{
    uint32_t parent, text, cursor, limit, length, copy, tail, joined, stored, remaining;
    uint32_t join[INSERT_JOIN_ARGUMENTS], store[INSERT_STORE_ARGUMENTS];
    uint32_t a = frame - INSERT_LOCAL_A, b = frame - INSERT_LOCAL_B, c = frame - INSERT_LOCAL_C;
    uint32_t t1 = frame - INSERT_LOCAL_T1, t2 = frame - INSERT_LOCAL_T2;
    uint32_t t3 = frame - INSERT_LOCAL_T3, t4 = frame - INSERT_LOCAL_T4;
    if (!read_field(services, object, TEXT_PARENT, &parent) ||
        !read_field(services, parent, TEXT_POINTER, &text) ||
        !read_field(services, object, TEXT_CURSOR, &cursor) ||
        !read_field(services, object, INSERT_LIMIT, &limit) ||
        !text_strlen(services, text, &length))
    {
        return 0;
    }
    vertrix_call(calls, TEXT_FROM_POINTER, a, text, 0, length, 0);
    vertrix_call(calls, TEXT_INIT, b, text, 0, length, 0);
    vertrix_call(calls, TEXT_INIT, c, TEXT_JOIN_COUNT, 0, length, 0);
    if (length == limit)
    {
        vertrix_call(calls, TEXT_RELEASE, c, 0, 0, length, 0);
        vertrix_call(calls, TEXT_RELEASE, b, 0, 0, length, 0);
        vertrix_call(calls, TEXT_RELEASE, a, 0, 0, length, 0);
        *result = 0;
        return 1;
    }
    copy = vertrix_call(calls, TEXT_COPY, a, t1, cursor + 1, length, 0);
    vertrix_call(calls, TEXT_ASSIGN, b, copy, cursor + 1, length, 0);
    vertrix_call(calls, TEXT_RELEASE, t1, 0, cursor + 1, length, 0);
    remaining = length - cursor;
    tail = vertrix_call(calls, TEXT_SLICE, a, t2, remaining - 1, remaining, 0);
    vertrix_call(calls, TEXT_ASSIGN, c, tail, remaining - 1, remaining, 0);
    vertrix_call(calls, TEXT_RELEASE, t2, 0, remaining - 1, remaining, 0);
    join[0] = t3;
    join[1] = b;
    join[2] = value;
    join[3] = c;
    joined = vertrix_calln(calls, INSERT_JOIN, t3, TEXT_JOIN_COUNT, remaining - 1, value, join,
                           INSERT_JOIN_ARGUMENTS, NULL);
    store[0] = t4;
    store[1] = joined;
    stored = vertrix_calln(calls, TEXT_JOIN, t4, TEXT_JOIN_COUNT, INSERT_STORE_EBX, value, store,
                           INSERT_STORE_ARGUMENTS, NULL);
    vertrix_call(calls, TEXT_ASSIGN, a, stored, INSERT_STORE_EBX, value, 0);
    vertrix_call(calls, INSERT_LEAVE_FIRST, TEXT_JOIN_COUNT, stored, INSERT_STORE_EBX, value, 0);
    vertrix_call(
        calls, TEXT_LEAVE,
        vertrix_call(calls, TEXT_STORE, parent + TEXT_POINTER, stored, INSERT_STORE_EBX, value, 0),
        stored, INSERT_STORE_EBX, value, 0);
    *result = 1;
    return 1;
}

enum
{
    FIELD_TEXT = 0x15c,
    FIELD_SIGNED_BYTE = 0x15d,
    FIELD_BYTE = 0x44,
    FIELD_COPY = 0x4cdb70,
    FIELD_CONVERT = 0x440610,
    FIELD_LOCAL_TEXT = 0x1c,
    FIELD_LOCAL_VALUE = 0x18,
    FIELD_LOCAL_STACK = 0x14,
    FIELD_HEADER_LENGTH = 4,
    FIELD_HEADER_SIZE = 0xc,
    FIELD_SIGN_SHIFT = 24
};

int vertrix_object_text_value(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t frame, uint32_t object, uint32_t edx, uint32_t *result)
{
    uint32_t text, length, byte, signed_dword, value;
    VertrixCallSite site = {FIELD_CONVERT, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, 0};
    uint32_t local = frame - FIELD_LOCAL_TEXT;
    vertrix_calln(calls, FIELD_COPY, object + FIELD_TEXT, local, edx, object, NULL, 0, &text);
    if (!read_field(services, text - FIELD_HEADER_SIZE, FIELD_HEADER_LENGTH, &length))
    {
        return 0;
    }
    if (length == 0)
    {
        vertrix_call(calls, DESCRIBE_RELEASE, local, 0, edx, object, 0);
        *result = 0;
        return 1;
    }
    if (!read_field(services, object, FIELD_BYTE, &byte) ||
        !read_field(services, object, FIELD_SIGNED_BYTE, &signed_dword))
    {
        return 0;
    }
    byte &= 0xff;
    site.eax = (uint32_t)((int32_t)signed_dword >> FIELD_SIGN_SHIFT);
    site.edx = text;
    site.ebx = byte;
    site.ecx = frame - FIELD_LOCAL_VALUE;
    site.stack = frame - FIELD_LOCAL_STACK;
    calls->call(&site, calls->context);
    value = site.out_ecx;
    vertrix_call(calls, DESCRIBE_RELEASE, local, 0, byte, value, 0);
    *result = value;
    return 1;
}

enum
{
    ROW_FRAME_DEPTH = 12,
    NEAREST_CALL_DEPTH = 0x1c,
    NEAREST_BEST = 0x4e20,
    FIELD_METRIC = 0xc,
    METRIC_SHIFT = 16,
    CURSOR_STORE = 0x170
};

int vertrix_object_text_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t entry, uint32_t object, uint32_t index, uint32_t *result)
{
    uint32_t parent, next = index + 1;
    if ((int32_t)next <= 0)
    {
        *result = 0;
        return 1;
    }
    return read_field(services, object, TEXT_PARENT, &parent) &&
           vertrix_object_text_value(calls, services, entry - ROW_FRAME_DEPTH, parent, next,
                                     result);
}

int vertrix_object_text_nearest(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t frame, uint32_t object, uint32_t target, uint32_t *result)
{
    uint32_t parent, text, length, metric, best = NEAREST_BEST;
    *result = NOT_FOUND;
    if (!read_field(services, object, TEXT_PARENT, &parent) ||
        !read_field(services, parent, TEXT_POINTER, &text) || !text_strlen(services, text, &length))
    {
        return 0;
    }
    for (int32_t i = -1; i < (int32_t)length; i++)
    {
        uint32_t row, distance;
        int32_t difference;
        if (!read_field(services, parent, FIELD_METRIC, &metric) ||
            !vertrix_object_text_row(calls, services, frame - NEAREST_CALL_DEPTH, object,
                                     (uint32_t)i, &row))
        {
            return 0;
        }
        difference = (int32_t)(row - target + (uint32_t)((int32_t)metric >> METRIC_SHIFT));
        distance = difference < 0 ? 0u - (uint32_t)difference : (uint32_t)difference;
        if ((int32_t)distance < (int32_t)best)
        {
            *result = (uint32_t)i;
            best = distance;
        }
    }
    return 1;
}

int vertrix_object_text_seek(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             uint32_t entry, uint32_t object, uint32_t target)
{
    uint32_t cursor;
    void *storage;
    size_t size;
    return vertrix_object_text_nearest(calls, services, entry - ROW_FRAME_DEPTH, object, target,
                                       &cursor) &&
           services->resolve(object, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, CURSOR_STORE, DWORD_WIDTH, cursor);
}

enum
{
    CURSOR_FIELD = 0x170,
    CURSOR_ROW_DEPTH = 8,
    CURSOR_HOME = 0xffffffffu
};

static int write_field(const VertrixFactoryServices *services, uint32_t item, size_t field,
                       uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(item, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, field, DWORD_WIDTH, value);
}

static int text_length_of(const VertrixFactoryServices *services, uint32_t object, uint32_t *length)
{
    uint32_t parent, text;
    return read_field(services, object, TEXT_PARENT, &parent) &&
           read_field(services, parent, TEXT_POINTER, &text) && text_strlen(services, text, length);
}

int vertrix_object_cursor_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t entry, uint32_t object, uint32_t *result)
{
    uint32_t cursor;
    return read_field(services, object, CURSOR_FIELD, &cursor) &&
           vertrix_object_text_row(calls, services, entry - CURSOR_ROW_DEPTH, object, cursor,
                                   result);
}

int vertrix_object_cursor_clamp(const VertrixFactoryServices *services, uint32_t object)
{
    uint32_t length, cursor;
    if (!text_length_of(services, object, &length) ||
        !read_field(services, object, CURSOR_FIELD, &cursor))
    {
        return 0;
    }
    if ((int32_t)cursor < -1)
    {
        return write_field(services, object, CURSOR_FIELD, CURSOR_HOME);
    }
    if ((int32_t)length <= (int32_t)cursor)
    {
        return write_field(services, object, CURSOR_FIELD, length - 1);
    }
    return 1;
}

int vertrix_object_cursor_step(const VertrixFactoryServices *services, uint32_t object,
                               int32_t delta)
{
    uint32_t cursor;
    return read_field(services, object, CURSOR_FIELD, &cursor) &&
           write_field(services, object, CURSOR_FIELD, cursor + (uint32_t)delta) &&
           vertrix_object_cursor_clamp(services, object);
}

int vertrix_object_cursor_home(const VertrixFactoryServices *services, uint32_t object)
{
    return write_field(services, object, CURSOR_FIELD, CURSOR_HOME) &&
           vertrix_object_cursor_clamp(services, object);
}

int vertrix_object_cursor_end(const VertrixFactoryServices *services, uint32_t object)
{
    uint32_t length;
    return text_length_of(services, object, &length) &&
           write_field(services, object, CURSOR_FIELD, length - 1) &&
           vertrix_object_cursor_clamp(services, object);
}

int vertrix_object_cursor_at_end(const VertrixFactoryServices *services, uint32_t object,
                                 uint32_t *result)
{
    uint32_t length, cursor;
    if (!text_length_of(services, object, &length) ||
        !read_field(services, object, CURSOR_FIELD, &cursor))
    {
        return 0;
    }
    *result = length - 1 == cursor;
    return 1;
}

enum
{
    KIND_FIELD = 8,
    KIND_INIT = 0x4ca280,
    KIND_STORE = 0x4ca370,
    KIND_DEFAULT_TEXT = 0x510737
};

static const uint32_t KIND_TEXTS[] = {0x510755, 0x510768, 0x510787, 0x5107a6, 0x5107ca,
                                      0x5107fb, 0x51081b, 0x51084f, 0x510880, 0x5108a5,
                                      0x5108d8, 0x5108f4, 0x51092d, 0x51096d, 0x51097f};

uint32_t vertrix_object_kind_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t variable, uint32_t object)
{
    uint32_t kind;
    if (!read_field(services, object, KIND_FIELD, &kind))
    {
        return 0;
    }
    vertrix_call(calls, KIND_INIT, variable, KIND_DEFAULT_TEXT, object, variable, 0);
    if (kind < sizeof KIND_TEXTS / sizeof KIND_TEXTS[0])
    {
        vertrix_call(calls, KIND_STORE, variable, KIND_TEXTS[kind], object, variable, 0);
    }
    return variable;
}
