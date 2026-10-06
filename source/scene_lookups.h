#ifndef VERTRIX_SCENE_LOOKUPS_H
#define VERTRIX_SCENE_LOOKUPS_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Original 0x471e10 (eax = object, ebx the caller's register). 0x4b5eb0 looks up kind 0x15 in
 * the list 0x54671c (edx = 0x15, ecx = object); a non-zero result goes through
 * 0x4123d0(object, 0, result). The same follows for kind 0x16 with the register ebx the first
 * lookup left. Returns the eax of the last call made: 0x4123d0 of the second lookup, or zero
 * when the second lookup finds nothing. */
uint32_t vertrix_scene_lookup_pair(const VertrixCalls *calls, uint32_t object, uint32_t ebx);

/* Original 0x4725f0 (ebx and ecx the caller's registers): 0x4b5eb0 looks up kind 0x190 in the
 * list 0x546744; a non-zero result has its dword +0x94c cleared. Returns that result, zero when
 * the object does not resolve or nothing is found. */
uint32_t vertrix_scene_clear_marker(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint32_t ebx,
                                    uint32_t ecx);
#endif
