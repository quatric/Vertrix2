#ifndef PORT_RTLUISCREENACTORS_H
#define PORT_RTLUISCREENACTORS_H

#include "port.h"

/* 0x46b810 (4544 B; reached from the register forwarder 0x46b800 and recursively from itself at
 * 0x46c5de) first makes 73 calls to ui_companion_spawn 0x471100. */
uint32_t vertrix_port_ui_screen_actors_build_46b810(PORT_SIGNATURE);

#endif
