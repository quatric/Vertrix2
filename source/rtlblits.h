#ifndef RTLBLITS_H
#define RTLBLITS_H

#include "port.h"

/* Keyed surface blits, run-length pictures and JPEG colour conversion */
uint32_t vertrix_port_surface_blit_keyed_47e200(PORT_SIGNATURE);
uint32_t vertrix_port_picture_decode_rle_480d60(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_ycc_rgb_convert_4bb270(PORT_SIGNATURE);

#endif
