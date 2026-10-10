#ifndef VERTRIX_LIFTED_WHOLE_11_H
#define VERTRIX_LIFTED_WHOLE_11_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F4202A0_STACK = 696,
    LIFTED_TITLE_LETTER_DIGIT_CALL_STACK = 216,
    LIFTED_RENDER_COLOR_BANK_BUILD_STACK = 184,
    LIFTED_LIST_RELEASE_ENTRIES_STACK = 140,
    LIFTED_F4E6AE0_STACK = 96
};

/* Original 0x4202a0. */
uint32_t lifted_f4202a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x459ec0. */
uint32_t lifted_title_letter_digit_call(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x474e00. */
uint32_t lifted_render_color_bank_build(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b7830. */
uint32_t lifted_list_release_entries(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4e6ae0. */
uint32_t lifted_f4e6ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
