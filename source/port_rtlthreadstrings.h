#ifndef PORT_RTLTHREADSTRINGS_H
#define PORT_RTLTHREADSTRINGS_H

#include "port.h"

/* Calls 0x4cf880 with eax 0 and raises through 0x4dee00 when it returns nonzero. */
uint32_t vertrix_port_rtl_thread_string_finish_4cf8d0(PORT_SIGNATURE);

#endif
