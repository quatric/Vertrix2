#ifndef PORT_RTLVIDEOONS_H
#define PORT_RTLVIDEOONS_H

#include "port.h"

/* VIDEO_On: creates the DirectDraw object, sets the cooperative level and display mode, creates the
 * primary, back (MYBUFFER_Background) and transparency (MYBUFFER_Trans_Buffer) surfaces and the
 * palette, reporting failures with their DirectDraw error text. */
uint32_t vertrix_port_video_on_484b60(PORT_SIGNATURE);

#endif
