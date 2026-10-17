#ifndef RTLGUARDEDCALLS_H
#define RTLGUARDEDCALLS_H

#include "port.h"

/* Calls an object's method +0x38 under a try frame and returns its result (0 when it raises). */
uint32_t vertrix_port_guarded_method38_call_489a10(PORT_SIGNATURE);

#endif
