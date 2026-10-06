#ifndef VERTRIX_PANEL_ACTOR_H
#define VERTRIX_PANEL_ACTOR_H
#include <stdint.h>

#include "actor_build.h"

/* Original 0x471020 (eax = text, edx, ebx and ecx the caller's registers, which reach the
 * allocator). 0x4ca000(0x308) allocates the panel, a non-zero result going through 0x4b2400;
 * 0x4adf20 initialises it and 0x4b25b0 (edx = text, ebx = the glyph byte of 0x4f9bff, ecx = the
 * word 0x4f8800) lays it out with ten stack arguments, nearest first: the words 0x4f8804 and
 * 0x4f8808 (sign extended high halves of the dwords at 0x4f8802 and 0x4f8806), the word 0x4f880c
 * minus 0xe, 2, 2, 0, 0, 1, 1, 1. 0x4b2d90 then measures it and a non-zero panel receives the
 * virtual call [[+0x158]] with edx = 2. Returns the eax of 0x4b2d90. */
uint32_t vertrix_panel_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, uint32_t text, uint32_t edx,
                             uint32_t ebx, uint32_t ecx);
#endif
