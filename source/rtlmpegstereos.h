#ifndef RTLMPEGSTEREOS_H
#define RTLMPEGSTEREOS_H

#include "port.h"

/* MPEG layer III intensity stereo for a granule (mpg123 III_i_stereo): the ratio tables at
 * 0x522f98..0x523258 split the left channel into both, by the band layouts at 0x4f5918. */
uint32_t vertrix_port_mpeg_intensity_stereo_4083a0(PORT_SIGNATURE);

#endif
