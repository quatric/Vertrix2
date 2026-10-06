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
