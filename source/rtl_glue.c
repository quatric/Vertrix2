#include "rtl_glue.h"

#include <math.h>
#include <string.h>

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    RECORD_COUNT = 0x10,
    RECORD_ARGUMENT = 0x30,
    RECORD_CLASS = 0x24,
    RECORD_FLAG = 0x28,
    RECORD_MARK_CLASS = 0x519724,
    RECORD_CLEAR_CLASS = 0x518d14,
    RECORD_INIT = 0x4cba70,
    RECORD_ACCESS_A = 0x4ce780,
    RECORD_ACCESS_B = 0x4ce740,
    FLAG_FALLBACK = 0x4c9b6a,
    STRING_HEADER = 0xc,
    STRING_LITERAL_SOURCE = 0x5c5c00,
    COPY_BLOCK_SHIFT = 7,
    PAD_PREPARE = 0x4e636c,
    PAD_EBX = 0x10,
    PAD_FILL = 0x30,
    WIDE_CONVERT = 0x4e62e0,
    READ_BUFFER = 0x100,
    READ_FRAME = 0x114,
    READ_SLACK = 2,
    READ_QUERY = 0x4db950,
    READ_ASSIGN = 0x4ca370,
    READ_GROW = 0x4ca670,
    READ_FINISH = 0x4ca6c0,
    READ_STEP = 0x100,
    READ_FIRST_EBX = 0xff,
    READ_ARGUMENTS = 3,
    SCOPE_RECORD_SCOPE = 4,
    SCOPE_OWNER = 0x1c,
    SCOPE_ERROR_TEXT = 0x5c7944,
    SCOPE_FLAGS_MASK = 0x40000000,
    SCOPE_ENTER_ARGUMENTS = 6,
    SCOPE_ENTER_FLAG = 1,
    SCOPE_RAISE = 0x4de900,
    SCOPE_FLAGS = 0x4cccc0,
    SCOPE_STATE = 0x4cf800,
    SCOPE_ENTER = 0x4d1ae0,
    SCOPE_LEAVE = 0x4cf850,
    SCOPE_STATE_FIRST = 4,
    SCOPE_STATE_SECOND = 8,
    SCOPE_STATE_THIRD = 0xc
};

static int read_field(const VertrixFactoryServices *services, uint32_t record, uint32_t offset,
                      uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(record, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, value);
}

static int write_field(const VertrixFactoryServices *services, uint32_t record, uint32_t offset,
                       uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(record, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, value);
}

uint32_t vertrix_rtl_record_field(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t target, uint32_t offset, uint32_t eax, uint32_t edx,
                                  uint32_t ebx, uint32_t ecx)
{
    uint32_t value;
    uint32_t record = vertrix_call(calls, target, eax, edx, ebx, ecx, 0);
    return read_field(services, record, offset, &value) ? value : 0;
}

uint32_t vertrix_rtl_record_increment(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t eax,
                                      uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t count;
    uint32_t record = vertrix_call(calls, RECORD_ACCESS_A, eax, edx, ebx, ecx, 0);
    if (!read_field(services, record, RECORD_COUNT, &count) ||
        !write_field(services, record, RECORD_COUNT, count + 1))
    {
        return 0;
    }
    return record;
}

uint32_t vertrix_rtl_record_set_argument(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services, uint32_t eax,
                                         uint32_t edx, uint32_t ebx, uint32_t ecx,
                                         uint32_t argument)
{
    uint32_t record = vertrix_call(calls, RECORD_ACCESS_B, eax, edx, ebx, ecx, 0);
    return write_field(services, record, RECORD_ARGUMENT, argument) ? record : 0;
}

uint32_t vertrix_rtl_record_mark(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t record = vertrix_call(calls, RECORD_INIT, eax, edx, ebx, ecx, 0);
    if (!write_field(services, record, RECORD_CLASS, RECORD_MARK_CLASS) ||
        !write_field(services, record, RECORD_FLAG, 1))
    {
        return 0;
    }
    return record;
}

uint32_t vertrix_rtl_record_clear(const VertrixFactoryServices *services, uint32_t record)
{
    static const uint32_t cleared[] = {0x1c, 0x20, 0x18, 0x4, 0x0, 0xc, 0x8, 0x10, 0x14};
    if (!write_field(services, record, RECORD_CLASS, RECORD_CLEAR_CLASS))
    {
        return 0;
    }
    for (size_t i = 0; i < sizeof cleared / sizeof cleared[0]; ++i)
    {
        if (!write_field(services, record, cleared[i], 0))
        {
            return 0;
        }
    }
    return record;
}

uint32_t vertrix_rtl_flagged_call(const VertrixCalls *calls, uint32_t flag, uint32_t direct,
                                  uint32_t fallback_ebx, uint32_t eax, uint32_t edx, uint32_t ebx,
                                  uint32_t ecx)
{
    if (flag != 0)
    {
        return vertrix_call(calls, direct, eax, edx, ebx, ecx, 0);
    }
    return vertrix_call(calls, FLAG_FALLBACK, eax, edx, fallback_ebx, ecx, 0);
}

uint32_t vertrix_rtl_pair_call(const VertrixCalls *calls, uint32_t first, uint32_t argument,
                               uint32_t ebx, uint32_t ecx)
{
    uint32_t result = vertrix_call(calls, first, 1, argument, ebx, ecx, 0);
    return vertrix_call(calls, 0x4ded70, result, argument, ebx, ecx, 0);
}

uint32_t vertrix_rtl_zero_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx, uint32_t ecx)
{
    return vertrix_call(calls, 0x4eb5c0, eax, 0, edx, ecx, 0);
}

uint32_t vertrix_rtl_deref_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                uint32_t pointed, uint32_t ecx)
{
    return vertrix_call(calls, 0x4d49a0, eax, edx, pointed, ecx, 0);
}

uint32_t vertrix_rtl_chain_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx, uint32_t ebx)
{
    uint32_t first = vertrix_call(calls, 0x4e0eaf, eax, edx, ebx, eax, 0);
    return vertrix_call(calls, 0x4e0ec7, first, eax, ebx, eax, 0);
}

int32_t vertrix_round_up(int32_t value, int32_t multiple)
{
    int32_t total = value + (multiple - 1);
    return total - total % multiple;
}

uint32_t vertrix_rtl_string_unique(const VertrixCalls *calls, uint32_t variable, uint32_t text,
                                   int32_t refcount, uint32_t ebx, uint32_t ecx)
{
    if (refcount < 0)
    {
        return vertrix_call(calls, 0x4ca370, variable, STRING_LITERAL_SOURCE, ebx, ecx, 0);
    }
    return vertrix_call(calls, 0x4ca110, variable, text - STRING_HEADER, ebx, ecx, 0);
}

uint32_t vertrix_rtl_string_reserve(const VertrixCalls *calls, uint32_t variable, uint32_t text,
                                    uint32_t edx, int32_t refcount, uint32_t capacity, uint32_t ebx)
{
    if (refcount > 1 || (int32_t)edx > (int32_t)capacity)
    {
        vertrix_call(calls, 0x4ca110, variable, edx, ebx, variable, 0);
        return vertrix_call(calls, 0x4ca0d0, variable, edx, ebx, variable, 0);
    }
    return text - STRING_HEADER;
}

uint32_t vertrix_rtl_stream_init(const VertrixFactoryServices *services, uint32_t object)
{
    static const uint32_t fields[][2] = {{0x0, 0x518cb4}, {0x4, 1},  {0x8, 0}, {0xc, 0},
                                         {0x10, 0},       {0x14, 1}, {0x18, 0}};
    for (size_t i = 0; i < sizeof fields / sizeof fields[0]; ++i)
    {
        if (!write_field(services, object, fields[i][0], fields[i][1]))
        {
            return 0;
        }
    }
    return object;
}

uint32_t vertrix_rtl_stream_init_derived(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services, uint32_t object,
                                         uint32_t ebx, uint32_t ecx)
{
    if (vertrix_rtl_stream_init(services, object) == 0 ||
        !write_field(services, object, 0, 0x518e24) || !write_field(services, object, 0x4c, 0) ||
        !write_field(services, object, 0x50, 0))
    {
        return 0;
    }
    vertrix_call(calls, 0x4cbf90, object, object, ebx, ecx, 0);
    return object;
}

uint32_t vertrix_rtl_block_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                uint32_t header)
{
    if (eax == 0)
    {
        return 0;
    }
    vertrix_call(calls, 0x4cea15, eax, header, edx, eax - 4, 0);
    return eax - 4;
}

uint32_t vertrix_rtl_terminate_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                    uint32_t ebx, char *buffer, size_t size)
{
    uint32_t length = vertrix_call(calls, 0x4df320, eax, edx, ebx, 0x4cd090, 0);
    if (length < size)
    {
        buffer[length] = 0;
    }
    return length;
}

