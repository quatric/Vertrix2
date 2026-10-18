#include "runtime.h"

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
    MEASURE_GUARD = 0x514f2c,
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

/* The destructor shape 0x481b30 and its copies share: the method table `table_value` at `table`,
 * the finalizer type `type` and the guard record `guard`. */
static uint32_t object_destroy_with(PORT_SIGNATURE, uint32_t table, uint32_t table_value,
                                    uint32_t type, uint32_t guard)
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
        result = port_call(&port, OBJECT_FINALIZE, object, type, entry->ebx, object);
        port_set32(&port, ebp, -0x14u, 0);
        port_call(&port, FREE_RECORD, result, 0, entry->ebx, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, table, table_value);
    /* The guard record the original links into fs:[0] and unlinks after the free. */
    port_set32(&port, ebp, -0x20u, port.env.chain);
    port_set32(&port, ebp, -0x1cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x18u, guard);
    port_set32(&port, ebp, -0x14u, 0);
    if ((mode & DESTROY_FREE) == 0)
    {
        return port_return(&port, object, mode);
    }
    port_call(&port, FREE_OBJECT, object, mode, GUARD_HANDLER, object);
    return port_return(&port, object, vertrix_lift_edx);
}

uint32_t vertrix_port_object_destroy(PORT_SIGNATURE)
{
    return object_destroy_with(calls, services, globals, entry, OBJECT_TABLE, OBJECT_TABLE_VALUE,
                               OBJECT_TYPE, OBJECT_GUARD);
}

uint32_t vertrix_port_object_destroy_425d50(PORT_SIGNATURE)
{
    return object_destroy_with(calls, services, globals, entry, 0x1c, 0x514464, 0x514470, 0x514440);
}

uint32_t vertrix_port_object_destroy_475700(PORT_SIGNATURE)
{
    return object_destroy_with(calls, services, globals, entry, 0x18, 0x5165c4, 0x516630, 0x51649c);
}

uint32_t vertrix_port_object_destroy_482320(PORT_SIGNATURE)
{
    return object_destroy_with(calls, services, globals, entry, 0x30, 0x516b94, 0x516ba0, 0x516b40);
}

