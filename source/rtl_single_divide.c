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
