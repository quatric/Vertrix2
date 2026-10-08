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
 * Hardware helpers 0x4d8204/0x4d8217, capability helper 0x4e223c, x87 state/traps remain
 * unverified. Unsupported dispatch or a missing required boundary returns zero preserving state. */
int vertrix_rtl_single_divide_software_entry(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                             void *context);
#endif