uint32_t vertrix_port_object_destroy_487890(PORT_SIGNATURE)
{
    return object_destroy_with(calls, services, globals, entry, 0xc, 0x516dc4, 0x516dd0, 0x516da0);
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

/* 0x440610's glyph setup and measure: style, size (unless a glyph) and the sum of the widths. */
static uint32_t measure_glyph(Port *port, uint32_t ebp, uint32_t glyph, uint32_t ecx, int sized)
{
    uint32_t font = (uint32_t)(int8_t)port_u8(port, ebp, -0x10u);
    if (sized)
    {
        uint32_t size = FONT_SIZES + font * FONT_SIZE;
        port_set8(port, glyph, 0x44, port_u8(port, ebp, -0xcu));
        port_set8(port, glyph, 0x8e, 0);
        port_set8(port, glyph, 0x8f, 1);
        port_set8(port, glyph, 0x91, 0);
        port_set32(port, glyph, 0xf4, port_u32(port, size, 0));
        port_set32(port, glyph, 0xf8, port_u32(port, size, 4));
    }
    else
    {
        uint32_t style = port_u8(port, ebp, -0xcu);
        port_set8(port, glyph, 0x8e, 0);
        port_set8(port, glyph, 0x8f, 1);
        port_set8(port, glyph, 0x44, style);
        port_set8(port, glyph, 0x91, 0);
    }
    return port_call(port, ACTOR_MEASURE, glyph, ebp - 0x2c, ebp - 0x28, ecx);
}

uint32_t vertrix_port_text_measure(PORT_SIGNATURE)
{
    /* push ebp, esi, edi, then 0x38 bytes: the guard record, the glyph and its size. */
    enum
    {
        BELOW = 0x44,
        ARGUMENTS = 1
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    uint32_t ebp = entry->esp - 4;
    uint32_t width = entry->ecx;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t edx;
    uint32_t ebx = 0;
    uint32_t ecx = MEASURE_GUARD;
    uint32_t glyph;
    uint32_t byte;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set8(&port, ebp, -0x10u, entry->eax);
    port_set32(&port, ebp, -0x14u, entry->edx);
    port_set8(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, ebp, -0x40u, port.env.chain);
    port_set32(&port, ebp, -0x3cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x38u, MEASURE_GUARD);
    port_set32(&port, ebp, -0x34u, 0);
    port_set32(&port, width, 0, 0);
    port_set32(&port, port_u32(&port, ebp, 8), 0, 0);
    if (port_call(&port, 0x4ccfe0, port_u32(&port, ebp, -0x14u), 0x50e12c, ebx, ecx) == 0)
    {
        /* No text: one blank glyph sizes the line. */
        edx = vertrix_lift_edx;
        glyph = port_call(&port, ALLOCATE_OBJECT, ACTOR_SIZE, edx, ebx, ecx);
        edx = vertrix_lift_edx;
        if (glyph != 0)
        {
            glyph = port_call(&port, ACTOR_CONSTRUCT, glyph, edx, ebx, ecx);
        }
        port_call_stack(&port, ACTOR_PLACE, glyph, 0, 0, 0, zeros, 5);
        ecx = 0;
        port_set32(&port, ebp, -0x20u, glyph);
        if (measure_glyph(&port, ebp, glyph, ecx, 1) != 0)
        {
            port_set32(&port, width, 0, 0);
            port_set32(&port, port_u32(&port, ebp, 8), 0, port_u32(&port, ebp, -0x28u));
        }
        edx = vertrix_lift_edx;
        glyph = port_u32(&port, ebp, -0x20u);
        if (glyph != 0)
        {
            ebx = port_u32(&port, glyph, ACTOR_TABLE);
            port_call(&port, port_u32(&port, ebx, 0), glyph, 2, ebx, ecx);
            edx = vertrix_lift_edx;
        }
        return port_return(&port, port_u32(&port, ebp, -0x40u), edx);
    }
    edx = vertrix_lift_edx;
    for (;;)
    {
        uint32_t holder;
        byte = port_u8(&port, port_u32(&port, ebp, -0x14u), 0);
        edx = (edx & 0xffffff00u) | byte;
        if (byte == 0)
        {
            break;
        }
        if (byte == ' ')
        {
            glyph = port_call(&port, ALLOCATE_OBJECT, ACTOR_SIZE, edx, ebx, ecx);
            edx = vertrix_lift_edx;
            if (glyph != 0)
            {
                port_set32(&port, ebp, -0x24u, glyph);
                port_set32(&port, ebp, -0x34u, 1);
                glyph = port_call(&port, ACTOR_CONSTRUCT, glyph, 1, ebx, 0);
                edx = vertrix_lift_edx;
                ecx = 0;
                port_set32(&port, ebp, -0x34u, 0);
            }
            port_call_stack(&port, ACTOR_PLACE, glyph, 0, 0, 0, zeros, 5);
            ebx = 0;
            ecx = 0;
            holder = ebp - 0x1c;
            port_set32(&port, holder, 0, glyph);
            if (measure_glyph(&port, ebp, glyph, ecx, 1) != 0)
            {
                uint32_t total = port_u32(&port, width, 0) + port_u32(&port, ebp, -0x2cu);
                uint32_t high = port_u32(&port, ebp, 8);
                port_set32(&port, width, 0, total);
                port_set32(&port, width, 0, total + 1);
                if (port_u32(&port, ebp, -0x28u) > port_u32(&port, high, 0))
                {
                    port_set32(&port, high, 0, port_u32(&port, ebp, -0x28u));
                }
            }
            edx = vertrix_lift_edx;
        }
        else
        {
            uint32_t source = port_call(
                &port, GLYPH_LOOKUP, (uint32_t)(int8_t)port_u8(&port, ebp, -0x10u), byte, ebx, ecx);
            edx = source;
            if (source == 0)
            {
                port_set32(&port, ebp, -0x14u, port_u32(&port, ebp, -0x14u) + 1);
                continue;
            }
            glyph = port_call(&port, ALLOCATE_OBJECT, ACTOR_SIZE, edx, ebx, ecx);
            edx = vertrix_lift_edx;
            if (glyph != 0)
            {
                port_set32(&port, ebp, -0x24u, glyph);
                port_set32(&port, ebp, -0x34u, 3);
                glyph = port_call(&port, ACTOR_CONSTRUCT, glyph, edx, 0, 3);
                edx = vertrix_lift_edx;
                ecx = 3;
                ebx = 0;
                port_set32(&port, ebp, -0x34u, 0);
            }
            zeros[2] = edx;
            port_call_stack(&port, ACTOR_PLACE, glyph, 0, 0, 0, zeros, 5);
            zeros[2] = 0;
            ebx = 0;
            ecx = 0;
            holder = ebp - 0x18;
            port_set32(&port, holder, 0, glyph);
            if (measure_glyph(&port, ebp, glyph, ecx, 0) != 0)
            {
                uint32_t total = port_u32(&port, width, 0) + port_u32(&port, ebp, -0x2cu);
                uint32_t high = port_u32(&port, ebp, 8);
                port_set32(&port, width, 0, total);
                port_set32(&port, width, 0, total + 1);
                if (port_u32(&port, ebp, -0x28u) > port_u32(&port, high, 0))
                {
                    port_set32(&port, high, 0, port_u32(&port, ebp, -0x28u));
                }
            }
            edx = vertrix_lift_edx;
        }
        glyph = port_u32(&port, holder, 0);
        if (glyph != 0)
        {
            ebx = port_u32(&port, glyph, ACTOR_TABLE);
            port_call(&port, port_u32(&port, ebx, 0), glyph, 2, ebx, ecx);
            edx = vertrix_lift_edx;
        }
        port_set32(&port, ebp, -0x34u, 0);
        port_set32(&port, ebp, -0x14u, port_u32(&port, ebp, -0x14u) + 1);
    }
    return port_return(&port, port_u32(&port, ebp, -0x40u), edx);
}

uint32_t vertrix_port_random_below(PORT_SIGNATURE)
{
    Port port;
    uint32_t table = entry->eax;
    uint32_t limit = entry->edx & 0xffff;
    uint32_t value;
    uint32_t result;
    uint32_t next;
    port_open(&port, calls, services, globals, entry);
    value = port_u16(&port, port_u32(&port, table, 8), 0);
    /* idiv by a zero limit faults in the original; the lifted copy leaves edx at 0 there. */
    result = limit != 0 ? value % limit : 0;
    port_set16(&port, table, 0xc, port_u16(&port, table, 0xc) + 1);
    next = port_u32(&port, table, 8) + 2;
    port_set32(&port, table, 8, next);
    if (port_u16(&port, table, 0xc) == 0x1001)
    {
        port_call(&port, port_u8(&port, table, 4) == 1 ? 0x482550 : 0x482540, table, result, next,
                  table);
        result = vertrix_lift_edx;
    }
    return port_return(&port, result, result);
}

uint32_t vertrix_port_animation_tick(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx = entry->eax;
    uint32_t eax;
    uint32_t count;
    uint32_t left;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4ac370, entry->eax, edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    eax = port_call(&port, 0x4ac390, edx, edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    count = port_call(&port, 0x4ac3b0, edx, edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    eax = port_call(&port, 0x4ac420, edx, edx, count, count);
    edx = vertrix_lift_edx;
    /* ebx keeps the count; ecx counts down. */
    left = count;
    while (left != 0)
    {
        port_call(&port, 0x4ac740, edx, edx, count, left);
        edx = vertrix_lift_edx;
        eax = port_call(&port, 0x4ac760, edx, edx, count, left);
        edx = vertrix_lift_edx;
        if (eax == 1)
        {
            eax = port_call(&port, 0x4ac700, edx, edx, count, left);
            edx = vertrix_lift_edx;
        }
        left--;
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_exception_destroy(PORT_SIGNATURE)
{
    /* push ecx, then 0x30 bytes holding the guard record at esp + 0x14. */
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - BELOW;
    uint32_t object = entry->eax;
    uint32_t edx = entry->edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    if ((edx & 4) != 0)
    {
        uint32_t eax;
        port_set32(&port, esp, 0x20, 1);
        port_set32(&port, esp, 0, object);
        eax = port_call(&port, 0x4ccb9f, object, 0x51a0f0, entry->ebx, object);
        port_set32(&port, esp, 0x20, 0);
        port_call(&port, 0x4ca040, eax, vertrix_lift_edx, entry->ebx, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0, 0x51a0d4);
    port_set32(&port, esp, 0x24, object);
    port_set8(&port, esp, 0x28, edx);
    port_set32(&port, esp, 0x14, port.env.chain);
    port_set32(&port, esp, 0x18, GUARD_HANDLER);
    port_set32(&port, esp, 0x1c, 0x51a058);
    port_set32(&port, esp, 0x20, 3);
    port_call(&port, 0x4ca040, port_u32(&port, object, 4), edx, entry->ebx, object);
    edx = vertrix_lift_edx;
    port_set32(&port, esp, 0x20, 0);
    port_set32(&port, object, 0, 0x517454);
    if ((edx & 2) != 0)
    {
        port_call(&port, 0x4ca050, object, edx, entry->ebx, object);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, object, edx);
}

uint32_t vertrix_port_actor_label_refresh(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, then 0x1c bytes: the guard record and a string. */
    enum
    {
        BELOW = 0x30,
        GUARD = 0x517c38
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t label;
    uint32_t x;
    uint32_t y;
    uint32_t pushed[3];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->eax);
    port_set32(&port, ebp, -0x2cu, port.env.chain);
    port_set32(&port, ebp, -0x28u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x24u, GUARD);
    port_set32(&port, ebp, -0x20u, 0);
    port_set8(&port, actor, 0x44, 0x10);
    port_call(&port, 0x4b5560, actor, GUARD_HANDLER, 0, GUARD);
    if (port_u32(&port, actor, 0x160) == 0)
    {
        return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
    }
    port_call(&port, 0x4ca070, ebp - 0x18, vertrix_lift_edx, 0, GUARD);
    port_set32(&port, ebp, -0x20u, 1);
    port_call(&port, 0x4ca370, ebp - 0x18, port_u32(&port, port_u32(&port, actor, 0x160), 0x15c), 0,
              GUARD);
    port_set8(&port, ebp, -0x14u, port_u8(&port, port_u32(&port, actor, 0x160), 0x160));
    /* The label's box: the actor's position plus the label offset (the sum then stands in both
     * registers) or plus its size less one. ecx keeps the x register for the calls below. */
    {
        uint32_t ecx;
        uint32_t near_y;
        x = port_u16(&port, actor, 0xe);
        if (port_u32(&port, actor, 0x168) == 0)
        {
            x += port_u16(&port, actor, 0x164);
            ecx = (uint32_t)(int16_t)x;
        }
        else
        {
            ecx = (uint32_t)(int16_t)x;
            x += port_u16(&port, actor, 0xf4) - 1;
        }
        y = port_u16(&port, actor, 0x16);
        if (port_u32(&port, actor, 0x16c) == 0)
        {
            y += port_u16(&port, actor, 0x166);
            near_y = y;
        }
        else
        {
            near_y = y;
            y += port_u16(&port, actor, 0xf8) - 1;
        }
        pushed[0] = (uint32_t)(int16_t)x;
        pushed[1] = (uint32_t)(int16_t)near_y;
        pushed[2] = (uint32_t)(int16_t)y;
        label = port_u32(&port, actor, 0x160);
        port_call_stack(&port, 0x4b65d0, label, port_u32(&port, ebp, -0x18u),
                        (uint32_t)(int8_t)port_u8(&port, ebp, -0x14u), ecx, pushed, 3);
        label = port_u32(&port, actor, 0x160);
        port_call(&port, port_u32(&port, port_u32(&port, label, 0x158), 4), label,
                  port_u32(&port, label, 0x158), 0, ecx);
        port_set32(&port, ebp, -0x20u, 0);
        port_call(&port, 0x4ca210, ebp - 0x18, 0, 0, ecx);
    }
    port_set32(&port, ebp, -0x20u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x2cu), entry->edx);
}

uint32_t vertrix_port_text_measure_layout(PORT_SIGNATURE)
{
    /* push ebp, esi, edi, then 0x2c bytes: the guard record and the measure and layout results. */
    enum
    {
        BELOW = 0x38,
        ARGUMENTS = 7
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    uint32_t ebp = entry->esp - 4;
    uint32_t pushed[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set8(&port, ebp, -0xcu, entry->eax);
    port_set16(&port, ebp, -0x10u, entry->ebx);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x2cu, 0x514f48);
    port_set32(&port, ebp, -0x28u, 0);
    pushed[0] = ebp - 0x1c;
    port_call_stack(&port, 0x440610, (uint32_t)(int8_t)port_u8(&port, ebp, -0xcu),
                    port_u32(&port, ebp, 0xc), port_u8(&port, ebp, 0x10), ebp - 0x20, pushed, 1);
    pushed[0] = (uint32_t)(int16_t)entry->edx;
    pushed[1] = (uint32_t)(int16_t)port_u16(&port, ebp, -0x10u);
    pushed[2] = (uint32_t)(int16_t)entry->ecx;
    pushed[3] = (uint32_t)(int16_t)port_u16(&port, ebp, 8);
    port_call_stack(&port, 0x440990, ebp - 0x18, ebp - 0x14, port_u32(&port, ebp, -0x20u),
                    port_u32(&port, ebp, -0x1cu), pushed, 4);
    port_set16(&port, port_u32(&port, ebp, 0x1c), 0, port_u32(&port, ebp, -0x18u));
    port_set16(&port, port_u32(&port, ebp, 0x20), 0, port_u32(&port, ebp, -0x14u));
    port_set32(&port, port_u32(&port, ebp, 0x14), 0, port_u32(&port, ebp, -0x20u));
    port_set32(&port, port_u32(&port, ebp, 0x18), 0, port_u32(&port, ebp, -0x1cu));
    return port_return(&port, port_u32(&port, ebp, -0x34u), port_u32(&port, ebp, 0x18));
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

/* 0x4d8650's constructor with the empty table `table`. */
static uint32_t list_create_with(PORT_SIGNATURE, uint32_t table)
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
    port_set32(&port, list, 0, table);
    port_set32(&port, list, 4, 0);
    port_set32(&port, list, 0x10, 0);
    port_set32(&port, list, 0xc, 0);
    port_set32(&port, list, 8, 0);
    return port_return(&port, list, entry->edx);
}

uint32_t vertrix_port_list_create(PORT_SIGNATURE)
{
    return list_create_with(calls, services, globals, entry, LIST_EMPTY_TABLE);
}

uint32_t vertrix_port_list_create_4e7540(PORT_SIGNATURE)
{
    return list_create_with(calls, services, globals, entry, 0x51c024);
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

/* 0x4b7610's shape: the table `table`, the element destructor `element`, the guard record `guard`
 * and the clear routine `clear`. */
static uint32_t string_list_destroy_with(PORT_SIGNATURE, uint32_t table, uint32_t element,
                                         uint32_t guard, uint32_t clear)
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
        result = port_call(&port, ARRAY_DESTROY, list, element, 1, list);
        port_set32(&port, ebp, -0x30u, 0);
        port_call(&port, ARRAY_FREE, result, vertrix_lift_edx, 1, list);
        return port_return(&port, list, vertrix_lift_edx);
    }
    port_set32(&port, list, 0, table);
    port_set32(&port, ebp, -0x28u, list);
    port_set32(&port, ebp, -0x1cu, list);
    port_set8(&port, ebp, -0x24u, 1);
    port_set8(&port, ebp, -0x18u, flags);
    port_set32(&port, ebp, -0x3cu, port.env.chain);
    port_set32(&port, ebp, -0x38u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x34u, guard);
    port_set32(&port, ebp, -0x30u, 3);
    port_call(&port, clear, list, GUARD_HANDLER, flags, list);
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

uint32_t vertrix_port_string_list_destroy(PORT_SIGNATURE)
{
    return string_list_destroy_with(calls, services, globals, entry, LIST_TABLE,
                                    STRING_LIST_DESTRUCTOR, STRING_LIST_DESTROY_GUARD,
                                    STRING_LIST_CLEAR);
}

uint32_t vertrix_port_string_list_destroy_48d530(PORT_SIGNATURE)
{
    return string_list_destroy_with(calls, services, globals, entry, 0x517a94, 0x517ab0, 0x517a50,
                                    0x48d6c0);
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

/* 0x476120's shape with the clear routine `clear`. */
static uint32_t record_clear_with(PORT_SIGNATURE, uint32_t clear)
{
    Port port;
    uint32_t index = entry->edx & 0xffff;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, clear, entry->eax + index * 0x60, index, entry->ebx, entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_record_clear(PORT_SIGNATURE)
{
    return record_clear_with(calls, services, globals, entry, CLEAR_FIRST);
}

uint32_t vertrix_port_record_clear_476010(PORT_SIGNATURE)
{
    return record_clear_with(calls, services, globals, entry, 0x4759e0);
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

/* 0x48d330's constructor with the table `table` at `field` and the base `base`. */
static uint32_t rule_set_construct_with(PORT_SIGNATURE, uint32_t field, uint32_t table,
                                        uint32_t base)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, field, table);
    port_call(&port, base, entry->eax, entry->eax, entry->ebx, entry->ecx);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_rule_set_construct(PORT_SIGNATURE)
{
    return rule_set_construct_with(calls, services, globals, entry, 0x34, 0x517a44, 0x48d480);
}

uint32_t vertrix_port_rule_set_construct_425d30(PORT_SIGNATURE)
{
    return rule_set_construct_with(calls, services, globals, entry, 0x1c, 0x514464, 0x425de0);
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

/* 0x476090's loop with the reset routine `reset`. */
static uint32_t key_records_reset_with(PORT_SIGNATURE, uint32_t reset)
{
    Port port;
    uint32_t key;
    port_open(&port, calls, services, globals, entry);
    for (key = 0; key < 0x100; key++)
    {
        port_call(&port, reset, entry->eax + key * 0x60, key + 1, entry->ebx, entry->eax);
    }
    return port_return(&port, 0x100, entry->edx);
}

uint32_t vertrix_port_key_records_reset(PORT_SIGNATURE)
{
    return key_records_reset_with(calls, services, globals, entry, 0x475a20);
}

uint32_t vertrix_port_key_records_reset_4766f0(PORT_SIGNATURE)
{
    return key_records_reset_with(calls, services, globals, entry, 0x475a80);
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

/* 0x476590's shape: `first` with edx `first_edx`, then `second` with edx `second_edx`, both on
 * the object. */
static uint32_t call_pair(PORT_SIGNATURE, uint32_t first, uint32_t first_edx, uint32_t second,
                          uint32_t second_edx)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, first, entry->eax, first_edx, entry->ebx, entry->eax);
    result = port_call(&port, second, entry->eax, second_edx, entry->ebx, entry->eax);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_key_pair_reset(PORT_SIGNATURE)
{
    return call_pair(calls, services, globals, entry, 0x476140, 0x7a, 0x476140, 0x7b);
}

uint32_t vertrix_port_board_mode_452a30(PORT_SIGNATURE)
{
    return call_pair(calls, services, globals, entry, 0x43bad0, 1, 0x452960, 0x452a50);
}

uint32_t vertrix_port_board_mode_452b00(PORT_SIGNATURE)
{
    return call_pair(calls, services, globals, entry, 0x43bad0, 2, 0x452960, 0x452b20);
}

uint32_t vertrix_port_board_mode_452bb0(PORT_SIGNATURE)
{
    return call_pair(calls, services, globals, entry, 0x43bad0, 3, 0x452960, 0x452bd0);
}

uint32_t vertrix_port_board_mode_452c60(PORT_SIGNATURE)
{
    return call_pair(calls, services, globals, entry, 0x43bad0, 4, 0x452960, 0x452c80);
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

uint32_t vertrix_port_stream_open_513e60_4182f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4cea15, entry->eax, 7, 0x513e60, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_stream_open_513e60_418550(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4cea15, entry->eax, 5, 0x513e60, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_stream_open_513e60_418570(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4cea15, entry->eax, 6, 0x513e60, entry->ecx);
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

/* 0x45d140's restart with the wander routine `wander` and the next update `next`. */
static uint32_t actor_restart_with(PORT_SIGNATURE, uint32_t wander, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, wander, actor, entry->edx, entry->ebx, actor);
    port_call(&port, 0x4ac510, actor, next, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_restart_45d160(PORT_SIGNATURE)
{
    return actor_restart_with(calls, services, globals, entry, 0x45cff0, 0x45d160);
}

uint32_t vertrix_port_actor_restart_45b150(PORT_SIGNATURE)
{
    return actor_restart_with(calls, services, globals, entry, 0x45afe0, 0x45b150);
}

/* 0x45d0c0's restart with the wander routine `wander` and the next update `next`. */
static uint32_t actor_restart_wait_with(PORT_SIGNATURE, uint32_t wander, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t wait;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, wander, actor, entry->edx, entry->ebx, actor);
    wait = port_call(&port, 0x4826c0, 0x598d30, 0x2710, entry->ebx, actor);
    port_call(&port, 0x4ac7d0, actor, (wait & 0xffff) + 0x7d0, entry->ebx, actor);
    port_call(&port, 0x4ac510, actor, next, entry->ebx, actor);
    result = port_call(&port, 0x4ac8f0, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_restart_45d100(PORT_SIGNATURE)
{
    return actor_restart_wait_with(calls, services, globals, entry, 0x45cff0, 0x45d100);
}

uint32_t vertrix_port_actor_restart_45b0f0(PORT_SIGNATURE)
{
    return actor_restart_wait_with(calls, services, globals, entry, 0x45afe0, 0x45b0f0);
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

uint32_t vertrix_port_layer_init_546780(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4b6020, 0x546780, entry->edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4b5fc0, 0x546780, vertrix_lift_edx, entry->ebx, entry->ecx);
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

uint32_t vertrix_port_bank_allocate_5130c4(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x4e628c, 0x5130c4, 0xff, entry->ebx, entry->ecx);
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

/* push edx; mov edx, eax; mov eax, `global`; call `routine`; pop edx: the shape of the copies
 * below. */
static uint32_t global_call(PORT_SIGNATURE, uint32_t routine, uint32_t global)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, routine, global, entry->eax, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_layer_add_546758(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4b6070, 0x546758);
}

uint32_t vertrix_port_layer_add_546780(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4b6070, 0x546780);
}

uint32_t vertrix_port_string_set_532be8(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x532be8);
}

uint32_t vertrix_port_string_set_532bec(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x532bec);
}

uint32_t vertrix_port_string_set_532bf0(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x532bf0);
}

uint32_t vertrix_port_string_set_532bf4(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x532bf4);
}

uint32_t vertrix_port_string_set_5332a8(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x5332a8);
}

uint32_t vertrix_port_string_set_5332ac(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x5332ac);
}

uint32_t vertrix_port_string_set_5332b0(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x5332b0);
}

uint32_t vertrix_port_string_set_5332b4(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x5332b4);
}

uint32_t vertrix_port_string_set_5332b8(PORT_SIGNATURE)
{
    return global_call(calls, services, globals, entry, 0x4ca370, 0x5332b8);
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

/* Advance every actor of the list `list` (count at list + 4) to its next update (0x4ac920). */
static uint32_t actors_take_next_in(PORT_SIGNATURE, uint32_t list)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, list + 4, 0);
    uint32_t index;
    result = count;
    for (index = 0; index < count; index++)
    {
        result = port_call(&port, 0x4ac920, port_u32(&port, port_u32(&port, list, 0), index * 4),
                           (index + 1) * 4, count, index + 1);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actors_take_next(PORT_SIGNATURE)
{
    return actors_take_next_in(calls, services, globals, entry, 0x546720);
}

uint32_t vertrix_port_actors_take_next_546748(PORT_SIGNATURE)
{
    return actors_take_next_in(calls, services, globals, entry, 0x546748);
}

uint32_t vertrix_port_actors_take_next_546734(PORT_SIGNATURE)
{
    return actors_take_next_in(calls, services, globals, entry, 0x546734);
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

/* 0x459760's frame with the step routine `step`. */
static uint32_t actor_animate_with(PORT_SIGNATURE, uint32_t step)
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
    result = port_call(&port, step, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, 0x4ac8f0, actor, 0, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_animate(PORT_SIGNATURE)
{
    return actor_animate_with(calls, services, globals, entry, 0x4ad6e0);
}

uint32_t vertrix_port_actor_animate_458450(PORT_SIGNATURE)
{
    return actor_animate_with(calls, services, globals, entry, 0x4ad580);
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

/* 1 when no actor of the list `list` (count at list + 4) is busy (0x4ac900). */
static uint32_t actors_all_idle_in(PORT_SIGNATURE, uint32_t list)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    uint32_t count = port_u32(&port, list + 4, 0);
    uint32_t index;
    for (index = 0; index < count; index++)
    {
        result = port_call(&port, 0x4ac900, port_u32(&port, port_u32(&port, list, 0), index * 4),
                           index, count, index * 4);
        if (result != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_actors_all_idle(PORT_SIGNATURE)
{
    return actors_all_idle_in(calls, services, globals, entry, 0x546770);
}

uint32_t vertrix_port_actors_all_idle_546720(PORT_SIGNATURE)
{
    return actors_all_idle_in(calls, services, globals, entry, 0x546720);
}

uint32_t vertrix_port_actors_all_idle_54675c(PORT_SIGNATURE)
{
    return actors_all_idle_in(calls, services, globals, entry, 0x54675c);
}

uint32_t vertrix_port_actors_all_idle_546748(PORT_SIGNATURE)
{
    return actors_all_idle_in(calls, services, globals, entry, 0x546748);
}

uint32_t vertrix_port_actors_all_idle_546734(PORT_SIGNATURE)
{
    return actors_all_idle_in(calls, services, globals, entry, 0x546734);
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

/* 0x492710's rows with the target pixel at `target_pixel`, `step` bytes each. */
static uint32_t music_rows_play_at(PORT_SIGNATURE, uint32_t target_pixel, uint32_t step)
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
        port_set32(&port, target_pixel, 0, port_u32(&port, target_pixel, 0) + step);
        ecx = port_u32(&port, 0x5bb764, 0) + edx;
        port_set32(&port, 0x5bb764, 0, ecx);
        row = (row - 1) & 0xffff;
    } while (row != 0);
    port_set16(&port, 0x5bc016, 0, 0);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_music_rows_play(PORT_SIGNATURE)
{
    return music_rows_play_at(calls, services, globals, entry, 0x5bb768, 4);
}

uint32_t vertrix_port_music_rows_play_49a420(PORT_SIGNATURE)
{
    return music_rows_play_at(calls, services, globals, entry, 0x5bb780, 2);
}

uint32_t vertrix_port_music_rows_play_4a24e0(PORT_SIGNATURE)
{
    return music_rows_play_at(calls, services, globals, entry, 0x5bb780, 2);
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

/* 0x4d8340's constructor with the table `table`. */
static uint32_t pool_construct_with(PORT_SIGNATURE, uint32_t table)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, entry->eax, 0, 0x517454);
    port_set32(&port, entry->eax, 0, table);
    port_set32(&port, entry->eax, 0xc, 0);
    port_set32(&port, entry->eax, 0x10, 0);
    port_set32(&port, entry->eax, 0x14, 0);
    port_set32(&port, entry->eax, 0x18, entry->edx);
    port_set32(&port, entry->eax, 8, 0);
    port_set32(&port, entry->eax, 4, 0);
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_pool_construct(PORT_SIGNATURE)
{
    return pool_construct_with(calls, services, globals, entry, 0x51a024);
}

uint32_t vertrix_port_pool_construct_4d8ab0(PORT_SIGNATURE)
{
    return pool_construct_with(calls, services, globals, entry, 0x51a1b4);
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

/* 0x457550's frame with the stepper `stepper`, the fade from `start` by `fade` and the update
 * `next` once it is done, `refresh` in every case. */
static uint32_t actor_drop_with(PORT_SIGNATURE, uint32_t stepper, uint32_t start, uint32_t fade,
                                uint32_t next, uint32_t refresh)
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
        result = port_call(&port, stepper, actor, vertrix_lift_edx, entry->ebx, actor);
        if (result == 0)
        {
            port_set16(&port, actor, 0x4a, start);
            port_set16(&port, actor, 0x4c, fade);
            port_call(&port, 0x4ac8f0, actor, next, entry->ebx, actor);
        }
    }
    result = port_call(&port, refresh, actor, vertrix_lift_edx, entry->ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_animate_drop(PORT_SIGNATURE)
{
    return actor_drop_with(calls, services, globals, entry, 0x4acc10, 0xff6a, 0xa, 0x4575b0,
                           0x4ac8a0);
}

uint32_t vertrix_port_actor_animate_drop_45a3e0(PORT_SIGNATURE)
{
    return actor_drop_with(calls, services, globals, entry, 0x4ad530, 0, 5, 0x45a440, 0x457890);
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

/* Move the 16.16 coordinate's whole word (+current_field + 2) towards the target's (+target_field +
 * 2) by steps times the speed word (+speed_field + 2), not past it (0x4aca60, 0x4acab0, 0x4acb00,
 * 0x4ad5e0, 0x4ad630). Returns 1 while it has not arrived, with the target word in the low half of
 * vertrix_lift_edx. */
static uint32_t actor_axis_approach_at(Port *port, uint32_t actor, uint32_t current_field,
                                       uint32_t target_field, uint32_t speed_field, uint32_t steps)
{
    int32_t step = (int32_t)steps * ((int32_t)port_u32(port, actor, speed_field) >> 16);
    int32_t current = (int32_t)port_u32(port, actor, current_field) >> 16;
    int32_t target = (int32_t)port_u32(port, actor, target_field) >> 16;
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
    port_set16(port, actor, current_field + 2, (uint32_t)next);
    stored = port_u16(port, actor, target_field + 2);
    vertrix_lift_edx = ((uint32_t)target & 0xffff0000u) | stored;
    return ((uint32_t)next & 0xffff) != stored;
}

/* The fields' common layout: the coordinate at +position, the target at +position + 2 and the
 * speed at +position + 4. */
static uint32_t actor_axis_approach(Port *port, uint32_t actor, uint32_t position, uint32_t steps)
{
    return actor_axis_approach_at(port, actor, position, position + 2, position + 4, steps);
}

uint32_t vertrix_port_actor_approach_x(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, actor_axis_approach(&port, entry->eax, 0xc, entry->edx),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_actor_approach_x_4ad5e0(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port,
                       actor_axis_approach_at(&port, entry->eax, 0x28, 0x2e, 0x30, entry->edx),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_actor_approach_x_4ad630(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port,
                       actor_axis_approach_at(&port, entry->eax, 0x38, 0x3e, 0x40, entry->edx),
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

/* 0x472100's actor of the kind `kind` at the rate `rate` (0x4ac7b0) with the update `next`. */
static uint32_t marker_actor_add_with(PORT_SIGNATURE, uint32_t kind, uint32_t rate, uint32_t next)
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
    port_set32(&port, actor, 0, kind);
    port_call(&port, 0x4ac7b0, actor, rate, 0, 0);
    port_call(&port, 0x4ac8f0, actor, next, 0, 0);
    port_call(&port, 0x4ac910, actor, 0, 0, 0);
    result = port_call(&port, 0x4b5e70, 0x54676c, actor, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_marker_actor_add(PORT_SIGNATURE)
{
    return marker_actor_add_with(calls, services, globals, entry, 7, 1, 0x456ea0);
}

uint32_t vertrix_port_marker_actor_add_472020(PORT_SIGNATURE)
{
    return marker_actor_add_with(calls, services, globals, entry, 2, 1, 0x456de0);
}

uint32_t vertrix_port_marker_actor_add_472090(PORT_SIGNATURE)
{
    return marker_actor_add_with(calls, services, globals, entry, 2, 1, 0x456e40);
}

uint32_t vertrix_port_marker_actor_add_4721e0(PORT_SIGNATURE)
{
    return marker_actor_add_with(calls, services, globals, entry, 3, 1, 0x456fa0);
}

uint32_t vertrix_port_marker_actor_add_472250(PORT_SIGNATURE)
{
    return marker_actor_add_with(calls, services, globals, entry, 4, 1, 0x457000);
}

uint32_t vertrix_port_marker_actor_add_4722c0(PORT_SIGNATURE)
{
    return marker_actor_add_with(calls, services, globals, entry, 5, 3, 0x457060);
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

/* 0x4724f0's actor of the kind `kind` with the counter rate `rate`, the value, goal and speed
 * (+0x58, +0x5c, +0x60) and the update `next`. */
static uint32_t sparkle_actor_add_with(PORT_SIGNATURE, uint32_t kind, uint32_t rate, uint32_t value,
                                       uint32_t goal, uint32_t speed, uint32_t next)
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
    port_set32(&port, actor, 0, kind);
    port_call(&port, 0x4ac7d0, actor, rate, 0, 0);
    port_set32(&port, actor, 0x58, value);
    port_set32(&port, actor, 0x5c, goal);
    port_set32(&port, actor, 0x60, speed);
    port_call(&port, 0x4ac8f0, actor, next, 0, 0);
    port_call(&port, 0x4ac910, actor, 0, 0, 0);
    result = port_call(&port, 0x4b5e70, 0x54676c, actor, 0, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_sparkle_actor_add(PORT_SIGNATURE)
{
    return sparkle_actor_add_with(calls, services, globals, entry, 8, 0xa, 0, 0x64, 1, 0x459760);
}

uint32_t vertrix_port_sparkle_actor_add_472470(PORT_SIGNATURE)
{
    return sparkle_actor_add_with(calls, services, globals, entry, 8, 0xf, 0, 0x64, 1, 0x459760);
}

uint32_t vertrix_port_sparkle_actor_add_472570(PORT_SIGNATURE)
{
    return sparkle_actor_add_with(calls, services, globals, entry, 9, 0xa, 0x1df, 0, 4, 0x4597a0);
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

/* 0x4acc10's fade for the level bytes `shift` bytes on. */
static uint32_t actor_fade_approach_with(PORT_SIGNATURE, uint32_t shift)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax + shift;
    int32_t step = (int32_t)entry->edx * ((int32_t)port_u32(&port, actor, 0x44) >> 16);
    int32_t current = (int32_t)port_u8(&port, actor, 0x44);
    int32_t target = (int32_t)port_u8(&port, actor, 0x45);
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
    port_set8(&port, actor, 0x44, (uint32_t)next);
    moving = ((uint32_t)next & 0xff) != port_u8(&port, actor, 0x45);
    return port_return(&port, moving, ((uint32_t)next & 0xffffff00) | moving);
}

uint32_t vertrix_port_actor_fade_approach(PORT_SIGNATURE)
{
    return actor_fade_approach_with(calls, services, globals, entry, 0);
}

uint32_t vertrix_port_actor_fade_approach_4ad580(PORT_SIGNATURE)
{
    return actor_fade_approach_with(calls, services, globals, entry, 0xa);
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

/* Map the twelve punctuation characters ' . & ! ? , / ; : < > @ of a font to the glyphs from
 * `first` on (0x48abf0), as the font setups 0x43f480 to 0x43fb70 do. */
static uint32_t font_punctuation_map(Port *port, uint32_t font, uint32_t first)
{
    static const uint8_t characters[12] = {0x27, 0x2e, 0x26, 0x21, 0x3f, 0x2c,
                                           0x2f, 0x3b, 0x3a, 0x3c, 0x3e, 0x40};
    uint32_t result = 0;
    uint32_t glyph;
    for (glyph = 0; glyph < 12; glyph++)
    {
        result = port_call(port, 0x48abf0, font, characters[glyph], first + glyph, font);
    }
    return result;
}

uint32_t vertrix_port_font_glyphs_map(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0x0), entry->edx);
}

uint32_t vertrix_port_font_glyphs_map_d6(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0xd6), entry->edx);
}

uint32_t vertrix_port_font_glyphs_map_5e(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0x5e), entry->edx);
}

uint32_t vertrix_port_font_glyphs_map_e6(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0xe6), entry->edx);
}

uint32_t vertrix_port_font_glyphs_map_116(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0x116), entry->edx);
}

uint32_t vertrix_port_font_glyphs_map_146(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0x146), entry->edx);
}

uint32_t vertrix_port_font_glyphs_map_176(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0x176), entry->edx);
}

uint32_t vertrix_port_font_glyphs_map_1a6(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0x1a6), entry->edx);
}

uint32_t vertrix_port_font_glyphs_map_1d6(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, font_punctuation_map(&port, entry->eax, 0x1d6), entry->edx);
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

uint32_t vertrix_port_player_entry_init(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t target = entry->eax;
    uint32_t source = entry->edx;
    uint32_t value;
    do
    {
        value = port_u8(&port, source++, 0);
        port_set8(&port, target++, 0, value);
    } while (value != 0);
    target = entry->eax + 0x104;
    source = entry->arguments[3];
    do
    {
        value = port_u8(&port, source++, 0);
        port_set8(&port, target++, 0, value);
    } while (value != 0);
    port_set32(&port, entry->eax, 0x208, 0);
    port_set32(&port, entry->eax, 0x20c, 0);
    port_set8(&port, entry->eax, 0x220, entry->ebx);
    port_set8(&port, entry->eax, 0x221, entry->ecx);
    port_set32(&port, entry->eax, 0x268, 0);
    port_set32(&port, entry->eax, 0x26c, 0);
    port_set32(&port, entry->eax, 0x270, 0);
    port_set32(&port, entry->eax, 0x274, 0);
    port_set32(&port, entry->eax, 0x278, 0);
    port_set8(&port, entry->eax, 0x222, entry->arguments[0]);
    port_set8(&port, entry->eax, 0x223, entry->arguments[1]);
    port_set8(&port, entry->eax, 0x224, entry->arguments[2]);
    return port_return(&port, entry->eax & 0xffffff00,
                       (entry->eax & 0xffffff00) | (entry->arguments[2] & 0xff));
}

uint32_t vertrix_port_static_init_50c08c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t records[3] = {0x50c08c, 0x50c0ac, 0x50c0cc};
    static const uint32_t handlers[3] = {0x4ee7f0, 0x4ee800, 0x4ee810};
    uint32_t index;
    for (index = 0; index < 3; index++)
    {
        port_set32(&port, records[index], 0, handlers[index]);
        port_set32(&port, records[index], 4, 0);
        port_set32(&port, records[index], 8, 0);
    }
    port_set32(&port, 0x50c0ec, 0, 0);
    port_set32(&port, 0x50c0f0, 0, 0);
    port_set32(&port, 0x50c0f4, 0, 0);
    return port_return(
        &port, port_call(&port, 0x4d30f0, 0x5c8b00, 0x50c0f8, entry->ebx, entry->ecx), entry->edx);
}

uint32_t vertrix_port_image_alpha_from_mask(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t mask =
        port_call_with(&port, 0x4816f0, entry->edx, 0, port_u32(&port, 0x558a28, 0),
                       port_u32(&port, 0x558a24, 0), port_u32(&port, 0x558a20, 0), entry->eax, 0);
    uint32_t count;
    uint32_t pixel;
    uint32_t value;
    uint32_t source;
    if (mask == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    count = port_u32(&port, entry->eax, 4) * port_u32(&port, entry->eax, 8);
    source = port_u32(&port, mask, 0);
    pixel = port_u32(&port, entry->eax, 0);
    value = count;
    port_set32(&port, 0x558a20, 0, source);
    port_set32(&port, 0x558a2c, 0, count);
    port_set32(&port, 0x558a28, 0, count);
    port_set32(&port, 0x558a24, 0, pixel);
    for (; count != 0; count--)
    {
        value = port_u32(&port, pixel, 0);
        value = port_u8(&port, source, 0) != 0 ? value | 0xff000000 : value & 0xffffff;
        port_set32(&port, pixel, 0, value);
        pixel += 4;
        source++;
        port_set32(&port, 0x558a24, 0, pixel);
        port_set32(&port, 0x558a20, 0, source);
        port_set32(&port, 0x558a28, 0, count - 1);
    }
    value = port_call_with(&port, 0x478d80, mask, value, 0, pixel, source, entry->eax, 0);
    return port_return(&port, value, vertrix_lift_edx);
}

uint32_t vertrix_port_mix_buffer_feed(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t samples = entry->eax;
    uint32_t remaining = entry->edx;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    while (remaining != 0)
    {
        uint32_t piece = remaining;
        uint32_t channel;
        if (port_u32(&port, 0x52fc30, 0) != 0)
        {
            uint32_t space = port_u32(&port, 0x52fc24, 0) - port_u32(&port, 0x52fc28, 0) + 0x40;
            uint32_t position;
            uint32_t size;
            piece = (space & 0xffffff00) | (space & 0xc0);
            if (piece > remaining)
            {
                piece = remaining;
            }
            position = port_u32(&port, 0x52fc28, 0) + piece;
            port_set32(&port, 0x52fc28, 0, position);
            size = port_u32(&port, 0x52fc24, 0);
            if ((int32_t)position >= (int32_t)size)
            {
                eax = position - size;
                port_set32(&port, 0x52fc28, 0, eax);
                eax = port_call_with(&port, port_u32(&port, 0x52fc30, 0), eax, edx, position,
                                     remaining, size, piece, 0);
                edx = vertrix_lift_edx;
            }
        }
        for (channel = 0; channel < port_u32(&port, 0x52fc18, 0); channel++)
        {
            uint32_t record = 0x52f918 + channel * 0x18;
            eax =
                port_call_with(&port, 0x40c460, samples, piece, record, record, channel, piece, 0);
            edx = vertrix_lift_edx;
        }
        samples += piece * 4;
        remaining -= piece;
    }
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_voice_note_reset(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t voice = entry->eax;
    uint32_t instrument;
    uint32_t depth;
    uint32_t speed;
    if ((port_u8(&port, voice, 0x3c) & 4) == 0)
    {
        port_set32(&port, voice, 0x40, 0);
    }
    if ((port_u8(&port, voice, 0x3c) & 0x40) == 0)
    {
        port_set32(&port, voice, 0x4c, 0);
    }
    port_set8(&port, voice, 0x70, 0);
    port_set8(&port, voice, 0x73, 0);
    port_set8(&port, voice, 0x72, 0);
    instrument = port_u32(&port, voice, 0x34);
    if (instrument != 0 && (port_u8(&port, instrument, 0xbc) & 1))
    {
        port_set32(&port, voice, 0x80, 0xffffffff);
        port_set32(&port, voice, 0x88, 0);
    }
    if (instrument != 0 && (port_u8(&port, instrument, 0xf4) & 1))
    {
        port_set32(&port, voice, 0x90, 0xffffffff);
        port_set32(&port, voice, 0x98, 0);
    }
    if (instrument != 0)
    {
        port_set32(&port, voice, 0x7c, port_u16(&port, instrument, 0x86));
    }
    port_set32(&port, voice, 0x78, 0x7fff);
    if (instrument == 0 || port_u8(&port, instrument, 0x84) == 0)
    {
        return port_return(&port, instrument, entry->edx);
    }
    port_set32(&port, voice, 0xa0, 0);
    depth = port_u8(&port, instrument, 0x84) << 8;
    speed = port_u8(&port, instrument, 0x83);
    if (speed == 0)
    {
        port_set32(&port, voice, 0xa8, 0);
        port_set32(&port, voice, 0xa4, depth);
        return port_return(&port, depth, entry->edx);
    }
    port_set32(&port, voice, 0xa8, depth / speed);
    port_set32(&port, voice, 0xa4, 0);
    return port_return(&port, depth / speed, entry->edx);
}

uint32_t vertrix_port_display_restore(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t display = entry->eax;
    port_set32(&port, 0x5b9b4c, 0, 0x7c);
    for (;;)
    {
        uint32_t surface = port_u32(&port, display, 0x68);
        uint32_t table = port_u32(&port, surface, 0);
        uint32_t flip[5] = {surface, 0, 0x5b9b4c, 1, 0};
        uint32_t result = port_call_stack(&port, port_u32(&port, table, 0x64), surface, table,
                                          display, entry->ecx, flip, 5);
        port_set32(&port, 0x5b9b48, 0, result);
        if (result == 0x887601c2)
        {
            uint32_t front = port_u32(&port, display, 0x64);
            table = port_u32(&port, front, 0);
            if (port_call_stack(&port, port_u32(&port, table, 0x6c), front, table, display,
                                entry->ecx, &front, 1) != 0)
            {
                return port_return(&port, 0, entry->edx);
            }
            result = port_call(&port, 0x487080, display, vertrix_lift_edx, display, entry->ecx);
            if (result == 0)
            {
                return port_return(&port, 0, entry->edx);
            }
        }
        else if (result == 0x8876021c)
        {
            do
            {
                uint32_t wait[2];
                surface = port_u32(&port, display, 0x68);
                table = port_u32(&port, surface, 0);
                wait[0] = surface;
                wait[1] = 2;
                result = port_call_stack(&port, port_u32(&port, table, 0x48), surface, table,
                                         display, entry->ecx, wait, 2);
            } while (result == 0x8876021c);
        }
        else
        {
            uint32_t view = port_u32(&port, 0x558c7c, 0);
            port_set32(&port, view, 0x14, port_u32(&port, 0x5b9b5c, 0));
            port_call(&port, 0x478da0, view, port_u32(&port, 0x5b9b5c, 0), display, entry->ecx);
            port_set32(&port, port_u32(&port, 0x558c7c, 0), 0, port_u32(&port, 0x5b9b70, 0));
            return port_return(&port, 1, entry->edx);
        }
    }
}

/* The bobbing states 0x45c480 and 0x45c540: on a new frame (0x4ac520) set the hover height +0x4a
 * and speed +0x4c and hand over to `next` when the animation ends (0x4ad530); then chase the
 * target 0x558944, 0x558946 (0x7d00 while 0x558958 is set) and fall into the idle state 0x45c3c0
 * when it is lost (0x4b0b70). */
static uint32_t actor_bob_step(Port *port, const LiftEntry *entry, uint32_t height, uint32_t next)
{
    uint32_t actor = entry->eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t eax;
    port_call(port, 0x4ac500, actor, entry->edx, ebx, actor);
    edx = vertrix_lift_edx;
    if (port_call(port, 0x4ac520, actor, edx, ebx, actor) == 1)
    {
        edx = port_call(port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_call(port, 0x4ac5b0, actor, edx, ebx, actor);
        port_set16(port, actor, 0x4a, height);
        port_set16(port, actor, 0x4c, 5);
        if (port_call(port, 0x4ad530, actor, vertrix_lift_edx, ebx, actor) == 0)
        {
            port_call(port, 0x4ac8f0, actor, next, ebx, actor);
        }
    }
    eax = port_u32(port, 0x558958, 0) != 0 ? 0x7d00 : 0;
    if (eax == 0)
    {
        eax = (eax & 0xffff0000) | port_u16(port, 0x558946, 0);
    }
    ebx = (uint32_t)(int16_t)eax;
    if (port_u32(port, 0x558958, 0) != 0)
    {
        eax = 0x7d00;
    }
    else
    {
        eax = (eax & 0xffff0000) | port_u16(port, 0x558944, 0);
    }
    if ((port_call(port, 0x4b0b70, actor, (uint32_t)(int16_t)eax, ebx, actor) & 0xff) == 0)
    {
        port_call(port, 0x4ac8f0, actor, 0x45c3c0, ebx, actor);
    }
    return port_call(port, 0x45c2f0, actor, vertrix_lift_edx, ebx, actor);
}

uint32_t vertrix_port_actor_hop_step(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t random;
    port_call(&port, 0x4ac500, actor, entry->edx, ebx, actor);
    if (port_call(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor) == 1)
    {
        ebx = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_call(&port, 0x4ac5b0, actor, 5, ebx, actor);
        random = port_call(&port, 0x4826c0, 0x598d30, vertrix_lift_edx, ebx, actor);
        port_set16(&port, actor, 0xe, port_u16(&port, actor, 0xe) + 2 - random);
        random = port_call(&port, 0x4826c0, 0x598d30, 5, ebx, actor);
        port_set16(&port, actor, 0x16, port_u16(&port, actor, 0x16) + 2 - random);
        if (port_call(&port, 0x4ad530, actor, ebx, ebx, actor) == 0)
        {
            port_call(&port, 0x4ac740, actor, vertrix_lift_edx, ebx, actor);
            if (port_call(&port, 0x4ac760, actor, vertrix_lift_edx, ebx, actor) == 1)
            {
                port_call(&port, 0x4ac700, actor, vertrix_lift_edx, ebx, actor);
            }
            port_set8(&port, actor, 0x44, 0);
            port_call(&port, 0x4ac8f0, actor, 0x4574a0, ebx, actor);
        }
    }
    edx = vertrix_lift_edx;
    return port_return(&port, port_call(&port, 0x4ac8a0, actor, edx, ebx, actor), entry->edx);
}

uint32_t vertrix_port_actor_bob_high(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, actor_bob_step(&port, entry, 0x32, 0x45c540), entry->edx);
}

uint32_t vertrix_port_actor_bob_low(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    return port_return(&port, actor_bob_step(&port, entry, 0, 0x45c480), entry->edx);
}

uint32_t vertrix_port_chunk_list_add(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t list = entry->eax;
    uint32_t size = entry->ebx;
    uint32_t chunk = port_call(&port, 0x4e7c90, 0x14, entry->edx, size, entry->ecx);
    uint32_t buffer;
    if (chunk == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    buffer = port_call(&port, 0x4e7c90, size, vertrix_lift_edx, size, chunk);
    port_set32(&port, chunk, 0, buffer);
    if (buffer == 0)
    {
        port_call(&port, 0x4ea190, chunk, vertrix_lift_edx, size, chunk);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, chunk, 4, size);
    port_call(&port, 0x4eb5e0, buffer, vertrix_lift_edx, size, chunk);
    port_set32(&port, chunk, 0xc, 0);
    port_set32(&port, chunk, 0x10, port_u32(&port, list, 0));
    port_set32(&port, chunk, 8, 0);
    if (port_u32(&port, list, 4) == 0)
    {
        port_set32(&port, list, 4, chunk);
    }
    else
    {
        port_set32(&port, port_u32(&port, list, 0), 0xc, chunk);
    }
    port_set32(&port, list, 0, chunk);
    port_set32(&port, list, 8, port_u32(&port, list, 8) + size);
    return port_return(&port, chunk, vertrix_lift_edx);
}

/* 0x45d420's step with the wander routine `wander` and the restart update `restart`. */
static uint32_t actor_climb_step_with(PORT_SIGNATURE, uint32_t wander, uint32_t restart)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t edx;
    uint32_t result;
    int finished = 1;
    port_call(&port, wander, actor, entry->edx, ebx, actor);
    port_call(&port, 0x4ac370, actor, vertrix_lift_edx, ebx, actor);
    result = port_call(&port, 0x4ac390, actor, vertrix_lift_edx, ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    ebx = port_call(&port, 0x4ac3b0, actor, vertrix_lift_edx, ebx, actor);
    port_call(&port, 0x4ac420, actor, ebx, ebx, actor);
    edx = vertrix_lift_edx;
    if (ebx != 0)
    {
        do
        {
            if (port_call(&port, 0x4ac780, actor, edx, ebx, actor) != 0)
            {
                finished = 0;
                break;
            }
            edx = vertrix_lift_edx - 1;
            port_call(&port, 0x4ac740, actor, edx, ebx, actor);
            edx = vertrix_lift_edx;
        } while (edx != 0);
        if (!finished)
        {
            edx = vertrix_lift_edx;
        }
    }
    port_call(&port, 0x4ac4a0, actor, edx, ebx, actor);
    result = port_call(&port, 0x4adfe0, actor, vertrix_lift_edx, ebx, actor);
    if (finished)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, 0x4ac8d0, actor, 0x544a34, ebx, actor);
    port_call(&port, 0x4ac710, actor, port_u32(&port, actor, 0x58), ebx, actor);
    port_call(&port, 0x4ac8a0, actor, restart, ebx, actor);
    return port_return(&port, port_call(&port, 0x4ac8f0, actor, vertrix_lift_edx, ebx, actor),
                       entry->edx);
}

uint32_t vertrix_port_actor_climb_step(PORT_SIGNATURE)
{
    return actor_climb_step_with(calls, services, globals, entry, 0x45cff0, 0x45d0c0);
}

uint32_t vertrix_port_actor_climb_step_45b410(PORT_SIGNATURE)
{
    return actor_climb_step_with(calls, services, globals, entry, 0x45afe0, 0x45b0b0);
}

uint32_t vertrix_port_mixer_open(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t flags;
    uint32_t buffer;
    port_call(&port, 0x4eb5c0, 0x52f918, 0, 0x324, entry->eax);
    port_set32(&port, 0x52fc1c, 0, port_u16(&port, entry->eax, 4));
    port_set32(&port, 0x52fc20, 0, port_u16(&port, entry->eax, 6));
    flags = port_u8(&port, 0x52fc1d, 0);
    if (flags & 0x80)
    {
        port_set32(&port, 0x52fc34, 0, (flags & 1) ? 0x401f9c : 0x401cd0);
        port_set32(&port, 0x52fc38, 0, (port_u8(&port, 0x52fc1d, 0) & 1) ? 0x4039e4 : 0x4036c8);
    }
    else
    {
        port_set32(&port, 0x52fc34, 0, (flags & 1) ? 0x401328 : 0x40109c);
        port_set32(&port, 0x52fc38, 0, (port_u8(&port, 0x52fc1d, 0) & 1) ? 0x402c18 : 0x402934);
    }
    buffer = port_call(&port, 0x4e7c90, 0x127ff, vertrix_lift_edx, 0x324, entry->eax);
    port_set32(&port, 0x52fc2c, 0, buffer);
    if (buffer == 0)
    {
        return port_return(&port, 8, entry->edx);
    }
    buffer = (buffer + 0x3ff) & 0xfffffc00;
    port_set32(&port, 0x52f910, 0, buffer);
    port_set32(&port, 0x52f914, 0, buffer + 0x10400);
    port_call(&port, 0x40ac30, 1, 0x60, 0x324, entry->eax);
    port_call(&port, 0x40ac00, 0x40cda0, vertrix_lift_edx, 0x324, entry->eax);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_image_clone(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t image = entry->eax;
    uint32_t copy;
    uint32_t pixels;
    uint32_t source;
    uint32_t size;
    uint32_t index;
    if (image == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    copy = port_call(&port, 0x4ec160, 1, 0x28, image, 0x28);
    for (index = 0; index < 0x28; index++)
    {
        port_set8(&port, copy, index, port_u8(&port, image, index));
    }
    size = port_u32(&port, image, 4) * port_u32(&port, image, 8) * port_u8(&port, image, 0x27);
    pixels = port_call(&port, 0x4ec160, size, 1, image, size);
    source = port_u32(&port, image, 0);
    for (index = 0; index < size; index++)
    {
        port_set8(&port, pixels, index, port_u8(&port, source, index));
    }
    port_set32(&port, copy, 0, pixels);
    return port_return(&port, copy, entry->edx);
}

uint32_t vertrix_port_actor_wander_start(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    uint32_t table;
    port_set8(&port, actor, 0x4e, 0);
    port_call(&port, 0x4ac500, actor, entry->edx, ebx, actor);
    if (port_call(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor) == 1)
    {
        result = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_call(&port, 0x4ac5b0, actor, result, ebx, actor);
        if (port_call(&port, 0x4ad6e0, actor, vertrix_lift_edx, ebx, actor) == 0)
        {
            port_set32(&port, actor, 0x58, 0);
            ebx = port_u16(&port, actor, 0x70);
            port_set32(
                &port, actor, 0x5c,
                port_call(&port, 0x482750, 0x598d30, port_u16(&port, actor, 0x64), ebx, actor));
            result = port_call(&port, 0x4826c0, 0x598d30, 0xa, ebx, actor);
            port_call(&port, 0x4ac470, actor, (result & 0xffff) + 2, ebx, actor);
            port_call(&port, 0x4ac710, actor, 0, ebx, actor);
            table = port_call(&port, 0x4b5eb0, 0x546744, 0x190, ebx, actor);
            result =
                port_call(&port, 0x4826c0, 0x598d30, port_u16(&port, table, 0x964), table, actor);
            ebx = table + (result & 0xffff) * 4;
            port_set16(&port, actor, 0xe, port_u16(&port, ebx, 0x874));
            port_set16(&port, actor, 0x16, port_u16(&port, ebx, 0x8ec));
            port_call(&port, 0x4ac8f0, actor, 0x457420, ebx, actor);
            port_set8(&port, actor, 0x4e, 0x32);
        }
    }
    return port_return(&port, port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor),
                       entry->edx);
}

uint32_t vertrix_port_voice_sample_select(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t voice = entry->eax;
    uint32_t note = port_u8(&port, voice, 7);
    uint32_t instrument;
    uint32_t sample;
    uint32_t record;
    uint32_t result;
    uint32_t effect;
    uint32_t on = note >= 1 && note <= 0x60;
    port_set8(&port, voice, 0, on);
    instrument = port_u32(&port, voice, 0x34);
    if (!on || instrument == 0)
    {
        return port_return(&port, (voice & 0xffffff00) | on, entry->edx);
    }
    sample = port_u8(&port, instrument, note + 0x1f);
    port_set8(&port, voice, 6, sample);
    if (sample >= port_u16(&port, instrument, 0x80))
    {
        port_set32(&port, voice, 0x38, 0);
        return port_return(&port, port_u16(&port, instrument, 0x80), entry->edx);
    }
    record = port_u32(&port, instrument, 0xf8) + sample * 0x3c;
    port_set32(&port, voice, 0x38, record);
    port_set32(&port, voice, 0xc, (uint32_t)(int8_t)port_u8(&port, record, 0x22));
    result = (uint32_t)(int8_t)port_u8(&port, record, 0x23);
    port_set32(&port, voice, 8, result);
    effect = port_u8(&port, voice, 3);
    if (effect == 3 || effect == 5)
    {
        return port_return(&port, result, entry->edx);
    }
    result = (result & 0xffffff00) | (port_u8(&port, voice, 2) & 0xf0);
    if ((result & 0xff) == 0xf0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, 0x40ce80, note, port_u32(&port, voice, 0xc),
                       port_u32(&port, voice, 8), voice);
    port_set32(&port, voice, 0x28, result);
    port_set32(&port, voice, 0x24, result);
    port_set8(&port, voice, 1, port_u8(&port, voice, 1) | 9);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_font_sheet_cut(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t columns;
    uint32_t glyph;
    uint32_t cell;
    uint32_t row;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result = 0;
    uint32_t index;
    for (index = 0; index < 0x5d; index++)
    {
        uint32_t paste[1] = {0x5a};
        glyph = port_call(&port, 0x4877f0, 0x544a88, index, ebx, ecx);
        columns = port_u32(&port, 0x4f905c, 0);
        cell = port_u8(&port, 0x4f92a0, index) - 1;
        row = cell / columns;
        ebx = (cell - columns * row) * (port_u32(&port, 0x4f9060, 0) + 1) +
              port_u32(&port, 0x4f9054, 0);
        ecx = port_u32(&port, 0x4f9058, 0) + row * (port_u32(&port, 0x4f9064, 0) + 1);
        port_call(&port, 0x482e10, glyph, entry->eax, ebx, ecx);
        columns = port_u32(&port, 0x4f905c, 0);
        row = index / columns;
        ebx = (index - columns * row) * (port_u32(&port, 0x4f9060, 0) + 1) +
              port_u32(&port, 0x4f9054, 0);
        ecx = port_u32(&port, 0x4f9058, 0) + (row + 2) * (port_u32(&port, 0x4f9064, 0) + 1);
        port_call_stack(&port, 0x482e80, glyph, entry->eax, ebx, ecx, paste, 1);
        result = port_call(&port, 0x483ed0, glyph, 0x5b9c60, ebx, ecx);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_font_sheet_cut_wide(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t cell = port_u8(&port, 0x53bc20, 0);
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result = 0;
    uint32_t index;
    for (index = 0; index < 0x13; index++)
    {
        uint32_t paste[5];
        uint32_t columns;
        uint32_t row;
        uint32_t glyph = port_call(&port, 0x4877f0, 0x544aa4, index, ebx, ecx);
        ebx = port_u32(&port, 0x4f9068, 0) +
              port_u8(&port, 0x4f9300, index) * (port_u32(&port, 0x4f9070, 0) + 1);
        port_call(&port, 0x482e10, glyph, entry->edx, ebx, port_u32(&port, 0x4f906c, 0));
        columns = port_u32(&port, 0x4f905c, 0);
        row = cell / columns;
        ebx = (cell - columns * row) * (port_u32(&port, 0x4f9060, 0) + 1) +
              port_u32(&port, 0x4f9054, 0);
        ecx = (row + 2) * (port_u32(&port, 0x4f9064, 0) + 1) + port_u32(&port, 0x4f9058, 0);
        paste[0] = 2;
        paste[1] = 2;
        paste[2] = port_u32(&port, 0x4f9060, 0);
        paste[3] = port_u32(&port, 0x4f9064, 0);
        paste[4] = 0x5a;
        port_call_stack(&port, 0x482f00, glyph, entry->eax, ebx, ecx, paste, 5);
        cell++;
        ebx = cell;
        result = port_call(&port, 0x483ed0, glyph, 0x5b9c60, ebx, ecx);
    }
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_pattern_cell_read(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t stream = port_u32(&port, 0x530440, 0);
    uint32_t flags = 0;
    uint32_t field;
    if (stream != 0)
    {
        flags = port_u8(&port, stream, 0);
        if (flags & 0x80)
        {
            port_set32(&port, 0x530440, 0, stream + 1);
        }
        else
        {
            flags = 0xff;
        }
    }
    for (field = 0; field < 5; field++)
    {
        uint32_t value = 0;
        if (flags & (1u << field))
        {
            stream = port_u32(&port, 0x530440, 0);
            value = port_u8(&port, stream, 0);
            port_set32(&port, 0x530440, 0, stream + 1);
        }
        port_set8(&port, entry->eax, field, value);
    }
    return port_return(&port, entry->eax, entry->edx);
}

uint32_t vertrix_port_font_strips_cut(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t fonts[3] = {0x544ba0, 0x544bbc, 0x544bd8};
    static const uint32_t strips[3] = {0x4f9090, 0x4f9080, 0x4f90a0};
    static const uint32_t counts[3] = {12, 12, 7};
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result = 0;
    uint32_t strip;
    for (strip = 0; strip < 3; strip++)
    {
        uint32_t index;
        for (index = 0; index < counts[strip]; index++)
        {
            uint32_t glyph = port_call(&port, 0x4877f0, fonts[strip], index, ebx, ecx);
            ecx = port_u32(&port, strips[strip], 4);
            ebx =
                (port_u32(&port, strips[strip], 8) + 1) * index + port_u32(&port, strips[strip], 0);
            port_call(&port, 0x482e10, glyph, entry->eax, ebx, ecx);
            result = port_call(&port, 0x483ed0, glyph, 0x5b9c60, ebx, ecx);
        }
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_module_tick(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t eax = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edx;
    uint32_t flags;
    uint32_t count;
    if (port_u8(&port, 0x531b44, 0) & 0x20)
    {
        return port_return(&port, eax, entry->edx);
    }
    edx = port_u32(&port, 0x531b4c, 0) + 1;
    port_set32(&port, 0x531b4c, 0, edx);
    if ((int32_t)edx >= (int32_t)port_u32(&port, 0x531b60, 0))
    {
        eax = port_call(&port, 0x40e940, eax, edx, ebx, ecx);
        edx = vertrix_lift_edx;
    }
    ecx = 0;
    if ((int32_t)port_u32(&port, 0x531b48, 0) > 0)
    {
        edx = 0x530444;
        do
        {
            eax = port_call(&port, 0x40dc80, edx, edx, ebx, ecx);
            eax = port_call(&port, 0x40dc50, edx, vertrix_lift_edx, ebx, ecx);
            eax = port_call(&port, 0x40e030, edx, vertrix_lift_edx, ebx, ecx);
            edx = vertrix_lift_edx + 0xb4;
            ecx++;
        } while ((int32_t)ecx < (int32_t)port_u32(&port, 0x531b48, 0));
    }
    flags = port_u8(&port, 0x531b44, 0);
    edx = (edx & 0xffffff00) | flags;
    if ((flags & 4) && port_u32(&port, 0x531b4c, 0) == 0)
    {
        eax = port_u32(&port, 0x531b78, 0) - 1;
        port_set32(&port, 0x531b78, 0, eax);
        if (eax == 0)
        {
            edx = (edx & 0xffff00ff) | ((flags & 0xfb) << 8);
            port_set8(&port, 0x531b44, 0, flags & 0xfb);
        }
    }
    flags = port_u8(&port, 0x531b44, 0);
    ebx = (ebx & 0xffffff00) | flags;
    if (flags & 0x10)
    {
        ebx = (ebx & 0xffff00ff) | ((flags & 0xef) << 8);
        port_set8(&port, 0x531b44, 0, flags & 0xef);
        ecx = 0;
        if ((int32_t)port_u32(&port, 0x531b48, 0) > 0)
        {
            edx = 0;
            do
            {
                port_set8(&port, edx, 0x530445, port_u8(&port, edx, 0x530445) | 2);
                edx += 0xb4;
                ecx++;
            } while ((int32_t)ecx < (int32_t)port_u32(&port, 0x531b48, 0));
        }
    }
    flags = port_u8(&port, 0x531b44, 0);
    eax = (eax & 0xffff00ff) | (flags << 8);
    if (flags & 8)
    {
        edx = (edx & 0xffffff00) | (flags & 0xf7);
        port_set8(&port, 0x531b44, 0, flags & 0xf7);
        eax = port_call(&port, 0x40ac20, port_u32(&port, 0x531b64, 0), edx, ebx, ecx);
    }
    for (count = 0; (int32_t)count < (int32_t)port_u32(&port, 0x531b48, 0); count++)
    {
        uint32_t channel = 0x530444 + count * 0xb4;
        eax = port_call_with(&port, 0x40e8a0, port_u32(&port, 0x531ac4, count * 4), channel,
                             count * 4, channel, count, 0, 0);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_environment_table_build(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t block = port_u32(&port, 0x509729, 0);
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t count = 0;
    uint32_t end = block;
    uint32_t length;
    uint32_t buffer;
    uint32_t table;
    uint32_t result;
    if (port_u32(&port, 0x5c81d4, 0) != 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    edx = (edx & 0xffffff00) | port_u8(&port, block, 0);
    if (port_u8(&port, block, 0) != 0)
    {
        for (;;)
        {
            uint32_t value = port_u8(&port, end, 0);
            ebx = end + 1;
            if (value != 0)
            {
                end = ebx;
                continue;
            }
            count++;
            value = port_u8(&port, ebx, 0);
            end = ebx;
            if (value == 0)
            {
                break;
            }
        }
        edx &= 0xffff00ff;
    }
    port_set32(&port, 0x5c81d4, 0, 0);
    length = end - block;
    if (length == 0)
    {
        length = 1;
    }
    buffer = port_call(&port, 0x4e7c90, length, edx, ebx, count);
    if (buffer == 0)
    {
        result = port_call(&port, 0x4e9f10, 0, 0, 0, count);
        return port_return(&port, result, entry->edx);
    }
    port_set32(&port, 0x5c8a90, 0, buffer);
    table = port_call(&port, 0x4e7c90, count * 5 + 4, buffer, buffer, count);
    if (table == 0)
    {
        result = port_call(&port, 0x4ea190, buffer, buffer, buffer, count);
        result = port_call(&port, 0x4e9f10, result, vertrix_lift_edx, buffer, count);
        return port_return(&port, result, entry->edx);
    }
    {
        uint32_t source = block;
        uint32_t target = buffer;
        uint32_t offset = 0;
        uint32_t strings = 0;
        if (port_u8(&port, block, 0) != 0)
        {
            do
            {
                uint32_t value;
                port_set32(&port, table, offset, target);
                do
                {
                    value = port_u8(&port, source++, 0);
                    port_set8(&port, target++, 0, value);
                } while (value != 0);
                offset += 4;
                strings++;
            } while (port_u8(&port, source, 0) != 0);
        }
        port_set32(&port, table, offset, 0);
        offset += 4;
        port_set32(&port, 0x5c81d0, 0, table + offset);
        port_set32(&port, 0x5c81d4, 0, table);
        result = port_call(&port, 0x4eb5c0, table + offset, 0, strings, offset);
        result = port_call(&port, 0x4e9f10, result, vertrix_lift_edx, strings, offset);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_channel_row_read(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t voice = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t eax = port_call(&port, 0x40e690, 0x531b80, voice, ebx, ecx);
    uint32_t effect = port_u8(&port, voice, 3);
    uint32_t instrument;
    uint32_t note;
    eax = (eax & 0xffff00ff) | (effect << 8);
    if (effect == 4 || effect == 6)
    {
        uint32_t next = port_u8(&port, 0x531b83, 0);
        eax = (eax & 0xffffff00) | next;
        if (next != 4 && next != 6)
        {
            eax = port_u32(&port, voice, 0x24);
            port_set32(&port, voice, 0x28, eax);
            port_set8(&port, voice, 1, port_u8(&port, voice, 1) | 1);
        }
    }
    else if (effect == 0 && port_u8(&port, voice, 4) != 0)
    {
        eax = port_u32(&port, voice, 0x24);
        port_set32(&port, voice, 0x28, eax);
        port_set8(&port, voice, 1, port_u8(&port, voice, 1) | 1);
    }
    port_set8(&port, voice, 2, port_u8(&port, 0x531b82, 0));
    port_set8(&port, voice, 3, port_u8(&port, 0x531b83, 0));
    eax = (eax & 0xffffff00) | port_u8(&port, 0x531b84, 0);
    port_set8(&port, voice, 4, eax);
    instrument = port_u8(&port, 0x531b81, 0);
    if (instrument >= 1)
    {
        ebx = port_u32(&port, 0x53043c, 0);
        eax = port_u16(&port, ebx, 0x2a);
        ecx = instrument;
        if ((int32_t)instrument <= (int32_t)eax)
        {
            port_set8(&port, voice, 5, instrument);
            eax = (instrument - 1) * 0xfc;
            ecx = port_u32(&port, ebx, 0x154) + eax;
            port_set32(&port, voice, 0x34, ecx);
        }
    }
    note = port_u8(&port, 0x531b80, 0);
    ecx = (ecx & 0xffffff00) | note;
    if (note >= 1 && note <= 0x60)
    {
        port_set8(&port, voice, 7, note);
        eax = port_call(&port, 0x40e580, voice, voice, ebx, ecx);
        if (port_u8(&port, 0x531b81, 0) != 0 && port_u32(&port, voice, 0x38) != 0)
        {
            eax = port_call(&port, 0x40df20, voice, voice, ebx, ecx);
        }
    }
    else if (note != 0)
    {
        eax = port_call(&port, 0x40e640, voice, voice, ebx, ecx);
    }
    if (port_u8(&port, 0x531b81, 0) == 0 || port_u32(&port, voice, 0x38) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_u8(&port, port_u32(&port, voice, 0x38), 0x20);
    port_set32(&port, voice, 0x14, eax);
    port_set32(&port, voice, 0x10, eax);
    port_set8(&port, voice, 1, port_u8(&port, voice, 1) | 2);
    if (port_u8(&port, 0x531b47, 0) & 0x80)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_u8(&port, port_u32(&port, voice, 0x38), 0x21);
    port_set32(&port, voice, 0x1c, eax);
    port_set8(&port, voice, 1, port_u8(&port, voice, 1) | 4);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_audio_driver_open(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t settings = entry->eax;
    uint32_t busy = port_u32(&port, 0x4f6418, 0);
    uint32_t edx = busy;
    uint32_t result;
    uint32_t driver;
    uint32_t table;
    uint32_t routines;
    if (busy != 0xffff)
    {
        return port_return(&port, 3, entry->edx);
    }
    if (settings != 0 && busy == port_u32(&port, settings, 0))
    {
        result = port_call(&port, 0x40a950, settings, busy, entry->ebx, settings);
        edx = vertrix_lift_edx;
        if (result != 0)
        {
            return port_return(&port, port_call(&port, 0x40a800, result, edx, entry->ebx, settings),
                               entry->edx);
        }
    }
    if (settings == 0)
    {
        return port_return(&port, port_call(&port, 0x40a800, 2, edx, entry->ebx, settings),
                           entry->edx);
    }
    if (port_u32(&port, settings, 0) >= 8 ||
        (driver = port_u32(&port, 0x52f090, port_u32(&port, settings, 0) * 4)) == 0)
    {
        return port_return(&port, port_call(&port, 0x40a800, 4, edx, entry->ebx, settings),
                           entry->edx);
    }
    table = port_u32(&port, driver, 0);
    if (table == 0)
    {
        table = 0x4f7658;
    }
    routines = port_u32(&port, driver, 4);
    if (routines == 0)
    {
        routines = 0x4f651c;
    }
    port_call(&port, 0x4eb5e0, 0x52f010, table, 0x18, settings);
    port_call(&port, 0x4eb5e0, 0x52f028, routines, 0x68, settings);
    result =
        port_call(&port, port_u32(&port, 0x52f018, 0), settings, vertrix_lift_edx, 0x68, settings);
    if (result != 0)
    {
        return port_return(&port,
                           port_call(&port, 0x40a800, result, vertrix_lift_edx, 0x68, settings),
                           entry->edx);
    }
    result =
        port_call(&port, port_u32(&port, 0x52f030, 0), settings, vertrix_lift_edx, 0x68, settings);
    if (result != 0)
    {
        port_call(&port, port_u32(&port, 0x52f01c, 0), result, vertrix_lift_edx, result, settings);
        return port_return(&port,
                           port_call(&port, 0x40a800, result, vertrix_lift_edx, result, settings),
                           entry->edx);
    }
    port_call(&port, 0x4eb5c0, 0x52f0b0, 0, 0x80, settings);
    port_set32(&port, 0x52f130, 0, 0);
    port_set32(&port, 0x4f6418, 0, port_u32(&port, settings, 0));
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_mixer_volume_tables(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t volume = entry->edx;
    uint32_t table;
    uint32_t level;
    uint32_t index;
    int32_t value;
    if (port_u32(&port, 0x52fc2c, 0) == 0)
    {
        return port_return(&port, 3, entry->edx);
    }
    if (entry->eax != 1 || volume > 0x100)
    {
        return port_return(&port, 2, entry->edx);
    }
    if ((port_u8(&port, 0x52fc1d, 0) & 1) == 0)
    {
        volume >>= 1;
    }
    table = port_u32(&port, 0x52f910, 0);
    for (level = 0; level <= 0x40; level++)
    {
        uint32_t step = level * volume;
        value = 0;
        for (index = 0; index < 0x80; index++, table += 4)
        {
            port_set32(&port, table, 0, (uint32_t)(value >> 4));
            value += (int32_t)step;
        }
        value = -value;
        for (index = 0; index < 0x80; index++, table += 4)
        {
            port_set32(&port, table, 0, (uint32_t)(value >> 4));
            value += (int32_t)step;
        }
    }
    table = port_u32(&port, 0x52f914, 0);
    for (level = 0; level < 0x20; level++)
    {
        value = 0;
        for (index = 0; index < 0x80; index++, table++)
        {
            port_set8(&port, table, 0, (uint32_t)(value >> 5));
            value += (int32_t)level;
        }
        value = -value;
        for (index = 0; index < 0x80; index++, table++)
        {
            port_set8(&port, table, 0, (uint32_t)(value >> 5));
            value += (int32_t)level;
        }
    }
    return port_return(&port, 0, table);
}

uint32_t vertrix_port_module_start(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t module = entry->eax;
    uint32_t channel;
    uint32_t edx;
    uint32_t ecx;
    if (port_u8(&port, 0x531b44, 0) & 0x80)
    {
        return port_return(&port, 3, entry->edx);
    }
    if (module == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_call(&port, 0x4eb5c0, 0x53043c, 0, 0x1744, entry->ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, 0x53043c, 0, module);
    port_set32(&port, 0x531b48, 0, port_u16(&port, module, 0x26));
    port_set16(&port, 0x531b46, 0, port_u16(&port, module, 0x20));
    port_set32(&port, 0x531b60, 0, port_u16(&port, module, 0x2c));
    port_set32(&port, 0x531b64, 0, port_u16(&port, module, 0x2e));
    port_set32(&port, 0x531b68, 0, 0x40);
    port_set16(&port, 0x531b44, 0, 0x81);
    for (channel = 0; (int32_t)channel < (int32_t)port_u32(&port, 0x531b48, 0); channel++)
    {
        uint32_t result =
            port_call(&port, 0x40acf0, 0x531ac4 + channel * 4, edx, channel, channel * 0xb4);
        uint32_t pan;
        if (result != 0)
        {
            port_call(&port, 0x40ed70, result, vertrix_lift_edx, channel, channel * 0xb4);
            return port_return(&port, 8, entry->edx);
        }
        pan = port_u8(&port, module + channel, 0x130);
        port_set32(&port, channel * 0xb4, 0x530460, pan);
        port_call(&port, 0x40ae10, port_u32(&port, 0x531ac4, channel * 4), pan, channel,
                  channel * 0xb4);
        edx = vertrix_lift_edx;
    }
    ecx = channel != 0 ? channel * 0xb4 : entry->ecx;
    port_call(&port, 0x40ac20, port_u32(&port, 0x531b64, 0), edx, channel, ecx);
    port_call(&port, 0x40ac10, 0x40eb10, vertrix_lift_edx, channel, ecx);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_static_init_503a1c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t index;
    for (index = 0; index < 8; index++)
    {
        port_set32(&port, 0x503a1c + index * 0x20, 0, 0x4d7430 + index * 0x10);
        port_set32(&port, 0x503a1c + index * 0x20, 4, 0);
        port_set32(&port, 0x503a1c + index * 0x20, 8, 0);
    }
    port_set32(&port, 0x503b1c, 0, 0);
    port_set32(&port, 0x503b20, 0, 0);
    port_set32(&port, 0x503b24, 0, 0);
    return port_return(
        &port, port_call(&port, 0x4d30f0, 0x5c75fc, 0x503b28, entry->ebx, entry->ecx), entry->edx);
}

uint32_t vertrix_port_dither_tables_build(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t pattern;
    uint32_t target = 0x5bdb00;
    for (pattern = 0; pattern < 0x10; pattern++)
    {
        uint32_t bits = port_u32(&port, 0x4ff8ac, pattern * 4);
        uint32_t row;
        for (row = 0; row < 0x40; row++)
        {
            uint32_t mask;
            for (mask = 0x8000; mask != 0; mask >>= 1)
            {
                port_set8(&port, target++, 0, (bits & mask) != 0);
            }
        }
    }
    for (pattern = 0; pattern < 0x10; pattern++)
    {
        uint32_t position;
        for (position = 0; position < 0x10; position++)
        {
            uint32_t count = 0;
            uint32_t index;
            for (index = 0; index < position; index++)
            {
                if (port_u8(&port, 0x5bdb00 + (pattern << 10), index) != 0)
                {
                    count++;
                }
            }
            port_set8(&port, 0x5c1b00 + pattern * 0x10, position, count);
        }
    }
    for (pattern = 1; pattern < 0x10; pattern++)
    {
        uint32_t gaps = 0x5c1c00 + (pattern << 10);
        uint32_t source = 0x5bdb00 + (pattern << 10) + 1;
        uint32_t gap = 1;
        uint32_t remaining;
        port_call(&port, 0x4eb5c0, gaps, 0, 0x400, 0x101);
        for (remaining = 0x3ff; remaining != 0; remaining--, source++)
        {
            if (port_u8(&port, source, 0) != 0)
            {
                port_set8(&port, gaps++, 0, gap);
                gap = 1;
            }
            else
            {
                gap = (gap + 1) & 0xff;
            }
        }
    }
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_fonts_create(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    static const uint32_t fonts[6] = {0x544a88, 0x544aa4, 0x544b84, 0x544ba0, 0x544bbc, 0x544bd8};
    static const uint32_t glyphs[6] = {0x5d, 0x13, 0xd, 0xc, 0xc, 7};
    static const uint32_t cells[6] = {0x4f9060, 0x4f9070, 0x4f9078, 0x4f9098, 0x4f9088, 0x4f90a8};
    uint32_t result = 0;
    uint32_t index;
    for (index = 0; index < 6; index++)
    {
        uint32_t width = port_u32(&port, cells[index], 0);
        uint32_t height = port_u32(&port, cells[index], 4);
        uint32_t stack[10] = {0, 0, 0, 0, width, height, 0, 0, index < 5, 4};
        result =
            port_call_stack(&port, 0x4875a0, fonts[index], glyphs[index], width, height, stack, 10);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_module_next_row(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t eax = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edx = 0;
    uint32_t flags;
    uint32_t module;
    uint32_t order;
    port_set32(&port, 0x531b4c, 0, 0);
    flags = port_u8(&port, 0x531b44, 0);
    eax = (eax & 0xffff00ff) | (flags << 8);
    if (flags & 4)
    {
        return port_return(&port, eax, entry->edx);
    }
    ecx = port_u32(&port, 0x531b50, 0) + 1;
    port_set32(&port, 0x531b50, 0, ecx);
    if ((int32_t)ecx >= (int32_t)port_u32(&port, 0x531b54, 0))
    {
        edx = flags | 2;
        port_set8(&port, 0x531b44, 0, edx);
    }
    flags = port_u8(&port, 0x531b44, 0);
    edx = (edx & 0xffff00ff) | (flags << 8);
    if (flags & 1)
    {
        port_set32(&port, 0x531b50, 0, port_u32(&port, 0x531b74, 0));
        port_set32(&port, 0x531b74, 0, 0);
        eax = port_u32(&port, 0x531b70, 0);
        port_set32(&port, 0x531b5c, 0, eax);
    }
    else if (flags & 2)
    {
        eax = port_u32(&port, 0x531b74, 0);
        port_set32(&port, 0x531b50, 0, eax);
        port_set32(&port, 0x531b74, 0, 0);
        port_set32(&port, 0x531b5c, 0, port_u32(&port, 0x531b5c, 0) + 1);
    }
    flags = port_u8(&port, 0x531b44, 0);
    ebx = (ebx & 0xffff00ff) | (flags << 8);
    if (flags & 3)
    {
        port_set8(&port, 0x531b44, 0, flags & 0xfc);
        module = port_u32(&port, 0x53043c, 0);
        ecx = port_u16(&port, module, 0x22);
        if (!((int32_t)ecx > (int32_t)port_u32(&port, 0x531b5c, 0)))
        {
            eax = port_u16(&port, module, 0x24);
            port_set32(&port, 0x531b5c, 0, eax);
            if ((int32_t)ecx <= (int32_t)eax)
            {
                port_set32(&port, 0x531b5c, 0, 0);
                port_set8(&port, 0x531b44, 0, port_u8(&port, 0x531b44, 0) | 0x20);
                return port_return(&port, eax, entry->edx);
            }
        }
        order = port_u8(&port, module + port_u32(&port, 0x531b5c, 0), 0x30);
        port_set32(&port, 0x531b58, 0, order);
        eax = port_u16(&port, module, 0x28);
        if ((int32_t)eax <= (int32_t)order)
        {
            port_set32(&port, 0x531b54, 0, 0x40);
            port_set32(&port, 0x530440, 0, 0);
        }
        else
        {
            uint32_t pattern = port_u32(&port, module, 0x150) + order * 12;
            edx = port_u16(&port, pattern, 4);
            port_set32(&port, 0x531b54, 0, edx);
            eax = port_u32(&port, pattern, 8);
            port_set32(&port, 0x530440, 0, eax);
            if (!((int32_t)edx > (int32_t)port_u32(&port, 0x531b50, 0)))
            {
                ebx = 0;
                port_set32(&port, 0x531b50, 0, 0);
            }
            for (ecx = 0; (int32_t)ecx < (int32_t)port_u32(&port, 0x531b50, 0); ecx++)
            {
                ebx = 0x531b85;
                for (edx = 0; (int32_t)edx < (int32_t)port_u32(&port, 0x531b48, 0);
                     edx = vertrix_lift_edx + 1)
                {
                    eax = port_call(&port, 0x40e690, ebx, edx, ebx, ecx);
                }
            }
        }
    }
    for (ecx = 0; (int32_t)ecx < (int32_t)port_u32(&port, 0x531b48, 0); ecx++)
    {
        edx = 0x530444 + ecx * 0xb4;
        eax = port_call(&port, 0x40e770, edx, edx, ebx, ecx);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_mpeg_header_decode(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t frame = entry->eax;
    uint32_t header = entry->edx;
    uint32_t rate;
    uint32_t layer;
    uint32_t bits;
    uint32_t divisor;
    int32_t size;
    if (header & 0x100000)
    {
        port_set32(&port, frame, 0xc, (header & 0x80000) == 0);
        port_set32(&port, frame, 0x10, 0);
    }
    else
    {
        port_set32(&port, frame, 0xc, 1);
        port_set32(&port, frame, 0x10, 1);
    }
    layer = 4 - ((header >> 17) & 3);
    port_set32(&port, frame, 0x18, layer);
    if (((header >> 10) & 3) == 3)
    {
        port_call(&port, 0x4eb4d4, 1, header, frame, layer);
        header = vertrix_lift_edx;
    }
    rate = (header >> 10) & 3;
    if (port_u32(&port, frame, 0x10) != 0)
    {
        rate += 6;
    }
    else
    {
        rate += port_u32(&port, frame, 0xc) * 3;
    }
    port_set32(&port, frame, 0x24, rate);
    port_set32(&port, frame, 0x1c, ((header >> 16) & 1) ^ 1);
    port_set32(&port, frame, 0x20, (header >> 12) & 0xf);
    port_set32(&port, frame, 0x28, (header >> 9) & 1);
    port_set32(&port, frame, 0x2c, (header >> 8) & 1);
    port_set32(&port, frame, 0x30, (header >> 6) & 3);
    port_set32(&port, frame, 0x34, (header >> 4) & 3);
    port_set32(&port, frame, 0x38, (header >> 3) & 1);
    port_set32(&port, frame, 0x3c, (header >> 2) & 1);
    port_set32(&port, frame, 0x40, header & 3);
    port_set32(&port, frame, 0, (port_u32(&port, frame, 0x30) != 3) + 1);
    bits = port_u32(&port, frame, 0x20);
    if (bits == 0)
    {
        return port_return(&port, 0, header & 3);
    }
    layer = port_u32(&port, frame, 0x18);
    if (layer == 1 || layer == 2)
    {
        return port_return(&port, 1, layer);
    }
    if (layer != 3)
    {
        return port_return(&port, 0, layer);
    }
    size = (int32_t)(port_u32(&port, 0x4f40ac, port_u32(&port, frame, 0xc) * 0xc0 + bits * 4) *
                     0x23280);
    port_set32(&port, frame, 0x44, (uint32_t)size);
    divisor = port_u32(&port, 0x4f41ac, port_u32(&port, frame, 0x24) * 4)
              << (port_u8(&port, frame, 0xc) & 31);
    port_set32(&port, frame, 0x44, (uint32_t)(size / (int32_t)divisor));
    port_set32(&port, frame, 0x44,
               (uint32_t)(size / (int32_t)divisor) + port_u32(&port, frame, 0x28) - 4);
    return port_return(&port, 1, (uint32_t)(size % (int32_t)divisor));
}

uint32_t vertrix_port_title_actors_spawn(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t animations[2];
    uint32_t idle[2];
    uint32_t xs[2];
    uint32_t ys[2];
    uint32_t states[2];
    uint32_t edx = 0;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t index;
    for (index = 0; index < 2; index++)
    {
        idle[index] = port_u32(&port, 0x4fd648, index * 4);
        xs[index] = port_u32(&port, 0x4fd650, index * 4);
        ys[index] = port_u32(&port, 0x4fd658, index * 4);
        animations[index] = port_u32(&port, 0x546834, index * 4);
        states[index] = port_u32(&port, 0x4fd660, index * 4);
    }
    for (index = 0; index < 2; index++)
    {
        static const uint32_t none[5] = {0, 0, 0, 0, 0};
        uint32_t actor = port_call(&port, 0x4ca000, 0x15c, edx, ebx, ecx);
        if (actor != 0)
        {
            actor = port_call(&port, 0x4abd70, actor, vertrix_lift_edx, ebx, ecx);
        }
        ebx = 0;
        ecx = 0;
        port_call_stack(&port, 0x4adf20, actor, 0, 0, 0, none, 5);
        port_call(&port, 0x4ac910, actor, 0, 0, 0);
        port_set16(&port, actor, 0x24, port_call(&port, 0x4826c0, 0x598d30, 0x168, 0, 0));
        port_set16(&port, actor, 0x28, port_call(&port, 0x4826c0, 0x598d30, 2, 0, 0) + 1);
        port_set8(&port, actor, 0x8f, 1);
        port_set32(&port, actor, 0x58, animations[index]);
        if (animations[index] == 0)
        {
            port_call(&port, 0x4ac950, actor, 0, 0, 0);
            port_call(&port, 0x4ac8d0, actor, 0, 0, 0);
        }
        else
        {
            port_call(&port, 0x4ac8d0, actor, idle[index], 0, 0);
            port_call(&port, 0x4ac710, actor, 0, 0, 0);
            port_call(&port, 0x4ac8a0, actor, 0x64, 0, 0);
        }
        port_call(&port, 0x4ac490, actor, 0x32, 0, 0);
        port_call(&port, 0x4ac7d0, actor, 0xc8, 0, 0);
        port_call(&port, 0x4ac860, actor, 0xa, 0, 0);
        port_set16(&port, actor, 8, xs[index]);
        port_set16(&port, actor, 0x12, 1);
        port_set16(&port, actor, 0x1a, 0);
        port_set16(&port, actor, 0xa, ys[index]);
        port_set16(&port, actor, 0xe, port_u16(&port, actor, 8));
        port_set16(&port, actor, 0x16, port_u16(&port, actor, 0xa));
        port_set32(&port, actor, 0x124, 1);
        port_call_stack(&port, 0x4ae110, actor, 0, 0, 0, none, 1);
        port_set32(&port, actor, 0x13c, 0);
        if (index == 0)
        {
            port_set32(&port, actor, 0x140, 1);
        }
        port_call(&port, 0x4ac8f0, actor, states[index], 0, 0);
        port_call(&port, 0x4b5e70, 0x546744, actor, 0, 0);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, index, entry->edx);
}

uint32_t vertrix_port_actor_face_target(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t result;
    uint32_t x;
    uint32_t y;
    uint32_t distance;
    uint32_t angle;
    uint32_t side;
    uint32_t facing;
    uint32_t ahead;
    uint32_t behind;
    port_call(&port, 0x4ac500, actor, entry->edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, entry->ecx);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, 0x4adfe0, actor, vertrix_lift_edx, entry->ebx, entry->ecx);
    result = port_call(&port, 0x4ac510, actor, vertrix_lift_edx, entry->ebx, entry->ecx);
    x = port_u32(&port, 0x558958, 0) != 0 ? 0x7d00 : port_u16(&port, 0x558944, 0);
    y = port_u32(&port, 0x558958, 0) != 0 ? 0x7d00 : port_u16(&port, 0x558946, 0);
    x = (uint32_t)(int16_t)x;
    y = (uint32_t)(int16_t)y;
    distance = port_call(&port, 0x484680, x, y, 0x1aa, 0x28);
    angle = port_call(&port, 0x484700, x, y, 0x1aa, 0x28);
    side = (((angle & 0xffff) + 0x70) & 0xffff) % 0x168;
    if (distance <= 0x19)
    {
        port_call(&port, 0x4ac8d0, actor, 0, distance, side);
        return port_return(&port, port_call(&port, 0x4ac950, actor, 0, distance, side), entry->edx);
    }
    side /= 0x2d;
    facing = port_u32(&port, actor, 0xb8);
    if (port_u32(&port, actor, 0xb0) == 0)
    {
        port_call(&port, 0x4ac8d0, actor, 0x54666c, distance, side);
        port_call(&port, 0x4ac710, actor, side, distance, side);
        return port_return(
            &port, port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, distance, side), entry->edx);
    }
    if (side == facing)
    {
        return port_return(&port, facing, entry->edx);
    }
    if ((int32_t)side > (int32_t)facing)
    {
        ahead = side - facing;
        behind = facing + 8 - side;
    }
    else
    {
        ahead = side + 8 - facing;
        behind = facing - side;
    }
    if (ahead > behind)
    {
        if (behind > 3)
        {
            port_call(&port, 0x4ac8d0, actor, 0, distance, side);
            return port_return(&port, port_call(&port, 0x4ac950, actor, 0, distance, side),
                               entry->edx);
        }
        facing--;
        if ((int32_t)facing < 0)
        {
            facing = 7;
        }
    }
    else
    {
        if (ahead > 3)
        {
            port_call(&port, 0x4ac8d0, actor, 0, distance, side);
            return port_return(&port, port_call(&port, 0x4ac950, actor, 0, distance, side),
                               entry->edx);
        }
        facing++;
        if ((int32_t)facing > 7)
        {
            facing = 0;
        }
    }
    port_call(&port, 0x4ac710, actor, facing, distance, side);
    return port_return(&port, port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, distance, side),
                       entry->edx);
}

uint32_t vertrix_port_static_init_animations(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    /* Each step: the routine, its object, then the ebx and edx the original sets
     * before it (0xffffffff where it keeps them). */
    static const uint32_t steps[84][4] = {
        {0x4872f0, 0x5449c4, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbc30, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x5449e0, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbc40, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x5449fc, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbc50, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544a18, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbc60, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544a34, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbc70, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544a50, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbc80, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544a6c, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbc90, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544a88, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbca0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544aa4, 0x515610, 0xffffffff},   {0x4ec1f7, 0x4fbcb0, 0xffffffff, 0x7},
        {0x4ccf3b, 0x544ac0, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbcc0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544b84, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbcd0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544ba0, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbce0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544bbc, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbcf0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544bd8, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd00, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544bf4, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd10, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544c10, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd20, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544c2c, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd30, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544c48, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd40, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544c64, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd50, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544c80, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd60, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544c9c, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd70, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544cb8, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd80, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544cd4, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbd90, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544cf0, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbda0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544d0c, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbdb0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544d28, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbdc0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544d44, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbdd0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x544d60, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbde0, 0xffffffff, 0xffffffff},
        {0x4ccf3b, 0x544d7c, 0x515610, 0x13},         {0x4ec1f7, 0x4fbdf0, 0x515610, 0xbe},
        {0x4ccf3b, 0x544f90, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe00, 0x515610, 0x5},
        {0x4ccf3b, 0x546458, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe10, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x5464e4, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe20, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x546500, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe30, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x54651c, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe40, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x546538, 0x515610, 0xffffffff},   {0x4ec1f7, 0x4fbe50, 0xffffffff, 0x7},
        {0x4ccf3b, 0x546554, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe60, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x546618, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe70, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x546634, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe80, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x546650, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbe90, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x54666c, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbea0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x546688, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbeb0, 0xffffffff, 0xffffffff},
        {0x4872f0, 0x5466a4, 0xffffffff, 0xffffffff}, {0x4ec1f7, 0x4fbec0, 0xffffffff, 0xffffffff}};
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t result = 0;
    uint32_t index;
    for (index = 0; index < 84; index++)
    {
        if (steps[index][2] != 0xffffffff)
        {
            ebx = steps[index][2];
        }
        if (steps[index][3] != 0xffffffff)
        {
            edx = steps[index][3];
        }
        result = port_call(&port, steps[index][0], steps[index][1], edx, ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, entry->edx);
}

/* The high half of the dword at `address`, sign extended (mov eax, [address]; sar eax, 16). */
static uint32_t port_high16(Port *port, uint32_t address)
{
    return (uint32_t)(int16_t)port_u16(port, address, 2);
}

uint32_t vertrix_port_actor_draw_frame(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t actor = entry->eax;
    uint32_t key = port_u32(&port, actor, 0x11c);
    uint32_t screen = port_u32(&port, 0x5bc010, 0);
    uint32_t eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    if (key != 0xff000000)
    {
        uint32_t stack[7] = {port_high16(&port, 0x5bb746),
                             port_high16(&port, 0x5bb748),
                             port_high16(&port, 0x5bbff4),
                             port_high16(&port, 0x5bbff8),
                             port_high16(&port, 0x5bbff6),
                             port_high16(&port, 0x5bbffa),
                             key};
        ebx = port_high16(&port, 0x5bb79e);
        ecx = port_high16(&port, 0x5bb7a0);
        eax = port_call_stack(&port, 0x47c710, screen, 0x5b9c60, ebx, ecx, stack, 7);
    }
    else
    {
        uint32_t depth = port_u8(&port, 0x5bb733, 0);
        uint32_t frame;
        uint32_t draw;
        if (depth == 4)
        {
            ecx = 0;
        }
        else if (depth == 2)
        {
            ecx = 1;
        }
        else if (depth == 1)
        {
            ecx = 2;
        }
        else if (depth == 0)
        {
            ecx = 3;
        }
        frame = port_call(&port, 0x4af370, actor, 1, ebx, ecx);
        frame = port_call(&port, 0x4af2a0, actor, frame, ebx, ecx);
        eax = frame;
        if (frame >= 0x5c)
        {
            ecx = 0;
            port_set32(&port, 0x5bb72c, 0, 0);
        }
        else
        {
            draw = port_u32(&port, 0x4ff024, ecx * 0x170 + frame * 4);
            port_set32(&port, 0x5bb72c, 0, draw);
            eax = draw;
            if (draw != 0)
            {
                eax = port_call(&port, 0x4ae250, actor, frame, ebx, ecx);
                eax =
                    port_call(&port, port_u32(&port, 0x5bb72c, 0), eax, vertrix_lift_edx, ebx, ecx);
            }
        }
    }
    if (port_u8(&port, actor, 0x110) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    screen = port_u32(&port, 0x5bc010, 0);
    if (port_u8(&port, 0x5bbffe, 0) == 2)
    {
        uint32_t left = port_high16(&port, 0x5bb746);
        uint32_t top = port_high16(&port, 0x5bb748);
        uint32_t right = port_high16(&port, 0x5bb79e);
        uint32_t bottom = port_high16(&port, 0x5bb7a0);
        uint32_t stack[7] = {left, top, right, bottom, left, top, port_u32(&port, actor, 0x118)};
        eax = port_call_stack(&port, 0x47c520, screen, 0x5b9c60, right, bottom, stack, 7);
        return port_return(&port, eax, entry->edx);
    }
    {
        uint32_t stack[7] = {port_high16(&port, 0x5bb746) + 1, port_high16(&port, 0x5bb748) + 1,
                             port_high16(&port, 0x5bbff4),     port_high16(&port, 0x5bbff8),
                             port_high16(&port, 0x5bbff6),     port_high16(&port, 0x5bbffa),
                             port_u32(&port, actor, 0x118)};
        eax = port_call_stack(&port, 0x47c520, screen, 0x5b9c60, port_high16(&port, 0x5bb79e) - 1,
                              port_high16(&port, 0x5bb7a0) - 1, stack, 7);
    }
    {
        uint32_t stack[7] = {port_high16(&port, 0x5bb746) + 2, port_high16(&port, 0x5bb748) + 2,
                             port_high16(&port, 0x5bbff4),     port_high16(&port, 0x5bbff8),
                             port_high16(&port, 0x5bbff6),     port_high16(&port, 0x5bbffa),
                             port_u32(&port, actor, 0x114)};
        eax = port_call_stack(&port, 0x47c520, port_u32(&port, 0x5bc010, 0), 0x5b9c60,
                              port_high16(&port, 0x5bb79e) - 2, port_high16(&port, 0x5bb7a0) - 2,
                              stack, 7);
    }
    if (port_u32(&port, actor, 0x13c) == 0)
    {
        uint32_t box = port_u32(&port, actor, 0x130) + 4;
        eax = port_call_stack(&port, 0x4ae110, actor,
                              (uint32_t)(int16_t)(port_u16(&port, actor, 0x128) - 2),
                              (uint32_t)(int16_t)(port_u16(&port, actor, 0x12a) - 2),
                              port_u32(&port, actor, 0x12c) + 4, &box, 1);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_time_from_tm(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    uint32_t tm = entry->eax;
    int32_t month = (int32_t)port_u32(&port, tm, 0x10);
    int32_t index = month % 12;
    uint32_t year = port_u32(&port, tm, 0x14);
    uint32_t table = 0x51c06c;
    uint32_t days;
    uint32_t seconds;
    if ((int32_t)year < (int32_t)0xf4fb7ea1)
    {
        return port_return(&port, 0xffffffff, entry->edx);
    }
    year += (uint32_t)(month / 12);
    while (index < 0)
    {
        index += 12;
        year--;
    }
    if ((int32_t)year < 0)
    {
        return port_return(&port, 0xffffffff, entry->edx);
    }
    if (port_call(&port, 0x4e9060, year + 0x76c, (uint32_t)(month % 12), table, 0xc) != 0)
    {
        table = 0x51c086;
    }
    days = ((year + 3) >> 2) + year * 365;
    days -= (uint32_t)((int32_t)(year + 0x63) / 100);
    days += (uint32_t)((int32_t)(year + 0x12b) / 400);
    days = (uint32_t)(int16_t)port_u16(&port, table, (uint32_t)index * 2) + days +
           port_u32(&port, tm, 0xc) - 1;
    seconds = port_u32(&port, tm, 0) + (port_u32(&port, tm, 4) + port_u32(&port, tm, 8) * 60) * 60;
    while ((int32_t)seconds < 0)
    {
        seconds += 0x15180;
        days--;
    }
    port_call(&port, 0x4e960c, port_call(&port, 0x4e7a00, days, seconds, 0, tm), vertrix_lift_edx,
              0, tm);
    seconds += port_u32(&port, 0x50b0dc, 0);
    if ((int32_t)port_u32(&port, tm, 0x20) < 0)
    {
        port_call(&port, 0x4e91e0, tm, vertrix_lift_edx, port_u32(&port, 0x50b0dc, 0),
                  port_u32(&port, tm, 0x20));
    }
    if ((int32_t)port_u32(&port, tm, 0x20) > 0)
    {
        seconds -= port_u32(&port, 0x50b0e4, 0);
    }
    while ((int32_t)seconds < 0)
    {
        days--;
        seconds += 0x15180;
    }
    if ((int32_t)days < 0x63de)
    {
        return port_return(&port, 0xffffffff, entry->edx);
    }
    if (days == 0x63de)
    {
        seconds -= 0x15180;
        if ((int32_t)port_u32(&port, 0x50b0dc, 0) <= 0 || (int32_t)seconds < 0)
        {
            return port_return(&port, 0xffffffff, entry->edx);
        }
        return port_return(&port, seconds, entry->edx);
    }
    return port_return(&port, seconds + (days - 0x63df) * 0x15180, entry->edx);
}

uint32_t vertrix_port_file_seek(PORT_SIGNATURE)
{
    Port port;
    uint32_t arguments[4];
    uint32_t result;
    uint32_t edx;
    port_open(&port, calls, services, globals, entry);
    arguments[0] = port_u32(&port, entry->eax, 4);
    arguments[1] = entry->edx;
    arguments[2] = 0;
    arguments[3] = entry->ebx;
    result = port_call_stack(&port, 0x4f1ca8, entry->eax, entry->edx, entry->ebx, entry->ecx,
                             arguments, 4);
    edx = vertrix_lift_edx;
    if (result == 0xffffffffu)
    {
        uint32_t error = port_call(&port, 0x4f1bbc, result, edx, result, entry->ecx);
        edx = vertrix_lift_edx;
        arguments[0] = error;
        arguments[1] = 0;
        port_call_stack(&port, 0x4d9930, error, edx, result, entry->ecx, arguments, 2);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_object_clamp_position(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    int32_t x = (int32_t)entry->edx;
    int32_t y = (int32_t)entry->ebx;
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
    port_open(&port, calls, services, globals, entry);
    left = (int32_t)port_u16(&port, object, 0x3c);
    top = (int32_t)port_u16(&port, object, 0x3e);
    right = (int32_t)port_u16(&port, object, 0x40);
    bottom = (int32_t)port_u16(&port, object, 0x42);
    if (x < left)
    {
        x = left;
    }
    else if (x > right)
    {
        x = right;
    }
    if (y < top)
    {
        y = top;
    }
    else if (y > bottom)
    {
        y = bottom;
    }
    port_set16(&port, object, 0x48, (uint32_t)x);
    port_set16(&port, object, 0x4a, (uint32_t)y);
    return port_return(&port, object, (uint32_t)x);
}

uint32_t vertrix_port_file_stream_destroy(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x38,
        GUARD_HANDLER = 0x4ec1ec,
        STREAM_GUARD = 0x519ce0,
        STREAM_TABLE = 0x519f14,
        BASE_TABLE = 0x517454
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t top = entry->esp - BELOW;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t edx = entry->edx;
    uint32_t base;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if (mode & 4)
    {
        /* An array: destroyed element by element (0x4ccb9f with the element destructor). */
        port_set32(&port, top, 0x20, 1);
        port_set32(&port, top, 0, object);
        result = port_call(&port, 0x4ccb9f, object, 0x519f70, mode, object);
        port_set32(&port, top, 0x20, 0);
        port_call(&port, 0x4ca040, result, vertrix_lift_edx, mode, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0, STREAM_TABLE);
    port_set32(&port, top, 0x24, object);
    port_set8(&port, top, 0x28, mode);
    /* The guard record the original links into fs:[0]. */
    port_set32(&port, top, 0x14, port.env.chain);
    port_set32(&port, top, 0x18, GUARD_HANDLER);
    port_set32(&port, top, 0x1c, STREAM_GUARD);
    port_set32(&port, top, 0x20, 4);
    if (port_u32(&port, object, 4) != 0xffffffffu && port_u32(&port, object, 8) != 0)
    {
        port_call(&port, 0x4d7aa0, object, edx, mode, object);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, top, 0x20, 3);
    base = port_call(&port, 0x4ca210, object + 0xc, 0, mode, object) - 0xc;
    edx = vertrix_lift_edx;
    port_set32(&port, top, 0x20, 0);
    port_set32(&port, base, 0, BASE_TABLE);
    if (mode & 2)
    {
        port_call(&port, 0x4ca050, base, edx, mode, base);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, base, edx);
}

uint32_t vertrix_port_thread_slot(PORT_SIGNATURE)
{
    enum
    {
        SLOTS = 0x5c77a8,
        SLOTS_STORAGE = 0x5c7770
    };
    Port port;
    uint32_t key = entry->eax;
    uint32_t make = entry->edx;
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t table;
    uint32_t index;
    uint32_t value = 0;
    uint32_t argument;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, key, 0) == 0)
    {
        if (port_u32(&port, 0, SLOTS) == 0)
        {
            port_set32(&port, 0, SLOTS, port_call(&port, 0x4dbac0, SLOTS_STORAGE, 1, key, ecx));
            edx = vertrix_lift_edx;
        }
        port_set32(&port, key, 0,
                   port_call(&port, 0x4dbb30, port_u32(&port, 0, SLOTS), edx, key, ecx));
        edx = vertrix_lift_edx;
    }
    table = port_u32(&port, 0, SLOTS);
    argument = port_u32(&port, table, 0);
    index = port_u32(&port, key, 0);
    /* The thread's slot array through TlsGetValue: its count at +8, the values at +0xc. */
    table = port_call_stack(&port, 0x4f1cdc, table, edx, key, ecx, &argument, 1);
    edx = vertrix_lift_edx;
    if (table != 0 && (int32_t)index < (int32_t)port_u32(&port, table, 8))
    {
        value = port_u32(&port, port_u32(&port, table, 0xc), index * 4);
    }
    if (value != 0)
    {
        return port_return(&port, value, edx);
    }
    value = port_call(&port, make, 0, edx, key, 0);
    port_call(&port, 0x4dbd20, port_u32(&port, 0, SLOTS), port_u32(&port, key, 0), value, value);
    return port_return(&port, value, vertrix_lift_edx);
}

uint32_t vertrix_port_days_to_tm(PORT_SIGNATURE)
{
    enum
    {
        DAY = 86400,
        LEAP_YEAR = 0x4e9060,
        MONTH_STARTS = 0x51c06c,
        LEAP_MONTH_STARTS = 0x51c086
    };
    Port port;
    uint32_t days = entry->eax;
    uint32_t seconds = entry->edx;
    uint32_t bias = entry->ebx;
    uint32_t tm = entry->ecx;
    uint32_t rest;
    uint32_t years;
    uint32_t yday;
    uint32_t length;
    uint32_t month;
    uint32_t table;
    port_open(&port, calls, services, globals, entry);
    /* The bias (a time zone) may move the time into the previous day. */
    if (seconds < 0xa8c0 && (int32_t)bias > 0)
    {
        seconds = seconds + DAY - bias;
        days += seconds / DAY - 1;
    }
    else
    {
        seconds -= bias;
        days += seconds / DAY;
    }
    rest = seconds % DAY;
    port_set32(&port, tm, 8, rest / 3600);
    rest %= 3600;
    port_set32(&port, tm, 4, rest / 60);
    port_set32(&port, tm, 0, rest % 60);
    /* Years from 1900: a first guess of 366-day years, then whole years of the guessed year's
     * length taken off. */
    years = days / 366;
    yday = days - years * 365;
    if (years != 0)
    {
        yday -= (years - 1) >> 2;
    }
    length = port_call(&port, LEAP_YEAR, years + 1900, years, yday, tm) + 365;
    while (yday >= length)
    {
        yday -= length;
        years++;
    }
    port_set32(&port, tm, 0x14, years);
    port_set32(&port, tm, 0x1c, yday);
    table = port_call(&port, LEAP_YEAR, years + 1900, years, yday, tm) != 0 ? LEAP_MONTH_STARTS
                                                                            : MONTH_STARTS;
    month = yday / 31;
    if (yday >= (uint32_t)((int32_t)port_u32(&port, table, month * 2) >> 16))
    {
        month++;
    }
    port_set32(&port, tm, 0x10, month);
    port_set32(&port, tm, 0xc,
               yday - (uint32_t)(int32_t)(int16_t)port_u16(&port, table, month * 2) + 1);
    port_set32(&port, tm, 0x18, (days + 1) % 7);
    return port_return(&port, tm, (days + 1) % 7);
}

uint32_t vertrix_port_tzset(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xbc,
        ZONE_SET = 0x50b0e8,
        DAYLIGHT = 0x50b0e0,
        DST_BIAS = 0x50b0e4,
        TIMEZONE = 0x50b0dc,
        STANDARD_NAME = 0x50afd0,
        DAYLIGHT_NAME = 0x50b051,
        WIDE_TO_NAME = 0x4ea350,
        PARSE_OFFSET = 0x4e969c,
        PARSE_RULE = 0x4e97b4,
        DST_START = 0x50af88,
        DST_END = 0x50afac
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t text;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    text = port_call(&port, 0x4dac40, 0x513080, entry->edx, ebx, ecx); /* getenv("TZ") */
    edx = vertrix_lift_edx;
    if (text == 0)
    {
        /* From GetTimeZoneInformation (slot 0x4f1bfc), once. */
        uint32_t zone = entry->esp - BELOW;
        uint32_t flags = port_u8(&port, 0, ZONE_SET);
        uint32_t argument = zone;
        uint32_t result;
        if ((flags & 1) && (flags & 2))
        {
            return port_return(&port, flags << 8, entry->edx);
        }
        flags |= 2;
        edx = (edx & 0xffff00ffu) | (flags << 8);
        port_set8(&port, 0, ZONE_SET, flags);
        result = port_call_stack(&port, 0x4f1bfc, zone, edx, ebx, ecx, &argument, 1);
        edx = vertrix_lift_edx;
        if (result == 0 || result > 2)
        {
            return port_return(&port, result, entry->edx);
        }
        if (result == 1)
        {
            ecx = 0;
            port_set32(&port, 0, DAYLIGHT, 0);
        }
        else
        {
            port_set32(&port, 0, DAYLIGHT, 1);
            ebx = port_u32(&port, zone, 0xa8) * 60;
            port_set32(&port, 0, DST_BIAS, ebx);
            ebx = 0 - ebx;
            port_set32(&port, 0, DST_BIAS, ebx);
        }
        port_set32(&port, 0, TIMEZONE,
                   (port_u32(&port, zone, 0x54) + port_u32(&port, zone, 0)) * 60);
        ebx = 0x80;
        result = port_call(&port, WIDE_TO_NAME, STANDARD_NAME, zone + 4, ebx, ecx);
        if (result == 0xffffffffu)
        {
            port_set8(&port, 0, STANDARD_NAME, 0);
        }
        else
        {
            ebx = 0;
            port_set8(&port, 0, STANDARD_NAME + 0x80, 0);
        }
        ebx = 0x80;
        result = port_call(&port, WIDE_TO_NAME, DAYLIGHT_NAME, zone + 0x58, ebx, ecx);
        if (result == 0xffffffffu)
        {
            port_set8(&port, 0, DAYLIGHT_NAME, 0);
        }
        else
        {
            port_set8(&port, 0, DAYLIGHT_NAME + 0x80, 0);
        }
        return port_return(&port, result, entry->edx);
    }
    {
        /* From TZ: the standard name and offset, then an optional daylight name, offset and
         * the two rules. */
        uint32_t local = entry->esp - 0x1c;
        uint32_t rest;
        uint32_t bias;
        port_set32(&port, 0, DAYLIGHT, 0);
        rest = port_call(&port, PARSE_OFFSET, text, STANDARD_NAME, TIMEZONE, ecx);
        ecx = rest;
        if (port_u8(&port, rest, 0) == 0)
        {
            port_set8(&port, 0, DAYLIGHT_NAME, 0);
            port_set32(&port, 0, DST_BIAS, port_u32(&port, 0, DST_BIAS));
            return port_return(&port, rest & 0xffff00ffu, entry->edx);
        }
        port_set32(&port, 0, DAYLIGHT, 1);
        port_set32(&port, local, 0, port_u32(&port, 0, TIMEZONE) - 3600);
        eax = port_call(&port, PARSE_OFFSET, rest, DAYLIGHT_NAME, local, rest);
        ecx = port_u32(&port, local, 0);
        bias = port_u32(&port, 0, TIMEZONE) - ecx;
        edx = eax;
        ebx = (local & 0xffffff00u) | port_u8(&port, eax, 0);
        port_set32(&port, 0, DST_BIAS, bias);
        if ((ebx & 0xff) == ',')
        {
            eax = port_call(&port, PARSE_RULE, eax + 1, DST_START, ebx, ecx);
            edx = eax;
        }
        ebx = (ebx & 0xffff00ffu) | (port_u8(&port, edx, 0) << 8);
        bias = port_u32(&port, 0, DST_BIAS);
        if (((ebx >> 8) & 0xff) == ',')
        {
            int32_t seconds;
            port_call(&port, PARSE_RULE, edx + 1, DST_END, ebx, ecx);
            bias = port_u32(&port, 0, DST_BIAS);
            seconds = (int32_t)bias;
            /* The end rule's time moves back by the daylight bias. */
            port_set32(&port, 0, DST_END + 8,
                       port_u32(&port, 0, DST_END + 8) - (uint32_t)(seconds / 3600));
            port_set32(&port, 0, DST_END + 4,
                       port_u32(&port, 0, DST_END + 4) - (uint32_t)((seconds / 60) % 60));
            eax = port_u32(&port, 0, DST_END) - (uint32_t)(seconds % 60);
            port_set32(&port, 0, DST_END, eax);
        }
        port_set32(&port, 0, DST_BIAS, bias);
        return port_return(&port, eax, entry->edx);
    }
}

/* The month table word for 0x4e91e0: the leap or common year's month starts. */
static int32_t dst_month_start(Port *port, int leap, uint32_t month)
{
    return (int32_t)port_u32(port, 0, (leap ? 0x51c084 : 0x51c06a) + month * 2) >> 16;
}

/* Whether the time is past (`start`) or before the rule's day, as far as the day decides:
 * 1 past it, 0 not, -1 on the day itself (the time of day decides). */
static int dst_rule_day(Port *port, uint32_t tm, uint32_t rule, uint32_t month, int32_t length,
                        uint32_t *edx, uint32_t second, int start)
{
    uint32_t kind = port_u32(port, rule, 0x20);
    if (kind == 0)
    {
        /* The nth (5: last) given weekday of a month. */
        int32_t rule_month = (int32_t)port_u32(port, rule, 0x10);
        int32_t weekday = (int32_t)port_u32(port, tm, 0x18);
        int32_t mday = (int32_t)port_u32(port, tm, 0xc);
        int32_t rule_weekday = (int32_t)port_u32(port, rule, 0x18);
        int32_t after;
        int32_t before;
        int32_t day;
        if ((int32_t)month != rule_month)
        {
            return ((int32_t)month > rule_month) == start;
        }
        after = mday - (weekday + 7 - rule_weekday) % 7;
        before = mday - 1 - (weekday + 6 - rule_weekday) % 7;
        if (port_u32(port, rule, 0xc) == 5)
        {
            day = length - 7;
            if (start)
            {
                return day >= after ? 0 : day < before ? 1 : -1;
            }
            return after <= day ? 1 : before > day ? 0 : -1;
        }
        day = (int32_t)(port_u32(port, rule, 0xc) - 1) * 7 + 1;
        if (start)
        {
            return day > after ? 0 : day <= before ? 1 : -1;
        }
        return after < day ? 1 : before < day ? 0 : -1;
    }
    {
        /* A day of the year; kind 1 counts February 29th only in leap years. */
        int32_t day = (int32_t)port_u32(port, rule, 0x1c);
        int32_t yday;
        if (kind == 1)
        {
            if (start)
            {
                *edx = (uint32_t)day;
            }
            if (port_call(port, 0x4e9060, port_u32(port, tm, 0x14) + 1900, *edx, second, tm) != 0 &&
                day > ((int32_t)port_u32(port, 0, 0x51c06e) >> 16))
            {
                day++;
            }
            day--;
        }
        yday = (int32_t)port_u32(port, tm, 0x1c);
        if (start)
        {
            return day > yday ? 0 : day == yday ? -1 : 1;
        }
        return day > yday ? 1 : day == yday ? -1 : 0;
    }
}

uint32_t vertrix_port_is_dst(PORT_SIGNATURE)
{
    enum
    {
        DST_START = 0x50af88,
        DST_END = 0x50afac
    };
    Port port;
    uint32_t tm = entry->eax;
    uint32_t edx;
    uint32_t south;
    uint32_t first;
    uint32_t second;
    uint32_t month;
    int32_t length;
    int leap;
    int day;
    uint32_t result = 0;
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, port_u32(&port, 0, 0x50b0d8), 0) == 0)
    {
        port_set32(&port, tm, 0x20, 0);
        return port_return(&port, 0, entry->edx);
    }
    /* A southern zone (0x4e9194: the end before the start) checks the reverse period. */
    south = port_call(&port, 0x4e9194, DST_START, DST_END, port_u32(&port, tm, 0x14), tm);
    edx = vertrix_lift_edx;
    first = south != 0 ? DST_END : DST_START;
    second = south != 0 ? DST_START : DST_END;
    month = port_u32(&port, tm, 0x10);
    leap = port_call(&port, 0x4e9060, port_u32(&port, tm, 0x14) + 1900, edx, second, tm) != 0;
    edx = vertrix_lift_edx;
    length = dst_month_start(&port, leap, month + 1) - dst_month_start(&port, leap, month);
    day = dst_rule_day(&port, tm, first, month, length, &edx, second, 1);
    if (day < 0)
    {
        /* On the day: 0x4e949c compares the time with the rule's. */
        result = port_call(&port, 0x4e949c, tm, first, second, tm) == 0;
    }
    else
    {
        result = (uint32_t)day;
    }
    if (result == 0)
    {
        result = south;
        port_set32(&port, tm, 0x20, result);
        return port_return(&port, result, entry->edx);
    }
    edx = 0;
    day = dst_rule_day(&port, tm, second, month, length, &edx, second, 0);
    if (day < 0)
    {
        result = port_call(&port, 0x4e949c, tm, second, second, tm);
    }
    else
    {
        result = (uint32_t)day;
    }
    if (south != 0)
    {
        result = south - result;
    }
    port_set32(&port, tm, 0x20, result);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_find_succeeded(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x124,
        FIND_DATA = 0x120 /* below ebp */
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t arguments[2];
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    arguments[0] = entry->eax;
    arguments[1] = ebp - FIND_DATA;
    result = port_call_stack(&port, 0x4d9060, entry->eax, ebp - FIND_DATA, entry->ebx, entry->ecx,
                             arguments, 2);
    return port_return(&port, result == 1, entry->edx);
}

uint32_t vertrix_port_scene_refresh(PORT_SIGNATURE)
{
    enum
    {
        SCREEN = 0x5b9c50
    };
    Port port;
    uint32_t scene = entry->eax;
    uint32_t ecx = entry->ebx;
    uint32_t ebx = entry->ebx;
    uint32_t edx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x41aaf0, scene, entry->edx, ebx, ecx);
    port_call(&port, 0x486d00, SCREEN, vertrix_lift_edx, ebx, ecx);
    ebx = vertrix_lift_edx;
    port_call(&port, 0x41a2f0, scene, port_u32(&port, 0, 0x558c7c), ebx, ecx);
    edx = vertrix_lift_edx;
    port_call(&port, 0x486da0, SCREEN, edx, ebx, ecx);
    eax = port_call(&port, 0x487020, SCREEN, vertrix_lift_edx, ebx, ecx);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_scratch_triple(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t pair = entry->esp - 8;
    uint32_t scratch = entry->esp - BELOW;
    uint32_t arguments[3];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    /* The argument pair is pushed, converted into a 12-byte temporary and back. */
    port_set32(&port, pair, 4, entry->edx);
    port_set32(&port, pair, 0, entry->eax);
    port_call(&port, 0x4e53b4, pair, scratch, entry->ebx, entry->ecx);
    port_call(&port, 0x4db131, scratch, vertrix_lift_edx, entry->ebx, entry->ecx);
    arguments[0] = port_u32(&port, scratch, 0);
    arguments[1] = port_u32(&port, scratch, 4);
    arguments[2] = port_u32(&port, scratch, 8);
    port_call_stack(&port, 0x4e543c, scratch, pair, entry->ebx, entry->ecx, arguments, 3);
    return port_return(&port, port_u32(&port, pair, 0), port_u32(&port, pair, 4));
}

/* The Windows error after a failed call, recorded by 0x4d9930 (GetLastError, slot 0x4f1bbc). */
static uint32_t file_error(Port *port, uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx)
{
    uint32_t arguments[2];
    uint32_t error = port_call(port, 0x4f1bbc, eax, edx, ebx, ecx);
    arguments[0] = error;
    arguments[1] = 0;
    return port_call_stack(port, 0x4d9930, error, vertrix_lift_edx, ebx, ecx, arguments, 2);
}

uint32_t vertrix_port_file_close(PORT_SIGNATURE)
{
    Port port;
    uint32_t file = entry->eax;
    uint32_t edx = 0;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, file, 4) != 0xffffffffu)
    {
        /* CloseHandle (slot 0x4f1b2c); edx notes a failure. */
        uint32_t argument = port_u32(&port, file, 4);
        edx = port_call_stack(&port, 0x4f1b2c, file, 0, file, entry->ecx, &argument, 1) == 0;
    }
    port_set32(&port, file, 4, 0xffffffffu);
    port_set32(&port, file, 8, 0);
    eax = port_call(&port, 0x4ca180, file + 0xc, edx, file, entry->ecx);
    if (vertrix_lift_edx != 0)
    {
        eax = file_error(&port, eax, vertrix_lift_edx, file, entry->ecx);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_file_transfer(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 8];
    uint32_t done = entry->esp - 8;
    uint32_t arguments[5];
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, 8);
    if (entry->ebx == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    /* ReadFile or WriteFile (slot 0x4f1c78) on the handle +4: the count done is returned. */
    arguments[0] = port_u32(&port, entry->eax, 4);
    arguments[1] = entry->edx;
    arguments[2] = entry->ebx;
    arguments[3] = done;
    arguments[4] = 0;
    if (port_call_stack(&port, 0x4f1c78, entry->eax, entry->edx, entry->ebx, done, arguments, 5) ==
        0)
    {
        file_error(&port, 0, vertrix_lift_edx, entry->ebx, done);
    }
    edx = vertrix_lift_edx;
    return port_return(&port, port_u32(&port, done, 0), edx);
}

uint32_t vertrix_port_thread_value(PORT_SIGNATURE)
{
    Port port;
    uint32_t slots = entry->eax;
    uint32_t index = entry->edx;
    uint32_t array;
    uint32_t eax;
    uint32_t value = 0;
    uint32_t argument;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, slots, 0) == 0xffffffffu)
    {
        /* Without a TLS index the array at +4 is shared, under the critical section +0x20. */
        argument = slots + 0x20;
        port_call_stack(&port, 0x4f1b48, slots + 0x20, index, slots, entry->ecx, &argument, 1);
        array = port_u32(&port, slots, 4);
    }
    else
    {
        argument = port_u32(&port, slots, 0);
        array = port_call_stack(&port, 0x4f1cdc, slots, index, slots, entry->ecx, &argument, 1);
    }
    eax = array;
    if (array != 0 && (int32_t)index < (int32_t)port_u32(&port, array, 8))
    {
        eax = port_u32(&port, array, 0xc);
        value = port_u32(&port, eax, index * 4);
    }
    if (port_u32(&port, slots, 0) == 0xffffffffu)
    {
        argument = slots + 0x20;
        port_call_stack(&port, 0x4f1c40, eax, vertrix_lift_edx, slots + 0x20, entry->ecx, &argument,
                        1);
    }
    return port_return(&port, value, vertrix_lift_edx);
}

uint32_t vertrix_port_object_construct_e(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x4c,
        GUARD_HANDLER = 0x4ec1ec,
        OBJECT_GUARD = 0x517008,
        TEMPORARY = 0x30 /* below ebp */
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t constructed;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x44u, port.env.chain);
    port_set32(&port, ebp, -0x40u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x3cu, OBJECT_GUARD);
    port_set32(&port, ebp, -0x38u, 0);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, object);
    /* The base constructor 0x4d7510, then the class's table; a temporary of the base class is
     * made and destroyed (0x4d7630). */
    constructed = port_call(&port, 0x4d7510, object, object, OBJECT_GUARD, GUARD_HANDLER);
    port_set32(&port, ebp, -0x38u, 1);
    port_set32(&port, constructed, 0, 0x5174b4);
    port_call(&port, 0x4d7510, ebp - TEMPORARY, 0, OBJECT_GUARD, constructed);
    port_set32(&port, ebp, -0x38u, 1);
    port_call(&port, 0x4d7630, ebp - TEMPORARY, vertrix_lift_edx, OBJECT_GUARD, constructed);
    port_set32(&port, ebp, -0x38u, 1);
    return port_return(&port, constructed, entry->edx);
}

uint32_t vertrix_port_grid_cell_call(PORT_SIGNATURE)
{
    enum
    {
        GRID = 0x544f90
    };
    Port port;
    uint8_t stack[0xc + 8 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t cell;
    uint32_t argument;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0xc, 2);
    /* Rows of 0x118 bytes, cells of 0x1c. */
    cell = GRID + entry->eax * 0x118 + entry->edx * 0x1c;
    argument = port_u32(&port, ebp, 0xc);
    return port_return(&port,
                       port_call_stack(&port, 0x487750, cell, entry->ebx, entry->ecx,
                                       port_u32(&port, ebp, 8), &argument, 1),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_point_distance(PORT_SIGNATURE)
{
    enum
    {
        DX = 0x598dc0,
        DY = 0x598dc4,
        GUESS = 0x598dc8,
        NEXT = 0x598dcc,
        CHANGE = 0x598dd0,
        SQUARE = 0x598dd4
    };
    Port port;
    int32_t dx = (int16_t)entry->ebx - (int16_t)entry->eax;
    int32_t dy = (int16_t)entry->ecx - (int16_t)entry->edx;
    uint32_t square;
    uint32_t guess = 1;
    uint32_t next;
    int32_t change;
    port_open(&port, calls, services, globals, entry);
    port_set32(&port, 0, DY, (uint32_t)dy);
    square = (uint32_t)dx * (uint32_t)dx + (uint32_t)dy * (uint32_t)dy;
    port_set32(&port, 0, DX, (uint32_t)dx);
    port_set32(&port, 0, SQUARE, square);
    /* Newton's method for the integer square root, from 1. */
    do
    {
        next = (port_u32(&port, 0, SQUARE) / guess + guess) >> 1;
        port_set32(&port, 0, GUESS, guess);
        change = (int32_t)(next - guess);
        port_set32(&port, 0, NEXT, next);
        port_set32(&port, 0, CHANGE, (uint32_t)(change < 0 ? -change : change));
        guess = next;
    } while ((int32_t)port_u32(&port, 0, CHANGE) > 1);
    port_set32(&port, 0, GUESS, next);
    return port_return(&port, next, change < 0 ? 0xffffffffu : 0);
}

uint32_t vertrix_port_local_time(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t time = entry->esp - BELOW; /* SYSTEMTIME */
    uint32_t tm = entry->eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_call_stack(&port, 0x4f1bc0, time, entry->edx, tm, entry->ecx, &time, 1);
    port_set32(&port, tm, 0x14, port_u16(&port, time, 0) - 1900);
    port_set32(&port, tm, 0x10, port_u16(&port, time, 2) - 1);
    port_set32(&port, tm, 0xc, port_u16(&port, time, 6));
    port_set32(&port, tm, 8, port_u16(&port, time, 8));
    port_set32(&port, tm, 4, port_u16(&port, time, 0xa));
    port_set32(&port, tm, 0x20, 0xffffffffu);
    port_set32(&port, tm, 0, port_u16(&port, time, 0xc));
    return port_return(&port, port_u16(&port, time, 0xe), entry->edx);
}

uint32_t vertrix_port_runtime_lock(PORT_SIGNATURE)
{
    enum
    {
        LOCKS_MADE = 0x5c79d0,
        SINGLE_THREAD = 0x5c79d4,
        LOCKS = 0x5c79d8, /* CRITICAL_SECTIONs of 0x18 bytes */
        LOCK_READY = 0x5c7b40,
        LOCK_GUARD = 0x5c7b28,
        ENTER = 0x4f1b48,
        INITIALIZE = 0x4f1c30,
        LEAVE = 0x4f1c40
    };
    Port port;
    uint8_t stack[4 + 8 + 4];
    uint32_t number;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t index;
    uint32_t section;
    uint32_t argument;
    port_open_arguments(&port, stack, calls, services, globals, entry, 4, 1);
    number = port_u32(&port, entry->esp, 4);
    if (port_u32(&port, 0, LOCKS_MADE) == 0)
    {
        eax = port_call(&port, 0x4de970, eax, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    if (port_u32(&port, 0, SINGLE_THREAD) != 0)
    {
        return port_return(&port, eax, edx);
    }
    index = number * 4;
    section = number * 0x18 + LOCKS;
    if (port_u32(&port, index, LOCK_READY) == 0)
    {
        /* Made on first use, under the guard lock. */
        argument = LOCK_GUARD;
        eax = port_call_stack(&port, ENTER, eax, edx, index, entry->ecx, &argument, 1);
        edx = vertrix_lift_edx;
        if (port_u32(&port, index, LOCK_READY) == 0)
        {
            argument = section;
            eax = port_call_stack(&port, INITIALIZE, section, edx, index, entry->ecx, &argument, 1);
            edx = vertrix_lift_edx;
            port_set32(&port, index, LOCK_READY, port_u32(&port, index, LOCK_READY) + 1);
        }
        argument = LOCK_GUARD;
        eax = port_call_stack(&port, LEAVE, eax, edx, index, entry->ecx, &argument, 1);
        edx = vertrix_lift_edx;
    }
    argument = section;
    eax = port_call_stack(&port, ENTER, eax, edx, section, entry->ecx, &argument, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_construct_array(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c,
        GUARD_HANDLER = 0x4ec1ec,
        ARRAY_GUARD = 0x518f20
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t top = entry->esp - BELOW;
    uint32_t array = entry->eax;
    uint32_t type = entry->ebx;
    uint32_t edx = entry->edx;
    uint32_t constructor;
    uint32_t size;
    uint32_t element = entry->eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, top, 0, port.env.chain);
    port_set32(&port, top, 4, GUARD_HANDLER);
    port_set32(&port, top, 8, ARRAY_GUARD);
    port_set32(&port, top, 0xc, 0);
    port_set32(&port, top, 0x14, 1);
    port_set32(&port, top, 0x18, 0);
    port_set32(&port, top, 0x1c, type);
    port_set32(&port, top, 0x20, array);
    port_set32(&port, top, 0xc, 1);
    constructor = port_u32(&port, type, 4);
    size = port_u32(&port, type, 0x10);
    /* The type's constructor (+4) on each element of its size (+0x10). */
    while (edx > port_u32(&port, top, 0x18))
    {
        port_call(&port, constructor, element, edx, constructor, element);
        edx = vertrix_lift_edx;
        port_set32(&port, top, 0x18, port_u32(&port, top, 0x18) + 1);
        element += size;
    }
    port_set32(&port, top, 0x14, 0);
    port_set32(&port, top, 0xc, 0);
    port_call(&port, 0x4ce9fd, top + 0x14, 0, constructor, port_u32(&port, top, 0x20));
    port_set32(&port, top, 0xc, 0);
    return port_return(&port, port_u32(&port, top, 0x20), vertrix_lift_edx);
}

uint32_t vertrix_port_object_pair_update(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t first;
    uint32_t second;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    first = port_call(&port, 0x4877f0, object, entry->ebx, entry->ebx, object);
    if (first == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    second = port_call(&port, 0x4877f0, object, entry->edx, first, object);
    if (second != 0)
    {
        port_call(&port, 0x4830f0, second, vertrix_lift_edx, first, object);
    }
    value = port_call(&port, 0x483110, first, vertrix_lift_edx, first, object);
    return port_return(&port, port_call(&port, 0x487850, object, entry->edx, value, object),
                       vertrix_lift_edx);
}

uint32_t vertrix_port_object_destroy_h(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c,
        GUARD_HANDLER = 0x4ec1ec,
        OBJECT_GUARD = 0x517650
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if (mode & 4)
    {
        /* An array: element destructor 0x513310, freed by 0x4ca040. */
        uint32_t result;
        port_set32(&port, ebp, -0x34u, object);
        port_set32(&port, ebp, -0x14u, 1);
        result = port_call(&port, 0x4ccb9f, object, 0x513310, entry->ebx, object);
        port_set32(&port, ebp, -0x14u, 0);
        port_call(&port, 0x4ca040, result, 0, entry->ebx, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0x110, 0x517684);
    port_set32(&port, ebp, -0x20u, port.env.chain);
    port_set32(&port, ebp, -0x1cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x18u, OBJECT_GUARD);
    port_set32(&port, ebp, -0x14u, 0);
    port_call(&port, 0x48a8c0, object, mode, GUARD_HANDLER, object);
    edx = vertrix_lift_edx;
    if (edx & 2)
    {
        port_call(&port, 0x4ca050, object, edx, GUARD_HANDLER, object);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, object, edx);
}

uint32_t vertrix_port_effect_construct(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c,
        GUARD_HANDLER = 0x4ec1ec,
        EFFECT_GUARD = 0x5164a8
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t owner = entry->eax;
    uint32_t base;
    uint32_t effect;
    uint32_t offset;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x2cu, EFFECT_GUARD);
    port_set32(&port, ebp, -0x20u, owner);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x28u, 0);
    base = port_call(&port, 0x4756d0, owner + 4, owner, EFFECT_GUARD, GUARD_HANDLER);
    port_set32(&port, ebp, -0x28u, 1);
    base = port_call(&port, 0x4d8340, base + 0x1c, 0xa, EFFECT_GUARD, GUARD_HANDLER);
    effect = base - 0x20;
    port_set32(&port, base, 0, 0x5165f4);
    port_set32(&port, ebp, -0x28u, 2);
    port_set32(&port, effect, 0x5c, 0x5165d4);
    port_set8(&port, effect, 0, 0);
    port_set8(&port, effect, 0x5a, 0);
    port_set16(&port, effect, 0x58, 0);
    for (offset = 0x44; offset <= 0x54; offset += 4)
    {
        port_set32(&port, effect, offset, 0);
    }
    port_set32(&port, effect, 0x40, port_u32(&port, 0, 0x553644));
    port_set32(&port, effect, 0x3c, port_u32(&port, 0, 0x553644));
    return port_return(&port, effect, entry->edx);
}

uint32_t vertrix_port_sprite_bank_load(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18,
        NAMES = 0x5410f8,
        SPRITES = 0x5410f4
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t count = entry->ebx;
    uint32_t loaded;
    uint32_t eax;
    uint32_t edx;
    uint32_t done;
    uint32_t slot;
    uint32_t name;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0xcu, count);
    loaded = port_call(&port, 0x4877f0, 0x546538, entry->ecx, count, entry->ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x10u, loaded);
    eax = loaded;
    if (loaded == 0 || count == 0)
    {
        return port_return(&port, eax, edx);
    }
    /* Each name from 0x5410f8 (from the first) gives the sprite stored at 0x5410f8 (from the
     * index), with 0x418270 between them. */
    slot = entry->eax * 4;
    name = entry->edx * 4;
    for (done = 0; done < count; done++)
    {
        eax = port_call(&port, 0x4831b0, port_u32(&port, name, NAMES), loaded,
                        port_u32(&port, ebp, 8), slot);
        edx = vertrix_lift_edx;
        slot += 4;
        name += 4;
        port_set32(&port, slot, SPRITES, eax);
        eax = port_call(&port, 0x418270, 2, edx, count, slot);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_error_construct(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24,
        GUARD_HANDLER = 0x4ec1ec
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp;
    uint32_t object = entry->eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, -0x24u, port.env.chain);
    port_set32(&port, esp, -0x20u, GUARD_HANDLER);
    port_set32(&port, esp, -0x1cu, 0x51a350);
    port_set32(&port, esp, -0x18u, 0);
    port_set8(&port, esp, -0xcu, 0);
    port_set32(&port, esp, -0x10u, object);
    port_set32(&port, object, 0, 0x517454);
    port_set32(&port, esp, -0x18u, 1);
    port_set32(&port, object, 0, 0x517474);
    port_set32(&port, object, 4, entry->edx);
    return port_return(&port, object, entry->edx);
}

uint32_t vertrix_port_zero_dwords(PORT_SIGNATURE)
{
    Port port;
    uint32_t at = entry->eax;
    uint32_t end;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0)
    {
        return port_return(&port, at, 0);
    }
    end = entry->edx * 4 + at;
    do
    {
        port_set32(&port, at, 0, 0);
        at += 4;
    } while (at < end);
    return port_return(&port, at, end);
}

uint32_t vertrix_port_string_assign_text(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, 0x10);
    /* A text gives its length (strlen import) to 0x4ca5a0. */
    if (edx != 0)
    {
        uint32_t text = entry->edx;
        edx = port_call_stack(&port, 0x4f1d24, entry->eax, edx, edx, entry->ecx, &text, 1);
    }
    port_call(&port, 0x4ca5a0, entry->eax, edx, entry->edx, entry->ecx);
    return port_return(&port, entry->eax, vertrix_lift_edx);
}

uint32_t vertrix_port_player_refresh(PORT_SIGNATURE)
{
    Port port;
    uint32_t player = entry->eax;
    uint32_t value;
    uint32_t eax;
    uint32_t ecx;
    port_open(&port, calls, services, globals, entry);
    value = port_call(&port, 0x4182c0, player, entry->edx, entry->ebx, entry->ecx);
    ecx = port_u32(&port, 0, 0x540048);
    port_call(&port, 0x41a2f0, player, port_u32(&port, port_u32(&port, 0, 0x544070), 0x268), value,
              ecx);
    port_call(&port, 0x41ab90, player, vertrix_lift_edx, value, ecx);
    eax = port_call(&port, 0x41a9e0, player, vertrix_lift_edx, value, ecx);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_block_chain_new(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 3 * 4];
    uint32_t esp = entry->esp;
    uint32_t chain;
    uint32_t block;
    uint32_t next;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 3);
    chain = port_u32(&port, esp, 4);
    /* A block of count * size bytes after a link, pushed onto the chain. */
    block = port_call(&port, 0x4c9ff0, port_u32(&port, esp, 8) * port_u32(&port, esp, 0xc) + 4,
                      entry->edx, entry->ebx, chain);
    next = port_u32(&port, chain, 0);
    port_set32(&port, block, 0, next);
    port_set32(&port, chain, 0, block);
    return port_return(&port, block, next);
}

uint32_t vertrix_port_lock_construct(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t inner = lock + 0x20;
    port_open_frame(&port, calls, services, globals, entry, 0x10);
    port_set32(&port, lock + 0x18, 4, 4);
    port_set32(&port, lock + 0x18, 0, 0);
    port_set32(&port, lock, 8, 0);
    port_set32(&port, lock, 0xc, 1);
    port_set32(&port, lock, 0x10, 0);
    port_set32(&port, lock, 0x14, 0);
    port_set32(&port, lock, 4, 0);
    if (edx != 0)
    {
        /* A named lock opens its event (import 0x4f1cd4); -1 is an error (0x4d9510). */
        uint32_t handle = port_call(&port, 0x4f1cd4, lock + 0x18, edx, lock, entry->ecx);
        edx = vertrix_lift_edx;
        port_set32(&port, lock, 0, handle);
        if (handle == 0xffffffffu)
        {
            port_call(&port, 0x4d9510, handle, edx, lock, entry->ecx);
            edx = vertrix_lift_edx;
        }
    }
    else
    {
        port_set32(&port, lock, 0, 0xffffffffu);
    }
    port_call_stack(&port, 0x4f1c30, inner, edx, lock, entry->ecx, &inner, 1);
    return port_return(&port, lock, vertrix_lift_edx);
}

/* 0x4d84f0's release with the page free `free`. */
static uint32_t pool_release_with(PORT_SIGNATURE, uint32_t free)
{
    Port port;
    uint32_t pool = entry->eax;
    uint32_t item = entry->edx;
    uint32_t eax = pool;
    uint32_t edx = item;
    uint32_t used;
    uint32_t head;
    port_open(&port, calls, services, globals, entry);
    /* The item goes back on the free list (+0x10); the last one in use frees the page. */
    head = port_u32(&port, pool, 0x10);
    port_set32(&port, item, 0, head);
    port_set32(&port, pool, 0x10, item);
    used = port_u32(&port, pool, 0xc) - 1;
    port_set32(&port, pool, 0xc, used);
    if (used == 0)
    {
        eax = port_call(&port, free, pool, item, entry->ebx, head);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_pool_release(PORT_SIGNATURE)
{
    return pool_release_with(calls, services, globals, entry, 0x4d83c0);
}

uint32_t vertrix_port_pool_release_4df0d0(PORT_SIGNATURE)
{
    return pool_release_with(calls, services, globals, entry, 0x4def90);
}

uint32_t vertrix_port_guarded_call_pair(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28,
        GUARD_HANDLER = 0x4ec1ec
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp;
    uint32_t object = entry->eax;
    uint32_t record = esp - 0x14;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, -0x28u, port.env.chain);
    port_set32(&port, esp, -0x24u, GUARD_HANDLER);
    port_set32(&port, esp, -0x20u, 0x519460);
    port_set32(&port, esp, -0x1cu, 0);
    port_set32(&port, esp, -0x14u, 1);
    port_set32(&port, esp, -0x10u, entry->edx);
    port_set32(&port, esp, -0xcu, entry->ebx);
    port_set32(&port, esp, -8u, object);
    port_set32(&port, esp, -0x1cu, 1);
    port_call(&port, 0x4ce9c0, record, entry->edx, entry->ebx, object);
    port_set32(&port, esp, -0x1cu, 0);
    port_call(&port, 0x4ce9fd, record, 0, entry->ebx, object);
    port_set32(&port, esp, -0x1cu, 0);
    return port_return(&port, object, vertrix_lift_edx);
}

uint32_t vertrix_port_array_destroy_elements(PORT_SIGNATURE)
{
    Port port;
    uint32_t array = entry->eax;
    uint32_t type;
    uint32_t size;
    uint32_t destructor;
    uint32_t element;
    uint32_t left;
    port_open(&port, calls, services, globals, entry);
    type = port_u32(&port, array, 8);
    size = port_u32(&port, type, 0x10);
    element = port_u32(&port, array, 4) * size + port_u32(&port, array, 0xc);
    destructor = port_u32(&port, type, 0xc);
    /* The elements are destroyed last first, the count (+4) kept current. */
    while ((left = port_u32(&port, array, 4)) != 0)
    {
        element -= size;
        port_set32(&port, array, 4, left - 1);
        port_call(&port, destructor, element, 0, element, array);
    }
    port_set32(&port, array, 0, 0);
    return port_return(&port, port_u32(&port, array, 0xc), entry->edx);
}

uint32_t vertrix_port_object_record_new(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    record = port_call(&port, 0x4ec160, 1, 0x1c, entry->ebx, entry->eax);
    port_set32(&port, record, 0, entry->eax);
    port_set32(&port, record, 4, entry->edx);
    port_set32(&port, record, 8, entry->ebx);
    port_set8(&port, record, 0xc, port_u8(&port, 0, 0x5b9ca6));
    return port_return(&port, record, vertrix_lift_edx);
}

uint32_t vertrix_port_thread_set_flag(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 2 * 4];
    uint32_t data;
    uint32_t flag;
    uint32_t edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 2);
    data = port_call(&port, 0x4ce740, entry->eax, entry->edx, entry->ebx, entry->ecx);
    flag = port_u8(&port, entry->esp, 4);
    edx = (vertrix_lift_edx & 0xffffff00u) | flag;
    port_set8(&port, data, 0x14, flag);
    if (port_u32(&port, entry->esp, 4) == 0)
    {
        port_call(&port, 0x4ecb50, 0xfffffffdu, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, 1, edx);
}

uint32_t vertrix_port_exit_list_init(PORT_SIGNATURE)
{
    enum
    {
        LOCK = 0x50817e,
        HEAD = 0x50818e,
        ENTRY = 0x50b3c0
    };
    Port port;
    uint32_t kept;
    uint32_t link;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, 8);
    port_call(&port, 0x4ec940, 0x5c8ae0, entry->edx, entry->ebx, entry->ecx);
    kept = vertrix_lift_edx;
    /* The entry is pushed on the list at 0x50818e under its lock. */
    port_call(&port, 0x4e14b0, LOCK, ENTRY, entry->ebx, entry->ecx);
    link = vertrix_lift_edx;
    port_set32(&port, link, 0, port_u32(&port, 0, HEAD));
    port_set32(&port, 0, HEAD, link);
    eax = port_call(&port, 0x4e14b7, LOCK, link, entry->ebx, entry->ecx);
    return port_return(&port, eax, kept);
}

uint32_t vertrix_port_console_handles(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t which;
    port_open_frame(&port, calls, services, globals, entry, 4);
    if (port_u32(&port, 0, 0x5c79bc) != 0)
    {
        /* The output and error handles (import 0x4f19e4 with 2 and 3), each plus one. */
        which = 2;
        eax = port_call_stack(&port, 0x4f19e4, eax, edx, entry->ebx, entry->ecx, &which, 1) + 1;
        edx = vertrix_lift_edx;
        port_set32(&port, 0, 0x5c7944, eax);
        which = 3;
        eax = port_call_stack(&port, 0x4f19e4, eax, edx, entry->ebx, entry->ecx, &which, 1) + 1;
        edx = vertrix_lift_edx;
        port_set32(&port, 0, 0x5c79cc, 1);
        port_set32(&port, 0, 0x5c7948, eax);
    }
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_runtime_version_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx = entry->edx;
    port_open_frame(&port, calls, services, globals, entry, 4);
    if (port_u32(&port, 0, 0x5c79d0) == 0)
    {
        uint32_t version;
        uint32_t old;
        port_set32(&port, 0, 0x5c79d0, port_u32(&port, 0, 0x5c79d0) + 1);
        version = port_call(&port, 0x4f1c00, entry->eax, entry->edx, entry->ebx, entry->ecx);
        edx = version & 0xff;
        /* A Win32s or Windows 9x system (high bit, major version under 4) has no section. */
        old = (int32_t)edx < 4 && (version & 0x80000000u) != 0;
        port_set32(&port, 0, 0x5c79d4, old);
        if (!old)
        {
            uint32_t section = 0x5c7b28;
            port_call_stack(&port, 0x4f1c30, 0, edx, entry->ebx, entry->ecx, &section, 1);
            edx = vertrix_lift_edx;
        }
    }
    return port_return(&port, port_u32(&port, 0, 0x5c79d0), edx);
}

/* 0x4ccdd0's shape with the import `import` and the method `method`. */
static uint32_t stream_flush_with(PORT_SIGNATURE, uint32_t import, uint32_t method)
{
    Port port;
    uint32_t stream = entry->eax;
    uint32_t inner;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, 0xc);
    inner = port_u32(&port, stream, 0x38);
    if (inner == 0)
    {
        uint32_t arguments[2];
        arguments[0] = port_u32(&port, stream, 0x1c);
        arguments[1] = entry->edx;
        eax = port_call_stack(&port, import, stream, entry->edx, entry->ebx, entry->ecx, arguments,
                              2);
    }
    else
    {
        uint32_t table = port_u32(&port, inner, 0);
        eax =
            port_call(&port, port_u32(&port, table, method), inner, entry->edx, entry->ebx, table);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_stream_flush_handle(PORT_SIGNATURE)
{
    return stream_flush_with(calls, services, globals, entry, 0x4f1af0, 0xa4);
}

uint32_t vertrix_port_stream_flush_4cce30(PORT_SIGNATURE)
{
    return stream_flush_with(calls, services, globals, entry, 0x4f1948, 0xac);
}

uint32_t vertrix_port_stream_init_derived(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24,
        GUARD_HANDLER = 0x4ec1ec
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp;
    uint32_t object = entry->eax;
    uint32_t stream;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, -0x24u, port.env.chain);
    port_set32(&port, esp, -0x20u, GUARD_HANDLER);
    port_set32(&port, esp, -0x1cu, 0x518d8c);
    port_set32(&port, esp, -0x18u, 0);
    port_set8(&port, esp, -0xcu, 0);
    port_set32(&port, esp, -0x10u, object);
    stream = port_call(&port, 0x4cb460, object, object, entry->ebx, entry->ecx);
    port_set32(&port, esp, -0x18u, 1);
    port_set32(&port, stream, 0, 0x518e24);
    port_set32(&port, stream, 0x4c, 0);
    port_set32(&port, stream, 0x50, 0);
    port_call(&port, 0x4cbf90, stream, stream, entry->ebx, entry->ecx);
    return port_return(&port, vertrix_lift_edx, entry->edx);
}

uint32_t vertrix_port_object_reset_block(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t eax;
    uint32_t offset;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, object, 0xc, 0);
    /* 0x47fbb0 fills the 16 bytes at esi, copied to +0xa4. */
    eax = port_call_with(&port, 0x47fbb0, object, entry->edx, entry->ebx, entry->ecx, ebp - 0x18,
                         object, ebp);
    for (offset = 0; offset < 0x10; offset += 4)
    {
        port_set32(&port, object, 0xa4 + offset, port_u32(&port, ebp, offset - 0x18));
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_game_screen_new(PORT_SIGNATURE)
{
    Port port;
    uint32_t screen;
    uint32_t edx;
    uint32_t arguments[4];
    port_open_frame(&port, calls, services, globals, entry, 0x14);
    screen = port_call(&port, 0x4ca000, 0x280, entry->edx, entry->ebx, entry->ecx);
    edx = vertrix_lift_edx;
    if (screen != 0)
    {
        screen = port_call(&port, 0x4413b0, screen, edx, entry->ebx, entry->ecx);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, 0, 0x544070, screen);
    arguments[0] = 0;
    arguments[1] = 0;
    arguments[2] = 0xd;
    arguments[3] = entry->ebx;
    port_call_stack(&port, 0x441530, screen, edx, 0, 0x10, arguments, 4);
    screen = port_call(&port, 0x441600, port_u32(&port, 0, 0x544070), vertrix_lift_edx, 0, 0x10);
    return port_return(&port, screen, vertrix_lift_edx);
}

uint32_t vertrix_port_raise_at_caller(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t record = entry->esp - BELOW;
    uint32_t arguments[3];
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    /* The three dwords at esp: the address from 0x4e0f8b and two left as they were. */
    arguments[0] = port_call(&port, 0x4e0f8b, 0, entry->edx, entry->ebx, 0);
    port_set32(&port, record, 0, arguments[0]);
    arguments[1] = port_u32(&port, record, 4);
    arguments[2] = port_u32(&port, record, 8);
    eax = port_call_stack(&port, 0x4cd8b0, 0, record, port.env.chain, 0, arguments, 3);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_object_destroy_e(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48,
        GUARD_HANDLER = 0x4ec1ec
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t result;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if (mode & 4)
    {
        /* An array: element destructor 0x514ef0, freed by 0x4ca040. */
        port_set32(&port, ebp, -0x44u, object);
        port_set32(&port, ebp, -0x24u, 1);
        result = port_call(&port, 0x4ccb9f, object, 0x514ef0, 1, object);
        port_set32(&port, ebp, -0x24u, 0);
        port_call(&port, 0x4ca040, result, vertrix_lift_edx, 1, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0, 0x5174b4);
    port_set32(&port, ebp, -0x1cu, object);
    port_set8(&port, ebp, -0x18u, mode);
    port_set32(&port, ebp, -0x30u, port.env.chain);
    port_set32(&port, ebp, -0x2cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x28u, 0x51701c);
    port_set32(&port, ebp, -0x24u, 3);
    /* The two strings (0x4d7630 with 0 and 1); the second returns the object. */
    port_call(&port, 0x4d7630, object, 0, mode, object);
    port_set32(&port, ebp, -0x24u, 0);
    result = port_call(&port, 0x4d7630, object, 1, mode, object);
    edx = 0;
    port_set32(&port, ebp, -0x24u, 0);
    if (mode & 2)
    {
        port_call(&port, 0x4ca050, result, edx, mode, result);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_lock_enter(PORT_SIGNATURE)
{
    enum
    {
        GLOBAL_LOCK = 0x5c8910
    };
    Port port;
    uint32_t lock = entry->eax;
    uint32_t thread;
    uint32_t eax;
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, 0x18);
    /* The current thread (import 0x4f1ba0) owns the lock already, or waits for its section. */
    thread = port_call(&port, 0x4f1ba0, lock, entry->edx, lock, entry->ecx);
    edx = port_u32(&port, lock, 8);
    eax = thread;
    if (thread != edx)
    {
        uint32_t section;
        if (port_u32(&port, lock, 4) == 0)
        {
            /* The section is created once, under the global lock. */
            eax = port_call(&port, 0x4e57ac, GLOBAL_LOCK, edx, lock, entry->ecx);
            edx = vertrix_lift_edx;
            if (port_u32(&port, lock, 4) == 0)
            {
                eax = port_call(&port, 0x4e55d4, eax, edx, lock, entry->ecx);
                edx = vertrix_lift_edx;
                port_set32(&port, lock, 4, 1);
                port_set32(&port, lock, 0, eax);
            }
            eax = port_call(&port, 0x4e5810, GLOBAL_LOCK, edx, lock, entry->ecx);
            edx = vertrix_lift_edx;
        }
        section = port_u32(&port, lock, 0);
        eax = port_call_stack(&port, 0x4f1b48, eax, edx, lock, entry->ecx, &section, 1);
        port_set32(&port, lock, 8, thread);
    }
    port_set32(&port, lock, 0xc, port_u32(&port, lock, 0xc) + 1);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_list_parse_texts(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30,
        GUARD_HANDLER = 0x4ec1ec,
        PARSE_GUARD = 0x5175fc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t limit;
    uint32_t edx = entry->edx;
    uint32_t ebx = PARSE_GUARD;
    uint32_t ecx = GUARD_HANDLER;
    uint32_t index;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, ebp, -0x14u, entry->ecx);
    port_set32(&port, ebp, -0x2cu, port.env.chain);
    port_set32(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x28u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x24u, PARSE_GUARD);
    port_set32(&port, ebp, -0x20u, 0);
    limit = port_u32(&port, ebp, 8);
    /* Each of the count (ebx, a word) destination strings gets the list's text longer than the
     * limit (0x48a300 into a temporary, 0x4ca310) or the default text (ecx, 0x4ca370). */
    for (index = 0; index < port_u16(&port, ebp, -0xcu); index++)
    {
        uint32_t texts = port_call(&port, 0x48a2e0, list, edx, ebx, ecx);
        edx = vertrix_lift_edx;
        uint32_t taken = 0;
        if (index < texts)
        {
            uint32_t length = port_call(&port, 0x48a2f0, list, index, ebx, ecx);
            edx = limit;
            if (length > limit)
            {
                uint32_t text;
                ecx = limit;
                ebx = index;
                text = port_call(&port, 0x48a300, list, ebp - 0x18, ebx, ecx);
                ecx = 1;
                ebx = 0;
                port_set32(&port, ebp, -0x20u, 1);
                port_call(&port, 0x4ca310, port_u32(&port, ebp, -0x10u), text, ebx, ecx);
                port_set32(&port, ebp, -0x20u, 0);
                port_call(&port, 0x4ca210, ebp - 0x18, 0, ebx, ecx);
                port_set32(&port, ebp, -0x20u, 0);
                taken = 1;
            }
        }
        if (!taken)
        {
            port_call(&port, 0x4ca370, port_u32(&port, ebp, -0x10u), port_u32(&port, ebp, -0x14u),
                      ebx, ecx);
        }
        edx = port_u32(&port, ebp, -0x10u) + 4;
        port_set32(&port, ebp, -0x10u, edx);
    }
    return port_return(&port, port_u32(&port, ebp, -0x2cu), edx);
}

/* 0x4816f0's read with the list reader `reader` and the guard record `guard`. */
static uint32_t list_file_read_with(PORT_SIGNATURE, uint32_t reader, uint32_t guard)
{
    enum
    {
        BELOW = 0x13c,
        GUARD_HANDLER = 0x4ec1ec
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t parser = ebp - 0x138;
    uint32_t mode = 0;
    uint32_t result = 0;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x24u, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, guard);
    port_set32(&port, ebp, -0x18u, 0);
    /* A parser on the stack (0x48a620) opens the named file (0x48a710 with 0x5466c8) and, when it
     * opens, reads the list from it (0x480ec0, then 0x48a8c0); it is destroyed (0x48a670). */
    port_call(&port, 0x48a620, parser, GUARD_HANDLER, 0, guard);
    port_set32(&port, ebp, -0x18u, 1);
    mode = port_u32(&port, 0, 0x5466c8);
    if (port_call(&port, 0x48a710, parser, entry->eax, mode, 0) == 1)
    {
        result = port_call(&port, reader, parser, entry->edx, mode, 0);
        port_call(&port, 0x48a8c0, parser, vertrix_lift_edx, mode, result);
    }
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x48a670, parser, 0, 0, result);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_list_file_read(PORT_SIGNATURE)
{
    return list_file_read_with(calls, services, globals, entry, 0x480ec0, 0x516acc);
}

uint32_t vertrix_port_list_file_read_474490(PORT_SIGNATURE)
{
    return list_file_read_with(calls, services, globals, entry, 0x4741a0, 0x5163f4);
}

uint32_t vertrix_port_array_list_make(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 8 + 10 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t slot = entry->edx * 4;
    uint32_t arguments[8];
    uint32_t image;
    uint32_t array;
    unsigned index;
    port_open_arguments(&port, stack, calls, services, globals, entry, 8, 10);
    port_set32(&port, port_u32(&port, list, 0), slot, 0);
    for (index = 0; index < 4; index++)
    {
        arguments[index] = port_u32(&port, ebp, 0x10 + 4 * index);
    }
    arguments[4] = port_u8(&port, ebp, 0x20);
    arguments[5] = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x24);
    arguments[6] = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x28);
    arguments[7] = port_u8(&port, ebp, 0x2c);
    /* The entry is built by 0x483060 from the ten arguments. */
    image = port_call_stack(&port, 0x483060, entry->ebx, entry->ecx, port_u32(&port, ebp, 8),
                            port_u32(&port, ebp, 0xc), arguments, 8);
    array = port_u32(&port, list, 0);
    port_set32(&port, array, slot, image);
    return port_return(&port, image, array);
}

uint32_t vertrix_port_list_parse_values(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30,
        GUARD_HANDLER = 0x4ec1ec,
        PARSE_GUARD = 0x517608
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t limit;
    uint32_t edx = entry->edx;
    uint32_t ebx = PARSE_GUARD;
    uint32_t ecx = GUARD_HANDLER;
    uint32_t index;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, ebp, -0x14u, entry->ecx);
    port_set32(&port, ebp, -0x2cu, port.env.chain);
    port_set32(&port, ebp, -0x10u, entry->edx);
    port_set32(&port, ebp, -0x28u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x24u, PARSE_GUARD);
    port_set32(&port, ebp, -0x20u, 0);
    limit = port_u32(&port, ebp, 8);
    /* Each of the count (ebx, a word) destination values gets the list's text longer than the
     * limit converted (0x48a300, 0x4d6710) or the default value (ecx). */
    for (index = 0; index < port_u16(&port, ebp, -0xcu); index++)
    {
        uint32_t texts = port_call(&port, 0x48a2e0, list, edx, ebx, ecx);
        uint32_t taken = 0;
        edx = vertrix_lift_edx;
        if (index < texts)
        {
            uint32_t length = port_call(&port, 0x48a2f0, list, index, ebx, ecx);
            edx = limit;
            if (length > limit)
            {
                uint32_t text;
                uint32_t value;
                ecx = limit;
                ebx = index;
                text = port_call(&port, 0x48a300, list, ebp - 0x18, ebx, ecx);
                port_set32(&port, ebp, -0x20u, 1);
                ebx = 0;
                value = port_call(&port, 0x4d6710, port_u32(&port, text, 0),
                                  port_u32(&port, ebp, -0x10u), ebx, ecx);
                port_set32(&port, vertrix_lift_edx, 0, value);
                port_set32(&port, ebp, -0x20u, 0);
                port_call(&port, 0x4ca210, ebp - 0x18, 0, ebx, ecx);
                port_set32(&port, ebp, -0x20u, 0);
                taken = 1;
            }
        }
        if (!taken)
        {
            port_set32(&port, port_u32(&port, ebp, -0x10u), 0, port_u32(&port, ebp, -0x14u));
        }
        edx = port_u32(&port, ebp, -0x10u) + 4;
        port_set32(&port, ebp, -0x10u, edx);
    }
    return port_return(&port, port_u32(&port, ebp, -0x2cu), edx);
}

uint32_t vertrix_port_settings_file_read(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x13c,
        GUARD_HANDLER = 0x4ec1ec,
        READ_GUARD = 0x5175bc
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t parser = ebp - 0x138;
    uint32_t mode;
    uint32_t result = 0;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x24u, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, READ_GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    /* As 0x4816f0, with the file given by the parser's own edx and read by 0x48a100. */
    port_call(&port, 0x48a620, parser, entry->edx, READ_GUARD, GUARD_HANDLER);
    port_set32(&port, ebp, -0x18u, 1);
    mode = port_u32(&port, 0, 0x5466c8);
    if (port_call(&port, 0x48a710, parser, vertrix_lift_edx, mode, 0) == 1)
    {
        result = port_call(&port, 0x48a100, entry->eax, parser, mode, 0);
        port_call(&port, 0x48a8c0, parser, vertrix_lift_edx, mode, result);
    }
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x48a670, parser, 0, 0, result);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_table_file_read(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x13c,
        GUARD_HANDLER = 0x4ec1ec,
        READ_GUARD = 0x5176f0
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t parser = ebp - 0x138;
    uint32_t mode;
    uint32_t result = 0xa;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x24u, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, READ_GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    /* As 0x4816f0, with 10 in ecx and the reader 0x48b2f0; a file that does not open returns
     * that 10. */
    port_call(&port, 0x48a620, parser, GUARD_HANDLER, 0, READ_GUARD);
    port_set32(&port, ebp, -0x18u, 1);
    mode = port_u32(&port, 0, 0x5466c8);
    if (port_call(&port, 0x48a710, parser, entry->eax, mode, result) == 1)
    {
        result = port_call(&port, 0x48b2f0, parser, entry->edx, mode, result);
        port_call(&port, 0x48a8c0, parser, vertrix_lift_edx, mode, result);
    }
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x48a670, parser, 0, 0, result);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_image_file_load(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t name = entry->eax;
    uint32_t archive;
    uint32_t loaded = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, 0);
    archive = port_u32(&port, 0, 0x5589e0);
    /* With the archive open and the name in it (0x45f590), the extension (0x489b40) picks the
     * loader: 0x50f90b for 0x4b7dd0, 0x50f910 for 0x48b240. A loader's nonzero result clears the
     * image it stored. */
    if (archive != 0 && port_call(&port, 0x45f590, name, 0, archive, name) != 0)
    {
        if (port_call(&port, 0x489b40, name, 0x50f90b, archive, name) == 1)
        {
            loaded = port_call(&port, 0x4b7dd0, name, ebp - 0x14, 0, name);
        }
        else if (port_call(&port, 0x489b40, name, 0x50f910, 0, name) == 1)
        {
            loaded = port_call(&port, 0x48b240, name, ebp - 0x14, 0, name);
        }
        if (loaded != 0)
        {
            port_set32(&port, ebp, -0x14u, 0);
        }
    }
    return port_return(&port, port_u32(&port, ebp, -0x14u), entry->edx);
}

uint32_t vertrix_port_image_list_file_read(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x140,
        GUARD_HANDLER = 0x4ec1ec,
        READ_GUARD = 0x516d6c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t parser = ebp - 0x13c;
    uint32_t list = entry->eax;
    uint32_t mode;
    uint32_t eax;
    uint32_t edx;
    uint32_t index = 0;
    uint32_t count;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x28u, port.env.chain);
    port_set32(&port, ebp, -0x24u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x20u, READ_GUARD);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call(&port, 0x48a620, parser, entry->edx, GUARD_HANDLER, list);
    port_set32(&port, ebp, -0x1cu, 1);
    mode = port_u32(&port, 0, 0x5466c8);
    if (port_call(&port, 0x48a710, parser, vertrix_lift_edx, mode, list) == 0)
    {
        /* The saved guard chain is what both exits return. */
        port_call(&port, 0x48a670, parser, 0, mode, list);
        return port_return(&port, port_u32(&port, ebp, -0x28u), vertrix_lift_edx);
    }
    /* A word count (0x482bb0), then that many images (0x482d00) into a new array. */
    port_call(&port, 0x482bb0, parser, ebp - 0x14, mode, list);
    count = port_u16(&port, ebp, -0x14u);
    port_set32(&port, list, 4, count);
    eax = port_call(&port, 0x4ec160, count, 4, 0, list);
    edx = port_u32(&port, list, 4);
    port_set32(&port, list, 0, eax);
    if (edx != 0)
    {
        edx = 0;
        do
        {
            uint32_t image;
            port_set32(&port, edx, port_u32(&port, list, 0), 0);
            image = port_call(&port, 0x482d00, parser, edx, index, list);
            edx = vertrix_lift_edx;
            port_set32(&port, edx, port_u32(&port, list, 0), image);
            index++;
            edx += 4;
        } while (index < port_u32(&port, list, 4));
    }
    port_call(&port, 0x48a8c0, parser, edx, index, list);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call(&port, 0x48a670, parser, 0, index, list);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x1cu, 0);
    return port_return(&port, port_u32(&port, ebp, -0x28u), edx);
}

uint32_t vertrix_port_array_list_build(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x18 + 8 + 10 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->eax;
    uint32_t arguments[8];
    uint32_t image = 0;
    uint32_t edx;
    uint32_t index;
    uint32_t offset;
    unsigned argument;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0x18, 10);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    port_set32(&port, ebp, -0x14u, entry->ecx);
    port_set32(&port, list, 4, entry->edx);
    image = port_call(&port, 0x4ec160, entry->edx, 4, entry->ebx, entry->ecx);
    edx = port_u32(&port, list, 4);
    port_set32(&port, list, 0, image);
    port_set32(&port, ebp, -0xcu, 0);
    if (edx == 0)
    {
        return port_return(&port, image, 0);
    }
    /* Each entry is built by 0x483060 from the same ten arguments (as 0x487660). */
    for (index = 0, offset = 0; index < edx; offset += 4)
    {
        port_set32(&port, offset, port_u32(&port, list, 0), 0);
        for (argument = 0; argument < 4; argument++)
        {
            arguments[argument] = port_u32(&port, ebp, 0x10 + 4 * argument);
        }
        arguments[4] = port_u8(&port, ebp, 0x20);
        arguments[5] = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x24);
        arguments[6] = (uint32_t)(int32_t)(int8_t)port_u8(&port, ebp, 0x28);
        arguments[7] = port_u8(&port, ebp, 0x2c);
        image = port_call_stack(&port, 0x483060, port_u32(&port, ebp, -0x10u),
                                port_u32(&port, ebp, -0x14u), port_u32(&port, ebp, 8),
                                port_u32(&port, ebp, 0xc), arguments, 8);
        port_set32(&port, port_u32(&port, list, 0), offset, image);
        index = port_u32(&port, ebp, -0xcu) + 1;
        port_set32(&port, ebp, -0xcu, index);
        edx = port_u32(&port, list, 4);
    }
    return port_return(&port, image, edx);
}

uint32_t vertrix_port_bitmap_file_read(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x140,
        GUARD_HANDLER = 0x4ec1ec,
        READ_GUARD = 0x5163dc
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t parser = ebp - 0x13c;
    uint32_t mode;
    uint32_t result = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x28u, port.env.chain);
    port_set32(&port, ebp, -0x24u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x20u, READ_GUARD);
    port_set32(&port, ebp, -0x1cu, 0);
    /* A parser on the stack opens the named file (0x48a620, 0x48a710 with 0x5466c8) and the
     * bitmap is read from it (0x473cf0, then 0x48a8c0). */
    port_call(&port, 0x48a620, parser, entry->eax, READ_GUARD, GUARD_HANDLER);
    mode = port_u32(&port, 0, 0x5466c8);
    port_set32(&port, ebp, -0x1cu, 1);
    if (port_call(&port, 0x48a710, parser, vertrix_lift_edx, mode, GUARD_HANDLER) == 1)
    {
        result = port_call(&port, 0x473cf0, parser, vertrix_lift_edx, mode, 0);
        port_call(&port, 0x48a8c0, parser, vertrix_lift_edx, mode, result);
    }
    port_set32(&port, ebp, -0x1cu, 0);
    port_call(&port, 0x48a670, parser, 0, mode, result);
    port_set32(&port, ebp, -0x1cu, 0);
    return port_return(&port, result, entry->edx);
}

/* The table fills: the entry built by 0x487660 with the rectangle's size, then the image looked up
 * (0x4877f0), framed by the rectangle (0x482e10) and added to 0x5b9c60 (0x483ed0). */
static uint32_t table_fill(Port *port, uint32_t table, uint32_t slot, uint32_t rectangle,
                           uint32_t first, uint32_t second)
{
    uint32_t width = port_u32(port, rectangle, 4);
    uint32_t height = port_u32(port, rectangle, 8);
    uint32_t arguments[10] = {first, second, 0, 0, width, height, 0, 0, 1, 4};
    uint32_t image;
    port_call_stack(port, 0x487660, table, slot, width, height, arguments, 10);
    image = port_call(port, 0x4877f0, table, slot, width, height);
    port_call(port, 0x482e10, image, rectangle, 0, 0);
    return port_call(port, 0x483ed0, image, 0x5b9c60, 0, 0);
}

uint32_t vertrix_port_table_fill_slot(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, 0x30);
    eax = table_fill(&port, 0x544a34, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, eax, vertrix_lift_edx);
}

static uint32_t table_fill_indexed(PORT_SIGNATURE, uint32_t base)
{
    Port port;
    uint8_t stack[0x10 + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t table = base + entry->eax * 0x1c;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0x10, 1);
    port_set32(&port, ebp, -0xcu, table);
    eax = table_fill(&port, table, entry->edx, entry->ebx, entry->ecx, port_u32(&port, ebp, 8));
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_table_fill_indexed(PORT_SIGNATURE)
{
    return table_fill_indexed(calls, services, globals, entry, 0x546458);
}

uint32_t vertrix_port_table_fill_indexed_b(PORT_SIGNATURE)
{
    return table_fill_indexed(calls, services, globals, entry, 0x544d7c);
}

uint32_t vertrix_port_record_prefix_sum(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = entry->eax;
    uint32_t count;
    uint32_t sum = 0;
    uint32_t at;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x28u, record);
    port_set32(&port, ebp, -0x1cu, 0);
    count = port_u32(&port, record, 8);
    at = port_u32(&port, record, 0);
    eax = at;
    /* Each sample becomes the running sum (words when +0x16 bit 0 is set, else bytes). */
    if (port_u8(&port, record, 0x16) & 1)
    {
        for (count >>= 1; count-- != 0; at += 2)
        {
            port_set16(&port, at, 0, port_u16(&port, at, 0) + sum);
            sum = eax = port_u16(&port, at, 0);
        }
        port_set32(&port, ebp, -0x24u, at);
    }
    else
    {
        for (; count-- != 0; at++)
        {
            port_set8(&port, at, 0, port_u8(&port, at, 0) + sum);
            sum = eax = port_u8(&port, at, 0);
        }
        port_set32(&port, ebp, -0x20u, at);
    }
    port_set32(&port, ebp, -0x1cu, sum);
    port_set32(&port, ebp, -0x18u, 0xffffffffu);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_sample_file_read(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x13c,
        GUARD_HANDLER = 0x4ec1ec,
        READ_GUARD = 0x518750
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t parser = ebp - 0x138;
    uint32_t mode;
    uint32_t result = 0xa;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x24u, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, READ_GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    /* As 0x48b240, with the reader 0x4b7e80. */
    port_call(&port, 0x48a620, parser, GUARD_HANDLER, 0, READ_GUARD);
    port_set32(&port, ebp, -0x18u, 1);
    mode = port_u32(&port, 0, 0x5466c8);
    if (port_call(&port, 0x48a710, parser, entry->eax, mode, result) == 1)
    {
        result = port_call(&port, 0x4b7e80, parser, entry->edx, mode, result);
        port_call(&port, 0x48a8c0, parser, vertrix_lift_edx, mode, result);
    }
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x48a670, parser, 0, 0, result);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, result, edx);
}

/* 0x4b5dc0's shape: the method table `table`, the element destructor `element` and the guard
 * record `guard`. */
static uint32_t object_destroy_a_with(PORT_SIGNATURE, uint32_t table, uint32_t element,
                                      uint32_t guard)
{
    enum
    {
        BELOW = 0x54,
        GUARD_HANDLER = 0x4ec1ec
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t result;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if (mode & 4)
    {
        /* An array: element destructor 0x516390, freed by 0x4ca040. */
        port_set32(&port, ebp, -0x50u, object);
        port_set32(&port, ebp, -0x30u, 1);
        result = port_call(&port, 0x4ccb9f, object, element, 1, object);
        port_set32(&port, ebp, -0x30u, 0);
        port_call(&port, 0x4ca040, result, vertrix_lift_edx, 1, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0, table);
    port_set32(&port, ebp, -0x28u, object);
    port_set32(&port, ebp, -0x1cu, object);
    port_set8(&port, ebp, -0x24u, 1);
    port_set8(&port, ebp, -0x18u, mode);
    port_set32(&port, ebp, -0x3cu, port.env.chain);
    port_set32(&port, ebp, -0x38u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x34u, guard);
    port_set32(&port, ebp, -0x30u, 0);
    /* The base destructor (0x4d86d0 with 1), mode 2 freeing it (0x4ca050). */
    result = port_call(&port, 0x4d86d0, object, 1, mode, object);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x30u, 0);
    if (mode & 2)
    {
        port_call(&port, 0x4ca050, result, edx, mode, result);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_object_destroy_a(PORT_SIGNATURE)
{
    return object_destroy_a_with(calls, services, globals, entry, 0x518344, 0x516390, 0x518300);
}

uint32_t vertrix_port_object_destroy_a_487930(PORT_SIGNATURE)
{
    return object_destroy_a_with(calls, services, globals, entry, 0x516e34, 0x516e50, 0x516df0);
}

uint32_t vertrix_port_path_split_strings(PORT_SIGNATURE)
{
    enum
    {
        PATH = 0x5b9cd0,
        DRIVE = 0x5b9dd8,
        DIRECTORY = 0x5b9de0,
        NAME = 0x5b9ee0,
        EXTENSION = 0x5b9fe0
    };
    Port port;
    uint8_t stack[0x18 + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t from = entry->eax;
    uint32_t to = PATH;
    uint32_t byte;
    uint32_t eax;
    uint32_t ebx = DIRECTORY;
    uint32_t ecx = NAME;
    uint32_t target;
    uint32_t extension = EXTENSION;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0x18, 1);
    port_set32(&port, ebp, -0x14u, entry->edx);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, ebp, -0x10u, entry->ecx);
    /* The path is copied to 0x5b9cd0 and split there (0x4daae8); each part asked for (a string
     * pointer, or the stack argument for the extension) is set from its buffer (0x4ca370). */
    do
    {
        byte = port_u8(&port, from, 0);
        port_set8(&port, to, 0, byte);
        from++;
        to++;
    } while (byte != 0);
    eax = port_call_stack(&port, 0x4daae8, PATH, DRIVE, ebx, ecx, &extension, 1);
    if ((target = port_u32(&port, ebp, -0x14u)) != 0)
    {
        eax = port_call(&port, 0x4ca370, target, DRIVE, ebx, ecx);
    }
    ecx = port_u32(&port, ebp, -0xcu);
    if (ecx != 0)
    {
        eax = port_call(&port, 0x4ca370, ecx, DIRECTORY, ebx, ecx);
    }
    ebx = port_u32(&port, ebp, -0x10u);
    if (ebx != 0)
    {
        eax = port_call(&port, 0x4ca370, ebx, NAME, ebx, ecx);
    }
    if ((target = port_u32(&port, ebp, 8)) != 0)
    {
        eax = port_call(&port, 0x4ca370, target, EXTENSION, ebx, ecx);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_archive_file_read(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x23c,
        GUARD_HANDLER = 0x4ec1ec,
        READ_GUARD = 0x516cc0
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t name = ebp - 0x124;
    uint32_t parser = ebp - 0x238;
    uint32_t ebx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x20u, port.env.chain);
    port_set32(&port, ebp, -0x1cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x18u, READ_GUARD);
    port_set32(&port, ebp, -0x14u, 0);
    /* The archive name (0x45f540 with 0x4fd208) must be present (0x45f590); its contents are
     * read into the destination (edx) by a parser on the stack. */
    port_call(&port, 0x45f540, name, 0x4fd208, entry->eax, entry->ebx);
    /* Both exits return the saved guard chain. */
    if (port_call(&port, 0x45f590, name, vertrix_lift_edx, entry->eax, entry->ebx) != 1)
    {
        return port_return(&port, port_u32(&port, ebp, -0x20u), vertrix_lift_edx);
    }
    port_call(&port, 0x48a620, parser, 1, entry->eax, entry->ebx);
    ebx = port_u32(&port, 0, 0x5466c8);
    port_set32(&port, ebp, -0x14u, vertrix_lift_edx);
    if (port_call(&port, 0x48a710, parser, name, ebx, entry->ebx) == 1)
    {
        ebx = 1;
        port_call(&port, 0x48a8a0, parser, vertrix_lift_edx, ebx, entry->ebx);
        port_call(&port, 0x48a930, parser, entry->edx, ebx, entry->ebx);
        port_call(&port, 0x48a8c0, parser, vertrix_lift_edx, ebx, entry->ebx);
    }
    port_set32(&port, ebp, -0x14u, 0);
    port_call(&port, 0x48a670, parser, 0, ebx, 0);
    port_set32(&port, ebp, -0x14u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x20u), vertrix_lift_edx);
}

uint32_t vertrix_port_object_destroy_parser_base(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x54,
        GUARD_HANDLER = 0x4ec1ec
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t result;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    if (mode & 4)
    {
        /* An array: element destructor 0x518720, freed by 0x4ca040. */
        port_set32(&port, ebp, -0x50u, object);
        port_set32(&port, ebp, -0x30u, 1);
        result = port_call(&port, 0x4ccb9f, object, 0x518720, 1, object);
        port_set32(&port, ebp, -0x30u, 0);
        port_call(&port, 0x4ca040, result, vertrix_lift_edx, 1, object);
        return port_return(&port, object, vertrix_lift_edx);
    }
    port_set32(&port, object, 0, 0x518704);
    port_set32(&port, ebp, -0x28u, object);
    port_set32(&port, ebp, -0x1cu, object);
    port_set8(&port, ebp, -0x24u, 1);
    port_set8(&port, ebp, -0x18u, mode);
    port_set32(&port, ebp, -0x3cu, port.env.chain);
    port_set32(&port, ebp, -0x38u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x34u, 0x5186b0);
    port_set32(&port, ebp, -0x30u, 3);
    /* Its contents (0x4b7b00), then the base destructor (0x4d86d0 with 1), mode 2 freeing it. */
    port_call(&port, 0x4b7b00, object, GUARD_HANDLER, mode, object);
    port_set32(&port, ebp, -0x30u, 0);
    result = port_call(&port, 0x4d86d0, object, 1, mode, object);
    edx = 0;
    port_set32(&port, ebp, -0x30u, 0);
    if (mode & 2)
    {
        port_call(&port, 0x4ca050, result, edx, mode, result);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, result, edx);
}

uint32_t vertrix_port_com_create(PORT_SIGNATURE)
{
    Port port;
    uint32_t out = entry->edx;
    uint32_t zero = 0;
    uint32_t arguments[5];
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, 0x1c);
    /* COM is initialised (import 0x4f1760), the object of class 0x40b010 and interface 0x40b020
     * created into *edx (import 0x4f175c) and, on success, its method +0x28 called with 0. */
    eax =
        port_call_stack(&port, 0x4f1760, entry->eax, entry->edx, entry->ebx, entry->ecx, &zero, 1);
    arguments[0] = 0x40b010;
    arguments[1] = entry->ebx;
    arguments[2] = 7;
    arguments[3] = 0x40b020;
    arguments[4] = out;
    eax = port_call_stack(&port, 0x4f175c, eax, vertrix_lift_edx, entry->ebx, entry->ecx, arguments,
                          5);
    if ((int32_t)eax >= 0)
    {
        uint32_t object = port_u32(&port, out, 0);
        uint32_t table = port_u32(&port, object, 0);
        uint32_t method[2];
        method[0] = object;
        method[1] = 0;
        eax = port_call_stack(&port, port_u32(&port, table, 0x28), object, table, entry->ebx,
                              entry->ecx, method, 2);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_com_probe(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    port_open_frame(&port, calls, services, globals, entry, 0x10);
    /* Create the object (0x40b620) into a local; release it (0x40b660) and return 0, or 5. */
    if (port_call(&port, 0x40b620, 0, ebp - 0xc, 0, entry->ecx) != 0)
    {
        return port_return(&port, 5, entry->edx);
    }
    port_call(&port, 0x40b660, port_u32(&port, ebp, -0xcu), vertrix_lift_edx, 0, entry->ecx);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_com_probe_40b0d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t ebp = entry->esp - 4;
    port_open_frame(&port, calls, services, globals, entry, 0x10);
    /* 0x40b6a0's code with the create and release copies 0x40b040 and 0x40b080. */
    if (port_call(&port, 0x40b040, 0, ebp - 0xc, 0, entry->ecx) != 0)
    {
        return port_return(&port, 5, entry->edx);
    }
    port_call(&port, 0x40b080, port_u32(&port, ebp, -0xcu), vertrix_lift_edx, 0, entry->ecx);
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_player_reset(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x28 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t player = entry->eax;
    uint32_t record = ebp - 0x24;
    uint32_t ebx = 0x513fe0;
    uint32_t ecx = 0x4ec1ec;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x28);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x20u, ecx);
    port_set32(&port, ebp, -0x1cu, ebx);
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x4b7cd0, record, entry->edx, ebx, ecx);
    edx = vertrix_lift_edx;
    /* A player other than 0x513c1e's is refreshed first (as 0x41a4e0). */
    if (edx != port_u8(&port, 0, 0x513c1e))
    {
        ebx = port_call(&port, 0x4182c0, port_u8(&port, 0, 0x513c1e), edx, ebx, ecx);
        ecx = port_u32(&port, 0, 0x540048);
        port_call(&port, 0x41a2f0, player, port_u32(&port, port_u32(&port, 0, 0x544070), 0x268),
                  ebx, ecx);
        edx = vertrix_lift_edx;
    }
    port_call(&port, 0x41aa20, player, edx, ebx, ecx);
    port_call(&port, 0x41aaa0, player, 0x423fb0, ebx, ecx);
    port_set8(&port, player, 0xc8, 6);
    port_call(&port, 0x418840, player, vertrix_lift_edx, ebx, ecx);
    return port_return(&port, port_u32(&port, record, 0), vertrix_lift_edx);
}

uint32_t vertrix_port_timer_start(PORT_SIGNATURE)
{
    Port port;
    uint32_t rate = entry->ebx & 0xffff;
    uint32_t period;
    uint32_t resolution = 0x14;
    uint32_t arguments[5];
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, 0x20);
    if (rate == 0)
    {
        /* The original divides by zero here. */
        return port_return(&port, 0, entry->edx);
    }
    /* A periodic multimedia timer (import 0x4f1734) of 1000 / rate ms calling 0x484530 with the
     * object; its id kept at 0x598db0 and the callback stored in the object. */
    period = (uint32_t)(1000 / (int32_t)rate);
    if ((period & 0xffff) < resolution)
    {
        resolution = period;
    }
    arguments[0] = period & 0xffff;
    arguments[1] = resolution & 0xffff;
    arguments[2] = 0x484530;
    arguments[3] = entry->eax;
    arguments[4] = 1;
    eax = port_call_stack(&port, 0x4f1734, period & 0xffff, resolution & 0xffff, rate, resolution,
                          arguments, 5);
    port_set32(&port, 0, 0x598db0, eax);
    port_set32(&port, entry->eax, 0, entry->edx);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_fdiv_check(PORT_SIGNATURE)
{
    Port port;
    uint32_t local = entry->esp - 0x1c;
    uint32_t eax = entry->eax;
    uint32_t edx;
    uint32_t quotient;
    port_open_frame(&port, calls, services, globals, entry, 0x1c);
    /* The Pentium division check: 4195835 - (4195835 / 3145727) * 3145727 compared with a small
     * epsilon (0x4eb652, 0x4db507, 0x4db34a, 0x4eb57c); a faulty divider sets 0x508798 bit 0. */
    port_set32(&port, local, 8, 0xc0000000u);
    port_set32(&port, local, 0xc, 0x4150017eu);
    port_set32(&port, local, 0, 0x80000000u);
    port_set32(&port, local, 4, 0x4147ffffu);
    if (port_u8(&port, 0, 0x5054a1) < 3)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call(&port, 0x4eb652, 0xc0000000u, 0x4150017eu, 0x80000000u, 0x4147ffffu);
    quotient = port_call(&port, 0x4db507, eax, vertrix_lift_edx, 0x80000000u, 0x4147ffffu);
    edx = vertrix_lift_edx;
    eax = port_call(&port, 0x4db34a, 0xc0000000u, 0x4150017eu, quotient, edx);
    eax = port_call(&port, 0x4eb57c, eax, vertrix_lift_edx, 0xe2308c3au, 0x3e45798eu);
    if (!(vertrix_lift_fl.zf || vertrix_lift_fl.sf != vertrix_lift_fl.of))
    {
        port_set8(&port, 0, 0x508798, port_u8(&port, 0, 0x508798) | 1);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_stack_limits(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x2c + 8];
    uint32_t buffer = entry->esp - 0x2c;
    uint32_t arguments[3];
    uint32_t eax;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x2c);
    /* The stack's region (import 0x4f1cf4, VirtualQuery of a local): its top, and its bottom
     * above the guard pages, by the system version (0x509731, 0x50972f). */
    arguments[0] = entry->esp - 0x10;
    arguments[1] = buffer;
    arguments[2] = 0x1c;
    port_call_stack(&port, 0x4f1cf4, entry->esp - 0x10, entry->edx, entry->eax, entry->ecx,
                    arguments, 3);
    edx = port_u32(&port, buffer, 0) + port_u32(&port, buffer, 0xc);
    eax = port_u32(&port, buffer, 4);
    if (port_u16(&port, 0, 0x509731) < 0x8000)
    {
        eax += 0x3000;
    }
    else if (port_u8(&port, 0, 0x50972f) < 4)
    {
        eax += 0x12000;
    }
    else
    {
        eax += 0x13000;
    }
    if (entry->eax != 0)
    {
        port_set32(&port, entry->eax, 0, eax);
    }
    if (entry->edx != 0)
    {
        port_set32(&port, entry->edx, 0, edx);
    }
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_thread_stream_init(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x28 + 8];
    uint32_t esp = entry->esp;
    uint32_t object = entry->eax;
    uint32_t stream;
    uint32_t data;
    uint32_t edx;
    uint32_t value;
    static const uint8_t cleared[] = {0x60, 0x84, 0x88, 0x74, 0x80, 0xa0, 0x78};
    static const uint8_t cleared_after[] = {0x68, 0xa4, 0x98, 0x9c, 0x8c, 0x90,
                                            0xac, 0xb8, 0xbc, 0xb4, 0x7c};
    unsigned index;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x28);
    port_set32(&port, esp, -0x28u, port.env.chain);
    port_set32(&port, esp, -0x24u, 0x4ec1ec);
    port_set32(&port, esp, -0x20u, 0x5188d0);
    port_set32(&port, esp, -0x1cu, 0);
    port_set8(&port, esp, -0x10u, 0);
    port_set32(&port, esp, -0x14u, object);
    /* The derived stream (0x4cbf10) with the table 0x518a94, tied to the thread data (0x4ce780,
     * 0x4ce740) and the current process and thread (imports 0x4f1b9c, 0x4f1ba0). */
    stream = port_call(&port, 0x4cbf10, object, entry->edx, object, entry->ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esp, -0x1cu, 1);
    port_set32(&port, stream, 0, 0x518a94);
    port_set32(&port, stream, 0x70, edx);
    data = port_call(&port, 0x4ce780, stream, edx, stream, entry->ecx);
    port_set32(&port, data, 4, stream);
    value = port_call(&port, 0x4f1b9c, data, vertrix_lift_edx, stream, entry->ecx);
    port_set32(&port, stream, 0x28, value);
    value = port_call(&port, 0x4f1ba0, value, vertrix_lift_edx, stream, entry->ecx);
    port_set32(&port, stream, 0x2c, value);
    data = port_call(&port, 0x4ce740, value, vertrix_lift_edx, stream, entry->ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, data, 4, stream);
    for (index = 0; index < sizeof cleared; index++)
    {
        port_set32(&port, stream, cleared[index], 0);
    }
    port_set16(&port, stream, 0xaa, 0);
    for (index = 0; index < sizeof cleared_after; index++)
    {
        port_set32(&port, stream, cleared_after[index], 0);
    }
    port_set32(&port, stream, 0xb0, 0x200);
    port_set16(&port, stream, 0xa8, port_u16(&port, stream, 0xaa));
    return port_return(&port, stream, edx);
}

uint32_t vertrix_port_sound_slot_select(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[8 + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t offset = (entry->edx & 0xffff) * 0x60;
    uint32_t slot = entry->eax + offset;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, 8, 1);
    /* The slot (0x60 bytes each) becomes current (0x54d62c); unless sound is off (0x553648) it
     * is opened (0x475b00) and, when that fails, set up (0x475be0) and started (0x475af0). */
    port_set32(&port, 0, 0x54d62c, slot);
    if (port_u32(&port, 0, 0x553648) != 0)
    {
        return port_return(&port, offset, entry->ebx);
    }
    eax = port_call(&port, 0x475b00, slot, entry->ebx, entry->ecx, 0);
    if (eax != 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    port_call(&port, 0x475be0, port_u32(&port, 0, 0x54d62c), vertrix_lift_edx, entry->ecx,
              port_u32(&port, ebp, 8));
    eax = port_call(&port, 0x475af0, port_u32(&port, 0, 0x54d62c), vertrix_lift_edx, entry->ecx,
                    port_u32(&port, ebp, 8));
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_timer_resolution(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x1c + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t caps = ebp - 0x18;
    uint32_t ebx = 0x46;
    uint32_t ecx = entry->ecx;
    uint32_t minimum;
    uint32_t period;
    uint32_t eax;
    uint32_t arguments[4];
    port_open_stack(&port, stack, calls, services, globals, entry, 0x1c);
    /* The 70 Hz game timer (0x4844b0), then the finest period the device allows, at least 1
     * (import 0x4f1728), begun (import 0x4f1720) and kept at 0x5bd848, and an event (import
     * 0x4f1b30) at 0x5bd840. */
    port_call(&port, 0x4844b0, 0x5bd82c, 0x4b7b80, ebx, ecx);
    arguments[0] = caps;
    arguments[1] = 8;
    port_call_stack(&port, 0x4f1728, caps, vertrix_lift_edx, ebx, ecx, arguments, 2);
    minimum = port_u32(&port, caps, 0);
    period = minimum > 1 ? minimum : 1;
    ecx = port_u32(&port, ebp, -0x14u);
    if (period < ecx)
    {
        ebx = port_u32(&port, caps, 0);
        period = ebx > 1 ? ebx : 1;
    }
    else
    {
        period = ecx;
    }
    port_set32(&port, 0, 0x5bd848, period);
    eax = port_call_stack(&port, 0x4f1720, period, minimum, ebx, ecx, &period, 1);
    arguments[0] = 0;
    arguments[1] = 1;
    arguments[2] = 0;
    arguments[3] = 0;
    port_set32(&port, 0, 0x5bd83c, 1);
    eax = port_call_stack(&port, 0x4f1b30, eax, vertrix_lift_edx, ebx, ecx, arguments, 4);
    port_set32(&port, 0, 0x5bd840, eax);
    return port_return(&port, eax, entry->edx);
}

/* The sound voice setups (0x475be0, 0x475b20): a new voice (0x4ca000, 0x4756d0) set up by
 * 0x475790 with the kind and attached to the slot's list (0x4d8510). */
static uint32_t voice_attach(Port *port, uint32_t slot, uint32_t kind, uint32_t ebx, uint32_t ecx,
                             uint32_t edx)
{
    uint32_t voice = 0;
    uint32_t memory = port_call(port, 0x4ca000, 0x1c, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    if (memory != 0)
    {
        voice = port_call(port, 0x4756d0, memory, edx, ebx, ecx);
        edx = vertrix_lift_edx;
    }
    port_call_stack(port, 0x475790, voice, kind, edx, ebx, &ecx, 1);
    return port_call(port, 0x4d8510, slot + 0x20, voice, edx, ebx);
}

uint32_t vertrix_port_sound_voice_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    port_open_frame(&port, calls, services, globals, entry, 0x10);
    if (port_u32(&port, 0, 0x553648) == 0)
    {
        eax = voice_attach(&port, entry->eax, 2, entry->ebx, entry->ecx, entry->edx);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_sound_voice_play(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, 0x10);
    if (port_u32(&port, 0, 0x553648) == 0)
    {
        eax = voice_attach(&port, entry->eax, 1, entry->ebx, entry->ecx, entry->edx);
    }
    else
    {
        /* Sound off: 0x475b80 on 0x55364c with the slot's word +0x58. */
        uint32_t arguments[2];
        arguments[0] = entry->ebx;
        arguments[1] = entry->ecx;
        eax = port_call_stack(&port, 0x475b80, 0x55364c, port_u16(&port, entry->eax, 0x58), 0,
                              entry->edx, arguments, 2);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_sound_slot_play(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x10 + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t slot = entry->eax + (entry->edx & 0xffff) * 0x60;
    uint32_t argument;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0x10, 1);
    port_set32(&port, ebp, -0xcu, entry->eax);
    argument = port_u32(&port, ebp, 8);
    /* The slot (0x60 bytes each) becomes the playing one (0x54d628); with sound on it is opened
     * (0x475b00) and, when that succeeds, a voice played (0x475b20) and started (0x475ad0). */
    port_set32(&port, 0, 0x54d628, slot);
    if (port_u32(&port, 0, 0x553648) != 0)
    {
        eax = port_call(&port, 0x475b20, slot, entry->ebx, entry->ecx, argument);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    eax = port_call(&port, 0x475b00, slot, slot, entry->ebx, entry->ecx);
    if (eax == 1)
    {
        port_call(&port, 0x475b20, port_u32(&port, 0, 0x54d628), entry->ebx, entry->ecx, argument);
        eax = port_call(&port, 0x475ad0, port_u32(&port, 0, 0x54d628), entry->ebx, entry->ecx,
                        argument);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_object_construct_f(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x38 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t mixer;
    uint32_t index;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x38);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x5164e0);
    port_set32(&port, ebp, -0x28u, 0);
    port_set8(&port, ebp, -0x1cu, 0);
    port_set32(&port, ebp, -0x20u, object);
    /* The sound mixer: 256 slots of 0x60 bytes (0x4ccf3b with the slot table 0x516650), each
     * numbered at +0x58, its table 0x5165e4 at +0x6000; then 0x476090, 0x4760f0 and 0x4766b0,
     * with sound marked off (0x553648) before the last. */
    mixer = port_call(&port, 0x4ccf3b, object, 0x100, 0x516650, object);
    port_set32(&port, mixer, 0x6000, 0x5165e4);
    for (index = 0; index < 0x100; index++)
    {
        port_set16(&port, mixer, index * 0x60 + 0x58, index);
    }
    port_call(&port, 0x476090, mixer, 0x100, 0x516650, mixer);
    port_call(&port, 0x4760f0, mixer, 0, 0x516650, mixer);
    port_set32(&port, 0, 0x553648, 1);
    port_call(&port, 0x4766b0, mixer, vertrix_lift_edx, 0x516650, mixer);
    return port_return(&port, mixer, entry->edx);
}

uint32_t vertrix_port_sound_file_read(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x154,
        GUARD_HANDLER = 0x4ec1ec,
        READ_GUARD = 0x518760
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t parser = ebp - 0x150;
    uint32_t mode;
    uint32_t value;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x24u, entry->eax);
    port_set32(&port, ebp, -0x28u, entry->edx);
    port_set32(&port, ebp, -0x3cu, port.env.chain);
    port_set32(&port, ebp, -0x38u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x34u, READ_GUARD);
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x20u, 0xa);
    port_set8(&port, ebp, -0x2cu, port_u8(&port, ebp, -0x2cu));
    /* As the other file reads, with the reader 0x4b826f; a file that does not open returns 10. */
    value = port_call(&port, 0x48a620, parser, entry->edx, entry->ebx, entry->ecx);
    port_set32(&port, ebp, -0x1cu, value);
    port_set32(&port, ebp, -0x18u, value);
    port_set32(&port, ebp, -0x30u, 1);
    mode = port_u32(&port, 0, 0x5466c8);
    port_set32(&port, ebp, -0x14u, mode);
    if (port_call(&port, 0x48a710, parser, entry->eax, mode, entry->ecx) == 1)
    {
        value = port_call(&port, 0x4b826f, parser, entry->edx, mode, entry->ecx);
        port_set32(&port, ebp, -0x20u, value);
        port_call(&port, 0x48a8c0, parser, vertrix_lift_edx, mode, entry->ecx);
    }
    port_set32(&port, ebp, -0x30u, 0);
    port_call(&port, 0x48a670, parser, 0, mode, entry->ecx);
    port_set32(&port, ebp, -0x30u, 0);
    return port_return(&port, port_u32(&port, ebp, -0x20u), vertrix_lift_edx);
}

uint32_t vertrix_port_heap_lock_enter(PORT_SIGNATURE)
{
    LiftEntry lock = *entry;
    /* The heap's lock 0x5c8920: the original continues into 0x4e57ac. */
    lock.eax = 0x5c8920;
    return vertrix_port_lock_enter(calls, services, globals, &lock);
}

uint32_t vertrix_port_thread_runtime_init(PORT_SIGNATURE)
{
    static const uint32_t hooks[][2] = {
        {0x507ca0, 0x4e5728}, {0x507ca4, 0x4e5738}, {0x507ca8, 0x4e5748}, {0x507cac, 0x4e5750},
        {0x507cb0, 0x4e5710}, {0x507cb4, 0x4e571c}, {0x507cc8, 0x4e5794}, {0x507ccc, 0x4e579c},
        {0x509748, 0x4e57ac}, {0x50974c, 0x4e5810}, {0x509750, 0x4e5700}, {0x507cb8, 0x4e576c},
        {0x507cbc, 0x4e5780}, {0x507cc0, 0x4e5774}, {0x507cc4, 0x4e5788}};
    Port port;
    uint32_t eax;
    uint32_t edx;
    uint32_t tables;
    uint32_t arguments[2];
    unsigned index;
    port_open_frame(&port, calls, services, globals, entry, 0x20);
    /* When threads are available (0x4e58b8), install the runtime's locking hooks, create the
     * global lock (0x4e55d4 at 0x5c8910), set up the thread's tables (0x4e8510) and store them
     * in its TLS slot (import 0x4f1ce0). */
    eax = port_call(&port, 0x4e58b8, entry->eax, entry->edx, entry->ebx, entry->ecx);
    if (eax == 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    for (index = 0; index < sizeof hooks / sizeof hooks[0]; index++)
    {
        port_set32(&port, 0, hooks[index][0], hooks[index][1]);
    }
    eax = port_call(&port, 0x4e55d4, 0x4e5774, 0x4e5788, 1, 0x4e57a4);
    tables = port_u32(&port, 0, 0x5c7b9c);
    port_set32(&port, 0, 0x5c8910, eax);
    port_set32(&port, 0, 0x5c8914, 1);
    port_set32(&port, 0, 0x507cd0, 0x4e57a4);
    port_set32(&port, 0, 0x507cd4, 0x4e5808);
    eax = port_u32(&port, tables, 0xda);
    port_set32(&port, 0, 0x507cd8, 0x4e59c4);
    port_call(&port, 0x4e8510, eax, tables, 1, 0x4e57a4);
    edx = vertrix_lift_edx;
    arguments[0] = port_u32(&port, 0, 0x507c98);
    arguments[1] = port_u32(&port, 0, 0x5c7b9c);
    eax = port_call_stack(&port, 0x4f1ce0, arguments[0], edx, 1, 0x4e57a4, arguments, 2);
    port_set32(&port, 0, 0x507c9c, 0x4e5838);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_runtime_errors_init(PORT_SIGNATURE)
{
    static const uint32_t names[][2] = {
        {0x5c7939, 0x506a90}, {0x5c793a, 0x506aa8}, {0x5c793b, 0x506ac0}, {0x5c793c, 0x506ad8},
        {0x5c793d, 0x506af0}, {0x5c793e, 0x506b08}, {0x5c793f, 0x506b20}, {0x5c7940, 0x506b38},
        {0x5c7941, 0x506b50}, {0x5c7942, 0x506b68}};
    Port port;
    uint8_t stack[0x30 + 8];
    uint32_t esp = entry->esp;
    unsigned index;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x30);
    port_set32(&port, esp, -0x30u, port.env.chain);
    port_set32(&port, esp, -0x2cu, 0x4ec1ec);
    port_set32(&port, esp, -0x28u, 0x51afa0);
    port_set32(&port, esp, -0x24u, 0);
    /* The runtime's two static error objects (0x5c7804 with code 0xf022, 0x5c78a0 with 0xf024),
     * each after its name (0x4d30f0) and registered for exit (0x4ec1f7), then the eleven
     * exception names (0x4d30f0). */
    port_call(&port, 0x4d30f0, 0x5c7800, 0x506a48, entry->ebx, entry->ecx);
    port_set32(&port, esp, -0x10u, 0x5c7804);
    port_set8(&port, esp, -0xcu, 0);
    port_set32(&port, esp, -0x1cu, 0x5c7804);
    port_set8(&port, esp, -0x18u, 0);
    port_call(&port, 0x4d92f0, 0x5c7804, 0, entry->ebx, entry->ecx);
    port_set32(&port, 0, 0x5c7810, 0);
    port_set32(&port, 0, 0x5c7814, 0);
    port_set32(&port, 0, 0x5c7804, 0x51b534);
    port_set32(&port, 0, 0x5c7898, 0xf022);
    port_set32(&port, esp, -0x24u, 0);
    port_call(&port, 0x4ec1f7, 0x506730, 0x506a60, entry->ebx, entry->ecx);
    port_call(&port, 0x4d30f0, 0x5c789c, vertrix_lift_edx, entry->ebx, entry->ecx);
    port_set32(&port, esp, -0x10u, 0x5c78a0);
    port_set8(&port, esp, -0xcu, 0);
    port_set32(&port, esp, -0x1cu, 0x5c78a0);
    port_set8(&port, esp, -0x18u, 0);
    port_call(&port, 0x4d92f0, 0x5c78a0, 0, entry->ebx, entry->ecx);
    port_set32(&port, 0, 0x5c78ac, 0);
    port_set32(&port, 0, 0x5c78b0, 0);
    port_set32(&port, esp, -0x24u, 5);
    port_set32(&port, 0, 0x5c78a0, 0x51b554);
    port_set32(&port, 0, 0x5c7934, 0xf024);
    port_set32(&port, esp, -0x24u, 0);
    port_call(&port, 0x4ec1f7, 0x506740, 0x506a78, entry->ebx, entry->ecx);
    port_call(&port, 0x4d30f0, 0x5c7938, vertrix_lift_edx, entry->ebx, entry->ecx);
    for (index = 0; index < sizeof names / sizeof names[0]; index++)
    {
        port_call(&port, 0x4d30f0, names[index][0], names[index][1], entry->ebx, entry->ecx);
    }
    /* The saved guard chain is returned. */
    return port_return(&port, port_u32(&port, esp, -0x30u), entry->edx);
}

uint32_t vertrix_port_system_info_init(PORT_SIGNATURE)
{
    Port port;
    uint32_t info = entry->eax;
    uint32_t local = entry->esp - 0x10;
    uint32_t version;
    uint32_t major;
    uint32_t minor;
    uint32_t ecx;
    uint32_t eax;
    uint32_t edx;
    uint32_t nt;
    uint32_t argument;
    port_open_frame(&port, calls, services, globals, entry, 0x18);
    /* The system version (import 0x4f1c00): +0x70 major.minor, +0x74 the high bit (not NT),
     * +0x78 and +0x80 major 4 or above, +0x7c its inverse, +0x84 Win32s, +0x88 large memory
     * (import 0x4f1be0); then 0x4de900, the two grey brushes (import 0x4f17d8), 0x4de810 and the
     * arrow and wait cursors (import 0x4f1a38). */
    version = port_call(&port, 0x4f1c00, entry->eax, entry->edx, info, entry->ecx);
    major = version & 0xff;
    minor = (version >> 8) & 0xff;
    port_set32(&port, local, 0, minor);
    ecx = (major << 8) + minor;
    port_set32(&port, info, 0x70, ecx);
    port_set32(&port, info, 0x74, (version & 0x80000000u) != 0);
    nt = (int32_t)major >= 4;
    port_set32(&port, info, 0x78, nt);
    edx = 1 - nt;
    port_set32(&port, info, 0x7c, edx);
    port_set32(&port, info, 0x80, nt);
    eax = port_u32(&port, info, 0x74) != 0 && nt == 0;
    port_set32(&port, info, 0x88, 0);
    port_set32(&port, info, 0x84, eax);
    if (port_u32(&port, info, 0x78) != 0)
    {
        argument = 0;
        eax = port_call_stack(&port, 0x4f1be0, eax, edx, info, ecx, &argument, 1);
        edx = vertrix_lift_edx;
        port_set32(&port, info, 0x88, eax >= 0x40000);
    }
    eax = port_call(&port, 0x4de900, info, edx, info, ecx);
    argument = 0xc0c0c0;
    eax = port_call_stack(&port, 0x4f17d8, eax, vertrix_lift_edx, info, ecx, &argument, 1);
    argument = 0x808080;
    port_set32(&port, info, 0x20, eax);
    eax = port_call_stack(&port, 0x4f17d8, eax, vertrix_lift_edx, info, ecx, &argument, 1);
    port_set32(&port, info, 0x2c, 0);
    port_set32(&port, info, 0x30, 0);
    port_set32(&port, info, 0x28, 0);
    port_set32(&port, info, 0x34, 0);
    port_set32(&port, info, 0x3c, 0);
    port_set32(&port, info, 0x38, 0);
    port_set32(&port, info, 0x24, eax);
    port_set32(&port, info, 0x40, 0);
    eax = port_call(&port, 0x4de810, info, vertrix_lift_edx, info, ecx);
    {
        uint32_t cursor[2];
        cursor[0] = 0;
        cursor[1] = 0x7f02;
        eax = port_call_stack(&port, 0x4f1a38, eax, vertrix_lift_edx, info, ecx, cursor, 2);
        port_set32(&port, info, 0x58, eax);
        cursor[1] = 0x7f00;
        eax = port_call_stack(&port, 0x4f1a38, eax, vertrix_lift_edx, info, ecx, cursor, 2);
    }
    port_set32(&port, info, 0x60, 0);
    port_set32(&port, info, 0x5c, eax);
    port_set32(&port, info, 0x10, (port_u32(&port, info, 0x78) != 0) + 1);
    port_set32(&port, info, 0x6c, 0);
    port_set32(&port, info, 0x60, 0);
    port_set32(&port, info, 0x14, (port_u32(&port, info, 0x78) != 0) + 1);
    return port_return(&port, info, entry->edx);
}

uint32_t vertrix_port_sound_device_open(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[0x40 + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, 0x40);
    port_set32(&port, 0, 0x5589e0, 0);
    port_set32(&port, 0, 0x598dac, 0);
    port_set32(&port, 0, 0x5589d4, 0);
    port_set32(&port, 0, 0x598d60, 0);
    port_set32(&port, 0, 0x598da8, 1);
    port_set32(&port, 0, 0x5589dc, 1);
    /* The output device (0x40a950) set to 44100 Hz (0x40a8f0) in 16-bit stereo (0x40a9d0, the
     * format 0x101); success sets 0x5589e0. */
    eax = port_call(&port, 0x40a950, ebp - 0x10, 0, entry->ebx, entry->ecx);
    if (eax != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call(&port, 0x40a8f0, port_u32(&port, ebp, -0x10u), ebp - 0x3c, 0xac44, entry->ecx);
    port_set16(&port, ebp, -0x12u, 0xac44);
    port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x10u));
    port_set16(&port, ebp, -0x14u, 0x101);
    eax = port_call(&port, 0x40a9d0, ebp - 0x18, 0x101, 0xac44, entry->ecx);
    if (eax == 0)
    {
        port_set32(&port, 0, 0x5589e0, 1);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_font_set_construct(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then 0x20 bytes holding the guard record. */
    enum
    {
        BELOW = 0x38,
        GUARD = 0x517740
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t part;
    uint32_t set;
    uint32_t index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, ebp, -0x34u, port.env.chain);
    port_set32(&port, ebp, -0x30u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x2cu, GUARD);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x20u, object);
    port_set8(&port, ebp, -0x1cu, 0);
    /* The base (0x47e4f0), then three parts at +0x1ec, +0x200 and +0x214 (0x48d520), the guard
     * state counting them; the set's table is 0x517994 with its part numbers, the set is kept at
     * 0x558ccc and the eleven slots from 0x5bb47c are cleared. */
    part = port_call(&port, 0x47e4f0, object, object, 4, 3);
    port_set32(&port, ebp, -0x28u, 1);
    part = port_call(&port, 0x48d520, part + 0x1ec, 2, 4, 3);
    port_set32(&port, ebp, -0x28u, vertrix_lift_edx);
    part = port_call(&port, 0x48d520, part + 0x14, vertrix_lift_edx, 4, 3);
    port_set32(&port, ebp, -0x28u, 3);
    set = port_call(&port, 0x48d520, part + 0x14, vertrix_lift_edx, 4, 3) - 0x214;
    port_set32(&port, ebp, -0x28u, 4);
    for (index = 0; index < 11; index++)
    {
        port_set32(&port, 0, 0x5bb47c + index * 4, 0);
    }
    port_set32(&port, set, 0x1c8, 0x517994);
    port_set8(&port, set, 0x1cc, 3);
    port_set8(&port, set, 0x1d0, 4);
    port_set8(&port, set, 0x1d8, 5);
    port_set8(&port, set, 0x1e0, 6);
    port_set8(&port, set, 0x1e2, 7);
    port_set8(&port, set, 0x1e4, 8);
    port_set8(&port, set, 0x1e5, 9);
    port_set8(&port, set, 0x1e6, 0xa);
    port_set8(&port, set, 0x1e7, 2);
    port_set32(&port, 0, 0x558ccc, set);
    return port_return(&port, set, entry->edx);
}

uint32_t vertrix_port_surface_lock_test(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then 0x64 bytes: a 100-byte surface description. */
    enum
    {
        BELOW = 0x7c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t display = entry->eax;
    uint32_t description = ebp - 0x78;
    uint32_t attempt;
    uint32_t ecx = entry->ecx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    /* Up to twice: lock the surface at +0x68 (method +0x14, flags 0x1000400) and, when that
     * works, unlock the one at +0x64 (method +0x2c); 1 once both work, 0 when either fails. */
    for (attempt = 0; attempt < 2; attempt++)
    {
        uint32_t surface;
        uint32_t other;
        uint32_t table;
        uint32_t lock[6];
        uint32_t unlock[3];
        port_set32(&port, description, 0, 0x64);
        port_set32(&port, ebp, -0x28u, 0);
        surface = port_u32(&port, display, 0x68);
        ecx = port_u32(&port, surface, 0);
        lock[0] = surface;
        lock[1] = 0;
        lock[2] = 0;
        lock[3] = 0;
        lock[4] = 0x1000400;
        lock[5] = description;
        if (port_call_stack(&port, port_u32(&port, ecx, 0x14), surface, description, attempt, ecx,
                            lock, 6) != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        other = port_u32(&port, display, 0x64);
        table = port_u32(&port, other, 0);
        unlock[0] = other;
        unlock[1] = 0;
        unlock[2] = 1;
        if (port_call_stack(&port, port_u32(&port, table, 0x2c), other, table, attempt, ecx, unlock,
                            3) != 0)
        {
            return port_return(&port, 0, entry->edx);
        }
    }
    return port_return(&port, 1, entry->edx);
}

uint32_t vertrix_port_sounds_load_all(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, then 0x104 bytes: the path buffer. */
    enum
    {
        BELOW = 0x118,
        NAMES = 0x532ebc,
        SLOTS = 0x533164,
        COUNT = 0x4c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t path = ebp - 0x114;
    uint32_t index;
    uint32_t eax = entry->eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    /* Each of the 76 sounds: ".\SON\" (0x4fcef0) and its name joined (0x45f540), loaded
     * (0x482aa0) into its slot, the progress advanced by one (0x418270). */
    for (index = 0; index < COUNT; index++)
    {
        uint32_t name = port_u32(&port, 0, NAMES + index * 4);
        port_set32(&port, 0, SLOTS + index * 4, 0);
        port_call(&port, 0x45f540, path, 0x4fcef0, name, index);
        eax = port_call(&port, 0x482aa0, path, vertrix_lift_edx, name, index);
        port_set32(&port, 0, SLOTS + index * 4, eax);
        eax = port_call(&port, 0x418270, 1, vertrix_lift_edx, name, index + 1);
    }
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_sound_start(PORT_SIGNATURE)
{
    enum
    {
        SOUND_ON = 0x598d60,
        VOLUME_ON = 0x598da8,
        PLAYING = 0x598d68,
        VOICES = 0x598d88
    };
    Port port;
    uint32_t ebx = entry->ebx;
    uint32_t sound = entry->eax & 0xff;
    uint32_t slot = sound * 4;
    uint32_t sample;
    uint32_t voice;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, SOUND_ON) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (port_u32(&port, 0, VOLUME_ON) == 0)
    {
        ebx = 0;
    }
    /* The sound is stopped first (0x482b40); a sample left in edx is played on its voice: started
     * (0x40adb0), at the sample's rate word +0x14 (0x40adf0) and the volume (0x40ae00). */
    port_call(&port, 0x482b40, sound, entry->edx, ebx, sound);
    sample = vertrix_lift_edx;
    if (sample == 0)
    {
        port_set32(&port, 0, PLAYING + slot, 0);
        return port_return(&port, 0, 0);
    }
    voice = port_u32(&port, 0, VOICES + slot);
    port_set32(&port, 0, PLAYING + slot, sample);
    port_call(&port, 0x40adb0, voice, sample, ebx, slot);
    port_call(&port, 0x40adf0, port_u32(&port, 0, VOICES + slot),
              port_u16(&port, port_u32(&port, 0, PLAYING + slot), 0x14), ebx, slot);
    port_call(&port, 0x40ae00, port_u32(&port, 0, VOICES + slot), ebx, ebx, slot);
    return port_return(&port, 1, vertrix_lift_edx);
}

uint32_t vertrix_port_scene_enter_game(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, then 0x14 bytes holding the guard record. */
    enum
    {
        BELOW = 0x28,
        GUARD = 0x513fe8
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    uint32_t record = ebp - 0x24;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    /* 0x4b7cd0, the flag cleared (0x41a930), 0x418d50, the flag entered with the leave routine
     * 0x41a800 (0x41a940), 0x418820, then the next step 0x41a520 (0x418840). */
    port_call(&port, 0x4b7cd0, record, GUARD_HANDLER, GUARD, scene);
    port_call(&port, 0x41a930, scene, vertrix_lift_edx, GUARD, scene);
    port_call(&port, 0x418d50, scene, vertrix_lift_edx, GUARD, scene);
    port_call(&port, 0x41a940, scene, 0x41a800, GUARD, scene);
    port_call(&port, 0x418820, scene, vertrix_lift_edx, GUARD, scene);
    port_call(&port, 0x418840, scene, 0x41a520, GUARD, scene);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}

uint32_t vertrix_port_sound_device_caps(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, then 0x34 bytes: the device capabilities. */
    enum
    {
        BELOW = 0x48,
        GET_CAPS = 0x4f173c,
        UNKNOWN_NAME = 0x50c814
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t info = entry->eax;
    uint32_t caps = ebp - 0x44;
    uint32_t name = ebp - 0x3c;
    uint32_t arguments[3];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    /* The wave mapper's capabilities (waveOutGetDevCapsA); on failure the name 0x50c814 and no
     * formats. The name (30 bytes, 0x4eb860) goes to +2, version 0x100 to +0 and the formats to
     * +0x20. */
    arguments[0] = 0xffffffffu;
    arguments[1] = caps;
    arguments[2] = 0x34;
    if (port_call_stack(&port, GET_CAPS, caps, entry->edx, entry->ebx, entry->ecx, arguments, 3) !=
        0)
    {
        port_call(&port, 0x4eb860, name, UNKNOWN_NAME, 0x20, entry->ecx);
        port_set32(&port, ebp, -0x1cu, 0);
    }
    port_call(&port, 0x4eb860, info + 2, name, 0x1e, entry->ecx);
    port_set16(&port, info, 0, 0x100);
    port_set32(&port, info, 0x20, port_u32(&port, ebp, -0x1cu));
    return port_return(&port, 0, entry->edx);
}

uint32_t vertrix_port_display_start(PORT_SIGNATURE)
{
    enum
    {
        DISPLAY = 0x5b9c50,
        SHOW_CURSOR = 0x4f1ae4
    };
    Port port;
    uint32_t window = entry->eax;
    uint32_t mode = entry->edx & 0xff;
    uint32_t eax;
    uint32_t hide = 0;
    port_open(&port, calls, services, globals, entry);
    /* The display 0x5b9c50 opened on the window in the mode (0x484b60); when its surfaces lock
     * (0x487080) the window is shown (0x4ccdd0 with 3) and the cursor hidden, otherwise the display
     * is closed (0x486e20). 1 once started. */
    if (port_call(&port, 0x484b60, DISPLAY, window, mode, window) != 1)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    if (port_call(&port, 0x487080, DISPLAY, vertrix_lift_edx, mode, window) == 0)
    {
        port_call(&port, 0x486e20, DISPLAY, window, mode, window);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    eax = port_call(&port, 0x4ccdd0, window, 3, mode, window);
    port_call_stack(&port, SHOW_CURSOR, eax, vertrix_lift_edx, mode, window, &hide, 1);
    return port_return(&port, 1, vertrix_lift_edx);
}

uint32_t vertrix_port_handler_table_setup(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then 0x5c bytes: the guard record and three
     * three-dword handler records, each copied once. */
    enum
    {
        BELOW = 0x74,
        GUARD = 0x513f50
    };
    static const uint32_t cleared[] = {0x4f9dd4, 0x4f9dd8, 0x4f9df4, 0x4f9df8};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x70;
    unsigned index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x6cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x68u, GUARD);
    port_set32(&port, ebp, -0x64u, 0);
    /* The records {0x424180, 0, 0}, {0x4241f0, 0, 0} and {0x424200, 0, 0}, built at -0x2c, -0x38
     * and -0x44 and copied to -0x5c, -0x50 and -0x20, fill 0x4f9db0, 0x4f9e10 and 0x4f9e30; the
     * single handlers 0x4241d0 and 0x4241e0 go to 0x4f9dd0 and 0x4f9df0. */
    port_set32(&port, ebp, -0x2cu, 0x424180);
    port_set32(&port, ebp, -0x28u, 0);
    port_set32(&port, ebp, -0x24u, 0);
    for (index = 0; index < 4; index++)
    {
        port_set32(&port, 0, cleared[index], 0);
    }
    port_set32(&port, ebp, -0x34u, 0);
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x40u, 0);
    port_set32(&port, ebp, -0x3cu, 0);
    for (index = 0; index < 3; index++)
    {
        port_set32(&port, ebp, -0x5cu + index * 4, port_u32(&port, ebp, -0x2cu + index * 4));
    }
    port_set32(&port, 0, 0x4f9dd0, 0x4241d0);
    port_set32(&port, 0, 0x4f9db0, port_u32(&port, ebp, -0x5cu));
    port_set32(&port, 0, 0x4f9df0, 0x4241e0);
    port_set32(&port, ebp, -0x38u, 0x4241f0);
    port_set32(&port, 0, 0x4f9db4, port_u32(&port, ebp, -0x58u));
    for (index = 0; index < 3; index++)
    {
        port_set32(&port, ebp, -0x50u + index * 4, port_u32(&port, ebp, -0x38u + index * 4));
    }
    port_set32(&port, 0, 0x4f9db8, port_u32(&port, ebp, -0x54u));
    port_set32(&port, ebp, -0x44u, 0x424200);
    port_set32(&port, 0, 0x4f9e10, port_u32(&port, ebp, -0x50u));
    port_set32(&port, 0, 0x4f9e14, port_u32(&port, ebp, -0x4cu));
    for (index = 0; index < 3; index++)
    {
        port_set32(&port, ebp, -0x20u + index * 4, port_u32(&port, ebp, -0x44u + index * 4));
    }
    port_set32(&port, 0, 0x4f9e18, port_u32(&port, ebp, -0x48u));
    port_set32(&port, 0, 0x4f9e50, 0);
    port_set32(&port, 0, 0x4f9e30, port_u32(&port, ebp, -0x20u));
    port_set32(&port, 0, 0x4f9e54, 0);
    port_set32(&port, 0, 0x4f9e34, port_u32(&port, ebp, -0x1cu));
    port_set32(&port, 0, 0x4f9e38, port_u32(&port, ebp, -0x18u));
    port_set32(&port, 0, 0x4f9e58, 0);
    port_call(&port, 0x4d30f0, 0x540618, 0x4f9e5c, 0, GUARD);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}

uint32_t vertrix_port_music_start(PORT_SIGNATURE)
{
    /* push ebp, ecx, esi, edi, then 0x11c bytes: the guard record, the name string and the path. */
    enum
    {
        BELOW = 0x12c,
        GUARD = 0x513f88,
        MUSIC_FOLDER = 0x4fcce0,
        NO_MUSIC = 0x50d7c9
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t track = entry->edx;
    uint32_t mode = entry->ebx;
    uint32_t record = ebp - 0x24;
    uint32_t name = ebp - 0x10;
    uint32_t path = ebp - 0x128;
    uint32_t row;
    uint32_t ebx;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    /* The track's name: row [0x532ba0] (0x70 bytes each) of 0x4f83bc picks a string of 0x5330a8,
     * copied (0x4ca090). The path ".\MUSIQUE\" + name (0x45f540), or + "MUSNULL.XM" when it does
     * not exist (0x45f590); audio is shut down (0x478ae0), the module loaded in the mode
     * (0x478910), the input mode (0x478b40) and volume [0x532b9c] (0x4828f0) applied. */
    row = port_u32(&port, 0, 0x532ba0) * 0x70;
    port_call(&port, 0x4ca090, name, port_u32(&port, row + track * 4, 0x4f83bc) * 4 + 0x5330a8,
              GUARD, mode);
    port_set32(&port, ebp, -0x18u, 1);
    ebx = port_u32(&port, name, 0);
    port_call(&port, 0x45f540, path, MUSIC_FOLDER, ebx, mode);
    eax = port_call(&port, 0x45f590, path, vertrix_lift_edx, ebx, mode);
    if (eax == 0)
    {
        ebx = NO_MUSIC;
        eax = port_call(&port, 0x45f540, path, MUSIC_FOLDER, ebx, mode);
    }
    port_call(&port, 0x478ae0, eax, vertrix_lift_edx, ebx, mode);
    port_call(&port, 0x478910, path, mode, ebx, mode);
    port_call(&port, 0x478b40, port_u32(&port, 0, 0x532b98), vertrix_lift_edx, ebx, mode);
    port_call(&port, 0x4828f0, port_u32(&port, 0, 0x532b9c), 0, ebx, 0);
    port_set32(&port, ebp, -0x18u, vertrix_lift_edx);
    port_call(&port, 0x4ca210, name, vertrix_lift_edx, ebx, 0);
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, port_u32(&port, record, 0), vertrix_lift_edx);
}

uint32_t vertrix_port_mouse_axis_mode_set(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, esi, edi, then 0x14 bytes: the axis mode property. */
    enum
    {
        BELOW = 0x28,
        UNACQUIRE = 0x20,
        SET_PROPERTY = 0x18,
        ACQUIRE = 0x1c,
        AXIS_MODE = 2
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t mouse = entry->eax;
    uint32_t property = ebp - 0x24;
    uint32_t device;
    uint32_t table;
    uint32_t arguments[3];
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    /* An acquired device (+0xc) is released around the change: the property (size 0x14, header
     * 0x10, whole device) is relative when edx is 0, absolute otherwise. */
    if (port_u32(&port, mouse, 0xc) != 0)
    {
        device = port_u32(&port, mouse, 0x30);
        table = port_u32(&port, device, 0);
        port_call_stack(&port, port_u32(&port, table, UNACQUIRE), device, table, mouse, entry->ecx,
                        &device, 1);
    }
    port_set32(&port, property, 0, 0x14);
    port_set32(&port, property, 4, 0x10);
    port_set32(&port, property, 8, 0);
    port_set32(&port, property, 0xc, 0);
    port_set32(&port, property, 0x10, entry->edx == 0);
    device = port_u32(&port, mouse, 0x30);
    table = port_u32(&port, device, 0);
    arguments[0] = device;
    arguments[1] = AXIS_MODE;
    arguments[2] = property;
    eax = port_call_stack(&port, port_u32(&port, table, SET_PROPERTY), device, table, mouse, 0x14,
                          arguments, 3);
    if (port_u32(&port, mouse, 0xc) == 0)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    device = port_u32(&port, mouse, 0x30);
    table = port_u32(&port, device, 0);
    eax = port_call_stack(&port, port_u32(&port, table, ACQUIRE), table, vertrix_lift_edx, device,
                          0x14, &device, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}

uint32_t vertrix_port_surface_describe(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, esi, edi, then 0x18 bytes: the guard record and a string. */
    enum
    {
        BELOW = 0x2c,
        GUARD = 0x516840
    };
    static const uint32_t bits[5] = {0x50ea2b, 0x50ea2d, 0x50ea30, 0x50ea33, 0x50ea36};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t surface = entry->eax;
    uint32_t record = ebp - 0x28;
    uint32_t text = ebp - 0x14;
    uint32_t depth;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x24u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x20u, GUARD);
    port_set32(&port, ebp, -0x1cu, 0);
    /* A text built and dropped: "nb bits   : " and the depth (+0xd: 8, 15, 16, 24 or 32), then
     * "use pitch :" and YES or NO by +0x10 (0x4ca070, 0x4ca370, 0x4ca600, 0x4ca210). */
    port_call(&port, 0x4ca070, text, GUARD_HANDLER, GUARD, surface);
    port_set32(&port, ebp, -0x1cu, 1);
    port_call(&port, 0x4ca370, text, 0x50ea1e, GUARD, surface);
    depth = port_u8(&port, surface, 0xd);
    if (depth < 5)
    {
        port_call(&port, 0x4ca600, text, bits[depth], GUARD, surface);
    }
    port_call(&port, 0x4ca370, text, 0x50ea3c, GUARD, surface);
    port_call(&port, 0x4ca600, text, port_u32(&port, surface, 0x10) == 1 ? 0x50ea48 : 0x50ea4c,
              GUARD, surface);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call(&port, 0x4ca210, text, 0, GUARD, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    return port_return(&port, port_u32(&port, record, 0), vertrix_lift_edx);
}

uint32_t vertrix_port_image_load_any(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then 0x18 bytes: the guard record and the extension. */
    enum
    {
        BELOW = 0x30,
        GUARD = 0x515078,
        IMAGE = 0x5b9c60
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t path = entry->eax;
    uint32_t record = ebp - 0x2c;
    uint32_t extension = ebp - 0x18;
    uint32_t bmp;
    uint32_t jpg;
    uint32_t result = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x28u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x24u, GUARD);
    port_set32(&port, ebp, -0x20u, 0);
    /* The path's extension (0x489640) picks the reader: ".BMP" 0x474490, ".JPG" 0x48ad00, into
     * 0x5b9c60; anything else gives 0. */
    port_call(&port, 0x4ca070, extension, GUARD_HANDLER, 0, GUARD);
    port_set32(&port, ebp, -0x20u, 1);
    port_call_stack(&port, 0x489640, path, 0, 0, 0, &extension, 1);
    bmp = port_call(&port, 0x489d00, port_u32(&port, extension, 0), 0x50e13e, 0, 0);
    jpg = port_call(&port, 0x489d00, port_u32(&port, extension, 0), 0x50e143, bmp, bmp);
    if (bmp == 1)
    {
        result = port_call(&port, 0x474490, path, IMAGE, bmp, bmp);
    }
    else if (jpg == 1)
    {
        result = port_call(&port, 0x48ad00, path, IMAGE, bmp, bmp);
    }
    port_set32(&port, ebp, -0x20u, 0);
    port_call(&port, 0x4ca210, extension, 0, bmp, 0);
    port_set32(&port, ebp, -0x20u, 0);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_saved_file_load(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, esi, edi, then 0x128 bytes: the guard record and a parser. */
    enum
    {
        BELOW = 0x13c,
        GUARD = 0x514528
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t saved = entry->eax;
    uint32_t record = ebp - 0x24;
    uint32_t parser = ebp - 0x138;
    uint32_t name;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, GUARD);
    port_set32(&port, ebp, -0x18u, 0);
    /* A file that is found (0x4895e0) and passes 0x4895b0 with 0 is opened by a parser on the
     * stack (0x48a620, 0x48a710) and its blocks read (0x4293e0, then 0x48a8c0); the parser is
     * destroyed (0x48a670). */
    if (port_call(&port, 0x4895e0, entry->edx, entry->edx, GUARD_HANDLER, saved) != 1)
    {
        return port_return(&port, port_u32(&port, record, 0), vertrix_lift_edx);
    }
    name = vertrix_lift_edx;
    if (port_call(&port, 0x4895b0, name, name, GUARD_HANDLER, saved) != 0)
    {
        return port_return(&port, port_u32(&port, record, 0), vertrix_lift_edx);
    }
    port_call(&port, 0x48a620, parser, vertrix_lift_edx, GUARD_HANDLER, saved);
    port_set32(&port, ebp, -0x18u, 1);
    if (port_call(&port, 0x48a710, parser, vertrix_lift_edx, 0, saved) == 1)
    {
        port_call(&port, 0x4293e0, saved, parser, 0, saved);
        port_call(&port, 0x48a8c0, parser, vertrix_lift_edx, 0, saved);
    }
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, 0x48a670, parser, 0, 0, 0);
    port_set32(&port, ebp, -0x18u, 0);
    return port_return(&port, port_u32(&port, record, 0), vertrix_lift_edx);
}

uint32_t vertrix_port_noise_fill(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then 8 bytes: the time and a divisor. */
    enum
    {
        BELOW = 0x20,
        TIME_NOW = 0x4ec1a0,
        SEED = 0x4d8620,
        RANDOM = 0x4d85fc,
        SAMPLES = 0x1001,
        RESEED = 0x1f4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t reader = entry->eax;
    uint32_t time = ebp - 0x1c;
    uint32_t left = SAMPLES;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    /* Seeded from the time (0x4ec1a0, 0x4d8620) and again every 500 samples, 4097 words from the
     * start (+0) on: two 15-bit randoms (0x4d85fc) and one bit summed, kept to 16 bits; the
     * cursor +8 follows, and the reader restarts (0x482540). */
    eax = port_call(&port, TIME_NOW, time, entry->edx, entry->ebx, reader);
    eax = port_call(&port, SEED, eax, vertrix_lift_edx, entry->ebx, reader);
    edx = vertrix_lift_edx;
    eax = port_u32(&port, reader, 0);
    ebx = RESEED;
    port_set32(&port, reader, 8, eax);
    do
    {
        int32_t random;
        int32_t sum;
        uint32_t cursor;
        random = (int32_t)port_call(&port, RANDOM, eax, edx, ebx, reader);
        edx = (uint32_t)(random % 0x8000);
        eax = (uint32_t)(random / 0x8000);
        random = (int32_t)port_call(&port, RANDOM, eax, edx, ebx, reader);
        sum = (int32_t)vertrix_lift_edx;
        port_set32(&port, ebp, -0x18u, 0x8000);
        edx = (uint32_t)(random % 0x8000);
        eax = (uint32_t)(random / 0x8000);
        random = (int32_t)port_call(&port, RANDOM, eax, edx, ebx, reader);
        sum = (int32_t)((uint32_t)sum + vertrix_lift_edx);
        port_set32(&port, ebp, -0x18u, 2);
        sum = (int32_t)((uint32_t)(random % 2) + (uint32_t)sum);
        cursor = port_u32(&port, reader, 8);
        port_set16(&port, cursor, 0, (uint32_t)(sum % 0x10000));
        eax = cursor;
        edx = port_u32(&port, reader, 8) + 2;
        left--;
        port_set32(&port, reader, 8, edx);
        ebx = (ebx & 0xffff0000u) | ((ebx - 1) & 0xffff);
        if ((ebx & 0xffff) == 0)
        {
            ebx = RESEED;
            eax = port_call(&port, TIME_NOW, time, edx, ebx, reader);
            eax = port_call(&port, SEED, eax, vertrix_lift_edx, ebx, reader);
            edx = vertrix_lift_edx;
        }
    } while (left != 0);
    eax = port_call(&port, 0x482540, reader, edx, ebx, reader);
    return port_return(&port, eax, entry->edx);
}

/* The option label shape of 0x445f00 and its six copies: the option's value ([0x532bfc] plus the
 * menu's +0x70) formatted by `format` into a string (with 0x532c04) set as the label's (+0x160)
 * text (+0x15c, 0x4ca370), drawn in colour 7 when it is [0x532c00] and 0xd otherwise. */
static uint32_t option_label_set(PORT_SIGNATURE, uint32_t format, uint32_t guard)
{
    /* push ebp, ebx, ecx, edx, esi, edi, then 0x18 bytes: the guard record and the string. */
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t menu = entry->eax;
    uint32_t record = ebp - 0x2c;
    uint32_t text = ebp - 0x18;
    uint32_t value;
    uint32_t label;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, ebp, -0x14u, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x28u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x24u, guard);
    port_set32(&port, ebp, -0x20u, 0);
    value = port_u32(&port, 0, 0x532bfc) + port_u32(&port, menu, 0x70);
    label = port_u32(&port, menu, 0x160);
    result = port_call(&port, format, 0x532c04, text, value, value);
    port_set32(&port, ebp, -0x20u, 1);
    port_call(&port, 0x4ca370, label + 0x15c, port_u32(&port, result, 0), 0, value);
    port_set32(&port, ebp, -0x20u, 0);
    port_call(&port, 0x4ca210, text, 0, 0, value);
    port_set32(&port, ebp, -0x20u, 0);
    port_set8(&port, label, 0x52, value == port_u32(&port, 0, 0x532c00) ? 7 : 0xd);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}

uint32_t vertrix_port_option_label_445f00(PORT_SIGNATURE)
{
    return option_label_set(calls, services, globals, entry, 0x4b73a0, 0x5151bc);
}

uint32_t vertrix_port_option_label_445fc0(PORT_SIGNATURE)
{
    return option_label_set(calls, services, globals, entry, 0x4b7300, 0x5151c8);
}

uint32_t vertrix_port_option_label_446080(PORT_SIGNATURE)
{
    return option_label_set(calls, services, globals, entry, 0x4b7080, 0x5151d4);
}

uint32_t vertrix_port_option_label_446140(PORT_SIGNATURE)
{
    return option_label_set(calls, services, globals, entry, 0x4b7120, 0x5151e0);
}

uint32_t vertrix_port_option_label_446200(PORT_SIGNATURE)
{
    return option_label_set(calls, services, globals, entry, 0x4b71c0, 0x5151ec);
}

uint32_t vertrix_port_option_label_4462c0(PORT_SIGNATURE)
{
    return option_label_set(calls, services, globals, entry, 0x4b7260, 0x5151f8);
}

uint32_t vertrix_port_option_label_446380(PORT_SIGNATURE)
{
    return option_label_set(calls, services, globals, entry, 0x4b7420, 0x515204);
}

/* The menu item input shape of 0x449500 and its five copies, for the item whose settings word is at
 * `setting` and whose chosen state is `chosen`: an item 0x449460 accepts returns 1; otherwise it is
 * highlighted (0x4493d0 with 0x74) and chosen (0x4ac8f0) by a click inside it (the input 0x54d640's
 * key 0x74 (0x476480), its position (0x4764a0) hit-tested by 0x4b0b70) or, for a keyed item
 * (+0x70), its key (+0x64); then 0x449390 runs. */
static uint32_t menu_item_input(PORT_SIGNATURE, uint32_t setting, uint32_t chosen)
{
    /* push ebp, ebx, ecx, edx, esi, then 0xc bytes: the click's three results. */
    enum
    {
        BELOW = 0x20,
        INPUT = 0x54d640,
        CLICK = 0x74
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t item = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result;
    int choose = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    result = port_call(&port, 0x449460, item, port_u32(&port, 0, setting), ebx, ecx);
    if (result == 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, 0x4493d0, item, CLICK, ebx, ecx);
    if (port_call(&port, 0x476480, INPUT, vertrix_lift_edx, ebx, ecx) == 1)
    {
        uint32_t out = ebp - 0x18;
        ecx = ebp - 0x14;
        port_call_stack(&port, 0x4764a0, INPUT, CLICK, ebp - 0x1c, ecx, &out, 1);
        ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x14u);
        choose = (port_call(&port, 0x4b0b70, item,
                            (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu), ebx, ecx) &
                  0xff) != 0;
    }
    else if (port_u32(&port, item, 0x70) == 1)
    {
        choose = port_call(&port, 0x476480, INPUT, port_u16(&port, item, 0x64), ebx, ecx) == 1;
    }
    if (choose)
    {
        port_call(&port, 0x4ac8f0, item, chosen, ebx, ecx);
    }
    result = port_call(&port, 0x449390, item, port_u32(&port, 0, setting), ebx, ecx);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_menu_item_input_449500(PORT_SIGNATURE)
{
    return menu_item_input(calls, services, globals, entry, 0x4fbed0, 0x4495b0);
}

uint32_t vertrix_port_menu_item_input_449660(PORT_SIGNATURE)
{
    return menu_item_input(calls, services, globals, entry, 0x4fbee0, 0x449710);
}

uint32_t vertrix_port_menu_item_input_4497c0(PORT_SIGNATURE)
{
    return menu_item_input(calls, services, globals, entry, 0x4fbed8, 0x449870);
}

uint32_t vertrix_port_menu_item_input_449aa0(PORT_SIGNATURE)
{
    return menu_item_input(calls, services, globals, entry, 0x4fbee8, 0x449b50);
}

uint32_t vertrix_port_menu_item_input_449c00(PORT_SIGNATURE)
{
    return menu_item_input(calls, services, globals, entry, 0x4fbef8, 0x449cb0);
}

uint32_t vertrix_port_menu_item_input_449d60(PORT_SIGNATURE)
{
    return menu_item_input(calls, services, globals, entry, 0x4fbef0, 0x449e10);
}

/* The actor frame shape of 0x44d250, 0x44c4c0 and their copies: `first` and 0x4ac500, then, when
 * the counter is due (0x4ac520), its steps consumed (0x4ac540, 0x4ac5b0), the fade (+0x4a set to
 * `start`, +0x4c to `fade`) stepped (0x4ad530) and, once it is done, the update `next` set
 * (0x4ac8f0); the image is refreshed (0x4ac8a0) in every case. */
static uint32_t actor_fade_frame_with(PORT_SIGNATURE, uint32_t first, uint32_t next, uint32_t start,
                                      uint32_t fade)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, first, actor, entry->edx, ebx, actor);
    port_call(&port, 0x4ac500, actor, vertrix_lift_edx, ebx, actor);
    if (port_call(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor) == 1)
    {
        result = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_call(&port, 0x4ac5b0, actor, result, ebx, actor);
        port_set16(&port, actor, 0x4a, start);
        port_set16(&port, actor, 0x4c, fade);
        if (port_call(&port, 0x4ad530, actor, vertrix_lift_edx, ebx, actor) == 0)
        {
            port_call(&port, 0x4ac8f0, actor, next, ebx, actor);
        }
    }
    result = port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_fade_frame_44d250(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44d2c0, 0, 0x14);
}

uint32_t vertrix_port_actor_fade_frame_44d4f0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44d560, 0, 0x14);
}

uint32_t vertrix_port_actor_fade_frame_44d840(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0, 0x14);
}

uint32_t vertrix_port_actor_fade_frame_44dc80(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0, 0x14);
}

uint32_t vertrix_port_actor_fade_frame_44e670(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0, 0xa);
}

uint32_t vertrix_port_actor_fade_frame_44f0b0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0, 0x14);
}

uint32_t vertrix_port_actor_fade_frame_44f770(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0, 0xa);
}

uint32_t vertrix_port_actor_fade_frame_44f920(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0, 0x14);
}

uint32_t vertrix_port_actor_fade_frame_45be40(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0, 0x14);
}

uint32_t vertrix_port_actor_fade_frame_44c4c0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x44c2a0, 0x44c530, 0x28, 0xa);
}

uint32_t vertrix_port_actor_fade_frame_44d1e0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44d250, 0x64, 0xa);
}

uint32_t vertrix_port_actor_fade_frame_44d480(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44d4f0, 0xff9c, 0x14);
}

uint32_t vertrix_port_actor_fade_frame_44d7d0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44d840, 0x32, 0xa);
}

uint32_t vertrix_port_actor_fade_frame_44f040(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44f0b0, 0x32, 0xa);
}

uint32_t vertrix_port_actor_fade_frame_44f700(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44f770, 0x64, 0xa);
}

uint32_t vertrix_port_actor_fade_frame_45bdd0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x45be40, 0xff9c, 0x14);
}

/* The scene step shape of 0x41c0f0 and its six copies: under the guard record `guard` run `first`,
 * then set the scene's step `step` (0x418840) and next `next` (0x418820). */
static uint32_t scene_step_with(PORT_SIGNATURE, uint32_t first, uint32_t step, uint32_t next,
                                uint32_t guard)
{
    /* push ebp, ebx, ecx, edx, esi, then 0x14 bytes holding the guard record. */
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t scene = entry->eax;
    uint32_t record = ebp - 0x24;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, record, 0, port.env.chain);
    port_set32(&port, ebp, -0x20u, GUARD_HANDLER);
    port_set32(&port, ebp, -0x1cu, guard);
    port_set32(&port, ebp, -0x18u, 0);
    port_call(&port, first, scene, GUARD_HANDLER, guard, scene);
    port_call(&port, 0x418840, scene, step, guard, scene);
    port_call(&port, 0x418820, scene, next, guard, scene);
    return port_return(&port, port_u32(&port, record, 0), entry->edx);
}

uint32_t vertrix_port_scene_step_41c0f0(PORT_SIGNATURE)
{
    return scene_step_with(calls, services, globals, entry, 0x41c020, 0x421f10, 0x41b680, 0x514024);
}

uint32_t vertrix_port_scene_step_41c160(PORT_SIGNATURE)
{
    return scene_step_with(calls, services, globals, entry, 0x41c020, 0x421f10, 0x41f080, 0x514028);
}

uint32_t vertrix_port_scene_step_41c1d0(PORT_SIGNATURE)
{
    return scene_step_with(calls, services, globals, entry, 0x41c020, 0x421f10, 0x41c6d0, 0x51402c);
}

uint32_t vertrix_port_scene_step_41c240(PORT_SIGNATURE)
{
    return scene_step_with(calls, services, globals, entry, 0x41c020, 0x421f10, 0x41c6d0, 0x514030);
}

uint32_t vertrix_port_scene_step_41c2b0(PORT_SIGNATURE)
{
    return scene_step_with(calls, services, globals, entry, 0x41c020, 0x421f10, 0x41c6d0, 0x514034);
}

uint32_t vertrix_port_scene_step_41c6d0(PORT_SIGNATURE)
{
    return scene_step_with(calls, services, globals, entry, 0x41c410, 0x423960, 0x41c7b0, 0x514044);
}

uint32_t vertrix_port_scene_step_41c740(PORT_SIGNATURE)
{
    return scene_step_with(calls, services, globals, entry, 0x41c410, 0x423960, 0x41c7b0, 0x514048);
}

/* The actor frame shape of 0x44c880 and its copies: `first` and 0x4ac500, then, when the counter is
 * due (0x4ac520), its steps consumed (0x4ac540, 0x4ac5b0), the movement stepped by `stepper` and,
 * once it arrives, the update `next` set (0x4ac8f0); `refresh` runs in every case. */
static uint32_t actor_step_frame(PORT_SIGNATURE, uint32_t first, uint32_t stepper, uint32_t next,
                                 uint32_t refresh)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, first, actor, entry->edx, ebx, actor);
    port_call(&port, 0x4ac500, actor, vertrix_lift_edx, ebx, actor);
    if (port_call(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor) == 1)
    {
        result = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_call(&port, 0x4ac5b0, actor, result, ebx, actor);
        if (port_call(&port, stepper, actor, vertrix_lift_edx, ebx, actor) == 0)
        {
            port_call(&port, 0x4ac8f0, actor, next, ebx, actor);
        }
    }
    result = port_call(&port, refresh, actor, vertrix_lift_edx, ebx, actor);
    return port_return(&port, result, entry->edx);
}

/* The sound cue shape of 0x478570 and its copies: the slot `slot` of 0x54d640 played by `play`
 * (0x4761d0 or 0x476280) at the object's pitch and volume words (+0x48, +0x4a), or at 0x7d00 for
 * both when +0x60 is set. */
static uint32_t sound_cue(PORT_SIGNATURE, uint32_t play, uint32_t slot)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t zero = 0;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, object, 0x60) == 0)
    {
        result = port_call_stack(&port, play, 0x54d640, slot, port_u16(&port, object, 0x48),
                                 port_u16(&port, object, 0x4a), &zero, 1);
    }
    else
    {
        result = port_call_stack(&port, play, 0x54d640, slot, 0x7d00, 0x7d00, &zero, 1);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_step_frame_44c880(PORT_SIGNATURE)
{
    return actor_step_frame(calls, services, globals, entry, 0x4ac1f0, 0x4acab0, 0x44c860,
                            0x4ac8a0);
}

uint32_t vertrix_port_actor_step_frame_44c8e0(PORT_SIGNATURE)
{
    return actor_step_frame(calls, services, globals, entry, 0x4ac1f0, 0x4acab0, 0x44c860,
                            0x4ac8a0);
}

uint32_t vertrix_port_actor_step_frame_44ebe0(PORT_SIGNATURE)
{
    return actor_step_frame(calls, services, globals, entry, 0x4ac1f0, 0x4ad6e0, 0x44ec40,
                            0x4ac8a0);
}

uint32_t vertrix_port_actor_step_frame_4582d0(PORT_SIGNATURE)
{
    return actor_step_frame(calls, services, globals, entry, 0x457810, 0x4ad530, 0x458330,
                            0x457890);
}

uint32_t vertrix_port_actor_step_frame_45b790(PORT_SIGNATURE)
{
    return actor_step_frame(calls, services, globals, entry, 0x4ac1f0, 0x4ad6e0, 0x45b7f0,
                            0x4ac8a0);
}

uint32_t vertrix_port_actor_step_frame_45bd00(PORT_SIGNATURE)
{
    return actor_step_frame(calls, services, globals, entry, 0x4ac1f0, 0x4ad6e0, 0x45bd60,
                            0x4ac8a0);
}

uint32_t vertrix_port_actor_step_frame_45bf20(PORT_SIGNATURE)
{
    return actor_step_frame(calls, services, globals, entry, 0x4ac1f0, 0x4ad6e0, 0x45bf80,
                            0x4ac8a0);
}

uint32_t vertrix_port_sound_cue_478570(PORT_SIGNATURE)
{
    return sound_cue(calls, services, globals, entry, 0x4761d0, 0x72);
}

uint32_t vertrix_port_sound_cue_4785c0(PORT_SIGNATURE)
{
    return sound_cue(calls, services, globals, entry, 0x476280, 0x72);
}

uint32_t vertrix_port_sound_cue_478610(PORT_SIGNATURE)
{
    return sound_cue(calls, services, globals, entry, 0x4761d0, 0x73);
}

uint32_t vertrix_port_sound_cue_478660(PORT_SIGNATURE)
{
    return sound_cue(calls, services, globals, entry, 0x476280, 0x73);
}

uint32_t vertrix_port_sound_cue_4786b0(PORT_SIGNATURE)
{
    return sound_cue(calls, services, globals, entry, 0x4761d0, 0x70);
}

uint32_t vertrix_port_sound_cue_478700(PORT_SIGNATURE)
{
    return sound_cue(calls, services, globals, entry, 0x476280, 0x70);
}

uint32_t vertrix_port_sound_cue_478750(PORT_SIGNATURE)
{
    return sound_cue(calls, services, globals, entry, 0x4761d0, 0x71);
}

uint32_t vertrix_port_sound_cue_4787a0(PORT_SIGNATURE)
{
    return sound_cue(calls, services, globals, entry, 0x476280, 0x71);
}

/* The board action shape of 0x4535d0 and its copies: when the board's (+0x3b0) current action
 * (+0x4c8) is `action`, 0x43acd0; otherwise 0x43ac00 and `apply` on the board. The object left in
 * edx then gets its method +4 (table +0x158), and 0x43bbf0 runs. */
static uint32_t board_action(PORT_SIGNATURE, uint32_t action, uint32_t apply)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t board;
    uint32_t target;
    uint32_t table;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    board = port_u32(&port, object, 0x3b0);
    if (port_u32(&port, board, 0x4c8) == action)
    {
        port_call(&port, 0x43acd0, object, port_u32(&port, object, 0x15c), object, board);
    }
    else
    {
        port_call(&port, 0x43ac00, object, port_u32(&port, object, 0x15c), object, board);
        port_call(&port, apply, board, vertrix_lift_edx, object, board);
    }
    target = vertrix_lift_edx;
    table = port_u32(&port, target, 0x158);
    port_call(&port, port_u32(&port, table, 4), target, target, object, table);
    result = port_call(&port, 0x43bbf0, object, vertrix_lift_edx, object, table);
    return port_return(&port, result, entry->edx);
}

