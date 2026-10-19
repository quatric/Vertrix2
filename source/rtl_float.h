#ifndef VERTRIX_RTL_FLOAT_H
#define VERTRIX_RTL_FLOAT_H
#include <stdint.h>

/* Register outputs and the three cached helpers selected by the original initializer.
 * helper/add, multiply and divide are globals 503ea0/503ea4/503ea8. hardware is byte 5054a1,
 * capability is byte 508798 and control is the x87 control word. */
typedef struct VertrixRtlFloatState
{
    uint32_t eax, edx, ebx, ecx;
    uint32_t helper, multiply, divide;
    uint32_t hardware, capability, control;
} VertrixRtlFloatState;

/* Actual software overflow calls 4dae94 (thread error record) then 4e7280 (error code 84).
 * The boundary receives and returns live registers; it owns callee effects and may not return
 * when the original error handler raises. */
typedef void (*VertrixRtlFloatCall)(uint32_t target, VertrixRtlFloatState *registers,
                                    void *context);

/* Original 0x4d809c: single subtraction, including zero fast paths, software bit arithmetic,
 * masked x87 arithmetic, EDX outputs and lazy helper-cache selection. The supplied state models
 * register/global inputs. Hardware supports masked exceptions and precision controls 24/53/64;
 * x87 status/environment and unmasked traps remain outside this API's proven scope. Unsupported
 * modes or missing required overflow boundary return zero and preserve state. On success, return
 * one with original register outputs in state. No host floating arithmetic is used. */
int vertrix_rtl_single_subtract_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                     void *context);
/* Original 0x4d80a6: the same addition entry, without subtraction's initial EDX sign toggle. */
int vertrix_rtl_single_add_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                void *context);
/* The same entries (subtract nonzero for 0x4d809c) once the helper cache holds the software
 * helper 0x4d80d5: the registers of the original's outputs in state, its cached helpers untouched.
 * Returns zero, the state unchanged, where the result overflows and needs the error boundary. */
int vertrix_rtl_single_add_software(VertrixRtlFloatState *state, int subtract);

static inline uint32_t vertrix_rtl_rotate(uint32_t value, unsigned shift)
{
    return (value << shift) | (value >> (32 - shift));
}

/* The arithmetic of the software add helper 0x4d80d5 on the nonzero singles a and b: 1 with the
 * sum in *eax and the edx it leaves in *edx; 0 where the sum overflows, with the eax and edx its
 * error tail starts from. */
static inline int vertrix_rtl_single_add_values(uint32_t a, uint32_t b, uint32_t *eax,
                                                uint32_t *edx)
{
    uint8_t signs = (uint8_t)((a >> 31) * 5 + (b >> 31));
    a = vertrix_rtl_rotate(a << 1, 8);
    b = vertrix_rtl_rotate(b << 1, 8);
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
                *eax = ((uint32_t)(signs & 1) << 31) | (a >> 1);
                *edx = b;
                return 0;
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
                *eax = 0;
                *edx = b;
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
                *eax = 0;
                *edx = b;
                return 1;
            }
        }
    }
    a = (a & 0xffffff00u) | exponent;
    a = vertrix_rtl_rotate(a, 24);
    *eax = ((uint32_t)(signs & 1) << 31) | (a >> 1);
    *edx = b;
    return 1;
}

/* vertrix_rtl_single_add_software on registers: the zero early returns, then 0x4d80d5. Returns
 * zero, *eax and *edx unchanged, where the sum overflows. */
static inline int vertrix_rtl_single_add_quick(uint32_t eax, uint32_t edx, int subtract,
                                               uint32_t *out_eax, uint32_t *out_edx)
{
    uint32_t a, b;
    if (subtract && edx)
    {
        edx ^= 0x80000000u;
    }
    if (!edx || !eax)
    {
        *out_eax = eax ? eax : edx;
        *out_edx = edx;
        return 1;
    }
    if (!vertrix_rtl_single_add_values(eax, edx, &a, &b))
    {
        return 0;
    }
    *out_eax = a;
    *out_edx = b;
    return 1;
}

#endif
