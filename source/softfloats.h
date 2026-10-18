#ifndef SOFTFLOATS_H
#define SOFTFLOATS_H
#include "port.h"

/* Clean ports of the runtime's software floating point helpers (port.h). The port has no x87, so
 * the runtime's emulation runs (lift_runtime.h, lift_x87). A double is passed in two registers,
 * the high dword (sign, exponent, top of the mantissa) in edx or ecx and the low one in eax or
 * ebx. */

/* Original 0x4eb57c: compare the double edx:eax with ecx:ebx. A high dword with a zero exponent
 * counts as zero (its low dword is still compared). Returns -1, 0 or 1 in eax and in the flags:
 * equal leaves the flags of cmp eax, ebx; otherwise those of inc on -2 or 0 (zf and of clear, sf
 * for -1) with cf set for -1. edx is left shifted as the routine leaves it. */
uint32_t vertrix_port_double_compare(PORT_SIGNATURE);

/* Original 0x4eb526: the single in eax as a double in edx:eax. Zero keeps eax (its sign) with edx
 * 0; infinity becomes edx = eax | 0x7ff00000 and eax 0; a denormal is normalized first. */
uint32_t vertrix_port_single_to_double(PORT_SIGNATURE);

/* Original 0x4d67f0: the single in eax truncated to an unsigned integer, cl the exponent at which
 * it saturates (the result is then 0xffffffff >> (0x9f - cl)); below 1 is 0. The sign is ignored.
 * edx is unchanged. */
uint32_t vertrix_port_float_to_integer(PORT_SIGNATURE);

/* Original 0x4d67e4: as 0x4d67f0 for a non-negative eax; a negative one is handed to 0x4d67f0 by a
 * call and its result negated. */
uint32_t vertrix_port_float_to_signed(PORT_SIGNATURE);

/* Original 0x4d67a8: 0x4d67e4 with cl = 0x9e (saturating at 0x7fffffff). */
uint32_t vertrix_port_float_to_int32(PORT_SIGNATURE);

/* Original 0x4d6768: the signed integer in eax as a double in edx:eax (0 gives 0:0). */
uint32_t vertrix_port_int_to_double(PORT_SIGNATURE);

/* Original 0x4dae62: the absolute value of the double edx:eax (the sign bit of edx cleared). */
uint32_t vertrix_port_double_absolute(PORT_SIGNATURE);

/* Original 0x4dad19: the sign of the double edx:eax from its high dword alone: 0 when edx is 0,
 * -1 when it is negative and 1 otherwise. edx is unchanged. */
uint32_t vertrix_port_double_sign(PORT_SIGNATURE);

/* Original 0x4eb5b4: the single in eax negated (0 stays 0, -0 becomes 0). edx is unchanged. */
uint32_t vertrix_port_single_negate(PORT_SIGNATURE);

/* Original 0x4eb606: the double edx:eax as a single, rounded at the 24th bit (adding 1 << 28 to
 * the shifted mantissa). A zero exponent gives 0; too small 0 and too large infinity with the
 * sign. edx is the shifted, rounded high dword (or the result, or unchanged for a zero exponent).
 */
uint32_t vertrix_port_double_to_single(PORT_SIGNATURE);

/* Original 0x4eb892: the double edx:eax truncated toward zero to a signed integer. Below 0.5 in
 * magnitude gives 0 and 2^31 or more 0x80000000. The routine's rounding step (shared with the
 * entry at 0x4eb896) is masked off by this entry's al = 0x1f. edx is the shifted mantissa it
 * leaves (the high dword without its sign on the early returns). */
uint32_t vertrix_port_double_to_int(PORT_SIGNATURE);

/* Original 0x4d74a6: the unsigned integer in eax as a single, the bits below the 24 kept
 * truncated (0 gives 0). edx is unchanged. */
uint32_t vertrix_port_unsigned_to_single(PORT_SIGNATURE);

/* Original 0x4d74d1: the signed integer in eax as a single: a negative one is negated, handed to
 * 0x4d74a6 by a call and given the sign bit. */
uint32_t vertrix_port_signed_to_single(PORT_SIGNATURE);

