#ifndef PORT_RTLSESSIONSTARTS_H
#define PORT_RTLSESSIONSTARTS_H

#include "port.h"

/* At 0x48cc30, the routine returns 0 when [edi+0x1bc] is null. */
uint32_t vertrix_port_network_session_start_48cc30(PORT_SIGNATURE);

#endif
