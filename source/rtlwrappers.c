#include "rtlwrappers.h"

/* The runtime library's thin wrappers. */

static uint32_t call_frame(Port *port, const LiftEntry *entry, uint32_t target, uint32_t eax,
                           uint32_t edx, uint32_t ebx, uint32_t ecx, const uint32_t *stack,
                           unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, entry->esi, entry->edi, entry->ebp,
                               stack, count);
}

/* Original 0x441120: a forward to 0x4ea190. */
uint32_t vertrix_port_rtl_forward_free_441120(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x4ea190, entry->eax, entry->edx, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* 0x4da71b with the frame slot holding `slot` (eax) for the table `table` (edx and the stack
 * argument). */
static uint32_t table_register(PORT_SIGNATURE, uint32_t table, uint32_t slot)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 4;
    uint32_t args[1];
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0, slot);
    args[0] = slot;
    eax = call_frame(&port, entry, 0x4da71b, esp, table, entry->ebx, entry->ecx, args, 1);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4d9530: table_register of 0x51a5a0 with 0x5c76b8. */
uint32_t vertrix_port_rtl_table_register_4d9530(PORT_SIGNATURE)
{
    return table_register(calls, services, globals, entry, 0x51a5a0, 0x5c76b8);
}

/* Original 0x4dde50: table_register of 0x51b7d0 with 0x5c7804. */
uint32_t vertrix_port_rtl_table_register_4dde50(PORT_SIGNATURE)
{
    return table_register(calls, services, globals, entry, 0x51b7d0, 0x5c7804);
}

/* Originals 0x4e2371 and 0x4e237d: error 0x83 (0x4e7280) and a signed infinity, edx:eax (the
 * sign from the error's eax). */
uint32_t vertrix_port_rtl_infinity_error_4e2371(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x4e7280, 0x83, entry->edx, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, entry->ebp);
    return port_return(&port, 0, (eax & 0x80000000u) | 0x7ff00000u);
}

uint32_t vertrix_port_rtl_infinity_error_4e237d(PORT_SIGNATURE)
{
    return vertrix_port_rtl_infinity_error_4e2371(calls, services, globals, entry);
}

/* Original 0x4d4300: the object eax's +0x8c plus 0x20000, or 0 without one. */
uint32_t vertrix_port_rtl_offset_handle_4d4300(PORT_SIGNATURE)
{
    Port port;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    value = port_u32(&port, entry->eax, 0x8c);
    return port_return(&port, value != 0 ? value + 0x20000 : 0, entry->edx);
}

/* Original 0x4e08a0: the stack left, esp less the limit at 0x507c9c's [eax]; edx kept. */
uint32_t vertrix_port_rtl_stack_left_4e08a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 4;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0, entry->edx);
    eax = port_call_with(&port, port_u32(&port, 0, 0x507c9c), entry->eax, entry->edx, entry->ebx,
                         entry->ecx, entry->esi, entry->edi, entry->ebp);
    eax = esp - port_u32(&port, eax, 0);
    return port_return(&port, eax, port_u32(&port, esp, 0));
}

/* Original 0x4ccc40: an object of 0x10 bytes (0x4dba80) given the class 0x518a84. */
uint32_t vertrix_port_rtl_object_new_4ccc40(PORT_SIGNATURE)
{
    Port port;
    uint32_t args[1] = {0x10};
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    eax =
        call_frame(&port, entry, 0x4dba80, entry->eax, entry->edx, entry->ebx, entry->ecx, args, 1);
    if (eax != 0)
    {
        port_set32(&port, eax, 0, 0x518a84);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4cf4a0 (ret 0xc): 0x4f19f8 of the handle +0x1c of the first argument with the second,
 * then 0x4cccc0 of the first and third, its eax stored at its edx. */
uint32_t vertrix_port_rtl_handle_query_4cf4a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0
    };
    Port port;
    uint8_t stack[BELOW + 8 + 12];
    uint32_t first;
    uint32_t args[2];
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    first = port_u32(&port, entry->esp, 4);
    args[0] = port_u32(&port, first, 0x1c);
    args[1] = port_u32(&port, entry->esp, 8);
    call_frame(&port, entry, 0x4f19f8, first, entry->edx, entry->ebx, entry->ecx, args, 2);
    eax = port_call_with(&port, 0x4cccc0, first, port_u32(&port, entry->esp, 0xc), entry->ebx,
                         entry->ecx, entry->esi, entry->edi, entry->ebp);
    port_set32(&port, vertrix_lift_edx, 0, eax);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4e105a: 2 when multibyte text is on (0x5c8950) and the byte at eax leads a pair
 * (bit 0 of 0x5c8961's entry), else 1; edx kept. */
uint32_t vertrix_port_rtl_lead_byte_4e105a(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = 1;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x5c8950) != 0 &&
        (port_u8(&port, port_u8(&port, entry->eax, 0), 0x5c8961) & 1) != 0)
    {
        eax = 2;
    }
    return port_return(&port, eax, entry->edx);
}
