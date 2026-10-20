#include "rtlextendeds.h"

enum
{
    TOP = 0x80000000u,
    INDEFINITE = 0xc0000000u,
    BIAS = 0x3fff,
    MULTIPLY_BIAS = 0x3ffe,
    MAXIMUM = 0x7fff,
    SMALLEST = -0x40,

    DIVIDE_INVALID = 0x4e2371, /* 0/0 */
    DIVIDE_BY_ZERO = 0x4e237d
};

static VertrixExtended result(uint32_t eax, uint32_t edx, uint32_t esi)
{
    VertrixExtended value = {eax, edx, esi};
    return value;
}

/* esi with its low word replaced. */
static uint32_t with_low(uint32_t word, uint32_t low)
{
    return (word & 0xffff0000u) | (low & 0xffffu);
}

/* add esi, value: the sum, and whether it carried or overflowed (jb or jo). */
static uint32_t add_flags(uint32_t esi, uint32_t value, int *special)
{
    const uint32_t sum = esi + value;
    const int carry = sum < esi;
    const int overflow = (int)((~(esi ^ value) & (esi ^ sum)) >> 31);
    *special = carry || overflow;
    return sum;
}

/* The sign and exponent of a word as the originals take them: sign in bit 31, exponent below. */
static uint32_t sign_exponent(uint32_t word)
{
    return (uint32_t)(int32_t)(int16_t)word & 0x80007fffu;
}

/* The end shared by the operations (add ecx, ecx; rcr cx, 1): the word with the sign of bit 31. */
static uint32_t finish(uint32_t word)
{
    const uint32_t sign = word >> 31;
    word <<= 1;
    return with_low(word, (sign << 15) | ((word & 0xffffu) >> 1));
}

/* shrd eax, edx, cl; shrd edx, 0, cl (the count taken mod 32). */
static void shift_right(uint32_t *eax, uint32_t *edx, unsigned count)
{
    count &= 31;
    if (count != 0)
    {
        *eax = (*eax >> count) | (*edx << (32 - count));
        *edx >>= count;
    }
}

/* Original 0x4edc0e: the product. Infinities and NaNs (an exponent word of 0x7fff either sign)
 * are taken first: a NaN wins (the larger mantissa of two), infinity times zero is the indefinite
 * NaN, infinity keeps its sign turned by a negative other. A zero is +0. The 128-bit product of
 * the mantissas is normalized, rounded to nearest even on the bits below (the lowest dword only
 * as a sticky bit), and overflows to infinity, or is denormalized and flushed below 2^-64. */
