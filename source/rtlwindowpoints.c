#include "rtlwindowpoints.h"

enum
{
    /* The frame under the return slot: three saved registers, then (from its low end S) the point
     * made a client point (S) and the point copied (S+8). */
    BELOW = 0x1c,
    CLIENT_POINT = 0,
    POINT_COPY = 8,

    CLASS_CHECK_MODE = 2,

    WINDOW_FROM_POINT = 0x4f1b20,
    GET_PARENT = 0x4f19c8,
    SCREEN_TO_CLIENT = 0x4f1a84,
    IS_WINDOW_ENABLED = 0x4f1a24,
    CLASS_CHECK = 0x4dc290,
    CHILD_AT_POINT = 0x4dc2f0
};

/* Original 0x4ee750 (ebx = a screen point): the window under the point (WindowFromPoint), or 0.
 * When that window's parent passes 0x4dc290 (with 2) the parent is returned. Otherwise a visible
 * child control of the window under the point (0x4dc2f0, with the point made a client point by
 * ScreenToClient) is returned when IsWindowEnabled says it is disabled; else the window. edx
 * (callers read it) is the last callee's. */
uint32_t vertrix_port_rtl_window_at_point_4ee750(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - BELOW;
    const uint32_t point = entry->ebx;
    port_set32(&port, frame, POINT_COPY, port_u32(&port, point, 0));
    port_set32(&port, frame, POINT_COPY + 4, port_u32(&port, point, 4));
    port_set32(&port, frame, CLIENT_POINT, port_u32(&port, frame, POINT_COPY));
    port_set32(&port, frame, CLIENT_POINT + 4, port_u32(&port, frame, POINT_COPY + 4));
    uint32_t args[3] = {port_u32(&port, frame, POINT_COPY), port_u32(&port, frame, POINT_COPY + 4)};
    const uint32_t window = port_call_stack(&port, WINDOW_FROM_POINT, entry->eax, entry->edx, point,
                                            entry->ecx, args, 2);
    if (window == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    args[0] = window;
    const uint32_t parent =
        port_call_stack(&port, GET_PARENT, window, vertrix_lift_edx, point, entry->ecx, args, 1);
    if (parent != 0)
    {
        args[0] = parent;
        args[1] = CLASS_CHECK_MODE;
        if (port_call_stack(&port, CLASS_CHECK, parent, vertrix_lift_edx, parent, entry->ecx, args,
                            2) != 0)
        {
            return port_return(&port, parent, vertrix_lift_edx);
        }
    }
    args[0] = window;
    args[1] = frame + CLIENT_POINT;
    port_call_stack(&port, SCREEN_TO_CLIENT, frame + CLIENT_POINT, vertrix_lift_edx, parent,
                    entry->ecx, args, 2);
    args[0] = window;
    args[1] = port_u32(&port, frame, CLIENT_POINT);
    args[2] = port_u32(&port, frame, CLIENT_POINT + 4);
    const uint32_t child = port_call_stack(&port, CHILD_AT_POINT, frame + CLIENT_POINT,
                                           vertrix_lift_edx, parent, entry->ecx, args, 3);
    if (child != 0)
    {
        args[0] = child;
        if (port_call_stack(&port, IS_WINDOW_ENABLED, child, vertrix_lift_edx, child, entry->ecx,
                            args, 1) == 0)
        {
            return port_return(&port, child, vertrix_lift_edx);
        }
    }
    return port_return(&port, window, vertrix_lift_edx);
}
