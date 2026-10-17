#ifndef PORT_RTLPENDINGERRORS_H
#define PORT_RTLPENDINGERRORS_H

#include "port.h"

/* Checks the runtime's pending error state (0x50ba74, 0x5c8af4, 0x5c8af8) for the error reporter.
 */
uint32_t vertrix_port_rtl_pending_error_check_4ed880(PORT_SIGNATURE);

#endif
