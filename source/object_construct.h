#ifndef VERTRIX_OBJECT_CONSTRUCT_H
#define VERTRIX_OBJECT_CONSTRUCT_H
#include "block_factory.h"
#include "call_glue.h"
#include <stdint.h>

/* Constructors of the original, without the Delphi exception frame (the fs:[0] chain they push is
 * runtime scaffolding that leaves no state behind). The registers the frame leaves in edx and ebx
 * are what the callees see, so they are passed on to the call boundary. */
enum
{
    VERTRIX_CONSTRUCT_FRAME_HANDLER = 0x4ec1ec
};

/* Original 0x42e870: the board constructor. 0x4abd70, then 0x4b5db0 on the result + 0xcec; seven
 * array initialisations through 0x4b2290; ten setup calls on the board; the fixed fields zeroed
 * (and +0xa68 = 2, +0xb90 = 1). Returns the board (the 0x4b5db0 result - 0xcec), zero when it
 * does not resolve. */
uint32_t vertrix_board_construct(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t eax);

/* Original 0x43d6a0: 0x4abd70, then the table 0x514df4 at +0x158, two 0x4b2290 array
 * initialisations (0x1f4 at +0x15c and 8 at +0x92c), zero at +0x94c and one at +0x950. Returns the
 * object, zero when it does not resolve. */
uint32_t vertrix_slot_object_construct(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t eax);

/* Original 0x4413b0: three chained 0x4b5db0 calls from +0x22c (+0x14 each), the table 0x5150f4 at
 * +0x27c of the object that comes back. Returns it, zero when it does not resolve. */
uint32_t vertrix_chain_object_construct(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services, uint32_t eax);

/* Original 0x472570: allocate 0x15c bytes (0x4ca000 through the services), build through 0x4abd70
 * when that succeeded, place the actor at zero (vertrix_actor_initialize), store 9 at +0, run
 * 0x4ac7d0 with 10, store 0x1df, 0 and 4 at +0x58, +0x5c and +0x60, bind the handler 0x4597a0
 * through 0x4ac8f0, run 0x4ac910 on zero and append the actor to the list 0x54676c through
 * 0x4b5e70. edx, ebx and ecx are the caller's values for the construction call. Returns the eax of
 * the append, zero when the actor does not resolve. */
uint32_t vertrix_special_actor_spawn(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t edx,
                                     uint32_t ebx, uint32_t ecx);
#endif
