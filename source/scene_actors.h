#ifndef VERTRIX_SCENE_ACTORS_H
#define VERTRIX_SCENE_ACTORS_H
#include <stdint.h>

#include "actor_build.h"

/* Original 0x471340 (edx, ebx and ecx the caller's registers, which reach the allocator and the
 * wrapper). The delay is 180 times the dword 0x53bdac[dword 0x532a64] plus 0x1388. 0x4ca000(0x15c)
 * allocates the actor, a non-zero result going through 0x4abd70; 0x4adf20 initialises it, 0x4ac8f0
 * sets the handler 0x457770, 0x4ac7d0 the delay, the dword +0 = 0xc8 and 0x4b5e70 registers it
 * with the list 0x54671c. Returns the eax of 0x4b5e70, zero when the actor does not resolve. */
uint32_t vertrix_delay_actor_spawn(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t edx, uint32_t ebx,
                                   uint32_t ecx);

/* Original 0x472620 (the registers as above). 0x4ca000(0x15c) allocates the actor, a non-zero
 * result going through 0x4abd70; 0x4adf20 places it at x = 0x140 and y = 0xf0, the dword +0 is
 * 0x13, 0x4ac8d0 binds resource 0x544a34, 0x4ac710 selects the frame held in the dword 0x532a68,
 * 0x4ac8a0 and 0x4ac7b0 receive 0x46, the byte +0x4e is 0x64, +0x93 is 0, the dword +0x150 is 1,
 * 0x4ac8f0 sets the handler 0x45ad20 and 0x4b5e70 registers it with the list 0x54671c. Returns
 * the eax of 0x4b5e70, zero when the actor does not resolve. */
uint32_t vertrix_banner_actor_spawn(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t edx, uint32_t ebx,
                                    uint32_t ecx);
#endif
