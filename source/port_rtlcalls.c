#include "port_rtlcalls.h"

/* The runtime library's call sequences. */

static uint32_t call_frame(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                           uint32_t edx, uint32_t ebx, uint32_t ecx, uint32_t esi,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = entry->edi;
    vertrix_lift_in_ebp = entry->ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4e1590: the handle [eax], when set, closed by 0x4f1c18; eax kept. */
uint32_t vertrix_port_rtl_handle_close_4e1590(PORT_SIGNATURE)
{
    Port port;
    uint32_t place = entry->eax;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    args[0] = port_u32(&port, place, 0);
    if (args[0] == 0)
    {
        return port_return(&port, place, entry->edx);
    }
    call_frame(&port, entry, 0x4f1c18, place, entry->edx, place, entry->ecx, entry->esi, args, 1);
    return port_return(&port, place, vertrix_lift_edx);
}

/* Original 0x43d370: the three dwords of 0x487a10 of the object eax's +0x468 into [edx], [ebx] and
 * [ecx] (edx as the call leaves it), then that object's method +0x14 with edx 0 and ebx 1. */
uint32_t vertrix_port_rtl_triple_fetch_43d370(PORT_SIGNATURE)
{
    Port port;
    uint32_t self = entry->eax;
    uint32_t triple;
    uint32_t first;
    uint32_t object;
    uint32_t methods;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    triple = port_call_with(&port, 0x487a10, port_u32(&port, self, 0x468), entry->edx, entry->ebx,
                            entry->ecx, self, entry->edi, entry->ebp);
    first = port_u32(&port, triple, 0);
    port_set32(&port, vertrix_lift_edx, 0, first);
    port_set32(&port, entry->ebx, 0, port_u32(&port, triple, 4));
    port_set32(&port, entry->ecx, 0, port_u32(&port, triple, 8));
    object = port_u32(&port, self, 0x468);
    methods = port_u32(&port, object, 0);
    eax = port_call_with(&port, port_u32(&port, methods, 0x14), object, 0, 1, methods, self, first,
                         entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4ce7e0: an object of 0x18 bytes (0x4dba80) of the class 0x519354 with +0xc cleared
 * and +0x10 0x14. */
uint32_t vertrix_port_rtl_object_new_4ce7e0(PORT_SIGNATURE)
{
    Port port;
    uint32_t args[1] = {0x18};
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = call_frame(&port, entry, 0x4dba80, entry->eax, entry->edx, entry->ebx, entry->ecx,
                     entry->esi, args, 1);
    if (eax != 0)
    {
        port_set32(&port, eax, 0xc, 0);
        port_set32(&port, eax, 0x10, 0);
        port_set32(&port, eax, 0, 0x519354);
        port_set32(&port, eax, 0x10, 0x14);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4eb4d4: the exit with the code eax: the hook 0x50b3ac, the error box (0x4e6bac of
 * 0x10 and 0xff) for a program (0x5c7b90 clear), then 0x4eb500; edx kept. */
uint32_t vertrix_port_rtl_exit_4eb4d4(PORT_SIGNATURE)
{
    Port port;
    uint32_t code = entry->eax;
    uint32_t edx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, port_u32(&port, 0, 0x50b3ac), code, entry->edx, code, entry->ecx,
                   entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    if (port_u8(&port, 0, 0x5c7b90) == 0)
    {
        port_call_with(&port, 0x4e6bac, 0x10, 0xff, code, entry->ecx, entry->esi, entry->edi,
                       entry->ebp);
        edx = vertrix_lift_edx;
    }
    eax = port_call_with(&port, 0x4eb500, code, edx, code, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e59c4: 0x4e596c of 1, then the handle 0x507c98 (unless -1) closed by 0x4f1cd8 and
 * set to -1; edx 0x4e596c's. */
uint32_t vertrix_port_rtl_shutdown_4e59c4(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    uint32_t edx;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x4e596c, 1, entry->edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    args[0] = port_u32(&port, 0, 0x507c98);
    if (args[0] != 0xffffffffu)
    {
        eax = call_frame(&port, entry, 0x4f1cd8, eax, args[0], entry->ebx, entry->ecx, entry->esi,
                         args, 1);
        port_set32(&port, 0, 0x507c98, 0xffffffffu);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x4d6a30 (ret 0x10): for the message 0x110 (second argument), the window of the first
 * (0x4cf910) found in 0x503b28 (0x4d3020) answers by its method +0xc0 (1 when none); other
 * messages give 0. */
uint32_t vertrix_port_rtl_dialog_init_4d6a30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 16];
    uint32_t args[1];
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    if (port_u32(&port, entry->esp, 8) != 0x110)
    {
        return port_return(&port, 0, entry->edx);
    }
    args[0] = port_u32(&port, entry->esp, 4);
    eax = call_frame(&port, entry, 0x4cf910, entry->eax, entry->edx, entry->ebx, entry->ecx,
                     entry->esi, args, 1);
    eax = port_call_with(&port, 0x4d3020, 0x503b28, eax, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    if (eax == 0)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
    eax = port_call_with(&port, port_u32(&port, port_u32(&port, eax, 0), 0xc0), eax,
                         port_u32(&port, eax, 0), entry->ebx, entry->ecx, entry->esi, entry->edi,
                         entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4e506c: the math error record eax, unless the hook 0x5096e0 takes it, reported
 * (0x4e5024 of its kind +0 and name +4, then 0x4dae80 for a domain error, 0x4dae94 otherwise);
 * edx:eax its result +0x18. */
uint32_t vertrix_port_rtl_math_error_4e506c(PORT_SIGNATURE)
{
    Port port;
    uint32_t record = entry->eax;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, port_u32(&port, 0, 0x5096e0), record, entry->edx, record,
                         entry->ecx, entry->esi, entry->edi, entry->ebp);
    if (eax == 0)
    {
        eax =
            port_call_with(&port, 0x4e5024, port_u32(&port, record, 0), port_u32(&port, record, 4),
                           record, entry->ecx, entry->esi, entry->edi, entry->ebp);
        port_call_with(&port, port_u32(&port, record, 0) == 1 ? 0x4dae80 : 0x4dae94, eax,
                       vertrix_lift_edx, record, entry->ecx, entry->esi, entry->edi, entry->ebp);
    }
    return port_return(&port, port_u32(&port, record, 0x18), port_u32(&port, record, 0x1c));
}
