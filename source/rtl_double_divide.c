#include "rtl_double_divide.h"
#include <stddef.h>
typedef struct
{
    uint32_t word[4];
} Product;
static int software(VertrixRtlFloatState *s, VertrixRtlFloatCall call, void *context)
{
    uint32_t ah = s->edx, b = s->ebx, bh = s->ecx;
    uint32_t sign = (ah ^ bh) & 0x80000000u, denominator_sign = bh & 0x80000000u;
    int ea = (ah >> 20) & 2047, eb = (bh >> 20) & 2047;
    ah &= 0xfffff;
    bh &= 0xfffff;
    /* Normalize the actual 64-bit mantissas; software exponent zero starts at zero. */
    uint64_t left = ((uint64_t)(s->edx & 0xfffff) << 32) | s->eax;
    uint64_t right = ((uint64_t)bh << 32) | b;
    if (!ea)
    {
        while (!(left & (UINT64_C(1) << 52)))
        {
            left <<= 1;
            --ea;
        }
    }
    else
    {
        left |= UINT64_C(1) << 52;
    }
    if (!eb)
    {
        while (!(right & (UINT64_C(1) << 52)))
        {
            right <<= 1;
            --eb;
        }
    }
    else
    {
        right |= UINT64_C(1) << 52;
    }
    ah = (uint32_t)(left >> 32);
    b = (uint32_t)right;
    uint32_t scratch = denominator_sign | (uint16_t)eb;
    int exponent = ea - eb + 1023;
    if (exponent >= 2047)
    {
        if (!call)
        {
            return 0;
        }
        s->eax = scratch;
        s->edx = ah;
        s->ebx = b;
        s->ecx = scratch;
        call(0x4dae94, s, context);
        s->eax = 0x84;
        call(0x4e7280, s, context);
        s->eax = 0;
        s->edx = denominator_sign | 0x7ff00000u;
        return 1;
    }
    if (exponent < -52)
    {
        s->eax = s->edx = 0;
        s->ebx = b;
        s->ecx = scratch;
        return 1;
    }
    left <<= 11;
    right <<= 11;
    unsigned whole = left >= right;
    uint64_t remainder = left - (whole ? right : 0), quotient = 0, first_remainder = 0;
    for (unsigned i = 0; i < 64; ++i)
    {
        unsigned carry = (unsigned)(remainder >> 63);
        remainder <<= 1;
        quotient <<= 1;
        if (carry || remainder >= right)
        {
            remainder -= right;
            quotient |= 1;
        }
        if (i == 31)
        {
            first_remainder = remainder;
        }
    }
    uint32_t second = (uint32_t)quotient;
    uint64_t estimate_numerator = first_remainder;
    uint32_t divisor_high = (uint32_t)(right >> 32);
    if ((first_remainder >> 32) >= divisor_high)
    {
        estimate_numerator -= (uint64_t)divisor_high << 32;
    }
    unsigned estimated_nonzero = estimate_numerator / divisor_high != 0;
    uint32_t scratch_final =
        estimated_nonzero ? (uint32_t)(0u - (uint32_t)right * second) : (uint32_t)(right >> 32);
    --exponent;
    if (whole)
    {
        quotient = (quotient >> 1) | (UINT64_C(1) << 63);
        ++exponent;
    }
    uint64_t mantissa = (quotient >> 11) + ((quotient >> 10) & 1);
    /* OR fff00000 before rounding implements carry into exponent via wrap. */
    uint32_t low = (uint32_t)mantissa;
    uint32_t high = (uint32_t)(quotient >> 43) | 0xfff00000u;
    uint32_t before = (uint32_t)(quotient >> 11);
    if (low < before)
    {
        ++high;
        if (!high)
        {
            ++exponent;
        }
    }
    s->ecx = (scratch_final & 0xffffff00u) | 11;
    if (exponent <= 0)
    {
        unsigned count = (unsigned)(exponent == 0 ? 1 : -exponent) & 31;
        high &= 0x1fffff;
        if (exponent < 0)
        {
            s->ecx = (s->ecx & 0xffff0000u) | (uint16_t)-exponent;
        }
        else
        {
            s->ecx = (s->ecx & 0xffffff00u) | 1;
        }
        if (count)
        {
            low = (low >> count) | (high << (32 - count));
            high >>= count;
        }
        exponent = 0;
    }
    s->eax = low;
    s->edx = (high & 0xfffff) | ((uint32_t)exponent << 20) | sign;
    s->ebx = 0;
    return 1;
}
static unsigned bit(const Product *p, unsigned position)
{
    return position < 128 ? (p->word[position / 32] >> (position % 32)) & 1 : 0;
}

