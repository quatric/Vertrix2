#ifndef VERTRIX_BITMAP_LOAD_H
#define VERTRIX_BITMAP_LOAD_H
#include <stdint.h>

#include "block_factory.h"
#include "call_glue.h"

/* The stack locals the stream reads fill (the 0x80 bytes below the frame): the services resolve
 * the address frame - VERTRIX_BITMAP_FRAME_SIZE to their storage. */
enum
{
    VERTRIX_BITMAP_FRAME_SIZE = 0x80
};

/* Original 0x473cf0 (eax = stream; edx, ebx and ecx are the caller's registers; `frame` is the
 * token for ebp): reads a 24 bit uncompressed bitmap from the stream. 0x48a8a0 prepares the
 * stream, 0x48aad0 gives its position, the file header (14 bytes) and the 40 byte information
 * header are read with 0x48a930 into the frame; a size other than 0x28, one plane other than one,
 * a bit count other than 0x18 or a compression other than zero returns zero. Otherwise 0x478d10
 * creates a surface for the width, the absolute height and four bytes a pixel; 0x48aaf0 seeks to
 * the pixel data; each row reads the pixels as three bytes (0x48a930, one at a time through the
 * frame) stored as four (the fourth zero) at the surface's pixel pointer (+0) and skips the row
 * padding with 0x48aa90. 0x479b50 finishes the surface, which is returned. *result is the
 * original's eax. Returns zero when memory cannot be accessed. */
int vertrix_bitmap_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t frame, uint32_t stream, uint32_t edx, uint32_t ebx, uint32_t ecx,
                        uint32_t *result);

#endif
