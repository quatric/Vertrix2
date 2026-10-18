#ifndef RTLPUMPS_H
#define RTLPUMPS_H

#include "port.h"

/* The JPEG restart resynchronisation and the application's message pump */
uint32_t vertrix_port_jpeg_resync_restart_4c0860(PORT_SIGNATURE);
uint32_t vertrix_port_application_pump_4cc0d0(PORT_SIGNATURE);

#endif
