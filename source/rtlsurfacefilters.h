#ifndef RTLSURFACEFILTERS_H
#define RTLSURFACEFILTERS_H

#include "port.h"

/* libjpeg decompress_smooth_data (eax = cinfo, edx = output_buf): returns 0 suspended, 3 row
 * completed or 4 scan completed, in eax and edx. */
uint32_t vertrix_port_surface_filter_rows_4ba7b0(PORT_SIGNATURE);

#endif
