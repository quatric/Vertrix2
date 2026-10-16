#include "port_rtllookups.h"

/* Short routines: lookups, small frame records and a selecting jump. */

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

/* Original 0x4dabd0: a non-zero eax goes on to 0x4e3ce0; else 0x4e3f20 and 0. */
uint32_t vertrix_port_rtl_select_4e3ce0_4dabd0(PORT_SIGNATURE)
{
    Port port;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (entry->eax != 0)
    {
        result =
            port_forward(&port, entry, 0x4e3ce0, entry->eax, entry->edx, entry->ebx, entry->ecx);
        return port_return(&port, result, vertrix_lift_edx);
    }
    port_forward(&port, entry, 0x4e3f20, 0, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x42a190: 1 when the choice of row edx (16 dwords a row) and column ebx in the grid
 * eax (+0x15c) holds an item whose byte +0x15c is clear, else 0 (the shared return 0x42a15a);
 * edx is left shifted by 4. */
uint32_t vertrix_port_choice_grid_available_42a190(PORT_SIGNATURE)
{
    Port port;
    uint32_t edx = entry->edx << 4;
    uint32_t item;
    port_open(&port, calls, services, globals, entry);
    item = port_u32(&port, entry->eax + edx, entry->ebx * 4 + 0x15c);
    if (item == 0 || port_u8(&port, item, 0x15c) != 0)
    {
        return port_return(&port, 0, edx);
    }
    return port_return(&port, 1, edx);
}

/* Original 0x475ab0 (ret 4): 0x475790 of eax + 4 with dl sign extended and the stack argument
 * passed on (also in esi); edx as 0x475790 leaves it. */
uint32_t vertrix_port_list_push_call_475ab0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t argument;
    uint32_t result;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    argument = port_u32(&port, ebp, 8);
    result = call_frame(&port, 0x475790, entry->eax + 4, (uint32_t)(int32_t)(int8_t)entry->edx,
                        entry->ebx, entry->ecx, argument, entry->edi, ebp, &argument, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4cd9f0: 0x4e0f8b of eax (ecx eax) stored in a frame record whose address goes to
 * 0x4cd8b0 with eax, and the edx 0x4e0f8b left in ebx. */
uint32_t vertrix_port_rtl_local_call_4cd9f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t value;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x10, entry->ebx);
    port_set32(&port, esp, 0xc, entry->ecx);
    value = port_forward(&port, entry, 0x4e0f8b, entry->eax, entry->edx, entry->ebx, entry->eax);
    port_set32(&port, esp, 0, value);
    result = port_forward(&port, entry, 0x4cd8b0, entry->eax, esp, vertrix_lift_edx, entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4d9510: 0x4da71b of a frame dword holding 0x5c761c, with 0x51a560. */
uint32_t vertrix_port_rtl_static_init_call_4d9510(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0, 0x5c761c);
    result = port_forward(&port, entry, 0x4da71b, esp, 0x51a560, entry->ebx, entry->ecx);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4df140: the entry 0x4df0f0 finds for eax and edx (ebx a frame dword, ecx the
 * caller's ebx); its +0xc stored at ebx and 1, else 0. */
uint32_t vertrix_port_rtl_table_lookup_value_4df140(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t found;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 4, entry->ecx);
    found = port_forward(&port, entry, 0x4df0f0, entry->eax, entry->edx, esp, entry->ebx);
    if (found == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, entry->ebx, 0, port_u32(&port, found, 0xc));
    return port_return(&port, 1, vertrix_lift_edx);
}
