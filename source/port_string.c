#include "port_string.h"

enum
{
    MULTI_BYTE = 0x5c8950,
    LEAD_BYTES = 0x5c8961,
    EMPTY_STRING = 0x500818,
    STRING_COUNT = 0x00,
    STRING_LENGTH = 0x04,
    STRING_CAPACITY = 0x08,
    STRING_TEXT = 0x0c,
    STRING_EXTRA = 0x0d,
    EMPTY_TEXT = 0x4ca060,
    ALLOCATE = 0x4c9ff0,
    DECREMENT = 0x4f1c34,
    FREE_MEMORY = 0x4ca040,
    EMPTY_TEXT_ADDRESS = 0x50081c,
    APPEND_TEXT = 0x4ca5a0,
    RELEASE_RECORD = 0x4ca150,
    GROW_APPEND = 0x4ca3f0,
    MOVE_BYTES = 0x4eb5e0,
    STRING_NEW = 0x4ca0d0,
    STRING_CLEAR = 0x4ca110,
    STRING_COPY = 0x4ca2e0,
    INCREMENT = 0x4f1c38,
    STRING_RESERVE = 0x4ca1e0,
    STRING_SET = 0x4ca2e0,
    STRING_MAKE_UNIQUE = 0x4ca1a0,
    IS_SPACE = 0x4e10d0,
    CHAR_NEXT = 0x4e1054,
    MOVE_TEXT = 0x4e1140,
    STRING_SET_TEXT = 0x4ca370,
    TEXT_LENGTH = 0x4f1d24,
    READ_RESOURCE_STRING = 0x4db8c0
};

static int lead_byte(Port *port, uint32_t text)
{
    return port_u32(port, 0, MULTI_BYTE) != 0 &&
           (port_u8(port, 0, LEAD_BYTES + port_u8(port, text, 0)) & 1) != 0;
}

uint32_t vertrix_port_char_next(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (lead_byte(&port, text) && port_u8(&port, text, 1) != 0)
    {
        return port_return(&port, text + 2, entry->edx);
    }
    return port_return(&port, text + 1, entry->edx);
}

uint32_t vertrix_port_char_length(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, lead_byte(&port, entry->eax) ? 2 : 1, entry->edx);
}

uint32_t vertrix_port_char_put(PORT_SIGNATURE)
{
    Port port;
    uint32_t code = entry->eax;
    uint32_t to = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if ((code & 0xff00) == 0)
    {
        port_set8(&port, to, 0, code);
        return port_return(&port, to, entry->edx);
    }
    port_set8(&port, to, 1, code);
    port_set8(&port, to, 0, code >> 8);
    return port_return(&port, to, code >> 8);
}

uint32_t vertrix_port_string_new(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot = entry->eax;
    uint32_t length = entry->edx;
    uint32_t record;
    uint32_t text;
    port_open(&port, calls, services, globals, entry);
    if (length == 0)
    {
        text = port_u32(&port, port_call(&port, EMPTY_TEXT, slot, length, slot, entry->ecx), 0);
        port_set32(&port, slot, 0, text);
        return port_return(&port, text, vertrix_lift_edx);
    }
    record = port_call(&port, ALLOCATE, length + STRING_EXTRA, length, slot, entry->ecx);
    length = vertrix_lift_edx;
    text = record + STRING_TEXT;
    port_set32(&port, record, STRING_COUNT, 1);
    port_set8(&port, text + length, 0, 0);
    port_set32(&port, record, STRING_LENGTH, length);
    port_set32(&port, record, STRING_CAPACITY, length);
    port_set32(&port, slot, 0, text);
    return port_return(&port, record, length);
}

uint32_t vertrix_port_string_release(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->arguments[0];
    int32_t left;
    port_open(&port, calls, services, globals, entry);
    if (record == port_u32(&port, 0, EMPTY_STRING))
    {
        return port_return(&port, record, entry->edx);
    }
    left = (int32_t)port_call_stack(&port, DECREMENT, record, entry->edx, entry->ebx, entry->ecx,
                                    &record, 1);
    if (left > 0)
    {
        return port_return(&port, (uint32_t)left, vertrix_lift_edx);
    }
    record = port_call(&port, FREE_MEMORY, record, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, record, vertrix_lift_edx);
}

uint32_t vertrix_port_string_empty(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, EMPTY_TEXT_ADDRESS, entry->edx);
}

