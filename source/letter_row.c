#include "letter_row.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    INIT = 0x4ca070,
    STORE = 0x4ca370,
    MEASURE = 0x440610,
    ALLOCATE = 0x4ca000,
    CONSTRUCT = 0x4abd70,
    INITIALISE = 0x4adf20,
    MAP = 0x43f420,
    SET_GLYPH = 0x4ac950,
    BIND = 0x4ac8a0,
    SET_HANDLER = 0x4ac8f0,
    SET_BOUNDS = 0x4ad510,
    DRAW = 0x4826c0,
    SET_DELAY = 0x4ac7d0,
    CLEAR_TIMER = 0x4ac510,
    REGISTER = 0x4b5e70,
    RELEASE = 0x4ca210,
    LOCAL_WIDTH = 0x28,
    LOCAL_STACK = 0x24,
    INIT_EDX = 0x4ec1ec,
    STORE_EBX = 0x10,
    HEADER_SIZE = 0xc,
    HEADER_LENGTH = 4,
    SCREEN_WIDTH = 0x280,
    START_OFFSET = 0x11,
    START_Y = 0xf0,
    STEP = 0x23,
    ACTOR_SIZE = 0x15c,
    LIST = 0x546758,
    RANDOM = 0x598d30,
    ANGLE_RANGE = 0x168,
    SPEED_RANGE = 3,
    SPEED_BASE = 4,
    DELAY = 0xa,
    PROPERTY_STEP = 0x140,
    SIGN_SHIFT = 24,
    HALF_SHIFT = 16
};

typedef struct Row
{
    const VertrixFactoryServices *services;
    int ok;
} Row;

static void put(Row *r, uint32_t object, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!r->services->resolve(object, &storage, &size, r->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        r->ok = 0;
    }
}

static uint32_t get(Row *r, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!r->services->resolve(handle, &storage, &size, r->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        r->ok = 0;
    }
    return value;
}

typedef struct RowSpec
{
    uint32_t text;
    uint32_t handler;
    uint32_t init_ecx;
    uint32_t local_text;
    int full;
} RowSpec;

