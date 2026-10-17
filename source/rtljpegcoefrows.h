#ifndef RTLJPEGCOEFROWS_H
#define RTLJPEGCOEFROWS_H

#include "port.h"

/* libjpeg decompress_data for buffered-image mode: consume input until ahead of the output, then
 * the inverse DCT of one iMCU row of every needed component. */
uint32_t vertrix_port_jpeg_decompress_coef_rows_4ba470(PORT_SIGNATURE);

#endif