uint32_t vertrix_rtl_local_call(const VertrixCalls *calls, uint32_t local, uint32_t eax,
                                uint32_t edx, uint32_t ebx)
{
    vertrix_call(calls, 0x4e0f8b, eax, edx, ebx, eax, 0);
    return vertrix_call(calls, 0x4cd8b0, eax, local, edx, eax, 0);
}

uint32_t vertrix_rtl_class_address(void)
{
    return 0x4cf9d0;
}

uint32_t vertrix_rtl_mode_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx, uint32_t ebx,
                               uint32_t ecx)
{
    return vertrix_call(calls, 0x4d67e4, eax, edx, ebx, (ecx & ~0xffu) | 0x9f, 0);
}

uint32_t vertrix_rtl_release_inner(const VertrixCalls *calls, uint32_t variable, uint32_t inner,
                                   uint32_t edx, uint32_t ebx)
{
    if (inner != 0)
    {
        vertrix_call(calls, 0x4ce9c0, variable, edx, ebx, variable, 0);
    }
    return variable;
}

uint32_t vertrix_rtl_record_forward(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                    uint32_t ecx)
{
    uint32_t record = vertrix_call(calls, RECORD_ACCESS_A, eax, edx, eax, ecx, 0);
    return vertrix_call(calls, 0x4dba20, record + 8, eax, eax, ecx, 0);
}

uint32_t vertrix_rtl_triple_call(const VertrixCalls *calls, uint32_t argument, uint32_t ebx,
                                 uint32_t ecx)
{
    uint32_t first = vertrix_call(calls, 0x4cf880, 1, argument, ebx, ecx, 0);
    uint32_t second = vertrix_call(calls, 0x4ded70, first, argument, ebx, first, 0);
    vertrix_call(calls, 0x4cce90, second, first, second, first, 0);
    return second;
}

uint32_t vertrix_rtl_write_text_call(const VertrixCalls *calls, uint32_t frame, uint32_t eax,
                                     uint32_t text, uint32_t length)
{
    vertrix_call(calls, 0x4d79c0, eax, frame - 0x18, 4, length, 0);
    return vertrix_call(calls, 0x4d79c0, eax, text, length, length, 0);
}

uint32_t vertrix_rtl_byte_local_call(const VertrixCalls *calls, uint32_t target, uint32_t local,
                                     uint32_t eax)
{
    vertrix_call(calls, target, eax, 1, local, eax, 0);
    return eax;
}

uint32_t vertrix_rtl_swapped_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                  uint32_t ebx)
{
    if (edx == 0)
    {
        return 0;
    }
    return vertrix_call(calls, 0x4d3010, edx, eax, ebx, edx, 0) != 0 ? edx : 0;
}

uint32_t vertrix_rtl_sign_compare(uint32_t a, uint32_t b)
{
    uint32_t edx = b;
    if ((a ^ b) < 0x80000000u)
    {
        uint32_t difference = a - b;
        if (difference == 0)
        {
            return 0;
        }
        uint32_t borrow = a < b ? 1u : 0u;
        edx = ~(b ^ ((borrow << 31) | (difference >> 1)));
    }
    return ((edx >> 31) != 0) ? 1u : 0xffffffffu;
}

uint32_t vertrix_rtl_static_init_call(const VertrixCalls *calls, uint32_t local, uint32_t table,
                                      uint32_t ebx, uint32_t ecx)
{
    return vertrix_call(calls, 0x4da71b, local, table, ebx, ecx, 0);
}

uint32_t vertrix_rtl_ebx_from_edx_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                       uint32_t ecx)
{
    return vertrix_call(calls, 0x4dad38, eax, edx, edx, ecx, 0);
}

uint32_t vertrix_rtl_sign_of(uint32_t value)
{
    if (value == 0)
    {
        return 0;
    }
    return (int32_t)value < 0 ? 0xffffffffu : 1u;
}

uint32_t vertrix_rtl_stack_pair_call(const VertrixCalls *calls, uint32_t target, uint32_t local,
                                     uint32_t first, uint32_t second, uint32_t ecx)
{
    return vertrix_call(calls, target, first, second, local, ecx, 0);
}

uint32_t vertrix_rtl_flags_call(const VertrixCalls *calls, uint32_t local, uint32_t edx,
                                uint32_t ebx, uint32_t ecx)
{
    uint32_t kind = ebx & 0x1f;
    uint32_t flags = (kind == 8 || edx != 0) ? 0x1040u : 0x1080u;
    return vertrix_call(calls, 0x4dad38, kind | flags, local, local, ecx, 0);
}

uint32_t vertrix_rtl_scratch_triple_call(const VertrixCalls *calls, uint32_t pair, uint32_t scratch,
                                         uint32_t eax, uint32_t ebx, uint32_t ecx)
{
    vertrix_call(calls, 0x4e53b4, pair, scratch, ebx, ecx, 0);
    vertrix_call(calls, 0x4db131, scratch, scratch, ebx, ecx, 0);
    vertrix_call(calls, 0x4e543c, scratch, pair, ebx, ecx, 0);
    return eax;
}

uint32_t vertrix_rtl_zero_call3(const VertrixCalls *calls, uint32_t ecx)
{
    vertrix_call(calls, 0x4da3ba, 0, 0, 0, ecx, 0);
    return 0;
}

enum
{
    SLACK_TOTAL = 4,
    SLACK_KIND = 0x16,
    SLACK_FLAGS = 0x1e,
    SLACK_FIRST = 0x20,
    SLACK_PARTS = 6,
    SLACK_SKIP = 8,
    SLACK_KIND_VALUE = 0x30,
    TABLE_CLASS = 0x51bb54,
    TABLE_INITIAL = 0x11,
    PROBE_HANDLE = 0x94,
    PROBE_BUFFER = 0x14,
    PROBE_STATE = 0xc,
    PROBE_RESULT = 0x10,
    PROBE_LENGTH = 0x80,
    PROBE_ARGUMENTS = 3,
    DOUBLE_BIAS = 0x3ff,
    FLOAT_BIAS = 0x7f,
    FLOAT_FULL = 0x96,
    FLOAT_LIMIT = 0x9f,
    SHIFT_MASK = 0x1f,
    STRING_LENGTH = 4,
    STRING_CAPACITY = 8,
    BUFFER_STREAM_CLASS = 0x519664,
    BUFFER_STREAM_STORAGE = 0x1c,
    BUFFER_STREAM_CAPACITY = 0x20,
    CHAIN_PARENT = 0x10,
    TABLE_VALUE = 0xc,
    LINK_SLOT = 0x38,
    LINK_TABLE = 0x34,
    LINK_TABLE_BIAS = 0x20,
    LINK_KEY = 0x1c,
    LINK_BACK = 0x24,
    LINK_NESTED_FRAME = 12,
    RANGE_ENTRY = 0x20,
    DERIVED_CLASS = 0x514284,
    DERIVED_FLAG = 0xc8,
    DERIVED_FIELD = 0xd8,
    EVENT_TABLE_FIRST = 0x38,
    EVENT_TABLE_SECOND = 0x1c,
    EVENT_TABLE_FIRST_CHUNK = 0xa,
    EVENT_TABLE_SECOND_CHUNK = 4,
    EVENT_TABLE_RESERVE = 7,
    TEST_LOCK = 0x50817e,
    EXPONENT_MASK = 0x7ff0,
    EXPONENT_SHIFT = 4,
    EXPONENT_OFFSET = 0x3fe,
    MANTISSA_SIGN_MASK = 0x800f,
    EXPONENT_HALF = 0x3fe0,
    DECIMAL_BASE = 10,
    SIGN_BIT = 0x80000000u,
    FLAG_WORD = 0x1e,
    FLAG_PAD = 0x16,
    FLAG_LEFT = 8,
    FLAG_ALTERNATE = 1,
    FLAG_SIGN = 4,
    FLAG_SPACE = 2,
    RECORD_COPY_SIZE = 0x34,
    PREFIX_WORDS = 1,
    RLE_RUN_MARK = 0xc0,
    RLE_ERROR_TEXT = 0x50f725,
    PATH_A_COPY = 0x5ba0e0,
    PATH_A_FIRST = 0x5ba1e8,
    PATH_A_SECOND = 0x5ba1f0,
    PATH_B_COPY = 0x5baa08,
    PATH_B_FIRST = 0x5bab10,
    PATH_B_SECOND = 0x5bab18,
    PATH_B_THIRD = 0x5bac18,
    PATH_B_STACK = 0x5bad18,
    PATH_C_COPY = 0x5b9cd0,
    PATH_C_FIRST = 0x5b9dd8,
    PATH_C_SECOND = 0x5b9de0,
    PATH_C_THIRD = 0x5b9ee0,
    PATH_C_STACK = 0x5b9fe0,
    CHUNK_FIELDS = 7,
    LIST_HEAD = 4,
    STRING_MEMBER = 0x1c,
    STRING_FLAG = 0x38,
    LIST_FIELDS = 4,
    FLAG_FIELDS = 2,
    LIST_CLASS = 0x51b5d4,
    FLAG_CLASS = 0x517474
};