uint32_t vertrix_port_string_append_char(PORT_SIGNATURE)
{
    Port port;
    uint32_t local = entry->esp - 12;
    port_open_frame(&port, calls, services, globals, entry, 12);
    port_set32(&port, entry->esp, (uint32_t)-4, entry->ebx);
    port_set32(&port, entry->esp, (uint32_t)-8, entry->ecx);
    port_set8(&port, local, 0, entry->edx);
    port_call(&port, APPEND_TEXT, entry->eax, 1, local, entry->eax);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

uint32_t vertrix_port_string_append(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t count = entry->edx;
    uint32_t source = entry->ebx;
    uint32_t text;
    uint32_t record;
    uint32_t length;
    port_open(&port, calls, services, globals, entry);
    if (count == 0)
    {
        return port_return(&port, string, source);
    }
    text = port_u32(&port, string, 0);
    record = text - STRING_TEXT;
    if ((int32_t)port_u32(&port, record, STRING_COUNT) <= 1 &&
        (int32_t)(port_u32(&port, record, STRING_LENGTH) + count) <=
            (int32_t)port_u32(&port, record, STRING_CAPACITY))
    {
        port_call(&port, MOVE_BYTES, text + port_u32(&port, record, STRING_LENGTH), source, count,
                  count);
        text = port_u32(&port, string, 0);
        port_set32(&port, text, STRING_LENGTH - STRING_TEXT,
                   port_u32(&port, text, STRING_LENGTH - STRING_TEXT) + count);
        text = port_u32(&port, string, 0);
        length = port_u32(&port, text - STRING_TEXT, STRING_LENGTH);
        port_set8(&port, text, length, 0);
        return port_return(&port, length, text);
    }
    text = port_u32(&port, string, 0);
    record = text - STRING_TEXT;
    {
        uint32_t grow_stack[1] = {source};
        uint32_t release_stack[1] = {record};
        uint32_t grown =
            port_call_stack(&port, GROW_APPEND, string, port_u32(&port, record, STRING_LENGTH),
                            text, count, grow_stack, 1);
        uint32_t result = port_call_stack(&port, RELEASE_RECORD, grown, vertrix_lift_edx, text,
                                          count, release_stack, 1);
        return port_return(&port, result, vertrix_lift_edx);
    }
}

/* The release of 0x4ca150 on the record of the string at `string`: 0 for the empty string, else
 * the last call's eax (edx in vertrix_lift_edx, which stays entry edx for the empty string). */
static uint32_t release_string(Port *port, uint32_t string, const LiftEntry *entry, int *empty)
{
    uint32_t record = port_u32(port, string, 0) - STRING_TEXT;
    int32_t left;
    vertrix_lift_edx = entry->edx;
    *empty = record == port_u32(port, 0, EMPTY_STRING);
    if (*empty)
    {
        return record;
    }
    left = (int32_t)port_call_stack(port, DECREMENT, record, entry->edx, string, entry->ecx,
                                    &record, 1);
    if (left > 0)
    {
        return (uint32_t)left;
    }
    return port_call(port, FREE_MEMORY, port_u32(port, string, 0) - STRING_TEXT, vertrix_lift_edx,
                     string, entry->ecx);
}

uint32_t vertrix_port_string_release_variable(PORT_SIGNATURE)
{
    Port port;
    int empty;
    port_open(&port, calls, services, globals, entry);
    release_string(&port, entry->eax, entry, &empty);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

uint32_t vertrix_port_string_clear(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t result;
    int empty;
    port_open(&port, calls, services, globals, entry);
    result = release_string(&port, string, entry, &empty);
    if (empty)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, EMPTY_TEXT, result, vertrix_lift_edx, string, entry->ecx);
    result = port_u32(&port, result, 0);
    port_set32(&port, string, 0, result);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_char_end(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, text, 0) == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    if (lead_byte(&port, text) && port_u8(&port, text, 1) == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_string_concat(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t first_count = entry->edx;
    uint32_t first = entry->ebx;
    uint32_t second_count = entry->ecx;
    uint32_t second = entry->arguments[0];
    uint32_t total = first_count + second_count;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (total == 0)
    {
        return port_return(&port, string, total);
    }
    port_call(&port, STRING_NEW, string, total, first, second_count);
    port_call(&port, MOVE_BYTES, port_u32(&port, string, 0), first, first_count, second_count);
    result = port_call(&port, MOVE_BYTES, port_u32(&port, string, 0) + first_count, second,
                       second_count, second_count);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_string_assign(PORT_SIGNATURE)
{
    Port port;
    uint32_t variable = entry->eax;
    uint32_t source = entry->edx;
    uint32_t record;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, variable, 0) == port_u32(&port, source, 0))
    {
        return port_return(&port, variable, edx);
    }
    record = port_u32(&port, variable, 0) - STRING_TEXT;
    if (((int32_t)port_u32(&port, record, STRING_COUNT) >= 0 ||
         record == port_u32(&port, 0, EMPTY_STRING)) &&
        (int32_t)port_u32(&port, port_u32(&port, source, 0) - STRING_TEXT, STRING_COUNT) >= 0)
    {
        port_call(&port, STRING_CLEAR, variable, source, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
        record = port_u32(&port, edx, 0);
        port_set32(&port, variable, 0, record);
        record -= STRING_TEXT;
        port_call_stack(&port, INCREMENT, record, edx, entry->ebx, entry->ecx, &record, 1);
    }
    else
    {
        uint32_t text = port_u32(&port, source, 0);
        port_call(&port, STRING_COPY, variable, port_u32(&port, text - STRING_TEXT, STRING_LENGTH),
                  text, entry->ecx);
    }
    return port_return(&port, variable, vertrix_lift_edx);
}

/* Whether the dword holds a zero byte (the original's `(x - 0x01010101) & ~x & 0x80808080`). */
static int has_zero(uint32_t value)
{
    return ((value + 0xfefefeffu) & ~value & 0x80808080u) != 0;
}

/* Two differing dwords: -1 or 1 by their first differing byte, 0 when a matching zero byte comes
 * first. */
static uint32_t dword_order(uint32_t mine, uint32_t theirs, LiftFlags *flags)
{
    unsigned shift;
    for (shift = 0; shift < 32; shift += 8)
    {
        uint32_t a = (mine >> shift) & 0xff;
        uint32_t b = (theirs >> shift) & 0xff;
        if (a != b)
        {
            return lift_or(8, a < b ? 0xff : 0, 1, flags) == 1 ? 1 : 0xffffffffu;
        }
        if (a == 0)
        {
            break;
        }
    }
    return 0;
}

uint32_t vertrix_port_string_compare(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    uint32_t other = entry->edx;
    uint32_t result = 0;
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    port_open(&port, calls, services, globals, entry);
    while (text != other)
    {
        unsigned index;
        int ended = 0;
        for (index = 0; index < 4 && !ended; index++)
        {
            uint32_t mine = port_u32(&port, text, index * 4);
            uint32_t theirs = port_u32(&port, other, index * 4);
            if (mine != theirs)
            {
                result = dword_order(mine, theirs, &flags);
                ended = 1;
                break;
            }
            if (index == 3)
            {
                text += 16;
                other += 16;
            }
            ended = has_zero(mine);
        }
        if (ended)
        {
            break;
        }
    }
    if (result == 0)
    {
        (void)lift_sub(32, 0, 0, &flags);
    }
    vertrix_lift_fl = flags;
    return port_return(&port, result, other);
}

uint32_t vertrix_port_string_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t text;
    port_open(&port, calls, services, globals, entry);
    text = port_call(&port, EMPTY_TEXT, string, entry->edx, string, entry->ecx);
    port_set32(&port, string, 0, port_u32(&port, text, 0));
    return port_return(&port, string, entry->edx);
}

uint32_t vertrix_port_string_reserve(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    record = port_u32(&port, string, 0) - STRING_TEXT;
    if ((int32_t)port_u32(&port, record, STRING_COUNT) <= 1 &&
        (int32_t)entry->edx <= (int32_t)port_u32(&port, record, STRING_CAPACITY))
    {
        return port_return(&port, record, entry->edx);
    }
    port_call(&port, STRING_CLEAR, string, entry->edx, entry->ebx, string);
    record = port_call(&port, STRING_NEW, string, vertrix_lift_edx, entry->ebx, string);
    return port_return(&port, record, vertrix_lift_edx);
}

uint32_t vertrix_port_string_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t length = entry->edx;
    uint32_t text = entry->ebx;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, STRING_RESERVE, string, length, text, string);
    port_call(&port, MOVE_BYTES, port_u32(&port, string, 0), text, length, string);
    edx = vertrix_lift_edx;
    text = port_u32(&port, string, 0);
    port_set32(&port, text, -8u, length);
    text = port_u32(&port, string, 0);
    port_set8(&port, length, text, 0);
    return port_return(&port, text, edx);
}

