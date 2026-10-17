#ifndef RTLMP3MEMORYDECODES_H
#define RTLMP3MEMORYDECODES_H

#include "port.h"

/* Decodes a whole MP3 stream into memory: allocates a 400,000-byte buffer, resets the reader,
 * decodes frames 0x2000 bytes at a time (0x405f70) and appends each frame's output, then wraps the
 * result in a new 0x18-byte record. */
uint32_t vertrix_port_mp3_decode_to_memory_48b2f0(PORT_SIGNATURE);

#endif
