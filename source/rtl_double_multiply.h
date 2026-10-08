#ifndef VERTRIX_RTL_DOUBLE_MULTIPLY_H
#define VERTRIX_RTL_DOUBLE_MULTIPLY_H
#include "rtl_float.h"

/* Original 0x4db507: multiply EDX:EAX by ECX:EBX. The shared state carries four
 * input/output registers, hardware byte 0x5054a1 and x87 control. Cache fields are
 * untouched. Software reproduces original mantissa arithmetic, scratch-register
 * outputs, masked shift counts and overflow calls 0x4dae94/0x4e7280. Hardware
 * supports masked exceptions, precision 24/53/64 and all rounding controls, with
 * original double-store rounding and its high-word-only negative-zero cleanup.
 * No host floating arithmetic is used. x87 status/environment and unmasked traps
 * are excluded. Unsupported arithmetic or a missing required error boundary fails
 * without changing state. Signed-zero fast paths precede mode validation. */
int vertrix_rtl_double_multiply_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                     void *context);
#endif
