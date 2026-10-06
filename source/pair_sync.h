#ifndef VERTRIX_PAIR_SYNC_H
#define VERTRIX_PAIR_SYNC_H
#include <stdint.h>

#include "actor_storage.h"
#include "call_glue.h"
#include "object_glue.h"

enum
{
    VERTRIX_PAIR_FLAG_COUNT = 8
};

/* Original 0x473630. first and second are the objects held by the globals 0x540f8c and 0x540f90,
 * With the global 0x532a84 (gate) zero the four words +0x160..+0x166 of each object go
 * through 0x476320 on the table 0x54d640; 0x476440 (edx = the global 0x5bd834, value) and 0x476010
 * follow in any case; if the global read again
 * afterwards (gate_after) is zero the word pairs (+0x160/+0x168 .. +0x166/+0x16e) of each object go
 * through 0x4735e0. Returns the eax of the last call. */
uint32_t vertrix_pair_words(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t first, uint32_t second, uint32_t gate, uint32_t gate_after,
                            uint32_t value);

/* Originals 0x4737d0 (flags 0x5bb4ec..0x5bb4ef and 0x5bb4f4..0x5bb4f7) and 0x473960 (0x5bb4f0..
 * 0x5bb4f3 and 0x5bb4f8..0x5bb4fb): 0x476010 on the table, then, with the global 0x532a7c (gate)
 * one, the words +0x16c, +0x16e, +0x168 and +0x16a of the second object take the flags 0..3 and
 * those of the first object the flags 4..7, through 0x473610; otherwise the objects swap roles.
 * Returns the eax of the last call. */
uint32_t vertrix_pair_flags(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t first, uint32_t second, uint32_t gate,
                            const uint8_t flags[VERTRIX_PAIR_FLAG_COUNT]);

/* Original 0x473af0 (ebx the caller's): the object is the second one when the global 0x532a7c
 * (gate) is one, otherwise the first. 0x476480 on its words +0x164, +0x166, +0x160, +0x162 gives
 * the bytes 0..3 (the globals 0x5bb594..0x5bb597), 0x476320 stores the words +0x160..+0x166,
 * 0x476440 and 0x476010 follow with edx zero, then the probes give the bytes 4..7
 * (0x5bb598
 * ..0x5bb59b) and the words are stored again. Returns the last eax. */
uint32_t vertrix_pair_scan(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           uint32_t first, uint32_t second, uint32_t gate, uint32_t ebx,
                           uint8_t bytes[VERTRIX_PAIR_FLAG_COUNT]);

#endif
