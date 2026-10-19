#ifndef RTLDEBUGGERREPORTS_H
#define RTLDEBUGGERREPORTS_H

#include "port.h"

/* The runtime's error report: the debugger first, then the exit or the message. */
uint32_t vertrix_port_rtl_error_report_4dee73(PORT_SIGNATURE);
/* 0x4dee73's code on a caller's Port, for a routine that jumps into it (0x4e0c0c). Returns its eax
 * and leaves its edx in vertrix_lift_edx. */
uint32_t vertrix_rtl_error_report(Port *port, uint32_t text, uint32_t number);
/* The same report that only shows the message when no debugger took it. */
uint32_t vertrix_port_rtl_error_message_4e628c(PORT_SIGNATURE);

#endif
