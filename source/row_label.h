#ifndef VERTRIX_ROW_LABEL_H
#define VERTRIX_ROW_LABEL_H
#include <stdint.h>

#include "actor_build.h"

/* Original 0x470b20 (al = row, edx = text, ebx the caller's register whose upper bytes reach the
 * allocator). Builds a labelled row from a frame actor and a text actor. y = word(sign extended
 * row * 0x16 + word 0x4f88ac + 1); 0x4ca000(0x170, ecx = 0xdc) allocates the frame, a non-zero
 * result going through 0x4b3100; 0x4adf20 and 0x4b54d0 (x = 2, y, width 0xdc, height 0x16) and
 * 0x4ac7b0 (period two) set it, bytes +0x52 = 9, +0x44 = 0x10, +0x94 = 1, +0x95 = 0 and
 * +0x8e = 3 and words +0x48 = 0 and the clip +0xa8..+0xae (0, 0x27f, word 0x4f88ac, 0x1df)
 * follow. The text actor (0x4ca000(0x180), a non-zero result going through 0x4b6350 with
 * ecx = 3) receives 0x4b65d0 (text, the glyph byte of 0x4f9c0b), +0x44 = 0x10, +0x4e = 0x32,
 * +0x93 = 0, +0x95 = 4, the same clip and +0x8e = 3, and 0x4b3210 links it to the frame with
 * both flags one. Returns the frame actor, zero when an actor does not resolve. */
uint32_t vertrix_row_label(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, uint32_t eax, uint32_t edx, uint32_t ebx);
#endif
