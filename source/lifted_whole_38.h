#ifndef VERTRIX_LIFTED_WHOLE_38_H
#define VERTRIX_LIFTED_WHOLE_38_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4CEAA0_STACK = 700,
    LIFTED_F4D3140_STACK = 868,
    LIFTED_F4DB8B0_STACK = 112,
    LIFTED_F4DD190_STACK = 184,
    LIFTED_F4E5EF0_STACK = 140,
    LIFTED_F4E7200_STACK = 108
};

/* Original 0x4ceaa0. */
uint32_t lifted_f4ceaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d3140. */
uint32_t lifted_f4d3140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db8b0. */
uint32_t lifted_f4db8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dd190. */
uint32_t lifted_f4dd190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e5ef0. */
uint32_t lifted_f4e5ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7200. */
uint32_t lifted_f4e7200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
