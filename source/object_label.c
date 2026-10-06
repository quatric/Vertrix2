#include "object_label.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    LABEL_INIT = 0x4ca070,
    LABEL_ASSIGN = 0x4ca370,
    LABEL_RELEASE = 0x4ca210,
    LABEL_PLACE = 0x4b65d0,
    LABEL_PLACE_ARGUMENTS = 3,
    LABEL_PARENT = 0x160,
    LABEL_OFFSET_X = 0x164,
    LABEL_OFFSET_Y = 0x166,
    LABEL_FLAG_X = 0x168,
    LABEL_FLAG_Y = 0x16c,
    LABEL_PARENT_TEXT = 0x15c,
    LABEL_PARENT_GLYPH = 0x160,
    LABEL_LEFT = 0xe,
    LABEL_TOP = 0x16,
    LABEL_WIDTH = 0xf4,
    LABEL_HEIGHT = 0xf8
};

static int16_t signed_word(uint32_t value)
{
    return (int16_t)(uint16_t)value;
}

static uint32_t sign_extend(uint32_t value)
{
    return (uint32_t)(int32_t)signed_word(value);
}

int vertrix_object_place_label(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t object, uint32_t parent, uint32_t ebx, uint32_t ecx,
                               uint32_t flag_x_arg, uint32_t flag_y_arg, uint32_t temp)
{
    void *storage;
    size_t size;
    void *parent_storage;
    size_t parent_size;
    uint32_t held = 0;
    uint32_t flag_x;
    uint32_t flag_y;
    uint32_t left;
    uint32_t top;
    uint32_t text;
    uint32_t glyph;
    uint32_t x1;
    uint32_t x2;
    uint32_t y1;
    uint32_t y2;
    uint32_t stack[LABEL_PLACE_ARGUMENTS];
    uint32_t word;
    uint32_t word_extra;
    if (!services->resolve(object, &storage, &size, services->context))
    {
        return 0;
    }
    vertrix_calln(calls, LABEL_INIT, temp, parent, ebx, ecx, NULL, 0, &held);
    if (!vertrix_actor_storage_write(storage, size, LABEL_PARENT, DWORD_WIDTH, parent) ||
        !vertrix_actor_storage_write(storage, size, LABEL_OFFSET_X, WORD_WIDTH, ebx) ||
        !vertrix_actor_storage_write(storage, size, LABEL_OFFSET_Y, WORD_WIDTH, ecx) ||
        !vertrix_actor_storage_write(storage, size, LABEL_FLAG_X, DWORD_WIDTH, flag_x_arg) ||
        !vertrix_actor_storage_write(storage, size, LABEL_FLAG_Y, DWORD_WIDTH, flag_y_arg))
    {
        return 0;
    }
    if (parent == 0)
    {
        vertrix_call(calls, LABEL_RELEASE, temp, 0, ebx, ecx, 0);
        return 1;
    }
    if (!services->resolve(parent, &parent_storage, &parent_size, services->context) ||
        !vertrix_actor_storage_read(parent_storage, parent_size, LABEL_PARENT_TEXT, DWORD_WIDTH,
                                    &text))
    {
        return 0;
    }
    vertrix_calln(calls, LABEL_ASSIGN, temp, text, ebx, ecx, NULL, 0, &held);
    if (!vertrix_actor_storage_read(parent_storage, parent_size, LABEL_PARENT_GLYPH, BYTE_WIDTH,
                                    &glyph) ||
        !vertrix_actor_storage_read(storage, size, LABEL_FLAG_X, DWORD_WIDTH, &flag_x) ||
        !vertrix_actor_storage_read(storage, size, LABEL_FLAG_Y, DWORD_WIDTH, &flag_y) ||
        !vertrix_actor_storage_read(storage, size, LABEL_LEFT, WORD_WIDTH, &left) ||
        !vertrix_actor_storage_read(storage, size, LABEL_TOP, WORD_WIDTH, &top))
    {
        return 0;
    }
    glyph = (uint32_t)(int32_t)(int8_t)glyph;
    if (flag_x == 0)
    {
        if (!vertrix_actor_storage_read(storage, size, LABEL_OFFSET_X, WORD_WIDTH, &word))
        {
            return 0;
        }
        x1 = left + word;
        x2 = x1;
    }
    else
    {
        if (!vertrix_actor_storage_read(storage, size, LABEL_WIDTH, WORD_WIDTH, &word))
        {
            return 0;
        }
        x1 = left;
        x2 = left + word - 1;
    }
    if (flag_y == 0)
    {
        if (!vertrix_actor_storage_read(storage, size, LABEL_OFFSET_Y, WORD_WIDTH, &word_extra))
        {
            return 0;
        }
        y1 = top + word_extra;
        y2 = y1;
    }
    else
    {
        if (!vertrix_actor_storage_read(storage, size, LABEL_HEIGHT, WORD_WIDTH, &word_extra))
        {
            return 0;
        }
        y1 = top;
        y2 = top + word_extra - 1;
    }
    x1 = sign_extend(x1);
    stack[0] = sign_extend(x2);
    stack[1] = sign_extend(y1);
    stack[2] = sign_extend(y2);
    vertrix_calln(calls, LABEL_PLACE, parent, held, glyph, x1, stack, LABEL_PLACE_ARGUMENTS, NULL);
    vertrix_call(calls, LABEL_RELEASE, temp, 0, glyph, x1, 0);
    return 1;
}
