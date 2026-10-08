#ifndef VERTRIX_RTL_SINGLE_DIVIDE_H
#define VERTRIX_RTL_SINGLE_DIVIDE_H
#include "rtl_float.h"

/* Original 0x4d8227: exact software single divide over raw operand words. State EAX/EDX/EBX/ECX
 * receive original outputs, including division remainder and non-IEEE exponent/rounding rules.
 * Zero denominator calls 4e7280 with code 0x83; overflow calls 4dae94 then 4e7280 with code 0x84.
 * Those live register/global boundaries own callee effects and may not return when they raise.
 * Missing state or a required error boundary returns zero and preserves state. Success returns
 * one with outputs in state. This helper does not select or alter cached float helpers itself. */
int vertrix_rtl_single_divide_software_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                            void *context);
/* Original fragment 0x4d81fe: verified software dispatch, including lazy helper-cache selection
 * at divide sentinel 0x4d82bb. Supports cached 0x4d8227 or lazy software hardware-byte zero only.
 * Hardware dispatch is outside this convenience helper; use divide_full for masked hardware routes.
 * Unsupported dispatch or a missing required boundary returns zero preserving state. */
int vertrix_rtl_single_divide_software_entry(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                             void *context);
/* Original 0x4d81fe: complete normal single divide dispatch with exact EAX/EDX/EBX/ECX
 * outputs, lazy helper-cache selection and original software error boundaries.
 * Hardware routes 0x4d8204/0x4d8217 model both x87 rounding stages with integer division.
 * The capability helper 0x4e223c uses exact 15/16 operand scaling under masked precision64
 * before restoring caller control; its result matches this model for single operands.
 * Hardware requires masked x87 exceptions and precision 24/53/64. FPSW, x87 stack,
 * pending exceptions and unmasked traps are outside this register/cache model.
 * Arbitrary custom helper pointers and unsupported controls reject before committing state.
 * Missing state or required software error boundary returns zero; success returns one with
 * the original result in state EAX. The generic extended-input 0x4e223c ABI is not exposed. */
int vertrix_rtl_single_divide_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                   void *context);
#endif
