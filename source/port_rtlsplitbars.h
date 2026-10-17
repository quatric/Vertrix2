#ifndef PORT_RTLSPLITBARS_H
#define PORT_RTLSPLITBARS_H

#include "port.h"

/* Lays out and draws a two-part bar: the first child actor (+0x17c) gets width (value - min) *
 * width / (max - min) from +0x18c, +0x184, +0x188 and +0xf4, the second (+0x180) the rest, and both
 * are drawn through their vtables. */
uint32_t vertrix_port_split_bar_draw_4b3de0(PORT_SIGNATURE);

#endif
