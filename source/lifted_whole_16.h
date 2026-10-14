#ifndef VERTRIX_LIFTED_WHOLE_16_H
#define VERTRIX_LIFTED_WHOLE_16_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_AI_SEARCH_STACK = 516,
    LIFTED_F429910_STACK = 168,
    LIFTED_F42A3C0_STACK = 164,
    LIFTED_F42B190_STACK = 168,
    LIFTED_F432480_STACK = 228,
    LIFTED_F43A1A0_STACK = 164,
    LIFTED_F43A970_STACK = 180,
    LIFTED_TITLE_LETTER_FIRST_CALL_STACK = 212
};

/* Original 0x4270a0. */
uint32_t lifted_ai_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x429910. */
uint32_t lifted_f429910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42a3c0. */
uint32_t lifted_f42a3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x42b190. */
uint32_t lifted_f42b190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x432480. */
uint32_t lifted_f432480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a1a0. */
uint32_t lifted_f43a1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x43a970. */
uint32_t lifted_f43a970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4713d0. */
uint32_t lifted_title_letter_first_call(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
