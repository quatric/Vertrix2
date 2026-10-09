#ifndef VERTRIX_S3M_PATTERN_H
#define VERTRIX_S3M_PATTERN_H
#include <stdint.h>

#include "actor_build.h"
#include "block_factory.h"
#include "call_glue.h"

/* The row buffer the converter assembles each row in (0x53207c, five bytes a channel: note,
 * instrument, volume, command and parameter, 0xa0 bytes cleared each row) directly followed by
 * the per-channel parameter memory (0x53211c, 0x20 bytes cleared once). Channels are not limited
 * to 32, so both are reached through one handle the services resolve to at least 0x500 bytes. */
enum
{
    VERTRIX_S3M_ROW = 0x53207c,
    VERTRIX_S3M_ROW_SIZE = 0x500
};

/* Original 0x410270 (eax = channel count, edx = packed S3M pattern, ebx = its length in bytes,
 * ecx = the 32 byte channel map, stack = pattern record; called from 0x410c9e with the map
 * 0x5324dc): sets the record's words (+0 zero, +2 the count, +4 0x40 rows, +6 zero), allocates
 * count * 0x180 bytes with 0x4e7c90 (the pointer goes to +8; zero returns 8) and clears the
 * parameter memory. Each of the 64 rows clears the row buffer and reads events until a zero byte
 * or the end of the data: the flag's low five bits select the channel through the map (a mapped
 * channel at or past the count is skipped after its bytes are read), bit 0x20 adds note and
 * instrument, 0x40 the volume and 0x80 command and parameter. Notes become octave * 12 + note + 1
 * (above 0x60 none), 0xfe key off 0x61 and 0xff none. A non-zero parameter is remembered for the
 * channel; a zero one is taken from memory for D, E, F, G, K, L and Q (0x4ec1d0 against the text
 * "DEFGKLQ" at 0x50c80c). The command letter is translated (tables 0x4101d8 and 0x410244) into
 * the XM effect, and note, instrument, volume (at most 0x40, stored plus 0x10) and effect are
 * stored when present. The row is then emitted for every channel below the count as a flag byte
 * (0x80, 1, 2, 4, 8 and 0x10 for the parts present) followed by those parts. Finally the record's
 * size word becomes the bytes written and 0x4ec0e0 resizes the allocation (zero returns 8).
 * *result is the original's eax: zero, or 8 on an allocation failure. Memory the services do not
 * resolve is read through `globals` and stored through the 0xf0000000 pseudo call, as the lifted
 * routines do; without `globals` it returns zero instead. */
int vertrix_s3m_pattern(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, uint32_t channels, uint32_t source,
                        uint32_t length, uint32_t map, uint32_t record, uint32_t *result);

#endif
