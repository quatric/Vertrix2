#ifndef RTLJPEGMCUDECODES_H
#define RTLJPEGMCUDECODES_H

#include "port.h"

/* libjpeg decode_mcu for sequential Huffman scans: decodes the DC difference and AC coefficients of
 * each block in the MCU. */
uint32_t vertrix_port_jpeg_decode_mcu_4bc1e0(PORT_SIGNATURE);

#endif