VertrixExtended vertrix_extended_multiply(uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                                          uint32_t esi)
{
    int special;
    const uint32_t first = esi & 0xffffu;
    if (first == 0xffffu || first == 0x7fffu)
    {
        /* 0x4edb72: the first is infinite or NaN. */
        if (eax == 0 && edx == TOP && ebx == 0 && ecx == 0)
        {
            return result(eax, INDEFINITE, 0xffffffffu);
        }
        esi = add_flags(esi, 0x10000, &special);
        if (!special)
        {
            if (eax == 0 && edx == TOP && (int32_t)esi < 0)
            {
                esi ^= 0x8000;
            }
            return result(eax, edx, esi);
        }
        /* 0x4edbb0: both. */
        esi -= 0x10000;
        if (edx > ecx || (edx == ecx && eax > ebx))
        {
            return result(eax, edx, esi);
        }
        if (edx == ecx && eax == ebx)
        {
            if (eax != 0 || edx != TOP)
            {
                return result(eax, edx, esi);
            }
            if ((int16_t)esi < 0)
            {
                esi ^= edx;
            }
        }
        return result(ebx, ecx, esi >> 16);
    }
    esi = add_flags(esi, 0x10000, &special);
    if (special)
    {
        /* 0x4edbdc: the second is infinite or NaN. */
        esi -= 0x10000;
        if (ebx == 0 && ecx == TOP)
        {
            if (eax == 0 && edx == 0)
            {
                ecx = INDEFINITE;
                esi = 0xffffffffu;
            }
            else if ((int16_t)esi < 0)
            {
                esi ^= ecx;
            }
        }
        return result(ebx, ecx, esi >> 16);
    }
    esi -= 0x10000;
    if (eax == 0 && edx == 0 && ((esi << 1) & 0xffffu) == 0)
    {
        return result(0, 0, esi & 0xffff0000u);
    }
    if (ecx == 0 && ebx == 0 && (esi & 0x7fff0000u) == 0)
    {
        return result(0, 0, 0);
    }
    uint32_t word = sign_exponent(esi >> 16) + sign_exponent(esi);
    uint32_t exponent = word & 0xffffu;
    const int below = exponent < MULTIPLY_BIAS;
    exponent = (exponent - MULTIPLY_BIAS) & 0xffffu;
    if (!below && exponent >= MAXIMUM)
    {
        return result(0, TOP, finish(with_low(word, MAXIMUM)));
    }
    if ((int16_t)exponent < SMALLEST)
    {
        return result(0, 0, finish(0));
    }
    const uint64_t low_low = (uint64_t)eax * ebx;
    const uint64_t low_high = (uint64_t)eax * ecx;
    const uint64_t high_low = (uint64_t)edx * ebx;
    const uint64_t high_high = (uint64_t)edx * ecx;
    const uint32_t w0 = (uint32_t)low_low;
    uint64_t sum = (low_low >> 32) + (uint32_t)low_high + (uint32_t)high_low;
    uint32_t w1 = (uint32_t)sum;
    sum = (sum >> 32) + (low_high >> 32) + (high_low >> 32) + (uint32_t)high_high;
    uint32_t w2 = (uint32_t)sum;
    uint32_t w3 = (uint32_t)((sum >> 32) + (high_high >> 32));
    if ((w3 & TOP) == 0)
    {
        w3 = (w3 << 1) | (w2 >> 31);
        w2 = (w2 << 1) | (w1 >> 31);
        w1 <<= 1;
        exponent = (exponent - 1) & 0xffffu;
    }
    const uint32_t half = w1 >> 31;
    w1 <<= 1;
    if (half)
    {
        const uint32_t up = w1 != 0 || w0 != 0 ? 1 : (w2 & 1);
        const uint64_t low = (uint64_t)w2 + up;
        const uint64_t high = (uint64_t)w3 + (low >> 32);
        w2 = (uint32_t)low;
        w3 = (uint32_t)high;
        if (high >> 32)
        {
            w2 = (w2 >> 1) | (w3 << 31);
            w3 = (w3 >> 1) | TOP;
            exponent = (exponent + 1) & 0xffffu;
            if (exponent == MAXIMUM)
            {
                return result(0, TOP, finish(with_low(word, MAXIMUM)));
            }
        }
    }
    if ((int16_t)exponent <= 0)
    {
        const unsigned count = exponent == 0 ? 1 : ((0u - exponent) & 0xffu);
        shift_right(&w2, &w3, count);
        exponent = 0;
    }
    return result(w2, w3, finish(with_low(word, exponent)));
}

/* Original 0x4eddc4: the quotient. Infinities and NaNs first (a NaN wins, infinity over infinity
 * is the indefinite NaN, an infinite dividend keeps its sign turned by a negative divisor, a
 * finite one over infinity is a signed zero); 0/0 raises the invalid operation (0x4e2371) and is
 * the indefinite NaN, another value over zero raises division by zero (0x4e237d) and is infinity.
 * Denormal operands are normalized, the mantissas divided in two 32-bit steps with corrections,
 * the quotient truncated (not rounded), then denormalized or flushed as the product is. An
 * overflow takes the divisor's sign. */
