#include "port_runtime.h"

enum
{
    THREAD_DATA = 0x507c9c,
    SEED = 0x0c,
    SEED_ADDRESS = 0x4d85f0,
    GET_LAST_ERROR = 0x4f1bbc,
    SET_LAST_ERROR = 0x4f1cb0,
    TLS_GET_VALUE = 0x4f1cdc,
    TLS_INDEX = 0x507c98,
    THREAD_DATA_NEW = 0x4e8400,
    THREAD_DATA_PENDING = 0x53,
    THREAD_DATA_FINISH = 0x4e843c,
    CODE_PAGE = 0x50a820,
    CODE_PAGE_DOUBLE_BYTE = 0x3a4,
    IS_SPACE_DOUBLE_BYTE = 0x4e7140,
    IS_DIGIT_DOUBLE_BYTE = 0x4e70d0,
    C1_DIGIT = 4,
    CHARACTER_CLASSES = 0x507d58,
    CLASS_SPACE = 2,
    CLASS_DIGIT = 0x20,
    CHARACTER_BYTES = 0x4e7120,
    BYTES_LENGTH = 0x4e6f30,
    GET_STRING_TYPE = 0x4f1bec,
    LOCALE_USER_DEFAULT = 0x400,
    CT_CTYPE1 = 1,
    C1_SPACE = 8,
    LIST_ITEMS = 4,
    LIST_COUNT = 8,
    LIST_ITEM = 0x4b79c0,
    LIST_ITEM_FIELD = 0x4b7a80,
    ITEM_FIELD = 8,
    LIST_TEXT = 0x4b79e0,
    OBJECT_TABLE = 0x28,
    OBJECT_TABLE_VALUE = 0x516b14,
    BUFFER_AT = 0,
    BUFFER_COUNT = 0x10,
    FPU_PRESENT = 0x5054a1,
    SINE_FPU = 0x4db710,
    TRIG = 0x4c9b6a,
    TRIG_SINE = 2,
    GUARD_HANDLER = 0x4ec1ec,
    OBJECT_GUARD = 0x516af0,
    OBJECT_TYPE = 0x515130,
    OBJECT_FINALIZE = 0x4ccb9f,
    FREE_RECORD = 0x4ca040,
    FREE_OBJECT = 0x4ca050,
    DESTROY_FREE = 2,
    DESTROY_FINALIZE = 4,
    LIST_TEXT_GUARD = 0x5186cc,
    LIST_TEXT_DEFAULT = 0x5110cb,
    STRING_FROM = 0x4ca280,
    ITEM_TEXT = 0x4b7710,
    STRING_ASSIGN = 0x4ca310,
    STRING_RELEASE = 0x4ca210,
    ARRAY_DATA = 4,
    ARRAY_SIZE = 8,
    ARRAY_CAPACITY = 0xc,
    ARRAY_GROW = 0x10,
    ARRAY_GROW_MIN = 4,
    ARRAY_GROW_MAX = 0x400,
    ALLOCATE = 0x4c9ff0,
    CLEAR_BYTES = 0x4eb5c0,
    MOVE_BYTES = 0x4eb5e0,
    ALLOCATE_MEMORY = 0x4e7c90,
    SURFACE_WIDTH = 4,
    SURFACE_BYTES = 0xc,
    SURFACE_PADDED = 0x10,
    SURFACE_PITCH = 0x14,
    SURFACE_PADDING = 0x18
};

uint32_t vertrix_port_random_seed_address(PORT_SIGNATURE)
{
    Port port;
    uint32_t data;
    port_open(&port, calls, services, globals, entry);
    data = port_call(&port, port_u32(&port, 0, THREAD_DATA), entry->eax, entry->edx, entry->ebx,
                     entry->ecx);
    return port_return(&port, data + SEED, vertrix_lift_edx);
}

