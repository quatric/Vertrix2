#include "rtlwindowcenters.h"

enum
{
    /* The window's rectangle, the work area and the rectangle it is centred in, under the saved
     * ebx, ecx, esi, edi and ebp. */
    BELOW = 0x44,
    WINDOW_RECT = 0x44,
    WORK_RECT = 0x34,
    PARENT_RECT = 0x24,
    LEFT = 0,
    TOP = 4,
    RIGHT = 8,
    BOTTOM = 0xc,

    HANDLE = 0x1c, /* the window object's and the parent object's window */
    CHILD = 0x40000000,
    VISIBLE = 0x10000000,
    MINIMIZED = 0x20000000,
    OWNER = 4,           /* GW_OWNER */
    STYLE = 0xfffffff0u, /* GWL_STYLE */
    WORK_AREA = 0x30,    /* SPI_GETWORKAREA */
    CENTER_ON = 0x36b,   /* the owner's answer: the window to centre on instead */
    MOVE_FLAGS = 0x15,   /* SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE */

    WINDOW_STYLE = 0x4cccc0,
    SET_POSITION = 0x4ccd80,
    GET_PARENT = 0x4f19c8, /* import slots */
    GET_WINDOW = 0x4f1a04,
    SEND_MESSAGE = 0x4f1a94,
    GET_WINDOW_RECT = 0x4f19f8,
    GET_WINDOW_LONG = 0x4f19f0,
    SYSTEM_PARAMETERS = 0x4f1af4,
    GET_CLIENT_RECT = 0x4f196c,
    MAP_WINDOW_POINTS = 0x4f1a48
};

static uint32_t import(Port *port, uint32_t slot, const uint32_t *arguments, unsigned count)
{
    return port_call_stack(port, port_u32(port, slot, 0), 0, 0, 0, 0, arguments, count);
}

/* Where an edge goes: centred, then kept inside [low, high]. */
static int32_t place(int32_t centre, int32_t size, int32_t low, int32_t high)
{
    int32_t at = centre - size / 2;
    if (at < low)
    {
        return low;
    }
    if (at + size > high)
    {
        return high - size;
    }
    return at;
}

/* Original 0x4d2710 (eax = the window object, edx = the object to centre over or 0): a window
 * centred. Without an object it is centred over its parent (a child window) or its owner, unless
 * the owner names another window (message 0x36b). A top-level window is centred over that window
 * while it is visible and not minimized, else over the work area, and kept inside the work area;
 * a child is centred in its parent's client area. The window is moved (0x4ccd80, no size, order or
 * activation change). */
uint32_t vertrix_port_rtl_window_center_4d2710(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t window = entry->eax;
    const uint32_t over = entry->edx;
    const uint32_t window_rect = entry->esp - WINDOW_RECT;
    const uint32_t work_rect = entry->esp - WORK_RECT;
    const uint32_t parent_rect = entry->esp - PARENT_RECT;
    const uint32_t style = port_call(&port, WINDOW_STYLE, window, over, entry->ebx, entry->ecx);
    const uint32_t handle = port_u32(&port, window, HANDLE);
    uint32_t centre_on = over != 0 ? port_u32(&port, over, HANDLE) : 0;
    if (over == 0)
    {
        if (style & CHILD)
        {
            centre_on = import(&port, GET_PARENT, &handle, 1);
        }
        else
        {
            const uint32_t arguments[2] = {handle, OWNER};
            centre_on = import(&port, GET_WINDOW, arguments, 2);
        }
        if (centre_on != 0)
        {
            const uint32_t arguments[4] = {centre_on, CENTER_ON, 0, 0};
            const uint32_t named = import(&port, SEND_MESSAGE, arguments, 4);
            if (named != 0)
            {
                centre_on = named;
            }
        }
    }
    {
        const uint32_t arguments[2] = {handle, window_rect};
        import(&port, GET_WINDOW_RECT, arguments, 2);
    }
    if ((style & CHILD) == 0)
    {
        if (centre_on != 0)
        {
            const uint32_t arguments[2] = {centre_on, STYLE};
            const uint32_t shown = import(&port, GET_WINDOW_LONG, arguments, 2);
            if ((shown & VISIBLE) == 0 || (shown & MINIMIZED) != 0)
            {
                centre_on = 0;
            }
        }
        {
            const uint32_t arguments[4] = {WORK_AREA, 0, work_rect, 0};
            import(&port, SYSTEM_PARAMETERS, arguments, 4);
        }
        if (centre_on == 0)
        {
            port_copy(&port, parent_rect, work_rect, 16);
        }
        else
        {
            const uint32_t arguments[2] = {centre_on, parent_rect};
            import(&port, GET_WINDOW_RECT, arguments, 2);
        }
    }
    else
    {
        const uint32_t parent = import(&port, GET_PARENT, &handle, 1);
        {
            const uint32_t arguments[2] = {parent, work_rect};
            import(&port, GET_CLIENT_RECT, arguments, 2);
        }
        {
            const uint32_t arguments[2] = {centre_on, parent_rect};
            import(&port, GET_CLIENT_RECT, arguments, 2);
        }
        const uint32_t arguments[4] = {centre_on, parent, parent_rect, 2};
        import(&port, MAP_WINDOW_POINTS, arguments, 4);
    }
    const int32_t width =
        (int32_t)(port_u32(&port, window_rect, RIGHT) - port_u32(&port, window_rect, LEFT));
    const int32_t height =
        (int32_t)(port_u32(&port, window_rect, BOTTOM) - port_u32(&port, window_rect, TOP));
    const int32_t x = place(
        (int32_t)(port_u32(&port, parent_rect, LEFT) + port_u32(&port, parent_rect, RIGHT)) / 2,
        width, (int32_t)port_u32(&port, work_rect, LEFT),
        (int32_t)port_u32(&port, work_rect, RIGHT));
    const int32_t y = place(
        (int32_t)(port_u32(&port, parent_rect, TOP) + port_u32(&port, parent_rect, BOTTOM)) / 2,
        height, (int32_t)port_u32(&port, work_rect, TOP),
        (int32_t)port_u32(&port, work_rect, BOTTOM));
    const uint32_t arguments[3] = {0xffffffffu, 0xffffffffu, MOVE_FLAGS};
    const uint32_t result =
        port_call_stack(&port, SET_POSITION, window, 0, (uint32_t)x, (uint32_t)y, arguments, 3);
    return port_return(&port, result, vertrix_lift_edx);
}
