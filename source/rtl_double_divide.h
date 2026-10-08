#ifndef VERTRIX_RTL_DOUBLE_DIVIDE_H
#define VERTRIX_RTL_DOUBLE_DIVIDE_H
#include "rtl_float.h"
/* Original 0x4eb652: double division with denominator/numerator zero paths, exact software
 * quotient arithmetic and masked hardware PC24/53/64 rounding. State contains original
 * EAX/EDX/EBX/ECX outputs; callback models error callees. Unmasked traps and x87 status/environment
 * are outside the boundary. Unsupported modes or missing error callback preserve state. */
int vertrix_rtl_double_divide_full(VertrixRtlFloatState *state, VertrixRtlFloatCall call,
                                   void *context);
#endif