uint32_t vertrix_rtl_construct_list(uint32_t object, uint8_t *storage)
{
    uint32_t fields[LIST_FIELDS] = {LIST_CLASS, 0, 0, 0};
    memcpy(storage, fields, sizeof fields);
    return object;
}

uint32_t vertrix_rtl_construct_flag(uint32_t object, uint8_t *storage)
{
    uint32_t fields[FLAG_FIELDS] = {FLAG_CLASS, 1};
    memcpy(storage, fields, sizeof fields);
    return object;
}

void vertrix_rtl_select_float_helpers(uint8_t fast_flag, uint8_t mode_flags, uint32_t table[3])
{
    if (fast_flag != 0)
    {
        table[0] = 0x4d80b7;
        table[1] = 0x4d8188;
        table[2] = (mode_flags & 1) != 0 ? 0x4d8204 : 0x4d8217;
    }
    else
    {
        table[0] = 0x4d80d5;
        table[1] = 0x4d8198;
        table[2] = 0x4d8227;
    }
}

uint32_t vertrix_rtl_construct_chunk_list(uint32_t object, uint8_t *storage, uint32_t class_pointer,
                                          uint32_t chunk_size)
{
    uint32_t fields[CHUNK_FIELDS] = {class_pointer, 0, 0, 0, 0, 0, chunk_size};
    memcpy(storage, fields, sizeof fields);
    return object;
}

static uint32_t release_member(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t object, uint32_t member, uint32_t target, uint32_t edx,
                               uint32_t clear_always)
{
    uint32_t held = 0;
    read_field(services, object, member, &held);
    if (held != 0)
    {
        uint32_t result = vertrix_call(calls, target, 0, edx, held, object, 0);
        if (result != 0)
        {
            uint32_t pointer = 0;
            read_field(services, object, member, &pointer);
            vertrix_call(calls, 0x4df1c0, result, pointer, held, object, 0);
        }
    }
    if (clear_always != 0 || held != 0)
    {
        write_field(services, object, member, 0);
    }
    return held;
}

uint32_t vertrix_rtl_release_list_head(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t object,
                                       uint32_t edx)
{
    return release_member(calls, services, object, LIST_HEAD, 0x4ddbe0, edx, 1);
}

uint32_t vertrix_rtl_release_string_member(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services, uint32_t object,
                                           uint32_t edx)
{
    uint32_t held = release_member(calls, services, object, STRING_MEMBER, 0x4cf880, edx, 0);
    write_field(services, object, STRING_FLAG, 0);
    return held;
}

uint32_t vertrix_rtl_lookup_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, uint32_t table, uint32_t ebx, uint32_t ecx)
{
    uint32_t key = 0;
    read_field(services, object, 0, &key);
    if (key == 0 || table == 0)
    {
        return 0;
    }
    return vertrix_call(calls, 0x4dbcd0, table, key, ebx, ecx, 0);
}

uint32_t vertrix_rtl_distribute_slack(uint32_t object, uint8_t *storage, size_t size)
{
    uint32_t total = 0;
    uint32_t parts[SLACK_PARTS] = {0};
    uint32_t flags = 0;
    uint32_t kind = 0;
    vertrix_actor_storage_read(storage, size, SLACK_FLAGS, 1, &flags);
    vertrix_actor_storage_read(storage, size, SLACK_KIND, 1, &kind);
    if ((flags & SLACK_SKIP) != 0 || kind != SLACK_KIND_VALUE)
    {
        return object;
    }
    vertrix_actor_storage_read(storage, size, SLACK_TOTAL, DWORD_WIDTH, &total);
    for (unsigned i = 0; i < SLACK_PARTS; i++)
    {
        vertrix_actor_storage_read(storage, size, SLACK_FIRST + DWORD_WIDTH * i, DWORD_WIDTH,
                                   &parts[i]);
        total -= parts[i];
    }
    if ((int32_t)total > 0)
    {
        vertrix_actor_storage_write(storage, size, SLACK_FIRST + DWORD_WIDTH, DWORD_WIDTH,
                                    parts[1] + total);
    }
    return object;
}

uint32_t vertrix_rtl_construct_table(uint32_t object, uint8_t *storage, uint32_t chunk_size)
{
    uint32_t fields[CHUNK_FIELDS] = {TABLE_CLASS, 0, TABLE_INITIAL, 0, 0, 0, chunk_size};
    memcpy(storage, fields, sizeof fields);
    return object;
}

uint32_t vertrix_rtl_probe_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t object, uint32_t edx, uint32_t ecx)
{
    uint32_t handle = 0;
    uint32_t stack[PROBE_ARGUMENTS];
    read_field(services, object, PROBE_HANDLE, &handle);
    stack[0] = handle;
    stack[1] = object + PROBE_BUFFER;
    stack[2] = PROBE_LENGTH;
    write_field(services, object, PROBE_STATE, 1);
    uint32_t result = vertrix_calln(calls, 0x4db950, object + PROBE_BUFFER, edx, object, ecx, stack,
                                    PROBE_ARGUMENTS, NULL);
    uint32_t flag = result != 0 ? 1u : 0u;
    write_field(services, object, PROBE_RESULT, flag);
    return flag;
}

uint64_t vertrix_rtl_integer_to_double(uint32_t value)
{
    if (value == 0)
    {
        return 0;
    }
    uint32_t top = 31;
    while ((value >> top) == 0)
    {
        top--;
    }
    uint32_t shifted = (value << (31 - top)) << 1;
    uint32_t high = ((shifted & 0xfffff000u) | (top + DOUBLE_BIAS));
    high = (high >> 12) | (high << 20);
    return ((uint64_t)high << 32) | (shifted << 20);
}

uint32_t vertrix_rtl_float_to_integer(uint32_t bits, uint8_t limit)
{
    if (bits == 0)
    {
        return 0;
    }
    uint32_t doubled = bits << 1;
    uint8_t exponent = (uint8_t)(doubled >> 24);
    if (exponent < FLOAT_BIAS)
    {
        return 0;
    }
    uint32_t rotated = (doubled << 8) | (doubled >> 24);
    uint32_t value = (0x80000000u | (rotated >> 1)) >> 8;
    if (exponent >= limit)
    {
        return 0xffffffffu >> ((uint8_t)(FLOAT_LIMIT - limit) & SHIFT_MASK);
    }
    if (exponent < FLOAT_FULL)
    {
        return value >> ((uint8_t)(FLOAT_FULL - exponent) & SHIFT_MASK);
    }
    return value << ((uint8_t)(exponent - FLOAT_FULL) & SHIFT_MASK);
}

uint32_t vertrix_rtl_string_append_pair(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t variable,
                                        uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t text)
{
    uint32_t pointer = 0;
    if (edx + ecx == 0)
    {
        return variable;
    }
    vertrix_call(calls, 0x4ca0d0, variable, edx + ecx, ebx, ecx, 0);
    read_field(services, variable, 0, &pointer);
    vertrix_call(calls, 0x4eb5e0, pointer, ebx, edx, ecx, 0);
    read_field(services, variable, 0, &pointer);
    return vertrix_call(calls, 0x4eb5e0, pointer + edx, text, ecx, ecx, 0);
}

uint32_t vertrix_rtl_string_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t variable, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t source = vertrix_call(calls, 0x4ca060, variable, edx, ebx, ecx, 0);
    uint32_t pointer = 0;
    read_field(services, source, 0, &pointer);
    write_field(services, variable, 0, pointer);
    if ((int32_t)ebx >= 1)
    {
        vertrix_call(calls, 0x4ca0d0, variable, ebx, ebx, ecx, 0);
        read_field(services, variable, 0, &pointer);
        vertrix_call(calls, 0x4eb5c0, pointer, (uint32_t)(int32_t)(int8_t)edx, ebx, ecx, 0);
    }
    return variable;
}

uint32_t vertrix_rtl_string_copy_pair(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services, uint32_t first,
                                      uint32_t second, uint32_t ebx, uint32_t ecx, uint32_t extra)
{
    uint32_t sum = extra + ebx;
    uint32_t pointer = 0;
    if (sum == 0)
    {
        uint32_t source = vertrix_call(calls, 0x4ca060, first, 0, ebx, ecx, 0);
        read_field(services, source, 0, &pointer);
        write_field(services, second, 0, pointer);
        return pointer;
    }
    vertrix_call(calls, 0x4ca0d0, second, sum, ebx, ecx, 0);
    uint32_t base = 0;
    read_field(services, first, 0, &base);
    read_field(services, second, 0, &pointer);
    return vertrix_call(calls, 0x4eb5e0, pointer, base + ecx, ebx, ecx, 0);
}

