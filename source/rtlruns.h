#ifndef RTLRUNS_H
#define RTLRUNS_H

#include "port.h"

/* Run-length decoding, paired actor release, colour histogram, named objects and title letter waves
 */
uint32_t vertrix_port_rle_decode_481480(PORT_SIGNATURE);
uint32_t vertrix_port_jpeg_histogram_rows_4c6ff0(PORT_SIGNATURE);
uint32_t vertrix_port_object_named_423ea0(PORT_SIGNATURE);
uint32_t vertrix_port_title_letter_wave_fly_45a910(PORT_SIGNATURE);

#endif
