#ifndef PORT_RTLFORMATSCANS_H
#define PORT_RTLFORMATSCANS_H

#include "port.h"

/* Scans a format string for the printf core, handling flags (+0x10) and literal text. */
uint32_t vertrix_port_rtl_format_scan_4e4110(PORT_SIGNATURE);

#endif