/* The actor frame shape of 0x44f120 and its copies: 0x4ac1f0 and 0x4ac500, then, when the counter
 * is due (0x4ac520), its steps consumed (0x4ac540, 0x4ac5b0), +0x4a set to `start`, the fade
 * stepped (0x4ad530) and, once it is done, the update `next` set (0x4ac8f0); the image is refreshed
 * (0x4ac8a0) in every case. */
static uint32_t actor_swing_frame(PORT_SIGNATURE, uint32_t start, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4ac1f0, actor, entry->edx, ebx, actor);
    port_call(&port, 0x4ac500, actor, vertrix_lift_edx, ebx, actor);
    if (port_call(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor) == 1)
    {
        result = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_call(&port, 0x4ac5b0, actor, result, ebx, actor);
        port_set16(&port, actor, 0x4a, start);
        if (port_call(&port, 0x4ad530, actor, vertrix_lift_edx, ebx, actor) == 0)
        {
            port_call(&port, 0x4ac8f0, actor, next, ebx, actor);
        }
    }
    result = port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_board_action_4535d0(PORT_SIGNATURE)
{
    return board_action(calls, services, globals, entry, 0x23, 0x43cf30);
}

uint32_t vertrix_port_board_action_4537b0(PORT_SIGNATURE)
{
    return board_action(calls, services, globals, entry, 0x2f, 0x43ceb0);
}

