#ifndef VERTRIX_LIFTED_HUD_DECOR_H
#define VERTRIX_LIFTED_HUD_DECOR_H
#include <stdint.h>

#include "lift_runtime.h"

enum
{
    LIFTED_HUD_DECOR_STACK = 1096
};

/* The original routine 0x46b810 lifted instruction by instruction (see tools/lift.py). `entry`
 * holds the registers at entry, esp (the address of the return slot), the stack dwords above it and
 * the LIFTED_HUD_DECOR_STACK bytes below it the routine may read before it writes them. */
uint32_t lifted_hud_decor(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);
#endif