uint32_t vertrix_rtl_string_unique_size(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t variable,
                                        uint32_t edx, uint32_t ebx)
{
    uint32_t pointer = 0;
    uint32_t references = 0;
    uint32_t capacity = 0;
    read_field(services, variable, 0, &pointer);
    read_field(services, pointer - STRING_HEADER, 0, &references);
    read_field(services, pointer - STRING_HEADER, STRING_CAPACITY, &capacity);
    if ((int32_t)references <= 1 && (int32_t)edx <= (int32_t)capacity)
    {
        return pointer;
    }
    uint32_t header = pointer - STRING_HEADER;
    uint32_t length = 0;
    read_field(services, header, STRING_LENGTH, &length);
    uint32_t size = (int32_t)edx < (int32_t)length ? length : edx;
    vertrix_call(calls, 0x4ca0d0, variable, size, ebx, length, 0);
    read_field(services, variable, 0, &pointer);
    vertrix_call(calls, 0x4eb5e0, pointer, header + STRING_HEADER, length + 1, length, 0);
    read_field(services, variable, 0, &pointer);
    write_field(services, pointer - STRING_HEADER, STRING_LENGTH, length);
    vertrix_call(calls, 0x4ca150, pointer - STRING_HEADER, header + STRING_HEADER, length + 1,
                 length, header);
    read_field(services, variable, 0, &pointer);
    return pointer;
}

uint32_t vertrix_rtl_string_set_length(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t variable,
                                       uint32_t length)
{
    uint32_t pointer = vertrix_rtl_string_unique_size(calls, services, variable, length, length);
    read_field(services, variable, 0, &pointer);
    write_field(services, pointer - STRING_HEADER, STRING_LENGTH, length);
    void *storage;
    size_t size;
    if (services->resolve(pointer - STRING_HEADER, &storage, &size, services->context))
    {
        vertrix_actor_storage_write(storage, size, STRING_HEADER + length, 1, 0);
    }
    read_field(services, variable, 0, &pointer);
    return pointer;
}

