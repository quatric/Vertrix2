#include "port_wrappers.h"

/* The C runtime's handle close, plain import call and opener without a mode. */

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

/* Original 0x4e59d0: the handle 0x507c98, unless -1, is closed (slot 0x4f1cd8) and set to -1. */
uint32_t vertrix_port_handle_close_4e59d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t handle;
    uint32_t eax = entry->eax;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    handle = port_u32(&port, 0, 0x507c98);
    if (handle != 0xffffffffu)
    {
        args[0] = handle;
        eax = call_frame(&port, 0x4f1cd8, eax, handle, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp, args, 1);
        port_set32(&port, 0, 0x507c98, 0xffffffffu);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e9d10: the import of the slot 0x4f1b98 with no arguments. */
uint32_t vertrix_port_import_call_4e9d10(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = call_frame(&port, 0x4f1b98, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi,
                     entry->edi, entry->ebp, 0, 0);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4ebb78: the opener 0x4ebb34 with ebx 0. */
uint32_t vertrix_port_open_plain_4ebb78(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x4ebb34, entry->eax, entry->edx, 0, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}
