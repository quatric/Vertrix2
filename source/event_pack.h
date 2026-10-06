#ifndef VERTRIX_EVENT_PACK_H
#define VERTRIX_EVENT_PACK_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* Original 0x40f1a0 (eax = track number, edx = track record; ebx is the caller's register): sets
 * the record's words (+0 zero, +2 the number, +4 0x40, +6 the number * 0x140 truncated to sixteen
 * bits), allocates that many bytes with 0x4e7c90 (the pointer goes to +8; zero returns 8), has
 * 0x40c220 fill the number * 256 bytes at pointer + number * 64 and packs them in place, four bytes
 * (a 12 bit value passed through 0x40f170, the high nibble of the first byte with the high nibble
 * of the third, the low nibble of the third with the fourth as a 12 bit command, the fourth byte as
 * a level) at a time, into a flag byte (0x80, 1, 2, 8 and 0x10 for the parts present) followed
 * by the parts present. A command of 0x100, 0x200, 0xa00, 0xe10, 0xe20, 0xea0 or 0xeb0 drops its
 * part and the level; otherwise the level is rescaled when the part is 8. Finally the record's size
 * word becomes the bytes written and 0x4ec0e0 resizes the allocation (zero returns 8). *result is
 * the original's eax: zero, or 8 on an allocation failure. Returns zero when memory cannot be
 * accessed. */
int vertrix_event_pack(const VertrixCalls *calls, const VertrixFactoryServices *services,
                       uint32_t number, uint32_t record, uint32_t ebx, uint32_t *result);

#endif
