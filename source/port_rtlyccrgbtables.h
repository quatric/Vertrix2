#ifndef PORT_RTLYCCRGBTABLES_H
#define PORT_RTLYCCRGBTABLES_H

#include "port.h"

/* The routine at 0x4bb170 makes four memory-manager calls through [[eax+4]], each asking for 0x400
 * bytes from pool 1. */
uint32_t vertrix_port_jpeg_build_ycc_rgb_table_4bb170(PORT_SIGNATURE);

#endif
