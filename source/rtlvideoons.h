#ifndef RTLVIDEOONS_H
#define RTLVIDEOONS_H

#include "port.h"

/* Switches the display to a video mode with DirectDraw (eax = the display, edx = its window, bl =
 * the mode); returns 1, or 0 after reporting the failure. */
uint32_t vertrix_port_video_on_484b60(PORT_SIGNATURE);

#endif
