#ifndef RTLMESSAGEQUEUES_H
#define RTLMESSAGEQUEUES_H

#include "port.h"

/* Takes the next message off the network session's queue (+0x200) under the lock 0x5328f0. */
uint32_t vertrix_port_message_queue_take_48be70(PORT_SIGNATURE);

#endif
