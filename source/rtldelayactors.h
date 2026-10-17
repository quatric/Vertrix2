#ifndef RTLDELAYACTORS_H
#define RTLDELAYACTORS_H

#include "port.h"

/* Creates the actor that waits while a message is read (5000 + 180 per character of the message
 * on show) and appends it to the object list 0x54671c. */
uint32_t vertrix_port_delay_actor_spawn_471340(PORT_SIGNATURE);

#endif
