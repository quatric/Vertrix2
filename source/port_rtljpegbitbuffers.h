#ifndef PORT_RTLJPEGBITBUFFERS_H
#define PORT_RTLJPEGBITBUFFERS_H

#include "port.h"

/* libjpeg jpeg_fill_bit_buffer: loads bytes into the Huffman bit buffer, refilling the source and
 * stopping at a marker; past a marker it pads with zeros and warns once. */
uint32_t vertrix_port_jpeg_fill_bit_buffer_4bbf30(PORT_SIGNATURE);

#endif
