#ifndef VERTRIX_TITLE_LETTER_H
#define VERTRIX_TITLE_LETTER_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Original 0x4713d0 and 0x4715a0 (eax = mode; `frame` is the token for ebp): make one letter
 * actor. 0x4ca070 initialises a local string (frame - 0x20), 0x4ca000 and (when it answers)
 * 0x4abd70 (with 2) make the actor, 0x4cdfb0 (cdecl; local, the text 0x50e62c or 0x50e630, 3)
 * copies the text into the local (the string pointer comes back in out_value) and the dword at +4
 * becomes 2 for mode 1, otherwise 1. The position is the dword pair of the globals 0x4f8a48
 * (mode 1) or 0x4f8a50 plus 0x3c and 0x9c. The first character is mapped (0x43f420 with the
 * signed byte at 0x4f9c02) and given to 0x4ac950 and 0x4ac8a0; the words and bytes at +0xc, +0x52
 * (0x4715a0 only, 3), +0x94, +0x95, +0x93, +0x4e, +8, +0xa, +0x16, +0xe, +0x30, +0x24, +0x28,
 * +0x32 and the dwords +0x58, +0x5c and +0x60 are set around 0x4ac8f0 (handler 0x459be0), 0x4ad510
 * (bounds from the dwords at +6 and +8), 0x4ac7d0, 0x4ac510 and 0x4b5e70 (list 0x54671c), and
 * 0x4ca210 releases the local. The services resolve the globals and the string header. */
enum
{
    VERTRIX_TITLE_FIRST_GLOBALS = 0x4f8a48,
    VERTRIX_TITLE_SECOND_GLOBALS = 0x4f8a50
};

int vertrix_title_letter_first(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               uint32_t frame, uint32_t mode);
int vertrix_title_letter_second(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t frame, uint32_t mode);

#endif
