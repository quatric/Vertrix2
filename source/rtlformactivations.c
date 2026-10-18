#include "rtlformactivations.h"

enum
{
    /* The control: its window handle and its state (+0x25 bit 1 while its own activation is
     * sent). */
    CONTROL_HANDLE = 0x1c,
    CONTROL_STATE = 0x25,
    STATE_ACTIVATING = 2,

    /* The activation flags: bit 3 or bit 2 asks for the non-client activation, bit 3 making it
     * inactive. */
    FLAGS_NONCLIENT = 0xc,
    FLAGS_INACTIVE = 8,
    FORM_STYLE = 0x40000000,

    WM_NCACTIVATE = 0x86,
    OWNED_ACTIVATE = 0x36d,
    FIRST_CHILD = 5,
    NEXT_WINDOW = 2,

    STYLE_OF = 0x4cccc0,
    FORM_OF = 0x4d1930,
    ACTIVE_OF = 0x4cce00,
    OWNED_BY = 0x4d4390,
    SEND_MESSAGE = 0x4f1a94,
    GET_DESKTOP_WINDOW = 0x4f1978,
    GET_WINDOW = 0x4f1a04
};

/* Original 0x4d4700 (eax = the control, edx = the activation flags): the control's form (the
 * control itself when 0x4cccc0 has bit 30, else 0x4d1930) gets the non-client activation when the
 * flags ask for it: WM_NCACTIVATE with 1 to the form 0x4cce00 leaves when that is set, active and
 * another window than the control (with the control's +0x25 bit 1 set meanwhile), else with 0 to
 * the form. Then every top-level window (GetWindow from the desktop's first child, 2 for the next)
 * owned by the form (0x4d4390) gets message 0x36d with the flags. Returns 0 (the last GetWindow).
 */
uint32_t vertrix_port_rtl_form_activate_4d4700(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t control = entry->eax;
    const uint32_t flags = entry->edx;
    const uint32_t ecx = entry->ecx;
    uint32_t args[4];
    uint32_t form = control;
    if ((port_call(&port, STYLE_OF, control, flags, control, ecx) & FORM_STYLE) == 0)
    {
        form = port_call_with(&port, FORM_OF, control, vertrix_lift_edx, control, ecx, entry->esi,
                              entry->edi, entry->ebp);
    }
    if ((flags & FLAGS_NONCLIENT) != 0)
    {
        const uint32_t active = (flags & FLAGS_INACTIVE) == 0;
        const uint32_t found = port_call(&port, ACTIVE_OF, form, form, control, ecx);
        const uint32_t window = vertrix_lift_edx;
        if (active && found != 0 && window != control)
        {
            port_set8(&port, control, CONTROL_STATE,
                      port_u8(&port, control, CONTROL_STATE) | STATE_ACTIVATING);
            args[0] = port_u32(&port, window, CONTROL_HANDLE);
            args[1] = WM_NCACTIVATE;
            args[2] = 1;
            args[3] = 0;
            port_call_stack(&port, SEND_MESSAGE, found, window, control, ecx, args, 4);
            port_set8(&port, control, CONTROL_STATE,
                      port_u8(&port, control, CONTROL_STATE) & ~STATE_ACTIVATING);
        }
        else
        {
            args[0] = port_u32(&port, form, CONTROL_HANDLE);
            args[1] = WM_NCACTIVATE;
            args[2] = 0;
            args[3] = 0;
            port_call_stack(&port, SEND_MESSAGE, found, window, control, ecx, args, 4);
        }
    }
    const uint32_t desktop =
        port_call_stack(&port, GET_DESKTOP_WINDOW, 0, vertrix_lift_edx, control, ecx, NULL, 0);
    args[0] = desktop;
    args[1] = FIRST_CHILD;
    uint32_t window =
        port_call_stack(&port, GET_WINDOW, desktop, vertrix_lift_edx, control, ecx, args, 2);
    while (window != 0 && !port.env.failed)
    {
        args[0] = port_u32(&port, form, CONTROL_HANDLE);
        args[1] = window;
        vertrix_lift_in_esi = form;
        vertrix_lift_in_edi = entry->edi;
        vertrix_lift_in_ebp = entry->ebp;
        const uint32_t owned =
            port_call_stack(&port, OWNED_BY, window, vertrix_lift_edx, window, ecx, args, 2);
        vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
        if (owned != 0)
        {
            args[0] = window;
            args[1] = OWNED_ACTIVATE;
            args[2] = flags;
            args[3] = 0;
            port_call_stack(&port, SEND_MESSAGE, owned, vertrix_lift_edx, window, ecx, args, 4);
        }
        args[0] = window;
        args[1] = NEXT_WINDOW;
        window = port_call_stack(&port, GET_WINDOW, window, vertrix_lift_edx, window, ecx, args, 2);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}
