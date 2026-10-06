#include "text_wrap.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    SPACE = 0x20,
    ASSIGN = 0x4ca370,
    FROM_LITERAL = 0x4ca280,
    APPEND = 0x4ca630,
    MEASURE = 0x440610,
    RELEASE = 0x4ca210,
    CHAR_LITERAL = 0x511083,
    SPACE_LITERAL = 0x511084,
    SPACE_EBX = 3,
    FIELD_FONT_WORD = 0xe,
    FIELD_LEFT = 0x16,
    FIELD_NAME = 0x15c,
    FIELD_FONT = 0x160,
    FIELD_LINES = 0x161,
    FIELD_STARTS = 0x162,
    FIELD_LENGTHS = 0x22a,
    FIELD_SPACING = 0x44,
    LOCAL_CHAR_STRING = 0x48,
    LOCAL_CHAR_WIDTH = 0x44,
    LOCAL_CHAR_EXTRA = 0x40,
    LOCAL_SPACE_STRING = 0x3c,
    LOCAL_SPACE_WIDTH = 0x38,
    LOCAL_SPACE_EXTRA = 0x34,
    SIGN_SHIFT = 24,
    HALF_SHIFT = 16,
    JUNK_OFFSET = 2
};

typedef struct Wrap
{
    const VertrixFactoryServices *services;
    int ok;
} Wrap;

static uint32_t get(Wrap *w, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!w->services->resolve(handle, &storage, &size, w->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        w->ok = 0;
    }
    return value;
}

static void put(Wrap *w, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!w->services->resolve(handle, &storage, &size, w->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        w->ok = 0;
    }
}

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* The width of the string 0x4ca280 (and 0x4ca630 after it) made, measured by 0x440610. */
static uint32_t measure(const VertrixCalls *calls, uint32_t frame, uint32_t font_sign,
                        uint32_t string, uint32_t spacing, uint32_t ecx_local, uint32_t stack_local)
{
    VertrixCallSite site = {
        MEASURE, font_sign, string, spacing, frame - ecx_local, frame - stack_local, 0, 0,
        0,       0,         {0},    0};
    calls->call(&site, calls->context);
    return site.out_ecx;
}

static uint32_t line_get(Wrap *w, uint32_t object, uint32_t base, uint32_t line)
{
    return get(w, object, base + WORD_WIDTH * line, WORD_WIDTH);
}

static void line_put(Wrap *w, uint32_t object, uint32_t base, uint32_t line, uint32_t value)
{
    put(w, object, base + WORD_WIDTH * line, WORD_WIDTH, value);
}

/* Closes the line being built: its length is the position less its start. */
static uint32_t close_line(Wrap *w, uint32_t object, uint32_t position)
{
    uint32_t count = get(w, object, FIELD_LINES, BYTE_WIDTH);
    line_put(w, object, FIELD_LENGTHS, count, position - line_get(w, object, FIELD_STARTS, count));
    return count;
}

static void trim_lines(Wrap *w, uint32_t object, uint32_t text)
{
    uint32_t i;
    for (i = 0; w->ok && i < get(w, object, FIELD_LINES, BYTE_WIDTH); i++)
    {
        int32_t last = (int32_t)line_get(w, object, FIELD_LENGTHS, i) - 1;
        uint32_t start = line_get(w, object, FIELD_STARTS, i);
        if (last <= 0)
        {
            continue;
        }
        while (last > 0 && get(w, text, start + (uint32_t)last, BYTE_WIDTH) == SPACE)
        {
            last--;
        }
        line_put(w, object, FIELD_LENGTHS, i, last > 0 ? (uint32_t)last + 1 : 0);
    }
}

