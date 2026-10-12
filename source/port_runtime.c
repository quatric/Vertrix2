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
    RESOURCE_PREPARE = 0x483ce0,
    TRIPLE_ALLOCATE = 0x487710,
    RANDOM_NEXT = 0x4826c0,
    BANKS = 0x544f90,
    LIST_TABLE_518704 = 0x518704,
    LIST_CONSTRUCT_518704 = 0x4b78d0,
    LOCAL_ALLOC = 0x4f1c4c,
    OUT_OF_MEMORY = 0x4d9510,
    FREE_LIST = 0x50818e,
    OBJECT_RELEASE = 0x4ce9c0,
    LOCKING_OFF = 0x5c79d4,
    LOCK_SECTIONS = 0x5c79d8,
    LOCK_TAKE = 0x4de9c0,
    LOCK_GIVE = 0x4dea40,
    LINK_PUSH = 0x4dba10,
    LOCK_ROUTINE = 0x509748,
    UNLOCK_ROUTINE = 0x50974c,
    LOCAL_TIME = 0x4ec850,
    CALL_48A930 = 0x48a930,
    IMAGE_LIBRARY = 0x544a6c,
    IMAGE_LOAD = 0x4877f0,
    IMAGE_DRAW = 0x482e10,
    IMAGE_RELEASE = 0x483ed0,
    IMAGE_RELEASE_STATE = 0x5b9c60,
    BLOCK_ALLOCATE = 0x4d85f0,
    LIST_TABLE_518344 = 0x518344,
    CLEAR_ALLOCATE = 0x4ec160,
    CALL_4B7B00 = 0x4b7b00,
    RESOURCE_IS_LOADED = 0x4877e0,
    STREAM_TELL = 0x5bb250,
    COUNTED_GUARD = 0x51a344,
    COUNTED_TABLE = 0x517474,
    TIMER_LOCK = 0x540020,
    TIMER_COUNT = 0x540044,
    TIMER_DRAWN = 0x54004c,
    TIMER_SURFACE = 0x540048,
    TIMER_COUNT_GET = 0x4182c0,
    MAIN_APPLICATION = 0x4ce740,
    SCREEN_REFRESH = 0x41a040,
    SCREEN_REPAINT = 0x41a2b0,
    SCREEN_BLIT = 0x47ce10,
    SET_FIRST = 0x4759d0,
    KEY_FLAG_CLEAR = 0x475af0,
    KEY_STATE = 0x475790,
    KEY_EVENTS = 0x4759e0,
    THREAD_ID = 0x4f1bbc,
    THREAD_BLOCK = 0x4dbf80,
    THREAD_BLOCKS = 0x5c5c60,
    THREAD_BLOCK_CREATE = 0x4ce7c0,
    CHAIN_CLEANUP = 0x4d9350,
    FLAG_LOCK = 0x50817e,
    LOCK_ENTER = 0x4e14b0,
    LOCK_LEAVE = 0x4e14b7,
    MEMORY_FREE = 0x4ea190,
    CLEAR_FIRST = 0x4757b0,
    CHAR_UPPER = 0x4f1904,
    STRING_OWN = 0x4ca1a0,
    TIME_SINCE_FRAME = 0x4b7d70,
    IDLE_RUN = 0x418830,
    GAME_PAUSED = 0x532b40,
    POINTER_HIDDEN = 0x558958,
    CURSOR = 0x558c7c,
    CURSOR_UPDATE = 0x45fab0,
    CURSOR_DRAW = 0x45fa70,
    INPUT_LOCK_SECTION = 0x5328c0,
    ENTER_SECTION = 0x4f1b48,
    LEAVE_SECTION = 0x4f1c40,
    MOUSE = 0x5588f8,
    KEEP_PLACE = 0x478460,
    KEYS_AGE = 0x476400,
    LIST_TAKE = 0x4d8540,
    TIME_GET_TIME = 0x4f172c,
    FRAME_DELTA = 0x5bd834,
    FRAME_NOW = 0x5bd838,
    FRAME_LAST = 0x5bd844,
    RATE_START = 0x5329fc,
    RATE_TIME = 0x532a00,
    RATE = 0x532a04,
    FLIP_RESULT = 0x5b9c4c,
    PAUSE_KEY = 0x3b,
    PAUSED = 0x532a08,
    KEY_INPUT = 0x54d640,
    KEY_READY = 0x476480,
    KEY_TAKE = 0x4762e0,
    TEXT_AT_END = 0x4e7b50,
    CHARACTER_SIZE = 0x4e6f30,
    DOUBLE_BYTE_ON = 0x5c8950,
    DOUBLE_BYTE_LEADS = 0x5c8961,
    FILL_BYTES = 0x4eb5c0,
    TICKS = 0x5329f8,
    SCREEN_PRESENT = 0x485550,
    SCREEN_STATE = 0x5b9c50,
    STRING_COPY_RECORD = 0x4ca110,
    STRING_EMPTY_TEXT = 0x5c5c00,
    STRING_SET_TEXT = 0x4ca370,
    TEXT_LENGTH = 0x4e39f0,
    COPY_MEMORY = 0x4e7b90,
    TIME_BUILD = 0x4e33d0,
    TIME_FROM_SYSTEM = 0x4e3420,
    FILE_TIME_TO_LOCAL = 0x4f1b54,
    FILE_TIME_TO_SYSTEM = 0x4f1b58,
    TIME_DAYS = 0x4e909c,
    TIME_MAKE = 0x4e7850,
    STRING_LIST_DESTROY_GUARD = 0x518620,
    STRING_LIST_CLEAR = 0x4b7830,
    LIST_DESTROY = 0x4d86d0,
    ARRAY_DESTROY = 0x4ccb9f,
    ARRAY_FREE = 0x4ca040,
    STRING_LIST_DESTRUCTOR = 0x513ea0,
    STRING_LIST_GUARD = 0x51864c,
    STRING_DESTROY = 0x4ca210,
    FREE_MEMORY = 0x4ca050,
    POINTER_ARRAY_RESIZE = 0x4d8770,
    ENVIRONMENT = 0x5c81d4,
    COMPARE_LENGTH = 0x4e4080,
    LIST_CREATE_GUARD = 0x51a04c,
    LIST_BASE_TABLE = 0x517454,
    LIST_EMPTY_TABLE = 0x51a0d4,
    AUDIO_DEVICE = 0x4f6418,
    AUDIO_LOCKS = 0x4f644c,
    AUDIO_LOCKED = 0x52f020,
    AUDIO_LOCK = 0x40ab20,
    LIST_CREATE = 0x4d8650,
    LIST_TABLE = 0x518694,
    LIST_REMOVE = 0x4d88a0,
    STREAM_ENDED = 0x48a910,
    STREAM_PEEK = 0x48aa80,
    STREAM_SKIP = 0x48aa90,
    STREAM_SKIP_LINE = 0x48a380,
    TEXT_DRAW_GUARD = 0x514f58,
    TEXT_MEASURE = 0x4408e0,
    TEXT_DRAW_AT = 0x440a20,
    GLYPHS_GUARD = 0x514f4c,
    GLYPH_LOOKUP = 0x43f420,
    ACTOR_SIZE = 0x15c,
    ACTOR_CONSTRUCT = 0x4abd70,
    ACTOR_PLACE = 0x4adf20,
    ACTOR_MEASURE = 0x4b14c0,
    ACTOR_TABLE = 0x158,
    FONT_SIZES = 0x541988,
    FONT_SIZE = 0x20c,
    DRAW_SCALE = 0x44,
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
    ALLOCATE_OBJECT = 0x4ca000,
    STRING_COPY = 0x4ca090,
    LIST_INSERT = 0x4d88a0,
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

uint32_t vertrix_port_list_append_text(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t count;
    uint32_t slot;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, list, LIST_COUNT);
    slot = port_call(&port, ALLOCATE_OBJECT, 4, entry->edx, entry->ebx, entry->ecx);
    if (slot != 0)
    {
        slot = port_call(&port, STRING_COPY, slot, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    port_call(&port, LIST_INSERT, list, count, slot, 1);
    return port_return(&port, 0, vertrix_lift_edx);
}

uint32_t vertrix_port_text_draw(PORT_SIGNATURE)
{
    /* push ebp, esi, edi, then 0x28 bytes: the guard record and the four results. */
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t alignment = (uint32_t)(int8_t)entry->edx;
    uint32_t text = entry->arguments[2];
    uint32_t actor = entry->arguments[3];
    uint32_t arguments[7];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x30u, port.env.chain);
    port_set32(&port, ebp, -0x2cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x28u, TEXT_DRAW_GUARD);
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x14u, (uint32_t)(int16_t)entry->ebx);
    arguments[0] = (uint32_t)(int16_t)entry->arguments[1];
    arguments[1] = text;
    arguments[2] = port_u8(&port, actor, DRAW_SCALE);
    arguments[3] = ebp - 0x1c;
    arguments[4] = ebp - 0x18;
    arguments[5] = ebp - 0xc;
    arguments[6] = ebp - 0x10;
    port_call_stack(&port, TEXT_MEASURE, alignment, (uint32_t)(int16_t)entry->ebx,
                    (uint32_t)(int16_t)entry->ecx, (uint32_t)(int16_t)entry->arguments[0],
                    arguments, 7);
    arguments[0] = text;
    arguments[1] = actor;
    port_call_stack(&port, TEXT_DRAW_AT, entry->eax, alignment,
                    (uint32_t)((int32_t)port_u32(&port, ebp, -0xeu) >> 16),
                    (uint32_t)((int32_t)port_u32(&port, ebp, -0x12u) >> 16), arguments, 2);
    return port_return(&port, port_u32(&port, ebp, -0x30u), vertrix_lift_edx);
}

/* Copy a byte, word or word of the actor's drawing settings to the glyph actor. */
static void copy8(Port *port, uint32_t to, uint32_t from, uint32_t offset)
{
    port_set8(port, to, offset, port_u8(port, from, offset));
}

static void copy16(Port *port, uint32_t to, uint32_t from, uint32_t offset)
{
    port_set16(port, to, offset, port_u16(port, from, offset));
}

uint32_t vertrix_port_text_draw_glyphs(PORT_SIGNATURE)
{
    /* push ebp, esi, edi, then 0x38 bytes: the guard record, the glyph and its size. */
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->arguments[1];
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t edx = GUARD_HANDLER;
    uint32_t ebx = 0;
    uint32_t ecx = GLYPHS_GUARD;
    uint32_t text;
    uint32_t glyph;
    uint32_t byte;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, entry->eax);
    port_set8(&port, ebp, -0xcu, entry->edx);
    port_set16(&port, ebp, -0x10u, entry->ebx);
    port_set16(&port, ebp, -0x14u, entry->ecx);
    port_set32(&port, ebp, -0x40u, port.env.chain);
    port_set32(&port, ebp, -0x3cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x38u, GLYPHS_GUARD);
    port_set32(&port, ebp, -0x34u, 0);
    text = port_u32(&port, ebp, 8);
    byte = port_u8(&port, text, 0);
    while (byte != 0)
    {
        uint32_t font = (uint32_t)(int8_t)port_u8(&port, ebp, -0xcu);
        text = port_u32(&port, ebp, 8);
        byte = port_u8(&port, text, 0);
        ebx = (ebx & 0xffffff00u) | byte;
        if (byte == ' ')
        {
            uint32_t size;
            glyph = port_call(&port, ALLOCATE_OBJECT, ACTOR_SIZE, edx, ebx, ecx);
            edx = vertrix_lift_edx;
            if (glyph != 0)
            {
                glyph = port_call(&port, ACTOR_CONSTRUCT, glyph, edx, ebx, ecx);
                edx = vertrix_lift_edx;
            }
            port_call_stack(&port, ACTOR_PLACE, glyph, 0, 0, 0, zeros, 5);
            ebx = 0;
            ecx = 0;
            copy8(&port, glyph, actor, 0x44);
            copy8(&port, glyph, actor, 0x91);
            size = FONT_SIZES + font * FONT_SIZE;
            port_set32(&port, glyph, 0xf4, port_u32(&port, size, 0));
            port_set32(&port, glyph, 0xf8, port_u32(&port, size, 4));
            port_set32(&port, ebp, -0x20u, glyph);
            if (port_call(&port, ACTOR_MEASURE, glyph, ebp - 0x28, ebp - 0x24, 0) != 0)
            {
                ecx = port_u32(&port, ebp, -0x10u) + port_u32(&port, ebp, -0x28u);
                port_set16(&port, ebp, -0x10u, ecx + 1);
            }
            edx = port_u32(&port, ebp, -0x20u);
            if (edx != 0)
            {
                ebx = port_u32(&port, edx, ACTOR_TABLE);
                port_call(&port, port_u32(&port, ebx, 0), edx, 2, ebx, ecx);
                edx = vertrix_lift_edx;
            }
        }
        else
        {
            edx = port_call(&port, GLYPH_LOOKUP, font, byte, ebx, ecx);
            if (edx != 0)
            {
                uint32_t arguments[5];
                glyph = port_call(&port, ALLOCATE_OBJECT, ACTOR_SIZE, edx, ebx, ecx);
                edx = vertrix_lift_edx;
                if (glyph != 0)
                {
                    ecx = 1;
                    ebx = 0;
                    port_set32(&port, ebp, -0x1cu, glyph);
                    port_set32(&port, ebp, -0x34u, 1);
                    glyph = port_call(&port, ACTOR_CONSTRUCT, glyph, edx, ebx, ecx);
                    edx = vertrix_lift_edx;
                    port_set32(&port, ebp, -0x34u, 0);
                }
                arguments[0] = 0;
                arguments[1] = 0;
                arguments[2] = edx;
                arguments[3] = 0;
                arguments[4] = 0;
                ebx = (uint32_t)(int16_t)port_u16(&port, ebp, -0x14u);
                ecx = 0;
                port_call_stack(&port, ACTOR_PLACE, glyph,
                                (uint32_t)(int16_t)port_u16(&port, ebp, -0x10u), ebx, 0, arguments,
                                5);
                copy8(&port, glyph, actor, 0x8e);
                port_set8(&port, glyph, 0x8f, 1);
                port_set8(&port, glyph, 0x8e, port_u8(&port, actor, 0x8e));
                copy8(&port, glyph, actor, 0x4e);
                copy16(&port, glyph, actor, 0x48);
                copy8(&port, glyph, actor, 0x52);
                copy8(&port, glyph, actor, 0x94);
                copy8(&port, glyph, actor, 0x95);
                copy8(&port, glyph, actor, 0x93);
                copy8(&port, glyph, actor, 0x44);
                copy8(&port, glyph, actor, 0x91);
                port_set32(&port, glyph, 0x80, port_u32(&port, actor, 0x80));
                copy8(&port, glyph, actor, 0x8c);
                copy16(&port, glyph, actor, 0xa8);
                copy16(&port, glyph, actor, 0xaa);
                copy16(&port, glyph, actor, 0xac);
                copy16(&port, glyph, actor, 0xae);
                ebx = ebp - 0x24;
                port_set32(&port, ebp, -0x2cu, glyph);
                if (port_call(&port, ACTOR_MEASURE, glyph, ebp - 0x28, ebx, 0) != 0)
                {
                    ebx = port_u32(&port, glyph, ACTOR_TABLE);
                    port_call(&port, port_u32(&port, ebx, 8), glyph, port_u32(&port, ebp, -0x18u),
                              ebx, 0);
                    edx = port_u32(&port, ebp, -0x10u) + port_u32(&port, ebp, -0x28u);
                    ebx = edx + 1;
                    port_set16(&port, ebp, -0x10u, ebx);
                }
                else
                {
                    edx = vertrix_lift_edx;
                }
                glyph = port_u32(&port, ebp, -0x2cu);
                if (glyph != 0)
                {
                    ebx = port_u32(&port, glyph, ACTOR_TABLE);
                    port_call(&port, port_u32(&port, ebx, 0), glyph, 2, ebx, ecx);
                    edx = vertrix_lift_edx;
                }
                port_set32(&port, ebp, -0x34u, 0);
            }
        }
        text = port_u32(&port, ebp, 8) + 1;
        byte = port_u8(&port, text, 0);
        edx = (edx & 0xffff00ffu) | (byte << 8);
        port_set32(&port, ebp, 8, text);
    }
    return port_return(&port, port_u32(&port, ebp, -0x40u), edx);
}

uint32_t vertrix_port_upper_case(PORT_SIGNATURE)
{
    Port port;
    uint32_t character = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)character >= 'a' && (int32_t)character <= 'z')
    {
        character -= 0x20;
    }
    return port_return(&port, character, entry->edx);
}

uint32_t vertrix_port_stream_token_ahead(PORT_SIGNATURE)
{
    Port port;
    uint32_t reader = entry->eax;
    uint32_t stream = entry->edx;
    uint32_t edx = entry->edx;
    port_open(&port, calls, services, globals, entry);
    for (;;)
    {
        uint32_t byte;
        if (port_call(&port, STREAM_ENDED, stream, edx, reader, stream) != 0)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
        byte = port_u8(&port,
                       port_call(&port, STREAM_PEEK, stream, vertrix_lift_edx, reader, stream), 0);
        if (byte == '/')
        {
            port_call(&port, STREAM_SKIP, stream, 1, reader, stream);
            port_call(&port, STREAM_SKIP_LINE, reader, stream, reader, stream);
            return port_return(&port, 0, vertrix_lift_edx);
        }
        if (byte == '\n' || byte == '\r')
        {
            port_call(&port, STREAM_SKIP, stream, 1, reader, stream);
            return port_return(&port, 0, vertrix_lift_edx);
        }
        if (byte != ' ')
        {
            return port_return(&port, 1, vertrix_lift_edx);
        }
        port_call(&port, STREAM_SKIP, stream, 1, reader, stream);
        edx = vertrix_lift_edx;
    }
}

uint32_t vertrix_port_audio_lock_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, AUDIO_LOCK, 0, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_audio_lock(PORT_SIGNATURE)
{
    Port port;
    uint32_t locks;
    uint32_t result = 0;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, AUDIO_DEVICE) == 0xffff)
    {
        return port_return(&port, 0, entry->edx);
    }
    locks = port_u32(&port, 0, AUDIO_LOCKS) + 1;
    port_set32(&port, 0, AUDIO_LOCKS, locks);
    if (locks == 1)
    {
        result = port_call(&port, port_u32(&port, 0, AUDIO_LOCKED), entry->eax, entry->eax, locks,
                           entry->ecx);
    }
    port_set32(&port, 0, AUDIO_LOCKS, port_u32(&port, 0, AUDIO_LOCKS) - 1);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_list_construct(PORT_SIGNATURE)
{
    Port port;
    uint32_t list;
    port_open(&port, calls, services, globals, entry);
    list = port_call(&port, LIST_CREATE, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, list, 0, LIST_TABLE);
    return port_return(&port, list, vertrix_lift_edx);
}

uint32_t vertrix_port_list_delete(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, LIST_REMOVE, entry->eax, port_u32(&port, entry->eax, 8), entry->edx, 1);
    return port_return(&port, 0, vertrix_lift_edx);
}

uint32_t vertrix_port_stream_skip_line(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call(&port, STREAM_ENDED, stream, entry->edx, ebx, stream);
    while (eax == 0)
    {
        uint32_t byte = port_u8(&port, port_call(&port, STREAM_PEEK, stream, 1, ebx, stream), 0);
        ebx = (ebx & 0xffffff00u) | byte;
        eax = port_call(&port, STREAM_SKIP, stream, vertrix_lift_edx, ebx, stream);
        if (byte == '\n' || byte == '\r')
        {
            break;
        }
        eax = port_call(&port, STREAM_ENDED, stream, vertrix_lift_edx, ebx, stream);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_list_create(PORT_SIGNATURE)
{
    /* push edx, then 0x20 bytes: the guard record from esp, the list at esp + 0x14. */
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t list = entry->eax;
    uint32_t record = entry->esp - BELOW;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->edx);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, record, 4, GUARD_HANDLER);
    port_set32(&port, record, 8, LIST_CREATE_GUARD);
    port_set32(&port, record, 0xc, 0);
    port_set8(&port, record, 0x18, 0);
    port_set32(&port, record, 0x14, list);
    port_set32(&port, list, 0, LIST_BASE_TABLE);
    port_set32(&port, record, 0xc, 1);
    port_set32(&port, list, 0, LIST_EMPTY_TABLE);
    port_set32(&port, list, 4, 0);
    port_set32(&port, list, 0x10, 0);
    port_set32(&port, list, 0xc, 0);
    port_set32(&port, list, 8, 0);
    return port_return(&port, list, entry->edx);
}

