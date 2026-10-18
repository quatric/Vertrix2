#include "rtlchildwindowpoints.h"

enum
{
    /* The frame under the return slot: three saved registers, then (from its low end S) a child's
     * rectangle (S) and a copy of the point (S+0x10). */
    BELOW = 0x24,
    ARGUMENTS = 3,
    RECTANGLE = 0,
    POINT_COPY = 0x10,

    /* The stdcall arguments above the return slot: the parent and the point's two coordinates. */
    ARGUMENT_PARENT = 4,
    ARGUMENT_POINT = 8,

    NO_CONTROL_ID = 0xffff,
    GWL_STYLE = 0xfffffff0u,
    WS_VISIBLE = 0x10000000,
    GW_CHILD = 5,
    GW_HWNDNEXT = 2,

    CLIENT_TO_SCREEN = 0x4f1918,
    GET_WINDOW = 0x4f1a04,
    GET_DLG_CTRL_ID = 0x4f1980,
    GET_WINDOW_LONG = 0x4f19f0,
    GET_WINDOW_RECT = 0x4f19f8,
    PT_IN_RECT = 0x4f1a68
};

static uint32_t next_window(Port *port, uint32_t window, uint32_t relation)
{
    const uint32_t args[2] = {window, relation};
    return port_call_stack(port, GET_WINDOW, window, vertrix_lift_edx, window, 0, args, 2);
}

/* Original 0x4dc2f0 (stdcall: parent, x, y): the parent's first visible child control (one with a
 * control id other than 0xffff and WS_VISIBLE) whose window rectangle holds the point, the point
 * first made a screen point (ClientToScreen in place on the arguments). Children are walked with
 * GetWindow (5, then 2). Returns the child, or 0. */
uint32_t vertrix_port_rtl_child_window_at_point_4dc2f0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const uint32_t frame = entry->esp - BELOW;
    const uint32_t parent = port_u32(&port, entry->esp, ARGUMENT_PARENT);
    const uint32_t point = entry->esp + ARGUMENT_POINT;
    uint32_t args[3] = {parent, point};
    port_call_stack(&port, CLIENT_TO_SCREEN, point, entry->edx, entry->ebx, entry->ecx, args, 2);
    uint32_t child = next_window(&port, parent, GW_CHILD);
    while (child != 0 && !port.env.failed)
    {
        args[0] = child;
        const uint32_t id =
            port_call_stack(&port, GET_DLG_CTRL_ID, child, vertrix_lift_edx, child, 0, args, 1);
        args[1] = GWL_STYLE;
        if ((id & 0xffff) != NO_CONTROL_ID &&
            (port_call_stack(&port, GET_WINDOW_LONG, child, vertrix_lift_edx, child, 0, args, 2) &
             WS_VISIBLE) != 0)
        {
            args[1] = frame + RECTANGLE;
            port_call_stack(&port, GET_WINDOW_RECT, frame + RECTANGLE, vertrix_lift_edx, child, 0,
                            args, 2);
            port_set32(&port, frame, POINT_COPY, port_u32(&port, point, 0));
            port_set32(&port, frame, POINT_COPY + 4, port_u32(&port, point, 4));
            args[0] = frame + RECTANGLE;
            args[1] = port_u32(&port, frame, POINT_COPY);
            args[2] = port_u32(&port, frame, POINT_COPY + 4);
            if (port_call_stack(&port, PT_IN_RECT, frame + RECTANGLE, vertrix_lift_edx, child, 0,
                                args, 3) != 0)
            {
                return port_return(&port, child, vertrix_lift_edx);
            }
        }
        child = next_window(&port, child, GW_HWNDNEXT);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}
