#ifndef VERTRIX_NATIVE_MEMORY_H
#define VERTRIX_NATIVE_MEMORY_H
#include <stddef.h>
#include <stdint.h>

#include "actor_build.h"
#include "block_factory.h"
#include "call_glue.h"

/* Memory of the original's address space as the hand-recovered routines that run from the lifted
 * dispatcher see it: an address the services resolve (an object, or an interior pointer on the
 * lifted host) is read and written in place; any other address is read through `globals` and
 * stored through the 0xf0000000 pseudo call (LIFT_GLOBAL_STORE in lift_runtime.h: eax the
 * address, edx the value, one stack argument the width), as lift_load and lift_store do. Without
 * `globals` an unresolvable access clears `ok` instead. */
typedef struct VertrixNativeMemory
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    const VertrixGlobals *globals;
    int ok;
} VertrixNativeMemory;

uint32_t vertrix_native_get(VertrixNativeMemory *memory, uint32_t base, size_t offset,
                            unsigned width);
void vertrix_native_put(VertrixNativeMemory *memory, uint32_t base, size_t offset, unsigned width,
                        uint32_t value);

#endif
