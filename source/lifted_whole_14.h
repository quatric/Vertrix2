#ifndef VERTRIX_LIFTED_WHOLE_14_H
#define VERTRIX_LIFTED_WHOLE_14_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F429A10_STACK = 100,
    LIFTED_F429A80_STACK = 104,
    LIFTED_F429AF0_STACK = 100,
    LIFTED_F43A280_STACK = 84,
    LIFTED_F43D4D0_STACK = 244,
    LIFTED_F4B5A60_STACK = 252
};

/* Original 0x429a10. */
uint32_t lifted_f429a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429a80. */
uint32_t lifted_f429a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429af0. */
uint32_t lifted_f429af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a280. */
uint32_t lifted_f43a280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43d4d0. */
uint32_t lifted_f43d4d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b5a60. */
uint32_t lifted_f4b5a60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
