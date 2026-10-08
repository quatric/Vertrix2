#include "rtl_double_add.h"
#include <stddef.h>

/* Exact unsigned magnitude in units of the smallest double subnormal, 2^-1074. */
typedef struct
{
    uint64_t word[34];
} Magnitude;

static Magnitude magnitude(uint64_t bits)
{
    Magnitude result = {{0}};
    unsigned exponent = (unsigned)((bits >> 52) & 2047);
    uint64_t fraction = bits & UINT64_C(0xfffffffffffff);
    unsigned shift = exponent ? exponent - 1 : 0;
    if (exponent)
    {
        fraction |= UINT64_C(0x10000000000000);
    }
    unsigned index = shift / 64, position = shift % 64;
    result.word[index] = (uint64_t)fraction << position;
    if (position > 11)
    {
        result.word[index + 1] = (uint64_t)fraction >> (64 - position);
    }
    return result;
}

static int compare(const Magnitude *a, const Magnitude *b)
{
    for (unsigned i = 34; i-- > 0;)
    {
        if (a->word[i] != b->word[i])
        {
            return a->word[i] > b->word[i] ? 1 : -1;
        }
    }
    return 0;
}

static Magnitude combine(const Magnitude *a, const Magnitude *b, int subtract)
{
    Magnitude result;
    uint64_t carry = 0;
    for (unsigned i = 0; i < 34; i++)
    {
        uint64_t first = a->word[i], second = b->word[i];
        if (subtract)
        {
            uint64_t value = first - second;
            uint64_t borrow = first < second;
            result.word[i] = value - carry;
            carry = borrow || value < carry;
        }
        else
        {
            uint64_t value = first + second;
            uint64_t overflow = value < first;
            result.word[i] = value + carry;
            carry = overflow || result.word[i] < value;
        }
    }
    return result;
}

static int highest(const Magnitude *a)
{
    for (unsigned i = 2176; i-- > 0;)
    {
        if ((a->word[i / 64] >> (i % 64)) & 1)
        {
            return (int)i;
        }
    }
    return -1;
}

static unsigned bit(const Magnitude *a, unsigned position)
{
    return (unsigned)((a->word[position / 64] >> (position % 64)) & 1);
}

static void round_magnitude(Magnitude *a, unsigned shift, unsigned sign, unsigned mode)
{
    if (!shift)
    {
        return;
    }
    unsigned remainder = 0, sticky = 0;
    for (unsigned i = 0; i < shift; i++)
    {
        unsigned set = bit(a, i);
        remainder |= set;
        if (i + 1 < shift)
        {
            sticky |= set;
        }
    }
    unsigned increment = mode == 0   ? bit(a, shift - 1) && (sticky || bit(a, shift))
                         : mode == 1 ? remainder && sign
                         : mode == 2 ? remainder && !sign
                                     : 0;
    for (unsigned i = 0; i < shift; i++)
    {
        a->word[i / 64] &= ~(UINT64_C(1) << (i % 64));
    }
    if (increment)
    {
        for (unsigned i = shift; i < 2176; i++)
        {
            uint64_t mask = UINT64_C(1) << (i % 64);
            unsigned set = bit(a, i);
            a->word[i / 64] ^= mask;
            if (!set)
            {
                break;
            }
        }
    }
}

static uint64_t hardware_add(uint64_t a, uint64_t b, uint32_t control)
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
            unsigned qa = (fa >> 51) & 1, qb = (fb >> 51) & 1;
            if (qa != qb)
            {
                chosen = qa ? a : b;
            }
            else
            {
                chosen = fa > fb ? a : fb > fa ? b : a & b;
            }
        }
        return chosen | UINT64_C(0x8000000000000);
    }
    if (ea == 2047 || eb == 2047)
    {
        return ea == 2047 && eb == 2047 && ((a ^ b) >> 63) ? UINT64_C(0xfff8000000000000)
               : ea == 2047                                ? a
                                                           : b;
    }
    Magnitude left = magnitude(a), right = magnitude(b), result;
    unsigned sign = a >> 63;
    if ((a ^ b) >> 63)
    {
        int order = compare(&left, &right);
        if (order == 0)
        {
            return 0;
        }
        if (order < 0)
        {
            result = combine(&right, &left, 1);
            sign = b >> 63;
        }
        else
        {
            result = combine(&left, &right, 1);
        }
    }
    else
    {
        result = combine(&left, &right, 0);
    }
    unsigned precision_code = (control >> 8) & 3;
    unsigned precision = precision_code == 0 ? 24 : precision_code == 2 ? 53 : 64;
    unsigned mode = (control >> 10) & 3;
    int top = highest(&result);
    round_magnitude(&result, top >= (int)precision ? (unsigned)top + 1 - precision : 0, sign, mode);
    top = highest(&result);
    round_magnitude(&result, top > 52 ? (unsigned)top - 52 : 0, sign, mode);
    top = highest(&result);
    if (top < 0)
    {
        return 0;
    }
    if (top > 2097)
    {
        unsigned infinity = mode == 0 || (mode == 1 && sign) || (mode == 2 && !sign);
        return ((uint64_t)sign << 63) |
               (infinity ? UINT64_C(0x7ff0000000000000) : UINT64_C(0x7fefffffffffffff));
    }
    unsigned shift = top > 52 ? (unsigned)top - 52 : 0;
    uint64_t fraction = 0;
    for (unsigned i = 0; i < 53; i++)
    {
        fraction |= (uint64_t)bit(&result, shift + i) << i;
    }
    uint64_t exponent = top >= 52 ? (uint64_t)top - 51 : 0;
    return ((uint64_t)sign << 63) | (exponent << 52) |
           (fraction & (exponent ? UINT64_C(0xfffffffffffff) : UINT64_C(0x1fffffffffffff)));
}

