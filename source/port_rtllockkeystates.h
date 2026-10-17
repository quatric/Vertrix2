#ifndef PORT_RTLLOCKKEYSTATES_H
#define PORT_RTLLOCKKEYSTATES_H

#include "port.h"

/* Answers messages 0xe701..0xe706: reads GetKeyState for Caps Lock, Num Lock, Scroll Lock or Kana
 * (masked with 1, or 0x8000 when [0x5c79c8] is set) and passes it to the handler at [msg+0x24];
 * other codes set +0x18 to 1. */
uint32_t vertrix_port_lock_key_state_query_4d5bf8(PORT_SIGNATURE);

#endif
