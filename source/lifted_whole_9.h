#ifndef VERTRIX_LIFTED_WHOLE_9_H
#define VERTRIX_LIFTED_WHOLE_9_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_BOARD_SPIN_MARKED_STACK = 256,
    LIFTED_F480080_STACK = 84,
    LIFTED_STRING_APPEND_CALLS_STACK = 84,
    LIFTED_TEXT_WRAP_STACK = 216,
    LIFTED_F4C6020_STACK = 148,
    LIFTED_F4C6C80_STACK = 200,
    LIFTED_F4EC68C_STACK = 96
};

/* Original 0x437fe0. */
uint32_t lifted_board_spin_marked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480080. */
uint32_t lifted_f480080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x489760. */
uint32_t lifted_string_append_calls(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b25b0. */
uint32_t lifted_text_wrap(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6020. */
uint32_t lifted_f4c6020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4c6c80. */
uint32_t lifted_f4c6c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ec68c. */
uint32_t lifted_f4ec68c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

#endif
