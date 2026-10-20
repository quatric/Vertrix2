#include "rtlfloatdigits.h"

enum
{
    /* The frame: ebp under the return address, then the saved ecx, esi and edi and the locals down
     * to ebp - 0x94. */
    BELOW = 0x98,
    EBP = 4,

    LEADING = -0x94, /* a '0' ahead of the digits, for a carry out of them */
    DIGITS = -0x93,
    PRECISION_LEFT = -0x14,
    TRIM = -0x10,
    PLACE = -0x1c,
    COUNT = -0x18,
    NEXT = -0x20,
    TEXT = -0x24,
    VALUE = -0x30, /* the value's magnitude, an extended real */
    VALUE_WORD = -0x28,
    VALUE_HIGH = -0x2c,
    PART = -0x3c,
    TEN_EIGHT = -0x54, /* 10^8 as an extended real, then a product */
    WHOLE = -0x48,

    /* The conversion's parameters. */
    PRECISION = 0,
    DECIMALS = 4,
    MODE = 8,
    SIGN = 0x14,
    RESULT_FIRST = 0x18,
    LENGTH = 0x1c,
    MODE_E = 1,
    MODE_F = 2,
    MODE_G = 4,
    MODE_ALWAYS_FIXED = 8,
    MODE_LONG = 0x20,
    MODE_LONGER = 0x40,

    EXTENDED_EXPONENT = 0x7fff,
    ONE_EXPONENT = 0x3ffe,
    TEN_EIGHT_WORD = 0x4019,
    TEN_EIGHT_HIGH = 0xbebc2000u,
    TEN_SIXTEEN_WORD = 0x4034,
    TEN_SIXTEEN_HIGH = 0x8e1bc9bfu,
    TEN_SIXTEEN_LOW = 0x4000000u,

    CLASSIFY = 0x4edf7f,
    DIVIDE = 0x4edd24,
    TO_INTEGER = 0x4ee025,
    FROM_INTEGER = 0x4ee094,
    MULTIPLY = 0x4edb48,
    SUBTRACT = 0x4ee0dc,
    SCALE = 0x4ecc60,
    FORMAT_FIXED = 0x4ed096,
    FORMAT_EXPONENT = 0x4ed2b5
};

/* 0x4ecf60: two digits of `value` (under 100 as a byte pair), as ax / 10. */
static void two_digits(Port *port, uint32_t *at, uint32_t value)
{
    uint32_t low = value & 0xff;
    uint32_t high = (value >> 8) & 0xff;
    if (low >= 10)
    {
        const uint32_t ax = value & 0xffff;
        low = (ax / 10) & 0xff;
        high = (ax % 10) & 0xff;
    }
    else
    {
        const uint32_t swap = low;
        low = high;
        high = swap;
    }
    port_set8(port, *at, 0, low + '0');
    port_set8(port, *at, 1, high + '0');
    *at += 2;
}

/* 0x4ecf49: four digits, the hundreds by a 16-bit division. */
static void four_digits(Port *port, uint32_t *at, uint32_t value)
{
    uint32_t quotient = 0;
    uint32_t rest = value;
    if (value >= 100)
    {
        quotient = (value & 0xffff) / 100;
        rest = (value & 0xffff) % 100;
    }
    two_digits(port, at, quotient);
    two_digits(port, at, rest);
}

/* 0x4ecf33: eight digits, the ten thousands by a 32-bit division. */
static void eight_digits(Port *port, uint32_t *at, uint32_t value)
{
    uint32_t quotient = 0;
    uint32_t rest = value;
    if (value >= 10000)
    {
        quotient = value / 10000;
        rest = value % 10000;
    }
    four_digits(port, at, quotient);
    four_digits(port, at, rest);
}

