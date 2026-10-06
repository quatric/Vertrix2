#ifndef VERTRIX_HUD_BUILDER_H
#define VERTRIX_HUD_BUILDER_H
#include <stdint.h>

#include "actor_build.h"

/* Original 0x46b810 (eax = mode, edx = selector): the builder of the game screen's decor actors.
 * Every actor goes through 0x471100 with the position taken from the layout table
 * 0x4f888a..0x4f8cba (words shifted down by 0x10), the frame dword of the table 0x4fbf28..0x4fbfdc,
 * an index and the stack arguments (selector, mode): the fixed pieces, the bonus slot grid of 7
 * rows and 4 columns (each cell is asked with 0x4178d0 for the characters [0x532a68] and [0x532a6c]
 * when the selector is -1, and creates the pairs 0x2a/0x2c and 0x2b/0x2d), the two name boxes 0x20
 * and 0x21 (when 0x4126f0 accepts them: a 0x180 text actor through 0x4ca000, 0x4b6350, 0x4adf20 and
 * 0x4b65d0, the style 0x4123d0, the byte +0x44 = 0x10, +0x110 = 1 for the selector and 0x4b5e70
 * into the list 0x54671c) and the remaining side pieces. Returns the result of the last 0x471100
 * call, zero when a label does not resolve. */
uint32_t vertrix_hud_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, uint32_t mode, uint32_t selector);
#endif