uint32_t vertrix_port_string_set_text(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t text = entry->edx;
    uint32_t length = text;
    port_open(&port, calls, services, globals, entry);
    if (text != 0)
    {
        length = port_call_stack(&port, TEXT_LENGTH, string, text, text, entry->ecx, &text, 1);
    }
    port_call(&port, STRING_SET, string, length, text, entry->ecx);
    return port_return(&port, string, vertrix_lift_edx);
}

uint32_t vertrix_port_string_make_unique(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t record;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    record = port_u32(&port, string, 0) - STRING_TEXT;
    if ((int32_t)port_u32(&port, record, STRING_COUNT) <= 1)
    {
        return port_return(&port, string, entry->edx);
    }
    port_call(&port, STRING_CLEAR, string, entry->edx, record, string);
    port_call(&port, STRING_NEW, string, port_u32(&port, record, STRING_LENGTH), record, string);
    result = port_call(&port, MOVE_BYTES, port_u32(&port, string, 0), record + STRING_TEXT,
                       port_u32(&port, record, STRING_LENGTH) + 1, port_u32(&port, string, 0));
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_string_from(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t source = entry->edx;
    uint32_t text;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    text = port_call(&port, EMPTY_TEXT, string, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, string, 0, port_u32(&port, text, 0));
    edx = vertrix_lift_edx;
    if (source != 0 && (source >> 16) == 0)
    {
        port_call(&port, READ_RESOURCE_STRING, string, source & 0xffff, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    else if (source != 0)
    {
        uint32_t length = port_call_stack(&port, TEXT_LENGTH, source >> 16, edx, entry->ebx,
                                          entry->ecx, &source, 1);
        edx = vertrix_lift_edx;
        if (length != 0)
        {
            port_call(&port, STRING_NEW, string, length, length, entry->ecx);
            port_call(&port, MOVE_BYTES, port_u32(&port, string, 0), source, length, entry->ecx);
            edx = vertrix_lift_edx;
        }
    }
    return port_return(&port, string, edx);
}

uint32_t vertrix_port_char_code(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    uint32_t code;
    port_open(&port, calls, services, globals, entry);
    code = port_u8(&port, text, 0);
    if (lead_byte(&port, text))
    {
        code = (code << 8) | port_u8(&port, text, 1);
    }
    return port_return(&port, code, entry->edx);
}

uint32_t vertrix_port_string_copy(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t source = entry->edx;
    uint32_t text;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    text = port_u32(&port, source, 0);
    record = text - STRING_TEXT;
    if ((int32_t)port_u32(&port, record, STRING_COUNT) >= 0)
    {
        port_set32(&port, string, 0, text);
        port_call_stack(&port, INCREMENT, record, record, string, entry->ecx, &record, 1);
    }
    else
    {
        uint32_t empty = port_call(&port, EMPTY_TEXT, text, record, string, entry->ecx);
        port_set32(&port, string, 0, port_u32(&port, empty, 0));
        port_call(&port, STRING_SET_TEXT, string, port_u32(&port, source, 0), string, entry->ecx);
    }
    return port_return(&port, string, vertrix_lift_edx);
}

uint32_t vertrix_port_string_set_length(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t length;
    uint32_t text;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, STRING_MAKE_UNIQUE, string, entry->edx, string, entry->ecx);
    length = vertrix_lift_edx;
    if (length == 0xffffffffu)
    {
        text = port_u32(&port, string, 0);
        length = port_call_stack(&port, TEXT_LENGTH, result, length, string, entry->ecx, &text, 1);
    }
    text = port_u32(&port, string, 0);
    port_set32(&port, text, -8u, length);
    text = port_u32(&port, string, 0);
    port_set8(&port, length, text, 0);
    return port_return(&port, text, length);
}

uint32_t vertrix_port_string_reserve_unique(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t size = entry->edx;
    uint32_t record;
    uint32_t length;
    port_open(&port, calls, services, globals, entry);
    record = port_u32(&port, string, 0) - STRING_TEXT;
    if ((int32_t)port_u32(&port, record, STRING_COUNT) <= 1 &&
        (int32_t)size <= (int32_t)port_u32(&port, record, STRING_CAPACITY))
    {
        return port_return(&port, port_u32(&port, string, 0), entry->edx);
    }
    record = port_u32(&port, string, 0) - STRING_TEXT;
    length = port_u32(&port, record, STRING_LENGTH);
    if ((int32_t)size < (int32_t)length)
    {
        size = length;
    }
    port_call(&port, STRING_NEW, string, size, entry->ebx, length);
    port_call(&port, MOVE_BYTES, port_u32(&port, string, 0), record + STRING_TEXT, length + 1,
              length);
    port_set32(&port, port_u32(&port, string, 0) - STRING_TEXT, STRING_LENGTH, length);
    port_call_stack(&port, RELEASE_RECORD, port_u32(&port, string, 0) - STRING_TEXT,
                    vertrix_lift_edx, length + 1, length, &record, 1);
    return port_return(&port, port_u32(&port, string, 0), vertrix_lift_edx);
}

uint32_t vertrix_port_string_trim_end(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t at;
    uint32_t last = 0;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call(&port, STRING_MAKE_UNIQUE, string, entry->edx, entry->ebx, entry->ecx);
    at = port_u32(&port, string, 0);
    while (port_u8(&port, at, 0) != 0)
    {
        /* The first of a run of trailing spaces. */
        if (port_call(&port, IS_SPACE, (uint32_t)(int8_t)port_u8(&port, at, 0), at, entry->ebx,
                      last) != 0)
        {
            if (last == 0)
            {
                last = at;
            }
        }
        else
        {
            last = 0;
        }
        at = vertrix_lift_edx;
        eax = at = port_call(&port, CHAR_NEXT, at, at, entry->ebx, last);
    }
    if (last != 0)
    {
        port_set8(&port, last, 0, 0);
        eax = port_u32(&port, string, 0);
        port_set32(&port, eax, -8u, last - port_u32(&port, string, 0));
        eax -= STRING_TEXT;
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_string_trim_start(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t at;
    uint32_t text;
    uint32_t length;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, STRING_MAKE_UNIQUE, string, entry->edx, entry->ebx, string);
    at = port_u32(&port, string, 0);
    for (;;)
    {
        uint32_t space = port_call(&port, IS_SPACE, (uint32_t)(int8_t)port_u8(&port, at, 0), at,
                                   entry->ebx, string);
        at = vertrix_lift_edx;
        if (space == 0)
        {
            break;
        }
        at = port_call(&port, CHAR_NEXT, at, at, entry->ebx, string);
    }
    text = port_u32(&port, string, 0);
    length = port_u32(&port, text - STRING_TEXT, STRING_LENGTH) - (at - text);
    port_call(&port, MOVE_TEXT, text, at, length + 1, string);
    text = port_u32(&port, string, 0);
    port_set32(&port, text, -8u, length);
    return port_return(&port, text - STRING_TEXT, entry->edx);
}

uint32_t vertrix_port_text_length_limit(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t length = 0;
    port_open(&port, calls, services, globals, entry);
    for (;;)
    {
        uint32_t byte = port_u8(&port, at, 0);
        at++;
        if (byte == 0 || length == entry->ebx)
        {
            break;
        }
        length++;
    }
    return port_return(&port, length, at);
}

enum
{
    FORMAT_WIDTH = 4,
    FORMAT_PAD = 0x16,
    FORMAT_FLAGS = 0x1e,
    FORMAT_PARTS = 0x20,
    FORMAT_ZEROS = 0x24,
    FLAG_ALTERNATE = 1,
    FLAG_SPACE = 2,
    FLAG_PLUS = 4,
    FLAG_LEFT = 8
};

uint32_t vertrix_port_format_flags(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t spec = entry->edx;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, spec, FORMAT_FLAGS, 0);
    for (;; at++)
    {
        uint32_t byte = port_u8(&port, at, 0);
        uint32_t flags = port_u8(&port, spec, FORMAT_FLAGS);
        if (byte == '-')
        {
            flags |= FLAG_LEFT;
        }
        else if (byte == '#')
        {
            flags |= FLAG_ALTERNATE;
        }
        else if (byte == '+')
        {
            flags = (flags | FLAG_PLUS) & ~FLAG_SPACE;
        }
        else if (byte == ' ')
        {
            if (!(flags & FLAG_PLUS))
            {
                flags |= FLAG_SPACE;
            }
        }
        else if (byte == '0')
        {
            port_set8(&port, spec, FORMAT_PAD, byte);
        }
        else
        {
            break;
        }
        port_set8(&port, spec, FORMAT_FLAGS, flags);
    }
    return port_return(&port, at, entry->edx);
}

uint32_t vertrix_port_format_zero_pad(PORT_SIGNATURE)
{
    Port port;
    uint32_t spec = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (!(port_u8(&port, spec, FORMAT_FLAGS) & FLAG_LEFT) &&
        port_u8(&port, spec, FORMAT_PAD) == '0')
    {
        int32_t left = (int32_t)port_u32(&port, spec, FORMAT_WIDTH);
        uint32_t part;
        for (part = 0; part < 6; part++)
        {
            left -= (int32_t)port_u32(&port, spec, FORMAT_PARTS + part * 4);
        }
        if (left > 0)
        {
            port_set32(&port, spec, FORMAT_ZEROS, port_u32(&port, spec, FORMAT_ZEROS) + left);
        }
    }
    return port_return(&port, entry->eax, entry->edx);
}

enum
{
    FORMAT_PRECISION = 8,
    FORMAT_SIZE = 0x1f,
    FORMAT_READ_FLAGS = 0x4df81c,
    SIZE_LONG = 0x20,
    SIZE_SHORT = 0x10,
    SIZE_NEAR = 0x40,
    SIZE_FAR = 0x80,
    SIZE_WIDE = 1
};

/* The next variable argument, as the original's `va_arg`. */
static uint32_t next_argument(Port *port, uint32_t list)
{
    uint32_t at = port_u32(port, list, 0) + 4;
    port_set32(port, list, 0, at);
    return port_u32(port, at, -4u);
}

/* Read decimal digits into the field, leaving edx as the original does. */
static uint32_t read_number(Port *port, uint32_t spec, uint32_t field, uint32_t *at, uint32_t edx)
{
    for (;;)
    {
        uint32_t byte = port_u8(port, *at, 0);
        edx = (edx & 0xffffff00u) | byte;
        if (byte < '0' || byte > '9')
        {
            return edx;
        }
        edx = byte - '0';
        port_set32(port, spec, field, port_u32(port, spec, field) * 10 + edx);
        (*at)++;
    }
}

uint32_t vertrix_port_format_spec(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->edx;
    uint32_t spec = entry->ebx;
    uint32_t at;
    uint32_t edx;
    uint32_t byte;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, spec, FORMAT_PAD, ' ');
    at = port_call(&port, FORMAT_READ_FLAGS, entry->eax, spec, spec, entry->ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, spec, FORMAT_WIDTH, 0);
    if (port_u8(&port, at, 0) == '*')
    {
        edx = next_argument(&port, list);
        port_set32(&port, spec, FORMAT_WIDTH, edx);
        if ((int32_t)edx < 0)
        {
            port_set32(&port, spec, FORMAT_WIDTH, 0u - edx);
            port_set8(&port, spec, FORMAT_FLAGS, port_u8(&port, spec, FORMAT_FLAGS) | FLAG_LEFT);
        }
        at++;
    }
    else
    {
        edx = read_number(&port, spec, FORMAT_WIDTH, &at, edx);
    }
    port_set32(&port, spec, FORMAT_PRECISION, 0xffffffffu);
    if (port_u8(&port, at, 0) == '.')
    {
        port_set32(&port, spec, FORMAT_PRECISION, 0);
        at++;
        if (port_u8(&port, at, 0) == '*')
        {
            edx = next_argument(&port, list);
            port_set32(&port, spec, FORMAT_PRECISION, edx);
            if ((int32_t)edx < 0)
            {
                port_set32(&port, spec, FORMAT_PRECISION, 0xffffffffu);
            }
            at++;
        }
        else
        {
            edx = read_number(&port, spec, FORMAT_PRECISION, &at, edx);
        }
        if (port_u32(&port, spec, FORMAT_PRECISION) != 0xffffffffu)
        {
            port_set8(&port, spec, FORMAT_PAD, ' ');
        }
    }
    byte = port_u8(&port, at, 0);
    edx = (edx & 0xffffff00u) | byte;
    switch (byte)
    {
        case 'l':
        case 'w':
            port_set8(&port, spec, FORMAT_FLAGS, port_u8(&port, spec, FORMAT_FLAGS) | SIZE_LONG);
            at++;
            break;
        case 'h':
            port_set8(&port, spec, FORMAT_FLAGS, port_u8(&port, spec, FORMAT_FLAGS) | SIZE_SHORT);
            at++;
            break;
        case 'N':
            port_set8(&port, spec, FORMAT_FLAGS, port_u8(&port, spec, FORMAT_FLAGS) | SIZE_NEAR);
            at++;
            break;
        case 'F':
            port_set8(&port, spec, FORMAT_FLAGS, port_u8(&port, spec, FORMAT_FLAGS) | SIZE_FAR);
            at++;
            break;
        case 'L':
            edx = (edx & 0xffffff00u) | (port_u8(&port, spec, FORMAT_SIZE) | SIZE_WIDE);
            port_set8(&port, spec, FORMAT_SIZE, edx);
            at++;
            break;
        case 'I':
            if (port_u8(&port, at, 1) == '6' && port_u8(&port, at, 2) == '4')
            {
                port_set8(&port, spec, FORMAT_SIZE, port_u8(&port, spec, FORMAT_SIZE) | SIZE_WIDE);
                at += 3;
            }
            break;
    }
    return port_return(&port, at, edx);
}

uint32_t vertrix_port_copy_terminated(PORT_SIGNATURE)
{
    Port port;
    uint32_t destination = entry->eax;
    uint32_t source = entry->edx;
    uint32_t edx = entry->ebx;
    uint32_t length;
    uint32_t end;
    port_open(&port, calls, services, globals, entry);
    if (destination == 0)
    {
        return port_return(&port, destination, edx);
    }
    if ((int32_t)entry->ebx > (int32_t)entry->ecx)
    {
        edx = entry->ecx;
    }
    length = port_call(&port, 0x4e39a0, source, edx, entry->ebx, entry->ecx);
    port_call(&port, 0x4e39d0, destination, source, length, length);
    end = port_call(&port, 0x4e39f0, destination, length, length, length);
    port_set8(&port, destination, end, 0);
    return port_return(&port, end, vertrix_lift_edx);
}

/* The character at p into edx's low byte, as the original's mov dl, [eax] does. */
static uint32_t root_char(Port *port, uint32_t p, uint32_t *edx)
{
    *edx = (*edx & 0xffffff00u) | port_u8(port, p, 0);
    return *edx & 0xff;
}

static int root_separator(uint32_t c)
{
    return c == '\\' || c == '/';
}

uint32_t vertrix_port_path_root(PORT_SIGNATURE)
{
    enum
    {
        CHAR_NEXT = 0x4e1054,
        PATH_MAX_LENGTH = 0x104
    };
    Port port;
    uint8_t stack[0xc + 8 + 8];
    uint32_t name;
    uint32_t string;
    uint32_t buffer;
    uint32_t p;
    uint32_t edx;
    uint32_t arguments[3];
    port_open_arguments(&port, stack, calls, services, globals, entry, 0xc, 2);
    name = port_u32(&port, entry->esp, 4);
    string = port_u32(&port, entry->esp, 8);
    buffer = port_call(&port, 0x4ca670, string, PATH_MAX_LENGTH, PATH_MAX_LENGTH, entry->ecx);
    p = port_call(&port, 0x4eb5c0, buffer, 0, PATH_MAX_LENGTH, entry->ecx);
    edx = vertrix_lift_edx;
    /* lstrcpynA(buffer, name, MAX_PATH) through slot 0x4f1d20. */
    arguments[0] = buffer;
    arguments[1] = name;
    arguments[2] = PATH_MAX_LENGTH;
    port_call_stack(&port, 0x4f1d20, p, edx, PATH_MAX_LENGTH, entry->ecx, arguments, 3);
    edx = vertrix_lift_edx;
#define NEXT()                                                                                     \
    do                                                                                             \
    {                                                                                              \
        p = port_call(&port, CHAR_NEXT, p, edx, PATH_MAX_LENGTH, entry->ecx);                      \
        edx = vertrix_lift_edx;                                                                    \
    } while (0)
    /* A UNC name: two separators somewhere. */
    p = buffer;
    while (port_u8(&port, p, 0) != 0)
    {
        if (root_separator(root_char(&port, p, &edx)) &&
            root_separator(root_char(&port, p + 1, &edx)))
        {
            break;
        }
        NEXT();
    }
    if (port_u8(&port, p, 0) != 0)
    {
        /* \\server\share: past the server and the share. */
        p += 2;
        while (port_u8(&port, p, 0) != 0 && !root_separator(root_char(&port, p, &edx)))
        {
            NEXT();
        }
        if (port_u8(&port, p, 0) != 0)
        {
            do
            {
                NEXT();
            } while (port_u8(&port, p, 0) != 0 && !root_separator(root_char(&port, p, &edx)));
        }
    }
    else
    {
        /* A drive: up to the first separator. */
        p = buffer;
        while (port_u8(&port, p, 0) != 0 && !root_separator(root_char(&port, p, &edx)))
        {
            NEXT();
        }
    }
#undef NEXT
    if (port_u8(&port, p, 0) != 0)
    {
        port_set8(&port, p, 1, 0);
    }
    p = port_call(&port, 0x4ca6c0, string, 0xffffffffu, PATH_MAX_LENGTH, entry->ecx);
    return port_return(&port, p, vertrix_lift_edx);
}

uint32_t vertrix_port_full_path(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x168,
        GUARD_HANDLER = 0x4ec1ec,
        PATH_GUARD = 0x519d30,
        PATH_MAX_LENGTH = 0x104,
        ROOT = 0xc,        /* below ebp: the root string */
        FILE_PART = 0x10,  /* below ebp: the file part pointer */
        FLAGS = 8,         /* below ebp: the volume's flags */
        FIND_DATA = 0x164, /* below ebp: WIN32_FIND_DATAA */
        FOUND_NAME = 0x138 /* its cFileName */
    };
    Port port;
    uint8_t stack[BELOW + 8 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t name;
    uint32_t buffer;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result;
    uint32_t arguments[8];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    name = port_u32(&port, ebp, 8);
    buffer = port_u32(&port, ebp, 0xc);
    port_set32(&port, ebp, -0x24u, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, PATH_GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    /* GetFullPathNameA (slot 0x4f1bb8). */
    arguments[0] = buffer;
    arguments[1] = PATH_MAX_LENGTH;
    arguments[2] = name;
    arguments[3] = ebp - FILE_PART;
    result = port_call_stack(&port, 0x4f1bb8, ebp - FILE_PART, edx, ebx, ecx, arguments, 4);
    edx = vertrix_lift_edx;
    if (result == 0)
    {
        /* Failed: the name copied as it is (lstrcpynA, slot 0x4f1d20). */
        arguments[0] = name;
        arguments[1] = buffer;
        arguments[2] = PATH_MAX_LENGTH;
        port_call_stack(&port, 0x4f1d20, result, edx, ebx, ecx, arguments, 3);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_call(&port, 0x4ca070, ebp - ROOT, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x18u, 1);
    arguments[0] = name;
    arguments[1] = ebp - ROOT;
    port_call_stack(&port, 0x4d7d70, ebp - ROOT, edx, ebx, ecx, arguments, 2);
    edx = vertrix_lift_edx;
    /* GetVolumeInformationA(root, ..., &serial, &flags, ...) (slot 0x4f1c04). */
    arguments[0] = port_u32(&port, ebp, -ROOT);
    arguments[1] = 0;
    arguments[2] = 0;
    arguments[3] = 0;
    arguments[4] = ebp - 4;
    arguments[5] = ebp - FLAGS;
    arguments[6] = 0;
    arguments[7] = 0;
    result = port_call_stack(&port, 0x4f1c04, ebp - 4, edx, ebx, ecx, arguments, 8);
    edx = vertrix_lift_edx;
    if (result == 0)
    {
        port_call(&port, 0x4ca210, ebp - ROOT, 0, ebx, ecx);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    if ((port_u8(&port, ebp, -FLAGS) & 2) == 0)
    {
        /* A volume without case-preserved names: CharUpperA (slot 0x4f1904). */
        arguments[0] = name;
        result = port_call_stack(&port, 0x4f1904, result, edx, ebx, ecx, arguments, 1);
        edx = vertrix_lift_edx;
    }
    if ((port_u8(&port, ebp, -FLAGS) & 4) == 0)
    {
        /* Without Unicode names on disk: the file part from FindFirstFileA (slots 0x4f1b60,
         * 0x4f1b5c FindClose, 0x4f1d1c lstrcpyA). */
        arguments[0] = buffer;
        arguments[1] = ebp - FIND_DATA;
        result = port_call_stack(&port, 0x4f1b60, ebp - FIND_DATA, edx, ebx, ecx, arguments, 2);
        edx = vertrix_lift_edx;
        if (result != 0xffffffffu)
        {
            arguments[0] = result;
            port_call_stack(&port, 0x4f1b5c, result, edx, ebx, ecx, arguments, 1);
            edx = vertrix_lift_edx;
            arguments[0] = port_u32(&port, ebp, -FILE_PART);
            arguments[1] = ebp - FOUND_NAME;
            port_call_stack(&port, 0x4f1d1c, ebp - FOUND_NAME, edx, ebx, ecx, arguments, 2);
            edx = vertrix_lift_edx;
        }
    }
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x4ca210, ebp - ROOT, 0, ebx, 1);
    return port_return(&port, 1, vertrix_lift_edx);
}
