#ifndef RTLHANDLERTHUNKS_H
#define RTLHANDLERTHUNKS_H

#include "port.h"

/* The exception handler the guarded routines store in their frames (a jump to 0x4e6e19): returns
 * 0 when the exception is handled here, 1 to go on searching. */
uint32_t vertrix_port_rtl_exception_handler_thunk_4ec1ec(PORT_SIGNATURE);

#endif
