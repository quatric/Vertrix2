#ifndef VERTRIX_SLIDE_PAIR_H
#define VERTRIX_SLIDE_PAIR_H
#include <stdint.h>

#include "actor_build.h"

/* Original 0x4711a0 (eax = value). Two actors are built and registered with the list 0x54671c.
 * Each is 0x4ca000(0x15c) (edx = 0x4ec1ec, ebx = 0, ecx = 0x516248 for the first; the registers
 * the previous call left for the second) through 0x4abd70 (ecx = 3 for the second), 0x4adf20,
 * 0x4ac490 (value), 0x4ac7b0 (1), the dword +0 = 0x15 or 0x16, 0x4ac8d0 (resource 0x544d44 or
 * 0x544d60), 0x4ac710 (0), the word +0xe from the word 0x4f8a48 or 0x4f8a50, the word +0x16 from
 * the word 0x4f8a4c or 0x4f8a54 plus 0x108, 0x4ac8f0 (handler 0x44c860) and 0x4b5e70. The
 * original returns the saved exception chain head; this returns one, zero when an actor does
 * not resolve. */
int vertrix_slide_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       const VertrixGlobals *globals, uint32_t value);
#endif
