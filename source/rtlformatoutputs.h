#ifndef RTLFORMATOUTPUTS_H
#define RTLFORMATOUTPUTS_H

#include "port.h"

/* The runtime's stream printf: locks the stream and prints through the printf core (0x4df320) with
 * the stream writer, buffering an unbuffered stream for the call. */
uint32_t vertrix_port_rtl_format_output_4e2434(PORT_SIGNATURE);

#endif
