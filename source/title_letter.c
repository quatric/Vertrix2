#include "title_letter.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    HEADER_SIZE = 0xc,
    HALF_SHIFT = 16,
    SIGN_SHIFT = 24,
    TEXT_LOCAL = 0x20,
    INIT_EDX = 0x4ec1ec,
    ACTOR_SIZE = 0x15c,
    INIT = 0x4ca070,
    ALLOCATE = 0x4ca000,
    CONSTRUCT = 0x4abd70,
    COPY_TEXT = 0x4cdfb0,
    INITIALISE = 0x4adf20,
    MAP = 0x43f420,
    SET_GLYPH = 0x4ac950,
    BIND = 0x4ac8a0,
    SET_HANDLER = 0x4ac8f0,
    SET_BOUNDS = 0x4ad510,
    SET_DELAY = 0x4ac7d0,
    CLEAR_TIMER = 0x4ac510,
    REGISTER = 0x4b5e70,
    RELEASE = 0x4ca210,
    LIST = 0x54671c,
    CONSTRUCT_MODE = 2,
    COPY_LENGTH = 3,
    MODE_FIRST = 1,
    X_OFFSET = 0x3c,
    Y_OFFSET = 0x9c,
    HANDLER = 0x459be0,
    BOUNDS_WIDTH = 0x3c,
    DELAY = 0xa,
    GLYPH_GLOBAL = 0x4f9c02
};

typedef struct Title
{
    const VertrixFactoryServices *services;
    int ok;
} Title;

static void put(Title *t, uint32_t object, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!t->services->resolve(object, &storage, &size, t->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        t->ok = 0;
    }
}

static uint32_t get(Title *t, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!t->services->resolve(handle, &storage, &size, t->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        t->ok = 0;
    }
    return value;
}

typedef struct TitleSpec
{
    uint32_t init_ebx;
    uint32_t text;
    int priority;
} TitleSpec;