uint32_t vertrix_port_board_action_453800(PORT_SIGNATURE)
{
    return board_action(calls, services, globals, entry, 0x31, 0x43cef0);
}

uint32_t vertrix_port_board_action_453850(PORT_SIGNATURE)
{
    return board_action(calls, services, globals, entry, 0x24, 0x43cfb0);
}

uint32_t vertrix_port_board_action_4538a0(PORT_SIGNATURE)
{
    return board_action(calls, services, globals, entry, 0x28, 0x43cff0);
}

uint32_t vertrix_port_board_action_453990(PORT_SIGNATURE)
{
    return board_action(calls, services, globals, entry, 0x2d, 0x43d0b0);
}

uint32_t vertrix_port_board_action_4539e0(PORT_SIGNATURE)
{
    return board_action(calls, services, globals, entry, 0x2e, 0x43d0f0);
}

uint32_t vertrix_port_board_action_453a80(PORT_SIGNATURE)
{
    return board_action(calls, services, globals, entry, 0x2c, 0x43cda0);
}

uint32_t vertrix_port_actor_swing_frame_44f120(PORT_SIGNATURE)
{
    return actor_swing_frame(calls, services, globals, entry, 0x64, 0x44f180);
}

uint32_t vertrix_port_actor_swing_frame_44f180(PORT_SIGNATURE)
{
    return actor_swing_frame(calls, services, globals, entry, 0xff9c, 0x44f120);
}