/* Original 0x4e5177 (edx:eax = mantissa bits, edi = exponent field): normalize the mantissa so
 * its leading one is bit 20 of the high dword, moving the exponent field (in units of 0x100000)
 * with it; a right shift rounds up on the last bit shifted out. Returns the double edx:eax, the
 * high dword's top 12 bits the exponent field (0:0 for a zero mantissa). */
uint32_t vertrix_port_double_normalize(PORT_SIGNATURE);

/* Original 0x4e509c (eax = address of a double, edx = address for its integer part): split the
 * double. The integer part (the double with its fraction bits cleared, 0 below 1 or for a zero
 * exponent, the whole double from 2^52) goes to edx's address; the fraction, normalized by
 * 0x4e5177 (edi the exponent field, ecx the exponent less 0x3ff, minus 21 above 20) and given the
 * sign when not 0, replaces the double. Returns the fraction as edx:eax (0 with edx the high dword
 * when the fraction is 0 without a call). */
uint32_t vertrix_port_double_split(PORT_SIGNATURE);

/* Original 0x4dae1e (edx:eax = double, ebx = address for the integer part): 0x4e509c on a copy in
 * its frame. Returns the fraction as edx:eax and stores the integer part at ebx. */
uint32_t vertrix_port_double_split_call(PORT_SIGNATURE);

/* Original 0x4e5271 (edx:eax = double, ebx = power of two): the double scaled by 2^ebx, the power
 * clamped to [-16000, 16000]. A zero high dword returns the double; an exponent at or below 0 gives
 * 0:0; one of 0x7ff or more calls 0x4dae94 (eax the exponent, ecx the high dword's top 16 bits
 * under the entry ecx's low 16) and returns the infinity at 0x51ab90, negated by 0x4dae4a when the
 * top 16 bits are not positive. */
uint32_t vertrix_port_double_scale(PORT_SIGNATURE);

/* Original 0x4db1fd (edx:eax = double, ebx = address for the exponent): frexp. The exponent less
 * 0x3fe is stored (0 when the high dword is 0) and the double is returned with its exponent field
 * 0x3fe (the high dword unchanged when 0). */
uint32_t vertrix_port_double_exponent_split(PORT_SIGNATURE);

/* Original 0x4db6a4 (edx:eax = x, ebx = coefficients, ecx = count): Horner's rule: from the first
 * coefficient, count times multiply by x (0x4db507) and add the next coefficient (0x4db350).
 * Returns the double edx:eax. */
uint32_t vertrix_port_double_polynomial(PORT_SIGNATURE);

/* Original 0x4d67b2: 0x4d67e4 with cl = 0x9f (saturating at 0xffffffff). */
uint32_t vertrix_port_float_to_uint32(PORT_SIGNATURE);

/* Original 0x4db34a: the double edx:eax minus ecx:ebx: ecx's sign flipped, then the add 0x4db350.
 * A zero operand (its low dword 0 and its high one 0 or 0x80000000) returns the other. With the
 * coprocessor (0x5054a1) it adds with fadd, which this platform does not have (lift_x87). In
 * software the mantissas get their hidden bits and one guard bit; the smaller is shifted right by
 * the exponent difference (more than 0x36 returns the larger), the bits shifted out kept as
 * sticky bits; a negative sum is negated, rounded up first when the shift was 0x35 or more and a
 * sticky bit other than the top one is set. The sum is normalized, rounded to nearest even and
 * packed; an exponent reaching 0 gives the denormal unrounded, one reaching 0x7ff jumps to
 * 0x4e2389 with eax = sign and exponent, edx the high mantissa, ebx the rounding scratch and ecx
 * the sign difference and shift. */
uint32_t vertrix_port_double_subtract(PORT_SIGNATURE);

/* Original 0x4c9e2f: log of the double edx:eax. A high dword of 0 or below goes to the math error
 * 0x4db866 (ebx = 0xa); with the coprocessor (0x5054a1) to 0x4db896. Otherwise frexp (0x4db1fd,
 * the exponent e in the frame at ebp - 0x24) gives m. Above sqrt(1/2) (0x4eb57c) f = m - 0.5 - 0.5
 * and x = m; otherwise e is lowered and f = x = m - 0.5. z = f / (x * 0.5 + 0.5), w = z * z and
 * r = f + z * w * P(w) / Q(w) (0x4db6a4 on 0x518830 and 0x518848); a non-zero e adds
 * e * -2.12e-4 and e * 0.693359375. Every helper is called with the registers the original leaves
 * in it: the caller's ebx and ecx carry over a call. */
