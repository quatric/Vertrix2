#ifndef PORT_RTLGAMESCREENSETUPS_H
#define PORT_RTLGAMESCREENSETUPS_H

#include "port.h"

/* Sets the view rect (0x41ab90), loads scenes 0 and 1 (0x41e280) indexed by 0x532a70, and makes
 * overlay sprites. */
uint32_t vertrix_port_game_screen_setup_424360(PORT_SIGNATURE);

#endif
