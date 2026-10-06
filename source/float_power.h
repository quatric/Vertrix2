#ifndef VERTRIX_FLOAT_POWER_H
#define VERTRIX_FLOAT_POWER_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The stack locals the power routine keeps (the 0x1c bytes from frame - 0x24 up to frame - 8: x at
 * -0x24, the split or working double at -0x1c, y at -0x14 and the integer exponent at -0xc), which
 * its callees also read and write through pointers: the services resolve
 * frame - VERTRIX_FLOAT_POWER_FRAME to their storage. */
enum
{
    VERTRIX_FLOAT_POWER_FRAME = 0x24,
    VERTRIX_FLOAT_POWER_FRAME_SIZE = 0x1c
};

/* Original 0x4c9921 (edx:eax = x, ecx:ebx = y; `frame` is the token for ebp): x to the power y
 * through the float helpers 0x4dad19 (classification of the arguments, no register arguments),
 * 0x4dae1e (split y into the integer part, at frame - 0x1c, and the fraction), 0x4eb892 (to
 * integer), 0x4dae4a (negate), 0x4c9e2f (logarithm), 0x4db507 (multiply), 0x4dae62 (absolute
 * value), 0x4eb57c (compare, the answer's sign standing for the flags), 0x4daed8 (exponential),
 * 0x4eb652 (divide), 0x4dad38 (error raise) and 0x4dae94 (underflow). A zero classification raises
 * 0x8047 for a negative y high dword, 0x4047 for a zero one and answers x otherwise. Otherwise the
 * integer part of y is found; a negative classification (x below zero) with a non-integer y raises
 * 0x2047, with an integer y negates x and remembers whether the exponent is odd. The logarithm of x
 * times y beyond +-709.78 raises (0x8107 or 0x1107) for a positive product, or underflows to zero;
 * a non-integer y (or an exponent of 0x80000000) is the exponential of the product; an integer
 * exponent is computed by repeated squaring (a negative one inverts x first); an odd exponent
 * with a negative x negates the result. *result is edx:eax. Returns zero when memory cannot be
 * accessed. */
int vertrix_float_power(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t x_low, uint32_t x_high, uint32_t y_low,
                        uint32_t y_high, uint64_t *result);

#endif
