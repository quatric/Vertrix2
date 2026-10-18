#ifndef VERTRIX_LIFTED_WHOLE_8_H
#define VERTRIX_LIFTED_WHOLE_8_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4C17DA_STACK = 232,
    LIFTED_F4C8CD0_STACK = 216,
    LIFTED_F4CE740_STACK = 220,
    LIFTED_F4CE760_STACK = 220,
    LIFTED_F4DBD20_STACK = 192,
    LIFTED_F4DC030_STACK = 216,
    LIFTED_F4E0328_STACK = 128,
    LIFTED_F4E08F0_STACK = 72,
    LIFTED_F4E0B7C_STACK = 104,
    LIFTED_F4E0C0C_STACK = 88,
    LIFTED_F4E6C37_STACK = 132,
    LIFTED_F4EDC0E_STACK = 88,
    LIFTED_F4EDDC4_STACK = 104
};

/* Original 0x4c17da. */
uint32_t lifted_f4c17da(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8cd0. */
uint32_t lifted_f4c8cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce740. */
uint32_t lifted_f4ce740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ce760. */
uint32_t lifted_f4ce760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dbd20. */
uint32_t lifted_f4dbd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc030. */
uint32_t lifted_f4dc030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0328. */
uint32_t lifted_f4e0328(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e08f0. */
uint32_t lifted_f4e08f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0b7c. */
uint32_t lifted_f4e0b7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0c0c. */
uint32_t lifted_f4e0c0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6c37. */
uint32_t lifted_f4e6c37(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4edc0e. */
uint32_t lifted_f4edc0e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4eddc4. */
uint32_t lifted_f4eddc4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
