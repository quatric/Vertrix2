#ifndef VERTRIX_PITCH_CURVE_H
#define VERTRIX_PITCH_CURVE_H
#include <stdint.h>

enum
{
    VERTRIX_PITCH_BASE_RATE = 8363,
    VERTRIX_PITCH_SHIFT = 15,
    VERTRIX_PITCH_LIMIT = 0x1000
};

/* Original0x410150: fixed point logarithm of a rate relative to 8363 Hz. All arithmetic is 32-bit
 * signed with rounding (+0x400 before each shift by 11): the value (rate << 15) / 8363 is halved
 * (rounded up) while above 0x1000, adding 0x6000 to the exponent each time (starting at
 * 0xfffe8000); a cubic polynomial of the reduced value is added to the exponent and the sum is
 * shifted right by 4. */
int32_t vertrix_pitch_curve(uint32_t rate);
#endif