uint32_t vertrix_port_actor_swing_frame_44f4a0(PORT_SIGNATURE)
{
    return actor_swing_frame(calls, services, globals, entry, 0x64, 0x44f500);
}

uint32_t vertrix_port_actor_swing_frame_44f500(PORT_SIGNATURE)
{
    return actor_swing_frame(calls, services, globals, entry, 0xff9c, 0x44f4a0);
}

uint32_t vertrix_port_actor_swing_frame_44f5d0(PORT_SIGNATURE)
{
    return actor_swing_frame(calls, services, globals, entry, 0x64, 0x44f630);
}

uint32_t vertrix_port_actor_swing_frame_44f630(PORT_SIGNATURE)
{
    return actor_swing_frame(calls, services, globals, entry, 0xff9c, 0x44f5d0);
}

uint32_t vertrix_port_child_check_453570(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t table;
    uint32_t result;
    int passed = 0;
    port_open(&port, calls, services, globals, entry);
    /* The child (+0x15c) is tested by 0x42eca0 and 0x42ecc0 against 0x44c860; when both pass,
     * 0x42ebe0 runs and afterwards 0x43bbf0. Its method +4 (table +0x158) runs in every case. */
    child = port_u32(&port, object, 0x15c);
    if (port_call(&port, 0x42eca0, child, 0x44c860, object, child) != 0 &&
        port_call(&port, 0x42ecc0, child, 0x44c860, object, child) != 0)
    {
        passed = 1;
        port_call(&port, 0x42ebe0, child, vertrix_lift_edx, object, child);
    }
    table = port_u32(&port, child, 0x158);
    result = port_call(&port, port_u32(&port, table, 4), child, table, object, child);
    if (passed)
    {
        result = port_call(&port, 0x43bbf0, object, vertrix_lift_edx, object, child);
    }
    return port_return(&port, result, entry->edx);
}

