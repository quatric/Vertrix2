#ifndef VERTRIX_PANEL_GROUP_H
#define VERTRIX_PANEL_GROUP_H
#include <stdint.h>

#include "actor_build.h"

/* Original 0x470d20 (eax = first text, edx = second text, ebx = third text, ecx = fourth text).
 * Up to four actors are registered with the list 0x54671c, in this order: a panel for a non-zero
 * first text, a text actor for a non-zero third, a panel for a non-zero second and a text actor
 * for a non-zero fourth. A panel is 0x4ca000(0x308) through 0x4b2400, 0x4adf20, 0x4ac7b0 (2),
 * the bytes +0x52 = 9, +0x4e = 0x28, +0x93, +0x94 and +0x95 = 1, the word +0x48 = 0xffec and
 * 0x4b25b0 with the ten stack arguments of 0x471020 over the globals 0x4f87fe, 0x4f8802,
 * 0x4f8806 and 0x4f880c (first) or 0x4f880e, 0x4f8812, 0x4f8816 and 0x4f881c (second). A text
 * actor is 0x4ca000(0x180) through 0x4b6350, 0x4adf20, 0x4b65d0 (the glyph byte of 0x540019, the
 * word at 0x4f8800 and a box from the words 0x4f8800, 0x4f8804, 0x4f8808, 0x4f880c, or 0x4f880e
 * with 0x4f8810, 0x4f8814, 0x4f8818, 0x4f881c), 0x4ac7b0 (2), the bytes +0x44 = 6, +0x93 and
 * +0x94 = 1, +0x95 = 5. The allocator receives the registers the previous call left. Returns the
 * eax of the last call to 0x4b5e70, or the first text when nothing was built. */
uint32_t vertrix_panel_group(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, uint32_t first, uint32_t second,
                             uint32_t third, uint32_t fourth);
#endif
