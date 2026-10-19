#include "rtl_single_multiply.h"
#include <stddef.h>

static int software_multiply(VertrixRtlFloatState *s, VertrixRtlFloatCall call, void *context)
{
    uint32_t a, b;
    if (vertrix_rtl_single_multiply_values(s->eax, s->edx, s->ecx, &a, &b))
    {
        s->eax = a;
        s->edx = b;
        return 1;
    }
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

int vertrix_rtl_single_multiply_software(VertrixRtlFloatState *state)
{
    return vertrix_rtl_single_multiply_quick(state->eax, state->edx, state->ecx, &state->eax,
                                             &state->edx);
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
