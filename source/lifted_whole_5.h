#ifndef VERTRIX_LIFTED_WHOLE_5_H
#define VERTRIX_LIFTED_WHOLE_5_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4C6460_STACK = 100,
    LIFTED_F4C8500_STACK = 2200,
    LIFTED_F4CD56C_STACK = 244,
    LIFTED_F4CD7DC_STACK = 84,
    LIFTED_F4CFA20_STACK = 408,
    LIFTED_F4D01A0_STACK = 152,
    LIFTED_F4D4700_STACK = 196,
    LIFTED_F4D5AB0_STACK = 472
};

/* Original 0x4c6460. */
uint32_t lifted_f4c6460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8500. */
uint32_t lifted_f4c8500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd56c. */
uint32_t lifted_f4cd56c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd7dc. */
uint32_t lifted_f4cd7dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cfa20. */
uint32_t lifted_f4cfa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d01a0. */
uint32_t lifted_f4d01a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4700. */
uint32_t lifted_f4d4700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5ab0. */
uint32_t lifted_f4d5ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
