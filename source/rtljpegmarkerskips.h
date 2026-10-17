#ifndef RTLJPEGMARKERSKIPS_H
#define RTLJPEGMARKERSKIPS_H

#include "port.h"

/* At 0x4bf6a0, reads a 2-byte big-endian marker length from the source manager at [cinfo+0x18]. */
uint32_t vertrix_port_jpeg_skip_variable_marker_4bf6a0(PORT_SIGNATURE);

#endif
