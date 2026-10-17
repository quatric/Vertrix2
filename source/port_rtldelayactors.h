#ifndef PORT_RTLDELAYACTORS_H
#define PORT_RTLDELAYACTORS_H

#include "port.h"

/* Creates a 0x15c-byte timing actor: update 0x457770, time scale 0x1388 + 180 * table
 * 0x53bdac[[0x532a64]], first field 0xc8, then links it through 0x4b5e70 on list 0x54671c. */
uint32_t vertrix_port_delay_actor_spawn_471340(PORT_SIGNATURE);

#endif
