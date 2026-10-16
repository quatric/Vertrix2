#ifndef PORT_RTLJPEGQUANTPASSES_H
#define PORT_RTLJPEGQUANTPASSES_H

#include "port.h"

/* 0x4c9550 has the structure of libjpeg's jquant2 start_pass_2_quant and is reached through a
 * method pointer. */
uint32_t vertrix_port_jpeg_quant2_start_pass_4c9550(PORT_SIGNATURE);

#endif
