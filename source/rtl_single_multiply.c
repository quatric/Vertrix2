#include "rtl_single_multiply.h"
#include <stddef.h>

static uint32_t rotate(uint32_t value, unsigned shift)
{
    return (value << shift) | (value >> (32 - shift));
}

static int software_multiply(VertrixRtlFloatState *s, VertrixRtlFloatCall call, void *context)
{
    uint32_t a = s->eax, b = s->edx;
    uint32_t flags = rotate(s->ecx * 2u + (a >> 31) + (b >> 31), 31);
    a = rotate(a << 1, 8);
    b = rotate(b << 1, 8);
    uint8_t ea = (uint8_t)((uint8_t)a - 127u);
    uint8_t eb = (uint8_t)((uint8_t)b - 127u);
    uint8_t sum = (uint8_t)(ea + eb);
    a = (a & 0xffffff00u) | ea;
    b = (b & 0xffffff00u) | sum;
    int signed_sum = (int8_t)ea + (int8_t)eb;
    if (signed_sum < -128 || signed_sum > 127)
    {
        if (!(sum & 128))
        {
            s->eax = 0;
            s->edx = b;
            return 1;
        }
        a = flags;
        goto overflow;
    }
    if ((int8_t)sum <= -127)
    {
        s->eax = 0;
        s->edx = b;
        return 1;
    }
    uint8_t exponent = (uint8_t)(sum + 128u);
    flags = (flags & 0xffffff00u) | exponent;
    a = 0x80000000u | ((a & 0xffffff00u) >> 1);
    b = 0x80000000u | ((b & 0xffffff00u) >> 1);
    uint64_t product = (uint64_t)a * b;
    a = (uint32_t)product;
    b = (uint32_t)(product >> 32);
    if (!(b & 0x80000000u))
    {
        b <<= 1;
        exponent--;
    }
    unsigned carry = (b >> 7) & 1;
    b = (b >> 8) | ((b & 0x80000000u) ? 0xff000000u : 0);
    uint32_t rounded = b + carry;
    carry = rounded < b;
    b = rounded;
    exponent = (uint8_t)(exponent + carry);
    flags = (flags & 0xffffff00u) | exponent;
    if (!exponent)
    {
        a = flags;
        goto overflow;
    }
    b = rotate((b << 9) | exponent, 24);
    b = (flags & 0x80000000u) | (b >> 1);
    s->eax = b;
    s->edx = b;
    return 1;

overflow:
    if (!call)
    {
        return 0;
    }
    /* The error tail saves the working ECX sign/exponent before restoring caller ECX. */
    s->eax = a;
    s->edx = b;
    uint32_t saved = a;
    call(0x4dae94, s, context);
    s->eax = 0x84;
    call(0x4e7280, s, context);
    s->eax = (saved & 0x80000000u) | 0x7f800000u;
    return 1;
}

static unsigned highest(uint64_t value)
{
    unsigned bit = 0;
    while (value >>= 1)
    {
        bit++;
    }
    return bit;
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

static uint32_t hardware_multiply(uint32_t a, uint32_t b, uint32_t control)
{
    unsigned ea = (a >> 23) & 255, eb = (b >> 23) & 255;
    uint32_t fa = a & 0x7fffff, fb = b & 0x7fffff;
    if ((ea == 255 && fa) || (eb == 255 && fb))
    {
        uint32_t chosen;
        if (ea != 255 || !fa)
        {
            chosen = b;
        }
        else if (eb != 255 || !fb)
        {
            chosen = a;
        }
        else
        {
            unsigned qa = (fa >> 22) & 1, qb = (fb >> 22) & 1;
            chosen = qa != qb ? (qa ? a : b) : fa > fb ? a : fb > fa ? b : a & b;
        }
        return chosen | 0x400000;
    }
    unsigned sign = (a ^ b) >> 31;
    if (ea == 255 || eb == 255)
    {
        return (!(a & 0x7fffffffu) || !(b & 0x7fffffffu)) ? 0xffc00000u
                                                          : (sign << 31) | 0x7f800000u;
    }
    uint64_t product = (uint64_t)(fa | (ea ? 0x800000 : 0)) * (fb | (eb ? 0x800000 : 0));
    if (!product)
    {
        return 0;
    }
    int power = (ea ? (int)ea - 150 : -149) + (eb ? (int)eb - 150 : -149);
    unsigned mode = (control >> 10) & 3;
    unsigned top = highest(product);
    if (((control >> 8) & 3) == 0 && top > 23)
    {
        unsigned shift = top - 23;
        product = round_shift(product, shift, sign, mode) << shift;
        top = highest(product);
    }
    if ((int)top + power < -126)
    {
        int shift = -(power + 149);
        uint32_t subnormal = shift > 0 ? (uint32_t)round_shift(product, (unsigned)shift, sign, mode)
                                       : (uint32_t)(product << (unsigned)-shift);
        return subnormal ? (sign << 31) | subnormal : 0;
    }
    unsigned shift = top > 23 ? top - 23 : 0;
    product = round_shift(product, shift, sign, mode) << shift;
    top = highest(product);
    int exponent = (int)top + power + 127;
    if (exponent >= 255)
    {
        unsigned infinity = mode == 0 || (mode == 1 && sign) || (mode == 2 && !sign);
        return (sign << 31) | (infinity ? 0x7f800000u : 0x7f7fffffu);
    }
    uint32_t fraction =
        top > 23 ? (uint32_t)(product >> (top - 23)) : (uint32_t)(product << (23 - top));
    return (sign << 31) | ((uint32_t)exponent << 23) | (fraction & 0x7fffff);
}

int vertrix_rtl_single_multiply_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                     void *context)
{
    if (!state)
    {
        return 0;
    }
    VertrixRtlFloatState s = *state;
    if (!s.eax || !s.edx)
    {
        s.eax = 0;
        *state = s;
        return 1;
    }
    if (s.multiply == 0x4d82b0)
    {
        s.helper = s.hardware ? 0x4d80b7 : 0x4d80d5;
        s.multiply = s.hardware ? 0x4d8188 : 0x4d8198;
        s.divide = !s.hardware ? 0x4d8227 : (s.capability & 1) ? 0x4d8204 : 0x4d8217;
    }
    if (s.multiply == 0x4d8198)
    {
        if (!software_multiply(&s, call, context))
        {
            return 0;
        }
    }
    else if (s.multiply == 0x4d8188)
    {
        if ((s.control & 63) != 63 || ((s.control >> 8) & 3) == 1)
        {
            return 0;
        }
        s.eax = hardware_multiply(s.eax, s.edx, s.control);
    }
    else
    {
        return 0;
    }
    *state = s;
    return 1;
}
