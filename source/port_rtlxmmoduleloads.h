#ifndef PORT_RTLXMMODULELOADS_H
#define PORT_RTLXMMODULELOADS_H

#include "port.h"

/* Allocates a 0x158-byte module record with vertrix_port_clear_allocate at 0x4b828c and returns
 * error 8 if that fails. */
uint32_t vertrix_port_xm_module_load_4b826f(PORT_SIGNATURE);

#endif
