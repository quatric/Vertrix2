#include "bits_fill.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    OBJECT_FLAGS = 0,
    OBJECT_INDEX = 0xc,
    OBJECT_MODE = 0x10,
    OBJECT_FLAG = 0x14,
    TABLE_B = 0x10,
    READ_BITS = 0x404680,
    MODE_PAIRS = 2,
    PAIR_READS = 18,
    SPLIT_FIRST_READS = 8,
    SPLIT_SECOND_READS = 9,
    WIDE_D_READS = 11,
    WIDE_B_READS = 10,
    FLAG_SKIP_FIRST = 8,
    FLAG_SKIP_SECOND = 4,
    FLAG_SKIP_THIRD = 2,
    FLAG_SKIP_FOURTH = 1,
    FIRST_GROUP = 6,
    OTHER_GROUP = 5,
    ZERO_FILL_DWORDS = 3,
    SCALE_PAIR = 18,
    SCALE_WIDE = 10
};

typedef struct Fill
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    uint32_t out;
    uint32_t count;
    uint32_t width_d;
    uint32_t width_b;
    int ok;
} Fill;

static int out_store(Fill *fill, uint32_t value)
{
    void *storage;
    size_t size;
    if (!fill->services->resolve(fill->out, &storage, &size, fill->services->context) ||
        !vertrix_actor_storage_write(storage, size, (size_t)fill->count * DWORD_WIDTH, DWORD_WIDTH,
                                     value))
    {
        fill->ok = 0;
        return 0;
    }
    fill->count++;
    return 1;
}

/* One read of `width` bits with the original's edx. */
static void read_field(Fill *fill, uint32_t width, uint32_t edx)
{
    uint32_t pointer = fill->out + fill->count * DWORD_WIDTH;
    out_store(fill, vertrix_call(fill->calls, READ_BITS, width, edx, fill->width_b, pointer, 0));
}

static void reads_of_d(Fill *fill, uint32_t times)
{
    for (uint32_t i = 0; i < times && fill->ok; i++)
    {
        read_field(fill, fill->width_d, fill->width_d);
    }
}

static void reads_of_b(Fill *fill, uint32_t times, int counted)
{
    for (uint32_t i = 0; i < times && fill->ok; i++)
    {
        read_field(fill, fill->width_b, counted ? times - i : fill->width_d);
    }
}

static void zero_fill(Fill *fill, uint32_t times)
{
    for (uint32_t i = 0; i < times && fill->ok; i++)
    {
        out_store(fill, 0);
    }
}

static int read_object(const VertrixFactoryServices *services, uint32_t object, size_t field,
                       uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(object, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, field, DWORD_WIDTH, value);
}

static void terminate(Fill *fill)
{
    void *storage;
    size_t size;
    if (!fill->services->resolve(fill->out, &storage, &size, fill->services->context) ||
        !vertrix_actor_storage_write(storage, size, (size_t)fill->count * DWORD_WIDTH, DWORD_WIDTH,
                                     0))
    {
        fill->ok = 0;
    }
}

int vertrix_bits_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t out, uint32_t object, uint32_t *total)
{
    Fill fill = {calls, services, out, 0, 0, 0, 1};
    uint32_t index, mode, flag, flags, edi = 0;
    void *tables;
    size_t tables_size;
    uint32_t d, b;
    if (!read_object(services, object, OBJECT_INDEX, &index) ||
        !read_object(services, object, OBJECT_MODE, &mode) ||
        !services->resolve(VERTRIX_BITS_TABLES, &tables, &tables_size, services->context) ||
        !vertrix_actor_storage_read(tables, tables_size, index, 1, &d) ||
        !vertrix_actor_storage_read(tables, tables_size, TABLE_B + (size_t)index, 1, &b))
    {
        return 0;
    }
    fill.width_d = d;
    fill.width_b = b;
    if (mode == MODE_PAIRS)
    {
        uint32_t reads = PAIR_READS;
        if (!read_object(services, object, OBJECT_FLAG, &flag))
        {
            return 0;
        }
        edi = SCALE_PAIR * (d + b);
        if (flag != 0)
        {
            reads_of_d(&fill, SPLIT_FIRST_READS);
            reads = SPLIT_SECOND_READS;
            edi -= d;
        }
        reads_of_d(&fill, reads);
        reads_of_b(&fill, PAIR_READS, 1);
        for (uint32_t i = 0; i < ZERO_FILL_DWORDS && fill.ok; i++)
        {
            out_store(&fill, 0);
        }
        *total = edi;
        return fill.ok;
    }
    if (!read_object(services, object, OBJECT_FLAGS, &flags))
    {
        return 0;
    }
    if ((int32_t)flags < 0)
    {
        reads_of_d(&fill, WIDE_D_READS);
        reads_of_b(&fill, WIDE_B_READS, 0);
        *total = SCALE_WIDE * (b + d) + d;
        terminate(&fill);
        return fill.ok;
    }
    if ((flags & FLAG_SKIP_FIRST) != 0)
    {
        zero_fill(&fill, FIRST_GROUP);
    }
    else
    {
        reads_of_d(&fill, FIRST_GROUP);
        edi += FIRST_GROUP * d;
    }
    if ((flags & FLAG_SKIP_SECOND) != 0)
    {
        zero_fill(&fill, OTHER_GROUP);
    }
    else
    {
        reads_of_d(&fill, OTHER_GROUP);
        edi += OTHER_GROUP * d;
    }
    if ((flags & FLAG_SKIP_THIRD) != 0)
    {
        zero_fill(&fill, OTHER_GROUP);
    }
    else
    {
        reads_of_b(&fill, OTHER_GROUP, 1);
        edi += OTHER_GROUP * b;
    }
    if ((flags & FLAG_SKIP_FOURTH) != 0)
    {
        zero_fill(&fill, OTHER_GROUP);
    }
    else
    {
        reads_of_b(&fill, OTHER_GROUP, 1);
        edi += OTHER_GROUP * b;
    }
    terminate(&fill);
    *total = edi;
    return fill.ok;
}

