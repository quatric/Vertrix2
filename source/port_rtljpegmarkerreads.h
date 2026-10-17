#ifndef PORT_RTLJPEGMARKERREADS_H
#define PORT_RTLJPEGMARKERREADS_H

#include "port.h"

/* libjpeg read_markers: reads markers until a start of scan or end of image, handing each one to
 * its reader. */
uint32_t vertrix_port_jpeg_read_markers_4bf940(PORT_SIGNATURE);

#endif
