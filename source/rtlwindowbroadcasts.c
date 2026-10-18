#include "rtlwindowbroadcasts.h"

enum
{
    /* The frame under the return slot: four saved registers. */
    BELOW = 0x10,
    ARGUMENTS = 6,

    /* The stdcall arguments above the return slot. */
    ARGUMENT_PARENT = 4,
    ARGUMENT_MESSAGE = 8,
    ARGUMENT_WPARAM = 0xc,
    ARGUMENT_LPARAM = 0x10,
    ARGUMENT_DEEP = 0x14,
    ARGUMENT_CONTROLS = 0x18,

    /* A control found for a window: its handler argument. */
    CONTROL_HANDLER = 0x1c,

    NEXT_WINDOW = 2,

    GET_TOP_WINDOW = 0x4f19e8,
    GET_WINDOW = 0x4f1a04,
    SEND_MESSAGE = 0x4f1a94,
    CONTROL_OF = 0x4cf910,
    CONTROL_DISPATCH = 0x4cf650,
    BROADCAST = 0x4d1ae0
};

/* A call with stack arguments handing the callee esi, edi and ebp (0x4cf650 reads edi and ebp). */
static uint32_t call_with_stack(Port *port, uint32_t target, uint32_t eax, uint32_t edx,
                                uint32_t ebx, uint32_t ecx, uint32_t esi, uint32_t edi,
                                uint32_t ebp, const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4d1ae0 (stdcall: parent, message, wparam, lparam, deep, controls): sends a message
 * to every child window of the parent (GetTopWindow, then GetWindow with 2 for the next). With
 * `controls` set the message goes to the child's control (0x4cf910), when it has one, through
 * 0x4cf650 with the control, its +0x1c and the message's three values; else SendMessageA. With
 * `deep` set a child that has children of its own is walked the same way first. Returns 0 (the
 * last GetWindow); edx is the last callee's. */
uint32_t vertrix_port_rtl_window_broadcast_4d1ae0(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    const uint32_t message = port_u32(&port, entry->esp, ARGUMENT_MESSAGE);
    const uint32_t wparam = port_u32(&port, entry->esp, ARGUMENT_WPARAM);
    const uint32_t lparam = port_u32(&port, entry->esp, ARGUMENT_LPARAM);
    const uint32_t deep = port_u32(&port, entry->esp, ARGUMENT_DEEP);
    const uint32_t controls = port_u32(&port, entry->esp, ARGUMENT_CONTROLS);
    uint32_t args[6] = {port_u32(&port, entry->esp, ARGUMENT_PARENT)};
    uint32_t window = port_call_stack(&port, GET_TOP_WINDOW, entry->eax, entry->edx, entry->ebx,
                                      entry->ecx, args, 1);
    while (window != 0 && !port.env.failed)
    {
        if (controls != 0)
        {
            args[0] = window;
            const uint32_t control = port_call_stack(&port, CONTROL_OF, window, vertrix_lift_edx,
                                                     window, entry->ecx, args, 1);
            if (control != 0)
            {
                args[0] = control;
                args[1] = port_u32(&port, control, CONTROL_HANDLER);
                args[2] = message;
                args[3] = wparam;
                args[4] = lparam;
                call_with_stack(&port, CONTROL_DISPATCH, control, vertrix_lift_edx, window,
                                entry->ecx, wparam, message, lparam, args, 5);
            }
        }
        else
        {
            args[0] = window;
            args[1] = message;
            args[2] = wparam;
            args[3] = lparam;
            port_call_stack(&port, SEND_MESSAGE, window, vertrix_lift_edx, window, entry->ecx, args,
                            4);
        }
        if (deep != 0)
        {
            args[0] = window;
            const uint32_t child = port_call_stack(&port, GET_TOP_WINDOW, window, vertrix_lift_edx,
                                                   window, entry->ecx, args, 1);
            if (child != 0)
            {
                args[1] = message;
                args[2] = wparam;
                args[3] = lparam;
                args[4] = deep;
                args[5] = controls;
                call_with_stack(&port, BROADCAST, child, vertrix_lift_edx, window, entry->ecx,
                                wparam, message, lparam, args, 6);
            }
        }
        args[0] = window;
        args[1] = NEXT_WINDOW;
        window = port_call_stack(&port, GET_WINDOW, window, vertrix_lift_edx, window, entry->ecx,
                                 args, 2);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}
