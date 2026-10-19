#ifndef VERTRIX_LIFTED_WHOLE_13_H
#define VERTRIX_LIFTED_WHOLE_13_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4D2710_STACK = 300,
    LIFTED_F4DFB24_STACK = 168,
    LIFTED_F4E63B0_STACK = 156,
    LIFTED_F4E7F18_STACK = 116,
    LIFTED_F4E843C_STACK = 136,
    LIFTED_F4E969C_STACK = 120,
    LIFTED_F4E9E30_STACK = 108
};

/* Original 0x4d2710. */
uint32_t lifted_f4d2710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dfb24. */
uint32_t lifted_f4dfb24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e63b0. */
uint32_t lifted_f4e63b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7f18. */
uint32_t lifted_f4e7f18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e843c. */
uint32_t lifted_f4e843c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e969c. */
uint32_t lifted_f4e969c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e9e30. */
uint32_t lifted_f4e9e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
