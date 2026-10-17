#ifndef RTLJPEGCOLORSELECTS_H
#define RTLJPEGCOLORSELECTS_H

#include "port.h"

/* libjpeg two-pass quantizer finish_pass1: median-cut box splitting over the 32x64x32 histogram
 * (select_colors), then one colormap entry per box. */
uint32_t vertrix_port_jpeg_quant2_select_colors_4c90e0(PORT_SIGNATURE);

#endif
