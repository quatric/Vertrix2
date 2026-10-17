#ifndef PORT_RTLJPEGCOLORSELECTS_H
#define PORT_RTLJPEGCOLORSELECTS_H

#include "port.h"

/* libjpeg two-pass quantizer select_colors: median-cut box splitting over the 32x64x32 histogram,
 * then one colormap entry per box. */
uint32_t vertrix_port_jpeg_quant2_select_colors_4c90e0(PORT_SIGNATURE);

#endif
