#ifndef RTLMPEGHUFFMANS_H
#define RTLMPEGHUFFMANS_H

#include "port.h"

/* mpg123's III_dequantize_sample (eax = xr, edx = the scale factors, ebx = gr_info, ecx = the
 * sample rate, part2bits on the stack): returns 0, or 1 when the granule read past its bits. */
uint32_t vertrix_port_mpeg_huffman_decode_407830(PORT_SIGNATURE);

#endif
