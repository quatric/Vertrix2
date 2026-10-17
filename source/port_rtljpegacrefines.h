#ifndef PORT_RTLJPEGACREFINES_H
#define PORT_RTLJPEGACREFINES_H

#include "port.h"

/* libjpeg decode_mcu_AC_refine: one progressive AC refinement pass over an MCU, including restart
 * handling and the end-of-band run. */
uint32_t vertrix_port_jpeg_decode_ac_refine_4c2d60(PORT_SIGNATURE);

#endif
