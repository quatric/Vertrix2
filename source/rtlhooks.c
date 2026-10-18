#include "rtlhooks.h"

/* Message hooks, decimal text to packed numbers and surface blits. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4cfc90 (ret 0x10): the message hook: with this thread's hook record (0x4dc030 of
 * 0x5c5c28, made by 0x4ccc40) holding a window (+4), the colour messages 0x134..0x138 go to
 * 0x4d2540 (as 2..6, with the third and fourth arguments and the record's +4 and +8), which may
 * answer the window; anything else goes on to 0x4cfa20 with the four arguments. */
uint32_t vertrix_port_rtl_message_hook_4cfc90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 16];
    uint32_t message;
    uint32_t record;
    uint32_t eax;
    uint32_t args[5];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 4);
    port_set32(&port, entry->esp - 4, 0, entry->ebx);
    port_set32(&port, entry->esp - 8, 0, entry->esi);
    message = port_u32(&port, entry->esp, 8);
    record = port_call_with(&port, 0x4dc030, 0x5c5c28, 0x4ccc40, entry->ebx, entry->ecx, message,
                            entry->edi, entry->ebp);
    eax = record;
    if (port_u32(&port, record, 4) != 0 && message >= 0x134 && message <= 0x138)
    {
        args[0] = port_u32(&port, entry->esp, 0xc);
        args[1] = port_u32(&port, entry->esp, 0x10);
        args[2] = message - 0x132;
        args[3] = port_u32(&port, record, 4);
        args[4] = port_u32(&port, record, 8);
        eax = call_frame(&port, 0x4d2540, message - 0x132, vertrix_lift_edx, record, entry->ecx,
                         message, entry->edi, entry->ebp, args, 5);
        if (eax != 0)
        {
            return port_return(&port, port_u32(&port, record, 4), vertrix_lift_edx);
        }
    }
    args[0] = port_u32(&port, entry->esp, 4);
    args[1] = message;
    args[2] = port_u32(&port, entry->esp, 0xc);
    args[3] = port_u32(&port, entry->esp, 0x10);
    eax = call_frame(&port, 0x4cfa20, eax, vertrix_lift_edx, record, entry->ecx, message,
                     entry->edi, entry->ebp, args, 4);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* 96-bit `high:middle:low` plus `add_high:add_middle:add_low`. */
static void add96(uint32_t *high, uint32_t *middle, uint32_t *low, uint32_t add_high,
                  uint32_t add_middle, uint32_t add_low)
{
    uint32_t sum = *low + add_low;
    uint32_t carry = sum < add_low;
    uint32_t mid = *middle + add_middle;
    uint32_t carry2 = mid < add_middle;
    *low = sum;
    *middle = mid + carry;
    carry2 |= *middle < carry;
    *high = *high + add_high + carry2;
}

/* Original 0x4ee370: the decimal digits at eax (to their end) as a 96-bit number, packed by
 * 0x4ee3d2 (exponent 0x405e) into the extended value at edx, its last word the text's end. */
uint32_t vertrix_port_rtl_decimal_pack_4ee370(PORT_SIGNATURE)
{
    Port port;
    uint32_t text = entry->eax;
    uint32_t target = entry->edx;
    uint32_t high = 0;
    uint32_t middle = 0;
    uint32_t low = 0;
    uint32_t ebx = entry->ebx;
    uint32_t eax;
    uint32_t c;
    port_open(&port, calls, services, globals, entry);
    while ((c = port_u8(&port, text, 0)) != 0 && !port.env.failed)
    {
        uint32_t old_high = high;
        uint32_t old_middle = middle;
        uint32_t old_low = low;
        ebx = middle;
        add96(&high, &middle, &low, high, middle, low);
        add96(&high, &middle, &low, high, middle, low);
        add96(&high, &middle, &low, old_high, old_middle, old_low);
        add96(&high, &middle, &low, high, middle, low);
        add96(&high, &middle, &low, 0, 0, c & 0xf);
        text++;
    }
    eax = port_call_with(&port, 0x4ee3d2, middle, high, ebx, middle, text, 0x405e, low);
    port_set32(&port, target, 4, vertrix_lift_edx);
    port_set32(&port, target, 0, eax);
    port_set16(&port, target, 8, text);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x47fa90: the surface eax (+0, unless locked at +0x30) blitted through its method +0x1c
 * (the frame pair of ecx and edx, flags 0x28 with an out word); 1 when that answers 0x15800e,
 * else 0 after 0x480080 reports it. */
uint32_t vertrix_port_surface_blit_47fa90(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t self = entry->eax;
    uint32_t surface;
    uint32_t methods;
    uint32_t eax;
    uint32_t args[8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->esi);
    surface = port_u32(&port, self, 0);
    if (surface == 0 || port_u32(&port, self, 0x30) != 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_set32(&port, ebp, -0xc, entry->edx);
    port_set32(&port, ebp, -0x10, entry->ecx);
    methods = port_u32(&port, surface, 0);
    args[0] = surface;
    args[1] = entry->ebx;
    args[2] = ebp - 0x10;
    args[3] = 1;
    args[4] = 0;
    args[5] = 0;
    args[6] = ebp - 8;
    args[7] = 0x28;
    eax = call_frame(&port, port_u32(&port, methods, 0x1c), surface, ebp - 0x10, entry->ebx,
                     methods, self, entry->edi, ebp, args, 8);
    if (eax == 0x15800e)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
    port_call_with(&port, 0x480080, self, eax, entry->ebx, methods, self, entry->edi, ebp);
    return port_return(&port, 0, vertrix_lift_edx);
}
