#ifndef PORT_RTLHIGHSCOREMENUS_H
#define PORT_RTLHIGHSCOREMENUS_H

#include "port.h"

/* At 0x4651b0, places a 0x11b x 0xb4 label box (0x460a40) centred on the screen size read from
 * [0x558c7c] and adds the 'HIGHS' title (0x50e4a7) through 0x460c50. */
uint32_t vertrix_port_high_scores_menu_build_4651b0(PORT_SIGNATURE);

#endif
