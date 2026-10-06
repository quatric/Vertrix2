#ifndef VERTRIX_MARKER_ACTOR_H
#define VERTRIX_MARKER_ACTOR_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Original 0x465a70 (eax = x, dx = y, ebx = frame the caller's registers): 0x4ca000(0x15c)
 * allocates the actor, a non-zero result going through 0x4abd70 (edx, ebx and ecx = x kept);
 * 0x4adf20 (five zero stack arguments) places it at the sign extended x and y, 0x4ac8d0 binds the
 * resource 0x544a18, 0x4ac710 and 0x4ac8a0 select the frame, the bytes +0x93 and +0x95 are set
 * to one, +0x4e to zero, the word +0x48 to 0xffd8 and 0x4b5e70 registers it with the list
 * 0x54671c. Returns the eax of 0x4b5e70, zero when the actor does not resolve. */
uint32_t vertrix_marker_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t x, uint32_t y, uint32_t frame);
#endif