/* The actor frame shape of 0x44c3e0 and its copies: `first` and 0x4ac500, then, when the counter is
 * due (0x4ac520), its steps consumed (0x4ac540, 0x4ac5b0), the value's goal (+0x5c) and speed
 * (+0x60) set, the value stepped (0x4ad6e0) and, once it arrives, the update `next` set (0x4ac8f0);
 * the image is refreshed (0x4ac8a0) in every case. */
static uint32_t actor_value_frame(PORT_SIGNATURE, uint32_t first, uint32_t goal, uint32_t speed,
                                  uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, first, actor, entry->edx, ebx, actor);
    port_call(&port, 0x4ac500, actor, vertrix_lift_edx, ebx, actor);
    if (port_call(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, actor) == 1)
    {
        result = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, actor);
        port_call(&port, 0x4ac5b0, actor, result, ebx, actor);
        port_set32(&port, actor, 0x5c, goal);
        port_set32(&port, actor, 0x60, speed);
        if (port_call(&port, 0x4ad6e0, actor, vertrix_lift_edx, ebx, actor) == 0)
        {
            port_call(&port, 0x4ac8f0, actor, next, ebx, actor);
        }
    }
    result = port_call(&port, 0x4ac8a0, actor, vertrix_lift_edx, ebx, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_actor_fade_frame_44c9d0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44ca40, 0xc8, 4);
}

