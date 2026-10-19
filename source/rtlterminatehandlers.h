#ifndef RTLTERMINATEHANDLERS_H
#define RTLTERMINATEHANDLERS_H

#include "port.h"

/* terminate(): the thread's terminate handler, else the exception's message, else exit(1). */
uint32_t vertrix_port_rtl_terminate_4e6c37(PORT_SIGNATURE);

/* exit(code) (0x4e078c) run in place by a routine that jumps into it, with the edx and ecx it
 * hands over; returns as the original returns under the verifier, from the buffers' release. */
uint32_t vertrix_rtl_exit(Port *port, uint32_t code, uint32_t edx, uint32_t ecx);

#endif
