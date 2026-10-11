#ifndef VERTRIX_LIFTED_WHOLE_17_H
#define VERTRIX_LIFTED_WHOLE_17_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F425D50_STACK = 136,
    LIFTED_F425E40_STACK = 156,
    LIFTED_F427850_STACK = 468,
    LIFTED_F42B8D0_STACK = 96,
    LIFTED_F42BCA0_STACK = 188,
    LIFTED_F42EA00_STACK = 208,
    LIFTED_F43A0B0_STACK = 156,
    LIFTED_F482320_STACK = 136,
    LIFTED_F487930_STACK = 168
};

/* Original 0x425d50. */
uint32_t lifted_f425d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425e40. */
uint32_t lifted_f425e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x427850. */
uint32_t lifted_f427850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b8d0. */
uint32_t lifted_f42b8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42bca0. */
uint32_t lifted_f42bca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42ea00. */
uint32_t lifted_f42ea00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a0b0. */
uint32_t lifted_f43a0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x482320. */
uint32_t lifted_f482320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x487930. */
uint32_t lifted_f487930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