uint32_t vertrix_port_actor_fade_frame_44ca40(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c9d0, 0xff38, 4);
}

uint32_t vertrix_port_actor_fade_frame_45b7f0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0xffb0, 4);
}

uint32_t vertrix_port_actor_fade_frame_45bd60(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0xffb0, 4);
}

uint32_t vertrix_port_actor_fade_frame_45bf80(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0xffb0, 4);
}

uint32_t vertrix_port_actor_value_frame_44c3e0(PORT_SIGNATURE)
{
    return actor_value_frame(calls, services, globals, entry, 0x44c2a0, 0x28, 0xa, 0x44c4c0);
}

uint32_t vertrix_port_actor_value_frame_44c450(PORT_SIGNATURE)
{
    return actor_value_frame(calls, services, globals, entry, 0x44c2a0, 0x50, 0xa, 0x44c4c0);
}

uint32_t vertrix_port_actor_value_frame_44d3a0(PORT_SIGNATURE)
{
    return actor_value_frame(calls, services, globals, entry, 0x4ac1f0, 0x64, 0x14, 0x44d410);
}

uint32_t vertrix_port_actor_value_frame_44d5f0(PORT_SIGNATURE)
{
    return actor_value_frame(calls, services, globals, entry, 0x4ac1f0, 0xffffff9c, 0x14, 0x44d660);
}

