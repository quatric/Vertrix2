#ifndef PORT_RTLALPHAEDGES_H
#define PORT_RTLALPHAEDGES_H

#include "port.h"

/* For a 32-bit image (+0x27 = 4) with alpha (+0x26 = 1): points the level tables 0x55f1f0/0x55f1f4
 * at rows edx and 100 - edx of 0x558cf0, copies the pixels, and gives each opaque pixel the average
 * colour of itself and its opaque neighbours above, below, left and right. */
uint32_t vertrix_port_image_alpha_edge_smooth_483790(PORT_SIGNATURE);

#endif