uint32_t vertrix_port_log(PORT_SIGNATURE);

/* Original 0x4daed8: e to the edx:eax, as recovered in float_exp.h, written call by call: x and
 * the working value at ebp - 0x3c (handed to the error raise 0x4dad2e), the integer parts at
 * ebp - 0x34 (0x4dae1e). |x| below 0x3cc003c9f368cb40 gives 1; above 0x40862e42fefa39ef 0 for a
 * negative x, else 0x4dad2e with 0x8104; the coprocessor (0x5054a1) hands it to 0x4e51c8.
 * Otherwise x * log2(e) is split, the fraction scaled by 16 and split again into a nibble, the
 * rational approximation (P + Q) / (Q - P) is multiplied by the table 0x51ab70 entry of each set
 * bit of the nibble and scaled by 2^n (0x4e5271). Every helper gets the registers the original
 * leaves in it. */
uint32_t vertrix_port_exp(PORT_SIGNATURE);

/* Original 0x4c9921: edx:eax (x) to the power ecx:ebx (y), x at ebp - 0x24 and y at ebp - 0x14
 * handed to the error raise 0x4dad38. x = 0 (0x4dad19) gives 0 for y > 0, else raises 0x8047
 * (y < 0) or 0x4047. y is split (0x4dae1e) into n (0x4eb892) and a fraction; a negative x with a
 * fraction raises 0x2047 (its result returned as is), otherwise x is negated and the result's sign
 * kept for an odd n. y * log(x) (0x4c9e2f) beyond 0x40862e42fefa39ef in magnitude gives 0
 * (through 0x4dae94 with ecx = 0) when negative, else raises 0x8107 (a positive sign) or 0x1107.
 * A fraction or n = 0x80000000 takes exp (0x4daed8); otherwise x^n by squaring (1/x first for a
 * negative n). Every helper gets the registers the original leaves in it. */
uint32_t vertrix_port_power(PORT_SIGNATURE);

/* Original 0x4c9b6a (edx:eax = x, ebx = 0 sine, 1 tangent, 2 cosine): the trigonometric core. An
 * exponent (0x4db1fd) of 0x20 or more raises 0x4dad2e with entry ebx of 0x518824 | 0x2400. x is
 * reduced by pi/4 (0x4db250, stack arguments: the octant at ebp - 0x28, the rest at ebp - 0x34),
 * the octant moved by 2 for the cosine; an odd octant takes pi/4 - r. The exponent of r picks the
 * series length (0x518800); the cosine series (0x4db6a4 on 0x5187b8) and the sine series (0x4db6d9
 * on 0x518770) run as the octant and the kind need, below 2^-26 r and 1 stand in. Octant bit 4
 * negates; the tangent divides by the other series (0 gives the signed infinity 0x51ab90 after
 * 0x4dae94). An exponent of 0x1c or more raises 0x4dad38 with 0x200. Every helper gets the
 * registers the original leaves in it. */
uint32_t vertrix_port_trig(PORT_SIGNATURE);

/* Original 0x4db250 (stack: a, b, int *quotient, double *remainder; registers kept): the
 * remainder of a by b with the low bits of the quotient. b's high dword 0 gives 0 and 0. Both
 * mantissas get the hidden bit (a denormal's too); an exponent of a below b's leaves a as the
 * remainder. Otherwise long division, one quotient bit per exponent step: a doubled past 2^53
 * subtracts without comparing, below 2^52 shifts in a 0. A non-zero remainder is normalized at
 * b's exponent; a's sign is set unless the high dword is 0, and the quotient is negated when the
 * signs differ. */
uint32_t vertrix_port_double_remainder(PORT_SIGNATURE);

/* Original 0x4db6d9 (edx:eax = x, ebx = coefficients, ecx = count): x * P(x * x) with 0x4db6a4
 * on the coefficients (the odd series of the sine). */
uint32_t vertrix_port_double_polynomial_odd(PORT_SIGNATURE);

#endif
