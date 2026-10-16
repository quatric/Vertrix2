#ifndef PORT_RTLLOBBYSCREENS_H
#define PORT_RTLLOBBYSCREENS_H

#include "port.h"

/* Builds the 'LOBBY LAUNCH' screen at 0x4633b0, using a mode argument passed in eax and saved at
 * ebp-0x1ac. */
uint32_t vertrix_port_lobby_launch_screen_4633b0(PORT_SIGNATURE);

#endif
