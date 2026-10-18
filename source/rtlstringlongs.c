#include "rtlstringlongs.h"

enum
{
    /* The character class table (indexed by the character + 1; 2 marks a blank) and the largest
     * value per base that can take one more digit without overflow. */
    CHARACTER_CLASSES = 0x507d58,
    CLASS_BLANK = 2,
    DIGIT_LIMITS = 0x50b214,

    BASE_MINIMUM = 2,
    BASE_MAXIMUM = 36,
    BASE_HEX = 16,
    BASE_OCTAL = 8,
    BASE_DECIMAL = 10,

    /* The errors reported through 0x4dae70: an invalid base and an out-of-range value. */
    ERROR_BASE = 0xd,
    ERROR_RANGE = 0xe,

    SIGNED = 1,
    RESULT_LONG_MIN = 0x80000000u,
    RESULT_LONG_MAX = 0x7fffffff,
    RESULT_ULONG_MAX = 0xffffffffu,

    ERROR_SET = 0x4dae70,
    DIGIT_VALUE = 0x4ea6b0
};

/* Original 0x4ea540 (eax = the string, edx = where to store the end or 0, ebx = the base or 0,
 * ecx = 1 for a signed result): the runtime's strtol and strtoul. The end is first set to the
 * string; blanks and one sign are skipped; base 0 means 16 after "0x" or "0X", 8 after "0", else
 * 10, and base 16 skips a "0x" prefix; a base outside 2 to 36 reports 0xd and returns 0. Digits
 * (0x4ea6b0) below the base are accumulated, overflow noted when the value exceeds the base's limit
 * or wraps. The end is the first character not taken (the string when no digit was). Out of range
 * (overflow, or a signed value above 0x7fffffff other than -0x80000000) reports 0xe and returns
 * ULONG_MAX, or LONG_MIN or LONG_MAX by the sign; else the value, negated after a '-'. */
uint32_t vertrix_port_rtl_string_to_long_4ea540(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t string = entry->eax;
    const uint32_t end = entry->edx;
    const uint32_t kind = entry->ecx;
    uint32_t base = entry->ebx;
    if (end != 0)
    {
        port_set32(&port, end, 0, string);
    }
    uint32_t at = string;
    while ((port_u8(&port, CHARACTER_CLASSES, (port_u8(&port, at, 0) + 1) & 0xff) & CLASS_BLANK) !=
               0 &&
           !port.env.failed)
    {
        at++;
    }
    const uint32_t sign = port_u8(&port, at, 0);
    if (sign == '+' || sign == '-')
    {
        at++;
    }
    int hex_prefix = 0;
    if (base == 0)
    {
        if (port_u8(&port, at, 0) == '0' &&
            (port_u8(&port, at, 1) == 'x' || port_u8(&port, at, 1) == 'X'))
        {
            base = BASE_HEX;
            hex_prefix = 1;
        }
        else
        {
            base = port_u8(&port, at, 0) == '0' ? BASE_OCTAL : BASE_DECIMAL;
        }
    }
    else if ((int32_t)base < (int32_t)BASE_MINIMUM || (int32_t)base > (int32_t)BASE_MAXIMUM)
    {
        port_call(&port, ERROR_SET, ERROR_BASE, at, entry->ebx, entry->ecx);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    else if (base == BASE_HEX)
    {
        hex_prefix = 1;
    }
    if (hex_prefix && port_u8(&port, at, 0) == '0' &&
        (port_u8(&port, at, 1) == 'x' || port_u8(&port, at, 1) == 'X'))
    {
        at += 2;
    }
    const uint32_t start = at;
    const uint32_t limit = port_u32(&port, DIGIT_LIMITS, base * 4);
    int overflow = 0;
    uint32_t value = 0;
    for (;;)
    {
        const uint32_t digit = port_call(&port, DIGIT_VALUE, port_u8(&port, at, 0), at, value, 0);
        if ((int32_t)digit >= (int32_t)base || port.env.failed)
        {
            break;
        }
        if (value > limit)
        {
            overflow = 1;
        }
        const uint32_t before = value;
        value = value * base + digit;
        if (value < before)
        {
            overflow = 1;
        }
        at++;
    }
    if (at == start)
    {
        at = string;
    }
    if (end != 0)
    {
        port_set32(&port, end, 0, at);
    }
    int out_of_range = overflow;
    if (kind == SIGNED && value >= RESULT_LONG_MIN && (value != RESULT_LONG_MIN || sign != '-'))
    {
        out_of_range = 1;
    }
    if (out_of_range)
    {
        port_call(&port, ERROR_SET, ERROR_RANGE, at, value, 0);
        if (kind == 0)
        {
            return port_return(&port, RESULT_ULONG_MAX, vertrix_lift_edx);
        }
        return port_return(&port, sign == '-' ? RESULT_LONG_MIN : RESULT_LONG_MAX,
                           vertrix_lift_edx);
    }
    if (sign == '-')
    {
        value = 0u - value;
    }
    return port_return(&port, value, at);
}
