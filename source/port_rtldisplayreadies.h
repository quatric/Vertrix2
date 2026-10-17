#ifndef PORT_RTLDISPLAYREADIES_H
#define PORT_RTLDISPLAYREADIES_H

#include "port.h"

/* Returns 1 when the display object has both its first field and its +0x10 field set; otherwise it
 * continues at 0x47ed00. */
uint32_t vertrix_port_display_ready_47f410(PORT_SIGNATURE);

#endif
