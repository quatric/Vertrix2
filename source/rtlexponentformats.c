#include "rtlexponentformats.h"

enum
{
    /* The format's fields: precision (+0), decimal point (+4), flags (+8: 4 the precision counts
     * significant digits, 8 no point, 0x10 a point always), the exponent letter (+0xc, 0 for
     * none), the exponent's digits (+0x10), and the lengths it fills in: the integer part's
     * (+0x18), the fraction's end (+0x1c), its trailing zeros (+0x20) and the exponent's (+0x24).
     */
    FORMAT_PRECISION = 0x0,
    FORMAT_POINT = 0x4,
    FORMAT_FLAGS = 0x8,
    FORMAT_LETTER = 0xc,
    FORMAT_EXPONENT_DIGITS = 0x10,
    FORMAT_INTEGER_END = 0x18,
    FORMAT_FRACTION_END = 0x1c,
    FORMAT_ZEROS = 0x20,
    FORMAT_EXPONENT_LENGTH = 0x24,

    FLAG_SIGNIFICANT = 4,
    FLAG_NO_POINT = 8,
    FLAG_POINT = 0x10,

    /* The stack argument: the output buffer. */
    ARGUMENT_BUFFER = 4,

    FILL = 0x4eb5c0,
    ZERO = '0'
};

/* 0x4eb5c0: `count` zeros at `to` (eax, edx the byte, ebx the count; ecx is passed through). */
static void zeros(Port *port, uint32_t to, uint32_t count, uint32_t ecx)
{
    port_call(port, FILL, to, ZERO, count, ecx);
}

/* One exponent digit: the quotient of `exponent` by `unit` (0 when it is less), the exponent left
 * the remainder. */
static void digit(Port *port, uint32_t buffer, uint32_t *at, int32_t *exponent, int32_t unit)
{
    int32_t quotient = 0;
    if (*exponent >= unit)
    {
        quotient = *exponent / unit;
        *exponent -= quotient * unit;
    }
    port_set8(port, buffer, *at, (uint32_t)quotient + ZERO);
    *at += 1;
}

/* Original 0x4ed2b5 (eax the format, edx the digits, ebx their count, ecx the exponent; stdcall:
 * the buffer): writes a number in exponent form, the digits before the point (or "0"), zeros up
 * to it, the point, the fraction's digits up to the precision, the exponent letter, its sign and
 * at least the format's count of its digits (raised as it needs, up to 4), and a terminating 0.
 * Returns the terminator's address in eax and the exponent's length in edx. */
uint32_t vertrix_port_rtl_exponent_format_4ed2b5(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t format = entry->eax;
    uint32_t source = entry->edx;
    int32_t count = (int32_t)entry->ebx;
    int32_t exponent = (int32_t)entry->ecx;
    const uint32_t buffer = port_u32(&port, entry->esp, ARGUMENT_BUFFER);

    int32_t precision = (int32_t)port_u32(&port, format, FORMAT_PRECISION);
    const int32_t point = (int32_t)port_u32(&port, format, FORMAT_POINT);
    if (point > 0)
    {
        precision = precision - point + 1;
    }
    else
    {
        precision += point;
    }
    uint32_t at = 0;
    if (port_u8(&port, format, FORMAT_FLAGS) & FLAG_SIGNIFICANT)
    {
        if (count < precision)
        {
            precision = count;
        }
        precision--;
        if (precision < 0)
        {
            precision = 0;
        }
    }

    const int32_t integer = (int32_t)port_u32(&port, format, FORMAT_POINT);
    if (integer <= 0)
    {
        port_set8(&port, buffer, at, ZERO);
        at++;
    }
    else
    {
        int32_t copied = integer;
        if (copied > count)
        {
            copied = count;
        }
        port_copy(&port, buffer + at, source, (uint32_t)copied);
        at += (uint32_t)copied;
        source += (uint32_t)copied;
        count -= copied;
        const int32_t wanted = (int32_t)port_u32(&port, format, FORMAT_POINT);
        if (copied < wanted)
        {
            const uint32_t fill = (uint32_t)(wanted - copied);
            zeros(&port, buffer + at, fill, (uint32_t)copied);
            at += fill;
        }
    }
    port_set32(&port, format, FORMAT_INTEGER_END, at);

    const uint32_t flags = port_u8(&port, format, FORMAT_FLAGS);
    if (!(flags & FLAG_NO_POINT) &&
        (precision > 0 || (port_u8(&port, format, FORMAT_FLAGS) & FLAG_POINT)))
    {
        port_set8(&port, buffer, at, '.');
        at++;
    }
    const int32_t leading = (int32_t)port_u32(&port, format, FORMAT_POINT);
    if (leading < 0)
    {
        const uint32_t fill = (uint32_t)-leading;
        zeros(&port, buffer + at, fill, at);
        at += fill;
    }
    if (precision > 0)
    {
        if (precision < count)
        {
            count = precision;
        }
        if (count != 0)
        {
            port_copy(&port, buffer + at, source, (uint32_t)count);
            at += (uint32_t)count;
        }
        port_set32(&port, format, FORMAT_FRACTION_END, at);
        port_set32(&port, format, FORMAT_ZEROS, (uint32_t)(precision - count));
    }
    if (port_u32(&port, format, FORMAT_LETTER) != 0)
    {
        port_set8(&port, buffer, at, port_u8(&port, format, FORMAT_LETTER));
        at++;
    }
    if (exponent >= 0)
    {
        port_set8(&port, buffer, at, '+');
    }
    else
    {
        exponent = (int32_t)(0u - (uint32_t)exponent);
        port_set8(&port, buffer, at, '-');
    }
    at++;

    /* The jump table at 0x4ed2a5: digits 0 means 3 or 4, 1 to 3 at least that many. */
    uint32_t digits = port_u32(&port, format, FORMAT_EXPONENT_DIGITS);
    if (digits == 0)
    {
        digits = exponent >= 1000 ? 4 : 3;
    }
    else if (digits <= 3)
    {
        if (digits == 1 && exponent >= 10)
        {
            digits = 2;
        }
        if (digits <= 2 && exponent >= 100)
        {
            digits = 3;
        }
        if (exponent >= 1000)
        {
            digits = 4;
        }
    }
    port_set32(&port, format, FORMAT_EXPONENT_DIGITS, digits);
    if ((int32_t)digits >= 4)
    {
        digit(&port, buffer, &at, &exponent, 1000);
    }
    if ((int32_t)digits >= 3)
    {
        digit(&port, buffer, &at, &exponent, 100);
    }
    if ((int32_t)digits >= 2)
    {
        digit(&port, buffer, &at, &exponent, 10);
    }
    port_set8(&port, buffer, at, (uint32_t)exponent + ZERO);
    at++;
    const uint32_t length = at - port_u32(&port, format, FORMAT_FRACTION_END);
    port_set32(&port, format, FORMAT_EXPONENT_LENGTH, length);
    port_set8(&port, buffer, at, 0);
    return port_return(&port, buffer + at, length);
}
