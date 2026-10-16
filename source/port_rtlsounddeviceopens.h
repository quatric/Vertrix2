#ifndef PORT_RTLSOUNDDEVICEOPENS_H
#define PORT_RTLSOUNDDEVICEOPENS_H

#include "port.h"

/* At 0x40b6e0 the routine zeroes the 0x79c-byte sound state at 0x52f170 and returns 2 if its config
 * argument is null. */
uint32_t vertrix_port_sound_device_open_40b6e0(PORT_SIGNATURE);

#endif
