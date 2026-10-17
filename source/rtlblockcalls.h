#ifndef RTLBLOCKCALLS_H
#define RTLBLOCKCALLS_H

#include "port.h"

/* Releases a runtime block through 0x4cea15 and returns its header's address. */
uint32_t vertrix_port_rtl_block_call_4ccb9f(PORT_SIGNATURE);

#endif
