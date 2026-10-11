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
    STRING_NEW = 0x4ca0d0
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