static int highest(const Product *p)
{
    for (unsigned i = 128; i-- > 0;)
    {
        if (bit(p, i))
        {
            return (int)i;
        }
    }
    return -1;
}

static unsigned rounding(const Product *p, unsigned shift, unsigned sign, unsigned mode)
{
    if (!shift)
    {
        return 0;
    }
    unsigned sticky = 0;
    for (unsigned i = 0; i < shift && i < 128; ++i)
    {
        if (i + 1 != shift)
        {
            sticky |= bit(p, i);
        }
    }
    unsigned half = bit(p, shift - 1);
    unsigned remainder = half | sticky;
    return mode == 0   ? half && (sticky || bit(p, shift))
           : mode == 1 ? remainder && sign
           : mode == 2 ? remainder && !sign
                       : 0;
}

static void round_product(Product *p, unsigned shift, unsigned sign, unsigned mode)
{
    unsigned increment = rounding(p, shift, sign, mode);
    for (unsigned i = 0; i < shift; ++i)
    {
        p->word[i / 32] &= ~(UINT32_C(1) << (i % 32));
    }
    if (increment)
    {
        for (unsigned i = shift; i < 128; ++i)
        {
            unsigned set = bit(p, i);
            p->word[i / 32] ^= UINT32_C(1) << (i % 32);
            if (!set)
            {
                break;
            }
        }
    }
}

static uint64_t shifted(const Product *p, unsigned shift)
{
    uint64_t value = 0;
    for (unsigned i = 0; i < 64; ++i)
    {
        value |= (uint64_t)bit(p, shift + i) << i;
    }
    return value;
}

