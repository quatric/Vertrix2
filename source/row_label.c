#include "row_label.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    ROW_ALLOCATE = 0x4ca000,
    ROW_FRAME_SIZE = 0x170,
    ROW_FRAME_WRAP = 0x4b3100,
    ROW_TEXT_SIZE = 0x180,
    ROW_TEXT_WRAP = 0x4b6350,
    ROW_TEXT_WRAP_ECX = 3,
    ROW_BOX = 0x4b54d0,
    ROW_PERIOD = 0x4ac7b0,
    ROW_PLACE = 0x4b65d0,
    ROW_LINK = 0x4b3210,
    ROW_X = 2,
    ROW_WIDTH = 0xdc,
    ROW_HEIGHT = 0x16,
    ROW_PERIOD_STEPS = 2,
    ROW_BASE = 0x4f88ac,
    ROW_GLYPH = 0x4f9c08,
    ROW_STRIDE = 0x16,
    ROW_CLIP_RIGHT = 0x27f,
    ROW_CLIP_BOTTOM = 0x1df,
    ROW_CLIP_LEFT = 0xa8,
    ROW_CLIP_FIRST = 0xaa,
    ROW_CLIP_TOP = 0xac,
    ROW_CLIP_LAST = 0xae,
    ROW_MODE = 0x8e,
    ROW_STYLE = 0x44,
    ROW_SHADOW = 0x52,
    ROW_OFFSET = 0x48,
    ROW_STATE = 0x4e,
    ROW_SHOWN = 0x93,
    ROW_SHOWN_FRAME = 0x94,
    ROW_SHOWN_TEXT = 0x95
};

static int store_clip(const VertrixFactoryServices *services, const VertrixGlobals *globals,
                      uint32_t actor)
{
    return vertrix_build_store(services, actor, ROW_CLIP_LEFT, WORD_WIDTH, 0) &&
           vertrix_build_store(services, actor, ROW_CLIP_FIRST, WORD_WIDTH, ROW_CLIP_RIGHT) &&
           vertrix_build_store(services, actor, ROW_CLIP_LAST, WORD_WIDTH, ROW_CLIP_BOTTOM) &&
           vertrix_build_store(services, actor, ROW_CLIP_TOP, WORD_WIDTH,
                               vertrix_build_global_word(globals, ROW_BASE)) &&
           vertrix_build_store(services, actor, ROW_MODE, BYTE_WIDTH, 3);
}

uint32_t vertrix_row_label(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, uint32_t eax, uint32_t edx, uint32_t ebx)
{
    uint32_t row = vertrix_build_sign8(eax);
    uint32_t y =
        vertrix_build_word(row * ROW_STRIDE + vertrix_build_global_word(globals, ROW_BASE) + 1);
    uint32_t merged = (ebx & ~0xffu) | (eax & 0xff);
    uint32_t sign_y = vertrix_build_sign16(y);
    uint32_t frame = vertrix_call(calls, ROW_ALLOCATE, ROW_FRAME_SIZE, ROW_X, merged, ROW_WIDTH, 0);
    uint32_t text;
    uint32_t stack[2] = {1, 1};
    static const uint32_t zeros[3] = {0, 0, 0};
    uint32_t glyph;
    if (frame != 0)
    {
        frame = vertrix_call(calls, ROW_FRAME_WRAP, frame, 0, merged, ROW_WIDTH, 0);
    }
    vertrix_build_init(calls, frame);
    vertrix_call(calls, ROW_BOX, frame, ROW_X, sign_y, ROW_WIDTH, ROW_HEIGHT);
    vertrix_call(calls, ROW_PERIOD, frame, ROW_PERIOD_STEPS, sign_y, ROW_WIDTH, 0);
    if (!vertrix_build_store(services, frame, ROW_SHADOW, BYTE_WIDTH, 9) ||
        !vertrix_build_store(services, frame, ROW_OFFSET, WORD_WIDTH, 0) ||
        !vertrix_build_store(services, frame, ROW_STYLE, BYTE_WIDTH, 0x10) ||
        !vertrix_build_store(services, frame, ROW_SHOWN_FRAME, BYTE_WIDTH, 1) ||
        !vertrix_build_store(services, frame, ROW_SHOWN_TEXT, BYTE_WIDTH, 0) ||
        !store_clip(services, globals, frame))
    {
        return 0;
    }
    text = vertrix_call(calls, ROW_ALLOCATE, ROW_TEXT_SIZE, ROW_X, sign_y, ROW_WIDTH, 0);
    if (text != 0)
    {
        text = vertrix_call(calls, ROW_TEXT_WRAP, text, ROW_X, 0, ROW_TEXT_WRAP_ECX, 0);
    }
    vertrix_build_init(calls, text);
    glyph = vertrix_build_global_high8(globals, ROW_GLYPH);
    vertrix_calln(calls, ROW_PLACE, text, edx, glyph, 0, zeros, 3, NULL);
    vertrix_call(calls, ROW_PERIOD, text, ROW_PERIOD_STEPS, glyph, 0, 0);
    if (!vertrix_build_store(services, text, ROW_STYLE, BYTE_WIDTH, 0x10) ||
        !vertrix_build_store(services, text, ROW_STATE, BYTE_WIDTH, 0x32) ||
        !vertrix_build_store(services, text, ROW_SHOWN, BYTE_WIDTH, 0) ||
        !vertrix_build_store(services, text, ROW_SHOWN_TEXT, BYTE_WIDTH, 4))
    {
        return 0;
    }
    vertrix_calln(calls, ROW_LINK, frame, text, 0, 0, stack, 2, NULL);
    if (!store_clip(services, globals, text))
    {
        return 0;
    }
    return frame;
}
