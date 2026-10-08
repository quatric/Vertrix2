#ifndef VERTRIX_GAME_FRAME_H
#define VERTRIX_GAME_FRAME_H
#include "actor_build.h"
#include "call_glue.h"
#include <stdint.h>

/* Original 0x41b820: the idle handler that runs one frame of the game screen, the counterpart of
 * the title handler 0x41c7b0 (title_frame.h) with three scene lists. It runs the stage routines in
 * order and, when the screen slot at 0x532a4c differs from the requested screen at 0x532a98,
 * performs the transition for the screen it is leaving: most clear the scene list and run a
 * screen routine (0x461610, 0x461790, ...), the level screens copy the four settings at
 * 0x532b54..0x532b60 to 0x532bbc..0x532bc8, reset the play state and install the next handler
 * (0x41c0c0, 0x41c160, 0x41c1d0, 0x41c240, 0x41c2b0 ...) through 0x418840.
 *
 * Every stage and screen routine stays an unrecovered callee reached through `calls`; the static
 * flags are read through `globals` and stored through the boundary store. It returns zero (the
 * original leaves the previous exception-chain pointer in EAX, which nothing reads). */
uint32_t vertrix_game_frame(const VertrixCalls *calls, const VertrixGlobals *globals,
                            uint32_t form);

#endif
