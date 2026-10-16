#ifndef PORT_RTLGLOBALINITS_H
#define PORT_RTLGLOBALINITS_H

#include "port.h"

/* 0x412700 (ret at 0x413801, no callers) is a static initializer with an SEH frame. */
uint32_t vertrix_port_game_globals_init_412700(PORT_SIGNATURE);

#endif
