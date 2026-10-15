#include "port_rtlloops.h"

/* The runtime library's record sweeps. */

/* Original 0x4cd847: every record 0x4e0eaf finds for eax, edx and ebx is handed with eax to
 * 0x4e0ec7, until none is left; eax 0. */
uint32_t vertrix_port_record_sweep_4cd847(PORT_SIGNATURE)
{
    Port port;
    uint32_t found;
    port_open(&port, calls, services, globals, entry);
    for (;;)
    {
        found = port_call_with(&port, 0x4e0eaf, entry->eax, entry->edx, entry->ebx, entry->eax,
                               entry->ebx, entry->edx, entry->ebp);
        if (found == 0 || port.env.failed)
        {
            break;
        }
        port_call_with(&port, 0x4e0ec7, found, entry->eax, entry->ebx, entry->eax, entry->ebx,
                       entry->edx, entry->ebp);
    }
    return port_return(&port, found, vertrix_lift_edx);
}

static uint32_t call_frame(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                           uint32_t edx, uint32_t ebx, const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = entry->esi;
    vertrix_lift_in_edi = entry->edi;
    vertrix_lift_in_ebp = entry->ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, entry->ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4cf5d0 (ret 0xc): for code -2 (the second stack argument) and a button press 0x201,
 * 0x207 or 0x204 (the third), the window 0x4d1900 finds for the first argument, taken to its
 * top window (0x4f199c, 0x4cf8e0), unless it is already the active one (0x4f1994, 0x4cf8e0) and
 * when 0x4cce00 allows it, is brought forward (0x4f1aac on its handle +0x1c), giving 1; else 0. */
uint32_t vertrix_port_rtl_window_click_raise_4cf5d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * 3];
    uint32_t message;
    uint32_t window;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t args[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    message = port_u32(&port, entry->esp, 0xc);
    if (port_u32(&port, entry->esp, 8) != 0xfffffffeu ||
        (message != 0x201 && message != 0x207 && message != 0x204))
    {
        return port_return(&port, 0, edx);
    }
    window = port_call_with(&port, 0x4d1900, port_u32(&port, entry->esp, 4), edx, entry->ebx,
                            entry->ecx, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    if (window != 0)
    {
        args[0] = port_u32(&port, window, 0x1c);
        eax = call_frame(&port, entry, 0x4f199c, window, edx, window, args, 1);
        args[0] = eax;
        window = call_frame(&port, entry, 0x4cf8e0, eax, vertrix_lift_edx, window, args, 1);
        edx = vertrix_lift_edx;
    }
    if (window == 0)
    {
        return port_return(&port, 0, edx);
    }
    eax = call_frame(&port, entry, 0x4f1994, window, edx, window, args, 0);
    args[0] = eax;
    eax = call_frame(&port, entry, 0x4cf8e0, eax, vertrix_lift_edx, window, args, 1);
    edx = vertrix_lift_edx;
    if (window == eax)
    {
        return port_return(&port, 0, edx);
    }
    eax = port_call_with(&port, 0x4cce00, window, edx, window, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    edx = vertrix_lift_edx;
    if (eax == 0)
    {
        return port_return(&port, 0, edx);
    }
    args[0] = port_u32(&port, window, 0x1c);
    call_frame(&port, entry, 0x4f1aac, eax, edx, window, args, 1);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x4ddc60: the object eax gives up its handle +4 (returned in eax, the field cleared);
 * a set handle is first unmapped from the map 0x4ddbe0 gives (0x4df1c0). edx kept. */
uint32_t vertrix_port_rtl_handle_detach_4ddc60(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t handle;
    uint32_t map;
    port_open(&port, calls, services, globals, entry);
    handle = port_u32(&port, self, 4);
    if (handle != 0)
    {
        map = port_call_with(&port, 0x4ddbe0, 0, entry->edx, handle, self, entry->esi, entry->edi,
                             entry->ebp);
        if (map != 0)
        {
            port_call_with(&port, 0x4df1c0, map, port_u32(&port, self, 4), handle, self, entry->esi,
                           entry->edi, entry->ebp);
        }
    }
    port_set32(&port, self, 4, 0);
    return port_return(&port, handle, entry->edx);
}
