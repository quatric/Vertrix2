#include "port_rtlranges.h"

/* The runtime library's range table dispatch. */

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

/* Original 0x4cb820 (ret 4): the object eax handles the code ebx for edx and ecx. Code -2 goes to
 * the method +4 of the handler +8 of 0x4ce760's object (with the stack argument). Otherwise the
 * code's high word (0x111 when none, or for code -1) and low word are looked up (0x4d0b30 with
 * edx) in the tables chained from the method +0x30's list (+4 each, next +0); the first match
 * hands its three dwords +0x14 and +0x10 to 0x4cb5a0 with ecx and the stack argument. No match
 * gives 0. */
uint32_t vertrix_port_rtl_range_dispatch_4cb820(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t self = entry->eax;
    uint32_t code = entry->ebx;
    uint32_t ebp = entry->edx;
    uint32_t edi = entry->ecx;
    uint32_t argument;
    uint32_t low;
    uint32_t kind = 0;
    uint32_t eax;
    uint32_t node;
    uint32_t methods;
    uint32_t args[6];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    argument = port_u32(&port, entry->esp, 4);
    if (code == 0xfffffffeu)
    {
        eax = port_call_with(&port, 0x4ce760, self, entry->edx, code, entry->ecx, entry->esi, edi,
                             ebp);
        eax = port_u32(&port, eax, 8);
        methods = port_u32(&port, eax, 0);
        args[0] = argument;
        eax = call_frame(&port, port_u32(&port, methods, 4), eax, self, ebp, edi, methods, edi, ebp,
                         args, 1);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    low = code;
    if (code != 0xffffffffu)
    {
        kind = code >> 16;
        low = code & 0xffff;
    }
    if (kind == 0)
    {
        kind = 0x111;
    }
    methods = port_u32(&port, self, 0);
    eax = port_call_with(&port, port_u32(&port, methods, 0x30), self, entry->edx, methods,
                         entry->ecx, kind, edi, ebp);
    node = eax;
    while (node != 0 && !port.env.failed)
    {
        args[0] = port_u32(&port, node, 4);
        args[1] = kind;
        args[2] = low;
        args[3] = ebp;
        eax = call_frame(&port, 0x4d0b30, eax, vertrix_lift_edx, node, entry->ecx, kind, edi, ebp,
                         args, 4);
        if (eax != 0)
        {
            args[0] = port_u32(&port, eax, 0x14);
            args[1] = port_u32(&port, eax, 0x18);
            args[2] = port_u32(&port, eax, 0x1c);
            args[3] = edi;
            args[4] = port_u32(&port, eax, 0x10);
            args[5] = argument;
            eax = call_frame(&port, 0x4cb5a0, self, ebp, low, entry->ecx, eax + 0x20,
                             entry->esp - 0x14, ebp, args, 6);
            return port_return(&port, eax, vertrix_lift_edx);
        }
        node = port_u32(&port, node, 0);
    }
    return port_return(&port, 0, vertrix_lift_edx);
}
