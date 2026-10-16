#ifndef VERTRIX_LIFTED_WHOLE_9_H
#define VERTRIX_LIFTED_WHOLE_9_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F41D6D0_STACK = 392,
    LIFTED_F423BC0_STACK = 220,
    LIFTED_BOARDS_CONVERT_COUNTS_STACK = 208,
    LIFTED_BOARDS_CONVERT_RANDOM_STACK = 220,
    LIFTED_F4375F0_STACK = 176,
    LIFTED_BOARD_SPIN_MARKED_STACK = 256,
    LIFTED_F480080_STACK = 84,
    LIFTED_OBJECT_KIND_TEXT_STACK = 172,
    LIFTED_STRING_APPEND_CALLS_STACK = 84,
    LIFTED_TEXT_WRAP_STACK = 216,
    LIFTED_F4C6020_STACK = 148,
    LIFTED_F4C6C80_STACK = 200,
    LIFTED_F4EC68C_STACK = 96
};

/* Original 0x41d6d0. */
uint32_t lifted_f41d6d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x423bc0. */
uint32_t lifted_f423bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436b40. */
uint32_t lifted_boards_convert_counts(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x436d80. */
uint32_t lifted_boards_convert_random(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4375f0. */
uint32_t lifted_f4375f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x437fe0. */
uint32_t lifted_board_spin_marked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x480080. */
uint32_t lifted_f480080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x488d80. */
uint32_t lifted_object_kind_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
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
