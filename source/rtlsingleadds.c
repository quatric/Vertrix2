#include "rtlsingleadds.h"

enum
{
    SIGN = 0x80000000u,
    INFINITY_BITS = 0x7f800000u,
    ROUND = 0x80,
    OVERFLOW_CODE = 0x84,

    RANGE_ERROR = 0x4dae94,
    FLOAT_ERROR = 0x4e7280
};

/* An operand's mantissa with its integer bit, in bits 31..8. */
static uint32_t mantissa(uint32_t bits)
{
    return SIGN | ((bits << 8) & 0x7fffff00u);
}

/* Original 0x4d80d5 (eax, edx = two singles): the runtime's software single add, without NaNs,
 * infinities or denormals. The smaller operand's mantissa is shifted to the larger's exponent (a
 * shift of 0x20 or more, as a signed byte, clears it; a larger shift wraps as x86 shifts do); equal
 * signs add, a carry raising the exponent (past 255: 0x4dae94, then 0x4e7280 with 0x84, and the
 * signed infinity); unequal signs subtract, the sign following the larger and an exact 0 returned
 * as +0. The result is rounded (+0x80 to the 24-bit mantissa), normalized (an exponent reaching 0
 * gives 0) and packed. edx (callers read it) is the shifted mantissa of the smaller operand, or the
 * error routines' on overflow. */
uint32_t vertrix_port_rtl_single_add_4d80d5(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t a = entry->eax;
    const uint32_t b = entry->edx;
    /* The sign flags: bit 0 the signs differ, bit 1 both negative, bit 2 the larger's sign. */
    uint8_t flags = (uint8_t)(5 * (a >> 31) + (b >> 31));
    uint8_t exponent = (uint8_t)(a >> 23);
    const uint8_t exponent_b = (uint8_t)(b >> 23);
    uint32_t larger = mantissa(a);
    uint32_t smaller = mantissa(b);
    uint8_t shift = (uint8_t)(exponent - exponent_b);
    if (shift != 0)
    {
        if (exponent < exponent_b)
        {
            exponent = exponent_b;
            shift = (uint8_t)-shift;
            const uint32_t swap = larger;
            larger = smaller;
            smaller = swap;
            flags ^= 4;
        }
        smaller = (int8_t)shift < 0x20 ? smaller >> (shift & 0x1f) : 0;
    }
    uint32_t sum;
    uint8_t sign;
    if ((flags & 1) == 0)
    {
        sign = (flags >> 1) & 1;
        sum = larger + smaller;
        if (sum < larger)
        {
            sum = (sum >> 1) | SIGN;
            exponent++;
            if (exponent == 0)
            {
                port_call(&port, RANGE_ERROR, (sum >> 1) | ((uint32_t)sign << 31), smaller, 0, 0);
                port_call(&port, FLOAT_ERROR, OVERFLOW_CODE, vertrix_lift_edx, 0, 0);
                return port_return(&port, ((uint32_t)sign << 31) | INFINITY_BITS, vertrix_lift_edx);
            }
        }
    }
    else
    {
        sign = (flags >> 2) & 1;
        sum = larger - smaller;
        if (larger < smaller)
        {
            sign++;
            sum = 0u - sum;
        }
        else if (sum == 0)
        {
            return port_return(&port, 0, smaller);
        }
    }
    /* Round, then shift the integer bit out (normalizing). */
    const uint32_t rounded = sum + ROUND;
    sum = rounded & 0xffffff00u;
    if (rounded < ROUND)
    {
        exponent++;
    }
    else
    {
        for (;;)
        {
            const uint32_t top = sum & SIGN;
            sum <<= 1;
            if (top != 0)
            {
                break;
            }
            exponent--;
            if (exponent == 0)
            {
                return port_return(&port, 0, smaller);
            }
        }
    }
    const uint32_t packed = (((uint32_t)exponent << 24) | (sum >> 8)) >> 1;
    return port_return(&port, ((uint32_t)(sign & 1) << 31) | packed, smaller);
}
