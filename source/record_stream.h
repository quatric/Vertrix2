#ifndef VERTRIX_RECORD_STREAM_H
#define VERTRIX_RECORD_STREAM_H
#include "object_dwords.h"
#include "stream_read.h"

enum
{
    VERTRIX_SAVED_BLOCK_SIZE = 0x228,
    VERTRIX_SAVED_BLOCK_DATA = 0x224,
    VERTRIX_SAVED_BLOCK_STATE_LOADED = 1,
    VERTRIX_SAVED_BLOCK_STATE_READY = 2
};

/* Original0x4293e0: load a saved block into object from a range stream (the layout of
 * object_dwords.h: the first dword points at a block of two dwords, start and length). Nothing
 * happens unless the length is 0x228. Otherwise the state dword at +0 and the 0x224 data bytes at
 * +4 are read, the 20 bytes at +0x70 are complemented, and a state of 1 becomes 2 with the dword
 * at +0x50 cleared. Returns 0 for short object or stream storage. */
int vertrix_saved_block_load(void *object, size_t object_size, void *stream, size_t stream_size,
                             VertrixMemoryRead read, void *read_context, VertrixStreamFetch fetch,
                             void *fetch_context);

/* Original0x4121e0: load a record table (record_slots.h layout) from a range stream: start the
 * stream, read the 8 bytes at +0x5b8 (two dwords; the second, at +0x5bc, is taken as the record
 * count), then read that many records of 12 bytes to the start of the table. The dword at +0x5bc
 * keeps the value it had before the call. A count above the 122 records of the table would overrun
 * the object in the original and is rejected, as is short storage; returns 0 for both. */
int vertrix_record_table_load(void *table, size_t table_size, void *stream, size_t stream_size,
                              VertrixMemoryRead read, void *read_context, VertrixStreamFetch fetch,
                              void *fetch_context);
#endif
