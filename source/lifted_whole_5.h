#ifndef VERTRIX_LIFTED_WHOLE_5_H
#define VERTRIX_LIFTED_WHOLE_5_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4BEF10_STACK = 108,
    LIFTED_F4C2000_STACK = 132,
    LIFTED_F4C4000_STACK = 408,
    LIFTED_F4C4730_STACK = 244,
    LIFTED_F4C6460_STACK = 100,
    LIFTED_F4C70F0_STACK = 268,
    LIFTED_F4C8500_STACK = 2200,
    LIFTED_F4CB5A0_STACK = 196,
    LIFTED_RTL_BLOCK_CALL_STACK = 80,
    LIFTED_RTL_TERMINATE_CALL_STACK = 76,
    LIFTED_RTL_VARARG_CALL_STACK = 84,
    LIFTED_F4CD56C_STACK = 244,
    LIFTED_F4CD7DC_STACK = 84,
    LIFTED_F4CDBE0_STACK = 192,
    LIFTED_F4CFA20_STACK = 408,
    LIFTED_F4D01A0_STACK = 152,
    LIFTED_RTL_ANCESTOR_SEARCH_STACK = 76,
    LIFTED_F4D4700_STACK = 196,
    LIFTED_F4D5AB0_STACK = 472
};

/* Original 0x4bef10. */
uint32_t lifted_f4bef10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c2000. */
uint32_t lifted_f4c2000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4000. */
uint32_t lifted_f4c4000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c4730. */
uint32_t lifted_f4c4730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6460. */
uint32_t lifted_f4c6460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c70f0. */
uint32_t lifted_f4c70f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c8500. */
uint32_t lifted_f4c8500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cb5a0. */
uint32_t lifted_f4cb5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccb9f. */
uint32_t lifted_rtl_block_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd0a4. */
uint32_t lifted_rtl_terminate_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd544. */
uint32_t lifted_rtl_vararg_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd56c. */
uint32_t lifted_f4cd56c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cd7dc. */
uint32_t lifted_f4cd7dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cdbe0. */
uint32_t lifted_f4cdbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4cfa20. */
uint32_t lifted_f4cfa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d01a0. */
uint32_t lifted_f4d01a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4390. */
uint32_t lifted_rtl_ancestor_search(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d4700. */
uint32_t lifted_f4d4700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d5ab0. */
uint32_t lifted_f4d5ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
