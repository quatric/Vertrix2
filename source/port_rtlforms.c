#include "port_rtlforms.h"

/* Form state updates, item broadcasts and wide text conversion. */

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

/* Original 0x47fc10: the text ebx (ecx characters, -1 to its end) widened into edx by 0x4f1c6c
 * and ended; nothing without a text or target. */
uint32_t vertrix_port_text_widen_47fc10(PORT_SIGNATURE)
{
    Port port;
    uint32_t target = entry->edx;
    uint32_t text = entry->ebx;
    uint32_t eax = entry->eax;
    uint32_t edi = entry->ecx;
    uint32_t args[6];
    port_open(&port, calls, services, globals, entry);
    if (target == 0 || text == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    if (edi == 0xffffffffu)
    {
        uint32_t length = 0;
        while (port_u8(&port, text, length) != 0 && !port.env.failed)
        {
            length++;
        }
        eax = 0;
        edi = length + 1;
    }
    args[0] = 0;
    args[1] = 0;
    args[2] = text;
    args[3] = 0xffffffffu;
    args[4] = target;
    args[5] = edi - 1;
    eax = call_frame(&port, 0x4f1c6c, eax, entry->edx, text, edi - 1, target, edi, entry->ebp, args,
                     6);
    port_set16(&port, target, edi * 2 - 2, 0);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x43a280: each of the three items of eax (+0x15c) given edx by its class (+0x158)
 * method +8. edx as the last step leaves it. */
uint32_t vertrix_port_items_broadcast_43a280(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t esi = entry->esi;
    uint32_t slot;
    port_open(&port, calls, services, globals, entry);
    for (slot = self; slot != self + 0xc && !port.env.failed; slot += 4)
    {
        edx = port_u32(&port, slot, 0x15c);
        if (edx != 0)
        {
            esi = port_u32(&port, edx, 0x158);
            eax = port_call_with(&port, port_u32(&port, esi, 8), edx, entry->edx, entry->edx, slot,
                                 esi, self + 0xc, entry->ebp);
            edx = vertrix_lift_edx;
        }
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4d49a0: unless 0x4cf850 gives -1, a form whose method +0xe0 agrees gets the message
 * 0x362 (0x4f1a60 with 0xe001) and its method +0xcc with 1 (0); a refusal gives -1. */
uint32_t vertrix_port_rtl_form_close_4d49a0(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t methods;
    uint32_t table;
    uint32_t eax;
    uint32_t args[4];
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x4cf850, self, entry->edx, entry->ebx, entry->ecx, self,
                         entry->edi, entry->ebp);
    if (eax == 0xffffffffu)
    {
        return port_return(&port, eax, vertrix_lift_edx);
    }
    methods = port_u32(&port, self, 0);
    eax = port_call_with(&port, port_u32(&port, methods, 0xe0), self, vertrix_lift_edx, entry->ebx,
                         methods, self, entry->edi, entry->ebp);
    if (eax == 0)
    {
        return port_return(&port, 0xffffffffu, vertrix_lift_edx);
    }
    args[0] = port_u32(&port, self, 0x1c);
    args[1] = 0x362;
    args[2] = 0xe001;
    args[3] = 0;
    call_frame(&port, 0x4f1a60, eax, vertrix_lift_edx, entry->ebx, methods, self, entry->edi,
               entry->ebp, args, 4);
    table = port_u32(&port, self, 0);
    port_call_with(&port, port_u32(&port, table, 0xcc), self, 1, table, methods, self, entry->edi,
                   entry->ebp);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x4d6080: the form eax's pending changes (+0xb8): bit 0 its method +0xe8 with +0xa8,
 * bit 1 its method +0xe4 with 1, bit 3 its method +0xcc with bit 2 and 0x4f1b14 of its handle
 * +0x1c; a changed +0x90 (against +0x94) goes to 0x4d5910; the changes cleared, edx kept. */
uint32_t vertrix_port_rtl_form_apply_4d6080(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t ecx = entry->ecx;
    uint32_t edx;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    if ((port_u8(&port, self, 0xb8) & 1) != 0)
    {
        ecx = port_u32(&port, self, 0);
        eax = port_call_with(&port, port_u32(&port, ecx, 0xe8), eax, port_u32(&port, self, 0xa8),
                             self, ecx, entry->esi, entry->edi, entry->ebp);
    }
    if ((port_u8(&port, self, 0xb8) & 2) != 0)
    {
        ecx = port_u32(&port, self, 0);
        eax = port_call_with(&port, port_u32(&port, ecx, 0xe4), self, 1, self, ecx, entry->esi,
                             entry->edi, entry->ebp);
    }
    if ((port_u8(&port, self, 0xb8) & 8) != 0)
    {
        ecx = port_u32(&port, self, 0);
        eax =
            port_call_with(&port, port_u32(&port, ecx, 0xcc), self, port_u32(&port, self, 0xb8) & 4,
                           self, ecx, entry->esi, entry->edi, entry->ebp);
        args[0] = port_u32(&port, self, 0x1c);
        eax = call_frame(&port, 0x4f1b14, eax, vertrix_lift_edx, self, ecx, entry->esi, entry->edi,
                         entry->ebp, args, 1);
    }
    edx = port_u32(&port, self, 0x90);
    if (edx != port_u32(&port, self, 0x94))
    {
        eax = port_call_with(&port, 0x4d5910, self, edx, self, ecx, entry->esi, entry->edi,
                             entry->ebp);
    }
    port_set32(&port, self, 0xb8, 0);
    return port_return(&port, eax, entry->edx);
}
