#include "port_rtlformats.h"

/* The runtime library's number formatting. */

/* `rep movsd` then `rep movsb`: `count` bytes from `from` to `to`, forwards. */
static void copy_forward(Port *port, uint32_t to, uint32_t from, uint32_t count)
{
    uint32_t at;
    for (at = 0; at + 4 <= count && !port->env.failed; at += 4)
    {
        port_set32(port, to, at, port_u32(port, from, at));
    }
    for (; at < count && !port->env.failed; at++)
    {
        port_set8(port, to, at, port_u8(port, from, at));
    }
}

/* Original 0x4ed096 (ret 4): the ebx digits edx with the decimal exponent ecx laid out in fixed
 * point into the buffer (stack argument) for the format eax (precision +0; flags +8: 4 significant
 * digits, 8 no point or leading zero, 0x10 the point kept). The leading zeros (+0x18 and +0x20,
 * after the digits +0x1c), the digits after the point (+0x24) and the trailing zeros (+0x28)
 * are noted and the text ended. eax the last copy's length, edx the end. */
uint32_t vertrix_port_rtl_fixed_format_4ed096(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t spec = entry->eax;
    uint32_t digits = entry->edx;
    uint32_t count = entry->ebx;
    uint32_t buffer;
    uint32_t precision;
    uint32_t point;
    uint32_t edx = 0;
    uint32_t flags;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, entry->esp, -4, entry->ebp);
    port_set32(&port, entry->esp, -8, entry->esi);
    port_set32(&port, entry->esp, -0xc, entry->edi);
    port_set32(&port, entry->esp, -0x14, entry->eax);
    port_set32(&port, entry->esp, -0x18, entry->edx);
    port_set32(&port, entry->esp, -0x1c, entry->ecx);
    buffer = port_u32(&port, entry->esp, 4);
    precision = port_u32(&port, spec, 0);
    point = entry->ecx + 1;
    if ((port_u8(&port, spec, 8) & 4) != 0)
    {
        if ((int32_t)count < (int32_t)precision && (port_u8(&port, spec, 8) & 0x10) == 0)
        {
            precision = count;
        }
        precision -= point;
        if ((int32_t)precision < 0)
        {
            precision = 0;
        }
    }
    if ((int32_t)point <= 0)
    {
        if ((port_u8(&port, spec, 8) & 8) == 0)
        {
            port_set8(&port, buffer, 0, 0x30);
            edx = 1;
            if ((int32_t)precision > 0 || (port_u8(&port, spec, 8) & 0x10) != 0)
            {
                port_set8(&port, buffer, 1, 0x2e);
                edx = 2;
            }
        }
        port_set32(&port, spec, 0x1c, edx);
        if ((int32_t)-point > (int32_t)precision)
        {
            point = -precision;
        }
        port_set32(&port, spec, 0x18, point);
        port_set32(&port, spec, 0x20, -point);
        precision += point;
        if ((int32_t)count > (int32_t)precision)
        {
            count = precision;
        }
        copy_forward(&port, buffer + edx, digits, count);
        port_set32(&port, spec, 0x24, count);
        edx += count;
        port_set32(&port, spec, 0x28, precision - count);
    }
    else if ((int32_t)count < (int32_t)point)
    {
        copy_forward(&port, buffer, digits, count);
        port_set32(&port, spec, 0x1c, count);
        edx = count;
        port_set32(&port, spec, 0x20, point - count);
        flags = port_u8(&port, spec, 8);
        port_set32(&port, spec, 0x18, point);
        if ((flags & 8) == 0 && ((int32_t)precision > 0 || (flags & 0x10) != 0))
        {
            port_set8(&port, buffer, edx, 0x2e);
            edx++;
            port_set32(&port, spec, 0x24, 1);
        }
        port_set32(&port, spec, 0x28, precision);
    }
    else
    {
        copy_forward(&port, buffer, digits, point);
        flags = port_u8(&port, spec, 8);
        edx = point;
        count -= point;
        port_set32(&port, spec, 0x18, point);
        if ((flags & 8) != 0)
        {
            if (port_u8(&port, buffer, 0) == 0x30)
            {
                port_set32(&port, spec, 0x18, 0);
            }
        }
        else if ((int32_t)precision > 0 || (flags & 0x10) != 0)
        {
            port_set8(&port, buffer, edx, 0x2e);
            edx++;
        }
        if ((int32_t)count > (int32_t)precision)
        {
            count = precision;
        }
        copy_forward(&port, buffer + edx, digits + point, count);
        edx += count;
        port_set32(&port, spec, 0x1c, edx);
        port_set32(&port, spec, 0x20, precision - count);
    }
    edx += buffer;
    port_set8(&port, edx, 0, 0);
    return port_return(&port, count, edx);
}