uint32_t vertrix_port_actor_fade_frame_44c530(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x44c2a0, 0x44c3d0, 0, 2);
}

uint32_t vertrix_port_actor_fade_frame_44e600(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44e670, 0x32, 5);
}

uint32_t vertrix_port_actor_fade_frame_45c0e0(PORT_SIGNATURE)
{
    return actor_fade_frame_with(calls, services, globals, entry, 0x4ac1f0, 0x44c860, 0xffd8, 2);
}

uint32_t vertrix_port_actor_value_frame_44d660(PORT_SIGNATURE)
{
    return actor_value_frame(calls, services, globals, entry, 0x4ac1f0, 0, 0x14, 0x44d6d0);
}

uint32_t vertrix_port_actor_value_frame_45b860(PORT_SIGNATURE)
{
    return actor_value_frame(calls, services, globals, entry, 0x4ac1f0, 0x64, 4, 0x45b8d0);
}

uint32_t vertrix_port_actor_swing_frame_44f1e0(PORT_SIGNATURE)
{
    return actor_swing_frame(calls, services, globals, entry, 0, 0x44c860);
}

uint32_t vertrix_port_bank_allocate_5464e4(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    result = port_call(&port, 0x487640, 0x5464e4, 8, entry->ebx, entry->ecx);
    return port_return(&port, result, entry->edx);
}

/* The button frame shape of 0x456390 and its two copies: the counter stepped (0x4ac500) and, when
 * due (0x4ac520), the fade from 0 by 5 (0x4ad530); then, when the cursor (0x558944, 0x558946, or
 * 0x7d00 while 0x558958 is set) is over the button (0x4b0b70) it is lit (+0x48 = 0x23); a click
 * inside it (the input 0x54d640's key 0x74, its position by 0x4764a0) sets the update `next` and
 * +0x48 to 0x3c. */
static uint32_t button_frame(PORT_SIGNATURE, uint32_t next)
{
    /* push ebp, ebx, ecx, edx, esi, then 0xc bytes: the click's three results. */
    enum
    {
        BELOW = 0x20,
        INPUT = 0x54d640,
        CLICK = 0x74,
        OFF_SCREEN = 0x7d00
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t button = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_call(&port, 0x4ac500, button, entry->edx, ebx, button);
    eax = port_call(&port, 0x4ac520, button, vertrix_lift_edx, ebx, button);
    edx = vertrix_lift_edx;
    if (eax == 1)
    {
        eax = port_call(&port, 0x4ac540, button, edx, ebx, button);
        port_call(&port, 0x4ac5b0, button, eax, ebx, button);
        port_set16(&port, button, 0x4a, 0);
        port_set16(&port, button, 0x4c, 5);
        eax = port_call(&port, 0x4ad530, button, vertrix_lift_edx, ebx, button);
        edx = vertrix_lift_edx;
    }
    if (port_u32(&port, 0, 0x558958) != 0)
    {
        eax = OFF_SCREEN;
    }
    else
    {
        eax = (eax & 0xffff0000u) | port_u16(&port, 0, 0x558946);
    }
    ecx = port_u32(&port, 0, 0x558958);
    ebx = (uint32_t)(int32_t)(int16_t)eax;
    if (ecx != 0)
    {
        edx = OFF_SCREEN;
    }
    else
    {
        edx = (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558944);
    }
    if ((port_call(&port, 0x4b0b70, button, edx, ebx, ecx) & 0xff) != 0)
    {
        port_set16(&port, button, 0x48, 0x23);
    }
    eax = port_call(&port, 0x476480, INPUT, CLICK, ebx, ecx);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    {
        uint32_t out = ebp - 0x18;
        ecx = ebp - 0x14;
        port_call_stack(&port, 0x4764a0, INPUT, CLICK, ebp - 0x1c, ecx, &out, 1);
    }
    ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x14u);
    eax = port_call(&port, 0x4b0b70, button,
                    (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu), ebx, ecx);
    if ((eax & 0xff) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    eax = port_call(&port, 0x4ac8f0, button, next, ebx, ecx);
    port_set16(&port, button, 0x48, 0x3c);
    return port_return(&port, eax, entry->edx);
}

uint32_t vertrix_port_button_frame_456390(PORT_SIGNATURE)
{
    return button_frame(calls, services, globals, entry, 0x456490);
}

uint32_t vertrix_port_button_frame_456570(PORT_SIGNATURE)
{
    return button_frame(calls, services, globals, entry, 0x456670);
}

uint32_t vertrix_port_button_frame_456760(PORT_SIGNATURE)
{
    return button_frame(calls, services, globals, entry, 0x456860);
}

uint32_t vertrix_port_actor_orbit_frame(PORT_SIGNATURE)
{
    /* push ebp, ebx, ecx, edx, esi, then 0x10 bytes: the polar offset and the drawn size. */
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t steps;
    uint32_t half;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_call(&port, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    /* When the counter is due: turn by the steps (0x4ad060), take the polar offset (0x4ad260) and
     * the drawn size (0x4b14c0) and centre the actor on the offset (+0xe, +0x16); the angle field
     * +0x32 advances by the steps, the value at +0x64 steps (0x4ad750) and, once it arrives, is
     * cleared and the axis at +0x28 approached by one (0x4ad5e0); on arrival the update ends. */
    steps = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac5b0, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ad060, actor, steps, ebp - 0x18, actor);
    port_call(&port, 0x4ad260, actor, ebp - 0x14, ebp - 0x18, actor);
    port_set32(&port, ebp, -0x20u, 0);
    port_set32(&port, ebp, -0x1cu, 0);
    port_call(&port, 0x4b14c0, actor, ebp - 0x20, ebp - 0x1c, actor);
    half = port_u32(&port, ebp, -0x20u) >> 1;
    port_set16(&port, actor, 0xe, (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u) - half);
    half = port_u32(&port, ebp, -0x1cu) >> 1;
    result = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x14u) - half;
    half = port_u16(&port, actor, 0x32);
    port_set16(&port, actor, 0x16, result);
    port_set16(&port, actor, 0x32, half + steps);
    result = port_call(&port, 0x4ad750, actor, steps, ebp - 0x1c, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set32(&port, actor, 0x64, 0);
    result = port_call(&port, 0x4ad5e0, actor, 1, ebp - 0x1c, actor);
    if (result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    result = port_call(&port, 0x4ac8f0, actor, 0, ebp - 0x1c, actor);
    return port_return(&port, result, entry->edx);
}

/* The pool destructor shape of 0x4d83f0 and its three copies: mode 4 destroys an array (each
 * element by `element` through 0x4ccb9f, the block freed by 0x4ca040); otherwise, under the guard
 * record `guard`, the table `table` is set, the pages released (`release`), the base table 0x517454
 * set and, when the edx it leaves has bit 1, the object freed (0x4ca050). Returns the object. */
static uint32_t pool_destroy(PORT_SIGNATURE, uint32_t table, uint32_t element, uint32_t guard,
                             uint32_t release)
{
    /* push ecx, then 0x30 bytes holding the guard record at esp + 0x14. */
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t pool = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t frame = entry->esp - BELOW;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    if (edx & 4)
    {
        port_set32(&port, frame, 0x20, 1);
        port_set32(&port, frame, 0, pool);
        result = port_call(&port, 0x4ccb9f, pool, element, entry->ebx, pool);
        port_set32(&port, frame, 0x20, 0);
        port_call(&port, 0x4ca040, result, vertrix_lift_edx, entry->ebx, pool);
        return port_return(&port, pool, vertrix_lift_edx);
    }
    port_set32(&port, pool, 0, table);
    port_set32(&port, frame, 0x24, pool);
    port_set8(&port, frame, 0x28, edx);
    port_set32(&port, frame, 0x14, port.env.chain);
    port_set32(&port, frame, 0x18, GUARD_HANDLER);
    port_set32(&port, frame, 0x1c, guard);
    port_set32(&port, frame, 0x20, 3);
    port_call(&port, release, pool, edx, entry->ebx, pool);
    edx = vertrix_lift_edx;
    port_set32(&port, frame, 0x20, 0);
    port_set32(&port, pool, 0, 0x517454);
    if (edx & 2)
    {
        port_call(&port, 0x4ca050, pool, edx, entry->ebx, pool);
        edx = vertrix_lift_edx;
    }
    return port_return(&port, pool, edx);
}

uint32_t vertrix_port_pool_destroy_4d83f0(PORT_SIGNATURE)
{
    return pool_destroy(calls, services, globals, entry, 0x51a024, 0x519a10, 0x519fc8, 0x4d83c0);
}

uint32_t vertrix_port_pool_destroy_4d8b80(PORT_SIGNATURE)
{
    return pool_destroy(calls, services, globals, entry, 0x51a1b4, 0x516f80, 0x51a128, 0x4d8b30);
}

uint32_t vertrix_port_pool_destroy_4defd0(PORT_SIGNATURE)
{
    return pool_destroy(calls, services, globals, entry, 0x51bb54, 0x51bb70, 0x51baf8, 0x4def90);
}

uint32_t vertrix_port_pool_destroy_4ee980(PORT_SIGNATURE)
{
    return pool_destroy(calls, services, globals, entry, 0x51c2d4, 0x51c2f0, 0x51c278, 0x4ee910);
}

/* The menu item click shape of 0x44a040 and its two copies, for the item whose settings word is at
 * `setting` and whose chosen state is `chosen`: an item 0x449460 accepts returns 1; otherwise it is
 * highlighted (0x4493d0 with 0x74) and chosen (0x4ac8f0) by a click inside it (the input 0x54d640's
 * key 0x74 (0x476480), its position (0x4764a0) hit-tested by 0x4b0b70); then 0x449390 runs. */
static uint32_t menu_item_click(PORT_SIGNATURE, uint32_t setting, uint32_t chosen)
{
    /* push ebp, ebx, ecx, edx, esi, then 0xc bytes: the click's three results. */
    enum
    {
        BELOW = 0x20,
        INPUT = 0x54d640,
        CLICK = 0x74
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t item = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    result = port_call(&port, 0x449460, item, port_u32(&port, 0, setting), ebx, ecx);
    if (result == 1)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, 0x4493d0, item, CLICK, ebx, ecx);
    if (port_call(&port, 0x476480, INPUT, vertrix_lift_edx, ebx, ecx) == 1)
    {
        uint32_t out = ebp - 0x14;
        ecx = ebp - 0x18;
        port_call_stack(&port, 0x4764a0, INPUT, CLICK, ebp - 0x1c, ecx, &out, 1);
        ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u);
        if ((port_call(&port, 0x4b0b70, item,
                       (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x1cu), ebx, ecx) &
             0xff) != 0)
        {
            port_call(&port, 0x4ac8f0, item, chosen, ebx, ecx);
        }
    }
    result = port_call(&port, 0x449390, item, port_u32(&port, 0, setting), ebx, ecx);
    return port_return(&port, result, entry->edx);
}

/* The effect bind shape of 0x455670 and its two copies: the child (+0x15c) gets 0x4375a0; when its
 * test `check` gives 1 the object gets the two bindings 0x43c0e0 ([0x4f8184], [0x4f81b0]) and the
 * update `next` and the child +0xb8c is set, otherwise 0x43acd0 runs; the child's method +4 (table
 * +0x158) follows, and 0x43bbf0 after the second case. */
static uint32_t effect_bind(PORT_SIGNATURE, uint32_t check, uint32_t next)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t child;
    uint32_t table;
    uint32_t result;
    int other = 0;
    port_open(&port, calls, services, globals, entry);
    child = port_u32(&port, object, 0x15c);
    port_call(&port, 0x4375a0, child, entry->edx, child, object);
    if (port_call(&port, check, child, vertrix_lift_edx, child, object) == 1)
    {
        port_call(&port, 0x43c0e0, object, port_u32(&port, 0, 0x4f8184), child, object);
        port_call(&port, 0x43c0e0, object, port_u32(&port, 0, 0x4f81b0), child, object);
        port_call(&port, 0x4ac8f0, object, next, child, object);
        port_set32(&port, child, 0xb8c, 1);
    }
    else
    {
        other = 1;
        port_call(&port, 0x43acd0, object, vertrix_lift_edx, child, object);
    }
    table = port_u32(&port, child, 0x158);
    result = port_call(&port, port_u32(&port, table, 4), child, table, child, object);
    if (other)
    {
        result = port_call(&port, 0x43bbf0, object, vertrix_lift_edx, child, object);
    }
    return port_return(&port, result, entry->edx);
}

/* The approach frame shape of 0x456300 and its two copies: rate 1 (0x4ac7b0), then, when the
 * counter is due, the three axes approached by the steps (0x4aca60, 0x4acab0, 0x4acb00); once all
 * arrive the update `next` and rate 2 are set. */
static uint32_t approach_frame(PORT_SIGNATURE, uint32_t next)
{
    Port port;
    uint32_t actor = entry->eax;
    uint32_t steps;
    uint32_t x;
    uint32_t y;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_call(&port, 0x4ac7b0, actor, 1, entry->ebx, actor);
    port_call(&port, 0x4ac500, actor, vertrix_lift_edx, entry->ebx, actor);
    result = port_call(&port, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (result != 1)
    {
        return port_return(&port, result, entry->edx);
    }
    steps = port_call(&port, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_call(&port, 0x4ac5b0, actor, vertrix_lift_edx, steps, actor);
    x = port_call(&port, 0x4aca60, actor, steps, steps, actor);
    y = port_call(&port, 0x4acab0, actor, steps, steps, actor);
    result = port_call(&port, 0x4acb00, actor, steps, steps, actor);
    if (x != 0 || y != 0 || result != 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_call(&port, 0x4ac8f0, actor, next, steps, actor);
    result = port_call(&port, 0x4ac7b0, actor, 2, steps, actor);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_menu_item_click_44a040(PORT_SIGNATURE)
{
    return menu_item_click(calls, services, globals, entry, 0x4fbf00, 0x44a0e0);
}

uint32_t vertrix_port_menu_item_click_44a170(PORT_SIGNATURE)
{
    return menu_item_click(calls, services, globals, entry, 0x4fbf10, 0x44a210);
}

uint32_t vertrix_port_menu_item_click_44a2a0(PORT_SIGNATURE)
{
    return menu_item_click(calls, services, globals, entry, 0x4fbf08, 0x44a340);
}

uint32_t vertrix_port_effect_bind_455670(PORT_SIGNATURE)
{
    return effect_bind(calls, services, globals, entry, 0x4375f0, 0x455700);
}

uint32_t vertrix_port_effect_bind_4558e0(PORT_SIGNATURE)
{
    return effect_bind(calls, services, globals, entry, 0x437be0, 0x455970);
}

uint32_t vertrix_port_effect_bind_455a00(PORT_SIGNATURE)
{
    return effect_bind(calls, services, globals, entry, 0x437d70, 0x455a90);
}

uint32_t vertrix_port_approach_frame_456300(PORT_SIGNATURE)
{
    return approach_frame(calls, services, globals, entry, 0x456390);
}

uint32_t vertrix_port_approach_frame_4564e0(PORT_SIGNATURE)
{
    return approach_frame(calls, services, globals, entry, 0x456570);
}

uint32_t vertrix_port_approach_frame_4566d0(PORT_SIGNATURE)
{
    return approach_frame(calls, services, globals, entry, 0x456760);
}

/* The block fade frame shape of 0x44c960 and its five copies: +0x93 set, 0x4ac1f0 and 0x4ac500,
 * then, when the counter is due (0x4ac520), its steps consumed (0x4ac540, 0x4ac5b0), the level's
 * target (+0x4f) and speed (+0x50) set, the level stepped (0x4ad580) and, once it arrives, the
 * update `next` set (0x4ac8f0); the image is refreshed (0x4ac8a0) in every case. */
static uint32_t block_fade_frame(PORT_SIGNATURE, uint32_t target, uint32_t speed, uint32_t next)
{
    Port port;
    uint32_t block = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    port_set8(&port, block, 0x93, 1);
    port_call(&port, 0x4ac1f0, block, entry->edx, ebx, block);
    port_call(&port, 0x4ac500, block, vertrix_lift_edx, ebx, block);
    if (port_call(&port, 0x4ac520, block, vertrix_lift_edx, ebx, block) == 1)
    {
        result = port_call(&port, 0x4ac540, block, vertrix_lift_edx, ebx, block);
        port_call(&port, 0x4ac5b0, block, result, ebx, block);
        port_set8(&port, block, 0x4f, target);
        port_set16(&port, block, 0x50, speed);
        if (port_call(&port, 0x4ad580, block, vertrix_lift_edx, ebx, block) == 0)
        {
            port_call(&port, 0x4ac8f0, block, next, ebx, block);
        }
    }
    result = port_call(&port, 0x4ac8a0, block, vertrix_lift_edx, ebx, block);
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_block_fade_frame_44c960(PORT_SIGNATURE)
{
    return block_fade_frame(calls, services, globals, entry, 0x0, 8, 0x44c940);
}

uint32_t vertrix_port_block_fade_frame_44cbf0(PORT_SIGNATURE)
{
    return block_fade_frame(calls, services, globals, entry, 0x64, 5, 0x44cc60);
}

uint32_t vertrix_port_block_fade_frame_44cc60(PORT_SIGNATURE)
{
    return block_fade_frame(calls, services, globals, entry, 0x0, 5, 0x44cbf0);
}

uint32_t vertrix_port_block_fade_frame_44d2c0(PORT_SIGNATURE)
{
    return block_fade_frame(calls, services, globals, entry, 0x0, 8, 0x44c860);
}

uint32_t vertrix_port_block_fade_frame_44d410(PORT_SIGNATURE)
{
    return block_fade_frame(calls, services, globals, entry, 0x64, 8, 0x44c860);
}

uint32_t vertrix_port_block_fade_frame_44d760(PORT_SIGNATURE)
{
    return block_fade_frame(calls, services, globals, entry, 0x64, 8, 0x44d7d0);
}

/* The option value formatter shape of 0x4b7120 and its copies (eax = options, edx = string, ebx =
 * value): under the guard record `guard` the value's entry (0x4b6fa0) is looked up and the string
 * set empty (0x4ca280 with `empty`); with an entry, its field `field` names one of the `count`
 * texts of `names` (0x415ed0 with `table`) that the string is set to (0x4ca370). Returns the
 * string. */
static uint32_t option_value_text(PORT_SIGNATURE, uint32_t guard, uint32_t empty, uint32_t field,
                                  uint32_t names, uint32_t table, uint32_t count)
{
    /* push ebp, ecx, esi, edi, then 0x14 bytes holding the guard record. */
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t options = entry->eax;
    uint32_t text = entry->edx;
    uint32_t value;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x20u, port.env.chain);
    port_set32(&port, ebp, -0x1cu, GUARD_HANDLER);
    port_set32(&port, ebp, -0x14u, 0);
    port_set32(&port, ebp, -0x18u, guard);
    value = port_call(&port, 0x4b6fa0, options, entry->ebx, GUARD_HANDLER, options);
    port_call(&port, 0x4ca280, text, empty, GUARD_HANDLER, value);
    if (value != 0)
    {
        uint32_t name =
            port_call(&port, 0x415ed0, port_u32(&port, value, field), names, table, count);
        port_call(&port, 0x4ca370, text, name, table, count);
    }
    return port_return(&port, text, vertrix_lift_edx);
}

uint32_t vertrix_port_option_value_text_4b7080(PORT_SIGNATURE)
{
    return option_value_text(calls, services, globals, entry, 0x51852c, 0x5110bc, 0x0, 0x532c44,
                             0x4f80e4, 3);
}

uint32_t vertrix_port_option_value_text_4b7120(PORT_SIGNATURE)
{
    return option_value_text(calls, services, globals, entry, 0x518530, 0x5110bd, 0x4, 0x532c50,
                             0x4f80f0, 10);
}

uint32_t vertrix_port_option_value_text_4b71c0(PORT_SIGNATURE)
{
    return option_value_text(calls, services, globals, entry, 0x518534, 0x5110be, 0x8, 0x532c78,
                             0x4f8118, 2);
}

uint32_t vertrix_port_option_value_text_4b7260(PORT_SIGNATURE)
{
    return option_value_text(calls, services, globals, entry, 0x518538, 0x5110bf, 0xc, 0x532c80,
                             0x4f8120, 2);
}

uint32_t vertrix_port_option_value_text_4b7300(PORT_SIGNATURE)
{
    return option_value_text(calls, services, globals, entry, 0x51853c, 0x5110c0, 0x10, 0x532c88,
                             0x4f8168, 2);
}

uint32_t vertrix_port_music_rows_play_4aa1e0(PORT_SIGNATURE)
{
    return music_rows_play_at(calls, services, globals, entry, 0x5bb778, 1);
}
