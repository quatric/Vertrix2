#ifndef PORT_RTLJPEGQUANT1STARTS_H
#define PORT_RTLJPEGQUANT1STARTS_H

#include "port.h"

/* libjpeg one-pass quantizer start_pass: picks the colour quantize routine by dither mode (none,
 * ordered or Floyd-Steinberg) and component count; an unknown mode is error 0x30. */
uint32_t vertrix_port_jpeg_quant1_start_pass_4c6a20(PORT_SIGNATURE);

#endif
