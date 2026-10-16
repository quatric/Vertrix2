#include "port_rtlowners.h"

/* Window handle lookups and guarded image copies. */

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

/* Original 0x4d1890 (ret 4): the form owning the window handle (first argument): a known control
 * (0x4cf910) leads through its parent handle (+0x20, or 0x4f19c8 of its handle +0x1c) to the
 * control (0x4cf8e0) whose handle +0x1c is the answer (0 without one); an unknown handle is its
 * own parent (0x4f19c8) when a child (style bit 30 by 0x4f19f0 of -16), else 0x4f1a04 of it
 * with 4. */
uint32_t vertrix_port_rtl_owner_handle_4d1890(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t handle;
    uint32_t control;
    uint32_t eax;
    uint32_t args[2];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    handle = port_u32(&port, entry->esp, 4);
    args[0] = handle;
    control = call_frame(&port, 0x4cf910, entry->eax, entry->edx, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp, args, 1);
    if (control != 0)
    {
        eax = control;
        args[0] = port_u32(&port, control, 0x20);
        if (args[0] == 0)
        {
            args[0] = port_u32(&port, control, 0x1c);
            args[0] = call_frame(&port, 0x4f19c8, control, vertrix_lift_edx, entry->ebx, entry->ecx,
                                 entry->esi, entry->edi, entry->ebp, args, 1);
            eax = args[0];
        }
        eax = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp, args, 1);
        return port_return(&port, eax != 0 ? port_u32(&port, eax, 0x1c) : 0, vertrix_lift_edx);
    }
    args[0] = handle;
    args[1] = 0xfffffff0u;
    eax = call_frame(&port, 0x4f19f0, 0, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 2);
    if ((eax & 0x40000000u) != 0)
    {
        args[0] = handle;
        eax = call_frame(&port, 0x4f19c8, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp, args, 1);
        return port_return(&port, eax, vertrix_lift_edx);
    }
    args[0] = handle;
    args[1] = 4;
    eax = call_frame(&port, 0x4f1a04, eax, vertrix_lift_edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, args, 2);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x489170: under a guard frame (0x4ec1ec, 0x517144) and a jump buffer (0x4d93f0 and
 * 0x4d9f06), 0x4d79c0 copies ebx times ecx bytes from edx into eax; a jump back (1) ends it
 * through 0x4da6b6 instead. 0x4d9430 closes the buffer. eax 1 when copied, else 0. */
uint32_t vertrix_port_guarded_copy_489170(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x74
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t eax;
    uint32_t ebx = 0;
    uint32_t ecx = 0x517144;
    uint32_t esi = self;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->esi);
    port_set32(&port, ebp, -8, entry->edi);
    port_set32(&port, ebp, -0x14, entry->edx);
    port_set32(&port, ebp, -0x20, entry->ebx);
    port_set32(&port, ebp, -0xc, entry->ecx);
    port_set32(&port, ebp, -0x3c, port.env.chain);
    port.env.chain = ebp - 0x3c;
    port_set32(&port, ebp, -0x38, 0x4ec1ec);
    port_set32(&port, ebp, -0x34, 0x517144);
    port_set32(&port, ebp, -0x30, 0);
    port_set32(&port, ebp, -0x18, 1);
    eax = port_call_with(&port, 0x4d93f0, ebp - 0x28, 0x4ec1ec, 0, 0x517144, self, 1, ebp);
    port_set32(&port, ebp, -0x30, 2);
    eax = port_call_with(&port, 0x4d9f06, ebp - 0x70, vertrix_lift_edx, 0, 0x517144, self, 1, ebp);
    if (eax != 1)
    {
        ebx = port_u32(&port, ebp, -0x20) * port_u32(&port, ebp, -0xc);
        eax = port_call_with(&port, 0x4d79c0, self, port_u32(&port, ebp, -0x14), ebx, ecx, esi, 1,
                             ebp);
    }
    else
    {
        ecx = 4;
        eax = port_u32(&port, ebp, -0x10);
        port_set32(&port, ebp, -0x30, 4);
        port_set32(&port, ebp, -0x24, eax);
        port_set32(&port, ebp, -0x18, 0);
        esi = 2;
        eax = port_call_with(&port, 0x4da6b6, eax, vertrix_lift_edx, 0, 4, 2, 1, ebp);
        port_set32(&port, ebp, -0x30, 2);
    }
    port_set32(&port, ebp, -0x30, 0);
    port_call_with(&port, 0x4d9430, eax, vertrix_lift_edx, ebx, ecx, esi, 0, ebp);
    port_set32(&port, ebp, -0x30, 0);
    port_set32(&port, ebp, -0x1c, port_u32(&port, ebp, -0x18));
    port.env.chain = port_u32(&port, ebp, -0x3c);
    return port_return(&port, port_u32(&port, ebp, -0x1c), vertrix_lift_edx);
}
