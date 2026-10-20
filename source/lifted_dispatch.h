#ifndef VERTRIX_LIFTED_DISPATCH_H
#define VERTRIX_LIFTED_DISPATCH_H
#include <stdint.h>

#include "actor_build.h"

/* Number of original routines that run as verified lifted C (tools/gen_dispatch.py). */
unsigned vertrix_lifted_count(void);

/* How many lifted routines are executing now (the frames in vertrix_lift_frames). */
unsigned vertrix_lifted_depth(void);

/* Print every dispatched routine's original address and call depth (debugging). */
void vertrix_lifted_set_trace(int enabled);

/* Called after every lifted routine returns, with its address and entry EAX (debugging). */
extern void (*vertrix_lifted_after_hook)(uint32_t target, uint32_t eax);

/* The lifted routine for an original address, or 0 when the routine stays a call boundary. */
int vertrix_lifted_has(uint32_t target);

struct LiftEntry;
typedef uint32_t (*VertrixLiftedFunction)(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals,
                                          const struct LiftEntry *entry);

/* The function a call through `calls` to `target` with no stack arguments would run now, and the
 * frame index vertrix_lifted_dispatch would set; NULL when `calls` is not a VertrixLiftedCalls,
 * when the call would not reach a routine, or when the trace or the after hook watches every
 * dispatch (vertrix_lift_routine_hook). */
VertrixLiftedFunction vertrix_lifted_function(const VertrixCalls *calls, uint32_t target,
                                              unsigned *index);

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
