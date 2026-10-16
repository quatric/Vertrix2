#ifndef PORT_RTLJPEGINPUTS_H
#define PORT_RTLJPEGINPUTS_H

#include "port.h"

/* This routine matches libjpeg's jdinput consume_markers with initial_setup inlined (0x4bcea0). */
uint32_t vertrix_port_jpeg_input_consume_markers_4bcea0(PORT_SIGNATURE);

#endif
