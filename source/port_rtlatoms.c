#include "port_rtlatoms.h"

/* Atom pairs answered between windows. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4d51c0: the atom pair ebx (low and high words) sent to the control eax from the
 * window edx: when both match the application's pair +0xa8/+0xaa (0x4ce740's +4) each is read into
 * the frame (import 0x4f1c1c, 259 bytes) and released (0x4f1c08), and the window posted 0x3e4 with
 * the control's handle +0x1c and the pair (0x4f1a94). eax 0. */
uint32_t vertrix_port_atom_pair_answer_4d51c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x114
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - BELOW;
    uint32_t control = entry->eax;
    uint32_t window = entry->edx;
    uint32_t pair = entry->ebx;
    uint32_t application;
    uint32_t low = pair & 0xffff;
    uint32_t high = (pair >> 16) & 0xffff;
    uint32_t ecx = entry->ecx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    port_set32(&port, entry->esp, -8u, entry->esi);
    port_set32(&port, entry->esp, -0xcu, entry->edi);
    port_set32(&port, entry->esp, -0x10u, entry->ebp);
    application = call_frame(&port, 0x4ce740, control, entry->edx, entry->ebx, ecx, pair, control,
                             window, NULL, 0);
    application = port_u32(&port, application, 4);
    if (low == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    if (high == 0 || low != port_u16(&port, application, 0xa8) ||
        high != port_u16(&port, application, 0xaa))
    {
        return port_return(&port, 0, high);
    }
    {
        uint32_t args[3] = {low, esp, 0x103};
        call_frame(&port, 0x4f1c1c, low, high, application, ecx, pair, control, window, args, 3);
        args[0] = esp;
        call_frame(&port, 0x4f1c08, esp, vertrix_lift_edx, application, ecx, pair, control, window,
                   args, 1);
        args[0] = port_u16(&port, application, 0xaa);
        args[1] = esp;
        args[2] = 0x103;
        call_frame(&port, 0x4f1c1c, args[0], vertrix_lift_edx, application, ecx, pair, control,
                   window, args, 3);
        args[0] = esp;
        call_frame(&port, 0x4f1c08, esp, vertrix_lift_edx, application, ecx, pair, control, window,
                   args, 1);
    }
    {
        uint32_t lparam =
            (port_u16(&port, application, 0xaa) << 16) | port_u16(&port, application, 0xa8);
        uint32_t args[4] = {window, 0x3e4, port_u32(&port, control, 0x1c), lparam};
        call_frame(&port, 0x4f1a94, lparam, port_u16(&port, application, 0xa8), application, ecx,
                   pair, control, window, args, 4);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}
