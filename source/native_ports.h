#ifndef VERTRIX_NATIVE_PORTS_H
#define VERTRIX_NATIVE_PORTS_H
#include <stdint.h>

#include "native_memory.h"

/* Small hand-recovered routines whose batch lift did not pass verification, written over the
 * original's address space (native_memory.h) so the lifted dispatcher can run them in place of a
 * call boundary. Each returns the original's eax on return. */

/* Original 0x4327e0 (eax = slot pointers, edx = kind bytes, ebx = count): for each slot,
 * one at a time, the kind byte is 0xff when the dword is zero and the slot object's byte +0x15c
 * otherwise (vertrix_board_snapshot_kinds in board_markers.h on native arrays). The loop runs at
 * least once when the count is non-zero and stops when the slot pointer reaches eax + count * 4
 * (unsigned, wrapping); the stores happen in order, so overlapping arrays read earlier stores.
 * Returns the final slot pointer (eax unchanged for a zero count). */
uint32_t vertrix_port_kind_snapshot(VertrixNativeMemory *memory, uint32_t slots, uint32_t kinds,
                                    uint32_t count);

/* Original 0x4046e0: read the next bit of the coded stream, most significant first. The byte at
 * the stream pointer (global 0x51f014) is shifted left by the low five bits of the bit index
 * (global 0x51f018) as an eight bit value (an index of 8 or more leaves zero) and its top bit is
 * the result. The index plus one is stored, the pointer advances by that sum shifted right
 * arithmetically by three, and the index keeps its low three bits; the three stores happen in
 * that order. vertrix_bit_reader_next in bit_reader.h is the same on a native reader. */
uint32_t vertrix_port_bit_read(VertrixNativeMemory *memory);

#endif