uint32_t vertrix_port_stream_skip_blank(PORT_SIGNATURE)
{
    Port port;
    uint32_t reader = entry->eax;
    uint32_t stream = entry->edx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call(&port, STREAM_ENDED, stream, entry->edx, reader, stream);
    while (eax == 0)
    {
        uint32_t at = port_call(&port, STREAM_PEEK, stream, vertrix_lift_edx, reader, stream);
        uint32_t byte = port_u8(&port, at, 0);
        if (byte == '/')
        {
            port_call(&port, STREAM_SKIP, stream, 1, reader, stream);
            port_call(&port, STREAM_SKIP_LINE, reader, stream, reader, stream);
        }
        else if (byte == ' ' || byte == '\n' || byte == '\r')
        {
            port_call(&port, STREAM_SKIP, stream, 1, reader, stream);
        }
        else
        {
            return port_return(&port, (at & 0xffffff00u) | byte, vertrix_lift_edx);
        }
        eax = port_call(&port, STREAM_ENDED, stream, vertrix_lift_edx, reader, stream);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_environment_value(PORT_SIGNATURE)
{
    Port port;
    uint32_t name = entry->eax;
    uint32_t at;
    uint32_t length = 0;
    uint32_t text;
    port_open(&port, calls, services, globals, entry);
    at = port_u32(&port, 0, ENVIRONMENT);
    if (at == 0 || name == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    while (port_u8(&port, name, length) != 0)
    {
        length++;
    }
    for (; (text = port_u32(&port, at, 0)) != 0; at += 4)
    {
        if (port_call(&port, COMPARE_LENGTH, text, name, length, text) == 0 &&
            port_u8(&port, text, length) == '=')
        {
            return port_return(&port, text + length + 1, entry->edx);
        }
    }
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_string_list_clear(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then 0x24 bytes: the guard record and a string. */
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t list = entry->eax;
    uint32_t ebp = entry->esp - 4;
    uint32_t count;
    uint32_t index;
    uint32_t ecx = STRING_LIST_GUARD;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x24u, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, STRING_LIST_GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    count = port_u32(&port, list, 8);
    if (count != 0)
    {
        ecx = 0;
        for (index = 0; index < count;)
        {
            uint32_t item = port_u32(&port, port_u32(&port, list, 4), ecx);
            if (item != 0)
            {
                uint32_t memory;
                port_set32(&port, ebp, -0x18u, 1);
                port_set32(&port, ebp, -0x38u, item);
                memory = port_call(&port, STRING_DESTROY, item, 0, index, ecx);
                port_set32(&port, ebp, -0x18u, 0);
                port_call(&port, FREE_MEMORY, memory, 0, index, ecx);
            }
            ecx += 4;
            index++;
            port_set32(&port, ebp, -0x18u, 0);
        }
    }
    port_call(&port, POINTER_ARRAY_RESIZE, list, 0, 0xffffffffu, ecx);
    return port_return(&port, port_u32(&port, ebp, -0x24u), entry->edx);
}

uint32_t vertrix_port_string_list_destroy(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, esi, edi, then 0x40 bytes: the guard record and its state. */
    enum
    {
        BELOW = 0x54
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t list = entry->eax;
    uint32_t flags = entry->edx;
    uint32_t ebp = entry->esp - 4;
    uint32_t result;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if (flags & 4)
    {
        port_set32(&port, ebp, -0x50u, list);
        port_set32(&port, ebp, -0x30u, 1);
        result = port_call(&port, ARRAY_DESTROY, list, STRING_LIST_DESTRUCTOR, 1, list);
        port_set32(&port, ebp, -0x30u, 0);
        port_call(&port, ARRAY_FREE, result, vertrix_lift_edx, 1, list);
        return port_return(&port, list, vertrix_lift_edx);
    }
    port_set32(&port, list, 0, LIST_TABLE);
    port_set32(&port, ebp, -0x28u, list);
    port_set32(&port, ebp, -0x1cu, list);
    port_set8(&port, ebp, -0x24u, 1);
    port_set8(&port, ebp, -0x18u, flags);
    port_set32(&port, ebp, -0x3cu, port.env.chain);
    port_set32(&port, ebp, -0x38u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x34u, STRING_LIST_DESTROY_GUARD);
    port_set32(&port, ebp, -0x30u, 3);
    port_call(&port, STRING_LIST_CLEAR, list, GUARD_HANDLER, flags, list);
    port_set32(&port, ebp, -0x30u, 0);
    result = port_call(&port, LIST_DESTROY, list, 1, flags, list);
    port_set32(&port, ebp, -0x30u, 0);
    edx = 0;
    if (flags & 2)
    {
        port_call(&port, FREE_MEMORY, result, 0, flags, result);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_time_later(PORT_SIGNATURE)
{
    Port port;
    uint32_t first = entry->eax;
    uint32_t second = entry->edx;
    uint32_t days;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, first, 0x20) == 0 && port_u32(&port, second, 0x20) == 0)
    {
        int32_t a = (int32_t)port_u32(&port, first, 0x10);
        int32_t b = (int32_t)port_u32(&port, second, 0x10);
        if (a != b)
        {
            return port_return(&port, a > b, entry->edx);
        }
    }
    days = port_call(&port, TIME_DAYS, first, entry->ebx, entry->ebx, second);
    return port_return(&port,
                       (int32_t)days > (int32_t)port_call(&port, TIME_DAYS, second, entry->ebx,
                                                          entry->ebx, second),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_time_make(PORT_SIGNATURE)
{
    /* push esi, then 0x24 bytes: the struct tm. */
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t tm = entry->esp - BELOW;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->esi);
    port_set32(&port, tm, 0xc, entry->ecx);
    port_set32(&port, tm, 0, entry->arguments[2]);
    port_set32(&port, tm, 4, entry->arguments[1]);
    port_set32(&port, tm, 8, entry->arguments[0]);
    port_set32(&port, tm, 0x10, entry->ebx - 1);
    port_set32(&port, tm, 0x20, entry->arguments[3]);
    port_set32(&port, tm, 0x14, entry->edx - 1900);
    result = port_call(&port, TIME_MAKE, tm, entry->edx - 1900, entry->ebx - 1, entry->ecx);
    port_set32(&port, entry->eax, 0, result);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

uint32_t vertrix_port_time_from_system(PORT_SIGNATURE)
{
    /* push ecx, esi, then the result slot. */
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t system = entry->edx;
    uint32_t slot = entry->esp - BELOW;
    uint32_t year;
    uint32_t arguments[4];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    port_set32(&port, entry->esp, -8u, entry->esi);
    year = port_u16(&port, system, 0);
    if ((int32_t)year < 1900)
    {
        port_set32(&port, entry->eax, 0, 0);
        return port_return(&port, entry->eax, entry->edx);
    }
    arguments[0] = port_u16(&port, system, 8);
    arguments[1] = port_u16(&port, system, 0xa);
    arguments[2] = port_u16(&port, system, 0xc);
    arguments[3] = entry->ebx;
    port_call_stack(&port, TIME_BUILD, slot, year, port_u16(&port, system, 2),
                    port_u16(&port, system, 6), arguments, 4);
    port_set32(&port, entry->eax, 0, port_u32(&port, slot, 0));
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

uint32_t vertrix_port_time_from_file(PORT_SIGNATURE)
{
    /* push ecx, esi, then 0x1c bytes: the SYSTEMTIME, the local FILETIME and the result. */
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t locals = entry->esp - BELOW;
    uint32_t arguments[2];
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    port_set32(&port, entry->esp, -8u, entry->esi);
    arguments[0] = entry->edx;
    arguments[1] = locals + 0x10;
    result = port_call_stack(&port, FILE_TIME_TO_LOCAL, locals + 0x10, entry->edx, entry->ebx,
                             entry->ecx, arguments, 2);
    if (result != 0)
    {
        arguments[0] = locals + 0x10;
        arguments[1] = locals;
        result = port_call_stack(&port, FILE_TIME_TO_SYSTEM, locals + 0x10, vertrix_lift_edx,
                                 entry->ebx, entry->ecx, arguments, 2);
        if (result != 0)
        {
            port_call(&port, TIME_FROM_SYSTEM, locals + 0x18, locals, entry->ebx, entry->ecx);
            result = port_u32(&port, locals, 0x18);
        }
    }
    port_set32(&port, entry->eax, 0, result);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

uint32_t vertrix_port_field4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, 4), entry->edx);
}

uint32_t vertrix_port_clear_flag5a(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0x5a, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_tick_count(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, TICKS, port_u32(&port, 0, TICKS) + 1);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_screen_present_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, SCREEN_PRESENT, SCREEN_STATE, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_input_record_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, record, 0x10, 0);
    port_set32(&port, record, 0x14, 0);
    port_set8(&port, record, 0, entry->edx);
    port_set32(&port, record, 4, entry->ebx);
    port_set32(&port, record, 8, entry->ecx);
    port_set32(&port, record, 0xc, entry->arguments[0]);
    return port_return(&port, record, entry->edx);
}

uint32_t vertrix_port_string_detach(PORT_SIGNATURE)
{
    Port port;
    uint32_t string = entry->eax;
    uint32_t record;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    record = port_u32(&port, string, 0) - 0xc;
    if ((int32_t)port_u32(&port, record, 0) >= 0)
    {
        result = port_call(&port, STRING_COPY_RECORD, string, record, entry->ebx, entry->ecx);
    }
    else
    {
        result =
            port_call(&port, STRING_SET_TEXT, string, STRING_EMPTY_TEXT, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_text_copy(PORT_SIGNATURE)
{
    Port port;
    uint32_t target = entry->eax;
    uint32_t source = entry->edx;
    uint32_t length;
    port_open(&port, calls, services, globals, entry);
    length = port_call(&port, TEXT_LENGTH, source, entry->ebx, entry->ebx, target);
    port_call(&port, COPY_MEMORY, target, source, length + 1, target);
    return port_return(&port, target, vertrix_lift_edx);
}

/* 0x486da0 and 0x485520: the COM restore of the surface at `field`, the result kept at `keep`. */
static uint32_t surface_restore(PORT_SIGNATURE, uint32_t field, uint32_t keep)
{
    Port port;
    uint32_t surface;
    uint32_t methods;
    uint32_t arguments[2];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    surface = port_u32(&port, entry->eax, field);
    methods = port_u32(&port, surface, 0);
    arguments[0] = surface;
    arguments[1] = 0;
    result = port_call_stack(&port, port_u32(&port, methods, 0x80), surface, methods, entry->ebx,
                             entry->ecx, arguments, 2);
    port_set32(&port, 0, keep, result);
    return port_return(&port, result == 0, entry->edx);
}

uint32_t vertrix_port_surface_restore_68(PORT_SIGNATURE)
{
    return surface_restore(calls, services, globals, entry, 0x68, 0x5b9bc8);
}

uint32_t vertrix_port_surface_restore_6c(PORT_SIGNATURE)
{
    return surface_restore(calls, services, globals, entry, 0x6c, 0x5b99c0);
}

uint32_t vertrix_port_surface_set_format(PORT_SIGNATURE)
{
    Port port;
    uint32_t bits = entry->edx & 0xff;
    port_open(&port, calls, services, globals, entry);
    if (bits == 8 || bits == 15 || bits == 16 || bits == 24 || bits == 32)
    {
        port_set8(&port, entry->eax, 0xd,
                  bits == 8    ? 0
                  : bits == 15 ? 1
                  : bits == 16 ? 2
                  : bits == 24 ? 3
                               : 4);
    }
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_pause_toggle(PORT_SIGNATURE)
{
    Port port;
    uint32_t paused;
    port_open(&port, calls, services, globals, entry);
    if (port_call(&port, KEY_READY, KEY_INPUT, PAUSE_KEY, entry->ebx, entry->ecx) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_call(&port, KEY_TAKE, KEY_INPUT, PAUSE_KEY, entry->ebx, entry->ecx);
    paused = 1 - port_u32(&port, 0, PAUSED);
    port_set32(&port, 0, PAUSED, paused);
    return port_return(&port, paused, entry->edx);
}

uint32_t vertrix_port_text_characters(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t left = entry->edx;
    uint32_t count = 0;
    port_open(&port, calls, services, globals, entry);
    for (;;)
    {
        uint32_t size;
        if (port_call(&port, TEXT_AT_END, at, left, at, count) != 0)
        {
            left = vertrix_lift_edx;
            break;
        }
        left = vertrix_lift_edx;
        if (left == 0)
        {
            break;
        }
        size = port_call(&port, CHARACTER_SIZE, at, left, at, count);
        left = vertrix_lift_edx;
        if (left < size)
        {
            break;
        }
        count++;
        left -= size;
        at += size;
    }
    return port_return(&port, count, left);
}

uint32_t vertrix_port_text_copy_limit(PORT_SIGNATURE)
{
    Port port;
    uint32_t target = entry->eax;
    uint32_t at = entry->eax;
    uint32_t source = entry->edx;
    uint32_t left = entry->ebx;
    uint32_t edx;
    uint32_t ecx = entry->ecx;
    port_open(&port, calls, services, globals, entry);
    while (left != 0 && port_u8(&port, source, 0) != 0)
    {
        ecx = (ecx & 0xffffff00u) | port_u8(&port, source, 0);
        port_set8(&port, at, 0, ecx);
        at++;
        source++;
        left--;
    }
    edx = source;
    if (port_u8(&port, source, 0) != 0 && at > target && port_u32(&port, 0, DOUBLE_BYTE_ON) != 0)
    {
        edx = port_u8(&port, 0, DOUBLE_BYTE_LEADS + port_u8(&port, source, -1u)) & 1;
        if (edx != 0)
        {
            port_set8(&port, at, -1u, 0);
        }
    }
    if (left != 0)
    {
        port_call(&port, FILL_BYTES, at, 0, left, ecx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, target, edx);
}

/* DDERR_SURFACELOST. */
static const uint32_t SURFACE_LOST = 0x887601c2u;

uint32_t vertrix_port_object_list_destroy(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax + 0x20;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    port_open(&port, calls, services, globals, entry);
    while (port_u32(&port, list, 0xc) != 0)
    {
        uint32_t item = port_call(&port, LIST_TAKE, list, edx, ebx, list);
        edx = vertrix_lift_edx;
        eax = item;
        if (item != 0)
        {
            ebx = port_u32(&port, item, 0x18);
            eax = port_call(&port, port_u32(&port, ebx, 0), item, 2, ebx, list);
            edx = vertrix_lift_edx;
        }
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_frame_time(PORT_SIGNATURE)
{
    Port port;
    uint32_t now;
    uint32_t last;
    uint32_t delta = 0;
    port_open(&port, calls, services, globals, entry);
    now = port_call_stack(&port, TIME_GET_TIME, entry->eax, entry->edx,
                          port_u32(&port, 0, FRAME_DELTA), entry->ecx, 0, 0);
    port_set32(&port, 0, FRAME_NOW, now);
    last = port_u32(&port, 0, FRAME_LAST);
    if (now > last)
    {
        delta = now - last;
    }
    port_set32(&port, 0, FRAME_LAST, now);
    if (delta >= 0xffff)
    {
        delta = 0xffff;
    }
    port_set32(&port, 0, FRAME_DELTA, delta);
    return port_return(&port, delta, entry->edx);
}

uint32_t vertrix_port_frame_rate(PORT_SIGNATURE)
{
    Port port;
    uint32_t now;
    uint32_t span;
    port_open(&port, calls, services, globals, entry);
    now = port_u32(&port, 0, FRAME_NOW);
    span = now - port_u32(&port, 0, RATE_START);
    port_set32(&port, 0, RATE_TIME, now);
    if (span < 1000)
    {
        return port_return(&port, now, entry->edx);
    }
    port_set32(&port, 0, RATE, port_u32(&port, 0, TICKS) * 1000 / span);
    port_set32(&port, 0, TICKS, 0);
    now = port_u32(&port, 0, FRAME_NOW);
    port_set32(&port, 0, RATE_START, now);
    return port_return(&port, now, entry->edx);
}

/* The surface's COM method at `method`, with its stack arguments after the surface. */
static uint32_t surface_method(Port *port, uint32_t surface, uint32_t method, uint32_t ebx,
                               uint32_t ecx, int flip)
{
    uint32_t methods = port_u32(port, surface, 0);
    uint32_t arguments[3] = {surface, 0, 1};
    return port_call_stack(port, port_u32(port, methods, method), surface, methods, ebx, ecx,
                           arguments, flip ? 3 : 1);
}

uint32_t vertrix_port_surface_flip(PORT_SIGNATURE)
{
    Port port;
    uint32_t screen = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = surface_method(&port, port_u32(&port, screen, 0x64), 0x2c, screen, entry->ecx, 1);
    port_set32(&port, 0, FLIP_RESULT, result);
    if (result != SURFACE_LOST)
    {
        return port_return(&port, result, entry->edx);
    }
    result = surface_method(&port, port_u32(&port, screen, 0x64), 0x6c, screen, entry->ecx, 0);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = surface_method(&port, port_u32(&port, screen, 0x64), 0x2c, screen, entry->ecx, 1);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_word_table_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = entry->edx & 0xff;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 8 + index * 2, entry->ebx);
    return port_return(&port, entry->eax, index);
}

uint32_t vertrix_port_field_04(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, 4), entry->edx);
}

uint32_t vertrix_port_field_08(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, 8), entry->edx);
}

uint32_t vertrix_port_field_0c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, entry->eax, 0xc), entry->edx);
}

uint32_t vertrix_port_clear_first_byte(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_holder_free(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, MEMORY_FREE, port_u32(&port, entry->eax, 0), entry->eax, entry->ebx,
              entry->ecx);
    result =
        port_call(&port, MEMORY_FREE, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_record_clear(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = entry->edx & 0xffff;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_call(&port, CLEAR_FIRST, entry->eax + index * 0x60, index, entry->ebx, entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_string_upper(PORT_SIGNATURE)
{
    Port port;
    uint32_t text;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, STRING_OWN, entry->eax, entry->eax, entry->ebx, entry->ecx);
    text = port_u32(&port, vertrix_lift_edx, 0);
    result = port_call_stack(&port, CHAR_UPPER, result, vertrix_lift_edx, entry->ebx, entry->ecx,
                             &text, 1);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_time_since_frame(PORT_SIGNATURE)
{
    Port port;
    uint32_t now;
    uint32_t last;
    port_open(&port, calls, services, globals, entry);
    now =
        port_call_stack(&port, TIME_GET_TIME, entry->eax, entry->edx, entry->ebx, entry->ecx, 0, 0);
    port_set32(&port, 0, FRAME_NOW, now);
    last = port_u32(&port, 0, FRAME_LAST);
    return port_return(&port, now > last ? now - last : 0, entry->edx);
}

uint32_t vertrix_port_idle_check(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, TIME_SINCE_FRAME, entry->eax, entry->eax, entry->ebx, entry->ecx);
    if (result < 2000)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, IDLE_RUN, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* 0x4194b0 and 0x419490: the cursor routine unless paused or the pointer is hidden. */
static uint32_t cursor_call(PORT_SIGNATURE, uint32_t routine, uint32_t argument)
{
    Port port;
    uint32_t hidden;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, GAME_PAUSED) != 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    hidden = port_u32(&port, 0, POINTER_HIDDEN);
    if (hidden != 0)
    {
        return port_return(&port, hidden, entry->edx);
    }
    result = port_call(&port, routine, argument ? port_u32(&port, 0, CURSOR) : 0, entry->edx,
                       entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_cursor_update(PORT_SIGNATURE)
{
    return cursor_call(calls, services, globals, entry, CURSOR_UPDATE, 1);
}

uint32_t vertrix_port_cursor_draw(PORT_SIGNATURE)
{
    return cursor_call(calls, services, globals, entry, CURSOR_DRAW, 0);
}

uint32_t vertrix_port_input_frame(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock = INPUT_LOCK_SECTION;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call_stack(&port, ENTER_SECTION, entry->eax, entry->edx, entry->ebx, entry->ecx, &lock, 1);
    port_call(&port, KEEP_PLACE, MOUSE, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_call(&port, KEYS_AGE, KEY_INPUT, port_u32(&port, 0, FRAME_DELTA), entry->ebx,
                       entry->ecx);
    result = port_call_stack(&port, LEAVE_SECTION, result, vertrix_lift_edx, entry->ebx, entry->ecx,
                             &lock, 1);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_thread_chain_push(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t thread;
    uint32_t block;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, record, 4, 0);
    thread = port_call_stack(&port, THREAD_ID, record, entry->edx, record, entry->ecx, 0, 0);
    block = port_call(&port, THREAD_BLOCK, THREAD_BLOCKS, THREAD_BLOCK_CREATE, record, thread);
    port_call_stack(&port, SET_LAST_ERROR, block, vertrix_lift_edx, record, thread, &thread, 1);
    port_set32(&port, record, 0, port_u32(&port, block, 0x10));
    port_set32(&port, block, 0x10, record);
    return port_return(&port, record, entry->edx);
}

uint32_t vertrix_port_thread_chain_pop(PORT_SIGNATURE)
{
    Port port;
    uint32_t thread;
    uint32_t block;
    uint32_t top;
    uint32_t edx;
    uint32_t next;
    port_open(&port, calls, services, globals, entry);
    thread =
        port_call_stack(&port, THREAD_ID, entry->eax, entry->edx, entry->ebx, entry->ecx, 0, 0);
    block = port_call(&port, THREAD_BLOCK, THREAD_BLOCKS, THREAD_BLOCK_CREATE, entry->ebx, thread);
    port_call_stack(&port, SET_LAST_ERROR, block, vertrix_lift_edx, block + 0x10, thread, &thread,
                    1);
    top = port_u32(&port, block, 0x10);
    edx = top;
    if (port_u32(&port, top, 4) != 0)
    {
        port_call(&port, CHAIN_CLEANUP, port_u32(&port, top, 4), top, block + 0x10, block + 0x10);
        edx = vertrix_lift_edx;
    }
    next = port_u32(&port, edx, 0);
    port_set32(&port, block, 0x10, next);
    return port_return(&port, next, edx);
}

uint32_t vertrix_port_flag_test_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t flags = entry->eax;
    uint32_t was = 1;
    uint32_t bit;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, flags, 0) & entry->edx)
    {
        return port_return(&port, 1, entry->edx);
    }
    port_call(&port, LOCK_ENTER, FLAG_LOCK, entry->edx, 1, flags);
    bit = vertrix_lift_edx;
    if (!(port_u8(&port, flags, 0) & bit))
    {
        was = 0;
        port_set8(&port, flags, 0, port_u8(&port, flags, 0) | (bit & 0xff));
    }
    port_call(&port, LOCK_LEAVE, FLAG_LOCK, bit, was, flags);
    return port_return(&port, was, vertrix_lift_edx);
}

uint32_t vertrix_port_stream_rewind(PORT_SIGNATURE)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t buffer;
    port_open(&port, calls, services, globals, entry);
    buffer = port_u32(&port, stream, 0);
    port_set32(&port, stream, 4, port_u32(&port, buffer, 0));
    buffer = port_u32(&port, stream, 0);
    port_set32(&port, stream, 8, port_u32(&port, stream, 4) + port_u32(&port, buffer, 4));
    return port_return(&port, stream, entry->edx);
}

uint32_t vertrix_port_stream_tell(PORT_SIGNATURE)
{
    Port port;
    uint32_t place;
    port_open(&port, calls, services, globals, entry);
    place = port_u32(&port, entry->eax, 4) - port_u32(&port, port_u32(&port, entry->eax, 0), 0);
    port_set32(&port, 0, STREAM_TELL, place);
    return port_return(&port, place, entry->edx);
}

uint32_t vertrix_port_stream_seek(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 4,
               port_u32(&port, port_u32(&port, entry->eax, 0), 0) + entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_counted_create(PORT_SIGNATURE)
{
    /* push edx, then 0x20 bytes: the guard record from esp, the object at esp + 0x14. */
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t object = entry->eax;
    uint32_t record = entry->esp - BELOW;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->edx);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, record, 4, GUARD_HANDLER);
    port_set32(&port, record, 8, COUNTED_GUARD);
    port_set32(&port, record, 0xc, 0);
    port_set8(&port, record, 0x18, 0);
    port_set32(&port, record, 0x14, object);
    port_set32(&port, object, 0, LIST_BASE_TABLE);
    port_set32(&port, record, 0xc, 1);
    port_set32(&port, object, 0, COUNTED_TABLE);
    port_set32(&port, object, 4, 1);
    return port_return(&port, object, entry->edx);
}

uint32_t vertrix_port_timer_count(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock = TIMER_LOCK;
    uint32_t count;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_stack(&port, ENTER_SECTION, entry->eax, entry->edx, entry->ebx, entry->ecx,
                          &lock, 1);
    count = port_u32(&port, 0, TIMER_COUNT);
    port_call_stack(&port, LEAVE_SECTION, eax, vertrix_lift_edx, count, entry->ecx, &lock, 1);
    return port_return(&port, count, entry->edx);
}

uint32_t vertrix_port_timer_advance(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock = TIMER_LOCK;
    uint32_t ticks = entry->eax;
    uint32_t eax;
    uint32_t application;
    port_open(&port, calls, services, globals, entry);
    eax =
        port_call_stack(&port, ENTER_SECTION, entry->eax, entry->edx, ticks, entry->ecx, &lock, 1);
    port_set32(&port, 0, TIMER_COUNT, port_u32(&port, 0, TIMER_COUNT) + ticks);
    eax = port_call_stack(&port, LEAVE_SECTION, eax, port_u32(&port, 0, TIMER_COUNT), ticks,
                          entry->ecx, &lock, 1);
    application = port_call(&port, MAIN_APPLICATION, eax, vertrix_lift_edx, ticks, entry->ecx);
    eax = port_call(&port, SCREEN_REFRESH, port_u32(&port, port_u32(&port, application, 4), 0x1c),
                    0, ticks, entry->ecx);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_screen_refresh(PORT_SIGNATURE)
{
    Port port;
    uint32_t window = entry->eax;
    uint32_t count;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    count = port_call(&port, TIMER_COUNT_GET, window, port_u32(&port, 0, TIMER_DRAWN), entry->edx,
                      window);
    if (vertrix_lift_edx == count && entry->edx != 1)
    {
        return port_return(&port, count, vertrix_lift_edx);
    }
    port_set32(&port, 0, TIMER_DRAWN, count);
    result = port_call(&port, SCREEN_REPAINT, window, vertrix_lift_edx,
                       port_u32(&port, 0, TIMER_SURFACE), window);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_screen_blit(PORT_SIGNATURE)
{
    Port port;
    uint32_t buffer;
    uint32_t arguments[4];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    buffer = port_u32(&port, entry->eax, 0xd0);
    arguments[0] = 0;
    arguments[1] = 0;
    arguments[2] = port_u32(&port, buffer, 4) * entry->ebx / entry->ecx;
    arguments[3] = port_u32(&port, buffer, 8);
    result = port_call_stack(&port, SCREEN_BLIT, entry->edx, buffer, 0, 0x1cd, arguments, 4);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_triple_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t table = entry->eax;
    uint32_t offset = entry->edx << 2;
    uint32_t slot;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, port_u32(&port, table, 0xc), offset, entry->ebx);
    port_set32(&port, port_u32(&port, table, 0x10), offset, entry->ecx);
    slot = port_u32(&port, table, 8) + offset;
    port_set32(&port, slot, 0, entry->arguments[0]);
    return port_return(&port, slot, entry->arguments[0]);
}

uint32_t vertrix_port_list_init_516d94(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, list, 0x18, 0x516d94);
    for (offset = 0; offset <= 0x14; offset += 4)
    {
        port_set32(&port, list, offset, 0);
    }
    return port_return(&port, list, entry->edx);
}

uint32_t vertrix_port_input_state_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t state = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, state, 0x18, 0x5165c4);
    port_set8(&port, state, 0, 0);
    port_set32(&port, state, 4, 0);
    port_set32(&port, state, 8, 0);
    port_set32(&port, state, 0xc, 0);
    port_set16(&port, state, 0x10, 0);
    port_set32(&port, state, 0x14, 0);
    return port_return(&port, state, entry->edx);
}

uint32_t vertrix_port_set_first_byte(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0, 1);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_record_mark(PORT_SIGNATURE)
{
    Port port;
    uint32_t index = entry->edx & 0xffff;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, SET_FIRST, entry->eax + index * 0x60, index, entry->ebx, entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_key_record_clear(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t zero = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, KEY_FLAG_CLEAR, record, entry->edx, entry->ebx, entry->ecx);
    port_call_stack(&port, KEY_STATE, record + 4, 0, 0, 0, &zero, 1);
    result = port_call(&port, KEY_EVENTS, record, vertrix_lift_edx, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_object_field4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, port_u32(&port, entry->eax, 0), 4), entry->edx);
}

uint32_t vertrix_port_call_4b7b00(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, CALL_4B7B00, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_resource_frame(PORT_SIGNATURE)
{
    Port port;
    uint32_t resource = entry->eax;
    port_open(&port, calls, services, globals, entry);
    if (port_call(&port, RESOURCE_IS_LOADED, resource, entry->edx, entry->ebx, resource) != 1)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    return port_return(&port, port_u32(&port, port_u32(&port, resource, 8), vertrix_lift_edx * 4),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_call_48a930(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, CALL_48A930, entry->eax, entry->edx, 1, 2);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_fixed_divide(PORT_SIGNATURE)
{
    Port port;
    int64_t dividend = (int64_t)(int32_t)entry->eax * 65536;
    int64_t divisor = (int32_t)entry->edx;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, (uint32_t)(dividend / divisor), (uint32_t)(dividend % divisor));
}

uint32_t vertrix_port_array_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t array;
    port_open(&port, calls, services, globals, entry);
    array = port_u32(&port, entry->eax, 0);
    port_set32(&port, array, entry->edx * 4, entry->ebx);
    return port_return(&port, array, entry->edx);
}

uint32_t vertrix_port_list_delete_4b5e70(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, LIST_REMOVE, entry->eax, port_u32(&port, entry->eax, 8), entry->edx, 1);
    return port_return(&port, 0, vertrix_lift_edx);
}

uint32_t vertrix_port_frame_time_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t now;
    port_open(&port, calls, services, globals, entry);
    now =
        port_call_stack(&port, TIME_GET_TIME, entry->eax, entry->edx, entry->ebx, entry->ecx, 0, 0);
    port_set32(&port, 0, FRAME_NOW, now);
    port_set32(&port, 0, FRAME_LAST, now);
    return port_return(&port, now, entry->edx);
}

uint32_t vertrix_port_image_show(PORT_SIGNATURE)
{
    Port port;
    uint32_t image;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    image = port_call(&port, IMAGE_LOAD, IMAGE_LIBRARY, entry->eax, 0, 0);
    port_call(&port, IMAGE_DRAW, image, entry->edx, 0, 0);
    result = port_call(&port, IMAGE_RELEASE, image, IMAGE_RELEASE_STATE, 0, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_pair_set(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0, entry->edx);
    port_set32(&port, entry->eax, 4, entry->ebx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_word_table_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t table = entry->eax;
    uint32_t index;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, table, 0x208, 0x5176b4);
    port_set32(&port, table, 0, 0);
    port_set32(&port, table, 4, 0);
    for (index = 0; index < 0xff; index++)
    {
        port_set16(&port, table, 8 + index * 2, 0xffff);
    }
    return port_return(&port, table, entry->edx);
}

uint32_t vertrix_port_block_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t block;
    port_open(&port, calls, services, globals, entry);
    block = port_call(&port, BLOCK_ALLOCATE, entry->eax, entry->eax, entry->ebx, entry->ecx);
    if (block != 0)
    {
        port_set32(&port, block, 0, vertrix_lift_edx);
    }
    return port_return(&port, block, entry->edx);
}

uint32_t vertrix_port_list_construct_518344(PORT_SIGNATURE)
{
    Port port;
    uint32_t list;
    port_open(&port, calls, services, globals, entry);
    list = port_call(&port, LIST_CREATE, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, list, 0, LIST_TABLE_518344);
    return port_return(&port, list, vertrix_lift_edx);
}

uint32_t vertrix_port_dword_array_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t array = entry->eax;
    uint32_t memory;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, array, 4, entry->edx);
    memory = port_call(&port, CLEAR_ALLOCATE, entry->edx, 4, entry->ebx, array);
    port_set32(&port, array, 0, memory);
    return port_return(&port, memory, vertrix_lift_edx);
}