static uint64_t hardware(uint64_t a, uint64_t b, uint32_t control)
{
    unsigned ea = (unsigned)((a >> 52) & 2047), eb = (unsigned)((b >> 52) & 2047);
    uint64_t fa = a & UINT64_C(0xfffffffffffff), fb = b & UINT64_C(0xfffffffffffff);
    if ((ea == 2047 && fa) || (eb == 2047 && fb))
    {
        uint64_t chosen;
        if (ea != 2047 || !fa)
        {
            chosen = b;
        }
        else if (eb != 2047 || !fb)
        {
            chosen = a;
        }
        else
        {
            unsigned qa = (unsigned)((fa >> 51) & 1), qb = (unsigned)((fb >> 51) & 1);
            chosen = qa != qb ? (qa ? a : b) : fa > fb ? a : fb > fa ? b : a & b;
        }
        return chosen | UINT64_C(0x8000000000000);
    }
    uint64_t sign = (a ^ b) & UINT64_C(0x8000000000000000);
    if (ea == 2047 && eb != 2047)
    {
        return sign | UINT64_C(0x7ff0000000000000);
    }
    if (ea == 2047 && eb == 2047)
    {
        return UINT64_C(0xfff8000000000000);
    }
    if (eb == 2047)
    {
        return sign;
    }
    uint64_t left = fa | (ea ? UINT64_C(1) << 52 : 0);
    uint64_t right = fb | (eb ? UINT64_C(1) << 52 : 0);
    int ratio_power = 0;
    while (!(left & (UINT64_C(1) << 52)))
    {
        left <<= 1;
        --ratio_power;
    }
    while (!(right & (UINT64_C(1) << 52)))
    {
        right <<= 1;
        ++ratio_power;
    }
    if (left < right)
    {
        left <<= 1;
        --ratio_power;
    }
    Product product = {{0, 0, 0, 0x80000000u}};
    uint64_t remainder = left - right;
    for (unsigned i = 127; i-- > 0;)
    {
        remainder <<= 1;
        if (remainder >= right)
        {
            remainder -= right;
            product.word[i / 32] |= UINT32_C(1) << (i % 32);
        }
    }
    if (remainder)
    {
        product.word[0] |= 1;
    }
    int power = (ea ? (int)ea - 1075 : -1074) - (eb ? (int)eb - 1075 : -1074) + ratio_power - 127;
    for (unsigned i = 0; i < 3; ++i)
    {
        product.word[i] = (product.word[i] >> 1) | (product.word[i + 1] << 31);
    }
    product.word[3] >>= 1;
    if (remainder)
    {
        product.word[0] |= 1;
    }
    ++power;
    unsigned mode = (control >> 10) & 3;
    unsigned precision_code = (control >> 8) & 3;
    int precision = precision_code == 0 ? 24 : precision_code == 2 ? 53 : 64;
    int top = highest(&product);
    if (top >= precision)
    {
        round_product(&product, (unsigned)(top + 1 - precision), (unsigned)(sign >> 63), mode);
        top = highest(&product);
    }
    if (top + power < -1022)
    {
        int shift = -(power + 1074);
        uint64_t value = shift > 0
                             ? shifted(&product, (unsigned)shift) +
                                   rounding(&product, (unsigned)shift, (unsigned)(sign >> 63), mode)
                             : shifted(&product, 0) << (unsigned)-shift;
        return sign | value;
    }
    unsigned shift = top > 52 ? (unsigned)(top - 52) : 0;
    round_product(&product, shift, (unsigned)(sign >> 63), mode);
    top = highest(&product);
    int exponent = top + power + 1023;
    if (exponent >= 2047)
    {
        unsigned infinity = mode == 0 || (mode == 1 && sign) || (mode == 2 && !sign);
        return sign | (infinity ? UINT64_C(0x7ff0000000000000) : UINT64_C(0x7fefffffffffffff));
    }
    uint64_t fraction = top > 52 ? shifted(&product, (unsigned)(top - 52))
                                 : shifted(&product, 0) << (unsigned)(52 - top);
    return sign | ((uint64_t)exponent << 52) | (fraction & UINT64_C(0xfffffffffffff));
}

int vertrix_rtl_double_divide_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                   void *context)
{
    if (!state)
    {
        return 0;
    }
    VertrixRtlFloatState s = *state;
    if (!s.ebx && !(s.ecx << 1))
    {
        if (!call)
        {
            return 0;
        }
        s.ecx = 0;
        s.eax = 0x83;
        call(0x4e7280, &s, context);
        s.edx = (s.eax & 0x80000000u) | 0x7ff00000u;
        s.eax = 0;
    }
    else if (!s.eax && !(s.edx << 1))
    {
        s.edx = 0;
    }
    else if (s.hardware)
    {
        if ((s.control & 63) != 63 || ((s.control >> 8) & 3) == 1)
        {
            return 0;
        }
        uint64_t value =
            hardware(((uint64_t)s.edx << 32) | s.eax, ((uint64_t)s.ecx << 32) | s.ebx, s.control);
        s.eax = (uint32_t)value;
        s.edx = (uint32_t)(value >> 32);
        if (s.edx == 0x80000000u)
        {
            s.eax = s.edx = 0;
        }
    }
    else if (!software(&s, call, context))
    {
        return 0;
    }
    *state = s;
    return 1;
}
