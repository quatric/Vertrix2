#ifndef PORT_RTLHANDLERTHUNKS_H
#define PORT_RTLHANDLERTHUNKS_H

#include "port.h"

/* The exception handler address the guarded routines store in their frames: a jump to 0x4e6e19. */
uint32_t vertrix_port_rtl_exception_handler_thunk_4ec1ec(PORT_SIGNATURE);

#endif
