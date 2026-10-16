#ifndef VERTRIX_LIFTED_WHOLE_16_H
#define VERTRIX_LIFTED_WHOLE_16_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_AI_SEARCH_STACK = 516,
    LIFTED_F432480_STACK = 228
};

/* Original 0x4270a0. */
uint32_t lifted_ai_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432480. */
uint32_t lifted_f432480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
