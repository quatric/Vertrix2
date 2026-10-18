#include "rtlsinglemultiplies.h"

enum
{
    SIGN = 0x80000000u,
    INFINITY_BITS = 0x7f800000u,
    BIAS = 0x7f,
    OVERFLOW_CODE = 0x84,

    RANGE_ERROR = 0x4dae94,
    FLOAT_ERROR = 0x4e7280
};

/* An operand's mantissa with its integer bit, in bits 31..8. */
static uint32_t mantissa(uint32_t bits)
{
    return SIGN | ((bits << 8) & 0x7fffff00u);
}

/* The overflow tail the original shares with its divide and add (0x4e23b5): 0x4dae94 with the
 * working edx, 0x4e7280 with 0x84, then the signed infinity; edx is 0x4e7280's. */
static uint32_t overflow(Port *port, uint32_t sign, uint32_t edx)
{
    port_call(port, RANGE_ERROR, sign, edx, 0, 0);
    port_call(port, FLOAT_ERROR, OVERFLOW_CODE, vertrix_lift_edx, 0, 0);
    return port_return(port, (sign & SIGN) | INFINITY_BITS, vertrix_lift_edx);
}

/* Original 0x4d8198 (eax, edx = two singles): the runtime's software single multiply, without
 * NaNs, infinities, zeros or denormals. The unbiased exponents are added as signed bytes: past
 * +127 (a signed overflow to negative) overflows, below -126 gives 0. The 24-bit mantissas'
 * product is normalized (its top dword shifted left once when the top bit is clear, the exponent
 * lowered), rounded by the bit below the 24 kept, and packed with the exponent + 0x80; an exponent
 * byte of 0 then overflows. edx (callers read it) is the result too; for 0 it is the second
 * operand rotated with the exponent sum in its low byte. */
uint32_t vertrix_port_rtl_single_multiply_4d8198(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t a = entry->eax;
    const uint32_t b = entry->edx;
    /* ecx's bit 31 the result's sign; its low byte becomes the exponent. */
    const uint32_t doubled = entry->ecx * 2 + (a >> 31) + (b >> 31);
    const uint32_t sign = (doubled << 31) | (doubled >> 1);
    const int sum = (int8_t)(uint8_t)((a >> 23) - BIAS) + (int8_t)(uint8_t)((b >> 23) - BIAS);
    const uint8_t exponent_sum = (uint8_t)sum;
    const uint32_t working = (b << 9) | exponent_sum;
    if (sum > 127)
    {
        return overflow(&port, sign, working);
    }
    if (sum < -128 || (int8_t)exponent_sum <= -127)
    {
        return port_return(&port, 0, working);
    }
    uint8_t exponent = (uint8_t)(exponent_sum + 0x80);
    uint32_t high = (uint32_t)(((uint64_t)mantissa(a) * mantissa(b)) >> 32);
    if ((high & SIGN) == 0)
    {
        high <<= 1;
        exponent--;
    }
    const uint32_t round = (high >> 7) & 1;
    high = (uint32_t)((int32_t)high >> 8);
    const uint32_t rounded = high + round;
    exponent = (uint8_t)(exponent + (rounded < high));
    high = rounded;
    if (exponent == 0)
    {
        return overflow(&port, sign & 0xffffff00u, high);
    }
    const uint32_t shifted = (high << 9) | exponent;
    const uint32_t result = (sign & SIGN) | (((shifted >> 8) | (shifted << 24)) >> 1);
    return port_return(&port, result, result);
}
