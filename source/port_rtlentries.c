#include "port_rtlentries.h"

/* Path part copies and handle slot entries. */

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

/* Original 0x4db980 (ret 0x10): the part of the path (second argument) after as many separators
 * (fourth argument, by 0x4db9fc) as the third says, up to the next, copied into the text (first
 * argument: 0x4ca6f0 and 0x4eb5e0), its length by 0x4f1d24 when it runs to the end. eax 1, or 0
 * (the text cleared by 0x4ca180) when there are too few. */
uint32_t vertrix_port_rtl_path_part_4db980(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 16];
    uint32_t text;
    uint32_t place;
    uint32_t count;
    uint32_t ecx;
    uint32_t separator;
    uint32_t eax;
    uint32_t length;
    uint32_t args[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    port_set32(&port, entry->esp - 4, 0, entry->ebx);
    port_set32(&port, entry->esp - 8, 0, entry->esi);
    text = port_u32(&port, entry->esp, 4);
    place = port_u32(&port, entry->esp, 8);
    count = port_u32(&port, entry->esp, 0xc);
    ecx = (entry->ecx & 0xffffff00u) | port_u8(&port, entry->esp, 0x10);
    separator = (uint32_t)(int32_t)(int8_t)(ecx & 0xff);
    if (place == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (;;)
    {
        count--;
        if (count == 0xffffffffu || port.env.failed)
        {
            break;
        }
        eax = port_call_with(&port, 0x4db9fc, place, separator, count, ecx, place, entry->edi,
                             entry->ebp);
        if (eax == 0)
        {
            port_call_with(&port, 0x4ca180, text, vertrix_lift_edx, count, ecx, place, entry->edi,
                           entry->ebp);
            return port_return(&port, 0, vertrix_lift_edx);
        }
        place = eax + 1;
    }
    eax = port_call_with(&port, 0x4db9fc, place, separator, count, ecx, place, entry->edi,
                         entry->ebp);
    if (eax == 0)
    {
        args[0] = place;
        length = call_frame(&port, 0x4f1d24, 0, vertrix_lift_edx, count, ecx, place, entry->edi,
                            entry->ebp, args, 1);
    }
    else
    {
        length = eax - place;
    }
    eax = port_call_with(&port, 0x4ca6f0, text, length, length, ecx, place, entry->edi, entry->ebp);
    port_call_with(&port, 0x4eb5e0, eax, place, length, ecx, place, entry->edi, entry->ebp);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* The handle eax put in the first free runtime handle slot (0x507c8c, 0x507c90 of them, grown by
 * 0x4ec0e0 when full) under the hooks 0x507cd0 and 0x507cd4; the slot number. */
static uint32_t handle_slot_add(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t count;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    uint32_t table;
    uint32_t index = 0;
    port_open(&port, calls, services, globals, entry);
    port_forward_esi(&port, entry, port_u32(&port, 0, 0x507cd0), value, entry->edx, entry->ebx,
                     entry->ecx, value);
    count = port_u32(&port, 0, 0x507c90);
    ebx = count;
    if ((int32_t)count > 0)
    {
        uint32_t offset;
        ecx = count * 4;
        for (offset = 0; (int32_t)offset < (int32_t)ecx; offset += 4, index++)
        {
            ebx = port_u32(&port, 0, 0x507c8c) + offset;
            if (port_u32(&port, ebx, 0) == 0)
            {
                port_set32(&port, ebx, 0, value);
                port_forward_esi(&port, entry, port_u32(&port, 0, 0x507cd4), offset, index, ebx,
                                 ecx, value);
                return port_return(&port, vertrix_lift_edx, entry->edx);
            }
        }
    }
    count = port_u32(&port, 0, 0x507c90);
    table = port_forward_esi(&port, entry, 0x4ec0e0, port_u32(&port, 0, 0x507c8c), (count + 1) * 4,
                             ebx, ecx, value);
    count = port_u32(&port, 0, 0x507c90);
    port_set32(&port, 0, 0x507c8c, table);
    port_set32(&port, table + count * 4, 0, value);
    port_set32(&port, 0, 0x507c90, count + 1);
    port_forward_esi(&port, entry, port_u32(&port, 0, 0x507cd4), table, count, ebx, count + 1,
                     value);
    return port_return(&port, port_u32(&port, 0, 0x507c90) - 1, entry->edx);
}

/* Original 0x4e5748: the handle eax added to the runtime's handle slots; the original continues
 * into 0x4e02a4. */
uint32_t vertrix_port_rtl_handle_slot_add_4e5748(PORT_SIGNATURE)
{
    return handle_slot_add(calls, services, globals, entry);
}
