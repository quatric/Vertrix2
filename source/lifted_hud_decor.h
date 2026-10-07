#ifndef VERTRIX_LIFTED_HUD_DECOR_H
#define VERTRIX_LIFTED_HUD_DECOR_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_HUD_DECOR_LOCALS = 76
};

/* The original routine 0x46b810 lifted instruction by instruction (see tools/lift.py). `frame` is
 * the token for ebp, eax/edx/ebx/ecx the entry registers, `arguments` the stack dwords above the
 * return address, `garbage` the LIFTED_HUD_DECOR_LOCALS bytes of stack below ebp the routine may
 * read before it writes them and `chain` the value of fs:[0] at entry (the routine returns it). */
uint32_t lifted_hud_decor(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, uint32_t frame, uint32_t eax, uint32_t edx,
                          uint32_t ebx, uint32_t ecx, const uint32_t *arguments,
                          const uint8_t *garbage, uint32_t chain);
#endif
