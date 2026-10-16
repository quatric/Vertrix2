#ifndef VERTRIX_LIFTED_WHOLE_0_H
#define VERTRIX_LIFTED_WHOLE_0_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F406170_STACK = 852,
    LIFTED_F407020_STACK = 184,
    LIFTED_F407830_STACK = 392,
    LIFTED_F4083A0_STACK = 212,
    LIFTED_CURVE_TABLE_BUILD_STACK = 120,
    LIFTED_F4193B0_STACK = 168,
    LIFTED_PIECE_INIT_FROM_KIND_STACK = 68
};

/* Original 0x406170. */
uint32_t lifted_f406170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407020. */
uint32_t lifted_f407020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x407830. */
uint32_t lifted_f407830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4083a0. */
uint32_t lifted_f4083a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x40ba00. */
uint32_t lifted_curve_table_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4193b0. */
uint32_t lifted_f4193b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x425ef0. */
uint32_t lifted_piece_init_from_kind(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

#endif
