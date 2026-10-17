#ifndef PORT_RTLMESSAGEQUEUES_H
#define PORT_RTLMESSAGEQUEUES_H

#include "port.h"

/* Enters the critical section 0x5328f0 and takes the next 4-byte message from the list at +0x200
 * into ebx. */
uint32_t vertrix_port_message_queue_take_48be70(PORT_SIGNATURE);

#endif
