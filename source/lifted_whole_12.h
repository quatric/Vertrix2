#ifndef VERTRIX_LIFTED_WHOLE_12_H
#define VERTRIX_LIFTED_WHOLE_12_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4B9F70_STACK = 184,
    LIFTED_F4BA470_STACK = 152,
    LIFTED_F4BA7B0_STACK = 484,
    LIFTED_F4BF940_STACK = 696,
    LIFTED_F4CAE30_STACK = 200,
    LIFTED_F4CD819_STACK = 72,
    LIFTED_F4EC970_STACK = 152
};

/* Original 0x4b9f70. */
uint32_t lifted_f4b9f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ba470. */
uint32_t lifted_f4ba470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ba7b0. */
uint32_t lifted_f4ba7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4bf940. */
uint32_t lifted_f4bf940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cae30. */
uint32_t lifted_f4cae30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd819. */
uint32_t lifted_f4cd819(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec970. */
uint32_t lifted_f4ec970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