uint32_t vertrix_rtl_construct_buffer_stream(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             uint32_t object, uint32_t size, int store_size)
{
    if (vertrix_rtl_stream_init(services, object) == 0 ||
        !write_field(services, object, 0, BUFFER_STREAM_CLASS))
    {
        return 0;
    }
    vertrix_call(calls, 0x4eb5c0, object + BUFFER_STREAM_STORAGE, 0, BUFFER_STREAM_CAPACITY, object,
                 0);
    if (store_size != 0 && !write_field(services, object, BUFFER_STREAM_STORAGE, size))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_rtl_string_make_unique(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t variable,
                                        uint32_t edx)
{
    uint32_t pointer = 0;
    uint32_t references = 0;
    read_field(services, variable, 0, &pointer);
    uint32_t header = pointer - STRING_HEADER;
    read_field(services, header, 0, &references);
    if ((int32_t)references <= 1)
    {
        return variable;
    }
    uint32_t length = 0;
    vertrix_call(calls, 0x4ca110, variable, edx, header, variable, 0);
    read_field(services, header, STRING_LENGTH, &length);
    vertrix_call(calls, 0x4ca0d0, variable, length, header, variable, 0);
    read_field(services, header, STRING_LENGTH, &length);
    read_field(services, variable, 0, &pointer);
    return vertrix_call(calls, 0x4eb5e0, pointer, header + STRING_HEADER, length + 1, pointer, 0);
}

uint32_t vertrix_rtl_class_chain_contains(const VertrixFactoryServices *services, uint32_t start,
                                          uint32_t target)
{
    uint32_t current = start;
    while (current != 0)
    {
        if (current == target)
        {
            return 1;
        }
        uint32_t next = 0;
        if (!read_field(services, current, CHAIN_PARENT, &next))
        {
            return 0;
        }
        current = next;
    }
    return 0;
}

uint32_t vertrix_rtl_wide_length(const uint16_t *text)
{
    uint32_t length = 0;
    while (text[length] != 0)
    {
        length++;
    }
    return length;
}

uint32_t vertrix_rtl_ancestor_search(const VertrixCalls *calls, uint32_t eax, uint32_t ecx,
                                     uint32_t candidate, uint32_t start)
{
    if (candidate == start)
    {
        return 1;
    }
    uint32_t current = eax;
    uint32_t edx = start;
    for (;;)
    {
        uint32_t next = vertrix_call(calls, 0x4d1890, current, edx, candidate, ecx, edx);
        if (next == 0)
        {
            return 0;
        }
        if (next == candidate)
        {
            return 1;
        }
        current = next;
        edx = next;
    }
}

uint32_t vertrix_rtl_table_lookup_value(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t local,
                                        uint32_t eax, uint32_t edx, uint32_t out)
{
    uint32_t entry = vertrix_call(calls, 0x4df0f0, eax, edx, local, out, 0);
    uint32_t value = 0;
    if (entry == 0)
    {
        return 0;
    }
    read_field(services, entry, TABLE_VALUE, &value);
    write_field(services, out, 0, value);
    return 1;
}

uint32_t vertrix_rtl_forward_pair(const VertrixCalls *calls, uint32_t edx, uint32_t ebx,
                                  uint32_t ecx, uint32_t first, uint32_t second)
{
    if (first == 0)
    {
        return 0;
    }
    uint32_t arguments[3] = {first, first, second};
    uint32_t result = vertrix_calln(calls, 0x4d9ae0, first, edx, ebx, ecx, arguments, 3, NULL);
    return vertrix_calln(calls, 0x4d9a10, result, edx, ebx, ecx, &result, 1, NULL);
}

uint32_t vertrix_rtl_link_owner(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t frame_local, uint32_t owner, uint32_t member)
{
    uint32_t linked = 0;
    uint32_t table = 0;
    uint32_t key = 0;
    if (owner == 0 || !read_field(services, owner, LINK_SLOT, &linked) || linked != 0 ||
        member == 0 || !read_field(services, member, LINK_TABLE, &table) || table == 0)
    {
        return owner;
    }
    read_field(services, owner, LINK_KEY, &key);
    uint32_t entry = vertrix_call(calls, 0x4df0f0, table + LINK_TABLE_BIAS, key,
                                  frame_local - LINK_NESTED_FRAME, frame_local, 0);
    uint32_t target = 0;
    if (entry == 0 || !read_field(services, entry, TABLE_VALUE, &target))
    {
        return 0;
    }
    uint32_t previous = 0;
    uint32_t previous_slot = 0;
    read_field(services, target, LINK_BACK, &previous);
    if (previous != 0 && read_field(services, previous, LINK_SLOT, &previous_slot) &&
        previous_slot == target)
    {
        write_field(services, previous, LINK_SLOT, 0);
    }
    write_field(services, owner, LINK_SLOT, target);
    write_field(services, target, LINK_BACK, owner);
    return target;
}

uint32_t vertrix_rtl_range_table_find(const uint8_t *table, size_t size, uint32_t base,
                                      uint32_t first, uint32_t second, uint32_t value)
{
    for (size_t offset = 0; offset + RANGE_ENTRY <= size; offset += RANGE_ENTRY)
    {
        uint32_t key_first, key_second, low, high, used;
        vertrix_actor_storage_read(table, size, offset, DWORD_WIDTH, &key_first);
        vertrix_actor_storage_read(table, size, offset + 4, DWORD_WIDTH, &key_second);
        vertrix_actor_storage_read(table, size, offset + 8, DWORD_WIDTH, &low);
        vertrix_actor_storage_read(table, size, offset + 0xc, DWORD_WIDTH, &high);
        vertrix_actor_storage_read(table, size, offset + 0x10, DWORD_WIDTH, &used);
        if (used == 0)
        {
            return 0;
        }
        if (first == key_first && second == key_second && value >= low && value <= high)
        {
            return base + (uint32_t)offset;
        }
    }
    return 0;
}

uint32_t vertrix_rtl_bracket_call(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                  uint32_t ebx, uint32_t ecx)
{
    uint32_t value = vertrix_call(calls, 0x4db507, eax, edx, eax, edx, 0);
    value = vertrix_call(calls, 0x4db6a4, value, edx, ebx, ecx, 0);
    return vertrix_call(calls, 0x4db507, value, edx, eax, edx, 0);
}

uint32_t vertrix_rtl_construct_derived_stream(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services, uint32_t eax,
                                              uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t object = vertrix_call(calls, 0x4d3e20, eax, edx, ebx, ecx, 0);
    void *storage;
    size_t size;
    if (!write_field(services, object, 0, DERIVED_CLASS) ||
        !services->resolve(object, &storage, &size, services->context) ||
        !vertrix_actor_storage_write(storage, size, DERIVED_FLAG, 1, 0) ||
        !write_field(services, object, DERIVED_FIELD, 0))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_rtl_construct_event_table(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services, uint32_t object,
                                           uint32_t first, uint32_t second, uint32_t ecx)
{
    void *storage;
    size_t size;
    if (!services->resolve(object, &storage, &size, services->context) ||
        size < EVENT_TABLE_SECOND + CHUNK_FIELDS * DWORD_WIDTH)
    {
        return 0;
    }
    vertrix_rtl_construct_table(object, storage, EVENT_TABLE_FIRST_CHUNK);
    vertrix_rtl_construct_table(object + EVENT_TABLE_SECOND,
                                (uint8_t *)storage + EVENT_TABLE_SECOND, EVENT_TABLE_SECOND_CHUNK);
    vertrix_call(calls, 0x4def50, object + EVENT_TABLE_SECOND, EVENT_TABLE_RESERVE, 0, ecx, 0);
    return write_field(services, object, EVENT_TABLE_FIRST, first) &&
                   write_field(services, object, EVENT_TABLE_FIRST + DWORD_WIDTH, second) &&
                   write_field(services, object, EVENT_TABLE_FIRST + 2 * DWORD_WIDTH, ecx)
               ? object
               : 0;
}

uint32_t vertrix_rtl_store_in_slot(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t eax,
                                   uint32_t ebx, uint32_t ecx)
{
    uint32_t slot = vertrix_call(calls, 0x4d85f0, eax, eax, ebx, ecx, 0);
    if (slot != 0)
    {
        write_field(services, slot, 0, eax);
    }
    return slot;
}

uint32_t vertrix_rtl_vararg_call(const VertrixCalls *calls, uint32_t local, uint32_t first,
                                 uint32_t second, uint32_t third)
{
    return vertrix_call(calls, 0x4cd56c, first, second, third, local, 0);
}

static int read_byte(const VertrixFactoryServices *services, uint32_t object, uint8_t *value)
{
    void *storage;
    size_t size;
    uint32_t wide = 0;
    if (!services->resolve(object, &storage, &size, services->context) ||
        !vertrix_actor_storage_read(storage, size, 0, 1, &wide))
    {
        return 0;
    }
    *value = (uint8_t)wide;
    return 1;
}

uint32_t vertrix_rtl_test_and_set(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t mask)
{
    uint8_t flags = 0;
    uint32_t result = 1;
    if (!read_byte(services, object, &flags))
    {
        return 0;
    }
    if ((flags & mask) != 0)
    {
        return 1;
    }
    vertrix_call(calls, 0x4e14b0, TEST_LOCK, mask, 1, object, 0);
    read_byte(services, object, &flags);
    if ((flags & mask) == 0)
    {
        void *storage;
        size_t size;
        result = 0;
        if (services->resolve(object, &storage, &size, services->context))
        {
            vertrix_actor_storage_write(storage, size, 0, 1, (uint8_t)(flags | (uint8_t)mask));
        }
    }
    vertrix_call(calls, 0x4e14b7, TEST_LOCK, mask, result, object, 0);
    return result;
}

uint32_t vertrix_rtl_local_chain_call(const VertrixCalls *calls, uint32_t local, uint32_t eax,
                                      uint32_t edx, uint32_t ebx, uint32_t chain)
{
    vertrix_call(calls, 0x4e0f8b, eax, edx, ebx, eax, 0);
    return vertrix_call(calls, 0x4cd8b0, eax, local, chain, eax, 0);
}

uint32_t vertrix_rtl_string_concat(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t result,
                                   uint32_t first, uint32_t second, uint32_t ebx, uint32_t ecx)
{
    uint32_t first_text = 0;
    uint32_t second_text = 0;
    uint32_t first_length = 0;
    uint32_t second_length = 0;
    vertrix_call(calls, 0x4ca070, result, second, ebx, ecx, 0);
    read_field(services, second, 0, &second_text);
    read_field(services, second_text - STRING_HEADER, STRING_LENGTH, &second_length);
    read_field(services, first, 0, &first_text);
    read_field(services, first_text - STRING_HEADER, STRING_LENGTH, &first_length);
    vertrix_rtl_string_append_pair(calls, services, result, first_length, first_text, second_length,
                                   second_text);
    return result;
}

uint64_t vertrix_rtl_split_exponent(uint32_t low, uint32_t high, uint32_t *exponent)
{
    int32_t biased = 0;
    if (high != 0)
    {
        uint32_t word = high >> 16;
        biased = (int32_t)((word & EXPONENT_MASK) >> EXPONENT_SHIFT) - EXPONENT_OFFSET;
        high = (high & 0xffffu) | (((word & MANTISSA_SIGN_MASK) | EXPONENT_HALF) << 16);
    }
    *exponent = (uint32_t)biased;
    return ((uint64_t)high << 32) | low;
}

static int is_space(uint8_t character)
{
    return character == ' ' || (character >= '\t' && character <= '\r');
}

uint32_t vertrix_rtl_parse_integer(const uint8_t *text)
{
    uint32_t value = 0;
    uint8_t sign;
    while (is_space(*text))
    {
        text++;
    }
    sign = *text;
    if (sign == '+' || sign == '-')
    {
        text++;
    }
    while (*text >= '0' && *text <= '9')
    {
        value = value * DECIMAL_BASE + *text - '0';
        text++;
    }
    return sign == '-' ? 0u - value : value;
}

uint32_t vertrix_rtl_copy_terminated(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t destination,
                                     uint32_t source, uint32_t limit, uint32_t capacity)
{
    if (destination == 0)
    {
        return 0;
    }
    uint32_t count = (int32_t)limit > (int32_t)capacity ? capacity : limit;
    uint32_t length = vertrix_call(calls, 0x4e39a0, source, count, limit, capacity, 0);
    vertrix_call(calls, 0x4e39d0, destination, source, length, length, 0);
    uint32_t end = vertrix_call(calls, 0x4e39f0, destination, length, length, length, 0);
    void *storage;
    size_t size;
    if (services->resolve(destination, &storage, &size, services->context))
    {
        vertrix_actor_storage_write(storage, size, end, 1, 0);
    }
    return end;
}

static uint8_t text_byte(const VertrixFactoryServices *services, uint32_t header, uint32_t address)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (services->resolve(header, &storage, &size, services->context) &&
        vertrix_actor_storage_read(storage, size, address - header, 1, &value))
    {
        return (uint8_t)value;
    }
    return 0;
}

uint32_t vertrix_rtl_string_trim_end(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t variable,
                                     uint32_t edx, uint32_t ebx)
{
    uint32_t text = 0;
    uint32_t result = vertrix_rtl_string_make_unique(calls, services, variable, edx);
    read_field(services, variable, 0, &text);
    uint32_t header = text - STRING_HEADER;
    uint32_t pointer = text;
    uint32_t run_start = 0;
    if (text_byte(services, header, pointer) != 0)
    {
        do
        {
            uint32_t character = (uint32_t)(int32_t)(int8_t)text_byte(services, header, pointer);
            if (vertrix_call(calls, 0x4e10d0, character, pointer, ebx, run_start, 0) != 0)
            {
                run_start = run_start == 0 ? pointer : run_start;
            }
            else
            {
                run_start = 0;
            }
            result = vertrix_call(calls, 0x4e1054, pointer, pointer, ebx, run_start, 0);
            pointer = result;
        } while (text_byte(services, header, pointer) != 0);
    }
    if (run_start == 0)
    {
        return result;
    }
    void *storage;
    size_t size;
    if (services->resolve(header, &storage, &size, services->context))
    {
        vertrix_actor_storage_write(storage, size, run_start - header, 1, 0);
    }
    write_field(services, header, STRING_LENGTH, run_start - text);
    return header;
}

uint32_t vertrix_rtl_string_trim_start(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t variable,
                                       uint32_t edx, uint32_t ebx)
{
    uint32_t text = 0;
    uint32_t length = 0;
    vertrix_rtl_string_make_unique(calls, services, variable, edx);
    read_field(services, variable, 0, &text);
    uint32_t header = text - STRING_HEADER;
    uint32_t pointer = text;
    for (;;)
    {
        uint32_t character = (uint32_t)(int32_t)(int8_t)text_byte(services, header, pointer);
        if (vertrix_call(calls, 0x4e10d0, character, pointer, ebx, variable, 0) == 0)
        {
            break;
        }
        pointer = vertrix_call(calls, 0x4e1054, pointer, pointer, ebx, variable, 0);
    }
    read_field(services, variable, 0, &text);
    read_field(services, text - STRING_HEADER, STRING_LENGTH, &length);
    length -= pointer - text;
    vertrix_call(calls, 0x4e1140, text, pointer, length + 1, variable, 0);
    read_field(services, variable, 0, &text);
    write_field(services, text - STRING_HEADER, STRING_LENGTH, length);
    return text - STRING_HEADER;
}

uint32_t vertrix_rtl_segment_dispatch(const VertrixCalls *calls, uint32_t eax, uint32_t edx,
                                      uint32_t data_segment)
{
    if (vertrix_call(calls, 0x4e6220, eax, data_segment, eax, edx, 0) != 0)
    {
        return vertrix_call(calls, 0x4eb4d4, edx, data_segment, eax, edx, 0);
    }
    return vertrix_call(calls, 0x4e6250, eax, edx, eax, edx, 0);
}

uint64_t vertrix_rtl_negate_double(uint32_t low, uint32_t high)
{
    if (low != 0 || high != 0)
    {
        high ^= SIGN_BIT;
    }
    return ((uint64_t)high << 32) | low;
}

uint64_t vertrix_rtl_absolute_double(uint32_t low, uint32_t high)
{
    if ((int32_t)high < 0)
    {
        return vertrix_rtl_negate_double(low, high);
    }
    return ((uint64_t)high << 32) | low;
}

uint32_t vertrix_rtl_parse_format_flags(const uint8_t *text, uint32_t base, uint8_t *storage,
                                        size_t size)
{
    uint32_t flags = 0;
    uint32_t offset = 0;
    for (;; offset++)
    {
        uint8_t character = text[offset];
        if (character == '-')
        {
            flags |= FLAG_LEFT;
        }
        else if (character == '#')
        {
            flags |= FLAG_ALTERNATE;
        }
        else if (character == '+')
        {
            flags = (flags | FLAG_SIGN) & ~(uint32_t)FLAG_SPACE;
        }
        else if (character == ' ')
        {
            if ((flags & FLAG_SIGN) == 0)
            {
                flags |= FLAG_SPACE;
            }
        }
        else if (character == '0')
        {
            vertrix_actor_storage_write(storage, size, FLAG_PAD, 1, character);
        }
        else
        {
            break;
        }
    }
    vertrix_actor_storage_write(storage, size, FLAG_WORD, 2, 0);
    vertrix_actor_storage_write(storage, size, FLAG_WORD, 1, flags & 0xff);
    return base + offset;
}

uint32_t vertrix_rtl_string_tail(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t source, uint32_t destination, uint32_t start,
                                 uint32_t ecx)
{
    uint32_t text = 0;
    uint32_t length = 0;
    uint32_t from = start;
    read_field(services, source, 0, &text);
    read_field(services, text - STRING_HEADER, STRING_LENGTH, &length);
    if ((int32_t)from < 0)
    {
        from = 0;
    }
    else if ((int32_t)from > (int32_t)length)
    {
        from = length;
    }
    vertrix_call(calls, 0x4ca070, destination, destination, from, ecx, 0);
    read_field(services, source, 0, &text);
    read_field(services, text - STRING_HEADER, STRING_LENGTH, &length);
    vertrix_rtl_string_copy_pair(calls, services, source, destination, from, length - from, 0);
    return destination;
}

uint32_t vertrix_record_copy(uint32_t destination, uint8_t *destination_storage,
                             const uint8_t *source_storage)
{
    memcpy(destination_storage, source_storage, RECORD_COPY_SIZE);
    return destination;
}

void vertrix_record_prefix_sum(uint32_t count, uint32_t flags, uint8_t *data)
{
    uint32_t sum = 0;
    if ((flags & PREFIX_WORDS) != 0)
    {
        for (uint32_t i = 0; i < count / 2; i++)
        {
            uint16_t value;
            memcpy(&value, data + 2 * i, sizeof value);
            value = (uint16_t)(value + (uint16_t)sum);
            memcpy(data + 2 * i, &value, sizeof value);
            sum = value;
        }
        return;
    }
    for (uint32_t i = 0; i < count; i++)
    {
        data[i] = (uint8_t)(data[i] + (uint8_t)sum);
        sum = data[i];
    }
}

typedef struct RleState
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
} RleState;