static int build_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                     uint32_t frame, const RowSpec *spec)
{
    Row row = {services, 1};
    Row *r = &row;
    uint32_t local = frame - spec->local_text, width_local = frame - LOCAL_WIDTH;
    uint32_t ebx = 0, ecx = spec->init_ecx, edx = INIT_EDX, text, length, glyph_byte, width, x, y,
             i;
    uint32_t toggle = 1, stack[5] = {0, 0, 0, 0, 0}, high = 0;
    VertrixCallSite site = {MEASURE, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, 0};
    vertrix_call(calls, INIT, local, edx, ebx, ecx, 0);
    ebx = STORE_EBX;
    ecx = width_local;
    vertrix_calln(calls, STORE, local, spec->text, ebx, ecx, NULL, 0, &text);
    length = get(r, text - HEADER_SIZE, HEADER_LENGTH, DWORD_WIDTH);
    glyph_byte = (uint32_t)((int32_t)get(r, VERTRIX_LETTER_GLOBAL, 0, DWORD_WIDTH) >> SIGN_SHIFT);
    site.eax = glyph_byte;
    site.edx = text;
    site.ebx = ebx;
    site.ecx = ecx;
    site.stack = frame - LOCAL_STACK;
    calls->call(&site, calls->context);
    width = site.out_ecx;
    x = ((SCREEN_WIDTH - width + 1) >> 1) + START_OFFSET;
    y = START_Y;
    edx = 1;
    ecx = 0;
    for (i = 0; r->ok && i < length; i++)
    {
        uint32_t object, mapped, letter, bounds_x, bounds_y;
        object = vertrix_call(calls, ALLOCATE, ACTOR_SIZE, edx, ebx, ecx, 0);
        if (object != 0)
        {
            object = vertrix_call(calls, CONSTRUCT, object, edx, ebx, ecx, 0);
        }
        vertrix_calln(calls, INITIALISE, object, 0, 0, 0, stack, 5, NULL);
        edx = 0;
        ebx = 0;
        ecx = 0;
        letter = get(r, text - HEADER_SIZE, HEADER_SIZE + i, BYTE_WIDTH);
        mapped = vertrix_call(calls, MAP, glyph_byte, letter, ebx, ecx, 0);
        edx = mapped;
        vertrix_call(calls, SET_GLYPH, object, edx, ebx, ecx, 0);
        vertrix_call(calls, BIND, object, edx, ebx, ecx, 0);
        put(r, object, 0xc, WORD_WIDTH, 0);
        if (spec->full)
        {
            put(r, object, 0x52, BYTE_WIDTH, 0);
            put(r, object, 0x95, BYTE_WIDTH, 5);
        }
        put(r, object, 0x94, BYTE_WIDTH, spec->full ? 2 : 1);
        put(r, object, 0x93, BYTE_WIDTH, 0);
        put(r, object, 8, WORD_WIDTH, x);
        put(r, object, 0xa, WORD_WIDTH, y);
        put(r, object, 0xe, WORD_WIDTH, x);
        put(r, object, 0x16, WORD_WIDTH, y);
        put(r, object, 0x10, WORD_WIDTH, x);
        put(r, object, 0x18, WORD_WIDTH, y);
        edx = spec->handler;
        put(r, object, 0x4e, BYTE_WIDTH, 0x32);
        vertrix_call(calls, SET_HANDLER, object, edx, ebx, ecx, 0);
        put(r, object, 0x30, WORD_WIDTH, PROPERTY_STEP);
        bounds_x = (uint32_t)((int32_t)get(r, object, 6, DWORD_WIDTH) >> HALF_SHIFT);
        bounds_y = (uint32_t)((int32_t)get(r, object, 8, DWORD_WIDTH) >> HALF_SHIFT);
        edx = (uint32_t)((int32_t)get(r, object, 0x2e, DWORD_WIDTH) >> HALF_SHIFT);
        ebx = bounds_x;
        ecx = bounds_y;
        vertrix_call(calls, SET_BOUNDS, object, edx, ebx, ecx, 0);
        edx = ANGLE_RANGE;
        put(r, object, 0x24, WORD_WIDTH, vertrix_call(calls, DRAW, RANDOM, edx, ebx, ecx, 0));
        edx = SPEED_RANGE;
        put(r, object, 0x28, WORD_WIDTH,
            vertrix_call(calls, DRAW, RANDOM, edx, ebx, ecx, 0) + SPEED_BASE);
        put(r, object, 0x32, WORD_WIDTH, 3);
        if (toggle == 0)
        {
            put(r, object, 0x28, WORD_WIDTH, 0u - (get(r, object, 0x28, WORD_WIDTH) & 0xffff));
        }
        edx = DELAY;
        ebx = x;
        vertrix_call(calls, SET_DELAY, object, edx, ebx, ecx, 0);
        vertrix_call(calls, CLEAR_TIMER, object, edx, ebx, ecx, 0);
        ebx = x + STEP;
        put(r, object, 0x44, BYTE_WIDTH, 0);
        vertrix_call(calls, REGISTER, LIST, object, ebx, ecx, 0);
        x = ebx;
        edx = length;
        toggle = 1 - toggle;
    }
    (void)high;
    vertrix_call(calls, RELEASE, local, 0, ebx, ecx, 0);
    return r->ok;
}

int vertrix_letter_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       uint32_t frame)
{
    static const RowSpec spec = {VERTRIX_LETTER_TEXT, 0x45a290, 0x5161d4, 0x2c, 1};
    return build_row(calls, services, frame, &spec);
}

int vertrix_letter_row_second(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t frame)
{
    static const RowSpec spec = {VERTRIX_LETTER_SECOND_TEXT, 0x45a620, 0x5161e0, 0x34, 0};
    return build_row(calls, services, frame, &spec);
}

enum
{
    GRID_COUNTS = 0x540000,
    GRID_TEXTS = 0x53fe20,
    GRID_TEXT_STRIDE = 0xc,
    GRID_INIT_EBX = 0x5161c8,
    GRID_START_Y = 0x1a4,
    GRID_ROW_STEP = 0x32,
    GRID_TEXT_LOCAL = 0x38,
    GRID_WIDTH_LOCAL = 0x34,
    GRID_MULT_LOCAL = 0x30,
    GRID_TAIL = 3,
    GRID_COPY = 0x4ca310,
    GRID_COPY_EBX = 0x10,
    GRID_SCREEN_HEIGHT = 0x1e0,
    GRID_TAIL_HANDLER = 0x457e40,
    GRID_HANDLER = 0x4578f0,
    GRID_SHAPE = 0x458410,
    GRID_LIST = 0x54671c,
    GRID_SHAPE_DELAY = 0x14,
    SET_SHAPE = 0x4ac910
};