int vertrix_text_wrap(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t frame, const VertrixTextWrap *a)
{
    Wrap wrap = {services, 1};
    Wrap *w = &wrap;
    uint32_t object = a->object, name = object + FIELD_NAME, pointer, length = 0, position = 0;
    uint32_t available, running = 0, word = 0, junk, ebx = name, first = 1, font_sign, spacing;
    uint32_t end;
    vertrix_calln(calls, ASSIGN, name, a->text, name, a->ecx, NULL, 0, &pointer);
    put(w, object, FIELD_NAME, DWORD_WIDTH, pointer);
    put(w, object, FIELD_FONT, BYTE_WIDTH, a->font);
    put(w, object, FIELD_FONT_WORD, WORD_WIDTH, a->ecx);
    put(w, object, FIELD_LEFT, WORD_WIDTH, a->left);
    put(w, object, 0xf4, DWORD_WIDTH, sign16(a->right));
    put(w, object, 0xf8, DWORD_WIDTH, sign16(a->bottom));
    put(w, object, 0x2f2, WORD_WIDTH, a->margin_left);
    put(w, object, 0x2f4, WORD_WIDTH, a->margin_right);
    put(w, object, 0x2f6, WORD_WIDTH, a->spacing_a);
    put(w, object, 0x2f8, WORD_WIDTH, a->spacing_b);
    put(w, object, 0x2fc, DWORD_WIDTH, a->flag_a);
    put(w, object, 0x300, DWORD_WIDTH, a->flag_b);
    put(w, object, 0x304, DWORD_WIDTH, a->flag_c);
    while (w->ok && get(w, a->text, length, BYTE_WIDTH) != 0)
    {
        length++;
    }
    put(w, object, FIELD_LINES, BYTE_WIDTH, 0);
    available = a->right - (a->margin_left + a->margin_right);
    junk = get(w, frame - VERTRIX_TEXT_WRAP_FRAME, JUNK_OFFSET, WORD_WIDTH);
    font_sign = (uint32_t)(int32_t)(int8_t)get(w, object, FIELD_FONT, BYTE_WIDTH);
    spacing = get(w, object, FIELD_SPACING, BYTE_WIDTH);
    end = a->text + length;
    if (length != 0)
    {
        uint32_t i = 0;
        while (w->ok && get(w, pointer, i, BYTE_WIDTH) == SPACE)
        {
            position++;
            i++;
            if (i >= length)
            {
                break;
            }
        }
    }
    while (w->ok && position < length)
    {
        uint32_t index = position, scan = position, rc = 0;
        word = 0;
        while (w->ok && get(w, a->text, index, BYTE_WIDTH) != SPACE)
        {
            uint32_t string, character = get(w, a->text, index, BYTE_WIDTH);
            vertrix_calln(calls, FROM_LITERAL, frame - LOCAL_CHAR_STRING, CHAR_LITERAL, ebx, rc,
                          NULL, 0, &string);
            vertrix_calln(calls, APPEND, frame - LOCAL_CHAR_STRING, character, ebx, rc, NULL, 0,
                          &string);
            index++;
            scan++;
            word = (word + measure(calls, frame, font_sign, string, spacing, LOCAL_CHAR_WIDTH,
                                   LOCAL_CHAR_EXTRA)) &
                   0xffff;
            ebx = end;
            rc = 0;
            vertrix_call(calls, RELEASE, frame - LOCAL_CHAR_STRING, 0, ebx, rc, 0);
            if (index >= length)
            {
                break;
            }
        }
        if ((int32_t)(sign16(word) + (running & 0xffff)) > (int32_t)(available & 0xffff))
        {
            uint32_t count = get(w, object, FIELD_LINES, BYTE_WIDTH);
            uint32_t start = line_get(w, object, FIELD_STARTS, count);
            line_put(w, object, FIELD_LENGTHS, count, position - (((scan & 0xffff0000u) | start)));
            put(w, object, FIELD_LINES, BYTE_WIDTH, count + 1);
            running = 0;
            first = 1;
            ebx = (ebx & 0xffffff00u) | ((count + 1) & 0xff);
            continue;
        }
        if (first == 1)
        {
            line_put(w, object, FIELD_STARTS, get(w, object, FIELD_LINES, BYTE_WIDTH), position);
            first = 0;
        }
        ebx = running + ((junk << 16) | word);
        running = ebx;
        position = scan;
        word = 0;
        if (scan < length && get(w, pointer, scan, BYTE_WIDTH) == SPACE)
        {
            uint32_t space_ecx = 0;
            while (w->ok && scan < length && get(w, pointer, scan, BYTE_WIDTH) == SPACE)
            {
                uint32_t string;
                vertrix_calln(calls, FROM_LITERAL, frame - LOCAL_SPACE_STRING, SPACE_LITERAL,
                              SPACE_EBX, space_ecx, NULL, 0, &string);
                scan++;
                word = (word + measure(calls, frame, font_sign, string, spacing, LOCAL_SPACE_WIDTH,
                                       LOCAL_SPACE_EXTRA)) &
                       0xffff;
                vertrix_call(calls, RELEASE, frame - LOCAL_SPACE_STRING, 0, spacing,
                             frame - LOCAL_SPACE_WIDTH, 0);
                space_ecx = frame - LOCAL_SPACE_WIDTH;
                ebx = spacing;
            }
        }
        if ((int32_t)((running & 0xffff) + sign16(word)) > (int32_t)(available & 0xffff))
        {
            uint32_t count = get(w, object, FIELD_LINES, BYTE_WIDTH);
            uint32_t start = line_get(w, object, FIELD_STARTS, count);
            line_put(w, object, FIELD_LENGTHS, count, (position - start) & 0xffff);
            ebx = 1 | (((count + 1) & 0xff) << 8);
            put(w, object, FIELD_LINES, BYTE_WIDTH, count + 1);
            running = 0;
            first = 1;
            position = scan;
        }
        else
        {
            ebx = running + ((junk << 16) | word);
            running = ebx;
            position = scan;
        }
    }
    if ((running & 0xffff) != 0)
    {
        uint32_t count = close_line(w, object, position);
        put(w, object, FIELD_LINES, BYTE_WIDTH, count + 1);
    }
    trim_lines(w, object, pointer);
    return w->ok;
}
