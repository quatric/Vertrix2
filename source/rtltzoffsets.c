#include "rtltzoffsets.h"

enum
{
    LONGEST_NAME = 0x80
};

static int is_digit(uint32_t byte)
{
    return byte >= '0' && byte <= '9';
}

/* 0x4e9670's decimal number (wrapping), with `*text` moved past it. */
static uint32_t decimal(Port *port, uint32_t *text)
{
    uint32_t value = 0;
    for (uint32_t byte = port_u8(port, *text, 0); is_digit(byte) && !port->env.failed;
         byte = port_u8(port, *text, 0))
    {
        value = value * 10 + byte - '0';
        *text += 1;
    }
    return value;
}

/* Original 0x4e969c (eax = the text, edx = the name, ebx = where the offset goes): a zone in the TZ
 * variable, after a ':' at the start. Its name runs to the end, a ',', a sign or a digit and is
 * copied (at most 0x80 characters) and ended. A sign may follow, then, when a digit does, hours
 * with ':' minutes and ':' seconds (0x4e9670 each), stored as seconds, negated for '-'. Returns
 * the text after what was read. */
uint32_t vertrix_port_rtl_tz_offset_4e969c(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t name = entry->edx;
    const uint32_t offset = entry->ebx;
    uint32_t text = entry->eax;
    if (port_u8(&port, text, 0) == ':')
    {
        text++;
    }
    const uint32_t start = text;
    uint32_t stop = port_u8(&port, text, 0);
    while (stop != 0 && stop != ',' && stop != '-' && stop != '+' && !is_digit(stop) &&
           !port.env.failed)
    {
        stop = port_u8(&port, ++text, 0);
    }
    int32_t length = (int32_t)(text - start);
    if (length > LONGEST_NAME)
    {
        length = LONGEST_NAME;
    }
    port_copy(&port, name, start, (uint32_t)length);
    port_set8(&port, name, (uint32_t)length, 0);
    const int negative = stop == '-';
    if (stop == '-' || stop == '+')
    {
        text++;
    }
    if (is_digit(port_u8(&port, text, 0)))
    {
        const uint32_t hours = decimal(&port, &text);
        uint32_t minutes = 0;
        uint32_t seconds = 0;
        if (port_u8(&port, text, 0) == ':')
        {
            text++;
            minutes = decimal(&port, &text);
            if (port_u8(&port, text, 0) == ':')
            {
                text++;
                seconds = decimal(&port, &text);
            }
        }
        const uint32_t value = (hours * 60 + minutes) * 60 + seconds;
        port_set32(&port, offset, 0, negative ? 0u - value : value);
    }
    return port_return(&port, text, vertrix_lift_edx);
}