int vertrix_letter_grid(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t index)
{
    Row row = {services, 1};
    Row *r = &row;
    uint32_t local = frame - GRID_TEXT_LOCAL, width_local = frame - GRID_WIDTH_LOCAL;
    uint32_t count, y = GRID_START_Y, table, text = 0, length, width, mult, x, j, i;
    uint32_t glyph_byte, ecx = INIT_EDX;
    VertrixCallSite site = {MEASURE, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, 0};
    vertrix_call(calls, INIT, local, index, GRID_INIT_EBX, INIT_EDX, 0);
    count = get(r, GRID_COUNTS + DWORD_WIDTH * index, 0, DWORD_WIDTH);
    table = GRID_TEXTS + DWORD_WIDTH * index;
    for (j = 0; r->ok && j < count; j++)
    {
        uint32_t tail = 3u - count + j;
        uint32_t edx, ebx;
        vertrix_calln(calls, GRID_COPY, local, table, GRID_COPY_EBX, width_local, NULL, 0, &text);
        length = get(r, text - HEADER_SIZE, HEADER_LENGTH, DWORD_WIDTH);
        glyph_byte =
            (uint32_t)((int32_t)get(r, VERTRIX_LETTER_GLOBAL, 0, DWORD_WIDTH) >> SIGN_SHIFT);
        site.eax = glyph_byte;
        site.edx = text;
        site.ebx = GRID_COPY_EBX;
        site.ecx = width_local;
        site.stack = frame - GRID_MULT_LOCAL;
        calls->call(&site, calls->context);
        width = site.out_ecx;
        mult = site.out_value;
        x = ((SCREEN_WIDTH - width + 1) >> 1) + START_OFFSET;
        edx = text;
        ebx = GRID_COPY_EBX;
        ecx = width_local;
        for (i = 0; r->ok && i < length; i++)
        {
            uint32_t stack[5] = {0, 0, 0, GRID_HANDLER, 0};
            uint32_t object, letter, mapped, place, later = 0;
            object = vertrix_call(calls, ALLOCATE, ACTOR_SIZE, edx, ebx, ecx, 0);
            if (object != 0)
            {
                object = vertrix_call(calls, CONSTRUCT, object, edx, ebx, ecx, 0);
            }
            vertrix_calln(calls, INITIALISE, object, 0, 0, 0, stack, 5, NULL);
            letter = get(r, text - HEADER_SIZE, HEADER_SIZE + i, BYTE_WIDTH);
            mapped = vertrix_call(calls, MAP, glyph_byte, letter, 0, 0, 0);
            vertrix_call(calls, SET_GLYPH, object, mapped, 0, 0, 0);
            vertrix_call(calls, BIND, object, mapped, 0, 0, 0);
            put(r, object, 0xc, WORD_WIDTH, 0);
            put(r, object, 8, WORD_WIDTH, x);
            put(r, object, 0xa, WORD_WIDTH, y);
            put(r, object, 0xe, WORD_WIDTH, x);
            put(r, object, 0x16, WORD_WIDTH, y);
            put(r, object, 0x10, WORD_WIDTH, x);
            put(r, object, 0x18, WORD_WIDTH, 0xffd8);
            if (j >= count - GRID_TAIL)
            {
                vertrix_call(calls, SET_HANDLER, object, GRID_TAIL_HANDLER, 0, 0, 0);
                place = ((GRID_SCREEN_HEIGHT - (mult * 3 + 0x28)) >> 1) + (mult + 0x14) * tail;
                later = tail;
                put(r, object, 0x52, BYTE_WIDTH, 9);
                put(r, object, 0x94, BYTE_WIDTH, 1);
                put(r, object, 0x95, BYTE_WIDTH, 4);
                put(r, object, 0x93, BYTE_WIDTH, 1);
                put(r, object, 0x4e, BYTE_WIDTH, 0x32);
                put(r, object, 0x18, WORD_WIDTH, (mult >> 1) + place);
            }
            vertrix_call(calls, SET_SHAPE, object, GRID_SHAPE, 0, later, 0);
            put(r, object, 0x12, WORD_WIDTH, 1);
            put(r, object, 0x1a, WORD_WIDTH, 1);
            put(r, object, 0x44, BYTE_WIDTH, 0);
            vertrix_call(calls, SET_DELAY, object, GRID_SHAPE_DELAY, 0, later, 0);
            vertrix_call(calls, REGISTER, GRID_LIST, object, 0, length, 0);
            x += STEP;
            edx = i + 1;
            ebx = 0;
            ecx = length;
        }
        y += GRID_ROW_STEP;
        table += GRID_TEXT_STRIDE;
        ecx = count;
    }
    vertrix_call(calls, RELEASE, local, 0, 0, count == 0 ? INIT_EDX : count, 0);
    return r->ok;
}

