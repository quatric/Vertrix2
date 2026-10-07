#ifndef VERTRIX_LIFTED_GAME_SCREEN_H
#define VERTRIX_LIFTED_GAME_SCREEN_H
#include <stdint.h>

#include "lift_runtime.h"

enum
{
    LIFTED_GAME_SCREEN_STACK = 2064
};

/* The original routine 0x46c9d0 lifted instruction by instruction (see tools/lift.py). `entry`
 * holds the registers at entry, esp (the address of the return slot), the stack dwords above it and
 * the LIFTED_GAME_SCREEN_STACK bytes below it the routine may read before it writes them. */
uint32_t lifted_game_screen(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry);
#endif
