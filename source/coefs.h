#ifndef COEFS_H
#define COEFS_H

#include "port.h"

/* The image decoder's choice of block smoothing, the Huffman slow path and the application marker.
 */
uint32_t vertrix_port_block_smoothing_pick_4b9de0(PORT_SIGNATURE);
uint32_t vertrix_port_huffman_decode_slow_4bc050(PORT_SIGNATURE);
uint32_t vertrix_port_application_marker_4bf270(PORT_SIGNATURE);

#endif
