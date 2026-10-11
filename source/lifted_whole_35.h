#ifndef VERTRIX_LIFTED_WHOLE_35_H
#define VERTRIX_LIFTED_WHOLE_35_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F40C7D0_STACK = 88,
    LIFTED_F410F20_STACK = 160,
    LIFTED_F410F80_STACK = 76,
    LIFTED_F410FA0_STACK = 224,
    LIFTED_F4111C0_STACK = 132,
    LIFTED_F411270_STACK = 64
};

/* Original 0x40c7d0. */
uint32_t lifted_f40c7d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x410f20. */
uint32_t lifted_f410f20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x410f80. */
uint32_t lifted_f410f80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x410fa0. */
uint32_t lifted_f410fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4111c0. */
uint32_t lifted_f4111c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x411270. */
uint32_t lifted_f411270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
