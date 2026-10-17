#ifndef VERTRIX_LIFTED_WHOLE_6_H
#define VERTRIX_LIFTED_WHOLE_6_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_RTL_SIGN_COMPARE_STACK = 64,
    LIFTED_F4D80D5_STACK = 84,
    LIFTED_F4D8198_STACK = 80,
    LIFTED_RTL_SINGLE_DIVIDE_SOFTWARE_FULL_STACK = 88,
    LIFTED_OBJECT_DESTROY_G_STACK = 136,
    LIFTED_NODE_POOL_TAKE_INITIALISED_STACK = 104,
    LIFTED_F4DB131_STACK = 88,
    LIFTED_F4DC2F0_STACK = 184,
    LIFTED_RTL_SEGMENT_DISPATCH_STACK = 84,
    LIFTED_F4E0AE5_STACK = 104,
    LIFTED_F4E3CE0_STACK = 112,
    LIFTED_F4E628C_STACK = 80,
    LIFTED_F4E6C98_STACK = 80,
    LIFTED_F4E7FC4_STACK = 400,
    LIFTED_F4E88BF_STACK = 76,
    LIFTED_F4E8CC8_STACK = 104,
    LIFTED_F4EA350_STACK = 108,
    LIFTED_F4EA540_STACK = 104
};

/* Original 0x4d8082. */
uint32_t lifted_rtl_sign_compare(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d80d5. */
uint32_t lifted_f4d80d5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8198. */
uint32_t lifted_f4d8198(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8227. */
uint32_t lifted_rtl_single_divide_software_full(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry);

/* Original 0x4d8b80. */
uint32_t lifted_object_destroy_g(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4d8c20. */
uint32_t lifted_node_pool_take_initialised(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4db131. */
uint32_t lifted_f4db131(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dc2f0. */
uint32_t lifted_f4dc2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4dee73. */
uint32_t lifted_rtl_segment_dispatch(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e0ae5. */
uint32_t lifted_f4e0ae5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e3ce0. */
uint32_t lifted_f4e3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e628c. */
uint32_t lifted_f4e628c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6c98. */
uint32_t lifted_f4e6c98(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e7fc4. */
uint32_t lifted_f4e7fc4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e88bf. */
uint32_t lifted_f4e88bf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e8cc8. */
uint32_t lifted_f4e8cc8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea350. */
uint32_t lifted_f4ea350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ea540. */
uint32_t lifted_f4ea540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
