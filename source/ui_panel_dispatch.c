#include "ui_panel_dispatch.h"

enum
{
    SLOT_DESTROY = 0,
    SLOT_FIRST = 1,
    SLOT_SECOND = 2,
    DESTROY_AND_FREE = 2
};

void vertrix_ui_panels_destroy(const uint32_t panels[VERTRIX_PANEL_COUNT], VertrixVirtualCall call,
                               void *context)
{
    for (int i = 0; i < VERTRIX_PANEL_COUNT; ++i)
    {
        if (panels[i])
        {
            call(context, panels[i], SLOT_DESTROY, DESTROY_AND_FREE);
        }
    }
}

void vertrix_ui_panels_slot1(const uint32_t panels[VERTRIX_PANEL_COUNT], VertrixVirtualCall call,
                             void *context)
{
    for (int i = 0; i < VERTRIX_PANEL_COUNT; ++i)
    {
        call(context, panels[i], SLOT_FIRST, 0);
    }
}

void vertrix_ui_panels_slot2(const uint32_t panels[VERTRIX_PANEL_COUNT], uint32_t argument,
                             VertrixVirtualCall call, void *context)
{
    static const int order[VERTRIX_PANEL_COUNT] = {1, 2, 3, 0};
    for (int i = 0; i < VERTRIX_PANEL_COUNT; ++i)
    {
        call(context, panels[order[i]], SLOT_SECOND, argument);
    }
}

uint32_t vertrix_ui_panel_release(uint32_t panel, VertrixVirtualCall call, void *context)
{
    if (panel)
    {
        call(context, panel, SLOT_DESTROY, DESTROY_AND_FREE);
    }
    return 0;
}

static int panel_method(const VertrixCalls *calls, VertrixMemoryRead read, void *context,
                        uint32_t handle, unsigned slot, uint32_t ebx, uint32_t ecx,
                        uint32_t argument, int table_argument, int table_ebx, uint32_t *result)
{
    uint32_t table, target;
    if (!calls || !calls->call || !read(handle + 0x158, 4, &table, context) ||
        !read(table + slot * 4, 4, &target, context))
    {
        return 0;
    }
    *result = vertrix_call(calls, target, handle, table_argument ? table : argument,
                           table_ebx ? table : ebx, slot == 0 ? table : ecx, 0);
    return 1;
}

static int panels_full(const VertrixCalls *calls, VertrixMemoryRead read, void *context,
                       unsigned slot, uint32_t eax, uint32_t ebx, uint32_t ecx, uint32_t *result)
{
    if (!read || !result)
    {
        return 0;
    }
    uint32_t returned = eax;
    for (unsigned i = 0; i < 4; ++i)
    {
        unsigned index = slot == 2 ? (i + 1) % 4 : i;
        uint32_t handle;
        if (!read(0x54670c + index * 4, 4, &handle, context))
        {
            return 0;
        }
        if (slot == 0 && i == 2)
        {
            ebx = handle;
        }
        if (slot == 0 && !handle)
        {
            continue;
        }
        if (!panel_method(calls, read, context, handle, slot, ebx, slot == 2 ? eax : ecx,
                          slot == 0 ? 2 : eax, slot == 1, slot == 2, &returned))
        {
            return 0;
        }
    }
    *result = returned;
    return 1;
}

int vertrix_ui_panels_destroy_full(const VertrixCalls *calls, VertrixMemoryRead read,
                                   void *memory_context, uint32_t eax, uint32_t ebx, uint32_t ecx,
                                   uint32_t *result)
{
    return panels_full(calls, read, memory_context, 0, eax, ebx, ecx, result);
}

int vertrix_ui_panels_slot1_full(const VertrixCalls *calls, VertrixMemoryRead read,
                                 void *memory_context, uint32_t eax, uint32_t ebx, uint32_t ecx,
                                 uint32_t *result)
{
    return panels_full(calls, read, memory_context, 1, eax, ebx, ecx, result);
}

int vertrix_ui_panels_slot2_full(const VertrixCalls *calls, VertrixMemoryRead read,
                                 void *memory_context, uint32_t eax, uint32_t ebx, uint32_t ecx,
                                 uint32_t *result)
{
    return panels_full(calls, read, memory_context, 2, eax, ebx, ecx, result);
}

int vertrix_ui_panel_release_full(const VertrixCalls *calls, VertrixMemoryRead read,
                                  VertrixMemoryWrite write, void *memory_context, uint32_t eax,
                                  uint32_t ebx, uint32_t ecx, uint32_t *result)
{
    uint32_t handle;
    if (!read || !result || !read(0x546794, 4, &handle, memory_context))
    {
        return 0;
    }
    uint32_t returned = eax;
    if (handle &&
        (!write ||
         !panel_method(calls, read, memory_context, handle, 0, ebx, ecx, 2, 0, 0, &returned) ||
         !write(0x546794, 4, 0, memory_context)))
    {
        return 0;
    }
    *result = returned;
    return 1;
}
