#include "label_actor.h"

#include "actor_storage.h"

enum
{
    BYTE_WIDTH = 1,
    ALLOCATE = 0x4ca000,
    INIT = 0x4adf20,
    INIT_ARGUMENTS = 5,
    SET_BOX = 0x4b54d0,
    SET_PERIOD = 0x4ac7b0,
    SET_FIRST = 0x4ac4e0,
    SET_VALUE = 0x4ac4f0,
    PLACE_TEXT = 0x4b65d0,
    LINK = 0x4b3210,
    FRAME_SIZE = 0x170,
    FRAME_WRAP = 0x4b3100,
    TEXT_SIZE = 0x180,
    TEXT_WRAP = 0x4b6350,
    TEXT_WRAP_ECX = 3,
    BOX_SIZE = 0x160,
    BOX_WRAP = 0x4b5400,
    SEH_FRAME = 0x4ec1ec,
    SEH_FRAME_FIRST = 0x515750,
    SEH_FRAME_SECOND = 0x51576c,
    PERIOD_STEPS = 2,
    FIELD_STYLE = 0x44,
    FIELD_SHADOW = 0x52,
    FIELD_SHOWN = 0x94,
    FIELD_SHOWN_TOO = 0x95,
    FIELD_MODE = 0x110,
    SECOND_EDX = 0x7f
};

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)(uint16_t)value;
}

static uint32_t word(uint32_t value)
{
    return value & 0xffff;
}

static int store_byte(const VertrixFactoryServices *services, uint32_t handle, uint32_t offset,
                      uint32_t value)
{
    void *storage;
    size_t size;
    return services->resolve(handle, &storage, &size, services->context) &&
           vertrix_actor_storage_write(storage, size, offset, BYTE_WIDTH, value);
}

static void init_actor(const VertrixCalls *calls, uint32_t actor)
{
    static const uint32_t zeros[INIT_ARGUMENTS] = {0, 0, 0, 0, 0};
    vertrix_calln(calls, INIT, actor, 0, 0, 0, zeros, INIT_ARGUMENTS, NULL);
}

uint32_t vertrix_label_frame(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             unsigned variant, uint32_t p, uint32_t dw, uint32_t bx, uint32_t cx,
                             const uint32_t arguments[5])
{
    static const uint32_t zeros[3] = {0, 0, 0};
    uint32_t width = bx - 4;
    uint32_t height = cx - 4;
    uint32_t y = sign16(dw + 2);
    uint32_t period_edx = PERIOD_STEPS;
    uint32_t text_edx;
    uint32_t glyph;
    uint32_t offset;
    uint32_t flag;
    uint32_t style;
    uint32_t frame;
    uint32_t text;
    uint32_t ebx_after;
    uint32_t stack[2];
    if (variant == 0)
    {
        text_edx = arguments[2];
        glyph = arguments[3];
        offset = arguments[0];
        flag = arguments[1];
        style = arguments[4];
    }
    else
    {
        text_edx = arguments[0];
        glyph = arguments[1];
        offset = arguments[3];
        flag = arguments[4];
        style = arguments[2];
    }
    frame = vertrix_call(calls, ALLOCATE, FRAME_SIZE, SEH_FRAME, 0,
                         variant == 0 ? SEH_FRAME_FIRST : SEH_FRAME_SECOND, 0);
    if (frame != 0)
    {
        frame = vertrix_call(calls, FRAME_WRAP, frame, 0, width, height, 0);
    }
    init_actor(calls, frame);
    vertrix_call(calls, SET_BOX, frame, sign16(p + 2), y, word(width), word(height));
    vertrix_call(calls, SET_PERIOD, frame, PERIOD_STEPS, y, word(width), 0);
    if (!store_byte(services, frame, FIELD_MODE, variant) ||
        (variant == 1 && !store_byte(services, frame, FIELD_SHADOW, 9)) ||
        !store_byte(services, frame, FIELD_SHOWN, 1) ||
        (variant == 1 && !store_byte(services, frame, FIELD_SHOWN_TOO, 1)))
    {
        return 0;
    }
    ebx_after = y;
    if (variant == 1)
    {
        vertrix_call(calls, SET_FIRST, frame, SECOND_EDX, 0, word(width), 0);
        period_edx = SECOND_EDX;
        ebx_after = 0;
    }
    text = vertrix_call(calls, ALLOCATE, TEXT_SIZE, period_edx, ebx_after, word(width), 0);
    if (text != 0)
    {
        text = vertrix_call(calls, TEXT_WRAP, text, period_edx, 0, TEXT_WRAP_ECX, 0);
    }
    init_actor(calls, text);
    vertrix_calln(calls, PLACE_TEXT, text, text_edx, (uint32_t)(int32_t)(int8_t)glyph, 0, zeros, 3,
                  NULL);
    vertrix_call(calls, SET_PERIOD, text, PERIOD_STEPS, (uint32_t)(int32_t)(int8_t)glyph, 0, 0);
    if (!store_byte(services, text, FIELD_STYLE, style))
    {
        return 0;
    }
    stack[0] = flag;
    stack[1] = 1;
    vertrix_calln(calls, LINK, frame, text, word(offset), 0, stack, 2, NULL);
    return frame;
}

uint32_t vertrix_label_box(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           unsigned variant, uint32_t p, uint32_t dw, uint32_t bx, uint32_t cx,
                           uint32_t stale)
{
    uint32_t ebx = (((stale & 0xffff) << 16) | word(dw)) + 2;
    uint32_t height = cx - 4;
    uint32_t width = bx - 4;
    uint32_t y = sign16(ebx);
    uint32_t actor = vertrix_call(calls, ALLOCATE, BOX_SIZE, p + 2, ebx, height, 0);
    if (actor != 0)
    {
        actor = vertrix_call(calls, BOX_WRAP, actor, p + 2, ebx, height, 0);
    }
    init_actor(calls, actor);
    vertrix_call(calls, SET_BOX, actor, sign16(p + 2), y, word(width), word(height));
    vertrix_call(calls, SET_PERIOD, actor, PERIOD_STEPS, y, word(width), 0);
    if (!store_byte(services, actor, FIELD_SHOWN, 1) ||
        !store_byte(services, actor, FIELD_SHOWN_TOO, 1) ||
        !store_byte(services, actor, FIELD_MODE, 1))
    {
        return 0;
    }
    vertrix_call(calls, SET_VALUE, actor, variant == 0 ? 0x450080 : 0x7f, 0, word(width), 0);
    vertrix_call(calls, SET_FIRST, actor, variant == 0 ? 0x3003e : 0x3f, 0, word(width), 0);
    return actor;
}
