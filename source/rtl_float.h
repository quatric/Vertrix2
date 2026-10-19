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
#endif