uint32_t vertrix_port_random(PORT_SIGNATURE)
{
    Port port;
    uint32_t seed;
    uint32_t address;
    port_open(&port, calls, services, globals, entry);
    address = port_call(&port, SEED_ADDRESS, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (address == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    seed = port_u32(&port, address, 0) * 0x41c64e6du + 0x3039;
    port_set32(&port, address, 0, seed);
    return port_return(&port, (seed >> 16) & 0x7fff, entry->edx);
}

uint32_t vertrix_port_thread_data(PORT_SIGNATURE)
{
    Port port;
    uint32_t error;
    uint32_t index;
    uint32_t data;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    error = port_call(&port, GET_LAST_ERROR, entry->eax, entry->edx, entry->ebx, entry->ecx);
    index = port_u32(&port, 0, TLS_INDEX);
    data = port_call_stack(&port, TLS_GET_VALUE, error, index, entry->ebx, entry->ecx, &index, 1);
    eax = data;
    if (data == 0)
    {
        data = eax = port_call(&port, THREAD_DATA_NEW, 0, vertrix_lift_edx, 0, entry->ecx);
    }
    else if (port_u8(&port, data, THREAD_DATA_PENDING) != 0)
    {
        data = eax = port_call(&port, THREAD_DATA_FINISH, data, vertrix_lift_edx, data, entry->ecx);
    }
    port_call_stack(&port, SET_LAST_ERROR, eax, vertrix_lift_edx, data, entry->ecx, &error, 1);
    return port_return(&port, data, entry->edx);
}

/* The character test of 0x4e10d0 and 0x4e1060: `double_byte` answers for a lead byte under the
 * double-byte code page, otherwise GetStringTypeA's CT_CTYPE1 type is masked. */
static uint32_t character_type(PORT_SIGNATURE, uint32_t double_byte, uint32_t mask)
{
    /* push ecx, push edx, then the character type (esp) and the bytes (esp + 4). */
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint32_t type = entry->esp - BELOW;
    uint32_t bytes = type + 4;
    uint32_t length;
    uint32_t arguments[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    port_set32(&port, entry->esp, -8u, entry->edx);
    if (port_u32(&port, 0, CODE_PAGE) == CODE_PAGE_DOUBLE_BYTE && (entry->eax & 0xff00) != 0)
    {
        uint32_t result =
            port_call(&port, double_byte, entry->eax, entry->edx, entry->ebx, entry->ecx);
        return port_return(&port, result, port_u32(&port, entry->esp, -8u));
    }
    port_call(&port, CHARACTER_BYTES, entry->eax, bytes, entry->ebx, entry->ecx);
    length = port_call(&port, BYTES_LENGTH, bytes, vertrix_lift_edx & 0xffffff00u, entry->ebx,
                       entry->ecx);
    port_set8(&port, bytes, length, vertrix_lift_edx);
    arguments[0] = LOCALE_USER_DEFAULT;
    arguments[1] = CT_CTYPE1;
    arguments[2] = bytes;
    arguments[3] = length;
    arguments[4] = type;
    if (port_call_stack(&port, GET_STRING_TYPE, bytes, type, entry->ebx, entry->ecx, arguments,
                        5) != 1)
    {
        return port_return(&port, 0, port_u32(&port, entry->esp, -8u));
    }
    return port_return(&port, port_u32(&port, type, 0) & mask, port_u32(&port, entry->esp, -8u));
}

uint32_t vertrix_port_is_space(PORT_SIGNATURE)
{
    return character_type(calls, services, globals, entry, IS_SPACE_DOUBLE_BYTE, C1_SPACE);
}

uint32_t vertrix_port_is_digit(PORT_SIGNATURE)
{
    return character_type(calls, services, globals, entry, IS_DIGIT_DOUBLE_BYTE, C1_DIGIT);
}

uint32_t vertrix_port_leap_year(PORT_SIGNATURE)
{
    Port port;
    uint32_t year = entry->eax;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, (year & 3) == 0 && (year % 100 != 0 || year % 400 == 0), entry->edx);
}

uint32_t vertrix_port_parse_integer(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    uint32_t sign;
    uint32_t value = 0;
    port_open(&port, calls, services, globals, entry);
    while (port_u8(&port, 0, CHARACTER_CLASSES + ((port_u8(&port, text, 0) + 1) & 0xff)) &
           CLASS_SPACE)
    {
        text++;
    }
    sign = port_u8(&port, text, 0);
    if (sign == '+' || sign == '-')
    {
        text++;
    }
    while (port_u8(&port, 0, CHARACTER_CLASSES + ((port_u8(&port, text, 0) + 1) & 0xff)) &
           CLASS_DIGIT)
    {
        value = value * 10 + port_u8(&port, text, 0) - '0';
        text++;
    }
    if (sign == '-')
    {
        value = 0u - value;
    }
    return port_return(&port, value, entry->edx);
}

uint32_t vertrix_port_fixed_multiply(PORT_SIGNATURE)
{
    Port port;
    uint64_t product = (uint64_t)((int64_t)(int32_t)entry->eax * (int32_t)entry->edx);
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, (uint32_t)(product >> 16), (uint32_t)(product >> 32));
}

uint32_t vertrix_port_list_item(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t index = entry->edx;
    uint32_t item = 0;
    port_open(&port, calls, services, globals, entry);
    if (index < port_u32(&port, list, LIST_COUNT))
    {
        item = port_u32(&port, port_u32(&port, list, LIST_ITEMS), index * 4);
    }
    return port_return(&port, item, entry->edx);
}

/* `(span - size) / 2` as the original rounds it (towards zero), with edx the dividend's sign. */
static uint32_t center_offset(uint32_t span, uint32_t *edx)
{
    *edx = (uint32_t)((int32_t)span >> 31);
    return (uint32_t)((int32_t)(span - *edx) >> 1);
}

uint32_t vertrix_port_text_layout(PORT_SIGNATURE)
{
    Port port;
    uint32_t x_out = entry->eax;
    uint32_t y_out = entry->edx;
    uint32_t left = entry->arguments[0];
    uint32_t right = entry->arguments[1];
    uint32_t top = entry->arguments[2];
    uint32_t bottom = entry->arguments[3];
    uint32_t edx = entry->edx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, x_out, 0, 0);
    port_set16(&port, y_out, 0, 0);
    if ((int16_t)right > (int16_t)left)
    {
        eax = (uint32_t)(int16_t)right - (uint32_t)(int16_t)left + 1 -
              (uint32_t)(int16_t)entry->ebx + 1;
        eax = center_offset(eax, &edx);
        port_set16(&port, x_out, 0, eax);
        eax = (uint32_t)(int16_t)eax;
        if ((int32_t)eax < 0)
        {
            return port_return(&port, eax, edx);
        }
    }
    if ((int16_t)top < (int16_t)bottom)
    {
        eax =
            (uint32_t)(int16_t)bottom - (uint32_t)(int16_t)top + 1 - (uint32_t)(int16_t)entry->ecx;
        eax = center_offset(eax, &edx);
        port_set16(&port, y_out, 0, eax);
        eax = (uint32_t)(int16_t)eax;
        if ((int32_t)eax < 0)
        {
            return port_return(&port, eax, edx);
        }
    }
    port_set16(&port, x_out, 0, port_u16(&port, x_out, 0) + left);
    port_set16(&port, y_out, 0, port_u16(&port, y_out, 0) + top);
    return port_return(&port, top, edx);
}

