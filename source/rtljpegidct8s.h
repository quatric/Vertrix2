#ifndef RTLJPEGIDCT8S_H
#define RTLJPEGIDCT8S_H

#include "port.h"

/* libjpeg 8x8 inverse DCT with dequantisation, a shortcut for columns whose AC terms are zero, and
 * range limiting. */
uint32_t vertrix_port_jpeg_idct_8x8_4c4000(PORT_SIGNATURE);

#endif
