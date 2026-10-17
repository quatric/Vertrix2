#ifndef PORT_RTLOWNERNOTES_H
#define PORT_RTLOWNERNOTES_H

#include "port.h"

/* Calls the object's method +0xd0, then hands it with its +0x58 and +0x4c fields to the thread
 * record's handler. */
uint32_t vertrix_port_rtl_object_notify_owner_4d7140(PORT_SIGNATURE);

#endif