static int build_title(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       uint32_t frame, uint32_t mode, const TitleSpec *spec)
{
    Title title = {services, 1};
    Title *t = &title;
    uint32_t local = frame - TEXT_LOCAL, object, text, x, y, letter, mapped, bounds_x, bounds_y;
    uint32_t stack[5] = {0, 0, 0, 0, 0}, copy[COPY_LENGTH];
    uint32_t base = mode == MODE_FIRST ? VERTRIX_TITLE_FIRST_GLOBALS : VERTRIX_TITLE_SECOND_GLOBALS;
    vertrix_call(calls, INIT, local, INIT_EDX, spec->init_ebx, mode, 0);
    object = vertrix_call(calls, ALLOCATE, ACTOR_SIZE, INIT_EDX, spec->init_ebx, mode, 0);
    if (object != 0)
    {
        object = vertrix_call(calls, CONSTRUCT, object, CONSTRUCT_MODE, spec->init_ebx, mode, 0);
    }
    copy[0] = local;
    copy[1] = spec->text;
    copy[2] = COPY_LENGTH;
    vertrix_calln(calls, COPY_TEXT, local, object, spec->init_ebx, mode, copy, COPY_LENGTH, &text);
    put(t, object, 4, DWORD_WIDTH, mode == MODE_FIRST ? 2 : 1);
    x = get(t, base, 0, DWORD_WIDTH) + X_OFFSET;
    y = get(t, base + DWORD_WIDTH, 0, DWORD_WIDTH) + Y_OFFSET;
    vertrix_calln(calls, INITIALISE, object, 0, 0, 0, stack, 5, NULL);
    letter = get(t, text - HEADER_SIZE, HEADER_SIZE, BYTE_WIDTH);
    mapped = vertrix_call(calls, MAP,
                          (uint32_t)((int32_t)get(t, GLYPH_GLOBAL, 0, DWORD_WIDTH) >> SIGN_SHIFT),
                          letter, 0, 0, 0);
    vertrix_call(calls, SET_GLYPH, object, mapped, 0, 0, 0);
    vertrix_call(calls, BIND, object, mapped, 0, 0, 0);
    put(t, object, 0xc, WORD_WIDTH, 0);
    if (spec->priority != 0)
    {
        put(t, object, 0x52, BYTE_WIDTH, (uint32_t)spec->priority);
    }
    put(t, object, 0x94, BYTE_WIDTH, 1);
    put(t, object, 0x95, BYTE_WIDTH, 4);
    put(t, object, 0x93, BYTE_WIDTH, 1);
    put(t, object, 0x4e, BYTE_WIDTH, 0x32);
    put(t, object, 8, WORD_WIDTH, x);
    put(t, object, 0xa, WORD_WIDTH, y);
    put(t, object, 0x16, WORD_WIDTH, y);
    put(t, object, 0xe, WORD_WIDTH, x);
    vertrix_call(calls, SET_HANDLER, object, HANDLER, 0, 0, 0);
    bounds_y = (uint32_t)((int32_t)get(t, object, 8, DWORD_WIDTH) >> HALF_SHIFT);
    bounds_x = (uint32_t)((int32_t)get(t, object, 6, DWORD_WIDTH) >> HALF_SHIFT);
    vertrix_call(calls, SET_BOUNDS, object, BOUNDS_WIDTH, bounds_x, bounds_y, 0);
    put(t, object, 0x30, WORD_WIDTH, BOUNDS_WIDTH);
    put(t, object, 0x24, WORD_WIDTH, 0);
    put(t, object, 0x28, WORD_WIDTH, 0x14);
    put(t, object, 0x32, WORD_WIDTH, 1);
    vertrix_call(calls, SET_DELAY, object, DELAY, bounds_x, bounds_y, 0);
    vertrix_call(calls, CLEAR_TIMER, object, DELAY, bounds_x, bounds_y, 0);
    put(t, object, 0x58, DWORD_WIDTH, 3);
    put(t, object, 0x5c, DWORD_WIDTH, 0);
    put(t, object, 0x60, DWORD_WIDTH, 1);
    put(t, object, 0x44, BYTE_WIDTH, 0);
    vertrix_call(calls, REGISTER, LIST, object, bounds_x, bounds_y, 0);
    vertrix_call(calls, RELEASE, local, 0, bounds_x, bounds_y, 0);
    return t->ok;
}

int vertrix_title_letter_first(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t mode)
{
    static const TitleSpec spec = {0x516264, 0x50e62c, 0};
    return build_title(calls, services, frame, mode, &spec);
}

int vertrix_title_letter_second(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t frame, uint32_t mode)
{
    static const TitleSpec spec = {0x516278, 0x50e630, 3};
    return build_title(calls, services, frame, mode, &spec);
}

