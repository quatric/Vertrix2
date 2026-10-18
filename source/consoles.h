#ifndef CONSOLES_H
#define CONSOLES_H

#include "port.h"

/* Handle close and console character write routines. */
uint32_t vertrix_port_handle_close_4e7c30(PORT_SIGNATURE);
uint32_t vertrix_port_console_put_4eda00(PORT_SIGNATURE);

#endif
