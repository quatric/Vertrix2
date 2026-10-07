#ifndef VERTRIX_LIFTED_DISPATCH_H
#define VERTRIX_LIFTED_DISPATCH_H
#include <stdint.h>

#include "actor_build.h"

/* Number of original routines that run as verified lifted C (tools/gen_dispatch.py). */
unsigned vertrix_lifted_count(void);

/* The lifted routine for an original address, or 0 when the routine stays a call boundary. */
int vertrix_lifted_has(uint32_t target);

/* Run the lifted routine for site->target with the registers and stack arguments of the site.
 * Returns 1 and stores the routine's eax in *result when there is one. */
int vertrix_lifted_dispatch(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const VertrixCallSite *site,
                            uint32_t *result);

/* VertrixCalls that run the lifted routine for a target when there is one and otherwise forward
 * the call to `inner` (the platform's implementation of the unrecovered routines). */
typedef struct VertrixLiftedCalls
{
    VertrixCalls calls;
    const VertrixCalls *inner;
    const VertrixFactoryServices *services;
    const VertrixGlobals *globals;
} VertrixLiftedCalls;

void vertrix_lifted_calls_init(VertrixLiftedCalls *adapter, const VertrixCalls *inner,
                               const VertrixFactoryServices *services,
                               const VertrixGlobals *globals);
#endif
