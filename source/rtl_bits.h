#ifndef VERTRIX_RTL_BITS_H
#define VERTRIX_RTL_BITS_H
#include <stdint.h>

/* Original 0x4eb5b4: toggle the single-precision sign bit when EAX is nonzero.
 * Positive zero remains zero; negative zero becomes positive zero. The operation treats all
 * other bit patterns, including infinities and NaNs, identically. Original EDX is unchanged.
 * This API exposes EAX; arithmetic flags remain the responsibility of the lifted caller. */
uint32_t vertrix_rtl_single_negate(uint32_t bits);
#endif
