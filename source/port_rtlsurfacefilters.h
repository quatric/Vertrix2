#ifndef PORT_RTLSURFACEFILTERS_H
#define PORT_RTLSURFACEFILTERS_H

#include "port.h"

/* Loops over the rows of an object (count at +0x24, descriptor at +0xd8), clipped by
 * +0x90/+0x98/+0x9c/+0x140. */
uint32_t vertrix_port_surface_filter_rows_4ba7b0(PORT_SIGNATURE);

#endif
