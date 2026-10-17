#ifndef RTLJPEGSCANSETUPS_H
#define RTLJPEGSCANSETUPS_H

#include "port.h"

/* libjpeg start_input_pass with per_scan_setup and latch_quant_tables inlined: the scan's MCU
 * layout, the components' quantisation tables, then the entropy and coefficient passes. */
uint32_t vertrix_port_jpeg_per_scan_setup_4bcbc0(PORT_SIGNATURE);

#endif