VertrixExtended vertrix_extended_divide(Port *port, uint32_t eax, uint32_t edx, uint32_t ebx,
                                        uint32_t ecx, uint32_t esi)
{
    int special;
    const uint32_t first = esi & 0xffffu;
    if (first == 0xffffu || first == 0x7fffu)
    {
        /* 0x4edd4e: the dividend is infinite or NaN. */
        esi = add_flags(esi, 0x10000, &special);
        if (!special)
        {
            if ((int32_t)esi < 0 && eax == 0 && edx == TOP)
            {
                esi ^= 0x8000;
            }
            return result(eax, edx, esi);
        }
        esi -= 0x10000;
        if (eax == 0 && ebx == 0 && edx == TOP && ecx == edx)
        {
            return result(eax, INDEFINITE, with_low(esi, 0xffff));
        }
        if (edx > ecx || (edx == ecx && eax > ebx))
        {
            return result(eax, edx, esi);
        }
        return result(ebx, ecx, esi >> 16);
    }
    esi = add_flags(esi, 0x10000, &special);
    if (special)
    {
        /* 0x4edd9f: the divisor is infinite or NaN. */
        esi -= 0x10000;
        if (ebx == 0 && ecx == TOP)
        {
            esi = (esi ^ (esi << 16)) & ecx;
            ecx = 0;
        }
        return result(ebx, ecx, esi >> 16);
    }
    esi -= 0x10000;
    if (ecx == 0 && ebx == 0 && (esi & 0x7fff0000u) == 0)
    {
        if (eax == 0 && edx == 0 && ((esi << 1) & 0xffffu) == 0)
        {
            port_call(port, DIVIDE_INVALID, with_low(esi, 0), 0, 0, 0);
            return result(0, INDEFINITE, with_low(esi, 0xffff));
        }
        port_call(port, DIVIDE_BY_ZERO, eax, edx, 0, 0);
        return result(0, TOP, esi | 0x7fff);
    }
    if (eax == 0 && edx == 0 && ((esi << 1) & 0xffffu) == 0)
    {
        return result(0, 0, esi & 0xffff0000u);
    }
    uint32_t dividend = sign_exponent(esi);
    uint32_t divisor = sign_exponent(esi >> 16);
    dividend = (dividend & 0xffffu) | (((dividend ^ divisor) & TOP));
    uint32_t divisor_high = ecx;
    uint32_t divisor_low = ebx;
    if ((dividend & 0xffffu) == 0)
    {
        do
        {
            edx = (edx << 1) | (eax >> 31);
            eax <<= 1;
            dividend = with_low(dividend, dividend - 1);
        } while ((edx & TOP) == 0);
    }
    if ((divisor & 0xffffu) == 0)
    {
        do
        {
            divisor_high = (divisor_high << 1) | (divisor_low >> 31);
            divisor_low <<= 1;
            divisor = with_low(divisor, divisor - 1);
        } while ((divisor_high & TOP) == 0);
    }
    dividend = with_low(dividend, dividend - divisor + BIAS);
    const uint32_t exponent = dividend & 0xffffu;
    if ((exponent & 0x8000u) == 0 && exponent >= MAXIMUM)
    {
        return result(0, TOP, finish(with_low(divisor, MAXIMUM)));
    }
    if ((int16_t)exponent < SMALLEST)
    {
        return result(0, 0, finish(0));
    }
    /* The quotient's digits: q2 (the integer bit), q1 and q0. */
    uint32_t numerator_high = edx;
    uint32_t numerator_low = eax;
    uint32_t q2 = 0;
    if (!(divisor_high > numerator_high))
    {
        edx -= divisor_high;
        q2 = 1;
    }
    uint64_t pair = ((uint64_t)edx << 32) | numerator_low;
    uint32_t q1 = (uint32_t)(pair / divisor_high);
    {
        const uint64_t low = (uint64_t)divisor_low * q1;
        const uint64_t high = (uint64_t)divisor_high * q1 + (low >> 32);
        uint32_t t0 = (uint32_t)low;
        uint64_t t = high;
        if (q2 & 1)
        {
            t += ((uint64_t)divisor_high << 32) | divisor_low;
        }
        /* (numerator : 0) - (t : t0), 96 bits. */
        uint32_t r0 = 0u - t0;
        uint32_t borrow = t0 != 0;
        uint64_t middle = (uint64_t)numerator_low - (uint32_t)t - borrow;
        uint32_t r1 = (uint32_t)middle;
        borrow = (uint32_t)(middle >> 63);
        uint32_t r2 = numerator_high - (uint32_t)(t >> 32) - borrow;
        while (r2 != 0)
        {
            if (q1-- == 0)
            {
                q2--;
            }
            uint64_t add = (uint64_t)r0 + divisor_low;
            r0 = (uint32_t)add;
            add = (uint64_t)r1 + divisor_high + (add >> 32);
            r1 = (uint32_t)add;
            r2 += (uint32_t)(add >> 32);
        }
        numerator_high = r1;
        numerator_low = r0;
    }
    if (!(divisor_high > numerator_high))
    {
        numerator_high -= divisor_high;
        if (++q1 == 0)
        {
            q2++;
        }
    }
    pair = ((uint64_t)numerator_high << 32) | numerator_low;
    uint32_t q0 = (uint32_t)(pair / divisor_high);
    if (q0 != 0)
    {
        const uint64_t low = (uint64_t)divisor_low * q0;
        const uint64_t t = (uint64_t)divisor_high * q0 + (low >> 32);
        const uint32_t t0 = (uint32_t)low;
        uint32_t r0 = 0u - t0;
        uint32_t borrow = t0 != 0;
        uint64_t middle = (uint64_t)numerator_low - (uint32_t)t - borrow;
        uint32_t r1 = (uint32_t)middle;
        borrow = (uint32_t)(middle >> 63);
        uint32_t r2 = numerator_high - (uint32_t)(t >> 32) - borrow;
        while (r2 != 0)
        {
            if (q0-- == 0 && q1-- == 0)
            {
                q2--;
            }
            uint64_t add = (uint64_t)r0 + divisor_low;
            r0 = (uint32_t)add;
            add = (uint64_t)r1 + divisor_high + (add >> 32);
            r1 = (uint32_t)add;
            r2 += (uint32_t)(add >> 32);
        }
    }
    eax = q0;
    edx = q1;
    dividend = with_low(dividend, dividend - 1);
    if (q2 & 1)
    {
        eax = (eax >> 1) | (edx << 31);
        edx = (edx >> 1) | TOP;
        dividend += 1;
    }
    if ((int16_t)dividend <= 0)
    {
        const unsigned count = (dividend & 0xffffu) == 0 ? 1 : ((0u - dividend) & 0xffu);
        shift_right(&eax, &edx, count);
        dividend = with_low(dividend, 0);
    }
    return result(eax, edx, finish(dividend));
}

