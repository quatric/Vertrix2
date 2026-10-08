#include "rtl_single_divide.h"
#include <stddef.h>

static uint32_t rotate(uint32_t value, unsigned count)
{
    return (value << count) | (value >> (32 - count));
}

static int overflow(VertrixRtlFloatState *s, VertrixRtlFloatCall call, void *context,
                    uint32_t saved)
{
    if (!call)
    {
        return 0;
    }
    call(0x4dae94, s, context);
    s->eax = 0x84;
    call(0x4e7280, s, context);
    s->eax = (saved & 0x80000000u) | 0x7f800000u;
    return 1;
}

int vertrix_rtl_single_divide_software_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                            void *context)
{
    if (!state)
    {
        return 0;
    }
    VertrixRtlFloatState s = *state;
    uint32_t a = s.eax, b = s.edx, saved_ecx = s.ecx;
    unsigned bsign = b >> 31;
    b += b;
    s.edx = b;
    if (!b)
    {
        if (!call)
        {
            return 0;
        }
        s.eax = 0x83;
        call(0x4e7280, &s, context);
        s.eax = (s.eax & 0x80000000u) | 0x7f800000u;
        *state = s;
        return 1;
    }
    uint32_t signs = saved_ecx * 2u + bsign;
    unsigned asign = a >> 31;
    a += a;
    if (!a)
    {
        s.eax = 0;
        *state = s;
        return 1;
    }
    signs = rotate(signs + asign, 31);
    a = rotate(a, 8);
    b = rotate(b, 8);
    uint8_t ae = (uint8_t)((a & 255u) - 127u);
    uint8_t be = (uint8_t)((b & 255u) - 127u);
    int difference = (int8_t)ae - (int8_t)be;
    uint8_t exponent = (uint8_t)difference;
    a = (a & 0xffffff00u) | exponent;
    b = (b & 0xffffff00u) | be;
    s.edx = b;
    if (difference < -128 || difference > 127)
    {
        if (exponent & 128u)
        {
            a = (signs & 0x80000000u) | (a >> 1);
            s.eax = a;
            if (!overflow(&s, call, context, a))
            {
                return 0;
            }
        }
        else
        {
            s.eax = 0;
        }
        *state = s;
        return 1;
    }
    if ((int8_t)exponent <= -127)
    {
        s.eax = 0;
        *state = s;
        return 1;
    }
    exponent = (uint8_t)(exponent + 127u);
    signs = (signs & 0xffff00ffu) | ((uint32_t)exponent << 8);
    a = 0x80000000u | ((a & 0xffffff00u) >> 1);
    b = 0x80000000u | ((b & 0xffffff00u) >> 1);
    uint64_t numerator = (uint64_t)(a >> 1) << 32;
    uint32_t quotient = (uint32_t)(numerator / b);
    s.edx = (uint32_t)(numerator % b);
    if (!(quotient & 0x80000000u))
    {
        quotient += quotient;
        exponent = (uint8_t)(exponent - 1u);
        signs = (signs & 0xffff00ffu) | ((uint32_t)exponent << 8);
    }
    unsigned round = (quotient >> 7) & 1;
    uint32_t shifted = (quotient >> 8) | 0xff000000u;
    quotient = shifted + round;
    if (quotient < shifted)
    {
        exponent = (uint8_t)(exponent + 1u);
        signs = (signs & 0xffff00ffu) | ((uint32_t)exponent << 8);
        if (!exponent)
        {
            s.eax = signs;
            if (!overflow(&s, call, context, signs))
            {
                return 0;
            }
            *state = s;
            return 1;
        }
    }
    quotient = (quotient << 9) | exponent;
    quotient = rotate(quotient, 24);
    s.eax = (signs & 0x80000000u) | (quotient >> 1);
    *state = s;
    return 1;
}

int vertrix_rtl_single_divide_software_entry(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                             void *context)
{
    if (!state)
    {
        return 0;
    }
    VertrixRtlFloatState s = *state;
    if (s.divide == 0x4d82bb)
    {
        if (s.hardware & 0xffu)
        {
            return 0;
        }
        s.helper = 0x4d80d5;
        s.multiply = 0x4d8198;
        s.divide = 0x4d8227;
    }
    if (s.divide != 0x4d8227 || !vertrix_rtl_single_divide_software_full(&s, call, context))
    {
        return 0;
    }
    *state = s;
    return 1;
}

/* Round an unsigned integer divided by 2^shift. Large shifts still retain directed rounding. */
static uint64_t round_shift(uint64_t value, unsigned shift, unsigned sign, unsigned mode)
{
    if (!shift)
    {
        return value;
    }
    uint64_t quotient = shift < 64 ? value >> shift : 0;
    unsigned remainder = shift < 64 ? !!(value & ((UINT64_C(1) << shift) - 1)) : !!value;
    unsigned half = shift <= 64 ? (unsigned)((value >> (shift - 1)) & 1) : 0;
    unsigned sticky = shift <= 64 ? !!(value & ((UINT64_C(1) << (shift - 1)) - 1)) : !!value;
    unsigned increment = mode == 0   ? half && (sticky || (quotient & 1))
                         : mode == 1 ? remainder && sign
                         : mode == 2 ? remainder && !sign
                                     : 0;
    return quotient + increment;
}

