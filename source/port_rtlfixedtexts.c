#include "port_rtlfixedtexts.h"

/* The runtime's text for a 16.16 fixed-point number. */

enum
{
    SPEC_PRECISION = 8,
    DEFAULT_PRECISION = 4,
    UNSIGNED_TO_TEXT = 0x4e636c
};

static uint32_t text_end(Port *port, uint32_t text)
{
    while (port_u8(port, text, 0) != 0 && !port->env.failed)
    {
        text++;
    }
    return text;
}

static uint32_t skip_zeros(Port *port, uint32_t text)
{
    while (port_u8(port, text, 0) == '0' && !port->env.failed)
    {
        text++;
    }
    return text;
}

/* Rounds the digits before `end` up by one, from the last: nines become zeros and carry, the
 * point is stepped over. When every digit was a nine the text becomes 1 followed by zeros, one
 * more before the point. */
static void round_up(Port *port, uint32_t start, uint32_t end)
{
    uint32_t at = end;
    while (at != start && !port->env.failed)
    {
        at--;
        if (port_u8(port, at, 0) == '.')
        {
            at--;
        }
        const uint32_t digit = port_u8(port, at, 0);
        if (digit != '9')
        {
            port_set8(port, at, 0, digit + 1);
            return;
        }
        port_set8(port, at, 0, '0');
    }
    port_set8(port, start, 0, '1');
    at = skip_zeros(port, start + 1);
    if (port_u8(port, at, 0) == '.')
    {
        port_set8(port, at, 0, '0');
        at++;
        port_set8(port, at, 0, '.');
        at = skip_zeros(port, at + 1);
    }
    port_set8(port, at, 0, '0');
    port_set8(port, at, 1, 0);
}

/* Original 0x4df978 (eax = the text, edx = the value, ebx = the field): a minus sign, the integer
 * part (0x4e636c, base 10), then a point and the field's precision in fraction digits (4 when it
 * is -1, which is stored back), rounded half up. A precision of 0 leaves out the point and adds
 * no terminator of its own. */
uint32_t vertrix_port_rtl_format_fixed_point_4df978(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t spec = entry->ebx;
    uint32_t text = entry->eax;
    uint32_t value = entry->edx;
    if ((int32_t)value < 0)
    {
        value = 0u - value;
        port_set8(&port, text, 0, '-');
        text++;
    }
    if (port_u32(&port, spec, SPEC_PRECISION) == 0xffffffffu)
    {
        port_set32(&port, spec, SPEC_PRECISION, DEFAULT_PRECISION);
    }
    port_call(&port, UNSIGNED_TO_TEXT, value >> 16, text, 10, 0);
    uint32_t end = text_end(&port, text);
    if (port_u32(&port, spec, SPEC_PRECISION) != 0)
    {
        port_set8(&port, end, 0, '.');
        end++;
        for (int32_t digits = 0;
             digits < (int32_t)port_u32(&port, spec, SPEC_PRECISION) && !port.env.failed; digits++)
        {
            value = (value & 0xffff) * 10;
            port_set8(&port, end, 0, '0' + ((value >> 16) & 0xff));
            end++;
        }
        port_set8(&port, end, 0, 0);
    }
    if ((value & 0x8000) != 0)
    {
        round_up(&port, text, end);
    }
    return port_return(&port, 0, 0);
}
