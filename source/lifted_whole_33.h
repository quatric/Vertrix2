#ifndef VERTRIX_LIFTED_WHOLE_33_H
#define VERTRIX_LIFTED_WHOLE_33_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F40B0A0_STACK = 80,
    LIFTED_F40B0D0_STACK = 88,
    LIFTED_F40B110_STACK = 416,
    LIFTED_F40B490_STACK = 216,
    LIFTED_F40CCF0_STACK = 68,
    LIFTED_F48B2F0_STACK = 26668
};

/* Original 0x40b0a0. */
uint32_t lifted_f40b0a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b0d0. */
uint32_t lifted_f40b0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b110. */
uint32_t lifted_f40b110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40b490. */
uint32_t lifted_f40b490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ccf0. */
uint32_t lifted_f40ccf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x48b2f0. */
uint32_t lifted_f48b2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
