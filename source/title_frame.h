#ifndef VERTRIX_TITLE_FRAME_H
#define VERTRIX_TITLE_FRAME_H
#include "actor_build.h"
#include "call_glue.h"
#include <stdint.h>

/* Original 0x41c7b0: the idle handler that runs one frame of the title and menu screens. The form
 * (EAX) is passed on to the stage routines; the routine installs the next handler itself through
 * 0x418840 (the handlers 0x41c9e0 and 0x41cbb0) when the requested screen at 0x532a98 differs from
 * the current one at 0x532a50.
 *
 * It only orders calls: every stage, the scene lists and the transitions stay unrecovered
 * callees reached through `calls`, with the registers each one reads (EAX, and EDX where noted).
 * The static flags it tests are read through `globals` and it stores the bytes and dwords it
 * changes through the boundary store. It returns zero (the original leaves the previous
 * exception-chain pointer in EAX, which nothing reads). */
uint32_t vertrix_title_frame(const VertrixCalls *calls, const VertrixGlobals *globals,
                             uint32_t form);

#endif