enum
{
    HEADER_READ_FIELD = 0x404610,
    HEADER_READ_BITS = 0x404680,
    HEADER_READ_FLAG = 0x4046e0,
    HEADER_ERROR = 0x4eb4d4,
    HEADER_MODE_THREE = 3,
    HEADER_ECX_THREE = 4,
    HEADER_FIRST_BITS = 8,
    HEADER_SECOND_BITS = 2,
    HEADER_ENTRIES = 8,
    HEADER_ENTRY_SIZE = 0xd0,
    HEADER_SELECTOR_BYTES = 144,
    HEADER_BASE_BITS = 0xc,
    HEADER_SIZE_BITS = 9,
    HEADER_SIZE_LIMIT = 0x120,
    HEADER_POINTER_BITS = 8,
    HEADER_POINTER_ORIGIN = 0x523698,
    HEADER_POINTER_SHIFT = 2,
    HEADER_POINTER_FLAG_BONUS = 8,
    HEADER_MODE_BITS = 2,
    HEADER_SMALL_BITS = 5,
    HEADER_PICK_BITS = 3,
    HEADER_PICK_SHIFT = 5,
    HEADER_PICKS = 3,
    HEADER_PICK_STRIDE = 4,
    HEADER_WIDE_SELECTOR = 8,
    HEADER_WIDTH_WIDE = 0x36,
    HEADER_WIDTH_NARROW = 0x1b,
    HEADER_WIDTH_PAIR = 0x12,
    HEADER_ERROR_ARGUMENT = 1,
    HEADER_ROW_BITS = 4,
    HEADER_WORD_SHIFT = 16,
    HEADER_WORD_SECOND = 2,
    HEADER_BIAS = 1,
    F_BASE = 4,
    F_SIZE = 8,
    F_PLAIN = 0xc,
    F_MODE = 0x10,
    F_EXTRA = 0x14,
    F_SMALL_A = 0x18,
    F_SMALL_B = 0x1c,
    F_SMALL_C = 0x20,
    F_WIDTH = 0x44,
    F_HEIGHT = 0x48,
    F_FIRST_FLAG = 0x50,
    F_SECOND_FLAG = 0x54,
    F_PICK = 0x58,
    F_POINTER = 0x64
};

typedef struct Header
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    uint32_t record;
    int ok;
} Header;

static void put(Header *header, size_t offset, uint32_t value)
{
    void *storage;
    size_t size;
    if (!header->services->resolve(header->record, &storage, &size, header->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, value))
    {
        header->ok = 0;
    }
}

static uint32_t word_at(Header *header, size_t offset)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!header->services->resolve(VERTRIX_BITS_WORDS, &storage, &size,
                                   header->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, &value))
    {
        header->ok = 0;
    }
    return (uint32_t)((int32_t)value >> HEADER_WORD_SHIFT >> HEADER_BIAS);
}

