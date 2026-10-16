#ifndef PORT_RTLJPEGMAINCONTROLLERS_H
#define PORT_RTLJPEGMAINCONTROLLERS_H

#include "port.h"

/* The routine at 0x4bdde0 matches libjpeg's jinit_d_main_controller. */
uint32_t vertrix_port_jpeg_init_main_controller_4bdde0(PORT_SIGNATURE);

#endif
