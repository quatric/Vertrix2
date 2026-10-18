#include "rtlconsoles.h"

/* Device state queries, standard handle set-up and window activation. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x40c160: the state of the device eax (below 0x20, from the table 0x52f178) into edx:
 * 1 when its method +0x24 leaves bit 0 of the frame flags clear, after a first 1; eax 1 for a
 * number past the table, 2 without edx, else 0. */
uint32_t vertrix_port_device_state_40c160(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t out = entry->edx;
    uint32_t device;
    uint32_t methods;
    uint32_t args[2];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    if (entry->eax >= 0x20)
    {
        return port_return(&port, 1, entry->edx);
    }
    if (out == 0)
    {
        return port_return(&port, 2, entry->edx);
    }
    port_set32(&port, out, 0, 1);
    device = port_u32(&port, entry->eax << 2, 0x52f178);
    if (device == 0)
    {
        return port_return(&port, 0, 0);
    }
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = ebp - 0xc;
    call_frame(&port, port_u32(&port, methods, 0x24), device, ebp - 0xc, out, methods, entry->esi,
               entry->edi, ebp, args, 2);
    port_set32(&port, out, 0, (port_u8(&port, ebp, -0xc) & 1) == 0 ? 1 : 0);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* One standard handle `which` (0x4f1be8): a missing one (0 or -1) goes to 0x4e0490, then
 * 0x4e02a4. */
static uint32_t standard_handle(Port *port, const LiftEntry *entry, uint32_t eax, uint32_t edx,
                                uint32_t which, uint32_t *edx_out)
{
    uint32_t args[1];
    args[0] = which;
    eax = call_frame(port, 0x4f1be8, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                     entry->ebp, args, 1);
    edx = eax;
    if (eax == 0 || eax == 0xffffffffu)
    {
        eax = port_call_with(port, 0x4e0490, eax, edx, entry->ebx, entry->ecx, entry->esi,
                             entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_call_with(port, 0x4e02a4, eax, edx, entry->ebx, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    *edx_out = vertrix_lift_edx;
    return eax;
}

/* Original 0x4e0430: the standard input, output and error handles (-10, -11, -12) each set up.
 * edx kept. */
uint32_t vertrix_port_rtl_standard_handles_4e0430(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t eax;
    uint32_t edx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp - 4, 0, entry->ecx);
    port_set32(&port, entry->esp - 8, 0, entry->edx);
    eax = standard_handle(&port, entry, entry->eax, entry->edx, 0xfffffff6u, &edx);
    eax = standard_handle(&port, entry, eax, edx, 0xfffffff5u, &edx);
    eax = standard_handle(&port, entry, eax, edx, 0xfffffff4u, &edx);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4d4e60: the window eax activated by the message edx (0x4d21a0, its method +0xf4); its
 * frame (+0x68) told by method +0x5c whether the low word is set with a clear high word; when it
 * is the active form's (0x4cbe80) +0x1c, the control to focus (0x4d5350, after its method +0xc4
 * when none) gets method +0xe8 with 0. eax 0. */
uint32_t vertrix_port_rtl_window_activate_4d4e60(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t message = entry->edx;
    uint32_t ecx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t esi = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t methods;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x4d21a0, self, message, ebx, ecx, esi, entry->edi, entry->ebp);
    methods = port_u32(&port, self, 0);
    eax = port_call_with(&port, port_u32(&port, methods, 0xf4), self, methods, ebx, ecx, esi,
                         entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    if (port_u32(&port, self, 0x68) != 0)
    {
        eax = port_u32(&port, self, 0x68);
        edx = ecx & 0xffff;
        ebx = port_u32(&port, eax, 0);
        if (edx != 0)
        {
            ecx = (ecx >> 16) & 0xffff;
            edx = ecx == 0 ? 1 : 0;
        }
        eax = port_call_with(&port, port_u32(&port, ebx, 0x5c), eax, edx, ebx, ecx, esi, entry->edi,
                             entry->ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_call_with(&port, 0x4cbe80, eax, edx, ebx, ecx, esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    if (port_u32(&port, eax, 0x1c) == self)
    {
        eax = port_call_with(&port, 0x4d5350, self, edx, ebx, ecx, esi, entry->edi, entry->ebp);
        edx = vertrix_lift_edx;
        if (eax == 0)
        {
            methods = port_u32(&port, self, 0);
            eax = port_call_with(&port, port_u32(&port, methods, 0xc4), self, methods, ebx, ecx,
                                 esi, entry->edi, entry->ebp);
            eax = port_call_with(&port, 0x4d5350, eax, vertrix_lift_edx, ebx, ecx, esi, entry->edi,
                                 entry->ebp);
            edx = vertrix_lift_edx;
        }
        if (eax != 0)
        {
            methods = port_u32(&port, eax, 0);
            port_call_with(&port, port_u32(&port, methods, 0xe8), eax, 0, eax, eax, methods,
                           entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
        }
    }
    return port_return(&port, 0, edx);
}