int vertrix_bits_header(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t record, int32_t count, uint32_t flag, uint32_t selector,
                        uint32_t mode)
{
    Header header = {calls, services, record, 1};
    uint32_t k = mode == HEADER_MODE_THREE ? HEADER_ECX_THREE : 0;
    uint32_t n = (uint32_t)count, ebx = flag, eax, edx;
    uint32_t selector_bytes = selector * HEADER_SELECTOR_BYTES,
             pointer_base = k * HEADER_PICK_STRIDE;
    eax = vertrix_call(calls, HEADER_READ_FIELD, HEADER_FIRST_BITS, n, ebx, k, 0);
    put(&header, 0, eax);
    if (count == 1)
    {
        eax = vertrix_call(calls, HEADER_READ_FLAG, eax, n, ebx, k, 0);
    }
    else
    {
        eax = vertrix_call(calls, HEADER_READ_BITS, HEADER_SECOND_BITS, n, ebx, k, 0);
    }
    put(&header, HEADER_PICK_STRIDE, eax);
    for (int32_t i = 0; i < count && header.ok; i++)
    {
        uint32_t entry = record + HEADER_ENTRIES + HEADER_ENTRY_SIZE * (uint32_t)i;
        size_t at = HEADER_ENTRIES + (size_t)HEADER_ENTRY_SIZE * (size_t)i;
        uint32_t pointer, mode_field;
        edx = i == 0 ? selector : (uint32_t)i;
        eax = vertrix_call(calls, HEADER_READ_FIELD, HEADER_BASE_BITS, edx, ebx, entry, 0);
        put(&header, at + F_BASE, eax);
        eax = vertrix_call(calls, HEADER_READ_BITS, HEADER_SIZE_BITS, edx, ebx, entry, 0);
        put(&header, at + F_SIZE, eax > HEADER_SIZE_LIMIT ? HEADER_SIZE_LIMIT : eax);
        eax = vertrix_call(calls, HEADER_READ_BITS, HEADER_POINTER_BITS, edx, ebx, entry, 0);
        edx = pointer_base + (HEADER_POINTER_ORIGIN - (eax << HEADER_POINTER_SHIFT));
        pointer = flag != 0 ? edx + HEADER_POINTER_FLAG_BONUS : edx;
        put(&header, at + F_POINTER, pointer);
        eax = vertrix_call(calls, HEADER_READ_FIELD, HEADER_SIZE_BITS, edx, ebx, entry, 0);
        put(&header, at + F_PLAIN, eax);
        eax = vertrix_call(calls, HEADER_READ_FLAG, eax, edx, ebx, entry, 0);
        if (eax != 0)
        {
            eax = vertrix_call(calls, HEADER_READ_BITS, HEADER_MODE_BITS, edx, ebx, entry, 0);
            put(&header, at + F_MODE, eax);
            mode_field = eax;
            eax = vertrix_call(calls, HEADER_READ_FLAG, eax, edx, ebx, entry, 0);
            put(&header, at + F_EXTRA, eax);
            eax = vertrix_call(calls, HEADER_READ_BITS, HEADER_SMALL_BITS, edx, ebx, entry, 0);
            put(&header, at + F_SMALL_A, eax);
            eax = vertrix_call(calls, HEADER_READ_BITS, HEADER_SMALL_BITS, edx, ebx, entry, 0);
            put(&header, at + F_SMALL_B, eax);
            put(&header, at + F_SMALL_C, 0);
            for (uint32_t pick = 0; pick < HEADER_PICKS; pick++)
            {
                edx = entry + pick * HEADER_PICK_STRIDE;
                eax = vertrix_call(calls, HEADER_READ_BITS, HEADER_PICK_BITS, edx, ebx, entry, 0);
                ebx = pointer;
                eax = (eax << HEADER_PICK_SHIFT) + pointer;
                put(&header, at + F_PICK + pick * HEADER_PICK_STRIDE, eax);
            }
            edx = entry + F_PLAIN;
            if (mode_field == 0)
            {
                eax = vertrix_call(calls, HEADER_ERROR, HEADER_ERROR_ARGUMENT, edx, ebx, entry, 0);
            }
            put(&header, at + F_WIDTH,
                mode_field == HEADER_MODE_BITS
                    ? HEADER_WIDTH_PAIR
                    : (selector == HEADER_WIDE_SELECTOR ? HEADER_WIDTH_WIDE : HEADER_WIDTH_NARROW));
            put(&header, at + F_HEIGHT, HEADER_SIZE_LIMIT);
        }
        else
        {
            uint32_t rows, columns, first, second;
            ebx = HEADER_SMALL_BITS;
            for (uint32_t small = 0; small < HEADER_PICKS; small++)
            {
                edx = entry + small * HEADER_PICK_STRIDE;
                eax = vertrix_call(calls, HEADER_READ_BITS, HEADER_SMALL_BITS, edx, ebx, entry, 0);
                put(&header, at + F_SMALL_A + small * HEADER_PICK_STRIDE, eax);
            }
            edx = entry + F_PLAIN;
            rows = vertrix_call(calls, HEADER_READ_BITS, HEADER_ROW_BITS, edx, ebx, entry, 0);
            edx = rows;
            columns = vertrix_call(calls, HEADER_READ_BITS, HEADER_PICK_BITS, edx, ebx, entry, 0);
            first = word_at(&header, selector_bytes + 2 * (size_t)rows);
            ebx = first;
            put(&header, at + F_WIDTH, first);
            eax = word_at(&header,
                          selector_bytes + 2 * ((size_t)columns + rows) + HEADER_WORD_SECOND);
            put(&header, at + F_HEIGHT, eax);
            second = eax;
            (void)second;
            put(&header, at + F_MODE, 0);
            put(&header, at + F_EXTRA, 0);
        }
        eax = vertrix_call(calls, HEADER_READ_FLAG, eax, edx, ebx, entry, 0);
        put(&header, at + F_FIRST_FLAG, eax);
        eax = vertrix_call(calls, HEADER_READ_FLAG, eax, edx, ebx, entry, 0);
        put(&header, at + F_SECOND_FLAG, eax);
    }
    return header.ok;
}
