#ifndef PORT_RTLJPEGSOFMARKERS_H
#define PORT_RTLJPEGSOFMARKERS_H

#include "port.h"

/* libjpeg get_sof: reads a start-of-frame marker (precision, image size, components and their
 * sampling factors and quantisation tables). */
uint32_t vertrix_port_jpeg_get_sof_4be0b0(PORT_SIGNATURE);

#endif
