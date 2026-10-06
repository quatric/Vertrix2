#ifndef VERTRIX_FLOAT_SPLIT_H
#define VERTRIX_FLOAT_SPLIT_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The two doubles the split works on (the 0x10 bytes below the frame: the integer part at the
 * bottom, the value and then its fractional part at frame - 8): the services resolve
 * frame - VERTRIX_FLOAT_SPLIT_FRAME to their storage. */
enum
{
    VERTRIX_FLOAT_SPLIT_FRAME = 0x10,
    VERTRIX_FLOAT_SPLIT_FRAME_SIZE = 0x10
};

/* Original 0x4dae1e (edx:eax = the double, ebx = pointer for the integer part, ecx the caller's;
 * `frame` is the token for ebp): the double is stored at frame - 8 and 0x4e509c (eax = frame - 8,
 * edx = frame - 0x10, ebx, ecx) splits it: the integer part at frame - 0x10 is stored through ebx
 * (two dwords) and the fractional part, now at frame - 8, is returned. *result is edx:eax. Returns
 * zero when memory cannot be accessed. */
int vertrix_float_split(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t low, uint32_t high, uint32_t destination,
                        uint32_t ecx, uint64_t *result);

#endif
