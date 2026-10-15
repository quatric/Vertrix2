#ifndef PORT_WRAPPERS_H
#define PORT_WRAPPERS_H

#include "port.h"

/* Handle close, plain import call and opener without a mode routines. */
uint32_t vertrix_port_handle_close_4e59d0(PORT_SIGNATURE);
uint32_t vertrix_port_import_call_4e9d10(PORT_SIGNATURE);
uint32_t vertrix_port_open_plain_4ebb78(PORT_SIGNATURE);

#endif
