#ifndef VERTRIX_SURFACE_CLEAR_H
#define VERTRIX_SURFACE_CLEAR_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The two surface globals (0x558c80 and 0x558c88): the services resolve VERTRIX_SURFACE_PAIR to
 * their storage. */
enum
{
    VERTRIX_SURFACE_PAIR = 0x558c80,
    VERTRIX_SURFACE_PAIR_SIZE = 0xc,
    VERTRIX_SURFACE_SECOND = 0x8
};

/* Original 0x41ac70 (ebx and ecx are the caller's registers): fills the surface in 0x558c88 with
 * colour zero through 0x478f50. *result is the original's eax (the fill's). Returns zero when
 * memory cannot be accessed. */
int vertrix_surface_clear_second(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t ebx, uint32_t ecx, uint32_t *result);

/* Original 0x4856a0 (eax = argument; edx and ebx are the caller's registers): 0x4872c0 makes a
 * surface for the argument (the first call with the caller's edx, the second with zero), which is
 * stored in 0x558c80 and then 0x558c88, each cleared through 0x478f50 with colour zero. Returns
 * zero when memory cannot be accessed; the original answers one. */
int vertrix_surface_pair_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              uint32_t argument, uint32_t edx, uint32_t ebx);

#endif
