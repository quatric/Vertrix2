#include "rtl_double_multiply.h"
#include <stddef.h>

typedef struct
{
    uint32_t word[4];
} Product;

static Product multiply(uint64_t a, uint64_t b)
{
    Product p = {{0}};
    for (unsigned i = 0; i < 2; ++i)
    {
        uint64_t carry = 0;
        for (unsigned j = 0; j < 2; ++j)
        {
            uint64_t value = (uint64_t)(uint32_t)(a >> (32 * i)) * (uint32_t)(b >> (32 * j)) +
                             p.word[i + j] + carry;
            p.word[i + j] = (uint32_t)value;
            carry = value >> 32;
        }
        p.word[i + 2] = (uint32_t)carry;
    }
    return p;
}

static int software(VertrixRtlFloatState *s, VertrixRtlFloatCall call, void *context)
{
    uint32_t a = s->eax, ah = s->edx, b = s->ebx, bh = s->ecx;
    uint32_t signs = (ah ^ bh) & 0x80000000u;
    int exponent_a = (int)((ah >> 20) & 2047), exponent_b = (int)((bh >> 20) & 2047);
    ah &= 0xfffff;
    bh &= 0xfffff;
    if (!exponent_a)
    {
        exponent_a = 1;
        do
        {
            exponent_a--;
            ah = (ah << 1) | (a >> 31);
            a <<= 1;
        } while (!(ah & 0x100000));
    }
    ah |= 0x100000;
    if (!exponent_b)
    {
        exponent_b = 1;
        do
        {
            exponent_b--;
            bh = (bh << 1) | (b >> 31);
            b <<= 1;
        } while (!(bh & 0x100000));
    }
    bh |= 0x100000;
    int exponent = exponent_a + exponent_b - 1023;
    uint32_t work = signs | (uint16_t)exponent;
    if (exponent >= 2047)
    {
        goto overflow;
    }
    if (exponent < -53)
    {
        s->eax = 0;
        s->edx = 0;
        s->ebx = b;
        s->ecx = work;
        return 1;
    }
    uint64_t left = (((uint64_t)ah << 32) | a) << 11;
    uint64_t right = (((uint64_t)bh << 32) | b) << 11;
    Product p = multiply(left, right);
    uint32_t sticky = p.word[0];
    uint64_t top = ((uint64_t)p.word[3] << 32) | p.word[2];
    b = (uint32_t)top << 22;
    top >>= 10;
    a = (uint32_t)top;
    ah = (uint32_t)(top >> 32);
    if (ah & 0x200000)
    {
        b = (b >> 1) | (a << 31);
        a = (a >> 1) | (ah << 31);
        ah >>= 1;
        exponent++;
        work = signs | (uint16_t)exponent;
        if (exponent == 2047)
        {
            goto overflow;
        }
    }
    unsigned carry = b >> 31;
    b <<= 1;
    if (carry)
    {
        if (!b)
        {
            carry = sticky ? 1 : a & 1;
        }
        uint32_t rounded = a + carry;
        carry = rounded < a;
        a = rounded;
        ah += carry;
        if (ah & 0x200000)
        {
            a = (a >> 1) | (ah << 31);
            ah >>= 1;
            exponent++;
            work = signs | (uint16_t)exponent;
            if (exponent == 2047)
            {
                goto overflow;
            }
        }
    }
    if (exponent <= 0)
    {
        unsigned count = (unsigned)(exponent == 0 ? 1 : -exponent - 1) & 31;
        b = 0;
        if (count)
        {
            a = (a >> count) | (ah << (32 - count));
            ah >>= count;
        }
        exponent = 0;
    }
    s->ecx = signs | ((uint32_t)exponent << 20);
    s->eax = a;
    s->edx = (ah & 0xfffff) | s->ecx;
    s->ebx = b;
    return 1;

overflow:
    if (!call)
    {
        return 0;
    }
    s->eax = work;
    s->edx = ah;
    s->ebx = b;
    s->ecx = work;
    call(0x4dae94, s, context);
    s->eax = 0x84;
    call(0x4e7280, s, context);
    s->eax = 0;
    s->edx = signs | 0x7ff00000u;
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
    if (ea == 2047 || eb == 2047)
    {
        return sign | UINT64_C(0x7ff0000000000000);
    }
    Product product =
        multiply(fa | (ea ? UINT64_C(1) << 52 : 0), fb | (eb ? UINT64_C(1) << 52 : 0));
    int power = (ea ? (int)ea - 1075 : -1074) + (eb ? (int)eb - 1075 : -1074);
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

int vertrix_rtl_double_multiply_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                     void *context)
{
    if (!state)
    {
        return 0;
    }
    VertrixRtlFloatState s = *state;
    if (!s.eax && !(s.edx << 1))
    {
        s.edx = 0;
        *state = s;
        return 1;
    }
    if (!s.ebx && !(s.ecx << 1))
    {
        s.eax = s.edx = s.ecx = 0;
        *state = s;
        return 1;
    }
    if (s.hardware)
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
