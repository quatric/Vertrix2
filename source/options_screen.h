#ifndef VERTRIX_OPTIONS_SCREEN_H
#define VERTRIX_OPTIONS_SCREEN_H
#include <stdint.h>

#include "actor_build.h"

/* Original 0x461fc0: the builder of the options screen (`frame` is the token for ebp, `stale` the
 * low word of the unwritten stack dword at ebp - 0x32 that reaches 0x4ac7b0 and 0x4b5e70 in ecx).
 * Six AnsiString locals are initialised (0x4ca070 and 0x4ca280); two are formatted with 0x4cdfb0
 * from the settings dwords 0x532b98 and 0x532b9c, four take the names 0x415ed0 gives for the
 * dwords 0x532ba0..0x532bac (assigned by 0x4ca370). The panel rows are laid out with the box
 * words computed from the dwords at +4 and +8 of the object [0x558c7c], then built through
 * 0x460a40 (frames), 0x460c50 (texts), 0x460ad0 and 0x460ed0 (value fields) and 0x460fa0 and
 * 0x460b60 (lists). Three actors follow (0x4ca000 with 0x4b5c60 or 0x4abd70, handlers 0x4576d0,
 * 0x457670 and 0x45c6e0, 0x4ac7b0 and 0x4b5e70 into the list 0x54671c); the dword 0x532a48 is
 * cleared (stored in *selection) and 0x4cda10 ends the routine. The original returns the saved
 * exception chain head, which is not modeled: returns 1, zero when an actor does not resolve. */
uint32_t vertrix_options_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, uint32_t frame, uint32_t stale,
                               uint32_t *selection);
#endif