static uint32_t rle_read(const VertrixCalls *calls, RleState *state, uint32_t stream,
                         uint32_t local)
{
    uint32_t value = 0;
    state->edx = local;
    state->ebx = 1;
    state->ecx = 1;
    state->eax = vertrix_calln(calls, 0x48a930, stream, local, 1, 1, NULL, 0, &value);
    return value & 0xff;
}

uint32_t vertrix_rle_decode(const VertrixCalls *calls, uint32_t local, uint32_t stream,
                            uint32_t destination, uint32_t remaining, uint32_t expected,
                            uint8_t *output)
{
    RleState state = {stream, destination, remaining, expected};
    size_t offset = 0;
    if (remaining != 0)
    {
        do
        {
            uint32_t byte = rle_read(calls, &state, stream, local);
            uint32_t count = 1;
            state.eax = --remaining;
            if (byte >= RLE_RUN_MARK)
            {
                count = byte - RLE_RUN_MARK;
                byte = rle_read(calls, &state, stream, local);
                remaining--;
            }
            state.edx = 0xffffffffu;
            while (count != 0)
            {
                output[offset++] = (uint8_t)byte;
                expected--;
                state.ecx = expected;
                state.eax = (state.eax & ~0xffu) | byte;
                count--;
            }
        } while (remaining != 0);
    }
    if (expected != 0)
    {
        uint32_t stack[1] = {RLE_ERROR_TEXT};
        vertrix_calln(calls, 0x4d85c0, state.eax, state.edx, state.ebx, state.ecx, stack, 1, NULL);
        vertrix_call(calls, 0x4eb4d4, 1, state.edx, state.ebx, state.ecx, 0);
    }
    return 0;
}

uint32_t vertrix_rle_decode_bitmap(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t local,
                                   uint32_t stream, uint32_t width, uint32_t height, uint32_t ecx,
                                   uint8_t *output)
{
    uint32_t remaining = width * height;
    uint32_t bitmap = vertrix_call(calls, 0x478d10, width, height, 1, ecx, 0);
    uint32_t destination = 0;
    size_t offset = 0;
    read_field(services, bitmap, 0, &destination);
    while (remaining != 0)
    {
        uint32_t value = 0;
        uint32_t byte;
        uint32_t count = 1;
        vertrix_calln(calls, 0x48a930, stream, local, 1, 1, NULL, 0, &value);
        byte = value & 0xff;
        if (byte >= RLE_RUN_MARK)
        {
            count = byte - RLE_RUN_MARK;
            vertrix_calln(calls, 0x48a930, stream, local, 1, 1, NULL, 0, &value);
            byte = value & 0xff;
        }
        while (count != 0)
        {
            output[offset++] = (uint8_t)byte;
            remaining--;
            count--;
        }
    }
    return bitmap;
}

static void copy_terminated_pairs(uint8_t *destination, const uint8_t *text)
{
    size_t i = 0;
    do
    {
        destination[i] = text[i];
    } while (text[i++] != 0);
}

uint32_t vertrix_path_split_a(const VertrixCalls *calls, uint32_t variable, const uint8_t *text,
                              uint8_t *destination)
{
    uint32_t stack[1] = {0};
    copy_terminated_pairs(destination, text);
    vertrix_calln(calls, 0x4daae8, PATH_A_COPY, PATH_A_FIRST, PATH_A_SECOND, 0, stack, 1, NULL);
    vertrix_call(calls, 0x4ca370, variable, PATH_A_FIRST, PATH_A_SECOND, 0, 0);
    return vertrix_call(calls, 0x4ca600, variable, PATH_A_SECOND, PATH_A_SECOND, 0, 0);
}

uint32_t vertrix_path_split_b(const VertrixCalls *calls, uint32_t variable, uint32_t edx,
                              const uint8_t *text, uint8_t *destination)
{
    uint32_t stack[1] = {PATH_B_STACK};
    copy_terminated_pairs(destination, text);
    vertrix_calln(calls, 0x4daae8, PATH_B_COPY, PATH_B_FIRST, PATH_B_SECOND, PATH_B_THIRD, stack, 1,
                  NULL);
    vertrix_call(calls, 0x4ca370, variable, PATH_B_FIRST, PATH_B_SECOND, PATH_B_THIRD, 0);
    vertrix_call(calls, 0x4ca600, variable, PATH_B_SECOND, PATH_B_SECOND, PATH_B_THIRD, 0);
    vertrix_call(calls, 0x4ca600, variable, PATH_B_THIRD, PATH_B_SECOND, PATH_B_THIRD, 0);
    return vertrix_call(calls, 0x4ca600, variable, edx, PATH_B_SECOND, PATH_B_THIRD, 0);
}

uint32_t vertrix_path_split_c(const VertrixCalls *calls, const uint8_t *text, uint32_t first,
                              uint32_t second, uint32_t third, uint32_t fourth,
                              uint8_t *destination)
{
    uint32_t stack[1] = {PATH_C_STACK};
    uint32_t result;
    uint32_t ebx = PATH_C_SECOND;
    uint32_t ecx = PATH_C_THIRD;
    copy_terminated_pairs(destination, text);
    result = vertrix_calln(calls, 0x4daae8, PATH_C_COPY, PATH_C_FIRST, PATH_C_SECOND, PATH_C_THIRD,
                           stack, 1, NULL);
    if (first != 0)
    {
        result = vertrix_call(calls, 0x4ca370, first, PATH_C_FIRST, ebx, ecx, 0);
    }
    ecx = second;
    if (second != 0)
    {
        result = vertrix_call(calls, 0x4ca370, second, PATH_C_SECOND, ebx, ecx, 0);
    }
    ebx = third;
    if (third != 0)
    {
        result = vertrix_call(calls, 0x4ca370, third, PATH_C_THIRD, ebx, ecx, 0);
    }
    if (fourth != 0)
    {
        result = vertrix_call(calls, 0x4ca370, fourth, PATH_C_STACK, ebx, ecx, 0);
    }
    return result;
}

