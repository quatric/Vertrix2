#ifndef VERTRIX_PORT_LAYOUT_H
#define VERTRIX_PORT_LAYOUT_H
#include "port.h"

/* Clean ports of the actor layout (port.h). */

/* Original 0x4ad870 (eax = actor): place the actor against its anchor (+0x104, an actor with an
 * image at +0xb4). The anchor's position is clamped to the screen ([0x544070] +0x208 by +0x20c)
 * and its index in the screen's scale map kept at 0x5bb648; the scale is the anchor's +0x44, or
 * with its +0x91 set the screen's (+0x221, or 1 + the map byte when +0x220 is set). The actor's
 * alignment bytes (+0xfc horizontal, +0xfd vertical: 0 centre, 1 to 3 edges) and offsets (+0xfe,
 * +0x100) then give its +0xe, +0x16 and +0x1e from the anchor's image (scaled by sixteenths with
 * the table at 0x5c1b00 when the scale is not 16). The working values live in the globals
 * 0x5bb638 to 0x5bb688; bx, cx, si and di are stored back to 0x5bb666, 0x5bb664, 0x5bb684 and
 * 0x5bb656 as the original leaves them. Returns the actor (the anchor when it has no image); edx
 * is unchanged. */
uint32_t vertrix_port_actor_layout(PORT_SIGNATURE);

#endif
