#ifndef VERTRIX_LIFTED_WHOLE_24_H
#define VERTRIX_LIFTED_WHOLE_24_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4B4100_STACK = 96,
    LIFTED_F4B4150_STACK = 92,
    LIFTED_F4B41A0_STACK = 88,
    LIFTED_F4B41F0_STACK = 92
};

/* Original 0x4b4100. */
uint32_t lifted_f4b4100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b4150. */
uint32_t lifted_f4b4150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b41a0. */
uint32_t lifted_f4b41a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b41f0. */
uint32_t lifted_f4b41f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
