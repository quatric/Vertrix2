#ifndef PORT_RTLREADS_H
#define PORT_RTLREADS_H

#include "port.h"

/* Text to double conversion, pending error fetches and decoder scanline reads */
uint32_t vertrix_port_rtl_text_to_double_4ed79f(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_pending_error_4ed984(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_read_scanlines_4b99b0(PORT_SIGNATURE);

#endif
