#ifndef VERTRIX_LIFTED_SELECT_SCREEN_H
#define VERTRIX_LIFTED_SELECT_SCREEN_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_SELECT_SCREEN_LOCALS = 92
};

/* The original routine 0x466d60 lifted instruction by instruction (see tools/lift.py). `frame` is
 * the token for ebp, eax/edx/ebx/ecx the entry registers, `arguments` the stack dwords above the
 * return address, `garbage` the LIFTED_SELECT_SCREEN_LOCALS bytes of stack below ebp the routine
 * may read before it writes them and `chain` the value of fs:[0] at entry (the routine returns it).
 */
uint32_t lifted_select_screen(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, uint32_t frame, uint32_t eax,
                              uint32_t edx, uint32_t ebx, uint32_t ecx, const uint32_t *arguments,
                              const uint8_t *garbage, uint32_t chain);
#endif
