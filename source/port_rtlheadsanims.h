#ifndef PORT_RTLHEADSANIMS_H
#define PORT_RTLHEADSANIMS_H

#include "port.h"

/* For the set index in eax, 0x41e310 reads the count at 0x53969c and returns early if it is 1 or
 * less. */
uint32_t vertrix_port_heads_anims_load_41e310(PORT_SIGNATURE);

#endif
