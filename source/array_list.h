#ifndef VERTRIX_ARRAY_LIST_H
#define VERTRIX_ARRAY_LIST_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Original 0x4874f0: releases an array list object (array handle at +0, count at +4, buffers at
 * +8, +0xc and +0x10, mode flag at +0x14). With the flag clear it calls 0x4830f0 on every item and
 * releases the array through 0x4ea190; otherwise it releases the three buffers. `edx` is the
 * caller's register, passed to the first releases. Returns eax. */
uint32_t vertrix_array_list_release(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t object,
                                    uint32_t edx);

/* Original 0x4876c0: calls 0x483790(item, edx = argument) on every non-null item of the array
 * list. Returns eax, the count, or the object when nothing is called. */
uint32_t vertrix_array_list_each(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, uint32_t argument);

enum
{
    VERTRIX_SLOT_MAKE_ARGUMENTS = 10
};

/* Original 0x487660 (ret 0x28): clears the slot `index` of the array list's array, builds the
 * entry with 0x483060 and stores its result there. eax/edx of the call are `ebx_in`/`ecx_in`, the
 * registers the caller passed; `arguments` are the ten stack dwords (the first is ebx, the second
 * ecx, four dwords, the bytes at +0x20 and +0x2c, and the sign extended bytes at +0x24 and +0x28
 * are the callee's stack). Returns the entry. */
uint32_t vertrix_array_list_make(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, uint32_t index, uint32_t ebx_in, uint32_t ecx_in,
                                 const uint32_t arguments[VERTRIX_SLOT_MAKE_ARGUMENTS]);
/* Original 0x4875a0 (ret 0x28, the ten arguments as for 0x487660): the count is stored at +4,
 * 0x4ec160(count, 4) allocates the array stored at +0, and every entry is made as by
 * vertrix_array_list_make. Returns the last entry (or the array for an empty list). */
uint32_t vertrix_array_list_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, uint32_t count, uint32_t ebx_in, uint32_t ecx_in,
                                  const uint32_t arguments[VERTRIX_SLOT_MAKE_ARGUMENTS]);

#endif
