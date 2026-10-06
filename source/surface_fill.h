#ifndef VERTRIX_SURFACE_FILL_H
#define VERTRIX_SURFACE_FILL_H
#include <stdint.h>

#include "block_factory.h"

/* The scratch globals the fill keeps (0x5589f4 up to the format byte 0x558a50): the services
 * resolve VERTRIX_FILL_STATE to their storage. */
enum
{
    VERTRIX_FILL_STATE = 0x5589f4,
    VERTRIX_FILL_STATE_SIZE = 0x60
};

/* Original 0x478f50 (eax = surface, edx = colour): fills the surface's pixel memory (the pointer
 * at +0) with the colour repeated to fill a dword, as its bytes a pixel (+0xc) decide: 1 repeats
 * the low byte four times, 2 the low word twice, 4 keeps the colour and any other count keeps the
 * previous dword at 0x558a08. A zero dword at +0x10 fills width (+4) * height (+8) * bytes / 4
 * dwords in one run; otherwise each of the height rows fills width * bytes / 4 dwords and the
 * pointer then moves on by the dword at +0x18. 0x479a40 packs the colour for the format byte at
 * +0xd into 0x558a0c (and the format into 0x558a50). The original keeps its loop registers in the
 * globals 0x5589f4 (pointer), 0x5589f8 (count), 0x5589fc, 0x558a00 (rows), 0x558a04 (pitch) and
 * 0x558a08 (the dword), all in the state region. *result is the original's eax. Returns zero when
 * memory cannot be accessed. */
int vertrix_surface_fill(const VertrixFactoryServices *services, uint32_t surface, uint32_t colour,
                         uint32_t *result);

#endif
