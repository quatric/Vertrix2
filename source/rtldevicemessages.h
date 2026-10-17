#ifndef RTLDEVICEMESSAGES_H
#define RTLDEVICEMESSAGES_H

#include "port.h"

/* The event callback of the sound device's COM object: six events go on to the object at
 * 0x558ccc; others return 0. */
uint32_t vertrix_port_device_message_dispatch_47eab0(PORT_SIGNATURE);

#endif
