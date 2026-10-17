#ifndef RTLNETWORKHANDLES_H
#define RTLNETWORKHANDLES_H

#include "port.h"

/* Closes the network session's handles (0x5bb47c..0x5bb4a4) and clears them. */
uint32_t vertrix_port_network_handles_close_48b970(PORT_SIGNATURE);

#endif
