#ifndef PORT_RTLSURFACEBLITS_H
#define PORT_RTLSURFACEBLITS_H

#include "port.h"

/* Copies a rectangle from one surface to another, choosing the path from both surfaces' pixel sizes
 * (+0xc, +0xd) and locks (+0x10) and caching the sizes and pitches in 0x558c2c..0x558c43. */
uint32_t vertrix_port_surface_blit_47ce10(PORT_SIGNATURE);

#endif
