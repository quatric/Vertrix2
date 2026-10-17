#ifndef PORT_RTLACTORSPANS_H
#define PORT_RTLACTORSPANS_H

#include "port.h"

/* Paints an actor onto its target surface, unless it has no image (+0x13c) or the target is 8-bit,
 * using the blit globals at 0x5bb7xx. */
uint32_t vertrix_port_actor_paint_span_4b17e0(PORT_SIGNATURE);

#endif