/* Original 0x4eccb9 (eax = the extended real, edx = the conversion's parameters, ebx = the text,
 * ecx as 0x4ec970 leaves it): the digits of a value for printf. The sign goes to the parameters
 * (+0x14) and the magnitude is classified (0x4edf7f): zero, "nan" or "inf" (length 3), or a number.
 * A number is scaled by a power of ten near its decimal exponent (0x4ecc60), or split by 10^8 when
 * it lies between 10^8 and 10^16, and its digits produced eight at a time (0x4ee025 to an integer,
 * the rest kept by 0x4ee094, 0x4ee0dc and 0x4edb48) for as many as the precision asks (at most 15,
 * 20 or 40 with the long modes). Leading zeros are skipped, the digits cut to the precision and
 * rounded (trailing zeros or nines dropped, a carry into the '0' ahead), and the fixed (0x4ed096:
 * %f, and %g for an exponent from -4 to below the precision or with mode 8) or exponent (0x4ed2b5)
 * layout writes the text. */
uint32_t vertrix_port_rtl_float_digits_4eccb9(PORT_SIGNATURE)
{
    Port port;
    uint8_t stack[BELOW + 8];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t ebp = entry->esp - EBP;
#define AT(offset) (ebp + (uint32_t)(offset))
    const uint32_t parameters = entry->edx;
    const uint32_t text = entry->ebx;
    const uint32_t source = entry->eax;
    uint32_t ecx = entry->ecx;
    uint32_t edx = parameters;
    uint32_t edi = 0;
    uint32_t eax;
    uint32_t ebx;

    port_set32(&port, AT(TEXT), 0, text);
    port_set32(&port, parameters, SIGN, 0);
    port_set16(&port, AT(VALUE_WORD), 0, port_u16(&port, source, 8));
    port_set32(&port, AT(VALUE_HIGH), 0, port_u32(&port, source, 4));
    port_set32(&port, AT(VALUE), 0, port_u32(&port, source, 0));
    if (port_u8(&port, AT(VALUE_WORD + 1), 0) & 0x80)
    {
        port_set32(&port, parameters, SIGN, 0xffffffffu);
    }
    port_set8(&port, AT(VALUE_WORD + 1), 0, port_u8(&port, AT(VALUE_WORD + 1), 0) & 0x7f);
    port_set32(&port, parameters, LENGTH, 0);
    port_set32(&port, parameters, 0x20, 0);
    port_set32(&port, parameters, 0x24, 0);
    port_set32(&port, parameters, 0x28, 0);
    port_set32(&port, parameters, RESULT_FIRST, 0);
    const uint32_t kind = port_call(&port, CLASSIFY, AT(VALUE), edx, text, ecx);
    edx = vertrix_lift_edx;
    switch (kind)
    {
        case 0:
        case 4:
            port_set32(&port, parameters, SIGN, 0);
            ecx = 0;
            goto digits;
        case 2:
        case 3:
            port_set8(&port, text, 0, kind == 2 ? 'n' : 'i');
            port_set8(&port, text, 1, kind == 2 ? 'a' : 'n');
            port_set8(&port, text, 2, kind == 2 ? 'n' : 'f');
            port_set8(&port, text, 3, 0);
            port_set32(&port, parameters, LENGTH, 3);
            return port_return(&port, text, edx);
        case 1:
            break;
        default:
            goto digits;
    }
    {
        /* The decimal exponent, about (binary exponent) * log10(2), less 4. */
        const int32_t binary = (int32_t)port_u16(&port, AT(VALUE_WORD), 0) - ONE_EXPONENT;
        ecx = (uint32_t)((int32_t)((uint32_t)binary * 0x7597u) / 100000) - 4;
    }
    if (ecx == 0)
    {
        goto digits;
    }
    if ((int32_t)ecx < 0)
    {
        ecx = 0u - (((0u - ecx) + 3) & 0xfffffffcu);
        goto scale;
    }
    {
        const uint32_t word = port_u16(&port, AT(VALUE_WORD), 0);
        const uint32_t high = port_u32(&port, AT(VALUE_HIGH), 0);
        if (word < TEN_EIGHT_WORD || (word == TEN_EIGHT_WORD && high < TEN_EIGHT_HIGH))
        {
            ecx = 0;
            goto digits;
        }
        if (!(word < TEN_SIXTEEN_WORD ||
              (word == TEN_SIXTEEN_WORD &&
               (high < TEN_SIXTEEN_HIGH ||
                (high == TEN_SIXTEEN_HIGH && port_u32(&port, AT(VALUE), 0) < TEN_SIXTEEN_LOW)))))
        {
            ecx &= 0xfffffffcu;
            goto scale;
        }
    }
    /* Between 10^8 and 10^16: the high eight digits apart. */
    port_set16(&port, AT(TEN_EIGHT + 8), 0, TEN_EIGHT_WORD);
    port_set32(&port, AT(TEN_EIGHT + 4), 0, TEN_EIGHT_HIGH);
    ecx = 0;
    port_set32(&port, AT(TEN_EIGHT), 0, 0);
    port_call_with(&port, DIVIDE, AT(VALUE), AT(TEN_EIGHT), AT(PART), ecx, parameters, edi, ebp);
    edi = port_call_with(&port, TO_INTEGER, AT(PART), AT(PART), AT(TEN_EIGHT), ecx, parameters, edi,
                         ebp);
    edx = vertrix_lift_edx;
    port_call_with(&port, FROM_INTEGER, edi, edx, AT(TEN_EIGHT), ecx, parameters, edi, ebp);
    port_call_with(&port, MULTIPLY, AT(PART), AT(TEN_EIGHT), AT(TEN_EIGHT), ecx, parameters, edi,
                   ebp);
    ecx = 8;
    port_call_with(&port, SUBTRACT, AT(VALUE), AT(TEN_EIGHT), AT(VALUE), ecx, parameters, edi, ebp);
    goto digits;

scale:
    port_call_with(&port, SCALE, AT(VALUE), 0u - ecx, text, ecx, parameters, edi, ebp);

digits:
    {
        const uint32_t mode = port_u8(&port, parameters, MODE);
        if (mode & MODE_F)
        {
            uint32_t wanted = port_u32(&port, parameters, PRECISION) + ecx + 10;
            const uint32_t decimals = port_u32(&port, parameters, DECIMALS);
            if ((int32_t)decimals > 0)
            {
                wanted += decimals;
            }
            port_set32(&port, AT(PRECISION_LEFT), 0, wanted);
        }
        else
        {
            port_set32(&port, AT(PRECISION_LEFT), 0, port_u32(&port, parameters, PRECISION) + 7);
        }
        uint32_t most = (mode & MODE_LONG) ? 0x14 : 0xf;
        if (port_u8(&port, parameters, MODE) & MODE_LONGER)
        {
            most += most;
        }
        most += 4;
        if ((int32_t)most < (int32_t)port_u32(&port, AT(PRECISION_LEFT), 0))
        {
            port_set32(&port, AT(PRECISION_LEFT), 0, most);
        }
    }
    port_set8(&port, AT(LEADING), 0, '0');
    port_set8(&port, AT(DIGITS), 0, 0);
    port_set32(&port, AT(NEXT), 0, AT(DIGITS));
    port_set32(&port, AT(COUNT), 0, 0);
    while (!port.env.failed)
    {
        const uint32_t left = port_u32(&port, AT(PRECISION_LEFT), 0);
        if ((int32_t)left <= 0)
        {
            break;
        }
        ebx = left - 8;
        port_set32(&port, AT(PRECISION_LEFT), 0, ebx);
        if (edi == 0)
        {
            if ((port_u16(&port, AT(VALUE_WORD), 0) & EXTENDED_EXPONENT) == 0)
            {
                break;
            }
            edi =
                port_call_with(&port, TO_INTEGER, AT(VALUE), left, ebx, ecx, parameters, edi, ebp);
            if ((int32_t)ebx > 0)
            {
                port_call_with(&port, FROM_INTEGER, edi, AT(WHOLE), AT(VALUE), ecx, parameters, edi,
                               ebp);
                port_call_with(&port, SUBTRACT, AT(VALUE), AT(WHOLE), AT(VALUE), ecx, parameters,
                               edi, ebp);
                port_set16(&port, AT(WHOLE + 8), 0, TEN_EIGHT_WORD);
                port_set32(&port, AT(WHOLE + 4), 0, TEN_EIGHT_HIGH);
                port_set32(&port, AT(WHOLE), 0, 0);
                port_call_with(&port, MULTIPLY, AT(VALUE), AT(WHOLE), AT(VALUE), ecx, parameters,
                               edi, ebp);
            }
        }
        uint32_t at = port_u32(&port, AT(NEXT), 0);
        eight_digits(&port, &at, edi);
        port_set8(&port, at, 0, 0);
        port_set32(&port, AT(NEXT), 0, at);
        port_set32(&port, AT(COUNT), 0, port_u32(&port, AT(COUNT), 0) + 8);
        edi = 0;
    }
    /* The digits: leading zeros skipped, then cut to the precision and rounded. */
    eax = port_u32(&port, AT(COUNT), 0);
    edx = AT(DIGITS);
    ecx += 7;
    while (port_u8(&port, edx, 0) == '0' && !port.env.failed)
    {
        eax--;
        ecx--;
        edx++;
    }
    {
        const uint32_t mode = port_u8(&port, parameters, MODE);
        edi = port_u32(&port, parameters, PRECISION);
        if (mode & MODE_F)
        {
            ecx += port_u32(&port, parameters, DECIMALS);
            edi += ecx + 1;
        }
        else if (mode & MODE_E)
        {
            const uint32_t decimals = port_u32(&port, parameters, DECIMALS);
            if ((int32_t)decimals > 0)
            {
                edi++;
            }
            else
            {
                edi += decimals;
            }
            ecx++;
            ecx -= port_u32(&port, parameters, DECIMALS);
        }
    }
    if ((int32_t)edi >= 0)
    {
        if ((int32_t)edi > (int32_t)eax)
        {
            edi = eax;
        }
        uint32_t most = (port_u8(&port, parameters, MODE) & MODE_LONG) ? 0x14 : 0xf;
        if (port_u8(&port, parameters, MODE) & MODE_LONGER)
        {
            most += most;
        }
        if ((int32_t)edi > (int32_t)most)
        {
            edi = most + 1;
        }
        port_set8(&port, AT(TRIM), 0, '0');
        if ((int32_t)eax > (int32_t)edi && port_u8(&port, edx + edi, 0) >= '5')
        {
            port_set8(&port, AT(TRIM), 0, '9');
        }
        port_set32(&port, AT(PLACE), 0, edi);
        uint32_t last = edi + edx;
        uint32_t byte;
        const uint32_t trim = port_u8(&port, AT(TRIM), 0);
        for (;;)
        {
            port_set32(&port, AT(PLACE), 0, port_u32(&port, AT(PLACE), 0) - 1);
            last--;
            byte = port_u8(&port, last, 0);
            if (byte != trim || port.env.failed)
            {
                break;
            }
            edi--;
        }
        if (trim == '9')
        {
            port_set8(&port, last, 0, byte + 1);
        }
        if ((int32_t)port_u32(&port, AT(PLACE), 0) < 0)
        {
            edx--;
            edi++;
            ecx++;
        }
    }
    if ((int32_t)edi <= 0)
    {
        edi = 1;
        ecx = 0;
        port_set8(&port, AT(LEADING), 0, '0');
        edx = AT(LEADING);
        port_set32(&port, parameters, SIGN, ecx);
    }
    {
        const uint32_t mode = port_u8(&port, parameters, MODE);
        int fixed = (mode & MODE_F) != 0;
        if (!fixed && (mode & MODE_G))
        {
            fixed = ((int32_t)ecx >= -4 &&
                     (int32_t)ecx < (int32_t)port_u32(&port, parameters, PRECISION)) ||
                    (port_u8(&port, parameters, MODE) & MODE_ALWAYS_FIXED);
        }
        const uint32_t argument = text;
        port_call_stack(&port, fixed ? FORMAT_FIXED : FORMAT_EXPONENT, parameters, edx, edi, ecx,
                        &argument, 1);
    }
    return port_return(&port, text, vertrix_lift_edx);
#undef AT
}