uint32_t vertrix_rtl_scope_refresh(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t object,
                                   uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t record, scope, owner, flags, state, first, second, third, id;
    uint32_t arguments[SCOPE_ENTER_ARGUMENTS];
    uint32_t last_edx = edx;
    record = vertrix_call(calls, RECORD_ACCESS_B, object, edx, ebx, ecx, 0);
    if (!read_field(services, record, SCOPE_RECORD_SCOPE, &scope) ||
        !read_field(services, scope, SCOPE_OWNER, &owner))
    {
        return 0;
    }
    if (object == owner)
    {
        vertrix_call(calls, SCOPE_RAISE, SCOPE_ERROR_TEXT, edx, ebx, ecx, 0);
    }
    flags = vertrix_call(calls, SCOPE_FLAGS, object, edx, ebx, ecx, 0);
    if ((flags & SCOPE_FLAGS_MASK) == 0)
    {
        state = vertrix_call(calls, SCOPE_STATE, flags, edx, ebx, ecx, 0);
        if (!read_field(services, state, SCOPE_STATE_FIRST, &first) ||
            !read_field(services, state, SCOPE_STATE_SECOND, &second) ||
            !read_field(services, state, SCOPE_STATE_THIRD, &third) ||
            !read_field(services, object, SCOPE_OWNER, &id))
        {
            return 0;
        }
        arguments[0] = id;
        arguments[1] = first;
        arguments[2] = second;
        arguments[3] = third;
        arguments[4] = SCOPE_ENTER_FLAG;
        arguments[5] = SCOPE_ENTER_FLAG;
        vertrix_calln(calls, SCOPE_ENTER, third, second, ebx, ecx, arguments, SCOPE_ENTER_ARGUMENTS,
                      NULL);
        last_edx = second;
    }
    return vertrix_call(calls, SCOPE_LEAVE, object, last_edx, ebx, ecx, 0);
}

uint32_t vertrix_rtl_copy_blocks(uint8_t *destination, const uint8_t *source, uint32_t blocks)
{
    uint32_t length = blocks << COPY_BLOCK_SHIFT;
    memmove(destination, source, length);
    return length;
}

uint32_t vertrix_rtl_read_into(const VertrixCalls *calls, uint32_t stack, uint32_t object,
                               uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t buffer = stack - READ_FRAME;
    uint32_t arguments[READ_ARGUMENTS] = {edx, buffer, READ_BUFFER};
    uint32_t length =
        vertrix_calln(calls, READ_QUERY, buffer, edx, ebx, ecx, arguments, READ_ARGUMENTS, NULL);
    uint32_t limit = READ_BUFFER;
    uint32_t value = READ_FIRST_EBX;
    if (READ_BUFFER - length > READ_SLACK)
    {
        vertrix_call(calls, READ_ASSIGN, object, buffer, length, ecx, 0);
        return (int32_t)length > 0;
    }
    for (;;)
    {
        uint32_t pointer;
        limit += READ_STEP;
        value += READ_STEP;
        pointer = vertrix_call(calls, READ_GROW, object, value, value, ecx, 0);
        arguments[1] = pointer;
        arguments[2] = limit;
        ecx = vertrix_calln(calls, READ_QUERY, pointer, value, value, ecx, arguments,
                            READ_ARGUMENTS, NULL);
        if ((int32_t)(limit - ecx) > READ_SLACK)
        {
            break;
        }
    }
    vertrix_call(calls, READ_FINISH, object, 0xffffffffu, value, ecx, 0);
    return (int32_t)ecx > 0;
}

uint32_t vertrix_rtl_pad_zeros(const VertrixCalls *calls, uint32_t eax, uint32_t edx, uint32_t ecx,
                               uint32_t width, uint8_t *text)
{
    int32_t length = 0, index;
    int32_t spare;
    vertrix_call(calls, PAD_PREPARE, eax, edx, PAD_EBX, ecx, 0);
    while (text[length] != 0)
    {
        length++;
    }
    spare = (int32_t)width - 1;
    for (index = length; index > 0; index--)
    {
        text[spare] = text[index - 1];
        spare--;
    }
    for (index = spare; index >= 0; index--)
    {
        text[index] = PAD_FILL;
        spare--;
    }
    text[width] = 0;
    return (uint32_t)spare;
}

uint32_t vertrix_rtl_length_limit(const uint8_t *text, uint32_t limit)
{
    uint32_t length = 0;
    while (text[length] != 0 && length != limit)
    {
        length++;
    }
    return length;
}

uint32_t vertrix_rtl_wide_byte_count(const VertrixCalls *calls, uint32_t local, uint32_t address,
                                     const uint16_t *text, int32_t limit)
{
    int32_t bytes = 0;
    uint32_t index = 0;
    while (text[index] != 0 && (limit == -1 || bytes <= limit))
    {
        uint32_t result = vertrix_call(calls, WIDE_CONVERT, local, text[index],
                                       address + 2 * (index + 1), (uint32_t)bytes, 0);
        index++;
        if (result != 0xffffffffu)
        {
            bytes += (int32_t)result;
        }
    }
    if (limit != -1 && bytes > limit)
    {
        return (uint32_t)limit;
    }
    return (uint32_t)bytes;
}

static const uint32_t FLOAT_SIGN = 0x80000000u;

uint32_t vertrix_float_add(const VertrixCalls *calls, uint32_t helper, uint32_t eax, uint32_t edx)
{
    if (edx == 0)
    {
        return eax;
    }
    if (eax == 0)
    {
        return edx;
    }
    return vertrix_call(calls, helper, eax, edx, 0, 0, 0);
}

uint32_t vertrix_float_subtract(const VertrixCalls *calls, uint32_t helper, uint32_t eax,
                                uint32_t edx)
{
    if (edx == 0)
    {
        return eax;
    }
    return vertrix_float_add(calls, helper, eax, edx ^ FLOAT_SIGN);
}

uint64_t vertrix_rtl_natural_log(uint64_t bits)
{
    double value, result;
    memcpy(&value, &bits, sizeof value);
    result = log(value);
    memcpy(&bits, &result, sizeof bits);
    return bits;
}

enum
{
    SQRT_ERROR = 0x4dad2e,
    SQRT_ERROR_CODE = 0x2043,
    SQRT_SOFTWARE = 0x4db10a,
    SQRT_LOCAL = 8,
    SQRT_HALF_SHIFT = 32,
    SQRT_GRID = 2048,
    WIDE_LENGTH = 0x4d8580,
    WIDE_RESIZE = 0x4ca1e0,
    WIDE_COPY = 0x4ca730,
    WIDE_FINISH = 0x4ca6c0
};

/* fsqrt rounds to 64 mantissa bits before the double store. The result differs from the correctly
 * rounded square root r only when the odd r lies within half a 64-bit grid step of the midpoint to
 * its neighbour: the extended value then lands exactly on the midpoint and the tie goes to the even
 * neighbour. The residual x - r * r is exact, which decides it. */
static double extended_square_root(double value)
{
    double root = sqrt(value);
    uint64_t bits;
    memcpy(&bits, &root, sizeof bits);
    if (root > 0.0 && isfinite(root) && (bits & 1) != 0)
    {
        double residual = fma(-root, root, value);
        double step = nextafter(root, INFINITY) - root;
        double scale = root * step;
        double fraction = scale / SQRT_GRID;
        double sum = fabs(residual) + fraction;
        double mirror = sum - fabs(residual);
        double error = (fabs(residual) - (sum - mirror)) + (fraction - mirror);
        if ((sum - scale) + error >= 0.0)
        {
            return nextafter(root, residual > 0.0 ? INFINITY : -INFINITY);
        }
    }
    return root;
}

uint64_t vertrix_rtl_square_root(const VertrixCalls *calls, uint32_t frame, uint32_t hardware,
                                 uint32_t eax, uint32_t edx)
{
    if ((int32_t)edx < 0)
    {
        eax = vertrix_call(calls, SQRT_ERROR, SQRT_ERROR_CODE, frame - SQRT_LOCAL, 0, 0, 0);
        edx = frame - SQRT_LOCAL;
    }
    else if ((hardware & 0xff) != 0)
    {
        uint64_t bits = (uint64_t)edx << SQRT_HALF_SHIFT | eax;
        double value, result;
        memcpy(&value, &bits, sizeof value);
        result = extended_square_root(value);
        memcpy(&bits, &result, sizeof bits);
        eax = (uint32_t)bits;
        edx = (uint32_t)(bits >> SQRT_HALF_SHIFT);
    }
    else if (edx != 0)
    {
        eax = vertrix_call(calls, SQRT_SOFTWARE, eax, edx, 0, 0, 0);
    }
    return (uint64_t)edx << SQRT_HALF_SHIFT | eax;
}

