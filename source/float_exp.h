#ifndef VERTRIX_FLOAT_EXP_H
#define VERTRIX_FLOAT_EXP_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The storage the exponential uses besides its registers: the integer part the split leaves at
 * frame - 0x34 (8 bytes: the services resolve frame - VERTRIX_FLOAT_EXP_FRAME to their storage),
 * the flag byte at 0x5054a1 (hardware path when non-zero) and the table of four doubles at
 * 0x51ab70 (resolved by their handles). */
enum
{
    VERTRIX_FLOAT_EXP_FRAME = 0x34,
    VERTRIX_FLOAT_EXP_FRAME_SIZE = 8,
    VERTRIX_FLOAT_EXP_FLAG = 0x5054a1,
    VERTRIX_FLOAT_EXP_TABLE = 0x51ab70,
    VERTRIX_FLOAT_EXP_TABLE_SIZE = 0x20
};

/* Original 0x4daed8 (edx:eax = x, ebx and ecx the caller's; `frame` is the token for ebp): e to
 * the x, through the float helpers 0x4dae62 (absolute value), 0x4eb57c (compare, the answer's sign
 * standing for the flags the original tests), 0x4db507 (multiply), 0x4db350 (add), 0x4db34a
 * (subtract), 0x4eb652 (divide), 0x4e5271 (scale by a power of two: ebx the exponent), 0x4dae1e
 * (split into integer and fractional parts: the integer part comes back at frame - 0x34), 0x4eb892
 * (to integer), 0x4dad19 (no arguments) and 0x4dad2e (error raise); double results come back in
 * eax and the call's out_value (edx). |x| below 0x3cc003c9f368cb40 answers 1.0; above 0x40862e42
 * fefa39ef it answers zero for a negative x and raises 0x8104 (answering its result) otherwise.
 * With the flag byte set 0x4e51c8 computes it. Otherwise x * log2(e) (0x3ff71547652b8301) is
 * split, a negative power flips the fraction (1 - f, one less for the integer part when the high
 * dword of the fraction is not zero), the fraction is scaled by 16 and split again to give a
 * nibble, a rational approximation (1 + ... over 1 - ...) of the remaining fraction is multiplied
 * by the table entry of each set bit of the nibble and finally scaled by 2^n. *result is edx:eax.
 * Returns zero when memory cannot be accessed. */
int vertrix_float_exp(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t frame, uint32_t low, uint32_t high, uint32_t ebx, uint32_t ecx,
                      uint64_t *result);

#endif
