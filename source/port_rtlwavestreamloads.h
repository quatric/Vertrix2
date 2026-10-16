#ifndef PORT_RTLWAVESTREAMLOADS_H
#define PORT_RTLWAVESTREAMLOADS_H

#include "port.h"

/* The routine 0x4b7e80 returns 2 when the output pointer is null, otherwise sets *out to 0. */
uint32_t vertrix_port_wave_stream_load_4b7e80(PORT_SIGNATURE);

#endif
