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
#endif
