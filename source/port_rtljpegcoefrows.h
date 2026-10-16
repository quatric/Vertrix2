#ifndef PORT_RTLJPEGCOEFROWS_H
#define PORT_RTLJPEGCOEFROWS_H

#include "port.h"

/* At 0x4ba470, while the input counters (+0x90/+0x94) are behind the output counters (+0x98/+0x9c),
 * the routine keeps calling the consume-input hook at [[+0x1b4]], and it returns 0 if that hook
 * returns 0. */
uint32_t vertrix_port_jpeg_decompress_coef_rows_4ba470(PORT_SIGNATURE);

#endif
