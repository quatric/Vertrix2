#include "rtlsingledivides.h"

enum
{
    SIGN = 0x80000000u,
    INFINITY_BITS = 0x7f800000u,
    BIAS = 0x7f,
    DIVIDE_BY_ZERO_CODE = 0x83,
    OVERFLOW_CODE = 0x84,

    RANGE_ERROR = 0x4dae94,
    FLOAT_ERROR = 0x4e7280
};

/* An operand's mantissa with its integer bit, in bits 31..8. */
static uint32_t mantissa(uint32_t bits)
{
    return SIGN | ((bits << 8) & 0x7fffff00u);
}

/* The overflow tail the original shares with its multiply and add (0x4e23b5): 0x4dae94 with the
 * working edx, 0x4e7280 with 0x84, then the signed infinity; edx is 0x4e7280's. */
static uint32_t overflow(Port *port, uint32_t sign, uint32_t edx)
{
    port_call(port, RANGE_ERROR, sign, edx, 0, 0);
    port_call(port, FLOAT_ERROR, OVERFLOW_CODE, vertrix_lift_edx, 0, 0);
    return port_return(port, (sign & SIGN) | INFINITY_BITS, vertrix_lift_edx);
}

/* Original 0x4d8227 (eax = the dividend, edx = the divisor, both singles): the runtime's software
 * single divide, without NaNs, infinities or denormals. A zero divisor reports 0x83 (0x4e7280) and
 * returns an infinity carrying that routine's sign bit; a zero dividend returns 0. The unbiased
 * exponents are subtracted as signed bytes: past +127 overflows, below -126 gives 0. The 24-bit
 * mantissas' quotient (the dividend's shifted right once over the divisor's) is normalized, rounded
 * by the bit below the 24 kept and packed with the exponent + 0x7f; a rounding carry that wraps the
 * exponent byte overflows. edx (callers read it) is the division's remainder; for 0 it is the
 * divisor doubled (zero dividend) or rotated with its unbiased exponent in its low byte. */
uint32_t vertrix_port_rtl_single_divide_4d8227(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t a = entry->eax;
    const uint32_t b = entry->edx;
    if ((b << 1) == 0)
    {
        const uint32_t reported =
            port_call(&port, FLOAT_ERROR, DIVIDE_BY_ZERO_CODE, b << 1, entry->ebx, entry->ecx);
        return port_return(&port, (reported & SIGN) | INFINITY_BITS, vertrix_lift_edx);
    }
    if ((a << 1) == 0)
    {
        return port_return(&port, 0, b << 1);
    }
    /* ecx's bit 31 the result's sign; its second byte becomes the exponent. */
    const uint32_t doubled = entry->ecx * 2 + (b >> 31) + (a >> 31);
    uint32_t sign = (doubled << 31) | (doubled >> 1);
    const uint8_t exponent_b = (uint8_t)((b >> 23) - BIAS);
    const int difference = (int8_t)(uint8_t)((a >> 23) - BIAS) - (int8_t)exponent_b;
    const uint32_t working = (b << 9) | exponent_b;
    if (difference > 127)
    {
        return overflow(&port, sign, working);
    }
    if (difference < -128 || (int8_t)(uint8_t)difference <= -127)
    {
        return port_return(&port, 0, working);
    }
    uint8_t exponent = (uint8_t)(difference + BIAS);
    const uint32_t divisor = mantissa(b);
    const uint64_t dividend = (uint64_t)(mantissa(a) >> 1) << 32;
    uint32_t quotient = (uint32_t)(dividend / divisor);
    const uint32_t remainder = (uint32_t)(dividend % divisor);
    if ((quotient & SIGN) == 0)
    {
        quotient <<= 1;
        exponent--;
    }
    const uint32_t round = (quotient >> 7) & 1;
    quotient = (uint32_t)((int32_t)quotient >> 8);
    const uint32_t rounded = quotient + round;
    if (rounded < quotient)
    {
        exponent++;
        if (exponent == 0)
        {
            sign = (sign & 0xffff00ffu) | ((uint32_t)exponent << 8);
            return overflow(&port, sign, remainder);
        }
    }
    quotient = rounded;
    const uint32_t shifted = (quotient << 9) | exponent;
    const uint32_t result = (sign & SIGN) | (((shifted >> 8) | (shifted << 24)) >> 1);
    return port_return(&port, result, remainder);
}
