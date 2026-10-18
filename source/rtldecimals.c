#include "rtldecimals.h"

/* Decimal text of a number. */

/* Original 0x4776a0: the number eax written to edx as decimal text of at most bl digits (one fewer
 * when negative, the minus sign after), built backwards in the frame from the lowest digit (a
 * lone 0 when there are none) and copied out reversed with its end 0. eax the length; edx the
 * last place copied. */
uint32_t vertrix_port_format_decimal_4776a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t base = entry->esp - 0x20;
    uint32_t out = entry->edx;
    uint32_t edx = entry->edx;
    uint32_t value = entry->eax;
    uint32_t limit = entry->ebx & 0xff;
    uint32_t count = 0;
    uint32_t index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ecx);
    port_set32(&port, entry->esp, -8u, entry->esi);
    port_set8(&port, base, 0x14, 0);
    if ((int32_t)value < 0)
    {
        edx = (edx & 0xffffff00u) | 1;
        value = 0u - value;
        port_set8(&port, base, 0x14, 1);
        limit = (limit - 1) & 0xff;
    }
    port_set32(&port, base, -4u, entry->edi);
    if (value != 0)
    {
        do
        {
            int32_t quotient;
            uint32_t digit;
            if (count >= limit)
            {
                break;
            }
            quotient = (int32_t)value / 10;
            digit = value - (uint32_t)quotient * 10;
            edx = (digit & 0xffffff00u) | ((digit + 0x30) & 0xff);
            port_set8(&port, base, count, digit + 0x30);
            count = (count + 1) & 0xff;
            value = (uint32_t)quotient;
        } while (value != 0);
    }
    if (count == 0 && value == 0)
    {
        port_set8(&port, base, 0, 0x30);
        count = 1;
        edx = (edx & 0xffff00ffu) | 0x3000;
    }
    if (port_u8(&port, base, 0x14) == 1)
    {
        port_set8(&port, base, count, 0x2d);
        count = (count + 1) & 0xff;
    }
    port_set8(&port, base, count, 0);
    for (index = 0; count != 0; index++)
    {
        edx = index;
        port_set8(&port, out, index, port_u8(&port, base, count - 1));
        count--;
    }
    port_set8(&port, out, index, 0);
    return port_return(&port, index, edx);
}
