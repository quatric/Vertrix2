#ifndef PORT_RTLMPEGSTEREOS_H
#define PORT_RTLMPEGSTEREOS_H

#include "port.h"

/* Applies layer III stereo processing for a granule: intensity stereo ratios from the tables at
 * 0x522f98 and 0x523098 (picked by the mode extension), with the scale factor band table at
 * 0x4f5918. */
uint32_t vertrix_port_mpeg_intensity_stereo_4083a0(PORT_SIGNATURE);

#endif