enum
{
    MENU_TABLE = 0x53fd38,
    CHOICE_RANGE = 3,
    MENU_TABLE_STRIDE = 12,
    MENU_TEXT_LOCAL = 0x3c,
    MENU_WIDTH_LOCAL = 0x38,
    MENU_MULT_LOCAL = 0x34,
    MENU_ARRAY_LOCAL = 0x128,
    MENU_ARRAY_COUNT = 0x30,
    MENU_ARRAY_SIZE = 4,
    MENU_ARRAY_EBX = 0x513e60,
    MENU_INIT_ECX = 0x5161a4,
    MENU_ARRAY_INIT = 0x4ccf3b,
    MENU_BLANK = 0x50e60d,
    MENU_SECOND_LAST = 0x50e60e,
    MENU_LAST_BUT_ONE = 0x50e616,
    MENU_LAST = 0x50e619,
    MENU_BASE = 0x53d998,
    MENU_FIRST_STRIDE = 0x4c,
    MENU_ENTRY_STRIDE = 0xe4,
    MENU_EXTRA = 8,
    MENU_TRIM = 0x4ca710,
    MENU_FINISH = 0x4cda10
};

int vertrix_letter_menu(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t index)
{
    Row row = {services, 1};
    Row *r = &row;
    uint32_t local = frame - MENU_TEXT_LOCAL, width_local = frame - MENU_WIDTH_LOCAL;
    uint32_t array = frame - MENU_ARRAY_LOCAL, choice, rows, source, cursor, end;
    uint32_t y = GRID_START_Y, text = 0, length, width, mult, x, j, i, glyph_byte;
    uint32_t eax, edx, ebx, ecx;
    VertrixCallSite site = {MEASURE, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0}, 0};
    vertrix_call(calls, INIT, local, INIT_EDX, 0, MENU_INIT_ECX, 0);
    vertrix_call(calls, MENU_ARRAY_INIT, array, MENU_ARRAY_COUNT, MENU_ARRAY_EBX, MENU_ARRAY_SIZE,
                 0);
    choice = vertrix_call(calls, DRAW, RANDOM, CHOICE_RANGE, MENU_ARRAY_EBX, MENU_ARRAY_SIZE, 0) &
             0xffff;
    rows = get(r, MENU_TABLE + MENU_TABLE_STRIDE * index + DWORD_WIDTH * choice, 0, DWORD_WIDTH) +
           MENU_EXTRA;
    end = array + MENU_ARRAY_COUNT * DWORD_WIDTH;
    for (cursor = array; cursor != end; cursor += DWORD_WIDTH)
    {
        vertrix_call(calls, STORE, cursor, MENU_BLANK, choice, end, 0);
    }
    source = DWORD_WIDTH * index + MENU_FIRST_STRIDE * choice + MENU_BASE;
    end = array + (rows - MENU_EXTRA) * DWORD_WIDTH;
    if (array < end)
    {
        cursor = array;
        do
        {
            vertrix_call(calls, GRID_COPY, cursor, source, choice, end, 0);
            vertrix_call(calls, MENU_TRIM, cursor, source, choice, end, 0);
            cursor += DWORD_WIDTH;
            source += MENU_ENTRY_STRIDE;
        } while (cursor < end);
    }
    ecx = rows * DWORD_WIDTH;
    vertrix_call(calls, STORE, array + ecx - 3 * DWORD_WIDTH, MENU_SECOND_LAST, GRID_START_Y, ecx,
                 0);
    ecx -= DWORD_WIDTH;
    vertrix_call(calls, STORE, array + ecx - DWORD_WIDTH, MENU_LAST_BUT_ONE, GRID_START_Y, ecx, 0);
    eax = vertrix_call(calls, STORE, array + ecx, MENU_LAST, GRID_START_Y, ecx, 0);
    edx = MENU_LAST;
    ebx = GRID_START_Y;
    cursor = array;
    for (j = 0; r->ok && j < rows; j++)
    {
        uint32_t tail = 3u - rows + j;
        vertrix_calln(calls, GRID_COPY, local, cursor, GRID_COPY_EBX, width_local, NULL, 0, &text);
        length = get(r, text - HEADER_SIZE, HEADER_LENGTH, DWORD_WIDTH);
        glyph_byte =
            (uint32_t)((int32_t)get(r, VERTRIX_LETTER_GLOBAL, 0, DWORD_WIDTH) >> SIGN_SHIFT);
        site.eax = glyph_byte;
        site.edx = text;
        site.ebx = GRID_COPY_EBX;
        site.ecx = width_local;
        site.stack = frame - MENU_MULT_LOCAL;
        calls->call(&site, calls->context);
        width = site.out_ecx;
        mult = site.out_value;
        x = ((SCREEN_WIDTH - width + 1) >> 1) + START_OFFSET;
        edx = text;
        ebx = GRID_COPY_EBX;
        ecx = width_local;
        for (i = 0; r->ok && i < length; i++)
        {
            uint32_t stack[5] = {0, 0, 0, GRID_HANDLER, 0};
            uint32_t object, letter, mapped, place;
            object = vertrix_call(calls, ALLOCATE, ACTOR_SIZE, edx, ebx, ecx, 0);
            if (object != 0)
            {
                object = vertrix_call(calls, CONSTRUCT, object, edx, ebx, ecx, 0);
            }
            vertrix_calln(calls, INITIALISE, object, 0, 0, 0, stack, 5, NULL);
            letter = get(r, text - HEADER_SIZE, HEADER_SIZE + i, BYTE_WIDTH);
            mapped = vertrix_call(calls, MAP, glyph_byte, letter, 0, 0, 0);
            vertrix_call(calls, SET_GLYPH, object, mapped, 0, 0, 0);
            vertrix_call(calls, BIND, object, mapped, 0, 0, 0);
            put(r, object, 0xc, WORD_WIDTH, 0);
            put(r, object, 8, WORD_WIDTH, x);
            put(r, object, 0xa, WORD_WIDTH, y);
            put(r, object, 0xe, WORD_WIDTH, x);
            put(r, object, 0x16, WORD_WIDTH, y);
            put(r, object, 0x10, WORD_WIDTH, x);
            put(r, object, 0x18, WORD_WIDTH, 0xffd8);
            ebx = 0;
            if (j >= rows - GRID_TAIL)
            {
                vertrix_call(calls, SET_HANDLER, object, GRID_TAIL_HANDLER, 0, rows - GRID_TAIL, 0);
                place = ((GRID_SCREEN_HEIGHT - (mult * 3 + 0x28)) >> 1) + (mult + 0x14) * tail;
                put(r, object, 0x52, BYTE_WIDTH, 9);
                put(r, object, 0x94, BYTE_WIDTH, 1);
                put(r, object, 0x95, BYTE_WIDTH, 4);
                put(r, object, 0x93, BYTE_WIDTH, 1);
                put(r, object, 0x4e, BYTE_WIDTH, 0x32);
                put(r, object, 0x18, WORD_WIDTH, (mult >> 1) + place);
                ebx = tail;
            }
            vertrix_call(calls, SET_SHAPE, object, GRID_SHAPE, ebx, i, 0);
            put(r, object, 0x12, WORD_WIDTH, 1);
            put(r, object, 0x1a, WORD_WIDTH, 1);
            put(r, object, 0x44, BYTE_WIDTH, 0);
            vertrix_call(calls, SET_DELAY, object, GRID_SHAPE_DELAY, ebx, i, 0);
            vertrix_call(calls, REGISTER, GRID_LIST, object, length, i, 0);
            x += STEP;
            edx = x;
            ebx = length;
            ecx = i + 1;
        }
        y += GRID_ROW_STEP;
        cursor += DWORD_WIDTH;
        eax = y;
        edx = cursor;
        ebx = j + 1;
        ecx = 3u - rows + j + 1;
    }
    vertrix_call(calls, MENU_FINISH, eax, edx, ebx, ecx, 0);
    return r->ok;
}
