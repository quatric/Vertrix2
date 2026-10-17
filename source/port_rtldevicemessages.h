#ifndef PORT_RTLDEVICEMESSAGES_H
#define PORT_RTLDEVICEMESSAGES_H

#include "port.h"

/* A three-argument stdcall callback (ret 0xc): message codes 5..0x16 go through the table at
 * 0x47ea64 to the methods of the device object [0x558ccc] (its vtable at +0x1c8, or 0x47ed10 and
 * 0x47eeb0) with the third argument; other codes return 0. */
uint32_t vertrix_port_device_message_dispatch_47eab0(PORT_SIGNATURE);

#endif
