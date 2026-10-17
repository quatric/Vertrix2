#ifndef PORT_RTLDOSERRORS_H
#define PORT_RTLDOSERRORS_H

#include "port.h"

/* Maps a Windows error code (the stack argument) to the C runtime errno value. */
uint32_t vertrix_port_rtl_dos_error_to_errno_4d9ae0(PORT_SIGNATURE);

#endif
