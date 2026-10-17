#ifndef PORT_RTLJPEGMERGEDCHECKS_H
#define PORT_RTLJPEGMERGEDCHECKS_H

#include "port.h"

/* libjpeg use_merged_upsample: whether the merged upsampling and colour conversion path can be used
 * (no fancy upsampling, YCbCr to 3-component RGB, 2x1 or 2x2 luma sampling and matching scaled
 * sizes). */
uint32_t vertrix_port_jpeg_use_merged_upsample_4c0b51(PORT_SIGNATURE);

#endif