/* Original 0x4ee1e8 (0x4ee160 with the second sign turned, 0x4ee1e5 without): the sum. Infinities
 * and NaNs first (a NaN wins, the larger mantissa of two; infinities of opposite effective signs
 * are the indefinite NaN). A zero gives the other operand (+0 for two zeros). The smaller operand
 * is aligned (more than 64 bits apart, the larger is the sum), its bits shifted out kept as a
 * sticky dword; opposite signs subtract by complement. The sum is normalized left (to the
 * smallest exponent) or right on a carry, rounded by the first bit out and the sticky bits, and
 * overflows to infinity. */
VertrixExtended vertrix_extended_add(uint32_t eax, uint32_t edx, uint32_t ebx, uint32_t ecx,
                                     uint32_t esi, uint32_t negate)
{
    int special;
    const uint32_t first = esi & 0xffffu;
    if (first == 0xffffu || first == 0x7fffu)
    {
        /* 0x4ee16b: the first is infinite or NaN. */
        esi = add_flags(esi, 0x10000, &special);
        if (!special)
        {
            return result(eax, edx, esi);
        }
        esi -= 0x10000;
        if (eax == 0 && ebx == 0 && edx == TOP && ecx == edx)
        {
            const int same = (esi & 0xffffu) == (esi >> 16);
            if (same == (negate != 0))
            {
                return result(ebx, INDEFINITE, with_low(esi, 0xffff));
            }
            return result(ebx, edx, esi);
        }
        if (edx > ecx || (edx == ecx && eax > ebx) || (edx == ecx && eax == ebx && negate == 0))
        {
            return result(eax, edx, esi);
        }
        return result(ebx, ecx, esi >> 16);
    }
    esi = add_flags(esi, 0x10000, &special);
    if (special)
    {
        /* 0x4ee1c8: the second is infinite or NaN. */
        esi -= 0x10000;
        if (ebx == 0 && ecx == TOP)
        {
            esi ^= negate;
        }
        return result(ebx, ecx, esi >> 16);
    }
    esi -= 0x10000;
    esi ^= negate;
    if (eax == 0 && edx == 0 && ((esi << 1) & 0xffffu) == 0)
    {
        uint32_t word = (esi >> 16) << 1;
        if ((((ebx & 0xffff0000u) | ((ebx | word) & 0xffffu)) | ecx) != 0)
        {
            word >>= 1;
        }
        return result(ebx, ecx, word);
    }
    if (ecx == 0 && ebx == 0 && (esi & 0x7fff0000u) == 0)
    {
        return result(eax, edx, esi);
    }
    const uint32_t first_word = sign_exponent(esi);
    const uint32_t second_word = sign_exponent(esi >> 16);
    uint32_t larger = second_word;
    const uint32_t differ = (first_word ^ second_word) & TOP;
    uint32_t high = ecx; /* the operand with the larger exponent */
    uint32_t low = ebx;
    uint32_t distance = ((second_word & 0xffffu) - (first_word & 0xffffu)) & 0xffffu;
    if (distance != 0 && (second_word & 0xffffu) < (first_word & 0xffffu))
    {
        larger = first_word;
        distance = (0u - distance) & 0xffffu;
        high = edx;
        low = eax;
        edx = ecx;
        eax = ebx;
    }
    if (distance > 0x40)
    {
        return result(low, high, finish(larger));
    }
    uint32_t carry = 0; /* ch: 0, or 0xff for a subtraction */
    if (differ)
    {
        carry = 0xff;
        high = 0u - high - (low != 0);
        low = 0u - low;
        larger ^= TOP;
    }
    uint32_t sticky = 0;
    const unsigned count = distance & 0xffu;
    if (count != 0)
    {
        uint32_t out = 0;
        if (count >= 0x20)
        {
            sticky = eax != 0;
            if (count == 0x40)
            {
                sticky |= edx;
                edx = 0;
            }
            eax = edx;
            edx = 0;
        }
        if ((count & 31) != 0)
        {
            out = eax << (32 - (count & 31));
        }
        sticky |= out;
        shift_right(&eax, &edx, count);
    }
    {
        const uint64_t sum_low = (uint64_t)eax + low;
        const uint64_t sum_high = (uint64_t)edx + high + (sum_low >> 32);
        eax = (uint32_t)sum_low;
        edx = (uint32_t)sum_high;
        carry = (carry + (uint32_t)(sum_high >> 32)) & 0xffu;
    }
    if (carry & 0x80)
    {
        if (count == 0x40)
        {
            const uint32_t up = (sticky & 0x7fffffffu) != 0;
            const uint64_t sum_low = (uint64_t)eax + up;
            const uint64_t sum_high = (uint64_t)edx + (sum_low >> 32);
            eax = (uint32_t)sum_low;
            edx = (uint32_t)sum_high;
            carry = (carry + (uint32_t)(sum_high >> 32)) & 0xffu;
        }
        edx = 0u - edx - (eax != 0);
        eax = 0u - eax;
        carry = 0;
        larger ^= TOP;
    }
    if (((eax & 0xffffff00u) | ((eax | carry) & 0xffu) | edx) == 0)
    {
        return result(eax, edx, finish(0));
    }
    uint32_t exponent = larger & 0xffffu;
    if (exponent == 0)
    {
        return result(eax, edx, finish(larger));
    }
    if (carry == 0)
    {
        uint32_t in = sticky >> 31;
        for (;;)
        {
            exponent = (exponent - 1) & 0xffffu;
            if (exponent == 0)
            {
                return result(eax, edx, finish(with_low(larger, 0)));
            }
            const uint32_t out = edx >> 31;
            edx = (edx << 1) | (eax >> 31);
            eax = (eax << 1) | in;
            in = 0;
            if (out)
            {
                break;
            }
        }
    }
    exponent = (exponent + 1) & 0xffffu;
    if (exponent == MAXIMUM)
    {
        return result(0, TOP, finish(with_low(larger, MAXIMUM)));
    }
    uint32_t round = eax & 1;
    eax = (eax >> 1) | (edx << 31);
    edx = (edx >> 1) | TOP;
    if (round)
    {
        const uint32_t doubled = sticky << 1;
        const uint32_t up = doubled != 0 ? sticky >> 31 : (eax & 1);
        const uint64_t sum_low = (uint64_t)eax + up;
        const uint64_t sum_high = (uint64_t)edx + (sum_low >> 32);
        eax = (uint32_t)sum_low;
        edx = (uint32_t)sum_high;
        if (sum_high >> 32)
        {
            eax = (eax >> 1) | (edx << 31);
            edx = (edx >> 1) | TOP;
            exponent = (exponent + 1) & 0xffffu;
            if (exponent == MAXIMUM)
            {
                return result(0, TOP, finish(with_low(larger, MAXIMUM)));
            }
        }
    }
    return result(eax, edx, finish(with_low(larger, exponent)));
}

/* The dispatch entries: the operation on the registers, eax and edx back (their only callers,
 * 0x4edb48, 0x4edd24 and 0x4ee0dc, call the functions above for si). */
uint32_t vertrix_port_rtl_extended_multiply_4edc0e(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const VertrixExtended value =
        vertrix_extended_multiply(entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi);
    return port_return(&port, value.eax, value.edx);
}

uint32_t vertrix_port_rtl_extended_divide_4eddc4(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const VertrixExtended value =
        vertrix_extended_divide(&port, entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi);
    return port_return(&port, value.eax, value.edx);
}

uint32_t vertrix_port_rtl_extended_subtract_4ee160(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const VertrixExtended value =
        vertrix_extended_add(entry->eax, entry->edx, entry->ebx, entry->ecx, entry->esi, TOP);
    return port_return(&port, value.eax, value.edx);
}
