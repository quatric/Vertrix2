#ifndef VERTRIX_LIFTED_UNVERIFIED_H
#define VERTRIX_LIFTED_UNVERIFIED_H
#include <stdint.h>

#include "actor_build.h"

enum
{
    LIFTED_F42A200_STACK = 120,
    LIFTED_OBJECT_CONSTRUCT_LABELED_BOX_STACK = 136,
    LIFTED_OBJECT_LABEL_TEXT_STACK = 128,
    LIFTED_F4CCF3B_STACK = 120
};

/* Original 0x42a200. */
uint32_t lifted_f42a200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b6350. */
uint32_t lifted_object_construct_labeled_box(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4b65d0. */
uint32_t lifted_object_label_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x4ccf3b. */
uint32_t lifted_f4ccf3b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry);
#endif
