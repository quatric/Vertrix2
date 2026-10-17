#ifndef PORT_RTLNETWORKHANDLES_H
#define PORT_RTLNETWORKHANDLES_H

#include "port.h"

/* Unless [0x5bb4a4] is set, closes the network handles kept at 0x5bb47c. */
uint32_t vertrix_port_network_handles_close_48b970(PORT_SIGNATURE);

#endif
