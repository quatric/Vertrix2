#ifndef VERTRIX_NATIVE_DISPATCH_H
#define VERTRIX_NATIVE_DISPATCH_H
#include "lift_runtime.h"

/* Entry points that let the lifted-routine dispatcher run a hand-recovered routine in place of a
 * lifted one. Each has the signature of a lifted routine and unpacks the registers of its
 * LiftEntry; tools/gen_dispatch.py lists them in the dispatch table (NATIVE_PORTS in
 * tools/dispatch_boundaries.py). */

/* Original 0x41c7b0, see title_frame.h. */
uint32_t vertrix_native_title_frame(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry);

/* Original 0x41b820, see game_frame.h. */
uint32_t vertrix_native_game_frame(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry);

#endif
