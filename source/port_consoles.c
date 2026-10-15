#include "port_consoles.h"

/* The C runtime's handle close and console character write. */

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

/* Original 0x4e7c30: the handle number eax, when within 0 to 0x507c34, is closed under the lock
 * (0x507ca0, 0x507ca4) by the slot 0x4f1b6c on its entry of 0x507c8c, giving 0, or -1 with the
 * error kept (0x4e0884) on failure; out of range the error 4 is set (0x4dae70) and -1 given. */
uint32_t vertrix_port_handle_close_4e7c30(PORT_SIGNATURE)
{
    Port port;
    uint32_t number = entry->eax;
    uint32_t result = 0;
    uint32_t handle;
    uint32_t eax;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    if ((int32_t)number < 0 || number > port_u32(&port, 0, 0x507c34))
    {
        port_call_with(&port, 0x4dae70, 4, entry->edx, number, entry->ecx, 0, entry->edi,
                       entry->ebp);
        return port_return(&port, 0xffffffffu, entry->edx);
    }
    port_call_with(&port, port_u32(&port, 0, 0x507ca0), number, entry->edx, number, entry->ecx, 0,
                   entry->edi, entry->ebp);
    handle = port_u32(&port, port_u32(&port, 0, 0x507c8c), number * 4);
    args[0] = handle;
    eax = call_frame(&port, 0x4f1b6c, handle, vertrix_lift_edx, number, entry->ecx, 0, entry->edi,
                     entry->ebp, args, 1);
    if (eax == 0)
    {
        port_call_with(&port, 0x4e0884, eax, vertrix_lift_edx, number, entry->ecx, 0, entry->edi,
                       entry->ebp);
        result = 0xffffffffu;
    }
    port_call_with(&port, port_u32(&port, 0, 0x507ca4), number, vertrix_lift_edx, number,
                   entry->ecx, result, entry->edi, entry->ebp);
    return port_return(&port, result, entry->edx);
}

/* Original 0x4eda00: the character eax is written to the console: by the hooks 0x507cfc (with 1)
 * and 0x507d38 when that is set, otherwise under the lock 1 (0x507ca0, 0x507ca4) to the handle of
 * 0x4e89f4 by the slot 0x4f1d04. The character. */
uint32_t vertrix_port_console_put_4eda00(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t base = entry->esp - BELOW;
    uint32_t character = entry->eax;
    uint32_t hook;
    uint32_t eax;
    uint32_t args[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    hook = port_u32(&port, 0, 0x507d38);
    port_set8(&port, base, 4, character);
    if (hook != 0)
    {
        eax = port_call_with(&port, port_u32(&port, 0, 0x507cfc), 1, character, character,
                             entry->ecx, entry->esi, entry->edi, entry->ebp);
        port_call_with(&port, port_u32(&port, 0, 0x507d38), eax, vertrix_lift_edx, character,
                       entry->ecx, entry->esi, entry->edi, entry->ebp);
        return port_return(&port, character, entry->edx);
    }
    eax = port_call_with(&port, port_u32(&port, 0, 0x507ca0), 1, 0, character, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    eax = port_call_with(&port, 0x4e89f4, eax, vertrix_lift_edx, character, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    args[0] = eax;
    args[1] = base + 4;
    args[2] = 1;
    args[3] = base;
    args[4] = vertrix_lift_edx;
    call_frame(&port, 0x4f1d04, eax, base + 4, character, entry->ecx, entry->esi, entry->edi,
               entry->ebp, args, 5);
    port_call_with(&port, port_u32(&port, 0, 0x507ca4), 1, vertrix_lift_edx, character, entry->ecx,
                   entry->esi, entry->edi, entry->ebp);
    return port_return(&port, character, entry->edx);
}
