#ifndef RTLPLAYSCREENHEADS_H
#define RTLPLAYSCREENHEADS_H

#include "port.h"

/* Sets up the play screen with heads and bombs: loads both heads' animations (0x41e310), the
 * background and bomb images (.\IMAGE\BACKGROUND\, .\IMAGE\BOMBES\), starts the music, resets the
 * keys and timers, fades in and builds the play screen actors. */
uint32_t vertrix_port_play_screen_setup_with_heads_41cc30(PORT_SIGNATURE);

#endif
