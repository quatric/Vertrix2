#ifndef PORT_RTLJPEGIDCTPASSES_H
#define PORT_RTLJPEGIDCTPASSES_H

#include "port.h"

/* libjpeg start_pass for the inverse DCT: picks each component's IDCT by its scaled size (1x1, 2x2,
 * 4x4, or 8x8 by the DCT method) and copies its quantisation table into the multiplier table. */
uint32_t vertrix_port_jpeg_idct_start_pass_4bb870(PORT_SIGNATURE);

#endif