static int build_title_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t frame, uint32_t mode, const TitleSpec *spec)
{
    Title title = {services, 1};
    Title *t = &title;
    uint32_t local = frame - TEXT_LOCAL, object, text, x, y, letter, mapped, bounds_x, bounds_y;
    uint32_t stack[5] = {0, 0, 0, 0, 0}, copy[COPY_LENGTH];
    uint32_t base = mode == MODE_FIRST ? VERTRIX_TITLE_FIRST_GLOBALS : VERTRIX_TITLE_SECOND_GLOBALS;
    vertrix_call(calls, INIT, local, INIT_EDX, spec->init_ebx, mode, 0);
    object = vertrix_call(calls, ALLOCATE, ACTOR_SIZE, INIT_EDX, spec->init_ebx, mode, 0);
    if (object != 0)
    {
        object = vertrix_call(calls, CONSTRUCT, object, CONSTRUCT_MODE, spec->init_ebx, mode, 0);
    }
    copy[0] = local;
    copy[1] = spec->text;
    copy[2] = COPY_LENGTH;
    vertrix_calln(calls, COPY_TEXT, local, object, spec->init_ebx, mode, copy, COPY_LENGTH, &text);
    put(t, local, 0, DWORD_WIDTH, text);
    put(t, object, 4, DWORD_WIDTH, mode == MODE_FIRST ? 2 : 1);
    x = get(t, base, 0, DWORD_WIDTH) + X_OFFSET;
    y = get(t, base + DWORD_WIDTH, 0, DWORD_WIDTH) + Y_OFFSET;
    vertrix_calln(calls, INITIALISE, object, 0, 0, 0, stack, 5, NULL);
    text = get(t, local, 0, DWORD_WIDTH);
    letter = get(t, text - HEADER_SIZE, HEADER_SIZE, BYTE_WIDTH);
    mapped = vertrix_call(calls, MAP,
                          (uint32_t)((int32_t)get(t, GLYPH_GLOBAL, 0, DWORD_WIDTH) >> SIGN_SHIFT),
                          letter, 0, 0, 0);
    vertrix_call(calls, SET_GLYPH, object, mapped, 0, 0, 0);
    vertrix_call(calls, BIND, object, mapped, 0, 0, 0);
    put(t, object, 0xc, WORD_WIDTH, 0);
    if (spec->priority != 0)
    {
        put(t, object, 0x52, BYTE_WIDTH, (uint32_t)spec->priority);
    }
    put(t, object, 0x94, BYTE_WIDTH, 1);
    put(t, object, 0x95, BYTE_WIDTH, 4);
    put(t, object, 0x93, BYTE_WIDTH, 1);
    put(t, object, 0x4e, BYTE_WIDTH, 0x32);
    put(t, object, 8, WORD_WIDTH, x);
    put(t, object, 0xa, WORD_WIDTH, y);
    put(t, object, 0x16, WORD_WIDTH, y);
    put(t, object, 0xe, WORD_WIDTH, x);
    vertrix_call(calls, SET_HANDLER, object, HANDLER, 0, 0, 0);
    bounds_y = (uint32_t)((int32_t)get(t, object, 8, DWORD_WIDTH) >> HALF_SHIFT);
    bounds_x = (uint32_t)((int32_t)get(t, object, 6, DWORD_WIDTH) >> HALF_SHIFT);
    vertrix_call(calls, SET_BOUNDS, object, BOUNDS_WIDTH, bounds_x, bounds_y, 0);
    put(t, object, 0x30, WORD_WIDTH, BOUNDS_WIDTH);
    put(t, object, 0x24, WORD_WIDTH, 0);
    put(t, object, 0x28, WORD_WIDTH, 0x14);
    put(t, object, 0x32, WORD_WIDTH, 1);
    vertrix_call(calls, SET_DELAY, object, DELAY, bounds_x, bounds_y, 0);
    vertrix_call(calls, CLEAR_TIMER, object, DELAY, bounds_x, bounds_y, 0);
    put(t, object, 0x58, DWORD_WIDTH, 3);
    put(t, object, 0x5c, DWORD_WIDTH, 0);
    put(t, object, 0x60, DWORD_WIDTH, 1);
    put(t, object, 0x44, BYTE_WIDTH, 0);
    vertrix_call(calls, REGISTER, LIST, object, bounds_x, bounds_y, 0);
    vertrix_call(calls, RELEASE, local, 0, bounds_x, bounds_y, 0);
    return t->ok;
}

uint32_t vertrix_title_letter_first_call(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services, uint32_t frame,
                                         uint32_t mode, uint32_t previous_exception)
{
    if (!calls || !calls->call || !services || !services->resolve)
    {
        return 0;
    }
    static const TitleSpec spec = {0x516264, 0x50e62c, 0};
    return build_title_full(calls, services, frame, mode, &spec) ? previous_exception : 0;
}

uint32_t vertrix_title_letter_second_call(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services, uint32_t frame,
                                          uint32_t mode, uint32_t previous_exception)
{
    if (!calls || !calls->call || !services || !services->resolve)
    {
        return 0;
    }
    static const TitleSpec spec = {0x516278, 0x50e630, 3};
    return build_title_full(calls, services, frame, mode, &spec) ? previous_exception : 0;
}