uint32_t vertrix_rtl_wide_assign(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t variable, uint32_t source, uint32_t ebx)
{
    uint32_t length = 0, text;
    if (source != 0)
    {
        length = vertrix_call(calls, WIDE_LENGTH, source, source, ebx, variable, 0);
    }
    ebx = length * 2;
    vertrix_call(calls, WIDE_RESIZE, variable, ebx, ebx, variable, 0);
    ebx++;
    if (!read_field(services, variable, 0, &text))
    {
        return 0;
    }
    vertrix_call(calls, WIDE_COPY, text, source, ebx, variable, 0);
    vertrix_call(calls, WIDE_FINISH, variable, 0xffffffffu, ebx, variable, 0);
    return variable;
}

enum
{
    LOWER_FIRST = 0x61,
    LOWER_LAST = 0x7a,
    CASE_DELTA = 0x20
};

static uint32_t upper_case(uint32_t character)
{
    return character >= LOWER_FIRST && character <= LOWER_LAST ? character - CASE_DELTA : character;
}

static int text_length(const uint8_t *text, size_t size, size_t *length)
{
    for (size_t i = 0; i < size; i++)
    {
        if (text[i] == 0)
        {
            *length = i;
            return 1;
        }
    }
    return 0;
}

int vertrix_rtl_text_equal(const VertrixFactoryServices *services, uint32_t first, uint32_t second,
                           uint32_t *result)
{
    void *first_storage, *second_storage;
    size_t first_size, second_size, first_length, second_length;
    const uint8_t *a, *b;
    if (!services->resolve(first, &first_storage, &first_size, services->context) ||
        !services->resolve(second, &second_storage, &second_size, services->context))
    {
        return 0;
    }
    a = first_storage;
    b = second_storage;
    if (!text_length(a, first_size, &first_length) || !text_length(b, second_size, &second_length))
    {
        return 0;
    }
    *result = 0;
    if (first_length != second_length)
    {
        return 1;
    }
    /* A mismatch on the last character leaves both cursors on the terminator, which the original
     * reports as equal. */
    for (size_t i = 0; a[i] != 0; i++)
    {
        if (upper_case(a[i]) != upper_case(b[i]) && a[i + 1] != 0)
        {
            return 1;
        }
    }
    *result = 1;
    return 1;
}

enum
{
    FLOAT_EXPONENT = 0x7ff00000u,
    FLOAT_MANTISSA = 0xfffffu,
    FLOAT_HIDDEN = 0x100000u,
    FLOAT_OVERFLOW = 0x200000u,
    FLOAT_SIGN_BIT = 0x80000000u
};

static int mantissa_at_least(uint32_t high, uint32_t low, uint32_t other_high, uint32_t other_low)
{
    return high > other_high || (high == other_high && low >= other_low);
}

void vertrix_float_remainder(uint32_t low, uint32_t high, uint32_t other_low, uint32_t other_high,
                             uint32_t *quotient, uint32_t *result_low, uint32_t *result_high)
{
    uint32_t exponent, other_exponent, a_high, b_high, bits = 0, sign;
    int32_t diff;
    uint32_t a_low = low;
    if (other_high == 0)
    {
        *quotient = 0;
        *result_low = 0;
        *result_high = 0;
        return;
    }
    exponent = high & FLOAT_EXPONENT;
    other_exponent = other_high & FLOAT_EXPONENT;
    a_high = (high & FLOAT_MANTISSA) | FLOAT_HIDDEN;
    b_high = (other_high & FLOAT_MANTISSA) | FLOAT_HIDDEN;
    diff = (int32_t)(exponent - other_exponent);
    if (diff < 0)
    {
        diff = (int32_t)(uint32_t)diff;
        exponent = (uint32_t)diff + other_exponent;
        bits = 0;
    }
    else
    {
        enum
        {
            COMPARE,
            SUBTRACT,
            ZERO_BIT
        } step = COMPARE;
        for (;;)
        {
            uint32_t bit = 0;
            if (step == COMPARE)
            {
                step = mantissa_at_least(a_high, a_low, b_high, other_low) ? SUBTRACT : ZERO_BIT;
            }
            if (step == SUBTRACT)
            {
                uint64_t a =
                    ((uint64_t)a_high << 32 | a_low) - ((uint64_t)b_high << 32 | other_low);
                a_high = (uint32_t)(a >> 32);
                a_low = (uint32_t)a;
                bit = 1;
            }
            bits = bits << 1 | bit;
            diff = (int32_t)((uint32_t)diff - FLOAT_HIDDEN);
            if (diff < 0)
            {
                break;
            }
            a_high = a_high << 1 | a_low >> 31;
            a_low <<= 1;
            if (a_high >= FLOAT_OVERFLOW)
            {
                step = SUBTRACT;
            }
            else
            {
                step = a_high >= FLOAT_HIDDEN ? COMPARE : ZERO_BIT;
            }
        }
        exponent = 0;
        if (a_low != 0 || a_high != 0)
        {
            while ((a_high & FLOAT_OVERFLOW) == 0)
            {
                a_high = a_high << 1 | a_low >> 31;
                a_low <<= 1;
                exponent -= FLOAT_HIDDEN;
            }
            a_low = a_low >> 1 | a_high << 31;
            a_high >>= 1;
            exponent += FLOAT_HIDDEN;
            exponent += other_exponent;
        }
    }
    a_high = (a_high & FLOAT_MANTISSA) + exponent;
    sign = high & FLOAT_SIGN_BIT;
    if (a_high != 0)
    {
        a_high |= sign;
    }
    if (((sign ^ other_high) & FLOAT_SIGN_BIT) != 0)
    {
        bits = 0u - bits;
    }
    *quotient = bits;
    *result_low = a_low;
    *result_high = a_high;
}

enum
{
    JUMP_EBX = 0x00,
    JUMP_ECX = 0x04,
    JUMP_EDX = 0x08,
    JUMP_ESI = 0x0c,
    JUMP_EDI = 0x10,
    JUMP_EBP = 0x14,
    JUMP_RETURN = 0x18,
    JUMP_ESP = 0x1c,
    JUMP_ES = 0x20,
    JUMP_DS = 0x22,
    JUMP_CS = 0x24,
    JUMP_FS = 0x26,
    JUMP_GS = 0x28,
    JUMP_SS = 0x2a,
    JUMP_CHAIN = 0x2c,
    JUMP_WORD = 2,
    JUMP_DWORD = 4
};

int vertrix_rtl_jump_capture(void *storage, size_t size, const VertrixJumpState *state)
{
    static const struct
    {
        size_t offset;
        unsigned width;
    } layout[] = {{JUMP_EBX, JUMP_DWORD},    {JUMP_ECX, JUMP_DWORD}, {JUMP_EDX, JUMP_DWORD},
                  {JUMP_ESI, JUMP_DWORD},    {JUMP_EDI, JUMP_DWORD}, {JUMP_EBP, JUMP_DWORD},
                  {JUMP_RETURN, JUMP_DWORD}, {JUMP_ESP, JUMP_DWORD}, {JUMP_ES, JUMP_WORD},
                  {JUMP_DS, JUMP_WORD},      {JUMP_CS, JUMP_WORD},   {JUMP_FS, JUMP_WORD},
                  {JUMP_GS, JUMP_WORD},      {JUMP_SS, JUMP_WORD},   {JUMP_CHAIN, JUMP_DWORD}};
    const uint32_t values[] = {state->ebx,
                               state->ecx,
                               state->edx,
                               state->esi,
                               state->edi,
                               state->ebp,
                               state->return_address,
                               state->esp,
                               state->es,
                               state->ds,
                               state->cs,
                               state->fs,
                               state->gs,
                               state->ss,
                               state->chain};
    for (size_t i = 0; i < sizeof layout / sizeof layout[0]; i++)
    {
        if (!vertrix_actor_storage_write(storage, size, layout[i].offset, layout[i].width,
                                         values[i]))
        {
            return 0;
        }
    }
    return 1;
}

enum
{
    ROWS_POINTER = 4
};

int vertrix_rtl_copy_rows(const VertrixFactoryServices *services, uint32_t source_array,
                          uint32_t source_index, uint32_t destination_array,
                          uint32_t destination_index, int32_t count, uint32_t size)
{
    for (int32_t row = 0; row < count; row++)
    {
        void *array_storage, *row_storage, *target_storage;
        size_t array_size, row_size, target_size;
        uint32_t source, target;
        size_t source_offset = ((size_t)source_index + (size_t)row) * ROWS_POINTER;
        size_t target_offset = ((size_t)destination_index + (size_t)row) * ROWS_POINTER;
        if (!services->resolve(destination_array, &array_storage, &array_size, services->context) ||
            !vertrix_actor_storage_read(array_storage, array_size, target_offset, ROWS_POINTER,
                                        &target) ||
            !services->resolve(source_array, &array_storage, &array_size, services->context) ||
            !vertrix_actor_storage_read(array_storage, array_size, source_offset, ROWS_POINTER,
                                        &source) ||
            !services->resolve(source, &row_storage, &row_size, services->context) ||
            !services->resolve(target, &target_storage, &target_size, services->context) ||
            size > row_size || size > target_size)
        {
            return 0;
        }
        memmove(target_storage, row_storage, size);
    }
    return 1;
}
