#ifndef VERTRIX_LIFTED_WHOLE_17_H
#define VERTRIX_LIFTED_WHOLE_17_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F427850_STACK = 468,
    LIFTED_F42B8D0_STACK = 96,
    LIFTED_F42BCA0_STACK = 188,
    LIFTED_F42EA00_STACK = 208
};

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

#endif