/* Integer long division retains all 64 x87 significand bits and the exact remainder. */
static uint32_t hardware_divide(uint32_t a, uint32_t b, uint32_t control)
{
    unsigned ea = (a >> 23) & 255, eb = (b >> 23) & 255;
    uint32_t fa = a & 0x7fffff, fb = b & 0x7fffff;
    if ((ea == 255 && fa) || (eb == 255 && fb))
    {
        uint32_t chosen;
        if (ea != 255 || !fa)
            chosen = b;
        else if (eb != 255 || !fb)
            chosen = a;
        else
        {
            unsigned qa = (fa >> 22) & 1, qb = (fb >> 22) & 1;
            chosen = qa != qb ? (qa ? a : b) : fa > fb ? a : fb > fa ? b : a & b;
        }
        return chosen | 0x400000;
    }
    unsigned sign = (a ^ b) >> 31;
    uint32_t ma = fa | (ea && ea != 255 ? 0x800000 : 0);
    uint32_t mb = fb | (eb && eb != 255 ? 0x800000 : 0);
    if ((ea == 255 && eb == 255) || (!ma && !mb && ea != 255 && eb != 255))
        return 0xffc00000u;
    if (ea == 255 || (!mb && eb != 255))
        return (sign << 31) | 0x7f800000u;
    if (eb == 255 || !ma)
        return 0;
    int power = (ea ? (int)ea - 150 : -149) - (eb ? (int)eb - 150 : -149);
    while (!(ma & 0x800000))
    {
        ma <<= 1;
        power--;
    }
    while (!(mb & 0x800000))
    {
        mb <<= 1;
        power++;
    }
    if (ma < mb)
    {
        ma <<= 1;
        power--;
    }
    unsigned precision_code = (control >> 8) & 3;
    unsigned precision = precision_code == 0 ? 24 : precision_code == 2 ? 53 : 64;
    unsigned mode = (control >> 10) & 3;
    uint32_t remainder = ma - mb;
    uint64_t quotient = 1;
    for (unsigned i = 1; i < precision; i++)
    {
        remainder <<= 1;
        quotient <<= 1;
        if (remainder >= mb)
        {
            remainder -= mb;
            quotient |= 1;
        }
    }
    unsigned increment = mode == 0 ? remainder * 2u > mb || (remainder * 2u == mb && (quotient & 1))
                         : mode == 1 ? remainder && sign
                         : mode == 2 ? remainder && !sign
                                     : 0;
    if (increment)
    {
        quotient++;
        if (!quotient || (precision < 64 && quotient == (UINT64_C(1) << precision)))
        {
            quotient = UINT64_C(1) << (precision - 1);
            power++;
        }
    }
    if (power < -126)
    {
        unsigned shift = (unsigned)((int)precision - 1 - power - 149);
        uint32_t result = (uint32_t)round_shift(quotient, shift, sign, mode);
        return result ? (sign << 31) | result : 0;
    }
    uint64_t fraction = round_shift(quotient, precision - 24, sign, mode);
    if (fraction == 0x1000000)
    {
        fraction >>= 1;
        power++;
    }
    if (power > 127)
    {
        unsigned infinity = mode == 0 || (mode == 1 && sign) || (mode == 2 && !sign);
        return (sign << 31) | (infinity ? 0x7f800000u : 0x7f7fffffu);
    }
    return (sign << 31) | ((uint32_t)(power + 127) << 23) | ((uint32_t)fraction & 0x7fffff);
}

int vertrix_rtl_single_divide_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                   void *context)
{
    if (!state)
        return 0;
    VertrixRtlFloatState s = *state;
    if (s.divide == 0x4d82bb)
    {
        s.helper = s.hardware ? 0x4d80b7 : 0x4d80d5;
        s.multiply = s.hardware ? 0x4d8188 : 0x4d8198;
        s.divide = !s.hardware ? 0x4d8227 : (s.capability & 1) ? 0x4d8204 : 0x4d8217;
    }
    if (s.divide == 0x4d8227)
    {
        if (!vertrix_rtl_single_divide_software_full(&s, call, context))
            return 0;
    }
    else if (s.divide == 0x4d8204 || s.divide == 0x4d8217)
    {
        if ((s.control & 0x3f) != 0x3f || ((s.control >> 8) & 3) == 1)
            return 0;
        s.eax = hardware_divide(s.eax, s.edx, s.control);
    }
    else
        return 0;
    *state = s;
    return 1;
}