uint32_t vertrix_port_counted_unlock(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock = entry->eax;
    uint32_t count;
    uint32_t eax = entry->eax;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, lock, 0xc);
    if (count != 0)
    {
        port_set32(&port, lock, 0xc, count - 1);
        if (count - 1 == 0)
        {
            uint32_t section = port_u32(&port, lock, 0);
            port_set32(&port, lock, 8, 0);
            eax = port_call_stack(&port, LEAVE_SECTION, lock, count, 0, entry->ecx, &section, 1);
        }
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_free_list_push(PORT_SIGNATURE)
{
    Port port;
    uint32_t node;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, LOCK_ENTER, FLAG_LOCK, entry->eax, entry->ebx, entry->ecx);
    node = vertrix_lift_edx;
    port_set32(&port, node, 0, port_u32(&port, 0, FREE_LIST));
    port_set32(&port, 0, FREE_LIST, node);
    result = port_call(&port, LOCK_LEAVE, FLAG_LOCK, node, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_object_release_if(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, entry->eax, 0) == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    port_call(&port, OBJECT_RELEASE, entry->eax, entry->edx, entry->ebx, entry->eax);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

uint32_t vertrix_port_text_copy_padded(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t source = entry->edx;
    uint32_t left = entry->ebx;
    port_open(&port, calls, services, globals, entry);
    while (left != 0 && port_u8(&port, source, 0) != 0)
    {
        port_set8(&port, at, 0, port_u8(&port, source, 0));
        at++;
        source++;
        left--;
    }
    while (left != 0)
    {
        port_set8(&port, at, 0, 0);
        at++;
        left--;
    }
    return port_return(&port, entry->eax, 0);
}

uint32_t vertrix_port_link_push(PORT_SIGNATURE)
{
    Port port;
    uint32_t list = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, port_u32(&port, list, 4), entry->edx, port_u32(&port, list, 0));
    port_set32(&port, list, 0, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_lock_leave(PORT_SIGNATURE)
{
    Port port;
    uint32_t section;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, LOCKING_OFF) != 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    section = entry->arguments[0] * 0x18 + LOCK_SECTIONS;
    result = port_call_stack(&port, LEAVE_SECTION, section, entry->edx, entry->ebx, entry->ecx,
                             &section, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_application_link(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t zero = 0;
    uint32_t application;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    application = port_call(&port, MAIN_APPLICATION, value, entry->edx, value, entry->ecx);
    port_call_stack(&port, LOCK_TAKE, application, vertrix_lift_edx, value, entry->ecx, &zero, 1);
    eax = port_call(&port, LINK_PUSH, application + 0x1c, entry->edx, value, entry->ecx);
    port_call_stack(&port, LOCK_GIVE, eax, vertrix_lift_edx, value, entry->ecx, &zero, 1);
    return port_return(&port, value, vertrix_lift_edx);
}

uint32_t vertrix_port_lock_enter_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, port_u32(&port, 0, LOCK_ROUTINE), entry->eax, entry->edx, entry->ebx,
                       entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_lock_leave_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, port_u32(&port, 0, UNLOCK_ROUTINE), entry->eax, entry->edx,
                       entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_time_now(PORT_SIGNATURE)
{
    /* push ebx, edx, then 0x24 bytes: the struct tm. */
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t tm = entry->esp - BELOW;
    uint32_t time;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->edx);
    if ((int32_t)port_call(&port, LOCAL_TIME, tm, entry->eax, entry->ebx, entry->ecx) >= 500)
    {
        port_set32(&port, tm, 0, port_u32(&port, tm, 0) + 1);
    }
    time = port_call(&port, TIME_MAKE, tm, vertrix_lift_edx, entry->ebx, entry->ecx);
    if (vertrix_lift_edx != 0)
    {
        port_set32(&port, vertrix_lift_edx, 0, time);
    }
    return port_return(&port, time, entry->edx);
}

uint32_t vertrix_port_load_prepare(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, IMAGE_LOAD, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (result != 0)
    {
        result =
            port_call(&port, RESOURCE_PREPARE, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_triple_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t table = entry->eax;
    uint32_t memory;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, table, 4, entry->edx);
    port_set32(&port, table, 8, port_call(&port, CLEAR_ALLOCATE, entry->edx, 4, entry->ebx, table));
    port_set32(&port, table, 0xc,
               port_call(&port, CLEAR_ALLOCATE, port_u32(&port, table, 4), 4, entry->ebx, table));
    memory = port_call(&port, CLEAR_ALLOCATE, port_u32(&port, table, 4), 4, entry->ebx, table);
    port_set32(&port, table, 0x14, 1);
    port_set32(&port, table, 0x10, memory);
    return port_return(&port, memory, vertrix_lift_edx);
}

uint32_t vertrix_port_holder_free_if(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (entry->eax == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_call(&port, MEMORY_FREE, port_u32(&port, entry->eax, 0), entry->eax, entry->ebx,
              entry->ecx);
    result =
        port_call(&port, MEMORY_FREE, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_random_range(PORT_SIGNATURE)
{
    Port port;
    uint32_t span = entry->ebx - entry->edx + 1;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_call(&port, RANDOM_NEXT, entry->eax, span & 0xffff, span, entry->edx);
    return port_return(&port, (value & 0xffff) + (entry->edx & 0xffff), entry->edx & 0xffff);
}

uint32_t vertrix_port_bank_table_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, TRIPLE_ALLOCATE, BANKS + entry->eax * 0x118 + entry->edx * 0x1c,
                       entry->ebx, entry->ebx, entry->edx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_list_construct_518704(PORT_SIGNATURE)
{
    Port port;
    uint32_t list;
    port_open(&port, calls, services, globals, entry);
    list = port_call(&port, LIST_CREATE, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, list, 0, LIST_TABLE_518704);
    return port_return(&port, list, vertrix_lift_edx);
}

uint32_t vertrix_port_list_construct_517644(PORT_SIGNATURE)
{
    Port port;
    uint32_t list;
    port_open(&port, calls, services, globals, entry);
    list = port_call(&port, LIST_CONSTRUCT_518704, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, list, 0x14, 0x517644);
    return port_return(&port, list, vertrix_lift_edx);
}

uint32_t vertrix_port_local_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t arguments[2] = {0x40, entry->arguments[0]};
    uint32_t memory;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    memory = port_call_stack(&port, LOCAL_ALLOC, entry->eax, entry->edx, entry->ebx, entry->ecx,
                             arguments, 2);
    edx = vertrix_lift_edx;
    if (memory == 0)
    {
        port_call(&port, OUT_OF_MEMORY, 0, edx, 0, entry->ecx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, memory, edx);
}

uint32_t vertrix_port_state_set_c0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xc0, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_state_copy_c0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xbc, port_u32(&port, entry->eax, 0xc0));
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_state_set_bc(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xbc, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_handle_close_clear(PORT_SIGNATURE)
{
    Port port;
    uint32_t holder = entry->arguments[0];
    uint32_t handle;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    handle = port_u32(&port, holder, 0);
    if (handle == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result =
        port_call_stack(&port, 0x4f17e0, entry->eax, entry->edx, holder, entry->ecx, &handle, 1);
    port_set32(&port, holder, 0, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_nothing_4e04f4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_box_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t box = entry->eax;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, box, 0x3c, entry->edx);
    port_set16(&port, box, 0x40, entry->ecx);
    port_set16(&port, box, 0x3e, entry->ebx);
    port_set16(&port, box, 0x42, entry->arguments[0]);
    return port_return(&port, box, entry->arguments[0]);
}

uint32_t vertrix_port_bank_list_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result = port_call(&port, 0x487640, 0x546458 + entry->eax * 0x1c, entry->edx, entry->ebx,
                       entry->eax * 4);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_clock_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t now;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4b7cd0, entry->eax, 0, entry->ebx, entry->ecx);
    now = port_u32(&port, FRAME_NOW, 0);
    port_set32(&port, 0x5329f8, 0, 0);
    port_set32(&port, 0x5329fc, 0, now);
    port_set32(&port, 0x532a04, 0, 0);
    return port_return(&port, now, entry->edx);
}

uint32_t vertrix_port_actor_set_b4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xb4, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_take_f0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x154, port_u32(&port, entry->eax, 0xf0));
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_rule_set_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x34, 0x517a44);
    port_call(&port, 0x48d480, entry->eax, entry->eax, entry->ebx, entry->ecx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_reader_restart(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, entry->eax, 0xc, 0);
    port_set32(&port, entry->eax, 8, port_u32(&port, entry->eax, 0));
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_audio_hook_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t slot = 0;
    port_open(&port, calls, services, globals, entry);
    for (;;)
    {
        uint32_t hook = port_u32(&port, 0x52f090, slot * 4);
        if (hook == 0 || hook == entry->eax)
        {
            break;
        }
        if (++slot >= 8)
        {
            return port_return(&port, 8, entry->edx);
        }
    }
    port_set32(&port, 0x52f090, slot * 4, entry->eax);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_list_construct_517a94(PORT_SIGNATURE)
{
    Port port;
    uint32_t list;
    port_open(&port, calls, services, globals, entry);
    list = port_call(&port, LIST_CREATE, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, list, 0, 0x517a94);
    return port_return(&port, list, vertrix_lift_edx);
}

uint32_t vertrix_port_key_records_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t key;
    port_open(&port, calls, services, globals, entry);
    for (key = 0; key < 0x100; key++)
    {
        port_call(&port, 0x475a20, entry->eax + key * 0x60, key + 1, entry->ebx, entry->eax);
    }
    return port_return(&port, 0x100, entry->edx);
}

uint32_t vertrix_port_layer_top_draw(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4b5fc0, 0x54676c, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_bank_setup_5466a4(PORT_SIGNATURE)
{
    Port port;
    uint32_t first;
    uint32_t second;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x487640, 0x5466a4, 1, entry->ebx, entry->ecx);
    first = port_call(&port, 0x4877f0, 0x546538, 9, entry->ebx, entry->ecx);
    second = port_call(&port, 0x4877f0, 0x5449fc, port_u32(&port, 0x4fbf74, 0), 1, first);
    result = port_call(&port, 0x4831b0, second, first, 1, first);
    result = port_call(&port, 0x487850, 0x5466a4, 0, result, first);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_surface_create_544a6c(PORT_SIGNATURE)
{
    Port port;
    static const uint32_t stack[10] = {0, 0, 0, 0, 0xa0, 0x78, 0, 0, 0, 4};
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call_stack(&port, 0x4875a0, 0x544a6c, 0x14, 0xa0, 0x78, stack, 10);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_surface_create_544d28(PORT_SIGNATURE)
{
    Port port;
    static const uint32_t stack[10] = {0, 0, 0, 0, 0x1e, 0x1e, 0, 0, 1, 4};
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call_stack(&port, 0x4875a0, 0x544d28, 8, 0x1e, 0x1e, stack, 10);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_square_setup(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set16(&port, actor, 0x12, 8);
    port_set16(&port, actor, 0x10, port_u16(&port, actor, 0x14));
    port_set16(&port, actor, 0x18, port_u16(&port, actor, 0x1c));
    port_set16(&port, actor, 0x1a, 8);
    port_call(&port, 0x4ac7b0, actor, 2, entry->ebx, actor);
    port_call(&port, 0x4ac510, actor, 0x448790, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_scene_leave(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x41aa20, entry->eax, entry->eax, entry->ebx, entry->ecx);
    result = port_call(&port, 0x41aaa0, vertrix_lift_edx, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4b7cd0, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x477d70, 0x5588f8, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_view_rect_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t scene;
    uint32_t stack[4];
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    scene = port_u32(&port, 0x544070, 0);
    stack[0] = port_u16(&port, scene, 0x214);
    stack[1] = port_u16(&port, scene, 0x216);
    stack[2] = port_u16(&port, scene, 0x218);
    stack[3] = port_u16(&port, scene, 0x21a);
    result = port_call_stack(&port, 0x47ce10, port_u32(&port, 0x558c80, 0),
                             port_u32(&port, scene, 0x268), 0, 0, stack, 4);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_scene_release(PORT_SIGNATURE)
{
    Port port;
    uint32_t scene;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x441a80, port_u32(&port, 0x544070, 0), entry->edx, entry->ebx,
                       entry->ecx);
    scene = port_u32(&port, 0x544070, 0);
    if (scene != 0)
    {
        uint32_t table = port_u32(&port, scene, 0x27c);
        result = port_call(&port, port_u32(&port, table, 0), scene, 2, entry->ebx, table);
    }
    port_set32(&port, 0x544070, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_scene_flag_enter(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x540040, 0, 1);
    result = port_call(&port, 0x41a040, entry->eax, 1, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_scene_flag_clear(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x54004c, 0, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_block_chain_free(PORT_SIGNATURE)
{
    Port port;
    uint32_t block = entry->eax;
    port_open(&port, calls, services, globals, entry);
    while (block != 0)
    {
        uint32_t next = port_u32(&port, block, 0);
        port_call(&port, 0x4ca040, block, next, entry->ebx, entry->ecx);
        block = next;
    }
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_queue_pop(PORT_SIGNATURE)
{
    Port port;
    uint32_t queue = entry->eax;
    uint32_t node;
    uint32_t next;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    node = port_u32(&port, queue, 4);
    next = port_u32(&port, node, 0);
    value = port_u32(&port, node, 8);
    port_set32(&port, queue, 4, next);
    if (next != 0)
    {
        port_set32(&port, next, 4, 0);
    }
    else
    {
        port_set32(&port, queue, 8, 0);
    }
    port_call(&port, 0x4d84f0, queue, node, next, value);
    return port_return(&port, value, entry->edx);
}

uint32_t vertrix_port_queue_push(PORT_SIGNATURE)
{
    Port port;
    uint32_t queue = entry->eax;
    uint32_t node;
    uint32_t last;
    port_open(&port, calls, services, globals, entry);
    node = port_call(&port, 0x4d8490, queue, port_u32(&port, queue, 8), 0, queue);
    port_set32(&port, node, 8, entry->edx);
    last = port_u32(&port, queue, 8);
    if (last != 0)
    {
        port_set32(&port, last, 0, node);
    }
    else
    {
        port_set32(&port, queue, 4, node);
    }
    port_set32(&port, queue, 8, node);
    return port_return(&port, node, node);
}

uint32_t vertrix_port_pool_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t pool = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, pool, 0xc, 0);
    port_set32(&port, pool, 0x10, 0);
    port_set32(&port, pool, 8, 0);
    port_set32(&port, pool, 4, 0);
    result = port_call(&port, 0x4e2400, port_u32(&port, pool, 0x14), pool, entry->ebx, entry->ecx);
    port_set32(&port, pool, 0x14, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_cell_colour_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t cell;
    port_open(&port, calls, services, globals, entry);
    cell = port_call(&port, 0x478d10, port_u16(&port, record, 0x3e), port_u16(&port, record, 0x40),
                     port_u8(&port, record, 0x10), record);
    port_set8(&port, cell, 0xd, port_u8(&port, record, 0x24));
    return port_return(&port, cell, entry->edx);
}

uint32_t vertrix_port_sound_play_if_ready(PORT_SIGNATURE)
{
    Port port;
    uint32_t sound = entry->eax & 0xff;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4829c0, sound, entry->edx, entry->ebx, sound);
    if (result == 1)
    {
        result = port_call(&port, 0x482a40, sound, vertrix_lift_edx, entry->ebx, sound);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_sound_play(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x40adc0, port_u32(&port, 0x598d88, (entry->eax & 0xff) * 4),
                       entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_buffer_4k_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t buffer;
    port_open(&port, calls, services, globals, entry);
    buffer = port_call(&port, 0x4ec160, 0x1001, 2, entry->ebx, entry->eax);
    port_set8(&port, entry->eax, 4, 1);
    port_set32(&port, entry->eax, 0, buffer);
    return port_return(&port, buffer, entry->edx);
}

uint32_t vertrix_port_reader_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x14, 0x516c24);
    port_set32(&port, entry->eax, 0, 0);
    port_set8(&port, entry->eax, 4, 1);
    port_set32(&port, entry->eax, 8, 0);
    port_set16(&port, entry->eax, 0xc, 0);
    port_set32(&port, entry->eax, 0x10, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_key_slots_clear(PORT_SIGNATURE)
{
    Port port;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xa4, 0);
    port_set32(&port, entry->eax, 0xa8, 0);
    port_set32(&port, entry->eax, 0xac, 0);
    port_set32(&port, entry->eax, 0xb0, 0);
    for (offset = 0x24; offset <= 0xa0; offset += 4)
    {
        port_set32(&port, entry->eax, offset, 0);
    }
    return port_return(&port, entry->eax + 0x80, entry->edx);
}

uint32_t vertrix_port_key_construct(PORT_SIGNATURE)
{
    Port port;
    uint32_t key = entry->eax;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, key, 0xcc, 0x5166d4);
    port_set8(&port, key, 8, 0);
    port_set32(&port, key, 4, 0);
    port_set32(&port, key, 0x1c, 0);
    port_set32(&port, key, 0x20, 0);
    port_set32(&port, key, 0x14, 0);
    port_set32(&port, key, 0x18, 0);
    port_set32(&port, key, 0x10, 0);
    port_set32(&port, key, 0xc, 0);
    for (offset = 0x24; offset <= 0xa0; offset += 4)
    {
        port_set32(&port, key, offset, 0);
    }
    port_set32(&port, key, 0xa4, 0);
    port_set32(&port, key, 0xa8, 0);
    port_set32(&port, key, 0xac, 0);
    port_set32(&port, key, 0xb0, 0);
    return port_return(&port, key, entry->edx);
}

uint32_t vertrix_port_key_pair_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x476140, entry->eax, 0x7a, entry->ebx, entry->eax);
    result = port_call(&port, 0x476140, entry->eax, 0x7b, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_key_all_release(PORT_SIGNATURE)
{
    Port port;
    uint32_t key;
    uint32_t result = entry->eax;
    port_open(&port, calls, services, globals, entry);
    for (key = 0; key < 0x100; key++)
    {
        result = port_call(&port, 0x476120, entry->eax, key, key, entry->eax);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_record_free_test(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u8(&port, entry->eax, 0x5a) == 0, entry->edx);
}

uint32_t vertrix_port_entry_copy(PORT_SIGNATURE)
{
    Port port;
    uint32_t last;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, entry->eax, 0, port_u8(&port, entry->edx, 0));
    port_set32(&port, entry->eax, 4, port_u32(&port, entry->edx, 4));
    port_set32(&port, entry->eax, 8, port_u32(&port, entry->edx, 8));
    last = port_u32(&port, entry->edx, 0xc);
    port_set32(&port, entry->eax, 0xc, last);
    return port_return(&port, entry->eax, last);
}

uint32_t vertrix_port_stream_open_513e60(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4cea15, entry->eax, 4, 0x513e60, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_bank_slot_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result = port_call(&port, 0x487640, entry->eax * 0x1c + 0x544d7c, entry->edx, entry->ebx,
                       entry->eax * 4);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_restart_45d160(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x45cff0, actor, entry->edx, entry->ebx, actor);
    port_call(&port, 0x4ac510, actor, 0x45d160, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_restart_45d100(PORT_SIGNATURE)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t wait;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x45cff0, actor, entry->edx, entry->ebx, actor);
    wait = port_call(&port, 0x4826c0, 0x598d30, 0x2710, entry->ebx, actor);
    port_call(&port, 0x4ac7d0, actor, (wait & 0xffff) + 0x7d0, entry->ebx, actor);
    port_call(&port, 0x4ac510, actor, 0x45d100, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c8b04(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c8b04, 0x50c428, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c8a84(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c8a84, 0x50ae38, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_handle_mark_text(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    record = port_call(&port, port_u32(&port, 0x507c9c, 0), entry->eax, entry->edx, entry->ebx,
                       entry->ecx) +
             port_u32(&port, 0x5c5c54, 0);
    port_set8(&port, record, 4, port_u8(&port, record, 4) | 2);
    return port_return(&port, record, vertrix_lift_edx);
}

uint32_t vertrix_port_error_set_code(PORT_SIGNATURE)
{
    Port port;
    uint32_t code = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (code == 0xfffffffd)
    {
        code = 0xffffffff;
    }
    else if (code == 0)
    {
        code = 0xfffffffd;
    }
    else if (code == 0x3a4)
    {
        code = 0xfffffffc;
    }
    result = port_call(&port, 0x4e6f60, code, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, (result == 0) - 1, vertrix_lift_edx);
}

uint32_t vertrix_port_stream_reset_text(PORT_SIGNATURE)
{
    Port port;
    static const uint32_t stack[2] = {0, 0x410};
    port_open(&port, calls, services, globals, entry);
    port_call_stack(&port, 0x4ec910, entry->eax, entry->edx, entry->eax, entry->ecx, stack, 2);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_hooks_set_509794(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x509794, 0, 0x4ec970);
    port_set32(&port, 0x509798, 0, 0x4eca85);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_hooks_set_507cdc(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x507cdc, 0, 0x4e8d38);
    port_set32(&port, 0x507ce0, 0, 0x4e8d80);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_zero_4ea130(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_hook_call_50b20c(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, port_u32(&port, 0x50b20c, 0), entry->eax, entry->edx, entry->ebx,
                       entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_thread_record_start(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (record == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_set32(&port, record, 0xc, 1);
    result = port_call(&port, 0x4e6630, record, 0, record, entry->ecx);
    result =
        port_call_stack(&port, 0x4f1ba0, result, vertrix_lift_edx, record, entry->ecx, NULL, 0);
    port_set32(&port, record, 0xda, result);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_threads_mark_all(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t thread;
    port_call(&port, port_u32(&port, 0x507cc8, 0), entry->eax, entry->edx, entry->ebx, entry->ecx);
    thread = vertrix_lift_edx;
    for (record = port_u32(&port, 0x5c8aa0, 0); record != 0; record = port_u32(&port, record, 0))
    {
        thread = port_u32(&port, record, 8);
        port_set8(&port, thread, 0x53, 1);
    }
    result = port_call(&port, port_u32(&port, 0x507ccc, 0), 0, thread, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_nothing_425f40(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_nothing_4e08b0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_hook_call_52f024(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, port_u32(&port, 0x52f024, 0), entry->eax, entry->edx, entry->ebx,
                       entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_hook_call_52f044(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, port_u32(&port, 0x52f044, 0), entry->eax, entry->edx, entry->ebx,
                       entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_hook_call_52f048(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, port_u32(&port, 0x52f048, 0), entry->eax, entry->edx, entry->ebx,
                       entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_hook_call_52f04c(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, port_u32(&port, 0x52f04c, 0), entry->eax, entry->edx, entry->ebx,
                       entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_pointer_add_4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, entry->eax + 4, entry->edx);
}

uint32_t vertrix_port_table_set_5167a4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0xc, 0x5167a4);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_table_set_516c84(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 4, 0x516c84);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_actor_set_11c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x11c, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_frame_count_get(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, 0x5bd83c, 0), entry->edx);
}

uint32_t vertrix_port_global_set_52fc30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x52fc30, 0, entry->eax);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_global_set_532574(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x532574, 0, entry->eax);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_layer_draw_54671c(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4b5fc0, 0x54671c, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_layer_clear_54671c(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4b61c0, 0x54671c, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_layer_clear_546744(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4b61c0, 0x546744, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_layer_clear_546730(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4b61c0, 0x546730, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_list_construct_518574(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d8650, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, result, 0, 0x518574);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_global_get_5c7b9c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, port_u32(&port, 0x5c7b9c, 0), entry->edx);
}

uint32_t vertrix_port_reader_construct_516744(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x14, 0x516744);
    port_set8(&port, entry->eax, 4, 0);
    port_set32(&port, entry->eax, 0, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_handle_table_allocate(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4e62b0, 0x24, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, 0x5c5c54, 0, result);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_global_clear_540014(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x540014, 0, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_sound_object_construct(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x481b20, entry->eax + 0x10, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, result, 0x60, 0x516d34);
    return port_return(&port, result - 0x10, vertrix_lift_edx);
}

uint32_t vertrix_port_frame_counter_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x484410, 0x5bd82c, entry->edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4ec1f7, 0x4ff89b, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_bank_allocate_544a34(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x487640, 0x544a34, 0x13, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_bank_load_544a88(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4876c0, 0x544a88, 0x50, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_layer_add_54671c(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4b6070, 0x54671c, entry->eax, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_layer_add_546744(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4b6070, 0x546744, entry->eax, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_layer_add_546730(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4b6070, 0x546730, entry->eax, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_scale_reset(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0, 0);
    port_set32(&port, entry->eax, 4, 0);
    port_set32(&port, entry->eax, 8, 0x1800000);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_lock_init_5bb228(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5bb228, 0x4fec10, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c5c50(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c5c50, 0x501368, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c7560(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c7560, 0x502e48, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c7600(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c7600, 0x503e68, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c7604(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c7604, 0x5041a8, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c7610(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c7610, 0x5044b8, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c7614(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c7614, 0x5047d8, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c7750(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c7750, 0x5051a8, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c7b88(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c7b88, 0x507c08, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c81c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c81c0, 0x508158, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_init_5c8a80(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4d30f0, 0x5c8a80, 0x50ab28, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_level_restart(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x532a38, 0, 0);
    result = port_call(&port, 0x415580, entry->eax, 0, entry->ebx, entry->ecx);
    result = port_call(&port, 0x413bd0, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_file_object_new(PORT_SIGNATURE)
{
    Port port;
    static const uint32_t size = 0x103c;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_call_stack(&port, 0x4dba80, entry->eax, entry->edx, entry->ebx, entry->ecx, &size, 1);
    if (result == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    result = port_call(&port, 0x4ce230, result, 1, entry->ebx, entry->ecx);
    port_set32(&port, result, 0, 0x519374);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_stream_object_new(PORT_SIGNATURE)
{
    Port port;
    static const uint32_t size = 0x114;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_call_stack(&port, 0x4dba80, entry->eax, entry->edx, entry->ebx, entry->ecx, &size, 1);
    if (result != 0)
    {
        port_set32(&port, result, 0, 0x519334);
        port_set32(&port, result, 0xd8, 0xffffffff);
        port_set32(&port, result, 0x104, 0xffffffff);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_hud_layer_add_54671c(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4854a0, 0x5b9c50, entry->edx, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_call(&port, 0x4719f0, port_u32(&port, 0x558c84, 0), vertrix_lift_edx, entry->ebx,
              entry->ecx);
    result = port_call(&port, 0x485520, 0x5b9c50, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_hud_layer_add_546730(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4854a0, 0x5b9c50, entry->edx, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_call(&port, 0x471b20, port_u32(&port, 0x558c84, 0), vertrix_lift_edx, entry->ebx,
              entry->ecx);
    result = port_call(&port, 0x485520, 0x5b9c50, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_hud_layer_add_546744(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4854a0, 0x5b9c50, entry->edx, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_call(&port, 0x471aa0, port_u32(&port, 0x558c84, 0), vertrix_lift_edx, entry->ebx,
              entry->ecx);
    result = port_call(&port, 0x485520, 0x5b9c50, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_record_start(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x44, 0);
    port_set32(&port, entry->eax, 0x48, port_u32(&port, entry->eax, 0x3c));
    port_set8(&port, entry->eax, 0x5a, 1);
    port_set32(&port, entry->eax, 0x4c, entry->edx);
    port_set32(&port, entry->eax, 0x50, entry->ebx);
    port_set32(&port, entry->eax, 0x54, entry->ecx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_memory_free_dispatch(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, 0x5054a1, 0) != 0)
    {
        result = port_call(&port, 0x4db719, entry->eax, entry->edx, entry->ebx, entry->ecx);
    }
    else
    {
        result = port_call(&port, 0x4c9b6a, entry->eax, entry->edx, 0, entry->ecx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_memory_free_dispatch_4db7c8(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, 0x5054a1, 0) != 0)
    {
        result = port_call(&port, 0x4db7c8, entry->eax, entry->edx, entry->ebx, entry->ecx);
    }
    else
    {
        result = port_call(&port, 0x4c9b6a, entry->eax, entry->edx, 1, entry->ecx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_table_init_541988(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4ccf3b, 0x541988, 0x13, 0x514fb0, entry->ecx);
    result = port_call(&port, 0x4ec1f7, 0x4fb9ae, vertrix_lift_edx, 0x514fb0, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_player_target_take(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x471c40, port_u32(&port, entry->eax, 0x14c), entry->eax, entry->ebx,
                       entry->ecx);
    if (result == 1)
    {
        result = port_u32(&port, entry->eax, 0x14c);
        port_set32(&port, 0x532a4c, 0, result);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_rules_refresh(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x47e7d0, 0x5bb254, entry->edx, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_call(&port, 0x48c970, 0x5bb254, vertrix_lift_edx, entry->ebx, entry->ecx);
    port_call(&port, 0x48c860, 0x5bb254, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x47e9b0, 0x5bb254, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_import_check_4f1740(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_call_stack(&port, 0x4f1740, entry->eax, entry->edx, entry->ebx, entry->ecx, NULL, 0);
    return port_return(&port, result != 0 ? 0 : 5, entry->edx);
}

uint32_t vertrix_port_input_mode_apply(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0x5589d4, 0) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result = port_call(&port, 0x40ee60, port_u32(&port, 0x5589dc, 0) == 1 ? entry->eax : 0, 1,
                       entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_heap_reserve(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t top;
    port_call(&port, port_u32(&port, 0x507cc8, 0), entry->eax, entry->edx, entry->eax, entry->ecx);
    top = port_u32(&port, 0x509768, 0);
    port_set32(&port, 0x509768, 0, top + entry->eax);
    result = port_call(&port, 0x4e85c0, top + entry->eax, top, entry->eax, entry->ecx);
    port_call(&port, port_u32(&port, 0x507ccc, 0), result, top, entry->eax, entry->ecx);
    return port_return(&port, top, entry->edx);
}

uint32_t vertrix_port_audio_hooks_install(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0x4f6418, 0) != 0xffff)
    {
        return port_return(&port, 3, entry->edx);
    }
    port_call(&port, 0x40a890, 0x4f76d8, entry->edx, entry->ebx, entry->ecx);
    port_call(&port, 0x40a890, 0x4f76f8, vertrix_lift_edx, entry->ebx, entry->ecx);
    port_call(&port, 0x40a890, 0x4f6514, vertrix_lift_edx, entry->ebx, entry->ecx);
    port_call(&port, 0x40a890, 0x4f6468, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x40a800, 0, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_handle_flag_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t flag = entry->ebx & 0xff;
    if (flag != 0)
    {
        port_set8(&port, entry->eax, 8, flag);
        port_set32(&port, entry->eax, 0, 0);
        return port_return(&port, 0, entry->edx);
    }
    result = port_call(&port, 0x477b10, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_set8(&port, entry->eax, 8, 0);
    port_set32(&port, entry->eax, 0, result);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_view_cells_setup(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4872c0, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_set32(&port, 0x558c80, 0, result);
    port_call(&port, 0x478f50, result, 0, entry->ebx, entry->eax);
    result = port_call(&port, 0x4872c0, entry->eax, vertrix_lift_edx, entry->ebx, entry->eax);
    port_set32(&port, 0x558c88, 0, result);
    port_call(&port, 0x478f50, result, 0, entry->ebx, entry->eax);
    return port_return(&port, 1, entry->edx);
}

/* The tail jump into 0x4df2e1 (behind 0x4ec1f7): push the exit record onto the list 0x50818e
 * under the lock 0x50817e (0x4e14b0, 0x4e14b7). The jump keeps edx. */
static uint32_t exit_register_tail(Port *port, uint32_t record, const LiftEntry *entry)
{
    uint32_t result;
    port_call(port, 0x4e14b0, 0x50817e, record, entry->ebx, entry->ecx);
    port_set32(port, record, 0, port_u32(port, 0x50818e, 0));
    port_set32(port, 0x50818e, 0, record);
    result = port_call(port, 0x4e14b7, 0x50817e, record, entry->ebx, entry->ecx);
    return result;
}

uint32_t vertrix_port_exit_register_501fc0(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4ec1f7, 0x501fc0, entry->edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    return port_return(&port, exit_register_tail(&port, 0x501fd0, entry), edx);
}

uint32_t vertrix_port_exit_register_507250(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4ec1f7, 0x507250, entry->edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    return port_return(&port, exit_register_tail(&port, 0x507260, entry), edx);
}

uint32_t vertrix_port_metrics_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4de630, 0x5c7944, entry->edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    return port_return(&port, exit_register_tail(&port, 0x506c30, entry), edx);
}

uint32_t vertrix_port_key_all_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t key;
    result = entry->eax;
    for (key = 0; key < 0x100; key++)
    {
        result = port_call(&port, 0x476140, entry->eax, key, key, entry->eax);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_library_probe(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t name = 0x50fc31;
    result =
        port_call_stack(&port, 0x4f1c44, entry->eax, entry->edx, entry->ebx, entry->ecx, &name, 1);
    if (result == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_call_stack(&port, 0x4f1b78, result, vertrix_lift_edx, entry->ebx, entry->ecx, &result, 1);
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_handle_open_flag(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t edx = entry->edx;
    uint32_t flag = entry->ebx & 0xff;
    if (flag == 0)
    {
        port_call(&port, 0x477390, entry->eax, entry->edx, entry->ebx, entry->eax);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, entry->eax, 0, 1);
    port_set8(&port, entry->eax, 4, flag);
    return port_return(&port, 1, edx);
}

uint32_t vertrix_port_stream_tables_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x500fbc, 0, 0);
    port_set32(&port, 0x500fc0, 0, 0);
    port_set32(&port, 0x500fc4, 0, 0);
    port_set32(&port, 0x500fc8, 0, 0);
    port_set32(&port, 0x500fcc, 0, 0);
    port_set32(&port, 0x500fd0, 0, 0);
    port_set32(&port, 0x500ff0, 0, 0);
    port_set32(&port, 0x500ff4, 0, 0);
    port_set32(&port, 0x500ff8, 0, 0);
    port_set32(&port, 0x500ffc, 0, 0);
    port_set32(&port, 0x501000, 0, 0);
    port_set32(&port, 0x501004, 0, 0);
    result = port_call(&port, 0x4d30f0, 0x5c5c4c, 0x501038, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_stream_section_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t section = entry->eax + 0x54;
    port_set32(&port, section, (uint32_t)-0x38, 0);
    port_set32(&port, section, (uint32_t)-0x34, 0);
    port_set32(&port, section, (uint32_t)-0x2c, 0);
    port_set32(&port, section, (uint32_t)-0x28, 0);
    port_set32(&port, section, (uint32_t)-0x20, 0);
    port_set32(&port, section, 8, 0);
    result =
        port_call_stack(&port, 0x4f1970, section, entry->edx, entry->eax, entry->ecx, &section, 1);
    port_set32(&port, entry->eax, 0x24, 1);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_scene_enter(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t scene = entry->eax;
    port_call(&port, 0x4b7cd0, scene, entry->edx, entry->ebx, scene);
    port_call(&port, 0x41a930, scene, vertrix_lift_edx, entry->ebx, scene);
    port_call(&port, 0x418af0, scene, vertrix_lift_edx, entry->ebx, scene);
    port_call(&port, 0x41a940, scene, 0x41a700, entry->ebx, scene);
    port_call(&port, 0x418820, scene, vertrix_lift_edx, entry->ebx, scene);
    result = port_call(&port, 0x418840, scene, 0x41a520, entry->ebx, scene);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_text_item_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t item = port_call(&port, 0x4ca000, 0x96c, entry->eax, entry->ebx, entry->ecx);
    if (item != 0)
    {
        item = port_call(&port, 0x43e100, item, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    port_call(&port, 0x43e4d0, item, vertrix_lift_edx, entry->ebx, item);
    port_set32(&port, item, 0, 0x190);
    result = port_call(&port, 0x4b5e70, 0x546744, item, entry->ebx, item);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_key_set_select(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t key;
    if (entry->edx == port_u32(&port, 0x553648, 0))
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    port_set32(&port, 0x553648, 0, entry->edx);
    port_call(&port, 0x4759e0, 0x55364c, entry->edx, entry->ebx, entry->eax);
    for (key = 0; key < 0x100; key++)
    {
        port_call(&port, 0x475a80, entry->eax + key * 0x60, key + 1, entry->ebx, entry->eax);
    }
    return port_return(&port, 0x100, 0x100);
}

uint32_t vertrix_port_file_object_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t object = entry->eax;
    port_set32(&port, object, 0x1c, 0);
    port_set32(&port, object, 0x20, 0);
    port_set32(&port, object, 0x24, 0);
    port_set32(&port, object, 0x28, 0);
    port_set32(&port, object, 0, 0x519344);
    port_set32(&port, object, 0x28, 0x1c);
    port_set32(&port, object, 0x20, 0x14);
    port_set16(&port, object, 0x18, 0);
    port_set32(&port, object, 0x30, 1);
    port_set8(&port, object, 0x14, entry->edx & 0xff);
    return port_return(&port, object, object + 0x1c);
}

uint32_t vertrix_port_actor_square_setup_45c830(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    port_set16(&port, actor, 0x12, 8);
    port_set16(&port, actor, 0x10, port_u16(&port, actor, 0x14));
    port_set16(&port, actor, 0x18, port_u16(&port, actor, 0x1c));
    port_set16(&port, actor, 0x1a, 8);
    port_call(&port, 0x4ac7b0, actor, 2, entry->ebx, actor);
    port_call(&port, 0x4ac510, actor, 0x45c830, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_thread_record_ensure(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t record = entry->eax;
    uint32_t ebx = entry->ebx;
    if (record == 0)
    {
        record =
            port_call(&port, 0x4ec160, 1, port_u32(&port, 0x509768, 0), entry->ebx, entry->ecx);
        if (record != 0)
        {
            ebx = port_u32(&port, 0x509768, 0);
            port_set8(&port, record, 0x52, 1);
            port_set32(&port, record, 0xf0, ebx);
        }
    }
    port_call(&port, 0x4e8620, record, record, ebx, entry->ecx);
    return port_return(&port, record, entry->edx);
}

uint32_t vertrix_port_reader_dword_be(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t value;
    value = port_call(&port, 0x405ee0, entry->eax, entry->edx, entry->ebx, entry->eax) << 8;
    result = port_call(&port, 0x405ee0, entry->eax, value, entry->ebx, entry->eax);
    value = (vertrix_lift_edx | result) << 8;
    result = port_call(&port, 0x405ee0, entry->eax, value, entry->ebx, entry->eax);
    value = (vertrix_lift_edx | result) << 8;
    result = port_call(&port, 0x405ee0, entry->eax, value, entry->ebx, entry->eax);
    port_set32(&port, entry->eax, 0x3664, vertrix_lift_edx | result);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_sounds_show(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t volume;
    volume = port_u32(&port, 0x532b9c, 0);
    port_call(&port, 0x482a60, 0, port_u32(&port, 0x533164, port_u32(&port, 0x4f819c, 0) * 4),
              volume, entry->eax);
    volume = port_u32(&port, 0x532b9c, 0);
    port_call(&port, 0x482a60, 4, port_u32(&port, 0x533164, port_u32(&port, 0x4f819c, 0) * 4),
              volume, entry->eax);
    result = port_call(&port, 0x4ac8f0, entry->eax, 0, volume, entry->eax);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_scene_reload(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t scene = entry->eax;
    uint32_t setting;
    port_call(&port, 0x41a4e0, scene, entry->edx, 0, scene);
    setting = port_u8(&port, 0x513c1c, 0);
    port_call(&port, 0x41a320, scene, setting, setting, scene);
    port_call(&port, 0x41aa20, scene, vertrix_lift_edx, setting, scene);
    port_call(&port, 0x41a440, scene, setting, setting, scene);
    result = port_call(&port, 0x418820, scene, 0x41a6c0, setting, scene);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actors_take_next(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, 0x546724, 0);
    uint32_t index;
    result = count;
    for (index = 0; index < count; index++)
    {
        result =
            port_call(&port, 0x4ac920, port_u32(&port, port_u32(&port, 0x546720, 0), index * 4),
                      (index + 1) * 4, count, index + 1);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_sounds_volume_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t volume;
    uint32_t slot;
    if (port_u32(&port, 0x598d60, 0) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    volume = port_u32(&port, 0x598da8, 0) != 0 ? entry->eax : 0;
    result = entry->eax;
    for (slot = 0; slot < 8; slot++)
    {
        result = port_call(&port, 0x40ae00, port_u32(&port, 0x598d88, slot * 4), volume, volume,
                           (slot + 1) * 4);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_audio_reset(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x52f130, 0, 0);
    port_set32(&port, 0x4f6418, 0, 0xffff);
    port_call(&port, 0x4eb5c0, 0x52f0b0, 0, 0x80, entry->eax);
    port_call(&port, 0x4eb5e0, 0x52f010, 0x4f7658, 0x18, entry->eax);
    port_call(&port, 0x4eb5e0, 0x52f028, 0x4f7670, 0x68, entry->eax);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_audio_open(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4eb5c0, 0x52f0b0, 0, 0x80, entry->eax);
    result = port_call(&port, port_u32(&port, 0x52f03c, 0), entry->eax, vertrix_lift_edx, 0x80,
                       entry->eax);
    if (result == 0)
    {
        port_set32(&port, 0x52f130, 0, entry->eax);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_box_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0x74, 0x516804);
    port_set8(&port, entry->eax, 8, 0);
    port_set32(&port, entry->eax, 0xc, 0);
    port_set32(&port, entry->eax, 0x44, 0xc8);
    port_set16(&port, entry->eax, 0x3c, 0);
    port_set16(&port, entry->eax, 0x3e, 0);
    port_set16(&port, entry->eax, 0x40, 0);
    port_set16(&port, entry->eax, 0x42, 0);
    port_set16(&port, entry->eax, 0x4c, 0);
    port_set16(&port, entry->eax, 0x4e, 0);
    port_set16(&port, entry->eax, 0x48, 0);
    port_set16(&port, entry->eax, 0x4a, 0);
    port_set32(&port, entry->eax, 0x60, 0);
    port_set32(&port, entry->eax, 0x64, 0);
    port_set32(&port, entry->eax, 0x68, 0);
    port_set32(&port, entry->eax, 0x6c, 0);
    port_set32(&port, entry->eax, 0x70, 0);
    port_set32(&port, entry->eax, 0x54, 0);
    port_set32(&port, entry->eax, 0x58, 0);
    port_set16(&port, entry->eax, 0x5c, 0);
    port_set16(&port, entry->eax, 0x5e, 0);
    port_set16(&port, entry->eax, 0x50, 0);
    port_set16(&port, entry->eax, 0x52, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_lock_leave_5c8920(PORT_SIGNATURE)
{
    Port port;
    uint32_t count;
    uint32_t handle;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, 0x5c8920, 0xc);
    if (count == 0)
    {
        return port_return(&port, 0x5c8920, entry->edx);
    }
    port_set32(&port, 0x5c8920, 0xc, count - 1);
    if (count != 1)
    {
        return port_return(&port, 0x5c8920, entry->edx);
    }
    handle = port_u32(&port, 0x5c8920, 0);
    port_set32(&port, 0x5c8920, 8, 0);
    result = port_call_stack(&port, 0x4f1c40, 0x5c8920, count, 0, entry->ecx, &handle, 1);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_box_key_press(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t zero = 0;
    uint32_t x = 0x7d00;
    uint32_t y = 0x7d00;
    if (port_u32(&port, entry->eax, 0x60) == 0)
    {
        x = port_u16(&port, entry->eax, 0x48);
        y = port_u16(&port, entry->eax, 0x4a);
    }
    result = port_call_stack(&port, 0x4761d0, 0x54d640, entry->edx & 0xffff, x, y, &zero, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_box_key_release(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t zero = 0;
    uint32_t x = 0x7d00;
    uint32_t y = 0x7d00;
    if (port_u32(&port, entry->eax, 0x60) == 0)
    {
        x = port_u16(&port, entry->eax, 0x48);
        y = port_u16(&port, entry->eax, 0x4a);
    }
    result = port_call_stack(&port, 0x476280, 0x54d640, entry->edx & 0xffff, x, y, &zero, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_audio_channels_set(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t flags = port_u8(&port, 0x531b44, 0);
    if ((flags & 0x80) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    if (entry->eax > 0x40)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, 0x531b68, 0, entry->eax);
    if ((flags & 0x20) == 0)
    {
        port_set8(&port, 0x531b44, 0, flags | 0x10);
    }
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_voices_enable(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t voice;
    if (entry->eax < 1 || entry->eax > 0x20)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, 0x52fc18, 0, entry->eax);
    for (voice = 0; voice < entry->eax; voice++)
    {
        port_set8(&port, 0x52f92e, voice * 0x18, 1);
    }
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_actor_animate(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    port_call(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac5b0, actor, result, entry->ebx, actor);
    result = port_call(&port, 0x4ad6e0, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, 0x4ac8f0, actor, 0, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_rule_clear(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t offset;
    for (offset = 0; offset < 0x10; offset++)
    {
        port_set8(&port, entry->eax, offset, 0);
    }
    for (offset = 0x10; offset <= 0x30; offset += 4)
    {
        port_set32(&port, entry->eax, offset, 0);
    }
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_audio_thread_start(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t create[6] = {0, 0, 0x40aed0, 0, 0, 0x52f144};
    uint32_t arguments[2];
    uint32_t thread;
    result = port_call(&port, 0x40ae80, entry->eax, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, 0x52f14c, 0, 0);
    port_set32(&port, 0x52f148, 0, 0);
    thread = port_call_stack(&port, 0x4f1b38, result, 0, entry->ebx, entry->ecx, create, 6);
    port_set32(&port, 0x52f140, 0, thread);
    arguments[0] = thread;
    arguments[1] = 0x80;
    result = port_call_stack(&port, 0x4f1cb4, thread, 0, entry->ebx, entry->ecx, arguments, 2);
    thread = port_u32(&port, 0x52f140, 0);
    arguments[0] = thread;
    arguments[1] = 0xf;
    result = port_call_stack(&port, 0x4f1cbc, result, 0, thread, entry->ecx, arguments, 2);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_surface_create_544bf4(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t width = port_u32(&port, 0x4f90b8, 0);
    uint32_t height = port_u32(&port, 0x4f90bc, 0);
    uint32_t stack[10] = {width >> 1, height >> 1, 0, 0, width, height, 0, 0, 1, 4};
    result = port_call_stack(&port, 0x4875a0, 0x544bf4, port_u32(&port, 0x4f90b0, 0), width, height,
                             stack, 10);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_name_record_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t offset = 0;
    uint32_t value;
    port_set32(&port, entry->eax, 0x110, 0x517684);
    port_set32(&port, entry->eax, 0, 0);
    port_set32(&port, entry->eax, 4, 0);
    port_set32(&port, entry->eax, 8, 0);
    do
    {
        value = port_u8(&port, 0x510a5a, offset);
        port_set8(&port, entry->eax, 0xc + offset, value);
        offset++;
    } while (value != 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_stream_base_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0, 0x517454);
    port_set32(&port, entry->eax, 0, 0x518cb4);
    port_set32(&port, entry->eax, 4, 1);
    port_set32(&port, entry->eax, 8, 0);
    port_set32(&port, entry->eax, 0xc, 0);
    port_set32(&port, entry->eax, 0x10, 0);
    port_set32(&port, entry->eax, 0x14, 1);
    port_set32(&port, entry->eax, 0x18, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_error_object_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0, 0x517454);
    port_set32(&port, entry->eax, 0, 0x51bb54);
    port_set32(&port, entry->eax, 4, 0);
    port_set32(&port, entry->eax, 8, 0x11);
    port_set32(&port, entry->eax, 0xc, 0);
    port_set32(&port, entry->eax, 0x10, 0);
    port_set32(&port, entry->eax, 0x14, 0);
    port_set32(&port, entry->eax, 0x18, entry->edx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_view_size_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t view;
    uint32_t stack[4];
    result = port_call(&port, 0x4854a0, 0x5b9c50, entry->edx, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    view = port_u32(&port, 0x558c84, 0);
    stack[0] = 0;
    stack[1] = 0;
    stack[2] = port_u32(&port, view, 4);
    stack[3] = port_u32(&port, view, 8);
    port_call_stack(&port, 0x47ce10, port_u32(&port, 0x558c88, 0), view, 0, 0, stack, 4);
    result = port_call(&port, 0x485520, 0x5b9c50, vertrix_lift_edx, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_file_exists(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t archive = port_u32(&port, 0x5466c8, 0);
    if (archive == 0)
    {
        result = port_call(&port, 0x4895e0, entry->eax, 0, entry->ebx, 0);
        return port_return(&port, result == 1, entry->edx);
    }
    result = port_call(&port, 0x487fd0, archive, entry->eax, archive, 0);
    return port_return(&port, result != 0xffffffff, entry->edx);
}

uint32_t vertrix_port_actors_all_idle(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, 0x546774, 0);
    uint32_t index;
    for (index = 0; index < count; index++)
    {
        result =
            port_call(&port, 0x4ac900, port_u32(&port, port_u32(&port, 0x546770, 0), index * 4),
                      index, count, index * 4);
        if (result != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_static_init_55608c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x477240, 0x55608c, 0x4ec1ec, 0, 0x51670c);
    port_call(&port, 0x4ec1f7, 0x4fea9d, vertrix_lift_edx, 0, 0x51670c);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_static_init_5560bc(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x477870, 0x5560bc, 0x4ec1ec, 0, 0x51677c);
    port_call(&port, 0x4ec1f7, 0x4feac9, vertrix_lift_edx, 0, 0x51677c);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_static_init_5588f8(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4779c0, 0x5588f8, 0x4ec1ec, 0, 0x5167dc);
    port_call(&port, 0x4ec1f7, 0x4feae4, vertrix_lift_edx, 0, 0x5167dc);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_static_init_5b9c50(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x484a60, 0x5b9c50, 0x4ec1ec, 0, 0x516cec);
    port_call(&port, 0x4ec1f7, 0x4feb7c, vertrix_lift_edx, 0, 0x516cec);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_image_alpha_key(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, entry->eax, 4) * port_u32(&port, entry->eax, 8);
    uint32_t pixel = port_u32(&port, entry->eax, 0);
    uint32_t last = entry->eax;
    port_set32(&port, 0x558a4c, 0, count);
    for (; count != 0; count--)
    {
        uint32_t value = port_u32(&port, pixel, 0);
        last = pixel;
        port_set32(&port, pixel, 0, value == entry->edx ? value & 0xffffff : value | 0xff000000);
        pixel += 4;
    }
    port_set32(&port, 0x558a44, 0, pixel);
    port_set32(&port, 0x558a48, 0, 0);
    return port_return(&port, last, 0);
}

uint32_t vertrix_port_sound_stop(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t sound = entry->eax & 0xff;
    uint32_t edx = (entry->edx & 0xffffff00) | sound;
    if (port_u32(&port, 0x598d60, 0) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    if (port_u32(&port, 0x598d68, sound * 4) == 0)
    {
        return port_return(&port, sound, entry->edx);
    }
    result = port_call(&port, 0x4828a0, sound, edx, entry->ebx, sound * 4);
    edx = vertrix_lift_edx;
    if (result == 1)
    {
        port_call(&port, 0x40add0, port_u32(&port, 0x598d88, sound * 4), edx, entry->ebx,
                  sound * 4);
        edx = vertrix_lift_edx;
    }
    sound = edx & 0xff;
    port_set32(&port, 0x598d68, sound * 4, 0);
    return port_return(&port, sound, entry->edx);
}

uint32_t vertrix_port_music_rows_play(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t row = port_u16(&port, 0x5bc016, 0);
    do
    {
        uint32_t pointer;
        port_set16(&port, 0x5bc016, 0, row);
        port_call(&port, port_u32(&port, 0x5bb72c, 0), eax, edx, (ebx & 0xffff0000) | row, ecx);
        row = port_u16(&port, 0x5bc016, 0);
        pointer = port_u32(&port, 0x5bb7dc, 0);
        edx = port_u8(&port, pointer, 0) << 2;
        eax = pointer + 1;
        port_set32(&port, 0x5bb7dc, 0, eax);
        port_set32(&port, 0x5bb768, 0, port_u32(&port, 0x5bb768, 0) + 4);
        ecx = port_u32(&port, 0x5bb764, 0) + edx;
        port_set32(&port, 0x5bb764, 0, ecx);
        row = (row - 1) & 0xffff;
    } while (row != 0);
    port_set16(&port, 0x5bc016, 0, 0);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_layer_list_clear(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, entry->eax, 8);
    uint32_t index;
    result = count;
    for (index = 0; index < count; index++)
    {
        uint32_t item = port_u32(&port, port_u32(&port, entry->eax, 4), index * 4);
        uint32_t table = port_u32(&port, item, 0x158);
        result =
            port_call(&port, port_u32(&port, table, 0x18), item, index + 1, table, (index + 1) * 4);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_pool_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0, 0x517454);
    port_set32(&port, entry->eax, 0, 0x51a024);
    port_set32(&port, entry->eax, 0xc, 0);
    port_set32(&port, entry->eax, 0x10, 0);
    port_set32(&port, entry->eax, 0x14, 0);
    port_set32(&port, entry->eax, 0x18, entry->edx);
    port_set32(&port, entry->eax, 8, 0);
    port_set32(&port, entry->eax, 4, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_audio_tempo_set(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t rate;
    if (entry->eax < 0x20 || entry->eax > 0xff)
    {
        return port_return(&port, 2, entry->edx);
    }
    rate = port_u32(&port, 0x52fc20, 0);
    if (port_u8(&port, 0x52fc1d, 0) & 1)
    {
        rate += rate;
    }
    port_set32(&port, 0x52fc24, 0, rate * 5 / (entry->eax * 2));
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_level_count_matches(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t offset = entry->eax * 4;
    uint32_t index;
    uint32_t matches = 0;
    for (index = 0; index < port_u32(&port, 0x534f10, entry->eax * 4); index++)
    {
        if (entry->edx == port_u32(&port, 0x534c18, offset))
        {
            matches++;
        }
        offset += 0x4c;
    }
    return port_return(&port, matches, offset);
}

uint32_t vertrix_port_console_mode_probe(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t mode = port_u32(&port, 0x507c98, 0);
    if (mode == 0xffffffff)
    {
        mode = port_call_stack(&port, 0x4f1cd4, entry->eax, entry->edx, mode, entry->ecx, NULL, 0);
        if (port_u16(&port, 0x509731, 0) >= 0x8000 && port_u8(&port, 0x50972f, 0) < 4)
        {
            while (mode != 0xffffffff && mode <= 2)
            {
                port_set32(&port, 0x507c98, 0, mode);
                mode = port_call_stack(&port, 0x4f1cd4, mode, vertrix_lift_edx, mode, entry->ecx,
                                       NULL, 0);
            }
        }
    }
    port_set32(&port, 0x507c98, 0, mode);
    return port_return(&port, mode != 0xffffffff, entry->edx);
}

uint32_t vertrix_port_event_object_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t object;
    port_set32(&port, entry->eax, 0, 0x517454);
    object = port_call(&port, 0x4ca070, entry->eax + 0xc, entry->eax, entry->ebx, entry->ecx) - 0xc;
    port_set32(&port, object, 0, 0x519f14);
    port_set32(&port, object, 4, 0xffffffff);
    port_set32(&port, object, 8, 0);
    port_call(&port, 0x4ca180, object + 0xc, object, entry->ebx, entry->ecx);
    return port_return(&port, object, entry->edx);
}

uint32_t vertrix_port_sample_load(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t sample = entry->eax;
    uint32_t data;
    if (sample == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    data =
        port_call(&port, 0x4e7c90, port_u32(&port, sample, 8) + 4, sample, entry->ebx, entry->ecx);
    port_set32(&port, sample, 0, data);
    if (data == 0)
    {
        return port_return(&port, 8, entry->edx);
    }
    result = port_call(&port, port_u32(&port, 0x52f054, 0), sample, sample, entry->ebx, entry->ecx);
    if (result != 0)
    {
        port_call(&port, 0x4ea190, port_u32(&port, sample, 0), sample, entry->ebx, result);
        port_set32(&port, sample, 0, 0);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_static_init_5327f0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x411c70, 0x5327f0, 0x4ec1ec, 0, 0x51312c);
    port_call(&port, 0x4ec1f7, 0x4f7700, vertrix_lift_edx, 0, 0x51312c);
    port_set32(&port, 0x53291c, 0, 0);
    port_set32(&port, 0x532920, 0, 0);
    port_set32(&port, 0x532924, 0, 0);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_script_object_load(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t object = 0;
    result = port_call(&port, 0x489b40, entry->eax, 0x50de07, entry->ebx, entry->eax);
    if (result == 1)
    {
        object = port_call(&port, 0x473f10, entry->eax, vertrix_lift_edx, 0, entry->eax);
        return port_return(&port, object, entry->edx);
    }
    result = port_call(&port, 0x489b40, entry->eax, 0x50de0c, 0, entry->eax);
    if (result == 1)
    {
        object = port_call(&port, 0x48ac50, entry->eax, vertrix_lift_edx, 0, entry->eax);
    }
    return port_return(&port, object, entry->edx);
}

uint32_t vertrix_port_audio_shutdown(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t eax = entry->eax;
    uint32_t edx = 1;
    uint32_t ebx = entry->ebx;
    uint32_t sound;
    if (port_u32(&port, 0x5589d4, 0) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    if (port_u32(&port, 0x598d60, 0) == 1)
    {
        for (sound = 0; sound < 8; sound++)
        {
            port_call(&port, 0x482b40, sound, sound, (entry->ebx & 0xffffff00) | sound, entry->ecx);
            eax = port_call(&port, 0x40ad50, port_u32(&port, 0x598d88, sound * 4), sound,
                            (entry->ebx & 0xffffff00) | (sound + 1), entry->ecx);
        }
        edx = 8;
        ebx = 0;
        port_set32(&port, 0x598d60, 0, 0);
    }
    result = port_call(&port, 0x40ed70, eax, edx, ebx, entry->ecx);
    port_call(&port, 0x40aba0, result, vertrix_lift_edx, ebx, entry->ecx);
    result =
        port_call(&port, 0x40ef90, port_u32(&port, 0x5589d8, 0), vertrix_lift_edx, ebx, entry->ecx);
    port_set32(&port, 0x5589d4, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_sounds_pan_default(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t pans[8] = {0, 0x19, 0x32, 0x4b, 0xff, 0xe6, 0xcd, 0xb4};
    uint32_t slot;
    if (port_u32(&port, 0x598d60, 0) != 1)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result = entry->eax;
    for (slot = 0; slot < 8; slot++)
    {
        result = port_call(&port, 0x40ae10, port_u32(&port, 0x598d88, slot * 4), pans[slot],
                           entry->ebx, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_stream_length(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t stream = entry->eax;
    uint32_t position;
    position =
        port_call(&port, port_u32(&port, port_u32(&port, stream, 0), 0x30), stream, 0, 1, stream);
    result =
        port_call(&port, port_u32(&port, port_u32(&port, stream, 0), 0x30), stream, 0, 2, stream);
    port_call(&port, port_u32(&port, port_u32(&port, stream, 0), 0x30), stream, position, 0,
              stream);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_animate_drop(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    port_call(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result == 1)
    {
        result = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_call(&port, 0x4ac5b0, actor, result, entry->ebx, actor);
        result = port_call(&port, 0x4acc10, actor, vertrix_lift_edx, entry->ebx, actor);
        if (result == 0)
        {
            port_set16(&port, actor, 0x4a, 0xff6a);
            port_set16(&port, actor, 0x4c, 0xa);
            port_call(&port, 0x4ac8f0, actor, 0x4575b0, entry->ebx, actor);
        }
    }
    result = port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_bank_build_544a50(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t base;
    uint32_t index;
    port_call(&port, 0x487640, 0x544a50, 0x13, entry->ebx, entry->ecx);
    base = port_call(&port, 0x4877f0, 0x546538, 9, entry->ebx, 0);
    for (index = 0; index < 0x13; index++)
    {
        uint32_t image = port_call(&port, 0x4877f0, 0x544a34, index, 1, index);
        image = port_call(&port, 0x4831b0, image, base, 1, index);
        port_call(&port, 0x487850, 0x544a50, index, image, index);
        result = port_call(&port, 0x418270, 2, vertrix_lift_edx, image, index + 1);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_static_init_54d640(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x475ec0, 0x54d640, 0x4ec1ec, 0, 0x516498);
    port_call(&port, 0x4ec1f7, 0x4fd6e0, vertrix_lift_edx, 0, 0x516498);
    port_call(&port, 0x475840, 0x55364c, vertrix_lift_edx, 0, 0x516498);
    port_call(&port, 0x4ec1f7, 0x4fd6f0, vertrix_lift_edx, 0, 0x516498);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_static_init_5536c8(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4768e0, 0x5536c8, 0x4ec1ec, 0, 0x5166a8);
    port_call(&port, 0x4ec1f7, 0x4fea6d, vertrix_lift_edx, 0, 0x5166a8);
    port_call(&port, 0x4768e0, 0x553798, vertrix_lift_edx, 0, 0x5166a8);
    port_call(&port, 0x4ec1f7, 0x4fea7d, vertrix_lift_edx, 0, 0x5166a8);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_static_init_598d30(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x482480, 0x598d30, 0x4ec1ec, 0, 0x516bf8);
    port_call(&port, 0x4ec1f7, 0x4feb43, vertrix_lift_edx, 0, 0x516bf8);
    port_call(&port, 0x482480, 0x598d48, vertrix_lift_edx, 0, 0x516bf8);
    port_call(&port, 0x4ec1f7, 0x4feb53, vertrix_lift_edx, 0, 0x516bf8);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_key_layout_set(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t key = entry->eax;
    uint32_t layout;
    result = 0;
    port_set32(&port, key, 0xb4, entry->ecx);
    if ((entry->ebx & 0xff) == 0)
    {
        result = port_call(&port, 0x476aa0, key, entry->edx, entry->ebx, entry->ecx);
    }
    port_set8(&port, key, 8, entry->ebx & 0xff);
    port_set32(&port, key, 0, result);
    layout = port_u32(&port, key, 0xb4);
    if (layout == 0)
    {
        port_set32(&port, key, 0xb8, 0x78);
        port_set32(&port, key, 0xbc, 0x79);
        port_set32(&port, key, 0xc0, 0x76);
        port_set32(&port, key, 0xc4, 0x77);
        port_set32(&port, key, 0xc8, 0x7a);
    }
    else if (layout == 1)
    {
        port_set32(&port, key, 0xb8, 0x9c);
        port_set32(&port, key, 0xbc, 0x9d);
        port_set32(&port, key, 0xc0, 0x9a);
        port_set32(&port, key, 0xc4, 0x9b);
        port_set32(&port, key, 0xc8, 0x9e);
    }
    return port_return(&port, result, layout);
}

uint32_t vertrix_port_image_alpha_invert(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, entry->eax, 4) * port_u32(&port, entry->eax, 8);
    uint32_t pixel;
    if (port_u8(&port, entry->eax, 0x27) != 4)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    pixel = port_u32(&port, entry->eax, 0);
    for (; count != 0; count--)
    {
        port_set8(&port, pixel, 3, port_u8(&port, pixel, 3) != 0 ? 0 : 0xff);
        pixel += 4;
    }
    return port_return(&port, pixel, entry->edx);
}

uint32_t vertrix_port_angle_lookup(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    int32_t value = (int32_t)entry->eax;
    uint32_t magnitude;
    if (value >= 0)
    {
        if (value >= 0x10000)
        {
            return port_return(&port, 0, entry->edx);
        }
        return port_return(&port, port_u16(&port, 0x59993c, (uint32_t)value * 2), entry->edx);
    }
    magnitude = 0u - entry->eax;
    if ((int32_t)magnitude >= 0x10000)
    {
        return port_return(&port, 0xb4, entry->edx);
    }
    return port_return(&port, 0xb4 - port_u16(&port, 0x59993c, (magnitude & 0xffff) * 2),
                       entry->edx);
}

uint32_t vertrix_port_layer_lists_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t index;
    uint32_t edx = entry->edx;
    for (index = 0; index < 6; index++)
    {
        port_call(&port, 0x4b5db0, 0x54671c + index * 0x14, edx, entry->ebx, entry->ecx);
        result = port_call(&port, 0x4ec1f7, 0x4fd430 + index * 0x10, vertrix_lift_edx, entry->ebx,
                           entry->ecx);
        edx = vertrix_lift_edx;
    }
    for (index = 0; index < 4; index++)
    {
        port_set8(&port, 0x546830, index, port_u8(&port, 0x4f9c06, index));
    }
    return port_return(&port, (result & 0xffffff00) | port_u8(&port, 0x4f9c09, 0), edx);
}

uint32_t vertrix_port_name_record_reset(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t object = port_u32(&port, entry->eax, 0);
    uint32_t offset = 0;
    uint32_t value;
    result = entry->eax;
    if (object != 0)
    {
        result = port_call(&port, 0x478d80, object, entry->eax, entry->ebx, object);
    }
    port_set32(&port, entry->eax, 0, 0);
    port_set32(&port, entry->eax, 4, 0);
    port_set32(&port, entry->eax, 8, 0);
    do
    {
        value = port_u8(&port, 0x510ac1, offset);
        port_set8(&port, entry->eax, 0xc + offset, value);
        offset++;
    } while (value != 0);
    return port_return(&port, result & 0xffffff00, entry->edx);
}

uint32_t vertrix_port_memory_stream_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t stream;
    stream = port_call(&port, 0x4cb460, entry->eax, 0, 0x20, entry->eax);
    port_set32(&port, stream, 0, 0x519664);
    port_call(&port, 0x4eb5c0, stream + 0x1c, 0, 0x20, stream);
    port_set32(&port, stream, 0x1c, entry->edx);
    return port_return(&port, stream, vertrix_lift_edx);
}

uint32_t vertrix_port_voice_rate_set(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    int32_t rate = (int32_t)entry->edx;
    uint32_t mix;
    uint32_t step;
    if (entry->eax >= port_u32(&port, 0x52fc18, 0))
    {
        return port_return(&port, 1, entry->edx);
    }
    if (rate < 0x200 || rate > 0x80000)
    {
        return port_return(&port, 2, entry->edx);
    }
    mix = port_u32(&port, 0x52fc20, 0);
    step = (((uint32_t)rate << 12) + (mix >> 1)) / mix;
    port_set32(&port, 0x52f920, entry->eax * 0x18, step);
    return port_return(&port, 0, step);
}

uint32_t vertrix_port_layer_list_call(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, entry->eax, 8);
    uint32_t index;
    result = count;
    for (index = 0; index < count; index++)
    {
        uint32_t item = port_u32(&port, port_u32(&port, entry->eax, 4), index * 4);
        uint32_t table = port_u32(&port, item, 0x158);
        result = port_call_with(&port, port_u32(&port, table, 8), item, entry->edx, index + 1,
                                index * 4, entry->edx, table, 0);
    }
    return port_return(&port, result, count != 0 ? count : entry->edx);
}

uint32_t vertrix_port_sample_slot_take(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, 0x52f130, 0);
    uint32_t slot;
    if (entry->eax == 0)
    {
        port_set32(&port, 0x52f130, 0, count);
        return port_return(&port, 2, entry->edx);
    }
    for (slot = 0; slot < count; slot++)
    {
        if (port_u32(&port, 0x52f0b0, slot * 4) == 0)
        {
            port_set32(&port, 0x52f0b0, slot * 4, slot + 1);
            port_set32(&port, entry->eax, 0, slot + 1);
            port_set32(&port, 0x52f130, 0, count);
            return port_return(&port, 0, entry->edx);
        }
    }
    port_set32(&port, 0x52f130, 0, count);
    return port_return(&port, 8, entry->edx);
}

uint32_t vertrix_port_actor_respawn_wait(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t wait;
    port_call(&port, 0x45cdc0, actor, entry->edx, entry->ebx, actor);
    if (port_u32(&port, actor, 0x58) == 1)
    {
        result = port_call(&port, 0x4826c0, 0x598d30, 0x32, entry->ebx, actor);
        port_call(&port, 0x4ac490, actor, (result & 0xffff) + 0x32, entry->ebx, actor);
        result = port_call(&port, 0x4826c0, 0x598d30, 0x1388, entry->ebx, actor);
        wait = (result & 0xffff) + 0xbb8;
    }
    else
    {
        result = port_call(&port, 0x4826c0, 0x598d30, 0x1388, entry->ebx, actor);
        wait = (result & 0xffff) + 0x3e8;
    }
    port_call(&port, 0x4ac7d0, actor, wait, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, 0x45ce50, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* Move the 16.16 coordinate at +position + 2 towards the word at +position + 4 by steps times the
 * speed word at +position + 6, not past it (0x4aca60, 0x4acab0, 0x4acb00). Returns 1 while it has
 * not arrived, with the target word in the low half of vertrix_lift_edx. */
static uint32_t actor_axis_approach(Port *port, uint32_t actor, uint32_t position, uint32_t steps)
{
    int32_t step = (int32_t)steps * ((int32_t)port_u32(port, actor, position + 4) >> 16);
    int32_t current = (int32_t)port_u32(port, actor, position) >> 16;
    int32_t target = (int32_t)port_u32(port, actor, position + 2) >> 16;
    int32_t next = current;
    uint32_t stored;
    if (current > target)
    {
        next = current - step;
        if (next < target)
        {
            next = target;
        }
    }
    else if (current < target)
    {
        next = current + step;
        if (next > target)
        {
            next = target;
        }
    }
    port_set16(port, actor, position + 2, (uint32_t)next);
    stored = port_u16(port, actor, position + 4);
    vertrix_lift_edx = ((uint32_t)target & 0xffff0000u) | stored;
    return ((uint32_t)next & 0xffff) != stored;
}

uint32_t vertrix_port_actor_approach_x(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, actor_axis_approach(&port, entry->eax, 0xc, entry->edx),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_actor_approach_y(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, actor_axis_approach(&port, entry->eax, 0x14, entry->edx),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_actor_approach_z(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, actor_axis_approach(&port, entry->eax, 0x1c, entry->edx),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_scene_title_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t scene = entry->eax;
    port_call(&port, 0x41b310, scene, 0x4ec1ec, 0x514008, scene);
    port_set8(&port, scene, 0xc8, 1);
    port_call(&port, 0x418840, scene, 0x4237d0, 0x514008, scene);
    port_call(&port, 0x418820, scene, 0x41b820, 0x514008, scene);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_key_queue_next(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t zero = 0;
    uint32_t key = entry->eax;
    uint32_t next;
    port_call_stack(&port, 0x475790, key + 4, 0, 0, 0, &zero, 1);
    if (port_u32(&port, key, 0x2c) == 0)
    {
        return port_return(&port, key + 0x20, entry->edx);
    }
    next = port_call(&port, 0x4d8540, key + 0x20, vertrix_lift_edx, 0, 0);
    result = port_call(&port, 0x4757e0, key + 4, next, 0, next);
    if (next != 0)
    {
        uint32_t table = port_u32(&port, next, 0x18);
        result = port_call_with(&port, port_u32(&port, table, 0), next, 2, 0, next, table, 0, 0);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_thread_list_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t record = entry->edx;
    uint32_t node;
    uint32_t linked = 0;
    port_call(&port, port_u32(&port, 0x507cc8, 0), entry->eax, record, record, entry->ecx);
    node = port_call(&port, 0x4ec160, 1, 0x10, record, 1);
    result = node;
    if (node != 0)
    {
        result = port_call(&port, 0x4ea144, record, node, record, 1);
        if (result != 0)
        {
            result = port_call(&port, 0x4ea190, node, node, record, 1);
        }
        else
        {
            port_set32(&port, node, 8, record);
            port_set32(&port, node, 4, entry->eax);
            port_set32(&port, node, 0xc, port_u8(&port, record, 0x52));
            result = port_u32(&port, 0x5c8aa0, 0);
            port_set32(&port, 0x5c8aa0, 0, node);
            port_set32(&port, node, 0, result);
            linked = 1;
        }
    }
    port_call(&port, port_u32(&port, 0x507ccc, 0), result, node, record, linked);
    return port_return(&port, linked, vertrix_lift_edx);
}

uint32_t vertrix_port_screen_metrics_read(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t metrics = entry->eax;
    uint32_t arguments[2];
    uint32_t context;
    arguments[0] = 0xb;
    result =
        port_call_stack(&port, 0x4f19e4, metrics, entry->edx, metrics, entry->ecx, arguments, 1);
    port_set32(&port, metrics, 8, result);
    arguments[0] = 0xc;
    result =
        port_call_stack(&port, 0x4f19e4, result, entry->edx, metrics, entry->ecx, arguments, 1);
    port_set32(&port, metrics, 0xc, result);
    result = port_call(&port, port_u32(&port, metrics, 0x88) != 0 ? 0x4de5c0 : 0x4de600, result,
                       entry->edx, metrics, entry->ecx);
    arguments[0] = 0;
    context =
        port_call_stack(&port, 0x4f1974, result, entry->edx, metrics, entry->ecx, arguments, 1);
    arguments[0] = context;
    arguments[1] = 0x58;
    result =
        port_call_stack(&port, 0x4f1808, context, entry->edx, metrics, entry->ecx, arguments, 2);
    port_set32(&port, metrics, 0x18, result);
    arguments[0] = context;
    arguments[1] = 0x5a;
    result =
        port_call_stack(&port, 0x4f1808, result, entry->edx, metrics, entry->ecx, arguments, 2);
    port_set32(&port, metrics, 0x1c, result);
    arguments[0] = 0;
    arguments[1] = context;
    result =
        port_call_stack(&port, 0x4f1a78, result, entry->edx, metrics, entry->ecx, arguments, 2);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_tables_load(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4848f0, 0x50fc16, 0x598dfc, 0x5a0, 0x516cb0);
    port_call(&port, 0x4848f0, 0x50fc1e, 0x59939c, 0x5a0, 0x516cb0);
    port_call(&port, 0x4848f0, 0x50fc26, 0x59993c, 0x20000, 0x516cb0);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_text_width_chars(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t text = entry->eax;
    uint32_t count = entry->edx;
    uint32_t width = 0;
    for (;;)
    {
        if (port_call(&port, 0x4e7b50, text, width, text, count) != 0 || count == 0)
        {
            break;
        }
        if (port_u32(&port, 0x5c8950, 0) != 0 &&
            (port_u8(&port, 0x5c8961, port_u8(&port, text, 0)) & 1) != 0)
        {
            if (port_u8(&port, text, 1) == 0)
            {
                break;
            }
            width += port_call(&port, 0x4e6f30, text, width, text, count);
        }
        else
        {
            width++;
        }
        text = port_call(&port, 0x4e3a90, text, width, text, count);
        count--;
    }
    return port_return(&port, width, width);
}

uint32_t vertrix_port_player_key_pickup(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t key;
    if (port_u32(&port, 0x532b40, 0) != 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    key = port_u32(&port, 0x532b90, 0) & 0xffff;
    result = port_call(&port, 0x476480, 0x54d640, key, entry->ebx, key);
    if (result == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_call(&port, 0x4762e0, 0x54d640, key, entry->ebx, key);
    result = port_call(&port, 0x482a60, port_u8(&port, 0x532bb0, 0),
                       port_u32(&port, 0x533164, port_u32(&port, 0x4f81c4, 0) * 4),
                       port_u32(&port, 0x532b9c, 0), 1);
    port_set32(&port, 0x532b40, 0, 1);
    port_set32(&port, 0x532b48, 0, 1);
    port_set32(&port, 0x532b44, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_level_count_free(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t offset = entry->eax * 4;
    uint32_t index;
    uint32_t free = 0;
    for (index = 0; index < port_u32(&port, 0x534f10, entry->eax * 4); index++)
    {
        uint32_t kind = port_u32(&port, 0x534c18, offset);
        if (kind == 0 || kind == 3 || kind == 4 || kind == 5)
        {
            free++;
        }
        offset += 0x4c;
    }
    return port_return(&port, free, entry->edx);
}

uint32_t vertrix_port_digits_draw(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t digit;
    for (digit = 0; digit < 8; digit++)
    {
        uint32_t x = 1 + digit * 0x1f;
        uint32_t image = port_call(&port, 0x4877f0, 0x544d28, digit, x, 1);
        port_call(&port, 0x482e10, image, entry->eax, x, 1);
        result = port_call(&port, 0x483ed0, image, 0x5b9c60, x, x + 0x1f);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actors_target_idle(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, 0x546724, 0);
    uint32_t index;
    for (index = 0; index < count; index++)
    {
        uint32_t actor = port_u32(&port, port_u32(&port, 0x546720, 0), index * 4);
        uint32_t target = port_u32(&port, actor, 0x14c);
        if (target != entry->eax &&
            port_call(&port, 0x4ac900, actor, index, target, index * 4) != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_images_prepare(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t index;
    if (entry->ebx == 0)
    {
        return port_return(&port, entry->edx, 0);
    }
    for (index = 0; index < entry->ebx; index++)
    {
        uint32_t image = port_call(
            &port, 0x483400, port_u32(&port, 0x5410f8, (entry->edx + index) * 4), 1, 1, entry->ecx);
        port_set32(&port, 0x5410f8, (entry->eax + index) * 4, image);
        result = port_call(&port, 0x418270, 2, entry->ebx, index + 1, entry->ecx);
    }
    return port_return(&port, result, entry->ebx);
}

uint32_t vertrix_port_file_extension_is(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t extension = 0x5ba908;
    uint32_t offset = 0;
    uint32_t value;
    do
    {
        value = port_u8(&port, entry->eax, offset);
        port_set8(&port, 0x5ba5f8, offset, value);
        offset++;
    } while (value != 0);
    port_call_stack(&port, 0x4daae8, 0x5ba5f8, 0x5ba700, 0x5ba708, 0x5ba808, &extension, 1);
    result = port_call(&port, 0x489d00, 0x5ba908, entry->edx, 0x5ba708, 0x5ba808);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_view_rect_set_locked(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t scene;
    uint32_t stack[4];
    if (port_u32(&port, 0x558c84, 0) == 0 || port_u32(&port, 0x544070, 0) == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    result = port_call(&port, 0x4854a0, 0x5b9c50, entry->edx, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    scene = port_u32(&port, 0x544070, 0);
    stack[0] = port_u16(&port, scene, 0x214);
    stack[1] = port_u16(&port, scene, 0x216);
    stack[2] = port_u16(&port, scene, 0x218);
    stack[3] = port_u16(&port, scene, 0x21a);
    port_call_stack(&port, 0x47ce10, port_u32(&port, 0x558c84, 0), port_u32(&port, scene, 0x268), 0,
                    0, stack, 4);
    result = port_call(&port, 0x485520, 0x5b9c50, vertrix_lift_edx, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_marker_actor_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t place[5] = {0, 0, 0, 0, 0};
    uint32_t actor = port_call(&port, 0x4ca000, 0x15c, entry->edx, entry->ebx, entry->ecx);
    if (actor != 0)
    {
        actor = port_call(&port, 0x4abd70, actor, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    port_call_stack(&port, 0x4adf20, actor, 0, 0, 0, place, 5);
    port_set32(&port, actor, 0, 7);
    port_call(&port, 0x4ac7b0, actor, 1, 0, 0);
    port_call(&port, 0x4ac8f0, actor, 0x456ea0, 0, 0);
    port_call(&port, 0x4ac910, actor, 0, 0, 0);
    result = port_call(&port, 0x4b5e70, 0x54676c, actor, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_fade_ramp_build(PORT_SIGNATURE)
{
    Port port;
    uint32_t count;
    uint32_t level = 0;
    uint32_t step = 0;
    uint32_t cursor;
    port_open(&port, calls, services, globals, entry);
    count = port_u16(&port, entry->eax, 0x26);
    if (count == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    if (count == 1)
    {
        level = 0x80;
    }
    else
    {
        step = 0x100 / (count - 1);
    }
    /* The original compares addresses, so an end that wraps stops after one byte. */
    cursor = entry->eax;
    do
    {
        if (level > 0xff)
        {
            level = 0xff;
        }
        port_set8(&port, cursor, 0x130, level);
        cursor++;
        level += step;
    } while (cursor < entry->eax + count);
    return port_return(&port, cursor, entry->edx);
}

uint32_t vertrix_port_layer_list_destroy(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t list = entry->eax;
    uint32_t count = port_u32(&port, list, 8);
    uint32_t ecx = entry->ecx;
    uint32_t index;
    for (index = 0; index < count; index++)
    {
        uint32_t item = port_u32(&port, port_u32(&port, list, 4), index * 4);
        ecx = index * 4;
        if (item != 0)
        {
            uint32_t table = port_u32(&port, item, 0x158);
            port_call_with(&port, port_u32(&port, table, 0), item, 2, index, ecx, table, list, 0);
        }
        ecx += 4;
    }
    result = port_call(&port, 0x4d8770, list, 0, 0xffffffff, ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_object_list_free(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t list = entry->eax;
    uint32_t count = port_u32(&port, list, 8);
    uint32_t ecx = entry->ecx;
    uint32_t index;
    for (index = 0; index < count; index++)
    {
        uint32_t item = port_u32(&port, port_u32(&port, list, 4), index * 4);
        ecx = index * 4;
        if (item != 0)
        {
            uint32_t table = port_u32(&port, item, 0);
            port_call_with(&port, port_u32(&port, table, 4), item, 2, index, ecx, table, list, 0);
        }
        ecx += 4;
    }
    result = port_call(&port, 0x4d8770, list, 0, 0xffffffff, ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_pool_node_take(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t pool = entry->eax;
    uint32_t node;
    uint32_t next;
    if (port_u32(&port, pool, 0x10) == 0)
    {
        uint32_t stack[3];
        int32_t index;
        stack[0] = pool + 0x14;
        stack[1] = port_u32(&port, pool, 0x18);
        stack[2] = 0xc;
        node = port_call_stack(&port, 0x4e23e0, pool + 0x14, entry->edx, entry->ebx, entry->ecx,
                               stack, 3);
        index = (int32_t)port_u32(&port, pool, 0x18) - 1;
        node += 4 + (uint32_t)index * 0xc;
        for (; index >= 0; index--)
        {
            port_set32(&port, node, 0, port_u32(&port, pool, 0x10));
            port_set32(&port, pool, 0x10, node);
            node -= 0xc;
        }
    }
    node = port_u32(&port, pool, 0x10);
    next = port_u32(&port, node, 0);
    port_set32(&port, pool, 0x10, next);
    port_set32(&port, node, 4, entry->edx);
    port_set32(&port, node, 0, entry->ebx);
    port_set32(&port, pool, 0xc, port_u32(&port, pool, 0xc) + 1);
    port_set32(&port, node, 8, 0);
    return port_return(&port, node, next);
}

uint32_t vertrix_port_actor_wander_45cf30(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t mode = port_u32(&port, actor, 0xb8);
    port_call(&port, 0x45cdc0, actor, mode, entry->ebx, actor);
    result = port_call(&port, 0x4ac250, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        result = port_u32(&port, actor, 0xb8);
        if (vertrix_lift_edx == result)
        {
            return port_return(&port, result, entry->edx);
        }
        port_call(&port, 0x4adfe0, actor, vertrix_lift_edx, entry->ebx, actor);
        result = port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, 0x4adfe0, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac8a0, actor, 0x3e8, entry->ebx, actor);
    result = port_call(&port, 0x4826c0, 0x598d30, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac7d0, actor, (result & 0xffff) + 0x64, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, 0x45cf30, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_path_join(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t offset = 0;
    uint32_t end;
    uint32_t value;
    do
    {
        value = port_u8(&port, entry->edx, offset);
        port_set8(&port, entry->eax, offset, value);
        offset++;
    } while (value != 0);
    end = entry->eax + offset - 1;
    offset = 0;
    do
    {
        value = port_u8(&port, entry->ebx, offset);
        port_set8(&port, end, offset, value);
        offset++;
    } while (value != 0);
    return port_return(&port, entry->eax & 0xffffff00, entry->edx);
}

uint32_t vertrix_port_banks_setup_546618(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t base;
    uint32_t image;
    port_call(&port, 0x487640, 0x546618, 1, ebx, ecx);
    base = port_call(&port, 0x4877f0, 0x546538, 9, ebx, ecx);
    ecx = base;
    image = port_call(&port, 0x4877f0, 0x5449fc, port_u32(&port, 0x4fbfac, 0), 1, ecx);
    image = port_call(&port, 0x4831b0, image, base, 1, ecx);
    ebx = image;
    result = port_call(&port, 0x487850, 0x546618, 0, ebx, ecx);
    port_call(&port, 0x487640, 0x546634, 1, ebx, ecx);
    base = port_call(&port, 0x4877f0, 0x546538, 9, ebx, ecx);
    ecx = base;
    image = port_call(&port, 0x4877f0, 0x5449fc, port_u32(&port, 0x4fbfac, 0), 0, ecx);
    image = port_call(&port, 0x4831b0, image, base, 0, ecx);
    ebx = image;
    result = port_call(&port, 0x487850, 0x546634, 0, ebx, ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_keys_release_group(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t released[8] = {0x74, 0x75, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3};
    uint32_t index;
    for (index = 0; index < 8; index++)
    {
        port_call(&port, 0x476120, entry->eax, released[index], entry->ebx, entry->eax);
    }
    for (index = 0x70; index <= 0x73; index++)
    {
        result = port_call(&port, 0x476140, entry->eax, index, entry->ebx, entry->eax);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_bank_images_apply(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t count;
    uint32_t index;
    uint32_t edx = entry->edx;
    if (port_u32(&port, entry->eax, 0) == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    count = port_u32(&port, entry->eax, 4);
    if (count == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    for (index = 0; index < count; index++)
    {
        uint32_t image = port_u32(&port, port_u32(&port, entry->eax, 0), index * 4);
        edx = image;
        if (image != 0)
        {
            port_call_with(&port, 0x483790, image, entry->edx, index * 4, index, entry->eax,
                           entry->edx, 0);
            edx = vertrix_lift_edx;
        }
        count = port_u32(&port, entry->eax, 4);
    }
    return port_return(&port, count, edx);
}

uint32_t vertrix_port_scene_reload_513c1d(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t scene = entry->eax;
    uint32_t setting;
    port_call(&port, 0x41a4e0, scene, 0x4ec1ec, 0, scene);
    setting = port_u8(&port, 0x513c1d, 0);
    port_call(&port, 0x41a320, scene, setting, setting, scene);
    port_call(&port, 0x41aa20, scene, vertrix_lift_edx, setting, scene);
    port_call(&port, 0x41a440, scene, setting, setting, scene);
    port_call(&port, 0x418820, scene, 0x41a780, setting, scene);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_actor_animate_slide(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t frame;
    uint32_t width;
    port_call(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    frame = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac5b0, actor, 0, frame, actor);
    width = ((vertrix_lift_edx & 0xffff0000) | port_u16(&port, 0x5b9c8e, 0)) * 2;
    port_set32(&port, actor, 0x5c, (uint32_t)((int32_t)width / 3));
    port_set32(&port, actor, 0x60, 4);
    result = port_call(&port, 0x4ad6e0, actor, frame, frame, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, 0x4ac8f0, actor, 0, frame, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_sparkle_actor_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t place[5] = {0, 0, 0, 0, 0};
    uint32_t actor = port_call(&port, 0x4ca000, 0x15c, entry->edx, entry->ebx, entry->ecx);
    if (actor != 0)
    {
        actor = port_call(&port, 0x4abd70, actor, vertrix_lift_edx, entry->ebx, entry->ecx);
    }
    port_call_stack(&port, 0x4adf20, actor, 0, 0, 0, place, 5);
    port_set32(&port, actor, 0, 8);
    port_call(&port, 0x4ac7d0, actor, 0xa, 0, 0);
    port_set32(&port, actor, 0x58, 0);
    port_set32(&port, actor, 0x5c, 0x64);
    port_set32(&port, actor, 0x60, 1);
    port_call(&port, 0x4ac8f0, actor, 0x459760, 0, 0);
    port_call(&port, 0x4ac910, actor, 0, 0, 0);
    result = port_call(&port, 0x4b5e70, 0x54676c, actor, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_image_create(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t depth = entry->ebx & 0xff;
    uint32_t image;
    uint32_t pixels;
    image = port_call(&port, 0x4ec160, 1, 0x1c, entry->ebx, entry->ecx);
    pixels = port_call(&port, 0x4ec160, entry->eax * entry->edx * depth, 1, entry->ebx, image);
    port_set32(&port, image, 0, pixels);
    port_set32(&port, image, 4, entry->eax);
    port_set32(&port, image, 8, entry->edx);
    port_set8(&port, image, 0xc, depth);
    port_call(&port, 0x478cd0, image, (depth << 3) & 0xff, entry->ebx, image);
    port_set32(&port, image, 0x14, depth * entry->eax);
    port_call(&port, 0x478da0, image, vertrix_lift_edx, entry->ebx, image);
    return port_return(&port, image, vertrix_lift_edx);
}

uint32_t vertrix_port_audio_period_from(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    int32_t value = (int32_t)entry->eax;
    if (value <= 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_u8(&port, 0x531b46, 0) & 1)
    {
        uint32_t shift = (uint32_t)(value / 0x300) & 0x1f;
        int32_t period = (int32_t)port_u32(&port, 0x4f6584, (uint32_t)(value % 0x300) * 4);
        return port_return(&port, (uint32_t)(period >> shift), entry->edx);
    }
    return port_return(&port, (uint32_t)(0xda7790 / value), entry->edx);
}

uint32_t vertrix_port_actor_fade_approach(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    int32_t step = (int32_t)entry->edx * ((int32_t)port_u32(&port, entry->eax, 0x44) >> 16);
    int32_t current = (int32_t)port_u8(&port, entry->eax, 0x44);
    int32_t target = (int32_t)port_u8(&port, entry->eax, 0x45);
    int32_t next = current;
    uint32_t moving;
    if (current > target)
    {
        next = current - step;
        if (next < target)
        {
            next = target;
        }
    }
    else if (current < target)
    {
        next = current + step;
        if (next > target)
        {
            next = target;
        }
    }
    port_set8(&port, entry->eax, 0x44, (uint32_t)next);
    moving = ((uint32_t)next & 0xff) != port_u8(&port, entry->eax, 0x45);
    return port_return(&port, moving, ((uint32_t)next & 0xffffff00) | moving);
}

uint32_t vertrix_port_static_init_5bb254(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x48b550, 0x5bb254, 0x4ec1ec, 0, 0x51773c);
    port_call(&port, 0x4ec1f7, 0x4feca0, vertrix_lift_edx, 0, 0x51773c);
    port_call(&port, 0x48d330, 0x5bb4ec, vertrix_lift_edx, 0, 0x51773c);
    port_call(&port, 0x4ec1f7, 0x4fecb0, vertrix_lift_edx, 0, 0x51773c);
    port_call(&port, 0x48d330, 0x5bb524, vertrix_lift_edx, 0, 0x51773c);
    port_call(&port, 0x4ec1f7, 0x4fecc0, vertrix_lift_edx, 0, 0x51773c);
    port_call(&port, 0x48d330, 0x5bb55c, vertrix_lift_edx, 0, 0x51773c);
    port_call(&port, 0x4ec1f7, 0x4fecd0, vertrix_lift_edx, 0, 0x51773c);
    port_call(&port, 0x48d330, 0x5bb594, vertrix_lift_edx, 0, 0x51773c);
    port_call(&port, 0x4ec1f7, 0x4fece0, vertrix_lift_edx, 0, 0x51773c);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_file_buffer_new(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t size = 0x84;
    uint32_t object;
    uint32_t edx;
    object =
        port_call_stack(&port, 0x4dba80, entry->eax, entry->edx, entry->ebx, entry->ecx, &size, 1);
    edx = vertrix_lift_edx;
    if (object == 0)
    {
        return port_return(&port, 0, edx);
    }
    port_set32(&port, object, 0xc, 0);
    port_set32(&port, object, 8, 0);
    result = port_call(&port, 0x4deec0, object + 0x30, 0xa, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4deec0, result + 0x1c, 0xa, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4d8340, result + 0x1c, 0xa, entry->ebx, entry->ecx);
    object = result - 0x68;
    port_set32(&port, object, 0, 0x519364);
    port_set32(&port, object, 0xc, 0x54);
    port_set32(&port, object, 0x28, 0x4c9fe0);
    return port_return(&port, object, edx);
}

uint32_t vertrix_port_level_free_index(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t offset = entry->eax * 4;
    uint32_t index;
    uint32_t seen = 0;
    for (index = 0; index < port_u32(&port, 0x534f10, entry->eax * 4); index++)
    {
        uint32_t kind = port_u32(&port, 0x534c18, offset);
        if (kind == 0 || kind == 3 || kind == 4 || kind == 5)
        {
            if (seen == entry->edx)
            {
                return port_return(&port, index, index);
            }
            seen++;
        }
        offset += 0x4c;
    }
    return port_return(&port, 0, index);
}

uint32_t vertrix_port_game_load_all(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t steps[5] = {0x417c80, 0x425f40, 0x4b9050, 0x484550, 0x480730};
    uint32_t edx = entry->eax;
    uint32_t index;
    result = entry->eax;
    if (port_u32(&port, edx, 0xd8) == 0)
    {
        result = port_call(&port, 0x475090, result, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    result = port_call(&port, 0x418270, 0xa, edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    for (index = 0; index < 5; index++)
    {
        if (port_u32(&port, edx, 0xd8) == 0)
        {
            port_call(&port, steps[index], result, edx, entry->ebx, entry->ecx);
            edx = vertrix_lift_edx;
        }
        result = port_call(&port, 0x418270, 1, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    if (port_u32(&port, edx, 0xd8) == 0)
    {
        port_call(&port, 0x478860, result, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    result = port_call(&port, 0x418270, 1, edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4b7cd0, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4b7c00, result, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x418270, 1, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_audio_driver_info(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t info = entry->edx;
    uint32_t driver;
    uint32_t first;
    uint32_t second;
    if (info == 0)
    {
        return port_return(&port, 2, 0);
    }
    port_call(&port, 0x4eb5c0, info, 0, 0x24, info);
    if (entry->eax >= 8)
    {
        return port_return(&port, 4, vertrix_lift_edx);
    }
    driver = port_u32(&port, 0x52f090, entry->eax * 4);
    if (driver == 0)
    {
        return port_return(&port, 4, vertrix_lift_edx);
    }
    first = port_u32(&port, driver, 0);
    if (first != 0)
    {
        result =
            port_call_with(&port, port_u32(&port, first, 0), info, first, 0x24, info, first, 0, 0);
        return port_return(&port, result, vertrix_lift_edx);
    }
    second = port_u32(&port, driver, 4);
    if (second == 0)
    {
        return port_return(&port, 4, 0);
    }
    result = port_call_with(&port, port_u32(&port, second, 0), info, 0, second, info, second, 0, 0);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_actor_wander_45cdd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t speed;
    port_call(&port, 0x45cdc0, actor, port_u32(&port, actor, 0xb8), entry->ebx, actor);
    port_call(&port, 0x4adfe0, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac2b0, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        result = port_u32(&port, actor, 0xb8);
        if (vertrix_lift_edx == result)
        {
            return port_return(&port, result, entry->edx);
        }
        port_call(&port, 0x4adfe0, actor, vertrix_lift_edx, entry->ebx, actor);
        result = port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, 0x4ac710, actor, 0, entry->ebx, actor);
    speed = port_u32(&port, actor, 0x58);
    if (speed == 0)
    {
        port_call(&port, 0x4ac950, actor, 0, entry->ebx, actor);
        port_call(&port, 0x4ac8d0, actor, 0, entry->ebx, actor);
    }
    else
    {
        port_call(&port, 0x4ac8a0, actor, speed, entry->ebx, actor);
    }
    port_call(&port, 0x4adfe0, actor, 0x45cdd0, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_string_list_get(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, entry->eax, 8);
    port_call_with(&port, 0x4ca280, entry->edx, 0x5110ca, entry->ebx, entry->edx, entry->eax, count,
                   0);
    if (entry->ebx < count)
    {
        port_call_with(&port, 0x4ca310, entry->edx,
                       port_u32(&port, port_u32(&port, entry->eax, 4), entry->ebx * 4), entry->ebx,
                       entry->edx, entry->eax, count, 0);
    }
    return port_return(&port, entry->edx, vertrix_lift_edx);
}

uint32_t vertrix_port_level_offsets_534888(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t row;
    uint32_t base = 0;
    result = entry->eax;
    for (row = 0; row < 19; row++)
    {
        uint32_t index;
        result = base;
        for (index = 0; index < port_u32(&port, 0x53969c, row * 4); index++)
        {
            int32_t across =
                (int32_t)(port_u32(&port, 0x534888, row * 4) - port_u32(&port, 0x5396e8, result));
            int32_t down =
                (int32_t)(port_u32(&port, 0x5348d4, row * 4) - port_u32(&port, 0x53a8b8, result));
            if (across >= 0 && down >= 0)
            {
                port_set32(&port, 0x5372fc, result, (uint32_t)across);
                port_set32(&port, 0x5384cc, result, (uint32_t)down);
            }
            result += 4;
        }
        base += 0xf0;
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_level_offsets_540064(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t row;
    uint32_t base = 0;
    result = entry->eax;
    for (row = 0; row < 5; row++)
    {
        uint32_t index;
        result = base;
        for (index = 0; index < port_u32(&port, 0x54021c, row * 4); index++)
        {
            int32_t across =
                (int32_t)(port_u32(&port, 0x540064, row * 4) - port_u32(&port, 0x540230, result));
            int32_t down =
                (int32_t)(port_u32(&port, 0x540078, row * 4) - port_u32(&port, 0x540294, result));
            if (across >= 0 && down >= 0)
            {
                port_set32(&port, 0x540154, result, (uint32_t)across);
                port_set32(&port, 0x5401b8, result, (uint32_t)down);
            }
            result += 4;
        }
        base += 0x14;
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_scene_leave_game(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t section = 0x540020;
    uint32_t scene = entry->eax;
    port_call(&port, 0x41a4e0, scene, 0x4ec1ec, scene, 0x513fec);
    port_call(&port, 0x478d80, port_u32(&port, scene, 0xcc), vertrix_lift_edx, scene, 0x513fec);
    result =
        port_call(&port, 0x478d80, port_u32(&port, scene, 0xd0), vertrix_lift_edx, scene, 0x513fec);
    result =
        port_call_stack(&port, 0x4f1b3c, result, vertrix_lift_edx, scene, 0x513fec, &section, 1);
    port_set32(&port, scene, 0xd4, 0);
    port_call(&port, 0x4b7cd0, result, vertrix_lift_edx, scene, 0x513fec);
    port_call(&port, 0x41aa20, scene, vertrix_lift_edx, scene, 0x513fec);
    port_call(&port, 0x41aaa0, scene, vertrix_lift_edx, scene, 0x513fec);
    port_call(&port, 0x48c9f0, 0x5bb254, 0x41b680, scene, 0x513fec);
    port_call(&port, 0x418840, scene, vertrix_lift_edx, scene, 0x513fec);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_level_tables_build(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t group;
    uint32_t section;
    uint32_t level = 0;
    for (group = 0; group < 0x34; group++)
    {
        uint32_t slot = group * 8;
        uint32_t index;
        for (index = 0; index < port_u8(&port, 0x4f90c0, group); index++)
        {
            port_set8(&port, 0x53bb18, slot++, level++);
        }
    }
    level = 0;
    for (section = 0; section < 7; section++)
    {
        uint32_t count = port_u8(&port, 0x4f90f8, section);
        uint32_t total = 0;
        uint32_t index;
        for (index = 0; index < count; index++)
        {
            level++;
            total += port_u8(&port, 0x4f90bf, level);
        }
        port_set8(&port, 0x53bcc0, section, total);
    }
    return port_return(&port, level, entry->edx);
}

uint32_t vertrix_port_hud_construct(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t hud;
    result = port_call(&port, 0x4b5db0, entry->eax + 0x22c, entry->eax, 0x515010, 3);
    result = port_call(&port, 0x4b5db0, result + 0x14, 2, 0x515010, 3);
    result = port_call(&port, 0x4b5db0, result + 0x14, vertrix_lift_edx, 0x515010, 3);
    hud = result - 0x254;
    port_set32(&port, hud, 0x27c, 0x5150f4);
    return port_return(&port, hud, entry->edx);
}

uint32_t vertrix_port_hud_images_release(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t hud = entry->eax;
    uint32_t first = port_u32(&port, hud, 0x268);
    uint32_t second;
    uint32_t image;
    result = hud;
    if (first != 0)
    {
        result = port_call(&port, 0x478d80, first, hud, entry->ebx, first);
    }
    second = port_u32(&port, hud, 0x274);
    if (second != 0)
    {
        result = port_call(&port, 0x478d80, second, hud, second, first);
    }
    image = port_u32(&port, hud, 0x278);
    if (image != 0)
    {
        result = port_call(&port, 0x478d80, image, hud, second, first);
    }
    if (port_u8(&port, hud, 0x220) == 1)
    {
        image = port_u32(&port, hud, 0x270);
        if (image != 0)
        {
            result = port_call(&port, 0x478d80, image, hud, second, first);
        }
    }
    if (port_u8(&port, hud, 0x222) == 1)
    {
        result = port_u32(&port, hud, 0x26c);
        if (result != 0)
        {
            result = port_call(&port, 0x478d80, result, hud, second, first);
        }
    }
    port_set32(&port, hud, 0x268, 0);
    port_set32(&port, hud, 0x274, 0);
    port_set32(&port, hud, 0x278, 0);
    port_set32(&port, hud, 0x270, 0);
    port_set32(&port, hud, 0x26c, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_frames_busy(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t frames;
    uint32_t left;
    port_call(&port, 0x4ac370, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    result = port_call(&port, 0x4ac390, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    if (result != 1)
    {
        return port_return(&port, 1, entry->edx);
    }
    frames = port_call(&port, 0x4ac3b0, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    port_call(&port, 0x4ac420, actor, actor, frames, frames);
    actor = vertrix_lift_edx;
    for (left = frames; left != 0;)
    {
        result = port_call(&port, 0x4ac780, actor, actor, frames, left);
        actor = vertrix_lift_edx;
        if (result != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        left--;
        port_call(&port, 0x4ac740, actor, actor, frames, left);
        actor = vertrix_lift_edx;
    }
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_actor_frames_busy_4ac7a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t frames;
    uint32_t left;
    port_call(&port, 0x4ac370, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    result = port_call(&port, 0x4ac390, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    if (result != 1)
    {
        return port_return(&port, 1, entry->edx);
    }
    frames = port_call(&port, 0x4ac3b0, actor, actor, entry->ebx, entry->ecx);
    actor = vertrix_lift_edx;
    port_call(&port, 0x4ac420, actor, actor, frames, frames);
    actor = vertrix_lift_edx;
    for (left = frames; left != 0;)
    {
        result = port_call(&port, 0x4ac7a0, actor, actor, frames, left);
        actor = vertrix_lift_edx;
        if (result != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        left--;
        port_call(&port, 0x4ac750, actor, actor, frames, left);
        actor = vertrix_lift_edx;
    }
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_player_key_use(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t key = port_u16(&port, 0x532b94, 0);
    result = port_call(&port, 0x476480, 0x54d640, key, 0x514098, entry->eax);
    if (result != 0)
    {
        port_call(&port, 0x4762e0, 0x54d640, port_u16(&port, 0x532b94, 0), 0x514098, entry->eax);
        port_call(&port, 0x4192a0, entry->eax, vertrix_lift_edx, 0x514098, entry->eax);
    }
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_player_key_use_4193b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result =
        port_call(&port, 0x476480, 0x54d640, port_u16(&port, 0x532b94, 0), 0x51409c, entry->eax);
    if (result != 0)
    {
        port_call(&port, 0x4762e0, 0x54d640, port_u16(&port, 0x532b94, 0), 0x51409c, entry->eax);
        port_call(&port, 0x4193b0, entry->eax, vertrix_lift_edx, 0x51409c, entry->eax);
    }
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_tiles_draw(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t tile;
    result = entry->eax;
    for (tile = 0; tile < port_u32(&port, 0x4f90b0, 0); tile++)
    {
        uint32_t columns = port_u32(&port, 0x4f90b4, 0);
        uint32_t row = columns != 0 ? tile / columns : 0;
        uint32_t x = (port_u32(&port, 0x4f90b8, 0) + 1) * (tile - columns * row) + 1;
        uint32_t y = (port_u32(&port, 0x4f90bc, 0) + 1) * row + 1;
        uint32_t image = port_call(&port, 0x4877f0, 0x544bf4, tile, x, y);
        port_call(&port, 0x482e10, image, entry->eax, x, y);
        result = port_call(&port, 0x483ed0, image, 0x5b9c60, x, y);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_stream_types_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0x500b80, 0, 0x4cb390);
    port_set32(&port, 0x500b84, 0, 0);
    port_set32(&port, 0x500b88, 0, 0);
    port_set32(&port, 0x5c5c0c, 0, 0x4cb3a0);
    port_set32(&port, 0x5c5c10, 0, 0);
    port_set32(&port, 0x5c5c14, 0, 0);
    port_set32(&port, 0x500ba0, 0, 0x4cb3a0);
    port_set32(&port, 0x500ba4, 0, 0);
    port_set32(&port, 0x500ba8, 0, 0);
    port_set32(&port, 0x5c5c18, 0, 0x4cb3b0);
    port_set32(&port, 0x5c5c1c, 0, 0);
    port_set32(&port, 0x5c5c20, 0, 0);
    port_set32(&port, 0x500bc0, 0, 0x4cb3b0);
    port_set32(&port, 0x500be0, 0, 0);
    port_set32(&port, 0x500bc4, 0, 0);
    port_set32(&port, 0x500be4, 0, 0);
    port_set32(&port, 0x500bc8, 0, 0);
    port_set32(&port, 0x500be8, 0, 0);
    port_call(&port, 0x4d30f0, 0x5c5c24, 0x500bec, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4ec1f7, 0x500820, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_lock_record_new(PORT_SIGNATURE)
{
    Port port;
    uint32_t used;
    uint32_t record;
    uint32_t eax;
    uint32_t edx;
    uint32_t ecx = entry->ecx;
    port_open(&port, calls, services, globals, entry);
    used = port_u32(&port, 0x5c8940, 0);
    if ((int32_t)used < 0x40)
    {
        eax = used * 0x18;
        edx = used;
        record = 0x5c8310 + eax;
        port_set32(&port, 0x5c8940, 0, used + 1);
    }
    else
    {
        uint32_t list;
        record = port_call(&port, 0x4ec160, 1, 0x18, entry->ebx, entry->ecx);
        if (record == 0)
        {
            port_call(&port, 0x4e628c, 0x5129c0, 1, record, entry->ecx);
        }
        list = port_call(&port, 0x4ec0e0, port_u32(&port, 0x5c8948, 0),
                         (port_u32(&port, 0x5c8944, 0) + 1) * 4, record, entry->ecx);
        port_set32(&port, 0x5c8948, 0, list);
        if (list == 0)
        {
            port_call(&port, 0x4e628c, 0x5129e4, 1, record, entry->ecx);
        }
        eax = port_u32(&port, 0x5c8944, 0);
        edx = port_u32(&port, 0x5c8948, 0);
        ecx = eax + 1;
        port_set32(&port, edx, eax * 4, record);
        port_set32(&port, 0x5c8944, 0, ecx);
    }
    port_call_stack(&port, 0x4f1c30, eax, edx, record, ecx, &record, 1);
    return port_return(&port, record, entry->edx);
}

uint32_t vertrix_port_hud_object_construct(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t hud = port_call(&port, 0x4abd70, entry->eax, 0x4ec1ec, 0x514e30, entry->eax);
    port_set32(&port, hud, 0x158, 0x514e94);
    port_call(&port, 0x4b2290, hud + 0x15c, 0x1c2, 0x514e30, hud);
    port_call(&port, 0x4b2290, hud + 0x864, 3, 0x514e30, hud);
    port_call(&port, 0x4b2290, hud + 0x870, 1, 0x514e30, hud);
    port_set32(&port, hud, 0x968, 1);
    return port_return(&port, hud, entry->edx);
}

uint32_t vertrix_port_actor_drop_start(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    port_set8(&port, actor, 0x4e, 0);
    port_call(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result == 1)
    {
        result = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
        port_call(&port, 0x4ac5b0, actor, result, entry->ebx, actor);
        result = port_call(&port, 0x4ad6e0, actor, vertrix_lift_edx, entry->ebx, actor);
        if (result == 0)
        {
            port_set32(&port, actor, 0x58, 0);
            result = port_call(&port, 0x4826c0, 0x598d30, port_u16(&port, actor, 0x70), entry->ebx,
                               actor);
            port_set32(&port, actor, 0x5c, port_u32(&port, actor, 0x64) + (result & 0xffff));
            port_call(&port, 0x43e920, actor, port_u32(&port, actor, 0x5c), entry->ebx, actor);
            port_set8(&port, actor, 0x8e, 0);
            port_set8(&port, actor, 0x8f, 1);
            port_set8(&port, actor, 0x44, 0);
            port_set8(&port, actor, 0x45, 0x10);
            port_set16(&port, actor, 0x46, 1);
            port_set8(&port, actor, 0x4e, 0x32);
            port_set16(&port, actor, 0x48, 0);
            port_call(&port, 0x4ac8f0, actor, 0x457550, entry->ebx, actor);
        }
    }
    result = port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_file_streams_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t flags = port_u8(&port, 0x505275, 0) & 0xf8;
    uint32_t stream = 0x505234;
    uint32_t edx;
    uint32_t ecx = entry->ecx;
    port_set8(&port, 0x505275, 0, flags);
    port_set8(&port, 0x505275, 0, flags | 4);
    result = (entry->eax & 0xffff00ff) | (flags << 8);
    edx = port_u32(&port, 0x505240, 0);
    if (edx != 0)
    {
        do
        {
            uint32_t buffer = port_call(&port, 0x4e7c90, 0x1d, edx, stream, ecx);
            edx = vertrix_lift_edx;
            if (buffer == 0)
            {
                buffer = port_call(&port, 0x4e7c90, 0x1d, edx, stream, ecx);
                edx = vertrix_lift_edx;
                if (buffer == 0)
                {
                    port_call(&port, 0x4e628c, 0x512904, 1, stream, 0);
                    edx = vertrix_lift_edx;
                }
            }
            port_set32(&port, buffer, 4, stream);
            port_set32(&port, buffer, 0, port_u32(&port, 0x5c7760, 0));
            port_set32(&port, stream, 8, buffer);
            port_set32(&port, buffer, 8, 0);
            port_set8(&port, port_u32(&port, stream, 8), 0x14, 0);
            port_set32(&port, port_u32(&port, stream, 8), 0xc, 0);
            result = port_u32(&port, stream, 8);
            port_set32(&port, 0x5c7760, 0, buffer);
            ecx = port_u32(&port, stream, 0x26);
            stream += 0x1a;
        } while (ecx != 0);
    }
    port_set32(&port, 0x5c7764, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_game_object_construct(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t game = port_call(&port, 0x4ca970, entry->eax, 0, entry->eax, 0x513130);
    uint32_t section;
    port_set32(&port, game, 0, 0x5131c4);
    result = port_call(&port, 0x40af30, game, vertrix_lift_edx, game, 0x513130);
    result = port_call(&port, 0x477910, 0x5560bc, vertrix_lift_edx, game, 0x513130);
    result = port_call(&port, 0x45f3f0, result, vertrix_lift_edx, game, 0x513130);
    for (section = 0x5328c0; section <= 0x5328f0; section += 0x18)
    {
        result =
            port_call_stack(&port, 0x4f1c30, result, vertrix_lift_edx, game, 0x513130, &section, 1);
    }
    return port_return(&port, game, entry->edx);
}

uint32_t vertrix_port_voice_sample_set(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t voice;
    uint32_t data;
    uint32_t flags;
    if (entry->eax >= port_u32(&port, 0x52fc18, 0) || entry->edx == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    data = port_u32(&port, entry->edx, 4);
    if (data == 0)
    {
        return port_return(&port, 1, entry->edx);
    }
    voice = 0x52f918 + entry->eax * 0x18;
    port_set32(&port, voice, 0, data);
    port_set8(&port, voice, 0x16, 1);
    port_set32(&port, voice, 4, 0);
    flags = port_u8(&port, entry->edx, 0x16);
    if ((flags & 0x30) == 0)
    {
        port_set32(&port, voice, 0xc, port_u32(&port, entry->edx, 8));
        port_set32(&port, voice, 0x10, port_u32(&port, entry->edx, 8));
    }
    else
    {
        port_set32(&port, voice, 0xc, port_u32(&port, entry->edx, 0xc));
        port_set32(&port, voice, 0x10, port_u32(&port, entry->edx, 0x10));
        port_set8(&port, voice, 0x16, port_u8(&port, voice, 0x16) | 4);
        if (port_u8(&port, entry->edx, 0x16) & 0x20)
        {
            port_set8(&port, voice, 0x16, port_u8(&port, voice, 0x16) | 8);
        }
    }
    if (port_u8(&port, entry->edx, 0x16) & 1)
    {
        port_set32(&port, voice, 0xc, (uint32_t)((int32_t)port_u32(&port, voice, 0xc) >> 1));
        port_set32(&port, voice, 0x10, (uint32_t)((int32_t)port_u32(&port, voice, 0x10) >> 1));
        port_set8(&port, voice, 0x16, port_u8(&port, voice, 0x16) | 2);
    }
    port_set32(&port, voice, 4, port_u32(&port, voice, 4) << 12);
    port_set32(&port, voice, 0xc, port_u32(&port, voice, 0xc) << 12);
    port_set32(&port, voice, 0x10, port_u32(&port, voice, 0x10) << 12);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_actor_glide(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t frame;
    uint32_t across;
    uint32_t down;
    port_call(&port, 0x4ac7b0, actor, 1, entry->ebx, actor);
    port_call(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    frame = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac5b0, actor, vertrix_lift_edx, frame, actor);
    across = port_call(&port, 0x4aca60, actor, frame, frame, actor);
    down = port_call(&port, 0x4acab0, actor, frame, frame, actor);
    result = port_call(&port, 0x4acb00, actor, frame, frame, actor);
    if (across != 0 || down != 0 || result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, 0x4ac8f0, actor, 0, frame, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_glide_45c8b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t frame;
    uint32_t across;
    uint32_t down;
    port_call(&port, 0x4ac7b0, actor, 1, entry->ebx, actor);
    port_call(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    frame = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac5b0, actor, vertrix_lift_edx, frame, actor);
    across = port_call(&port, 0x4aca60, actor, frame, frame, actor);
    down = port_call(&port, 0x4acab0, actor, frame, frame, actor);
    result = port_call(&port, 0x4acb00, actor, frame, frame, actor);
    if (across != 0 || down != 0 || result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, 0x4ac8f0, actor, 0x45c8b0, frame, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_voice_command_apply(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t voice = entry->eax;
    uint32_t command = entry->edx;
    uint32_t edx = entry->edx;
    result = entry->eax;
    if ((port_u8(&port, command, 1) & 0x28) != 0 && port_u32(&port, command, 0x38) != 0)
    {
        result = port_call(&port, 0x40adb0, voice, port_u32(&port, command, 0x38) + 0x24, voice,
                           command);
        edx = vertrix_lift_edx;
        if (port_u8(&port, command, 1) & 0x20)
        {
            result =
                port_call(&port, 0x40ade0, voice, port_u32(&port, command, 0x74), voice, command);
            edx = vertrix_lift_edx;
        }
    }
    if (port_u8(&port, command, 1) & 0x10)
    {
        result = port_call(&port, 0x40add0, voice, edx, voice, command);
        edx = vertrix_lift_edx;
    }
    if (port_u8(&port, command, 1) & 1)
    {
        uint32_t period =
            port_call(&port, 0x40ce20, port_u32(&port, command, 0x2c), edx, voice, command);
        result = port_call(&port, 0x40adf0, voice, period, voice, command);
        edx = vertrix_lift_edx;
    }
    if (port_u8(&port, command, 1) & 2)
    {
        uint32_t volume =
            (uint32_t)((int32_t)(port_u32(&port, command, 0x18) * port_u32(&port, 0x531b68, 0)) >>
                       6);
        result = port_call(&port, 0x40ae00, voice, volume, voice, command);
        edx = vertrix_lift_edx;
    }
    if (port_u8(&port, command, 1) & 4)
    {
        result = port_call(&port, 0x40ae10, voice, port_u32(&port, command, 0x20), voice, command);
        edx = vertrix_lift_edx;
    }
    if (port_u8(&port, command, 1) & 8)
    {
        result = port_call(&port, 0x40adc0, voice, edx, voice, command);
        edx = vertrix_lift_edx;
    }
    port_set8(&port, command, 1, 0);
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_drop_actor_start(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->edx;
    uint32_t wait;
    port_set16(&port, 0x54101c, 0, port_u16(&port, 0x5b9c8e, 0));
    port_set16(&port, 0x54101e, 0, port_u16(&port, 0x5b9c90, 0));
    port_call(&port, 0x4ac8d0, actor, 0x544c64, entry->ebx, actor);
    port_call(&port, 0x4ac710, actor, 0, entry->ebx, actor);
    port_call(&port, 0x4ac8a0, actor, 5, entry->ebx, actor);
    port_call(&port, 0x4ac7b0, actor, vertrix_lift_edx, entry->ebx, actor);
    port_set16(&port, actor, 8, port_u16(&port, 0x54101c, 0));
    port_set16(&port, actor, 0xa, port_u16(&port, 0x54101e, 0));
    result = port_call(&port, 0x4826c0, 0x598d30, port_u16(&port, actor, 8), entry->ebx, actor);
    port_set16(&port, actor, 0xe, result);
    result = port_call(&port, 0x4826c0, 0x598d30, port_u16(&port, actor, 0xa), entry->ebx, actor);
    port_set16(&port, actor, 0x16, result);
    port_call(&port, 0x4ac8f0, actor, 0x4574a0, entry->ebx, actor);
    port_set32(&port, actor, 0x58, 0);
    port_set32(&port, actor, 0x60, 1);
    port_set32(&port, actor, 0x70, 0xc8);
    port_set32(&port, actor, 0x64, 0x64);
    result = port_call(&port, 0x4826c0, 0x598d30, port_u16(&port, actor, 0x70), entry->ebx, actor);
    port_set8(&port, actor, 0x93, 1);
    port_set8(&port, actor, 0x4e, 0);
    wait = result & 0xffff;
    port_set8(&port, actor, 0x44, 0);
    result = port_u32(&port, actor, 0x64) + wait;
    port_set32(&port, actor, 0x5c, result);
    return port_return(&port, result, wait);
}

uint32_t vertrix_port_actor_glide_take(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t frame;
    uint32_t across;
    uint32_t down;
    port_call(&port, 0x4ac7b0, actor, 1, entry->ebx, actor);
    port_call(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    frame = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac5b0, actor, vertrix_lift_edx, frame, actor);
    across = port_call(&port, 0x4aca60, actor, frame, frame, actor);
    down = port_call(&port, 0x4acab0, actor, frame, frame, actor);
    result = port_call(&port, 0x4acb00, actor, frame, frame, actor);
    if (across != 0 || down != 0 || result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, 0x4ac940, actor, 2, frame, actor);
    result = port_call(&port, 0x4ac7b0, actor, vertrix_lift_edx, frame, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_surface_lock(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t display = entry->eax;
    port_set32(&port, 0x5b9944, 0, 0x7c);
    for (;;)
    {
        uint32_t surface = port_u32(&port, display, 0x6c);
        uint32_t table = port_u32(&port, surface, 0);
        uint32_t lock[5] = {surface, 0, 0x5b9944, 1, 0};
        uint32_t view;
        result = port_call_stack(&port, port_u32(&port, table, 0x64), surface, table, display,
                                 entry->ecx, lock, 5);
        port_set32(&port, 0x5b9940, 0, result);
        if (result != 0x887601c2)
        {
            view = port_u32(&port, 0x558c84, 0);
            port_set32(&port, view, 0x14, port_u32(&port, 0x5b9954, 0));
            port_call(&port, 0x478da0, view, port_u32(&port, 0x5b9954, 0), display, entry->ecx);
            port_set32(&port, port_u32(&port, 0x558c84, 0), 0, port_u32(&port, 0x5b9968, 0));
            return port_return(&port, 1, entry->edx);
        }
        surface = port_u32(&port, display, 0x6c);
        table = port_u32(&port, surface, 0);
        result = port_call_stack(&port, port_u32(&port, table, 0x6c), surface, table, display,
                                 entry->ecx, &surface, 1);
        if (result != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        result = port_call(&port, 0x487080, display, table, display, entry->ecx);
        if (result == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
}

uint32_t vertrix_port_name_equals(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t first = entry->eax;
    uint32_t second = entry->edx;
    uint32_t length = 0;
    uint32_t other = 0;
    uint32_t ecx;
    while (port_u8(&port, first, length) != 0)
    {
        length++;
    }
    while (port_u8(&port, second, other) != 0)
    {
        other++;
    }
    if (other != length)
    {
        return port_return(&port, 0, entry->edx);
    }
    ecx = other;
    while (port_u8(&port, first, 0) != 0)
    {
        uint32_t left = port_call(&port, 0x4dabb0, port_u8(&port, first, 0), second, first, ecx);
        uint32_t right;
        second = vertrix_lift_edx;
        ecx = left;
        first++;
        right = port_call(&port, 0x4dabb0, port_u8(&port, second, 0), second + 1, first, ecx);
        second = vertrix_lift_edx;
        if (left != right)
        {
            break;
        }
    }
    return port_return(&port, port_u8(&port, first, 0) == 0, second);
}

uint32_t vertrix_port_static_init_5c7618(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4d30f0, 0x5c7618, 0x504e08, entry->ebx, entry->ecx);
    port_call(&port, 0x4d30f0, 0x5c7619, 0x504e20, entry->ebx, entry->ecx);
    port_call(&port, 0x4d92f0, 0x5c761c, 0, entry->ebx, entry->ecx);
    port_set32(&port, 0x5c7628, 0, 0);
    port_set32(&port, 0x5c762c, 0, 0);
    port_set32(&port, 0x5c761c, 0, 0x51a524);
    port_set32(&port, 0x5c76b0, 0, 0xf023);
    port_call(&port, 0x4ec1f7, 0x504af0, 0x504e38, entry->ebx, entry->ecx);
    port_call(&port, 0x4d30f0, 0x5c76b4, vertrix_lift_edx, entry->ebx, entry->ecx);
    port_call(&port, 0x4d92f0, 0x5c76b8, 0, entry->ebx, entry->ecx);
    port_set32(&port, 0x5c76c4, 0, 0);
    port_set32(&port, 0x5c76c8, 0, 0);
    port_set32(&port, 0x5c76b8, 0, 0x51a544);
    port_set32(&port, 0x5c774c, 0, 0xf021);
    port_call(&port, 0x4ec1f7, 0x504b00, vertrix_lift_edx, entry->ebx, entry->ecx);
    return port_return(&port, entry->chain, entry->edx);
}

uint32_t vertrix_port_box_fit_screen(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t width = port_u16(&port, 0x5b9c8e, 0);
    uint32_t height = port_u16(&port, 0x5b9c90, 0);
    uint32_t bottom = (height - 1) & 0xffff;
    port_call_stack(&port, 0x477e10, entry->eax, 0, 0, (width - 1) & 0xffff, &bottom, 1);
    result = port_call(&port, 0x478480, entry->eax, (width >> 1) & 0xffff, (height >> 1) & 0xffff,
                       (width - 1) & 0xffff);
    port_set32(&port, entry->eax, 0x64, 0);
    port_set32(&port, entry->eax, 0x68, 0);
    port_set32(&port, entry->eax, 0x6c, 0);
    port_set32(&port, entry->eax, 0x70, 0);
    return port_return(&port, result, entry->edx);
}


uint32_t vertrix_port_audio_driver_find(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t slot;
    if (entry->eax == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, entry->eax, 0, 0);
    if (port_u32(&port, 0x4f6418, 0) != 0xffff)
    {
        return port_return(&port, 3, entry->edx);
    }
    for (slot = 7; slot != 0; slot--)
    {
        uint32_t driver = port_u32(&port, 0x52f090, slot * 4);
        uint32_t table;
        if (driver == 0)
        {
            continue;
        }
        table = port_u32(&port, driver, 0);
        if (table != 0 && port_call_with(&port, port_u32(&port, table, 4), table, driver, slot * 4,
                                         slot, entry->eax, 0, 0) == 0)
        {
            port_set32(&port, entry->eax, 0, slot);
            return port_return(&port, 0, entry->edx);
        }
        table = port_u32(&port, driver, 4);
        if (table != 0 && port_call_with(&port, port_u32(&port, table, 4), table, driver, slot * 4,
                                         slot, entry->eax, 0, 0) == 0)
        {
            port_set32(&port, entry->eax, 0, slot);
            return port_return(&port, 0, entry->edx);
        }
    }
    return port_return(&port, 5, entry->edx);
}

uint32_t vertrix_port_font_glyphs_map(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    static const uint8_t characters[12] = {0x27, 0x2e, 0x26, 0x21, 0x3f, 0x2c,
                                           0x2f, 0x3b, 0x3a, 0x3c, 0x3e, 0x40};
    uint32_t glyph;
    for (glyph = 0; glyph < 12; glyph++)
    {
        result = port_call(&port, 0x48abf0, entry->eax, characters[glyph], glyph, entry->eax);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_double_to_extended(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t low = port_u32(&port, entry->eax, 0);
    uint32_t high = port_u32(&port, entry->eax, 4);
    uint32_t mantissa_low = low << 11;
    uint32_t mantissa_high = (high << 11) | (low >> 21);
    uint32_t exponent = (uint32_t)((int32_t)high >> 20);
    uint32_t field = exponent & 0x7ff;
    exponent = (exponent & 0xffff0000) | field;
    if (field == 0)
    {
        if (mantissa_high == 0 && mantissa_low == 0)
        {
            exponent = 0;
        }
        else
        {
            exponent = (exponent & 0xffff0000) | 0x3c01;
            if (mantissa_high == 0)
            {
                mantissa_high = mantissa_low;
                mantissa_low = 0;
                exponent = (exponent & 0xffff0000) | ((exponent - 0x20) & 0xffff);
            }
            while ((int32_t)mantissa_high >= 0)
            {
                mantissa_high = (mantissa_high << 1) | (mantissa_low >> 31);
                mantissa_low <<= 1;
                exponent = (exponent & 0xffff0000) | ((exponent - 1) & 0xffff);
            }
        }
    }
    else if (field == 0x7ff)
    {
        exponent = (exponent & 0xffff0000) | 0x7fff;
        if ((mantissa_high & 0x7fffffff) != 0 || mantissa_low != 0)
        {
            port_call(&port, 0x4e2371, mantissa_low, mantissa_high, entry->edx, exponent);
            mantissa_high |= 0x40000000;
        }
        mantissa_high |= 0x80000000;
    }
    else
    {
        exponent = (exponent & 0xffff0000) | ((exponent + 0x3c00) & 0xffff);
        mantissa_high |= 0x80000000;
    }
    port_set32(&port, entry->edx, 0, mantissa_low);
    port_set32(&port, entry->edx, 4, mantissa_high);
    port_set16(&port, entry->edx, 8, ((exponent >> 31) << 15) | (exponent & 0x7fff));
    return port_return(&port, mantissa_low, mantissa_high);
}
