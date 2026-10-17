#ifndef RTLALPHAEDGES_H
#define RTLALPHAEDGES_H

#include "port.h"

/* Smooth a 32-bit image: each pixel mixed with the average of its (opaque) neighbours above, below,
 * left and right, by a percentage. */
uint32_t vertrix_port_image_alpha_edge_smooth_483790(PORT_SIGNATURE);

#endif
