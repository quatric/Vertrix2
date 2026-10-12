#ifndef VERTRIX_PORT_IMDCT_H
#define VERTRIX_PORT_IMDCT_H
#include "port.h"

/* Original 0x4088e0 (eax = 18 singles, edx = the previous block's overlap, ebx = this block's
 * overlap, ecx = the window, stack = the output, 0x80 bytes a sample): the long-block inverse
 * transform of one subband. The inputs are summed in place, then five butterflies each give two
 * overlap values (windowed) and two outputs (windowed, plus the previous overlap). Every
 * operation is a call to the single-precision helpers. */
uint32_t vertrix_port_imdct_long(PORT_SIGNATURE);

#endif
