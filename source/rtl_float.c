#include "rtl_float.h"
#include <stddef.h>

static uint32_t rol(uint32_t value, unsigned count)
{
    return (value << count) | (value >> (32 - count));
}

/* Exact unsigned magnitude in units of the smallest single subnormal, 2^-149. */
typedef struct
{
    uint64_t word[5];
} Magnitude;

static Magnitude magnitude(uint32_t bits)
{
    Magnitude result = {{0}};
    unsigned exponent = (bits >> 23) & 255;
    uint32_t fraction = bits & 0x7fffff;
    unsigned shift = exponent ? exponent - 1 : 0;
    if (exponent)
    {
        fraction |= 0x800000;
    }
    unsigned index = shift / 64, position = shift % 64;
    result.word[index] = (uint64_t)fraction << position;
    if (position > 40)
    {
        result.word[index + 1] = (uint64_t)fraction >> (64 - position);
    }
    return result;
}

static int compare(const Magnitude *a, const Magnitude *b)
{
    for (unsigned i = 5; i-- > 0;)
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
    for (unsigned i = 0; i < 5; i++)
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
    for (unsigned i = 320; i-- > 0;)
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
        for (unsigned i = shift; i < 320; i++)
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

static uint32_t hardware_add(uint32_t a, uint32_t b, uint32_t control)
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
            if (qa != qb)
            {
                chosen = qa ? a : b;
            }
            else
            {
                chosen = fa > fb ? a : fb > fa ? b : a & b;
            }
        }
        return chosen | 0x00400000;
    }
    if (ea == 255 || eb == 255)
    {
        return ea == 255 && eb == 255 && ((a ^ b) >> 31) ? 0xffc00000 : ea == 255 ? a : b;
    }
    Magnitude left = magnitude(a), right = magnitude(b), result;
    unsigned sign = a >> 31;
    if ((a ^ b) >> 31)
    {
        int order = compare(&left, &right);
        if (order == 0)
        {
            return 0;
        }
        if (order < 0)
        {
            result = combine(&right, &left, 1);
            sign = b >> 31;
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
    round_magnitude(&result, top > 23 ? (unsigned)top - 23 : 0, sign, mode);
    top = highest(&result);
    if (top < 0)
    {
        return 0;
    }
    if (top > 276)
    {
        unsigned infinity = mode == 0 || (mode == 1 && sign) || (mode == 2 && !sign);
        return (sign << 31) | (infinity ? 0x7f800000 : 0x7f7fffff);
    }
    unsigned shift = top > 23 ? (unsigned)top - 23 : 0;
    uint32_t fraction = 0;
    for (unsigned i = 0; i < 24; i++)
    {
        fraction |= bit(&result, shift + i) << i;
    }
    uint32_t exponent = top >= 23 ? (uint32_t)top - 22 : 0;
    return (sign << 31) | (exponent << 23) | (fraction & (exponent ? 0x7fffff : 0xffffff));
}

static int software_add(VertrixRtlFloatState *s, VertrixRtlFloatCall call, void *context)
{
    uint32_t a = s->eax, b = s->edx;
    uint8_t signs = (uint8_t)((a >> 31) * 5 + (b >> 31));
    a = rol(a << 1, 8);
    b = rol(b << 1, 8);
    uint8_t exponent_a = (uint8_t)a, exponent_b = (uint8_t)b;
    a = 0x80000000u | ((a & 0xffffff00u) >> 1);
    b = 0x80000000u | ((b & 0xffffff00u) >> 1);
    uint8_t exponent = exponent_a;
    uint8_t gap = (uint8_t)(exponent_a - exponent_b);
    if (exponent_a != exponent_b)
    {
        if (exponent_a < exponent_b)
        {
            exponent = exponent_b;
            gap = (uint8_t)(exponent_b - exponent_a);
            uint32_t swap = a;
            a = b;
            b = swap;
            signs ^= 4;
        }
        b = (int8_t)gap < 32 ? b >> (gap & 31) : 0;
    }
    unsigned opposite = signs & 1;
    signs >>= 1;
    if (!opposite)
    {
        uint32_t sum = a + b;
        unsigned carry = sum < a;
        a = sum;
        if (carry)
        {
            a = 0x80000000u | (a >> 1);
            exponent++;
            if (!exponent)
            {
                a = ((uint32_t)(signs & 1) << 31) | (a >> 1);
                s->eax = a;
                s->edx = b;
                if (!call)
                {
                    return 0;
                }
                uint32_t saved = a;
                call(0x4dae94, s, context);
                s->eax = 0x84;
                call(0x4e7280, s, context);
                s->eax = (saved & 0x80000000u) | 0x7f800000u;
                return 1;
            }
        }
    }
    else
    {
        signs >>= 1;
        uint32_t difference = a - b;
        if (a < b)
        {
            signs++;
            a = 0u - difference;
        }
        else
        {
            a = difference;
            if (!a)
            {
                s->eax = 0;
                s->edx = b;
                return 1;
            }
        }
    }
    uint32_t rounded = a + 0x80;
    unsigned carry = rounded < a;
    a = rounded & 0xffffff00u;
    if (carry)
    {
        exponent++;
    }
    else
    {
        for (;;)
        {
            carry = a >> 31;
            a <<= 1;
            if (carry)
            {
                break;
            }
            exponent--;
            if (!exponent)
            {
                s->eax = 0;
                s->edx = b;
                return 1;
            }
        }
    }
    a = (a & 0xffffff00u) | exponent;
    a = rol(a, 24);
    s->eax = ((uint32_t)(signs & 1) << 31) | (a >> 1);
    s->edx = b;
    return 1;
}

static int single(VertrixRtlFloatState *state, VertrixRtlFloatCall call, void *context,
                  int subtract)
{
    if (!state)
    {
        return 0;
    }
    VertrixRtlFloatState s = *state;
    if (subtract && s.edx)
    {
        s.edx ^= 0x80000000u;
    }
    if (!s.edx || !s.eax)
    {
        if (!s.eax)
        {
            s.eax = s.edx;
        }
        *state = s;
        return 1;
    }
    if (s.helper == 0x4d82a5)
    {
        s.helper = s.hardware ? 0x4d80b7 : 0x4d80d5;
        s.multiply = s.hardware ? 0x4d8188 : 0x4d8198;
        s.divide = !s.hardware ? 0x4d8227 : (s.capability & 1) ? 0x4d8204 : 0x4d8217;
    }
    if (s.helper == 0x4d80d5)
    {
        if (!software_add(&s, call, context))
        {
            return 0;
        }
    }
    else if (s.helper == 0x4d80b7)
    {
        if ((s.control & 63) != 63 || ((s.control >> 8) & 3) == 1)
        {
            return 0;
        }
        s.eax = hardware_add(s.eax, s.edx, s.control);
        if (s.eax == 0x80000000u)
        {
            s.eax = 0;
        }
    }
    else
    {
        return 0;
    }
    *state = s;
    return 1;
}

int vertrix_rtl_single_add_software(VertrixRtlFloatState *state, int subtract)
{
    VertrixRtlFloatState s = *state;
    if (subtract && s.edx)
    {
        s.edx ^= 0x80000000u;
    }
    if (!s.edx || !s.eax)
    {
        if (!s.eax)
        {
            s.eax = s.edx;
        }
        *state = s;
        return 1;
    }
    if (!software_add(&s, NULL, NULL))
    {
        return 0;
    }
    *state = s;
    return 1;
}

int vertrix_rtl_single_subtract_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                     void *context)
{
    return single(state, call, context, 1);
}

int vertrix_rtl_single_add_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                void *context)
{
    return single(state, call, context, 0);
}
