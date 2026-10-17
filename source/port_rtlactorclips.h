#ifndef PORT_RTLACTORCLIPS_H
#define PORT_RTLACTORCLIPS_H

#include "port.h"

/* Draws an actor's image clipped to the view: loads its surface (+0xb4) and position (+0xe, +0x16)
 * into the blit globals at 0x5bb7xx and copies the visible part. */
uint32_t vertrix_port_actor_draw_clipped_4b0b70(PORT_SIGNATURE);

#endif
