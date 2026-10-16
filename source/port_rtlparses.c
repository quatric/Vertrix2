#include "port_rtlparses.h"

/* The runtime library's number parsing. */

/* Whether `c` is a decimal digit. */
static int is_digit(uint32_t c)
{
    return c >= 0x30 && c <= 0x39;
}

/* Original 0x4ed60b: the decimal text eax (blanks, sign, digits with a point, an exponent) read
 * into the extended real edx, its end kept in [ebx] when ebx is set. Up to 19 significant digits
 * (in the frame, trailing zeros dropped) become the mantissa by 0x4ee370 and are scaled by the
 * exponent with 0x4ecc60. eax 0 for no digits (zero), else 3 past the overflow exponent (308), 2
 * below it, 1 otherwise. */
uint32_t vertrix_port_rtl_text_to_extended_4ed60b(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x44
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t out = entry->edx;
    uint32_t end = entry->ebx;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    uint32_t ebx;
    uint32_t esi = 0;
    uint32_t fraction = 0;
    uint32_t mark = 0;
    uint32_t next;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ecx);
    port_set32(&port, ebp, -8, entry->esi);
    port_set32(&port, ebp, -0xc, entry->edi);
    port_set32(&port, ebp, -0x18, end);
    port_set32(&port, ebp, -0x20, eax);
    for (;;)
    {
        edx = (edx & 0xffffff00u) | port_u8(&port, eax, 0);
        if ((edx & 0xff) != 0x20 && ((edx & 0xff) < 9 || (edx & 0xff) > 0xd))
        {
            break;
        }
        eax++;
    }
    next = eax + 1;
    ecx &= 0xffffff00u;
    if ((edx & 0xff) == 0x2b)
    {
        eax = next;
    }
    else if ((edx & 0xff) == 0x2d)
    {
        ecx |= 1;
        eax = next;
    }
    ebx = 0;
    edx = (edx & 0xffff00ffu) | 0x3000;
    for (;;)
    {
        uint32_t c = port_u8(&port, eax, 0);
        edx = (edx & 0xffffff00u) | c;
        eax++;
        if (c == 0x2e)
        {
            if ((ecx & 8) != 0)
            {
                break;
            }
            ecx |= 8;
            continue;
        }
        if (!is_digit(c) || port.env.failed)
        {
            break;
        }
        if ((ecx & 8) != 0)
        {
            fraction++;
        }
        edx |= c << 8;
        if (((edx >> 8) & 0xff) != 0x30)
        {
            if ((int32_t)ebx < 0x13)
            {
                port_set8(&port, ebp, ebx - 0x40, c);
            }
            ebx++;
        }
        ecx |= 4;
    }
    if ((ecx & 4) != 0)
    {
        if ((edx & 0xff) == 0x65 || (edx & 0xff) == 0x45)
        {
            uint32_t sign = port_u8(&port, eax, 0);
            mark = eax - 1;
            ecx = (ecx & 0xffff00ffu) | (sign << 8);
            edx = eax + 1;
            if (sign == 0x2b)
            {
                eax = edx;
            }
            else if (sign == 0x2d)
            {
                ecx |= 2;
                eax = edx;
            }
            ecx &= 0xfffffffbu;
            for (;;)
            {
                uint32_t c = port_u8(&port, eax, 0);
                edx = (edx & 0xffffff00u) | c;
                if (!is_digit(c) || port.env.failed)
                {
                    break;
                }
                if ((int32_t)esi < 0x3e8)
                {
                    esi = esi * 10 + c - 0x30;
                }
                ecx |= 4;
                eax++;
            }
            if ((ecx & 2) != 0)
            {
                esi = -esi;
            }
            if ((ecx & 4) == 0)
            {
                eax = mark;
            }
        }
        else
        {
            eax--;
        }
        port_set32(&port, ebp, -0x20, eax);
    }
    if (end != 0)
    {
        edx = end;
        port_set32(&port, end, 0, port_u32(&port, ebp, -0x20));
    }
    esi -= fraction;
    if ((int32_t)ebx > 0x13)
    {
        esi += ebx - 0x13;
        ebx = 0x13;
    }
    while ((int32_t)ebx > 0 && port_u8(&port, ebp, ebx - 0x41) == 0x30 && !port.env.failed)
    {
        esi++;
        ebx--;
    }
    if (ebx == 0)
    {
        port_set16(&port, out, 8, 0);
        port_set32(&port, out, 4, 0);
        port_set32(&port, out, 0, 0);
        return port_return(&port, 0, edx);
    }
    port_set8(&port, ebp, ebx - 0x40, 0);
    port_call_with(&port, 0x4ee370, ebp - 0x40, ebp - 0x2c, ebx, ecx, esi, out, ebp);
    if (esi != 0)
    {
        port_call_with(&port, 0x4ecc60, ebp - 0x2c, esi, ebx, ecx, esi, out, ebp);
    }
    if ((ecx & 1) != 0)
    {
        port_set8(&port, ebp, -0x23, port_u8(&port, ebp, -0x23) | 0x80);
    }
    port_set16(&port, out, 8, port_u16(&port, ebp, -0x24));
    port_set32(&port, out, 4, port_u32(&port, ebp, -0x28));
    port_set32(&port, out, 0, port_u32(&port, ebp, -0x2c));
    eax = esi + ebx - 1;
    if ((int32_t)eax > 0x134)
    {
        eax = 3;
    }
    else if ((int32_t)eax < -0x134)
    {
        eax = 2;
    }
    else
    {
        eax = 1;
    }
    return port_return(&port, eax, vertrix_lift_edx);
}