static int software_add(VertrixRtlFloatState *s, VertrixRtlFloatCall call, void *context)
{
    uint32_t left_exponent = (s->edx & 0x80000000u) | ((s->edx >> 20) & 2047);
    uint32_t right_exponent = (s->ecx & 0x80000000u) | ((s->ecx >> 20) & 2047);
    uint32_t selected = right_exponent;
    uint32_t work = (left_exponent ^ right_exponent) & 0x80000000u;
    uint64_t a =
        ((uint64_t)((s->edx & 0xfffff) | ((left_exponent & 0xffff) ? 0x100000 : 0)) << 32) | s->eax;
    uint64_t b =
        ((uint64_t)((s->ecx & 0xfffff) | ((right_exponent & 0xffff) ? 0x100000 : 0)) << 32) |
        s->ebx;
    a <<= 1;
    b <<= 1;
    int gap = (int)(right_exponent & 0xffff) - (int)(left_exponent & 0xffff);
    if (gap < 0)
    {
        selected = left_exponent;
        gap = -gap;
        uint64_t swap = a;
        a = b;
        b = swap;
    }
    work |= (uint32_t)gap;
    s->ecx = work;
    s->ebx = (uint32_t)b;
    if (gap > 54)
    {
        uint64_t result = b >> 1;
        s->eax = (uint32_t)result;
        s->edx = ((uint32_t)(result >> 32) & 0xfffff) | (selected & 0x80000000u) |
                 ((selected & 2047) << 20);
        return 1;
    }
    if (work & 0x80000000u)
    {
        b = 0 - b;
        s->ebx = (uint32_t)b;
        selected ^= 0x80000000u;
    }
    uint32_t discarded = 0;
    if (gap)
    {
        if (gap >= 32)
        {
            discarded = !!(uint32_t)a;
            a >>= 32;
        }
        unsigned shift = (unsigned)gap & 31;
        if (shift)
            discarded |= (uint32_t)a << (32 - shift);
        a >>= shift;
    }
    a += b;
    if (a >> 63)
    {
        if (gap >= 53)
        {
            s->ebx = (s->ebx & 0xffffff00u) | !!(discarded & 0x7fffffffu);
            unsigned increment = s->ebx & 1;
            s->ebx >>= 1;
            a += increment;
        }
        a = 0 - a;
        selected ^= 0x80000000u;
    }
    s->ebx = (uint32_t)a | (uint32_t)(a >> 32);
    if (!a)
    {
        s->eax = 0;
        s->edx = 0;
        return 1;
    }
    if (!(selected & 0xffff))
        goto subnormal;
    while (!((uint32_t)(a >> 32) & 0x7fe00000))
    {
        selected = (selected & 0xffff0000u) | ((selected - 1) & 0xffff);
        if (!(selected & 0xffff))
            goto subnormal;
        a <<= 1;
    }
    if ((uint32_t)(a >> 32) & 0x400000)
    {
        discarded += (unsigned)(a & 1);
        a >>= 1;
        selected = (selected & 0xffff0000u) | ((selected + 1) & 0xffff);
        if ((selected & 0xffff) == 2047)
            goto overflow;
    }
    unsigned round = a & 1;
    a >>= 1;
    if (round)
    {
        s->ebx = (s->ebx & 0xffffff00u) | !!discarded;
        s->ebx |= (uint32_t)a;
        unsigned increment = s->ebx & 1;
        s->ebx >>= 1;
        a += increment;
        if ((uint32_t)(a >> 32) & 0x200000)
        {
            a >>= 1;
            selected = (selected & 0xffff0000u) | ((selected + 1) & 0xffff);
            if ((selected & 0xffff) == 2047)
                goto overflow;
        }
    }
    s->eax = (uint32_t)a;
    s->edx = ((uint32_t)(a >> 32) & 0xfffff) | (selected & 0x80000000u) | ((selected & 2047) << 20);
    s->ecx = selected * 2;
    return 1;
subnormal:
    a >>= 1;
    s->eax = (uint32_t)a;
    s->edx = (uint32_t)(a >> 32) | (selected & 0x80000000u);
    return 1;
overflow:
    if (!call)
        return 0;
    s->eax = selected;
    s->edx = (uint32_t)(a >> 32);
    uint32_t sign = selected & 0x80000000u;
    call(0x4dae94, s, context);
    s->eax = 0x84;
    call(0x4e7280, s, context);
    s->edx = sign | 0x7ff00000u;
    s->eax = 0;
    return 1;
}

int vertrix_rtl_double_add_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                void *context)
{
    if (!state)
        return 0;
    VertrixRtlFloatState s = *state;
    if (!s.ebx && !(s.ecx << 1))
    {
        s.ecx <<= 1;
        *state = s;
        return 1;
    }
    if (!s.eax && !(s.edx << 1))
    {
        s.edx = s.ecx;
        s.eax = s.ebx;
        *state = s;
        return 1;
    }
    if (s.hardware & 255)
    {
        if ((s.control & 0x3f) != 0x3f || ((s.control >> 8) & 3) == 1)
            return 0;
        uint64_t result = hardware_add(((uint64_t)s.edx << 32) | s.eax,
                                       ((uint64_t)s.ecx << 32) | s.ebx, s.control);
        s.eax = (uint32_t)result;
        s.edx = (uint32_t)(result >> 32);
        if (s.edx == 0x80000000u)
        {
            s.edx = 0;
            s.eax = 0;
        }
    }
    else if (!software_add(&s, call, context))
        return 0;
    *state = s;
    return 1;
}
