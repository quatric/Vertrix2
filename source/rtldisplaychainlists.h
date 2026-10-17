#ifndef RTLDISPLAYCHAINLISTS_H
#define RTLDISPLAYCHAINLISTS_H

#include "port.h"

/* Clears the global list at 0x532c04 (vertrix_port_children_release_4b7020), then takes a lock on
 * 0x558c9c (import 0x4f1b48). */
uint32_t vertrix_port_display_chain_list_rebuild_48c4a0(PORT_SIGNATURE);

#endif