uint32_t vertrix_port_list_item_field(PORT_SIGNATURE)
{
    Port port;
    uint32_t item;
    port_open(&port, calls, services, globals, entry);
    item = port_call(&port, LIST_ITEM, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, item != 0 ? port_u32(&port, item, ITEM_FIELD) : 0, vertrix_lift_edx);
}

uint32_t vertrix_port_list_item_field_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t field;
    port_open(&port, calls, services, globals, entry);
    field = port_call(&port, LIST_ITEM_FIELD, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, field, vertrix_lift_edx);
}

uint32_t vertrix_port_list_find(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t count;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, list, LIST_COUNT);
    if (count != 0)
    {
        uint32_t at = port_u32(&port, list, LIST_ITEMS);
        uint32_t end = at + count * 4;
        edx = at;
        do
        {
            edx = port_u32(&port, at, 0);
            if (port_u32(&port, edx, 0) == entry->edx)
            {
                return port_return(&port, edx, edx);
            }
            at += 4;
        } while (at < end);
    }
    return port_return(&port, 0, edx);
}

uint32_t vertrix_port_field8(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, ITEM_FIELD), entry->edx);
}

uint32_t vertrix_port_list_text_slot(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, LIST_TEXT, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, entry->edx, vertrix_lift_edx);
}

