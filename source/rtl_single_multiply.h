#ifndef VERTRIX_RTL_SINGLE_MULTIPLY_H
#define VERTRIX_RTL_SINGLE_MULTIPLY_H
#include "rtl_float.h"

/* Original 0x4d8177: single multiplication, including positive-zero early return,
 * lazy helper initialization and exact software helper 0x4d8198 register arithmetic.
 * The software overflow tail calls the shared error boundary with live registers.
 * Hardware helper 0x4d8188 supports masked exceptions, precision 24/53/64 and all four
 * rounding controls, including its final store to single. x87 status/environment and
 * unmasked traps are outside the proven API scope. No host floating arithmetic is used.
 * Return one with original register/cache outputs in state. Unsupported helpers/modes
 * or missing required error boundary return zero and preserve state. */
int vertrix_rtl_single_multiply_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                     void *context);
/* The same once the helper cache holds the software helper 0x4d8198: the original's register
 * outputs in state. Returns zero, the state unchanged, where the result overflows and needs the
 * error boundary. */
int vertrix_rtl_single_multiply_software(VertrixRtlFloatState *state);

/* The arithmetic of the software helper 0x4d8198 on the nonzero singles a and b, with the sign
 * flags it keeps in ecx: 1 with the product in *eax and the edx it leaves in *edx; 0 where the
 * product overflows, with the eax and edx its error tail starts from. */
static inline int vertrix_rtl_single_multiply_values(uint32_t a, uint32_t b, uint32_t ecx,
                                                     uint32_t *eax, uint32_t *edx)
{
    uint32_t flags = vertrix_rtl_rotate(ecx * 2u + (a >> 31) + (b >> 31), 31);
    a = vertrix_rtl_rotate(a << 1, 8);
    b = vertrix_rtl_rotate(b << 1, 8);
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
            *eax = 0;
            *edx = b;
            return 1;
        }
        *eax = flags;
        *edx = b;
        return 0;
    }
    if ((int8_t)sum <= -127)
    {
        *eax = 0;
        *edx = b;
        return 1;
    }
    uint8_t exponent = (uint8_t)(sum + 128u);
    flags = (flags & 0xffffff00u) | exponent;
    a = 0x80000000u | ((a & 0xffffff00u) >> 1);
    b = 0x80000000u | ((b & 0xffffff00u) >> 1);
    uint64_t product = (uint64_t)a * b;
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
        *eax = flags;
        *edx = b;
        return 0;
    }
    b = vertrix_rtl_rotate((b << 9) | exponent, 24);
    b = (flags & 0x80000000u) | (b >> 1);
    *eax = b;
    *edx = b;
    return 1;
}

/* vertrix_rtl_single_multiply_software on registers: the zero early return, then 0x4d8198. Returns
 * zero, *eax and *edx unchanged, where the product overflows. */
static inline int vertrix_rtl_single_multiply_quick(uint32_t eax, uint32_t edx, uint32_t ecx,
                                                    uint32_t *out_eax, uint32_t *out_edx)
{
    uint32_t a, b;
    if (!eax || !edx)
    {
        *out_eax = 0;
        *out_edx = edx;
        return 1;
    }
    if (!vertrix_rtl_single_multiply_values(eax, edx, ecx, &a, &b))
    {
        return 0;
    }
    *out_eax = a;
    *out_edx = b;
    return 1;
}
#endif
