#ifndef PORT_RTLCONSOLES_H
#define PORT_RTLCONSOLES_H

#include "port.h"

/* Device state queries, standard handle set-up and window activation */
uint32_t vertrix_port_device_state_40c160(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_standard_handles_4e0430(PORT_SIGNATURE);
uint32_t vertrix_port_rtl_window_activate_4d4e60(PORT_SIGNATURE);

#endif
