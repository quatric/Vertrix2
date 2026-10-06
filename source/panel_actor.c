#include "panel_actor.h"

enum
{
    DWORD_WIDTH = 4,
    PANEL_ALLOCATE = 0x4ca000,
    PANEL_SIZE = 0x308,
    PANEL_WRAP = 0x4b2400,
    PANEL_LAYOUT = 0x4b25b0,
    PANEL_LAYOUT_ARGUMENTS = 10,
    PANEL_MEASURE = 0x4b2d90,
    PANEL_VTABLE = 0x158,
    PANEL_VIRTUAL_EDX = 2,
    PANEL_GLYPH = 0x4f9bff,
    PANEL_LEFT = 0x4f87fe,
    PANEL_FIRST = 0x4f8802,
    PANEL_SECOND = 0x4f8806,
    PANEL_HEIGHT = 0x4f880c
};

uint32_t vertrix_panel_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, uint32_t text, uint32_t edx,
                             uint32_t ebx, uint32_t ecx)
{
    uint32_t panel = vertrix_call(calls, PANEL_ALLOCATE, PANEL_SIZE, edx, ebx, ecx, 0);
    uint32_t glyph;
    uint32_t left;
    uint32_t stack[PANEL_LAYOUT_ARGUMENTS];
    uint32_t result;
    uint32_t table;
    void *storage;
    size_t size;
    if (panel != 0)
    {
        panel = vertrix_call(calls, PANEL_WRAP, panel, edx, ebx, ecx, 0);
    }
    vertrix_build_init(calls, panel);
    glyph = vertrix_build_global_high8(globals, PANEL_GLYPH);
    left = vertrix_build_global_high16(globals, PANEL_LEFT);
    stack[0] = vertrix_build_global_high16(globals, PANEL_FIRST);
    stack[1] = vertrix_build_global_high16(globals, PANEL_SECOND);
    stack[2] = vertrix_build_sign16(vertrix_build_global_word(globals, PANEL_HEIGHT) - 0xe);
    stack[3] = 2;
    stack[4] = 2;
    stack[5] = 0;
    stack[6] = 0;
    stack[7] = 1;
    stack[8] = 1;
    stack[9] = 1;
    vertrix_calln(calls, PANEL_LAYOUT, panel, text, glyph, left, stack, PANEL_LAYOUT_ARGUMENTS,
                  NULL);
    result = vertrix_call(calls, PANEL_MEASURE, panel, text, glyph, left, 0);
    if (panel == 0)
    {
        return result;
    }
    if (!services->resolve(panel, &storage, &size, services->context) ||
        !vertrix_actor_storage_read(storage, size, PANEL_VTABLE, DWORD_WIDTH, &table))
    {
        return 0;
    }
    vertrix_call(calls, globals->read(table, globals->context), panel, PANEL_VIRTUAL_EDX, glyph,
                 table, 0);
    return result;
}