uint32_t vertrix_port_object_set_table(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, OBJECT_TABLE, OBJECT_TABLE_VALUE);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_buffer_put(PORT_SIGNATURE)
{
    Port port;
    uint32_t buffer = entry->eax;
    uint32_t at;
    port_open(&port, calls, services, globals, entry);
    at = port_u32(&port, buffer, BUFFER_AT);
    port_set32(&port, buffer, BUFFER_AT, at + 1);
    port_set8(&port, at, 0, entry->edx);
    port_set32(&port, buffer, BUFFER_COUNT, port_u32(&port, buffer, BUFFER_COUNT) + 1);
    return port_return(&port, buffer, at);
}

uint32_t vertrix_port_sine(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, 0, FPU_PRESENT) != 0)
    {
        result = port_call(&port, SINE_FPU, entry->eax, entry->edx, entry->ebx, entry->ecx);
    }
    else
    {
        result = port_call(&port, TRIG, entry->eax, entry->edx, TRIG_SINE, entry->ecx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_object_destroy(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t ebp = entry->esp - 4;
    uint32_t result;
    /* push ebp, ebx, ecx, esi, edi, then 0x24 bytes of locals. */
    port_open_frame(&port, calls, services, globals, entry, 0x38);
    if (mode & DESTROY_FINALIZE)
    {
        port_set32(&port, ebp, -0x34u, object);
        port_set32(&port, ebp, -0x14u, 1);
        result = port_call(&port, OBJECT_FINALIZE, object, OBJECT_TYPE, entry->ebx, object);
        port_set32(&port, ebp, -0x14u, 0);
        port_call(&port, FREE_RECORD, result, 0, entry->ebx, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, OBJECT_TABLE, OBJECT_TABLE_VALUE);
    /* The guard record the original links into fs:[0] and unlinks after the free. */
    port_set32(&port, ebp, -0x20u, port.env.chain);
    port_set32(&port, ebp, -0x1cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x18u, OBJECT_GUARD);
    port_set32(&port, ebp, -0x14u, 0);
    if ((mode & DESTROY_FREE) == 0)
    {
        return port_return(&port, object, mode);
    }
    port_call(&port, FREE_OBJECT, object, mode, GUARD_HANDLER, object);
    return port_return(&port, object, vertrix_lift_edx);
}

uint32_t vertrix_port_list_text(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t string = entry->edx;
    uint32_t ebp = entry->esp - 4;
    uint32_t item;
    /* push ebp, esi, edi, then 0x18 bytes of locals: the guard record and a string. */
    port_open_frame(&port, calls, services, globals, entry, 0x24);
    port_set32(&port, ebp, -0x20u, port.env.chain);
    port_set32(&port, ebp, -0x1cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x18u, LIST_TEXT_GUARD);
    port_set32(&port, ebp, -0x14u, 0);
    port_call(&port, STRING_FROM, string, LIST_TEXT_DEFAULT, entry->ebx, entry->ecx);
    item = port_call(&port, LIST_ITEM, list, entry->ebx, entry->ebx, entry->ecx);
    if (item != 0)
    {
        uint32_t text = port_call(&port, ITEM_TEXT, item, ebp - 0xc, entry->ecx, entry->ecx);
        port_set32(&port, ebp, -0x14u, 1);
        port_call(&port, STRING_ASSIGN, string, text, 0, 1);
        port_set32(&port, ebp, -0x14u, 0);
        port_call(&port, STRING_RELEASE, ebp - 0xc, 0, 0, 1);
    }
    port_set32(&port, ebp, -0x14u, 0);
    return port_return(&port, string, vertrix_lift_edx);
}

uint32_t vertrix_port_pointer_array_resize(PORT_SIGNATURE)
{
    Port port;
    uint32_t array = entry->eax;
    uint32_t size = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t edx = entry->edx;
    uint32_t data;
    uint32_t count;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (ebx != 0xffffffffu)
    {
        port_set32(&port, array, ARRAY_GROW, ebx);
    }
    if (size == 0)
    {
        result = port_call(&port, FREE_RECORD, port_u32(&port, array, ARRAY_DATA), 0, ebx, array);
        port_set32(&port, array, ARRAY_DATA, 0);
        port_set32(&port, array, ARRAY_CAPACITY, 0);
        port_set32(&port, array, ARRAY_SIZE, 0);
        return port_return(&port, result, vertrix_lift_edx);
    }
    if (port_u32(&port, array, ARRAY_DATA) == 0)
    {
        data = port_call(&port, ALLOCATE, size * 4, 0, size * 4, array);
        port_set32(&port, array, ARRAY_DATA, data);
        result = port_call(&port, CLEAR_BYTES, data, vertrix_lift_edx, size * 4, array);
        port_set32(&port, array, ARRAY_CAPACITY, size);
        port_set32(&port, array, ARRAY_SIZE, size);
        return port_return(&port, result, vertrix_lift_edx);
    }
    if ((int32_t)size <= (int32_t)port_u32(&port, array, ARRAY_CAPACITY))
    {
        result = array;
        count = port_u32(&port, array, ARRAY_SIZE);
        if ((int32_t)size > (int32_t)count)
        {
            result = port_call(&port, CLEAR_BYTES, port_u32(&port, array, ARRAY_DATA) + count * 4,
                               0, (size - count) * 4, array);
            edx = vertrix_lift_edx;
        }
        port_set32(&port, array, ARRAY_SIZE, size);
        return port_return(&port, result, edx);
    }
    {
        uint32_t grow = port_u32(&port, array, ARRAY_GROW);
        uint32_t capacity;
        if (grow == 0)
        {
            /* The old size / 8 towards zero; edx keeps the rounding's -8 or 0. */
            count = port_u32(&port, array, ARRAY_SIZE);
            edx = (uint32_t)((int32_t)count >> 31) << 3;
            grow = (uint32_t)((int32_t)count / 8);
            if ((int32_t)grow < ARRAY_GROW_MIN)
            {
                grow = ARRAY_GROW_MIN;
            }
            else if ((int32_t)grow > ARRAY_GROW_MAX)
            {
                grow = ARRAY_GROW_MAX;
            }
        }
        capacity = port_u32(&port, array, ARRAY_CAPACITY) + grow;
        if ((int32_t)size >= (int32_t)capacity)
        {
            capacity = size;
        }
        data = port_call(&port, ALLOCATE, capacity * 4, edx, ebx, array);
        count = port_u32(&port, array, ARRAY_SIZE);
        port_call(&port, MOVE_BYTES, data, port_u32(&port, array, ARRAY_DATA), count * 4, array);
        count = port_u32(&port, array, ARRAY_SIZE);
        port_call(&port, CLEAR_BYTES, data + count * 4, 0, (size - count) * 4, array);
        result = port_call(&port, FREE_RECORD, port_u32(&port, array, ARRAY_DATA), vertrix_lift_edx,
                           (size - count) * 4, array);
        port_set32(&port, array, ARRAY_DATA, data);
        port_set32(&port, array, ARRAY_SIZE, size);
        port_set32(&port, array, ARRAY_CAPACITY, capacity);
        return port_return(&port, result, vertrix_lift_edx);
    }
}

uint32_t vertrix_port_nothing(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_clear_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t size = entry->eax * entry->edx;
    uint32_t memory;
    port_open(&port, calls, services, globals, entry);
    memory = port_call(&port, ALLOCATE_MEMORY, size, entry->edx, size, entry->ecx);
    if (memory != 0)
    {
        memory = port_call(&port, CLEAR_BYTES, memory, 0, size, entry->ecx);
    }
    return port_return(&port, memory, vertrix_lift_edx);
}

uint32_t vertrix_port_surface_padding(PORT_SIGNATURE)
{
    Port port;
    uint32_t surface = entry->eax;
    uint32_t padding;
    port_open(&port, calls, services, globals, entry);
    padding = port_u32(&port, surface, SURFACE_PITCH) -
              port_u32(&port, surface, SURFACE_WIDTH) * port_u8(&port, surface, SURFACE_BYTES);
    port_set32(&port, surface, SURFACE_PADDING, padding);
    port_set32(&port, surface, SURFACE_PADDED, padding != 0);
    return port_return(&port, padding != 0, entry->edx);
}
