#ifndef PORT_RTLMPEGHUFFMANS_H
#define PORT_RTLMPEGHUFFMANS_H

#include "port.h"

/* Decodes a granule's Huffman-coded spectral values (big values through the table pairs, then the
 * count1 quadruples), reading bits through 0x404610 and 0x4046e0. */
uint32_t vertrix_port_mpeg_huffman_decode_407830(PORT_SIGNATURE);

#endif
