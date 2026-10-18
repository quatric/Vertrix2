#ifndef RTLEXCEPTIONSTEPS_H
#define RTLEXCEPTIONSTEPS_H

#include "port.h"

/* Rethrows the exception being handled at the innermost frame (eax and ecx for the new one). */
uint32_t vertrix_port_exception_chain_step_4da6b6(PORT_SIGNATURE);

#endif
